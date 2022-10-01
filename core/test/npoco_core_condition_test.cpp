/*
	npoco_core_condition_test.cpp - integration test for NPoco's condition variable implementation.
	
	Revision 0
	
	Description:
			- Starts two threads, one with a condition variable-based wait.
			- The second thread signals the condition variable after a delay.
			
	Success:
			- Condition variable is triggered, both threads successfully exit.
			
	2022/03/27, Maya Posch
*/


#include "../src/Condition.h"
#include "../src/Thread.h"
#include "../src/Runnable.h"

#include <iostream>


Poco::Condition gcv;
Poco::Mutex gm;


class Thread2 : public Poco::Runnable {
	//
	
public:
	virtual void run() {
		// Wait for 100 ms.
		Poco::Thread::current()->sleep(5000);
		
		// Trigger CV.
		gcv.signal();
	}
};


int main() {
	std::cout << "=================================" << std::endl;
	std::cout << "Starting Condition Variable test..." << std::endl;
	std::cout << "=================================" << std::endl;
	
	// Set up the second thread.
	Poco::Thread t2;
	Thread2 r2;
	t2.start(r2);
	
	// Enter CV-based wait.
	gm.lock();
	gcv.wait(gm);
	gm.unlock();
	
	// Clean up.
	std::cout << "Finished CV test..." << std::endl;
	
	return 0;
}