#include <Wire.h>

#include "src/button.h"
#include "src/config.h"
#include "src/lights/hsv_conversion.h"
#include "src/lights/lights.h"
#include "src/lights/pwm_board_writer.h"
#include "src/settings.h"
#include "src/time_handling.h"

Settings settings;
Settings old_settings;
button_ctrl::Button mode_button(MODE_BUTTON_INPUT_PIN);

unsigned long last_update_time;

void setup() {
    load_from_eeprom(settings);
    old_settings = settings;

    Serial.begin(9600);
    Serial.println("Booting up");

    // Start I2C bus.
    Wire.begin();
    lights::initialize_boards();
    Serial.println("I2C started");

    // Map button I/O.
    pinMode(MODE_BUTTON_INPUT_PIN, INPUT);

    // Start cycle clock.
    last_update_time = micros();
    Serial.println("Initialization complete. Begin looping");
}

void loop() {
    // Main state machine!
    if (time_diff(last_update_time, micros()) >= CYCLE_DT_uS) {
        // ----------------------- Update things -------------------------------
        mode_button.update();
        lights::update_lights(settings);
        lights::write_to_rgb_array();
        lights::write_to_boards();

        // ----------------------- Check things --------------------------------
        // Has the mode button been pressed?
        if (mode_button.rising_edge(CYCLE_DT_uS * 5)) { 
            lights::increment_light_setting(settings);
        }

        // Update the lights according to the selected settings.
        // Here, we don't have to do anything because the setting has already 
        // been updated and will be passed to the light controller's update 
        // function on the next cycle.

        // Finally, check to see if settings have changed. If so, write to 
        // EEPROM.
        if (different(settings, old_settings)) {
            save_to_eeprom(settings);
            old_settings = settings;
        }

        last_update_time = micros();
    }
}