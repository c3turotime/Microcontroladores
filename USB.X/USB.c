/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

#include "system.h"
#include "usb.h"

/** CONFIGURATION Bits **********************************************/
/*
// CONFIG3
#pragma config WPFP = WPFP511           // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable bit (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMOD = HS             // Primary Oscillator Select (HS oscillator mode selected)
#pragma config DISUVREG = OFF           // Internal USB 3.3V Regulator Disable bit (Regulator is disabled)
#pragma config IOL1WAY = ON             // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSCO functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-safe Clock Monitor are disabled)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary oscillator (XT, HS, EC) with PLL module (XTPLL,HSPLL, ECPLL))
#pragma config PLL_96MHZ = ON           // 96MHz PLL Disable (Enabled)
#pragma config PLLDIV = DIV3            // USB 96 MHz PLL Prescaler Select bits (Oscillator input divided by 3 (12MHz input))
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-speed start-up)disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator functions are shared with PGEC2/PGED2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

 */
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
void SYSTEM_Initialize( SYSTEM_STATE state )
{
    switch(state)
    {
        case SYSTEM_STATE_USB_START:
            LED_Enable(LED_USB_DEVICE_STATE);
            BUTTON_Enable(BUTTON_DEVICE_CDC_BASIC_DEMO);
            break;
            
        case SYSTEM_STATE_USB_SUSPEND:
            //If developing a bus powered USB device that needs to be USB compliant,
            //insert code here to reduce the I/O pin and microcontroller power consumption,
            //so that the total current is <2.5mA from the USB host's VBUS supply.
            //If developing a self powered application (or a bus powered device where
            //official USB compliance isn't critical), nothing strictly needs
            //to be done during USB suspend.

            USBSleepOnSuspend();
            break;

        case SYSTEM_STATE_USB_RESUME:
            //Here would be a good place to restore I/O pins and application states
            //back to their original values that may have been saved/changed at the 
            //start of the suspend event (ex: when the SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND)
            //callback was called.
            
            //If you didn't change any I/O pin states prior to entry into suspend,
            //then nothing explicitly needs to be done here.  However, by the time
            //the firmware returns from this function, the full application should
            //be restored into effectively exactly the same state as the application
            //was in, prior to entering USB suspend.
            
            //Additionally, before returning from this function, make sure the microcontroller's
            //currently active clock settings are compatible with USB operation, including
            //taking into consideration all possible microcontroller features/effects
            //that can affect the oscillator settings (such as internal/external 
            //switchover (two speed start up), fail-safe clock monitor, PLL lock time,
            //external crystal/resonator startup time (if using a crystal/resonator),
            //etc.

            //Additionally, the official USB specifications dictate that USB devices
            //must become fully operational and ready for new host requests/normal 
            //USB communication after a 10ms "resume recovery interval" has elapsed.
            //In order to meet this timing requirement and avoid possible issues,
            //make sure that all necessary oscillator startup is complete and this
            //function has returned within less than this 10ms interval.

            break;

        default:
            break;
    }
}

#if defined(USB_INTERRUPT)
void __attribute__((interrupt,auto_psv)) _USB1Interrupt()
{
    USBDeviceTasks();
}
#endif




/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = ON      // USB Voltage Regulator Enable bit (USB voltage regulator enabled)

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


/** INCLUDES *******************************************************/
#include "system.h"
#include <xc.h>
#include "app_device_cdc_basic.h"
#include "app_led_usb_status.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"


/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "system.h"

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "usb.h"

#include "app_led_usb_status.h"
#include "app_device_cdc_basic.h"
#include "usb_config.h"

/** VARIABLES ******************************************************/

static bool buttonPressed;
static char buttonMessage[] = "Button pressed.\r\n";
static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

/*********************************************************************
* Function: void APP_DeviceCDCBasicDemoInitialize(void);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCDCBasicDemoInitialize()
{   
    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 9600;

    buttonPressed = false;
}

/*********************************************************************
* Function: void APP_DeviceCDCBasicDemoTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCDCBasicDemoInitialize() and APP_DeviceCDCBasicDemoStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCDCBasicDemoTasks()
{
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
             /*
                if( USBIsDeviceSuspended()== true )
                 {
                 return;
                 }
             */   
    /* If the user has pressed the button associated with this demo, then we
     * are going to send a "Button Pressed" message to the terminal.
     */
    if(BUTTON_IsPressed(BUTTON_DEVICE_CDC_BASIC_DEMO) == true)
    {
        /* Make sure that we only send the message once per button press and
         * not continuously as the button is held.
         */
        if(buttonPressed == false)
        {
            /* Make sure that the CDC driver is ready for a transmission.
             */
            if(mUSBUSARTIsTxTrfReady() == true)
            {
                putrsUSBUSART(buttonMessage);
                buttonPressed = true;
            }
        }
    }
    else
    {
        /* If the button is released, we can then allow a new message to be
         * sent the next time the button is pressed.
         */
        buttonPressed = false;
    }

    /* Check to see if there is a transmission in progress, if there isn't, then
     * we can see about performing an echo response to data received.
     */
    if( USBUSARTIsTxTrfReady() == true)
    {
        uint8_t i;
        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

        /* For every byte that was read... */
        for(i=0; i<numBytesRead; i++)
        {
            switch(readBuffer[i])
            {
                /* If we receive new line or line feed commands, just echo
                 * them direct.
                 */
                case 0x0A:
                case 0x0D:
                    writeBuffer[i] = readBuffer[i];
                    break;

                /* If we receive something else, then echo it plus one
                 * so that if we receive 'a', we echo 'b' so that the
                 * user knows that it isn't the echo enabled on their
                 * terminal program.
                 */
                default:
                    writeBuffer[i] = readBuffer[i] + 1;
                    break;
            }
        }

        if(numBytesRead > 0)
        {
            /* After processing all of the received data, we need to send out
             * the "echo" data now.
             */
            putUSBUSART(writeBuffer,numBytesRead);
        }
    }

    CDCTxService();
}



/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "system.h"
#include "usb_device.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************

void APP_LEDUpdateUSBStatus(void)
{
    static uint16_t ledCount = 0;
/*
    if(USBIsDeviceSuspended() == true)
    {
        LED_Off(LED_USB_DEVICE_STATE);
        return;
    }
*/
    switch(USBGetDeviceState())
    {
        case CONFIGURED_STATE:
            /* We are configured.  Blink fast.
             * On for 75ms, off for 75ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_On(LED_USB_DEVICE_STATE);
            }
            else if(ledCount == 75)
            {
                LED_Off(LED_USB_DEVICE_STATE);
            }
            else if(ledCount > 150)
            {
                ledCount = 0;
            }
            break;

        default:
            /* We aren't configured yet, but we aren't suspended so let's blink with
             * a slow pulse. On for 50ms, then off for 950ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_On(LED_USB_DEVICE_STATE);
            }
            else if(ledCount == 50)
            {
                LED_Off(LED_USB_DEVICE_STATE);
            }
            else if(ledCount > 950)
            {
                ledCount = 0;
            }
            break;
    }

    /* Increment the millisecond counter. */
    ledCount++;
}

/*******************************************************************************
 End of File
*/


/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <xc.h>
#include <stdbool.h>
#include "buttons.h"

/*********************************************************************
* Function: bool BUTTON_IsPressed(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names 
*        of the buttons on the silkscreen on the board (as the demo 
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: true if pressed; false if not pressed.
*
********************************************************************/
bool BUTTON_IsPressed(BUTTON button)
{  
    switch(button)
    {
        case BUTTON_NONE:
            return false ;
        default:
            return false;
    }
    
    return false;
}

/*********************************************************************
* Function: void BUTTON_Enable(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names
*        of the buttons on the silkscreen on the board (as the demo
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: None
*
********************************************************************/
void BUTTON_Enable(BUTTON button)
{
    switch(button)
    {
        case BUTTON_NONE:
            break ;

        default:
            break;
    }
}



/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include "leds.h"
#include <stdbool.h>


/*********************************************************************
* Function: void LED_On(LED led);
*
* Overview: Turns requested LED on
*
* PreCondition: LED configured via LED_Configure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*         i.e. - LED_On(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
void LED_On(LED led)
{
    switch(led)
    {
        case LED_GREEN:
            TRISC &= ~0x0300;
            break;
        case LED_BLUE:
            TRISC &= ~0x00C0;
            break;
        case LED_RED:
            TRISC &= ~0x0030;
            break;

        case LED_NONE:
            break ;
    }
}

/*********************************************************************
* Function: void LED_Off(LED led);
*
* Overview: Turns requested LED off
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*         i.e. - LED_Off(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
void LED_Off(LED led)
{
    switch(led)
    {
        case LED_GREEN:
            TRISC |= 0x0300;
            break;

        case LED_BLUE:
            TRISC |= 0x00C0;
            break;

        case LED_RED:
            TRISC |= 0x0030;
            break;

        case LED_NONE:
            break ;
    }
}

/*********************************************************************
* Function: void LED_Toggle(LED led);
*
* Overview: Toggles the state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*         i.e. - LED_Toggle(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
void LED_Toggle(LED led)
{
    switch(led)
    {
        case LED_GREEN:
            TRISC ^= 0x0300;
            break;

        case LED_BLUE:
            TRISC ^= 0x00C0;
            break;

        case LED_RED:
            TRISC ^= 0x0030;
            break;

        case LED_NONE:
            break ;
    }
}

/*********************************************************************
* Function: bool LED_Get(LED led);
*
* Overview: Returns the current state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*         i.e. - LED_Get(LED_CONNECTION_DETECTED);
*
* Output: true if on, false if off
*
********************************************************************/
bool LED_Get(LED led)
{
    switch(led)
    {
        case LED_GREEN:
            return (TRISC & 0x0300) ? false : true;

        case LED_BLUE:
            return (TRISC & 0x00C0) ? false : true;

        case LED_RED:
            return (TRISC & 0x0030) ? false : true;

        case LED_NONE:
            return false ;
    }
    return false ;
}



/*********************************************************************
* Function: void LED_Enable(LED led);
*
* Overview: Configures the LED for use by the other LED API
*
* PreCondition: none
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*
* Output: none
*
********************************************************************/
void LED_Enable(LED led)
{
    switch(led)
    {
        case LED_GREEN:
            LATC &= ~0x0300;
	    TRISC |= 0x0300;
            break;

        case LED_BLUE:
            LATC &= ~0x00C0;
	    TRISC |= 0x00C0;
            break;

        case LED_RED:
            LATC &= ~0x0030;
            TRISC |= 0x0030;
            break;

        case LED_NONE:
            break ;
    }
}



/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/********************************************************************
-usb_descriptors.c-
-------------------------------------------------------------------
Filling in the descriptor values in the usb_descriptors.c file:
-------------------------------------------------------------------

[Device Descriptors]
The device descriptor is defined as a USB_DEVICE_DESCRIPTOR type.  
This type is defined in usb_ch9.h  Each entry into this structure
needs to be the correct length for the data type of the entry.

[Configuration Descriptors]
The configuration descriptor was changed in v2.x from a structure
to a uint8_t array.  Given that the configuration is now a byte array
each byte of multi-byte fields must be listed individually.  This
means that for fields like the total size of the configuration where
the field is a 16-bit value "64,0," is the correct entry for a
configuration that is only 64 bytes long and not "64," which is one
too few bytes.

The configuration attribute must always have the _DEFAULT
definition at the minimum. Additional options can be ORed
to the _DEFAULT attribute. Available options are _SELF and _RWU.
These definitions are defined in the usb_device.h file. The
_SELF tells the USB host that this device is self-powered. The
_RWU tells the USB host that this device supports Remote Wakeup.

[Endpoint Descriptors]
Like the configuration descriptor, the endpoint descriptors were 
changed in v2.x of the stack from a structure to a uint8_t array.  As
endpoint descriptors also has a field that are multi-byte entities,
please be sure to specify both bytes of the field.  For example, for
the endpoint size an endpoint that is 64 bytes needs to have the size
defined as "64,0," instead of "64,"

Take the following example:
    // Endpoint Descriptor //
    0x07,                       //the size of this descriptor //
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP02_IN,                   //EndpointAddress
    _INT,                       //Attributes
    0x08,0x00,                  //size (note: 2 bytes)
    0x02,                       //Interval

The first two parameters are self-explanatory. They specify the
length of this endpoint descriptor (7) and the descriptor type.
The next parameter identifies the endpoint, the definitions are
defined in usb_device.h and has the following naming
convention:
_EP<##>_<dir>
where ## is the endpoint number and dir is the direction of
transfer. The dir has the value of either 'OUT' or 'IN'.
The next parameter identifies the type of the endpoint. Available
options are _BULK, _INT, _ISO, and _CTRL. The _CTRL is not
typically used because the default control transfer endpoint is
not defined in the USB descriptors. When _ISO option is used,
addition options can be ORed to _ISO. Example:
_ISO|_AD|_FE
This describes the endpoint as an isochronous pipe with adaptive
and feedback attributes. See usb_device.h and the USB
specification for details. The next parameter defines the size of
the endpoint. The last parameter in the polling interval.

-------------------------------------------------------------------
Adding a USB String
-------------------------------------------------------------------
A string descriptor array should have the following format:

rom struct{byte bLength;byte bDscType;word string[size];}sdxxx={
sizeof(sdxxx),DSC_STR,<text>};

The above structure provides a means for the C compiler to
calculate the length of string descriptor sdxxx, where xxx is the
index number. The first two bytes of the descriptor are descriptor
length and type. The rest <text> are string texts which must be
in the unicode format. The unicode format is achieved by declaring
each character as a word type. The whole text string is declared
as a word array with the number of characters equals to <size>.
<size> has to be manually counted and entered into the array
declaration. Let's study this through an example:
if the string is "USB" , then the string descriptor should be:
(Using index 02)
rom struct{byte bLength;byte bDscType;word string[3];}sd002={
sizeof(sd002),DSC_STR,'U','S','B'};

A USB project may have multiple strings and the firmware supports
the management of multiple strings through a look-up table.
The look-up table is defined as:
rom const unsigned char *rom USB_SD_Ptr[]={&sd000,&sd001,&sd002};

The above declaration has 3 strings, sd000, sd001, and sd002.
Strings can be removed or added. sd000 is a specialized string
descriptor. It defines the language code, usually this is
US English (0x0409). The index of the string must match the index
position of the USB_SD_Ptr array, &sd000 must be in position
USB_SD_Ptr[0], &sd001 must be in position USB_SD_Ptr[1] and so on.
The look-up table USB_SD_Ptr is used by the get string handler
function.

-------------------------------------------------------------------

The look-up table scheme also applies to the configuration
descriptor. A USB device may have multiple configuration
descriptors, i.e. CFG01, CFG02, etc. To add a configuration
descriptor, user must implement a structure similar to CFG01.
The next step is to add the configuration descriptor name, i.e.
cfg01, cfg02,.., to the look-up table USB_CD_Ptr. USB_CD_Ptr[0]
is a dummy place holder since configuration 0 is the un-configured
state according to the definition in the USB specification.

********************************************************************/
 
/*********************************************************************
 * Descriptor specific type definitions are defined in:
 * usb_device.h
 *
 * Configuration options are defined in:
 * usb_config.h
 ********************************************************************/
#ifndef __USB_DESCRIPTORS_C
#define __USB_DESCRIPTORS_C
 
/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_cdc.h"

/** CONSTANTS ******************************************************/
#if defined(__18CXX)
#pragma romdata
#endif

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    CDC_DEVICE,             // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    0x04D8,                 // Vendor ID
    0x000A,                 // Product ID: CDC RS-232 Emulation Demo
    0x0100,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x00,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[]={
    /* Configuration Descriptor */
    0x09,//sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                // CONFIGURATION descriptor type
    67,0,                   // Total length of data for this cfg
    2,                      // Number of interfaces in this cfg
    1,                      // Index value of this configuration
    0,                      // Configuration string index
    _DEFAULT | _SELF,               // Attributes, see usb_device.h
    50,                     // Max power consumption (2X mA)
							
    /* Interface Descriptor */
    9,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    0,                      // Interface Number
    0,                      // Alternate Setting Number
    1,                      // Number of endpoints in this intf
    COMM_INTF,              // Class code
    ABSTRACT_CONTROL_MODEL, // Subclass code
    V25TER,                 // Protocol code
    0,                      // Interface string index

    /* CDC Class-Specific Descriptors */
    sizeof(USB_CDC_HEADER_FN_DSC),
    CS_INTERFACE,
    DSC_FN_HEADER,
    0x10,0x01,

    sizeof(USB_CDC_ACM_FN_DSC),
    CS_INTERFACE,
    DSC_FN_ACM,
    USB_CDC_ACM_FN_DSC_VAL,

    sizeof(USB_CDC_UNION_FN_DSC),
    CS_INTERFACE,
    DSC_FN_UNION,
    CDC_COMM_INTF_ID,
    CDC_DATA_INTF_ID,

    sizeof(USB_CDC_CALL_MGT_FN_DSC),
    CS_INTERFACE,
    DSC_FN_CALL_MGT,
    0x00,
    CDC_DATA_INTF_ID,

    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP02_IN,_INT,CDC_INT_EP_SIZE,0x02,
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP01_IN,            //EndpointAddress
    _INTERRUPT,                       //Attributes
    0x08,0x00,                  //size
    0x02,                       //Interval

    /* Interface Descriptor */
    9,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    1,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    DATA_INTF,              // Class code
    0,                      // Subclass code
    NO_PROTOCOL,            // Protocol code
    0,                      // Interface string index
    
    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP03_OUT,_BULK,CDC_BULK_OUT_EP_SIZE,0x00,
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP02_OUT,            //EndpointAddress
    _BULK,                       //Attributes
    0x40,0x00,                  //size
    0x00,                       //Interval

    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP03_IN,_BULK,CDC_BULK_IN_EP_SIZE,0x00
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP02_IN,            //EndpointAddress
    _BULK,                       //Attributes
    0x40,0x00,                  //size
    0x00,                       //Interval
};


//Language code string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409}};

//Manufacturer string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};

//Product string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'C','D','C',' ','R','S','-','2','3','2',' ',
'E','m','u','l','a','t','i','o','n',' ','D','e','m','o'}
};

//Serial number string descriptor.  If a serial number string is implemented, 
//it should be unique for every single device coming off the production assembly 
//line.  Plugging two devices with the same serial number into a computer 
//simultaneously will cause problems (in extreme cases BSOD).
//Note: Common OSes put restrictions on the possible values that are allowed.
//For best OS compatibility, the serial number string should only consist
//of UNICODE encoded numbers 0 through 9 and capital letters A through F.
//ROM struct{BYTE bLength;BYTE bDscType;WORD string[10];}sd003={
//sizeof(sd003),USB_DESCRIPTOR_STRING,
//{'0','1','2','3','4','5','6','7','8','9'}};

//Array of configuration descriptors
const uint8_t *const USB_CD_Ptr[]=
{
    (const uint8_t *const)&configDescriptor1
};
//Array of string descriptors
const uint8_t *const USB_SD_Ptr[USB_NUM_STRING_DESCRIPTORS]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002
    //(const uint8_t *const)&sd003  //uncomment if implementing a serial number string descriptor named sd003
};

#if defined(__18CXX)
    #pragma code
#endif

#endif
/** EOF usb_descriptors.c ****************************************************/



// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright 2015 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/
//DOM-IGNORE-END

