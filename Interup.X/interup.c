#include "confi.h"
#include <p18f4550.h>

#define _XTAL_FREQ 8000000
void interrupt miinterrupt (){
    //GIE=0;
    PORTC=TMR0L;
    PORTD=TMR0H;
    TMR0=0;
    INT0IF=0;
    RB6=0;
    __delay_ms(300);
}
void main(void){
    OSCCON= 0b01110010;
    ADCON1= 255;
    INTCON= 0b11010000;    
    TRISB=0x0F;
    TRISD=0;
    TRISC=0;
    while(1){
        if(RB6==0){
        RB6=1;
        T0CON= 0b10000111;
        TMR0=0;
        }
            
            
        RB7=1;
        __delay_ms(100);
        RB7=0;
        __delay_ms(100);
    }
    
}




