#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "../config.h"
#include "lights.h"
#include "pwm_board_writer.h"


extern uint8_t PWM_BOARD_MAPPING[9][3];
extern uint16_t RGB_SETTINGS[9][3];
extern uint8_t PWM_BOARD_ADDRS[2];


void lights::initialize_boards() {
    // Reset all boards.
    for (char board = 0; board < 2; board++) {
        Wire.beginTransmission(PWM_BOARD_ADDRS[board]);
        Wire.write(0x00);
        Wire.write(0x00);
        Wire.endTransmission();

        delay(10);

        // Since we will turn on all LEDs at the same time, might as well just
        // set the ON time to 0
        for (char channel=0; channel < 16; channel++) {
            Wire.beginTransmission(PWM_BOARD_ADDRS[board]);
            Wire.write(0x06 + 4 * channel);
            Wire.write(0x00);
            Wire.write(0x00);
            Wire.endTransmission();
        }
    }
}


void lights::write_to_boards() {
    FOR_LIGHTS(light_idx) {
        for (char color = 0; color < 3; color++) {
            auto board = get_pwm_board(light_idx, color);
            auto port = get_pwm_port(light_idx, color);

            uint16_t duty_cycle = RGB_SETTINGS[light_idx][color];
            uint8_t board_addr = PWM_BOARD_ADDRS[board];

            // Each port has 4 registers associated with it. ON Low, ON High,
            // OFF Low, and OFF high. ON Low gets the least significant 8 bits 
            // of the on time, and ON high gets the most significant 8 bits of 
            // the off time. We will only fiddle with the off times.
            Wire.beginTransmission(board_addr);
            Wire.write(0x06 + (4 * port) + 2);
            Wire.write(duty_cycle);
            Wire.write(duty_cycle >> 8);
            Wire.endTransmission();
        }
    }
}