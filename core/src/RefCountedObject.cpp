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


//
// inlines
//
inline int RefCountedObject::referenceCount() const {
	return _counter.value();
}


inline void RefCountedObject::duplicate() const {
	++_counter;
}


inline void RefCountedObject::release() const noexcept {
	//try 	{
		if (--_counter == 0) delete this;
	/*}
	catch (...) {
		poco_unexpected();
	}*/
}


} // namespace Poco
