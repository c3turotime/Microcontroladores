/* 
 * File:   TecladoYLCD.c
 * Author: Cus
 *
 * Created on 4 de octubre de 2017, 22:41
 */

#include <stdio.h>
#include <stdlib.h>
#include "confi.h"
#include "flex_lcd.h"
#include <pic18f4550.h>

/*
 * 
 */
char inKey(void){ // /10 *11 -12 +13 =14 on15
    TRISB = 0xF0;
    char valor=16;
    PORTB = 0b11111110;
    if(RB4==0){valor=13;}
    if(RB5==0){valor=12;}
    if(RB6==0){valor=11;}
    if(RB7==0){valor=10;}
    PORTB = 0b11111101;
    if(RB4==0){valor=14;}
    if(RB5==0){valor=3;}
    if(RB6==0){valor=6;}
    if(RB7==0){valor=9;}
    PORTB = 0b11111011;
    if(RB4==0){valor=0;}
    if(RB5==0){valor=2;}
    if(RB6==0){valor=5;}
    if(RB7==0){valor=8;}
    PORTB = 0b11110111;
    if(RB4==0){valor=15;}
    if(RB5==0){valor=1;}
    if(RB6==0){valor=4;}
    if(RB7==0){valor=7;}
    return valor;
}
void main(void) {
    OSCCON= 0b01110010;
    ADCON1= 0x0f;
    char buffer[20];
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    while(1){
    sprintf(buffer, "Valor: %03d",inKey());    
    Lcd_Out2(1,1,buffer);
    
    }
}

