#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

    void check_get_remove(int pos) const {
        if (pos < 0 || pos >= n) throw std::out_of_range("posición inválida!!!!");
    }
    void check_insert(int pos) const {
        if (pos < 0 || pos > n) throw std::out_of_range("posicion inválida!!!!");
    }
    Node<T>* node_at(int pos) const {
        check_get_remove(pos);
        Node<T>* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur;
    }

public:
    ListLinked() : first(nullptr), n(0) {}
    ~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
        n = 0;
    }

    void insert(int pos, T e) override {
        check_insert(pos);
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = node_at(pos - 1);
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }

    void append(T e) override { insert(n, e); }
    void prepend(T e) override { insert(0, e); }

    T remove(int pos) override {
        check_get_remove(pos);
        T out;
        if (pos == 0) {
            Node<T>* del = first;
            out = del->data;
            first = del->next;
            delete del;
        } else {
            Node<T>* prev = node_at(pos - 1);
            Node<T>* del = prev->next;
            out = del->data;
            prev->next = del->next;
            delete del;
        }
        --n;
        return out;
    }

    T get(int pos) override { return node_at(pos)->data; }
    int search(T e) override {
        Node<T>* cur = first; int i = 0;
        while (cur) { if (cur->data == e) return i; cur = cur->next; ++i; }
        return -1;
    }
    bool empty() override { return n == 0; }
    int  size()  override { return n; }

    T operator[](int pos) { return get(pos); }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [\n";
        Node<T>* cur = list.first;
        while (cur) { out << "  " << cur->data << "\n"; cur = cur->next; }
        out << "]\n";
        out << "size(): " << list.n << "\n";
        out << "empty(): " << (list.n == 0 ? "true" : "false") << "\n";
        return out;
    }
};

#endif 

