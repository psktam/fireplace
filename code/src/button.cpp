#include <Arduino.h>
#include "button.h"
#include "config.h"

namespace button_ctrl {


Button::Button(int _pin_number) {
    pin_number = _pin_number;
}


bool Button::rising_edge(unsigned long persist_us) {
    return (
        (time_since_on_us >= persist_us) && 
        (time_since_on_us < (persist_us + CYCLE_DT_uS)) &&
        digitalRead(pin_number)  // To guard overflow.
    );
}


void Button::update() {

    last_status = current_status;
    current_status = digitalRead(pin_number);

    if (current_status) {
        time_since_on_us = 0;
    }
    else {
        time_since_on_us += CYCLE_DT_uS;
    }

}

};