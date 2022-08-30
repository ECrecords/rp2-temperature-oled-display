#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#ifndef AHT10_H
#define AHT10_H

#define AHT10_DEFAULT_ADDRESS   (u_int8_t) 0x38
#define AHT10_ST_DATA_LEN       (size_t) 1
#define AHT10_RH_DATA_LEN       (size_t) 3
#define AHT10_TEMP_DATA_LEN     (size_t) 2

#define INIT_CMD_LEN 3
static const u_int8_t INIT_CMD[INIT_CMD_LEN];

#define TRIG_MES_CMD_LEN 3
static const u_int8_t TRIG_MES_CMD[TRIG_MES_CMD_LEN];

typedef struct AHT10_CONFIG_STRUCT
{
    i2c_inst_t *i2c;
    uint scl_pin;
    uint sda_pin;
    uint baudrate;
    u_int8_t address;    
} AHT10_Config;

typedef struct AHT10_STRUCT
{
    AHT10_Config *config;
    double rh;
    double temp_cel;
    double temp_far;
    u_int8_t state;
    bool init;
} AHT10;

uint aht10_init(u_int8_t address, AHT10_Config *config, AHT10 *sensor);

u_int32_t aht10_trigger_measurement(AHT10 *sensor);

void aht10_read_sensor(AHT10 *sensor);

#endif