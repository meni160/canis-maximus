#ifndef REFLECSENSOR_H_
#define REFLECSENSOR_H_

typedef enum {
	REFLECSENSOR_NUM_0 = 0,
	REFLECSENSOR_NUM_1,
	REFLECSENSOR_NUM_2,
    REFLECSENSOR_NUM_3,
    REFLECSENSOR_NUM_4,
    REFLECSENSOR_NUM_5,
    REFLECSENSOR_NUM_6,
    REFLECSENSOR_NUM_7,
	NUM_OF_REFLECSENSOR,
} reflecsensor_num_t;

/**
 * Função que define as configurações iniciais associadas aos sensores de refletância.
 */
void ReflecSensor_Initialize(void);

/**
 * Função que lê o sensor de refletância informado.
 * 
 * @param sensor_num Identifica o sensor.
 * 
 * @return GPIO level.
 */
int ReflecSensor_Read(reflecsensor_num_t sensor_num);

#endif /* REFLECSENSOR_H_ */