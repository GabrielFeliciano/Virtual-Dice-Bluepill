#include <stdbool.h>
#include "gpio/gpio.h"

// Types

enum ResultStatus {
    Err,
    Ok
};

struct ResultInt {
    enum ResultStatus status;
    int payload;
};

struct ResultArrayOfInt {
    enum ResultStatus status;
    int *payload;
    int size;
};

struct UpcommingSignal {
    int current;
    int last;
};

// Macros

#define button_pin 15

// Global variables

int display_pin[] = {3,4,5,6,7,8,9};

// Function signatures

typedef struct ResultArrayOfInt (*DisplayInputMapper)(int);
enum ResultStatus display_simbol(DisplayInputMapper strategy, int display_pins[], int num);

// Macros

#define write_number_on_proteus_7_seg_display(x) (display_simbol(Proteus7Seg_Strategy, display_pin, x))

struct ResultArrayOfInt Proteus7Seg_Strategy(int num);

// Program

void configure_pins() {
    // GPIO init
    gpio_init();

    // Button
    gpio_pin_mode(GPIOB, button_pin, gpio_mode_input_pupd);
    gpio_pin_write(GPIOB, button_pin, 0);

    // Display pins
    for (int i = 0; i < sizeof(display_pin)/sizeof(int); i++) {
        gpio_pin_mode(GPIOB, display_pin[i], gpio_mode_output_PP_2MHz);
    }
}

void main() {
    // Configure all pins
    configure_pins();

    // Configure 
    srand((unsigned) time(0));

    // Program state
    int number = 1;
    struct UpcommingSignal buttonState = {
        gpio_pin_read(GPIOB, button_pin), 
        gpio_pin_read(GPIOB, button_pin)
    };

    while (true) {
        buttonState.last = buttonState.current;
        buttonState.current = gpio_pin_read(GPIOB, button_pin);

        if (buttonState.last != buttonState.current && buttonState.current == 1) {
            // number += 1;
            // if (number > 6) number = 1;
            number = rand() % 6 + 1;
        }

        enum ResultStatus result = write_number_on_proteus_7_seg_display(number);
        int b = 1;
    }
}


// -----------------
// --- Functions ---
// -----------------

// Write output to pins
void write_pins(int pins[], int output[], int size) {
    for (int i = 0; i < size; i++) {
        int pin = pins[i];
        int value = output[i];
        gpio_pin_write(GPIOB, pin, value);
    }
}

// Given a strategy and a pin map, prints a number in displayer
// Int -> Pointer List Int -> (Int -> ResultArrayOfInt) -> ResultStatus
enum ResultStatus display_simbol(DisplayInputMapper strategy, int display_pins[], int num) {
    struct ResultArrayOfInt resultOutput = strategy(num);
    int *output = resultOutput.payload;

    if (sizeof(display_pins) != sizeof(output) || resultOutput.status == Err) return Err;

    write_pins(display_pins, output, resultOutput.size);

    return Ok;
}

// All Display Strategys

int outputPossibilities_Proteus7Seg_Strategy[6][7] = {
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}  // 6
};
struct ResultArrayOfInt Proteus7Seg_Strategy(int number) {
    // Validation
    enum ResultStatus status = Err;
    if (1 <= number && number <= 6) status = Ok;

    // Mapping
    int output[7];
    switch (number) {
        case 1 : *output = outputPossibilities_Proteus7Seg_Strategy[0]; break;
        case 2 : *output = outputPossibilities_Proteus7Seg_Strategy[1]; break;
        case 3 : *output = outputPossibilities_Proteus7Seg_Strategy[2]; break;
        case 4 : *output = outputPossibilities_Proteus7Seg_Strategy[3]; break;
        case 5 : *output = outputPossibilities_Proteus7Seg_Strategy[4]; break;
        case 6 : *output = outputPossibilities_Proteus7Seg_Strategy[5]; break;
    }

    // Return
    struct ResultArrayOfInt result = { status, *output, 7 };
    return result;
}

// End of All display strategys