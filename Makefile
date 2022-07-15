ifndef TARGET
$(error TARGET parameter not provided.)
endif

export TOP := $(CURDIR)
export TARGET

# Determine whether host OS is Linux or Windows
# Linux returns 'Linux', Windows doesn't have uname, OS X returns 'Darwin'.
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
export HOST = linux
else
export HOST = win32
export FILE_EXT = .exe
endif

# Set proper commandline commands for the detected OS
ifeq ($(HOST), linux)
export MKDIR 	= mkdir -p
export RM		= rm -rf
export CP		= cp -RL
#export LN		= ln -sf
else
# Assuming MSYS shell
export MKDIR 	= mkdir -p
export RM		= rm -rf
export CP		= cp -RL
#export LN		= mklink /d .
endif

include $(TARGET).mk

export TARGET_OS
export TARGET_ARCH
export TOOLCHAIN_NAME

all: foundation net util json

json:
	$(MAKE) -C ./JSON

core:
	$(MAKE) -C ./core

net:
	$(MAKE) -C ./net
	
util:
	$(MAKE) -C ./util
	
test: test-core
	
test-core:
	$(MAKE) -C ./core/test

clean: clean-json clean-core clean-net clean-util

clean-core:
	$(MAKE) -C ./core clean
	
clean-net:
	$(MAKE) -C ./net clean
	
clean-util:
	$(MAKE) -C ./util clean
	
clean-json:
	$(MAKE) -C ./JSON clean

.PHONY: all clean core net util json clean-net clean-foundation clean-json clean-util
