#include "battery.h"
#include "hardware/adc.h"
#include "pico/float.h"

// Mix of code from
// https://github.com/pimoroni/pimoroni-pico/blob/main/micropython/examples/pico_lipo_shim/battery_pico.py
// https://github.com/raspberrypi/pico-examples/blob/master/adc/read_vsys/read_vsys.c

#ifndef PICO_POWER_SAMPLE_COUNT
#define PICO_POWER_SAMPLE_COUNT 3
#endif

// Pin used for ADC 0
#define PICO_FIRST_ADC_PIN 26

#if CYW43_USES_VSYS_PIN
#include "pico/cyw43_arch.h"
#endif

int get_battery()
{
    float voltage = 0;
    int percent = 0;

    adc_init();

    // setup adc
    adc_gpio_init(PICO_VSYS_PIN);
    adc_select_input(PICO_VSYS_PIN - PICO_FIRST_ADC_PIN);

    adc_fifo_setup(true, false, 0, false, false);
    adc_run(true);

    // read vsys
    uint32_t vsys = 0;
    for(int i = 0; i < PICO_POWER_SAMPLE_COUNT; i++) {
        uint16_t val = adc_fifo_get_blocking();
        vsys += val;
    }

    adc_run(false);
    adc_fifo_drain();

    vsys /= PICO_POWER_SAMPLE_COUNT;

    // Generate voltage
    const float conversion_factor = 3 * 3.3f / (1 << 12);
    voltage = floorf(vsys * conversion_factor * 100) / 100;

    // Generate percent (V - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 100
    percent = ((voltage - 2.8) / (4.2 - 2.8)) * 100;

    return (percent > 100) ? 100 : percent;
}