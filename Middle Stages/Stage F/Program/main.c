#include <stdbool.h>
#include "gpio/gpio.h"

// Macros

#define button_pin 15
#define open_pin 14

// Program

void configure_pins() {
    // open pin
    gpio_pin_mode(GPIOB, open_pin, gpio_mode_input_analog);

    // button pin
    gpio_pin_mode(GPIOB, button_pin, gpio_mode_input_pupd);
    gpio_pin_write(GPIOB, button_pin, gpio_pupd_pd); 
}

void main() {
    // Configure all pins
    configure_pins();

    // Making everything plus 1 makes sure that we dont have any 0
    int weird_calc = (time(0) || 1) * (gpio_pin_read(GPIOB, open_pin) || 1);
    srand(weird_calc);

    int random_number;
    bool button_read;
    while (true) {
        button_read = gpio_pin_read(GPIOB, button_pin);
        if (button_read) {
            random_number = rand();
        }
    }
}