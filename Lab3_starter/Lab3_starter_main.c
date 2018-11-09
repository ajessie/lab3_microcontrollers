#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "ButtonLED_HAL.h"
#include "graphics_HAL.h"
#include "ADC_HAL.h"
#include "sound.h"
#include "song.h"
#include "Lab3.h"
#include "Timer32_HAL.h"

extern HWTimer_t timer0, timer1;
Graphics_Context g_sContext;

// 100ms in us unit is 100,000
#define T10MS_IN_US 10000
#define LEFT_THRESHOLD  0x1000
#define DURATION 100
#define THREE_SEC 40
#define ONE_SEC 48000000
#define DOWN_THRESHOLD  300
#define UP_THRESHOLD    0x1000
#define BALL_Y_STEP 10
#define BALL_TIME_STEP T10MS_IN_US
#define RIGHT_THRESHOLD 15000

extern song_t enter_sandman;
extern song_t hokie_fight;
Graphics_Context g_sContext;
static int down = 0;
static unsigned vx, vy;
static int down2 = 0;

void SongChoice(Screen *action, song_t *song){                                                           //This function is the display screen for the user to select a song to play
    static int up2 = 0;
    static int count = 0;
    bool joyStickPushedDown = false;
    bool joyStickPushedUp = false;
    Graphics_clearDisplay(&g_sContext);
    char text[16] = "Pick a song:";
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(&g_sContext, (int8_t *) text, -1, 0, 2, true);
    char string[22] = ">Enter Sandman";
    char string2[12] = "Hokie Song";
    Graphics_drawString(&g_sContext, (int8_t *) string, -1, 0, 20, true);
    Graphics_drawString(&g_sContext, (int8_t *) string2, -1, 0, 40, true);

    while(!BoosterpackTopButton_pressed())
    {
           getSampleJoyStick(&vx, &vy);                                         //Check if the user has moved the joystick
           if (vy < DOWN_THRESHOLD)
           {

             joyStickPushedDown = true;
             down2++;
             vy = 0;
           }

           else if (vy > 15000){
              joyStickPushedUp = true;
               up2++;
               vy = 0;
           }


           if (down2 == 1 && joyStickPushedDown == true){                                               //Below are the different display screens according to the users joystick movement
               Graphics_clearDisplay(&g_sContext);
               char text[16] = "Pick a song:";
               Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
               Graphics_drawString(&g_sContext, (int8_t *) text, -1, 0, 2, true);
               char string[20] = "Enter Sandman";
               char string2[30] = ">Hokie Song";
               Graphics_drawString(&g_sContext, (int8_t *) string, -1, 0, 20, true);
               Graphics_drawString(&g_sContext, (int8_t *) string2, -1, 0, 40, true);
               count++;
               down2 = 0;

           }

           else if (up2 == 1 && joyStickPushedUp == true){
               Graphics_clearDisplay(&g_sContext);
               char text[16] = "Pick a song:";
               Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
               Graphics_drawString(&g_sContext, (int8_t *) text, -1, 0, 2, true);
               char string[22] = ">Enter Sandman";
               char string2[12] = "Hokie Song";
               Graphics_drawString(&g_sContext, (int8_t *) string, -1, 0, 20, true);
               Graphics_drawString(&g_sContext, (int8_t *) string2, -1, 0, 40, true);
               up2 = 0;
           }

           if (down2 == 0 && BoosterpackTopButton_pressed()){
               action->display = play;
               song->song = Enter_sandman;
               rock(action, song);
               down2 = 0;
           }

           else  if (count != 0 && BoosterpackTopButton_pressed()){
               action->display = play;
               song->song = Hokie_fight;
               rock(action, song);
               count = 0;

           }
     }
}

