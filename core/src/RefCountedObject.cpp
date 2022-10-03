/*
	RefCountedObject.cpp 
*/


#include "RefCountedObject.h"


namespace Poco {


RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}


int RefCountedObject::referenceCount() const {
	return _counter.value();
}


void RefCountedObject::duplicate() const {
	++_counter;
}


void RefCountedObject::release() const {
	//try 	{
		if (--_counter == 0) delete this;
	/*}
	catch (...) {
		poco_unexpected();
	}*/
}


} // namespace Poco
