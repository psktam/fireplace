#include <Arduino.h>
#include <stdint.h>

#include "../config.h"
#include "intensity_profiles.h"


uint16_t INTENSITIES[9];
uint16_t TARGET_INTENSITIES[9];


void lights::Flickering::initialize() {
    FOR_LIGHTS(light_idx) {
        INTENSITIES[light_idx] = random(4096);
        TARGET_INTENSITIES[light_idx] = random(4096);
    }
}

void lights::Flickering::update() {
    // For each light, first roll to see if we change intensity. If so, change 
    // target intensity and tween to the value.
    double rate = 0.01;
    FOR_LIGHTS(light_idx) {
        if (random(100) > 98) {
            TARGET_INTENSITIES[light_idx] = random(4096);
        }

        INTENSITIES[light_idx] = lights::tween(
            TARGET_INTENSITIES[light_idx],
            INTENSITIES[light_idx],
            rate
        );
    }
}


void lights::CenterPulse::initialize() {
    phase = 0.0;
}

void lights::CenterPulse::update() {
    // Outer lights will be at a 90 degree offset to the center lights to show
    // direction.
    double center_signal = cos(phase) * 2048.0 + 2048.0;
    double outer_signal = sin(phase) * 2048.0 + 2048.0;

    // Set the center lights.
    INTENSITIES[3] = (uint16_t)center_signal;
    INTENSITIES[6] = (uint16_t)center_signal;
    INTENSITIES[7] = (uint16_t)center_signal;

    // Now the outers.
    INTENSITIES[1] = (uint16_t)outer_signal;
    INTENSITIES[2] = (uint16_t)outer_signal;
    INTENSITIES[4] = (uint16_t)outer_signal;
    INTENSITIES[5] = (uint16_t)outer_signal;
    INTENSITIES[8] = (uint16_t)outer_signal;

    // Finally advance the phase.
    double target_period = 1500000.0;  // microseconds, so 1.5 second
    double phase_delta = 2.0 * PI * CYCLE_DT_uS / target_period;
    phase += phase_delta;
    if (phase > (2.0 * PI)) {
        phase -= 2.0 * PI;
    }
}


void lights::Pulsing::initialize() {
    FOR_LIGHTS(light_idx) {
        // Phases can be anywhere between 0 and 2pi
        phases[light_idx] = ((double)random(0, 4096)) / 4096.0 * 2.0 * PI;
        // Periods are to be anywhere between 1 and 3 seconds
        periods[light_idx] = ((double)random(0, 4096)) / 4096.0 * 2.0 + 1.0;
    }
}

void lights::Pulsing::update() {
    FOR_LIGHTS(light_idx) {
        double signal = sin(phases[light_idx]) * 2048.0 + 2048.0;
        INTENSITIES[light_idx] = (uint16_t)signal;

        double target_period_us = periods[light_idx] * 1000000.0;
        double phase_delta = 2.0 * PI * CYCLE_DT_uS / target_period_us;
        phases[light_idx] += phase_delta;

        if (phases[light_idx] > (2.0 * PI)) {
            phases[light_idx] -= 2.0 * PI;
        }
    }
}