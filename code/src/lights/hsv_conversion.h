#ifndef HSV_CONVERSION_H
#define HSV_CONVERSION_H
#include <stdint.h>

namespace lights {

/**
 * Take the HUE_SATURATION_ARRAY and the INTENSITIES array and convert them to 
 * RGB values. Then write those values to the RGB_SETTINGS array.
*/
void write_to_rgb_array();


/**
 * Take in hue, saturation, and value, and write them out into an RGB vector.
*/
void convert_hsv_to_rgb(uint16_t hue, uint16_t saturation, uint16_t value, uint16_t* rgb);

};


#endif  // HSV_CONVERSION_H