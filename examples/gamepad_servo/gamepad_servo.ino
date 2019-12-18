/*
  PS3/4 Bluetooth Gamepad Controller servo test
  I2C interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in I2C mode
    http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
  
*/

#include "gamepad_ps4bt.h"
#include <PWMServo.h>

Gamepad_PS4BT ps4 = Gamepad_PS4BT(0x29);

uint8_t ledpin = LED_BUILTIN;
uint8_t xpin = 2;
uint8_t ypin = 3;
uint16_t lastx = 128;
uint16_t lasty = 128;
PWMServo xservo;
PWMServo yservo;


void setup() {
  // initialize serial communication at 57600 bits per second:
  // this is best rate for xbee radios

  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  xservo.attach(xpin);
  yservo.attach(ypin);

}

//**************************************************************************************
// Main loop
//**************************************************************************************
void loop() {

  if (ps4.get_data() == 0){

		// set the servo according to the left joystick Y value
		setServoHead(ps4.l_joystick_x,  ps4.l_joystick_y);

		// set the LED according to the L1 button press
		setLED(ps4.button_l1);

  }
  
  delay(50);

}

void setServoHead (uint16_t x, uint16_t y) {

  if (abs(lastx - x) > 15) {
    lastx = x;
    x = map(x, 0, CTL_MAX, 0, 180);
    xservo.write(x);

  }

  if (abs(lasty - y) > 15) {
    lasty = y;
    y = map(y, 0, CTL_MAX, 0, 180);
    yservo.write(y);

  }

}

void setLED (bool val) {

  digitalWrite(ledpin, val);

}
