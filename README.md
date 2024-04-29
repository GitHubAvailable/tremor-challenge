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
  - [Installation](#installation)
    - [Setup](#setup)
    - [Testing](#testing)

## Description
The workflow is shown in the following [state machine digram][workflow]:
![Workflow State Machine Diagram](./img/workflow.svg)

## Requirements
### Hardware
+ Adafruit Playground Classic;
+ Power Supply/USB Power Bank (or LIPO Battery).

### Software
+ [Visual Studio Code][vscode] with [PlatformIO IDE][platformIO] 
  Extension.

## Installation
### Setup

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

[vscode]: https://code.visualstudio.com/download
[platformIO]: https://platformio.org/platformio-ide
[workflow]: ./img/workflow.svg