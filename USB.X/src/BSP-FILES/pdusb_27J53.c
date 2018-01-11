/*********************************************************************
 *
 *       USB  Firmware PICDEM (FS) USB with 27J53 specific
 *
 *********************************************************************
 * FileName:        pdusb_27J53.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18F27J53
 * Board:           PICDEM USB (DM163010)
 * Compiler:        C18 3.40+ / xc8
 * Company:         HS-Ulm
 *
 * Author       Company     Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * VSK          HS-Ulm      22.07.14
 *                           
 *
 *		TODO
 *
 *		-	...
 *
 ******************************************************************************/

#include "system.h"

/** CONFIGURATION **************************************************/
// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 5       // PLL Prescaler Selection (Divide by 5 (20 MHz oscillator input))
#pragma config CFGPLLEN = ON    // PLL Enable Configuration Bit (PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset (Enabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = HSPLL      // Oscillator (HS+PLL, USB-HS+PLL)
#pragma config SOSCSEL = DIG    // T1OSC/SOSC Power Selection Bits (Digital (SCLKI) mode selected)
#pragma config CLKOEC = OFF     // EC Clock Out Enable Bit  (CLKO output disabled on the RA6 pin)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = INTOSCREF// RTCC Clock Select (RTCC uses INTRC)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Disabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = 8192   // Deep Sleep Watchdog Postscaler (1:8,192 (8.5 seconds))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config ADCSEL = BIT12   // ADC 10 or 12 Bit Select (12 - Bit ADC Enabled)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_1    // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 1)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region  (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<6:0>/WPEND region ignored)
#pragma config WPEND = PAGE_0   // Write/Erase Protect Region Select bit (valid when WPDIS = 0) (Pages 0 through WPFP<6:0> erase/write protected)
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock bit (System clock at 48 MHz USB CLKEN divide-by is set to 8)

         //WPFP[5:0], WPEND, and WPCFG bits ignored

/******************************************************************************
 * Function:        void initADC(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 *
 * Overview:
 *
 * Note:
 *
 *****************************************************************************/
void initADC(void)
{
    OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_2_TAD,
            ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,
            ADC_TRIG_CCP2,
            ADC_1ANA & ADC_VBG_OFF);
}

/******************************************************************************
 * Function:        void initCLKPLL(void)
 *
 * In this devices family of USB microcontrollers, the PLL will not power up and
 * be enabled by default, even if a PLL enabled oscillator configuration is
 * selected(such as HS+PLL). This allows the device to power up at a lower
 * initial operating frequency, which can be advantageous when powered from a
 * source which is not gauranteed to be adequate for 48MHz operation.
 * On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit
 * to power up the PLL.
 *****************************************************************************/
void initCLKPLL(void)
{
    unsigned int pll_startup_counter = 600;
    OSCTUNEbits.PLLEN = 1; //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
    while (pll_startup_counter--);
}

/******************************************************************************
 * Function:        void initSpecialEventTrigger(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 *
 * Overview:
 *
 * Note:
 *
 *****************************************************************************/
void initSpecialEventTrigger(void)
{
    
}

/** EOF picdemusb_27j.c *************************************************/
