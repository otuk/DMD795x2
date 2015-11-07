#include <DMD795x2.h>


void update_the_game(){
  static int i, j;
  unsigned short one_led = DMD_getpins(i,j);
  DMD_reset_display_data();
  DMD_add_display_data(&one_led, 1);
  j++;
  if (j==8){
     i++;
     j=0;
     if(i==8)
       i=0;
  }   
}

void setup() {
  // put your setup code here, to run once:
  /*
    Set pin connections to 74HC595 so you can control the shift register        
   eg latchPin 8 on Arduino is connected to the pin12 of the 74HC595           
   Arduino latchPin 8  =>  RCLK pin , pin12 on 74HC595                            
   Arduino clockPin 12 =>  SRCLK-serial clock of 595 -pin 11 on 74HC595           
   Arduino dataPin 11 => //SER -serial input pin of 595 - pin14 on 74HC595        
  */
  DMD_setup_ctl_pins(8, 12, 11); //You need to call this as part of you
}

void loop() {
  // put your main code here, to run repeatedly:
    update_the_game();
    DMD_render_matrix();
    DMD_fps(5); //change this value from 1 to 1200 see what happens
}
