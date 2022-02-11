;; Auto-generated. Do not edit!


(when (boundp 'car::odom)
  (if (not (find-package "CAR"))
    (make-package "CAR"))
  (shadow 'odom (find-package "CAR")))
(unless (find-package "CAR::ODOM")
  (make-package "CAR::ODOM"))

(in-package "ROS")
;;//! \htmlinclude odom.msg.html


(defclass car::odom
  :super ros::object
  :slots (_position_x _position_y _oriention _velocity_linear _velocity_angular ))

(defmethod car::odom
  (:init
   (&key
    ((:position_x __position_x) 0.0)
    ((:position_y __position_y) 0.0)
    ((:oriention __oriention) 0.0)
    ((:velocity_linear __velocity_linear) 0.0)
    ((:velocity_angular __velocity_angular) 0.0)
    )
   (send-super :init)
   (setq _position_x (float __position_x))
   (setq _position_y (float __position_y))
   (setq _oriention (float __oriention))
   (setq _velocity_linear (float __velocity_linear))
   (setq _velocity_angular (float __velocity_angular))
   self)
  (:position_x
   (&optional __position_x)
   (if __position_x (setq _position_x __position_x)) _position_x)
  (:position_y
   (&optional __position_y)
   (if __position_y (setq _position_y __position_y)) _position_y)
  (:oriention
   (&optional __oriention)
   (if __oriention (setq _oriention __oriention)) _oriention)
  (:velocity_linear
   (&optional __velocity_linear)
   (if __velocity_linear (setq _velocity_linear __velocity_linear)) _velocity_linear)
  (:velocity_angular
   (&optional __velocity_angular)
   (if __velocity_angular (setq _velocity_angular __velocity_angular)) _velocity_angular)
  (:serialization-length
   ()
   (+
    ;; float32 _position_x
    4
    ;; float32 _position_y
    4
    ;; float32 _oriention
    4
    ;; float32 _velocity_linear
    4
    ;; float32 _velocity_angular
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _position_x
       (sys::poke _position_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _position_y
       (sys::poke _position_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _oriention
       (sys::poke _oriention (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _velocity_linear
       (sys::poke _velocity_linear (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _velocity_angular
       (sys::poke _velocity_angular (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _position_x
     (setq _position_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _position_y
     (setq _position_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _oriention
     (setq _oriention (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _velocity_linear
     (setq _velocity_linear (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _velocity_angular
     (setq _velocity_angular (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get car::odom :md5sum-) "188ac42e6aff59c7fe2517b8262a562c")
(setf (get car::odom :datatype-) "car/odom")
(setf (get car::odom :definition-)
      "float32 position_x
float32 position_y
float32 oriention
float32 velocity_linear
float32 velocity_angular
")



(provide :car/odom "188ac42e6aff59c7fe2517b8262a562c")


