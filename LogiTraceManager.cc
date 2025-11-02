#include "LogiTraceManager.h"
#include <iostream>
#include <limits> // Para std::numeric_limits
#include <string>
using namespace std;
// Método principal que corre el bucle del menú
void LogiTraceManager::run() {  //Como este es el orquestador, con el metodo run(), ejecutamos los metodos de databasemanager. Aqui, esta la colaboracion de objetos.
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

// Muestra el menú de opciones
void LogiTraceManager::mostrarMenu() const {
    // system("cls"); // Descomentar en Windows para limpiar pantalla
    // system("clear"); // Descomentar en Linux/Mac para limpiar pantalla
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

// --- CREATE  ---
void LogiTraceManager::opcionAgregarFlete() {
    cout << "-- [Agregar Flete] --" << endl;
    int rut = leerEntero("Ingrese RUT de transportista (sin dig. verif.): ");
    
    // Busca al transportista. Si no existe, lo crea.
    Transportista* transportista = getTransportista(rut);
    if (!transportista) return; // Ocurrió un error

    int idFlete = leerEntero("Ingrese ID del nuevo flete: ");
    int cantidad = leerEntero("Ingrese cantidad de maxisacos: ");

    // --- COLABORACIÓN [cite: 30] ---
    // El Manager le delega la tarea de agregar el flete
    // al objeto Transportista correspondiente.
    transportista->agregarFlete(idFlete, cantidad);
}

// --- READ  ---
void LogiTraceManager::opcionMostrarResumen() {
    cout << "-- [Ver Resumen] --" << endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    // Buscamos en el 'map'
    auto it = transportistas.find(rut);
    if (it != transportistas.end()) {
        // 'it->second' es el objeto Transportista
        it->second.mostrarResumen();
    } else {
        cerr << "!! Error: Transportista con RUT " << rut << " no encontrado." << endl;
    }
}

// --- UPDATE  ---
void LogiTraceManager::opcionActualizarFlete() {
    cout << "-- [Actualizar Flete] --" << endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    int idFlete = leerEntero("Ingrese ID del flete a modificar: ");
    int nuevaCantidad = leerEntero("Ingrese la NUEVA cantidad de maxisacos: ");
    
    // De nuevo, delegamos la tarea
    if (it->second.actualizarFlete(idFlete, nuevaCantidad)) {
        cout << ">> Flete ID " << idFlete << " actualizado exitosamente." << endl;
    } else {
        cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << endl;
    }
}

// --- DELETE  ---
void LogiTraceManager::opcionEliminarFlete() {
    cout << "-- [Eliminar Flete] --" << endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    int idFlete = leerEntero("Ingrese ID del flete a eliminar: ");

    if (it->second.eliminarFlete(idFlete)) {
        cout << ">> Flete ID " << idFlete << " eliminado exitosamente." << endl;
    } else {
        cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << endl;
    }
}

// Lógica de 'DATABASE_WRITER'
void LogiTraceManager::opcionGenerarReporteFinal() {
    cout << "-- [Generar Reporte Final] --" << endl;
    int rut = leerEntero("Ingrese RUT de transportista a facturar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }
    
    Transportista& transportista = it->second;

    cout << "Generando reporte para " << transportista.getNombre() << "..." << endl;
    
    // --- COLABORACIÓN [cite: 30] ---
    // El Manager colabora con el dbManager, pasándole el objeto
    // Transportista que necesita.
    if (dbManager.generarReporte(transportista)) {
        // Si el reporte se genera bien, reseteamos la cuenta
        // (como pediste en el brief)
        transportista.facturar();
    } else {
        cerr << "!! Error al generar el reporte. No se facturara." << endl;
    }
}

// Lógica de 'DATABASE_WRITER' (Borrar)
void LogiTraceManager::opcionEliminarReporteGuardado() {
    cout << "-- [Eliminar Reporte Guardado] --" << endl;
    if (transportistas.empty()) {
        cout << "No hay transportistas registrados para borrar reportes." << endl;
        return;
    }

    cout << "Transportistas con reportes potenciales:" << endl;
    listarTransportistas(); // Mostramos la lista
    
    int rut = leerEntero("Ingrese RUT del transportista cuyo reporte desea eliminar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        cerr << "!! Error: Transportista no encontrado." << endl;
        return;
    }

    // Colaboramos con dbManager para borrar
    dbManager.eliminarReporte(it->second.getNombre(), it->second.getRut());
}


// --- Métodos Ayudantes ---

void LogiTraceManager::pausarConsola() const {
    cout << "\nPresione Enter para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.gcount() == 0) {
        // Si el ignore anterior no hizo nada (porque el buffer ya estaba limpio)
        // esperamos un nuevo Enter.
        cin.get();
    }
}

// Función segura para leer un entero y evitar que el programa crashee
// si el usuario ingresa letras.
int LogiTraceManager::leerEntero(const string& prompt) {
    int valor;
    while (true) {
        cout << prompt;
        cin >> valor;

        if (cin.fail()) {
            cin.clear(); // Limpia el flag de error
            // Descarta la línea incorrecta del buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "!! Entrada invalida. Por favor ingrese un numero." << endl;
        } else {
            // Descarta cualquier cosa extra en la línea (ej. "123abc")
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

// Ayudante para buscar o crear un transportista
Transportista* LogiTraceManager::getTransportista(int rut) {
    // Buscamos si el transportista ya existe
    auto it = transportistas.find(rut);
    
    if (it != transportistas.end()) {
        // Si existe, devolvemos un puntero a él
        return &(it->second);
    }

    // Si no existe, lo creamos
    cout << "Transportista nuevo. Ingrese nombre de la empresa: ";
    string nombre;
    getline(cin, nombre);

    // Creamos y movemos el nuevo transportista al 'map'.
    // Usamos 'emplace' que es más eficiente que 'insert'.
    auto resultado = transportistas.emplace(
        piecewise_construct,
        forward_as_tuple(rut),
        forward_as_tuple(nombre, rut)
    );

    // Devolvemos un puntero al objeto recién creado
    return &(resultado.first->second);
}

void LogiTraceManager::listarTransportistas() const {
    int i = 1;
    for (const auto& par : transportistas) {
        // par.first es el RUT (la key)
        // par.second es el Transportista (el value)
        cout << i++ << ". " << par.second.getNombre()
                  << " (RUT: " << par.first << ")" << endl;
    }
}