/*********************************************************************
 *
 *       USB  Firmware PICDEM (FS) USB with 25K50 specific
 *
 *********************************************************************
 * FileName:        pdusb_25k50.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18F25K50
 * Compiler:        C18 3.40+ / xc8
 * Company:         HS-Ulm
 *
 * Author       Company     Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * VSK          HS-Ulm      12.01.15
 *                           
 *
 *		TODO
 *
 *		-	...
 *
 ******************************************************************************/

#include "system.h"


#define USE_INTERNAL_OSC

/** CONFIGURATION Bits **********************************************/
#if defined (USE_INTERNAL_OSC)	    // Define this in system.h if using the HFINTOSC for USB operation
    #pragma config PLLSEL   = PLL3X     // PLL Selection (3x clock multiplier)
    #pragma config CFGPLLEN = OFF       // PLL Enable Configuration bit (PLL Disabled (firmware controlled))
    #pragma config CPUDIV   = NOCLKDIV  // CPU System Clock Postscaler (CPU uses system clock (no divide))
    #pragma config LS48MHZ  = SYS48X8   // Low Speed USB mode with 48 MHz system clock (System clock at 48 MHz, USB clock divider is set to 8)
    #pragma config FOSC     = INTOSCIO  // Oscillator Selection (Internal oscillator)
    #pragma config PCLKEN   = OFF       // Primary Oscillator Shutdown (Primary oscillator shutdown firmware controlled)
    #pragma config FCMEN    = OFF       // Fail-Safe Clock Monitor (Fail-Safe Clock Monitor disabled)
    #pragma config IESO     = OFF       // Internal/External Oscillator Switchover (Oscillator Switchover mode disabled)
    #pragma config nPWRTEN  = OFF       // Power-up Timer Enable (Power up timer disabled)
    #pragma config BOREN    = SBORDIS   // Brown-out Reset Enable (BOR enabled in hardware (SBOREN is ignored))
    #pragma config BORV     = 190       // Brown-out Reset Voltage (BOR set to 1.9V nominal)
    #pragma config nLPBOR   = ON        // Low-Power Brown-out Reset (Low-Power Brown-out Reset enabled)
    #pragma config WDTEN    = SWON      // Watchdog Timer Enable bits (WDT controlled by firmware (SWDTEN enabled))
    #pragma config WDTPS    = 32768     // Watchdog Timer Postscaler (1:32768)
    #pragma config CCP2MX   = RC1       // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
    #pragma config PBADEN   = OFF       // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
    #pragma config T3CMX    = RC0       // Timer3 Clock Input MUX bit (T3CKI function is on RC0)
    #pragma config SDOMX    = RC7       // SDO Output MUX bit (SDO function is on RC7)
    #pragma config MCLRE    = ON        // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)
    #pragma config STVREN   = ON        // Stack Full/Underflow Reset (Stack full/underflow will cause Reset)
    #pragma config LVP      = OFF       // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
    #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming Port Enable (ICPORT disabled)
    #pragma config XINST    = OFF       // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)
    #pragma config CP0      = OFF       // Block 0 Code Protect (Block 0 is not code-protected)
    #pragma config CP1      = OFF       // Block 1 Code Protect (Block 1 is not code-protected)
    #pragma config CP2      = OFF       // Block 2 Code Protect (Block 2 is not code-protected)
    #pragma config CP3      = OFF       // Block 3 Code Protect (Block 3 is not code-protected)
    #pragma config CPB      = OFF       // Boot Block Code Protect (Boot block is not code-protected)
    #pragma config CPD      = OFF       // Data EEPROM Code Protect (Data EEPROM is not code-protected)
    #pragma config WRT0     = OFF       // Block 0 Write Protect (Block 0 (0800-1FFFh) is not write-protected)
    #pragma config WRT1     = OFF       // Block 1 Write Protect (Block 1 (2000-3FFFh) is not write-protected)
    #pragma config WRT2     = OFF       // Block 2 Write Protect (Block 2 (04000-5FFFh) is not write-protected)
    #pragma config WRT3     = OFF       // Block 3 Write Protect (Block 3 (06000-7FFFh) is not write-protected)
    #pragma config WRTC     = OFF       // Configuration Registers Write Protect (Configuration registers (300000-3000FFh) are not write-protected)
    #pragma config WRTB     = OFF       // Boot Block Write Protect (Boot block (0000-7FFh) is not write-protected)
    #pragma config WRTD     = OFF       // Data EEPROM Write Protect (Data EEPROM is not write-protected)
    #pragma config EBTR0    = OFF       // Block 0 Table Read Protect (Block 0 is not protected from table reads executed in other blocks)
    #pragma config EBTR1    = OFF       // Block 1 Table Read Protect (Block 1 is not protected from table reads executed in other blocks)
    #pragma config EBTR2    = OFF       // Block 2 Table Read Protect (Block 2 is not protected from table reads executed in other blocks)
    #pragma config EBTR3    = OFF       // Block 3 Table Read Protect (Block 3 is not protected from table reads executed in other blocks)
    #pragma config EBTRB    = OFF       // Boot Block Table Read Protect (Boot block is not protected from table reads executed in other blocks)
