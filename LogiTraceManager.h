#pragma once
#include "Transportista.h"
#include "DatabaseManager.h"
#include <map> // Para std::map

// --- PATRÓN FACADE (FACHADA) ---
// Esta clase es el único punto de entrada a nuestro sistema.
// El 'main' solo hablará con esta clase, y esta clase
// "orquestará" a las demás (Transportista, DatabaseManager).
// Esto implementa tu idea de "Orquestador/main y distintos nodos/clases".
class LogiTraceManager {
private:
    // --- COMPOSICIÓN  ---
    // El Manager "posee" la lista de todos los transportistas
    // y posee al "DatabaseManager".
    
    // Usamos un 'map' para guardar los transportistas.
    // La 'key' es el RUT (int) y el 'value' es el objeto Transportista.
    // Esto hace que buscar por RUT sea súper rápido y eficiente.
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
    Transportista* getTransportista(int rut); // Busca o crea un transportista
    void listarTransportistas() const; // Para el borrado de reportes

public:
    // Constructor por defecto
    LogiTraceManager() = default;

    // El único método público: iniciar el programa
    void run();
};