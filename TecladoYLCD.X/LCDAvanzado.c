/* 
 * File:   TecladoYLCD.c
 * Author: Cus
 *
 * Created on 4 de octubre de 2017, 22:41
 */

#include <stdio.h>
#include <stdlib.h>
#include "confi.h"
#include "Serial_lcd.h"
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
    Lcd_Cmd(0b01000001);//pagina 27  HD44780    
    Lcd_Chr_CP(0b00001100);
    Lcd_Chr_CP(0b00010010);
    Lcd_Chr_CP(0b00010001);
    Lcd_Chr_CP(0b00001000);
    Lcd_Chr_CP(0b00000100);
    Lcd_Chr_CP(0b00000010);
    Lcd_Chr_CP(0b00000001);
    Lcd_Chr_CP(0b00000000);
    Lcd_Chr_CP(0b00000110);
    Lcd_Chr_CP(0b00001001);
    Lcd_Chr_CP(0b00010001);
    Lcd_Chr_CP(0b00000010);
    Lcd_Chr_CP(0b00000100);
    Lcd_Chr_CP(0b00001000);
    Lcd_Chr_CP(0b00010000);
    Lcd_Chr_CP(0b00000000);
    Lcd_Cmd(LCD_CLEAR);
    while(1){
    sprintf(buffer,"CGram ");     
    Lcd_Out2(1,1,buffer);
    Lcd_Chr_CP(0b00100001);//!
    Lcd_Chr_CP(0);
    Lcd_Chr_CP(1);
    Lcd_Chr_CP(2);
    __delay_ms(1000); 
    }
}


