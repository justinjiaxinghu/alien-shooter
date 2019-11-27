#include "ScreenObject.h"

#ifndef ALIENJILL_H
#define ALIENJILL_H

class AlienJill : public ScreenObject
{
    public:
        AlienJill();
        AlienJill(int, int, bool);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
};

#endif
        
