#ifndef NODO_H
#define NODO_H

#include <string>
#include "contribuidor.h"

struct Nodo {
    int id;
    std::string name;
    std::string last_name;
    char gender;  
    int age;
    int id_father;
    bool is_dead;
    bool was_chief;
    bool is_chief;
    
    Nodo* padre;
    Nodo* hijoIzquierdo;   
    Nodo* hermanoDerecho;  
    
    Contribuidor* contribuyentes;
    
    bool visited;
    bool resetDone;

    Nodo();
};

#endif
