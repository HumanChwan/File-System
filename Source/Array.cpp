#include "../Header/Array.h"

// <------Private Methods-------->
// Private Method to copy an array from an Array Class
template<class T>
void Array<T>::copy(T* array_a, const Array<T>& array_b) {
	for (uint32_t i = 0; i < array_b.length(); ++i) {
		array_a[i] = array_b[i];
	}
}

// <------Constructor-------->
template<class T>
Array<T>::Array() {
	m_length = 0;
	m_array = nullptr;
}

// <------Public Methods-------->
// Setter Method to append new element
template<class T>
void Array<T>::append(T element) {
	// non amortized appending
	T* new_array = new T[m_length + 1];
	copy(new_array, *this);
	new_array[m_length] = element;

	m_array = new_array;
}

// Getter Method of the length of the array
template<class T>
size_t Array<T>::length() const {
	return m_length;
}

// Getter Method for getting each index of the array
template<class T>
T Array<T>::operator[](int index) const {
	return m_array[index];
}

// <------Destructor-------->
template<class T>
Array<T>::~Array() {
 delete m_array;
}
