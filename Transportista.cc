#include "Transportista.h" //Incluimos este archivo, ya que nuestro .cc necesita conocer la definicion de su clase, y saber en que y como trabajara.
#include "Flete.h" //Incluimos este archivo, ya que nuestra clase Transportista.cc necesita conocer la definicion completa de la clase Flete.
#include <iostream>
#include <iomanip>   
#include <algorithm> 
using namespace std;

Transportista::Transportista(const std::string& nombre, int r) 
    : nombreEmpresa(nombre), rut(r), costoTotal(0.0) {}

std::string Transportista::getNombre() const { return nombreEmpresa; }
int Transportista::getRut() const { return rut; }
double Transportista::getCostoTotal() const { return costoTotal; }
const std::vector<std::unique_ptr<Servicio>>& Transportista::getFletes() const { return fletes; }

bool Transportista::fleteExiste(int id) const {
    for (const auto& flete : fletes) {
        if (flete->getID() == id) {
            return true; 
        }
    }
    return false; 
}

void Transportista::recalcularCostoTotal() {
    costoTotal = 0.0;
    for (const auto& flete : fletes) {
        costoTotal += flete->calcularCosto();
    }
}

//COMPOSICION 
bool Transportista::agregarFlete(int id, int cantidad) {
    if (fleteExiste(id)) {
        return false; 
    }
    fletes.push_back(make_unique<Flete>(id, cantidad));
    recalcularCostoTotal();
    return true; 
}


void Transportista::mostrarResumen() const {
    cout << "\n=== RESUMEN DE TRANSPORTISTA ===" << endl;
    cout << "Empresa: " << nombreEmpresa << " | RUT: " << rut << endl;
    
    if (fletes.empty()) {
        cout << "No hay fletes registrados." << endl;
        cout << "================================" << endl;
        return;
    }

    cout << "Fletes registrados:" << endl;
    for (const auto& flete : fletes) {
        flete->mostrarDetalle(); 
    }

    cout << "--------------------------------" << endl;
    cout << "COSTO TOTAL PROVISORIO: $" << fixed << setprecision(0) << costoTotal << endl;
    cout << "================================" << endl;
}

bool Transportista::actualizarFlete(int idFlete, int nuevaCantidad) {
    for (const auto& flete : fletes) {
        if (flete->getID() == idFlete) {
            flete->setCantidad(nuevaCantidad);
            recalcularCostoTotal();
            return true; 
        }
    }
    return false; 
}

bool Transportista::eliminarFlete(int idFlete) {
    auto old_size = fletes.size();
    
    fletes.erase(remove_if(fletes.begin(), fletes.end(),
        [idFlete](const unique_ptr<Servicio>& s) {
            return s->getID() == idFlete;
        }), 
        fletes.end());
        
    if (fletes.size() < old_size) {
        recalcularCostoTotal(); 
        return true;
    }
    return false; 
}

void Transportista::facturar() {
    fletes.clear(); 
    costoTotal = 0.0;
    cout << ">> Facturacion completa. Fletes del transportista reseteados." << endl;
}