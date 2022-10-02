ifndef TARGET
$(error TARGET parameter not provided.)
endif

include ../$(TARGET).mk

OUTPUT = libNPocoNet
VERSION := 0.1

INCLUDE = $(STD_INCLUDE) -I$(TOP)/build/$(TARGET)/npoco/include
CFLAGS = $(STD_CFLAGS) $(INCLUDE)
CXXFLAGS := $(STD_CXXFLAGS) $(INCLUDE)
SHARED_FLAGS := -fPIC -shared -Wl,-soname,$(OUTPUT).so.$(VERSION)

OBJROOT := ../build/$(TARGET)/npoco/obj
INCLOUT := $(TOP)/build/$(TARGET)/npoco/include/npoco/net
HEADERS := $(wildcard src/*.h) \
			$(wildcard src/platforms/*.h)
HTARGET := $(addprefix $(INCLOUT)/,$(notdir $(wildcard src/*.h))) \
			$(addprefix $(INCLOUT)/,$(notdir $(wildcard src/platforms/*.h)))
LD_FLAGS := $(STD_LDFLAGS)
LIBS := $(STD_LIBS) -lz


CSOURCES := $(wildcard src/*.c)
SOURCES := $(wildcard src/*.cpp)

COBJECTS := $(addprefix $(OBJROOT)/net/static/,$(notdir $(CSOURCES:.c=.o)))
SHARED_COBJECTS := $(addprefix $(OBJROOT)/net/shared/,$(notdir $(CSOURCES:.c=.o)))
OBJECTS := $(addprefix $(OBJROOT)/net/static/,$(notdir $(SOURCES:.cpp=.o)))
SHARED_OBJECTS := $(addprefix $(OBJROOT)/net/shared/,$(notdir $(SOURCES:.cpp=.o)))


all: makedir objfile $(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).a \
		$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).so.$(VERSION) $(HTARGET)
		
objfile:
	$(file >$(TOP)/build/$(TARGET)/npoco/obj/net/shared/s_objects.psr, $(SHARED_OBJECTS) $(SHARED_COBJECTS))

$(OBJROOT)/net/static/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJROOT)/net/static/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(OBJROOT)/net/shared/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(SHARED_FLAGS)
	
$(OBJROOT)/net/shared/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SHARED_FLAGS)
	
makedir:
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/obj/net/static
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/obj/net/shared
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/lib
	$(MKDIR) $(TOP)/build/$(TARGET)/npoco/include/npoco/net
	
$(INCLOUT)/%.h: $(HEADERS)
	$(CP) $< $@

$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).a: $(OBJECTS) $(COBJECTS)
	-rm -f $@
	$(AR) rcs $@ $^
	cp $@ $@.debug
	$(STRIP) -S --strip-unneeded $@
	
$(TOP)/build/$(TARGET)/npoco/lib/$(OUTPUT).so.$(VERSION): $(SHARED_OBJECTS) $(SHARED_COBJECTS)
	$(CXX) -o $@ $(SHARED_FLAGS) $(LD_FLAGS) @$(TOP)/build/$(TARGET)/npoco/obj/net/shared/s_objects.psr $(LIBS)
	cp $@ $@.debug
	$(STRIP) -S --strip-unneeded $@
	
clean:
	$(RM) $(OBJECTS)
