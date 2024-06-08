#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"
#include "pico/sleep.h"
#include "hardware/rtc.h"

#include "ticker.h"
#include "ticker_display.h"
#include "battery.h"

#include "secrets.h"

int main(void)
{
    stdio_init_all();

    if (cyw43_arch_init()) {
        puts("Failed to initialise WiFi\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        puts("Failed to connect WiFi\n");
        return 1;
    }

    printf("Connected with IP %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));

    while (1) {
        ticker arm, spx;

        bool res = get_ticker("ARM", "ARM", &arm);
        if (!res) {
            puts("Fetching ARM ticker data failed\n");
        }

        res = get_ticker("%5ESPX", "SPX", &spx);
        if (!res) {
            puts("Fetching SPX ticker data failed\n");
        }

        int battery = get_battery();

        printf("Update: ARM: %f, SPX: %f, Bat: %d\%\n", arm.price, spx.price, battery);

        display_tickers(&arm, &spx, battery);
        sleep_ms(5000);
    }

    cyw43_arch_deinit();
}
