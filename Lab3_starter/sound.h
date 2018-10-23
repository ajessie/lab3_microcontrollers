/*
 * sound.h
 *
 *  Created on: Oct 21, 2018
 *      Author: Leyla
 */

#ifndef SOUND_H_
#define SOUND_H_

typedef enum {note_silent,
              note_c4,
              note_d4,
              note_e4,
              note_f4,
              note_f4S,
              note_g4,
              note_a4,
              note_b4,
              note_c5,
              note_d5,
              note_e5,
              note_f5,
              note_fs5,
              note_g5,
              note_a5,
              note_b5,
              note_c6} tnote;

void InitSound();
void PlayNote(tnote n, unsigned ms);


#endif /* SOUND_H_ */
