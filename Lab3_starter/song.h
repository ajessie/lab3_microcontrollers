/*
 * song.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jon Bunting
 */

#ifndef SONG_H_
#define SONG_H_

#include "sound.h"

// This structure consists of an array of song notes (song_note_t *notes) and its length (unsigned int note_count)
// Any song can be implemented in such structure.
typedef  enum {Enter_sandman, Hokie_fight} Song;
typedef struct {
    unsigned int note_count;
    song_note_t  notes[100];
    Song song;
} song_t;

song_t enter_sandman;
song_t hokie_fight;

void InitSongList();
void PlaySong();


#endif /* SONG_H_ */
