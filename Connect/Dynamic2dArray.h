#ifndef _DYNAMIC2DARRAY_H_
#define _DYNAMIC2DARRAY_H_

#include <iostream>

template <class T>
class Dynamic2dArray {
public:
	Dynamic2dArray();
	void create(unsigned int columns, unsigned int rows);
	void clear();
	T& operator()(unsigned int x, unsigned int y) {
		return Array[y][x];
	}
	int maxRows() const {
		return rowCount;
	}
	int maxColumns() const {
		return columnCount;
	}
	template <class T>
	friend std::ostream& operator<<(std::ostream& os, Dynamic2dArray& arr);
private:
	T** Array;
	int columnCount, rowCount;
};



template <class T>
Dynamic2dArray<T>::Dynamic2dArray() : columnCount(0), rowCount(0) {

}

template <class T>
void Dynamic2dArray<T>::create(unsigned int columns, unsigned int rows) {
	columnCount = columns;
	rowCount = rows;
	Array = new T*[rows];
	for (unsigned int i = 0; i < rows; i++) {
		Array[i] = new T[columns];
	}
}

template <class T>
void Dynamic2dArray<T>::clear() {
	for(int i = 0; i < rowCount; ++i) {
		delete [] Array[i];
	}
	delete [] Array;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Dynamic2dArray<T>& arr) {
	os << "\n";
	for (int y = 0; y < arr.maxRows(); y++) {
		for (int x = 0; x < arr.maxColumns(); x++) {
			os << arr.at(x, y) << " | ";
		}
		os << "\n";
	}
	return os;
}

#endif