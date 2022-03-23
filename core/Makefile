ifndef TARGET
$(error TARGET parameter not provided.)
endif

include ../$(TARGET).mk

OUTPUT = libNPocoCore
VERSION := 0.1

INCLUDE = $(STD_INCLUDE) -Isrc -I$(TOP)/build/$(TARGET)/npoco/include
CFLAGS = $(STD_CFLAGS) $(INCLUDE)
CXXFLAGS := $(STD_CXXFLAGS) $(INCLUDE)
SHARED_FLAGS := -fPIC -shared -Wl,-soname,$(OUTPUT).so.$(VERSION)

OBJROOT := ../build/$(TARGET)/npoco/obj
INCLOUT := $(TOP)/build/$(TARGET)/npoco/include/npoco
HEADERS := $(wildcard src/*.h) \
			$(wildcard src/platforms/*.h)
HTARGET := $(addprefix $(INCLOUT)/,$(notdir $(wildcard src/*.h))) \
			$(addprefix $(INCLOUT)/,$(notdir $(wildcard src/platforms/*.h)))
LD_FLAGS := $(STD_LDFLAGS)
LIBS := $(STD_LIBS) -lz


CSOURCES := $(wildcard src/*.c)
SOURCES := $(wildcard src/*.cpp)

# ifneq ($(TARGET_OS), windows)
# SOURCES += SyslogChannel.cpp
# else
# SOURCES += WindowsConsoleChannel.cpp \
# EventLogChannel.cpp
# endif

COBJECTS := $(addprefix $(OBJROOT)/core/static/,$(notdir $(CSOURCES:.c=.o)))
SHARED_COBJECTS := $(addprefix $(OBJROOT)/core/shared/,$(notdir $(CSOURCES:.c=.o)))
OBJECTS := $(addprefix $(OBJROOT)/core/static/,$(notdir $(SOURCES:.cpp=.o)))
SHARED_OBJECTS := $(addprefix $(OBJROOT)/core/shared/,$(notdir $(SOURCES:.cpp=.o)))

#$(info Headers are [${HEADERS}])

all: makedir objfile $(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).a \
		$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).so.$(VERSION) $(HTARGET)
		
objfile:
	$(file >$(TOP)/build/$(TARGET)/npoco/obj/core/shared/s_objects.psr, $(SHARED_OBJECTS) $(SHARED_COBJECTS))

$(OBJROOT)/core/static/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJROOT)/core/static/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(OBJROOT)/core/shared/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(SHARED_FLAGS)
	
$(OBJROOT)/core/shared/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SHARED_FLAGS)
	
makedir:
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/obj/core/static
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/obj/core/shared
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/lib
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/include/npoco/Dynamic
	
$(INCLOUT)/%.h: $(HEADERS)
	$(CP) $< $@

$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).a: $(OBJECTS) $(COBJECTS)
	-rm -f $@
	$(AR) rcs $@ $^
	cp $@ $@.debug
	$(STRIP) -S --strip-unneeded $@
	
$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).so.$(VERSION): $(SHARED_OBJECTS) $(SHARED_COBJECTS)
	$(CXX) -o $@ $(SHARED_FLAGS) $(LD_FLAGS) @$(TOP)/build/$(TARGET)/npoco/obj/core/shared/s_objects.psr $(LIBS)
	cp $@ $@.debug
	$(STRIP) -S --strip-unneeded $@
	
clean:
	$(RM) $(OBJECTS)
