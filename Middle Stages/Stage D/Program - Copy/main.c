#include <stdbool.h>
#include "gpio/gpio.h"

int leds[] = {3,4,5,6,7,8,9};

void delay (int n) {
    for (int i = 0; i < n; i++);
}

void write_leds(int value) {
    for (int i = 0; i < sizeof(leds)/sizeof(int); i++) {
        gpio_pin_write(GPIOB, leds[i], value);
    }
}

void main() {
    gpio_init();

    for (int i = 0; i < sizeof(leds)/sizeof(int); i++) {
        gpio_pin_mode(GPIOB, leds[i], gpio_mode_output_PP_2MHz);
    }

    while (true) {
        write_leds(true);
        delay(500000);
        write_leds(false);
        delay(500000);
    }
}