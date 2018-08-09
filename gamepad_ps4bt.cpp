/*
  PS4 Bluetooth Gamepad Controller
  Serial HEX interface

  Using Hobbytronics USB Host adapter configured with PS3/4 Bluetooth software running in Serial HEX mode
  http://www.hobbytronics.co.uk/usb-host/ps3-ps4-controller-bluetooth
  
*/

#include <Gamepad_PS4BT.h>

//************************************************************************
// Class creator for both transmitter and receiver
//************************************************************************
Gamepad_PS4BT::Gamepad_PS4BT() {
	
}

//************************************************************************
// Begin receive function for receiving MCU (slave)
//************************************************************************
void Gamepad_PS4BT::beginRX(Stream &serial) {
	
	_serial = &serial;
	
}

uint8_t Gamepad_PS4BT::get_data(void) {

  _ps4_ok = 0;
	
  // if there's any serial available, read it:
  while (_serial->available() > 0) {
     byte c = _serial->read();  //gets one byte from serial buffer
     // Looking for start of input string CR LF P S 4 
     if(_str_start<3){
        switch(c){
           case 'P':
              _str_start++; 
              break;
           case 'S':
              if(_str_start==1){
                 _str_start++; 
              }  
              break;
           case '4':
              if(_str_start==2){
                 _str_start++; 
                 _tdata[0]='P';
                 _tdata[1]='S';
                 _tdata[2]='4';
                 _ps4_i=3;
              }  
              break;  
           default:
              _str_start=0;     
              break;
        }           
     }
     else{
        // Add value to tdata
        _tdata[_ps4_i++] = c;
        if(_ps4_i>=GAMEPAD_DATA) {
          // Complete string received - process data
          _str_start=0;  
          // Calculate check digit
          _crc_val=crc8(_tdata,GAMEPAD_DATA-3);
          if(_crc_val==_tdata[GAMEPAD_DATA-3]){
             // CRC Match - Data Valid
             // Set values
             l_joystick_x=_tdata[3];
             l_joystick_y=_tdata[4];
             r_joystick_x=_tdata[5];
             r_joystick_y=_tdata[6];
             accel_x=_tdata[7];
             accel_y=_tdata[8]; 
             l2=_tdata[9]; 
             r2=_tdata[10]; 
             
             if(((_tdata[11]&0x0F)==5) || ((_tdata[11]&0x0F)==6) || ((_tdata[11]&0x0F)==7)) button_left=1;  else button_left=0;	//W
             if(((_tdata[11]&0x0F)==3) || ((_tdata[11]&0x0F)==4) || ((_tdata[11]&0x0F)==5)) button_down=1;  else button_down=0;	//S
             if(((_tdata[11]&0x0F)==1) || ((_tdata[11]&0x0F)==2) || ((_tdata[11]&0x0F)==3)) button_right=1; else button_right=0;	//E
             if(((_tdata[11]&0x0F)==0) || ((_tdata[11]&0x0F)==1) || ((_tdata[11]&0x0F)==7)) button_up=1;    else button_up=0;		//N
             button_square  =((_tdata[11]&0b00010000)>>4); // SQUARE
             button_x       =((_tdata[11]&0b00100000)>>5); // X
             button_circle  =((_tdata[11]&0b01000000)>>6); // CIRCLE
             button_triangle=((_tdata[11]&0b10000000)>>7); // TRIANGLE

             button_l1     =((_tdata[12]&0b00000001));    // L1
             button_r1     =((_tdata[12]&0b00000010)>>1); // R1
             button_l2     =((_tdata[12]&0b00000100)>>2); // L2
             button_r2     =((_tdata[12]&0b00001000)>>3); // R2
             button_share  =((_tdata[12]&0b00010000)>>4); // SHARE
             button_options=((_tdata[12]&0b00100000)>>5); // OPTIONS
             button_l3     =((_tdata[12]&0b01000000)>>6); // L3
             button_r3     =((_tdata[12]&0b10000000)>>7); // R3

             button_ps4    =((_tdata[13]&0b00000001));    // PS4
             button_tpad   =((_tdata[13]&0b00000010)>>1); // TPAD
                
             tpad_x        =_tdata[14]; 
             tpad_y        =_tdata[15];      
             battery       =_tdata[16];       
             _ps4_ok = 0;     
          }   
          else{
             _ps4_ok = 99; 
          }           
        }
     }       
  }


  return _ps4_ok;

}

// CRC-8 Check Digit
unsigned char Gamepad_PS4BT::crc8(unsigned char *data, unsigned char len) {
  unsigned char crc = 0x00;
  unsigned char extract, i, sum;
  while (len--) {
    extract = *data++;
    for (i = 8; i; i--) {
      sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum) {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  return crc;
}

