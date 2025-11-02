#pragma once //esto fue lo que nos resolvio los errores de definicion multiple xd.
/* Como esta es una clase abstracta, que esta presente en varias clases derivadas (transportista, flete.h por ejemplo), cuando tratamos de compilar el programa completo,
el compilador trata de definir esta clase Servicio dos veces, lo cual tira error y no deja ejecutarlo.*/
// sin includes, pq solo usamos variables de tipo int.

class Servicio {
protected:
    int idServicio;

public:
    // Constructor
    Servicio(int id) : idServicio(id) {}
    
    // Destructor virtual, muy importante para el POLIMORFISMO.
    virtual ~Servicio() = default;

    // --- Métodos Virtuales para la ABSTRACCION ---
    //La palabra virtual, sumado al = 0, se nos transforma en metodos virtuales puros, obligando a la clase derivada Flete a implementarlos.
    virtual double calcularCosto() const = 0;
    virtual void mostrarDetalle() const = 0;
    virtual void setCantidad(int nuevaCantidad) = 0; 

    // --- ENCAPSULAMIENTO ---
    // Implementación directa en el .h porque si, queda mas facil que implementarlo fuera.
    int getID() const { return idServicio; }
};