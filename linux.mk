TARGET_OS = linux
TARGET_ARCH = x86

export CC = gcc
export CXX = g++
export CPP = cpp
export AR = ar
export LD = g++
export STRIP = strip
export OBJCOPY = objcopy

PLATFORM_FLAGS = 
STD_FLAGS = $(PLATFORM_FLAGS) -fPIC -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections
STD_CFLAGS = $(STD_FLAGS)
STD_CXXFLAGS = -std=c++11 $(STD_FLAGS)
STD_LDFLAGS = -L.
STD_INCLUDE = -I.
STD_LIBDIRS = $(STD_LDFLAGS)
STD_LIBS = -lssl -lcrypto
