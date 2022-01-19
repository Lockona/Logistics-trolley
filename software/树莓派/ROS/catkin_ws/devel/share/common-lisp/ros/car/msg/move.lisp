; Auto-generated. Do not edit!


(cl:in-package car-msg)


;//! \htmlinclude move.msg.html

(cl:defclass <move> (roslisp-msg-protocol:ros-message)
  ((speed
    :reader speed
    :initarg :speed
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:fixnum
    :initform 0))
)

(cl:defclass move (<move>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <move>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'move)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car-msg:<move> is deprecated: use car-msg:move instead.")))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:speed-val is deprecated.  Use car-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <move>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:angle-val is deprecated.  Use car-msg:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <move>) ostream)
  "Serializes a message object of type '<move>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'angle)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'angle)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <move>) istream)
  "Deserializes a message object of type '<move>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'speed)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'angle)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'angle)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<move>)))
  "Returns string type for a message object of type '<move>"
  "car/move")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'move)))
  "Returns string type for a message object of type 'move"
  "car/move")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<move>)))
  "Returns md5sum for a message object of type '<move>"
  "597e65a9308a300a178585c76dd2bae5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'move)))
  "Returns md5sum for a message object of type 'move"
  "597e65a9308a300a178585c76dd2bae5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<move>)))
  "Returns full string definition for message of type '<move>"
  (cl:format cl:nil "uint8 speed~%uint16 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'move)))
  "Returns full string definition for message of type 'move"
  (cl:format cl:nil "uint8 speed~%uint16 angle~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <move>))
  (cl:+ 0
     1
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <move>))
  "Converts a ROS message object to a list"
  (cl:list 'move
    (cl:cons ':speed (speed msg))
    (cl:cons ':angle (angle msg))
))
