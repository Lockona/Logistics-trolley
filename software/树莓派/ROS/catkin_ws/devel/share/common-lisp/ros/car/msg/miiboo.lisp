; Auto-generated. Do not edit!


(cl:in-package car-msg)


;//! \htmlinclude miiboo.msg.html

(cl:defclass <miiboo> (roslisp-msg-protocol:ros-message)
  ((frame_id
    :reader frame_id
    :initarg :frame_id
    :type cl:integer
    :initform 0)
   (left_wheel_speed
    :reader left_wheel_speed
    :initarg :left_wheel_speed
    :type cl:fixnum
    :initform 0)
   (right_wheel_speed
    :reader right_wheel_speed
    :initarg :right_wheel_speed
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type car-msg:imu
    :initform (cl:make-instance 'car-msg:imu)))
)

(cl:defclass miiboo (<miiboo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <miiboo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'miiboo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car-msg:<miiboo> is deprecated: use car-msg:miiboo instead.")))

(cl:ensure-generic-function 'frame_id-val :lambda-list '(m))
(cl:defmethod frame_id-val ((m <miiboo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:frame_id-val is deprecated.  Use car-msg:frame_id instead.")
  (frame_id m))

(cl:ensure-generic-function 'left_wheel_speed-val :lambda-list '(m))
(cl:defmethod left_wheel_speed-val ((m <miiboo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:left_wheel_speed-val is deprecated.  Use car-msg:left_wheel_speed instead.")
  (left_wheel_speed m))

(cl:ensure-generic-function 'right_wheel_speed-val :lambda-list '(m))
(cl:defmethod right_wheel_speed-val ((m <miiboo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:right_wheel_speed-val is deprecated.  Use car-msg:right_wheel_speed instead.")
  (right_wheel_speed m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <miiboo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:angle-val is deprecated.  Use car-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <miiboo>) ostream)
  "Serializes a message object of type '<miiboo>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'frame_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'frame_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'frame_id)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'left_wheel_speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'right_wheel_speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'angle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <miiboo>) istream)
  "Deserializes a message object of type '<miiboo>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'frame_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'frame_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'frame_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'frame_id)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'left_wheel_speed) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'right_wheel_speed) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'angle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<miiboo>)))
  "Returns string type for a message object of type '<miiboo>"
  "car/miiboo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'miiboo)))
  "Returns string type for a message object of type 'miiboo"
  "car/miiboo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<miiboo>)))
  "Returns md5sum for a message object of type '<miiboo>"
  "a9222de228ec580804ecbcde4d74572f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'miiboo)))
  "Returns md5sum for a message object of type 'miiboo"
  "a9222de228ec580804ecbcde4d74572f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<miiboo>)))
  "Returns full string definition for message of type '<miiboo>"
  (cl:format cl:nil "uint32 frame_id~%int16 left_wheel_speed~%int16 right_wheel_speed~%imu angle ~%================================================================================~%MSG: car/imu~%   float64 roll~%    float64 pitch~%    float64 yaw~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'miiboo)))
  "Returns full string definition for message of type 'miiboo"
  (cl:format cl:nil "uint32 frame_id~%int16 left_wheel_speed~%int16 right_wheel_speed~%imu angle ~%================================================================================~%MSG: car/imu~%   float64 roll~%    float64 pitch~%    float64 yaw~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <miiboo>))
  (cl:+ 0
     4
     2
     2
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'angle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <miiboo>))
  "Converts a ROS message object to a list"
  (cl:list 'miiboo
    (cl:cons ':frame_id (frame_id msg))
    (cl:cons ':left_wheel_speed (left_wheel_speed msg))
    (cl:cons ':right_wheel_speed (right_wheel_speed msg))
    (cl:cons ':angle (angle msg))
))
