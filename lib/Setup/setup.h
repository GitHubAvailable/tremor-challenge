/**
 * setup.h - Library of device setup functions for the 
 * Parkinsonian Tremor Detector.
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

#ifndef Setup_h
#define Setup_h

#include "report.h"

#define START_END PD4 // pin of start/end button
#define STATUS_LED PC7 // pin of status LED

void setupButtons();
void setupLED();
void setupTimer();

/*!
    @brief disable Timer 1 overflow interrupt.
*/
void cliTimer();

/*!
    @brief enable Timer 1 overflow interrupt.
*/
void seiTimer();

/*!
    @brief reset the report for measurement
    @note must be called before each test to ensure the 
    correctness of `avgAmplitude`
    @param the Report to be reset
*/
void resetReport(Report &report);

#endif