#pragma once
#include "State.hpp"
#include <cmath>

class Mesh {
private:
    int nx, ny;
    Float3 v_min, v_max;
    float hx, hy;
    float alpha;
    
    void calculate_cell_centers();

public:
    ExtState data;
    float dt;

    // Геттеры для доступа к приватным полям
    int get_nx() const { return nx; }
    Float3 get_vmin() const { return v_min; }
    float get_hx() const { return hx; }

    Mesh(int nx, int ny, Float3 min, Float3 max, float alpha);
    
    void calculate_dt();
    void apply_boundary_conditions();
    void initialize_gaussian(float T0, float sigma);
    void step();
};