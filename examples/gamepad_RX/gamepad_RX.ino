/*
  test of USB Host board with PS3/4 Bluetooth software
*/

#include "gamepad_ps4bt.h"

#define baudRate 57600

unsigned long time;
String buttons;
Gamepad_PS4BT ps4 = Gamepad_PS4BT(0x29);

void setup()  {

  SerialUSB.begin(baudRate);
  time = 0;
  while (!SerialUSB);
  SerialUSB.println("good to go");

}

void loop()  {

  if (ps4.get_data() == 0) {

    //Print out some of the data
    SerialUSB.print ("Left Joystick X = ");
    SerialUSB.print(ps4.l_joystick_x);
    SerialUSB.print(", Y = ");
    SerialUSB.println(ps4.l_joystick_y);
    SerialUSB.print ("Right Joystick X = ");
    SerialUSB.print(ps4.r_joystick_x);
    SerialUSB.print(", Y = ");
    SerialUSB.println(ps4.r_joystick_y);

    SerialUSB.print ("Tpad X = ");
    SerialUSB.println(ps4.tpad_x);
    SerialUSB.print ("Tpad Y = ");
    SerialUSB.println(ps4.tpad_y);

    SerialUSB.print ("Left 2 Pressure = ");
    SerialUSB.println(ps4.l2);
    SerialUSB.print ("Right 2 Pressure = ");
    SerialUSB.println(ps4.r2);

    buttons = "Buttons pressed: ";

    if (ps4.button_l3) {
      buttons = buttons + " JR ";
    }
    if (ps4.button_r3) {
      buttons = buttons + " Start ";
    }
    if (ps4.button_l1) {
      buttons = buttons + " L1 ";
    }
    if (ps4.button_l2) {
      buttons = buttons + " L2 ";
    }
    if (ps4.button_r1) {
      buttons = buttons + " R1 ";
    }
    if (ps4.button_r2) {
      buttons = buttons + " R2 ";
    }
    if (ps4.button_up) {
      buttons = buttons + " UP ";
    }
    if (ps4.button_down) {
      buttons = buttons + " DOWN ";
    }
    if (ps4.button_left) {
      buttons = buttons + " LEFT ";
    }
    if (ps4.button_right) {
      buttons = buttons + " RIGHT ";
    }
    if (ps4.button_triangle) {
      buttons = buttons + " Triangle ";
    }
    if (ps4.button_circle) {
      buttons = buttons + " Circle ";
    }
    if (ps4.button_x) {
      buttons = buttons + " X ";
    }
    if (ps4.button_square) {
      buttons = buttons + " Square ";
    }
    if (ps4.button_share) {
      buttons = buttons + " Select ";
    }
    if (ps4.button_options) {
      buttons = buttons + " JL ";
    }
    if (ps4.button_ps4) {
      buttons = buttons + " PS3 ";
    }

    SerialUSB.println (buttons);

  }
  
  delay(POLL_INTERVAL);
  
}
