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

#define SAMP_FREQ 2 * BUFFER_SIZE
#define BIN_WIDTH SAMP_FREQ / BUFFER_SIZE

void clearArr(float *arr, uint16_t length);

Analyzer::Analyzer(struct Buffer &buffer, struct Report &report): 
buffer(buffer), report(report)
{
    // Set imaginary part to 0 to avoid error.
    clearArr(imags, BUFFER_SIZE);

    // Initialize FFT object for signal processing.
    fft = ArduinoFFT<float>(buffer.buffer, imags, 
        BUFFER_SIZE, SAMP_FREQ);
}

void Analyzer::findMaxPeakInRange(float &freq, float &magnitude, 
float minFreq, float maxFreq)
{
    // Check input validity.
    if ((minFreq > maxFreq) 
        || (maxFreq < 0) 
        || (minFreq > SAMP_FREQ))
    {
        freq = -1;
        return;
    }

    // Bound frequency range.
    minFreq = max(minFreq, 0);
    maxFreq = min(maxFreq, SAMP_FREQ);

    // Determine start and end indices.
    uint16_t startIndex, endIndex;
    startIndex = (uint16_t) (minFreq / BIN_WIDTH);
    endIndex = (uint16_t) (maxFreq / BIN_WIDTH);

    // Ensure `startIndex` and `endIndex` match freq in desired range.
    startIndex = (startIndex * BIN_WIDTH < minFreq) ? 
        (startIndex + 1) : startIndex;
    endIndex = min(endIndex, BUFFER_LENGTH - 1);
    
    if (startIndex > endIndex)
    {
        freq = -1;
        return;
    }

    float leftMag, mag, rightMag;

    // Get adjacent values for `startIndex`.
    leftMag = (startIndex > 0) ? buffer.get(startIndex - 1) : 0;
    mag = buffer.get(startIndex);
    rightMag = (startIndex < BUFFER_LENGTH - 1) ? buffer.get(startIndex + 1) : 0;

    // Test the first freq in range.
    if (!(leftMag < mag) || !(mag > rightMag)) { freq = -1; }
    else
    {
        // Has a peak.
        freq = startIndex * BIN_WIDTH;
        magnitude = mag;
    }

    if (startIndex == endIndex) { return; }

    // Create `maxMag` to compare peak magnitude as `magnitude` is any float.
    float maxMag = 0;

    for (uint16_t index = startIndex + 1; index < endIndex; index++)
    {
        // Get values.
        leftMag = buffer.get(index - 1);
        mag = buffer.get(index);
        rightMag = buffer.get(index + 1);

        if (!(leftMag < mag) || !(mag > rightMag)) { continue; }
        if (mag <= maxMag) { continue; }

        freq = startIndex * BIN_WIDTH;
        maxMag = mag;
    }
    
    // Read last value.
    mag = buffer.get(endIndex);
    rightMag = (endIndex < BUFFER_LENGTH - 1) ? 
        buffer.get(endIndex + 1) : 0;

    if ((buffer.get(endIndex - 1) < mag) && (mag > rightMag))
    {
        if (mag > maxMag)
        {
            // Last is the greatest peak.
            freq = endIndex * BIN_WIDTH;
            magnitude = mag;
            return;
        }
    }

    magnitude = maxMag;
    return;
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
     */
    findMaxPeakInRange(peakFreq, accMagnitude, RECT_LOW, RECT_HIGH);

    if ((peakFreq >= RECT_LOW) && (peakFreq <= RECT_HIGH))
    {
        // Calculate the relative amplitude of displacement.
        float moveAmplitude = accMagnitude / pow(peakFreq, 2);

        if (moveAmplitude > 0.05) // some threshold, may need adjustion
        {
            // Dectected tremor.
            record.detected++;

            // Update average.
            record.avgAmplitude = (record.avgAmplitude * (record.detected - 1) 
                + moveAmplitude) / (record.detected);
        }
    }

    record.total++;

    // Reset imags part.
    clearArr(imags, BUFFER_SIZE);
}

void Analyzer::saveResult()
{
    report.total = record.total;
    report.detected = record.detected;
    report.avgAmplitude = record.avgAmplitude;
}

void Analyzer::clearResult()
{
    record.total = 0;
    record.detected = 0;
    record.avgAmplitude = 0;
}

/*!
    @brief set all entry of an array to 0
    @param arr a pointer to the array to be cleared
    @param length a 16 bit number that represent the length of `arr`
*/
void clearArr(float *arr, uint16_t length)
{
    uint16_t index = 0;
    while (index < length) { arr[index++] = 0; }
}