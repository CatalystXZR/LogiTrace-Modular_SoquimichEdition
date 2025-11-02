#include "Flete.h" // Incluye su propio encabezado, para corroborar que esta funcion Flete.cc esta implementando todo lo que prometimos en el .h, y que todo coincide segun lo que dijimos que hariamos en el .h
#include <iostream>
#include <iomanip> // Para setprecision

using namespace std;

const double Flete::PRECIO_POR_MAXISACO = 87000.0;

// HERENCIA Llama al constructor de la clase base (Servicio)
Flete::Flete(int id, int carga)
    : Servicio(id), cantidadCarga(carga) {}

double Flete::calcularCosto() const {
    return cantidadCarga * PRECIO_POR_MAXISACO;
}

// Implementación del método para mostrar detalles
void Flete::mostrarDetalle() const {
    cout << "    -> ID Flete: " << idServicio
              << " | Cantidad: " << cantidadCarga << " maxisacos"
              << " | Costo: $" << fixed << setprecision(0) << calcularCosto()
              << endl;
}

// --- UPDATE --- (metodo para actualizar la info de los fletes)
void Flete::setCantidad(int nuevaCantidad) {
    this->cantidadCarga = nuevaCantidad;
}

int Flete::getCantidad() const {
    return cantidadCarga;
}