/***************************************************************************
 *                                                                         *
 * Project Name : Home Defender                                            *
 *                                                                         *
 * Purpose : Create a functional GameBoy game with the capability to run   *
 * on original hardware.                                                   *
 *                                                                         *
 * Version : 3.0, Started 10/14/2022                                       *
 *                                                                         *
 * Author : Tanner Hall                                                    *
 *                                                                         *
 **************************************************************************/

// Base C Libraries
#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>
#include <stdio.h>


// Included C Files
#include "start_data.c"
#include "start_map.c"
#include "sprite.c"
#include "bkg_sprites.c"
#include "menu_screen.c"
#include "stats_screen.c"
#include "game_screen.c"


// Global Variables
uint8_t numplays;


void performanceDelay(uint8_t num){
    uint8_t i;
    for(i = 0; i < num; i++){
        wait_vbl_done();
    }
}


void playSounds(uint8_t soundVal){
    if(soundVal == 0){
        // Sound for A/Start press in menu.
        NR10_REG = 0x25;
        NR11_REG = 0x86;
        NR12_REG = 0x36;
        NR13_REG = 0x72;
        NR14_REG = 0x86;
    }
    if(soundVal == 1){
        // Sound for Cursor movement in menu.
        NR10_REG = 0x15;
        NR11_REG = 0xC0;
        NR12_REG = 0x24;
        NR13_REG = 0x73;
        NR14_REG = 0x86;
    }
    if(soundVal == 2){
        // Sound for Back-press in menu.
        NR10_REG = 0x2D;
        NR11_REG = 0x86;
        NR12_REG = 0x36;
        NR13_REG = 0x72;
        NR14_REG = 0x86;
    }
    if(soundVal == 3){
        // Sound for Standard Blast within Game.
        NR10_REG = 0x4D;
        NR11_REG = 0xCF;
        NR12_REG = 0x64;
        NR13_REG = 0xFA;
        NR14_REG = 0x86;
    }
    if(soundVal == 4){
        // Sound for Missile Blast within Game.
        NR41_REG = 0x03;
        NR42_REG = 0xE7;
        NR43_REG = 0xA8;
        NR44_REG = 0x80;
    }
    if(soundVal == 5){
        // Sound for Missile Recharge within Game.
        NR21_REG = 0xCA;
        NR22_REG = 0x83;
        NR23_REG = 0xD7;
        NR24_REG = 0xC6;
    }
    if(soundVal == 6){
        // Sound for Failed Missile Launch within Game.
        NR41_REG = 0x3A;
        NR42_REG = 0xA1;
        NR43_REG = 0x00;
        NR44_REG = 0xC0;
    }
    if(soundVal == 7){
        // Sound for Asteroid Destruction within Game.

    }
    if(soundVal == 8){
        // Sound for Asteroid Collision with Planet.
        NR41_REG = 0x00;
        NR42_REG = 0xD6;
        NR43_REG = 0x37;
        NR44_REG = 0x80;
    }
    if(soundVal == 9){
        // Sound for Ship Respawn
        // TODO: Change sound to unique sound.
        NR21_REG = 0xCA;
        NR22_REG = 0x83;
        NR23_REG = 0xD7;
        NR24_REG = 0xC6;
    }
}


void startScreen(){
    SHOW_BKG;

    waitpad(J_START);
    playSounds(0);
    performanceDelay(4);
}

void main(){

    //Enable Sound Profile
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    set_bkg_data(0, 172, start_data);
    set_bkg_tiles(0, 0, 20, 18, start_map);
    DISPLAY_ON;
    numplays = 0;

    while(1){

        startScreen();

        uint16_t seed;
        seed = DIV_REG;
        seed |= (uint16_t)DIV_REG << 8;
        initarand(seed);

        //menuSelection();

        //fadeTransition();
    }
}