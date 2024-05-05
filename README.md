# Parkinsonian Tremor Detector

This project aims to build an wearable Parkinsonian 
tremor detector based on based on Adafruit Playground 
Classic.

## Index
- [Parkinsonian Tremor Detector](#parkinsonian-tremor-detector)
  - [Index](#index)
  - [Description](#description)
  - [Requirements](#requirements)
    - [Hardware](#hardware)
    - [Software](#software)
  - [Setup](#setup)
    - [Hardware](#hardware-1)
    - [Software](#software-1)
    - [Testing](#testing)

## Description
The workflow is shown in the following [state machine digram][workflow]:
![Workflow State Machine Diagram](./img/workflow.svg)

## Requirements
### Hardware
+ Adafruit Playground Classic;
+ Power Supply/USB Power Bank (or LIPO Battery);
+ Tactile Switches (as external interrupt trigger);
+ 10 kohm resistor;
+ 2 pF capacitor (to prevent mechanical bouncing).

### Software
+ [Visual Studio Code][vscode] with [PlatformIO IDE][platformIO] 
  Extension.

## Setup
### Hardware
Circuit connection is shown in the following image:
![Hardware Connection](./img/connection.jpg)

### Software
1. Download zip folder by clicking the `Code` button on the upper
   right or clone the repository using 
   ```bash
   git clone https://github.com/GitHubAvailable/tremor-challenge
   ```
2. Open the folder in [Visual Studio Code][vscode]. 
   [PlatformIO IDE][platformIO] should be starting creating relevant 
   and dependencies automatically.

   **Note:** **DO NOT** open the project folder along with other folders, or the creation may not start.

**Known Bugs:**
1. Removing `#include <Adafruit_CircuitPlayground.h>` 
   in `src/main.cpp` will may lead to an error about `SPI.h` not found.

### Testing
Adafruit Playground Classic does not support PlatformUI Unit Testing.

[vscode]: https://code.visualstudio.com/download
[platformIO]: https://platformio.org/platformio-ide
[workflow]: ./img/workflow.svg