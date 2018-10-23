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

    unsigned int toneFreq[17] =
    {
     0,   // silent
     262, // C4
     294, // D4
     330, // E4
     349, // F4
     370, // FS4
     392, // G4
     440, // A4
     494, // B4
     524, // C5
     587, // D5
     659, // E5
     698, // F5
     740, // FS5
     784, // G5
     880, // A5
     988, // B5
     1047 // C6
    };

   Timer_A_PWMConfig pwmConfig;
   pwmConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
   pwmConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
   pwmConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
   pwmConfig.compareOutputMode =  TIMER_A_OUTPUTMODE_RESET_SET;
   pwmConfig.timerPeriod = SYSTEMCLOCK/64/toneFreq[songNote.note_name];
   pwmConfig.dutyCycle   = pwmConfig.timerPeriod /2;

   OneShotSWTimer_t noteLength;
   InitOneShotSWTimer(&noteLength, &timer0, songNote.note_length*1000);
   StartOneShotSWTimer(&noteLength);

   if (songNote.note_name != note_silent)
       Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
   while (!OneShotSWTimerExpired(&noteLength)) ;
   Timer_A_stopTimer(TIMER_A0_BASE);

}
