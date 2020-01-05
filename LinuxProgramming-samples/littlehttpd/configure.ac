AC_PREREQ(2.50)
AC_INIT(littlehttpd, 1.0.0, aamine@loveruby.net)
AC_CONFIG_SRCDIR([littlehttpd.c])
AC_CONFIG_HEADER([config.h])

AC_PROG_CC
AC_LANG_C

AC_CHECK_LIB(socket, socketpair)
AC_CHECK_LIB(nsl, t_open)

AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(unstd.h fcntl.h sys/stat.h sys/time.h sys/socket.h netdb.h\
                 syslog.h getopt.h pwd.h grp.h)

AC_C_CONST
AC_TYPE_SIZE_T
AC_STRUCT_TM

AC_CHECK_DECLS(initgroups, [], [], [#include <grp.h>
#include <sys/types.h>])

AC_FUNC_FORK
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_CHECK_FUNCS(memset strcasecmp strchr strerror strncasecmp strspn vfprintf\
	       socket getaddrinfo, [], [AC_MSG_ERROR(missing function)])
AC_CHECK_FUNCS(vsyslog vsnprintf, break)
AC_CHECK_FUNCS(getopt_long getopt, break)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
