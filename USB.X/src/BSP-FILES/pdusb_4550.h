/* 
 * File:   pdfusb_4550.h
 * Author: vsk hs-ulm
 *
 * Created on 9. Mai 2014, 10:39
 */

#ifndef PDFUSB_4550_H
#define	PDFUSB_4550_H

//#define OLD_USB_DEMO_BOARD    //for use with the 1. USB DEMO BOARD DM163010

// ------------------------------------------------------ fixed_address_momory.h
#define FIXED_ADDRESS_MEMORY

#define HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS  0x500
#define HID_CUSTOM_IN_DATA_BUFFER_ADDRESS   0x540

#if defined(__XC8)
  #define IN_DATA_BUFFER_ADDRESS_TAG      @0x500    // for CDC device (XC8)
  #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x540
  #define CONTROL_BUFFER_ADDRESS_TAG      @0x580
#elif defined(COMPILER_MPLAB_C18)
  #define IN_DATA_BUFFER_ADDRESS_TAG      =0x500   // for CDC device (C18)
  #define OUT_DATA_BUFFER_ADDRESS_TAG     =0x540
  #define CONTROL_BUFFER_ADDRESS_TAG      =0x580
#endif

// ------------------------------------------current adc/buttons/leds. h/c files
//                                                      legacy HardwareProfile.h


//-------------------------------------------------------------------------- LED
#ifdef OLD_USB_DEMO_BOARD
    #define mInitAllLEDs()      LATB &= 0x00; TRISB = 0x00;
    #define mLED_1              LATBbits.LATB0
    #define mLED_2              LATBbits.LATB1
    #define mLED_3              LATBbits.LATB2
    #define mLED_4              LATBbits.LATB3
#else
    #define mInitAllLEDs()      LATD &= 0xF0; TRISD &= 0xF0;
    #define mLED_1              LATDbits.LATD0
    #define mLED_2              LATDbits.LATD1
    #define mLED_3              LATDbits.LATD2
    #define mLED_4              LATDbits.LATD3
#endif

#define mGetLED_1()         mLED_1
#define mGetLED_2()         mLED_2
#define mGetLED_3()         mLED_3
#define mGetLED_4()         mLED_4

#define mLED_1_On()         mLED_1 = 1;
#define mLED_2_On()         mLED_2 = 1;
#define mLED_3_On()         mLED_3 = 1;
#define mLED_4_On()         mLED_4 = 1;

#define mLED_1_Off()        mLED_1 = 0;
#define mLED_2_Off()        mLED_2 = 0;
#define mLED_3_Off()        mLED_3 = 0;
#define mLED_4_Off()        mLED_4 = 0;

#define mLED_1_Toggle()     mLED_1 = !mLED_1;
#define mLED_2_Toggle()     mLED_2 = !mLED_2;
#define mLED_3_Toggle()     mLED_3 = !mLED_3;
#define mLED_4_Toggle()     mLED_4 = !mLED_4;

//----------------------------------------------------------------------- SWITCH
#ifdef OLD_USB_DEMO_BOARD
    #define mInitSwitch()       TRISAbits.TRISA4=1;
    #define mGetSwitch()        !PORTAbits.RA4
#else
    #define mInitSwitch()       TRISBbits.TRISB4=1;TRISBbits.TRISB5=1;
    #define mGetSwitch()        !PORTBbits.RB4
#endif

//------------------------------------------------------------------------- POTI
#define mInitPoti()         TRISAbits.TRISA0 = 1;
#define mGetPoti()          PORTAbits.RA0

void initADC(void);
void initSpecialEventTrigger(void);
#define initCLKPLL()    // not used for 4550

#endif	/* PDFUSB_4550_H */
