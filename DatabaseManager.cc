#include "DatabaseManager.h"
#include "Transportista.h" 
#include "Flete.h"         
#include <fstream>         
#include <iostream>
#include <iomanip>         
#include <cstdio>          

using namespace std;

// Implementación de 'generarReporte'
bool DatabaseManager::generarReporte(const Transportista& transportista) const {
    
    string filename = getFilename(transportista.getNombre(), transportista.getRut());
    
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "!! Error: No se pudo crear el archivo " << filename << endl;
        return false;
    }

    file << "PROFORMA FINAL\n";
    file << "CLIENTE:," << transportista.getNombre() << ",RUT:," << transportista.getRut() << "\n";
    file << "----------------------------------------\n";
    file << "ID FLETE,CANTIDAD (maxisacos),COSTO\n";

    // --- COLABORACIÓN ---
    for (const auto& servicio : transportista.getFletes()) {
        
        // static_cast para "bajar" de Servicio a Flete
        const Flete* fletePtr = static_cast<const Flete*>(servicio.get());
        
        file << fletePtr->getID() << ","
             << fletePtr->getCantidad() << ","
             << fixed << setprecision(0) << fletePtr->calcularCosto() << "\n";
    }

    file << "----------------------------------------\n";
    file << "TOTAL A PAGAR:," << transportista.getCostoTotal() << "\n";

    file.close();
    cout << ">> Reporte final generado exitosamente: " << filename << endl;
    return true;
}

// Implementación de 'eliminarReporte'
bool DatabaseManager::eliminarReporte(const string& nombreEmpresa, int rut) const {
    string filename = getFilename(nombreEmpresa, rut);
    
    if (remove(filename.c_str()) == 0) {
        cout << ">> Reporte " << filename << " eliminado exitosamente." << endl;
        return true;
    } else {
        cerr << "!! Error: No se pudo encontrar o eliminar el reporte " << filename << endl;
        return false;
    }
}

// Ayudante privado
string DatabaseManager::getFilename(const string& nombre, int rut) const {
    return nombre + "_" + to_string(rut) + ".csv";
}