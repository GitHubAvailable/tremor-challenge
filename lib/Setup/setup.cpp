/**
 * setup.cpp - Implementation of the setup functions of 
 * the Parkinsonion Tremor Detector.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the MIT-0 License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * MIT-0 License for more details.
 * 
 * Modified 22 April 2024 by Mark Liu
 */

#include <Arduino.h>
#include "setup.h"

void setupButtons()
{
    DDRD &= ~(OUTPUT << START_END); // set start/end button to INPUT.
}

void setupLED()
{
    DDRC |= (OUTPUT << STATUS_LED); // set status LED to OUTPUT.
    
    PORTC &= ~(HIGH << STATUS_LED); // default value is LOW.
}

void setupTimer()
{
    /* Setup Timer1 for triggering measurement. */
    /**
     * WGM (1111): Fast PWM, OCR1A as TOP
     * CS (001): Prescaler 1
     * Clock Top: 62500 (8MHz / 128Hz = 62500)
     * Enable Timer 1 Overflow Interrupt
     */
    TCCR1A |= (HIGH << WGM11)
            | (HIGH << WGM10);
    TCCR1B |= (HIGH << WGM13)
            | (HIGH << WGM12)
            | (HIGH << CS10);
    OCR1A = 62500;
    TIMSK1 |= (HIGH << TOIE1);
}

void cliTimer() { TIMSK1 &= ~(HIGH << TOIE1); }
void seiTimer() { TIMSK1 |= (HIGH << TOIE1); }

void resetReport(Report &report)
{
    report.total = 0;
    report.detected = 0;
    report.avgAmplitude = 0;
}