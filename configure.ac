# Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved

AC_MSG_NOTICE([Mokon Fitness Build Initilizing])

AC_INIT([Mokon Fitness],[DEV-VERSION],[mokon@mokon.net],[mfit],
        [http://mokon.net])

AC_COPYRIGHT([Copyright (C) 2013 David 'Mokon' Bond])
AC_REVISION([$Revision: 0.0 $])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AC_DEFINE([PACKAGE_COPYRIGHT],
          ["Copyright (C) 2013 David 'Mokon' Bond, All Rights Reserved"],
          [Copyright String for the Package])

###############################################################################
# Some standard mcommon configure file contents.
###############################################################################

m4_include([mcommon/configure.m4])

###############################################################################

AC_LANG([C++])
: ${CXXFLAGS=""}
AC_PROG_CXX #([g++, clang++])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_LIBTOOL

###############################################################################
# Dependancies
###############################################################################

M_CHECK_LIB([glog],[mfit])
M_CHECK_LIB([boost_system],[mfit])

AC_SUBST([mfit_LDADD])

###############################################################################

AC_CONFIG_FILES([
  Makefile
  object/Makefile
  test/Makefile
  doc/Makefile
])

AC_OUTPUT

