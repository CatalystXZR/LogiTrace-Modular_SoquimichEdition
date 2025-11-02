#pragma once
#include <string>

// Adelantamos la declaración de Transportista para evitar
// una "inclusión circular". Esto es una buena práctica.
class Transportista;

// --- ASOCIACIÓN  ---
// Esta clase "usa-un" Transportista para hacer su trabajo.
// No posee al transportista, solo lo recibe temporalmente.
// Implementa tu 'DATABASE_WRITER'
class DatabaseManager {
public:
    DatabaseManager() = default; // Constructor por defecto

    // Recibe un Transportista por REFERENCIA CONSTANTE.
    // 'const' porque no lo va a modificar.
    // '&' (referencia) para no crear una copia.
    bool generarReporte(const Transportista& transportista) const;

    // Borra un reporte basado en los datos
    bool eliminarReporte(const string& nombreEmpresa, int rut) const;

private:
    // Ayudante privado para generar el nombre del archivo
    string getFilename(const string& nombre, int rut) const;
};