;; Auto-generated. Do not edit!


(when (boundp 'test::test)
  (if (not (find-package "TEST"))
    (make-package "TEST"))
  (shadow 'test (find-package "TEST")))
(unless (find-package "TEST::TEST")
  (make-package "TEST::TEST"))
(unless (find-package "TEST::TESTREQUEST")
  (make-package "TEST::TESTREQUEST"))
(unless (find-package "TEST::TESTRESPONSE")
  (make-package "TEST::TESTRESPONSE"))

(in-package "ROS")





(intern "*OPEN*" (find-package "TEST::TESTREQUEST"))
(shadow '*OPEN* (find-package "TEST::TESTREQUEST"))
(defconstant test::testRequest::*OPEN* 1)
(intern "*CLOSE*" (find-package "TEST::TESTREQUEST"))
(shadow '*CLOSE* (find-package "TEST::TESTREQUEST"))
(defconstant test::testRequest::*CLOSE* 0)

(defun test::testRequest-to-symbol (const)
  (cond
        ((= const 1) 'test::testRequest::*open*)
        ((= const 0) 'test::testRequest::*close*)
        (t nil)))

(defclass test::testRequest
  :super ros::object
  :slots (_status ))

(defmethod test::testRequest
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

(defclass test::testResponse
  :super ros::object
  :slots (_result ))

(defmethod test::testResponse
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

(defclass test::test
  :super ros::object
  :slots ())

(setf (get test::test :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get test::test :datatype-) "test/test")
(setf (get test::test :request) test::testRequest)
(setf (get test::test :response) test::testResponse)

(defmethod test::testRequest
  (:response () (instance test::testResponse :init)))

(setf (get test::testRequest :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get test::testRequest :datatype-) "test/testRequest")
(setf (get test::testRequest :definition-)
      "uint8 status
uint8 open = 1
uint8 close = 0
---
uint8 result
")

(setf (get test::testResponse :md5sum-) "561098128dce463abb21b321b22f8a07")
(setf (get test::testResponse :datatype-) "test/testResponse")
(setf (get test::testResponse :definition-)
      "uint8 status
uint8 open = 1
uint8 close = 0
---
uint8 result
")



(provide :test/test "561098128dce463abb21b321b22f8a07")


