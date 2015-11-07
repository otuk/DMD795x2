#include "DMD795x2.h"

static int DMD_latchPin;
static int DMD_clockPin;
static int DMD_dataPin;

void DMD_setup_ctl_pins(int latchPin, int clockPin, int dataPin ) {
  /** 
   Set pin connections to 74HC595 so you can control the shift register
   eg latchPin 8 on Arduino is connected to the pin12 of the 74HC595
   Arduino latchPin =>  RCLK pin , pin12 on 74HC595
   Arduino clockPin =>  SRCLK-serial clock of 595 -pin 11 on 74HC595
   Arduino dataPin => //SER -serial input pin of 595 - pin14 on 74HC595

   and ...Connect the pin9 of the first 595 to the SER -serial pin of 
   the 2nd 595 - pin14

   connect all the out data pins (Q0 -Q7) from the first 595 
   to lower pins of dot matrix (pins 1 - 8) + resistor
   in an order Q0 -> 1, Q1 -> 2 etc
   [actually the connection is to the current limiting resistor 
   that is connected to the dot matrix pins 1-8 ]
   similarly but without the resistor
   connect all the out data pins of the second 595 Q0 -Q7 
   to dot matrix's upper pins (9 -16)

   also connect the voltage, GRD, 
   OE(O enable), MR(master reset) of the 74HC595 per its specs
*/

  DMD_latchPin = latchPin;
  DMD_clockPin = clockPin;
  DMD_dataPin = dataPin;
    
  pinMode(DMD_latchPin, OUTPUT);
  pinMode(DMD_clockPin, OUTPUT);
  pinMode(DMD_dataPin, OUTPUT);
}


// we will use this as the list of dots that is to be
// rendered on the dot matrix display
static unsigned short display_array [DOTMATMAX_X * DOTMATMAX_Y + 1]={0x00};
static int dalen = 0;


/*
 *  Reset the list of display LEDs to zero
 */
void DMD_reset_display_data(){
  display_array[0]=0x00;
  dalen = 0;
}


/*
 *  Your game will use this function to
 *  add anything that needs to be rendered
 */
void DMD_add_display_data(unsigned short* dots, int len){
  int upto= min(len+dalen, DOTMATMAX_X * DOTMATMAX_Y);
  for(int i=0; i<upto-dalen; i++){
    display_array[dalen +i] = *(dots+i);
  }
  dalen += (upto-dalen);
  display_array[dalen] = 0x00;
}


/**
 *  Call this in your loop() to update the display
 *  In a typical scenario, you will go thru these stages
 *  in your loop() function.
 *    -read inputs/sensors
 *    -update game data  and data to be displayed
 *    -reset the display
 *    -render the matrix
 *    -delay(?) and loop back   
 */
void DMD_render_matrix(){
  // the idea is to multiplex each led in the display_data list
  // once and so fast that the eye cannot tell
  // this loop will go thru the list of all leds to be displayed
  // one by one until max led count or early stop when it encounteres 0x00
  for(int i=0; i < DOTMATMAX_X * DOTMATMAX_Y; i++){
    unsigned short show = display_array[i];
    if (show == 0x00)
      break;
    digitalWrite(DMD_latchPin, LOW);
    byte data2  = show >> 8;
    byte data = show & 0xff;
    shiftOut(DMD_dataPin, DMD_clockPin, MSBFIRST, data2);
    shiftOut(DMD_dataPin, DMD_clockPin, MSBFIRST, data);
    digitalWrite(DMD_latchPin, HIGH);
  }
}


/**
 *  It provides the 16 bit combination
 *  for a LED at row r and column c
 *  to be lit
 */
unsigned short DMD_getpins(int r, int c){
  //for a given row  and column get the pin combination
  // to turn of that led
  unsigned short res = ALL_OFF;
  res = coff[c] & res;
  unsigned short h = helper[rp[r]-1];
  res = res | h;
  return res;
}

void DMD_fps(int fps){
  static long last = 0;
  static long current = 0;
  current = millis();
  if ((current - last) < (1000/fps)){
    delay((1000/fps) - (current - last));
  }  
  last = millis();
}
