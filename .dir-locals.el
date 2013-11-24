((nil
  . ((indent-tabs-mode nil)
     (tab-width 2)
     (c-basic-offset 2)
     (c-default-style "linux")
     (eval
      . (progn
          (let ((root-directory (when buffer-file-name
                                  (locate-dominating-file
                                   buffer-file-name
                                   ".dir-locals.el")))
                (project-find-file
                 (and (boundp 'project-find-file) project-find-file)))
            (unless project-find-file
              (setq compile-command (concat "mkdir " root-directory
                                            "build/ && cmake .. && make")))
            (when project-find-file
              (setq default-directory root-directory))))
      ))
  ))
