#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings {
    public:
        uint8_t color_setting;
        uint8_t intensity_setting;
};


void save_to_eeprom(Settings&);
void load_from_eeprom(Settings&);
bool different(Settings&, Settings&);


#endif // SETTINGS_H