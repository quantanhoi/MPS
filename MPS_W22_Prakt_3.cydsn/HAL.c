#include "HAL.h"

void switch_north_south_state(uint8 r, uint8 y, uint8 g){
     N_R(r), N_Y(y), N_G(g), S_R(r), S_Y(y), S_G(g) ;  
}
void switch_west_state(uint8 r, uint8 y, uint8 g){
     W_R(r), W_Y(y), W_G(g);
}

 // Alle rot 
void cleanState(){    
   _SET_ALL_LEDS_TO_RED;
}
void prepareNorthSouthToDrive(){
    _SET_NORTH_SOUTH_TO_RED_YELLOW;
}
void allowNorthSouthToDrive(){
    _ALLOW_NORTH_SOUTH_TO_DRIVE;
}
void prepareNorthSouthToStop(){
    _SET_NORTH_SOUTH_TO_YELLOW;
}

void prepareEastWestToDrive(){
    _SET_WEST_TO_RED_YELLOW;
}
void allowEastWestToDrive(){
    _ALLOW_WEST_TO_DRIVE;
}
void prepareEastWestToStop(){
    _SET_WEST_TO_YELLOW;
}

