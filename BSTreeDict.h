#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

// Clase que implementa un diccionario basado en un árbol binario de búsqueda (BST)
template <typename V>
class BSTreeDict: public Dict<V> {

    // Puntero al árbol binario de búsqueda que almacena las entradas del diccionario
    private:
        BSTree<TableEntry<V>>* tree;

    public:
        // Constructor: inicializa el árbol vacío
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>;  // Crea un nuevo árbol binario de búsqueda
        }

        // Destructor: libera la memoria del árbol
        ~BSTreeDict(){
            delete tree;  // Elimina el árbol binario de búsqueda
        }

        // Inserta una entrada en el diccionario (como un par clave-valor)
        void insert(string key, V value) override { 
            // Crea una nueva entrada con la clave y el valor proporcionado
            TableEntry<V> *t = new TableEntry<V>(key, value); 
            // Inserta la entrada en el árbol
            tree->insert(*t); 
            delete t;  // Elimina la entrada después de insertarla (ya está en el árbol)
        }

        // Busca un valor por su clave en el árbol
        V search(string key) override { 
            // Llama a la búsqueda en el árbol y devuelve el valor asociado a la clave
            return (tree->search(key)).value; 
        }

        // Elimina una entrada por su clave y devuelve el valor asociado
        V remove(string key) override {
            // Obtiene el valor antes de eliminar la entrada
            V val = (tree->search(key)).value;
            // Elimina la entrada del árbol
            tree->remove(key); 
            return val;  // Devuelve el valor eliminado
        }

        // Devuelve la cantidad de entradas en el diccionario
        int entries() override { 
            return tree->size();  // Llama a la función size() del árbol para obtener el número de entradas
        }

        // Sobrecarga del operador de salida para imprimir el árbol en formato de flujo
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
            out << *bs.tree;  // Imprime el árbol utilizando la sobrecarga de operador de salida del árbol
            return out;  // Devuelve el flujo de salida
        }

        // Sobrecarga del operador [] para buscar una clave en el diccionario
        V operator[](std::string key){
            return search(key);  // Llama a la función search() para obtener el valor asociado a la clave
        }
};

#endif

