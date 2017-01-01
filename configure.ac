AC_PREREQ([2.69])
AC_INIT([gsearch], [1.0], [henri.schmidt@tufts.edu])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC

PKG_CHECK_MODULES([curl], [libcurl])

AC_CONFIG_FILES([
        Makefile
        src/Makefile
        tests/Makefile
])

AC_OUTPUT
