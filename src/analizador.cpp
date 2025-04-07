#include "analizador.h"
#include <fstream>
#include <sstream>
#include <iostream>

Nodo** cargarFamilia(const std::string& filename, int& count) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo: " << filename << std::endl;
        count = 0;
        return nullptr;
    }
    std::string line;
    count = 0;
    bool headerSkipped = false;
    while (getline(file, line)) {
        if (!headerSkipped) { 
            headerSkipped = true;
            continue;
        }
        if(line.empty()) continue;
        count++;
    }
    Nodo** nodos = new Nodo*[count];
    file.clear();
    file.seekg(0, std::ios::beg);
    headerSkipped = false;
    int index = 0;
    while (getline(file, line)) {
        if (!headerSkipped) { headerSkipped = true; continue; }
        if(line.empty()) continue;
        std::istringstream ss(line);
        std::string token;
        Nodo* nuevo = new Nodo();
        getline(ss, token, ',');
        nuevo->id = std::stoi(token);
        
        getline(ss, token, ',');
        nuevo->name = token;
        
        getline(ss, token, ',');
        nuevo->last_name = token;
        
        getline(ss, token, ',');
        nuevo->gender = token[0];
        
        getline(ss, token, ',');
        nuevo->age = std::stoi(token);
        
        getline(ss, token, ',');
        nuevo->id_father = std::stoi(token);
        
        getline(ss, token, ',');
        nuevo->is_dead = (std::stoi(token) == 1);
        
        getline(ss, token, ',');
        nuevo->was_chief = (std::stoi(token) == 1);
        
        getline(ss, token, ',');
        nuevo->is_chief = (std::stoi(token) == 1);
        
        nuevo->padre = nullptr;
        nuevo->hijoIzquierdo = nullptr;
        nuevo->hermanoDerecho = nullptr;
        nuevo->contribuyentes = nullptr;
        
        nodos[index++] = nuevo;
    }
    file.close();
    return nodos;
}

void cargarContribuidores(const std::string& filename, Nodo** nodos, int count) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error abriendo el archivo: " << filename << std::endl;
        return;
    }
    std::string line;
    bool headerSkipped = false;
    while(getline(file, line)) {
        if(!headerSkipped) { headerSkipped = true; continue; }
        if(line.empty()) continue;
        std::istringstream ss(line);
        std::string token;
        Contribuidor* nuevo = new Contribuidor();
        
        getline(ss, token, ',');
        nuevo->nombre = token;
        
        getline(ss, token, ',');
        nuevo->edad = std::stoi(token);
        
        getline(ss, token, ',');
        int nodeId = std::stoi(token);
        
        getline(ss, token, ',');
        nuevo->descripcion = token;
        
        getline(ss, token, ',');
        nuevo->grado = std::stoi(token);
        
        nuevo->siguiente = nullptr;
        
        for (int i = 0; i < count; i++) {
            if (nodos[i]->id == nodeId) {
                Contribuidor** head = &(nodos[i]->contribuyentes);
                if (*head == nullptr || 
                    ((*head)->grado < nuevo->grado) || 
                    (((*head)->grado == nuevo->grado) && ((*head)->edad < nuevo->edad))) {
                    nuevo->siguiente = *head;
                    *head = nuevo;
                } else {
                    Contribuidor* current = *head;
                    while(current->siguiente != nullptr && 
                          !((current->siguiente->grado < nuevo->grado) || 
                          ((current->siguiente->grado == nuevo->grado) && (current->siguiente->edad < nuevo->edad)))) {
                        current = current->siguiente;
                    }
                    nuevo->siguiente = current->siguiente;
                    current->siguiente = nuevo;
                }
                break;
            }
        }
    }
    file.close();
}
