;; Auto-generated. Do not edit!


(when (boundp 'move::NewGoal)
  (if (not (find-package "MOVE"))
    (make-package "MOVE"))
  (shadow 'NewGoal (find-package "MOVE")))
(unless (find-package "MOVE::NEWGOAL")
  (make-package "MOVE::NEWGOAL"))

(in-package "ROS")
;;//! \htmlinclude NewGoal.msg.html


(defclass move::NewGoal
  :super ros::object
  :slots (_x _y _theta _cmd ))

(defmethod move::NewGoal
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:theta __theta) 0.0)
    ((:cmd __cmd) "")
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _theta (float __theta))
   (setq _cmd (string __cmd))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:cmd
   (&optional __cmd)
   (if __cmd (setq _cmd __cmd)) _cmd)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _theta
    4
    ;; string _cmd
    4 (length _cmd)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; string _cmd
       (write-long (length _cmd) s) (princ _cmd s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; string _cmd
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _cmd (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get move::NewGoal :md5sum-) "f12a1beafbdce7c5cf13573ff19d07b9")
(setf (get move::NewGoal :datatype-) "move/NewGoal")
(setf (get move::NewGoal :definition-)
      "float32 x
float32 y
float32 theta
string cmd

")



(provide :move/NewGoal "f12a1beafbdce7c5cf13573ff19d07b9")


