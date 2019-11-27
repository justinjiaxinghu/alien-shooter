#include "AlienAlice.h"
#include "AlienBob.h"
#include "AlienJack.h"
#include "AlienJill.h"
#include "Bullet.h"
#include "Ship.h"
#include "mbed.h"
#include "TMP36.h"
#include "SDFileSystem.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "Speaker.h"
#include "Shiftbrite.h"
#include "MMA8452.h"
#include "cstdlib"
#include <vector>

using namespace std;
Speaker mySpeaker(p24);
Timer t;
vector<ScreenObject *> v;
ScreenObject * ship = new Ship(60, 123);
ScreenObject * bullet = new Bullet(ship->getXPos() + 5, ship->getYPos() - 4, true);
int bulletCount = 0;
int enemiesAlive = 6;
Serial pc(USBTX,USBRX);
MMA8452 acc(p28, p27, 40000);
uLCD_4DGL uLCD(p9, p10, p11); // create a global lcd object

// use class to setup pushbuttons pins
PinDetect pb1(p21);
PinDetect pb2(p22); 
PinDetect pb3(p23);

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    if (bulletCount == 0) {
        bullet = new Bullet(ship->getXPos() + 5, ship->getYPos() - 4, true);
        v.push_back(bullet);
        bulletCount++;
    }
}
// Callback routine is interrupt activated by a debounced pb2 hit
void pb2_hit_callback (void)
{
    enemiesAlive = 0;
}
// Callback routine is interrupt activated by a debounced pb3 hit
void pb3_hit_callback (void)
{
// ADD CODE HERE
}

void playMusic(Speaker & mySpeaker)
{
    mySpeaker.PlayNote(200.0,0.3,0.1);
    mySpeaker.PlayNote(300.0,0.3,0.1);
    mySpeaker.PlayNote(400.0,0.3,0.1);
}

int main()
{
    uLCD.baudrate(299999);
    wait(0.5);
    // Use internal pullups for the three pushbuttons
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    pb1.attach_deasserted(&pb1_hit_callback);
    pb2.attach_deasserted(&pb2_hit_callback);
    pb3.attach_deasserted(&pb3_hit_callback);
    // Start sampling pb inputs using interrupts
    pb1.setSampleFrequency();
    pb2.setSampleFrequency();
    pb3.setSampleFrequency();
    // pushbuttons now setup and running
    
    int x = 0, y = 0, z = 0;
    
//    ScreenObject * alice1 = new AlienAlice(20,0,true);
//    ScreenObject * alice2 = new AlienAlice(40,11,true);
//    ScreenObject * bob1 = new AlienBob(20,22,true);
//    ScreenObject * bob2 = new AlienBob(60,33,true);
//    
//    v.push_back(alice1);
//    v.push_back(alice2);
//    v.push_back(bob1);
//    v.push_back(bob2);
    
    srand(time(0));
    int currY = 0;
    for (int i = 0; i < 6; i++) {
        int randNum = rand() % 4;
        int randX = rand() % 100;
        if (randNum == 0) {
            ScreenObject * alice = new AlienAlice(randX, currY, true);
            v.push_back(alice);
        } else if (randNum == 1) {
            ScreenObject * bob = new AlienBob(randX, currY, true);
            v.push_back(bob);
        } else if (randNum == 2) {
            ScreenObject * jack = new AlienJack(randX, currY, true);
            v.push_back(jack);
        } else {
            ScreenObject * jill = new AlienJill(randX, currY, true);
            v.push_back(jill);
        }
        currY += 10;
    }
    
    for (vector<ScreenObject *>::iterator it = v.begin(); it < v.end(); it++) {
        (*it)->draw(uLCD);
    }
    
    ship->draw(uLCD);
        
    playMusic(mySpeaker);
    t.start();
    
    while(true) {
        if (!acc.isXYZReady()) {
            wait(0.01);
        } else {
            acc.readXYZCounts(&x,&y,&z);
            ship->setSpeed(y/10 + 5);
            ship->update(uLCD);
            for (vector<ScreenObject *>::iterator it = v.begin(); it < v.end(); it++) {
                (*it)->update(uLCD);
                if ((*it) != bullet && (*it) != ship) {
                    int bulletX = bullet->getXPos();
                    int bulletY = bullet->getYPos();
                    int objectX = (*it)->getXPos();
                    int objectY = (*it)->getYPos();
                    if ((*it)->getAlive() && bullet->getAlive() && bulletX >= objectX && bulletX <= objectX + 11 && bulletY >= objectY && bulletY <= objectY + 8) {
                        mySpeaker.PlayNote(50.0,0.3,0.1);
                        enemiesAlive--;
                        bullet->setAlive(false);
                        (*it)->setAlive(false);
                        (*it)->update(uLCD);
                        bulletCount--;
                    }
                }
                if (bulletCount != 0 && bullet->getAlive() == false) {
                    bulletCount--;
                }
            }
        }
        if (enemiesAlive == 0) {
            t.stop();
            break;
        }
    }
    uLCD.cls();
    int timeElapsed = t.read_ms();
    uLCD.printf("\nCongratulations, lemur!\n"); 
    uLCD.printf("Time taken in ms: \n");
    uLCD.printf("%d\n", timeElapsed);
    
}