#include <EEPROM.h>
#include "settings.h"

#define _COLOR_SETTING_IDX 0
#define _INTENSITY_SETTING_IDX 1


void save_to_eeprom(Settings& settings) {
    EEPROM.write(_COLOR_SETTING_IDX, settings.color_setting);
    EEPROM.write(_INTENSITY_SETTING_IDX, settings.intensity_setting);
}


void load_from_eeprom(Settings& settings) {
    EEPROM.get(_COLOR_SETTING_IDX, settings.color_setting);
    EEPROM.get(_INTENSITY_SETTING_IDX, settings.intensity_setting);
}


bool different(Settings& s1, Settings& s2) {
    return (
        (s1.color_setting != s2.color_setting) || 
        (s1.intensity_setting != s2.intensity_setting)
    );
}