#else
#warning "external clock source 12MHz required !!!"
    #pragma config PLLSEL   = PLL4X     // PLL Selection (4x clock multiplier)
    #pragma config CFGPLLEN = ON        // PLL Enabled
    #pragma config CPUDIV   = NOCLKDIV  // CPU System Clock Postscaler (CPU uses system clock (no divide))
    #pragma config LS48MHZ  = SYS48X8   // Low Speed USB mode with 48 MHz system clock (System clock at 48 MHz, USB clock divider is set to 8)
    #pragma config FOSC     = HSH       // Oscillator Selection (HS oscillator, high power 4MHz to 25MHz)
    #pragma config PCLKEN   = OFF       // Primary Oscillator Shutdown (Primary oscillator shutdown firmware controlled)
    #pragma config FCMEN    = OFF       // Fail-Safe Clock Monitor (Fail-Safe Clock Monitor disabled)
    #pragma config IESO     = OFF       // Internal/External Oscillator Switchover (Oscillator Switchover mode disabled)
    #pragma config nPWRTEN  = OFF       // Power-up Timer Enable (Power up timer disabled)
    #pragma config BOREN    = SBORDIS   // Brown-out Reset Enable (BOR enabled in hardware (SBOREN is ignored))
    #pragma config BORV     = 190       // Brown-out Reset Voltage (BOR set to 1.9V nominal)
    #pragma config nLPBOR   = ON        // Low-Power Brown-out Reset (Low-Power Brown-out Reset enabled)
    #pragma config WDTEN    = OFF      // Watchdog Timer Enable bits (WDT controlled by firmware (SWDTEN enabled))
    #pragma config WDTPS    = 32768     // Watchdog Timer Postscaler (1:32768)
    #pragma config CCP2MX   = RC1       // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
    #pragma config PBADEN   = OFF       // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
    #pragma config T3CMX    = RC0       // Timer3 Clock Input MUX bit (T3CKI function is on RC0)
    #pragma config SDOMX    = RC7       // SDO Output MUX bit (SDO function is on RC7)
    #pragma config MCLRE    = ON        // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)
    #pragma config STVREN   = ON        // Stack Full/Underflow Reset (Stack full/underflow will cause Reset)
    #pragma config LVP      = OFF       // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
    #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming Port Enable (ICPORT disabled)
    #pragma config XINST    = OFF       // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)
    #pragma config CP0      = OFF       // Block 0 Code Protect (Block 0 is not code-protected)
    #pragma config CP1      = OFF       // Block 1 Code Protect (Block 1 is not code-protected)
    #pragma config CP2      = OFF       // Block 2 Code Protect (Block 2 is not code-protected)
    #pragma config CP3      = OFF       // Block 3 Code Protect (Block 3 is not code-protected)
    #pragma config CPB      = OFF       // Boot Block Code Protect (Boot block is not code-protected)
    #pragma config CPD      = OFF       // Data EEPROM Code Protect (Data EEPROM is not code-protected)
    #pragma config WRT0     = OFF       // Block 0 Write Protect (Block 0 (0800-1FFFh) is not write-protected)
    #pragma config WRT1     = OFF       // Block 1 Write Protect (Block 1 (2000-3FFFh) is not write-protected)
    #pragma config WRT2     = OFF       // Block 2 Write Protect (Block 2 (04000-5FFFh) is not write-protected)
    #pragma config WRT3     = OFF       // Block 3 Write Protect (Block 3 (06000-7FFFh) is not write-protected)
    #pragma config WRTC     = OFF       // Configuration Registers Write Protect (Configuration registers (300000-3000FFh) are not write-protected)
    #pragma config WRTB     = OFF       // Boot Block Write Protect (Boot block (0000-7FFh) is not write-protected)
    #pragma config WRTD     = OFF       // Data EEPROM Write Protect (Data EEPROM is not write-protected)
    #pragma config EBTR0    = OFF       // Block 0 Table Read Protect (Block 0 is not protected from table reads executed in other blocks)
    #pragma config EBTR1    = OFF       // Block 1 Table Read Protect (Block 1 is not protected from table reads executed in other blocks)
    #pragma config EBTR2    = OFF       // Block 2 Table Read Protect (Block 2 is not protected from table reads executed in other blocks)
    #pragma config EBTR3    = OFF       // Block 3 Table Read Protect (Block 3 is not protected from table reads executed in other blocks)
    #pragma config EBTRB    = OFF       // Boot Block Table Read Protect (Boot block is not protected from table reads executed in other blocks)
#endif


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
            ADC_CH0 & ADC_INT_OFF,
            ADC_TRIG_CCP2 & ADC_REF_VDD_VDD & ADC_REF_VDD_VSS);
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
#if defined (USE_INTERNAL_OSC)
    //Configure oscillator settings for clock settings compatible with USB
    //operation.  Note: Proper settings depends on USB speed (full or low).
        #if(USB_SPEED_OPTION == USB_FULL_SPEED)
            OSCTUNE = 0x80; //3X PLL ratio mode selected
            OSCCON = 0x70;  //Switch to 16MHz HFINTOSC
            OSCCON2 = 0x10; //Enable PLL, SOSC, PRI OSC drivers turned off
            while(OSCCON2bits.PLLRDY != 1);   //Wait for PLL lock
            ACTCON = 0x90;  //Enable active clock tuning for  USB operation
        #endif
#endif
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

/** EOF pdusb_25k50.c *************************************************/
