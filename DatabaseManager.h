#pragma once
#include <string> // <-- Incluido para std::string

// Declaración adelantada (Forward Declaration)
class Transportista;

// --- ASOCIACIÓN ---
class DatabaseManager {
public:
    DatabaseManager() = default; 

    // --- COLABORACIÓN ---
    bool generarReporte(const Transportista& transportista) const;

    // Usar std::string
    bool eliminarReporte(const std::string& nombreEmpresa, int rut) const;

private:
    // Usar std::string
    std::string getFilename(const std::string& nombre, int rut) const;
};