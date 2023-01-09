#ifndef AMPEL_HEADER_FILE
#define AMPEL_HEADER_FILE
    
#include "project.h"

/* Macros for I/O */ //"u" is unsigned int
#define LOW  (0u)  //!< on (active low)
#define HIGH (1u)  //!< off (active low)

#define NORTH_SOUTH(r,y,g) switch_north_south_state(r,y,g)
#define N_R(x) Pin_N_R_Write(x)
#define N_Y(x) Pin_N_Y_Write(x)
#define N_G(x) Pin_N_G_Write(x)

#define S_R(x) Pin_S_R_Write(x)
#define S_Y(x) Pin_S_Y_Write(x)
#define S_G(x) Pin_S_G_Write(x)
// =============================================================
#define WEST(r,y,g) switch_east_state(r,y,g)
#define W_R(x) Pin_W_R_Write(x)
#define W_Y(x) Pin_W_Y_Write(x)
#define W_G(x) Pin_W_G_Write(x)

    
#define E_CW(x) Pin_E_CW_Write(x)
#define S_EW(x) Pin_S_CW_Write(x)

#define F_OW(x) Pin_E_CW_Write(x)
#define F_NS(x) Pin_S_CW_Write(x)

    
//===============================================================
// State 0
#define _SET_ALL_LEDS_TO_RED ( NORTH_SOUTH(LOW, HIGH, HIGH), WEST(LOW, HIGH, HIGH), F_NS(LOW), F_OW(LOW) )
// State 1
#define _SET_NORTH_SOUTH_TO_RED_YELLOW ( NORTH_SOUTH(LOW, LOW, HIGH), WEST(LOW, HIGH, HIGH), F_NS(LOW), F_OW(LOW) )
// State 2
#define _ALLOW_NORTH_SOUTH_TO_DRIVE ( NORTH_SOUTH(HIGH, HIGH, LOW), WEST(LOW, HIGH, HIGH), F_NS(HIGH), F_OW(LOW) )
// State 3
#define _SET_NORTH_SOUTH_TO_YELLOW ( NORTH_SOUTH(HIGH, LOW, HIGH), WEST(LOW, HIGH, HIGH), F_NS(LOW), F_OW(LOW) )
// State 4
#define _SET_WEST_TO_RED_YELLOW ( NORTH_SOUTH(LOW, HIGH, HIGH), WEST(LOW, LOW, HIGH), F_NS(LOW), F_OW(LOW) )
// State 5 
#define _ALLOW_WEST_TO_DRIVE ( NORTH_SOUTH(LOW, HIGH, HIGH), WEST(HIGH, HIGH, LOW), F_NS(LOW), F_OW(HIGH) )
// State 6 
#define _SET_WEST_TO_YELLOW ( NORTH_SOUTH(LOW, HIGH, HIGH), WEST(HIGH, LOW, HIGH), F_NS(LOW), F_OW(LOW) )

// Functions for state macros
void switch_north_south_state(uint8 r, uint8 y, uint8 g);
void switch_east_state(uint8 r, uint8 y, uint8 g);

// Alle rot
void cleanState();

// north south traffic light
void prepareNorthSouthToDrive();
void allowNorthSouthToDrive();
void prepareNorthSouthToStop();

// west (east) traffic light
void prepareEastWestToDrive();
void allowEastWestToDrive();
void prepareEastWestToStop();


#endif
