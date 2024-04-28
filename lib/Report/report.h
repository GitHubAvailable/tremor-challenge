/**
 * report.h - Library of tremor report structure for the 
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

#ifndef Report_h
#define Report_h

#include <Arduino.h>

/** 
 * Report is used to store the result of 
 * current measurements of Parkinsonian tremor.
*/
struct Report
{
    /** if the user has Parkinsonian tremor */
    bool hasTremor = false;

    /** the relative intensity of the Parkinsonian tremor */
    uint8_t intensity = 0;
} report;

#endif