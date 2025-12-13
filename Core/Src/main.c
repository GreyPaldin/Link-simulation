#include "stm32f1xx.h"
#include "simulation.h"

// ВАРИАНТ 1: Звено ВТОРОГО порядка

SecondOrderParams params = {
    .K = 1.0f,
    .T2 = 1.0f,
    .E = 1.0f,
    .T_sample = 0.001f,
    .Step = 1.0f
};
SecondOrderState state;

/*
// ВАРИАНТ 2: Звено ПЕРВОГО порядка
FirstOrderParams params = {
    .K = 1.0f,
    .T1 = 1.0f,
    .T_sample = 0.001f,
    .Step = 1.0f
};
FirstOrderState state;
*/

float simulation_time = 0.0f;
volatile float current_output = 0.0f;

void SysTick_Handler(void) {
    // ВАРИАНТ 1: Для второго порядка
    current_output = SecondOrder_Update(&params, &state);
    
    // ВАРИАНТ 2: Для первого порядка
    // current_output = FirstOrder_Update(&params, &state);
    
    simulation_time += 0.001f;
}

void SysTick_Init(void) {
    SysTick->LOAD = 8001 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x07;
}

int main(void) {
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));
    
    simulation_time = 0.0f;
    current_output = 0.0f;
    
    // ВАРИАНТ 1: Инициализация второго порядка
    SecondOrder_Init(&state);
    
    // ВАРИАНТ 2: Инициализация первого порядка
    // FirstOrder_Init(&state);
    
    SysTick_Init();
    __enable_irq();
    
    while (1) {
    }
}