#include "Solver.hpp"
#include <cmath>

void Solver::calculate_dt() {
    dt = 0.4f * (mesh->get_hx() * mesh->get_hx()) / (4 * alpha);
}

void Solver::apply_bc() {
    float* T = mesh->get_T_curr();
    T[0] = 0.0f;
    T[mesh->get_nx() - 1] = 0.0f;
}

void Solver::initialize(float T0, float sigma) {
    const int nx = mesh->get_nx();
    float* T = mesh->get_T_curr();
    
    // Используем геттеры вместо прямого доступа
    float x_center = (mesh->get_vmax().x + mesh->get_vmin().x) / 2;
    float hx = mesh->get_hx();
    Float3 vmin = mesh->get_vmin();

    for (int i = 0; i < nx; ++i) {
        float x = vmin.x + (i + 0.5f) * hx;
        T[i] = T0 * exp(-pow(x - x_center, 2) / (2 * sigma * sigma));
    }
}

void CpuSolver::step() {
    const int nx = mesh->get_nx();
    const float hx = mesh->get_hx();
    float* T_curr = mesh->get_T_curr();
    float* T_next = mesh->get_T_next();

    for (int i = 1; i < nx-1; ++i) {
        float laplacian = (T_curr[i+1] - 2*T_curr[i] + T_curr[i-1]) / (hx*hx);
        T_next[i] = T_curr[i] + alpha * dt * laplacian;
    }

    apply_bc();
    mesh->data->swap();
}