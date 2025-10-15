#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <iostream>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size);

public:
    ListArray();
    ~ListArray();

    void insert(int pos, T e) override;
    void append(T e) override;
    void prepend(T e) override;
    T remove(int pos) override;
    T get(int pos) const override;
    int search(T e) const override;
    bool empty() const override;
    int size() const override;

    T operator[](int pos);
    template <typename U>
    friend std::ostream& operator<<(std::ostream &out, const ListArray<U> &list);
};

// Constructor
template <typename T>
ListArray<T>::ListArray() {
    arr = new T[MINSIZE];
    max = MINSIZE;
    n = 0;
}

// Destructor
template <typename T>
ListArray<T>::~ListArray() {
    delete[] arr;
}

// Redimensionar array
template <typename T>
void ListArray<T>::resize(int new_size) {
    T* nuevo = new T[new_size]; // crear un array de manera dinemica 
    for (int i = 0; i < n; i++) {
        nuevo[i] = arr[i];
    }
    delete[] arr;
    arr = nuevo;
    max = new_size;
}

// Insertar elemento en posición
template <typename T>
void ListArray<T>::insert(int pos, T e) {
    if (pos < 0 || pos > n) {
        throw std::out_of_range("Posición inválida");
    }
    if (n == max) {
        resize(max * 2);
    }
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = e;
    n++;
}

// Añadir al final
template <typename T>
void ListArray<T>::append(T e) {
    insert(n, e);
}

// Añadir al principio
template <typename T>
void ListArray<T>::prepend(T e) {
    insert(0, e);
}

// Eliminar elemento
template <typename T>
T ListArray<T>::remove(int pos) {
    if (pos < 0 || pos >= n) {
        throw std::out_of_range("Posición inválida");
    }
    T eliminado = arr[pos];
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
    if (n < max / 4 && max > MINSIZE) {
        resize(max / 2);
    }
    return eliminado;
}

// Obtener elemento
template <typename T>
T ListArray<T>::get(int pos) const {
    if (pos < 0 || pos >= n) {
        throw std::out_of_range("Posición inválida");
    }
    return arr[pos];
}

// Buscar elemento
template <typename T>
int ListArray<T>::search(T e) const {
    for (int i = 0; i < n; i++) {
        if (arr[i] == e) return i;
    }
    return -1;
}

// ¿Está vacía?
template <typename T>
bool ListArray<T>::empty() const {
    return n == 0;
}

// Tamaño actual
template <typename T>
int ListArray<T>::size() const {
    return n;
}

// Operador []
template <typename T>
T ListArray<T>::operator[](int pos) {
    if (pos < 0 || pos >= n) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return arr[pos];
}

// Operador <<
template <typename T>
std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
    out << "[";
    for (int i = 0; i < list.n; i++) {
        out << list.arr[i];
        if (i < list.n - 1) out << ", ";
    }
    out << "]";
    return out;
}

#endif


