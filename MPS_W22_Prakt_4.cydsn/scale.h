/* ========================================
 *
 * Copyright h_da, 2022
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __SCALE_H__
#define __SCALE_H__

/**
 * Tonleiter zwischen C5 und C6 mit Frequenzen
 * @see 
 */
typedef enum {
    C4 = 261,
    c4 = 277,
    D4 = 294,
    d4 = 311,
    E4 = 330,
    F4 = 349,
    f4 = 370,
    G4 = 391,
    g4 = 415,
    A4 = 440,
    H4 = 493,
    C5 = 523,
    c5 = 554,
    D5 = 587,
    d5 = 622,
    E5 = 659,
    F5 = 698,
    f5 = 740,
    G5 = 784,   
    g5 = 831,
    A5 = 880,
    a5 = 932,
    H5 = 988,
    C6 = 1047,
    pse  = 0    // pause, sound off
}  eTone;

#endif
/* [] END OF FILE */
