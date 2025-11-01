#include "Transportista.h"
#include "Flete.h" // Necesitamos incluir Flete para poder crearlos
#include <iostream>
#include <iomanip> // Para std::fixed, std::setprecision
#include <numeric> // Para std::accumulate
#include <algorithm> // Para std::find_if

// Constructor
Transportista::Transportista(const std::string& nombre, int rut)
    : nombreEmpresa(nombre), rutEmpresa(rut) {}

// Getters
std::string Transportista::getNombre() const { return nombreEmpresa; }
int Transportista::getRut() const { return rutEmpresa; }
const std::vector<std::unique_ptr<Servicio>>& Transportista::getFletes() const {
    return fletes;
}

// CREATE 
void Transportista::agregarFlete(int idFlete, int cantidadCarga) {
    // Creamos un NUEVO objeto Flete en el 'heap' y lo guardamos
    // en nuestro vector usando un puntero inteligente.
    // std::make_unique es la forma moderna y segura de hacerlo.
    fletes.push_back(std::make_unique<Flete>(idFlete, cantidadCarga));
    std::cout << ">> Flete ID " << idFlete << " agregado exitosamente a "
              << nombreEmpresa << "." << std::endl;
}

// READ 
void Transportista::mostrarResumen() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "RESUMEN PROFORMA" << std::endl;
    std::cout << "CLIENTE: " << nombreEmpresa << " - RUT: " << rutEmpresa << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "DETALLE DE FLETES:" << std::endl;

    if (fletes.empty()) {
        std::cout << "  (Sin fletes registrados)" << std::endl;
    } else {
        // --- POLIMORFISMO EN ACCIÓN [cite: 15, 23] ---
        // Iteramos sobre el vector de 'Servicio*'.
        // Cuando llamamos a flete->mostrarDetalle(), C++ sabe
        // automáticamente que debe llamar a la versión de 'Flete'
        // porque ese es el objeto real que está guardado.
        for (const auto& flete : fletes) {
            flete->mostrarDetalle();
        }
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "TOTAL A PAGAR: $" << std::fixed << std::setprecision(0) << getCostoTotal() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

// UPDATE 
bool Transportista::actualizarFlete(int idFlete, int nuevaCantidad) {
    Servicio* flete = getFlete(idFlete);
    if (flete) {
        // Aquí usamos el método 'setCantidad' de la interfaz 'Servicio'
        // que será implementado por 'Flete'.
        flete->setCantidad(nuevaCantidad);
        return true;
    }
    return false; // No se encontró el flete
}

// DELETE 
bool Transportista::eliminarFlete(int idFlete) {
    // Usamos el "idioma" de C++ erase-remove para borrar un elemento
    // del vector basado en una condición.
    auto it = std::remove_if(fletes.begin(), fletes.end(),
                             [idFlete](const std::unique_ptr<Servicio>& s) {
                                 return s->getID() == idFlete;
                             });

    if (it != fletes.end()) {
        fletes.erase(it, fletes.end()); // Aquí ocurre el borrado real
        return true;
    }
    return false; // No se encontró
}

// Ayudante para calcular el total
double Transportista::getCostoTotal() const {
    double total = 0.0;
    // --- COLABORACIÓN DE OBJETOS [cite: 30] ---
    // El Transportista "colabora" con sus objetos Flete,
    // pidiéndoles su costo y sumándolos.
    for (const auto& flete : fletes) {
        total += flete->calcularCosto(); // <-- Polimorfismo otra vez
    }
    return total;
}

// Resetea la cuenta (como pediste en el brief)
void Transportista::facturar() {
    fletes.clear(); // Borra todos los fletes del vector
    std::cout << ">> Cuenta de " << nombreEmpresa << " facturada y reseteada." << std::endl;
}

// Ayudante privado para buscar
Servicio* Transportista::getFlete(int idFlete) {
    // Usamos std::find_if para buscar en el vector
    auto it = std::find_if(fletes.begin(), fletes.end(),
                           [idFlete](const std::unique_ptr<Servicio>& s) {
                               return s->getID() == idFlete;
                           });

    if (it != fletes.end()) {
        return it->get(); // Devuelve el puntero 'raw' al objeto
    }
    return nullptr; // No encontrado
}