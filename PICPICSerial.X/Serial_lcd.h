#ifndef __Serial_lcd_H
#define __Serial_lcd_H
#define _XTAL_FREQ 8000000
//******************************************
//  Libreria para control de LCD Serial    *
//  Vladimir Cusatti                       *
//******************************************


#define LCD_RC7     RC7      // Puerto RX C7
#define TRISRC7     TRISC7

#define LCD_RC6     RC6       // Puerto TX C6
#define TRISRC6     TRISC6

#define SPBRGconfi     832       // Valor para configurar el baudrate segun datasheet
//832 para 2400 y 207 para 9600 a 8MHZ pag 246 del datasheet


//comandos disponibles
#define      LCD_FIRST_ROW           128
#define      LCD_SECOND_ROW          192
#define      LCD_THIRD_ROW           148
#define      LCD_FOURTH_ROW          212
#define      LCD_CLEAR               1
#define      LCD_RETURN_HOME         2
#define      LCD_CURSOR_OFF          12
#define      LCD_UNDERLINE_ON        14
#define      LCD_BLINK_CURSOR_ON     15
#define      LCD_MOVE_CURSOR_LEFT    16
#define      LCD_MOVE_CURSOR_RIGHT   20
#define      LCD_TURN_OFF            0
#define      LCD_TURN_ON             8
#define      LCD_SHIFT_LEFT          24
#define      LCD_SHIFT_RIGHT         28


void Lcd_Init(void);
void Lcd_Out(unsigned char y, unsigned char x, const char *buffer);
void Lcd_Out2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr_CP(char data);
void Lcd_Cmd(unsigned char data);

void Lcd_Init(void){
unsigned char data;
TRISRC7 = 1;
TRISRC6 = 1;
BAUDCON=0b01011000; //configuracion serial
TXSTA= 0b00100110; //configuracion serial
//configuracion de la velocidad en baudios
long SPBRGC =SPBRGconfi;
SPBRGC= SPBRGC >>8;
SPBRGH=SPBRGC;
SPBRGC= SPBRGconfi & 0b00000000011111111;
SPBRG=SPBRGC;
RCSTAbits.SPEN=1;
//fin de configuracion

__delay_us(5500);
__delay_us(5500);
__delay_us(5500);
__delay_us(5500);
__delay_us(5500);
__delay_us(5500);

data = 16; Lcd_Cmd(data);
data = 1;  Lcd_Cmd(data);
data = 15; Lcd_Cmd(data);
}


void Lcd_Out(unsigned char y, unsigned char x, const char *buffer)
{
unsigned char data;
switch (y)
{   
    case 1: data = 128 + x; break;
    case 2: data = 192 + x; break;
    case 3: data = 148 + x; break;
    case 4: data = 212 + x; break;
    default: break;
}
Lcd_Cmd(data);
while(*buffer)              // Write data to LCD up to null
{                
    Lcd_Chr_CP(*buffer);
    buffer++;               // Increment buffer
}
return;
}


void Lcd_Out2(unsigned char y, unsigned char x, char *buffer)
{
unsigned char data;
switch (y)
{
    case 1: data = 128 + x; break;
    case 2: data = 192 + x; break;
    case 3: data = 148 + x; break;
    case 4: data = 212 + x; break;
    default: break;
}
Lcd_Cmd(data);
while(*buffer)              // Write data to LCD up to null
{                
    Lcd_Chr_CP(*buffer);
    buffer++;               // Increment buffer
}
return;
}


void Lcd_Chr_CP(char data){
    TXREG=data;
    TXIF=0;
    while(!TXIF){}
}


void Lcd_Cmd(unsigned char data){
    Lcd_Chr_CP(254);
    Lcd_Chr_CP(data);
    while(!TRMT){}
}
#endif
























