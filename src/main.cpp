#include <iostream>
#include <string>
#include "analizador.h"
#include "arbol.h"
#include "nodo.h"

using namespace std;

int main() {
    int count = 0;
    Nodo** nodos = cargarFamilia("bin/familia.csv", count);
    if (nodos == nullptr || count == 0) {
        cout << "No se pudo cargar el archivo de familia." << endl;
        return 1;
    }
    Nodo* raiz = construirArbol(nodos, count);
    
    cargarContribuidores("bin/contribuidores.csv", nodos, count);
    
    Nodo* leader = nullptr;
    for (int i = 0; i < count; i++) {
        if (nodos[i]->is_chief) {
            leader = nodos[i];
            break;
        }
    }
    if (leader == nullptr) {
        cout << "No se encontro lider en los datos. Se asignara la raiz como lider." << endl;
        leader = raiz;
    }
    
    int opcion = 0;
    while (true) {
        validarLider(leader);
        
        cout << "\n Menu Principal \n";
        cout << "1. Mostrar linea de sucesion (solo vivos)\n";
        cout << "2. Actualizar datos de un nodo\n";
        cout << "3. Simular muerte del lider y reasignar liderazgo\n";
        cout << "4. Mostrar datos del lider actual\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(); 
        
        if (opcion == 1) {
            cout << "\nLinea de sucesion (solo vivos):\n";
            mostrarSucesion(raiz);
        } else if (opcion == 2) {
            int id;
            cout << "Ingrese el ID del nodo a actualizar: ";
            cin >> id;
            cin.ignore();
            Nodo* nodoActualizar = buscarNodo(raiz, id);
            if (nodoActualizar != nullptr) {
                actualizarNodo(nodoActualizar);
            } else {
                cout << "Nodo con ID " << id << " no encontrado." << endl;
            }
        } else if (opcion == 3) {
            cout << "Simulando la muerte del lider actual (ID: " << leader->id << ")." << endl;
            leader->is_dead = true;
            validarLider(leader);
        } else if (opcion == 4) {
            cout << "\nDatos del lider actual:\n";
            cout << "ID: " << leader->id 
                 << ", Nombre: " << leader->name << " " << leader->last_name 
                 << ", Edad: " << leader->age << endl;
            if (leader->contribuyentes != nullptr) {
                cout << "Lista de contribuidores:\n";
                Contribuidor* contrib = leader->contribuyentes;
                while(contrib != nullptr) {
                    cout << "- " << contrib->nombre 
                         << ", Edad: " << contrib->edad 
                         << ", Grado: " << contrib->grado 
                         << ", Descripcion: " << contrib->descripcion << endl;
                    contrib = contrib->siguiente;
                }
            } else {
                cout << "El lider no tiene contribuidores asociados." << endl;
            }
        } else if (opcion == 5) {
            cout << "Saliendo del programa." << endl;
            break;
        } else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    }
    
    liberarArbol(raiz);
    delete[] nodos;
    
    return 0;
}
