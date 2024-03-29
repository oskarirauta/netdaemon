all: world

CXX?=g++
CXXFLAGS?=--std=c++23 -Wall
LDFLAGS?=-L/lib -L/usr/lib
INCLUDES:=-I./include -I. -I./ext/json11
LIBS:=

OBJS:= \
	objs/json11.o \
	objs/app.o objs/settings.o objs/states.o \
	objs/scheduler.o \
	objs/clock_time.o objs/mutex.o objs/signal.o \
	objs/stage_ifd_check.o objs/stage_ping_check.o \
	objs/loop.o \
	objs/main.o

IPV6:=0

include common/Makefile.inc
include pingcpp/Makefile.inc
include logger/Makefile.inc
include Makefile.ubus

world: netdaemon

objs/json11.o: ext/json11/json11.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/app.o: src/app.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/settings.o: src/settings.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/states.o: src/states.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/clock_time.o: src/clock_time.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/scheduler.o: src/scheduler.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/mutex.o: src/mutex.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/signal.o: src/signal.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/stage_ifd_check.o: src/stage_ifd_check.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/stage_ping_check.o: src/stage_ping_check.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/loop.o: src/loop.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

netdaemon: $(OBJS) $(COMMON_OBJS) $(LOGGER_OBJS) $(PINGCPP_OBJS) $(UBUS_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(UBUS_LIBS) $^ -o $@;

clean:
	rm -f objs/** netdaemon
