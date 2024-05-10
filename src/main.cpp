/**
 * Team Members (Net ID):
 *     - Mark Liu (hl4963)
 *     - Christopher Haddad (cnh2026)
 *     - Nico Gomez Avila (ng2384)
 */
#include <Arduino.h>
// Removing the line below may cause `SPI.h` missing error
#include <Adafruit_CircuitPlayground.h> 
#include "analyzer.h"
#include "buffer.h"
#include "display.h"
#include "setup.h"
#include "state.h"

// Allocate software resources.
struct Buffer buffer;
struct Report report;

struct Analyzer analyzer = Analyzer(buffer, report);

volatile enum State state;

void setup() 
{
    // put your setup code here, to run once:
    cli(); // Setup process ignore any interrupt.
    // Setup Hardwares.
    Serial.begin(9600);
    setupButtons();
    setupLED();
    setupTimer();

    // Initialize report.
    resetReport(report);

    // Setup accelerometer and neopixels.
    CircuitPlayground.begin();

    // Enter Idle state.
    state = State::Idle; 
    sei();
}

ISR(TIMER1_OVF_vect)
{
    // Measure acceleration.
    analyzer.measure();
}

ISR(INT0_vect)
{
    cli(); // prevent multiple calls due to mechanical bouncing
    // Start/End button pressed, change state.
    state = (state == Idle) ? Measuring : Idle;

    if (state == Measuring)
    {
        // Clear previous data.
        analyzer.clearResult();

        // Start a new test.
        startTimer();
        showStart();
    }

    sei();
}

void loop() 
{
    // put your main code here, to run repeatedly:
    switch (state)
    {
        case Measuring:
            if (analyzer.getCurrentTotal() == TOTAL_MEASURES) 
            {
                // Save data to `report`.
                analyzer.saveResult();
                // Test is over.
                state = Idle;
                return;
            }

            // UpdateUI.
            showProgress((uint8_t) (analyzer.getCurrentTotal() * 100 / TOTAL_MEASURES));
            if (buffer.isBufferFull())
            {
                if (state == Idle)
                {
                    // Test cancelled.
                    return;
                }

                // Analyzing process should not be interrupted.
                stopTimer();
                analyzer.analyze();
                startTimer();

                // Reset buffer for new measurements.
                buffer.reset();
            }
            break;
        
        default:
            stopTimer();
            buffer.reset();

            clearUI();
            displayReport(report);
            while (state == Idle); // wait for test to start
    }
}