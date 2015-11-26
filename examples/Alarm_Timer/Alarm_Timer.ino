#include <DMD795x2.h>
#include <DMD_Alpha.h>
#include <math.h>

/***
 *
 *  This is a simple count down timer
 *  when turned on timer displays zero, the reset position.
 *  First move the joystick up (till 99) or down (till 0) to adjust the time to count down
 *  To start the timer push the joystick button
 *  The timer can be used as a seconds OR a minutes count down timer simply by MINUTETIMER define below
 *  To pause the timer push the joystick button
 *  To silence the end-of-time alarm push the joystick button
 *
 */

#define MINUTETIMER  // as is this is a minute timer, if you want a seconds timer simply comment this line out 

#define FPS 30
#define REPEATTONE 5000
#define TONEPIN 6  // a buzzer is connected to the pin6 arduino output 
#define FREQ 3000

#define MAXTIMER 99

#ifdef MINUTETIMER
#define SCALE 60000L
#else
#define SCALE 1000L
#endif


//jotstick parameters & thresholds
#define JX_PUSH A5  //analog5 input of arduino connected to the SW read of josstick
#define JX_MOVE A2  //analog2 input  of arduino connected to the X or Y axis of the joystick
#define JX_SPD 10  // how long to hold the joystick
#define JX_SW_LIM 50  //if the value is less than this button is pressed
#define JX_UP_LIM 800
#define JX_DOWN_LIM 300


//alarm timer struct
typedef struct {
  bool started;
  bool ended;
  long time_to_end;
  unsigned long last_timer_millis;
} at_s;

at_s mt;

void reset_timer(){
  mt.started = false;
  mt.ended = false;
  mt.time_to_end = 0*SCALE;
}


void setup() {
  /*
    Set pin connections to 74HC595 so you can control the shift register        
   eg latchPin 8 on Arduino is connected to the pin12 of the 74HC595           
   Arduino latchPin 8  =>  RCLK pin , pin12 on 74HC595                            
   Arduino clockPin 12 =>  SRCLK- serial clock of 595 -pin 11 on 74HC595           
   Arduino dataPin 11 => //SER -serial input pin of 595 - pin14 on 74HC595        
  */
  DMD_setup_ctl_pins(8, 12, 11); 
  reset_timer(); 
}

void start_timer(){
  mt.last_timer_millis = millis();
  mt.started = true;
}

void pause_timer(){
  mt.started = false;
}

void read_inputs(){
  static int btn_up = JX_SPD;
  static int btn_down = JX_SPD;
  static int btn_start = JX_SPD;
  static int btn_pause = 2*JX_SPD;
  static int btn_end = JX_SPD;
  // set mt.time_to_end  (in minutes or seconds)
  if (!mt.started & !mt.ended){
    int jx = analogRead(JX_MOVE); // if moved up or down
    int sw = analogRead(JX_PUSH); // if pressed
    //if moved up increase
    //if moved down decrease
    // if pressed start timer
    if (jx < JX_DOWN_LIM){
      if(btn_down--) return;
      if(mt.time_to_end > SCALE){
        mt.time_to_end -= SCALE; 
      }else{
	      mt.time_to_end = 0L;
      }  
      btn_down = JX_SPD;
    }else if(jx > JX_UP_LIM){
      if(btn_up--) return;
      if(mt.time_to_end < (MAXTIMER*SCALE - SCALE)){
        mt.time_to_end += SCALE; 
      }else{
        mt.time_to_end = MAXTIMER*SCALE;  
      }
      btn_up = JX_SPD;
    }else if (sw<=JX_SW_LIM){
      if(btn_start--) return;
      btn_start = JX_SPD;
      start_timer();     
     }else {
      btn_down= JX_SPD;
      btn_up = JX_SPD;
      btn_start = JX_SPD;
    }
  }else if(mt.started){
    //if pressed stop timer
    int sw = analogRead(JX_PUSH); // read if Joystick pressed 
    if (sw<=JX_SW_LIM){
       if(btn_pause--) return;
       btn_pause = 2*JX_SPD;
       pause_timer();
    }   
  }else if(mt.ended){
    int sw = analogRead(JX_PUSH); // read if Joystick pressed 
    if (sw<=JX_SW_LIM){
       if(btn_end--) return;
       btn_end = JX_SPD;
       reset_timer();
    }  
  }else{
    btn_pause = 2*JX_SPD;
    btn_end = JX_SPD;
  }
}

static unsigned long subtract(unsigned long left, unsigned long delta){
  return left - (delta); 
}

void process_time(){
  if (mt.started) {
     unsigned long current = millis();
     unsigned long delta = current - mt.last_timer_millis;
     mt.last_timer_millis = current;
     mt.time_to_end = subtract(mt.time_to_end, delta);
     if(mt.time_to_end <= 0){
       mt.ended = true;
       mt.started = false;
     }
  }
}

void show_end(){
  //play tone on buzzer
  static int repeat = REPEATTONE;
  if (mt.ended){
    if (repeat > 0){
       if (repeat-- % 100 == 0)
          tone(TONEPIN, FREQ, 2000);
    }else{
      reset_timer();
      repeat = REPEATTONE;
    }
  }
}

static int set_display(const pair_s* pa, int xslide, int yslide){
  int i = 0;
  while (pa[i].c != lend.c){
    // slide p[ostions if needed
    // get the pin representations
    // and add them to display matrix
    int c = pa[i].c + xslide;
    int r = pa[i].r + yslide;
    unsigned short one_led = DMD_getpins(r,c);
    DMD_add_display_data(&one_led, 1);
    i++;
  }
  return i;
}


void show_timer(){
  if(mt.started){
    static const pair_s spa = pair_s{0,1};
    static const pair_s stapa[]={spa, lend};
    // display a dot at the corner
    // if the timer starts running down 
    set_display(stapa,0,0);
  }
  //get units digit
  int val = (int) ceil(mt.time_to_end / (1.0*SCALE)); 
  int u = val % 10;
  //get tens digit
  int t =  val / 10;
  //find the fonts
  const pair_s* ua = ALPHA[16 + u];
  //slide right the units digit
  set_display(ua, 3, 0);  
  if (t>0){
    const pair_s* ta = ALPHA[16+t];
    set_display(ta, -1, 0); 
  }
}

void update_the_game(){
  read_inputs();
  process_time();
  show_end();
  show_timer();
}

void loop() {
  DMD_reset_display_data();
  update_the_game();
  DMD_render_matrix();
  DMD_fps(FPS); 
}


