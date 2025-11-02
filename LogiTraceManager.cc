#include "LogiTraceManager.h"
#include <iostream>
#include <limits> 
#include <utility> 

using namespace std;

// Método principal
void LogiTraceManager::run() {
    bool corriendo = true;
    while (corriendo) {
        mostrarMenu();
        int opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: opcionAgregarFlete(); break;
            case 2: opcionMostrarResumen(); break;
            case 3: opcionActualizarFlete(); break;
            case 4: opcionEliminarFlete(); break;
            case 5: opcionGenerarReporteFinal(); break;
            case 6: opcionEliminarReporteGuardado(); break;
            case 7:
                corriendo = false;
                cout << "Saliendo de LogiTrace... Adios!" << endl;
                break;
            default:
                cerr << "!! Opcion no valida. Intente de nuevo." << endl;
                break;
        }
        if (corriendo) {
            pausarConsola();
        }
    }
}

// Muestra el menú
void LogiTraceManager::mostrarMenu() const {
    cout << "\n========================================" << endl;
    cout << "  Bienvenido a LogiTrace v1.0" << endl;
    cout << "========================================" << endl;
    cout << "1. Agregar Flete (Create)" << endl;
    cout << "2. Ver Resumen Transportista (Read)" << endl;
    cout << "3. Actualizar Flete (Update)" << endl;
    cout << "4. Eliminar Flete (Delete)" << endl;
    cout << "5. Generar Reporte Final y Facturar" << endl;
    cout << "6. Eliminar Reporte Guardado" << endl;
    cout << "7. Salir" << endl;
    cout << "========================================" << endl;
}

// --- CREATE (MODIFICADO) ---
void LogiTraceManager::opcionAgregarFlete() {
    cout << "-- [Agregar Flete] --" << endl;
    
    // --- NUEVA LÓGICA: Mostrar transportistas existentes ---
    if (!transportistas.empty()) {
        cout << "Transportistas existentes:" << endl;
        listarTransportistas();
        cout << "----------------------------------------" << endl;
    }
    // --- FIN NUEVA LÓGICA ---
    
    int rut = leerEntero("Ingrese RUT de transportista (o uno nuevo): ");
    
    Transportista* transportista = getTransportista(rut);
    if (!transportista) return; 

    int idFlete = leerEntero("Ingrese ID del nuevo flete: ");
    int cantidad = leerEntero("Ingrese cantidad de maxisacos: ");

    if (transportista->agregarFlete(idFlete, cantidad)) {
        cout << ">> Flete ID " << idFlete << " agregado exitosamente." << endl;
    } else {
        cerr << "!! Error: El ID de flete " << idFlete << " ya existe para este transportista." << endl;
    }
}

// --- READ (MODIFICADO) ---
void LogiTraceManager::opcionMostrarResumen() {
    cout << "-- [Ver Resumen] --" << endl;
    
    // --- NUEVA LÓGICA: Mostrar transportistas existentes ---
    if (transportistas.empty()) {
        cout << "No hay transportistas registrados." << endl;
        return;
    }
    cout << "Transportistas existentes:" << endl;
    listarTransportistas();
    cout << "----------------------------------------" << endl;
    // --- FIN NUEVA LÓGICA ---

    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    auto it = transportistas.find(rut);
    if (it != transportistas.end()) {
        it->second.mostrarResumen();
    } else {
        cerr << "!! Error: Transportista con RUT " << rut << " no encontrado." << endl;
    }
}

// --- UPDATE (MODIFICADO) ---
void LogiTraceManager::opcionActualizarFlete() {
    cout << "-- [Actualizar Flete] --" << endl;

    // --- NUEVA LÓGICA: Mostrar transportistas existentes ---
    if (transportistas.empty()) {
        cout << "No hay transportistas para actualizar." << endl;
        return;
    }
    cout << "Transportistas existentes:" << endl;
    listarTransportistas();
    cout << "----------------------------------------" << endl;
    // --- FIN NUEVA LÓGICA ---
    
    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    // --- NUEVA LÓGICA: Mostrar fletes de ESE transportista ---
    cout << "Fletes actuales del transportista:" << endl;
    it->second.mostrarResumen(); // Usamos el resumen para mostrar los fletes
    // --- FIN NUEVA LÓGICA ---

    int idFlete = leerEntero("Ingrese ID del flete a modificar: ");
    int nuevaCantidad = leerEntero("Ingrese la NUEVA cantidad de maxisacos: ");
    
    if (it->second.actualizarFlete(idFlete, nuevaCantidad)) {
        cout << ">> Flete ID " << idFlete << " actualizado exitosamente." << endl;
    } else {
        cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << endl;
    }
}

