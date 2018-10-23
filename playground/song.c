
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
/*

#include "sound.h"

//100ms is equivalent to a 1/16th note based on 150BPM (beats per minute)
#define DURATION 100
#define STRING_1_LOCATION 0
#define STRING_2_LOCATION 0
#define STRING_3_LOCATION 0
#define STRING_4_LOCATION 0

typedef struct {
    unsigned string;
    unsigned position;
    unsigned time_in_song
} game_note_t;

typedef struct {
    tnote       *sounds;
    unsigned    *sound_length;
    game_note_t *song_notes;
} song_t;

song_t enter_sandman;
song_t hokie_fight;


void InitSongList() {
    // ENTER SANDMAN OPENING RIFF
    tnote       e_sounds[33];
    unsigned    e_sound_lengths[33];
    game_note_t e_notes[10];
    enter_sandman = (song_t){e_sounds, e_sound_lengths, e_notes};

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
    game_note_t h_notes[18];
    hokie_fight   = (song_t){h_sounds, h_sound_lengths, h_notes};

    hokie_fight.song_notes[0]  = (note_t){ STRING_1_LOCATION,0,30};
    hokie_fight.song_notes[1]  = (note_t){ STRING_2_LOCATION,0,35};
    hokie_fight.song_notes[2]  = (note_t){ STRING_3_LOCATION,0,40};
    hokie_fight.song_notes[3]  = (note_t){ STRING_1_LOCATION,0,45};
    hokie_fight.song_notes[4]  = (note_t){ STRING_2_LOCATION,0,50};
    hokie_fight.song_notes[5]  = (note_t){ STRING_2_LOCATION,0,65};
    hokie_fight.song_notes[6]  = (note_t){ STRING_3_LOCATION,0,70};
    hokie_fight.song_notes[7]  = (note_t){ STRING_1_LOCATION,0,85};
    hokie_fight.song_notes[8]  = (note_t){ STRING_4_LOCATION,0,90};
    hokie_fight.song_notes[9]  = (note_t){ STRING_1_LOCATION,0,105};
    hokie_fight.song_notes[10] = (note_t){ STRING_1_LOCATION,0,125};
    hokie_fight.song_notes[11] = (note_t){ STRING_1_LOCATION,0,130};
    hokie_fight.song_notes[12] = (note_t){ STRING_2_LOCATION,0,135};
    hokie_fight.song_notes[13] = (note_t){ STRING_3_LOCATION,0,140};
    hokie_fight.song_notes[14] = (note_t){ STRING_4_LOCATION,0,145};
    hokie_fight.song_notes[15] = (note_t){ STRING_4_LOCATION,0,150};
    hokie_fight.song_notes[16] = (note_t){ STRING_4_LOCATION,0,183};
    hokie_fight.song_notes[17] = (note_t){ 0,0,0 };


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

bool PlaySong(song_t song, bool reset, bool silent) {
    static int i = 0;
    bool song_over = false;

    if ( song.sounds[i] == end_note )
        song_over = true;

    if ( song_over || reset ) {
        i = 0;
        PlaySound(note_silent, 10, true);
        return song_over;
    }
    if ( silent ) {
        PlaySound(note_silent, 10, true);
        return song_over;
    }
    if ( !PlaySound(song.sounds[i], song.sound_length[i], false) ) {
        i++;
    }
    return song_over;
}


#endif /* SONG_LIST_H_ */
