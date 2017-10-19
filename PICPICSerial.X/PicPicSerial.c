#include <stdio.h>
#include <stdlib.h>
#include "confi.h"
#include "Serial_lcd.h"
#include <pic18f4550.h>
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
    char buffer[20]; //variable de ayuda para usar la LCD
    Lcd_Init(); // configura la velocidad serial a 2400 baudios
    Lcd_Out(1,1,"Probando");
    __delay_ms(2000);
    char datoR; //caracter recibido
    
    while(1){
    ConfiSerial9600();
    //Enviar comando de inicializacion
    char i;
    for(i=0;i<3;i++){
    TXREG= '$'; //Cochino dinero
    TXIF=0;
    while(!TXIF){}
    // esperar a recibir respuesta
    ONRX();
    int espera=1;
    while (espera!=0){
        if(RCIF){
            datoR=RCREG;
            sprintf(buffer,"Valor: %03d  ",datoR);
        RCIF=0;
        break;
        }
        espera++;
    }
    while(!TRMT){}
    OFFRX();
    }
    Lcd_Init();
    Lcd_Out2(2,1,buffer);
    }
}
