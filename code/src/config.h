#ifndef FIREPLACE_CONFIG_H
#define FIREPLACE_CONFIG_H

#include <stdint.h>

#define CYCLE_DT_uS 10000
#define CYCLE_FREQ 100

#define MODE_BUTTON_INPUT_PIN 7

#define R 0
#define G 1
#define B 2

#define ASSIGN_PORT(_BOARD, _PORT) (_BOARD << 2) | _PORT

// I guess C++ doesn't allow you to call functions outside of functions. Which
// makes sense. Too used to Python lol.
void initialize_pwm_mapping();
uint8_t get_pwm_board(uint8_t light_idx, uint8_t color);
uint8_t get_pwm_port(uint8_t light_idx, uint8_t color);

#endif // FIREPLACE_CONFIG_H