/*******************************************************************************
  USB Device Layer

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device.c

  Summary:
   Provides basic USB device functionality, including enumeration and USB
   chapter 9 required behavior.

  Description:
   Provides basic USB device functionality, including enumeration and USB
   chapter 9 required behavior.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "usb_config.h"

#include "usb.h"
#include "usb_ch9.h"
#include "usb_device.h"
#include "usb_device_local.h"

#ifndef uintptr_t
    #if  defined(__XC8__) || defined(__XC16__)
        #define uintptr_t uint16_t
    #elif defined (__XC32__)
        #define uintptr_t uint32_t
    #endif
#endif

#if defined(USB_USE_MSD)
    #include "usb_device_msd.h"
#endif

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
#if !defined(USE_USB_BUS_SENSE_IO)
    //Assume the +5V VBUS is always present (like it would be in a bus powered
    //only application), unless USE_USB_BUS_SENSE_IO and USB_BUS_SENSE have
    //been properly defined elsewhere in the project.
    #undef USB_BUS_SENSE
    #define USB_BUS_SENSE 1
#endif

#if defined(USB_DEVICE_DISABLE_DTS_CHECKING)
    #define _DTS_CHECKING_ENABLED 0
#else
    #define _DTS_CHECKING_ENABLED _DTSEN
#endif

#if !defined(self_power)
    //Assume the application is always bus powered, unless self_power has been
    //defined elsewhere in the project
    #define self_power 0    //0 = bus powered
#endif

#if !defined(USB_MAX_NUM_CONFIG_DSC)
    //Assume the application only implements one configuration descriptor,
    //unless otherwise specified elsewhere in the project
    #define USB_MAX_NUM_CONFIG_DSC      1
#endif

#if defined(__XC8)
    //Suppress expected/harmless compiler warning message about unused RAM variables
    //and certain function pointer usage.
    //Certain variables and function pointers are not used if you don't use all
    //of the USB stack APIs.  However, these variables should not be
    //removed (since they are still used/needed in some applications, and this
    //is a common file shared by many projects, some of which rely on the "unused"
    //variables/function pointers).
    #pragma warning disable 1090
    #if __XC8_VERSION > 1300
        #pragma warning disable 1471
    #endif
#endif

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************
typedef union
{
    uint8_t Val;
    struct __PACKED
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    } bits;
} uint8_t_VAL, uint8_t_BITS;

// *****************************************************************************
// *****************************************************************************
// Section: Variables
// *****************************************************************************
// *****************************************************************************
USB_VOLATILE USB_DEVICE_STATE USBDeviceState;
USB_VOLATILE uint8_t USBActiveConfiguration;
USB_VOLATILE uint8_t USBAlternateInterface[USB_MAX_NUM_INT];
//volatile BDT_ENTRY *pBDTEntryEP0OutCurrent;
//volatile BDT_ENTRY *pBDTEntryEP0OutNext;
//volatile BDT_ENTRY *pBDTEntryOut[USB_MAX_EP_NUMBER+1];
//volatile BDT_ENTRY *pBDTEntryIn[USB_MAX_EP_NUMBER+1];
USB_VOLATILE uint8_t shortPacketStatus;
USB_VOLATILE uint8_t controlTransferState;
USB_VOLATILE IN_PIPE inPipes[1];
USB_VOLATILE OUT_PIPE outPipes[1];
USB_VOLATILE uint8_t *pDst;
USB_VOLATILE bool RemoteWakeup;
USB_VOLATILE bool USBBusIsSuspended;
//USB_VOLATILE USTAT_FIELDS USTATcopy;
USB_VOLATILE uint8_t endpoint_number;
USB_VOLATILE bool BothEP0OutUOWNsSet;
USB_VOLATILE EP_STATUS ep_data_in[USB_MAX_EP_NUMBER+1];
USB_VOLATILE EP_STATUS ep_data_out[USB_MAX_EP_NUMBER+1];
USB_VOLATILE uint8_t USBStatusStageTimeoutCounter;
volatile bool USBDeferStatusStagePacket;
volatile bool USBStatusStageEnabledFlag1;
volatile bool USBStatusStageEnabledFlag2;
volatile bool USBDeferINDataStagePackets;
volatile bool USBDeferOUTDataStagePackets;
USB_VOLATILE uint32_t USB1msTickCount;
USB_VOLATILE uint8_t USBTicksSinceSuspendEnd;

/** USB FIXED LOCATION VARIABLES ***********************************/
#if defined(COMPILER_MPLAB_C18)
    #pragma udata USB_BDT=USB_BDT_ADDRESS
#endif

//volatile BDT_ENTRY BDT[BDT_NUM_ENTRIES] BDT_BASE_ADDR_TAG;

/********************************************************************
 * EP0 Buffer Space
 *******************************************************************/
//volatile CTRL_TRF_SETUP SetupPkt CTRL_TRF_SETUP_ADDR_TAG;
//volatile uint8_t CtrlTrfData[USB_EP0_BUFF_SIZE] CTRL_TRF_DATA_ADDR_TAG;

/********************************************************************
 * non-EP0 Buffer Space
 *******************************************************************/
#if defined(USB_USE_MSD)
    //Check if the MSD application specific USB endpoint buffer placement address 
    //macros have already been defined or not (ex: in a processor specific header)
    //The msd_cbw and msd_csw buffers must be USB module accessible (and therefore
    //must be at a certain address range on certain microcontrollers).
    #if !defined(MSD_CBW_ADDR_TAG)
        //Not previously defined.  Assume in this case all microcontroller RAM is
        //USB module accessible, and therefore, no specific address tag value is needed.
        #define MSD_CBW_ADDR_TAG
        #define MSD_CSW_ADDR_TAG
    #endif
	volatile USB_MSD_CBW msd_cbw MSD_CBW_ADDR_TAG;  //Must be located in USB module accessible RAM
	volatile USB_MSD_CSW msd_csw MSD_CSW_ADDR_TAG;  //Must be located in USB module accessible RAM

    #if defined(__18CXX) || defined(__XC8)
        volatile char msd_buffer[512] @ MSD_BUFFER_ADDRESS;
    #else
        volatile char msd_buffer[512];
	#endif
#endif

//Depricated in v2.2 - will be removed in a future revision
#if !defined(USB_USER_DEVICE_DESCRIPTOR)
    //Device descriptor
    extern const USB_DEVICE_DESCRIPTOR device_dsc;
#else
    USB_USER_DEVICE_DESCRIPTOR_INCLUDE;
#endif

#if !defined(USB_USER_CONFIG_DESCRIPTOR)
    //Array of configuration descriptors
    extern const uint8_t *const USB_CD_Ptr[];
#else
    USB_USER_CONFIG_DESCRIPTOR_INCLUDE;
#endif

//extern const uint8_t *const USB_SD_Ptr[];


// *****************************************************************************
// *****************************************************************************
// Section: Private and External Prototypes
// *****************************************************************************
// *****************************************************************************
extern bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size);

static void USBCtrlEPService(void);
static void USBCtrlTrfSetupHandler(void);
static void USBCtrlTrfInHandler(void);
static void USBCheckStdRequest(void);
static void USBStdGetDscHandler(void);
static void USBCtrlEPServiceComplete(void);
static void USBCtrlTrfTxService(void);
static void USBCtrlTrfRxService(void);
static void USBStdSetCfgHandler(void);
static void USBStdGetStatusHandler(void);
static void USBStdFeatureReqHandler(void);
static void USBCtrlTrfOutHandler(void);
static void USBConfigureEndpoint(uint8_t EPNum, uint8_t direction);
static void USBWakeFromSuspend(void);
static void USBSuspend(void);
static void USBStallHandler(void);

// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************

/**************************************************************************
    Function:
        void USBDeviceInit(void)
    
    Description:
        This function initializes the device stack it in the default state. The
        USB module will be completely reset including all of the internal
        variables, registers, and interrupt flags.
                
    Precondition:
        This function must be called before any of the other USB Device
        functions can be called, including USBDeviceTasks().
        
    Parameters:
        None
     
    Return Values:
        None
        
    Remarks:
        None
                                                          
  ***************************************************************************/
void USBDeviceInit(void)
{
    uint8_t i;

    USBDisableInterrupts();

    //Make sure that if a GPIO output driver exists on VBUS, that it is 
    //tri-stated to avoid potential contention with the host
    USB_HAL_VBUSTristate();
    
    // Clear all USB error flags
    USBClearInterruptRegister(UIR);  
       
    // Clears all USB interrupts          
    USBClearInterruptRegister(UIR); 

    //Clear all of the endpoint control registers
    UEP0 = 0;
    
    DisableNonZeroEndpoints(USB_MAX_EP_NUMBER);

    SetConfigurationOptions();

    //power up the module (if not already powered)
    USBPowerModule();

    //set the address of the BDT (if applicable)
    
    char *BDT=0x0400;
    USBSetBDTAddress(BDT);

    //Clear all of the BDT entries
    for(i = 0; i < (64/4); i++)
    {
        BDT[i*4]= 0x00;
        BDT[i*4+1]= 0x00;
        BDT[i*4+2]= 0x00;
        BDT[i*4+3]= 0x00;
    }

    // Assert reset request to all of the Ping Pong buffer pointers
    #define USBPingPongBufferReset PPBRST
    USBPingPongBufferReset = 1;   
    
    // Reset to default address
   for(i = 0; i < (64/4); i++)
    {
        BDT[i*4+2]= 0x00;
        BDT[i*4+3]= 0x00;
    }
    

    // Make sure packet processing is enabled
    //USBPacketDisable = 0;           
    UCONbits.PKTDIS=0;
    
    //Stop trying to reset ping pong buffer pointers
    USBPingPongBufferReset = 0;

    // Flush any pending transactions
    do
    {
        USBClearInterruptFlag(/*USBTransactionCompleteIFReg UIR*/UIR,/*USBTransactionCompleteIFBitNum bits.TRNIF*/ 3);
        //Initialize USB stack software state variables
        inPipes[0].info.Val = 0;
        outPipes[0].info.Val = 0;
        outPipes[0].wCount.Val = 0;
    }while(/*USBTransactionCompleteIF*/ !UIRbits.TRNIF == 1);

    //Set flags to true, so the USBCtrlEPAllowStatusStage() function knows not to
    //try and arm a status stage, even before the first control transfer starts.
    USBStatusStageEnabledFlag1 = true;
    USBStatusStageEnabledFlag2 = true;
    //Initialize other flags
    USBDeferINDataStagePackets = false;
    USBDeferOUTDataStagePackets = false;
    USBBusIsSuspended = false;

    //Initialize all pBDTEntryIn[] and pBDTEntryOut[]
    //pointers to NULL, so they don't get used inadvertently.
    
    UEP0=0b00010110;
    UEP1=0b00010110;
    UEP2=0b00010110;
    UEP3=0b00010110;
    UEP4=0b00010110;
    UEP5=0b00010110;
    UEP6=0b00010110;
    UEP7=0b00010110;
    UEP8=0b00010110;
    UEP9=0b00010110;
    UEP10=0b00010110;
    UEP11=0b00010110;
    UEP12=0b00010110;
    UEP13=0b00010110;
    UEP14=0b00010110;
    UEP15=0b00010110;

    //Get ready for the first packet
    
    // Initialize EP0 as a Ctrl EP
            
	//Prepare for the first SETUP on EP0 OUT
    UADDR=0x03;    //BDT[EP0_OUT_EVEN].ADR = ConvertToPhysicalAddress(&SetupPkt);
    BD0CNT= 10; //    BDT[EP0_OUT_EVEN].CNT = USB_EP0_BUFF_SIZE;
    BD0STAT= 0b00001000; //BDT[EP0_OUT_EVEN].STAT.Val = _DAT0|_BSTALL;
    BD0STAT= 0b10000000; //BDT[EP0_OUT_EVEN].STAT.Val |= _USIE;

    // Clear active configuration
    USBActiveConfiguration = 0;     

    USB1msTickCount = 0;            //Keeps track of total number of milliseconds since calling USBDeviceInit() when first initializing the USB module/stack code.
    USBTicksSinceSuspendEnd = 0;    //Keeps track of the number of milliseconds since a suspend condition has ended.

    //Indicate that we are now in the detached state
    USBDeviceState = DETACHED_STATE;
}



/**************************************************************************
  Function:
        void USBDeviceTasks(void)
    
  Summary:
    This function is the main state machine/transaction handler of the USB 
    device side stack.  When the USB stack is operated in "USB_POLLING" mode 
    (usb_config.h user option) the USBDeviceTasks() function should be called 
    periodically to receive and transmit packets through the stack. This 
    function also takes care of control transfers associated with the USB 
    enumeration process, and detecting various USB events (such as suspend).  
    This function should be called at least once every 1.8ms during the USB 
    enumeration process. After the enumeration process is complete (which can 
    be determined when USBGetDeviceState() returns CONFIGURED_STATE), the 
    USBDeviceTasks() handler may be called the faster of: either once 
    every 9.8ms, or as often as needed to make sure that the hardware USTAT 
    FIFO never gets full.  A good rule of thumb is to call USBDeviceTasks() at
    a minimum rate of either the frequency that USBTransferOnePacket() gets 
    called, or, once/1.8ms, whichever is faster.  See the inline code comments 
    near the top of usb_device.c for more details about minimum timing 
    requirements when calling USBDeviceTasks().
    
    When the USB stack is operated in "USB_INTERRUPT" mode, it is not necessary
    to call USBDeviceTasks() from the main loop context.  In the USB_INTERRUPT
    mode, the USBDeviceTasks() handler only needs to execute when a USB 
    interrupt occurs, and therefore only needs to be called from the interrupt 
    context.

  Description:
    This function is the main state machine/transaction handler of the USB 
    device side stack.  When the USB stack is operated in "USB_POLLING" mode 
    (usb_config.h user option) the USBDeviceTasks() function should be called 
    periodically to receive and transmit packets through the stack. This 
    function also takes care of control transfers associated with the USB 
    enumeration process, and detecting various USB events (such as suspend).  
    This function should be called at least once every 1.8ms during the USB 
    enumeration process. After the enumeration process is complete (which can 
    be determined when USBGetDeviceState() returns CONFIGURED_STATE), the 
    USBDeviceTasks() handler may be called the faster of: either once 
    every 9.8ms, or as often as needed to make sure that the hardware USTAT 
    FIFO never gets full.  A good rule of thumb is to call USBDeviceTasks() at
    a minimum rate of either the frequency that USBTransferOnePacket() gets 
    called, or, once/1.8ms, whichever is faster.  See the inline code comments 
    near the top of usb_device.c for more details about minimum timing 
    requirements when calling USBDeviceTasks().
    
    When the USB stack is operated in "USB_INTERRUPT" mode, it is not necessary
    to call USBDeviceTasks() from the main loop context.  In the USB_INTERRUPT
    mode, the USBDeviceTasks() handler only needs to execute when a USB 
    interrupt occurs, and therefore only needs to be called from the interrupt 
    context.

    Typical usage:
    <code>
    void main(void)
    {
        USBDeviceInit();
        while(1)
        {
            USBDeviceTasks(); //Takes care of enumeration and other USB events
            if((USBGetDeviceState() \< CONFIGURED_STATE) ||
               (USBIsDeviceSuspended() == true))
            {
                //Either the device is not configured or we are suspended,
                // so we don't want to execute any USB related application code
                continue;   //go back to the top of the while loop
            }
            else
            {
                //Otherwise we are free to run USB and non-USB related user 
                //application code.
                UserApplication();
            }
        }
    }
    </code>

  Precondition:
    Make sure the USBDeviceInit() function has been called prior to calling
    USBDeviceTasks() for the first time.
  Remarks:
    USBDeviceTasks() does not need to be called while in the USB suspend mode, 
    if the user application firmware in the USBCBSuspend() callback function
    enables the ACTVIF USB interrupt source and put the microcontroller into 
    sleep mode.  If the application firmware decides not to sleep the 
    microcontroller core during USB suspend (ex: continues running at full 
    frequency, or clock switches to a lower frequency), then the USBDeviceTasks()
    function must still be called periodically, at a rate frequent enough to 
    ensure the 10ms resume recovery interval USB specification is met.  Assuming
    a worst case primary oscillator and PLL start up time of less than 5ms, then
    USBDeviceTasks() should be called once every 5ms in this scenario.
   
    When the USB cable is detached, or the USB host is not actively powering 
    the VBUS line to +5V nominal, the application firmware does not always have 
    to call USBDeviceTasks() frequently, as no USB activity will be taking 
    place.  However, if USBDeviceTasks() is not called regularly, some 
    alternative means of promptly detecting when VBUS is powered (indicating 
    host attachment), or not powered (host powered down or USB cable unplugged)
    is still needed.  For self or dual self/bus powered USB applications, see 
    the USBDeviceAttach() and USBDeviceDetach() API documentation for additional 
    considerations.
    ***************************************************************************/
