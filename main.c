#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"
#include "ticker.h"
#include "ticker_display.h"
#include "battery.h"

#include "secrets.h"

int main(void)
{
    stdio_init_all();
    display_init();

    if (cyw43_arch_init()) {
        puts("Failed to initialise WiFi\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        puts("Failed to connect WiFi\n");
        return 1;
    }

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
        sleep_ms(3000);

        arm.price = get_battery();
        printf("Battery: %i\n", arm.price);

        display_tickers(&arm, &spx);
    }

    cyw43_arch_deinit();
}
