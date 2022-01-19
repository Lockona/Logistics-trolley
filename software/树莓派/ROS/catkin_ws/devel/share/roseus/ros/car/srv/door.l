;; Auto-generated. Do not edit!


(when (boundp 'car::door)
  (if (not (find-package "CAR"))
    (make-package "CAR"))
  (shadow 'door (find-package "CAR")))
(unless (find-package "CAR::DOOR")
  (make-package "CAR::DOOR"))
(unless (find-package "CAR::DOORREQUEST")
  (make-package "CAR::DOORREQUEST"))
(unless (find-package "CAR::DOORRESPONSE")
  (make-package "CAR::DOORRESPONSE"))

(in-package "ROS")





(intern "*OPEN*" (find-package "CAR::DOORREQUEST"))
(shadow '*OPEN* (find-package "CAR::DOORREQUEST"))
(defconstant car::doorRequest::*OPEN* 1)
(intern "*CLOSE*" (find-package "CAR::DOORREQUEST"))
(shadow '*CLOSE* (find-package "CAR::DOORREQUEST"))
(defconstant car::doorRequest::*CLOSE* 0)

(defun car::doorRequest-to-symbol (const)
  (cond
        ((= const 1) 'car::doorRequest::*open*)
        ((= const 0) 'car::doorRequest::*close*)
        (t nil)))

(defclass car::doorRequest
  :super ros::object
  :slots (_status ))

(defmethod car::doorRequest
  (:init
   (&key
    ((:status __status) 0)
    )
   (send-super :init)
   (setq _status (round __status))
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; uint8 _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _status
       (write-byte _status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass car::doorResponse
  :super ros::object
  :slots (_result ))

(defmethod car::doorResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; uint8 _result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _result
       (write-byte _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _result
     (setq _result (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass car::door
  :super ros::object
  :slots ())

(setf (get car::door :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get car::door :datatype-) "car/door")
(setf (get car::door :request) car::doorRequest)
(setf (get car::door :response) car::doorResponse)

(defmethod car::doorRequest
  (:response () (instance car::doorResponse :init)))

(setf (get car::doorRequest :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get car::doorRequest :datatype-) "car/doorRequest")
(setf (get car::doorRequest :definition-)
      "uint8 status
uint8 open = 1
uint8 close = 0
---
uint8 result
")

(setf (get car::doorResponse :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get car::doorResponse :datatype-) "car/doorResponse")
(setf (get car::doorResponse :definition-)
      "uint8 status
uint8 open = 1
uint8 close = 0
---
uint8 result
")



(provide :car/door "561098128dce463abb21b321b22f8a07")


