#include "AlienBob.h"
using namespace std;

#define ALIEN_HEIGHT 8 
#define ALIEN_WIDTH 11 
#define _ 0x000000 //BLACK 
#define X 0xFFFFFF //WHITE


int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,X,_,_,_,_,_,X,_,_,
    _,_,_,X,_,_,_,X,_,_,_,
    _,_,X,X,X,X,X,X,X,_,_,
    _,X,X,_,X,X,X,_,X,X,_,
    X,X,X,X,X,X,X,X,X,X,X,
    X,_,X,X,X,X,X,X,X,_,X,
    X,_,X,_,_,_,_,_,X,_,X,
    _,_,_,X,X,_,X,X,_,_,_,
};

int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,X,_,_,_,_,_,X,_,_,
    X,_,_,X,_,_,_,X,_,_,X,
    X,_,X,X,X,X,X,X,X,_,X,
    X,X,X,_,X,X,X,_,X,X,X,
    X,X,X,X,X,X,X,X,X,X,X,
    _,_,X,X,X,X,X,X,X,_,_,
    _,_,X,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,X,_,
};

AlienBob::AlienBob()
{
    this->xPos = 0;
    this->yPos = 0;
    this->alive = true;
    this->speed = 0;
    this->state = 0;
}

AlienBob::AlienBob(int xPos, int yPos, bool alive)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->alive = alive;
    this->speed = 6;
    this->state = 1;
}

void AlienBob::draw(uLCD_4DGL & uLCD)
{
    uLCD.BLIT(xPos, yPos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobDown_sprite);
}

void AlienBob::update(uLCD_4DGL & uLCD)
{
    uLCD.filled_rectangle(xPos, yPos, xPos + ALIEN_WIDTH, yPos + ALIEN_HEIGHT, BLACK);
    if (alive) {
        if (xPos + ALIEN_WIDTH + speed > 127 || xPos + speed < 0) {
            speed *= -1;
        }
        xPos = xPos + speed;
        
        if (state == 1) {
            uLCD.BLIT(xPos, yPos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobDown_sprite);
            state = 0;
        } else {
            uLCD.BLIT(xPos, yPos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobUp_sprite);
            state = 1;
        }
    }
}