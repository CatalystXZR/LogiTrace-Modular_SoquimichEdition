#pragma once
#include <string>

// --- ABSTRACCIÓN ---
// Esta es una "clase base abstracta". Define un CONTRATO.
// Dice: "Cualquier cosa que sea un 'Servicio' DEBE ser capaz de
// calcular su costo y mostrar su detalle".
// No podemos crear un objeto "Servicio" directamente, solo objetos de clases
// que hereden de él (como "Flete").
class Servicio {
protected:
    // 'protected' significa que esta clase y sus clases hijas (como Flete)
    // pueden ver esta variable. 'main' no puede.
    int idServicio;

public:
    // Constructor
    Servicio(int id) : idServicio(id) {}

    // Destructor virtual: MUY IMPORTANTE en clases base
    // para que la memoria se libere correctamente.
    virtual ~Servicio() {}

    // Getter simple
    int getID() const { return idServicio; }

    // --- MÉTODOS VIRTUALES PUROS (= 0) ---
    // Esto es lo que hace a la clase "abstracta".
    // Forzamos a las clases hijas (Flete) a implementar esta lógica.
    virtual double calcularCosto() const = 0;
    virtual void mostrarDetalle() const = 0;
    virtual void setCantidad(int nuevaCantidad) = 0;
};