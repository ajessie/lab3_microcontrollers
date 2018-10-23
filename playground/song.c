
/**
 * Virginia Tech
 * ECE 2534 - Microcontroller Programming
 * Author: Jon Bunting
 * Date:   10/21/2018
 *
 *
 *
 * Defines two songs to be played by a
 * "Guitar Hero"-like game developed for
 * the TI MSP432P4/Educational BoostXL.
 *
 */


#include "sound.h"
#include "song.h"

//100ms is equivalent to a 1/16th note based on 150BPM (beats per minute)
#define DURATION 100


void PlaySong(song_t song) {
    int i = 0;
    for (i=0; i<song.note_count; i++)
        PlayNote(song.notes[i]);
}

void InitSongList() {
    // ENTER SANDMAN OPENING RIFF
    enter_sandman.note_count = 31;

    enter_sandman.notes[0].note_name = note_silent;
    enter_sandman.notes[0].note_length = 40*DURATION;

    enter_sandman.notes[1].note_name = note_c4;
    enter_sandman.notes[1].note_length = 5*DURATION;

    enter_sandman.notes[2].note_name = note_c5;
    enter_sandman.notes[2].note_length = 2*DURATION;

    enter_sandman.notes[3].note_name = note_e5;
    enter_sandman.notes[3].note_length = 2*DURATION;

    enter_sandman.notes[4].note_name = note_g4;
    enter_sandman.notes[4].note_length = 2*DURATION;

    enter_sandman.notes[5].note_name = note_f4S;
    enter_sandman.notes[5].note_length = 4*DURATION;

    enter_sandman.notes[6].note_name = note_c5;
    enter_sandman.notes[6].note_length = 2*DURATION;

    enter_sandman.notes[7].note_name = note_c4;
    enter_sandman.notes[7].note_length = 5*DURATION;

    enter_sandman.notes[8].note_name = note_c5;
    enter_sandman.notes[8].note_length = 2*DURATION;

    enter_sandman.notes[9].note_name = note_e5;
    enter_sandman.notes[9].note_length = 2*DURATION;

    enter_sandman.notes[10].note_name = note_g4;
    enter_sandman.notes[10].note_length = 2*DURATION;
    /*
    enter_sandman.notes[11] = note_f4S;
    enter_sandman.notes[11] = 4*DURATION;
       enter_sandman.notes[12] = note_c5;
        enter_sandman.notes[12] = 2*DURATION;
        enter_sandman.notes[13] = note_c4;
        enter_sandman.notes[13] = 5*DURATION;
        enter_sandman.notes[14] = note_c5;
        enter_sandman.notes[14] = 2*DURATION;
        enter_sandman.notes[15] = note_e5;
        enter_sandman.notes[15] = 2*DURATION;
        enter_sandman.notes[16] = note_g4;
        enter_sandman.notes[16] = 2*DURATION;
        enter_sandman.notes[17] = note_f4S;
        enter_sandman.notes[17] = 4*DURATION;
        enter_sandman.notes[18] = note_c5;
        enter_sandman.notes[18] = 2*DURATION;
        enter_sandman.notes[19] = note_c4;
        enter_sandman.notes[19] = 5*DURATION;
        enter_sandman.notes[20] = note_c5;
        enter_sandman.notes[20] = 2*DURATION;
        enter_sandman.notes[21] = note_e5;
        enter_sandman.notes[21] = 2*DURATION;
        enter_sandman.notes[22] = note_g4;
        enter_sandman.notes[22] = 2*DURATION;
        enter_sandman.notes[23] = note_f4S;
        enter_sandman.notes[23] = 4*DURATION;
        enter_sandman.notes[24] = note_c5;
        enter_sandman.notes[24] = 2*DURATION;
        enter_sandman.notes[25] = note_c4;
        enter_sandman.notes[25] = 5*DURATION;
        enter_sandman.notes[26] = note_c5;
        enter_sandman.notes[26] = 2*DURATION;
        enter_sandman.notes[27] = note_e5;
        enter_sandman.notes[27] = 2*DURATION;
        enter_sandman.notes[28] = note_g4;
        enter_sandman.notes[28] = 2*DURATION;
        enter_sandman.notes[29] = note_f4S;
        enter_sandman.notes[29] = 4*DURATION;
        enter_sandman.notes[30] = note_c5;
        enter_sandman.notes[30] = 2*DURATION;
        enter_sandman.notes[31] = note_silent;
        enter_sandman.notes[31] = 40*DURATION;
        enter_sandman.notes[32] = end_note;
        enter_sandman.notes[32] = 2*DURATION;

*/

    hokie_fight.note_count = 22;

    hokie_fight.notes[0].note_name = note_silent;
    hokie_fight.notes[0].note_length = 40*DURATION;

    hokie_fight.notes[1].note_name = note_g4;
    hokie_fight.notes[1].note_length = 2*DURATION;

    hokie_fight.notes[2].note_name = note_a4;
    hokie_fight.notes[2].note_length = 2*DURATION;

    hokie_fight.notes[3].note_name = note_b4;
    hokie_fight.notes[3].note_length = 2*DURATION;

    hokie_fight.notes[4].note_name = note_c5;
    hokie_fight.notes[4].note_length = DURATION;

    hokie_fight.notes[5].note_name = note_silent;
    hokie_fight.notes[5].note_length = DURATION;

    hokie_fight.notes[6].note_name = note_c5;
    hokie_fight.notes[6].note_length = 6*DURATION;

    hokie_fight.notes[7].note_name = note_e5;
    hokie_fight.notes[7].note_length = DURATION;

    hokie_fight.notes[8].note_name = note_silent;
    hokie_fight.notes[8].note_length = DURATION;

    hokie_fight.notes[9].note_name = note_e5;
    hokie_fight.notes[9].note_length = 6*DURATION;

    hokie_fight.notes[10].note_name = note_f5;
    hokie_fight.notes[10].note_length = DURATION;

 /*   hokie_fight.notes[11] = note_silent;
    hokie_fight.notes[11] = DURATION;

    hokie_fight.notes[12] = note_f5;
    hokie_fight.notes[12] = 6*DURATION;

    hokie_fight.notes[13] = note_f5S;
    hokie_fight.notes[13] = 8*DURATION;

    hokie_fight.notes[14] = note_g5;
    hokie_fight.notes[14] = 2*DURATION;
        hokie_fight.notes[15] = note_g4;
        hokie_fight.notes[15] = 2*DURATION;
        hokie_fight.notes[16] = note_a4;
        hokie_fight.notes[16] = 2*DURATION;
        hokie_fight.notes[17] = note_c5;
        hokie_fight.notes[17] = 2*DURATION;
        hokie_fight.notes[18] = note_d5;
        hokie_fight.notes[18] = 2*DURATION;
        hokie_fight.notes[19] = note_c6;
        hokie_fight.notes[19] = 10*DURATION;
        hokie_fight.notes[20] = note_silent;
        hokie_fight.notes[20] = 2*DURATION;
        hokie_fight.notes[21] = note_c6;
        hokie_fight.notes[21] = DURATION;
        hokie_fight.notes[22] = note_silent;
        hokie_fight.notes[22] = 40*DURATION;

*/
}




