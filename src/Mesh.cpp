#include "Mesh.hpp"

Mesh::Mesh(int nx, int ny, Float3 min, Float3 max, float alpha) 
    : nx(nx), ny(ny), v_min(min), v_max(max), alpha(alpha), data(nx * ny) 
{
    hx = (max.x - min.x)/nx;
    hy = (max.y - min.y)/ny;
    calculate_cell_centers();
    calculate_dt();
}

void Mesh::calculate_cell_centers() {
    // Реализация остается пустой для 1D случая
}

void Mesh::calculate_dt() {
    dt = 0.4 * (hx * hx) / (4 * alpha);
}

void Mesh::apply_boundary_conditions() {
    for(int j = 0; j < ny; ++j) {
        data.curr.T[j * nx] = 0.0f;
        data.curr.T[(j+1)*nx - 1] = 0.0f;
    }
}

void Mesh::initialize_gaussian(float T0, float sigma) {
    float x_center = (v_max.x + v_min.x)/2;
    for(int i = 0; i < nx; ++i) {
        for(int j = 0; j < ny; ++j) {
            int idx = i + j*nx;
            float x = v_min.x + (i + 0.5f)*hx;
            data.curr.T[idx] = T0 * exp(-pow(x - x_center, 2)/(2*sigma*sigma));
        }
    }
}

void Mesh::step() {
    for(int i = 1; i < nx-1; ++i) {
        for(int j = 0; j < ny; ++j) {
            int idx = i + j*nx;
            float laplacian = (data.curr.T[idx+1] - 2*data.curr.T[idx] + data.curr.T[idx-1])/(hx*hx);
            data.next.T[idx] = data.curr.T[idx] + alpha * dt * laplacian;
        }
    }
}