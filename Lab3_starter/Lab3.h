/*
 * Lab3.h
 *
 *  Created on: Nov 4, 2018
 *      Author: Jessie
 */

#ifndef LAB3_H_
#define LAB3_H_


typedef enum {play, scores, learn, endGame, decision} menu;

typedef struct Screen
{
    menu display;
    int pos;
    int posy;
    int score;
    int lose;


} Screen;

// This function initializes all the peripherals except graphics
void initialize();
void ModifyLEDColor(bool leftButtonWasPushed, bool rightButtonWasPushed);
void Splash();
void drawDisplay();
void howToPlay(Screen *action);
void rock(Screen *action, song_t *song);
void Menu(Screen *action);
void Down(Screen *action);
void Down2(Screen *action);
void Up (Screen *action);
void DrawFrets(Screen *action);
void DrawRightSide();
void DrawFirstFret();
void DrawSecondFret();
void DrawThirdFret();
void DrawFourthFret();
void DrawVerticalOne();
void DrawVerticalTwo();
void DrawVerticalThree();
void DrawVerticalFour();
void DrawGreenCircle();
void DrawRedCircel();
void DrawYellowCircle();
void DrawBlueCircle();
void DrawLeftSide();
void MoveGreenCircle(Screen *action);
void EndGame(Screen *action);
void Point(Screen *action);
void SongChoice(Screen *action, song_t *song);
void MoveRedCircle(Screen *action);
void MoveBlueCircle(Screen *action);
void MoveYellowCircle(Screen *action);
#endif /* LAB3_H_ */
