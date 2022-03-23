ifndef NDK_HOME
$(error NDK_HOME parameter not set.)
endif

TARGET_OS = android
TARGET_ARCH = aarch64

ifndef ANDROID_ABI_LEVEL
ANDROID_ABI_LEVEL := 24
endif

ifdef OS
TOOLCHAIN_POSTFIX := .cmd
endif

export CC = aarch64-linux-android$(ANDROID_ABI_LEVEL)-clang$(TOOLCHAIN_POSTFIX)
export CXX = aarch64-linux-android$(ANDROID_ABI_LEVEL)-clang++$(TOOLCHAIN_POSTFIX)
export CPP = aarch64-linux-android-cpp
export AR = aarch64-linux-android-ar
export LD = aarch64-linux-android-ld
export STRIP = aarch64-linux-android-strip
export OBJCOPY = aarch64-linux-android-objcopy

SYSROOT := --sysroot=$(NDK_HOME)/sysroot -I$(NDK_HOME)/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1 \
				--gcc-toolchain=$(NDK_HOME)/toolchains/aarch64-linux-android-4.9


PLATFORM_FLAGS = $(SYSROOT) -DPOCO_ANDROID -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING \
					-DPOCO_NO_SHAREDMEMORY -D_DEBUG -DPOCO_UTIL_NO_XMLCONFIGURATION \
					-DPOCO_UTIL_NO_JSONCONFIGURATION
#STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -fPIE  -fno-strict-aliasing
STD_FLAGS = $(PLATFORM_FLAGS) -Og -g3 -Wall -ffunction-sections -fdata-sections -fpic -ffunction-sections -funwind-tables -fstack-protector -fno-strict-aliasing -fno-omit-frame-pointer
STD_CFLAGS = $(STD_FLAGS)
STD_CXXFLAGS = -std=c++14 -stdlib=libc++ $(STD_FLAGS) -frtti -fexceptions
STD_LDFLAGS = -L $(NDK_HOME)/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/lib/aarch64-linux-android/$(ANDROID_ABI_LEVEL)
STD_INCLUDE = -I.
STD_LIBDIRS = $(STD_LDFLAGS)
STD_LIBS = -lssl -lcrypto
