/*
 * sound.c
 *
 *  Created on: Oct 21, 2018
 *      Author: Leyla
 */

// TODO: In this file, only change the places you see the TODO sign. It is OK to change other places as well, but to get started you need to change those parts

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "sound.h"
#include "Timer32_HAL.h"


#define SYSTEMCLOCK 48000000
extern HWTimer_t timer0;

// TODO: Choose the right port and pin for the buzzer. This will allow the Timer_A to drive the buzzer
// Currently, Port 1 and Pin 0 are chosen here, but they may or may not be correct. They are simply place holders.
// If you ctrl+click, you will see other options
void InitSound() {
    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P1,
            GPIO_PIN0,
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

    // Initialize the one shot timer
    OneShotSWTimer_t noteLength;

    // If you study the interface, you will see the time (the third argument is given in us). Since
    // the input her is in ms, we need to multiply it with 1000
    InitOneShotSWTimer(&noteLength, &timer0, songNote.note_length*1000);

    // Let's start the timer that decides how long to play the note
    StartOneShotSWTimer(&noteLength);

    // If note is not silent, we are playing it
    if (songNote.note_name != note_silent)
        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);

    // We wait until the note is played for the duration it is supposed to
    while (!OneShotSWTimerExpired(&noteLength)) ;

    // We stop the PWM
    Timer_A_stopTimer(TIMER_A0_BASE);

}
