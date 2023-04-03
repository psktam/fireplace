#include <Arduino.h>
#include "color_profiles.h"


uint16_t HUE_SATURATION_ARRAY[9][2];
uint16_t TARGET_HUE_SATURATION_ARRAY[9][2];


void lights::OrangeProfile::initialize() {
    FOR_LIGHTS(light_idx) {
        // Set all hue and saturation values to orange.
        HUE_SATURATION_ARRAY[light_idx][0] = 1106;
        HUE_SATURATION_ARRAY[light_idx][1] = 4096;
    }
}

void lights::OrangeProfile::update() {
    // Does nothing. Because we don't change color from cycle to cycle lol.
}


void lights::RandomColorProfile::initialize() {
    FOR_LIGHTS(light_idx) {
        TARGET_HUE_SATURATION_ARRAY[light_idx][0] = random(4096);
        TARGET_HUE_SATURATION_ARRAY[light_idx][1] = random(4096);
    }
}

void lights::RandomColorProfile::update() {
    double rate = 0.001;
    FOR_LIGHTS(light_idx) {
        // For each light, roll to see if we want to change color. Then tween
        // to the target color.

        if (random(100) > 98) {  // Change color.
            TARGET_HUE_SATURATION_ARRAY[light_idx][0] = random(4096);
            TARGET_HUE_SATURATION_ARRAY[light_idx][1] = random(4096);
        }

        HUE_SATURATION_ARRAY[light_idx][0] = lights::tween(
            TARGET_HUE_SATURATION_ARRAY[light_idx][0],
            HUE_SATURATION_ARRAY[light_idx][0], 
            rate
        );
        HUE_SATURATION_ARRAY[light_idx][1] = lights::tween(
            TARGET_HUE_SATURATION_ARRAY[light_idx][1],
            HUE_SATURATION_ARRAY[light_idx][1],
            rate
        );
    }
}