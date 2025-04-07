#include "arbol.h"
#include <iostream>

void mostrarSucesionAux(Nodo* raiz) {
    if (raiz == nullptr) return;

    if (raiz->visited) {
        return;
    }
    raiz->visited = true; 

    if (!raiz->is_dead) {
        std::cout << "ID: " << raiz->id 
                  << ", Nombre: " << raiz->name << " " << raiz->last_name 
                  << ", Edad: " << raiz->age << std::endl;
    }

    mostrarSucesionAux(raiz->hijoIzquierdo);
    mostrarSucesionAux(raiz->hermanoDerecho);
}

void resetFlags(Nodo* raiz) {
    if (raiz == nullptr) return;
    if (raiz->resetDone) return;

    raiz->visited = false;
    raiz->resetDone = true;

    resetFlags(raiz->hijoIzquierdo);
    resetFlags(raiz->hermanoDerecho);
}

void clearResetFlags(Nodo* raiz) {
  if (raiz == nullptr) return;
  if (!raiz->resetDone) return; 
  
  raiz->resetDone = false;
  clearResetFlags(raiz->hijoIzquierdo);
  clearResetFlags(raiz->hermanoDerecho);
}

void mostrarSucesion(Nodo* raiz) {
  mostrarSucesionAux(raiz);
  resetFlags(raiz);
  clearResetFlags(raiz);
}

Nodo* construirArbol(Nodo** nodos, int count) {
  Nodo* raiz = nullptr;
  for (int i = 0; i < count; i++) {
    Nodo* current = nodos[i];
    if (current->id_father == 0) {
      raiz = current;
    } else {
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
  
  Nodo* buscarPrimerVivoVaronEnSubarbol(Nodo* node) {
    if (node == nullptr) return nullptr;
    if (!node->is_dead && node->gender == 'H') return node;
    Nodo* candidate = buscarPrimerVivoVaronEnSubarbol(node->hijoIzquierdo);
    if (candidate != nullptr) return candidate;
    return buscarPrimerVivoVaronEnSubarbol(node->hermanoDerecho);
  }
  
  Nodo* buscarPrimerVivoMujerEnSubarbol(Nodo* node) {
    if (node == nullptr) return nullptr;
    if (!node->is_dead && node->gender == 'M') return node;
    Nodo* candidate = buscarPrimerVivoMujerEnSubarbol(node->hijoIzquierdo);
    if (candidate != nullptr) return candidate;
    return buscarPrimerVivoMujerEnSubarbol(node->hermanoDerecho);
  }
  
  void validarLider(Nodo*& leader) {
    if (leader->is_dead || leader->age > 70) {
        std::cout << "El lider actual (" << leader->name << " " << leader->last_name 
                  << ", edad " << leader->age << ") no cumple las condiciones para ser lider." << std::endl;
        Nodo* nuevoLider = asignarNuevoLider(leader);
        if (nuevoLider != nullptr && nuevoLider != leader) {
            leader->is_chief = false;
            nuevoLider->is_chief = true;
            nuevoLider->was_chief = true;
            leader = nuevoLider;
            std::cout << "El liderazgo se ha reasignado a: " << leader->name 
                      << " " << leader->last_name << " (edad " << leader->age << ")." << std::endl;
        } else if (nuevoLider == nullptr) {
            std::cout << "No se encontro un candidato adecuado para el liderazgo." << std::endl;
        }
    }
  }

  Nodo* asignarNuevoLider(Nodo* leader) {
    if (leader->age > 70) {
      leader->is_dead = true;
    }
    
    Nodo* candidato = nullptr;
    
    if (leader->hijoIzquierdo != nullptr) {
      candidato = buscarPrimerVivoVaronEnSubarbol(leader->hijoIzquierdo);
      if (candidato != nullptr) {
        return candidato;
      }
    }
    
    if (leader->padre != nullptr) {
      Nodo* sibling = leader->padre->hijoIzquierdo;
      while (sibling != nullptr) {
        if (sibling != leader && !sibling->is_dead && sibling->gender == 'H') {
          return sibling;
        }
        if (sibling != leader && !sibling->is_dead) {
          candidato = buscarPrimerVivoVaronEnSubarbol(sibling->hijoIzquierdo);
          if (candidato != nullptr) {
            return candidato;
          }
        }
        sibling = sibling->hermanoDerecho;
      }
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
      
      if (leader->age > 70) {
        return nullptr; 
      }

      return leader;
    }
    
    void liberarArbol(Nodo* raiz) {
    if (raiz == nullptr) return;
    Contribuidor* contrib = raiz->contribuyentes;
    while(contrib != nullptr) {
      Contribuidor* temp = contrib;
      contrib = contrib->siguiente;
      delete temp;
    }
    Nodo* child = raiz->hijoIzquierdo;
    while(child != nullptr) {
      Nodo* nextSibling = child->hermanoDerecho;
      liberarArbol(child);
      child = nextSibling;
    }
    delete raiz;
}
