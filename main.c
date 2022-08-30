#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "aht10.h"

const uint LED_PIN = 25;

int main()
{
    
    AHT10_Config config;
    AHT10 sensor;

    config.address = AHT10_DEFAULT_ADDRESS;
    config.i2c = i2c_default;
    config.scl_pin = PICO_DEFAULT_I2C_SCL_PIN;
    config.sda_pin = PICO_DEFAULT_I2C_SDA_PIN;

    stdio_init_all();
    sleep_ms(10);

    sleep_ms(2000);
    printf("Hello, Pico!\n");
    sleep_ms(2000);
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    aht10_init( (u_int8_t)AHT10_DEFAULT_ADDRESS, &config, &sensor);

    // while (1)
    // {
    //     printf("Hello, Pico!\n");
    //     sleep_ms(1000);
    //     // aht10_read_sensor(&sensor);
    //     // printf("TEMP: %i\r", &(sensor.temp_data));
    //     // sleep_ms(10);
    // }
}