void MoveRedCircle(Screen *action){                                                                       //Move the red  circle
    static unsigned int x1 = 30;
    static unsigned int x2 = 50;
    static unsigned int x3 = 70;
    static unsigned int x4 = 90;
    static unsigned int y1 = 20;
    static unsigned int y2 = 20;
    static unsigned int y3 = 20;
    static unsigned int y4 = 20;

    static unsigned vx, vy;
    static bool moveToDown = true;
    static int circle_count = 0;
    static int red_circle = 0;
    static int blue_circle = 0;
    static int yellow_circle = 0;

    static OneShotSWTimer_t yMoveTimer;

    getSampleJoyStick(&vx, &vy);
    bool joyStickPushedtoRight = false;
    bool joyStickPushedtoLeft  = false;
    bool joyStickPushedDown    = false;
    bool joyStickPushedUp      = false;

    static bool init = true;
    if (init)
    {
        InitOneShotSWTimer(&yMoveTimer,
                           &timer0,
                           BALL_TIME_STEP);
        StartOneShotSWTimer(&yMoveTimer);

        init = false;
    }

    if (vx < LEFT_THRESHOLD)
    {
        joyStickPushedtoLeft = true;
    }

    else if (vx < RIGHT_THRESHOLD ){
        joyStickPushedtoRight = true;
    }

    else if (vy < DOWN_THRESHOLD)
    {

      joyStickPushedDown = true;
      vy = 0;
    }

    else if (vy > 15000){
       joyStickPushedUp = true;
        vy = 0;
    }

    if (OneShotSWTimerExpired(&yMoveTimer))
    {

        red_circle++;
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext,x2, y2, 50, 20);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawCircle(&g_sContext, x2, y2, 4);
        Graphics_fillCircle(&g_sContext, x2, y2, 4);

        StartOneShotSWTimer(&yMoveTimer);
        if (moveToDown)
        {
            red_circle++;
            y2 = y2 + 5;

            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
            Graphics_fillCircle(&g_sContext, x2, y2, 4);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
            Graphics_fillCircle(&g_sContext, x2, y2, 2);
            if (y2 == 110){
                moveToDown = false;
                if (y2==110 && joyStickPushedDown == true && BoosterpackTopButton_pressed()){           //this is how we will denote the correct seq for red note being played
                           action->score++;
                           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
                           Graphics_fillCircle(&g_sContext, x2, y2, 4);
                           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
                           Graphics_fillCircle(&g_sContext, x2, y2, 2);
                           y2 = 20;
                           Point(action);
                }

                else if (y2 == 110 && joyStickPushedDown == false && !BoosterpackTopButton_pressed()){
                    if(action->score ==0){
                        action->score = 0;
                        Point(action);
                    }

                    else if (action->score !=0){
                        action->score++;
                        Point(action);
                    }
                }
            }
        }

        else
        {
            y2 = 20;
            if (y2 < 110)
                moveToDown = true;
        }
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext,x2, y2, 50, 20);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawCircle(&g_sContext, x2, y2, 2);
        Graphics_fillCircle(&g_sContext, x2, y2, 2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
        Graphics_fillCircle(&g_sContext, x2, y2, 2);
   }
}

