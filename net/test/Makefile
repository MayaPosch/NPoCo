ifndef TARGET
$(error TARGET parameter not provided.)
endif

include ../../$(TARGET).mk

LIBS := -L../../build/$(TARGET)/npoco/lib -lNPocoNet -lNPocoCore
INCLUDES := -I../../build/$(TARGET)/npoco/include


all: udp

udp:
	$(CXX) -o udp_server_test udp_server_test.cpp $(INCLUDES) $(LIBS) $(STD_LIBS)
