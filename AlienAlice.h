#include "ScreenObject.h"

#ifndef ALIENALICE_H
#define ALIENALICE_H

class AlienAlice : public ScreenObject
{
    public:
        AlienAlice();
        AlienAlice(int, int, bool);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
};

#endif
        
