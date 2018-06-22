################################################################
# Common part of all test Makefiles (suffix part)

$(TESTS): ../src/$(LIBFILE)
../src/$(LIBFILE):
	cd ../src && $(MAKE) -f $(Makefile) CFLAGS="$(CFLAGS)" WARNS="$(WARNS)"

clean::
	@cd ../src && $(MAKE) -f $(Makefile) clean
