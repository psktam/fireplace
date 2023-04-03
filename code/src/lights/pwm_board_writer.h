#ifndef PWM_BOARD_WRITER_H
#define PWM_BOARD_WRITER_H
#include <stdint.h>

namespace lights {

/**
 * Send configuration messages to the PWM driver boards on startup.
*/
void initialize_boards();

/**
 * Send the RGB data over to the boards.
*/
void write_to_boards();

};


#endif  // PWM_BOARD_WRITER_H