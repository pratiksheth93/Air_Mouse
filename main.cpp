#include "mbed.h"
#include "USBMouse.h"
#include "MMA8451Q.h"
#include "TSISensor.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)

MMA8451Q acc(PTE25,PTE24, MMA8451_I2C_ADDRESS);
TSISensor tsi;
USBMouse mouse;

int main()
{
    int16_t x = 0;
    int16_t y = 0;
    int s=10;
    
    while(1)
    {
        x= -s*(acc.getAccY());
        y= s*acc.getAccX();
        
        mouse.move(x,y);
        
        //left click
        if (tsi.readPercentage() > 0.7)
        {
            mouse.press(MOUSE_LEFT);
        }
        else
        {
            mouse.release(MOUSE_LEFT);
        }
        //right click
        if (tsi.readPercentage() < 0.3 && tsi.readPercentage() > 0)
        {
         mouse.press(MOUSE_RIGHT);
        }
        else
        {
            mouse.release(MOUSE_RIGHT);
        }   
    }
}