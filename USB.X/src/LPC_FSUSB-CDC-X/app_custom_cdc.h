/* 
 * File:   app_custom_cdc.h
 * Author: vsk hs-ulm
 *
 * Created on 22. July 2014, 13:30
 */
#ifndef CUSTOM_CDC_H
#define	CUSTOM_CDC_H

//------------------------------------------- P U B L I C    P R O T O T Y P E S
void APP_CustomCDCInitialize(void);     // legacy
void APP_CustomCDCTasks(void);          // legacy ProcessIO()

void APP_USBCBSuspend(void);            // empty ;-)
void APP_USBCBWakeFromSuspend(void);    //
void APP_USBCB_SOF_Handler(void);       //
void APP_USBCBErrorHandler(void);       //
void APP_USBCBStdSetDscHandler(void);   //

//## HSU LED CTRL  I N S T R U C T I O N    D E F I N I T I O N S ##############

typedef enum {
    CID_INIT    = 0x00,         // init processor
//    CID_STOP        = 0x01,     // stop sending data
//    CID_CLOSE,
//    CID_OPEN,
//    CID_START       = 0x04,     // send data (continuous)
//    CID_SNGLSHOT    = 0x05,     // send one frame

//    CID_CHANNELS    = 0x06,     //
//    CID_SMPLINTRVL  = 0x07,     // set sampling time (in us)
//    CID_PCKSIZE     = 0x08,     // set package size (continuous)
//    CID_FRAMESIZE   = 0x09,     // set packagesize (single shot)
//    CID_RESOLUTION  = 0x0A,     // set 8bit / 16bit data

    CID_MISC        = 0x0B,     // send miscellanous info-string
    CID_MANU        = 0x0C,     // send developper info-string
    CID_DATE        = 0x0D,     // send date info-string
    CID_VERSION     = 0x0E,     // send version info-string
    CID_DEVICE      = 0x0F,     // send device identification string

//    CID_LED1_OFF    = 0x10,     // LED_1 switch off
//    CID_LED1_ON     = 0x11,     // LED_1 switch on
//    CID_LED1_TOG    = 0x13,     // LED_1 toggle
//    CID_LED1_GET    = 0x15,     // LED_1 get status
    CID_LED3_OFF    = 0x30,
    CID_LED3_ON,
    CID_LED3_TOG    = 0x33,
    CID_LED4_OFF    = 0x40,
    CID_LED4_ON,
    CID_LED4_TOG    = 0x43,
    CID_BUTTON      = 0x50,    // get button state (1 == pressed)
    CID_POTI        = 0x60,    // get analog value
    ID_MESSAGE      = 0x80,
    ID_ERROR        = 0xFF
}COMMANDS;

#endif	/* CUSTOM_CDC_H */

