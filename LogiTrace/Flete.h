#pragma once
#include "Servicio.h"

// --- HERENCIA ---
// La clase Flete "es-un" tipo de Servicio. Hereda públicamente de Servicio.
// También demuestra ENCAPSULAMIENTO, ya que sus datos
// (cantidadCarga) son privados.
class Flete : public Servicio {
private:
    // --- ENCAPSULAMIENTO ---
    // Los datos están protegidos. Solo se accede mediante métodos públicos.
    int cantidadCarga; // Cantidad de maxisacos
    // Usamos 'static const' para un valor que es compartido por TODOS
    // los objetos Flete y no cambia.
    static const double PRECIO_POR_MAXISACO; // 87000

public:
    // Constructor: Llama al constructor de la clase base (Servicio)
    // usando la "lista de inicialización".
    Flete(int id, int carga);

    // --- POLIMORFISMO ---
    // La palabra 'override' le dice al compilador que estamos
    // implementando intencionalmente un método de la clase base.
    // Aquí es donde la magia del polimorfismo ocurre.
    virtual double calcularCosto() const override;
    virtual void mostrarDetalle() const override;
    virtual void setCantidad(int nuevaCantidad) override; // Para el Update

    // Getter específico de Flete
    int getCantidad() const;
};