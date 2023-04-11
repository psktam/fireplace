#include <Arduino.h>
#include <stdint.h>
#include "lights.h"
#include "color_profiles.h"
#include "intensity_profiles.h"
#include "../settings.h"


lights::OrangeProfile _orange_profile;
lights::RandomColorProfile _random_color_profile;


lights::LightProfile* color_profiles[] = {
    &_orange_profile,
    &_random_color_profile
};


lights::Flickering _flickering_flame_profile;
lights::CenterPulse _centerpulse_profile;
lights::Pulsing _pulsing_profile;

lights::LightProfile* intensity_profiles[] = {
    &_flickering_flame_profile,
    &_centerpulse_profile,
    &_pulsing_profile
};


uint8_t lights::get_num_color_profiles() {
    return sizeof(color_profiles) / sizeof(*color_profiles);
}


uint8_t lights::get_num_intensity_profiles() {
    return sizeof(intensity_profiles) / sizeof(*intensity_profiles);
}


void lights::increment_light_setting(Settings& settings) {
    uint8_t num_color_settings = get_num_color_profiles();
    uint8_t num_intensity_settings = get_num_intensity_profiles();

    settings.color_setting = (settings.color_setting + 1) % num_color_settings;

    if (settings.color_setting == 0) {
        settings.intensity_setting = (settings.intensity_setting + 1) % num_intensity_settings;
    }

    // Take the newly-selected color and intensity settings and initialize them.
    initialize_lights(settings);
}


void lights::initialize_lights(Settings& settings) {
    color_profiles[settings.color_setting]->initialize();
    intensity_profiles[settings.intensity_setting]->initialize();
}


void lights::update_lights(Settings& settings) {
    color_profiles[settings.color_setting]->update();
    intensity_profiles[settings.intensity_setting]->update();
}


uint16_t lights::tween(uint16_t& target, uint16_t& current, uint16_t& rate) {
    double d_target = (double)target;
    double d_current = (double)current;

    if (d_current < d_target) {
        return min(d_current + rate, d_target);
    }
    else if (d_current > d_target) {
        return max(d_current - rate, d_target);
    }
    else {
        return d_target;
    }
}