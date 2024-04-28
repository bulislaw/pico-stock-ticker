#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

int main(void)
{
    stdio_init_all();
	DEV_Delay_ms(500);

    while (1) {
        sleep_ms(250);
        puts("Hello World\n");
        sleep_ms(1000);
    }
}
