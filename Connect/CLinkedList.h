#ifndef _CLINKEDLIST_H_
#define _CLINKEDLIST_H_

#include "List.h"
#include "Node.h"
#include <iostream>

template<class T>
class CLinkedList : public List {
	typedef Node<T> node_type;
	typedef node_type* node_pointer;
public:
	typedef typename node_type::value_type value_type;
	typedef typename node_type::reference_type reference_type;
	typedef typename node_type::const_reference_type const_reference_type;
	typedef typename node_type::pointer_type pointer_type;
	typedef typename node_type::const_pointer_type const_pointer_type;

	CLinkedList();
	CLinkedList(const CLinkedList& list);
	CLinkedList& operator=(const CLinkedList& list);
	virtual ~CLinkedList();
	node_pointer getHead() const;
	void push_back(const_reference_type object);
	void clear();
private:
	node_pointer head;
};

template<class T>
CLinkedList<T>::CLinkedList() : head(NULL) {
	
}

template<class T>
CLinkedList<T>::CLinkedList(const CLinkedList& list) : head(NULL){
	if (!list.getHead()) {
		return;
	}
	node_pointer temp = list.getHead();
	do {
		push_back(temp->getObject());
		temp = temp->getNext();
	} while (temp != list.getHead());
}

template<class T>
CLinkedList<T>& CLinkedList<T>::operator=(const CLinkedList& list) {
	if (*this != list) {
		clear();
		*this = CLinkedList(list);
	}
	return *this;
}

template<class T>
CLinkedList<T>::~CLinkedList() {
	clear();
	if (head) {
		delete head;
	}
	head = NULL;
}

template<class T>
typename CLinkedList<T>::node_pointer CLinkedList<T>::getHead() const {
	return head;
}

/*
If there is no head you cannot do head = new node_type(object, head);
because the head you pass in is NULL and this is a circular linked list
So you have to set the next node after the head is initiallized

If there is a head then loop loop and append at the back
*/
template<class T>
void CLinkedList<T>::push_back(const_reference_type object) {
	if (!head) {
		head = new node_type(object);
		head->setNext(head);
		//std::cout << "created " << head << " " << head->getNext() << "\n";
	} else {
		/*node_pointer temp = head;
		std::cout << temp << " = " << head << "\n";
		while (temp->getNext() != head) {
			std::cout << temp->getNext() << " != " << head << "\n";
			temp = temp->getNext();
		}
		std::cout << temp->getNext() << " = " << head << "\n";*/
		node_pointer temp = head;
		for ( ; temp->getNext() != head; temp = temp->getNext());
		temp->setNext(new node_type(object, temp->getNext()));
		//std::cout << temp->getNext() << " != " << head << "\n";
	}
	length++;
}


/*
Example of deleting a list: 
head -> 1 -> 2 -> 3 -|
  ^------------------+
temp = head.next      (temp = 1)
head.next = temp.next (head = 2)
delete temp

head -> 2 -> 3 -|
  ^-------------+

temp = head.next      (temp = 2)
head.next = temp.next (head = 3)
delete temp

head -> 3 -|
  ^--------+

temp = head.next      (temp = 3)
head.next = temp.next (head = Head)
delete temp

head -|
  ^---+

head = head so that stops the loop

Then deletes the head
*/

template<class T>
void CLinkedList<T>::clear() {
	if (!head) {
		return;
	}
	node_pointer temp = NULL;
	while (head->getNext() != head) {
		temp = head->getNext();
		head->setNext(temp->getNext());
		delete temp;
	}
	delete head;
	head = NULL;
	length = 0;
}

#endif