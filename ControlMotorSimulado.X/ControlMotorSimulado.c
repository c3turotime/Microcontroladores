/* 
 * File:   ControlMotorSimulado.c
 * Author: Cus
 *
 * Created on 10 de enero de 2018, 21:59
 */

// PIC18F2550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_HS // Oscillator Selection bits (Internal oscillator, HS oscillator used by USB (INTHS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>
#include <pic18f2550.h>
#include <xc.h>

#define _XTAL_FREQ 8000000 //8Mhz
/*
 * 
 */
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
void main(){
    //configuracion de Frecuencia
    OSCCON= 0b01110010;
    //delcaracion de entrada y salida
    TRISA=0xff; //todas entradas
    TRISBbits.RB7=1;//pin B7 como entrada
    //ADCON1=0b00001101;//A0 y A1 como analogicos no es necesario porque el metodo del CAD ya lo configura
    //configurar puertos digitales y analogicos
    //declaracion de variables
    long valor; //donde se guarda el PWM de entrada
    long vejez; //donde se guarda la vejez
    // en esta casion haremo un software que genere un PWM a 10khz y 40% de ciclo util
    //revisemos el dataSheet
    PR2=199; //PWM Period = [(PR2) + 1] ? 4 ? TOSC ?(TMR2 Prescale Value)
    //PWM Period = [199+1]*4*(1/8000000)*1 = 0.0001 s => FPWM= 10khz
    // PWM frequency is defined as 1/[PWM period].
    //CCPR1L=0b1010000; //mas significativo, tecnicamente control a 8 bit sise usa solo
    /*PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) ?TOSC ? (TMR2 Prescale Value)
     PWM Duty Cycle = (CCPR1L:CCPXCON<5:4>) ?TOSC ? (TMR2 Prescale Value)
     PWM Duty Cycle = (01010000=80 ) ?(1/8000000) ? (1)
     80/200=0,4
     */
    CCP1CONbits.DC1B1=0;// se colocan en 0 para no tomarlos en cuenta
    CCP1CONbits.DC1B0=0;//
    TRISCbits.RC2=0;
    T2CON= 0b00000100;/*bit 7 Unimplemented: Read as ?0?
                        bit 6-3 T2OUTPS3:T2OUTPS0: Timer2 Output Postscale Select bits
                        0000 = 1:1 Postscale
                        0001 = 1:2 Postscale
                        ?
                        ?
                        ?  
                        1111 = 1:16 Postscale
                        bit 2 TMR2ON: Timer2 On bit
                        1 = Timer2 is on
                        0 = Timer2 is off
                        bit 1-0 T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
                        00 = Prescaler is 1
                        01 = Prescaler is 4
                        1x = Prescaler is 16*/
    
    
    
    while(1){
        if(PORTBbits.RB7){
            //si es 1 PWM on
            CCP1CONbits.CCP1M3=1; // Se asume que todos los otros bits del CCP1 estan en 0
            CCP1CONbits.CCP1M2=1; // Estos dos bit activan el PWM
            valor=getCad(0);//devuelve un valor entre 0-255
            //parametrizar valor 256=>200 y 0=0
            valor=valor*200;
            valor=valor/256;
            //aplicación de la vejez
            vejez= getCad(1);
            valor=valor*vejez;
            valor=valor/256;
            CCPR1L= valor; //valor del duty.            
        }else{
            //si es 0 PWM off, no voy a simular el apagado suave.
            CCP1CONbits.CCP1M3=0; // Se asume que todos los otros bits del CCP1 estan en 0
            CCP1CONbits.CCP1M2=0; // Estos dos bit activan el PWM
            valor=1;
            CCPR1L=valor;
        }
        __delay_ms(500);//no me gustan estos delay pero hay que usarlo
        
    }
    
}
   