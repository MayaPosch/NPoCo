ifndef TARGET
$(error TARGET parameter not provided.)
endif

include ../../$(TARGET).mk

LIBS := -L$(TOP)/build/$(TARGET)/npoco/lib -lNPocoCore


all: cv

cv:
	$(CXX) -o condition_variable_test npoco_core_condition_test.cpp $(LIBS)
