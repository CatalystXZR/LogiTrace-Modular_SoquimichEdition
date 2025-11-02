#pragma once
#include "Transportista.h"
#include "DatabaseManager.h"
#include <map>     
#include <string>  

// --- PATRÓN FACADE (FACHADA) ---
class LogiTraceManager {
private:
    // --- COMPOSICIÓN  ---
    std::map<int, Transportista> transportistas;
    DatabaseManager dbManager;

    // --- Métodos Privados (Lógica del Menú) ---
    void mostrarMenu() const;
    void opcionAgregarFlete();      // C
    void opcionMostrarResumen();     // R
    void opcionActualizarFlete();    // U
    void opcionEliminarFlete();      // D
    void opcionGenerarReporteFinal();
    void opcionEliminarReporteGuardado();

    // Ayudantes internos
    void pausarConsola() const;
    int leerEntero(const std::string& prompt);
    Transportista* getTransportista(int rut); 
    void listarTransportistas() const; 

public:
    LogiTraceManager() = default;
    void run();
};