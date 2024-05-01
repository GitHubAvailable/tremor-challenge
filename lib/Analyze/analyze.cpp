/**
 * analyze.cpp - Implementation of the data processing functions 
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
 * Modified 29 April 2024 by Mark Liu
 */
#include <Adafruit_CircuitPlayground.h>
#include "analyzer.h"

#define BOARD CircuitPlayground

#define RECT_LOW 2 * LOW_FREQ // rectified low frequency
#define RECT_HIGH 2 * HIGH_FREQ // rectified high frequency

const float samplingFrequency = 2 * BUFFER_SIZE;

void clearArr(float *arr, uint16_t length);

Analyzer::Analyzer(struct Buffer &buffer, struct Report &report): 
buffer(buffer), report(report)
{
    // Set imaginary part to 0 to avoid error.
    clearArr(imags, BUFFER_SIZE);

    // Initialize FFT object for signal processing.
    fft = ArduinoFFT<float>(buffer.buffer, imags, 
        BUFFER_SIZE, samplingFrequency);
}

void Analyzer::measure()
{
    buffer.add(BOARD.motionX(), BOARD.motionY(), BOARD.motionZ());
}

void Analyzer::analyze()
{
    // Perform FFT on buffer.
    fft.windowing(FFTWindow::Hamming, FFTDirection::Forward); // weigh data
    fft.compute(FFTDirection::Forward); // compute FFT
    fft.complexToMagnitude(); // calculate magnitude

    float peakFreq, accMagnitude;

    /**
     * Get peak and magnitude. May need a low pass filter to 
     * improve accuracy.
     * 
     * TODO: use custom function find peak.
     */
    fft.majorPeakParabola(&peakFreq, &accMagnitude);

    if ((peakFreq >= RECT_LOW) && (peakFreq <= RECT_HIGH))
    {
        // Calculate the amplitude of displacement in cm.
        float moveAmplitude = accMagnitude / pow(peakFreq, 2) * 100;

        if (moveAmplitude > 5) // some threshold, may need adjustion
        {
            // Dectected tremor.
            report.detected++;

            // Update average.
            report.avgAmplitude = (report.avgAmplitude * (report.detected - 1) 
                + moveAmplitude) / (report.detected);
        }
    }

    report.total++;

    // Reset imags part.
    clearArr(imags, BUFFER_SIZE);
}

/*!
    @brief set all entry of an array to 0
    @param arr a pointer to the array to be cleared
    @param length a 16 bit number that represent the length of `arr`
*/
void clearArr(float *arr, uint16_t length)
{
    uint16_t index = 0;
    while (index < length) { arr[index] = 0; }
}