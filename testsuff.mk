################################################################
# Common part of all test Makefiles (suffix part)

$(TESTS): ../src/$(LIBFILE)
../src/$(LIBFILE):
	cd ../src && $(MAKE) CFLAGS="$(CFLAGS)" WARNS="$(WARNS)"

clean::
	@cd ../src && $(MAKE) clean
