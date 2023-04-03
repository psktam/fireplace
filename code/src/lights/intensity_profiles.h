#ifndef INTENSITY_PROFILES_H
#define INTENSITY_PROFILES_H
#include "lights.h"


namespace lights {

/**
 * Random flames flicker.
*/
class Flickering : public LightProfile {
    public:
        void initialize();
        void update();
};


/**
 * Fire pulses from the center and radiates outwards.
*/
class CenterPulse : public LightProfile {
    private:
        double phase;

    public:
        void initialize();
        void update();
};


/**
 * Random flames pulse sinusoidally slightly out of phase with 
 * each other.
*/
class Pulsing : public LightProfile {
    private:
        double phases[9];
        double periods[9];

    public:
        void initialize();
        void update();
};

};


#endif  // INTENSITY_PROFILES_H