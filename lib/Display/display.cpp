/**
 * display.cpp - Implementation of the UI display functions 
 * of the Parkinsonion Tremor Detector.
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

#include <Adafruit_CircuitPlayground.h>
#include "display.h"
#include "setup.h"

#define PROGRES_R 0
#define PROGRES_G 200
#define PROGRES_B 0

#define INTENS_COLOR 200, 0, 0
#define PROGRES_COLOR PROGRES_R, PROGRES_G, PROGRES_B

void clearUI()
{
    PORTC &= ~(HIGH << STATUS_LED);
    CircuitPlayground.clearPixels();
}

void showStart()
{
    PORTC |= (HIGH << STATUS_LED);
}

void showProgress(uint8_t percent)
{
    CircuitPlayground.clearPixels();

    // Turn on neopixel 0-9 by percent 0-99.
    uint8_t num, last;
    
    num = min(percent, 100) / 10;

    // Turn on first `num - 1` neopixels in `PROGRES_COLOR`.
    for (uint8_t index = 0; index < num; index++)
    {
        CircuitPlayground.setPixelColor(index, PROGRES_COLOR);
    }

    if (num == 10)
    {
        // All neopixels are on.
        return;
    }

    last = min(percent, 100) % 10;

    // Turn on `num` with brightness proportional to actual progress.
    CircuitPlayground.setPixelColor(
        num, PROGRES_R, last * PROGRES_G / 100, PROGRES_B
    );
}

void showIntensity(uint8_t percent)
{
    CircuitPlayground.clearPixels();

    // Light up neopixel 0-9 by percent 0-99.
    const int num = min(percent, 99) / 10;

    for (uint8_t index = 0; index <= num; index++)
    {
        CircuitPlayground.setPixelColor(index, INTENS_COLOR);
    }
}

void displayReport(Report &report)
{
    if (!report.hasTremor)
    {
        // No tremor detected.
        PORTC &= ~(HIGH << STATUS_LED);
        showProgress(100);
        return;
    }

    // Tremor detected.
    PORTC |= (HIGH << STATUS_LED);

    // Light neopixels according to intensity.
    showIntensity(report.intensity);
}