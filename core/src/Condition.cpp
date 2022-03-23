/*
	Condition.cpp - 
*/


#include "Condition.h"


namespace Poco {


Condition::Condition() { }

Condition::~Condition() { }


void Condition::signal() {
	FastMutex::ScopedLock lock(_mutex);
	if (!_waitQueue.empty()) {
		_waitQueue.front()->set();
		dequeue();
	}
}


void Condition::broadcast() {
	FastMutex::ScopedLock lock(_mutex);	
	for (auto p: _waitQueue) {
		p->set();
	}
	
	_waitQueue.clear();
}


void Condition::enqueue(Event& event) {
	_waitQueue.push_back(&event);
}


void Condition::dequeue() {
	_waitQueue.pop_front();
}


void Condition::dequeue(Event& event) {
	for (WaitQueue::iterator it = _waitQueue.begin(); it != _waitQueue.end(); ++it) {
		if (*it == &event) {
			_waitQueue.erase(it);
			break;
		}
	}
}


} // namespace Poco