void USBDeviceTasks(void)
{
    uint8_t i;

    #ifdef USB_SUPPORT_OTG
        //SRP Time Out Check
        if (USBOTGSRPIsReady())
        {
            if (USBT1MSECIF && USBT1MSECIE)
            {
                if (USBOTGGetSRPTimeOutFlag())
                {
                    if (USBOTGIsSRPTimeOutExpired())
                    {
                        USB_OTGEventHandler(0,OTG_EVENT_SRP_FAILED,0,0);
                    }
                }

                //Clear Interrupt Flag
                USBClearInterruptFlag(USBT1MSECIFReg,USBT1MSECIFBitNum);
            }
        }
    #endif

    #if defined(USB_POLLING)
    //If the interrupt option is selected then the customer is required
    //  to notify the stack when the device is attached or removed from the
    //  bus by calling the USBDeviceAttach() and USBDeviceDetach() functions.
    if (USB_BUS_SENSE != 1)
    {
         // Disable module & detach from bus
         U1CON = 0;             

         // Mask all USB interrupts              
         U1IE = 0;          

         //Move to the detached state                  
         USBDeviceState = DETACHED_STATE;

         #ifdef  USB_SUPPORT_OTG    
             //Disable D+ Pullup
             U1OTGCONbits.DPPULUP = 0;

             //Disable HNP
             USBOTGDisableHnp();

             //Deactivate HNP
             USBOTGDeactivateHnp();
             
             //If ID Pin Changed State
             if (USBIDIF && USBIDIE)
             {  
                 //Re-detect & Initialize
                  USBOTGInitialize();

                  //Clear ID Interrupt Flag
                  USBClearInterruptFlag(USBIDIFReg,USBIDIFBitNum);
             }
         #endif

         #if defined __C30__ || defined __XC16__
             //USBClearInterruptFlag(U1OTGIR, 3); 
         #endif
            //return so that we don't go through the rest of 
            //the state machine
         USBClearUSBInterrupt();
         return;
    }

	#ifdef USB_SUPPORT_OTG
    //If Session Is Started Then
    else
	{
        //If SRP Is Ready
        if (USBOTGSRPIsReady())
        {   
            //Clear SRPReady
            USBOTGClearSRPReady();

            //Clear SRP Timeout Flag
            USBOTGClearSRPTimeOutFlag();

            //Indicate Session Started
            UART2PrintString( "\r\n***** USB OTG B Event - Session Started  *****\r\n" );
        }
    }
	#endif	//#ifdef USB_SUPPORT_OTG

    //if we are in the detached state
    if(USBDeviceState == DETACHED_STATE)
    {
	    //Initialize register to known value
        U1CON = 0;                          

        // Mask all USB interrupts
        U1IE = 0;                                

        //Enable/set things like: pull ups, full/low-speed mode, 
        //set the ping pong mode, and set internal transceiver
        SetConfigurationOptions();

        // Enable module & attach to bus
        while(!U1CONbits.USBEN){U1CONbits.USBEN = 1;}

        //moved to the attached state
        USBDeviceState = ATTACHED_STATE;

        #ifdef  USB_SUPPORT_OTG
            U1OTGCON |= USB_OTG_DPLUS_ENABLE | USB_OTG_ENABLE;  
        #endif
    }
	#endif  //#if defined(USB_POLLING)

    if(USBDeviceState == ATTACHED_STATE)
    {
        /*
         * After enabling the USB module, it takes some time for the
         * voltage on the D+ or D- line to rise high enough to get out
         * of the SE0 condition. The USB Reset interrupt should not be
         * unmasked until the SE0 condition is cleared. This helps
         * prevent the firmware from misinterpreting this unique event
         * as a USB bus reset from the USB host.
         */

        if(!USBSE0Event)
        {
            //We recently attached, make sure we are in a clean state
            #if defined(__dsPIC33E__) || defined(_PIC24E__) || defined(__PIC32MM__)
                U1IR = 0xFFEF;  //Preserve IDLEIF info, so we can detect suspend
                                //during attach de-bounce interval
            #else
                USBClearInterruptRegister(U1IR);
            #endif

            #if defined(USB_POLLING)
                U1IE=0;                        // Mask all USB interrupts
            #endif
            USBResetIE = 1;             // Unmask RESET interrupt
            USBIdleIE = 1;             // Unmask IDLE interrupt
            USBDeviceState = POWERED_STATE;
        }
    }

    #ifdef  USB_SUPPORT_OTG
        //If ID Pin Changed State
        if (USBIDIF && USBIDIE)
        {  
            //Re-detect & Initialize
            USBOTGInitialize();

            USBClearInterruptFlag(USBIDIFReg,USBIDIFBitNum);
        }
    #endif

    /*
     * Task A: Service USB Activity Interrupt
     */
    if(USBActivityIF && USBActivityIE)
    {
        USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
        #if defined(USB_SUPPORT_OTG)
            U1OTGIR = 0x10;        
        #else
            USBWakeFromSuspend();
        #endif
    }

    /*
     * Pointless to continue servicing if the device is in suspend mode.
     */
    if(USBSuspendControl==1)
    {
        USBClearUSBInterrupt();
        return;
    }

    /*
     * Task B: Service USB Bus Reset Interrupt.
     * When bus reset is received during suspend, ACTVIF will be set first,
     * once the UCONbits.SUSPND is clear, then the URSTIF bit will be asserted.
     * This is why URSTIF is checked after ACTVIF.
     *
     * The USB reset flag is masked when the USB state is in
     * DETACHED_STATE or ATTACHED_STATE, and therefore cannot
     * cause a USB reset event during these two states.
     */
    if(USBResetIF && USBResetIE)
    {
        USBDeviceInit();

        //Re-enable the interrupts since the USBDeviceInit() function will
        //  disable them.  This will do nothing in a polling setup
        USBUnmaskInterrupts();

        USBDeviceState = DEFAULT_STATE;

        #ifdef USB_SUPPORT_OTG
             //Disable HNP
             USBOTGDisableHnp();

             //Deactivate HNP
             USBOTGDeactivateHnp();
        #endif

        USBClearInterruptFlag(USBResetIFReg,USBResetIFBitNum);
    }

    /*
     * Task C: Service other USB interrupts
     */
    if(USBIdleIF && USBIdleIE)
    { 
        #ifdef  USB_SUPPORT_OTG 
            //If Suspended, Try to switch to Host
            USBOTGSelectRole(ROLE_HOST);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
        #else
            USBSuspend();
        #endif
    }

    #if defined(__XC16__) || defined(__C30__) || defined(__XC32__)
        //Check if a 1ms interval has elapsed.	
        if(USBT1MSECIF)
        {
            USBClearInterruptFlag(USBT1MSECIFReg, USBT1MSECIFBitNum);
            USBIncrement1msInternalTimers();
        }
    #endif

    //Start-of-Frame Interrupt
    if(USBSOFIF)
    {
        //Call the user SOF event callback if enabled.
        if(USBSOFIE)
        {
            USB_SOF_HANDLER(EVENT_SOF,0,1);
        }    
        USBClearInterruptFlag(USBSOFIFReg,USBSOFIFBitNum);

        #if defined(__XC8__) || defined(__C18__)
            USBIncrement1msInternalTimers();
        #endif

        #if defined(USB_ENABLE_STATUS_STAGE_TIMEOUTS)
            //Supporting this feature requires a 1ms time base for keeping track of the timeout interval.
            #if(USB_SPEED_OPTION == USB_LOW_SPEED)
                #warning "Double click this message.  See inline code comments."
                //The "USB_ENABLE_STATUS_STAGE_TIMEOUTS" feature is optional and is
                //not strictly needed in all applications (ex: those that never call 
                //USBDeferStatusStage() and don't use host to device (OUT) control
                //transfers with data stage).  
                //However, if this feature is enabled and used in a low speed application,
                //it is required for the application code to periodically call the
                //USBIncrement1msInternalTimers() function at a nominally 1ms rate.
            #endif
            
            //Decrement our status stage counter.
            if(USBStatusStageTimeoutCounter != 0u)
            {
                USBStatusStageTimeoutCounter--;
            }
            //Check if too much time has elapsed since progress was made in 
            //processing the control transfer, without arming the status stage.  
            //If so, auto-arm the status stage to ensure that the control 
            //transfer can [eventually] complete, within the timing limits
            //dictated by section 9.2.6 of the official USB 2.0 specifications.
            if(USBStatusStageTimeoutCounter == 0)
            {
                USBCtrlEPAllowStatusStage();    //Does nothing if the status stage was already armed.
            } 
        #endif
    }

    if(USBStallIF && USBStallIE)
    {
        USBStallHandler();
    }

    if(USBErrorIF && USBErrorIE)
    {
        USB_ERROR_HANDLER(EVENT_BUS_ERROR,0,1);
        USBClearInterruptRegister(U1EIR);               // This clears UERRIF

        //On PIC18, clearing the source of the error will automatically clear
        //  the interrupt flag.  On other devices the interrupt flag must be 
        //  manually cleared. 
        #if defined(__C32__) || defined(__C30__) || defined __XC16__
            USBClearInterruptFlag( USBErrorIFReg, USBErrorIFBitNum );
        #endif
    }

    /*
     * Pointless to continue servicing if the host has not sent a bus reset.
     * Once bus reset is received, the device transitions into the DEFAULT
     * state and is ready for communication.
     */
    if(USBDeviceState < DEFAULT_STATE)
    {
        USBClearUSBInterrupt();
        return;
    }  

    /*
     * Task D: Servicing USB Transaction Complete Interrupt
     */
    if(USBTransactionCompleteIE)
    {
        for(i = 0; i < 4u; i++)	//Drain or deplete the USAT FIFO entries.  If the USB FIFO ever gets full, USB bandwidth
        {						//utilization can be compromised, and the device won't be able to receive SETUP packets.
            if(USBTransactionCompleteIF)
            {
                //Save and extract USTAT register info.  Will use this info later.
                USTATcopy.Val = U1STAT;
                endpoint_number = USBHALGetLastEndpoint(USTATcopy);

                USBClearInterruptFlag(USBTransactionCompleteIFReg,USBTransactionCompleteIFBitNum);

                //Keep track of the hardware ping pong state for endpoints other
                //than EP0, if ping pong buffering is enabled.
                #if (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0) || (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG)
                if(USBHALGetLastDirection(USTATcopy) == OUT_FROM_HOST)
                {
                    ep_data_out[endpoint_number].bits.ping_pong_state ^= 1;
                }
                else
                {
                    ep_data_in[endpoint_number].bits.ping_pong_state ^= 1;
                }
                #endif

                //USBCtrlEPService only services transactions over EP0.
                //It ignores all other EP transactions.
                if(endpoint_number == 0)
                {
                    USBCtrlEPService();
                }
                else
                {
                    USB_TRANSFER_COMPLETE_HANDLER(EVENT_TRANSFER, (uint8_t*)&USTATcopy.Val, 0);
                }
            }//end if(USBTransactionCompleteIF)
            else
            {
                break;	//USTAT FIFO must be empty.
            }
        }//end for()
    }//end if(USBTransactionCompleteIE)

    USBClearUSBInterrupt();
}//end of USBDeviceTasks()

/*******************************************************************************
  Function:
        void USBEnableEndpoint(uint8_t ep, uint8_t options)
    
  Summary:
    This function will enable the specified endpoint with the specified
    options
  Description:
    This function will enable the specified endpoint with the specified
    options.
    
    Typical Usage:
    <code>
    void USBCBInitEP(void)
    {
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
        USBMSDInit();
    }
    </code>
    
    In the above example endpoint number MSD_DATA_IN_EP is being configured
    for both IN and OUT traffic with handshaking enabled. Also since
    MSD_DATA_IN_EP is not endpoint 0 (MSD does not allow this), then we can
    explicitly disable SETUP packets on this endpoint.
  Conditions:
    None
  Input:
    uint8_t ep -       the endpoint to be configured
    uint8_t options -  optional settings for the endpoint. The options should
                    be ORed together to form a single options string. The
                    available optional settings for the endpoint. The
                    options should be ORed together to form a single options
                    string. The available options are the following\:
                    * USB_HANDSHAKE_ENABLED enables USB handshaking (ACK,
                      NAK)
                    * USB_HANDSHAKE_DISABLED disables USB handshaking (ACK,
                      NAK)
                    * USB_OUT_ENABLED enables the out direction
                    * USB_OUT_DISABLED disables the out direction
                    * USB_IN_ENABLED enables the in direction
                    * USB_IN_DISABLED disables the in direction
                    * USB_ALLOW_SETUP enables control transfers
                    * USB_DISALLOW_SETUP disables control transfers
                    * USB_STALL_ENDPOINT STALLs this endpoint
  Return:
    None
  Remarks:
    None                                                                                                          
  *****************************************************************************/
void USBEnableEndpoint(uint8_t ep, uint8_t options)
{
    unsigned char* p;
        
    //Use USBConfigureEndpoint() to set up the pBDTEntryIn/Out[ep] pointer and 
    //starting DTS state in the BDT entry.
    if(options & USB_OUT_ENABLED)
    {
        USBConfigureEndpoint(ep, OUT_FROM_HOST);
    }
    if(options & USB_IN_ENABLED)
    {
        USBConfigureEndpoint(ep, IN_TO_HOST);
    }

    //Update the relevant UEPx register to actually enable the endpoint with
    //the specified options (ex: handshaking enabled, control transfers allowed,
    //etc.)
    #if defined(__C32__)
        p = (unsigned char*)(&U1EP0+(4*ep));
    #else
        p = (unsigned char*)(&U1EP0+ep);
    #endif
    *p = options;
}


/*************************************************************************
  Function:
    USB_HANDLE USBTransferOnePacket(uint8_t ep, uint8_t dir, uint8_t* data, uint8_t len)
    
  Summary:
    Transfers a single packet (one transaction) of data on the USB bus.

  Description:
    The USBTransferOnePacket() function prepares a USB endpoint
    so that it may send data to the host (an IN transaction), or 
    receive data from the host (an OUT transaction).  The 
    USBTransferOnePacket() function can be used both to receive	and 
    send data to the host.  This function is the primary API function 
    provided by the USB stack firmware for sending or receiving application 
    data over the USB port.  

    The USBTransferOnePacket() is intended for use with all application 
    endpoints.  It is not used for sending or receiving application data 
    through endpoint 0 by using control transfers.  Separate API 
    functions, such as USBEP0Receive(), USBEP0SendRAMPtr(), and
    USBEP0SendROMPtr() are provided for this purpose.

    The	USBTransferOnePacket() writes to the Buffer Descriptor Table (BDT)
    entry associated with an endpoint buffer, and sets the UOWN bit, which 
    prepares the USB hardware to allow the transaction to complete.  The 
    application firmware can use the USBHandleBusy() macro to check the 
    status of the transaction, to see if the data has been successfully 
    transmitted yet.


    Typical Usage
    <code>
    //make sure that the we are in the configured state
    if(USBGetDeviceState() == CONFIGURED_STATE)
    {
        //make sure that the last transaction isn't busy by checking the handle
        if(!USBHandleBusy(USBInHandle))
        {
	        //Write the new data that we wish to send to the host to the INPacket[] array
	        INPacket[0] = USEFUL_APPLICATION_VALUE1;
	        INPacket[1] = USEFUL_APPLICATION_VALUE2;
	        //INPacket[2] = ... (fill in the rest of the packet data)
	      
            //Send the data contained in the INPacket[] array through endpoint "EP_NUM"
            USBInHandle = USBTransferOnePacket(EP_NUM,IN_TO_HOST,(uint8_t*)&INPacket[0],sizeof(INPacket));
        }
    }
    </code>

  Conditions:
    Before calling USBTransferOnePacket(), the following should be true.
    1.  The USB stack has already been initialized (USBDeviceInit() was called).
    2.  A transaction is not already pending on the specified endpoint.  This
        is done by checking the previous request using the USBHandleBusy() 
        macro (see the typical usage example).
    3.  The host has already sent a set configuration request and the 
        enumeration process is complete.
        This can be checked by verifying that the USBGetDeviceState() 
        macro returns "CONFIGURED_STATE", prior to calling 
        USBTransferOnePacket().
 					
  Input:
    uint8_t ep - The endpoint number that the data will be transmitted or
	          received on
    uint8_t dir - The direction of the transfer
               This value is either OUT_FROM_HOST or IN_TO_HOST
    uint8_t* data - For IN transactions: pointer to the RAM buffer containing
                 the data to be sent to the host.  For OUT transactions: pointer
                 to the RAM buffer that the received data should get written to.
   uint8_t len - Length of the data needing to be sent (for IN transactions).
              For OUT transactions, the len parameter should normally be set
              to the endpoint size specified in the endpoint descriptor.    

  Return Values:
    USB_HANDLE - handle to the transfer.  The handle is a pointer to 
                 the BDT entry associated with this transaction.  The
                 status of the transaction (ex: if it is complete or still
                 pending) can be checked using the USBHandleBusy() macro
                 and supplying the USB_HANDLE provided by
                 USBTransferOnePacket().

  Remarks:
    If calling the USBTransferOnePacket() function from within the USBCBInitEP()
    callback function, the set configuration is still being processed and the
    USBDeviceState may not be == CONFIGURED_STATE yet.  In this	special case, 
    the USBTransferOnePacket() may still be called, but make sure that the 
    endpoint has been enabled and initialized by the USBEnableEndpoint() 
    function first.  
    
  *************************************************************************/
USB_HANDLE USBTransferOnePacket(uint8_t ep,uint8_t dir,uint8_t* data,uint8_t len)
{
    volatile BDT_ENTRY* handle;

    //If the direction is IN
    if(dir != 0)
    {
        //point to the IN BDT of the specified endpoint
        handle = pBDTEntryIn[ep];
    }
    else
    {
        //else point to the OUT BDT of the specified endpoint
        handle = pBDTEntryOut[ep];
    }
    
    //Error checking code.  Make sure the handle (pBDTEntryIn[ep] or
    //pBDTEntryOut[ep]) is initialized before using it.
    if(handle == 0)
    {
        return 0;
    }

    //Toggle the DTS bit if required
    #if (USB_PING_PONG_MODE == USB_PING_PONG__NO_PING_PONG)
        handle->STAT.Val ^= _DTSMASK;
    #elif (USB_PING_PONG_MODE == USB_PING_PONG__EP0_OUT_ONLY)
        if(ep != 0)
        {
            handle->STAT.Val ^= _DTSMASK;
        }
    #endif

    //Set the data pointer, data length, and enable the endpoint
    handle->ADR = ConvertToPhysicalAddress(data);
    handle->CNT = len;
    handle->STAT.Val &= _DTSMASK;
    handle->STAT.Val |= (_DTSEN & _DTS_CHECKING_ENABLED);
    handle->STAT.Val |= _USIE;

    //Point to the next buffer for ping pong purposes.
    if(dir != OUT_FROM_HOST)
    {
        //toggle over the to the next buffer for an IN endpoint
        pBDTEntryIn[ep] = (BDT_ENTRY*)(((uintptr_t)pBDTEntryIn[ep]) ^ USB_NEXT_PING_PONG);
    }
    else
    {
        //toggle over the to the next buffer for an OUT endpoint
        pBDTEntryOut[ep] = (BDT_ENTRY*)(((uintptr_t)pBDTEntryOut[ep]) ^ USB_NEXT_PING_PONG);
    }
    return (USB_HANDLE)handle;
}


/********************************************************************
    Function:
        void USBStallEndpoint(uint8_t ep, uint8_t dir)
        
    Summary:
         Configures the specified endpoint to send STALL to the host, the next
         time the host tries to access the endpoint.
    
    PreCondition:
        None
        
    Parameters:
        uint8_t ep - The endpoint number that should be configured to send STALL.
        uint8_t dir - The direction of the endpoint to STALL, either
                   IN_TO_HOST or OUT_FROM_HOST.
        
    Return Values:
        None
        
    Remarks:
        None

 *******************************************************************/
void USBStallEndpoint(uint8_t ep, uint8_t dir)
{
    BDT_ENTRY *p;

    if(ep == 0)
    {
        //For control endpoints (ex: EP0), we need to STALL both IN and OUT
        //endpoints.  EP0 OUT must also be prepared to receive the next SETUP 
        //packet that will arrive.
        pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
        pBDTEntryEP0OutNext->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED)|_BSTALL;
        pBDTEntryEP0OutNext->STAT.Val |= _USIE;
        pBDTEntryIn[0]->STAT.Val = _BSTALL; 
        pBDTEntryIn[0]->STAT.Val |= _USIE;
               
    }
    else
    {
        p = (BDT_ENTRY*)(&BDT[EP(ep,dir,0)]);
        p->STAT.Val |= _BSTALL;
        p->STAT.Val |= _USIE;
    
        //If the device is in FULL or ALL_BUT_EP0 ping pong modes
        //then stall that entry as well
        #if (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG) || (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0)
        p = (BDT_ENTRY*)(&BDT[EP(ep,dir,1)]);
        p->STAT.Val |= _BSTALL;
        p->STAT.Val |= _USIE;
        #endif
    }
}

/**************************************************************************
    Function:
        void USBCancelIO(uint8_t endpoint)
    
    Description:
        This function cancels the transfers pending on the specified endpoint.
        This function can only be used after a SETUP packet is received and 
        before that setup packet is handled.  This is the time period in which
        the EVENT_EP0_REQUEST is thrown, before the event handler function
        returns to the stack.

    Precondition:
  
    Parameters:
        uint8_t endpoint - the endpoint number you wish to cancel the transfers for
     
    Return Values:
        None
        
    Remarks:
        None
                                                          
  **************************************************************************/
void USBCancelIO(uint8_t endpoint)
{
    if(USBPacketDisable == 1)
    {
    	//The PKTDIS bit is currently set right now.  It is therefore "safe"
    	//to mess with the BDT right now.
    	pBDTEntryIn[endpoint]->Val &= _DTSMASK;	//Makes UOWN = 0 (_UCPU mode).  Deactivates endpoint.  Only sends NAKs.
    	pBDTEntryIn[endpoint]->Val ^= _DTSMASK;	//Toggle the DTS bit.  This packet didn't get sent yet, and the next call to USBTransferOnePacket() will re-toggle the DTS bit back to the original (correct) value.
    	
    	//Need to do additional handling if ping-pong buffering is being used
        #if ((USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG) || (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0))
        //Point to the next buffer for ping pong purposes.  UOWN getting cleared
        //(either due to SIE clearing it after a transaction, or the firmware
        //clearing it) makes hardware ping pong pointer advance.
        pBDTEntryIn[endpoint] = (BDT_ENTRY*)(((uintptr_t)pBDTEntryIn[endpoint]) ^ USB_NEXT_PING_PONG);
        
    	pBDTEntryIn[endpoint]->STAT.Val &= _DTSMASK;
    	pBDTEntryIn[endpoint]->STAT.Val ^= _DTSMASK;
        #endif
    }
}

/**************************************************************************
    Function:
        void USBDeviceDetach(void)
   
    Summary:
        This function configures the USB module to "soft detach" itself from
        the USB host.
        
    Description:
        This function configures the USB module to perform a "soft detach"
        operation, by disabling the D+ (or D-) ~1.5k pull up resistor, which
        lets the host know the device is present and attached.  This will make
        the host think that the device has been unplugged.  This is potentially
        useful, as it allows the USB device to force the host to re-enumerate
        the device (on the firmware has re-enabled the USB module/pull up, by
        calling USBDeviceAttach(), to "soft re-attach" to the host).
        
    Precondition:
        Should only be called when USB_INTERRUPT is defined.  See remarks
        section if USB_POLLING mode option is being used (usb_config.h option).

        Additionally, this function should only be called from the main() loop 
        context.  Do not call this function from within an interrupt handler, as 
        this function may modify global interrupt enable bits and settings.
        
    Parameters:
        None
     
    Return Values:
        None
        
    Remarks:
        If the application firmware calls USBDeviceDetach(), it is strongly
        recommended that the firmware wait at least >= 80ms before calling
        USBDeviceAttach().  If the firmware performs a soft detach, and then
        re-attaches too soon (ex: after a few micro seconds for instance), some
        hosts may interpret this as an unexpected "glitch" rather than as a
        physical removal/re-attachment of the USB device.  In this case the host
        may simply ignore the event without re-enumerating the device.  To 
        ensure that the host properly detects and processes the device soft
        detach/re-attach, it is recommended to make sure the device remains 
        detached long enough to mimic a real human controlled USB 
        unplug/re-attach event (ex: after calling USBDeviceDetach(), do not
        call USBDeviceAttach() for at least 80+ms, preferably longer.
        
        Neither the USBDeviceDetach() or USBDeviceAttach() functions are blocking
        or take long to execute.  It is the application firmwares 
        responsibility for adding the 80+ms delay, when using these API 
        functions.
        
        Note: The Windows plug and play event handler processing is fairly 
        slow, especially in certain versions of Windows, and for certain USB
        device classes.  It has been observed that some device classes need to
        provide even more USB detach dwell interval (before calling 
        USBDeviceAttach()), in order to work correctly after re-enumeration.
        If the USB device is a CDC class device, it is recommended to wait
        at least 1.5 seconds or longer, before soft re-attaching to the host,
        to provide the plug and play event handler enough time to finish 
        processing the removal event, before the re-attach occurs.
        
        If the application is using the USB_POLLING mode option, then the 
        USBDeviceDetach() and USBDeviceAttach() functions are not available.  
        In this mode, the USB stack relies on the "#define USE_USB_BUS_SENSE_IO" 
        and "#define USB_BUS_SENSE" options in the 
        HardwareProfile ? [platform name].h file. 

        When using the USB_POLLING mode option, and the 
        "#define USE_USB_BUS_SENSE_IO" definition has been commented out, then 
        the USB stack assumes that it should always enable the USB module at 
        pretty much all times.  Basically, anytime the application firmware 
        calls USBDeviceTasks(), the firmware will automatically enable the USB 
        module.  This mode would typically be selected if the application was 
        designed to be a purely bus powered device.  In this case, the 
        application is powered from the +5V VBUS supply from the USB port, so 
        it is correct and sensible in this type of application to power up and 
        turn on the USB module, at anytime that the microcontroller is 
        powered (which implies the USB cable is attached and the host is also 
        powered).

        In a self powered application, the USB stack is designed with the 
        intention that the user will enable the "#define USE_USB_BUS_SENSE_IO" 
        option in the HardwareProfile ? [platform name].h file.  When this 
        option is defined, then the USBDeviceTasks() function will automatically 
        check the I/O pin port value of the designated pin (based on the 
        #define USB_BUS_SENSE option in the HardwareProfile ? [platform name].h 
        file), every time the application calls USBDeviceTasks().  If the 
        USBDeviceTasks() function is executed and finds that the pin defined by 
        the #define USB_BUS_SENSE is in a logic low state, then it will 
        automatically disable the USB module and tri-state the D+ and D- pins.  
        If however the USBDeviceTasks() function is executed and finds the pin 
        defined by the #define USB_BUS_SENSE is in a logic high state, then it 
        will automatically enable the USB module, if it has not already been 
        enabled.        
                                                          
  **************************************************************************/
