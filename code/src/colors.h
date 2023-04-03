#ifndef COLORS_H
#define COLORS_H
#include <stdint.h>

namespace colors {
// All colors are in 12-bit RGB values. Max value is 4096.

extern uint16_t ORANGE[3];


void scale(uint16_t intensity, uint16_t* base_color, uint16_t* out);


};

#endif