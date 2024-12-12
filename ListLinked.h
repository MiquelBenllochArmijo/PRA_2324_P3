#include <ostream>
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {
private:  
    int n;
    Node<T> *first; 

public:
    // Constructor
    ListLinked() {
        n = 0;
        first = nullptr;
    }

    // Destructor
    ~ListLinked() {
        for (int i = 0; i < n; i++) {
            Node<T> *aux = first->next;
            delete first;
            first = aux;
        }
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos >= 0 && pos < n) { 
            Node<T> *aux = first;
            for (int i = 0; i < pos; i++) 
                aux = aux->next;
            return aux->data;
        } else { 
            throw out_of_range("Posición no válida del array\n");
        }
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        Node<T> *aux = list.first;
        for (int i = 0; i < list.n; i++) {
            out << aux->data << " ";
            aux = aux->next; 
        }
        return out;
    }

    // Insertar en una posición específica
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw out_of_range("Posición no válida del array\n");
        }

        if (pos == 0) { 
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            int i = 0;

            while (prev != nullptr && i < pos - 1) {
                prev = prev->next;
                i++;
            }

            if (prev != nullptr) {
                prev->next = new Node<T>(e, prev->next);
            }
        }
        n++;
    }

    // Agregar al final de la lista
    void append(T e) override {
        insert(n, e);
    }

    // Agregar al inicio de la lista
    void prepend(T e) override {
        insert(0, e);
    }

    // Eliminar elemento en una posición específica
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición no válida del array\n");
        } else {
            T x;
            if (pos == 0) {
                Node<T>* aux = first;
                x = aux->data;
                first = first->next;
                delete aux;
            } else {
                Node<T>* aux = first->next;
                Node<T>* prev = first;

                for (int i = 1; i < pos; i++) {
                    aux = aux->next;
                    prev = prev->next;
                }

                x = aux->data;
                prev->next = aux->next;
                delete aux;
            }
            n--;
            return x;
        }
    }

    // Obtener elemento en una posición específica
    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición no válida del array\n");
        } else {
            Node<T>* aux = first; 
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data; 
        }  
    }

    // Buscar un elemento y devolver su posición
    int search(T e) override {
        Node<T>* aux = first; 
        int i = 0;

        while (aux != nullptr && aux->data != e) { 
            aux = aux->next;
            i++;
        }

        if (aux != nullptr) 
            return i;
        else 
            return -1;
    }

    // Comprobar si la lista está vacía
    bool empty() override {
        return n == 0;
    }

    // Devolver el tamaño de la lista
    int size() override {
        return n;
    }

    T* arr() override {
    // Implementación del método.
    return nullptr; // Ejemplo: Devuelve un puntero válido.
}

};

