#pragma once // explicado en otro script.
#include "Servicio.h" // Incluye la clase base de la que hereda

// --- HERENCIA ---
// La clase Flete "IS-A" tipo de Servicio.
class Flete : public Servicio {
private:
    // --- ENCAPSULAMIENTO ---
    int cantidadCarga; // Cantidad de maxisacos
    static const double PRECIO_POR_MAXISACO;

public:
    // Constructor
    Flete(int id, int carga);

    // --- POLIMORFISMO (Implementa la interfaz de Servicio) ---
    // 'override' confirma que estamos sobreescribiendo un metodo virtual, el cual estamos OBLIGADOS utilizar aqui, ya que los metodos de Servicio.h son virtuales absolutos (virtual + =0)
    double calcularCosto() const override;
    void mostrarDetalle() const override;
    void setCantidad(int nuevaCantidad) override; // Para el Update

    // Getter específico de Flete
    int getCantidad() const;
};