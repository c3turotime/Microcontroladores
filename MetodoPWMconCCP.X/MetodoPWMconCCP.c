/* 
 * File:   MetodoPWMporSoft.c
 * Author: Cus
 *
 * Created on 17 de enero de 2018, 21:34
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements
//********************config pragma***************************
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
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
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
//********************config pragma***************************
//********************Librerias y definiciones generales***********************
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>
#define _XTAL_FREQ 8000000
//********************Librerias y definiciones generales***********************
//*****************definiciones y variables globales del metodo****************

/**
 * Lanzador del metodo PWM se encarga de inicialicar el metodo y hacer calculos
 * y configuraciones basicas
 * @duty ciclo util de 0 a 100%
 * @fpwm valor de la frecuencia de trabajo de 500 Hz a 60000 Hz.
 */
void PWMccp1out(unsigned int duty, unsigned int fpwm){
    /*PWM Period = [(PR2) + 1] ? 4 ? TOSC ?(TMR2 Prescale Value)
     * PWM Period /(4 * TOSC * TMR2presc) - 1 = PR2
     * FOSC / (4 * FPWM * TMR2Presc) - 1 = PR2
    */
    TRISCbits.RC2=0;
    unsigned int prescalador=1;
    unsigned long PR2cal=_XTAL_FREQ;
    PR2cal=PR2cal/fpwm;
    PR2cal=PR2cal/4;  
    T2CON=0b00000000;
    while(PR2cal>256){
       prescalador=prescalador*4;
       T2CON++;
       PR2cal=PR2cal/4;
    }
    PR2cal--;
    PR2=PR2cal;
    /*PWM Duty Cycle = (CCPRXL:CCPXCON<5:4>) ? TOSC ? (TMR2 Prescale Value)
     * PWM Duty Cycle = (CCPR1L:CCP1CON<5:4>) ? TOSC ? (TMR2 Prescale Value)
     * (CCPR1L:CCP1CON<5:4>) = PWM Duty Cycle / (TOSC ? (TMR2 Prescale Value))
     * (CCPR1L:CCP1CON<5:4>) = xx%([(PR2) + 1] ? 4 ? TOSC ?(TMR2 Prescale Value)) / (TOSC ? (TMR2 Prescale Value))
     * (CCPR1L:CCP1CON<5:4>) = xx%[(PR2) + 1] ? 4 
     */
    unsigned long AuxCCPR1L=PR2cal;
    AuxCCPR1L++;
    AuxCCPR1L=AuxCCPR1L*duty;
    AuxCCPR1L=AuxCCPR1L*4;
    AuxCCPR1L=AuxCCPR1L/100;
    unsigned int AuxCCP1CON= AuxCCPR1L;
    AuxCCP1CON= AuxCCP1CON & 0b00000011 ;
    AuxCCP1CON= AuxCCP1CON*16;//<< 4
    CCP1CON= 0b00001100;
    CCP1CON= CCP1CON|AuxCCP1CON;
    AuxCCPR1L=AuxCCPR1L/4; //>>2
    CCPR1L=AuxCCPR1L;
    T2CONbits.TMR2ON=1;
    TMR2=0;       
}

//************************Codigo principal************************
void main() {
OSCCON= 0b01110011;        //configuración del Oscilador
ADCON1=0xff; //todo los puertos definidos como digitales

PWMccp1out(50,5000); //invocacion de la configuracion y el lanzador del metodo
TRISD=0;
while(1){PORTD++;}/*se puede hacer cualquier cosa menos usar el timer 0 
                   * dentro del while */
}

