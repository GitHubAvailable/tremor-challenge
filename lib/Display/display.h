/**
 * display.h - Library of the UI display functions for the 
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
 * Modified 27 April 2024 by Mark Liu
 */

#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include "report.h"


/*!
    @brief turn off the status LED and all neopixels
*/
void clearUI();

/*!
    @brief update UI to show a measurement just started
    @details turn on status LED
*/
void showStart();

/*!
    @brief update neopixels to reflect the current progress
    @param percent a `0` to `100` value representing the percent of 
    measuring time past respect to total measuring time
    @details lightup first `percent / 10` neopixels with the intensity 
    of the last one being `percent % 10` times of the regular brightness
    @example if percent is `69`, turn on neopixel 0-6, with neopixel 6 
    having 90% of the regular brightness
*/
void showProgress(uint8_t percent);

/*!
    @brief update neopixels to reflect the test result
    @param report a reference to the `Report` to be displayed
    @details when no tremor detected, turn on all neopixels in the same way 
    as the completed measuring view in measuring state; if tremor 
    detected lightup first `percent / 10` neopixel at regular intensity
    @example if `report.hasTremor` is `True` and `report.percent` is `69`, 
    turn on neopixel 0-6 all with regular intensity
*/
void displayReport(Report &report);

#endif