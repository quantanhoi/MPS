/* ========================================
 *
 * Copyright R. Mayer, h_da, FbI, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"
#include <stdio.h>          // für string-Operationen wie sprintf

/*
 * Diese Definitionen ermöglichen es, 
 * einfach Informationen auf den Bildschirm zu schreiben
 */
#define _VERSION_NR     "ver. 1.0"              //!< Version number. Please update
#define _PROJECT_NAME   "MPS_W22_Prakt_2"       //!< Project name
#define _PROCESSOR      "PSoC 5LP"              //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"              //!< Board or device type
#define _AUTHOR_        "Anne Stesi, Imo Biel"
#define _COMPANY        "Template MPS 3"

// String für die Anzeige zusammenbauen
#define _VERSTR_       (_PROJECT_NAME", "_DEVICE_NAME", "_PROCESSOR", "_VERSION_NR"\n\r"\
_AUTHOR_" ("_COMPANY"), "__DATE__" "__TIME__)

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
    cRx = UART_GetChar();       // read and copy char
}

static uint8_t fCWEW_Isr = 0;   //!< flag CW EW button isr, visible within main.c
/** 
 * Interrupt isr_CWSN for button Pin_CWSN interrupt service routine.
 *
 * @see fCWEW_Isr
 */
CY_ISR( MyIsrCWEW ) {
    /* Clear Interrupt first ! */
    Pin_CWEW_ClearInterrupt();
    fCWEW_Isr = 1;              // set flag
}
static int laufZeit = 0;
static int clkInterruptCounter = 0;
static int LED_CWEW = 0;
static int loopCountStart = 0;
static int loopCounter = 0;
/** 
 * Application clock interrupt service routine for isr_Clk
 *
 * @see fClock
 */
CY_ISR( IsrAppClk ) {
    // TODO: implementieren
    clkInterruptCounter++;
    if(clkInterruptCounter > 1000) {
        clkInterruptCounter = 0;
        laufZeit++;
        loopCountStart = 1;
    }
}


/**
 * Basisprojekt mit UART mit Interrupt, User Button mit Interrupt und Statusabfrage. 
 * Pin-I/O Einfache Eingabe mit Button, Ausgabe mit LED
 * für FreeSoC2
 * 
 * @author Ralf S. Mayer
 * @date 2022-11-13
 * @version 1.0
 */
int main(void)
{
    /* Initialize and start UART, register ISR */
    UART_Start();                       // start UART
    isr_UART_RX_StartEx( MyIsrUartRX ); // register ISR, enable itr uart

    /* Initialize and start MyIsrCWEW, register ISR */
    isr_CWEW_StartEx( MyIsrCWEW );      // register CWEW itr
    Pin_CWEW_ClearInterrupt();          // clear eventual interrupt
    isr_CWEW_ClearPending();            // clear eventual pending interrupt
    
    isr_Clk_StartEx( IsrAppClk );       // register application clock, enable isr clock, which has f = 1000hz
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART

    // Applikationsschleife
    for(;;)
    {

        /* 
         * Character aus Uart ISR abfragen 
         * Beipsiel für einfache Menuesteuerung
         * Achtung: Für UART in diesem Programm ist ein zusätzlicher FTDI USB-TTL-Adapter notwendig 
         */
        if ( cRx ) {
            char c = cRx;   // copy char
            cRx = 0;        // nicht vergessen!!! Warum?
            // +++ Menuesteuerung +++
            switch ( c ) {
                // Software reset, startet Programm neu
                case 'q':
                case 'Q':   // fallthrough
                    CySoftwareReset();
                    break;
                case 'm':   // so könnte man etwas steuern über die Konsole
                    UART_PutString( "Menu-Beispiel: Taste 'm' gedrueckt\n\r" );
                    break;
                    case 'l':
                    sprintf(buffer, "Sekunde: %d \n\r", laufZeit);
                    UART_PutString(buffer);
                    break;
                    case 'c':
                    sprintf(buffer, "Loop Counter: %d \n\r", loopCounter );
                    UART_PutString(buffer);
                    break;
                 
                // ... und so weiter ...
                default:
                    UART_PutChar( c );    // Buchstabe auf Bildschirm ausgeben ...
                                          // ... falls nicht vom Menue behandelt
                    break;
            }  // end switch          
        } // end if cRx
        //test interrupt
        if(Pin_CWEW_Read() == 0) {
            while(!Pin_CWEW_Read()) {
                    
            }
        }
        /*
         * count loops in 1 sec
         */
        // TODO
        if(loopCountStart && laufZeit < 2) {
            loopCounter++;
        }

        // Behandlung Button-Ereignis aus ISR
        if ( fCWEW_Isr ) {
            // TODO: implementieren und LED Pin_E_CW toggeln!
            if(LED_CWEW) {  
                Pin_E_CW_Write(1);      //weißE LEDs in OST_WEST ausschalten
                LED_CWEW = 0;
            }
            else {
                Pin_E_CW_Write(0);      ////weißE LEDs in OST_WEST anschalten
                LED_CWEW = 1;
            }
            fCWEW_Isr = 0;          //toggle end
        }
                
    } // end for
}

/* [] END OF FILE */
