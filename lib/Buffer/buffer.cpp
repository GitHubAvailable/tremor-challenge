/**
 * buffer.cpp - Implementation of the acceleration measurement 
 * buffer of the Parkinsonion Tremor Detector.
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

#include "buffer.h"

void Buffer::add(float x, float y, float z)
{
    // Add the acceleration components to corresponding array.
    this->buffer[X_AXIS][next] = x;
    this->buffer[Y_AXIS][next] = y;
    this->buffer[Z_AXIS][next] = z;
    
    (++next) %= BUFFER_LENGTH;
}