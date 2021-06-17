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

// Global variables

int display_pin[] = {3,4,5,6,7,8,9};

// Function signatures

typedef struct ResultArrayOfInt (*DisplayInputMapper)(int);
enum ResultStatus display_simbol(DisplayInputMapper strategy, int display_pins[], int num);

// Macros

#define display_turn_off_all(x) (display_simbol(TurnOffAll_Strategy, display_pin, x))
#define display_turn_on_all(x) (display_simbol(TurnOnAll_Strategy, display_pin, x))

struct ResultArrayOfInt TurnOffAll_Strategy(int number);
struct ResultArrayOfInt TurnOnAll_Strategy(int number);

// Program

void configure_pins() {
    // GPIO init
    gpio_init();

    // Display pins
    for (int i = 0; i < sizeof(display_pin)/sizeof(int); i++) {
        gpio_pin_mode(GPIOB, display_pin[i], gpio_mode_output_PP_2MHz);
    }
}

void bad_delay (int n) {
    for (int i = 0; i < n; i++);
}

void main() {
    // Configure all pins
    configure_pins();

    while (true) {
        enum ResultStatus result_on = display_turn_on_all(42);
        bad_delay(500000);
        enum ResultStatus result_off = display_turn_off_all(42);
        bad_delay(500000);
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

// Turn on All leds
int outputPossibilities_TurnOnAll_Strategy[1][7] = {
    {0, 0, 0, 0, 0, 0, 0}, // All
};
struct ResultArrayOfInt TurnOnAll_Strategy(int number) {
    // Validation
    enum ResultStatus status = Ok;

    // Mapping
    int output[7];
    *output = outputPossibilities_TurnOnAll_Strategy[0];

    // Return
    struct ResultArrayOfInt result = { status, *output, 7 };
    return result;
}

// Turn off All leds
int outputPossibilities_TurnOffAll_Strategy[1][7] = {
    {1, 1, 1, 1, 1, 1, 1}, // All
};
struct ResultArrayOfInt TurnOffAll_Strategy(int number) {
    // Validation
    enum ResultStatus status = Ok;

    // Mapping
    int output[7];
    *output = outputPossibilities_TurnOffAll_Strategy[0];

    // Return
    struct ResultArrayOfInt result = { status, *output, 7 };
    return result;
}

// End of All display strategys