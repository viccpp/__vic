################################################################
# Common part of all Makefiles

.SUFFIXES:
.SUFFIXES: .cpp .$(OBJSUFF) .$(TESTSUFF)

$(LIBFILE): $(OBJS)
	$(AR) $(ARFLAGS_ALL) $?

.cpp.$(OBJSUFF):
	$(CC) -c $(CFLAGS_ALL) $<

.cpp.$(TESTSUFF):
	$(CC) $(CFLAGS_ALL) $(CFLAGS_TEST) $< $(LIBS)

clean::
	del /Q /F *.$(OBJSUFF) *.$(ARSUFF) $(GARBAGE) 2>nul
