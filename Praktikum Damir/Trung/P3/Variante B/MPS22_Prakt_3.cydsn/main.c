/* ========================================
 *
 * Copyright R. Mayer, h_da, FbI, 
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"
#include "HAL.h"
#include <stdio.h>          // für string-Operationen wie sprintf
/*
 * Diese Definitionen ermöglichen es, 
 * einfach Informationen auf den Bildschirm zu schreiben
 */
#define _VERSION_NR     "ver. 1.1"              //!< Version number. Please update
#define _PROJECT_NAME   "MPS21_Prakt_3"         //!< Project name
#define _PROCESSOR      "PSoC 5LP"              //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"              //!< Board or device type
#define _AUTHOR_        "Jamil Boujada, Damir Maksuti"
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
//    UART_PutChar(cRx);
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
static uint32_t ms = 0;         //!< microseconds
static uint8_t  fsClock = 0;    //!< s flag
static uint32_t timer = 0;      //Aufgabe 2c
static uint16 brightness = 100;
/** 
 * Application clock interrupt service routine for isr_Clk
 *
 * @see fClock
 */
CY_ISR( IsrAppClk ) {
    // TODO: implementieren
    ms++;                     // increment ms timestamp
    if ((ms % 1000) == 0 ) {  // next 1 s reached
       fsClock = 1;                 // set flag 
       timer++;                     //Aufgabe 2c
    }    
}
void brightness_settings(u_int input){
    if(input && brightness < 1000){
        uint16 test = PWM_ReadCompare();
        brightness = brightness + 100;
        PWM_WriteCompare( brightness);
        
    }else if( brightness != 0){
        brightness = brightness - 100;
        PWM_WriteCompare(brightness - 100);
    }
}
/**
 * Basisprojekt mit UART mit Interrupt, User Button mit Interrupt und Statusabfrage. 
 * Pin-I/O Einfache Eingabe mit Button, Ausgabe mit LED
 * für FreeSoC2
 * 
 * @author Ralf S. Mayer
 * @date 2021-11-28
 * @version 1.0
 */
int main(void) {   
    /* Initialize and start UART, register ISR */
    UART_Start();                       // start UART
    isr_UART_RX_StartEx( MyIsrUartRX ); // register ISR, enable itr uart
    
    /* Initialize PWM */
    PWM_Start();                        // start PWM

    /* Initialize and start MyIsrCWEW, register ISR */
    isr_CWEW_StartEx( MyIsrCWEW );      // register CWEW itr
    Pin_CWEW_ClearInterrupt();          // clear eventual interrupt
    isr_CWEW_ClearPending();            // clear eventual pending interrupt    
    isr_Clk_StartEx( IsrAppClk );       // register application clock
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART
    
    // Applikationsschleife
    int zustand = 0;
    for(;;) {
        cRx = UART_GetChar();
        if ( fsClock ) {
            fsClock = 0;    // don't forget
            
            if(zustand == 0 && timer == 1) {
                cleanState(); // Alle rot
                zustand++;
                timer = 0;
            }           
            if(zustand == 1 && timer == 1) {               
                prepareNorthSouthToDrive();
                zustand++;
                timer = 0;               
            }            
            if(zustand == 2 && timer == 1) {
                allowNorthSouthToDrive();
                zustand++;
                timer = 0;
            }            
            if(zustand == 3 && timer == 3) {
                prepareNorthSouthToStop();
                zustand++;
                timer = 0;
            }
            if(zustand == 4 && timer == 1) {
                cleanState();
                zustand++;
                timer = 0;
            }            
            if(zustand == 5 && timer == 1) {
                prepareEastWestToDrive();
                zustand++;
                timer = 0;
            }            
            if(zustand == 6 && timer == 1) {
                allowEastWestToDrive();
                zustand++;
                timer = 0;
            }           
            if(zustand == 7 && timer == 2) {
                prepareEastWestToStop();
                zustand = 0;
                timer = 0;
            }
        }            
        // Behandlung Button-Ereignis aus ISR
        if(fCWEW_Isr){
            // schneller auf weiß für Fußgänger OST-WEST
            if (zustand == 0) { // alle rot -> direkt NORD-SÜD auf gelb -> state 2 wird aktiviert
                prepareNorthSouthToDrive();
                zustand = 2;
                timer = 0;
            }          
            // länger auf weiß für Fußgänger OST-WEST
            if (zustand == 3 && timer < 3) {
                timer = timer - 2;
            }            
            // schneller auf weiß für Fußgänger NORD-SÜD
            if (zustand == 4) { // alle rot -> direkt OST-WEST auf gelb -> state 6 wird aktiviert
                prepareEastWestToDrive();
                zustand = 6;
                timer = 0;
            }
             // länger auf weiß für Fußgänger NORD-SÜD
            if (zustand == 7 && timer < 2) {
                timer = timer - 2;
            }
            fCWEW_Isr = 0; // Wieder auf Null!
        }
        /* 
         * Character aus Uart ISR abfragen 
         * Beispiel für Menuesteuerung
         */
        
        if ( cRx ) {
            char c = cRx;   // copy char
            cRx = 0;        // nicht vergessen!!! Warum?
            // +++ Menuesteuerung +++
            sprintf( buffer, "Handle Keyboard %c\n\r", c );
            UART_PutString( buffer );
            switch ( c ) {
                // Software reset, startet Programm neu
                case 'q':
                case 'Q':   // fallthrough
                    CySoftwareReset();
                    break;
                case '+':   // fallthrough
                    brightness_settings(1);
                    break;
                case '-': 
                    brightness_settings(0);
                    break;
                case 'h':   // help
                case 'H':   // fallthrough
                    UART_PutString( "\n\rHelp:\n\r\\th,H: help\n\r\\tq,Q: software reset\n\r" );
                    break;
                default:
                    UART_PutChar( c );    // Buchstabe auf Bildschirm ausgeben
                    break;
            }  // end switch          
        } // end if cRx                        
    } // end for
}             
/* [] END OF FILE */