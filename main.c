#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "ticker.h"
#include "ticker_display.h"

int main(void)
{
    stdio_init_all();
    display_init();

    ticker arm, spx;
    bool res = get_ticker("ARM", &arm);
    if (!res) {
        puts("Fetching ARM ticker data failed\n");
    }

    res = get_ticker("SPX", &spx);
    if (!res) {
        puts("Fetching SPX ticker data failed\n");
    }

    display_tickers(&arm, &spx);

    while (1) {
        sleep_ms(250);
        puts("Hello World\n");
        sleep_ms(1000);
    }
}
