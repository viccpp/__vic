##############################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang|intel}] [std={98|11|14|17}] [pic=1]

include ../src/defs.mk
OBJSUFF = o
ARSUFF = a
std = 14

ifndef compiler
OS := $(shell uname)
ifeq ($(OS),Linux)
compiler = gcc
else ifeq ($(OS),FreeBSD)
compiler = clang
endif
endif

##############################################################################
ifeq ($(compiler),gcc)
CC     := g++ -std=c++$(std) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long)
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
##############################################################################
else ifeq ($(compiler),clang)
CC     := clang++ -std=c++$(std) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long )-Wno-non-literal-null-conversion
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
##############################################################################
else ifeq ($(compiler),intel)
ifeq ($(std),98)
$(error C++98 mode is not supported by Intel compiler)
endif
CC     := icpc -std=c++$(std) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS  :=
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
endif
##############################################################################

LIBSUFFIX = $(std)$(if $(pic),_pic)
LIBFILE := lib$(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
CFLAGS_ALL = -I../include $(if $(pic),$(CFLAGS_PIC) )$(CFLAGS) $(WARNS)
AR = ar
ARFLAGS = s
ARFLAGS_ALL = r$(ARFLAGS) $@

ifndef SOURCES
SOURCES := $(wildcard *.cpp)
endif
OBJS := $(patsubst %.cpp,%.$(OBJSUFF),$(SOURCES))

.PHONY: clean
include ../src/rules.mk
