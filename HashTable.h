#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

using namespace std;

// Clase genérica HashTable que implementa la interfaz Dict
// Toma como parámetros el tipo de valor (V) que se almacenará

template <typename V>
class HashTable : public Dict<V> {

private:
    int n; // Número actual de elementos en la tabla
    int max; // Capacidad máxima de la tabla
    ListLinked<TableEntry<V>>* table; // Array de listas enlazadas para manejar colisiones

    // Función hash que convierte una clave (string) en un índice
    int h(string key) {
        int res = 0;
        int size = key.length();

        // Suma los valores ASCII de los caracteres de la clave
        for (int i = 0; i < size; i++) {
            res += int(key.at(i));
        }

        // Devuelve el índice dentro de los límites de la tabla
        return res % max;
    }

public:
    // Constructor: inicializa la tabla hash con un tamaño dado
    HashTable(int size) {
        table = new ListLinked<TableEntry<V>>[size];
        max = size;
        n = 0;  // Inicialmente no hay elementos
    }

    // Destructor: libera la memoria asignada al array de listas enlazadas
    ~HashTable() {
        delete[] table;
    }

    // Devuelve la capacidad máxima de la tabla
    int capacity() {
        return max;
    }

    // Sobrecarga del operador << para imprimir el estado de la tabla
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
        out << "==============" << endl << endl;

        // Itera por cada cubeta
        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==" << endl << endl;
            out << "List => ";

            // Imprime los elementos de la lista enlazada en la cubeta
            for (int j = 0; j < th.table[i].size(); j++) {
                out << "[" << th.table[i][j].key << ":" << th.table[i][j].value << "] ";
            }

            out << endl << endl;
        }

        out << "==============" << endl << endl;
        return out;
    }

    // Sobrecarga del operador [] para buscar valores por clave
    V operator[](string key) {
        return search(key);
    }

    // Inserta un nuevo par clave-valor en la tabla
    void insert(string key, V value) override {
        int pos = h(key); // Calcula la posición usando la función hash

        // Verifica si la clave ya existe en la cubeta
        for (int i = 0; i < table[pos].size(); i++) {
            if (table[pos][i].key == key) {
                throw runtime_error("Key already exists!");
            }
        }

        // Crea una nueva entrada y la agrega a la lista enlazada
        TableEntry<V> newEntry(key, value);
        table[pos].append(newEntry);
        n++; // Incrementa el número de elementos
    }

    // Busca un valor asociado a una clave
    V search(string key) override {
        int pos = h(key); // Calcula la posición usando la función hash

        // Recorre la lista enlazada en la cubeta correspondiente
        for (int i = 0; i < table[pos].size(); i++) {
            if (table[pos][i].key == key) {
                return table[pos][i].value; // Devuelve el valor asociado
            }
        }

        // Si no se encuentra la clave, lanza una excepción
        throw runtime_error("Key not found!");
    }

    // Elimina una entrada por clave y devuelve su valor
    V remove(string key) override {
        int pos = h(key); // Calcula la posición usando la función hash

        // Busca la clave en la lista enlazada
        for (int i = 0; i < table[pos].size(); i++) {
            if (table[pos][i].key == key) {
                // Elimina la entrada y devuelve su valor
                V returnValue = table[pos].remove(i).value;
                n--; // Decrementa el número de elementos
                return returnValue;
            }
        }

        // Si no se encuentra la clave, lanza una excepción
        throw runtime_error("Key not found!");
    }

    // Devuelve el número de entradas en la tabla
    int entries() override {
        return n;
    }
};

#endif

