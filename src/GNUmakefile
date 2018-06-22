################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang|intel}] [std98=1] [pic=1]

include ../src/defs.mk
OBJSUFF = o
ARSUFF = a

ifndef compiler
OS := $(shell uname)
ifeq ($(OS),Linux)
compiler = gcc
else ifeq ($(OS),FreeBSD)
compiler = clang
endif
endif

ifeq ($(compiler),gcc)
CC     := g++ -std=c++$(if $(std98),98,11) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS  := $(if $(std98),-Wno-long-long)
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
else ifeq ($(compiler),clang)
CC     := clang++ -std=c++$(if $(std98),98,11) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3
WARNS  := $(if $(std98),-Wno-long-long )-Wno-non-literal-null-conversion
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
else ifeq ($(compiler),intel)
CC     := icpc $(if $(std98),$(error C++98 mode is not supported by Intel compiler),-std=c++11) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS  :=
CFLAGS_PIC = -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
endif

LIBSUFFIX = $(if $(std98),98)$(if $(pic),_pic)
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
