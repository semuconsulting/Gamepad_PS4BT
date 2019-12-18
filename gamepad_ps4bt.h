/*
  PS4 Bluetooth Gamepad Controller
  I2C Interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in I2C Mode
  http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth

*/

#ifndef _GAMEPAD_PS4BT_H_
#define _GAMEPAD_PS4BT_H_

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_I2C_ADDRESS 0x29
#define POLL_INTERVAL 20  // poll every 20 milliseconds
#define CTL_MAX 255       // maximum analogue control value (8-bit = 255, 10-bit = 1023)
#define PS4_I2C_LEN 14
#define PS4_OK 0

class Gamepad_PS4BT {

public:

  unsigned char  l_joystick_x;
  unsigned char  l_joystick_y;
  unsigned char  r_joystick_x;
  unsigned char  r_joystick_y;
  unsigned char  accel_x;
  unsigned char  accel_y;
  unsigned char  l2;
  unsigned char  r2;

  unsigned char  button_left;
  unsigned char  button_down;
  unsigned char  button_right;
  unsigned char  button_up;
  unsigned char  button_square;
  unsigned char  button_x;
  unsigned char  button_circle;
  unsigned char  button_triangle;

  unsigned char  button_l1;
  unsigned char  button_r1;
  unsigned char  button_l2;
  unsigned char  button_r2;
  unsigned char  button_share;
  unsigned char  button_options;
  unsigned char  button_l3;
  unsigned char  button_r3;

  unsigned char  button_ps4;
  unsigned char  button_tpad;

  unsigned char  tpad_x;
  unsigned char  tpad_y;
  unsigned char  battery;

  Gamepad_PS4BT(uint8_t i2c_addr = DEFAULT_I2C_ADDRESS);
  uint8_t get_data(void);
  void decode_data(void);

private:

  uint8_t _i2c_addr;
  unsigned char _ps4_ic2[PS4_I2C_LEN];

};

#endif
