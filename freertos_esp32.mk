
TARGET_OS = freertos
TARGET_ARCH = esp32

ifndef ESP_TOOLCHAIN
$(error ESP_TOOLCHAIN parameter not provided.)
endif

TOOL_PREFIX := $(ESP_TOOLCHAIN)/xtensa-esp32-elf-
export CC = $(TOOL_PREFIX)gcc
export CXX =  $(TOOL_PREFIX)g++
export CPP = $(TOOL_PREFIX)cpp
export AR = $(TOOL_PREFIX)ar
export LD = $(TOOL_PREFIX)ld
export STRIP = $(TOOL_PREFIX)strip
export OBJCOPY = $(TOOL_PREFIX)objcopy

#SYSROOT := --sysroot=$(NDK_HOME)/sysroot -I$(NDK_HOME)/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1 \
#				--gcc-toolchain=$(NDK_HOME)/toolchains/aarch64-linux-android-4.9


PLATFORM_FLAGS = $(SYSROOT) -D__FREERTOS__ -D__XTENSA__ -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING \
					-DPOCO_NO_SHAREDMEMORY -DPOCO_UTIL_NO_XMLCONFIGURATION \
					-DPOCO_UTIL_NO_JSONCONFIGURATION
#STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -fPIE  -fno-strict-aliasing
STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -ffunction-sections -fdata-sections -fpic -funwind-tables -fstack-protector -fno-strict-aliasing -fno-omit-frame-pointer
STD_CFLAGS = $(STD_FLAGS)
STD_CXXFLAGS = -std=c++14 $(STD_FLAGS) 
#-fno-rtti -fno-exception
STD_LDFLAGS = 
STD_INCLUDE = -I.
STD_LIBDIRS = $(STD_LDFLAGS)
#STD_LIBS = -lssl -lcrypto
