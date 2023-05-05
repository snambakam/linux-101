AC_PREREQ([2.69])
AC_INIT([dtls-session-manager], [1.3.0])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_SILENT_RULES([yes])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
LT_INIT
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PREFIX_DEFAULT(/opt/msft/csudp)

AC_CONFIG_HEADERS([include/config.h])

dnl Check supported operating systems
dnl

case "${host_os}:${host_cpu}" in
    linux*:x86_64)
        PLATFORM_LIB_PREFIX=lib64
        ;;
    linux*:aarch64)
        PLATFORM_LIB_PREFIX=lib
        ;;
    *)
        AC_ERROR("Unsupported operating system - ${host_os}:${host_cpu}")
        ;;
esac

CPPFLAGS="$CPPFLAGS -D_REENTRANT -D_GNU_SOURCE -fPIC"
AM_CFLAGS="$AM_CFLAGS -Wall -Werror -fno-strict-aliasing"

AC_SUBST(AM_CFLAGS)

AC_HEADER_STDC
AC_CHECK_HEADERS(pthread.h errno.h sys/types.h sys/stat.h)
AC_CHECK_HEADERS(stdio.h string.h strings.h)
AC_CHECK_HEADERS(unistd.h time.h inttypes.h sys/socket.h netdb.h syslog.h)
AC_CHECK_HEADERS(stdlib.h locale.h stddef.h stdarg.h assert.h signal.h)
AC_CHECK_HEADERS(ctype.h netinet/in.h arpa/inet.h fcntl.h sys/un.h dirent.h)
AC_CHECK_HEADERS(termios.h term.h limits.h uuid/uuid.h)
AC_CHECK_HEADERS(pwd.h grp.h nss.h nss_common.h nsswitch.h shadow.h crypt.h)
AC_CHECK_HEADERS(arpa/inet.h sys/epoll.h)

AC_C_CONST
AC_TYPE_SIZE_T

AC_FUNC_VPRINTF
AC_CHECK_FUNCS(strerror)

#--------------------------------------------------------------------

AC_ARG_ENABLE([debug],
    [AC_HELP_STRING([--enable-debug],
                    [enable debugging (default: disabled)])],
    [
        if test x"$enableval" = x"yes"
        then
            AM_CFLAGS="$AM_CFLAGS -g -O0"
            AM_CPPFLAGS="$AM_CPPFLAGS -DDEBUG"
        fi
    ])

#--------------------------------------------------------------------

AC_CHECK_LIB([dl],
    [dlopen],
    [DL_LIBS="-ldl"])

AC_CHECK_LIB([pthread],
    [pthread_self],
    [PTHREAD_LIBS="-lpthread"])

AC_SUBST(DL_LIBS)
AC_SUBST(PTHREAD_LIBS)
#--------------------------------------------------------------------

PREFIX=$prefix
AC_SUBST(PREFIX)

#--------------------------------------------------------------------

AC_CONFIG_FILES([Makefile
    utils/Makefile
])

AC_OUTPUT
