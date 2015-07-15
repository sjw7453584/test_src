(defun getpid()
  "use shell command to get pids"
  (interactive)
  (setq pid (shell-command-to-string "ps -elf |grep emacs | grep -v grep|awk -F ' ' 'END{print $4}'" ))
  (message pid)
  )
