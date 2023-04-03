#include <Arduino.h>
#include "hsv_conversion.h"
#include "lights.h"


double mod(double dividend, double divisor) {
    return dividend - (floor(dividend / divisor) * divisor);
}


extern uint16_t HUE_SATURATION_ARRAY[9][2];
extern uint16_t INTENSITIES[9];
extern uint16_t RGB_SETTINGS[9][3];


void lights::write_to_rgb_array() {

    FOR_LIGHTS(light_idx) {
        lights::convert_hsv_to_rgb(
            HUE_SATURATION_ARRAY[light_idx][0],
            HUE_SATURATION_ARRAY[light_idx][1],
            INTENSITIES[light_idx],
            RGB_SETTINGS[light_idx]
        );
    }
}


void lights::convert_hsv_to_rgb(uint16_t hue, uint16_t saturation, uint16_t value, uint16_t* rgb) {
    // hue should map 0 to 0 and 4096 to 360.
    // saturation and value should map 0 to 0 and 4096 to 1.0

    double d_hue = ((double)hue) / 4096.0 * 360.0;
    double d_saturation = ((double)saturation) / 4096.0;
    double d_value = ((double)value) / 4096.0;

    double chroma = d_saturation * d_value;
    double hprime = d_hue / 60.0;

    double x = chroma * (1.0 - abs(mod(hprime, 2.0) - 1.0));

    double rprime, gprime, bprime;
    if ((0.0 <= hprime) && (hprime < 1.0)) {
        rprime = chroma;
        gprime = x;
        bprime = 0.0;
    } else if ((1.0 <= hprime) && (hprime < 2.0)) {
        rprime = x;
        gprime = chroma;
        bprime = 0.0;
    } else if ((2.0 <= hprime) && (hprime < 3.0)) {
        rprime = 0.0;
        gprime = chroma;
        bprime = x;
    } else if ((3.0 <= hprime) && (hprime < 4.0)) {
        rprime = 0.0;
        gprime = x;
        bprime = chroma;
    } else if ((4.0 <= hprime) && (hprime < 5.0)) {
        rprime = x;
        gprime = 0.0;
        bprime = chroma;
    } else {
        rprime = chroma;
        gprime = 0.0;
        bprime = x;
    }

    double m = d_value - chroma;
    double d_r = rprime + m;
    double d_g = gprime + m;
    double d_b = bprime + m;

    // The d_r/g/b values range from 0.0 to 1.0. Remap to integer values s.t.
    // 0->0 and 1.0->4096.
    rgb[0] = (uint16_t)(d_r * 4096.0);
    rgb[1] = (uint16_t)(d_g * 4096.0);
    rgb[2] = (uint16_t)(d_b * 4096.0);
}