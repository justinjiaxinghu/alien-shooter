#include "ScreenObject.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public ScreenObject
{
    public:
        Bullet();
        Bullet(int, int, bool);
        virtual void draw(uLCD_4DGL &);
        virtual void update(uLCD_4DGL &);
};
        
#endif