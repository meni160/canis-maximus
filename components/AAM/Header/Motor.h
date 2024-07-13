#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h> //uint32_t

typedef enum {
	MOTOR_NUM_0 = 0,
	MOTOR_NUM_1,
	NUM_OF_MOTOR,
} motor_num_t;

typedef enum {
	MOTOR_CLOCKWISE = 0,
	MOTOR_ANTI_CLOCKWISE,
} motor_rotation_t;

/**
 * Função que define as configurações iniciais associadas aos motores.
 */
void Motor_Initialize(void);

/**
 * Função que define a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 * 
 * @param rotation Identifica o sentido de rotação.
 * 
 * @param duty Define o duty cycle do limite de rotação.
 */
void Motor_SetRotation(motor_num_t motor_num, motor_rotation_t rotation, uint32_t duty);

/**
 * Função que impede a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 */
void Motor_LockRotation(motor_num_t motor_num);

/**
 * Função que deixa livre a rotação do motor informado.
 * 
 * @param motor_num Identifica o motor.
 */
void Motor_FreeRotation(motor_num_t motor_num);

#endif /* MOTOR_H_ */