/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#if defined(COMPILER_MPLAB_C18) //++VSK def(COMP_MPLAB_C18)
    #define __attribute__(a)
    #define const far rom

    #include <p18cxxx.h>
    #include <adc.h>
    #include <timers.h>

#elif defined(__XC8)
    #include <xc.h>

#else
    #warning "compiler ???"
#endif

//#include <stdbool.h>  --VSK wth is ist needed for ?
//#include <buttons.h>  --VSK (moved all this stuff to lpcudk_14K50_hid.h)
//#include <leds.h>
//#include <adc.h>      VSK what a bad name :-(
//#include <io_mapping.h>
//#include <fixed_address_memory.h>
//#include <power.h>
#if defined(__18F14K50)
    #include "../BSP-FILES/lpcudk_14K50.h"
#elif defined(__18F4550)
    #include "../BSP-FILES/pdusb_4550.h"
#elif defined(__18F27J53)
    #include "../BSP-FILES/pdusb_27J53.h"
#elif defined(__18F25K50)
    #include "../BSP-FILES/pdusb_25K50.h"
#else
    #warning "PIC is not supported in this project !!!"
#endif
#define MAIN_RETURN void

/*** System States **************************************************/
typedef enum
{
    SYSTEM_STATE_USB_START,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME
} SYSTEM_STATE;


/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize( SYSTEM_STATE state );


/*********************************************************************
* Function: void SYSTEM_Tasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with SYSTEM_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
//void SYSTEM_Tasks(void);
#define SYSTEM_Tasks()  // VSK nothing to do ???

#endif //SYSTEM_H
