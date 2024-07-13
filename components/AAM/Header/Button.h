#ifndef BUTTON_H_
#define BUTTON_H_

#include "driver/gpio.h"

typedef enum {
	BUTTON_NUM_0 = 0,
	BUTTON_NUM_1,
	NUM_OF_BUTTON,
} button_num_t;

/**
 * Função que define as configurações iniciais associadas aos botões.
 */
void Button_Initialize(void);

/**
 * Função que define a rotina de interrupção para o botão informado.
 * 
 * @param button_num Identifica o botão.
 * 
 * @param isr_handler Identifica a função de interrupção.
 * 
 * @param args Parâmetro da função de interrupção.
 */
void Button_SetInterruptHandler(button_num_t button_num, gpio_isr_t isr_handler, void *args);

#endif /* BUTTON_H_ */