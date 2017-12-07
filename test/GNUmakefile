################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [check]

include ../defs.mk
SOURCES := $(wildcard *.cpp)
TESTS := $(patsubst %.cpp,%.$(TESTSUFF),$(SOURCES))

.PHONY: tests check
include ../testpref.mk
include ../src/GNUmakefile

# Override included values
CFLAGS = -pedantic-errors
CFLAGS_TEST = -MMD -o $@
WARNS = -Wall
ifdef std98
WARNS += -Wno-long-long
ifeq ($(compiler),gcc)
WARNS += -Wno-c++0x-compat
else ifeq ($(compiler),clang)
WARNS += -Wno-non-literal-null-conversion
endif
endif
GARBAGE += *.d *.$(TESTSUFF)

-include *.d
include ../testsuff.mk
