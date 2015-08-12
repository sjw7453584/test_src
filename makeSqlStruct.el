(defun get-string-from-file (filePath)
  "Return filePath's file content."
  (with-temp-buffer
    (insert-file-contents filePath)
    (buffer-string)))

(defun getClassAndTableName (sqlTableName)
  (let ((className "Sql") (tableName ""))
	(if (string-match-p "t_" sqlTableName)
		(setq tmpName (mapcar 'upcase-initials (cdr (split-string sqlTableName "_"))))
	  (setq tmpName (mapcar 'upcase-initials  (split-string sqlTableName "_")))
  
		)
	(while tmpName
	  (setq className (concat className (car tmpName)))
	  (setq tableName (concat tableName (car tmpName)))
	  (setq tmpName (cdr tmpName))
	  )
	(list className tableName)
	)
  )

;; (setq className (car (getClassAndTableName "t_activity_info")))
;; (setq tableName (cdr (getClassAndTableName "t_activity_ifno")))

(defun construct-sql-class()
  (interactive)
  "make sql class from tables.txt"
  ;; (setq prefix "Sql")
  (setq isFirst t)
  (setq buffer_strings (split-string (get-string-from-file "tables.txt") "\n"))
  (if (file-exists-p "DataBaseStruct.hpp")
	  (setq buffer (find-file-noselect "DataBaseStruct.hpp"))
	(setq buffer (create-file-buffer "DataBaseStruct.hpp"))
	)
  (set-buffer buffer)
  (erase-buffer)

  (princ "#ifndef _DATABASESTRUCT_H_\n#define _DATABASESTRUCT_H_\n" buffer)
  (princ "#include <string>\n#include <vector>\n#include \"gt/log/log.h\"\n#include \"DataParamType.h\"\n#include <math.h>\n#include \"CommDef.h\"\n" buffer)
  (princ "#define ToString(STR)		#STR
#define SETTYPENAME(NAME)	NAME.SetParamName(ToString(NAME), this);
#define SQL_BUFF_LEN		10240
#define MAX_USERNAME_LEN	64
#define MAX_USERID_LEN		64
#define MAX_GUILD_LEN		32
#define ATTRIBUTE_NUM		5
 
enum EDIRTY_DATA
{ 
	DIRTY_NONE= 0,
	DIRTY_UPDATE,
	DIRTY_INSERT,
	DIRTY_DELETE,
};

enum EITEM_STATUS
{
	ITEM_STATUS_NONE= 0,
	ITEM_STATUS_DELETED,
};
" buffer)
  (setq buffer_strings_tmp1 buffer_strings)

  (princ "enum ETableName\n{\n\tETableName_None =0,\n" buffer)
  (while buffer_strings_tmp1
	(setq cur_string1 (car buffer_strings_tmp1))
	(setq words_in_cur_strig1 (split-string cur_string1 " " ))
	(if (string= (car words_in_cur_strig1) "table")
		(progn (setq tableName1 (car (cdr words_in_cur_strig1)))
			   (princ (format "\tETableName_%s,\n" (nth 1 (getClassAndTableName tableName1))) buffer)
			   )
	  )
	(setq buffer_strings_tmp1 (cdr buffer_strings_tmp1))
	)
  (princ "};\n" buffer)
	  
  (setq buffer_strings_tmp buffer_strings)
  (while buffer_strings_tmp
	(setq cur_string (car buffer_strings_tmp))
	(setq words_in_cur_strig (split-string cur_string " " ))
	(if (string= (car words_in_cur_strig) "table")
		(if isFirst
			(progn
			  (setq isFirst nil)
			  (setq sqltableName (car (cdr words_in_cur_strig)))
			  (setq field_strings (cdr buffer_strings_tmp))

			  (princ (format "start construct class for table %s\n" sqltableName))
			  (setq className (car (getClassAndTableName sqltableName)))
			  (setq tableName (cdr (getClassAndTableName sqltableName)))

			  (princ (format "class %s : public SqlStructBase\n{\npublic:\n" className) buffer)
			  )
		  (progn
			(princ (format "end construct class for table %s\n" className))
			;; end last class
			(princ (format "public:\n\t%s()\n\t{\n\t\tSetTableIndex(ETableName_%s);\n" className tableName) buffer)
			(setq cur_field (car field_strings))
			(setq words_in_cur_field (split-string cur_field " "))
			(while ( and field_strings (not (string= cur_field "")) (not(string= (car words_in_cur_field) "table")))
			  (princ( format "\t\tSETTYPENAME(%s);\n" (car words_in_cur_field)) buffer)
			  (setq field_strings (cdr field_strings))
			  (setq cur_field (car field_strings))
			  (setq words_in_cur_field (split-string cur_field " "))
			  )
			(princ (format "\t}\n\t~%s(){}\n" className) buffer)
			(princ (format "\tvoid StructToBson(bo &boStruct)\n\t{\n\t\tbob bob%s;\n\t\tToBobStruct(bob%s);\n\t\tbobStruct = bob%s.obj();\n\t}\n" tableName tableName tableName) buffer)
			(princ (format "\tvoid BsonToStruct(bo &boStruct)\n\t{\n\t\tBoInitParam(boStruct);\n}\n") buffer)
			;; (princ (format "Query GetBaseQueryStr(uint32_t userID)\n{\nreturn QUERY(ToString(userID)<<userID);\n}\n"))
			(princ "\tbool GetUniqueKey();\n};\n" buffer)
			;;start new class
			(setq sqltableName (car (cdr words_in_cur_strig)))
			(setq field_strings (cdr buffer_strings_tmp))

			(princ (format "start construct class for table %s\n" sqltableName))
			;; (setq className (format "%s%s" prefix tableName))
			(setq className (car (getClassAndTableName sqltableName)))
			(setq tableName (cdr (getClassAndTableName sqltableName)))

			(princ (format "class %s : public SqlStructBase\n{\npublic:\n" className) buffer)
			)
		  )
	  (progn
		(or
		 (and (string=  (car (cdr words_in_cur_strig)) "int" )
				 (princ (format "\tDBParamInt32 %s;//%s\n" (car words_in_cur_strig) (nth 2 words_in_cur_strig)) buffer)
				 
				 )
		 (and (string=  (car (cdr words_in_cur_strig)) "string" )
				 (princ (format "\tDBParamString %s;//%s\n" (car words_in_cur_strig) (nth 2 words_in_cur_strig)) buffer)
				 
				 )
		 (and (string=  (car (cdr words_in_cur_strig)) "bigint" )
			  (princ (format "\tDBParamInt64 %s;//%s\n" (car words_in_cur_strig) (nth 2 words_in_cur_strig)) buffer)
			  
			  )

		)
	  ))
	(setq buffer_strings_tmp (cdr buffer_strings_tmp))
	)
  ;; end the last class
  (setq cur_field (car field_strings))
  (setq words_in_cur_field (split-string cur_field " "))
  (princ (format "public:\n\t%s()\n\t{\n\t\tSetTableIndex(ETableName_%s);\n" className tableName) buffer)

  (while (and field_strings (not (string= cur_field "")) (not(string= (car words_in_cur_field) "table")))
	(princ( format "\t\tSETTYPENAME(%s);\n" (car words_in_cur_field)) buffer)
	(setq field_strings (cdr field_strings))
	(setq cur_field (car field_strings))
	(setq words_in_cur_field (split-string cur_field " "))
	)
  (princ (format "\t}\n\t~%s(){}\n" className) buffer)
  (princ (format "\tvoid StructToBson(bo &boStruct)\n\t{\n\t\tbob bob%s;\n\t\tToBobStruct(bob%s);\n\t\tbobStruct = bob%s.obj();\n\t}\n" tableName tableName tableName) buffer)
  (princ (format "\tvoid BsonToStruct(bo &boStruct)\n\t{\n\t\tBoInitParam(boStruct);\n\t}\n") buffer)
  ;; (princ (format "Query GetBaseQueryStr(uint32_t userID)\n{\nreturn QUERY(ToString(userID)<<userID);\n}\n"))
  (princ "\tbool GetUniqueKey();\n};" buffer)
  (save-buffer)

  ;;hpp construct done ,now cpp begins
  
  (if (file-exists-p "DataBaseStruct.cpp")
	  (setq buffer (find-file-noselect "DataBaseStruct.cpp"))
	(setq buffer (create-file-buffer "DataBaseStruct.cpp"))
	)
  (set-buffer buffer)
  (erase-buffer)
  (princ "#include \"gt/stdafx.h\"
#include \"gt/log/log.h\"
#include \"DataBaseStruct.h\"
#include \"netproxy.h\"
#include <sstream>
void SqlStructBase::SetInsert(long long lUserId)
{
	isdirty = DIRTY_INSERT;
}

void SqlStructBase::SetUpdate(long long lUserId)
{
	isdirty = DIRTY_UPDATE;
}

void SqlStructBase::SetDelete(long long lUserId)
{
	isdirty = DIRTY_DELETE;
}

void SqlStructBase::SetNone()
{
	isdirty = DIRTY_NONE;
}

bool SqlStructBase::NeedSave()
{
	if (isdirty == DIRTY_NONE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void SqlStructBase::SetTableIndex(int index)
{
	tableindex = index;
}

int	 SqlStructBase::GetTableIndex()
{
	return tableindex;
}

void SqlStructBase::AddTypeToVec(DBParamType* pType)
{
	vParam.push_back(pType);
}

void SqlStructBase::ToBobStruct(bob &bobStruct)
{
	int vsize = vParam.size();
	for (int i=0; i<vsize; ++i)
	{
		vParam[i]->AppendToBo(bobStruct);
	}
}

void SqlStructBase::BoInitParam(bo &boStrue)
{
	int vsize = vParam.size();
	for (int i=0; i<vsize; ++i)
	{
		vParam[i]->GetFieldToVal(boStrue);
	}
}
" buffer)


  (setq buffer_strings_tmp buffer_strings)
  (while buffer_strings_tmp
	(setq cur_string (car buffer_strings_tmp))
	(setq words_in_cur_strig (split-string cur_string " " ))
	(if (string= (car words_in_cur_strig) "table")
		(progn 
		(setq sqltableName (car (cdr words_in_cur_strig)))
	  
		(setq className (car (getClassAndTableName sqltableName)))
		;; (setq tableName (cdr (getClassAndTableName sqltableName)))
		(princ (format "bool %s::GetUniqueKey()\n{\n\t string sTableName = GetTableNameByETableName(GetTableIndex());\n\tstring m_sDbName = g_pNetProxy->m_DbBaseConn.GetDBName();\n\treturn g_pNetProxy->m_DbBaseConn.GetDBConn().ensureIndex(m_sDbName + \".\" + sTableName, BSON(ToString(lUserId)<<1<<ToString(reportId)<<1), /*unique*/true);\n}\n" className) buffer)
		)
	  )
	(setq buffer_strings_tmp (cdr buffer_strings_tmp))
	)
  (save-buffer)
  )

(construct-sql-class)
(delete-file "tables.txt")
(delete-file "tmpfile.txt")
