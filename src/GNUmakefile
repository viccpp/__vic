################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang|msvc}] [std98=1]

include ../defs.mk

compiler ?= gcc

ifeq ($(compiler),gcc)
CC      = g++ -std=c++$(if $(std98),98,11) -mthreads
CFLAGS  = -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS   = $(if $(std98),-Wno-long-long)
bunutils = 1
else ifeq ($(compiler),clang)
CC      = clang++ -std=c++$(if $(std98),98,11)
CFLAGS  = -pedantic-errors -DNDEBUG -O3
WARNS   = $(if $(std98),-Wno-long-long )-Wno-non-literal-null-conversion
bunutils = 1
else ifeq ($(compiler),msvc)
CC      = cl /nologo $(if $(std98),$(error C++98 mode is not supported by MSVC++ compiler))
CFLAGS  = -DNDEBUG -D_CRT_SECURE_NO_DEPRECATE -O2 -Ob1
WARNS   =
endif

LIBSUFFIX = $(if $(std98),98)
ifdef bunutils
OBJSUFF = o
ARSUFF = a
LIBFILE := lib$(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
AR = ar
ARFLAGS = s
ARFLAGS_ALL = r$(ARFLAGS) $@
else
OBJSUFF = obj
ARSUFF = lib
LIBFILE := $(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
AR = lib
ARFLAGS =
ARFLAGS_ALL = -nologo $(ARFLAGS) /OUT:$@
endif
CFLAGS_ALL = -I../include -DUNICODE=1 $(CFLAGS) $(WARNS)

ifndef SOURCES
SOURCES := $(wildcard *.cpp)
endif
OBJS := $(patsubst %.cpp,%.$(OBJSUFF),$(SOURCES))

.PHONY: clean
include ../rules.mk
