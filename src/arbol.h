#ifndef ARBOL_H
#define ARBOL_H

#include "nodo.h"

// Función para construir el árbol a partir del arreglo de nodos
Nodo* construirArbol(Nodo** nodos, int count);

// Función para mostrar la línea de sucesión (solo miembros vivos)
void mostrarSucesion(Nodo* raiz);

// Función para buscar un nodo por id en el árbol
Nodo* buscarNodo(Nodo* raiz, int id);

// Función para actualizar los datos de un nodo (excepto id e id_father)
void actualizarNodo(Nodo* nodo);

// Función para asignar automáticamente un nuevo líder según las reglas establecidas
Nodo* asignarNuevoLider(Nodo* leader);

// Función para liberar la memoria del árbol y sus listas de contribuidores
void liberarArbol(Nodo* raiz);

#endif
