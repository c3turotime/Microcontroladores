#include "confi.h"
#include <p18f4550.h>

#define _XTAL_FREQ 8000000

void main(void){
    OSCCON= 0b01110010;
    T0CON= 0b10000100;
    //TMR0H=0;
    //TMR0L=0;
    TMR0=0;
    TRISB7=0;
    while(1){
        if (INTCONbits.T0IF){
            //asm(tgb RB7);
            RB7=!RB7;
            INTCONbits.T0IF=0;
        }
    }
    
}



