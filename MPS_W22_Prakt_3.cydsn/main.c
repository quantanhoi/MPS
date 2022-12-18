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
#include<HAL.h>

/*
 * Diese Definitionen ermöglichen es, 
 * einfach Informationen auf den Bildschirm zu schreiben
 */
#define _VERSION_NR     "ver. 1.0"              //!< Version number. Please update
#define _PROJECT_NAME   "MPS_W22_Prakt_3"       //!< Project name
#define _PROCESSOR      "PSoC 5LP"              //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"              //!< Board or device type
#define _AUTHOR_        "Ingo Knito und Arno Nym"
#define _COMPANY        "Template MPS 3"

/* ++++++++++++++++++++++++++++++++++
 * +++ Switche für Musterlösungen +++ 
 * ++++++++++++++++++++++++++++++++++ */

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

static uint8_t  fsClock = 0;    //!< s flag
static uint32_t count_ms = 0;   //!< ms count since start
/** 
 * Application clock interrupt service routine for isr_Clk
 *
 * @see fClock
 */
static uint32_t timer = 0;
static uint32_t zustand  = 0;
CY_ISR( IsrAppClk ) {
    count_ms++;                     // increment ms timestamp
    if ( (count_ms > 1000) ) { // next 1 s reached, set back to > 1000 as prak 2
       fsClock = 1;                 // set flag
        timer++;
        count_ms = 0;
    }
}


//somehow I can't set brightness = PWM_ReadCompare() here
static uint16 brightness = 300;
// change the avarage power to change brightness
void brightness_settings(u_int input){
    brightness = PWM_ReadCompare();
    if(input && brightness < 1000){
        //uint16 test = PWM_ReadCompare();
        brightness = brightness + 200;
        PWM_WriteCompare( brightness);
        return;
        
    }else if(!input && brightness <= 100){
        brightness = brightness + 100;
        PWM_WriteCompare(brightness);
        return;
    }
    else if(!input) {
        brightness = brightness -200;
        PWM_WriteCompare(brightness);
        return;
    }
}
/**
 * Basisprojekt mit UART mit Interrupt, User Button mit Interrupt und Statusabfrage. 
 * Pin-I/O Einfache Eingabe mit Button, Ausgabe mit LED
 * für FreeSoC2
 * 
 * @author Ralf S. Mayer
 * @date 2022-11-25
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
    
    /* Initialize PWM */
    PWM_Start();                        // start PWM

    /* Register isr_Clk interrupt and service routine */
    isr_Clk_StartEx( IsrAppClk );       // register and start application clock ISR
    
    CyGlobalIntEnable;                  /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART
    cRx = 'h';                                          // was passiert?
    
    // Applikationsschleife
    for(;;)
    {
        if ( fsClock ) {
            fsClock = 0;    // don't forget
            // TODO Ampelsteuerung
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
//        /* Fußgänger-Anforderung Ampel */        
//        // Behandlung Button-Ereignis aus ISR
        if(fCWEW_Isr){
            // fast foward to turn on led Fuß ost-west
            if (zustand == 0) { // alle rot -> direkt NORD-SÜD auf gelb -> state 2 wird aktiviert
                prepareNorthSouthToDrive();
                zustand = 2;
                timer = 0;
            }          
            // led Fuß ost-west lasts longer
            if (zustand == 3 && timer < 3) {
                timer = timer - 2;
            }            
            // fast foward for led fuß nord - süd
            if (zustand == 4) { // alle rot -> direkt OST-WEST auf gelb -> state 6 wird aktiviert
                prepareEastWestToDrive();
                zustand = 6;
                timer = 0;
            }
            // led Fuß nord - süd lasts longer
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
            switch ( c ) {
                // Software reset, startet Programm neu
                case 'q':
                case 'Q':   // fallthrough
                    CySoftwareReset();
                    break;
                case 'h':   // help
                case 'H':   // fallthrough
                    UART_PutString( "\n\rHelp:\n\r\
\th,H: help\n\r\
\tc: clear screen\n\r\
\tq,Q: software reset\n\r" );
                    break;
                    
                /* VT100 Steuerzeichen: clear screen (nicht verlangt, lediglich ein Test!) */
                case 'c':   // clear screen, see https://stackoverflow.com/questions/37774983/clearing-the-screen-by-printing-a-character
                    UART_PutString( "\033[2J\033[H" ); // clear screen \033[2J, 
                                                       // home position \033[H
                    break;
                    
                case '+':   
                    sprintf(buffer, "brightness: %d \n", brightness);
                    UART_PutString(buffer);
                    brightness_settings(0);
                    break;
                case '-': 
                    sprintf(buffer, "brightness: %d \n", brightness);
                    UART_PutString(buffer);
                    brightness_settings(1);
                    break;

                    // ... und so weiter ...
                default:
                    UART_PutChar( c );    // Buchstabe auf Bildschirm ausgeben
                    break;
            }  // end switch          
        } // end if cRx
                        
    } // end for
}

/* [] END OF FILE */
