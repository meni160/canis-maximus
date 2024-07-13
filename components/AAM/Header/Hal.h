#ifndef HAL_H_
#define HAL_H_

#include "ReflecSensor.h"
#include "Motor.h"
#include "Button.h"
#include <stdbool.h>

/**
 * Função que define as configurações iniciais da camada de abstração de hardware.
 */
void Hal_Initialize(void);

/**
 * Função que verifica se os motores estão habilitados.
 * 
 * @return true or false (1 or 0).
 */
bool Hal_MotorIsEnabled(void);

/**
 * Função que lê o sensor de refletância informado.
 * 
 * @param sensor_num Identifica o sensor.
 * 
 * @return GPIO level.
 */
int Hal_ReadReflecSensor(reflecsensor_num_t sensor_num);

/**
 * Função que define a rotação do motor esquerdo.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Hal_SetLeftMotorRotation(motor_rotation_t rotation, uint32_t duty);

/**
 * Função que impede a rotação do motor esquerdo.
 */
void Hal_LockLeftMotorRotation(void);

/**
 * Função que deixa livre a rotação do motor esquerdo.
 */
void Hal_FreeLeftMotorRotation(void);

/**
 * Função que define a rotação do motor direito.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Hal_SetRightMotorRotation(motor_rotation_t rotation, uint32_t duty);

/**
 * Função que impede a rotação do motor direito.
 */
void Hal_LockRightMotorRotation(void);

/**
 * Função que deixa livre a rotação do motor direito.
 */
void Hal_FreeRightMotorRotation(void);

#endif /* HAL_H_ */