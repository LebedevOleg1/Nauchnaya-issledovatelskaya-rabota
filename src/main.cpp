#include "Mesh.hpp"
#include <iostream>
#include <fstream>

void save_to_csv(const Mesh& mesh, int step) {
    std::ofstream file("output_" + std::to_string(step) + ".csv");
    for(int i = 0; i < mesh.get_nx(); ++i) {
        float x = mesh.get_vmin().x + (i + 0.5f) * mesh.get_hx();
        file << x << "," << mesh.data.curr.T[i] << "\n";
    }
}

int main() {
    const int nx = 50;
    const int ny = 1;
    const float alpha = 0.1f;
    const Float3 vmin(0.0f, 0.0f, 0.0f);
    const Float3 vmax(10.0f, 1.0f, 0.0f);
    
    Mesh mesh(nx, ny, vmin, vmax, alpha);
    mesh.initialize_gaussian(100.0f, 1.0f);
    
    const int total_steps = 100;
    for(int step = 0; step < total_steps; ++step) {
        mesh.apply_boundary_conditions();
        mesh.step();
        mesh.data.swap_states();
        
        if(step % 10 == 0) {
            save_to_csv(mesh, step/10);
            std::cout << "Step " << step << " completed\n";
        }
    }
    
    return 0;
}