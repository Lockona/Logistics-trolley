;; Auto-generated. Do not edit!


(when (boundp 'car::move)
  (if (not (find-package "CAR"))
    (make-package "CAR"))
  (shadow 'move (find-package "CAR")))
(unless (find-package "CAR::MOVE")
  (make-package "CAR::MOVE"))

(in-package "ROS")
;;//! \htmlinclude move.msg.html


(defclass car::move
  :super ros::object
  :slots (_speed _angle ))

(defmethod car::move
  (:init
   (&key
    ((:speed __speed) 0)
    ((:angle __angle) 0)
    )
   (send-super :init)
   (setq _speed (round __speed))
   (setq _angle (round __angle))
   self)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; uint8 _speed
    1
    ;; uint16 _angle
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _speed
       (write-byte _speed s)
     ;; uint16 _angle
       (write-word _angle s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _speed
     (setq _speed (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _angle
     (setq _angle (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get car::move :md5sum-) "597e65a9308a300a178585c76dd2bae5")
(setf (get car::move :datatype-) "car/move")
(setf (get car::move :definition-)
      "uint8 speed
uint16 angle
")



(provide :car/move "597e65a9308a300a178585c76dd2bae5")


