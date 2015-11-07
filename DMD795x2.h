#include <Arduino.h>

#ifndef DMD795x2_h
#define DMD795x2_h

#define LDELAY 20
#define DOTMATMAX_X 8
#define DOTMATMAX_Y 8

static const unsigned short helper [] = {
  0b0000000000000001,
  0b0000000000000010,
  0b0000000000000100,
  0b0000000000001000,
  0b0000000000010000,
  0b0000000000100000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000000100000000,
  0b0000001000000000,
  0b0000010000000000,
  0b0000100000000000,
  0b0001000000000000,
  0b0010000000000000,
  0b0100000000000000,
  0b1000000000000000
};


// this is the "weird" list of what led dotmatrix pins control on the dot matrix I am using
// eg pin9 turns on row 1 and pin 13 turns on column 1
// columns are the cathodes, so to run on the colum you set it to zero
// to turn on the anodes/rows you set them to one
// this complication is take care by the next getpins function by use of the ini variable that represents
// an initial state where no leds are ON on the matrix.
static const byte cp[] = {13, 3, 4, 10, 6, 11, 15, 16};
static const byte rp[] = {9, 14, 8, 12, 1, 7, 2, 5};
static const  unsigned short ALL_OFF = 0b1101011000101100;  // all leds off


static const unsigned short hc [] = {
  helper[cp[0] - 1],
  helper[cp[1] - 1],
  helper[cp[2] - 1],
  helper[cp[3] - 1],
  helper[cp[4] - 1],
  helper[cp[5] - 1],
  helper[cp[6] - 1],
  helper[cp[7] - 1]
};

static const unsigned short coff[] = {
  hc[1] | hc[2] | hc[3] | hc[4] | hc[5] | hc[6] | hc[7],
  hc[0] | hc[2] | hc[3] | hc[4] | hc[5] | hc[6] | hc[7],
  hc[0] | hc[1] | hc[3] | hc[4] | hc[5] | hc[6] | hc[7],
  hc[0] | hc[1] | hc[2] | hc[4] | hc[5] | hc[6] | hc[7],
  hc[0] | hc[1] | hc[2] | hc[3] | hc[5] | hc[6] | hc[7],
  hc[0] | hc[1] | hc[2] | hc[3] | hc[4] | hc[6] | hc[7],
  hc[0] | hc[1] | hc[2] | hc[3] | hc[4] | hc[5] | hc[7],
  hc[0] | hc[1] | hc[2] | hc[3] | hc[4] | hc[5] | hc[6]
};

void DMD_setup_ctl_pins(int latchPin, int clockPin, int dataPin );
unsigned short DMD_getpins(int r, int c);
void DMD_reset_display_data();
void DMD_add_display_data(unsigned short* dots, int len);
void DMD_render_matrix();
void DMD_fps(int fps);

#endif
