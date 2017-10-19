/* 
 * File:   PicPicEsclavo.c
 * Author: Cus
 *
 * Created on 19 de octubre de 2017, 0:10
 */

#include <stdio.h>
#include <stdlib.h>
#include "confi.h"
#include "flex_lcd.h"
#include <pic18f4550.h>
/*
 * 
 */
void ConfiSerial9600(){
//configurar a 9600
    TRISC7 = 1;
    TRISC6 = 1;
    BAUDCON=0b01011000; //configuracion serial
    TXSTA= 0b00100110; //configuracion serial
    //configuracion de la velocidad en baudios
    long SPBRGC =207; // valor para velocidad 207
    long AUX =SPBRGC;
    SPBRGC= SPBRGC >>8;
    SPBRGH=SPBRGC;
    SPBRGC= AUX & 0b00000000011111111;
    SPBRG=SPBRGC;
    RCSTAbits.SPEN=1; //encendido del puerto serial    
}
void ONRX(){
    RCSTA=0b10010000;
}
void OFFRX(){
    RCSTA=0b10000000;
}
void main(void) {
    OSCCON= 0b01110010; //reloj interno 8MH
    ADCON1= 0x0f;//All Digital
    TRISB=255;
    char buffer[20]; //variable de ayuda para usar la LCD
    Lcd_Init();
    Lcd_Out(1,1,"Todo OK");
    
    
    while(1){
    ConfiSerial9600();
    ONRX();
    // esperar a recibir Comando de inicio
    int espera=1;
    while (espera!=0){
    if(RCIF){
        if(RCREG=='$'){
        Lcd_Out(1,14,"$");
        //Enviar respuesta valor puerto B
        TXREG= PORTB; 
        TXIF=0;
        while(!TRMT){}
        __delay_ms (200);
        Lcd_Out(1,14," ");
        RCREG=0;
        }
    sprintf(buffer,"%03d",RCREG);
    Lcd_Out2(2,14,buffer);
    RCIF=0;
    }
    espera++;
    }
    OFFRX();
    sprintf(buffer,"Valor %03d ",PORTB);
    Lcd_Out2(2,1,buffer);
    
    }
}

