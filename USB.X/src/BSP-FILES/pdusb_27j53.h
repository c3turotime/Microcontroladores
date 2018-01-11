/* 
 * File:   picdemusb_27J53.h
 * Author: vsk hs-ulm
 *
 * Created on 22. July 2014, 10:59
 */

#ifndef PDUSB_27J53_H
#define	PDUSB_27J53_H


// ------------------------------------------------------ fixed_address_momory.h
// no fixed addresses needed for this PIC

// ------------------------------------------current adc/buttons/leds. h/c files
//                                                      legacy HardwareProfile.h


//-------------------------------------------------------------------------- LED
#define mInitAllLEDs()      LATB &= 0x00; TRISB = 0x00;
#define mLED_1              LATBbits.LATB0
#define mLED_2              LATBbits.LATB1
#define mLED_3              LATBbits.LATB2
#define mLED_4              LATBbits.LATB3


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
#define mInitSwitch()       //TRISAbits.TRISA4=1; (no RA4 because VddCore)
#define mGetSwitch()        0//!PORTAbits.RA4

//------------------------------------------------------------------------- POTI
#define mInitPoti()         TRISAbits.TRISA0 = 1;
#define mGetPoti()          PORTAbits.RA0

void initADC(void);
void initSpecialEventTrigger(void);
void initCLKPLL(void);

#endif	/* PDUSB_27J53_H */
