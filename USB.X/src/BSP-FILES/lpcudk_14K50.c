/*********************************************************************
 *
 *             USB Firmware LowPinCountUSB DK with 14K50 specific
 *
 *********************************************************************
 * FileName:        lpcudk_14K50_hid.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18F14K50
 * Compiler:        C18 3.40+ / XC8
 * Company:         HS-Ulm
 *
 * Author       Company     Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * VSK          HS-Ulm      29.09.10
 *                          02.10.13  
 *
 *		TODO
 *
 *		-	...
 *
 ******************************************************************************/

#include "system.h"

/** CONFIGURATION **************************************************/
        #pragma config CPUDIV = NOCLKDIV
        #pragma config USBDIV = OFF
        #pragma config FOSC   = HS
        #pragma config PLLEN  = ON
        #pragma config FCMEN  = OFF
        #pragma config IESO   = OFF
        #pragma config PWRTEN = OFF
        #pragma config BOREN  = OFF
        #pragma config BORV   = 30
        #pragma config WDTEN  = OFF
        #pragma config WDTPS  = 32768
  #if defined(__DEBUG)
        #pragma config MCLRE  = ON
  #else 
        #pragma config MCLRE  = OFF
  #endif
        #pragma config HFOFST = OFF
        #pragma config STVREN = ON
        #pragma config LVP    = OFF
        #pragma config XINST  = OFF
        #pragma config BBSIZ  = OFF
        #pragma config CP0    = OFF
        #pragma config CP1    = OFF
        #pragma config CPB    = OFF
        #pragma config WRT0   = OFF
        #pragma config WRT1   = OFF
        #pragma config WRTB   = OFF
        #pragma config WRTC   = OFF
        #pragma config EBTR0  = OFF
        #pragma config EBTR1  = OFF
        #pragma config EBTRB  = OFF       


/** VARIABLES ******************************************************/


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
            ADC_CH10 & ADC_INT_OFF,
            ADC_REF_VDD_VSS & ADC_REF_VDD_VDD,
	    0b0000010000000000);
}

/******************************************************************************
 * Function:        void initSpecialEventTrigger(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 *
 * Overview:    The special event trigger is used for automatic ADC
 *
 * Note:        NYI ;-)
 *
 *****************************************************************************/
void initSpecialEventTrigger(void)
{
    OpenTimer1(TIMER_INT_OFF & T1_16BIT_RW & T1_SOURCE_INT &
            T1_PS_1_8 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
    T1CONbits.TMR1ON = 0;
//    mCCPTIMER_STOP()
    T3CONbits.T3CCP1 = 0;       // Timer1 is the clock source for compare ECCP1
    CCPR1 = 60000;              // 12M (clk) / 8 (TMR1 Prescaler)    -> 25Hz
    CCP1CONbits.CCP1M = 0b1011; // Compare Mode with Special Event Trigger
}

/** EOF lpcudk_14k50_hid.c *************************************************/
