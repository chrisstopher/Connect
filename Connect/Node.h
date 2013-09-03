#ifndef _NODE_H_
#define _NODE_H_

#include <cstdlib> //for NULL

template<class T>
class Node {
public:
	typedef T value_type;
	typedef T& reference_type;
	typedef T const& const_reference_type;
	typedef T* pointer_type;
	typedef T const* const_pointer_type;

	Node(value_type obj, Node* nxt = NULL);
	Node* getNext() const;
	value_type getObject() const;
	void setNext(Node* nxt);
private:
	value_type object;
	Node* next;
};

template<class T>
Node<T>::Node(value_type obj, Node* nxt) : object(obj), next(nxt) {

};

template<class T>
Node<T>* Node<T>::getNext() const {
	return next;
}

template<class T>
typename Node<T>::value_type Node<T>::getObject() const {
	return object;
}

template<class T>
void Node<T>::setNext(Node* nxt) {
	next = nxt;
}

#endif