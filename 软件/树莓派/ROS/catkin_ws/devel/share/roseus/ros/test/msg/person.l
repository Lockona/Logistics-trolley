;; Auto-generated. Do not edit!


(when (boundp 'test::person)
  (if (not (find-package "TEST"))
    (make-package "TEST"))
  (shadow 'person (find-package "TEST")))
(unless (find-package "TEST::PERSON")
  (make-package "TEST::PERSON"))

(in-package "ROS")
;;//! \htmlinclude person.msg.html


(intern "*MALE*" (find-package "TEST::PERSON"))
(shadow '*MALE* (find-package "TEST::PERSON"))
(defconstant test::person::*MALE* 0)
(intern "*FEMALE*" (find-package "TEST::PERSON"))
(shadow '*FEMALE* (find-package "TEST::PERSON"))
(defconstant test::person::*FEMALE* 1)
(intern "*UNKNOW*" (find-package "TEST::PERSON"))
(shadow '*UNKNOW* (find-package "TEST::PERSON"))
(defconstant test::person::*UNKNOW* 2)

(defun test::person-to-symbol (const)
  (cond
        ((= const 0) 'test::person::*male*)
        ((= const 1) 'test::person::*female*)
        ((= const 2) 'test::person::*unknow*)
        (t nil)))

(defclass test::person
  :super ros::object
  :slots (_name _sex _age ))

(defmethod test::person
  (:init
   (&key
    ((:name __name) "")
    ((:sex __sex) 0)
    ((:age __age) 0)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _sex (round __sex))
   (setq _age (round __age))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:sex
   (&optional __sex)
   (if __sex (setq _sex __sex)) _sex)
  (:age
   (&optional __age)
   (if __age (setq _age __age)) _age)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; uint8 _sex
    1
    ;; uint8 _age
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; uint8 _sex
       (write-byte _sex s)
     ;; uint8 _age
       (write-byte _age s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _sex
     (setq _sex (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _age
     (setq _age (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get test::person :md5sum-) "f8ac7f42dd02e4aea0ff112097d249f1")
(setf (get test::person :datatype-) "test/person")
(setf (get test::person :definition-)
      "string name
uint8 sex
uint8 age

uint8 male = 0
uint8 female = 1
uint8 unknow = 2
")



(provide :test/person "f8ac7f42dd02e4aea0ff112097d249f1")


