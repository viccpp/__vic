################################################################
# Common part of all test Makefiles (prefix part)

LIBS = ../src/$(LIBFILE)

tests: $(TESTS)
	@

check: $(TESTS)
	@for t in $(TESTS); do echo "Running $$t..."; ./$$t || exit 1; done
	@echo OK
