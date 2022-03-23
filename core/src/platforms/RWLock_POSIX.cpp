/*
	RWLock_POSIX.cpp -
*/


#include "RWLock_POSIX.h"


namespace Poco {

RWLockImpl::RWLockImpl() {
	if (pthread_rwlock_init(&_rwl, NULL)) {
		//throw SystemException("cannot create reader/writer lock");
		// TODO: Handle error.
	}
}


RWLockImpl::~RWLockImpl() {
	pthread_rwlock_destroy(&_rwl);
}

} // namespace Poco
