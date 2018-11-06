#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "ButtonLED_HAL.h"
#include "graphics_HAL.h"
#include "ADC_HAL.h"
#include "sound.h"
#include "song.h"
#include "Lab3.h"

extern HWTimer_t timer0, timer1;
Graphics_Context g_sContext;


#define LEFT_THRESHOLD  0x1000
#define DURATION 100
#define THREE_SEC 40
#define ONE_SEC 48000000
#define DOWN_THRESHOLD  300
#define UP_THRESHOLD    0x1000

extern song_t enter_sandman;
extern song_t hokie_fight;
Graphics_Context g_sContext;
static int down = 0;

void DrawVerticalOne(){
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

void DrawRightSide(){
    uint16_t x_pos = 122, y_pos = 20;
    int i;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }
}

void rock (){
    Graphics_clearDisplay(&g_sContext);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);


    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    uint16_t x_pos = 6, y_pos = 20;
    int i;
    for (i =0; i < 114; i++){
        y_pos++;
        Graphics_drawPixel(&g_sContext, x_pos, y_pos);
    }

    DrawRightSide();
    DrawFirstFret();
    DrawSecondFret();
    DrawThirdFret();
    DrawFourthFret();
    DrawVerticalOne();
    DrawVerticalTwo();
    DrawVerticalThree();
    DrawVerticalFour();

}

void Splash (){
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    char Name[22] = "Jessie Acfalle";
    Graphics_drawString(&g_sContext, (int8_t *) Name, -1, 0, 64, true);
    char Game[22] = "Guitar Hero";
    Graphics_drawString(&g_sContext, (int8_t *) Game, -1, 0, 80, true);
}

void Menu (Screen *action){
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

void howToPlay(Screen *action){
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
    action->posy++;
    action->display = play;
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

    else if (action->display == play){
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

}

int main(void)
{

    Screen action;
    action.pos = 0;
    int three_count = 0;
    int up = 0;
    unsigned vx, vy;

    Graphics_Context g_sContext;

    InitGraphics(&g_sContext);
    initialize();

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
    getSampleJoyStick(&vx, &vy);
    bool joyStickPushedDown = false;
    bool joyStickPushedUp = false;

    if (vy < DOWN_THRESHOLD)
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
          action.display = play;
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
        else if (action.display == play){
            rock();
        }
    }
        else if (BoosterpackBottomButton_pressed()){
                Menu(&action);
                action.display = learn;
        }

    }
 }
    //TODO: comment out this part once you complete part 3
    /*
    InitSound();
    InitSongList();
    PlaySong(enter_sandman);
    PlaySong(hokie_fight);
*/


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


