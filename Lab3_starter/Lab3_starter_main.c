#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "ButtonLED_HAL.h"
#include "graphics_HAL.h"
#include "ADC_HAL.h"
#include "sound.h"
#include "song.h"

extern HWTimer_t timer0, timer1;


// This function initializes all the peripherals except graphics
void initialize();
void ModifyLEDColor(bool leftButtonWasPushed, bool rightButtonWasPushed);
void Splash();
void drawDisplay();

#define LEFT_THRESHOLD  0x1000
#define DURATION 100
#define THREE_SEC 40
#define ONE_SEC 48000000
#define DOWN_THRESHOLD  300

extern song_t enter_sandman;
extern song_t hokie_fight;
Graphics_Context g_sContext;

int main(void)
{
    int three_count = 0;
    int down = 0;
    unsigned vx, vy;

    Graphics_Context g_sContext;

    InitGraphics(&g_sContext);

    initialize();

    while(1){
    if (Timer32_getValue(TIMER32_0_BASE == 0))
        three_count++;
    getSampleJoyStick(&vx, &vy);
    bool joyStickPushedDown = false;
    bool joyStickPushedUp = false;
    drawXY(&g_sContext, vx, vy);

    if (vy < DOWN_THRESHOLD)
    {
      joyStickPushedDown = true;
      down++;


      if (down == 1){
          Graphics_clearDisplay(&g_sContext);
          Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
          Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
          char Title2[22] = "How to Play";
          Graphics_drawString(&g_sContext, (int8_t *) Title2, -1, 10, 64, true);
          char Play2[22] = ">Lets Rock!";
          Graphics_drawString(&g_sContext, (int8_t *) Play2, -1, 10, 80, true);
          char Scores2[22] = "Leader Board";
          Graphics_drawString(&g_sContext, (int8_t *) Scores2, -1, 10, 100, true);


      }
      else if (down == 2)
      {
          Graphics_clearDisplay(&g_sContext);
          Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
          Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
          char Title2[22] = "How to Play";
          Graphics_drawString(&g_sContext, (int8_t *) Title2, -1, 10, 64, true);
          char Play2[22] = "Lets Rock!";
          Graphics_drawString(&g_sContext, (int8_t *) Play2, -1, 10, 80, true);
          char Scores2[22] = ">Leader Board";
          Graphics_drawString(&g_sContext, (int8_t *) Scores2, -1, 10, 100, true);
      }
    }



    if(three_count < THREE_SEC){
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_SEA_GREEN);
    char Name[22] = "Jessie Acfalle";
    Graphics_drawString(&g_sContext, (int8_t *) Name, -1, 10, 64, true);
    char Game[22] = "Guitar Hero";
    Graphics_drawString(&g_sContext, (int8_t *) Game, -1, 10, 80, true);
    }

    else if (three_count == THREE_SEC){
        Graphics_clearDisplay(&g_sContext);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        char Title[22] = ">How to Play";
        Graphics_drawString(&g_sContext, (int8_t *) Title, -1, 10, 64, true);
        char Play[22]  = "Lets Rock!";
        Graphics_drawString(&g_sContext, (int8_t *) Play, -1, 10, 80, true);
        char Scores[22] = "Leader Board";
        Graphics_drawString(&g_sContext, (int8_t *) Scores, -1, 10, 100, true);
    }
 }




    button_t LauchpadLeftButton;
    initButton(&LauchpadLeftButton, GPIO_PORT_P1, GPIO_PIN1, &timer0);

    button_t LauchpadRightButton;
    initButton(&LauchpadRightButton, GPIO_PORT_P1, GPIO_PIN4, &timer0);

//    draw_Base(&g_sContext);
//    unsigned vx, vy;

    //TODO: comment out this part once you complete part 3
    /*
    InitSound();
    InitSongList();
    PlaySong(enter_sandman);
    PlaySong(hokie_fight);
*/


//    while (1)
//    {
//        bool leftButtonPushed = ButtonPushed(&LauchpadLeftButton);
//        bool rightButtonPushed = ButtonPushed(&LauchpadRightButton);
//
//        if (LaunchpadLeftButton_pressed())
//            turnOn_LaunchpadLED1();
//        else
//            turnOff_LaunchpadLED1();
//
//        if (LaunchpadRightButton_pressed())
//            turnOn_LaunchpadLED2_red();
//        else
//            turnOff_LaunchpadLED2_red();
//
//
//        ModifyLEDColor(leftButtonPushed,rightButtonPushed);
//        MoveCircle(&g_sContext, leftButtonPushed,rightButtonPushed);
//
//        getSampleJoyStick(&vx, &vy);
//        bool joyStickPushedtoRight = false;
//        bool joyStickPushedtoLeft = false;
//        drawXY(&g_sContext, vx, vy);
//
//        if (vx < LEFT_THRESHOLD)
//        {
//            joyStickPushedtoLeft = true;
//        }
//
//        ModifyLEDColor(joyStickPushedtoLeft,joyStickPushedtoRight);
//        MoveCircle(&g_sContext, joyStickPushedtoLeft,joyStickPushedtoRight);
//
//    }
}

void drawDisplay(){

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

//void Splash(){
//    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
//
//    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_SEA_GREEN);
//
//    char Name[22] = "Jessie Acfalle";
//    Graphics_drawString(&g_sContext, (int8_t *) Name, -1, 1, 100, true);
//
//}

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


