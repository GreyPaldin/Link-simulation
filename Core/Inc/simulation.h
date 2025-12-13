#ifndef SIMULATION_H
#define SIMULATION_H

// Структура для звена второго порядка
typedef struct {
    float K;          // Коэффициент усиления
    float T2;         // Постоянная времени T2  
    float T_sample;   // Время дискретизации
    float Step;       // Входной сигнал (ступенька)
    float E;          // Коэффициент E
} SecondOrderParams;

typedef struct {
    float y;          // Текущий выход
    float y_prev;     // Предыдущий выход
    float dy;         // Производная
    float dy_prev;    // Предыдущая производная
} SecondOrderState;

// Структура для звена первого порядка
typedef struct {
    float K;          // Коэффициент усиления
    float T1;         // Постоянная времени T1
    float T_sample;   // Время дискретизации
    float Step;       // Входной сигнал (ступенька)
} FirstOrderParams;

typedef struct {
    float y;          // Текущий выход
    float y_prev;     // Предыдущий выход
} FirstOrderState;

// Функции для звена второго порядка  
void SecondOrder_Init(SecondOrderState* state);
float SecondOrder_Update(const SecondOrderParams* params, SecondOrderState* state);

// Функции для звена первого порядка
void FirstOrder_Init(FirstOrderState* state);
float FirstOrder_Update(const FirstOrderParams* params, FirstOrderState* state);

#endif