#if defined(USB_INTERRUPT)
void USBDeviceDetach(void)
{
    //If the interrupt option is selected then the customer is required
    //  to notify the stack when the device is attached or removed from the
    //  bus by calling the USBDeviceAttach() and USBDeviceDetach() functions.
#ifdef USB_SUPPORT_OTG
    if (USB_BUS_SENSE != 1)
#endif
    {
         // Disable module & detach from bus
         U1CON = 0;             

         // Mask all USB interrupts              
         U1IE = 0;          

         //Move to the detached state                  
         USBDeviceState = DETACHED_STATE;

         #ifdef  USB_SUPPORT_OTG    
             //Disable D+ Pull-up
             U1OTGCONbits.DPPULUP = 0;

             //Disable HNP
             USBOTGDisableHnp();

             //Deactivate HNP
             USBOTGDeactivateHnp();
             
             //If ID Pin Changed State
             if (USBIDIF && USBIDIE)
             {  
                 //Re-detect & Initialize
                  USBOTGInitialize();

                  //Clear ID Interrupt Flag
                  USBClearInterruptFlag(USBIDIFReg,USBIDIFBitNum);
             }
         #endif

         #if defined __C30__ || defined __XC16__
             //USBClearInterruptFlag(U1OTGIR, 3); 
         #endif
            //return so that we don't go through the rest of 
            //the state machine
          return;
    }

#ifdef USB_SUPPORT_OTG
    //If Session Is Started Then
   else
   {
        //If SRP Is Ready
        if (USBOTGSRPIsReady())
        {   
            //Clear SRPReady
            USBOTGClearSRPReady();

            //Clear SRP Timeout Flag
            USBOTGClearSRPTimeOutFlag();

            //Indicate Session Started
            UART2PrintString( "\r\n***** USB OTG B Event - Session Started  *****\r\n" );
        }
    }
#endif
}
#endif  //#if defined(USB_INTERRUPT)
/**************************************************************************
    Function:
        void USBDeviceAttach(void)
    
    Summary:
        Checks if VBUS is present, and that the USB module is not already 
        initialized, and if so, enables the USB module so as to signal device 
        attachment to the USB host.   

    Description:
        This function indicates to the USB host that the USB device has been
        attached to the bus.  This function needs to be called in order for the
        device to start to enumerate on the bus.
                
    Precondition:
        Should only be called when USB_INTERRUPT is defined.  Also, should only 
        be called from the main() loop context.  Do not call USBDeviceAttach()
        from within an interrupt handler, as the USBDeviceAttach() function
        may modify global interrupt enable bits and settings.

        For normal USB devices:
        Make sure that if the module was previously on, that it has been turned off 
        for a long time (ex: 100ms+) before calling this function to re-enable the module.
        If the device turns off the D+ (for full speed) or D- (for low speed) ~1.5k ohm
        pull up resistor, and then turns it back on very quickly, common hosts will sometimes 
        reject this event, since no human could ever unplug and re-attach a USB device in a 
        microseconds (or nanoseconds) timescale.  The host could simply treat this as some kind 
        of glitch and ignore the event altogether.  
    Parameters:
        None
     
    Return Values:
        None       
    
    Remarks: 
		See also the USBDeviceDetach() API function documentation.                                                 
****************************************************************************/
#if defined(USB_INTERRUPT)
void USBDeviceAttach(void)
{
    //if we are in the detached state
    if(USBDeviceState == DETACHED_STATE)
    {
        if(USB_BUS_SENSE == 1)
        {
    	    //Initialize registers to known states.
            U1CON = 0;          
    
            // Mask all USB interrupts
            U1IE = 0;                                
    
            //Configure things like: pull ups, full/low-speed mode, 
            //set the ping pong mode, and set internal transceiver
            SetConfigurationOptions();
    
            USBEnableInterrupts();  //Modifies global interrupt settings
    
            // Enable module & attach to bus
            while(!U1CONbits.USBEN){U1CONbits.USBEN = 1;}
    
            //moved to the attached state
            USBDeviceState = ATTACHED_STATE;
    
            #ifdef  USB_SUPPORT_OTG
                U1OTGCON = USB_OTG_DPLUS_ENABLE | USB_OTG_ENABLE;  
            #endif
        }
    }
}
#endif  //#if defined(USB_INTERRUPT)


/*******************************************************************************
  Function: void USBCtrlEPAllowStatusStage(void);

  Summary: This function prepares the proper endpoint 0 IN or endpoint 0 OUT
            (based on the controlTransferState) to allow the status stage packet
            of a control transfer to complete.  This function gets used
            internally by the USB stack itself, but it may also be called from
            the application firmware, IF the application firmware called
            the USBDeferStatusStage() function during the initial processing
            of the control transfer request.  In this case, the application
            must call the USBCtrlEPAllowStatusStage() once, after it has fully
            completed processing and handling the data stage portion of the
            request.

            If the application firmware has no need for delaying control
            transfers, and therefore never calls USBDeferStatusStage(), then the
            application firmware should not call USBCtrlEPAllowStatusStage().

  Description:

  Conditions:
    None

  Input:

  Return:

  Remarks:
    None
  *****************************************************************************/
void USBCtrlEPAllowStatusStage(void)
{
    //Check and set two flags, prior to actually modifying any BDT entries.
    //This double checking is necessary to make certain that 
    //USBCtrlEPAllowStatusStage() can be called twice simultaneously (ex: once 
    //in main loop context, while simultaneously getting an interrupt which 
    //tries to call USBCtrlEPAllowStatusStage() again, at the same time).
    if(USBStatusStageEnabledFlag1 == false)
    {
        USBStatusStageEnabledFlag1 = true;
        if(USBStatusStageEnabledFlag2 == false)
        {
            USBStatusStageEnabledFlag2 = true;
        
            //Determine which endpoints (EP0 IN or OUT needs arming for the status
            //stage), based on the type of control transfer currently pending.
            if(controlTransferState == CTRL_TRF_RX)
            {
                pBDTEntryIn[0]->CNT = 0;
                pBDTEntryIn[0]->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);        
                pBDTEntryIn[0]->STAT.Val |= _USIE;
            }
            else if(controlTransferState == CTRL_TRF_TX)
            {
                BothEP0OutUOWNsSet = false;	//Indicator flag used in USBCtrlTrfOutHandler()

                //This buffer (when ping pong buffering is enabled on EP0 OUT) receives the
                //next SETUP packet.
                #if((USB_PING_PONG_MODE == USB_PING_PONG__EP0_OUT_ONLY) || (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG))
                    pBDTEntryEP0OutCurrent->CNT = USB_EP0_BUFF_SIZE;
                    pBDTEntryEP0OutCurrent->ADR = ConvertToPhysicalAddress(&SetupPkt);
                    pBDTEntryEP0OutCurrent->STAT.Val = _BSTALL; //Prepare endpoint to accept a SETUP transaction
                    pBDTEntryEP0OutCurrent->STAT.Val |= _USIE;
                    BothEP0OutUOWNsSet = true;	//Indicator flag used in USBCtrlTrfOutHandler()
                #endif

                //This EP0 OUT buffer receives the 0-byte OUT status stage packet.
                pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
                pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
                pBDTEntryEP0OutNext->STAT.Val = _USIE;           // Note: DTSEN is 0
            }
        }    
    }
}   


/*******************************************************************************
  Function: void USBCtrlEPAllowDataStage(void);
    
  Summary: This function allows the data stage of either a host-to-device or
            device-to-host control transfer (with data stage) to complete.
            This function is meant to be used in conjunction with either the
            USBDeferOUTDataStage() or USBDeferINDataStage().  If the firmware
            does not call either USBDeferOUTDataStage() or USBDeferINDataStage(),
            then the firmware does not need to manually call 
            USBCtrlEPAllowDataStage(), as the USB stack will call this function
            instead.
     
  Description:
    
  Conditions: A control transfer (with data stage) should already be pending, 
                if the firmware calls this function.  Additionally, the firmware
                should have called either USBDeferOUTDataStage() or 
                USBDeferINDataStage() at the start of the control transfer, if
                the firmware will be calling this function manually.

  Input:

  Return:

  Remarks: 
  *****************************************************************************/
void USBCtrlEPAllowDataStage(void)
{
    USBDeferINDataStagePackets = false;
    USBDeferOUTDataStagePackets = false;

    if(controlTransferState == CTRL_TRF_RX) //(<setup><out><out>...<out><in>)
    {
        //Prepare EP0 OUT to receive the first OUT data packet in the data stage sequence.
        pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
        pBDTEntryEP0OutNext->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
        pBDTEntryEP0OutNext->STAT.Val |= _USIE;
    }   
    else    //else must be controlTransferState == CTRL_TRF_TX (<setup><in><in>...<in><out>)
    {
        //Error check the data stage byte count.  Make sure the user specified
        //value was no greater than the number of bytes the host requested.
		if(SetupPkt.wLength < inPipes[0].wCount.Val)
		{
			inPipes[0].wCount.Val = SetupPkt.wLength;
		}
		USBCtrlTrfTxService();  //Copies one IN data packet worth of data from application buffer
		                        //to CtrlTrfData buffer.  Also keeps track of how many bytes remaining.

	    //Cnt should have been initialized by responsible request owner (ex: by
	    //using the USBEP0SendRAMPtr() or USBEP0SendROMPtr() API function).
		pBDTEntryIn[0]->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
		pBDTEntryIn[0]->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
        pBDTEntryIn[0]->STAT.Val |= _USIE;
    }     
}    


/******************************************************************************/
/** Internal Functions *********************************************************/
/******************************************************************************/

/********************************************************************
 * Function:        void USBConfigureEndpoint(uint8_t EPNum, uint8_t direction)
 *
 * PreCondition:    None
 *
 * Input:           uint8_t EPNum - the endpoint to be configured
 *                  uint8_t direction - the direction to be configured
 *                                   (either OUT_FROM_HOST or IN_TO_HOST)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function will configure the specified 
 *                  endpoint
 *
 * Note:            None
 *******************************************************************/
static void USBConfigureEndpoint(uint8_t EPNum, uint8_t direction)
{
    volatile BDT_ENTRY* handle;

    //Compute a pointer to the even BDT entry corresponding to the
    //EPNum and direction values passed to this function.
    handle = (volatile BDT_ENTRY*)&BDT[EP0_OUT_EVEN]; //Get address of start of BDT
    handle += EP(EPNum,direction,0u);     //Add in offset to the BDT of interest
    
    handle->STAT.UOWN = 0;  //mostly redundant, since USBStdSetCfgHandler() 
    //already cleared the entire BDT table

    //Make sure our pBDTEntryIn/Out[] pointer is initialized.  Needed later
    //for USBTransferOnePacket() API calls.
    if(direction == OUT_FROM_HOST)
    {
        pBDTEntryOut[EPNum] = handle;
    }
    else
    {
        pBDTEntryIn[EPNum] = handle;
    }

    #if (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG)
        handle->STAT.DTS = 0;
        (handle+1)->STAT.DTS = 1;
    #elif (USB_PING_PONG_MODE == USB_PING_PONG__NO_PING_PONG)
        //Set DTS to one because the first thing we will do
        //when transmitting is toggle the bit
        handle->STAT.DTS = 1;
    #elif (USB_PING_PONG_MODE == USB_PING_PONG__EP0_OUT_ONLY)
        if(EPNum != 0)
        {
            handle->STAT.DTS = 1;
        }
    #elif (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0)    
        if(EPNum != 0)
        {
            handle->STAT.DTS = 0;
            (handle+1)->STAT.DTS = 1;
        }
    #endif
}


/******************************************************************************
 * Function:        void USBCtrlEPServiceComplete(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine wrap up the remaining tasks in servicing
 *                  a Setup Request. Its main task is to set the endpoint
 *                  controls appropriately for a given situation. See code
 *                  below.
 *                  There are three main scenarios:
 *                  a) There was no handler for the Request, in this case
 *                     a STALL should be sent out.
 *                  b) The host has requested a read control transfer,
 *                     endpoints are required to be setup in a specific way.
 *                  c) The host has requested a write control transfer, or
 *                     a control data stage is not required, endpoints are
 *                     required to be setup in a specific way.
 *
 *                  Packet processing is resumed by clearing PKTDIS bit.
 *
 * Note:            None
 *****************************************************************************/
static void USBCtrlEPServiceComplete(void)
{
    /*
     * PKTDIS bit is set when a Setup Transaction is received.
     * Clear to resume packet processing.
     */
    USBPacketDisable = 0;

	//Check the busy bits and the SetupPtk.DataDir variables to determine what type of
	//control transfer is currently in progress.  We need to know the type of control
	//transfer that is currently pending, in order to know how to properly arm the 
	//EP0 IN and EP0 OUT endpoints.
    if(inPipes[0].info.bits.busy == 0)
    {
        if(outPipes[0].info.bits.busy == 1)
        {
            controlTransferState = CTRL_TRF_RX;
            /*
             * Control Write:
             * <SETUP[0]><OUT[1]><OUT[0]>...<IN[1]> | <SETUP[0]>
             */

            //1. Prepare OUT EP to receive data, unless a USB class request handler
            //   function decided to defer the data stage (ex: because the intended
            //   RAM buffer wasn't available yet) by calling USBDeferDataStage().
            //   If it did so, it is then responsible for calling USBCtrlEPAllowDataStage(),
            //   once it is ready to begin receiving the data.
            if(USBDeferOUTDataStagePackets == false)
            {
                USBCtrlEPAllowDataStage();
            }
            
            //2.  IN endpoint 0 status stage will be armed by USBCtrlEPAllowStatusStage() 
            //after all of the OUT data has been received and consumed, or if a timeout occurs.
            USBStatusStageEnabledFlag2 = false;
            USBStatusStageEnabledFlag1 = false;
        }
        else
        {
            /*
             * If no one knows how to service this request then stall.
             * Must also prepare EP0 to receive the next SETUP transaction.
             */
            pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
            pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
            pBDTEntryEP0OutNext->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED)|_BSTALL;
            pBDTEntryEP0OutNext->STAT.Val |= _USIE;
            pBDTEntryIn[0]->STAT.Val = _BSTALL;
            pBDTEntryIn[0]->STAT.Val |= _USIE;
        }
    }
    else    // A module has claimed ownership of the control transfer session.
    {
		if(SetupPkt.DataDir == USB_SETUP_DEVICE_TO_HOST_BITFIELD)
		{
			controlTransferState = CTRL_TRF_TX;
			/*
			 * Control Read:
			 * <SETUP[0]><IN[1]><IN[0]>...<OUT[1]> | <SETUP[0]>
			 *
			 * 1. Prepare IN EP to transfer data to the host.  If however the data
			 *    wasn't ready yet (ex: because the firmware needs to go and read it from
			 *    some slow/currently unavailable resource, such as an external I2C EEPconst),
			 *    Then the class request handler responsible should call the USBDeferDataStage()
			 *    macro.  In this case, the firmware may wait up to 500ms, before it is required
			 *    to transmit the first IN data packet.  Once the data is ready, and the firmware
			 *    is ready to begin sending the data, it should then call the 
			 *    USBCtrlEPAllowDataStage() function to start the data stage.
			 */
			if(USBDeferINDataStagePackets == false)
            {
                USBCtrlEPAllowDataStage();
			}

            // 2. (Optionally) allow the status stage now, to prepare for early termination.
            //    Note: If a class request handler decided to set USBDeferStatusStagePacket == true,
            //    then it is responsible for eventually calling USBCtrlEPAllowStatusStage() once it
            //    is ready.  If the class request handler does this, it needs to be careful to
            //    be written so that it can handle the early termination scenario.
            //    Ex: It should call USBCtrlEPAllowStatusStage() when any of the following occurs:
            //    1.  The desired total number of bytes were sent to the host.
            //    2.  The number of bytes that the host originally requested (in the SETUP packet that 
            //        started the control transfer) has been reached.
            //    3.  Or, if a timeout occurs (ex: <50ms since the last successful EP0 IN transaction), regardless 
            //        of how many bytes have actually been sent.  This is necessary to prevent a deadlock situation
            //        (where the control transfer can't complete, due to continuous NAK on status stage) if the
            //        host performs early termination.  If enabled, the USB_ENABLE_STATUS_STAGE_TIMEOUTS usb_config.h
            //        option can take care of this for you.
            //    Note: For this type of control transfer, there is normally no harm in simply arming the
            //    status stage packet right now, even if the IN data is not ready yet.  This allows for
            //    immediate early termination, without adding unnecessary delay.  Therefore, it is generally not
            //    recommended for the USB class handler firmware to call USBDeferStatusStage(), for this 
            //    type of control transfer.  If the USB class handler firmware needs more time to fetch the IN
            //    data that needs to be sent to the host, it should instead use the USBDeferDataStage() function.
            USBStatusStageEnabledFlag2 = false;
            USBStatusStageEnabledFlag1 = false;
            if(USBDeferStatusStagePacket == false)
            {
                USBCtrlEPAllowStatusStage();
            } 
		}
		else   // (SetupPkt.DataDir == USB_SETUP_DIRECTION_HOST_TO_DEVICE)
		{
			//This situation occurs for special types of control transfers,
			//such as that which occurs when the host sends a SET_ADDRESS
			//control transfer.  Ex:
			//
			//<SETUP[0]><IN[1]> | <SETUP[0]>
				
			//Although the data direction is HOST_TO_DEVICE, there is no data stage
			//(hence: outPipes[0].info.bits.busy == 0).  There is however still
			//an IN status stage.

			controlTransferState = CTRL_TRF_RX;     //Since this is a HOST_TO_DEVICE control transfer
			
			//1. Prepare OUT EP to receive the next SETUP packet.
			pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
			pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
			pBDTEntryEP0OutNext->STAT.Val = _BSTALL;
            pBDTEntryEP0OutNext->STAT.Val |= _USIE;
				
			//2. Prepare for IN status stage of the control transfer
            USBStatusStageEnabledFlag2 = false;
            USBStatusStageEnabledFlag1 = false;
			if(USBDeferStatusStagePacket == false)
            {
                USBCtrlEPAllowStatusStage();
            } 
		}

    }//end if(ctrl_trf_session_owner == MUID_NULL)

}//end USBCtrlEPServiceComplete


