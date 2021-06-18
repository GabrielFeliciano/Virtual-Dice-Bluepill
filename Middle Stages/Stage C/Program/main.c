#include <stdbool.h>
#include "gpio/gpio.h"

// Macros

#define button_pin 15
#define led_pin 6

// Program

void configure_pins() {
    // GPIO init
    gpio_init();

    // Sensor
    gpio_pin_mode(GPIOB, button_pin, gpio_mode_input_floating);

    // Led
    gpio_pin_mode(GPIOB, led_pin, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOB, led_pin, 0);
}

void main() {
    // Configure all pins
    configure_pins();

    bool sensorStatus;
    while (true) {
        sensorStatus = gpio_pin_read(GPIOB, button_pin);
        gpio_pin_write(GPIOB, led_pin, !sensorStatus);
        gpio_pin_write(GPIOC, 13, sensorStatus);
    }
}