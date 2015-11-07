
//game sprite constants
//do not change these
#define ENEMY_SIZE_Y  3
#define ENEMY_SIZE_X  2
#define HUNTER_SIZE 2
#define NOT_FIRED -1

// you can change the _SPD constants to see 
// how they impact the display and game play
// _SPD s are used as countdowns to zero, so smaller is faster 
#define BULLET_SPD 5
#define LOST_SHOW_SPD 20
#define HIT_SHOW_SPD 40
#define INIT_SHOW_SPD 60

//jotstick parameters/thresholds
#define JX_SPD 2
#define JX_SW_LIM 3
#define JX_LEFT_LIM 516
#define JX_RIGHT_LIM 508

//controls the tunes for rocket fire, explosion and loss
#define TONEPIN 6
#define FREQ 100
#define EXP_FREQ1 1000 
#define LOSS_FREQ1 500 


typedef struct {
  boolean init;
  boolean hit;
  boolean lost;
}  game_s;

typedef struct {
  int posx;
  int posy;
  int bx;
  int by;
  int bspeed;
  int displaylen;
  unsigned short display[HUNTER_SIZE];
} hunter_s;

typedef struct {
  int posx;
  int posy;
  int displaylen;
  unsigned short display[ENEMY_SIZE_Y];
} enemy_s;



 
