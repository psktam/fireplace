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


void lights::increment_light_setting(Settings& settings) {
    uint8_t num_color_settings = sizeof(color_profiles) / sizeof(*color_profiles);
    uint8_t num_intensity_settings = sizeof(intensity_profiles) / sizeof(*intensity_profiles);

    settings.color_setting = (settings.color_setting + 1) % num_color_settings;

    if (settings.color_setting == 0) {
        settings.intensity_setting = (settings.intensity_setting + 1) % num_intensity_settings;
    }

    // Take the newly-selected color and intensity settings and initialize them.
    color_profiles[settings.color_setting]->initialize();
    intensity_profiles[settings.intensity_setting]->initialize();
}


void lights::update_lights(Settings& settings) {
    color_profiles[settings.color_setting]->update();
    intensity_profiles[settings.intensity_setting]->update();
}


uint16_t lights::tween(uint16_t& target, uint16_t& current, double& rate) {
    double d_target = (double)target;
    double d_current = (double)current;

    return (uint16_t)((
        (d_current * (1.0 - rate)) +
        (d_target * rate)
    ) * 0.5);
}