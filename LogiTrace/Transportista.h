#pragma once
#include <string>
#include <vector>
#include <memory> // Para std::unique_ptr
#include "Servicio.h" // Incluimos la base abstracta

// --- COMPOSICIÓN y COLABORACIÓN [cite: 10, 11] ---
// Esta clase "tiene-un" nombre y "tiene-muchos" fletes.
// Esta es una relación de Composición: si borramos al Transportista,
// sus fletes también desaparecen.
class Transportista {
private:
    // --- ENCAPSULAMIENTO  ---
    std::string nombreEmpresa;
    int rutEmpresa;

    // --- POLIMORFISMO y COMPOSICIÓN ---
    // Usamos un vector de "punteros inteligentes" (unique_ptr)
    // a la clase base 'Servicio'.
    // Esto nos permite guardar CUALQUIER tipo de Servicio (Fletes, u otros
    // que creemos en el futuro) en la misma lista.
    std::vector<std::unique_ptr<Servicio>> fletes;

    // Función ayudante privada para buscar un flete
    Servicio* getFlete(int idFlete);

public:
    // Constructor. Nota: Usamos 'const&' para strings para
    // evitar copias innecesarias (más eficiente).
    Transportista(const std::string& nombre, int rut);

    // Deshabilitamos la copia para evitar problemas con unique_ptr
    Transportista(const Transportista&) = delete;
    Transportista& operator=(const Transportista&) = delete;

    // Habilitamos el "movimiento" (necesario para `std::map`)
    Transportista(Transportista&&) = default;
    Transportista& operator=(Transportista&&) = default;

    // Getters
    std::string getNombre() const;
    int getRut() const;
    const std::vector<std::unique_ptr<Servicio>>& getFletes() const;

    // --- Lógica del CRUD ---
    // CREATE 
    void agregarFlete(int idFlete, int cantidadCarga);
    
    // READ  (Tu `Calculate_subtotals`)
    void mostrarResumen() const;
    
    // UPDATE 
    bool actualizarFlete(int idFlete, int nuevaCantidad);
    
    // DELETE 
    bool eliminarFlete(int idFlete);

    // --- Otras lógicas de negocio ---
    double getCostoTotal() const;
    
    // Resetea los fletes después de facturar
    void facturar();
};