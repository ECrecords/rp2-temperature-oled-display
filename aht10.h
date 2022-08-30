#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#ifndef AHT10_H
#define AHT10_H

#define AHT10_DEFAULT_ADDRESS 0x38
#define AHT10_ST_DATA_LEN 8
#define AHT10_RH_DATA_LEN 24
#define AHT10_TEMP_DATA_LEN 16
#define AHT10_I2C_BAUDRATE 100 * 1000

static const u_int8_t INIT_CMD[3];
#define INIT_CMD_LEN 3

static const u_int32_t TRIG_MES_CMD;
#define TRIG_MES_CMD_LEN 6 * 4

typedef struct {
    u_int8_t address;
    i2c_inst_t *i2c;
    uint scl_pin;
    uint sda_pin;
} AHT10_Config;

typedef struct {
    AHT10_Config *config;
    u_int32_t *rh_data;
    u_int32_t *temp_data;
    u_int8_t *state;
    bool init;
} AHT10;


void aht10_init(u_int8_t address, AHT10_Config *config, AHT10 *sensor);

///AHT10 aht10_init();
u_int32_t aht10_trigger_measurement(AHT10 *sensor);

void aht10_read_sensor(AHT10 *sensor);

u_int32_t aht10_read_temp_cel(AHT10 *sensor);

u_int32_t aht10_read_temp_far(AHT10 *sensor);

u_int32_t aht10_read_rh(AHT10 *sensor);

#endif