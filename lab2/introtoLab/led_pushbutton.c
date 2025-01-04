#include <pigpio.h>
#include <stdio.h>

#define LED_PIN 17    // Replace with the GPIO pin for the LED
#define SWITCH_PIN 27 // Replace with the GPIO pin for the Switch

int main() {
    // Initialize GPIO
    if (gpioInitialise() < 0) {
        printf("GPIO Initialization failed\n");
        return 1;
    }

    // Set LED pin as output and Switch pin as input
    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioSetMode(SWITCH_PIN, PI_INPUT);

    // Set pull-up/down resistor for Switch pin to off
    gpioSetPullUpDown(SWITCH_PIN, PI_PUD_OFF);

    // Turn on the LED
    gpioWrite(LED_PIN, 1);

    // Wait for the switch to be pressed (switch reads 1)
    while (gpioRead(SWITCH_PIN) == 0);

    // Turn off the LED
    gpioWrite(LED_PIN, 0);

    // Terminate GPIO
    gpioTerminate();

    return 0;
}
