#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H
#include <stdint.h>

namespace button_ctrl {


class Button {
    public:
        int pin_number;
        bool current_status;
        bool last_status;
        unsigned long time_since_on_us;

        Button(int _pin_number);
        bool rising_edge(uint32_t persist_ms);
        void update();
};


};

#endif  // BUTTON_CONTROL_H