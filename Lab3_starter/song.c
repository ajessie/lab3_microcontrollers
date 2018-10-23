
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

//100ms is equivalent to a 1/16th note based on 150BPM (beats per minute)
#define DURATION 100


typedef struct {
    tnote       *sounds;
    unsigned    *sound_length;
} song_t;

song_t enter_sandman;
song_t hokie_fight;


void InitSongList() {
    // ENTER SANDMAN OPENING RIFF
    tnote       e_sounds[33];
    unsigned    e_sound_lengths[33];
    enter_sandman = (song_t){e_sounds, e_sound_lengths};

    enter_sandman.sounds[0] = note_silent;
    enter_sandman.sound_length[0] = 40*DURATION;
    enter_sandman.sounds[1] = note_c4;
    enter_sandman.sound_length[1] = 5*DURATION;
    enter_sandman.sounds[2] = note_c5;
    enter_sandman.sound_length[2] = 2*DURATION;
    enter_sandman.sounds[3] = note_e5;
    enter_sandman.sound_length[3] = 2*DURATION;
    enter_sandman.sounds[4] = note_g4;
    enter_sandman.sound_length[4] = 2*DURATION;
    enter_sandman.sounds[5] = note_f4S;
    enter_sandman.sound_length[5] = 4*DURATION;
    enter_sandman.sounds[6] = note_c5;
    enter_sandman.sound_length[6] = 2*DURATION;
    enter_sandman.sounds[7] = note_c4;
    enter_sandman.sound_length[7] = 5*DURATION;
    enter_sandman.sounds[8] = note_c5;
    enter_sandman.sound_length[8] = 2*DURATION;
    enter_sandman.sounds[9] = note_e5;
    enter_sandman.sound_length[9] = 2*DURATION;
    enter_sandman.sounds[10] = note_g4;
    enter_sandman.sound_length[10] = 2*DURATION;
    enter_sandman.sounds[11] = note_f4S;
    enter_sandman.sound_length[11] = 4*DURATION;
    enter_sandman.sounds[12] = note_c5;
    enter_sandman.sound_length[12] = 2*DURATION;
    enter_sandman.sounds[13] = note_c4;
    enter_sandman.sound_length[13] = 5*DURATION;
    enter_sandman.sounds[14] = note_c5;
    enter_sandman.sound_length[14] = 2*DURATION;
    enter_sandman.sounds[15] = note_e5;
    enter_sandman.sound_length[15] = 2*DURATION;
    enter_sandman.sounds[16] = note_g4;
    enter_sandman.sound_length[16] = 2*DURATION;
    enter_sandman.sounds[17] = note_f4S;
    enter_sandman.sound_length[17] = 4*DURATION;
    enter_sandman.sounds[18] = note_c5;
    enter_sandman.sound_length[18] = 2*DURATION;
    enter_sandman.sounds[19] = note_c4;
    enter_sandman.sound_length[19] = 5*DURATION;
    enter_sandman.sounds[20] = note_c5;
    enter_sandman.sound_length[20] = 2*DURATION;
    enter_sandman.sounds[21] = note_e5;
    enter_sandman.sound_length[21] = 2*DURATION;
    enter_sandman.sounds[22] = note_g4;
    enter_sandman.sound_length[22] = 2*DURATION;
    enter_sandman.sounds[23] = note_f4S;
    enter_sandman.sound_length[23] = 4*DURATION;
    enter_sandman.sounds[24] = note_c5;
    enter_sandman.sound_length[24] = 2*DURATION;
    enter_sandman.sounds[25] = note_c4;
    enter_sandman.sound_length[25] = 5*DURATION;
    enter_sandman.sounds[26] = note_c5;
    enter_sandman.sound_length[26] = 2*DURATION;
    enter_sandman.sounds[27] = note_e5;
    enter_sandman.sound_length[27] = 2*DURATION;
    enter_sandman.sounds[28] = note_g4;
    enter_sandman.sound_length[28] = 2*DURATION;
    enter_sandman.sounds[29] = note_f4S;
    enter_sandman.sound_length[29] = 4*DURATION;
    enter_sandman.sounds[30] = note_c5;
    enter_sandman.sound_length[30] = 2*DURATION;
    enter_sandman.sounds[31] = note_silent;
    enter_sandman.sound_length[31] = 40*DURATION;
    enter_sandman.sounds[32] = end_note;
    enter_sandman.sound_length[32] = 2*DURATION;


    // TECH TRIUMPH ENDING
    tnote       h_sounds[24];
    unsigned    h_sound_lengths[24];
    hokie_fight   = (song_t){h_sounds, h_sound_lengths};

    hokie_fight.sounds[0] = note_silent;
    hokie_fight.sound_length[0] = 40*DURATION;
    hokie_fight.sounds[1] = note_g4;
    hokie_fight.sound_length[1] = 2*DURATION;
    hokie_fight.sounds[2] = note_a4;
    hokie_fight.sound_length[2] = 2*DURATION;
    hokie_fight.sounds[3] = note_b4;
    hokie_fight.sound_length[3] = 2*DURATION;
    hokie_fight.sounds[4] = note_c5;
    hokie_fight.sound_length[4] = DURATION;
    hokie_fight.sounds[5] = note_silent;
    hokie_fight.sound_length[5] = DURATION;
    hokie_fight.sounds[6] = note_c5;
    hokie_fight.sound_length[6] = 6*DURATION;
    hokie_fight.sounds[7] = note_e5;
    hokie_fight.sound_length[7] = DURATION;
    hokie_fight.sounds[8] = note_silent;
    hokie_fight.sound_length[8] = DURATION;
    hokie_fight.sounds[9] = note_e5;
    hokie_fight.sound_length[9] = 6*DURATION;
    hokie_fight.sounds[10] = note_f5;
    hokie_fight.sound_length[10] = DURATION;
    hokie_fight.sounds[11] = note_silent;
    hokie_fight.sound_length[11] = DURATION;
    hokie_fight.sounds[12] = note_f5;
    hokie_fight.sound_length[12] = 6*DURATION;
    hokie_fight.sounds[13] = note_f5S;
    hokie_fight.sound_length[13] = 8*DURATION;
    hokie_fight.sounds[14] = note_g5;
    hokie_fight.sound_length[14] = 2*DURATION;
    hokie_fight.sounds[15] = note_g4;
    hokie_fight.sound_length[15] = 2*DURATION;
    hokie_fight.sounds[16] = note_a4;
    hokie_fight.sound_length[16] = 2*DURATION;
    hokie_fight.sounds[17] = note_c5;
    hokie_fight.sound_length[17] = 2*DURATION;
    hokie_fight.sounds[18] = note_d5;
    hokie_fight.sound_length[18] = 2*DURATION;
    hokie_fight.sounds[19] = note_c6;
    hokie_fight.sound_length[19] = 10*DURATION;
    hokie_fight.sounds[20] = note_silent;
    hokie_fight.sound_length[20] = 2*DURATION;
    hokie_fight.sounds[21] = note_c6;
    hokie_fight.sound_length[21] = DURATION;
    hokie_fight.sounds[22] = note_silent;
    hokie_fight.sound_length[22] = 40*DURATION;
    hokie_fight.sounds[23] = end_note;
    hokie_fight.sound_length[23] = 2*DURATION;


}



#endif /* SONG_LIST_H_ */
