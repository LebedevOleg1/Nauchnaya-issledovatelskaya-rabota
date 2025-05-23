#pragma once
#include <utility>  // Добавлено для std::swap

// 3D вектор (для совместимости с CUDA)
struct Float3 {
    float x, y, z;
    Float3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

// Состояние системы (сырые указатели для CUDA)
struct State {
    float* T;   // Температура
    Float3* v;  // Скорость (не используется)
    float* P;   // Давление (не используется)
    int size;

    State(int size) : size(size) {
        T = new float[size]();
        v = new Float3[size]();
        P = new float[size]();
    }

    ~State() {
        delete[] T;
        delete[] v;
        delete[] P;
    }
};

// Расширенное состояние (для двойной буферизации)
struct ExtState {
    State* curr;
    State* next;

    ExtState(int size) {
        curr = new State(size);
        next = new State(size);
    }

    ~ExtState() {
        delete curr;
        delete next;
    }

    void swap() {
        std::swap(curr, next);  // Теперь std::swap доступен
    }
};