/******************************************************************************
 * Function:        void USBCtrlTrfTxService(void)
 *
 * PreCondition:    pSrc, wCount, and usb_stat.ctrl_trf_mem are setup properly.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine is used for device to host control transfers 
 *					(IN transactions).  This function takes care of managing a
 *                  transfer over multiple USB transactions.
 *					This routine should be called from only two places.
 *                  One from USBCtrlEPServiceComplete() and one from
 *                  USBCtrlTrfInHandler().
 *
 * Note:            
 *****************************************************************************/
static void USBCtrlTrfTxService(void)
{
    uint8_t byteToSend;

    //Figure out how many bytes of data to send in the next IN transaction.
    //Assume a full size packet, unless otherwise determined below.
    byteToSend = USB_EP0_BUFF_SIZE;         
    if(inPipes[0].wCount.Val < (uint8_t)USB_EP0_BUFF_SIZE)
    {
        byteToSend = inPipes[0].wCount.Val;

        //Keep track of whether or not we have sent a "short packet" yet.
        //This is useful so that later on, we can configure EP0 IN to STALL,
        //after we have sent all of the intended data.  This makes sure the
        //hardware STALLs if the host erroneously tries to send more IN token 
        //packets, requesting more data than intended in the control transfer.
        if(shortPacketStatus == SHORT_PKT_NOT_USED)
        {
            shortPacketStatus = SHORT_PKT_PENDING;
        }
        else if(shortPacketStatus == SHORT_PKT_PENDING)
        {
            shortPacketStatus = SHORT_PKT_SENT;
        }
    }

    //Keep track of how many bytes remain to be sent in the transfer, by
    //subtracting the number of bytes about to be sent from the total.
    inPipes[0].wCount.Val -= byteToSend;
    
    //Next, load the number of bytes to send to BC7..0 in buffer descriptor.
    //Note: Control endpoints may never have a max packet size of > 64 bytes.
    //Therefore, the BC8 and BC9 bits should always be maintained clear.
    pBDTEntryIn[0]->CNT = byteToSend;

    //Now copy the data from the source location, to the CtrlTrfData[] buffer,
    //which we will send to the host.
    pDst = (USB_VOLATILE uint8_t*)CtrlTrfData;                // Set destination pointer
    if(inPipes[0].info.bits.ctrl_trf_mem == USB_EP0_ROM)   // Determine type of memory source
    {
        while(byteToSend)
        {
            *pDst++ = *inPipes[0].pSrc.bRom++;
            byteToSend--;
        }//end while(byte_to_send.Val)
    }
    else  // RAM
    {
        while(byteToSend)
        {
            *pDst++ = *inPipes[0].pSrc.bRam++;
            byteToSend--;
        }//end while(byte_to_send.Val)
    }//end if(usb_stat.ctrl_trf_mem == _const)
}//end USBCtrlTrfTxService

/******************************************************************************
 * Function:        void USBCtrlTrfRxService(void)
 *
 * PreCondition:    pDst and wCount are setup properly.
 *                  pSrc is always &CtrlTrfData
 *                  usb_stat.ctrl_trf_mem is always USB_EP0_RAM.
 *                  wCount should be set to 0 at the start of each control
 *                  transfer.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine is used for host to device control transfers
 *					(uses OUT transactions).  This function receives the data that arrives
 *					on EP0 OUT, and copies it into the appropriate outPipes[0].pDst.bRam
 *					buffer.  Once the host has sent all the data it was intending
 *					to send, this function will call the appropriate outPipes[0].pFunc()
 *					handler (unless it is NULL), so that it can be used by the
 *					intended target firmware.
 *
 * Note:            None
 *****************************************************************************/
static void USBCtrlTrfRxService(void)
{
    uint8_t byteToRead;
    uint8_t i;

    //Load byteToRead with the number of bytes the host just sent us in the 
    //last OUT transaction.
    byteToRead = pBDTEntryEP0OutCurrent->CNT;   

    //Update the "outPipes[0].wCount.Val", which keeps track of the total number
    //of remaining bytes expected to be received from the host, in the control
    //transfer.  First check to see if the host sent us more bytes than the
    //application firmware was expecting to receive.
    if(byteToRead > outPipes[0].wCount.Val)
    {
        byteToRead = outPipes[0].wCount.Val;
    }	
    //Reduce the number of remaining bytes by the number we just received.
    outPipes[0].wCount.Val -= byteToRead;

    //Copy the OUT DATAx packet bytes that we just received from the host,
    //into the user application buffer space.
    for(i=0;i<byteToRead;i++)
    {
        *outPipes[0].pDst.bRam++ = CtrlTrfData[i];
    }//end while(byteToRead.Val)

    //If there is more data to receive, prepare EP0 OUT so that it can receive 
	//the next packet in the sequence.
    if(outPipes[0].wCount.Val > 0)
    {
        pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
        if(pBDTEntryEP0OutCurrent->STAT.DTS == 0)
        {
            pBDTEntryEP0OutNext->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
            pBDTEntryEP0OutNext->STAT.Val |= _USIE;
        }
        else
        {
            pBDTEntryEP0OutNext->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED);
            pBDTEntryEP0OutNext->STAT.Val |= _USIE;
        }
    }
    else
    {
	    //We have received all OUT packets that we were expecting to
	    //receive for the control transfer.  Prepare EP0 OUT to receive
		//the next SETUP transaction that may arrive.
        pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
        //Configure EP0 OUT to receive the next SETUP transaction for any future
        //control transfers.  However, set BSTALL in case the host tries to send
        //more data than it claims it was going to send.
        pBDTEntryEP0OutNext->STAT.Val = _BSTALL;
        pBDTEntryEP0OutNext->STAT.Val |= _USIE;

		//All data bytes for the host to device control write (OUT) have now been
		//received successfully.
		//Go ahead and call the user specified callback function, to use/consume
		//the control transfer data (ex: if the "void (*function)" parameter 
		//was non-NULL when USBEP0Receive() was called).
        if(outPipes[0].pFunc != NULL)
        {
            #if defined(__XC8)
                //Special pragmas to suppress an expected/harmless warning
                //message when building with the XC8 compiler
                #pragma warning push
                #pragma warning disable 1088
                outPipes[0].pFunc();    //Call the user's callback function
                #pragma warning pop
            #else
                outPipes[0].pFunc();    //Call the user's callback function
            #endif
        }
        outPipes[0].info.bits.busy = 0;    

        //Ready to arm status stage IN transaction now, if the application
        //firmware has completed processing the request.  If it is still busy
        //and needs more time to finish handling the request, then the user
        //callback (the one called by the outPipes[0].pFunc();) should set the
        //USBDeferStatusStagePacket to true (by calling USBDeferStatusStage()).  In
        //this case, it is the application's firmware responsibility to call 
        //the USBCtrlEPAllowStatusStage() function, once it is fully done handling the request.
        //Note: The application firmware must process the request and call
        //USBCtrlEPAllowStatusStage() in a semi-timely fashion.  "Semi-timely"
        //means either 50ms, 500ms, or 5 seconds, depending on the type of
        //control transfer.  See the USB 2.0 specification section 9.2.6 for
        //more details.
        if(USBDeferStatusStagePacket == false)
        {
            USBCtrlEPAllowStatusStage();
        }            
    }    

}//end USBCtrlTrfRxService


/********************************************************************
 * Function:        void USBStdSetCfgHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine first disables all endpoints by
 *                  clearing UEP registers. It then configures
 *                  (initializes) endpoints by calling the callback
 *                  function USBCBInitEP().
 *
 * Note:            None
 *******************************************************************/
static void USBStdSetCfgHandler(void)
{
    uint8_t i;

    // This will generate a zero length packet
    inPipes[0].info.bits.busy = 1;            

    //Clear all of the endpoint control registers
    DisableNonZeroEndpoints(USB_MAX_EP_NUMBER);

    //Clear all of the BDT entries
    memset((void*)&BDT[0], 0x00, sizeof(BDT));

    // Assert reset request to all of the Ping Pong buffer pointers
    USBPingPongBufferReset = 1;                                   

	//Re-Initialize all ping pong software state bits to 0 (which corresponds to
	//the EVEN buffer being the next one that will be used), since we are also 
	//doing a hardware ping pong pointer reset above.
	for(i = 0; i < (uint8_t)(USB_MAX_EP_NUMBER+1u); i++)
	{
		ep_data_in[i].Val = 0u;
        ep_data_out[i].Val = 0u;
	}

    //clear the alternate interface settings
    memset((void*)&USBAlternateInterface,0x00,USB_MAX_NUM_INT);

    //Stop trying to reset ping pong buffer pointers
    USBPingPongBufferReset = 0;

    pBDTEntryIn[0] = (volatile BDT_ENTRY*)&BDT[EP0_IN_EVEN];

	//Set the next out to the current out packet
    pBDTEntryEP0OutCurrent = (volatile BDT_ENTRY*)&BDT[EP0_OUT_EVEN];
    pBDTEntryEP0OutNext = pBDTEntryEP0OutCurrent;

    //set the current configuration
    USBActiveConfiguration = SetupPkt.bConfigurationValue;

    //if the configuration value == 0
    if(USBActiveConfiguration == 0)
    {
        //Go back to the addressed state
        USBDeviceState = ADDRESS_STATE;
    }
    else
    {
        //initialize the required endpoints
        USB_SET_CONFIGURATION_HANDLER(EVENT_CONFIGURED,(void*)&USBActiveConfiguration,1);

        //Otherwise go to the configured state.  Update the state variable last,
        //after performing all of the set configuration related initialization
        //tasks.
        USBDeviceState = CONFIGURED_STATE;		
    }//end if(SetupPkt.bConfigurationValue == 0)
}//end USBStdSetCfgHandler


/********************************************************************
 * Function:        void USBStdGetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine handles the standard GET_DESCRIPTOR
 *                  request.
 *
 * Note:            None
 *******************************************************************/
static void USBStdGetDscHandler(void)
{
    if(SetupPkt.bmRequestType == 0x80)
    {
        inPipes[0].info.Val = USB_EP0_ROM | USB_EP0_BUSY | USB_EP0_INCLUDE_ZERO;

        switch(SetupPkt.bDescriptorType)
        {
            case USB_DESCRIPTOR_DEVICE:
                #if !defined(USB_USER_DEVICE_DESCRIPTOR)
                    inPipes[0].pSrc.bRom = (const uint8_t*)&device_dsc;
                #else
                    inPipes[0].pSrc.bRom = (const uint8_t*)USB_USER_DEVICE_DESCRIPTOR;
                #endif
                inPipes[0].wCount.Val = sizeof(device_dsc);
                break;
            case USB_DESCRIPTOR_CONFIGURATION:
                //First perform error case check, to make sure the host is requesting a 
                //legal descriptor index.  If the request index is illegal, don't do 
                //anything (so that the default STALL response will be sent).
                if(SetupPkt.bDscIndex < USB_MAX_NUM_CONFIG_DSC)
                {
                    #if !defined(USB_USER_CONFIG_DESCRIPTOR)
                        inPipes[0].pSrc.bRom = *(USB_CD_Ptr+SetupPkt.bDscIndex);
                    #else
                        inPipes[0].pSrc.bRom = *(USB_USER_CONFIG_DESCRIPTOR+SetupPkt.bDscIndex);
                    #endif

                    //This must be loaded using byte addressing.  The source pointer
                    //  may not be word aligned for the 16 or 32 bit machines resulting
                    //  in an address error on the dereference.
                    inPipes[0].wCount.byte.LB = *(inPipes[0].pSrc.bRom+2);
                    inPipes[0].wCount.byte.HB = *(inPipes[0].pSrc.bRom+3);
                }
				else
				{
					inPipes[0].info.Val = 0;
				}
                break;
            case USB_DESCRIPTOR_STRING:
                //USB_NUM_STRING_DESCRIPTORS was introduced as optional in release v2.3.  In v2.4 and
                //  later it is now mandatory.  This should be defined in usb_config.h and should
                //  indicate the number of string descriptors.
                if(SetupPkt.bDscIndex<USB_NUM_STRING_DESCRIPTORS)
                {
                    //Get a pointer to the String descriptor requested
                    inPipes[0].pSrc.bRom = *(USB_SD_Ptr+SetupPkt.bDscIndex);
                    // Set data count
                    inPipes[0].wCount.Val = *inPipes[0].pSrc.bRom;                    
                }
                #if defined(IMPLEMENT_MICROSOFT_OS_DESCRIPTOR)
                else if(SetupPkt.bDscIndex == MICROSOFT_OS_DESCRIPTOR_INDEX)
                {
                    //Get a pointer to the special MS OS string descriptor requested
                    inPipes[0].pSrc.bRom = (const uint8_t*)&MSOSDescriptor;
                    // Set data count
                    inPipes[0].wCount.Val = *inPipes[0].pSrc.bRom;                    
                }    
                #endif
                else
                {
                    inPipes[0].info.Val = 0;
                }
                break;
            default:
                inPipes[0].info.Val = 0;
                break;
        }//end switch
    }//end if
}//end USBStdGetDscHandler

/********************************************************************
 * Function:        void USBStdGetStatusHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine handles the standard GET_STATUS request
 *
 * Note:            None
 *******************************************************************/
static void USBStdGetStatusHandler(void)
{
    CtrlTrfData[0] = 0;                 // Initialize content
    CtrlTrfData[1] = 0;

    switch(SetupPkt.Recipient)
    {
        case USB_SETUP_RECIPIENT_DEVICE_BITFIELD:
            inPipes[0].info.bits.busy = 1;
            /*
             * [0]: bit0: Self-Powered Status [0] Bus-Powered [1] Self-Powered
             *      bit1: RemoteWakeup        [0] Disabled    [1] Enabled
             */
            if(self_power == 1) // self_power is defined in HardwareProfile.h
            {
                CtrlTrfData[0]|=0x01;
            }

            if(RemoteWakeup == true)
            {
                CtrlTrfData[0]|=0x02;
            }
            break;
        case USB_SETUP_RECIPIENT_INTERFACE_BITFIELD:
            inPipes[0].info.bits.busy = 1;     // No data to update
            break;
        case USB_SETUP_RECIPIENT_ENDPOINT_BITFIELD:
            inPipes[0].info.bits.busy = 1;
            /*
             * [0]: bit0: Halt Status [0] Not Halted [1] Halted
             */
            {
                BDT_ENTRY *p;

                if(SetupPkt.EPDir == 0)
                {
                    p = (BDT_ENTRY*)pBDTEntryOut[SetupPkt.EPNum];
                }
                else
                {
                    p = (BDT_ENTRY*)pBDTEntryIn[SetupPkt.EPNum];
                }

                if((p->STAT.UOWN == 1) && (p->STAT.BSTALL == 1))
                    CtrlTrfData[0]=0x01;    // Set bit0
                break;
            }
    }//end switch

    if(inPipes[0].info.bits.busy == 1)
    {
        inPipes[0].pSrc.bRam = (uint8_t*)&CtrlTrfData;        // Set Source
        inPipes[0].info.bits.ctrl_trf_mem = USB_EP0_RAM;      // Set memory type
        inPipes[0].wCount.v[0] = 2;                           // Set data count
    }//end if(...)
}//end USBStdGetStatusHandler

/********************************************************************
 * Function:        void USBStallHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        This function handles the event of a STALL 
 *                  occurring on the bus
 *
 * Note:            None
 *******************************************************************/
static void USBStallHandler(void)
{
    /*
     * Does not really have to do anything here,
     * even for the control endpoint.
     * All BDs of Endpoint 0 are owned by SIE right now,
     * but once a Setup Transaction is received, the ownership
     * for EP0_OUT will be returned to CPU.
     * When the Setup Transaction is serviced, the ownership
     * for EP0_IN will then be forced back to CPU by firmware.
     */

    if(U1EP0bits.EPSTALL == 1)
    {
        // UOWN - if 0, owned by CPU, if 1, owned by SIE
        if((pBDTEntryEP0OutCurrent->STAT.Val == _USIE) && (pBDTEntryIn[0]->STAT.Val == (_USIE|_BSTALL)))
        {
            // Set ep0Bo to stall also
            pBDTEntryEP0OutCurrent->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED)|_BSTALL;
            pBDTEntryEP0OutCurrent->STAT.Val |= _USIE;
        }//end if
        U1EP0bits.EPSTALL = 0;               // Clear stall status
    }//end if

    USBClearInterruptFlag(USBStallIFReg,USBStallIFBitNum);
}

/********************************************************************
 * Function:        void USBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    
 *
 * Overview:        This function handles if the host tries to 
 *                  suspend the device
 *
 * Note:            None
 *******************************************************************/
static void USBSuspend(void)
{
    /*
     * NOTE: Do not clear UIRbits.ACTVIF here!
     * Reason:
     * ACTVIF is only generated once an IDLEIF has been generated.
     * This is a 1:1 ratio interrupt generation.
     * For every IDLEIF, there will be only one ACTVIF regardless of
     * the number of subsequent bus transitions.
     *
     * If the ACTIF is cleared here, a problem could occur when:
     * [       IDLE       ][bus activity ->
     * <--- 3 ms ----->     ^
     *                ^     ACTVIF=1
     *                IDLEIF=1
     *  #           #           #           #   (#=Program polling flags)
     *                          ^
     *                          This polling loop will see both
     *                          IDLEIF=1 and ACTVIF=1.
     *                          However, the program services IDLEIF first
     *                          because ACTIVIE=0.
     *                          If this routine clears the only ACTIVIF,
     *                          then it can never get out of the suspend
     *                          mode.
     */
    USBActivityIE = 1;                     // Enable bus activity interrupt
    USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);

    #if defined(__18CXX) || defined(_PIC14E) || defined(__XC8)
        U1CONbits.SUSPND = 1;                   // Put USB module in power conserve
                                                // mode, SIE clock inactive
    #endif
    USBBusIsSuspended = true;
    USBTicksSinceSuspendEnd = 0;
 
    /*
     * At this point the PIC can go into sleep,idle, or
     * switch to a slower clock, etc.  This should be done in the
     * USBCBSuspend() if necessary.
     */
    USB_SUSPEND_HANDLER(EVENT_SUSPEND,0,0);
}

/********************************************************************
 * Function:        void USBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:
 *
 * Note:            None
 *******************************************************************/
static void USBWakeFromSuspend(void)
{
    USBBusIsSuspended = false;

    /*
     * If using clock switching, the place to restore the original
     * microcontroller core clock frequency is in the USBCBWakeFromSuspend() callback
     */
    USB_WAKEUP_FROM_SUSPEND_HANDLER(EVENT_RESUME,0,0);

    #if defined(__18CXX) || defined(_PIC14E) || defined(__XC8)
        //To avoid improperly clocking the USB module, make sure the oscillator
        //settings are consistent with USB operation before clearing the SUSPND bit.
        //Make sure the correct oscillator settings are selected in the 
        //"USB_WAKEUP_FROM_SUSPEND_HANDLER(EVENT_RESUME,0,0)" handler.
        U1CONbits.SUSPND = 0;   // Bring USB module out of power conserve
                                // mode.
    #endif


    USBActivityIE = 0;

    /********************************************************************
    Bug Fix: Feb 26, 2007 v2.1
    *********************************************************************
    The ACTVIF bit cannot be cleared immediately after the USB module wakes
    up from Suspend or while the USB module is suspended. A few clock cycles
    are required to synchronize the internal hardware state machine before
    the ACTIVIF bit can be cleared by firmware. Clearing the ACTVIF bit
    before the internal hardware is synchronized may not have an effect on
    the value of ACTVIF. Additionally, if the USB module uses the clock from
    the 96 MHz PLL source, then after clearing the SUSPND bit, the USB
    module may not be immediately operational while waiting for the 96 MHz
    PLL to lock.
    ********************************************************************/

    // UIRbits.ACTVIF = 0;                      // Removed
    #if defined(__18CXX) || defined(__XC8)
    while(USBActivityIF)
    #endif
    {
        USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
    }  // Added

    USBTicksSinceSuspendEnd = 0;

}//end USBWakeFromSuspend

/********************************************************************
 * Function:        void USBCtrlEPService(void)
 *
 * PreCondition:    USTAT is loaded with a valid endpoint address.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        USBCtrlEPService checks for three transaction
 *                  types that it knows how to service and services
 *                  them:
 *                  1. EP0 SETUP
 *                  2. EP0 OUT
 *                  3. EP0 IN
 *                  It ignores all other types (i.e. EP1, EP2, etc.)
 *
 * Note:            None
 *******************************************************************/
