#include "..\Header\Motor.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define MOTOR_PWMA          GPIO_NUM_25 // pin 14, RTCIO6
#define MOTOR_AIN2          GPIO_NUM_26
#define MOTOR_AIN1          GPIO_NUM_27

#define MOTOR_PWMB          GPIO_NUM_13 // pin 20, RTCIO14
#define MOTOR_BIN2          GPIO_NUM_12
#define MOTOR_BIN1          GPIO_NUM_14

#define LEDC_TIMER          LEDC_TIMER_0
#define LEDC_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES       LEDC_TIMER_13_BIT // 2^13 = 8192 => Max = 8191
#define LEDC_FREQUENCY      (4000) // 4 kHz
#define LEDC_CHANNEL_A      LEDC_CHANNEL_0
#define LEDC_CHANNEL_B      LEDC_CHANNEL_1

/**
 * Função que define as configurações iniciais associadas aos motores.
 */
void Motor_Initialize(void)
{
    gpio_reset_pin(MOTOR_AIN2);
    gpio_reset_pin(MOTOR_AIN1);
    gpio_reset_pin(MOTOR_BIN2);
    gpio_reset_pin(MOTOR_BIN1);

    gpio_set_direction(MOTOR_AIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_AIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_BIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_BIN1, GPIO_MODE_OUTPUT);

    // Configura o LEDC PWM timer
    ledc_timer_config_t ledc_timer_conf = {
        .speed_mode       = LEDC_MODE,       //modo de operação
        .timer_num        = LEDC_TIMER,      //seleção do timer
        .duty_resolution  = LEDC_DUTY_RES,   //seleciona resolução do duty cycle
        .freq_hz          = LEDC_FREQUENCY,  //frequencia de saida padrão
        .clk_cfg          = LEDC_AUTO_CLK    //fonte de clock (clock padrão de 40mhz)

    };
    ledc_timer_config(&ledc_timer_conf);

    // Configura o LEDC PWM channel para o PWMA
    ledc_channel_config_t ledc_channel_a_conf = {
        .speed_mode     = LEDC_MODE,            //modo de operação
        .channel        = LEDC_CHANNEL_A,       //canal de saída
        .timer_sel      = LEDC_TIMER,           //seleção do timer
        .intr_type      = LEDC_INTR_DISABLE,    //desativa interrupção
        .gpio_num       = MOTOR_PWMA,           //vinculação com pino de saída
        .duty           = 0,                    //define duty como 0%
        .hpoint         = 0                     //posição de inicio do ciclo do pwm
    };
    ledc_channel_config(&ledc_channel_a_conf);

    // Configura o LEDC PWM channel para o PWMB
    ledc_channel_config_t ledc_channel_b_conf = {
        .speed_mode     = LEDC_MODE,            //modo de operação
        .channel        = LEDC_CHANNEL_B,       //canal de saída
        .timer_sel      = LEDC_TIMER,           //seleção do timer
        .intr_type      = LEDC_INTR_DISABLE,    //desativa interrupção
        .gpio_num       = MOTOR_PWMB,           //vinculação com pino de saída
        .duty           = 0,                    //define duty como 0%
        .hpoint         = 0                     //posição de inicio do ciclo do pwm
    };
    ledc_channel_config(&ledc_channel_b_conf);
}

/**
 * Função que define a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Motor_SetRotation(motor_num_t motor_num, motor_rotation_t rotation, uint32_t duty)
{
    switch (motor_num) //escolhe entre qual motor controlado
    {
        case MOTOR_NUM_0:
            switch (rotation) //escolhe a direção de rotação
            {
                case MOTOR_ANTI_CLOCKWISE:
                    gpio_set_level(MOTOR_AIN2, 0);
                    gpio_set_level(MOTOR_AIN1, 1);
                    break;

                case MOTOR_CLOCKWISE:
                    gpio_set_level(MOTOR_AIN2, 1);
                    gpio_set_level(MOTOR_AIN1, 0);
                    break;
            }
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_A, duty); //define o novo ciclo de trabalho
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_A);    //atualiza o ciclo de trabalho
            break;

        case MOTOR_NUM_1:
            switch (rotation)
            {
                case MOTOR_ANTI_CLOCKWISE:
                    gpio_set_level(MOTOR_BIN2, 0);
                    gpio_set_level(MOTOR_BIN1, 1);
                    break;

                case MOTOR_CLOCKWISE:
                    gpio_set_level(MOTOR_BIN2, 1);
                    gpio_set_level(MOTOR_BIN1, 0);
                    break;
            }
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);
            break;

        default:
            break;
    }
}

/**
 * Função que impede a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 */
void Motor_LockRotation(motor_num_t motor_num)
{
    switch (motor_num)
    {
        case MOTOR_NUM_0:
            gpio_set_level(MOTOR_AIN2, 1);
            gpio_set_level(MOTOR_AIN1, 1);
            break;

        case MOTOR_NUM_1:
            gpio_set_level(MOTOR_BIN2, 1);
            gpio_set_level(MOTOR_BIN1, 1);
            break;

        default:
            break;
    }
}

/**
 * Função que deixa livre a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 */
void Motor_FreeRotation(motor_num_t motor_num)
{
    switch (motor_num)
    {
        case MOTOR_NUM_0:
            gpio_set_level(MOTOR_AIN2, 0);
            gpio_set_level(MOTOR_AIN1, 0);
            break;

        case MOTOR_NUM_1:
            gpio_set_level(MOTOR_BIN2, 0);
            gpio_set_level(MOTOR_BIN1, 0);
            break;

        default:
            break;
    }
}