#include "config.h"

uint16_t RGB_SETTINGS[9][3];
uint8_t PWM_BOARD_MAPPING[9][3] = {
    {ASSIGN_PORT(1, 8), ASSIGN_PORT(1, 0), ASSIGN_PORT(0, 0)},
    {ASSIGN_PORT(1, 9), ASSIGN_PORT(1, 1), ASSIGN_PORT(0, 1)},
    {ASSIGN_PORT(1, 10), ASSIGN_PORT(1, 2), ASSIGN_PORT(0, 2)},
    {ASSIGN_PORT(1, 11), ASSIGN_PORT(1, 3), ASSIGN_PORT(0, 3)},
    {ASSIGN_PORT(1, 12), ASSIGN_PORT(1, 4), ASSIGN_PORT(0, 4)},
    {ASSIGN_PORT(1, 13), ASSIGN_PORT(1, 5), ASSIGN_PORT(0, 5)},
    {ASSIGN_PORT(1, 14), ASSIGN_PORT(1, 6), ASSIGN_PORT(0, 6)},
    {ASSIGN_PORT(1, 15), ASSIGN_PORT(1, 7), ASSIGN_PORT(0, 7)},
    {ASSIGN_PORT(0, 8), ASSIGN_PORT(0, 9), ASSIGN_PORT(0, 10)}
};

uint8_t PWM_BOARD_ADDRS[2] = {
    0x40,
    0x41
};


uint8_t get_pwm_board(uint8_t light_idx, uint8_t color) {
    uint8_t raw_number = PWM_BOARD_MAPPING[light_idx][color];
    return (raw_number >> 6) & 0b00000011;
}


uint8_t get_pwm_port(uint8_t light_idx, uint8_t color) {
    uint8_t raw_number = PWM_BOARD_MAPPING[light_idx][color];
    return raw_number & 0b00111111;
}

