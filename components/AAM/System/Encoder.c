#include "../Header/Encoder.h"
#include "driver/gpio.h"

#define MOTOR_1_ENCODER_A   GPIO_NUM_34
#define MOTOR_1_ENCODER_B   GPIO_NUM_35
#define MOTOR_2_ENCODER_A   GPIO_NUM_32
#define MOTOR_2_ENCODER_B  GPIO_NUM_33


void Encoder_Initialize(void)
{
    gpio_reset_pin(MOTOR_1_ENCODER_A);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(MOTOR_1_ENCODER_A, GPIO_MODE_INPUT);   //seta o gpio como entrada
    gpio_set_pull_mode(MOTOR_1_ENCODER_A, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(MOTOR_1_ENCODER_A, GPIO_INTR_ANYEDGE);

    gpio_reset_pin(MOTOR_1_ENCODER_B);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(MOTOR_1_ENCODER_B, GPIO_MODE_INPUT);   //seta o gpio como entrada
    gpio_set_pull_mode(MOTOR_1_ENCODER_B, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(MOTOR_1_ENCODER_B, GPIO_INTR_ANYEDGE);

    gpio_reset_pin(MOTOR_2_ENCODER_A);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(MOTOR_2_ENCODER_A, GPIO_MODE_INPUT);   //seta o gpio como entrada
    gpio_set_pull_mode(MOTOR_2_ENCODER_A, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(MOTOR_2_ENCODER_A, GPIO_INTR_ANYEDGE);

    gpio_reset_pin(MOTOR_2_ENCODER_B);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(MOTOR_2_ENCODER_B, GPIO_MODE_INPUT);   //seta o gpio como entrada
    gpio_set_pull_mode(MOTOR_2_ENCODER_B, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(MOTOR_2_ENCODER_B, GPIO_INTR_ANYEDGE);

     gpio_install_isr_service(0);
}