static void USBCtrlEPService(void)
{
    //If we get to here, that means a successful transaction has just occurred 
    //on EP0.  This means "progress" has occurred in the currently pending 
    //control transfer, so we should re-initialize our timeout counter.
    #if defined(USB_ENABLE_STATUS_STAGE_TIMEOUTS)
        USBStatusStageTimeoutCounter = USB_STATUS_STAGE_TIMEOUT;
    #endif
	
	//Check if the last transaction was on EP0 OUT endpoint (of any kind, to either the even or odd buffer if ping pong buffers used)
    if((USTATcopy.Val & USTAT_EP0_PP_MASK) == USTAT_EP0_OUT_EVEN)
    {
		//Point to the EP0 OUT buffer of the buffer that arrived
        #if defined (_PIC14E) || defined(__18CXX) || defined(__XC8)
            pBDTEntryEP0OutCurrent = (volatile BDT_ENTRY*)&BDT[(USTATcopy.Val & USTAT_EP_MASK)>>1];
        #elif defined(__C30__) || defined(__C32__) || defined __XC16__
            pBDTEntryEP0OutCurrent = (volatile BDT_ENTRY*)&BDT[(USTATcopy.Val & USTAT_EP_MASK)>>2];
        #else
            #error "unimplemented"
        #endif

		//Set the next out to the current out packet
        pBDTEntryEP0OutNext = pBDTEntryEP0OutCurrent;
		//Toggle it to the next ping pong buffer (if applicable)
        pBDTEntryEP0OutNext = (volatile BDT_ENTRY*)(((uintptr_t)pBDTEntryEP0OutNext) ^ USB_NEXT_EP0_OUT_PING_PONG);

		//If the current EP0 OUT buffer has a SETUP packet
        if(pBDTEntryEP0OutCurrent->STAT.PID == PID_SETUP)
        {
	        //The SETUP transaction data may have gone into the the CtrlTrfData 
	        //buffer, or elsewhere, depending upon how the BDT was prepared
	        //before the transaction.  Therefore, we should copy the data to the 
	        //SetupPkt buffer so it can be processed correctly by USBCtrlTrfSetupHandler().		    
            memcpy((uint8_t*)&SetupPkt, (uint8_t*)ConvertToVirtualAddress(pBDTEntryEP0OutCurrent->ADR), 8);

			//Handle the control transfer (parse the 8-byte SETUP command and figure out what to do)
            USBCtrlTrfSetupHandler();
        }
        else
        {
			//Handle the DATA transfer
            USBCtrlTrfOutHandler();
        }
    }
    else if((USTATcopy.Val & USTAT_EP0_PP_MASK) == USTAT_EP0_IN)
    {
		//Otherwise the transmission was and EP0 IN
		//  so take care of the IN transfer
        USBCtrlTrfInHandler();
    }

}//end USBCtrlEPService

/********************************************************************
 * Function:        void USBCtrlTrfSetupHandler(void)
 *
 * PreCondition:    SetupPkt buffer is loaded with valid USB Setup Data
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine is a task dispatcher and has 3 stages.
 *                  1. It initializes the control transfer state machine.
 *                  2. It calls on each of the module that may know how to
 *                     service the Setup Request from the host.
 *                     Module Example: USBD, HID, CDC, MSD, ...
 *                     A callback function, USBCBCheckOtherReq(),
 *                     is required to call other module handlers.
 *                  3. Once each of the modules has had a chance to check if
 *                     it is responsible for servicing the request, stage 3
 *                     then checks direction of the transfer to determine how
 *                     to prepare EP0 for the control transfer.
 *                     Refer to USBCtrlEPServiceComplete() for more details.
 *
 * Note:            Microchip USB Firmware has three different states for
 *                  the control transfer state machine:
 *                  1. WAIT_SETUP
 *                  2. CTRL_TRF_TX (device sends data to host through IN transactions)
 *                  3. CTRL_TRF_RX (device receives data from host through OUT transactions)
 *                  Refer to firmware manual to find out how one state
 *                  is transitioned to another.
 *
 *                  A Control Transfer is composed of many USB transactions.
 *                  When transferring data over multiple transactions,
 *                  it is important to keep track of data source, data
 *                  destination, and data count. These three parameters are
 *                  stored in pSrc,pDst, and wCount. A flag is used to
 *                  note if the data source is from const or RAM.
 *
 *******************************************************************/
static void USBCtrlTrfSetupHandler(void)
{
    //--------------------------------------------------------------------------
    //1. Re-initialize state tracking variables related to control transfers.
    //--------------------------------------------------------------------------
    shortPacketStatus = SHORT_PKT_NOT_USED;  
    USBDeferStatusStagePacket = false;
    USBDeferINDataStagePackets = false;
    USBDeferOUTDataStagePackets = false;
    BothEP0OutUOWNsSet = false;
    controlTransferState = WAIT_SETUP;

    //Abandon any previous control transfers that might have been using EP0.
    //Ordinarily, nothing actually needs abandoning, since the previous control
    //transfer would have completed successfully prior to the host sending the next
    //SETUP packet.  However, in a timeout error case, or after an EP0 STALL event,
    //one or more UOWN bits might still be set.  If so, we should clear the UOWN bits,
    //so the EP0 IN/OUT endpoints are in a known inactive state, ready for re-arming
    //by the class request handler that will be called next.
    pBDTEntryIn[0]->STAT.Val &= ~(_USIE);  
    
    pBDTEntryIn[0] = (volatile BDT_ENTRY*)(((uintptr_t)pBDTEntryIn[0]) ^ USB_NEXT_EP0_IN_PING_PONG);
    pBDTEntryIn[0]->STAT.Val &= ~(_USIE);      
    pBDTEntryIn[0] = (volatile BDT_ENTRY*)(((uintptr_t)pBDTEntryIn[0]) ^ USB_NEXT_EP0_IN_PING_PONG);
    pBDTEntryEP0OutNext->STAT.Val &= ~(_USIE);         

    inPipes[0].info.Val = 0;
    inPipes[0].wCount.Val = 0;
    outPipes[0].info.Val = 0;
    outPipes[0].wCount.Val = 0;
    

    //--------------------------------------------------------------------------
    //2. Now find out what was in the SETUP packet, and begin handling the request.
    //--------------------------------------------------------------------------
    USBCheckStdRequest();                                               //Check for standard USB "Chapter 9" requests.
    USB_NONSTANDARD_EP0_REQUEST_HANDLER(EVENT_EP0_REQUEST,0,0); //Check for USB device class specific requests


    //--------------------------------------------------------------------------
    //3. Re-arm EP0 IN and EP0 OUT endpoints, based on the control transfer in 
    //   progress.  If one of the above handlers (in step 2) knew how to process
    //   the request, it will have set one of the inPipes[0].info.bits.busy or
    //   outPipes[0].info.bits.busy flags = 1.  This lets the
    //   USBCtrlEPServiceComplete() function know how and which endpoints to 
    //   arm.  If both info.bits.busy flags are = 0, then no one knew how to
    //   process the request.  In this case, the default behavior will be to
    //   perform protocol STALL on EP0.
    //-------------------------------------------------------------------------- 
    USBCtrlEPServiceComplete();
}//end USBCtrlTrfSetupHandler


/******************************************************************************
 * Function:        void USBCtrlTrfOutHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine handles an OUT transaction according to
 *                  which control transfer state is currently active.
 *
 * Note:            Note that if the the control transfer was from
 *                  host to device, the session owner should be notified
 *                  at the end of each OUT transaction to service the
 *                  received data.
 *
 *****************************************************************************/
static void USBCtrlTrfOutHandler(void)
{
    if(controlTransferState == CTRL_TRF_RX)
    {
        USBCtrlTrfRxService();	//Copies the newly received data into the appropriate buffer and configures EP0 OUT for next transaction.
    }
    else //In this case the last OUT transaction must have been a status stage of a CTRL_TRF_TX (<setup><in><in>...<OUT>  <-- this last OUT just occurred as the status stage)
    {
        //If the status stage is complete, this means we are done with the 
        //control transfer.  Go back to the idle "WAIT_SETUP" state.
        controlTransferState = WAIT_SETUP;

        //Prepare EP0 OUT for the next SETUP transaction, however, it may have
        //already been prepared if ping-pong buffering was enabled on EP0 OUT,
        //and the last control transfer was of direction: device to host, see
        //USBCtrlEPServiceComplete().  If it was already prepared, do not want
        //to do anything to the BDT.
        if(BothEP0OutUOWNsSet == false)
        {
            pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
            pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&SetupPkt);
            pBDTEntryEP0OutNext->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED)|_BSTALL;
            pBDTEntryEP0OutNext->STAT.Val |= _USIE;
        }
        else
        {
                BothEP0OutUOWNsSet = false;
        }
    }
}

/******************************************************************************
 * Function:        void USBCtrlTrfInHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine handles an IN transaction according to
 *                  which control transfer state is currently active.
 *
 * Note:            A Set Address Request must not change the actual address
 *                  of the device until the completion of the control
 *                  transfer. The end of the control transfer for Set Address
 *                  Request is an IN transaction. Therefore it is necessary
 *                  to service this unique situation when the condition is
 *                  right. Macro mUSBCheckAdrPendingState is defined in
 *                  usb9.h and its function is to specifically service this
 *                  event.
 *****************************************************************************/
static void USBCtrlTrfInHandler(void)
{
    uint8_t lastDTS;

    lastDTS = pBDTEntryIn[0]->STAT.DTS;

    //switch to the next ping pong buffer
    pBDTEntryIn[0] = (volatile BDT_ENTRY*)(((uintptr_t)pBDTEntryIn[0]) ^ USB_NEXT_EP0_IN_PING_PONG);

    //Must check if in ADR_PENDING_STATE.  If so, we need to update the address
    //now, since the IN status stage of the (set address) control transfer has 
    //evidently completed successfully.
    if(USBDeviceState == ADR_PENDING_STATE)
    {
        U1ADDR = (SetupPkt.bDevADR & 0x7F);
        if(U1ADDR != 0u)
        {
            USBDeviceState=ADDRESS_STATE;
        }
        else
        {
            USBDeviceState=DEFAULT_STATE;
        }
    }//end if


    if(controlTransferState == CTRL_TRF_TX)
    {
        pBDTEntryIn[0]->ADR = ConvertToPhysicalAddress(CtrlTrfData);
        USBCtrlTrfTxService();

        //Check if we have already sent a short packet.  If so, configure
        //the endpoint to STALL in response to any further IN tokens (in the
        //case that the host erroneously tries to receive more data than it
        //should).
        if(shortPacketStatus == SHORT_PKT_SENT)
        {
            // If a short packet has been sent, don't want to send any more,
            // stall next time if host is still trying to read.
            pBDTEntryIn[0]->STAT.Val = _BSTALL;
            pBDTEntryIn[0]->STAT.Val |= _USIE;
        }
        else
        {
            if(lastDTS == 0)
            {
                pBDTEntryIn[0]->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
                pBDTEntryIn[0]->STAT.Val |= _USIE;
            }
            else
            {
                pBDTEntryIn[0]->STAT.Val = _DAT0|(_DTSEN & _DTS_CHECKING_ENABLED);
                pBDTEntryIn[0]->STAT.Val |= _USIE;
            }
        }//end if(...)else
    }
	else // must have been a CTRL_TRF_RX status stage IN packet (<setup><out><out>...<IN>  <-- this last IN just occurred as the status stage)
	{
        //if someone is still expecting data from the control transfer
        //  then make sure to terminate that request and let them know that
        //  they are done
        if(outPipes[0].info.bits.busy == 1)
        {
            if(outPipes[0].pFunc != NULL)
            {
                outPipes[0].pFunc();
            }
            outPipes[0].info.bits.busy = 0;
        }
    	
        controlTransferState = WAIT_SETUP;
        //Don't need to arm EP0 OUT here.  It was already armed by the last <out> that
        //got processed by the USBCtrlTrfRxService() handler.
	}	

}


/********************************************************************
 * Function:        void USBCheckStdRequest(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine checks the setup data packet to see
 *                  if it knows how to handle it
 *
 * Note:            None
 *******************************************************************/
static void USBCheckStdRequest(void)
{
    if(SetupPkt.RequestType != USB_SETUP_TYPE_STANDARD_BITFIELD) return;

    switch(SetupPkt.bRequest)
    {
        case USB_REQUEST_SET_ADDRESS:
            inPipes[0].info.bits.busy = 1;            // This will generate a zero length packet
            USBDeviceState = ADR_PENDING_STATE;       // Update state only
            /* See USBCtrlTrfInHandler() for the next step */
            break;
        case USB_REQUEST_GET_DESCRIPTOR:
            USBStdGetDscHandler();
            break;
        case USB_REQUEST_SET_CONFIGURATION:
            USBStdSetCfgHandler();
            break;
        case USB_REQUEST_GET_CONFIGURATION:
            inPipes[0].pSrc.bRam = (uint8_t*)&USBActiveConfiguration;         // Set Source
            inPipes[0].info.bits.ctrl_trf_mem = USB_EP0_RAM;               // Set memory type
            inPipes[0].wCount.v[0] = 1;                         // Set data count
            inPipes[0].info.bits.busy = 1;
            break;
        case USB_REQUEST_GET_STATUS:
            USBStdGetStatusHandler();
            break;
        case USB_REQUEST_CLEAR_FEATURE:
        case USB_REQUEST_SET_FEATURE:
            USBStdFeatureReqHandler();
            break;
        case USB_REQUEST_GET_INTERFACE:
            inPipes[0].pSrc.bRam = (uint8_t*)&USBAlternateInterface[SetupPkt.bIntfID];  // Set source
            inPipes[0].info.bits.ctrl_trf_mem = USB_EP0_RAM;               // Set memory type
            inPipes[0].wCount.v[0] = 1;                         // Set data count
            inPipes[0].info.bits.busy = 1;
            break;
        case USB_REQUEST_SET_INTERFACE:
            inPipes[0].info.bits.busy = 1;
            USBAlternateInterface[SetupPkt.bIntfID] = SetupPkt.bAltID;
            break;
        case USB_REQUEST_SET_DESCRIPTOR:
            USB_SET_DESCRIPTOR_HANDLER(EVENT_SET_DESCRIPTOR,0,0);
            break;
        case USB_REQUEST_SYNCH_FRAME:
        default:
            break;
    }//end switch
}//end USBCheckStdRequest

/********************************************************************
 * Function:        void USBStdFeatureReqHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Can alter BDT entries.  Can also modify USB stack
 *                  Maintained variables.
 *
 * Side Effects:    None
 *
 * Overview:        This routine handles the standard SET & CLEAR
 *                  FEATURES requests
 *
 * Note:            This is a private function, intended for internal 
 *                  use by the USB stack, when processing SET/CLEAR
 *                  feature requests.  
 *******************************************************************/
static void USBStdFeatureReqHandler(void)
{
    BDT_ENTRY *p;
    EP_STATUS current_ep_data;
    #if defined(__C32__)
        uint32_t* pUEP;
    #else
        unsigned char* pUEP;             
    #endif
    

    #ifdef	USB_SUPPORT_OTG
    //Check for USB On-The-Go (OTG) specific requests
    if ((SetupPkt.bFeature == OTG_FEATURE_B_HNP_ENABLE)&&
        (SetupPkt.Recipient == USB_SETUP_RECIPIENT_DEVICE_BITFIELD))
    {  
        inPipes[0].info.bits.busy = 1;
        if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
            USBOTGEnableHnp();
        else
            USBOTGDisableHnp();
    }

    if ((SetupPkt.bFeature == OTG_FEATURE_A_HNP_SUPPORT)&&
        (SetupPkt.Recipient == USB_SETUP_RECIPIENT_DEVICE_BITFIELD))
    {
        inPipes[0].info.bits.busy = 1;
        if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
            USBOTGEnableSupportHnp();
        else
            USBOTGDisableSupportHnp();
    }

    if ((SetupPkt.bFeature == OTG_FEATURE_A_ALT_HNP_SUPPORT)&&
        (SetupPkt.Recipient == USB_SETUP_RECIPIENT_DEVICE_BITFIELD))
    {
        inPipes[0].info.bits.busy = 1;
        if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
            USBOTGEnableAltHnp();
        else
            USBOTGDisableAltHnp();
    }
    #endif   //#ifdef USB_SUPPORT_OTG 

    //Check if the host sent a valid SET or CLEAR feature (remote wakeup) request.
    if((SetupPkt.bFeature == USB_FEATURE_DEVICE_REMOTE_WAKEUP)&&
       (SetupPkt.Recipient == USB_SETUP_RECIPIENT_DEVICE_BITFIELD))
    {
        inPipes[0].info.bits.busy = 1;
        if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
            RemoteWakeup = true;
        else
            RemoteWakeup = false;
    }//end if

    //Check if the host sent a valid SET or CLEAR endpoint halt request.
    if((SetupPkt.bFeature == USB_FEATURE_ENDPOINT_HALT)&&
       (SetupPkt.Recipient == USB_SETUP_RECIPIENT_ENDPOINT_BITFIELD)&&
       (SetupPkt.EPNum != 0) && (SetupPkt.EPNum <= USB_MAX_EP_NUMBER)&&
       (USBDeviceState == CONFIGURED_STATE))
    {
		//The request was valid.  Take control of the control transfer and
		//perform the host requested action.
		inPipes[0].info.bits.busy = 1;

        //Fetch a pointer to the BDT that the host wants to SET/CLEAR halt on.
        if(SetupPkt.EPDir == OUT_FROM_HOST)
        {
            p = (BDT_ENTRY*)pBDTEntryOut[SetupPkt.EPNum];
            current_ep_data.Val = ep_data_out[SetupPkt.EPNum].Val;
        }
        else
        {
            p = (BDT_ENTRY*)pBDTEntryIn[SetupPkt.EPNum];
            current_ep_data.Val = ep_data_in[SetupPkt.EPNum].Val;
        }

        //If ping pong buffering is enabled on the requested endpoint, need 
        //to point to the one that is the active BDT entry which the SIE will 
        //use for the next attempted transaction on that EP number.
        #if (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0) || (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG)   
            if(current_ep_data.bits.ping_pong_state == 0) //Check if even
            {
                p = (BDT_ENTRY*)(((uintptr_t)p) & (~USB_NEXT_PING_PONG));
            }
            else //else must have been odd
            {
                p = (BDT_ENTRY*)(((uintptr_t)p) | USB_NEXT_PING_PONG);
            }
        #endif
        
        //Update the BDT pointers with the new, next entry based on the feature
        //  request
        if(SetupPkt.EPDir == OUT_FROM_HOST)
        {
            pBDTEntryOut[SetupPkt.EPNum] = (volatile BDT_ENTRY *)p;
        }
        else
        {
            pBDTEntryIn[SetupPkt.EPNum] = (volatile BDT_ENTRY *)p;
        }

		//Check if it was a SET_FEATURE endpoint halt request
        if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
        {
            if(p->STAT.UOWN == 1)
            {
                //Mark that we are terminating this transfer and that the user
                //  needs to be notified later
                if(SetupPkt.EPDir == OUT_FROM_HOST)
                {
                    ep_data_out[SetupPkt.EPNum].bits.transfer_terminated = 1;
                }
                else
                {
                    ep_data_in[SetupPkt.EPNum].bits.transfer_terminated = 1;
                }
            }

			//Then STALL the endpoint
            p->STAT.Val |= _BSTALL;
            p->STAT.Val |= _USIE;
        }//if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
        else
        {
			//Else the request must have been a CLEAR_FEATURE endpoint halt.
            #if (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0) || (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG)   
                //toggle over the to the non-active BDT
                p = (BDT_ENTRY*)(((uintptr_t)p) ^ USB_NEXT_PING_PONG);  

                if(p->STAT.UOWN == 1)
                {
                    //Clear UOWN and set DTS state so it will be correct the next time
                    //the application firmware uses USBTransferOnePacket() on the EP.
                    p->STAT.Val &= (~_USIE);    //Clear UOWN bit
                    p->STAT.Val |= _DAT1;       //Set DTS to DATA1
                    USB_TRANSFER_TERMINATED_HANDLER(EVENT_TRANSFER_TERMINATED,p,sizeof(p));
                }
                else
                {
                    //UOWN already clear, but still need to set DTS to DATA1     
					p->STAT.Val |= _DAT1;
                }

                //toggle back to the active BDT (the one the SIE is currently looking at
                //and will use for the next successful transaction to take place on the EP
                p = (BDT_ENTRY*)(((uintptr_t)p) ^ USB_NEXT_PING_PONG);
                
                //Check if we are currently terminating, or have previously terminated
                //a transaction on the given endpoint.  If so, need to clear UOWN,
                //set DTS to the proper state, and call the application callback
                //function.
                if((current_ep_data.bits.transfer_terminated != 0) || (p->STAT.UOWN == 1))
                {
                    if(SetupPkt.EPDir == OUT_FROM_HOST)
                    {
                        ep_data_out[SetupPkt.EPNum].bits.transfer_terminated = 0;
                    }
                    else
                    {
                        ep_data_in[SetupPkt.EPNum].bits.transfer_terminated = 0;
                    }
                    //clear UOWN, clear DTS to DATA0, and finally remove the STALL condition     
                    p->STAT.Val &= ~(_USIE | _DAT1 | _BSTALL);  
                    //Call the application event handler callback function, so it can 
					//decide if the endpoint should get re-armed again or not.
                    USB_TRANSFER_TERMINATED_HANDLER(EVENT_TRANSFER_TERMINATED,p,sizeof(p));
                }
                else
                {
                    //clear UOWN, clear DTS to DATA0, and finally remove the STALL condition     
                    p->STAT.Val &= ~(_USIE | _DAT1 | _BSTALL); 
                } 
            #else //else we must not be using ping-pong buffering on the requested endpoint
                //Check if we need to call the user transfer terminated event callback function.
                //We should call the callback, if the endpoint was previously terminated,
                //or the endpoint is currently armed, and the host is performing clear
                //endpoint halt, even though the endpoint wasn't stalled.
                if((current_ep_data.bits.transfer_terminated != 0) || (p->STAT.UOWN == 1))
                {
                    //We are going to call the user transfer terminated callback.
                    //Clear the flag so we know we took care of it and don't need
                    //to call it again later.
                    if(SetupPkt.EPDir == OUT_FROM_HOST)
                    {
                        ep_data_out[SetupPkt.EPNum].bits.transfer_terminated = 0;
                    }
                    else
                    {
                        ep_data_in[SetupPkt.EPNum].bits.transfer_terminated = 0;
                    }
 
                    //Clear UOWN and remove the STALL condition.   
                    //  In this case we also need to set the DTS bit to 1 so that
                    //  it toggles to DATA0 the next time the application firmware
                    //  calls USBTransferOnePacket() (or equivalent macro).  
                    p->STAT.Val &= ~(_USIE | _BSTALL);  
                    p->STAT.Val |= _DAT1;
                    //Let the application firmware know a transaction just
                    //got terminated by the host, and that it is now free to
                    //re-arm the endpoint or do other tasks if desired.                                        
                    USB_TRANSFER_TERMINATED_HANDLER(EVENT_TRANSFER_TERMINATED,p,sizeof(p));
                }
                else
                {
                    //Clear UOWN and remove the STALL condition.   
                    //  In this case we also need to set the DTS bit to 1 so that
                    //  it toggles to DATA0 the next time the application firmware
                    //  calls USBTransferOnePacket() (or equivalent macro).  
                    p->STAT.Val &= ~(_USIE | _BSTALL);  
                    p->STAT.Val |= _DAT1;
                } 
            #endif //end of #if (USB_PING_PONG_MODE == USB_PING_PONG__ALL_BUT_EP0) || (USB_PING_PONG_MODE == USB_PING_PONG__FULL_PING_PONG)   
            
			//Get a pointer to the appropriate UEPn register
            #if defined(__C32__)
                pUEP = (uint32_t*)(&U1EP0);
                pUEP += (SetupPkt.EPNum*4);
            #else
                pUEP = (unsigned char*)(&U1EP0+SetupPkt.EPNum);
            #endif

			//Clear the STALL bit in the UEP register
            *pUEP &= ~UEP_STALL;            
        }//end if(SetupPkt.bRequest == USB_REQUEST_SET_FEATURE)
    }//end if (lots of checks for set/clear endpoint halt)
}//end USBStdFeatureReqHandler




