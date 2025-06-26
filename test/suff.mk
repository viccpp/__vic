################################################################
# Common part of all test Makefiles (suffix part)

$(TESTS): ../src/$(LIBFILE)
../src/$(LIBFILE):
	cd ../src && $(MAKE) -f $(Makefile) std=$(std) CFLAGS="$(CFLAGS)" WARNS="$(WARNS)"

clean::
	@cd ../src && $(MAKE) -f $(Makefile) RM="$(RM)" clean
