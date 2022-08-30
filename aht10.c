#include "aht10.h"

static const u_int8_t INIT_CMD[3] = {0xE1, 0x08, 0x00};
static const u_int8_t TRIG_MES_CMD[3] = {0xAC, 0x33, 0x00};

void aht10_init(u_int8_t address, AHT10_Config *config, AHT10 *sensor)
{
    sensor->init = false;
    printf("HELLO IDK\n");
    uint baud = 0;

    baud = i2c_init(i2c_default, AHT10_I2C_BAUDRATE);

    printf("Baudrate: %i\n", baud);

    gpio_set_function(config->scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(config->scl_pin);

    gpio_set_function(config->sda_pin, GPIO_FUNC_I2C);
    gpio_pull_up(config->sda_pin);

    printf ("Pin %i: PULLED UP - %s\n", config->scl_pin, (gpio_is_pulled_up(config->scl_pin) ? "TRUE" : "FALSE") );
    printf ("Pin %i: %s\n", config->scl_pin, (gpio_get_function(config->scl_pin) == GPIO_FUNC_I2C ? "I2C" : "ERROR") );

    printf ("Pin %i: PULLED UP - %s\n", config->sda_pin, (gpio_is_pulled_up(config->sda_pin) ? "TRUE" : "FALSE") );
    printf ("Pin %i: %s\n", config->sda_pin, (gpio_get_function(config->sda_pin) == GPIO_FUNC_I2C ? "I2C" : "ERROR") );

    uint bytes_written;

    bytes_written = i2c_write_blocking(i2c_default, config->address, INIT_CMD, INIT_CMD_LEN, false);
    printf("Bytes written: %i\n", bytes_written);
    sensor->config = config;
    sensor->init = true;
}

u_int32_t aht10_trigger_measurement(AHT10 *sensor)
{
    return i2c_write_blocking(i2c_default, sensor->config->address, ((uint8_t *)&TRIG_MES_CMD), TRIG_MES_CMD_LEN, false);
}

void aht10_read_sensor(AHT10 *sensor)
{
    u_int32_t unproc_rh_data;
    u_int16_t unproc_temp_data;

    aht10_trigger_measurement(sensor);
    i2c_read_blocking(sensor->config->i2c, sensor->config->address, ((u_int8_t *)sensor->state), AHT10_ST_DATA_LEN, true);
    i2c_read_blocking(sensor->config->i2c, sensor->config->address, ((u_int8_t *)&unproc_rh_data), AHT10_RH_DATA_LEN, true);
    i2c_read_blocking(sensor->config->i2c, sensor->config->address, ((u_int8_t *)&unproc_temp_data), AHT10_TEMP_DATA_LEN, false);

    *(sensor->rh_data) = (unproc_rh_data / (1 << 20)) * 100;
    *(sensor->temp_data) = (unproc_temp_data / (1 << 20)) * (200 - 50);
}

u_int32_t aht10_read_temp_far(AHT10 *sensor);

u_int32_t aht10_read_rh(AHT10 *sensor);