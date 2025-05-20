#include "Solver.hpp"
#include "VTKWriter.hpp"

int main() {
    Mesh mesh(50, 1, {0, 0, 0}, {10, 1, 0});
    CpuSolver solver(&mesh, 0.1f);

    solver.initialize(100.0f, 1.0f);
    VTKWriter::save(&mesh, 0);

    for (int step = 0; step < 100; ++step) {
        solver.step();
        if (step % 10 == 0) {
            VTKWriter::save(&mesh, step / 10 + 1);
        }
    }

    return 0;
}