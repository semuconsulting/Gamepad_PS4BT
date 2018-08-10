/*
  PS3/4 Bluetooth Gamepad Controller servo test
  Serial HEX interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in Serial HEX mode
    http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
  
*/

#include "gamepad_ps4bt.h"
#include <Servo.h>

Gamepad_PS4BT ps3 = Gamepad_PS4BT();

uint8_t ledpin = LED_BUILTIN;
uint8_t xpin = 2;
uint8_t ypin = 3;
uint16_t lastx = 128;
uint16_t lasty = 128;
Servo xservo;
Servo yservo;


void setup() {
  // initialize serial communication at 57600 bits per second:
  // this is best rate for xbee radios

  Serial1.begin(57600);

  ps3.beginRX(Serial1);

  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  xservo.attach(xpin);
  yservo.attach(ypin);

}

//**************************************************************************************
// Main loop
//**************************************************************************************
void loop() {

  if (ps3.get_data() == 0){

		// set the servo according to the left joystick Y value
		setServoHead(ps3.l_joystick_x,  ps3.l_joystick_y);

		// set the LED according to the L1 button press
		setLED(ps3.button_l1);

  }
  
  delay(POLL_INTERVAL);

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

