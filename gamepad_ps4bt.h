/*
  PS4 Bluetooth Gamepad Controller
  Serial HEX interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in Serial HEX mode
  http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
  
*/

#ifndef _GAMEPAD_PS4BT_H_
#define _GAMEPAD_PS4BT_H_

#include <Arduino.h>      //needed for Serial

#define GAMEPAD_DATA 20   // 20 chars sent including the CRLF chars
#define POLL_INTERVAL 20  // poll every 20 milliseconds
#define CTL_MAX 255       // maximum analogue control value (8-bit = 255, 10-bit = 1023)

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
  
  Gamepad_PS4BT();
  void beginRX(Stream &serial);
 
  uint8_t get_data(void);
  unsigned char crc8(unsigned char *data, unsigned char len);

private:

  Stream* _serial;
  unsigned char _crc_val;
  unsigned char _tdata[GAMEPAD_DATA];
  unsigned char _str_start = 0;
  unsigned int  _ps4_i;
  uint8_t _ps4_ok = 0;  // valid data received
  
};  

#endif
