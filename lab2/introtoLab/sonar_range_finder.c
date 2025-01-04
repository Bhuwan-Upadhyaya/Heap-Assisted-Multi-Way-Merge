#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

#define TRIG_PIN 23  // Replace with the GPIO pin for Trigger
#define ECHO_PIN 24  // Replace with the GPIO pin for Echo
#define SPEED_OF_SOUND 34300  // Speed of sound in cm/s

int main() {
    // Initialize GPIO
    if (gpioInitialise() < 0) {
        printf("GPIO Initialization failed\n");
        return 1;
    }

    // Set TRIGGER pin as output and ECHO pin as input
    gpioSetMode(TRIG_PIN, PI_OUTPUT);
    gpioSetMode(ECHO_PIN, PI_INPUT);
    gpioSetPullUpDown(ECHO_PIN, PI_PUD_OFF);

    while (1) {
        // Send a trigger pulse
        gpioWrite(TRIG_PIN, 1);    // Set Trigger HIGH
        sleep(1);                  // Wait 1 second
        gpioWrite(TRIG_PIN, 0);    // Set Trigger LOW

        // Wait for Echo signal to go high
        while (gpioRead(ECHO_PIN) == 0);

        // Capture start time
        uint32_t start_sec, start_microsec;
        gpioTime(PI_TIME_RELATIVE, &start_sec, &start_microsec);

        // Wait for Echo signal to go low
        int count = 0;
        while (gpioRead(ECHO_PIN) == 1) {
            count++;
        }

        // Capture end time
        uint32_t end_sec, end_microsec;
        gpioTime(PI_TIME_RELATIVE, &end_sec, &end_microsec);

        // Calculate elapsed time in microseconds
        uint32_t elapsed_time_microsec = (end_sec - start_sec) * 1000000 + (end_microsec - start_microsec);
        printf("Count: %d, Elapsed time: %u microseconds\n", count, elapsed_time_microsec);

        // Calculate distance (time / 2 because the sound travels to the object and back)
        float distance_cm = (elapsed_time_microsec / 2.0) * (SPEED_OF_SOUND / 1000000.0);
        float distance_in = distance_cm / 2.54;

        // Print the calculated distance
        printf("Distance: %.2f cm (%.2f inches)\n", distance_cm, distance_in);
    }

    // Terminate GPIO
    gpioTerminate();

    return 0;
}
