/*
	MemoryStream.cpp - 
*/


#include "MemoryStream.h"


namespace Poco {


MemoryIOS::MemoryIOS(char* pBuffer, std::streamsize bufferSize):
	_buf(pBuffer, bufferSize)
{
	poco_ios_init(&_buf);
}


MemoryIOS::~MemoryIOS()
{
}


MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize): 
	MemoryIOS(const_cast<char*>(pBuffer), bufferSize), 
	std::istream(&_buf)
{
}


MemoryInputStream::~MemoryInputStream()
{
}


MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferSize): 
	MemoryIOS(pBuffer, bufferSize), 
	std::ostream(&_buf)
{
}


MemoryOutputStream::~MemoryOutputStream()
{
}


} // namespace Poco
