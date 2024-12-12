#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

// Clase BSTree: Implementación de un Árbol Binario de Búsqueda (Binary Search Tree)
template <typename T> 
class BSTree {
    private:
        int nelem;          // Número de elementos en el árbol
        BSNode<T> *root;    // Raíz del árbol

        /**
         * Busca un elemento en el árbol recursivamente.
         * @param n Nodo actual.
         * @param e Elemento a buscar.
         * @return Puntero al nodo que contiene el elemento.
         * @throws runtime_error Si el elemento no se encuentra.
         */
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw runtime_error("Element not found!");
            } else if (n->elem < e) {
                return search(n->right, e);  // Buscar en el subárbol derecho
            } else if (n->elem > e) {
                return search(n->left, e);   // Buscar en el subárbol izquierdo
            } else {
                return n;  // Nodo encontrado
            }
        }

        /**
         * Inserta un elemento en el árbol recursivamente.
         * @param n Nodo actual.
         * @param e Elemento a insertar.
         * @return Puntero al nodo actualizado.
         * @throws runtime_error Si el elemento ya existe.
         */
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                return new BSNode(e);  // Insertar el elemento en un nodo nuevo
            } else if (n->elem == e) {
                throw runtime_error("Duplicated element!");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);  // Insertar en el subárbol derecho
            } else {
                n->left = insert(n->left, e);    // Insertar en el subárbol izquierdo
            }
            return n;
        }

        /**
         * Realiza un recorrido inorden y lo imprime.
         * @param out Stream de salida.
         * @param n Nodo actual.
         */
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);  // Recorrer subárbol izquierdo
                out << n->elem << " ";       // Imprimir el elemento actual
                print_inorder(out, n->right); // Recorrer subárbol derecho
            }
        }

        /**
         * Elimina un elemento del árbol recursivamente.
         * @param n Nodo actual.
         * @param e Elemento a eliminar.
         * @return Puntero al nodo actualizado.
         * @throws runtime_error Si el elemento no se encuentra.
         */
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw runtime_error("Element not found!");
            } else if (n->elem < e) {
                n->right = remove(n->right, e);  // Buscar en el subárbol derecho
            } else if (n->elem > e) {
                n->left = remove(n->left, e);    // Buscar en el subárbol izquierdo
            } else {
                // Nodo encontrado
                if (n->left != nullptr && n->right != nullptr) {  // Caso: 2 hijos
                    n->elem = max(n->left);                      // Reemplazar con el máximo del subárbol izquierdo
                    n->left = remove_max(n->left);               // Eliminar el nodo que contiene ese máximo
                } else {  // Caso: 1 hijo o ninguno
                    n = (n->left != nullptr) ? n->left : n->right;  // Reemplazar el nodo por su hijo o nullptr
                }
            }
            return n;
        }

        /**
         * Encuentra el valor máximo en un subárbol.
         * @param n Nodo actual.
         * @return El valor máximo.
         * @throws runtime_error Si el subárbol está vacío.
         */
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw runtime_error("Subtree is empty!");
            } else if (n->right != nullptr) {
                return max(n->right);  // Continuar buscando hacia la derecha
            } else {
                return n->elem;  // Nodo más a la derecha, es el máximo
            }
        }

        /**
         * Elimina el nodo que contiene el valor máximo en un subárbol.
         * @param n Nodo actual.
         * @return Puntero al nodo actualizado.
         */
        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                return n->left;  // Reemplazar el nodo actual por su hijo izquierdo
            } else {
                n->right = remove_max(n->right);  // Continuar eliminando en el subárbol derecho
                return n;  // Retornar el nodo actual tras actualizar el subárbol derecho
            }
        }

        /**
         * Elimina todos los nodos del árbol recursivamente.
         * @param n Nodo actual.
         */
        void delete_cascade(BSNode<T>* n) {
            if (n == nullptr) return;  // Caso base: nodo vacío
            delete_cascade(n->left);  // Eliminar subárbol izquierdo
            delete_cascade(n->right); // Eliminar subárbol derecho
            delete n;                  // Eliminar el nodo actual
        }

    public:
        /**
         * Constructor: Crea un árbol vacío.
         */
        BSTree() {
            nelem = 0;
            root = nullptr;
        }

        /**
         * Retorna el número de elementos en el árbol.
         */
        int size() const {
            return nelem;
        }

        /**
         * Busca un elemento en el árbol.
         * @param e Elemento a buscar.
         * @return El elemento encontrado.
         */
        T search(T e) const {
            return search(root, e)->elem;
        }

        /**
         * Sobrecarga del operador [].
         * @param e Elemento a buscar.
         * @return El elemento encontrado.
         */
        T operator[](T e) const {
            return search(e);
        }

        /**
         * Inserta un elemento en el árbol.
         * @param e Elemento a insertar.
         */
        void insert(T e) {
            root = insert(root, e);
            nelem++;
        }

        /**
         * Imprime el árbol en inorden.
         */
        friend std::ostream& operator<<(std::ostream &out, BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }

        /**
         * Elimina un elemento del árbol.
         * @param e Elemento a eliminar.
         */
        void remove(T e) {
            root = remove(root, e);
            nelem--;
        }

        /**
         * Destructor: Elimina todos los nodos del árbol.
         */
        ~BSTree() {
            delete_cascade(root);
        }
};

#endif

