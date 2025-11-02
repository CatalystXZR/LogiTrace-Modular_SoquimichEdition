#include "DatabaseManager.h" // 1. Incluimos su propio plano (.h) para que sepa qué funciones tiene que implementar.
#include "Transportista.h" // 2. TRAEMOS AL TRANSPORTISTA. Lo necesitamos para poder "usarlo" (Asociación) y pedirle sus datos (getNombre, getFletes).
#include "Flete.h"   // 3. TRAEMOS AL FLETE. Lo necesitamos para la Línea 29. Como el transportista nos da un "Servicio" genérico, tenemos que forzarlo a ser "Flete" (static_cast) para poder usar getCantidad().
#include <fstream>   // 4. Librería para manejo de archivo (se llama file stream), o sea, para poder *escribir* el .csv.
#include <iostream>
#include <iomanip>   
#include <cstdio>      // 5. Esta es la librería C-Style que tiene la función mágica "remove" para borrar archivos del disco duro.

using namespace std; // Usamos esto en el .cc para no escribir std:: a cada rato.
/* using namespace std; SOLO SIRVE EN ARCHIVOS DE EXTENSION .CC, en .H TIRA UN ERROR BRIGIDO XD*/

// --- ASOCIACIÓN / COLABORACIÓN ---
// Esta es la pega principal del DBManager. Fíjate que recibe al Transportista (const Transportista&).
// NO es dueño de él (no es Composición), solo lo "usa" temporalmente para hacer su pega (Asociación).
// Es el "Contador" pidiéndole la "Carpeta" al "Administrador" (LogiTraceManager).
bool DatabaseManager::generarReporte(const Transportista& transportista) const {

    // Llama al ayudante privado de abajo (Línea 58) para armar el nombre del archivo (ej: "Empresa_123.csv").
 string filename = getFilename(transportista.getNombre(), transportista.getRut());

    // Aquí creamos el flujo de salida (ofstream) y abrimos (o creamos) el archivo .csv.
 ofstream file(filename);

    // Siempre hay que chequear si se pudo abrir el archivo. Si no, avisamos y nos vamos.
 if (!file.is_open()) {
     cerr << "!! Error: No se pudo crear el archivo " << filename << endl;
     return false;
 }

    // Escribimos la cabecera del Excel (CSV) con los datos del Transportista.
    // Aquí "colaboramos" llamando a transportista.getNombre() y getRut().
 file << "PROFORMA FINAL\n";
 file << "CLIENTE:," << transportista.getNombre() << ",RUT:," << transportista.getRut() << "\n";
 file << "----------------------------------------\n";
 file << "ID FLETE,CANTIDAD (maxisacos),COSTO\n";

 // --- INICIO DE LA COLABORACIÓN MAS DIRECTA ---
    // 1. Le pedimos al transportista (nuestro socio) que nos pase su lista de fletes (transportista.getFletes()).
 for (const auto& servicio : transportista.getFletes()) { 
        // 2. ¡OJO AQUÍ! El transportista nos da un "Servicio" genérico (gracias al Polimorfismo).
        // Pero nosotros (el DBManager) sabemos que *en verdad* es un "Flete" y necesitamos su método getCantidad().
        // static_cast es un "confía papi, yo sé lo que hago": lo forzamos a ser un puntero a Flete.
     const Flete* fletePtr = static_cast<const Flete*>(servicio.get()); 
     
        // 3. Ahora que tenemos el "FletePtr", colaboramos con él pidiéndole todos sus datos (getID, getCantidad, calcularCosto)
        // y los escribimos en el archivo.
        file << fletePtr->getID() << "," 
            << fletePtr->getCantidad() << "," 
            << fixed << setprecision(0) << fletePtr->calcularCosto() << "\n"; 
}

 file << "----------------------------------------\n";
    // Colaboramos una última vez con el Transportista para pedirle el costo total ya calculado.
 file << "TOTAL A PAGAR:," << transportista.getCostoTotal() << "\n";

    // Cerramos el archivo. ¡Importante para que Excel no reclame después!
 file.close();
 cout << ">> Reporte final generado exitosamente: " << filename << endl;
 return true;
}

// Esta es la otra pega del DBManager: borrar reportes.
bool DatabaseManager::eliminarReporte(const string& nombreEmpresa, int rut) const {
    // Usamos el mismo ayudante para saber QUÉ archivo borrar.
 string filename = getFilename(nombreEmpresa, rut);

    // Esta es la "cosa" que borra archivos (de la librería <cstdio>).
    // Le pide al Sistema Operativo (Windows) que borre el archivo. Si devuelve 0, todo salió bien.
    // (Como dijiste: si el archivo está abierto o no hay permisos, esto va a fallar).
 if (remove(filename.c_str()) == 0) {
     cout << ">> Reporte " << filename << " eliminado exitosamente." << endl;
     return true;
 } else {
     cerr << "!! Error: No se pudo encontrar o eliminar el reporte " << filename << endl;
     return false;
 }
}

// --- AYUDANTE PRIVADO (ENCAPSULAMIENTO) ---
// Esta función privada (Encapsulamiento) solo arma el nombre del archivo.
// Junta el nombre + "_" + el rut (convertido a string) + ".csv". Simple y ordenado.
string DatabaseManager::getFilename(const string& nombre, int rut) const {
 return nombre + "_" + to_string(rut) + ".csv";
}