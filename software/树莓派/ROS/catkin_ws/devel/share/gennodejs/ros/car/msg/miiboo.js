// Auto-generated. Do not edit!

// (in-package car.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let imu = require('./imu.js');

//-----------------------------------------------------------

class miiboo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.frame_id = null;
      this.left_wheel_speed = null;
      this.right_wheel_speed = null;
      this.angle = null;
    }
    else {
      if (initObj.hasOwnProperty('frame_id')) {
        this.frame_id = initObj.frame_id
      }
      else {
        this.frame_id = 0;
      }
      if (initObj.hasOwnProperty('left_wheel_speed')) {
        this.left_wheel_speed = initObj.left_wheel_speed
      }
      else {
        this.left_wheel_speed = 0;
      }
      if (initObj.hasOwnProperty('right_wheel_speed')) {
        this.right_wheel_speed = initObj.right_wheel_speed
      }
      else {
        this.right_wheel_speed = 0;
      }
      if (initObj.hasOwnProperty('angle')) {
        this.angle = initObj.angle
      }
      else {
        this.angle = new imu();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type miiboo
    // Serialize message field [frame_id]
    bufferOffset = _serializer.uint32(obj.frame_id, buffer, bufferOffset);
    // Serialize message field [left_wheel_speed]
    bufferOffset = _serializer.int16(obj.left_wheel_speed, buffer, bufferOffset);
    // Serialize message field [right_wheel_speed]
    bufferOffset = _serializer.int16(obj.right_wheel_speed, buffer, bufferOffset);
    // Serialize message field [angle]
    bufferOffset = imu.serialize(obj.angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type miiboo
    let len;
    let data = new miiboo(null);
    // Deserialize message field [frame_id]
    data.frame_id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [left_wheel_speed]
    data.left_wheel_speed = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [right_wheel_speed]
    data.right_wheel_speed = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [angle]
    data.angle = imu.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car/miiboo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a9222de228ec580804ecbcde4d74572f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 frame_id
    int16 left_wheel_speed
    int16 right_wheel_speed
    imu angle 
    ================================================================================
    MSG: car/imu
       float64 roll
        float64 pitch
        float64 yaw
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new miiboo(null);
    if (msg.frame_id !== undefined) {
      resolved.frame_id = msg.frame_id;
    }
    else {
      resolved.frame_id = 0
    }

    if (msg.left_wheel_speed !== undefined) {
      resolved.left_wheel_speed = msg.left_wheel_speed;
    }
    else {
      resolved.left_wheel_speed = 0
    }

    if (msg.right_wheel_speed !== undefined) {
      resolved.right_wheel_speed = msg.right_wheel_speed;
    }
    else {
      resolved.right_wheel_speed = 0
    }

    if (msg.angle !== undefined) {
      resolved.angle = imu.Resolve(msg.angle)
    }
    else {
      resolved.angle = new imu()
    }

    return resolved;
    }
};

module.exports = miiboo;