void MoveBlueCircle(Screen *action){                                                                    //Move the Blue circle
    static unsigned int x1 = 30;
    static unsigned int x2 = 50;
    static unsigned int x3 = 70;
    static unsigned int x4 = 90;
    static unsigned int y1 = 20;
    static unsigned int y2 = 20;
    static unsigned int y3 = 20;
    static unsigned int y4 = 20;

    static unsigned vx, vy;
    static bool moveToDown = true;
    static int circle_count = 0;
    static int red_circle = 0;
    static int blue_circle = 0;
    static int yellow_circle = 0;

    static OneShotSWTimer_t yMoveTimer;

    getSampleJoyStick(&vx, &vy);
    bool joyStickPushedtoRight = false;
    bool joyStickPushedtoLeft  = false;
    bool joyStickPushedDown    = false;
    bool joyStickPushedUp      = false;

    static bool init = true;
    if (init)
    {
        InitOneShotSWTimer(&yMoveTimer,
                           &timer0,
                           BALL_TIME_STEP);
        StartOneShotSWTimer(&yMoveTimer);

        init = false;
    }

    if (vx < LEFT_THRESHOLD)
    {
        joyStickPushedtoLeft = true;
    }

    else if (vx < RIGHT_THRESHOLD ){
        joyStickPushedtoRight = true;

    }

    else if (vy < DOWN_THRESHOLD)
    {

      joyStickPushedDown = true;
      vy = 0;
    }

    else if (vy > 15000){
       joyStickPushedUp = true;
        vy = 0;
    }

    if (OneShotSWTimerExpired(&yMoveTimer))
    {

        red_circle++;
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext,x4, y4, 90, 20);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawCircle(&g_sContext, x4, y4, 4);
        Graphics_fillCircle(&g_sContext, x4, y4, 4);

        StartOneShotSWTimer(&yMoveTimer);
        if (moveToDown)
        {
            red_circle++;
            y4 = y4 + 15;

            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_fillCircle(&g_sContext, x4, y4, 4);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
            Graphics_fillCircle(&g_sContext, x4, y4, 2);
            if (y4 == 110){
                moveToDown = false;
                if (y4==110 && joyStickPushedtoRight == true && BoosterpackTopButton_pressed()){            //this is how we will denote the seq. for blue string/note being played
                           action->score++;
                           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                           Graphics_fillCircle(&g_sContext, x4, y4, 4);
                           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
                           Graphics_fillCircle(&g_sContext, x4, y4, 2);
                           y4 = 20;
                           Point(action);
                }

                else if (y4 == 110 && joyStickPushedtoLeft == false && !BoosterpackTopButton_pressed()){
                    if(action->score ==0){
                        action->score = 0;
                        Point(action);
                    }

                    else if (action->score !=0){
                        action->score++;
                        Point(action);
                    }
                }
            }
        }

        else
        {
            y4 = 20;
            if (y4 < 110)
                moveToDown = true;
        }
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext,x4, y4, 90, 20);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawCircle(&g_sContext, x4, y4, 2);
        Graphics_fillCircle(&g_sContext, x4, y4, 2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_fillCircle(&g_sContext, x4, y4, 2);
   }
}

 void MoveGreenCircle(Screen *action){                                                             //Move the green notes down the screen

     static unsigned int x1 = 30;
     static unsigned int x2 = 50;
     static unsigned int x3 = 70;
     static unsigned int x4 = 90;
     static unsigned int y1 = 20;
     static unsigned int y2 = 20;
     static unsigned int y3 = 20;
     static unsigned int y4 = 20;

     static unsigned vx, vy;
     static bool moveToDown = true;
     static int circle_count = 0;
     static int red_circle = 0;
     static int blue_circle = 0;
     static int yellow_circle = 0;

     static OneShotSWTimer_t yMoveTimer;

     getSampleJoyStick(&vx, &vy);
     bool joyStickPushedtoRight = false;
     bool joyStickPushedtoLeft  = false;
     bool joyStickPushedDown    = false;
     bool joyStickPushedUp      = false;

     static bool init = true;
     if (init)
     {
         InitOneShotSWTimer(&yMoveTimer,
                            &timer0,
                            BALL_TIME_STEP);
         StartOneShotSWTimer(&yMoveTimer);

         init = false;
     }

     if (vx < LEFT_THRESHOLD)
     {
         joyStickPushedtoLeft = true;
     }

     else if (vx < RIGHT_THRESHOLD ){
         joyStickPushedtoRight = true;

     }

     else if (vy < DOWN_THRESHOLD)
     {

       joyStickPushedDown = true;
       vy = 0;
     }

     else if (vy > 15000){
        joyStickPushedUp = true;
         vy = 0;
     }

     if (OneShotSWTimerExpired(&yMoveTimer))
     {

         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);                                            //this will redraw the fret lines
         Graphics_drawLine(&g_sContext,x1, y1, 30, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x1, y1, 4);
         Graphics_fillCircle(&g_sContext, x1, y1, 4);

         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
         Graphics_drawLine(&g_sContext,x1, y1, 30, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x1, y1, 4);
         Graphics_fillCircle(&g_sContext, x1, y1, 4);

         StartOneShotSWTimer(&yMoveTimer);                                                                          //restart the timer
         if (moveToDown)
         {
             red_circle++;
             y1 = y1 + BALL_Y_STEP;

             if((OneShotSWTimerExpired(&yMoveTimer))){
             y2 = y2 + BALL_Y_STEP;

             StartOneShotSWTimer(&yMoveTimer);
             }

             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
             Graphics_fillCircle(&g_sContext, x1, y1, 4);
             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
             Graphics_fillCircle(&g_sContext, x1, y1, 2);
             if (y1 == 110){
                 moveToDown = false;
                 if (y1==110 && joyStickPushedtoLeft == true && BoosterpackTopButton_pressed()){                //this is how we will denote the seq for green note/string being played
                            action->score++;
                            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
                            Graphics_fillCircle(&g_sContext, x1, y1, 4);
                            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
                            Graphics_fillCircle(&g_sContext, x1, y1, 2);
                            y1 = 20;
                            Point(action);
                 }

                 else if (y1 == 110 && joyStickPushedtoLeft == false && !BoosterpackTopButton_pressed()){
                     if (action->score == 0){
                         action->score = 0;
                         Point(action);
                     }

                     else if (action->score !=0){
                         action->score--;
                         Point(action);
                     }
                 }
             }
         }

         else
         {
             y1 = 20;
             if (y1 < 110)
                 moveToDown = true;
         }
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
         Graphics_drawLine(&g_sContext,x1, y1, 30, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x1, y1, 2);
         Graphics_fillCircle(&g_sContext, x1, y1, 2);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
         Graphics_fillCircle(&g_sContext, x1, y1, 2);
    }
 }

 void MoveYellowCircle(Screen *action){                                                                        //move the yellow notes down the screen
     static unsigned int x1 = 30;
     static unsigned int x2 = 50;
     static unsigned int x3 = 70;
     static unsigned int x4 = 90;
     static unsigned int y1 = 20;
     static unsigned int y2 = 20;
     static unsigned int y3 = 20;
     static unsigned int y4 = 20;

     static unsigned vx, vy;
     static bool moveToDown = true;
     static int circle_count = 0;
     static int red_circle = 0;
     static int blue_circle = 0;
     static int yellow_circle = 0;

     static OneShotSWTimer_t yMoveTimer;

     getSampleJoyStick(&vx, &vy);
     bool joyStickPushedtoRight = false;
     bool joyStickPushedtoLeft  = false;
     bool joyStickPushedDown    = false;
     bool joyStickPushedUp      = false;

     static bool init = true;
     if (init)
     {
         InitOneShotSWTimer(&yMoveTimer,
                            &timer0,
                            BALL_TIME_STEP);
         StartOneShotSWTimer(&yMoveTimer);

         init = false;
     }

     if (vx < LEFT_THRESHOLD)
     {
         joyStickPushedtoLeft = true;
     }

     else if (vx < RIGHT_THRESHOLD ){
         joyStickPushedtoRight = true;

     }

     else if (vy < DOWN_THRESHOLD)
     {

       joyStickPushedDown = true;
       vy = 0;
     }

     else if (vy > 15000){
        joyStickPushedUp = true;
         vy = 0;
     }

     if (OneShotSWTimerExpired(&yMoveTimer))
     {

         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
         Graphics_drawLine(&g_sContext,x3, y3, 70, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x3, y3, 4);
         Graphics_fillCircle(&g_sContext, x3, y3, 4);

         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
         Graphics_drawLine(&g_sContext,x3, y3, 70, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x3, y3, 4);
         Graphics_fillCircle(&g_sContext, x3, y3, 4);

         StartOneShotSWTimer(&yMoveTimer);
         if (moveToDown)
         {
             red_circle++;
             y3 = y3 + BALL_Y_STEP;

             if((OneShotSWTimerExpired(&yMoveTimer))){
             y2 = y3 + 20;

             StartOneShotSWTimer(&yMoveTimer);
             }

             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
             Graphics_fillCircle(&g_sContext, x3, y3, 4);
             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
             Graphics_fillCircle(&g_sContext, x3, y3, 2);
             if (y3 == 110){
                 moveToDown = false;
                 if (y3==110 && joyStickPushedUp == true && BoosterpackTopButton_pressed()){                //denote the seq to have the yellow string played
                            action->score++;
                            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
                            Graphics_fillCircle(&g_sContext, x3, y3, 4);
                            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
                            Graphics_fillCircle(&g_sContext, x3, y3, 2);
                            y3 = 20;
                            Point(action);
                 }

                 else if (y3 == 110 && joyStickPushedUp == false && !BoosterpackTopButton_pressed()){
                     if (action->score == 0){
                         action->score = 0;
                         Point(action);
                     }

                     else if (action->score !=0){
                         action->score--;
                         Point(action);
                     }
                 }
             }
         }

         else
         {
             y3 = 20;
             if (y3 < 110)
                 moveToDown = true;
         }
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
         Graphics_drawLine(&g_sContext,x3, y3, 70, 20);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
         Graphics_drawCircle(&g_sContext, x3, y3, 2);
         Graphics_fillCircle(&g_sContext, x3, y3, 2);
         Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
         Graphics_fillCircle(&g_sContext, x3, y3, 2);
    }
 }


