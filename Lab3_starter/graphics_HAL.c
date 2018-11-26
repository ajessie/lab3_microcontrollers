/*
 * graphics_HAL.c
 *
 *  Created on: Oct 18, 2018
 *      Author: Leyla
 */

#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "Timer32_HAL.h"
Graphics_Context g_sContext;

// 100ms in us unit is 100,000
#define T2000MS_IN_US 2000


#define BALL_Y_STEP 10                   // The ball moves in y direction 10 pixesl per step
#define BALL_TIME_STEP T2000MS_IN_US      // We update the location of the ball evey 100 ms
// The above two numbers result in 10/100ms = 10/0.1s = 100 pixel/sec movement for the ball

extern HWTimer_t timer0, timer1;

void make_5digit_NumString(unsigned int num, int8_t *string)
{
    string[0]= (        num  / 10000) +'0';
    string[1]= ((num%10000) / 1000) +'0';
    string[2]= ((num%1000) / 100) +'0';
    string[3]= ((num%100) / 10) +'0';
    string[4]= ((num%10) / 1) +'0';
    string[5]= 0;
}

void drawXY(Graphics_Context *g_sContext_p, unsigned int x, unsigned int y)
{
    int8_t string[6];

    Graphics_drawString(g_sContext_p, "x=", -1, 10, 5, true);
    make_5digit_NumString(x, string);
    Graphics_drawString(g_sContext_p, string, -1, 30, 5, true);

    Graphics_drawString(g_sContext_p, "y=", -1, 10, 15, true);
    make_5digit_NumString(y, string);
    Graphics_drawString(g_sContext_p, string, -1, 30, 15, true);
}


void draw_Base(Graphics_Context *g_sContext_p)
{
    Graphics_Rectangle R;
    R.xMin = 0;
    R.xMax = 127;
    R.yMin = 32;
    R.yMax = 96;

    Graphics_drawRectangle(g_sContext_p, &R);
    Graphics_fillCircle(g_sContext_p, 63, 63, 10);
    Graphics_drawString(g_sContext_p, "circle move #:", -1, 10, 100, false);
    Graphics_drawString(g_sContext_p, "000", -1, 10, 110, true);
}

void make_3digit_NumString(unsigned int num, int8_t *string)
{
    string[0]= (num/100)+'0';
    string[1]= ((num%100) / 10) + '0';
    string[2]= (num%10)+'0';
    string[3] =0;

}


void MoveCircle(Graphics_Context *g_sContext_p, bool moveToLeft, bool moveToRight)
{
    static unsigned int x = 63;
    static unsigned int y = 63;
    static bool moveToDown = true;

    static unsigned int moveCount = 0;
    int8_t string[4];

    static OneShotSWTimer_t yMoveTimer;

    static bool init = true;
    if (init)
    {
        //
        InitOneShotSWTimer(&yMoveTimer,
                           &timer0,
                           BALL_TIME_STEP);
        StartOneShotSWTimer(&yMoveTimer);

        init = false;
    }

    if (OneShotSWTimerExpired(&yMoveTimer))
    {
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_fillCircle(g_sContext_p, x, y, 10);

        StartOneShotSWTimer(&yMoveTimer);
        if (moveToDown)
        {
            y = y + BALL_Y_STEP;
            if (y > 80)
                moveToDown = false;
        }
        else
        {
            y = y - BALL_Y_STEP;
            if (y < 50)
                moveToDown = true;
        }

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_fillCircle(g_sContext_p, x, y, 10);
    }

    if ((moveToLeft && (x>20)) || (moveToRight && (x<110)))
    {
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_fillCircle(g_sContext_p, x, y, 10);

        if (moveToLeft)
            x = x-10;
        else
            x = x+10;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_fillCircle(g_sContext_p, x, y, 10);

        moveCount++;
        make_3digit_NumString(moveCount, string);
        Graphics_drawString(g_sContext_p, string, -1, 10, 110, true);
    }

}
void InitFonts() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}


void InitGraphics(Graphics_Context *g_sContext_p) {

    InitFonts();
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}
