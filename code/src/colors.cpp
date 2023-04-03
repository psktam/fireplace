#include "colors.h"
#include "config.h"


namespace colors {
    uint16_t ORANGE[3] = {4096, 2185, 0};
};


void colors::scale(uint16_t intensity, uint16_t* base_color, uint16_t* out) {
    double scaler = (double)intensity / 4096.0;
    out[R] = (uint16_t)(scaler * (double)base_color[R]);
    out[G] = (uint16_t)(scaler * (double)base_color[G]);
    out[B] = (uint16_t)(scaler * (double)base_color[B]);
}