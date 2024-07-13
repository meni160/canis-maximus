#include "..\Header\Appl.h"
#include "..\Header\Hal.h" 
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" 

void Appl_FollowLine(void);
void Appl_StopFollowingLine(void);

int SENSOR_READ[8];                                                 //variável que condiciona as leituras dos sensores
int SENSOR_WEIGHT[8] = {7000,5000,3000,2000,2000,3000,5000,7000};   //variavel que leva o peso de cada sensor
int RIGHT_VALOR, LEFT_VALOR = 0;                                    //variaveis utilizadas para de fato definir as velocidades dos motores

/**
 * Função que define as configurações iniciais da aplicação.
 */
void Appl_Initialize(void)
{
}

/**
 * Função que é executada em um loop eterno
 */
void Appl_Handler(void)
{
    if(Hal_MotorIsEnabled())
        Appl_FollowLine();
    else
        Appl_StopFollowingLine();
}

/**
 * Função que contém a rotina para o robô seguir linha.
 */
void Appl_FollowLine(void)
{
    for (int i = 0; i <= 7; i++){  //loop que le cada sensor, atribui a leitura a variável e multiplica a leitura pelo peso
        SENSOR_READ[i] = !Hal_ReadReflecSensor(i); 
        SENSOR_READ[i] = SENSOR_READ[i] * SENSOR_WEIGHT[i];
    }

    for (int i = 7; i >= 0; i--){ //procura o maior valor a direita do array e o guarda no variavel RIGHT_VALOR
        if (SENSOR_READ[i] > 0) RIGHT_VALOR = SENSOR_READ[i]; 
    }

    for (int i = 0; i <= 7; i++){ //procura o maior valor a esquerda do array e o guarda no variavel LEFT_VALOR
        if (SENSOR_READ[i] > 0) LEFT_VALOR = SENSOR_READ[i]; 
    }

    //define com a velocidade mínima a variavel que carrega o menor valor entre LEFT_VALOR e RIGHT_VALOR
    if (LEFT_VALOR > RIGHT_VALOR){
        RIGHT_VALOR = 2000;
    }else{
        LEFT_VALOR = 2000;
    }
    //define a velocidade dos motores com base nas variaveis LEFT_VALOR e RIGHT_VALOR
    Hal_SetLeftMotorRotation(MOTOR_CLOCKWISE, LEFT_VALOR);
    Hal_SetRightMotorRotation(MOTOR_CLOCKWISE, RIGHT_VALOR);
}

/**
 * Função que contém a rotina para o robô parar de seguir linha.
 */
void Appl_StopFollowingLine(void)
{
    Hal_LockLeftMotorRotation();
    Hal_LockRightMotorRotation();
}