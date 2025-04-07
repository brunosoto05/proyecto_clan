#include "arbol.h"
#include <iostream>

// Función auxiliar para mostrar la línea de sucesión sin duplicados
void mostrarSucesionAux(Nodo* raiz) {
    if (raiz == nullptr) return;

    // Si ya se imprimió este nodo, se omite
    if (raiz->visited) {
        return;
    }
    raiz->visited = true; // Marcar como impreso

    // Imprime el nodo solo si está vivo
    if (!raiz->is_dead) {
        std::cout << "ID: " << raiz->id 
                  << ", Nombre: " << raiz->name << " " << raiz->last_name 
                  << ", Edad: " << raiz->age << std::endl;
    }

    // Recorrer el primer hijo y luego los hermanos
    mostrarSucesionAux(raiz->hijoIzquierdo);
    mostrarSucesionAux(raiz->hermanoDerecho);
}

// Función auxiliar para resetear los flags de impresión en todo el árbol
void resetFlags(Nodo* raiz) {
    if (raiz == nullptr) return;
    if (raiz->resetDone) return; // Evita procesar un nodo más de una vez

    // Restablecer la bandera de impresión
    raiz->visited = false;
    raiz->resetDone = true;

    resetFlags(raiz->hijoIzquierdo);
    resetFlags(raiz->hermanoDerecho);
}

// Función auxiliar para limpiar la bandera de reseteo, para que el árbol quede "limpio" para la siguiente llamada
void clearResetFlags(Nodo* raiz) {
  if (raiz == nullptr) return;
  if (!raiz->resetDone) return; // Si ya está limpio, no se procesa nuevamente
  
  raiz->resetDone = false;
  clearResetFlags(raiz->hijoIzquierdo);
  clearResetFlags(raiz->hermanoDerecho);
}

// Función pública para mostrar la línea de sucesión (solo vivos) sin duplicados
void mostrarSucesion(Nodo* raiz) {
  // Recorrer el árbol y marcar los nodos ya impresos
  mostrarSucesionAux(raiz);
  // Luego, resetear las banderas para futuras llamadas
  resetFlags(raiz);
  clearResetFlags(raiz);
}

