
#include "mbed.h"

DigitalIn mybutton(D4);
DigitalOut myrele(D6);
Timer timer, start;
bool flag = false;
long long btnTimer = 0;
int main()
{
    mybutton.mode(PullUp);
    timer.start();
    while(1) {
        if (mybutton && !flag && timer.read_ms() - btnTimer > 100) {
            flag = true;
            btnTimer = timer.read_ms();
            myrele = 1;
            printf("Button state is: press\n");
        }
        if (mybutton && flag && timer.read_ms() - btnTimer > 500) {
            flag = true;
            btnTimer = timer.read_ms();
            myrele = 1;
            printf("Button state is: hoooold\n");
        }
        if (!mybutton && flag && timer.read_ms() - btnTimer > 100) {
            flag = false;
            myrele = 0;
            btnTimer = timer.read_ms();
            printf("Button state is: relise\n");
        } 
    }
}