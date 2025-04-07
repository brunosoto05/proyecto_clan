#ifndef ARBOL_H
#define ARBOL_H

#include "nodo.h"

Nodo* construirArbol(Nodo** nodos, int count);

void mostrarSucesion(Nodo* raiz);

Nodo* buscarNodo(Nodo* raiz, int id);

void actualizarNodo(Nodo* nodo);

Nodo* asignarNuevoLider(Nodo* leader);

void validarLider(Nodo*& leader);

void liberarArbol(Nodo* raiz);

#endif