/**************************************************************************
    Function:
        void USBIncrement1msInternalTimers(void)

    Description:
        This function increments internal 1ms time base counters, which are
        useful for application code (that can use a 1ms time base/counter), and
        for certain USB event timing specific purposes.

        In USB full speed applications, the application code does not need to (and should
        not) explicitly call this function, as the USBDeviceTasks() function will
        automatically call this function whenever a 1ms time interval has elapsed
        (assuming the code is calling USBDeviceTasks() frequently enough in USB_POLLING
        mode, or that USB interrupts aren't being masked for more than 1ms at a time
        in USB_INTERRUPT mode).

        In USB low speed applications, the application firmware is responsible for
        periodically calling this function at a ~1ms rate.  This can be done using
        a general purpose microcontroller timer set to interrupt every 1ms for example.
        If the low speed application code does not call this function, the internal timers
        will not increment, and the USBGet1msTickCount() API function will not be available.
        Additionally, certain USB stack operations (like control transfer timeouts)
        may be unavailable.

    Precondition:
        This function should be called only after USBDeviceInit() has been
        called (at least once at the start of the application).  Ordinarily,
        application code should never call this function, unless it is a low speed
        USB device.

    Parameters:
        None

    Return Values:
        None

    Remarks:
        This function does not need to be called during USB suspend conditions, when
        the USB module/stack is disabled, or when the USB cable is detached from the host.
  ***************************************************************************/
void USBIncrement1msInternalTimers(void)
{
    #if(USB_SPEED_OPTION == USB_LOW_SPEED)
        #warning "For low speed USB applications, read the function comments for the USBIncrement1msInternalTimers() function, and implement code to call this function periodically."
    #endif

    //Increment timekeeping 1ms tick counters.  Useful for other APIs/code
    //that needs a 1ms time base that is active during USB non-suspended operation.
    USB1msTickCount++;
    if(USBIsBusSuspended() == false)
    {
        USBTicksSinceSuspendEnd++;
        //Check for 8-bit wraparound.  If so, force it to saturate at 255.
        if(USBTicksSinceSuspendEnd == 0)
        {
            USBTicksSinceSuspendEnd = 255;
        }
    }
}




/**************************************************************************
    Function:
        uint32_t USBGet1msTickCount(void)

    Description:
        This function retrieves a 32-bit unsigned integer that normally increments by
        one every one millisecond.  The count value starts from zero when the
        USBDeviceInit() function is first called.  See the remarks section for
        details on special circumstances where the tick count will not increment.

    Precondition:
        This function should be called only after USBDeviceInit() has been
        called (at least once at the start of the application).

    Parameters:
        None

    Return Values:
        uint32_t representing the approximate millisecond count, since the time the
        USBDeviceInit() function was first called.

    Remarks:
        On 8-bit USB full speed devices, the internal counter is incremented on
        every SOF packet detected.  Therefore, it will not increment during suspend
        or when the USB cable is detached.  However, on 16-bit devices, the T1MSECIF
        hardware interrupt source is used to increment the internal counter.  Therefore,
        on 16-bit devices, the count continue to increment during USB suspend or
        detach events, so long as the application code has not put the microcontroller
        to sleep during these events, and the application firmware is regularly
        calling the USBDeviceTasks() function (or allowing it to execute, if using
        USB_INTERRUPT mode operation).

        In USB low speed applications, the host does not broadcast SOF packets to
        the device, so the application firmware becomes responsible for calling
        USBIncrement1msInternalTimers() periodically (ex: from a general purpose
        timer interrupt handler), or else the returned value from this function will
        not increment.
        
        Prior to calling USBDeviceInit() for the first time the returned value will
        be unpredictable.

        This function is USB_INTERRUPT mode safe and may be called from main loop
        code without risk of retrieving a partially updated 32-bit number.

        However, this value only increments when the USBDeviceTasks() function is allowed
        to execute.  If USB_INTERRUPT mode is used, it is allowable to block on this
        function.  If however USB_POLLING mode is used, one must not block on this
        function without also calling USBDeviceTasks() continuously for the blocking
        duration (since the USB stack must still be allowed to execute, and the USB
        stack is also responsible for updating the tick counter internally).

        If the application is operating in USB_POLLING mode, this function should
        only be called from the main loop context, and not from an interrupt handler,
        as the returned value could be incorrect, if the main loop context code was in
        the process of updating the internal count at the moment of the interrupt event.
   ***************************************************************************/
uint32_t USBGet1msTickCount(void)
{
    #if defined (USB_INTERRUPT)
        uint32_t localContextValue;

        //Repeatedly read the interrupt context variable, until we get a stable/unchanging
        //value.  This ensures that the complete 32-bit value got read without
        //getting interrupted in between bytes.
        do
        {
            localContextValue = USB1msTickCount;
        }while(localContextValue != USB1msTickCount);

        return localContextValue;    
    
    #else
        return USB1msTickCount;
    #endif
}






/** EOF USBDevice.c *****************************************************/



// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright 2015 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/
//DOM-IGNORE-END

/********************************************************************
 Change History:
  Rev    Description
  ----   -----------
  2.3    Deprecated the mUSBUSARTIsTxTrfReady() macro.  It is 
         replaced by the USBUSARTIsTxTrfReady() function.

  2.6    Minor definition changes

  2.6a   No Changes

  2.7    Fixed error in the part support list of the variables section
         where the address of the CDC variables are defined.  The 
         PIC18F2553 was incorrectly named PIC18F2453 and the PIC18F4558
         was incorrectly named PIC18F4458.

         http://www.microchip.com/forums/fb.aspx?m=487397

  2.8    Minor change to CDCInitEP() to enhance ruggedness in
         multi0-threaded usage scenarios.
  
  2.9b   Updated to implement optional support for DTS reporting.

********************************************************************/

/** I N C L U D E S **********************************************************/
#include "system.h"
#include "usb.h"
#include "usb_device_cdc.h"

#ifdef USB_USE_CDC

#ifndef FIXED_ADDRESS_MEMORY
    #define IN_DATA_BUFFER_ADDRESS_TAG
    #define OUT_DATA_BUFFER_ADDRESS_TAG
    #define CONTROL_BUFFER_ADDRESS_TAG
#endif

#if !defined(IN_DATA_BUFFER_ADDRESS_TAG) || !defined(OUT_DATA_BUFFER_ADDRESS_TAG) || !defined(CONTROL_BUFFER_ADDRESS_TAG)
    #error "One of the fixed memory address definitions is not defined.  Please define the required address tags for the required buffers."
#endif

/** V A R I A B L E S ********************************************************/
volatile unsigned char cdc_data_tx[CDC_DATA_IN_EP_SIZE] IN_DATA_BUFFER_ADDRESS_TAG;
volatile unsigned char cdc_data_rx[CDC_DATA_OUT_EP_SIZE] OUT_DATA_BUFFER_ADDRESS_TAG;

typedef union
{
    LINE_CODING lineCoding;
    CDC_NOTICE cdcNotice;
} CONTROL_BUFFER;

//static CONTROL_BUFFER controlBuffer CONTROL_BUFFER_ADDRESS_TAG;

LINE_CODING line_coding;    // Buffer to store line coding information
CDC_NOTICE cdc_notice;

#if defined(USB_CDC_SUPPORT_DSR_REPORTING)
    SERIAL_STATE_NOTIFICATION SerialStatePacket;
#endif

uint8_t cdc_rx_len;            // total rx length
uint8_t cdc_trf_state;         // States are defined cdc.h
POINTER pCDCSrc;            // Dedicated source pointer
POINTER pCDCDst;            // Dedicated destination pointer
uint8_t cdc_tx_len;            // total tx length
uint8_t cdc_mem_type;          // _ROM, _RAM

USB_HANDLE CDCDataOutHandle;
USB_HANDLE CDCDataInHandle;


CONTROL_SIGNAL_BITMAP control_signal_bitmap;
uint32_t BaudRateGen;			// BRG value calculated from baud rate

#if defined(USB_CDC_SUPPORT_DSR_REPORTING)
    BM_SERIAL_STATE SerialStateBitmap;
    BM_SERIAL_STATE OldSerialStateBitmap;
    USB_HANDLE CDCNotificationInHandle;
#endif

/**************************************************************************
  SEND_ENCAPSULATED_COMMAND and GET_ENCAPSULATED_RESPONSE are required
  requests according to the CDC specification.
  However, it is not really being used here, therefore a dummy buffer is
  used for conformance.
 **************************************************************************/
#define dummy_length    0x08
uint8_t dummy_encapsulated_cmd_response[dummy_length];

#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
CTRL_TRF_RETURN USB_CDC_SET_LINE_CODING_HANDLER(CTRL_TRF_PARAMS);
#endif

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void USBCDCSetLineCoding(void);

/** D E C L A R A T I O N S **************************************************/
//#pragma code

/** C L A S S  S P E C I F I C  R E Q ****************************************/
/******************************************************************************
 	Function:
 		void USBCheckCDCRequest(void)
 
 	Description:
 		This routine checks the most recently received SETUP data packet to 
 		see if the request is specific to the CDC class.  If the request was
 		a CDC specific request, this function will take care of handling the
 		request and responding appropriately.
 		
 	PreCondition:
 		This function should only be called after a control transfer SETUP
 		packet has arrived from the host.

	Parameters:
		None
		
	Return Values:
		None
		
	Remarks:
		This function does not change status or do anything if the SETUP packet
		did not contain a CDC class specific request.		 
  *****************************************************************************/
void USBCheckCDCRequest(void)
{
    /*
     * If request recipient is not an interface then return
     */
    if(SetupPkt.Recipient != USB_SETUP_RECIPIENT_INTERFACE_BITFIELD) return;

    /*
     * If request type is not class-specific then return
     */
    if(SetupPkt.RequestType != USB_SETUP_TYPE_CLASS_BITFIELD) return;

    /*
     * Interface ID must match interface numbers associated with
     * CDC class, else return
     */
    if((SetupPkt.bIntfID != CDC_COMM_INTF_ID)&&
       (SetupPkt.bIntfID != CDC_DATA_INTF_ID)) return;
    
    switch(SetupPkt.bRequest)
    {
        //****** These commands are required ******//
        case SEND_ENCAPSULATED_COMMAND:
         //send the packet
            inPipes[0].pSrc.bRam = (uint8_t*)&dummy_encapsulated_cmd_response;
            inPipes[0].wCount.Val = dummy_length;
            inPipes[0].info.bits.ctrl_trf_mem = USB_EP0_RAM;
            inPipes[0].info.bits.busy = 1;
            break;
        case GET_ENCAPSULATED_RESPONSE:
            // Populate dummy_encapsulated_cmd_response first.
            inPipes[0].pSrc.bRam = (uint8_t*)&dummy_encapsulated_cmd_response;
            inPipes[0].info.bits.busy = 1;
            break;
        //****** End of required commands ******//

        #if defined(USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1)
        case SET_LINE_CODING:
            outPipes[0].wCount.Val = SetupPkt.wLength;
            outPipes[0].pDst.bRam = (uint8_t*)LINE_CODING_TARGET;
            outPipes[0].pFunc = LINE_CODING_PFUNC;
            outPipes[0].info.bits.busy = 1;
            break;
            
        case GET_LINE_CODING:
            USBEP0SendRAMPtr(
                (uint8_t*)&line_coding,
                LINE_CODING_LENGTH,
                USB_EP0_INCLUDE_ZERO);
            break;

        case SET_CONTROL_LINE_STATE:
            control_signal_bitmap._byte = (uint8_t)SetupPkt.wValue;
            //------------------------------------------------------------------            
            //One way to control the RTS pin is to allow the USB host to decide the value
            //that should be output on the RTS pin.  Although RTS and CTS pin functions
            //are technically intended for UART hardware based flow control, some legacy
            //UART devices use the RTS pin like a "general purpose" output pin 
            //from the PC host.  In this usage model, the RTS pin is not related
            //to flow control for RX/TX.
            //In this scenario, the USB host would want to be able to control the RTS
            //pin, and the below line of code should be uncommented.
            //However, if the intention is to implement true RTS/CTS flow control
            //for the RX/TX pair, then this application firmware should override
            //the USB host's setting for RTS, and instead generate a real RTS signal,
            //based on the amount of remaining buffer space available for the 
            //actual hardware UART of this microcontroller.  In this case, the 
            //below code should be left commented out, but instead RTS should be 
            //controlled in the application firmware responsible for operating the 
            //hardware UART of this microcontroller.
            //---------            
            //CONFIGURE_RTS(control_signal_bitmap.CARRIER_CONTROL);  
            //------------------------------------------------------------------            
            
            #if defined(USB_CDC_SUPPORT_DTR_SIGNALING)
                if(control_signal_bitmap.DTE_PRESENT == 1)
                {
                    UART_DTR = USB_CDC_DTR_ACTIVE_LEVEL;
                }
                else
                {
                    UART_DTR = (USB_CDC_DTR_ACTIVE_LEVEL ^ 1);
                }        
            #endif
            inPipes[0].info.bits.busy = 1;
            break;
        #endif

        #if defined(USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D2)
        case SEND_BREAK:                        // Optional
            inPipes[0].info.bits.busy = 1;
			if (SetupPkt.wValue == 0xFFFF)  //0xFFFF means send break indefinitely until a new SEND_BREAK command is received
			{
				UART_Tx = 0;       // Prepare to drive TX low (for break signaling)
				UART_TRISTx = 0;   // Make sure TX pin configured as an output
				UART_ENABLE = 0;   // Turn off USART (to relinquish TX pin control)
			}
			else if (SetupPkt.wValue == 0x0000) //0x0000 means stop sending indefinite break 
			{
    			UART_ENABLE = 1;   // turn on USART
				UART_TRISTx = 1;   // Make TX pin an input
			}
			else
			{
                //Send break signaling on the pin for (SetupPkt.wValue) milliseconds
                UART_SEND_BREAK();
			}
            break;
        #endif
        default:
            break;
    }//end switch(SetupPkt.bRequest)

}//end USBCheckCDCRequest

/** U S E R  A P I ***********************************************************/

/**************************************************************************
  Function:
        void CDCInitEP(void)
    
  Summary:
    This function initializes the CDC function driver. This function should
    be called after the SET_CONFIGURATION command (ex: within the context of
    the USBCBInitEP() function).
  Description:
    This function initializes the CDC function driver. This function sets
    the default line coding (baud rate, bit parity, number of data bits,
    and format). This function also enables the endpoints and prepares for
    the first transfer from the host.
    
    This function should be called after the SET_CONFIGURATION command.
    This is most simply done by calling this function from the
    USBCBInitEP() function.
    
    Typical Usage:
    <code>
        void USBCBInitEP(void)
        {
            CDCInitEP();
        }
    </code>
  Conditions:
    None
  Remarks:
    None                                                                   
  **************************************************************************/
