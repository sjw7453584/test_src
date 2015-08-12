#!/bin/bash
sqlFileName=$1
cat "$sqlFileName" |sed '/\/\*/,/\*\//d' |sed '/--/,/DROP TABLE IF EXISTS/d'|sed '/PRIMARY KEY/,/ENGINE=InnoDB/d'|sed '/FOREIGN_KEY_CHECKS/d' >tmpfile.txt
cat tmpfile.txt | sed "s/\`//g" |sed "s/ *//"|sed "s/ unsigned//" |sed "s/ NOT//"|sed "s/ AUTO_INCREMENT//" |sed "s/ NULL//"|sed "s/ DEFAULT//"|sed "s/ '[0-9]*'//g"|sed "s/ COMMENT//" |sed "s/([0-9]*)//"|sed "s/'//g"|sed "s/,//g"|sed "s/ CURRENT_TIMESTAMP//"|cut -d ' ' -f 1,2,3 |sed "s/ smallint/ int/" |sed "s/ varchar/ string/"|sed "s/ char/ string/" |sed "s/ tinyint/ int/" |sed "s/ blob/ string/" |sed "s/CREATE TABLE/table/" |sed "s/ timestamp/ int/"|sed "s/\r//g" >tables.txt

tableCnt=`cat tables.txt |grep "table " |sed -n '$='`
echo "${tableCnt} tables found"
exec emacs --batch -l "makeSqlStruct.el"
