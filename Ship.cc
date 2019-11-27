#include <Ship.h>
using namespace std;

#define SHIP_HEIGHT 4
#define SHIP_WIDTH 11 
#define _ 0x000000 //BLACK 
#define X 0xFFFFFF //WHITE

int ship_sprite[SHIP_HEIGHT * SHIP_WIDTH] = {
    X,X,X,X,X,X,X,X,X,X,X, 
    X,X,X,X,X,X,X,X,X,X,X, 
    X,X,X,X,X,X,X,X,X,X,X, 
    X,X,X,X,X,X,X,X,X,X,X, 
};

Ship::Ship()
{
    xPos = 0;
    yPos = 0;
}

Ship::Ship(int xPos, int yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
}

void Ship::draw(uLCD_4DGL & uLCD)
{
    uLCD.BLIT(xPos, yPos, SHIP_WIDTH, SHIP_HEIGHT, ship_sprite);
}

void Ship::update(uLCD_4DGL & uLCD)
{
    if (speed != 0) {
        uLCD.filled_rectangle(xPos, yPos, xPos + SHIP_WIDTH, yPos + SHIP_HEIGHT, BLACK);
        if (xPos + speed + SHIP_WIDTH > 127) {
            xPos = 127 - SHIP_WIDTH;
        } else if (xPos + speed < 0) {
            xPos = 0;
        } else {
            xPos += speed;
        }
        uLCD.BLIT(xPos, yPos, SHIP_WIDTH, SHIP_HEIGHT, ship_sprite);
    }
}
    