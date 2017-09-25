/*
 * File:   LCD.c
 * Author: Cus
 *
 * Created on 24 de septiembre de 2017, 2:00
 */


#include <xc.h>
#include <p18f4550.h>
#include "config.h"
#include "flex_lcd.h"
#define _XTAL_FREQ 8000000
#include <stdio.h>
short getCad(char canal){
ADCON1=0b00001100;
    switch(canal){
        case 0:
            ADCON0= 0b00000010;
            break;
        case 1:
            ADCON0= 0b00000110;
            break;
        case 2:
            ADCON0= 0b00001010;    
            break;
    }
    ADCON2= 0b00101001;
    ADON=1;
    GO_DONE=1;
    while(GO_DONE){
        
    }
    return ADRESH;
}
void main(void) {
OSCCON= 0b01110010;        //configuración del Oscilador
  //*****************************************************
TRISA=0xff;
TRISD=0;

while(1){
    PORTD= getCad(0);
       }
} //fin
  
