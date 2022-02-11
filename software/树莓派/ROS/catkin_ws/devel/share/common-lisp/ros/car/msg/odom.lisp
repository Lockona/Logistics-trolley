; Auto-generated. Do not edit!


(cl:in-package car-msg)


;//! \htmlinclude odom.msg.html

(cl:defclass <odom> (roslisp-msg-protocol:ros-message)
  ((position_x
    :reader position_x
    :initarg :position_x
    :type cl:float
    :initform 0.0)
   (position_y
    :reader position_y
    :initarg :position_y
    :type cl:float
    :initform 0.0)
   (oriention
    :reader oriention
    :initarg :oriention
    :type cl:float
    :initform 0.0)
   (velocity_linear
    :reader velocity_linear
    :initarg :velocity_linear
    :type cl:float
    :initform 0.0)
   (velocity_angular
    :reader velocity_angular
    :initarg :velocity_angular
    :type cl:float
    :initform 0.0))
)

(cl:defclass odom (<odom>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <odom>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'odom)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car-msg:<odom> is deprecated: use car-msg:odom instead.")))

(cl:ensure-generic-function 'position_x-val :lambda-list '(m))
(cl:defmethod position_x-val ((m <odom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:position_x-val is deprecated.  Use car-msg:position_x instead.")
  (position_x m))

(cl:ensure-generic-function 'position_y-val :lambda-list '(m))
(cl:defmethod position_y-val ((m <odom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:position_y-val is deprecated.  Use car-msg:position_y instead.")
  (position_y m))

(cl:ensure-generic-function 'oriention-val :lambda-list '(m))
(cl:defmethod oriention-val ((m <odom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:oriention-val is deprecated.  Use car-msg:oriention instead.")
  (oriention m))

(cl:ensure-generic-function 'velocity_linear-val :lambda-list '(m))
(cl:defmethod velocity_linear-val ((m <odom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:velocity_linear-val is deprecated.  Use car-msg:velocity_linear instead.")
  (velocity_linear m))

(cl:ensure-generic-function 'velocity_angular-val :lambda-list '(m))
(cl:defmethod velocity_angular-val ((m <odom>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-msg:velocity_angular-val is deprecated.  Use car-msg:velocity_angular instead.")
  (velocity_angular m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <odom>) ostream)
  "Serializes a message object of type '<odom>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'position_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'position_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'oriention))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity_linear))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity_angular))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <odom>) istream)
  "Deserializes a message object of type '<odom>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'position_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'position_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'oriention) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity_linear) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity_angular) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<odom>)))
  "Returns string type for a message object of type '<odom>"
  "car/odom")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'odom)))
  "Returns string type for a message object of type 'odom"
  "car/odom")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<odom>)))
  "Returns md5sum for a message object of type '<odom>"
  "188ac42e6aff59c7fe2517b8262a562c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'odom)))
  "Returns md5sum for a message object of type 'odom"
  "188ac42e6aff59c7fe2517b8262a562c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<odom>)))
  "Returns full string definition for message of type '<odom>"
  (cl:format cl:nil "float32 position_x~%float32 position_y~%float32 oriention~%float32 velocity_linear~%float32 velocity_angular~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'odom)))
  "Returns full string definition for message of type 'odom"
  (cl:format cl:nil "float32 position_x~%float32 position_y~%float32 oriention~%float32 velocity_linear~%float32 velocity_angular~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <odom>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <odom>))
  "Converts a ROS message object to a list"
  (cl:list 'odom
    (cl:cons ':position_x (position_x msg))
    (cl:cons ':position_y (position_y msg))
    (cl:cons ':oriention (oriention msg))
    (cl:cons ':velocity_linear (velocity_linear msg))
    (cl:cons ':velocity_angular (velocity_angular msg))
))
