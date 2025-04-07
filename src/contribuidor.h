#ifndef CONTRIBUIDOR_H
#define CONTRIBUIDOR_H

#include <string>

struct Contribuidor {
    std::string nombre;
    int edad;
    int id;  // ID del nodo (miembro de la familia) al que pertenece
    std::string descripcion;
    int grado;  // Grado de contribución (1 a 10)
    Contribuidor* siguiente;
    
    Contribuidor();
};

#endif