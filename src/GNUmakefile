################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang}] [std98=1]

include ../defs.mk
OBJSUFF = o
ARSUFF = a

compiler ?= gcc

ifeq ($(compiler),gcc)
CC      = g++ -std=c++$(if $(std98),98,11)
CFLAGS  = -pedantic-errors -DNDEBUG -O3
WARNS   = $(if $(std98),-Wno-long-long)
else ifeq ($(compiler),clang)
CC      = clang++ -std=c++$(if $(std98),98,11)
CFLAGS  = -pedantic-errors -DNDEBUG -O3
WARNS   = $(if $(std98),-Wno-long-long) -Wno-non-literal-null-conversion
endif

LIBSUFFIX = $(if $(std98),98)
LIBFILE := lib$(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
CFLAGS_ALL = -I../include $(CFLAGS) $(WARNS)
AR = ar
ARFLAGS = s
ARFLAGS_ALL = r$(ARFLAGS) $@

ifndef SOURCES
SOURCES := $(wildcard *.cpp)
endif
OBJS := $(patsubst %.cpp,%.$(OBJSUFF),$(SOURCES))

.PHONY: clean
include ../rules.mk
