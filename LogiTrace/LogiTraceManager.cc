#include "LogiTraceManager.h"
#include <iostream>
#include <limits> // Para std::numeric_limits
#include <string>

// Método principal que corre el bucle del menú
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
                std::cout << "Saliendo de LogiTrace... Adios!" << std::endl;
                break;
            default:
                std::cerr << "!! Opcion no valida. Intente de nuevo." << std::endl;
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
    std::cout << "\n========================================" << std::endl;
    std::cout << "  Bienvenido a LogiTrace v1.0" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Agregar Flete (Create)" << std::endl;
    std::cout << "2. Ver Resumen Transportista (Read)" << std::endl;
    std::cout << "3. Actualizar Flete (Update)" << std::endl;
    std::cout << "4. Eliminar Flete (Delete)" << std::endl;
    std::cout << "5. Generar Reporte Final y Facturar" << std::endl;
    std::cout << "6. Eliminar Reporte Guardado" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "========================================" << std::endl;
}

// --- CREATE  ---
void LogiTraceManager::opcionAgregarFlete() {
    std::cout << "-- [Agregar Flete] --" << std::endl;
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
    std::cout << "-- [Ver Resumen] --" << std::endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    // Buscamos en el 'map'
    auto it = transportistas.find(rut);
    if (it != transportistas.end()) {
        // 'it->second' es el objeto Transportista
        it->second.mostrarResumen();
    } else {
        std::cerr << "!! Error: Transportista con RUT " << rut << " no encontrado." << std::endl;
    }
}

// --- UPDATE  ---
void LogiTraceManager::opcionActualizarFlete() {
    std::cout << "-- [Actualizar Flete] --" << std::endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");
    
    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        std::cerr << "!! Error: Transportista no encontrado." << std::endl;
        return;
    }

    int idFlete = leerEntero("Ingrese ID del flete a modificar: ");
    int nuevaCantidad = leerEntero("Ingrese la NUEVA cantidad de maxisacos: ");
    
    // De nuevo, delegamos la tarea
    if (it->second.actualizarFlete(idFlete, nuevaCantidad)) {
        std::cout << ">> Flete ID " << idFlete << " actualizado exitosamente." << std::endl;
    } else {
        std::cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << std::endl;
    }
}

// --- DELETE  ---
void LogiTraceManager::opcionEliminarFlete() {
    std::cout << "-- [Eliminar Flete] --" << std::endl;
    int rut = leerEntero("Ingrese RUT de transportista: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        std::cerr << "!! Error: Transportista no encontrado." << std::endl;
        return;
    }

    int idFlete = leerEntero("Ingrese ID del flete a eliminar: ");

    if (it->second.eliminarFlete(idFlete)) {
        std::cout << ">> Flete ID " << idFlete << " eliminado exitosamente." << std::endl;
    } else {
        std::cerr << "!! Error: Flete con ID " << idFlete << " no encontrado." << std::endl;
    }
}

// Lógica de 'DATABASE_WRITER'
void LogiTraceManager::opcionGenerarReporteFinal() {
    std::cout << "-- [Generar Reporte Final] --" << std::endl;
    int rut = leerEntero("Ingrese RUT de transportista a facturar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        std::cerr << "!! Error: Transportista no encontrado." << std::endl;
        return;
    }
    
    Transportista& transportista = it->second;

    std::cout << "Generando reporte para " << transportista.getNombre() << "..." << std::endl;
    
    // --- COLABORACIÓN [cite: 30] ---
    // El Manager colabora con el dbManager, pasándole el objeto
    // Transportista que necesita.
    if (dbManager.generarReporte(transportista)) {
        // Si el reporte se genera bien, reseteamos la cuenta
        // (como pediste en el brief)
        transportista.facturar();
    } else {
        std::cerr << "!! Error al generar el reporte. No se facturara." << std::endl;
    }
}

// Lógica de 'DATABASE_WRITER' (Borrar)
void LogiTraceManager::opcionEliminarReporteGuardado() {
    std::cout << "-- [Eliminar Reporte Guardado] --" << std::endl;
    if (transportistas.empty()) {
        std::cout << "No hay transportistas registrados para borrar reportes." << std::endl;
        return;
    }

    std::cout << "Transportistas con reportes potenciales:" << std::endl;
    listarTransportistas(); // Mostramos la lista
    
    int rut = leerEntero("Ingrese RUT del transportista cuyo reporte desea eliminar: ");

    auto it = transportistas.find(rut);
    if (it == transportistas.end()) {
        std::cerr << "!! Error: Transportista no encontrado." << std::endl;
        return;
    }

    // Colaboramos con dbManager para borrar
    dbManager.eliminarReporte(it->second.getNombre(), it->second.getRut());
}


// --- Métodos Ayudantes ---

void LogiTraceManager::pausarConsola() const {
    std::cout << "\nPresione Enter para continuar..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (std::cin.gcount() == 0) {
        // Si el ignore anterior no hizo nada (porque el buffer ya estaba limpio)
        // esperamos un nuevo Enter.
        std::cin.get();
    }
}

// Función segura para leer un entero y evitar que el programa crashee
// si el usuario ingresa letras.
int LogiTraceManager::leerEntero(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpia el flag de error
            // Descarta la línea incorrecta del buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "!! Entrada invalida. Por favor ingrese un numero." << std::endl;
        } else {
            // Descarta cualquier cosa extra en la línea (ej. "123abc")
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::cout << "Transportista nuevo. Ingrese nombre de la empresa: ";
    std::string nombre;
    std::getline(std::cin, nombre);

    // Creamos y movemos el nuevo transportista al 'map'.
    // Usamos 'emplace' que es más eficiente que 'insert'.
    auto resultado = transportistas.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(rut),
        std::forward_as_tuple(nombre, rut)
    );

    // Devolvemos un puntero al objeto recién creado
    return &(resultado.first->second);
}

void LogiTraceManager::listarTransportistas() const {
    int i = 1;
    for (const auto& par : transportistas) {
        // par.first es el RUT (la key)
        // par.second es el Transportista (el value)
        std::cout << i++ << ". " << par.second.getNombre()
                  << " (RUT: " << par.first << ")" << std::endl;
    }
}