void CDCInitEP(void)
{
    //Abstract line coding information
    line_coding.dwDTERate   = 19200;      // baud rate
    line_coding.bCharFormat = 0x00;             // 1 stop bit
    line_coding.bParityType = 0x00;             // None
    line_coding.bDataBits = 0x08;               // 5,6,7,8, or 16

    cdc_rx_len = 0;
    
    /*
     * Do not have to init Cnt of IN pipes here.
     * Reason:  Number of BYTEs to send to the host
     *          varies from one transaction to
     *          another. Cnt should equal the exact
     *          number of BYTEs to transmit for
     *          a given IN transaction.
     *          This number of BYTEs will only
     *          be known right before the data is
     *          sent.
     */
    USBEnableEndpoint(CDC_COMM_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(CDC_DATA_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    CDCDataOutHandle = USBRxOnePacket(CDC_DATA_EP,(uint8_t*)&cdc_data_rx,sizeof(cdc_data_rx));
    CDCDataInHandle = NULL;

    #if defined(USB_CDC_SUPPORT_DSR_REPORTING)
      	CDCNotificationInHandle = NULL;
        mInitDTSPin();  //Configure DTS as a digital input
      	SerialStateBitmap.byte = 0x00;
      	OldSerialStateBitmap.byte = !SerialStateBitmap.byte;    //To force firmware to send an initial serial state packet to the host.
        //Prepare a SerialState notification element packet (contains info like DSR state)
        SerialStatePacket.bmRequestType = 0xA1; //Always 0xA1 for this type of packet.
        SerialStatePacket.bNotification = SERIAL_STATE;
        SerialStatePacket.wValue = 0x0000;  //Always 0x0000 for this type of packet
        SerialStatePacket.wIndex = CDC_COMM_INTF_ID;  //Interface number  
        SerialStatePacket.SerialState.byte = 0x00;
        SerialStatePacket.Reserved = 0x00;
        SerialStatePacket.wLength = 0x02;   //Always 2 bytes for this type of packet    
        CDCNotificationHandler();
  	#endif
  	
  	#if defined(USB_CDC_SUPPORT_DTR_SIGNALING)
  	    mInitDTRPin();
  	#endif
  	
  	#if defined(USB_CDC_SUPPORT_HARDWARE_FLOW_CONTROL)
  	    mInitRTSPin();
  	    mInitCTSPin();
  	#endif
    
    cdc_trf_state = CDC_TX_READY;
}//end CDCInitEP


/**************************************************************************
  Function: void CDCNotificationHandler(void)
  Summary: Checks for changes in DSR status and reports them to the USB host.
  Description: Checks for changes in DSR pin state and reports any changes
               to the USB host. 
  Conditions: CDCInitEP() must have been called previously, prior to calling
              CDCNotificationHandler() for the first time.
  Remarks:
    This function is only implemented and needed when the 
    USB_CDC_SUPPORT_DSR_REPORTING option has been enabled.  If the function is
    enabled, it should be called periodically to sample the DSR pin and feed
    the information to the USB host.  This can be done by calling 
    CDCNotificationHandler() by itself, or, by calling CDCTxService() which
    also calls CDCNotificationHandler() internally, when appropriate.
  **************************************************************************/
#if defined(USB_CDC_SUPPORT_DSR_REPORTING)
void CDCNotificationHandler(void)
{
    //Check the DTS I/O pin and if a state change is detected, notify the 
    //USB host by sending a serial state notification element packet.
    if(UART_DTS == USB_CDC_DSR_ACTIVE_LEVEL) //UART_DTS must be defined to be an I/O pin in the hardware profile to use the DTS feature (ex: "PORTXbits.RXY")
    {
        SerialStateBitmap.bits.DSR = 1;
    }  
    else
    {
        SerialStateBitmap.bits.DSR = 0;
    }        
    
    //If the state has changed, and the endpoint is available, send a packet to
    //notify the hUSB host of the change.
    if((SerialStateBitmap.byte != OldSerialStateBitmap.byte) && (!USBHandleBusy(CDCNotificationInHandle)))
    {
        //Copy the updated value into the USB packet buffer to send.
        SerialStatePacket.SerialState.byte = SerialStateBitmap.byte;
        //We don't need to write to the other bytes in the SerialStatePacket USB
        //buffer, since they don't change and will always be the same as our
        //initialized value.

        //Send the packet over USB to the host.
        CDCNotificationInHandle = USBTransferOnePacket(CDC_COMM_EP, IN_TO_HOST, (uint8_t*)&SerialStatePacket, sizeof(SERIAL_STATE_NOTIFICATION));
        
        //Save the old value, so we can detect changes later.
        OldSerialStateBitmap.byte = SerialStateBitmap.byte;
    }    
}//void CDCNotificationHandler(void)    
#else
    #define CDCNotificationHandler() {}
#endif


/**********************************************************************************
  Function:
    bool USBCDCEventHandler(USB_EVENT event, void *pdata, uint16_t size)
    
  Summary:
    Handles events from the USB stack, which may have an effect on the CDC 
    endpoint(s).

  Description:
    Handles events from the USB stack.  This function should be called when 
    there is a USB event that needs to be processed by the CDC driver.
    
  Conditions:
    Value of input argument 'len' should be smaller than the maximum
    endpoint size responsible for receiving bulk data from USB host for CDC
    class. Input argument 'buffer' should point to a buffer area that is
    bigger or equal to the size specified by 'len'.
  Input:
    event - the type of event that occurred
    pdata - pointer to the data that caused the event
    size - the size of the data that is pointed to by pdata
                                                                                   
  **********************************************************************************/
bool USBCDCEventHandler(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (uint16_t)event )
    {  
        case EVENT_TRANSFER_TERMINATED:
            if(pdata == CDCDataOutHandle)
            {
                CDCDataOutHandle = USBRxOnePacket(CDC_DATA_EP,(uint8_t*)&cdc_data_rx,sizeof(cdc_data_rx));
            }
            if(pdata == CDCDataInHandle)
            {
                //flush all of the data in the CDC buffer
                cdc_trf_state = CDC_TX_READY;
                cdc_tx_len = 0;
            }
            break;
        default:
            return false;
    }      
    return true;
}

/**********************************************************************************
  Function:
        uint8_t getsUSBUSART(char *buffer, uint8_t len)
    
  Summary:
    getsUSBUSART copies a string of BYTEs received through USB CDC Bulk OUT
    endpoint to a user's specified location. It is a non-blocking function.
    It does not wait for data if there is no data available. Instead it
    returns '0' to notify the caller that there is no data available.

  Description:
    getsUSBUSART copies a string of BYTEs received through USB CDC Bulk OUT
    endpoint to a user's specified location. It is a non-blocking function.
    It does not wait for data if there is no data available. Instead it
    returns '0' to notify the caller that there is no data available.
    
    Typical Usage:
    <code>
        uint8_t numBytes;
        uint8_t buffer[64]
    
        numBytes = getsUSBUSART(buffer,sizeof(buffer)); //until the buffer is free.
        if(numBytes \> 0)
        {
            //we received numBytes bytes of data and they are copied into
            //  the "buffer" variable.  We can do something with the data
            //  here.
        }
    </code>
  Conditions:
    Value of input argument 'len' should be smaller than the maximum
    endpoint size responsible for receiving bulk data from USB host for CDC
    class. Input argument 'buffer' should point to a buffer area that is
    bigger or equal to the size specified by 'len'.
  Input:
    buffer -  Pointer to where received BYTEs are to be stored
    len -     The number of BYTEs expected.
                                                                                   
  **********************************************************************************/
uint8_t getsUSBUSART(uint8_t *buffer, uint8_t len)
{
    cdc_rx_len = 0;
    
    if(!USBHandleBusy(CDCDataOutHandle))
    {
        /*
         * Adjust the expected number of BYTEs to equal
         * the actual number of BYTEs received.
         */
        if(len > USBHandleGetLength(CDCDataOutHandle))
            len = USBHandleGetLength(CDCDataOutHandle);
        
        /*
         * Copy data from dual-ram buffer to user's buffer
         */
        for(cdc_rx_len = 0; cdc_rx_len < len; cdc_rx_len++)
            buffer[cdc_rx_len] = cdc_data_rx[cdc_rx_len];

        /*
         * Prepare dual-ram buffer for next OUT transaction
         */

        CDCDataOutHandle = USBRxOnePacket(CDC_DATA_EP,(uint8_t*)&cdc_data_rx,sizeof(cdc_data_rx));

    }//end if
    
    return cdc_rx_len;
    
}//end getsUSBUSART

/******************************************************************************
  Function:
	void putUSBUSART(char *data, uint8_t length)
		
  Summary:
    putUSBUSART writes an array of data to the USB. Use this version, is
    capable of transferring 0x00 (what is typically a NULL character in any of
    the string transfer functions).

  Description:
    putUSBUSART writes an array of data to the USB. Use this version, is
    capable of transferring 0x00 (what is typically a NULL character in any of
    the string transfer functions).
    
    Typical Usage:
    <code>
        if(USBUSARTIsTxTrfReady())
        {
            char data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
            putUSBUSART(data,5);
        }
    </code>
    
    The transfer mechanism for device-to-host(put) is more flexible than
    host-to-device(get). It can handle a string of data larger than the
    maximum size of bulk IN endpoint. A state machine is used to transfer a
    \long string of data over multiple USB transactions. CDCTxService()
    must be called periodically to keep sending blocks of data to the host.

  Conditions:
    USBUSARTIsTxTrfReady() must return true. This indicates that the last
    transfer is complete and is ready to receive a new block of data. The
    string of characters pointed to by 'data' must equal to or smaller than
    255 BYTEs.

  Input:
    char *data - pointer to a RAM array of data to be transfered to the host
    uint8_t length - the number of bytes to be transfered (must be less than 255).
		
 *****************************************************************************/
void putUSBUSART(uint8_t *data, uint8_t  length)
{
    /*
     * User should have checked that cdc_trf_state is in CDC_TX_READY state
     * before calling this function.
     * As a safety precaution, this function checks the state one more time
     * to make sure it does not override any pending transactions.
     *
     * Currently it just quits the routine without reporting any errors back
     * to the user.
     *
     * Bottom line: User MUST make sure that USBUSARTIsTxTrfReady()==1
     *             before calling this function!
     * Example:
     * if(USBUSARTIsTxTrfReady())
     *     putUSBUSART(pData, Length);
     *
     * IMPORTANT: Never use the following blocking while loop to wait:
     * while(!USBUSARTIsTxTrfReady())
     *     putUSBUSART(pData, Length);
     *
     * The whole firmware framework is written based on cooperative
     * multi-tasking and a blocking code is not acceptable.
     * Use a state machine instead.
     */
    USBMaskInterrupts();
    if(cdc_trf_state == CDC_TX_READY)
    {
        mUSBUSARTTxRam((uint8_t*)data, length);     // See cdc.h
    }
    USBUnmaskInterrupts();
}//end putUSBUSART

/******************************************************************************
	Function:
		void putsUSBUSART(char *data)
		
  Summary:
    putsUSBUSART writes a string of data to the USB including the null
    character. Use this version, 'puts', to transfer data from a RAM buffer.

  Description:
    putsUSBUSART writes a string of data to the USB including the null
    character. Use this version, 'puts', to transfer data from a RAM buffer.
    
    Typical Usage:
    <code>
        if(USBUSARTIsTxTrfReady())
        {
            char data[] = "Hello World";
            putsUSBUSART(data);
        }
    </code>
    
    The transfer mechanism for device-to-host(put) is more flexible than
    host-to-device(get). It can handle a string of data larger than the
    maximum size of bulk IN endpoint. A state machine is used to transfer a
    \long string of data over multiple USB transactions. CDCTxService()
    must be called periodically to keep sending blocks of data to the host.

  Conditions:
    USBUSARTIsTxTrfReady() must return true. This indicates that the last
    transfer is complete and is ready to receive a new block of data. The
    string of characters pointed to by 'data' must equal to or smaller than
    255 BYTEs.

  Input:
    char *data -  null\-terminated string of constant data. If a
                            null character is not found, 255 BYTEs of data
                            will be transferred to the host.
		
 *****************************************************************************/
 
void putsUSBUSART(char *data)
{
    uint8_t len;
    char *pData;

    /*
     * User should have checked that cdc_trf_state is in CDC_TX_READY state
     * before calling this function.
     * As a safety precaution, this function checks the state one more time
     * to make sure it does not override any pending transactions.
     *
     * Currently it just quits the routine without reporting any errors back
     * to the user.
     *
     * Bottom line: User MUST make sure that USBUSARTIsTxTrfReady()==1
     *             before calling this function!
     * Example:
     * if(USBUSARTIsTxTrfReady())
     *     putsUSBUSART(pData, Length);
     *
     * IMPORTANT: Never use the following blocking while loop to wait:
     * while(!USBUSARTIsTxTrfReady())
     *     putsUSBUSART(pData);
     *
     * The whole firmware framework is written based on cooperative
     * multi-tasking and a blocking code is not acceptable.
     * Use a state machine instead.
     */
    USBMaskInterrupts();
    if(cdc_trf_state != CDC_TX_READY)
    {
        USBUnmaskInterrupts();
        return;
    }
    
    /*
     * While loop counts the number of BYTEs to send including the
     * null character.
     */
    len = 0;
    pData = data;
    do
    {
        len++;
        if(len == 255) break;       // Break loop once max len is reached.
    }while(*pData++);
    
    /*
     * Second piece of information (length of data to send) is ready.
     * Call mUSBUSARTTxRam to setup the transfer.
     * The actual transfer process will be handled by CDCTxService(),
     * which should be called once per Main Program loop.
     */
    mUSBUSARTTxRam((uint8_t*)data, len);     // See cdc.h
    USBUnmaskInterrupts();
}//end putsUSBUSART

/**************************************************************************
  Function:
        void putrsUSBUSART(const const char *data)
    
  Summary:
    putrsUSBUSART writes a string of data to the USB including the null
    character. Use this version, 'putrs', to transfer data literals and
    data located in program memory.

  Description:
    putrsUSBUSART writes a string of data to the USB including the null
    character. Use this version, 'putrs', to transfer data literals and
    data located in program memory.
    
    Typical Usage:
    <code>
        if(USBUSARTIsTxTrfReady())
        {
            putrsUSBUSART("Hello World");
        }
    </code>
    
    The transfer mechanism for device-to-host(put) is more flexible than
    host-to-device(get). It can handle a string of data larger than the
    maximum size of bulk IN endpoint. A state machine is used to transfer a
    \long string of data over multiple USB transactions. CDCTxService()
    must be called periodically to keep sending blocks of data to the host.

  Conditions:
    USBUSARTIsTxTrfReady() must return true. This indicates that the last
    transfer is complete and is ready to receive a new block of data. The
    string of characters pointed to by 'data' must equal to or smaller than
    255 BYTEs.

  Input:
    const const char *data -  null\-terminated string of constant data. If a
                            null character is not found, 255 uint8_ts of data
                            will be transferred to the host.
                                                                           
  **************************************************************************/
void putrsUSBUSART(const const char *data)
{
    uint8_t len;
    const const char *pData;

    /*
     * User should have checked that cdc_trf_state is in CDC_TX_READY state
     * before calling this function.
     * As a safety precaution, this function checks the state one more time
     * to make sure it does not override any pending transactions.
     *
     * Currently it just quits the routine without reporting any errors back
     * to the user.
     *
     * Bottom line: User MUST make sure that USBUSARTIsTxTrfReady()
     *             before calling this function!
     * Example:
     * if(USBUSARTIsTxTrfReady())
     *     putsUSBUSART(pData);
     *
     * IMPORTANT: Never use the following blocking while loop to wait:
     * while(cdc_trf_state != CDC_TX_READY)
     *     putsUSBUSART(pData);
     *
     * The whole firmware framework is written based on cooperative
     * multi-tasking and a blocking code is not acceptable.
     * Use a state machine instead.
     */
    USBMaskInterrupts();
    if(cdc_trf_state != CDC_TX_READY)
    {
        USBUnmaskInterrupts();
        return;
    }
    
    /*
     * While loop counts the number of BYTEs to send including the
     * null character.
     */
    len = 0;
    pData = data;
    do
    {
        len++;
        if(len == 255) break;       // Break loop once max len is reached.
    }while(*pData++);
    
    /*
     * Second piece of information (length of data to send) is ready.
     * Call mUSBUSARTTxRom to setup the transfer.
     * The actual transfer process will be handled by CDCTxService(),
     * which should be called once per Main Program loop.
     */

    mUSBUSARTTxRom((const uint8_t*)data,len); // See cdc.h
    USBUnmaskInterrupts();

}//end putrsUSBUSART

/************************************************************************
  Function:
        void CDCTxService(void)
    
  Summary:
    CDCTxService handles device-to-host transaction(s). This function
    should be called once per Main Program loop after the device reaches
    the configured state.
  Description:
    CDCTxService handles device-to-host transaction(s). This function
    should be called once per Main Program loop after the device reaches
    the configured state (after the CDCIniEP() function has already executed).
    This function is needed, in order to advance the internal software state 
    machine that takes care of sending multiple transactions worth of IN USB
    data to the host, associated with CDC serial data.  Failure to call 
    CDCTxService() periodically will prevent data from being sent to the
    USB host, over the CDC serial data interface.
    
    Typical Usage:
    <code>
    void main(void)
    {
        USBDeviceInit();
        while(1)
        {
            USBDeviceTasks();
            if((USBGetDeviceState() \< CONFIGURED_STATE) ||
               (USBIsDeviceSuspended() == true))
            {
                //Either the device is not configured or we are suspended
                //  so we don't want to do execute any application code
                continue;   //go back to the top of the while loop
            }
            else
            {
                //Keep trying to send data to the PC as required
                CDCTxService();
    
                //Run application code.
                UserApplication();
            }
        }
    }
    </code>
  Conditions:
    CDCIniEP() function should have already executed/the device should be
    in the CONFIGURED_STATE.
  Remarks:
    None                                                                 
  ************************************************************************/
 
void CDCTxService(void)
{
    uint8_t byte_to_send;
    uint8_t i;
    
    USBMaskInterrupts();
    
    CDCNotificationHandler();
    
    if(USBHandleBusy(CDCDataInHandle)) 
    {
        USBUnmaskInterrupts();
        return;
    }

    /*
     * Completing stage is necessary while [ mCDCUSartTxIsBusy()==1 ].
     * By having this stage, user can always check cdc_trf_state,
     * and not having to call mCDCUsartTxIsBusy() directly.
     */
    if(cdc_trf_state == CDC_TX_COMPLETING)
        cdc_trf_state = CDC_TX_READY;
    
    /*
     * If CDC_TX_READY state, nothing to do, just return.
     */
    if(cdc_trf_state == CDC_TX_READY)
    {
        USBUnmaskInterrupts();
        return;
    }
    
    /*
     * If CDC_TX_BUSY_ZLP state, send zero length packet
     */
    if(cdc_trf_state == CDC_TX_BUSY_ZLP)
    {
        CDCDataInHandle = USBTxOnePacket(CDC_DATA_EP,NULL,0);
        //CDC_DATA_BD_IN.CNT = 0;
        cdc_trf_state = CDC_TX_COMPLETING;
    }
    else if(cdc_trf_state == CDC_TX_BUSY)
    {
        /*
         * First, have to figure out how many byte of data to send.
         */
    	if(cdc_tx_len > sizeof(cdc_data_tx))
    	    byte_to_send = sizeof(cdc_data_tx);
    	else
    	    byte_to_send = cdc_tx_len;

        /*
         * Subtract the number of bytes just about to be sent from the total.
         */
    	cdc_tx_len = cdc_tx_len - byte_to_send;
    	  
        pCDCDst.bRam = (uint8_t*)&cdc_data_tx; // Set destination pointer
        
        i = byte_to_send;
        if(cdc_mem_type == USB_EP0_ROM)            // Determine type of memory source
        {
            while(i)
            {
                *pCDCDst.bRam = *pCDCSrc.bRom;
                pCDCDst.bRam++;
                pCDCSrc.bRom++;
                i--;
            }//end while(byte_to_send)
        }
        else
        {
            while(i)
            {
                *pCDCDst.bRam = *pCDCSrc.bRam;
                pCDCDst.bRam++;
                pCDCSrc.bRam++;
                i--;
            }
        }
        
        /*
         * Lastly, determine if a zero length packet state is necessary.
         * See explanation in USB Specification 2.0: Section 5.8.3
         */
        if(cdc_tx_len == 0)
        {
            if(byte_to_send == CDC_DATA_IN_EP_SIZE)
                cdc_trf_state = CDC_TX_BUSY_ZLP;
            else
                cdc_trf_state = CDC_TX_COMPLETING;
        }//end if(cdc_tx_len...)
        CDCDataInHandle = USBTxOnePacket(CDC_DATA_EP,(uint8_t*)&cdc_data_tx,byte_to_send);

    }//end if(cdc_tx_sate == CDC_TX_BUSY)
    
    USBUnmaskInterrupts();
}//end CDCTxService

#endif //USB_USE_CDC

/** EOF cdc.c ****************************************************************/



/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "system.h"

#include "app_device_cdc_basic.h"
#include "app_led_usb_status.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

/*******************************************************************
 * Function:        bool USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, uint16_t size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  uint16_t size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (int) event )
    {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            APP_LEDUpdateUSBStatus();

            //Call the hardware platform specific handler for suspend events for
            //possible further action (like optionally going reconfiguring the application
            //for lower power states and going to sleep during the suspend event).  This
            //would normally be done in USB compliant bus powered applications, although
            //no further processing is needed for purely self powered applications that
            //don't consume power from the host.
            SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND);
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            APP_LEDUpdateUSBStatus();

            //Call the hardware platform specific resume from suspend handler (ex: to
            //restore I/O pins to higher power states if they were changed during the 
            //preceding SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND) call at the start
            //of the suspend condition.
            SYSTEM_Initialize(SYSTEM_STATE_USB_RESUME);
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the 
             * demo code. */
            CDCInitEP();
            APP_DeviceCDCBasicDemoInitialize();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}

/*******************************************************************************
 End of File
*/





/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
void main(void)
{
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
    while(1)
    {
        SYSTEM_Tasks();

        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Application specific tasks
        APP_DeviceCDCBasicDemoTasks();

    }//end while
}//end main

/*******************************************************************************
 End of File
*/
