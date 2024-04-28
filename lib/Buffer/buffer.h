/**
 * buffer.h - Library of acceleration measurement buffer for the 
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

#ifndef Buffer_h
#define Buffer_h

#include <Arduino.h>

#define BUFFER_LENGTH 1024 // must be a power of 2

#define LENGTH(x, y, z) sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

/** 
 * Buffer is used to store magnitude of 
 * acceleration measurements.
*/
struct Buffer
{
    private:
        // TODO: must be public or set friend for parser.

        /** buffer for acceleration measurements on x, y, z axes */
        float buffer[3][BUFFER_LENGTH];

        /** index of next element to be inserted, same for all axes */
        int next;
        
        // bool isFull = false;
    
    public:
        float get(uint8_t axis, uint16_t index) const { return this->buffer[axis][index]; }
        void set(uint8_t axis, uint16_t index, float val) { this->buffer[axis][index] = val; }
        
        /*!
            @brief add a pair of acceleration components
            @param x a float value corresponding to the acceleration on the 
            x-axis.
            @param y a float value corresponding to the acceleration on the 
            x-axis.
            @param z a float value corresponding to the acceleration on the 
            x-axis.
        */
        void add(float x, float y, float z);
} buffer;

#endif