all: world

CXX?=g++
CXXFLAGS?=--std=c++23 -Wall
LDFLAGS?=-L/lib -L/usr/lib
INCLUDES:=-I./include -I.
LIBS:=

OBJS:= \
	objs/app.o \
	objs/mutex.o objs/signal.o \
	objs/loop.o \
	objs/main.o

IPV6:=0

include common/Makefile.inc
include pingcpp/Makefile.inc
include logger/Makefile.inc
include Makefile.ubus

world: netdaermon

objs/app.o: src/app.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/mutex.o: src/mutex.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/signal.o: src/signal.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/loop.o: src/loop.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

netdaemon: $(OBJS) $(COMMON_OBJS) $(LOGGER_OBJS) $(PINGCPP_OBJS) $(UBUS_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(UBUS_LIBS)  $^ -o $@;

clean:
	rm -f objs/** netdaemon
