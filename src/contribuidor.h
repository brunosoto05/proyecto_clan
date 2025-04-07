#ifndef CONTRIBUIDOR_H
#define CONTRIBUIDOR_H

#include <string>

struct Contribuidor {
    std::string nombre;
    int edad;
    int id; 
    std::string descripcion;
    int grado;  
    Contribuidor* siguiente;
    
    Contribuidor();
};

#endif
