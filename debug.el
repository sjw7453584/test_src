(require 'gud)

(defun debug_dbserver(&optional prog)
  "use shell command to get pids"
  ;; (interactive "sprogram to debug: ")
  (interactive)
  (setq path "/home/sunjiwen/trunk_new/sunjiwen_bigpiece/Server/bigpiece/server_api/DBSvr/bin/")
  (setq program "db_svr_2")
  (debug_program path program)

)

(defun debug_battle(&optional prog)
  "use shell command to get pids"
  ;; (interactive "sprogram to debug: ")
  (interactive)
  (setq path "/home/sunjiwen/trunk_new/sunjiwen_bigpiece/Server/bigpiece/server_api/battle_svr/bin/")
  (setq program "battle_svr_2")
  (debug_program path program)
)


(defun debug_program(path program)
  "use shell command to get pids"
  ;; (interactive "sprogram to debug: ")
  ;; (interactive)
  ;; (setq path "/home/sunjiwen/trunk_new/sunjiwen_bigpiece/Server/bigpiece/server_api/DBSvr/bin/")
  ;; (setq program "db_svr_2")
  (setq shell_cmd (format "ps -elf |grep %s  | grep -v grep|sed '1,2d'|awk -F ' ' 'END{print $4}'" program))
  (setq pid (string-to-int (shell-command-to-string shell_cmd )))
  (if  (get-buffer (concat "*gud-" program "*"))  nil (gdb (format "gdb --annotate=1 %s" (concat path program))))
  (with-current-buffer (format "*gud-%s*" program) (if  (get-buffer-process gud-comint-buffer)  (process-send-string (format "*gud-%s*" program) (format "attach %s\n" pid))
													 (progn (gdb (format "gdb --annotate=1 %s" (concat path program))) (process-send-string (format "*gud-%s*" program) (format "attach %s\n" pid)))))
  )

