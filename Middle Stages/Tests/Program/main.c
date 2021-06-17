#include <stdbool.h>
#include "gpio/gpio.h"

// Program

void configure_pins() {
    // GPIO init
    gpio_init();

    // gnd
    gpio_pin_mode(GPIOA, 9, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOA, 9, 0);

    // gnd led
    gpio_pin_mode(GPIOB, 3, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOB, 3, 1);

    gpio_pin_mode(GPIOB, 4, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOB, 4, 1);

    // vcc led
    gpio_pin_mode(GPIOB, 7, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOB, 7, 0);

    gpio_pin_mode(GPIOB, 8, gpio_mode_output_PP_10MHz);
    gpio_pin_write(GPIOB, 8, 0);
}

void main() {
    // Configure all pins
    configure_pins();
}