#pragma once /*eComo un mismo script (por ejemplo, LogiTraceManager.cc) puede terminar leyendo la definición
 de esta clase varias veces (al incluir otros archivos .h como Flete.h y Transportista.h, que también incluyen Servicio.h), con este comando hacemos que el compilador
solo lea la definición de la clase una vez por script. Esto evita errores de definicion multiple (nuestro dolor de cabeza durante varias horas, que no entendiamos xd). */
#include "Transportista.h"
#include "DatabaseManager.h"
#include <map>     
#include <string>  
/* Esta clase LogiTraceManager es nuestro orquestador. Que es un orquestador? En una orquesta, existe un baterista, un flautista, un violinista, y alguien que toca el bajo.
El baterista puede tocar Rock Metal, el flautista puede tocar musica clasica, el violinista puede tocar pop, y el bajo puede tocar reggeaton, todos hacen cosas distintas.
Pero es el Orquestador (quien tiene la batuta) el que hace que todos los distintos miembros de la orquesta trabajen en sincronia y produzcan una linda medolia.*/


class LogiTraceManager {
private:
    // --- COMPOSICIÓN  ---
    std::map<int, Transportista> transportistas;
    DatabaseManager dbManager;

    // --- metodos privados ---
    /* Aqui vemos el mayusculas que estamos cumpliendo con un crud funcional.
    1. El metodo agregar flete, permite CREATE/Crear nuevos fletes.
    2. El metodo Mostrar resumen, permite READ/Leer los fletes creados
    3. El metodo Actualizar Flete, permite Updatear/Actualizar la info de los fletes creados
    4. El metodo Eliminar Flete, permite DELETEAR/Eliminar fletes/info agregada/creada anteriormente.*/
    void mostrarMenu() const;
    void opcionAgregarFlete();      // Crud
    void opcionMostrarResumen();     // cRud
    void opcionActualizarFlete();    // crUd
    void opcionEliminarFlete();      // cruD
    void opcionGenerarReporteFinal(); //Crud x2
    void opcionEliminarReporteGuardado();` // cruD x2

    // Ayudantes internos
    void pausarConsola() const; //pausa el programa, y espera que el usuario ingrese la tecla enter para continuar
    int leerEntero(const std::string& prompt); //Valida que la entrada de usuario sea un numero, y si no lo es lo pide de nuevo. Es un manejo de errores basico
    Transportista* getTransportista(int rut);  //Recorre el vector con la info de los transportistas, asociados a un rut. Si el rut no existe, crea el value (nombre empresa) y la key (rut)
    void listarTransportistas() const; //Recorre el vector con la info de todos los transportistas, y los printea a partir de una iteracion

public: /*La interfaz es publica, ya que como dijimos, este es nuestro orquestador. Es el unico metodo publico que llama la funcion main y lo usa para echar a andar todo.
Es el corazon de nuestro programa. Es quien oculta la realidad nefasta de todos los musicos de nuestra orquesta (clases), y hace que suene armonico (que todo funcione bien)*/
    LogiTraceManager() = default; //Le dice al constructor que no haga nada especial para construir esta clase, solo que genere el mismo el constructor vacio.
    void run(); //Este metodo publico lo ejecutara la main. Como dije, es el metodo que permite echar a andar TODOS los metodos privados definidos anteriormente en este script.
};