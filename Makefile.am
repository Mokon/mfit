# Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = object test doc
dist_doc_DATA = README
# doc/*.pdf

TESTS = test/*.test
XFAIL_TESTS =
AM_COLOR_TESTS=always

clean-purge: clean
	rm -rf \
 	  aclocal.m4 autom4te.cache  config.h config.h.in  config.h.in~ \
    config.log config.status  configure  install-sh Makefile \
    Makefile.in  missing stamp-h1 src/Makefile.in src/Makefile depcomp \
    .deps src/.deps client COPYING INSTALL test/Makefile.in test/Makefile \
    test/.deps doc/Makefile.in doc/Makefile confdefs.h libtool gmon.out \
    config.guess ltmain.sh config.sub object/.deps object/Makefile.in \
		object/Makefile test-driver m4/*

.PHONY: clean-purge

