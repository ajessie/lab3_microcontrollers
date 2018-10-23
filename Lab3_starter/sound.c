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

void PlayNote(tnote n, unsigned ms) {

    // This array simply keeps the frequencies of the tones we are going to play
    unsigned int toneFreq[17] =
    {
     0,   // silent
     262, // C4
     294, // D4
     330, // E4
     349, // F4
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

   // The struct that holds all the info for PWM driving the speaker
   Timer_A_PWMConfig pwmConfig;

   // The clock source of the Timer_A (like most other examples in this course we use the system clock)
   pwmConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;

   // TODO: The clock divider, you need to choose this flag. Currently this value is set to 1. If you hold ctrl key and click on the TIMER_A_CLOCKSOURCE_DIVIDER_1 macro
   // you will see the other options, there are multiple options between 1 and 64 (not all numbers are possible)
   pwmConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;

   // TODO: The Timer_A register connected to the speaker. Currently, this is set to TIMER_A_CAPTURECOMPARE_REGISTER_0, which could or could not be the right answer.
   // You need to find this information from the combination of the BoosterPack and Launchpad user guides.
   // The printed quick guide can be the best place to find this information. If you hold the ctrl key and click on TIMER_A_CAPTURECOMPARE_REGISTER_0, you will see
   // the other options. (Refer to HW6 and how you drove RGB colors)
   pwmConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;

   // TODO: See if this mode suits you. If not, change it to something else. Ctrl+click can show you other modes. Refer to the user guide for details.
   pwmConfig.compareOutputMode =  TIMER_A_OUTPUTMODE_RESET_SET;

   // TODO: Choose the period of the PWM in terms of number of counter cycles. Currently, it is set to SYSTEMCLOCK which is 48M
   // You need to generate a different PWM for each note, pay attention to the clock divider you chose earlier.
   // Hint: you need to incorporate toneFreq to complete this part.
   pwmConfig.timerPeriod = SYSTEMCLOCK;

   // TODO: This is the duty cycle in terms of counter cycles. Currently it is set equal to pwmConfig.timerPeriod, which means 100% duty cycle.
   // Pay attention to the duty cycle of a musical note. Multiply the current value with a fraction to achieve that.
   pwmConfig.dutyCycle   = pwmConfig.timerPeriod;

   // Inititalize the one shot timer
   OneShotSWTimer_t noteLength;
   // If you study the interface, you will see the time (the third argument is given in us). Since
   // the input her is in ms, we need to multiply it with 1000
   InitOneShotSWTimer(&noteLength, &timer0, ms*1000);
   // Let's start the timer that decides how long to play the note
   StartOneShotSWTimer(&noteLength);

   // If note is not silent, we are playing it
   if (n != note_silent)
       Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

   // We wait until the note is played for the duration it is supposed to
   while (!OneShotSWTimerExpired(&noteLength)) ;

   // We stop the PWM
   Timer_A_stopTimer(TIMER_A0_BASE);

}
