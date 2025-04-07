#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>
#include "nodo.h"
#include "contribuidor.h"

// Función para cargar los datos familiares desde un CSV.
// Se almacena cada registro en un arreglo dinámico de punteros a Nodo.
// 'count' contendrá el número total de nodos leídos.
Nodo** cargarFamilia(const std::string& filename, int& count);

// Función para cargar los contribuidores desde un CSV y asignarlos al nodo correspondiente (según id).
void cargarContribuidores(const std::string& filename, Nodo** nodos, int count);

#endif
