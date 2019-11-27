#include "Bullet.h"
using namespace std;

#define BULLET_HEIGHT 3
#define BULLET_WIDTH 3
#define _ 0x000000 //BLACK 
#define X 0xFFFFFF //WHITE


int bullet_sprite[BULLET_HEIGHT * BULLET_WIDTH] = {
    X,X,X,
    X,X,X,
    X,X,X,
};

Bullet::Bullet()
{
    xPos = 0;
    yPos = 0;
    alive = true;
    speed = 0;
}

Bullet::Bullet(int xPos, int yPos, bool alive)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->alive = alive;
    this->speed = -8;
}

void Bullet::draw(uLCD_4DGL & uLCD)
{
    uLCD.BLIT(xPos, yPos, BULLET_WIDTH, BULLET_HEIGHT, bullet_sprite);
}

void Bullet::update(uLCD_4DGL & uLCD)
{
    uLCD.filled_rectangle(xPos, yPos, xPos + BULLET_WIDTH, yPos + BULLET_HEIGHT, BLACK);
    if (alive) {
        if (yPos + speed < 0) {
            alive = false;
        } else {
            yPos += speed;
            uLCD.BLIT(xPos, yPos, BULLET_WIDTH, BULLET_HEIGHT, bullet_sprite);
        }
    }
}



    
        