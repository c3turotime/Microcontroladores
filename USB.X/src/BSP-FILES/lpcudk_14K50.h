/*
 * File:   lpcudk_14k50.h
 * Author: vsk
 *
 * Created on 7. Mai 2014, 09:14
 */
#ifndef _LPCUDK_14k50_H
#define _LPCUDK_14K50_H

// ------------------------------------------------------ fixed_address_momory.h
#define FIXED_ADDRESS_MEMORY

#define HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS  0x260
#define HID_CUSTOM_IN_DATA_BUFFER_ADDRESS   0x2A0

#if defined(__XC8)
  #define IN_DATA_BUFFER_ADDRESS_TAG      @0x240    // for CDC device (XC8)
  #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x280
  #define CONTROL_BUFFER_ADDRESS_TAG      @0x2C0
#elif defined(COMPILER_MPLAB_C18)
  #define IN_DATA_BUFFER_ADDRESS_TAG      =0x240   // for CDC device (C18)
  #define OUT_DATA_BUFFER_ADDRESS_TAG     =0x280
  #define CONTROL_BUFFER_ADDRESS_TAG      =0x2C0
#endif

// --------------------------------------------------------------------- power.h
//                                                      legacy HardwareProfile.h
typedef enum
{
    POWER_SOURCE_USB,
    POWER_SOURCE_MAINS
} POWER_SOURCE;

/*********************************************************************
* Function: POWER_SOURCE POWER_SourceGet(void)
*
* Overview: Gets the current source of power for the board
* PreCondition: None
* Input: None
* Output: POWER_SOURCE - the current source of power for the board
*
********************************************************************/
//POWER_SOURCE POWER_SourceGet(void);
//#define POWER_SourceGet() POWER_SOURCE_MAINS
#define POWER_SourceGet() POWER_SOURCE_USB

// ------------------------------------------current adc/buttons/leds. h/c files
//                                                      legacy HardwareProfile.h


//-------------------------------------------------------------------------- LED
#define mInitAllLEDs()      LATC &= 0xF0; TRISC &= 0xF0;

#define mLED_1              LATCbits.LATC0
#define mLED_2              LATCbits.LATC1
#define mLED_3              LATCbits.LATC2
#define mLED_4              LATCbits.LATC3

#define mGetLED_1()         mLED_1
#define mGetLED_2()         mLED_2
#define mGetLED_3()         mLED_3
#define mGetLED_4()         mLED_4

#define mLED_1_On()         mLED_1 = 1
#define mLED_2_On()         mLED_2 = 1
#define mLED_3_On()         mLED_3 = 1
#define mLED_4_On()         mLED_4 = 1

#define mLED_1_Off()        mLED_1 = 0
#define mLED_2_Off()        mLED_2 = 0
#define mLED_3_Off()        mLED_3 = 0
#define mLED_4_Off()        mLED_4 = 0

#define mLED_1_Toggle()     mLED_1 = !mLED_1
#define mLED_2_Toggle()     mLED_2 = !mLED_2
#define mLED_3_Toggle()     mLED_3 = !mLED_3
#define mLED_4_Toggle()     mLED_4 = !mLED_4

//----------------------------------------------------------------------- SWITCH
#define mInitSwitch()       //TRISAbits.TRISA3=1 *14K50* input only !!!
#define mGetSwitch()        !PORTAbits.RA3

//------------------------------------------------------------------------- POTI
#define mInitPoti()         ANSELHbits.ANS10 = 1; TRISBbits.TRISB4 = 1;
#define mGetPoti()          PORTBbits.RB4


void initADC(void);
void initSpecialEventTrigger(void);
#define initCLKPLL()    // not used for 14K50

#endif //_LPCUDK_14k50_H
