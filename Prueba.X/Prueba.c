#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#define _XTAL_FREQ  8000000

void Timer0 (int tiempo){
    T0CON= 0b10000000;
    TMR0=65536 - tiempo;     
}
void interrupt one (void){
    if (INTCONbits.T0IF){
        Timer0(PORTB*512);               
        T0IF=0;
    }
    if (INTCONbits.INT0F){
        INT0F=0;
    }
    PORTC=PORTC+1;
} 
void main(void) {
    OSCCON = 0b01110010;     
    ADCON1 = 0b00001111;
    INTCON = 0xF0; 
    TRISB = 0xFF;
    TRISC = 248;
    TRISD = 0;
    PORTC = 0;    
    Timer0 (10000);
    while (1)
    {
        PORTD= PORTB;      
    }
}

