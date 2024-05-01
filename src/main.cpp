#include <Arduino.h>
// Removing the line below may cause `SPI.h` missing error
#include <Adafruit_CircuitPlayground.h> 
#include "analyzer.h"
#include "buffer.h"
#include "display.h"
#include "setup.h"
#include "state.h"

#define LAPSE 20

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

ISR(PCINT0_vect)
{
    if (!(PORTD & (HIGH << START_END))) { return; }

    // Start/End button pressed, change state.
    state = (State) ~(state);

    if (state == Measuring)
    {
        // Start a new test.
        resetReport(report);
        showStart();
    }
}

void loop() 
{
    // put your main code here, to run repeatedly:
    switch (state)
    {
        case Measuring:
            if (report.total == TOTAL_MEASURES) 
            {
                // Test is over.
                state = Idle;
                return;
            }

            // UpdateUI.
            showProgress((uint8_t) (report.total * 100 / TOTAL_MEASURES));

            if (buffer.isBufferFull())
            {
                if (state == Idle)
                {
                    // Test cancelled.
                    return;
                }

                // Analyzing process should not be interrupted.
                cliTimer();
                analyzer.analyze();
                seiTimer();

                // Reset buffer for new measurements.
                buffer.reset();
            }
            break;
        
        default:
            buffer.reset();

            clearUI();
            displayReport(report);
            while (state == Idle); // wait for test to start
    }
}