#pragma once
#include <vector>
#include <array>

using index_t = int;
using float_t = float;

struct Float3 {
    float_t x, y, z;
    Float3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

struct State {
    std::vector<float> T;
    std::vector<Float3> v;
    std::vector<float> P;
    
    State(size_t size) {
        T.resize(size, 0.0f);
        v.resize(size, Float3());
        P.resize(size, 0.0f);
    }
};

struct ExtState {
    State curr;
    State next;
    
    ExtState(size_t size) : curr(size), next(size) {}
    
    void swap_states() {
        std::swap(curr, next);
    }
};