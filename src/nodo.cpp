#include "nodo.h"

Nodo::Nodo() : id(0), age(0), id_father(0), gender('H'),
               is_dead(false), was_chief(false), is_chief(false),
               padre(nullptr), hijoIzquierdo(nullptr), hermanoDerecho(nullptr),
               contribuyentes(nullptr), visited(false), resetDone(false) {
}