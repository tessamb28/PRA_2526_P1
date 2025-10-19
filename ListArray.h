#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T*  arr;                 // array contiguo
    int max;                 // capacidad actual
    int n;                   // nº de elementos
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;
        T* nuevo = new T[new_size];
        // copiamos lo que quepa
        int to_copy = (n < new_size) ? n : new_size;
        for (int i = 0; i < to_copy; ++i) nuevo[i] = arr[i];
        delete[] arr;
        arr = nuevo;
        max = new_size;
        if (n > max) n = max;  // por seguridad si reducimos
    }

    // Comprobaciones de rango
    void check_get_remove(int pos) const {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
    }
    void check_insert(int pos) const {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida!");
    }

public:
    // ctor / dtor
    ListArray() : arr(nullptr), max(0), n(0) {
        resize(MINSIZE);
    }
    ~ListArray() override {
        delete[] arr;
    }

    // ---- Métodos de List<T> ----
    void insert(int pos, T e) override {
        check_insert(pos);
        if (n == max) resize(max * 2);            // crecer
        // desplazar a la derecha [pos..n-1]
        for (int i = n; i > pos; --i) arr[i] = arr[i - 1];
        arr[pos] = e;
        ++n;
    }

    void append(T e) override { insert(n, e); }   // al final
    void prepend(T e) override { insert(0, e); }  // al principio

    T remove(int pos) override {
        check_get_remove(pos);
        T out = arr[pos];                         // guardar valor
        // desplazar a la izquierda [pos+1..n-1]
        for (int i = pos; i < n - 1; ++i) arr[i] = arr[i + 1];
        --n;
        // encoger si está muy vacío
        if (n <= max / 4 && max > MINSIZE) resize(max / 2);
        return out;
    }

    T get(int pos) override {
        check_get_remove(pos);
        return arr[pos];                          // por valor (como pide el enunciado)
    }

    int search(T e) override {
        for (int i = 0; i < n; ++i)
            if (arr[i] == e) return i;
        return -1;
    }

    bool empty() override { return n == 0; }
    int size() override { return n; }

    // ---- Extras pedidos ----
    T operator[](int pos) {
        check_get_remove(pos);
        return arr[pos];                          // mismo contrato que get()
    }

    // impresión: formato simple tipo lista
    friend std::ostream& operator<<(std::ostream& out, const ListArray<T>& list) {
        out << "List => [\n";
        for (int i = 0; i < list.n; ++i) {
            out << "  " << list.arr[i] << (i + 1 == list.n ? "" : "") << "\n";
        }
        out << "]\n";
        out << "size(): " << list.n << "\n";
        out << "empty(): " << (list.n == 0 ? "true" : "false") << "\n";
        return out;
    }
};

#endif // LISTARRAY_H

