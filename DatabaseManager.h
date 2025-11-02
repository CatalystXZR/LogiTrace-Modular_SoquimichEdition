#pragma once
#include <string> // <-- Sino no vmaos a poder usar strings xdd
class Transportista;/*Esta forward declaration, basicamente le dice al compilador "Oye, confie papi, si existe una clase llamada Transportista
pero aun no te voy a decir sus metodos ni variables, pero debes saber que si existe. Nos sirve para romper dependencias circulares, y acelerar la compilacion.
Como para que se ejecute la clase Transportista.h, la cual necesita incluir DatabaseManager.h (pq quizas un transportista quiere llamar al database manager,
y el databasemanager.h necesita llamar al Transportista.h, pq necesita saber que es un transportista, sin la forward declaration nos daria un bucle infinito,
ya que nuestro compilador tendria un problema como: Para que existan los pollos, deben haber huevos. Y para que existan huevos, deben existir pollos. Es un bucle infinito sin solucion
si se sigue esa logica. Por eso le estamos diciendo al compilador, Papito, ya existen los huevos. Todavia no te dire que incluye un huevo, pero debes saber que ya lo tenemos.)*/

// --- ASOCIACIÓN ---
class DatabaseManager {
public:
    DatabaseManager() = default; 

    // --- COLABORACIÓN ---
    bool generarReporte(const Transportista& transportista) const;

    // Usar std::string
    bool eliminarReporte(const std::string& nombreEmpresa, int rut) const;

private:
    // Usar std::string
    std::string getFilename(const std::string& nombre, int rut) const;
};