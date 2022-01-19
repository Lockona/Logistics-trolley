
(cl:in-package :asdf)

(defsystem "car-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "door" :depends-on ("_package_door"))
    (:file "_package_door" :depends-on ("_package"))
  ))