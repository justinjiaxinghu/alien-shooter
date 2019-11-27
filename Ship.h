#include "ScreenObject.h"

#ifndef SHIP_H
#define SHIP_H

class Ship : public ScreenObject
{
    public:
        Ship();
        Ship(int, int);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
};

#endif
        