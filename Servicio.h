#pragma once

// Este archivo define la interfaz abstracta (Abstracción)
// No necesita includes porque no usa tipos complejos, solo 'int'.

class Servicio {
protected:
    int idServicio;

public:
    // Constructor
    Servicio(int id) : idServicio(id) {}
    
    // Destructor virtual (CLAVE para el Polimorfismo)
    virtual ~Servicio() = default;

    // --- Métodos Virtuales Puros (Abstracción) ---
    // Obligan a las clases derivadas (Flete) a implementarlos.
    virtual double calcularCosto() const = 0;
    virtual void mostrarDetalle() const = 0;
    virtual void setCantidad(int nuevaCantidad) = 0; 

    // --- Encapsulamiento ---
    // Implementación 'inline' (directa en el .h) porque es muy simple.
    int getID() const { return idServicio; }
};