#include "Flete.h"
#include <iostream>
#include <iomanip> // Para std::setprecision
using namespace std;

// Definimos e inicializamos la variable estática.
const double Flete::PRECIO_POR_MAXISACO = 87000.0;

// Constructor
Flete::Flete(int id, int carga)
    : Servicio(id), cantidadCarga(carga) {}

// Implementación de la lógica de negocio (tu `Calculate_freight_cost`)
double Flete::calcularCosto() const {
    // El 'const' al final significa que este método no modifica el objeto.
    return cantidadCarga * PRECIO_POR_MAXISACO;
}

// Implementación del método para mostrar detalles
void Flete::mostrarDetalle() const {
    cout << "    -> ID Flete: " << idServicio
              << " | Cantidad: " << cantidadCarga << " maxisacos"
              << " | Costo: $" << fixed << setprecision(0) << calcularCosto()
              << endl;
}

// Implementación del método para actualizar (el "Update" del CRUD)
void Flete::setCantidad(int nuevaCantidad) {
    this->cantidadCarga = nuevaCantidad;
}

int Flete::getCantidad() const {
    return cantidadCarga;
}