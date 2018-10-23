/*
 * sound.c
 *
 *  Created on: Oct 21, 2018
 *      Author: Leyla
 */


#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "sound.h"
#include "Timer32_HAL.h"


#define SYSTEMCLOCK 48000000
extern HWTimer_t timer0;

void InitSound() {
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P2,
            GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
}

void PlayNote(song_note_t songNote) {

double toneFreq[49] =
       {
        0.00,   // silent
        16.35,  // c0
        18.35,  // d0
        20.60,  // e0
        21.83,  // f0
        24.50,  // g0
        27.50,  // a0
        30.87,  // b0
        21.22,  // f0 flat
        29.14,  // b0 flat
        32.70,  // c1
        36.71,  // d1
        41.20,  // e1
        43.65,  // f1
        49.00,  // g1
        55.00,  // a1
        61.74,  // b1
        65.41,  // c2
        73.42,  // d2
        82.41,  // e2
        87.31,  // f2
        98.00,  // g2
        110.00, // a2
        123.47, // b2
        130.81, // c3
        146.83, // d3
        164.81, // e3
        174.61, // f3
        196.00, // g3
        220.00, // a3
        246.94, // b3
        261.63, // C4
        293.66, // D4
        329.63, // E4
        349.63, // F4
        392.00, // G4
        440.00, // A4
        493.88, // B4
        523.25, // C5
        587.33, // D5
        659.25, // E5
        698.46, // F5
        783.99, // G5
        880.00, // A5
        987.77, // B5
        739.99, // F5 sharp
        369.99, // F4 sharp
        369.99, // g4 flat
        1046.50 // C6
       };

   Timer_A_PWMConfig pwmConfig;
   pwmConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
   pwmConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
   pwmConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
   pwmConfig.compareOutputMode =  TIMER_A_OUTPUTMODE_RESET_SET;


   pwmConfig.timerPeriod = (double) SYSTEMCLOCK/ (double) 64/ toneFreq[songNote.note_name];
   pwmConfig.dutyCycle   = pwmConfig.timerPeriod /2;

   OneShotSWTimer_t noteLength;
   InitOneShotSWTimer(&noteLength, &timer0, songNote.note_length*1000);
   StartOneShotSWTimer(&noteLength);

   if (songNote.note_name != note_silent)
       Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
   while (!OneShotSWTimerExpired(&noteLength)) ;
   Timer_A_stopTimer(TIMER_A0_BASE);

}
