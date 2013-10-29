# Copyright (C) 2013 David 'Mokon' Bond,  All Rights Reserved

###############################################################################
# Shared
###############################################################################

SRC_DIR = ../src
bin_PROGRAMS =
AM_LIBTOOLFLAGS= --silent

# TODO update mcommon to build self.
SHARED_SOURCES = \
  ${SRC_DIR}/../mcommon/src/mcommon/Quantity.cpp \
  ${SRC_DIR}/../mcommon/src/mcommon/Unit.cpp \
  ${SRC_DIR}/Config.cpp \
  ${SRC_DIR}/mfit/Run.cpp \
  ${SRC_DIR}/Main.cpp 

if DEBUG
  AM_CXXFLAGS = -DDEBUG -g -O0 -rdynamic -fstack-protector-all -static -pg
  AM_LDFLAGS = -static -pg
else
  AM_CXXFLAGS = -g0 -O3
endif # DEBUG

AM_CXXFLAGS += -Wall -Wextra -std=c++11 -pedantic -Werror

###############################################################################
  bin_PROGRAMS += mfit

  mfit_CXXFLAGS =  $(AM_CXXFLAGS) -I../src -I../mcommon/src
  mfit_CPPFLAGS = $(AM_CPPFLAGS)
  mfit_LDFLAGS = $(LDFLAGS) -static
  mfit_LDADD += $(LDADD) $(AM_LDADD)

  mfit_SOURCES = \
  	${SHARED_SOURCES} 

