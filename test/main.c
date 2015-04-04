
#include <stdio.h>
#include "pwm.h"

int main(int argc, char **argv)
{
    // Very crude...
    if (argc == 2 && !strcmp(argv[1], "--pcm"))
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PCM);
    else
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PWM);

    // Setup demo parameters
    int demo_timeout = 10 * 1000000;
    int gpio = 17;
    int channel = 0;
    int subcycle_time_us = SUBCYCLE_TIME_US_DEFAULT; //10ms;

    // Setup channel
    init_channel(channel, subcycle_time_us);
    print_channel(channel);

    // Use the channel for various pulse widths
    add_channel_pulse(channel, gpio, 0, 50);
    add_channel_pulse(channel, gpio, 100, 50);
    add_channel_pulse(channel, gpio, 200, 50);
    add_channel_pulse(channel, gpio, 300, 50);
    usleep(demo_timeout);

    // Clear and start again
    clear_channel_gpio(0, 17);
    add_channel_pulse(channel, gpio, 0, 50);
    usleep(demo_timeout);

    // All done
    shutdown();
    exit(0);
}

