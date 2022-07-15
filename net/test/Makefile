ifndef TARGET
$(error TARGET parameter not provided.)
endif

include ../../$(TARGET).mk

LIBS := -L$(TOP)/build/$(TARGET)/npoco/lib -lNPocoCore -lNPocoNet


all: cv

cv:
	$(CXX) -o stream_socket_test npoco_core_condition_test.cpp $(LIBS)
