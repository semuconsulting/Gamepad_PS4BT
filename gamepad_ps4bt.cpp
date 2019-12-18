/*
  PS4 Bluetooth Gamepad Controller
  I2C interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in I2C Mode
  http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth

*/

#include <Gamepad_PS4BT.h>

//************************************************************************
// Class creator for both transmitter and receiver
//************************************************************************
Gamepad_PS4BT::Gamepad_PS4BT(uint8_t i2c_addr) {

  _i2c_addr = i2c_addr;

}

uint8_t Gamepad_PS4BT::get_data(void) {

  // Get data from PS4 DualShock Controller via I2C
  // We only want single byte values (0 to 255)

  unsigned char i2c_index=0;
  Wire.beginTransmission(_i2c_addr);  // transmit to device
  Wire.write(0);                        // Start receiving data from register 0
  Wire.endTransmission();               // end transmission

  Wire.requestFrom(_i2c_addr, PS4_I2C_LEN);    // request PS4_I2C_LEN bytes from PS4
  while(Wire.available())
  {
    _ps4_ic2[i2c_index++] = Wire.read();          // receive a byte and increment index
  }

  decode_data();

  return PS4_OK;

}

// Decode PS4 Data and move to struct
void Gamepad_PS4BT::decode_data(void){

  l_joystick_x = _ps4_ic2[0];
  l_joystick_y = _ps4_ic2[1];
  r_joystick_x = _ps4_ic2[2];
  r_joystick_y = _ps4_ic2[3];
  accel_x      = _ps4_ic2[4];
  accel_y      = _ps4_ic2[5];
  l2           = _ps4_ic2[6];
  r2           = _ps4_ic2[7];

  if(((_ps4_ic2[8]&0x0F)==5) || ((_ps4_ic2[8]&0x0F)==6) || ((_ps4_ic2[8]&0x0F)==7)) button_left=1;  else button_left=0;    //W
  if(((_ps4_ic2[8]&0x0F)==3) || ((_ps4_ic2[8]&0x0F)==4) || ((_ps4_ic2[8]&0x0F)==5)) button_down=1;  else button_down=0;    //S
  if(((_ps4_ic2[8]&0x0F)==1) || ((_ps4_ic2[8]&0x0F)==2) || ((_ps4_ic2[8]&0x0F)==3)) button_right=1; else button_right=0;   //E
  if(((_ps4_ic2[8]&0x0F)==0) || ((_ps4_ic2[8]&0x0F)==1) || ((_ps4_ic2[8]&0x0F)==7)) button_up=1;    else button_up=0;  //N
  button_square  =((_ps4_ic2[8]&0b00010000)>>4); // SQUARE
  button_x       =((_ps4_ic2[8]&0b00100000)>>5); // X
  button_circle  =((_ps4_ic2[8]&0b01000000)>>6); // CIRCLE
  button_triangle=((_ps4_ic2[8]&0b10000000)>>7); // TRIANGLE

  button_l1     =((_ps4_ic2[9]&0b00000001));    // L1
  button_r1     =((_ps4_ic2[9]&0b00000010)>>1); // R1
  button_l2     =((_ps4_ic2[9]&0b00000100)>>2); // L2
  button_r2     =((_ps4_ic2[9]&0b00001000)>>3); // R2
  button_share  =((_ps4_ic2[9]&0b00010000)>>4); // SHARE
  button_options=((_ps4_ic2[9]&0b00100000)>>5); // OPTIONS
  button_l3     =((_ps4_ic2[9]&0b01000000)>>6); // L3
  button_r3     =((_ps4_ic2[9]&0b10000000)>>7); // R3

  button_ps4    =((_ps4_ic2[10]&0b00000001));    // PS4
  button_tpad   =((_ps4_ic2[10]&0b00000010)>>1); // TPAD

  tpad_x        = _ps4_ic2[11];
  tpad_y        = _ps4_ic2[12];
  battery       = _ps4_ic2[13];

}
