/* ========================================
 *
 * Copyright R. Mayer, h_da, FbI, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>      // für string-Operationen wie sprintf

/*
 * Diese Definitionen ermöglichen es, 
 * einfach Compiler-Informationen und andere auf den Bildschirm zu schreiben
 */
#define _VERSION_NR     "ver. 1.0"      //!< Version number. Please update
#define _PROJECT_NAME   "MPS22_Prakt_5a" //!< Project name
#define _PROCESSOR      "PSoC 5LP"      //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"      //!< Board or device type
#define _AUTHOR_        "Marie O'hana, Effi Driehn"        //!< Ihr(e) Name(n)!
#define _COMPANY        "FbI Template MPS 5"

// String für die Anzeige zusammenbauen
#define _VERSTR_       (_PROJECT_NAME", "_DEVICE_NAME", "_PROCESSOR", "_VERSION_NR"\n\r"\
_AUTHOR_" ("_COMPANY"), "__DATE__" "__TIME__)

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * +++ Lösungs Template: An- und Abschalten von Teillösungen und Optionen +++ 
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#define I2C_PROJ_ON         //!< use I2C hardware
//#define I2C_SIMPLE_BLINK    //!< blink LED's  !Kommentar entfernen, wenn  implementiert!
#define READ_ADC            //!< ADC lesen    !Kommentar entfernen, wenn  implementiert!

/* +++ settings for PCF8574 Philips/NXP) 7(!)-bit address +++ */
#define I2C_PCF8574_BASE_ADDR (0x20)     //!< TODO!, ÄNDERN, FUNKTIONIERT NICHT! device base address
//probably 0b011, since VSS in connected to A2
#define I2C_PCF8574_DEV_ADDR  (0b001)    //!< TODO!ÄNDERN, FUNKTIONIERT NICHT! individual device address. !! ANPASSEN !!
#define I2C_PCF8574_ADDR      (I2C_PCF8574_BASE_ADDR | (I2C_PCF8574_DEV_ADDR)) //!< full 7-bit address




static uint8_t ADC_isr = 0;
CY_ISR( myADC_isr) {
    Pin_TIA_OUT_ClearInterrupt();
    ADC_isr = 1;
}
/* 
 * String Buffer für Anzeige am Bildschirm anlegen.
 * Auf die maximale Größe achten!
 */
#define BUFFER_SIZE 128             //!< string output buffer size for sprintf
static char buffer[BUFFER_SIZE];    //!< buffer (global) for sprintf

static char cRx = 0;                //!< character from UART, visible within main.c
/** 
 * UART RX interrupt service routine.
 *
 * Collect a characters from UART into a global input variable.
 * @see cRx
 */
CY_ISR( MyIsrUartRX ) {
    cRx = UART_GetChar();   // copy char
}

/**
 * Projekt-Template mit LED-TIA und SAR-ADC and PCF8574 8-bit I/O-Expander. 
 * 
 * @author Ralf S. Mayer
 * @date 2022-12-29
 * @version 1.0
 */
