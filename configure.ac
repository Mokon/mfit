# Copyright (C) 2013-2014 David 'Mokon' Bond, All Rights Reserved

AC_INIT([Mokon Fitness],[DEV-VERSION],[mokon@mokon.net],[mfit],
        [http://mokon.net])

m4_include([mcommon/templates/configure.m4])
m4_include([mcommon/templates/configure_cpp.m4])

AC_REVISION([$Revision: 0.0 $])
M_COPYRIGHT_PROPRIETARY([David 'Mokon' Bond],[2013-2014])

M_PROG_DEPS([mfit],[
                     [[boost_system],[]],
                     [[boost_program_options],[]],
                     [[boost_filesystem],[]],
                     [[glog],[]],
                     [[pugixml],[]],
                     [[mcommon],[-lpthread -lboost_system]]
                   ])

AC_OUTPUT

