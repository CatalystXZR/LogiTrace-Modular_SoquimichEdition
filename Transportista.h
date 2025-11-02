#pragma once
#include "Servicio.h" 
#include <vector>
#include <string>
#include <memory> 

class Transportista {
private:
    std::string nombreEmpresa;
    int rut;
    std::vector<std::unique_ptr<Servicio>> fletes;
    double costoTotal;

    void recalcularCostoTotal();
    bool fleteExiste(int id) const;

public:
    Transportista(const std::string& nombre, int r);

    std::string getNombre() const;
    int getRut() const;
    double getCostoTotal() const;
    const std::vector<std::unique_ptr<Servicio>>& getFletes() const;

    bool agregarFlete(int id, int cantidad); // C
    
    // --- MODIFICADO ---
    // Añadido 'const' para que LogiTraceManager pueda llamarlo
    // sin modificar el objeto (mejora de diseño).
    void mostrarResumen() const; // R
    
    bool actualizarFlete(int idFlete, int nuevaCantidad); // U
    bool eliminarFlete(int idFlete); // D
    
    void facturar();
};