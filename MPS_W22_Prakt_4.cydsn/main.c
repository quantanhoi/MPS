/* ========================================
 *
 * Copyright R. Mayer, h_da, FbI, 2022
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
#include "scale.h"      // Tonleiter / Frequenzen

/*
 * Diese Definitionen ermöglichen es, 
 * einfach Informationen auf den Bildschirm zu schreiben
 */
#define _VERSION_NR     "ver. 1.0"          //!< Version number. Please update
#define _PROJECT_NAME   "MPS_W22_Prakt_4"  //!< Project name
#define _PROCESSOR      "PSoC 5LP"          //!< Processor type
#define _DEVICE_NAME    "FreeSoC2"          //!< Board or device type
#define _AUTHOR_        "Nick Otin, Marie O'hana"
#define _COMPANY        "Template MPS22 Termin 4"

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

#define SOUND_OFF Out_Ena_Write(0)  //!< disable sound output
#define SOUND_ON  Out_Ena_Write(1)  //!< enable sound output

#include "scale.h"
#define SysClk 24000000
#define pre2 2      //f(tc) multiplier
#define topValue 65535
static int prescaler = 2;    

    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/


/* +++ TODO                 +++
 *     nützliche Macros ...
 */

    void setTone(eTone p_tone) {
        Timer_WritePeriod(SysClk / (pre2 * prescaler * topValue) / p_tone);
        
    }

/**
 * Struktur zur Beschreibung einer einzelnen Note.
 * Einfache Version ohne Artikulierung etc.
 * @version 2022-12-11
 */
typedef struct {
    eTone       tone;       //!< enummeration note name and frequency
    float       duration;   //!< tone or pause duration in ms, e.g. 1, 1/2, 1/4, ....
} sNoteSimple_t;

/**
 * Definition einer Tonfolge mit Tondauer unter Verwendung von
 * @see sNoteSimple_t
 * und
 * @see eTone
 */
void playTone(const sNoteSimple_t* psNote) {
    setTone(psNote->tone);
    SOUND_ON;
    CyDelay(psNote->duration*1000);
    SOUND_OFF;
}
void toneSettings(eTone tone, float dauer) {
    sNoteSimple_t tempNote;
    tempNote.duration = dauer;
    tempNote.tone = tone;
    playTone(&tempNote);
}

sNoteSimple_t harm[] = { 
                   {C5, 1./4}, {E5, 1./4}, {G5, 1./4}, 
                   {C5, 1./4}, {E5, 1./4}, {G5, 1./4}, 
                   {C5, 1./4}, {F5, 1./4}, {A5, 1./4}, 
                   {C5, 1./4}, {F5, 1./4}, {A5, 1./4}, 
                   {H4, 1./4}, {D5, 1./4}, {G5, 1./4}, 
                   {H4, 1./4}, {D5, 1./4}, {G5, 1./4}, 
                   {C5, 3./4}, {pse, 1./4}, {D5, 4./4}, {C5, 7./4},                
                 };

/* +++ TODO                 +++
 *     Funktion zum Abspielen von 'Lied'
 */
    /**
     * Play a sequence of tones.
     *
     * @param[in] psNote pointer to sNoteSimple_t array
     * @param len length of array
     * @return void
     * @todo Implementieren!
     */
void playSong(){
    int length = sizeof(harm)/sizeof(harm[0]);
    for(int i= 0; i < length; i++) {
        playTone(&harm[i]);
    }
}
    void play( const sNoteSimple_t* psNote, uint16_t len ) {
        // +++ TODO +++
        return;
    }

/** 
 * UART RX interrupt service routine.
 *
 * Collect a characters from UART into a global input variable.
 * @see cRx
 */
CY_ISR( MyIsrUartRX ) {
    cRx = UART_GetChar();     // copy char
}

/**
 * Basisprojekt mit UART mit Interrupt. 
 * für FreeSoC2
 * 
 * @author Ralf S. Mayer
 * @date 2022-12-11
 * @version 1.0
 */
int main(void)
{
    Timer_ReadPeriod();
    /* Initialisierung */
    UART_Start();           // start UART
    isr_UART_RX_StartEx( MyIsrUartRX ); // enable itr uart
    
    Timer_Start();
        
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Welcome and info text Ausgabe */
    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);  // formatiert in Buffer
    UART_PutString( buffer );                           // Ausgabe auf UART
        

    uint8_t regVal = 0;
    // Applikationsschleife
    for(;;)
    {
        //aufgabe 3b
        /* Character aus Uart ISR abfragen */
        if ( cRx ) {

            switch ( cRx ) {        // write Prescale Register value

                case '0':
                {
                    prescaler = 2;
                    RegPrescaler_Write(0);
                }
                case '1':
                {
                    prescaler = 16;
                    RegPrescaler_Write(1);
                }
                case '2':
                {
                    prescaler = 128;
                    RegPrescaler_Write(2);
                    
                }
                case '3':
                    //regVal = cRx - '0';     // erklären, wie das funktioniert!
                //basically, cRx is a character, in this case when we input 3, we can turn it to integer by substract with character '0' 
                    //RegPrescaler_Write( regVal );
                {
                    prescaler = 1024;
                    RegPrescaler_Write(3);
                }
                    break;

                case 'T':           // sound on
                    SOUND_ON;
                    break;
                case 't':           // sound off
                    SOUND_OFF;
                    break;
                case 'z':
                {
                    toneSettings(C5, 1./4);
                    uint16 period = Timer_ReadPeriod();
                    sprintf(buffer, "\n\r Periode: %d", period);
                    UART_PutString(buffer);
                    break;
                }
                case 'c':
                {
                    toneSettings(C4, 1./4);
                }
                case 'd':
                {
                    toneSettings(D4, 1./4);
                }
                case 'e':
                {
                    toneSettings(E4, 1./4);
                }
                case 'f':
                {
                    toneSettings(F4, 1./4);
                }
                case 'g':
                {
                    toneSettings(G4, 1./4);
                }
                case 'h':
                {
                    toneSettings(H4, 1./4);
                }
                case 'a':
                {
                    toneSettings(A4, 1./4);
                }

                default:                    
                    UART_PutChar( cRx );    // (unbenutzten) Buchstaben auf Bildschirm ausgeben
                    break;
            } // end switch
            cRx = 0;                    // nicht vergessen. Warum?
        }
       
    } // end for
}

/* [] END OF FILE */
