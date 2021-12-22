; Auto-generated. Do not edit!


(cl:in-package car-srv)


;//! \htmlinclude door-request.msg.html

(cl:defclass <door-request> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass door-request (<door-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <door-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'door-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car-srv:<door-request> is deprecated: use car-srv:door-request instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <door-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-srv:status-val is deprecated.  Use car-srv:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<door-request>)))
    "Constants for message type '<door-request>"
  '((:OPEN . 1)
    (:CLOSE . 0))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'door-request)))
    "Constants for message type 'door-request"
  '((:OPEN . 1)
    (:CLOSE . 0))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <door-request>) ostream)
  "Serializes a message object of type '<door-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <door-request>) istream)
  "Deserializes a message object of type '<door-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<door-request>)))
  "Returns string type for a service object of type '<door-request>"
  "car/doorRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'door-request)))
  "Returns string type for a service object of type 'door-request"
  "car/doorRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<door-request>)))
  "Returns md5sum for a message object of type '<door-request>"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'door-request)))
  "Returns md5sum for a message object of type 'door-request"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<door-request>)))
  "Returns full string definition for message of type '<door-request>"
  (cl:format cl:nil "uint8 status~%uint8 open = 1~%uint8 close = 0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'door-request)))
  "Returns full string definition for message of type 'door-request"
  (cl:format cl:nil "uint8 status~%uint8 open = 1~%uint8 close = 0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <door-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <door-request>))
  "Converts a ROS message object to a list"
  (cl:list 'door-request
    (cl:cons ':status (status msg))
))
;//! \htmlinclude door-response.msg.html

(cl:defclass <door-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:fixnum
    :initform 0))
)

(cl:defclass door-response (<door-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <door-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'door-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name car-srv:<door-response> is deprecated: use car-srv:door-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <door-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader car-srv:result-val is deprecated.  Use car-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <door-response>) ostream)
  "Serializes a message object of type '<door-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <door-response>) istream)
  "Deserializes a message object of type '<door-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<door-response>)))
  "Returns string type for a service object of type '<door-response>"
  "car/doorResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'door-response)))
  "Returns string type for a service object of type 'door-response"
  "car/doorResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<door-response>)))
  "Returns md5sum for a message object of type '<door-response>"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'door-response)))
  "Returns md5sum for a message object of type 'door-response"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<door-response>)))
  "Returns full string definition for message of type '<door-response>"
  (cl:format cl:nil "uint8 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'door-response)))
  "Returns full string definition for message of type 'door-response"
  (cl:format cl:nil "uint8 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <door-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <door-response>))
  "Converts a ROS message object to a list"
  (cl:list 'door-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'door)))
  'door-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'door)))
  'door-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'door)))
  "Returns string type for a service object of type '<door>"
  "car/door")