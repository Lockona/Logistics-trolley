// Auto-generated. Do not edit!

// (in-package car.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class odom {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.position_x = null;
      this.position_y = null;
      this.oriention = null;
      this.velocity_linear = null;
      this.velocity_angular = null;
    }
    else {
      if (initObj.hasOwnProperty('position_x')) {
        this.position_x = initObj.position_x
      }
      else {
        this.position_x = 0.0;
      }
      if (initObj.hasOwnProperty('position_y')) {
        this.position_y = initObj.position_y
      }
      else {
        this.position_y = 0.0;
      }
      if (initObj.hasOwnProperty('oriention')) {
        this.oriention = initObj.oriention
      }
      else {
        this.oriention = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_linear')) {
        this.velocity_linear = initObj.velocity_linear
      }
      else {
        this.velocity_linear = 0.0;
      }
      if (initObj.hasOwnProperty('velocity_angular')) {
        this.velocity_angular = initObj.velocity_angular
      }
      else {
        this.velocity_angular = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type odom
    // Serialize message field [position_x]
    bufferOffset = _serializer.float32(obj.position_x, buffer, bufferOffset);
    // Serialize message field [position_y]
    bufferOffset = _serializer.float32(obj.position_y, buffer, bufferOffset);
    // Serialize message field [oriention]
    bufferOffset = _serializer.float32(obj.oriention, buffer, bufferOffset);
    // Serialize message field [velocity_linear]
    bufferOffset = _serializer.float32(obj.velocity_linear, buffer, bufferOffset);
    // Serialize message field [velocity_angular]
    bufferOffset = _serializer.float32(obj.velocity_angular, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type odom
    let len;
    let data = new odom(null);
    // Deserialize message field [position_x]
    data.position_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [position_y]
    data.position_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [oriention]
    data.oriention = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [velocity_linear]
    data.velocity_linear = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [velocity_angular]
    data.velocity_angular = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car/odom';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '188ac42e6aff59c7fe2517b8262a562c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 position_x
    float32 position_y
    float32 oriention
    float32 velocity_linear
    float32 velocity_angular
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new odom(null);
    if (msg.position_x !== undefined) {
      resolved.position_x = msg.position_x;
    }
    else {
      resolved.position_x = 0.0
    }

    if (msg.position_y !== undefined) {
      resolved.position_y = msg.position_y;
    }
    else {
      resolved.position_y = 0.0
    }

    if (msg.oriention !== undefined) {
      resolved.oriention = msg.oriention;
    }
    else {
      resolved.oriention = 0.0
    }

    if (msg.velocity_linear !== undefined) {
      resolved.velocity_linear = msg.velocity_linear;
    }
    else {
      resolved.velocity_linear = 0.0
    }

    if (msg.velocity_angular !== undefined) {
      resolved.velocity_angular = msg.velocity_angular;
    }
    else {
      resolved.velocity_angular = 0.0
    }

    return resolved;
    }
};

module.exports = odom;
