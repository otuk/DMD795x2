#include <DMD795x2.h>
#include "invaders.h"

static enemy_s e;
static hunter_s h;  
static game_s g;

static void set_display_enemy(enemy_s* e){
  for(int i=0; i<ENEMY_SIZE_Y; i++){
    int nx = i%2==0 ? e->posx : e->posx + 1;
    int ny = e->posy+i;    
    e->display[i]=DMD_getpins(nx,ny);
  }  
}

static void set_pos_enemy(enemy_s* e, int x, int y){
  if (x > DOTMATMAX_X - ENEMY_SIZE_X  || x<0 || y> DOTMATMAX_Y - ENEMY_SIZE_Y || y<0)
      return;
  e->posx=x;
  e->posy=y;
  set_display_enemy(e);
}

static void set_display_hunter(hunter_s* hp){
  hp->display[0]=DMD_getpins(hp->posx, hp->posy); 
  if(hp->bx > NOT_FIRED){
    hp->displaylen = HUNTER_SIZE;
    hp->display[1]=DMD_getpins(hp->bx, hp->by); 
  }else
    hp-> displaylen =1; 
}

static void set_pos_hunter(hunter_s* hp, int x, int y){
  if (y> DOTMATMAX_Y-1 || y<0)
      return;
  hp->posx=x;
  hp->posy=y;
  set_display_hunter(hp);
}


static void init_enemy(enemy_s* e, int x, int y){
  e->displaylen = ENEMY_SIZE_Y;
  set_pos_enemy(e, x, y);
}

static void move_right_enemy(enemy_s* e){
  set_pos_enemy(e, e->posx, e->posy + 1);  
}

static void move_left_enemy(enemy_s* e){
  set_pos_enemy(e, e->posx, e->posy - 1);  
}

static void move_down_enemy(enemy_s* e){
  set_pos_enemy(e, e->posx +1 , e->posy );      
} 

static void init_hunter(hunter_s* hp, int y){
   hp->bx = NOT_FIRED;
   hp->by = NOT_FIRED;
   hp->bspeed = BULLET_SPD; // higher is slower
   set_pos_hunter(hp, DOTMATMAX_X -1, y);
}

static void move_right_hunter(hunter_s* hp){
  set_pos_hunter(hp, hp->posx, hp->posy + 1);      
}

static void move_left_hunter(hunter_s* hp){
  set_pos_hunter(hp, hp->posx, hp->posy - 1);       
}

static void fire_hunter(hunter_s* hp){
  if(hp->bx<0){
    hp->bx = hp->posx;
    hp->by = hp->posy;
    set_display_hunter(hp);
  }  
}

static void stop_bullet(hunter_s* hp){
   noTone(TONEPIN); 
   if (hp->bx <0){
      hp->bx = NOT_FIRED;
      hp->by = NOT_FIRED;
      //speed_control = hp->bspeed;
   }
}

static void move_bullet_hunter(hunter_s* hp){
  static int speed_control = hp->bspeed;
  if(hp->bx > NOT_FIRED){
    tone(TONEPIN, FREQ);
    if(--speed_control > 0)
       return;
    else {
       hp->bx -= 1;   
       stop_bullet(hp);
       speed_control = hp->bspeed; 
    }
    set_display_hunter(hp);
  }  
}


static bool check_hit(enemy_s* ep, hunter_s* hp){
  if(hp->bx>-1){
    //if(ep->posx <= hp->bx && ep->posx +2 >hp->bx){
      if(//ep->posx == hp->bx && ep->posy == hp->by  ||
         ep->posx+1 == hp->bx && ep->posy+1 == hp->by // ||  
         //ep->posx == hp->bx && ep->posy+2 == hp->by 
         ) {
            //enemy shot
            return true;
         }     
  }
  return false;
}

static bool check_loss(enemy_s* ep){
  if (ep->posx>=6)
    return true;
  else 
    return false;    
}

static bool move_enemy_randomly(enemy_s* ep){
    int r = random(0,100);
    if (r<30)
       return false;
    r=random(0,6);   
    if (r<2){
      return false;   
    }else if (r<3){
       move_right_enemy(ep);
    }else if (r<4){
       move_left_enemy(ep); 
    }else if (r<5){
      int y = random(0,10);
      if(y>7)
        move_down_enemy(ep);
    }
    return true;
}

