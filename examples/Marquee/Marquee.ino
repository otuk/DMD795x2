#include <DMD795x2.h>
#include <DMD_Alpha.h>

#include <string.h>  //strlen(
#include <ctype.h>  //toupper(
#include <math.h>  //ceil(


#define SPD 6
#define LEDON_DELAY 28
#define FPS 200
#define INITIAL_SLIDE -15
#define MAX_COL 7

const byte ALPHA_WIDTH = 5;  // shd this not be a variable per letter, for better reading?
const byte MAX_LETTERS_DISPLAYED = ceil((MAX_COL+1.)/ALPHA_WIDTH)+1;

//char* text_to_scroll = " !\"#$%&'()*+,-./0123456789:;<=>?@A B C D E F G H I J K L M N O P Q R S T U V W X Y Z  X";
const char* text_to_scroll = "  The quick brown fox jumps over the lazy dog 0123456789   X";// need a last visible character to signal end of string to display
//const char* text_to_scroll = "    Once upon a time, sixty years ago, a little girl lived in the \
//Big Woods of Wisconsin, in a little gray house made of logs. \
//\
//Laura Ingalls Wilder’s Little House in the Big Woods           \
//X";

short tlen =  strlen(text_to_scroll);

const pair_s* get_letter(const char* c){
  byte idx = toupper(*c)-32;
  if(idx >= ALPHA_SIZE){
    return NOTYET;
  }
  return ALPHA[idx];  
}

void init_the_game(){
  // append the last end chart to text to scroll
}

void update_the_game(){
  DMD_reset_display_data();
  unsigned short one_led[DOTMATMAX_X*DOTMATMAX_Y]={0x00};  
  static long long slide = INITIAL_SLIDE;
  slide++;
  short m=0; // number of dots to be displayed on this update()
  short lw=0; //how many letters shown in this update() on the dsiplay
  static short lale=1;  // last letter displayed on DotMatrixDisplay
  for(short le=lale-1; le<tlen; le++){
    if (lw==MAX_LETTERS_DISPLAYED){ // for optimization only 3 is 1 more than max letters 1 display 
                                    // can show at a time given display has 8 columns 
                                    // and letters are 5 col. wide.  avoids unnecessary operations.
                                
      break;
    }  
    long long shift = ((SPD-slide)/SPD) + le*ALPHA_WIDTH ; //how much shd each letter be shifted to the left
    byte ldot = 0;    
    const pair_s* alfa = get_letter(text_to_scroll+le);
    for(;;){ // loop thru the dots of a single letter - alfa, and decide if they shd be shown based on shift
      if (alfa[ldot].c == lend.c) // but first check if this is the last dot of the letter, ie if it is "lend"
        break;
      long long col = alfa[ldot].c+ shift ; // apply shift
      if (col > MAX_COL){ // check if after shift the letter is visible ie within the max-column
        break;
      }  
      if (col < 0){ //check if it is shifted left out of the display
        ldot++;
        continue;
      }  
      one_led[m++] = DMD_getpins(alfa[ldot].r, col); // add this dot to be displayed list
      if (le != lale) { // count how many letters are displayed in this screen update
        lw++; // one more letter, the max is 3 for optimization
        lale = le;
        if (le == (tlen-1)){  
           slide = INITIAL_SLIDE;  // if the letter displayed is the very end of string time to reset slide
           lale =0;
           //text_to_scroll = text_to_scroll2;
           //Serial.println("Reset slide"); 
        } 
      }
      ldot++;
    } 
  }
  one_led[m]=0x00; // needed?  
  DMD_add_display_data(one_led, m); 
  delay(LEDON_DELAY);// set for a good reading speed
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

  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    update_the_game();
    DMD_render_matrix();
    DMD_fps(FPS); 
}
