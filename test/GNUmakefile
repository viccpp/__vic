##############################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [modules=1] [check]

include ../src/defs.mk
Makefile = GNUmakefile
SOURCES := $(wildcard *.cpp)
TESTS := $(patsubst %.cpp,%.$(TESTSUFF),$(SOURCES))

.PHONY: tests check
include pref.mk
include ../src/$(Makefile)

# Override included values
##############################################################################
ifneq ($(filter $(compiler),msvc clang-cl),) # msvc or clang-cl
CFLAGS = -D_CRT_SECURE_NO_DEPRECATE
CFLAGS_TEST = -MT
WARNS = -W3 -wd4290 -wd4800 -D_CRT_SECURE_NO_WARNINGS
LIBS += user32.lib gdi32.lib ws2_32.lib notelemetry.obj
##############################################################################
else
CFLAGS = -pedantic-errors
CFLAGS_TEST = -static $(if $(modules),,-MMD )-o $@
WARNS = -Wall -Wno-unused-local-typedefs
ifeq ($(compiler),clang)
WARNS += -Wno-mismatched-tags
endif
ifeq ($(std),98)
WARNS += -Wno-long-long
ifeq ($(compiler),gcc)
WARNS += -Wno-c++0x-compat
else ifeq ($(compiler),clang)
WARNS += -Wno-non-literal-null-conversion
endif
endif
LIBS += -lgdi32 -lws2_32
GARBAGE += *.d
endif
##############################################################################
GARBAGE += *.$(TESTSUFF)

##############################################################################
ifdef modules
# GCC
ifeq ($(compiler),gcc)
PRECOMPILED_MODULES = gcm.cache/std.gcm gcm.cache/__vic.gcm
CC += -fmodules
GARBAGE += gcm.cache
# Clang
else ifeq ($(compiler),clang)
PRECOMPILED_MODULES = std.pcm __vic.pcm
CLANG_HOME = $(patsubst =%/bin,%,$(word 2,$(shell $(CC) -print-search-dirs)))
CFLAGS_TEST += -fprebuilt-module-path=.
PCM_FLAGS = -Wno-reserved-module-identifier -fmodules-reduced-bmi -fmodule-output=$@
GARBAGE += *.pcm
# MS VC++
else ifeq ($(compiler),msvc)
PRECOMPILED_MODULES = std.ifc __vic.ifc
MSVC_HOME = $(realpath $(dir $(shell where cl.exe))..\..\..)
LIBS += std.obj
GARBAGE += *.ifc
endif
CFLAGS_TEST += -D__VIC_USE_MODULES=1

$(TESTS): $(PRECOMPILED_MODULES)

gcm.cache/std.gcm:
	$(CC) $(CFLAGS_ALL) -c -fmodule-only -fsearch-include-path bits/std.cc
gcm.cache/__vic.gcm: ../include/__vic/modules/__vic.mpp
	$(CC) $(CFLAGS_ALL) -c -fmodule-only -xc++ $?

std.pcm:
	$(CC) $(CFLAGS_ALL) -c $(PCM_FLAGS) $(CLANG_HOME)/share/libc++/v1/std.cppm
	-$(RM) std.o
__vic.pcm: ../include/__vic/modules/__vic.mpp
	$(CC) $(CFLAGS_ALL) -c $(PCM_FLAGS) -xc++-module $?
	-$(RM) __vic.o

std.ifc:
	$(CC) $(CFLAGS_ALL) -c $(MSVC_HOME)/modules/std.ixx
__vic.ifc: ../include/__vic/modules/__vic.mpp
	$(CC)  $(CFLAGS_ALL) -c /interface /TP $?
	-@del /Q /F __vic.obj 2>nul
endif
##############################################################################

-include *.d
include suff.mk
