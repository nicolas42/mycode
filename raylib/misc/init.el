(setq ring-bell-function 'ignore)
(setq visible-bell t)

(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(default ((t (:foreground "#d3b58d" :background "#041818"))))
 '(custom-group-tag-face ((t (:underline t :foreground "lightblue"))) t)
 '(custom-variable-tag-face ((t (:underline t :foreground "lightblue"))) t)
 '(font-lock-builtin-face ((t nil)))
 ; '(font-lock-comment-face ((t (:foreground "yellow"))))
 '(font-lock-comment-face ((t (:foreground "#3fdf5f"))))
 '(font-lock-function-name-face ((((class color) (background dark)) (:foreground "white")))) 
 '(font-lock-keyword-face ((t (:foreground "white" ))))
 ; '(font-lock-string-face ((t (:foreground "gray160" :background "gray16"))))
 '(font-lock-string-face ((t (:foreground "#0fdfaf"))))
 '(font-lock-variable-name-face ((((class color) (background dark)) (:foreground "#c8d4ec"))))  
; '(font-lock-warning-face ((t (:foreground "#695a46"))))
 '(font-lock-warning-face ((t (:foreground "#504038"))))
 '(highlight ((t (:foreground "navyblue" :background "darkseagreen2"))))
 '(mode-line ((t (:inverse-video t))))
 '(region ((t (:background "blue"))))
 '(widget-field-face ((t (:foreground "white"))) t)
 '(widget-single-line-field-face ((t (:background "darkgray"))) t))

(global-font-lock-mode 1)
(set-cursor-color "lightgreen")
(set-background-color "#072626")
(global-set-key [C-return] 'save-buffer)

;(set-face-attribute 'default nil :font "Anonymous Pro-14")
; (set-face-attribute 'default nil :font "Consolas-18")
(set-frame-font "Monaco-18" nil t)

(set-face-foreground 'font-lock-builtin-face "lightgreen")


(setq make-backup-files nil)  ; stop creating backup~ files
(setq auto-save-default nil)  ; stop creating #autosave# files

; (setq backup-directory-alist `(("." . "~/.emacs.d/backups"))) ; change the directory to "~/.emacs.d/backups"
; (setq auto-save-file-name-transforms `((".*" "~/.emacs.d/auto-save-list/" t))) ; change the directory to "~/.emacs.d/auto-save-list/"
