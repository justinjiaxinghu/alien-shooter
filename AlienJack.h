#include "ScreenObject.h"

#ifndef ALIENJACK_H
#define ALIENJACK_H

class AlienJack : public ScreenObject
{
    public:
        AlienJack();
        AlienJack(int, int, bool);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
};

#endif
        
