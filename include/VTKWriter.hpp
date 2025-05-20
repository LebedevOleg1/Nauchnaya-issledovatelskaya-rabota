#pragma once
#include <string>   // Добавлено
#include <fstream>  // Добавлено
#include "Mesh.hpp"

class VTKWriter {
public:
    static void save(Mesh* mesh, int step) {
        std::string filename = "output_" + std::to_string(step) + ".vtr";
        std::ofstream file(filename);

        // Остальной код без изменений
        const int nx = mesh->get_nx();
        const Float3 vmin = mesh->get_vmin();

        file << "<?xml version=\"1.0\"?>\n";
        file << "<VTKFile type=\"RectilinearGrid\" version=\"0.1\">\n";
        file << "<RectilinearGrid WholeExtent=\"0 " << nx-1 << " 0 0 0 0\">\n";
        file << "<Piece Extent=\"0 " << nx-1 << " 0 0 0 0\">\n";
        
        file << "<PointData Scalars=\"Temperature\">\n";
        file << "<DataArray Name=\"Temperature\" type=\"Float32\" format=\"ascii\">\n";
        for(int i = 0; i < nx; ++i) file << mesh->get_T_curr()[i] << " ";
        file << "\n</DataArray>\n</PointData>\n";
        
        file << "<Coordinates>\n";
        file << "<DataArray type=\"Float32\" Name=\"X\">\n";
        for(int i = 0; i < nx; ++i) 
            file << vmin.x + (i + 0.5f)*mesh->get_hx() << " ";
        file << "\n</DataArray>\n";
        
        file << "<DataArray type=\"Float32\" Name=\"Y\">\n0.0\n</DataArray>\n";
        file << "<DataArray type=\"Float32\" Name=\"Z\">\n0.0\n</DataArray>\n";
        file << "</Coordinates>\n";
        
        file << "</Piece>\n</RectilinearGrid>\n</VTKFile>";
    }
};