void Point(Screen *action){                                                             //this function will update the score for the player
    char text[16] = "";
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    sprintf(text, "%u", action->score);
    Graphics_drawString(&g_sContext, (int8_t *) text, -1, 100, 2, true);
}

void DrawGreenCircle(){                                                                //Draw the green circle at bottom of the screen
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
    Graphics_fillCircle(&g_sContext, 30, 110, 6);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillCircle(&g_sContext, 30, 110, 4);
}

void DrawRedCircle(){                                                                   //Draw Red circle at bottom of screen
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_fillCircle(&g_sContext, 50, 110, 6);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillCircle(&g_sContext, 50, 110, 4);
}

void DrawYellowCircle(){                                                                //Draw yellow circle at bottom of page
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    Graphics_fillCircle(&g_sContext, 70, 110, 6);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillCircle(&g_sContext, 70, 110, 4);
}

void DrawBlueCircle(){                                                                  //Draw Blue circle at bottom of page
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_fillCircle(&g_sContext, 90, 110, 6);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillCircle(&g_sContext, 90, 110, 4);
}

void DrawVerticalOne(){                                                                 //Draw vertial lines
    uint16_t x_pos = 30, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

}

void DrawVerticalTwo(){
    uint16_t x_pos = 50, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

}

void DrawVerticalThree(){
    uint16_t x_pos = 70, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

}

