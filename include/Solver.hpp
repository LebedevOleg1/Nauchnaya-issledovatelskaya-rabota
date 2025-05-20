#pragma once
#include "Mesh.hpp"

class Solver {
protected:
    Mesh* mesh;
    float alpha;
    float dt;

    virtual void calculate_dt();
    virtual void apply_bc();

public:
    Solver(Mesh* mesh, float alpha) : mesh(mesh), alpha(alpha) {
        calculate_dt();
    }

    virtual ~Solver() = default;

    virtual void initialize(float T0, float sigma);
    virtual void step() = 0;
};

// Реализация для CPU
class CpuSolver : public Solver {
public:
    using Solver::Solver;

    void step() override;
};