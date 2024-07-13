#include "..\Header\ReflecSensor.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define REFLECSENSOR_MUX_SEC2      GPIO_NUM_16
#define REFLECSENSOR_MUX_SEC1      GPIO_NUM_4
#define REFLECSENSOR_MUX_SEC0      GPIO_NUM_2
#define REFLECSENSOR_IR_SIG        GPIO_NUM_15

/**
 * Função que define as configurações iniciais associadas aos sensores de refletância.
 */
void ReflecSensor_Initialize(void)
{
    gpio_reset_pin(REFLECSENSOR_MUX_SEC2);
    gpio_reset_pin(REFLECSENSOR_MUX_SEC1);
    gpio_reset_pin(REFLECSENSOR_MUX_SEC0);
    gpio_reset_pin(REFLECSENSOR_IR_SIG);

    gpio_set_direction(REFLECSENSOR_MUX_SEC2, GPIO_MODE_OUTPUT);
    gpio_set_direction(REFLECSENSOR_MUX_SEC1, GPIO_MODE_OUTPUT);
    gpio_set_direction(REFLECSENSOR_MUX_SEC0, GPIO_MODE_OUTPUT);
    gpio_set_direction(REFLECSENSOR_IR_SIG, GPIO_MODE_INPUT);
}

/**
 * Função que lê o sensor de refletância informado.
 * 
 * @param sensor_num Identifica o sensor.
 * 
 * @return GPIO level.
 */
int ReflecSensor_Read(reflecsensor_num_t sensor_num)
{
    switch (sensor_num) //seleciona o sensor a ser lido através das entradas de seleção do MUX
    {
        case REFLECSENSOR_NUM_0:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 0);
            break;

        case REFLECSENSOR_NUM_1:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 1);
            break;

        case REFLECSENSOR_NUM_2:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 0);
            break;

        case REFLECSENSOR_NUM_3:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 1);
            break;

        case REFLECSENSOR_NUM_4:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 0);
            break;

        case REFLECSENSOR_NUM_5:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 1);
            break;

        case REFLECSENSOR_NUM_6:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 0);
            break;

        case REFLECSENSOR_NUM_7:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 1);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 1);
            break;

        default:
            gpio_set_level(REFLECSENSOR_MUX_SEC2, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC1, 0);
            gpio_set_level(REFLECSENSOR_MUX_SEC0, 0);
            break;
    }

    vTaskDelay(1 / portTICK_PERIOD_MS); //Delay de 1ms

    return gpio_get_level(REFLECSENSOR_IR_SIG);
}