void DrawVerticalFour(){
    uint16_t x_pos = 90, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

}
/////////////////////Draw the frets/////////////////////////
void DrawFirstFret(){
    uint16_t x_pos = 6, y_pos = 50;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        x_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void DrawSecondFret(){
    uint16_t x_pos = 6, y_pos = 70;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        x_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void DrawThirdFret(){
    uint16_t x_pos = 6, y_pos = 90;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        x_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void DrawFourthFret(){
    uint16_t x_pos = 6, y_pos = 110;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        x_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void DrawLeftSide(){
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    uint16_t x_pos = 6, y_pos = 20;
    int i;
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

}

void DrawRightSide(){
    uint16_t x_pos = 122, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void rock (Screen *action, song_t *song){                                                //This is the function that handles game play
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    char string[22] = "Score:";
    Graphics_drawString(&g_sContext, (int8_t *) string, -1, 0, 2, true);
    static OneShotSWTimer_t yMoveTimer;
    InitOneShotSWTimer(&yMoveTimer, &timer0, 500000);
    StartOneShotSWTimer(&yMoveTimer);
    InitSound();
    InitSongList();
    DrawLeftSide();
    DrawRightSide();
    DrawFirstFret();
    DrawSecondFret();
    DrawThirdFret();
    DrawFourthFret();
    DrawVerticalOne();
    DrawVerticalTwo();
    DrawVerticalThree();
    DrawVerticalFour();
    DrawGreenCircle();
    DrawRedCircle();
    DrawYellowCircle();
    DrawBlueCircle();

    if (song->song == Enter_sandman)                                                                    //Select betwwen the different songs
        PlaySong(enter_sandman);
    else if (song->song == Hokie_fight)
        PlaySong(hokie_fight);

    while(1){
        if (OneShotSWTimerExpired(&yMoveTimer)){
            StartOneShotSWTimer(&yMoveTimer);
            MoveCircleDown(action);
            MoveRedCircle(action);
            MoveYellowCircle(action);
            MoveBlueCircle(action);
        }
    }

}

void EndGame(Screen *action){
        Graphics_clearDisplay(&g_sContext);
        char string[22] = "you lose!";
        char string2[22] = "Reset to play!";
        Graphics_drawString(&g_sContext, (int8_t *) string, -1, 0, 50, true);
        Graphics_drawString(&g_sContext, (int8_t *) string2, -1, 0, 68, true);
        action->display = endGame;
}

void Splash (){                                                                                             //Initial screen displayed for three seconds before main menu display
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    char Name[22] = "Jessie Acfalle";
    Graphics_drawString(&g_sContext, (int8_t *) Name, -1, 0, 64, true);
    char Game[22] = "Guitar Hero";
    Graphics_drawString(&g_sContext, (int8_t *) Game, -1, 0, 80, true);
}

void Menu (Screen *action){                                                                                //This is the main menu
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    char Title[22] = ">How to Play";
    Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
    char Play[22]  = "Lets Rock!";
    Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
    char Scores[22] = "Leader Board";
    Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
    action->display = learn;
}

void howToPlay(Screen *action){                                                                             //How to play screen
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    char info[100] = "Hit the right";
    char info3[100] = "buttons at the";
    char info2[22] = "right time to";
    char info4[12] = "score!";
    Graphics_drawString(&g_sContext, (int8_t *) info, -1, 0, 20, true);
    Graphics_drawString(&g_sContext, (int8_t *) info3, -1, 0, 40, true);
    Graphics_drawString(&g_sContext, (int8_t *) info2, -1, 0, 64, true);
    Graphics_drawString(&g_sContext, (int8_t *) info4, -1, 0, 80, true);
}
////////////Handle the different positions during main menu screen/////////////////////
void Down(Screen *action){
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    char Title2[22] = "How to Play";
    Graphics_drawString(&g_sContext, (int8_t *) Title2, -1, 10, 64, true);
    char Play2[22] = ">Lets Rock!";
    Graphics_drawString(&g_sContext, (int8_t *) Play2, -1, 10, 80, true);
    char Scores2[22] = "Leader Board";
    Graphics_drawString(&g_sContext, (int8_t *) Scores2, -1, 10, 100, true);
    action->display = decision;
}

void Down2(Screen *action){
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    char Title2[22] = "How to Play";
    Graphics_drawString(&g_sContext, (int8_t *) Title2, -1, 10, 64, true);
    char Play2[22] = "Lets Rock!";
    Graphics_drawString(&g_sContext, (int8_t *) Play2, -1, 10, 80, true);
    char Scores2[22] = ">Leader Board";
    Graphics_drawString(&g_sContext, (int8_t *) Scores2, -1, 10, 100, true);
    action->posy++;
    action->display = scores;
}

void Up(Screen *action){
    if(action->display == learn){
        Graphics_clearDisplay(&g_sContext);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        char Title[22] = ">How to Play";
        Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
        char Play[22]  = "Lets Rock!";
        Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
        char Scores[22] = "Leader Board";
        Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
        action->posy = 0;
        down = 0;
    }

    else if (action->display == decision){
        Graphics_clearDisplay(&g_sContext);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        char Title[22] = ">How to Play";
        Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
        char Play[22]  = "Lets Rock!";
        Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
        char Scores[22] = "Leader Board";
        Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
        down = 0;
        action->posy = 0;
    }

    else if (action->display == scores){
        Graphics_clearDisplay(&g_sContext);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        char Title[22] = "How to Play";
        Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
        char Play[22]  = ">Lets Rock!";
        Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
        char Scores[22] = "Leader Board";
        Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
        action->display = play;;
        action->posy = 0;
        down = 0;
    }

    else if (action->display == endGame){
        Graphics_clearDisplay(&g_sContext);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        char Title[22] = ">How to Play";
        Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
        char Play[22]  = "Lets Rock!";
        Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
        char Scores[22] = "Leader Board";
        Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
        down = 0;
        action->posy = 0;
    }

}

int main(void)
{

    Screen action;
    song_t song;
    action.pos = 0;
    int three_count = 0;
    int up = 0;

    static OneShotSWTimer_t yMoveTimer;

    Graphics_Context g_sContext;

    InitGraphics(&g_sContext);
    initialize();
    InitOneShotSWTimer(&yMoveTimer, &timer0, 1000000);
    StartOneShotSWTimer(&yMoveTimer);

//    InitSound();
//    InitSongList();
////    PlaySong(enter_sandman);
////    PlaySong(hokie_fight);


    while(1){
    if (Timer32_getValue(TIMER32_0_BASE == 0)){
        three_count++;

    if (three_count < THREE_SEC){
        Splash();
    }

    else if (three_count == THREE_SEC){
            Menu(&action);
        }
    }
    getSampleJoyStick(&vx, &vy);                                            //Get the joystick sample data
    bool joyStickPushedDown = false;
    bool joyStickPushedUp = false;

    if (vy < DOWN_THRESHOLD)                                                //Handle the different joystick movements and update
    {

      joyStickPushedDown = true;
      down++;
      vy = 0;
    }

    else if (vy > 15000){
       joyStickPushedUp = true;
        up++;
        vy = 0;
    }
      if (down == 1 && joyStickPushedDown == true){
              Down(&action);
      }

      else if (down == 2 && joyStickPushedDown == true)
      {
        Down2(&action);
     }

      else if (up == 1  &&  joyStickPushedUp == true){
          action.display = decision;
          Up(&action);
      }

      else if (up == 2 &&  joyStickPushedUp == true){
          action.display = learn ;
          Up(&action);

      }

      else if (up == 3 && joyStickPushedUp == true){
          action.display = scores;
          Up(&action);
          up = 0;
      }

    if (BoosterpackTopButton_pressed()){
        if (action.display == learn){
            howToPlay(&action);
        }

        else if (action.display == decision){
            SongChoice(&action, &song);
        }
    }
    else if (BoosterpackBottomButton_pressed()){
        if (action.display == learn){
           Menu(&action);
           action.display = learn;
        }
    }
  }
}
void initialize()
{
    // stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    Timer32_initModule(TIMER32_0_BASE, // There are two timers, we are using the one with the index 0
                       TIMER32_PRESCALER_1, // The prescaler value is 1; The clock is not divided before feeding the counter
                       TIMER32_32BIT, // The counter is used in 32-bit mode; the alternative is 16-bit mode
                       TIMER32_PERIODIC_MODE); //This options is irrelevant for a one-sh
    Timer32_setCount(TIMER32_0_BASE, ONE_SEC);  // The count related to the period of the timer
    Timer32_startTimer(TIMER32_0_BASE, false);

    // initialize the boosterPack LEDs and turn them off except for red LED
    initialize_BoosterpackLED_red();
    initialize_BoosterpackLED_green();
    initialize_BoosterpackLED_blue();
    initialize_LaunchpadLED1();
    initialize_LaunchpadLED2_red();
    initialize_LaunchpadLED2_blue();
    initialize_LaunchpadLED2_green();

    turnOn_BoosterpackLED_red();
    turnOff_BoosterpackLED_green();
    turnOff_BoosterpackLED_blue();
    turnOff_LaunchpadLED1();
    turnOff_LaunchpadLED2_red();
    turnOff_LaunchpadLED2_blue();
    turnOff_LaunchpadLED2_green();

    initHWTimer0();
    initHWTimer1();

    initADC();
    initJoyStick();
    startADC();
}

// This FSM has two inputs each of them the FSM if a button has been pushed or not
// The FSM has three states: Red, Green, Blue. The initial state is Red
// The FSM has three outputs, each output is a boolean that decides if an LED should be on or off
// When the left button is pressed, the FSM goes
void ModifyLEDColor(bool leftButtonWasPushed, bool rightButtonWasPushed)
{
    typedef enum {red, green, blue} LED_state_t;

    static LED_state_t BoosterLED = red;

    // outputs of the FSM and their default
    bool toggleGreen = false;
    bool toggleBlue = false;
    bool toggleRed = false;

    switch(BoosterLED)
    {
    case red:
        if (leftButtonWasPushed)
        {
            // next state
            BoosterLED = green;

            //outputs
            // This turns green on
            toggleGreen = true;

            // This turns red off
            toggleRed = true;
        }
        else if (rightButtonWasPushed)
        {
            BoosterLED = blue;

            //outputs
            toggleBlue = true;
            toggleRed = true;
        }
        break;
    case green:
        if (leftButtonWasPushed)
        {
            // next state
            BoosterLED = blue;

            //outputs
            toggleBlue = true;
            toggleGreen = true;
        }
        else if (rightButtonWasPushed)
        {
            BoosterLED = red;

            //outputs
            toggleRed = true;
            toggleGreen = true;
        }
        break;
    case blue:
        if (leftButtonWasPushed)
        {
            // next state
            BoosterLED = red;

            //outputs
            toggleRed = true;
            toggleBlue = true;
        }
        else if (rightButtonWasPushed)
        {
            BoosterLED = green;

            //outputs
            toggleGreen = true;
            toggleBlue = true;
        }
    }

    if (toggleRed)
        toggle_BoosterpackLED_red();

    if (toggleGreen)
        toggle_BoosterpackLED_green();

    if (toggleBlue)
        toggle_BoosterpackLED_blue();

}
