#include "DatabaseManager.h"
#include "Transportista.h" // Aquí sí incluimos el .h completo
#include "Flete.h"
#include <fstream> // Para std::ofstream (file streams)
#include <iostream>
#include <iomanip>
#include <cstdio> // Para std::remove (borrar archivos)
//aaa me llamo matias hola como estas todo bien y tu?
//Como estan todoos


// Implementación de 'generarReporte'
bool DatabaseManager::generarReporte(const Transportista& transportista) const {
    // 'const' al final, porque este método no modifica al DatabaseManager.
    
    // Tu 'Load_excel' simplificado a un .csv
    // (CSV = Comma Separated Values, un Excel muy simple)
    std::string filename = getFilename(transportista.getNombre(), transportista.getRut());
    
    // std::ofstream es un "output file stream"
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "!! Error: No se pudo crear el archivo " << filename << std::endl;
        return false;
    }

    // Escribimos el resumen (la "proforma") en el archivo.
    // Esto es básicamente un "copy-paste" de 'mostrarResumen'
    // pero usando 'file' en lugar de 'std::cout'.
    
    file << "PROFORMA FINAL\n";
    file << "CLIENTE:," << transportista.getNombre() << ",RUT:," << transportista.getRut() << "\n";
    file << "----------------------------------------\n";
    file << "ID FLETE,CANTIDAD (maxisacos),COSTO\n";

    // --- COLABORACIÓN [cite: 30] ---
    // El DatabaseManager colabora con el Transportista, pidiéndole
    // su lista de fletes para poder iterarla.
    for (const auto& flete : transportista.getFletes()) {
        file << flete->getID() << ","
             // Necesitamos "castear" el Servicio a Flete para
             // poder llamar a getCantidad().
             << static_cast<Flete*>(flete.get())->getCantidad() << ","
             << std::fixed << std::setprecision(0) << flete->calcularCosto() << "\n";
    }

    file << "----------------------------------------\n";
    file << "TOTAL A PAGAR:," << transportista.getCostoTotal() << "\n";

    file.close();
    std::cout << ">> Reporte final generado exitosamente: " << filename << std::endl;
    return true;
}

// Implementación de 'eliminarReporte'
bool DatabaseManager::eliminarReporte(const std::string& nombreEmpresa, int rut) const {
    std::string filename = getFilename(nombreEmpresa, rut);
    
    // std::remove retorna 0 si fue exitoso
    if (std::remove(filename.c_str()) == 0) {
        std::cout << ">> Reporte " << filename << " eliminado exitosamente." << std::endl;
        return true;
    } else {
        std::cerr << "!! Error: No se pudo encontrar o eliminar el reporte " << filename << std::endl;
        return false;
    }
}

// Ayudante privado
std::string DatabaseManager::getFilename(const std::string& nombre, int rut) const {
    // Creamos un nombre de archivo único, ej: "Transportes_A_12345678.csv"
    return nombre + "_" + std::to_string(rut) + ".csv";
}