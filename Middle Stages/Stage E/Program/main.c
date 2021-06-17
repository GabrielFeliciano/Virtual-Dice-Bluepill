#include <stdbool.h>
#include "gpio/gpio.h"

// Macros

// Program

void configure_pins() {
    
}

void bad_delay (int n) {
    for (int i = 0; i < n; i++);
}

void main() {
    // Configure all pins
    configure_pins();
    srand(time(0));

    while (true) {
        int random_number = rand();
        bad_delay(1000000);
    }
}