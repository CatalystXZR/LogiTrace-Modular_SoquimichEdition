#include "DatabaseManager.h"
#include "Transportista.h" // Aquí sí incluimos el .h completo
#include "Flete.h"
#include <fstream> // Para std::ofstream (file streams)
#include <iostream>
#include <iomanip>
#include <cstdio> // Para std::remove (borrar archivos)
using namespace std;

//Acaso esto igual? LOL
// HERMANO ESTA WEA ESTA BIZARRAAAA
// Implementación de 'generarReporte'
bool DatabaseManager::generarReporte(const Transportista& transportista) const {
    // 'const' al final, porque este método no modifica al DatabaseManager.
    
    // Tu 'Load_excel' simplificado a un .csv
    // (CSV = Comma Separated Values, un Excel muy simple)
    string filename = getFilename(transportista.getNombre(), transportista.getRut());
    
    // std::ofstream es un "output file stream"
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "!! Error: No se pudo crear el archivo " << filename << endl;
        return false;
    }

    // Escribimos el resumen (la "proforma") en el archivo.
    // Esto es básicamente un "copy-paste" de 'mostrarResumen'
    // pero usando 'file' en lugar de 'cout'.
    
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
             << fixed << setprecision(0) << flete->calcularCosto() << "\n";
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
    
    // remove retorna 0 si fue exitoso
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
    // Creamos un nombre de archivo único, ej: "Transportes_A_12345678.csv"
    return nombre + "_" + to_string(rut) + ".csv";
}