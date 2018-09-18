##############################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang}] [std={98|11|14|17}]

include ../src/defs.mk
OBJSUFF = o
ARSUFF = a
std = 14
compiler = gcc

##############################################################################
ifeq ($(compiler),gcc)
CC     := g++ -std=c++$(std)
CFLAGS := -pedantic-errors -DNDEBUG -O3
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long)
##############################################################################
else ifeq ($(compiler),clang)
CC     := clang++ -std=c++$(std)
CFLAGS := -pedantic-errors -DNDEBUG -O3
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long )-Wno-non-literal-null-conversion
endif
##############################################################################

LIBSUFFIX = $(std)
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
include ../src/rules.mk
