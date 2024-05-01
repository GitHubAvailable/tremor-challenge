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

#define BUFFER_SIZE 128 // must be a power of 2

#define LENGTH(x, y, z) sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

/** 
 * Buffer is used to store magnitude of 
 * acceleration measurements.
*/
struct Buffer
{
    private:
        // TODO: must be public or set friend for parser.

        /** buffer for acceleration magnitude */
        float buffer[BUFFER_SIZE];

        /** index of next element to be inserted, same for all axes */
        int next;
        
        /** if the buffer is full */
        bool isFull = false;
    
    public:
        float get(uint16_t index) const { return this->buffer[index]; }
        void set(uint16_t index, float val) { this->buffer[index] = val; }

        bool isBufferFull() const { return isFull; }

        /*!
            @brief add a magnitude of acceleration value
            @param val a flat value corresponding to the magnitude of the
            acceleration.
        */
        void add(float val);

        /*!
            @brief add a magnitude of acceleration by its components
            @param x a float value corresponding to the acceleration on the 
            x-axis
            @param y a float value corresponding to the acceleration on the 
            y-axis
            @param z a float value corresponding to the acceleration on the 
            z-axis
        */
        void add(float x, float y, float z);

        /*!
            @brief reset the buffer for storing new measurements
            @details reset `next` and `isFull`
        */
        void reset();
        
        friend struct Analyzer;

};

#endif