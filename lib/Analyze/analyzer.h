/**
 * analyze.h - Library of the data processing functions for the 
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
 * Modified 29 April 2024 by Mark Liu
 */
#ifndef Analyzer_h
#define Analyzer_h

#include <arduinoFFT.h>
#include "buffer.h"
#include "report.h"

#define LOW_FREQ 3
#define HIGH_FREQ 6

#define TOTAL_MEASURES 500

struct Analyzer
{
    private:
        /** reference to the buffer where the data are stored */
        struct Buffer &buffer;

        /** imaginary parts for FFT, will be set to 0 */
        float imags[BUFFER_SIZE];

        /** reference to the report where results are written to */
        struct Report &report;

        /** an fft object used to analyze signals */
        ArduinoFFT<float> fft;
    
    public:
        /*!
            @brief construct an analyzer using a specific buffer 
            and a Report struct
            @param buffer a reference to the buffer where the 
            data are stored
            @param report a reference to the report where results 
            are written to
        */
        Analyzer(struct Buffer &buffer, struct Report &report);

        /*!
            @brief measure the current acceleration and store it in buffer
        */
        void measure();

        /*!
            @brief analyze frequency of wave data in the current buffer 
            in place and update the report
            @details perform FFT on the buffer and check if desired 
            frequency is present and calculate intensity as the averaged
            magnitude over the square of the frequency
        */
        void analyze();
};

#endif