//not used - for test only
//if you want to test before adding a joystick/button to read input
// you can use this to move hunter
static void  move_hunter_randomly(hunter_s* hp){
    int r=random(0,35);
    if (r<3){
      move_left_hunter(hp);
    }else if(r<6){
      move_right_hunter(hp);
    }      
    r = random(0,45);
    if(r<1)
       fire_hunter(hp);
}

static void show_game(){
    move_bullet_hunter(&h);
    if(check_hit(&e, &h)){
        if(e.displaylen) e.displaylen--;
        g.hit = true;
    }else if (check_loss(&e)){
       g.lost = true;
    }
    DMD_reset_display_data(); 
    move_enemy_randomly(&e);
    DMD_add_display_data(e.display, e.displaylen);
    DMD_add_display_data(h.display, h.displaylen);
}

static void show_init_sequence(){
   static int init_display_speed = INIT_SHOW_SPD;
   if(init_display_speed--){
     DMD_reset_display_data();
   }else{
     g.init = false;
     init_display_speed = INIT_SHOW_SPD;
   }
}

static void init_game_data(game_s* gp){
  randomSeed(analogRead(A0));
  init_enemy(&e, 0, random(0,6));
  init_hunter(&h, random(0,DOTMATMAX_Y));
  gp->init = true;
  gp->hit = false;
  gp->lost = false;
} 

static void show_hit(){
  stop_bullet(&h);
  static int hit_display_speed = HIT_SHOW_SPD;
  tone(TONEPIN, EXP_FREQ1 + (hit_display_speed*50 ) );
  static unsigned short hit_display[DOTMATMAX_X * DOTMATMAX_Y];
  if(hit_display_speed--){
    int k= 5 - (hit_display_speed/8);
    int m =0;
    for(int i=3-k; i<5+k; i++){
      if(i<0 || i>7) continue;
      for(int j=3-k; j<5+k; j++){
       if(j<0 || j>7) continue;
       if (i==3-k || i==5+k-1)   
         hit_display[m++]=DMD_getpins(i,j);
       else if ((i>3-k && i<5+k-1) && (j==3-k || j==5+k-1))        
         hit_display[m++]=DMD_getpins(i,j);
      }
    }
    DMD_reset_display_data();
    DMD_add_display_data(hit_display, m);
  }else{ 
    init_game_data(&g);
    hit_display_speed = HIT_SHOW_SPD;
    noTone(TONEPIN);
  }  
}

static void show_game_lost(){
  stop_bullet(&h);
  static int lost_display_speed = LOST_SHOW_SPD;
  tone(TONEPIN, LOSS_FREQ1 + ((30-lost_display_speed)*80 ) );
  static unsigned short lost_display[DOTMATMAX_X * DOTMATMAX_Y];
  if(lost_display_speed--){
    int m=0;
    for(int i=0; i<DOTMATMAX_X; i++){
      for(int j=0; j<DOTMATMAX_Y; j++){
        lost_display[m++] = DMD_getpins(i,j);
      }
    };
    DMD_reset_display_data();
    DMD_add_display_data(lost_display, m);
  }else{  
    init_game_data(&g);  
    lost_display_speed = LOST_SHOW_SPD;
    noTone(TONEPIN);
  }  
}

static void read_inputs(){
  int sw = analogRead(A5); // read if Joystick pressed - fire!
  if (sw<=JX_SW_LIM)
    fire_hunter(&h);;
  static int btn_left = JX_SPD;
  static int btn_right = JX_SPD;
  int jx = analogRead(A2); // read if joystick moved on x axis 
                           // (try reading on y axis if this does not work)
  if (jx < JX_RIGHT_LIM){
    if(btn_right--) return;
    move_right_hunter(&h);
    btn_right = JX_SPD;
  }else if(jx > JX_LEFT_LIM){
    if(btn_left--) return;
    move_left_hunter(&h);
    btn_left = JX_SPD; 
  }else{
    btn_right = JX_SPD;
    btn_left = JX_SPD;
  }  
}

static void update_the_game(void){
  if(g.init){
    show_init_sequence();
  }else if(g.hit){
    show_hit();
  }else if(g.lost){
    show_game_lost();
  }else{ //normal game play  
    read_inputs();
    show_game();
  }
}


void setup() {
  // put your setup code here, to run once:
  DMD_setup_ctl_pins(8, 12, 11); //You need to call this as part of you
  init_game_data(&g);
}

void loop() {
  // put your main code here, to run repeatedly:
    update_the_game();
    DMD_render_matrix();
    DMD_fps(60);
}