int main(void)
{
    /* +++ Initialisierung +++ */
    UART_Start();                       // start UART
    isr_UART_RX_StartEx( MyIsrUartRX ); // register and enable itr uart

    // Photo Diode ADC Initialization
    TIA_PD_Start();             // Start TIA for photo diode
    ADC_SAR_PD_Start();         // Start ADC
    // +++ TODO +++
    ADC_SAR_PD_Init();
    // !!! ADC Konversion starten, Befehl? !!!
    // TODO!  // Start ADC conversion
        
#ifdef I2C_PROJ_ON
    // +++ TODO +++

    /* Start I2C UDB Master */
    I2C_Start();
    I2C_MasterSendStart(I2C_PCF8574_ADDR,0);     //master will write data to slave using 0
    // !!! I2C starten, Befehl? !!!
    // TODO!                        // start device
#endif // I2C_PROJ_ON

    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART

    int16_t sarResult;                  // signed SAR result
    int8_t sarResult8bit;
    
#ifdef I2C_PROJ_ON
    uint8_t  sts = I2C_MSTR_NO_ERROR;    // I2C transfer status (no error)
    
    /* +++ test output for adresses +++ */
    sprintf( buffer, "PCF8574 base I2C-address:    0x%02X\n\r", I2C_PCF8574_BASE_ADDR );
    UART_PutString( buffer );
    sprintf( buffer, "PCF8574 I2C-dev-address:     0x%02X\n\r", I2C_PCF8574_DEV_ADDR );
    UART_PutString( buffer );
    sprintf( buffer, "PCF8574 I2C-address (7 bit): 0x%02X\n\r", I2C_PCF8574_ADDR );
    UART_PutString( buffer );
#endif // I2C_PROJ_ON

    /* +++ Declarationen +++ */
    uint8_t     chr = 0;            // for char von der UART

    /* +++ Applikationsschleife         +++
     * +++ wird ständig durchlaufen     +++ 
     */
    for(;;)
    {
        
#ifdef I2C_PROJ_ON
        /* +++ I2C I/O-Expander +++ */
        static uint8_t i2cByte = 0;         // warum static ?
        //sarResult = ADC_SAR_PD_GetResult16();
        //i2cByte = sarResult >> 8;                                        // ... weil nur einmal initialisiert, dann unten verändert
    #ifdef I2C_SIMPLE_BLINK             // simple blink LED's
        // blinking all LED's
        sts = I2C_MasterClearStatus();  // clear master status
        if ( sts != I2C_MSTR_NO_ERROR ) {
            UART_PutString( "I2C error clear\n\r" );
        }
        sts = I2C_MasterSendStart( I2C_PCF8574_ADDR, 0);  // send address for write
        if ( sts != I2C_MSTR_NO_ERROR ) {
            UART_PutString( "I2C error address\n\r" );
        }
        sts = I2C_MasterWriteByte(i2cByte);              // write byte
        if ( sts != I2C_MSTR_NO_ERROR ) {
            UART_PutString( "I2C error write\n\r" );
        }
        sts = I2C_MasterSendStop();                      // stop comm
        if ( sts != I2C_MSTR_NO_ERROR ) {
            UART_PutString( "I2C error stop\n\r" );
        }
        CyDelay( 100 );                 // some delay
        i2cByte = ~i2cByte;             // invert all bits for blinking
        #else  // implementieren
        /* +++ TODO +++ */
        /* eigene Werte auf I/O*/    
            i2cByte = ADC_SAR_PD_GetResult8();      //helligkeit
                    sts = I2C_MasterClearStatus();  // clear master status
            if ( sts != I2C_MSTR_NO_ERROR ) {
                UART_PutString( "I2C error clear\n\r" );
            }
            sts = I2C_MasterSendStart( I2C_PCF8574_ADDR, 0);  // send address for write
            if ( sts != I2C_MSTR_NO_ERROR ) {
                UART_PutString( "I2C error address\n\r" );
            }
            //because the data is only 8 bit long, is it better to use WriteByte instead of writeBuff here?
            sts = I2C_MasterWriteBuf(I2C_PCF8574_ADDR , &i2cByte , 1, I2C_MODE_COMPLETE_XFER);;              // write byte
            if ( sts != I2C_MSTR_NO_ERROR ) {
                UART_PutString( "I2C error write\n\r" );
            }
            sts = I2C_MasterSendStop();                      // stop comm
            if ( sts != I2C_MSTR_NO_ERROR ) {
                UART_PutString( "I2C error stop\n\r" );
            }
            CyDelay( 100 );                 // some delay
            i2cByte = ~i2cByte;             // invert all bits for blinking
            
    #endif // I2C_SIMPLE_BLINK   

#endif // I2C_PROJ_ON

#ifdef READ_ADC

    /* +++ TODO +++ */
    /* ??? wie kann man erreichen, dass hier das Ende der Konversion abgewartet wird ??? */
    // TODO!   // blocks until end of conversion
    if (ADC_SAR_PD_IsEndConversion(1)) {      //after the last conversion is finished
        /* !!! ADC-Wert in sarResult auslesen !!! */
        sarResult = ADC_SAR_PD_GetResult16();
        sarResult8bit = sarResult >> 8;
        //sarResult = ADC_SAR_PD_GetResult8();        // read SAR
        /* !!! ADC-Wert anzeigen !!! */
        sprintf( buffer, "ADC: %d\n\r", sarResult );
        UART_PutString( buffer );
//        ADC_isr = 0;
    }

#endif // READ_ADC

        /* +++ Character aus Uart, ISR abfragen +++ */
        if ( cRx ) {
            chr = cRx;                  // copy character
            cRx = 0;                    // nicht vergessen!
        }
        /* +++ Character aus Uart auswerten +++ */
        if ( chr != 0 ) {               // da kam ein Zeichen ...
            switch (chr) {              // Zeichen auswerten
                //  *** nicht verlangt ***
                case 'h':               // Help
                case 'H':               // fallthrough
                    UART_PutString( "Help:\n\r" );
                    UART_PutString( "\th,H:\tHelp\n\r" );
                    UART_PutString( "\tQ:\tSoftware Reset\n\r" );
                    break;
                //  *** nicht verlangt ***
                case 'q':               // 'q,Q' reset
                case 'Q':               // fallthrough
                    CySoftwareReset();
                    break;
                default:
                    UART_PutString( "unbekannte Eingabe <" );
                    UART_PutChar( chr );
                    UART_PutString( "> !!! \n\r" );   // Zeilenabschluss LF CR
                    
                    break;
            } // end switch
            chr = 0;                    // nicht vergessen mit ISR
        }
        
    } // end for
   
} // end main

/* [] END OF FILE */
