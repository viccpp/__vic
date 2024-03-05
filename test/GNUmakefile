##############################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [check]

include ../src/defs.mk
Makefile = GNUmakefile
SOURCES := $(wildcard *.cpp)
TESTS := $(patsubst %.cpp,%.$(TESTSUFF),$(SOURCES))

.PHONY: tests check
include pref.mk
include ../src/$(Makefile)

# Override included values
ifneq ($(filter $(compiler),msvc clang-cl),) # msvc or clang-cl
CFLAGS = -D_CRT_SECURE_NO_DEPRECATE
CFLAGS_TEST = -MT
WARNS = -W3 -wd4290 -wd4800 -D_CRT_SECURE_NO_WARNINGS
LIBS += user32.lib gdi32.lib notelemetry.obj
else
CFLAGS = -pedantic-errors
CFLAGS_TEST = -static -MMD -o $@
WARNS = -Wall -Wno-unused-local-typedefs
ifeq ($(std),98)
WARNS += -Wno-long-long
ifeq ($(compiler),gcc)
WARNS += -Wno-c++0x-compat
else ifeq ($(compiler),clang)
WARNS += -Wno-non-literal-null-conversion
endif
endif
LIBS += -lgdi32
GARBAGE += *.d
endif
GARBAGE += *.$(TESTSUFF)

-include *.d
include suff.mk
