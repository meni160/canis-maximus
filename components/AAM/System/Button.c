#include "..\Header\Button.h"

#define GPIO_BUTTON_0    GPIO_NUM_19
#define GPIO_BUTTON_1    GPIO_NUM_18

/**
 * Função que define as configurações iniciais associadas aos botões.
 */
void Button_Initialize(void)
{
    gpio_reset_pin(GPIO_BUTTON_0);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(GPIO_BUTTON_0, GPIO_MODE_INPUT);   //seta o gpio como saída
    gpio_set_pull_mode(GPIO_BUTTON_0, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(GPIO_BUTTON_0, GPIO_INTR_NEGEDGE); //falling edge
    
    gpio_reset_pin(GPIO_BUTTON_1);                        //reseta as condigurações do GPIO para um default do compilador
    gpio_set_direction(GPIO_BUTTON_1, GPIO_MODE_INPUT);   //seta o gpio como saída
    gpio_set_pull_mode(GPIO_BUTTON_1, GPIO_PULLUP_ONLY);  //ativa pullup no gpio
    gpio_set_intr_type(GPIO_BUTTON_1, GPIO_INTR_NEGEDGE); //falling edge

    gpio_install_isr_service(0);
}

/**
 * Função que define a rotina de interrupção para o botão informado.
 * 
 * @param button_num Identifica o botão.
 * 
 * @param isr_handler Identifica a função de interrupção.
 * 
 * @param args Parâmetro da função de interrupção.
 */
void Button_SetInterruptHandler(button_num_t button_num, gpio_isr_t isr_handler, void *args)
{
    switch (button_num)
    {
        case BUTTON_NUM_0:
            gpio_isr_handler_add(GPIO_BUTTON_0, isr_handler, args);
            break;
        
        case BUTTON_NUM_1:
            gpio_isr_handler_add(GPIO_BUTTON_1, isr_handler, args);
            break;
    
        default:
            break;
    }
}
