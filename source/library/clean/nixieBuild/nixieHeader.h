#ifndef NIXIEHEADER_H
#define NIXIEHEADER_H

#include <stdint.h>

const uint8_t select_pins[6] = {0, 1, 2, 3, 4, 5};
const uint8_t data_pins[4] = {6, 7, 8, 9};

const uint8_t nixieZero[4] = {0, 0, 0, 0};
const uint8_t nixieOne[4] = {0, 0, 0, 1};
const uint8_t nixieTwo[4] = {0, 0, 1, 0};
const uint8_t nixieThree[4] = {0, 0, 1, 1};
const uint8_t nixieFour[4] = {0, 1, 0, 0};
const uint8_t nixieFive[4] = {0, 1, 0, 1};
const uint8_t nixieSix[4] = {0, 1, 1, 0};
const uint8_t nixieSeven[4] = {0, 1, 1, 1};
const uint8_t nixieEight[4] = {1, 0, 0, 0};
const uint8_t nixieNine[4] = {1, 0, 0, 1};


#endif
