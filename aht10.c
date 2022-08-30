#include "aht10.h"

static const u_int8_t INIT_CMD[INIT_CMD_LEN] = {0xE1, 0x08, 0x00};
static const u_int8_t TRIG_MES_CMD[TRIG_MES_CMD_LEN] = {0xAC, 0x33, 0x00};

uint aht10_init(u_int8_t address, AHT10_Config *config, AHT10 *sensor)
{
    uint baud = PICO_ERROR_GENERIC;

    baud = i2c_init(config->i2c, config->baudrate);

    gpio_set_function(config->scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(config->scl_pin);

    gpio_set_function(config->sda_pin, GPIO_FUNC_I2C);
    gpio_pull_up(config->sda_pin);

    // Write initiation command onto I2C FIFO
    i2c_write_blocking(config->i2c, config->address, INIT_CMD, INIT_CMD_LEN, false);
    
    sensor->config = config;
    sensor->init = true;
}

u_int32_t aht10_trigger_measurement(AHT10 *sensor)
{
    return i2c_write_blocking(i2c_default, sensor->config->address, TRIG_MES_CMD, TRIG_MES_CMD_LEN, false);
}

void aht10_read_sensor(AHT10 *sensor)
{
    u_int8_t raw_data[AHT10_ST_DATA_LEN+AHT10_RH_DATA_LEN+AHT10_TEMP_DATA_LEN];

    u_int32_t tmp_rh;
    u_int32_t tmp_temp;

    aht10_trigger_measurement(sensor);

    i2c_read_blocking(sensor->config->i2c, sensor->config->address, raw_data, AHT10_ST_DATA_LEN+AHT10_RH_DATA_LEN+AHT10_TEMP_DATA_LEN, false);

    sensor->state = raw_data[0];
    tmp_rh = (raw_data[1] << 12) | (raw_data[2] << 4) | (raw_data[3] & 0xF0);
    tmp_temp = ((raw_data[3] & 0x0F) << 16) | (raw_data[4] << 8) | raw_data[5];

    sensor->rh = ( ( (double) (tmp_rh) ) / (1 << 20) ) * 100;
    sensor->temp_cel = ( (double)(tmp_temp) / (1 << 20) ) * 200 - 50;
    sensor->temp_far = ( (sensor->temp_cel) * (9.0/5.0) ) + 32.0;
}