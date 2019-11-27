#include "ScreenObject.h"

#ifndef ALIENBOB_H
#define ALIENBOB_H

class AlienBob : public ScreenObject
{
    public:
        AlienBob();
        AlienBob(int, int, bool);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
    private:
        int state;
};
        
#endif