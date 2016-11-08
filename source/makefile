# Makefile template for shared library
DTARGET := build/libraumkernel.so
STARGET := build/libraumkernel.a

# defining the source files for the project
SRCFILES := $(wildcard *.cpp)
SRCFILES += $(wildcard device/*.cpp)
SRCFILES += $(wildcard device/eventParser/*.cpp)
SRCFILES += $(wildcard device/proxies/*.cpp)
SRCFILES += $(wildcard httpclient/*.cpp)
SRCFILES += $(wildcard logger/*.cpp)
SRCFILES += $(wildcard manager/*.cpp)
SRCFILES += $(wildcard media/*.cpp)
SRCFILES += $(wildcard media/item/*.cpp)
SRCFILES += $(wildcard tools/*.cpp)
SRCFILES += $(wildcard xml/pugixml/*.cpp)

INCPATH     := -I includes/
LIBSPATH    := libs/linux_$(arch)/
LIBSPATHEXE := libs
#LIBSPATHEXE := ./
DLIBSDEF    :=  $(LIBSPATH)libohNetCore.a $(LIBSPATH)libohNetDevices.a $(LIBSPATH)libohNetProxies.a
SLIBSDEF    :=  $(LIBSPATH)libohNetCore.a $(LIBSPATH)libohNetDevices.a $(LIBSPATH)libohNetProxies.a


ifeq ($(arch),) 
  COMPILER          := g++
  ARCHITECTURE      := 
  ARCHCOMPILERFLAGS :=
endif

ifeq ($(arch),X64) 
  COMPILER          := g++-4.9
  ARCHITECTURE      := -m64
  ARCHCOMPILERFLAGS :=
endif

ifeq ($(arch),ARMV7HF)
  COMPILER          := arm-linux-gnueabihf-g++-4.9 
  ARCHITECTURE      := -march=armv7-a
  ARCHCOMPILERFLAGS := -fasynchronous-unwind-tables -mapcs-frame
endif

ifeq ($(arch),ARMV5TE)
  COMPILER          := arm-linux-gnueabi-g++-4.9 
  ARCHITECTURE      := -march=armv5te -mtune=xscale
  ARCHCOMPILERFLAGS := -fasynchronous-unwind-tables -mapcs-frame
endif 


COMPILERFLAGS :=  -std=c++11 -fPIC -Wall -Wno-unknown-pragmas -Wno-unused-parameter -funwind-tables -Wextra -O2 -c -pthread 
LINKERFLAGS   :=  -pthread -static-libgcc -static-libstdc++ -rdynamic -Wl,--no-as-needed -ldl -L$(LIBSPATH) -Wl,-rpath,$(LIBSPATHEXE) 


DEBUG = 
ifeq ($(dbg),1)
  DEBUG = -g
endif

DLINKERFLAGS  	 := $(ARCHITECTURE) $(LINKERFLAGS) -shared
SLINKERFLAGS  	 := $(ARCHITECTURE) $(LINKERFLAGS)
DCOMPILERFLAGS   := $(ARCHITECTURE) $(COMPILERFLAGS) $(DEBUG) $(ARCHCOMPILERFLAGS) $(INCPATH)
SCOMPILERFLAGS   := $(ARCHITECTURE) $(COMPILERFLAGS) $(DEBUG) $(ARCHCOMPILERFLAGS) $(INCPATH)

RM  := rm -f 
RMR := rm -rf
AR  := ar

ARFLAGS := rcs

DOBJDIR := build/obj-dyn/
SOBJDIR := build/obj-stat/

DOBJFILES := $(addprefix $(DOBJDIR), $(SRCFILES:.cpp=.o))
SOBJFILES := $(addprefix $(SOBJDIR), $(SRCFILES:.cpp=.o))


.PHONY: all


### when calling make then build static and dynamic target
all: ${DTARGET} ${STARGET}
	

### create dynamic library
$(DTARGET): $(DOBJFILES)	
	$(COMPILER) ${DLINKERFLAGS} -o $@ $^ $(DLIBSDEF) 

$(DOBJDIR)%.o: %.cpp
	@ mkdir -p $(basename $@)
	$(COMPILER) $(DCOMPILERFLAGS) -MMD -c -o $@ $<

-include $(DOBJFILES:.o=.d)


### create static library
$(STARGET): $(SOBJFILES)
	$(AR) $(ARFLAGS) $@ $^ $(SLIBSDEF) 

$(SOBJDIR)%.o: %.cpp
	@ mkdir -p $(basename $@)
	$(COMPILER) $(SCOMPILERFLAGS) -MMD -c -o $@ $<

-include $(SOBJFILES:.o=.d)


### clear all build relevant files 
.PHONY: clean
clean:
	-${RM} ${DTARGET} ${STARGET} ${DOBJFILES} ${SOBJFILES} $(DOBJFILES:.o=.d) 
	-${RMR} ${DOBJDIR} ${SOBJDIR}
