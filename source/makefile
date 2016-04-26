# Makefile template for shared library

ifeq ($(arch),X64) 
  ARCHITECTURE = -m64
  CC = g++-4.9
  CXX = g++-4.9
  LIBSDEF =  libs/linux_x64/libohNetCore.a libs/linux_x64/libohNetDevices.a libs/linux_x64/libohNetProxies.a
  TARGET = libs/_tmpBuild/raumkernel.so
endif
	
ifeq ($(arch),X86) 
  ARCHITECTURE = -m32 
  CC = g++-4.9
  CXX = g++-4.9
  LIBSDEF =  libs/linux_x86/libohNetCore.a libs/linux_x86/libohNetDevices.a libs/linux_x86/libohNetProxies.a
  TARGET = libs/_tmpBuild/raumkernel.so
endif

ifeq ($(arch),ARMA53)
  ARCHITECTURE = -march=armv8-a
  CC = arm-linux-gnueabihf-g++-4.9 
  CXX = arm-linux-gnueabihf-g++-4.9
  LIBSDEF = libs/linux_ARMA53/libohNetCore.a libs/linux_ARMA53/libohNetDevices.a libs/linux_ARMA53/libohNetProxies.a
  TARGET = libs/_tmpBuild/raumkernel.so
endif

ifeq ($(arch),ARMV7HF)
  ARCHITECTURE = 
  CC = arm-linux-gnueabihf-g++-4.9 
  CXX = arm-linux-gnueabihf-g++-4.9
  LIBSDEF = libs/linux_ARMV7/libohNetCore.a libs/linux_ARMV7/libohNetDevices.a libs/linux_ARMV7/libohNetProxies.a
  TARGET = libs/_tmpBuild/raumkernel.so
endif

ifeq ($(arch),ARMV6)
  ARCHITECTURE = -march=armv6
  CC = arm-linux-gnueabi-g++-4.9 
  CXX = arm-linux-gnueabi-g++-4.9
  LIBSDEF = libs/linux_ARMV6/libohNetCore.a libs/linux_ARMV6/libohNetDevices.a libs/linux_ARMV6/libohNetProxies.a
  TARGET = libs/_tmpBuild/raumkernel.so
endif


DEBUG = 
ifeq ($(dbg),1)
  DEBUG = -g
endif

INCPATH = -I includes/

CFLAGS = $(ARCHITECTURE) -std=c++11 -fPIC -Wall -Wno-unknown-pragmas -Wno-unused-parameter -Wextra -O2 $(DEBUG) -c -pthread $(INCPATH)
CXXFLAGS = $(ARCHITECTURE) -std=c++11 -fPIC -Wall -Wno-unknown-pragmas -Wno-unused-parameter -Wextra -O2 $(DEBUG) -c -pthread $(INCPATH)
LDFLAGS = $(ARCHITECTURE) -shared -pthread -static-libgcc -static-libstdc++

RM = rm -f 

SRCS = $(wildcard *.cpp)
SRCS += $(wildcard device/*.cpp)
SRCS += $(wildcard device/eventParser/*.cpp)
SRCS += $(wildcard device/proxies/*.cpp)
SRCS += $(wildcard httpclient/*.cpp)
SRCS += $(wildcard logger/*.cpp)
SRCS += $(wildcard manager/*.cpp)
SRCS += $(wildcard media/*.cpp)
SRCS += $(wildcard media/item/*.cpp)
SRCS += $(wildcard tools/*.cpp)
SRCS += $(wildcard xml/pugixml/*.cpp)

OBJS = $(SRCS:.cpp=.o)


.PHONY: all
all: ${TARGET}

$(TARGET): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^ $(LIBSDEF)
 
$(SRCS:.cpp=.d):%.d:%.cpp
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.cpp=.d)


#.PHONY: clean
#clean:
#	-${RM} ${TARGET} ${OBJS} $(SRCS:.cpp=.d) 
.PHONY: clean
clean:
	-${RM} ${TARGET} ${OBJS} $(SRCS:.cpp=.d) 
