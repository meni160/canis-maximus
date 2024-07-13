#include "..\Header\Hal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LEFT_MOTOR                MOTOR_NUM_0
#define RIGHT_MOTOR               MOTOR_NUM_1

#define MOTOR_ENABLE_BUTTON       BUTTON_NUM_0
#define REDUNDANT_BUTTON          BUTTON_NUM_1 //Por enquanto não tem funcionalidade própria.

bool motor_enabled = false;

/**
 * Função de interrupção que alterna o nível lógico da variável motor_enabled.
 * 
 * @param arg Ponteiro genérico que é definido por padrão na configuração da interrupção GPIO. Não é utilizado para esta aplicação.
 */
static void IRAM_ATTR toggle_motor_enabled_isr_handler(void* arg)
{
    motor_enabled = !motor_enabled;
}

/**
 * Função que define as configurações iniciais da camada de abstração de hardware.
 */
void Hal_Initialize(void)
{
    ReflecSensor_Initialize();
	Motor_Initialize();
	Button_Initialize();
	Button_SetInterruptHandler(MOTOR_ENABLE_BUTTON, toggle_motor_enabled_isr_handler, NULL);
	Button_SetInterruptHandler(REDUNDANT_BUTTON, toggle_motor_enabled_isr_handler, NULL); //Repete a funcionalidade do MOTOR_ENABLE_BUTTON.
}

/**
 * Função que verifica se os motores estão habilitados.
 * 
 * @return true or false (1 or 0).
 */
bool Hal_MotorIsEnabled(void)
{
	return motor_enabled;
}

/**
 * Função que lê o sensor de refletância informado.
 * 
 * @param sensor_num Identifica o sensor.
 * 
 * @return GPIO level.
 */
int Hal_ReadReflecSensor(reflecsensor_num_t sensor_num)
{
	return ReflecSensor_Read(sensor_num);
}

/**
 * Função que define a rotação do motor esquerdo.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Hal_SetLeftMotorRotation(motor_rotation_t rotation, uint32_t duty)
{
	Motor_SetRotation(LEFT_MOTOR, rotation, duty);
}

/**
 * Função que impede a rotação do motor esquerdo.
 */
void Hal_LockLeftMotorRotation(void)
{
	Motor_LockRotation(LEFT_MOTOR);
}

/**
 * Função que deixa livre a rotação do motor esquerdo.
 */
void Hal_FreeLeftMotorRotation(void)
{
	Motor_FreeRotation(LEFT_MOTOR);
}

/**
 * Função que define a rotação do motor direito.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Hal_SetRightMotorRotation(motor_rotation_t rotation, uint32_t duty)
{
	Motor_SetRotation(RIGHT_MOTOR, rotation, duty);
}

/**
 * Função que impede a rotação do motor direito.
 */
void Hal_LockRightMotorRotation(void)
{
	Motor_LockRotation(RIGHT_MOTOR);
}

/**
 * Função que deixa livre a rotação do motor direito.
 */
void Hal_FreeRightMotorRotation(void)
{
	Motor_FreeRotation(RIGHT_MOTOR);
}