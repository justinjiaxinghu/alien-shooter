#include "AlienJack.h"
using namespace std;

#define ALIEN_HEIGHT 8 
#define ALIEN_WIDTH 11 
#define _ 0x0000FF //BLACK 
#define X 0xFFFFFF //WHITE

int AlienJack_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,_,_,X,X,X,_,_,_,_, 
    _,X,X,X,X,X,X,X,X,X,_, 
    X,X,X,X,X,X,X,X,X,X,X, 
    X,X,X,_,_,X,_,_,X,X,X, 
    X,X,X,X,X,X,X,X,X,X,X, 
    _,_,_,X,X,_,X,X,_,_,_, 
    _,_,X,X,_,_,_,X,X,_,_, 
    X,X,_,_,_,X,_,_,_,X,X,
};

AlienJack::AlienJack()
{
    this->xPos = 0;
    this->yPos = 0;
    this->alive = true;
    this->speed = 0;
}

AlienJack::AlienJack(int xPos, int yPos, bool alive)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->alive = alive;
    this->speed = 1;
}

void AlienJack::draw(uLCD_4DGL & uLCD)
{
    uLCD.BLIT(xPos, yPos, ALIEN_WIDTH, ALIEN_HEIGHT, AlienJack_sprite);
}

void AlienJack::update(uLCD_4DGL & uLCD)
{
    uLCD.filled_rectangle(xPos, yPos, xPos + ALIEN_WIDTH, yPos + ALIEN_HEIGHT, BLACK);
    if (alive) {
        if (xPos + ALIEN_WIDTH + speed > 127 || xPos + speed < 0) {
            speed *= -1;
        }
        xPos = xPos + speed;
        uLCD.BLIT(xPos, yPos, ALIEN_WIDTH, ALIEN_HEIGHT, AlienJack_sprite);
    }
}


        
        

