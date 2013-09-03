#ifndef _LIST_H_
#define _LIST_H_

class List {
public:
	List();
	virtual ~List();
	unsigned int size() const;
protected:
	unsigned int length;
};

#endif