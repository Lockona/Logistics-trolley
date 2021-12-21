; Auto-generated. Do not edit!


(cl:in-package test-srv)


;//! \htmlinclude test-request.msg.html

(cl:defclass <test-request> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass test-request (<test-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <test-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'test-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test-srv:<test-request> is deprecated: use test-srv:test-request instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <test-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test-srv:status-val is deprecated.  Use test-srv:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<test-request>)))
    "Constants for message type '<test-request>"
  '((:OPEN . 1)
    (:CLOSE . 0))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'test-request)))
    "Constants for message type 'test-request"
  '((:OPEN . 1)
    (:CLOSE . 0))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <test-request>) ostream)
  "Serializes a message object of type '<test-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <test-request>) istream)
  "Deserializes a message object of type '<test-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<test-request>)))
  "Returns string type for a service object of type '<test-request>"
  "test/testRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'test-request)))
  "Returns string type for a service object of type 'test-request"
  "test/testRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<test-request>)))
  "Returns md5sum for a message object of type '<test-request>"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'test-request)))
  "Returns md5sum for a message object of type 'test-request"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<test-request>)))
  "Returns full string definition for message of type '<test-request>"
  (cl:format cl:nil "uint8 status~%uint8 open = 1~%uint8 close = 0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'test-request)))
  "Returns full string definition for message of type 'test-request"
  (cl:format cl:nil "uint8 status~%uint8 open = 1~%uint8 close = 0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <test-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <test-request>))
  "Converts a ROS message object to a list"
  (cl:list 'test-request
    (cl:cons ':status (status msg))
))
;//! \htmlinclude test-response.msg.html

(cl:defclass <test-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:fixnum
    :initform 0))
)

(cl:defclass test-response (<test-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <test-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'test-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name test-srv:<test-response> is deprecated: use test-srv:test-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <test-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader test-srv:result-val is deprecated.  Use test-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <test-response>) ostream)
  "Serializes a message object of type '<test-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <test-response>) istream)
  "Deserializes a message object of type '<test-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<test-response>)))
  "Returns string type for a service object of type '<test-response>"
  "test/testResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'test-response)))
  "Returns string type for a service object of type 'test-response"
  "test/testResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<test-response>)))
  "Returns md5sum for a message object of type '<test-response>"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'test-response)))
  "Returns md5sum for a message object of type 'test-response"
  "561098128dce463abb21b321b22f8a07")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<test-response>)))
  "Returns full string definition for message of type '<test-response>"
  (cl:format cl:nil "uint8 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'test-response)))
  "Returns full string definition for message of type 'test-response"
  (cl:format cl:nil "uint8 result~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <test-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <test-response>))
  "Converts a ROS message object to a list"
  (cl:list 'test-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'test)))
  'test-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'test)))
  'test-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'test)))
  "Returns string type for a service object of type '<test>"
  "test/test")