#ifndef LIGHTS_LIGHTS_H
#define LIGHTS_LIGHTS_H

#include <stdint.h>
#include "../settings.h"


#define FOR_LIGHTS(A) for(char A = 0; A < 9; A++)


namespace lights {

/**
 * Cycle through all color settings first, then cycle through intensity 
 * settings.
*/
void increment_light_setting(Settings& settings);
void initialize_lights(Settings& settings);
void update_lights(Settings& light_setting);
uint8_t get_num_color_profiles();
uint8_t get_num_intensity_profiles();


class LightProfile {
    public:
        virtual void initialize() = 0;
        virtual void update() = 0;
};


class IntensityProfile : public LightProfile {
    public:
        uint16_t* intensity_array;

        virtual void initialize() = 0;
        virtual void update() = 0;
};


uint16_t tween(uint16_t&, uint16_t&, uint16_t&);


};

#endif  // LIGHTS_LIGHTS_H