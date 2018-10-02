/*
 * File:   controlDCDC35a25.c
 * Author: cus0001
 *
 * Created on 1 de octubre de 2018, 19:15
 */

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic12f675.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>
short getCad(){
    TRISIObits.TRISIO0=1;
    ANSEL=0b00000001; //b7=0 b6-4 reloj= fosc/2 ; b3-0 pin 0:digital o 1:analog
    ADCON0=0b00000011; // left VDD 0 0 CH0 (iniciar conversion) modulo_on
    while(GO_DONE){
        
    }
    return ADRESH;
}
void main(void) {
    TRISIObits.TRISIO5=0;
    GPIObits.GP5=1;
    short CAD;
    while(1){
        CAD=getCad();
        if(CAD<190){
            GPIObits.GP5=1;
        }
        if(CAD>200){
            GPIObits.GP5=0;
        }
    }
    return;
}
