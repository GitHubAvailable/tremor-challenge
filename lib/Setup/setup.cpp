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