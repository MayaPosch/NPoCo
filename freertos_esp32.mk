
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
					-DPOCO_UTIL_NO_JSONCONFIGURATION -DPOCO_THREAD_STACK_SIZE=10240
#STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -fPIE  -fno-strict-aliasing
STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -ffunction-sections -fdata-sections -fpic -funwind-tables -fstack-protector -fno-strict-aliasing -fno-omit-frame-pointer
STD_CFLAGS = $(STD_FLAGS)
# Use gnu++14 rather than c++14 because we need the VA_ARGS GNU extensions in FreeRTOS (portmacro.h).
STD_CXXFLAGS = -std=gnu++14 $(STD_FLAGS) 
#-fno-rtti -fno-exception
STD_LDFLAGS = 
STD_INCLUDE = -I. -I$(ESP_TOOLCHAIN)/../../framework-espidf/components/lwip/lwip/src/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/lwip/port/esp32/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/newlib/platform_include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/esp_system/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/esp_common/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/freertos/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/freertos/include/esp_additions/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/freertos/include/esp_additions/freertos/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/freertos/port/xtensa/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/xtensa/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/xtensa/esp32/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/esp_rom/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/soc/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/soc/esp32/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/esp_hw_support/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/hal/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/hal/esp32/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/esp_timer/include/ \
				-I$(ESP_TOOLCHAIN)/../../framework-espidf/components/heap/include/ \
				-Isrc/platforms/esp32/
STD_LIBDIRS = $(STD_LDFLAGS)
#STD_LIBS = -lssl -lcrypto
