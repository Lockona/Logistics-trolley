
(cl:in-package :asdf)

(defsystem "car-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "imu" :depends-on ("_package_imu"))
    (:file "_package_imu" :depends-on ("_package"))
    (:file "miiboo" :depends-on ("_package_miiboo"))
    (:file "_package_miiboo" :depends-on ("_package"))
    (:file "move" :depends-on ("_package_move"))
    (:file "_package_move" :depends-on ("_package"))
  ))