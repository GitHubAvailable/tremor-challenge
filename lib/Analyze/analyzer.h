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

#define TOTAL_MEASURES 50

struct Analyzer
{
    private:
        /** reference to the buffer where the data are stored */
        struct Buffer &buffer;

        /** imaginary parts for FFT, will be set to 0 */
        float imags[BUFFER_SIZE];

        /** the report that stores the temporary report */
        struct Report record;

        /** reference to the report where final results are written to */
        struct Report &report;

        /** an fft object used to analyze signals */
        ArduinoFFT<float> fft;

        /*!
            @brief find the max peak between `minFreq` and `maxFreq`, inclusive, 
            set `freq` to `-1` if doesn't find or parameters invalid.
            @param freq a reference to the variable to store the frequency 
            of the peak
            @param magnitude a reference to the variable to store the 
            magnitude of the peak
            @param minFreq a nonnegative float value corresponding to 
            the minimum of the frequency range
            @param maxFreq a nonnegative float value corresponding to 
            the maximum of the frequency range
            @note should only be called after FFT on `buffer`
        */
        void findMaxPeakInRange(float &freq, float &magnitude, 
            float minFreq, float maxFreq);
    
    public:
        uint8_t getCurrentTotal() { return record.total; }
        uint8_t getCurrentDetected() { return record.detected; }
        float getCurrentAvgAmplitude() { return record.avgAmplitude; }

        /*!
            @brief construct an analyzer using a specific buffer 
            and a Report struct
            @param buffer a reference to the buffer where the 
            data are stored, its length must be power of 2 to run FFT
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

        /*!
            @brief write the result from `record` to `report`
        */
        void saveResult();

        /*!
            @brief reset the temporary report `record`
        */
        void clearResult();
};

#endif