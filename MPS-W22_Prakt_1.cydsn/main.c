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
#define _PROJECT_NAME   "MPS-W22_Prakt_1" //!< Project name
#define _PROCESSOR      "PSoC 5LP"      //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"      //!< Board or device type
#define _AUTHOR_        "Marge Rite, Peter Silie" //!< Ihr(e) Name(n)!
#define _COMPANY        "FbI Template MPS"

// String für die Anzeige zusammenbauen
#define _VERSTR_       (_PROJECT_NAME", "_DEVICE_NAME", "_PROCESSOR", "_VERSION_NR"\n\r"\
_AUTHOR_" ("_COMPANY"), "__DATE__" "__TIME__)

/* Macros for I/O */
#define LED_ON  (0u)                //!< LED on (active low)
#define LED_OFF (1u)                //!< LED off (active low)

/* 
 * String Buffer für Anzeige am Bildschirm anlegen.
 * Auf die maximale Größe achten!
 */
#define BUFFER_SIZE 128             //!< string output buffer size for sprintf
static char buffer[BUFFER_SIZE];    //!< buffer (global) for sprintf

/**
 * Template-Projekt 1_1 mit UART ohne Interrupt. 
 * für FreeSoC2. Muss nach Aufgabenstellung erweitert werden.
 * 
 * @author Ralf S. Mayer
 * @date 2020-08-23
 * @version 1.0
 */
int main(void)
{
    /* Initialisierung */
    UART_Start();                       // start UART

    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART
    
    /* +++ Declarationen +++ */
    uint8_t chr = 0;                       // for char von der UART
    
    /* +++ Applikationsschleife         +++
       +++ wird ständig durchlaufen     +++ */
    for(;;)
    {
        /* +++ Character aus Uart mit Polling abfragen +++ */
        chr = UART_GetChar();           // fragt UART nach empfangene char ab
                                        //  = 0: wenn nichts empfangen
                                        // != 0: empfangenes Zeichen
                                        // Polling, nicht wartend
        // chr auswerten falls != 0
        if ( chr != 0 ) {               // da kam ein Zeichen ...
            // ein kleines Menu ... 
            // >>> (TODO um Einträg erweitern!) <<<
            //  z.B. grüne LED ein- 'G' und 'g' ausschalten
            switch (chr) {              // Zeichen auswerten
                case 'x':               // 'x' auswerten
                    UART_PutString( "... da ist ein <x>'\n\r" );
                                        // String Ausgabe, Zeilenabschluss LF CR
                    break;
                case 'R': 
                    Pin_N_R_Write(LED_ON);
                    break;
                case 'Y':
                    Pin_N_Y_Write(LED_ON);
                    break;
                case 'G':
                    Pin_N_G_Write(LED_ON);
                    break;
                case 'r':
                    Pin_N_G_Write(LED_OFF);
                    break;
                case 'y':
                    Pin_N_G_Write(LED_OFF);
                    break;
                case 'g':
                    Pin_N_G_Write(LED_OFF);
                    break;
                default:
                    sprintf( buffer, "erwarte ein <x>, aber <%c> wurde eingegeben\n\r", chr );
                    UART_PutString( buffer );
                    break;
            } // end switch
            chr = 0;                    // nicht vergessen (mit ISR)
        }


        /* +++ Taste CWEW abfragen +++ */
        if ( Pin_CWEW_Read() == 0 ) {   // warum auf 0 abfragen? beim 0 wird kein signal gesendet
            while(!Pin_CWEW_Read()) {       // warte auf loslegen
            }
            Pin_E_CW_Write( !Pin_E_CW_Read() ); // toggle
        }           

        /* +++ LED blinken lassen, warten mit Schleife +++ */
        
        // für Teilaufgabe 6 Kommentare entfernen
        // Testen mit DEBUG und RELEASE
        volatile uint32_t loop;                  // geht mit DEBUG, aber nicht mit RELEASE
                                        // warum??? 
                                        // Frage, was macht 'volatile'?
        Pin_N_R_Write( LED_ON );        // anschalten
        for ( loop = 0; loop < 1000000; loop++ )    // warten mit Schleife
            ;
        Pin_N_R_Write( LED_OFF );       // ausschalten
        for ( loop = 0; loop < 1000000; loop++ )    // warten mit Schleife
            ;
        
    } // end for
    
} // end main

/* [] END OF FILE */