// --- DELETE (MODIFICADO) ---
void LogiTraceManager::opcionEliminarFlete() {
    cout << "-- [Eliminar Flete] --" << endl;

    // --- NUEVA LÓGICA: Mostrar transportistas existentes ---
    if (transportistas.empty()) {
        cout << "No hay transportistas para eliminar." << endl;
        return;
    }
    cout << "Transportistas existentes:" << endl;
    listarTransportistas();
    cout << "----------------------------------------" << endl;
    // --- FIN NUEVA LÓGICA ---

    int rut = leerEntero("Ingrese RUT de transportista: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    // --- NUEVA LÓGICA: Mostrar fletes de ESE transportista ---
    cout << "Fletes actuales del transportista:" << endl;
    it->second.mostrarResumen();
    // --- FIN NUEVA LÓGICA ---

    int idFlete = leerEntero("Ingrese ID del flete a eliminar: ");

    if (it->second.eliminarFlete(idFlete)) {
        cout << ">> Flete ID " << idFlete << " eliminado exitosamente." << endl;
    } else {
        cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << endl;
    }
}

// --- GENERAR REPORTE (MODIFICADO) ---
void LogiTraceManager::opcionGenerarReporteFinal() {
    cout << "-- [Generar Reporte Final] --" << endl;

    // --- NUEVA LÓGICA: Mostrar transportistas existentes ---
    if (transportistas.empty()) {
        cout << "No hay transportistas para generar reportes." << endl;
        return;
    }
    cout << "Transportistas existentes:" << endl;
    listarTransportistas();
    cout << "----------------------------------------" << endl;
    // --- FIN NUEVA LÓGICA ---

    int rut = leerEntero("Ingrese RUT de transportista a facturar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }
    
    Transportista& transportista = it->second;
    cout << "Generando reporte para " << transportista.getNombre() << "..." << endl;
    
    if (dbManager.generarReporte(transportista)) {
        transportista.facturar();
    } else {
        cerr << "!! Error al generar el reporte. No se facturara." << endl;
    }
}

// --- ELIMINAR REPORTE (MODIFICADO) ---
void LogiTraceManager::opcionEliminarReporteGuardado() {
    cout << "-- [Eliminar Reporte Guardado] --" << endl;
    
    // --- LÓGICA EXISTENTE (ya cumplía el requisito) ---
    if (transportistas.empty()) {
        cout << "No hay transportistas registrados para borrar reportes." << endl;
        return;
    }
    cout << "Transportistas con reportes potenciales:" << endl;
    listarTransportistas(); 
    cout << "----------------------------------------" << endl;
    // --- FIN LÓGICA EXISTENTE ---
    
    int rut = leerEntero("Ingrese RUT del transportista cuyo reporte desea eliminar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    dbManager.eliminarReporte(it->second.getNombre(), it->second.getRut());
}


// --- Métodos Ayudantes ---

void LogiTraceManager::pausarConsola() const {
    cout << "\nPresione Enter para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.gcount() == 0) {
        cin.get();
    }
}

int LogiTraceManager::leerEntero(const string& prompt) {
    int valor;
    while (true) {
        cout << prompt;
        cin >> valor;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "!! Entrada invalida. Por favor ingrese un numero." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

Transportista* LogiTraceManager::getTransportista(int rut) {
    auto it = transportistas.find(rut);
    
    if (it != transportistas.end()) {
        return &(it->second); 
    }

    cout << "Transportista nuevo. Ingrese nombre de la empresa: ";
    string nombre;
    getline(cin, nombre); 

    auto resultado = transportistas.emplace(
        piecewise_construct,
        forward_as_tuple(rut),
        forward_as_tuple(nombre, rut)
    );

    return &(resultado.first->second); 
}

void LogiTraceManager::listarTransportistas() const {
    int i = 1;
    for (const auto& par : transportistas) {
        cout << "  " << i++ << ". " << par.second.getNombre()
                  << " (RUT: " << par.first << ")" << endl;
    }
}