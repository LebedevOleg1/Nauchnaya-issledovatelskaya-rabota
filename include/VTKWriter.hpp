#pragma once
#include "Mesh.hpp"
#include <fstream>

class VTKWriter {
public:
    static void save(Mesh* mesh, int step) {
        std::string filename = "output_" + std::to_string(step) + ".vtr";
        std::ofstream file(filename);

        file << "<?xml version=\"1.0\"?>\n";
        file << "<VTKFile type=\"RectilinearGrid\" version=\"0.1\">\n";
        file << "<RectilinearGrid WholeExtent=\"0 " << mesh->get_nx()-1 << " 0 0 0 0\">\n";
        file << "<Piece Extent=\"0 " << mesh->get_nx()-1 << " 0 0 0 0\">\n";
        file << "<PointData Scalars=\"Temperature\">\n";
        file << "<DataArray Name=\"Temperature\" type=\"Float32\" format=\"ascii\">\n";

        float* T = mesh->get_T_curr();
        for (int i = 0; i < mesh->get_nx(); ++i) {
            file << T[i] << " ";
        }

        file << "\n</DataArray>\n</PointData>\n<Coordinates>\n";
        file << "<DataArray type=\"Float32\" Name=\"X\">\n";
        for (int i = 0; i < mesh->get_nx(); ++i) {
            // Используем геттер вместо прямого доступа
            file << mesh->get_vmin().x + (i + 0.5f) * mesh->get_hx() << " ";
        }
        file << "\n</DataArray>\n</Coordinates>\n</Piece>\n</RectilinearGrid>\n</VTKFile>";
    }
};