(require 'gud)
(defun debug_battle(&optional prog)
  "use shell command to get pids"
  ;; (interactive "sprogram to debug: ")
  (interactive)
  (setq program "battle_svr_2")
  (setq shell_cmd (format "ps -elf |grep %s |grep signal | grep -v grep|awk -F ' ' 'END{print $4}'" program))
  (setq pid (string-to-int (shell-command-to-string shell_cmd )))
  (gdb (format "gdb --annotate=1 %s" program))
  (process-send-string (format "*gud-%s*" program) (format "attach %s\n" pid))
  )

(defun debug_dbserver(&optional prog)
  "use shell command to get pids"
  ;; (interactive "sprogram to debug: ")
  (interactive)
  (setq program "db_svr_2")
  (setq shell_cmd (format "ps -elf |grep %s |grep hrtime | grep -v grep|awk -F ' ' 'END{print $4}'" program))
  (setq pid (string-to-int (shell-command-to-string shell_cmd )))
  (gdb (format "gdb --annotate=1 %s" program))
  (process-send-string (format "*gud-%s*" program) (format "attach %s\n" pid))
  )
