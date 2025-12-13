#include "simulation.h"

// ===== ЗВЕНО ПЕРВОГО ПОРЯДКА =====
void FirstOrder_Init(FirstOrderState* state) {
    state->y = 0.0f;
    state->y_prev = 0.0f;
}

float FirstOrder_Update(const FirstOrderParams* params, FirstOrderState* state) {
    // Простая формула как в машине состояний
    state->y = state->y_prev + params->T_sample * (params->K * params->Step - state->y_prev) / params->T1;
    
    // Обновляем предыдущее значение
    state->y_prev = state->y;
    
    return state->y;
}

// ===== ЗВЕНО ВТОРОГО ПОРЯДКА =====
void SecondOrder_Init(SecondOrderState* state) {
    state->y = 0.0f;
    state->y_prev = 0.0f;
    state->dy = 0.0f;
    state->dy_prev = 0.0f;
}

float SecondOrder_Update(const SecondOrderParams* params, SecondOrderState* state) {
    // Расчет производной (правильно)
    float dy = (state->y - state->y_prev) / params->T_sample;
    
    // ПРАВИЛЬНАЯ дискретная форма: T2²·d²y/dt² + T2·E·dy/dt + y = K·Step
    // У тебя в Matlab: ddy = (K*Step - y - T2*1*dy) / T2;
    float ddy = (params->K * params->Step - state->y - params->T2 * params->E * dy) / params->T2;
    
    // Интегрирование (правильно)
    float dy_new = state->dy + ddy * params->T_sample;
    float y_new = state->y + dy_new * params->T_sample;
    
    // Обновление состояний
    state->y_prev = state->y;
    state->y = y_new;
    state->dy_prev = state->dy;
    state->dy = dy_new;
    
    return state->y;
}