// Construir el árbol relacionando cada nodo con su padre (usando id_father)
Nodo* construirArbol(Nodo** nodos, int count) {
  Nodo* raiz = nullptr;
  for (int i = 0; i < count; i++) {
    Nodo* current = nodos[i];
    if (current->id_father == 0) {
      // Se asume que el nodo con id_father 0 es la raíz
      raiz = current;
    } else {
      // Buscar el padre según id_father
      for (int j = 0; j < count; j++) {
        if (nodos[j]->id == current->id_father) {
                    current->padre = nodos[j];
                    if (nodos[j]->hijoIzquierdo == nullptr) {
                      nodos[j]->hijoIzquierdo = current;
                    } else {
                        Nodo* sibling = nodos[j]->hijoIzquierdo;
                        while(sibling->hermanoDerecho != nullptr) {
                          sibling = sibling->hermanoDerecho;
                        }
                        sibling->hermanoDerecho = current;
                      }
                      break;
                    }
                  }
                }
              }
              return raiz;
            }
            
            Nodo* buscarNodo(Nodo* raiz, int id) {
              if (raiz == nullptr) return nullptr;
              if (raiz->id == id) return raiz;
              Nodo* result = buscarNodo(raiz->hijoIzquierdo, id);
              if (result != nullptr) return result;
              return buscarNodo(raiz->hermanoDerecho, id);
            }
            
            void actualizarNodo(Nodo* nodo) {
              if (nodo == nullptr) return;
              std::cout << "Actualizando nodo ID: " << nodo->id << std::endl;
              
              std::cout << "Nombre actual: " << nodo->name << ". Ingrese nuevo nombre (o enter para mantener): ";
              std::string input;
              std::getline(std::cin, input);
              if (!input.empty()) nodo->name = input;
              
              std::cout << "Apellido actual: " << nodo->last_name << ". Ingrese nuevo apellido (o enter para mantener): ";
              std::getline(std::cin, input);
              if (!input.empty()) nodo->last_name = input;
              
              std::cout << "Genero actual: " << nodo->gender << ". Ingrese nuevo genero (H/M) (o enter para mantener): ";
              std::getline(std::cin, input);
              if (!input.empty()) nodo->gender = input[0];
              
              std::cout << "Edad actual: " << nodo->age << ". Ingrese nueva edad (o enter para mantener): ";
              std::getline(std::cin, input);
              if (!input.empty()) nodo->age = std::stoi(input);
              
              std::cout << "Estado de vida actual (0 vivo, 1 muerto): " << nodo->is_dead << ". Ingrese nuevo estado (0/1) (o enter para mantener): ";
              std::getline(std::cin, input);
              if (!input.empty()) nodo->is_dead = (std::stoi(input) == 1);
              
    std::cout << "Fue jefe anteriormente (0/1): " << nodo->was_chief << ". Ingrese nuevo valor (0/1) (o enter para mantener): ";
    std::getline(std::cin, input);
    if (!input.empty()) nodo->was_chief = (std::stoi(input) == 1);
    
    std::cout << "Es jefe actualmente (0/1): " << nodo->is_chief << ". Ingrese nuevo valor (0/1) (o enter para mantener): ";
    std::getline(std::cin, input);
    if (!input.empty()) nodo->is_chief = (std::stoi(input) == 1);
  }
  
  // Función auxiliar: Buscar el primer descendiente vivo varón en el subárbol (excluyendo el nodo raíz)
  Nodo* buscarPrimerVivoVaronEnSubarbol(Nodo* node) {
    if (node == nullptr) return nullptr;
    if (!node->is_dead && node->gender == 'H') return node;
    Nodo* candidate = buscarPrimerVivoVaronEnSubarbol(node->hijoIzquierdo);
    if (candidate != nullptr) return candidate;
    return buscarPrimerVivoVaronEnSubarbol(node->hermanoDerecho);
  }
  
  // Función auxiliar similar para buscar descendientes vivos femeninos (si fuera necesario)
  Nodo* buscarPrimerVivoMujerEnSubarbol(Nodo* node) {
    if (node == nullptr) return nullptr;
    if (!node->is_dead && node->gender == 'M') return node;
    Nodo* candidate = buscarPrimerVivoMujerEnSubarbol(node->hijoIzquierdo);
    if (candidate != nullptr) return candidate;
    return buscarPrimerVivoMujerEnSubarbol(node->hermanoDerecho);
  }

  Nodo* asignarNuevoLider(Nodo* leader) {
    // Si el líder tiene más de 70 años, se inhabilita para ser líder.
    if (leader->age > 70) {
      leader->is_dead = true;
    }
    
    Nodo* candidato = nullptr;
    
    // 1. Buscar entre los hijos directos.
    if (leader->hijoIzquierdo != nullptr) {
      candidato = buscarPrimerVivoVaronEnSubarbol(leader->hijoIzquierdo);
      if (candidato != nullptr) {
        return candidato;
      }
    }
    
    // 2. Buscar entre los hermanos y, si es posible, entre los tíos.
    if (leader->padre != nullptr) {
      // Buscar en hermanos
      Nodo* sibling = leader->padre->hijoIzquierdo;
      while (sibling != nullptr) {
        if (sibling != leader && !sibling->is_dead && sibling->gender == 'H') {
          return sibling;
        }
        // Si el hermano no es hombre o no cumple, buscar en su subárbol.
        if (sibling != leader && !sibling->is_dead) {
          candidato = buscarPrimerVivoVaronEnSubarbol(sibling->hijoIzquierdo);
          if (candidato != nullptr) {
            return candidato;
          }
        }
        sibling = sibling->hermanoDerecho;
      }
      // Buscar en tíos (hermanos del padre)
      if (leader->padre->padre != nullptr) {
        Nodo* uncle = leader->padre->padre->hijoIzquierdo;
        while (uncle != nullptr) {
          if (uncle != leader->padre && !uncle->is_dead && uncle->gender == 'H') {
              return uncle;
            }
            if (uncle != leader->padre && !uncle->is_dead) {
              candidato = buscarPrimerVivoVaronEnSubarbol(uncle->hijoIzquierdo);
              if (candidato != nullptr) {
                return candidato;
              }
            }
            uncle = uncle->hermanoDerecho;
          }
        }
      }
      
      // 3. Buscar entre ancestros (por ejemplo, buscando el primer ancestro que tenga al menos dos hijos
      // y a partir de allí se intente hallar un candidato).
      Nodo* ancestro = leader->padre;
      while (ancestro != nullptr) {
        int countChildren = 0;
        Nodo* child = ancestro->hijoIzquierdo;
        while (child != nullptr) {
          countChildren++;
          child = child->hermanoDerecho;
        }
        if (countChildren >= 2) {
          candidato = buscarPrimerVivoVaronEnSubarbol(ancestro->hijoIzquierdo);
          if (candidato != nullptr) {
            return candidato;
          }
        }
        ancestro = ancestro->padre;
      }
      
      // 4. Si el líder tiene más de 70 años, ya no se permite retenerlo como líder.
      if (leader->age > 70) {
        return nullptr;  // Indica que no se encontró un candidato adecuado.
      }
      
      // 5. Si el líder está dentro de la edad permitida y no se encontró otro candidato,
      // se retorna el mismo (aunque este caso no debería ocurrir si se modificó la edad a más de 70).
      return leader;
    }
    
    // Función que valida si el líder actual cumple las condiciones para ser líder.
    // Si no es así (edad > 70 o marcado como muerto), se intenta reasignar el liderazgo.
    
    
    void liberarArbol(Nodo* raiz) {
    if (raiz == nullptr) return;
    // Liberar la lista de contribuidores
    Contribuidor* contrib = raiz->contribuyentes;
    while(contrib != nullptr) {
      Contribuidor* temp = contrib;
      contrib = contrib->siguiente;
      delete temp;
    }
    // Liberar recursivamente los hijos
    Nodo* child = raiz->hijoIzquierdo;
    while(child != nullptr) {
      Nodo* nextSibling = child->hermanoDerecho;
      liberarArbol(child);
      child = nextSibling;
    }
    delete raiz;
}
