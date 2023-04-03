#ifndef COLOR_PROFILES_H
#define COLOR_PROFILES_H

#include "lights.h"

namespace lights {


class OrangeProfile : public LightProfile {
    public:
        void initialize();
        void update();
};


class RandomColorProfile : public LightProfile {
    public:
        void initialize();
        void update();
};

};


#endif  // COLOR_PROFILES_H