# Arduino Mega Timers

This C++ class template provides an interface for creating timers on an Arduino Mega. Timers are useful for performing tasks periodically or for precisely controlling events in hardware projects.

## Usage

To use this template, follow these steps:

1. This repository uses c++20 features, I recommend using the modm's  [avr-gcc 11.2.0](https://github.com/modm-io/avr-gcc/releases/tag/v11.2.0).
2. Install it on PlatformIO using this information as a [reference](https://community.platformio.org/t/using-different-toolchain-versions/22787).
3. Edit the platformio.ini file to select the compiler, this repository and add the partial std library as follows:

```ini
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino
build_flags = -std=gnu++20 -w -Os
build_unflags = -std=gnu++11
platform_packages = 
    ;modm avr-gcc 11.2 ( https://github.com/modm-io/avr-gcc/releases/tag/v11.2.0 )
    ;[name=]@complete path to package folder
    toolchain-atmelavr@/home/villabaal/.platformio/packages/avr-gcc
lib_deps = 
    ;Partial stdlib
    https://github.com/modm-io/avr-libstdcpp.git
    ;Timers
    https://github.com/Villabaal/Arduino-Mega-Timers.git

```

4. Select the `Timer` template with the desired timer number (from 1 to 5).
5. Set the callback function (`isr`) to perform actions when the timer completes.
6. Call the `enableTimer()` method to start the timer.
7. Optionally, you can adjust the timer interval using the `setInterval()` method.

## Code Example

```cpp
#include <Arduino.h>
#include "Timers.h"

//select timer 1
using timer = Timer<1>;

// Define the callback function for the timer
void myCallback() {
    // Actions to perform when the timer completes
    Serial.println("Timer has completed!");
}

void setup() {
    Serial.begin(9600);
    
    // Configure the timer
    timer::isr = myCallback; // Assign the callback function
    timer::setInterval(2000); // Optionally: adjust the timer interval
    
    // Start the timer
    timer::enableTimer();
}

void loop() {
    // No specific code needed in the main loop if using the timer
}
```