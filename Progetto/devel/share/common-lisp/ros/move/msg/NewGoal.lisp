; Auto-generated. Do not edit!


(cl:in-package move-msg)


;//! \htmlinclude NewGoal.msg.html

(cl:defclass <NewGoal> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (theta
    :reader theta
    :initarg :theta
    :type cl:float
    :initform 0.0)
   (cmd
    :reader cmd
    :initarg :cmd
    :type cl:string
    :initform ""))
)

(cl:defclass NewGoal (<NewGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <NewGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'NewGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name move-msg:<NewGoal> is deprecated: use move-msg:NewGoal instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <NewGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader move-msg:x-val is deprecated.  Use move-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <NewGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader move-msg:y-val is deprecated.  Use move-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <NewGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader move-msg:theta-val is deprecated.  Use move-msg:theta instead.")
  (theta m))

(cl:ensure-generic-function 'cmd-val :lambda-list '(m))
(cl:defmethod cmd-val ((m <NewGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader move-msg:cmd-val is deprecated.  Use move-msg:cmd instead.")
  (cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <NewGoal>) ostream)
  "Serializes a message object of type '<NewGoal>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'theta))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'cmd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'cmd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <NewGoal>) istream)
  "Deserializes a message object of type '<NewGoal>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'theta) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'cmd) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'cmd) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<NewGoal>)))
  "Returns string type for a message object of type '<NewGoal>"
  "move/NewGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'NewGoal)))
  "Returns string type for a message object of type 'NewGoal"
  "move/NewGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<NewGoal>)))
  "Returns md5sum for a message object of type '<NewGoal>"
  "f12a1beafbdce7c5cf13573ff19d07b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'NewGoal)))
  "Returns md5sum for a message object of type 'NewGoal"
  "f12a1beafbdce7c5cf13573ff19d07b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<NewGoal>)))
  "Returns full string definition for message of type '<NewGoal>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 theta~%string cmd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'NewGoal)))
  "Returns full string definition for message of type 'NewGoal"
  (cl:format cl:nil "float32 x~%float32 y~%float32 theta~%string cmd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <NewGoal>))
  (cl:+ 0
     4
     4
     4
     4 (cl:length (cl:slot-value msg 'cmd))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <NewGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'NewGoal
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':theta (theta msg))
    (cl:cons ':cmd (cmd msg))
))
