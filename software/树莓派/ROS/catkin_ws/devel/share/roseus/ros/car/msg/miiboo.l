;; Auto-generated. Do not edit!


(when (boundp 'car::miiboo)
  (if (not (find-package "CAR"))
    (make-package "CAR"))
  (shadow 'miiboo (find-package "CAR")))
(unless (find-package "CAR::MIIBOO")
  (make-package "CAR::MIIBOO"))

(in-package "ROS")
;;//! \htmlinclude miiboo.msg.html


(defclass car::miiboo
  :super ros::object
  :slots (_frame_id _left_wheel_speed _right_wheel_speed _angle ))

(defmethod car::miiboo
  (:init
   (&key
    ((:frame_id __frame_id) 0)
    ((:left_wheel_speed __left_wheel_speed) 0)
    ((:right_wheel_speed __right_wheel_speed) 0)
    ((:angle __angle) (instance car::imu :init))
    )
   (send-super :init)
   (setq _frame_id (round __frame_id))
   (setq _left_wheel_speed (round __left_wheel_speed))
   (setq _right_wheel_speed (round __right_wheel_speed))
   (setq _angle __angle)
   self)
  (:frame_id
   (&optional __frame_id)
   (if __frame_id (setq _frame_id __frame_id)) _frame_id)
  (:left_wheel_speed
   (&optional __left_wheel_speed)
   (if __left_wheel_speed (setq _left_wheel_speed __left_wheel_speed)) _left_wheel_speed)
  (:right_wheel_speed
   (&optional __right_wheel_speed)
   (if __right_wheel_speed (setq _right_wheel_speed __right_wheel_speed)) _right_wheel_speed)
  (:angle
   (&rest __angle)
   (if (keywordp (car __angle))
       (send* _angle __angle)
     (progn
       (if __angle (setq _angle (car __angle)))
       _angle)))
  (:serialization-length
   ()
   (+
    ;; uint32 _frame_id
    4
    ;; int16 _left_wheel_speed
    2
    ;; int16 _right_wheel_speed
    2
    ;; car/imu _angle
    (send _angle :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _frame_id
       (write-long _frame_id s)
     ;; int16 _left_wheel_speed
       (write-word _left_wheel_speed s)
     ;; int16 _right_wheel_speed
       (write-word _right_wheel_speed s)
     ;; car/imu _angle
       (send _angle :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _frame_id
     (setq _frame_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int16 _left_wheel_speed
     (setq _left_wheel_speed (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _right_wheel_speed
     (setq _right_wheel_speed (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; car/imu _angle
     (send _angle :deserialize buf ptr-) (incf ptr- (send _angle :serialization-length))
   ;;
   self)
  )

(setf (get car::miiboo :md5sum-) "a9222de228ec580804ecbcde4d74572f")
(setf (get car::miiboo :datatype-) "car/miiboo")
(setf (get car::miiboo :definition-)
      "uint32 frame_id
int16 left_wheel_speed
int16 right_wheel_speed
imu angle 
================================================================================
MSG: car/imu
   float64 roll
    float64 pitch
    float64 yaw
")



(provide :car/miiboo "a9222de228ec580804ecbcde4d74572f")


