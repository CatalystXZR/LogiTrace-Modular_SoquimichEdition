#pragma once
#include "Servicio.h" // Incluye la clase base de la que hereda

// --- HERENCIA ---
// La clase Flete "es-un" tipo de Servicio.
class Flete : public Servicio {
private:
    // --- ENCAPSULAMIENTO ---
    int cantidadCarga; // Cantidad de maxisacos
    static const double PRECIO_POR_MAXISACO;

public:
    // Constructor
    Flete(int id, int carga);

    // --- POLIMORFISMO (Implementa la interfaz de Servicio) ---
    // 'override' confirma que estamos sobreescribiendo un método virtual.
    double calcularCosto() const override;
    void mostrarDetalle() const override;
    void setCantidad(int nuevaCantidad) override; // Para el Update

    // Getter específico de Flete
    int getCantidad() const;
};