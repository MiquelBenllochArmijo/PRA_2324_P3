#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

using namespace std;

/**
 * Clase template que representa un nodo en un árbol binario de búsqueda.
 * Cada nodo tiene un elemento genérico (elem) y dos punteros:
 * - left: apunta al nodo hijo izquierdo (valores menores que el nodo actual).
 * - right: apunta al nodo hijo derecho (valores mayores que el nodo actual).
 */
template <typename T> 
class BSNode {
    public:
        T elem;                // Elemento almacenado en el nodo.
        BSNode<T>* left;       // Puntero al hijo izquierdo.
        BSNode<T>* right;      // Puntero al hijo derecho.

        /**
         * Constructor del nodo.
         * @param elem Elemento que se almacenará en el nodo.
         * @param left Puntero al hijo izquierdo (por defecto nullptr).
         * @param right Puntero al hijo derecho (por defecto nullptr).
         */
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr) {
            this->elem = elem;
            this->left = left;
            this->right = right;
        }

        /**
         * Sobrecarga del operador << para imprimir el contenido del nodo.
         * Permite enviar el nodo a un flujo de salida (como std::cout).
         * @param out Referencia al flujo de salida.
         * @param bsn Nodo que se quiere imprimir.
         * @return Referencia al flujo de salida actualizado.
         */
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
            out << bsn.elem; // Imprime el elemento almacenado en el nodo.
            return out;
        }
};

#endif

