
#include "mbed.h"
#include "button.h"
#include "iostream"
Button mybutton(D4);
DigitalOut myrele(D6);
int main()
{
    while (1)
    {
        mybutton.status();
    }
    
}