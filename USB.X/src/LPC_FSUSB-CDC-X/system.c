
#include "system.h"
#include "system_config.h"
#include "app_custom_cdc.h"
#include <usb/usb.h>



#ifdef  COMPILER_MPLAB_C18                      // MCHP C18 comppiler
    void SYS_InterruptHigh();
    void SYS_InterruptLow();

    #pragma code HIGH_INTERRUPT_VECTOR = 0x08
    void High_ISR(void) {
        _asm goto SYS_InterruptHigh _endasm
    }
    #pragma code LOW_INTERRUPT_VECTOR = 0x18
    void Low_ISR(void) {
        _asm goto SYS_InterruptLow _endasm
    }
    #pragma code
    #pragma interrupt SYS_InterruptHigh
    void SYS_InterruptHigh() {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
    #if defined(USB_INTERRUPT)
        USBDeviceTasks();
    #endif
    } //This return will be a "retfie fast", since this is in a #pragma interrupt section
    #pragma interruptlow SYS_InterruptLow
    void SYS_InterruptLow() {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
    } //This return will be a "retfie", since this is in a #pragma interruptlow section


#elif defined(__XC8)                            // MCHP XC8 compiler
    void interrupt SYS_InterruptHigh() {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
    #if defined(USB_INTERRUPT)
        USBDeviceTasks();
    #endif
    } //This return will be a "retfie fast"
    void interrupt low_priority SYS_InterruptLow() {
        //Check which interrupt flag caused the interrupt.
        //Service the interrupt
        //Clear the interrupt flag
        //Etc.
    }

#else
  #error NO VALID COMPILER SELECTED !!!
#endif


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
            initCLKPLL();
            ADCON1 |= 0x0F;                 // Default all pins to digital
            mInitAllLEDs();
            mInitSwitch();
            mInitPoti();
            initADC();
            break;

        case SYSTEM_STATE_USB_SUSPEND:
            break;

        case SYSTEM_STATE_USB_RESUME:
            break;
    }
}

