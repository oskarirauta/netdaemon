all: world

CXX?=g++
CXXFLAGS?=--std=c++23 -Wall
INCLUDES:=-I./include -I.

OBJS:= \
	objs/app.o \
	objs/main.o

IPV6:=0

include common/Makefile.inc
include pingcpp/Makefile.inc
include logger/Makefile.inc

world: netguard

objs/app.o: src/app.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

netguard: $(OBJS) $(COMMON_OBJS) $(LOGGER_OBJS) $(PINGCPP_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@;

clean:
	rm -f objs/** netguard
