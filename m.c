#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "inttypes.h"

#define BUFSIZE 4096

#define M       0x6d
#define I       0x69
#define S       0x73
#define P       0x70

#define _________0  0x00
#define _______M_0  0x01
#define ______MI_0  0x02
#define _____MIS_0  0x03
#define ____MISS_0  0x04
#define ___MISSI_0  0x05
#define __MISSIS_0  0x06
#define _MISSISS_0  0x07
#define MISSISSI_0  0x08
#define ISSISSIP_0  0x09
#define SSISSIPP_0  0x0a
#define _________1  0x40
#define _______M_1  0x41
#define ______MI_1  0x42
#define _____MIS_1  0x43
#define ____MISS_1  0x44
#define ___MISSI_1  0x45
#define __MISSIS_1  0x46
#define _MISSISS_1  0x47
#define MISSISSI_1  0x48
#define ISSISSIP_1  0x49
#define SSISSIPP_1  0x4a
#define _________2  0x80

uint64_t buffer[BUFSIZE];
uint8_t  trans[23][256];

// prototypes
void init();
uint8_t transit(uint8_t s, uint64_t x);

int main() {
  init();

  uint8_t  state = 0;
  uint64_t count = 0;

  int file = open("m.txt", O_RDONLY);

  for(;;) {
    ssize_t len = read(file, buffer, sizeof buffer);

    if (len < sizeof buffer) {
      break;
    }

    for (size_t i=0; i < BUFSIZE; i++) {
      state = transit(state, buffer[i]);
      if (state == 1) { printf("FOO\n", state); }
      count++;
      state %= 0x40;
    }
  }

  printf("%" PRIu64 "\n", count);
}

uint8_t transit(uint8_t s, uint64_t x) {
  return
    trans[
      trans[
        trans[
          trans[
            trans[
              trans[
                trans[
                  trans[ s
                  ] [(x & 0xff) >> 0x00]
                ] [(x & 0xff00) >> 0x08]
              ] [(x & 0xff0000) >> 0x10]
            ] [(x & 0xff000000) >> 0x18]
          ] [(x & 0xff00000000) >> 0x20]
        ] [(x & 0xff0000000000) >> 0x28]
      ] [(x & 0xff000000000000) >> 0x30]
    ] [(x & 0xff00000000000000) >> 0x38];
}

void init() {
  // Initialise buffer with zeros.
  memset(&buffer, 0, sizeof buffer);
  // Initialise transition table.
  memset(trans[_________0], _________0, 256);
  memset(trans[_______M_0], _________0, 256);
  memset(trans[______MI_0], _________0, 256);
  memset(trans[_____MIS_0], _________0, 256);
  memset(trans[____MISS_0], _________0, 256);
  memset(trans[___MISSI_0], _________0, 256);
  memset(trans[__MISSIS_0], _________0, 256);
  memset(trans[_MISSISS_0], _________0, 256);
  memset(trans[MISSISSI_0], _________0, 256);
  memset(trans[ISSISSIP_0], _________0, 256);
  memset(trans[SSISSIPP_0], _________0, 256);
  memset(trans[_________1], _________1, 256);
  memset(trans[_______M_1], _________1, 256);
  memset(trans[______MI_1], _________1, 256);
  memset(trans[_____MIS_1], _________1, 256);
  memset(trans[____MISS_1], _________1, 256);
  memset(trans[___MISSI_1], _________1, 256);
  memset(trans[__MISSIS_1], _________1, 256);
  memset(trans[_MISSISS_1], _________1, 256);
  memset(trans[MISSISSI_1], _________1, 256);
  memset(trans[ISSISSIP_1], _________1, 256);
  memset(trans[SSISSIPP_1], _________1, 256);
  memset(trans[_________2], _________2, 256);

  trans[_________0][M] = _______M_0;
  trans[_______M_0][I] = ______MI_0;
  trans[______MI_0][S] = _____MIS_0;
  trans[_____MIS_0][S] = ____MISS_0;
  trans[____MISS_0][I] = ___MISSI_0;
  trans[___MISSI_0][S] = __MISSIS_0;
  trans[__MISSIS_0][S] = _MISSISS_0;
  trans[_MISSISS_0][I] = MISSISSI_0;
  trans[MISSISSI_0][P] = ISSISSIP_0;
  trans[ISSISSIP_0][P] = SSISSIPP_0;
  trans[SSISSIPP_0][I] = _________1;
  trans[_________1][M] = _______M_1;
  trans[_______M_1][I] = ______MI_1;
  trans[______MI_1][S] = _____MIS_1;
  trans[_____MIS_1][S] = ____MISS_1;
  trans[____MISS_1][I] = ___MISSI_1;
  trans[___MISSI_1][S] = __MISSIS_1;
  trans[__MISSIS_1][S] = _MISSISS_1;
  trans[_MISSISS_1][I] = MISSISSI_1;
  trans[MISSISSI_1][P] = ISSISSIP_1;
  trans[ISSISSIP_1][P] = MISSISSI_1;
  trans[SSISSIPP_1][I] = _________2;
}
