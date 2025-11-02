#include "Transportista.h"
#include "Flete.h" // Necesitamos incluir Flete para poder crearlos
#include <iostream>
#include <iomanip> // Para fixed, setprecision
#include <numeric> // Para accumulate
#include <algorithm> // Para find_if
using namespace std;

// Constructor
Transportista::Transportista(const string& nombre, int rut)
    : nombreEmpresa(nombre), rutEmpresa(rut) {}

// Getters
string Transportista::getNombre() const { return nombreEmpresa; }
int Transportista::getRut() const { return rutEmpresa; }
const vector<unique_ptr<Servicio>>& Transportista::getFletes() const {
    return fletes;
}

// CREATE 
void Transportista::agregarFlete(int idFlete, int cantidadCarga) {
    // Creamos un NUEVO objeto Flete en el 'heap' y lo guardamos
    // en nuestro vector usando un puntero inteligente.
    // make_unique es la forma comoda y segura de hacerlo.
    fletes.push_back(make_unique<Flete>(idFlete, cantidadCarga));
    cout << ">> Flete ID " << idFlete << " agregado exitosamente a "
              << nombreEmpresa << "." << endl;
}

// READ 
void Transportista::mostrarResumen() const {
    cout << "----------------------------------------" << endl;
    cout << "RESUMEN PROFORMA" << endl;
    cout << "CLIENTE: " << nombreEmpresa << " - RUT: " << rutEmpresa << endl;
    cout << "----------------------------------------" << endl;
    cout << "DETALLE DE FLETES:" << endl;

    if (fletes.empty()) {
        cout << "  (Sin fletes registrados)" << endl;
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

    cout << "----------------------------------------" << endl;
    cout << "TOTAL A PAGAR: $" << fixed << setprecision(0) << getCostoTotal() << endl;
    cout << "----------------------------------------" << endl;
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
    auto it = remove_if(fletes.begin(), fletes.end(),
                             [idFlete](const unique_ptr<Servicio>& s) {
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
    cout << ">> Cuenta de " << nombreEmpresa << " facturada y reseteada." << endl;
}

// Ayudante privado para buscar
Servicio* Transportista::getFlete(int idFlete) {
    // Usamos find_if para buscar en el vector
    auto it = find_if(fletes.begin(), fletes.end(),
                           [idFlete](const unique_ptr<Servicio>& s) {
                               return s->getID() == idFlete;
                           });

    if (it != fletes.end()) {
        return it->get(); // Devuelve el puntero 'raw' al objeto
    }
    return nullptr; // No encontrado
}