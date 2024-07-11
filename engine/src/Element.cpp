#include "Element.h"

Element const& Element::operator =(Element const& other)
{
	data = other.data;
	return *this;
}