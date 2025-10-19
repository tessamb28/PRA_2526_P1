#ifndef NODE_H
#define NODE_H
#include <ostream>
template <typename T>
class Node {
	public:
		T data;		//dato almacenado
		Node<T>* next;	//puntero al siguiente
		//constructor: next es nullptr por defecto
		explicit Node(T data, Node<T>* next=nullptr) : data(data), next(next) {}
		//imprime solo el dato
		friend std::ostream& operator <<(std::ostream& out, const Node<T>& node){
			out<<node.data;
			return out;
		}
};
#endif

