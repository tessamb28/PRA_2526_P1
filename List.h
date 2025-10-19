#ifndef LIST_H
#define LIST_H
#include <stdexcept>
template <typename T>
class List{
	public:
		virtual ~List() =default; //destructor virtual
		//inserta un elemento e en la posicion por
		virtual void insert(int pos, T e) =0;
		//inserta e al final de la lista
		virtual void append(T e)=0;
		//inserta e al principio de la lista
		virtual void prepend(T e)=0;
		//devuelve el elemento en la posicion por (sin borrarlo)
		virtual T get(int pos)=0;
		//busca e y devuelve su posicion
		virtual int search(T e)=0;
		//devuelve true si la lista esta vacia
		virtual bool empty()=0;
		//devuelve el numero de elementos de la lista
		virtual int size()=0;
};
#endif

