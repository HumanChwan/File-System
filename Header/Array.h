#ifndef ARRAY
#define ARRAY


#include <cstdint>
#include <cstddef>

template<class T>
class Array {
private:
	T* m_array;
	int m_length;
private:
	void copy(T* array_a, const Array& array_b);

public:
	Array();

	void append(T element);

	size_t length() const;
	T operator[](int index) const;

	~Array();
};

#endif
