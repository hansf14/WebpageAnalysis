#ifndef ELEMENT_H
#define ELEMENT_H

//Element Class
//1.For generic usage in other data stures and get away with structural dependency
//2.In order to cope with possible change in the future
template <typename T>
class Element
{
public:
	T data;

public:
	Element() : data(){}
	Element(T const& srcData) : data(srcData){}
	Element(Element<T> const& other) : data(other.data){}
	~Element(){}

	void set(T const& srcData){ data = srcData; }
	T const get() const { return data; }

	Element<T> const& operator =(Element<T> const& other){ data = other.data; return *this; }
	T const& operator =(T const& srcData){ data = srcData; return data; }
};

#endif