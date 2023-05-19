AC_PREREQ([2.69])
AC_INIT([csgrpc], [1.0.0])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_SILENT_RULES([yes])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
LT_INIT
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PREFIX_DEFAULT(/usr/lib/csgrpc)

AC_CONFIG_HEADERS([include/csgrpc-config.h])

dnl Check supported operating systems
dnl

case "${host_os}:${host_cpu}" in
    linux*:x86_64)
        PLATFORM_LIB_PREFIX=lib64
        ;;
    linux*:aarch64)
        PLATFORM_LIB_PREFIX=lib64
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
AC_CHECK_HEADERS(arpa/inet.h sys/epoll.h sys/timerfd.h)

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
                changequote({,})
                CFLAGS=`echo "$CFLAGS" | sed -e 's/-O[0-9]*//g'`
                CFLAGS="$CFLAGS -g -O0"
                CXXFLAGS=`echo "$CXXFLAGS" | sed -e 's/-O[0-9]*//g'`
                CXXFLAGS="$CXXFLAGS -g -O0"
                changequote([,])
        fi
    ])

#--------------------------------------------------------------------

AC_ARG_WITH([ssl],
    [AC_HELP_STRING([--with-ssl=<dir>],
                    [use SSL binaries rooted at prefix <dir>])],
    [
        OPENSSL_BASE_PATH="$withval"
    ],
    [
        OPENSSL_BASE_PATH="/usr"
    ])

AC_ARG_WITH([ssl-includes],
    [AC_HELP_STRING([--with-ssl-includes=<dir>],
                    [use SSL headers located in prefix <dir>])],
    [
        OPENSSL_INCLUDES="-DOPENSSL_NO_KRB5 -I$withval"
    ],
    [
        OPENSSL_INCLUDES="-DOPENSSL_NO_KRB5 -I$OPENSSL_BASE_PATH/include"
    ])

AC_ARG_WITH([ssl-libs],
    [AC_HELP_STRING([--with-ssl-libs=<dir>],
                    [use SSL libraries located in prefix <dir>])],
    [
        OPENSSL_LDFLAGS="-L$withval"
    ],
    [
        OPENSSL_LDFLAGS="-L$OPENSSL_BASE_PATH/$PLATFORM_LIB_PREFIX -Wl,-rpath,$prefix/$PLATFORM_LIB_PREFIX"
    ])

AC_SUBST(OPENSSL_BASE_PATH)
AC_SUBST(OPENSSL_INCLUDES)
AC_SUBST(OPENSSL_LDFLAGS)

saved_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $OPENSSL_INCLUDES"
AC_CHECK_HEADERS(openssl/crypto.h openssl/ssl.h openssl/err.h openssl/rsa.h openssl/evp.h openssl/rand.h)
CPPFLAGS="$saved_CPPFLAGS"

#--------------------------------------------------------------------

AC_ARG_WITH([jansson],
    [AC_HELP_STRING([--with-jansson=<dir>],
                    [use jansson binaries rooted at prefix <dir>])],
    [
        JANSSON_BASE_PATH="$withval"
    ],
    [
        JANSSON_BASE_PATH="/usr"
    ])

JANSSON_INCLUDES="-I$JANSSON_BASE_PATH/include"
JANSSON_LDFLAGS="-L$JANSSON_BASE_PATH/lib"

AC_CHECK_HEADERS(jansson.h)
AC_SUBST(JANSSON_BASE_PATH)
AC_SUBST(JANSSON_INCLUDES)
AC_SUBST(JANSSON_LDFLAGS)

#--------------------------------------------------------------------

AC_ARG_WITH([grpc],
    [AC_HELP_STRING([--with-grpc=<dir>],
                    [use GRPC binaries rooted at prefix <dir>])],
    [
        GRPC_BASE_PATH="$withval"
    ],
    [
        GRPC_BASE_PATH="/usr"
    ])

GRPC_INCLUDES="-I$GRPC_BASE_PATH/include"
GRPC_LDFLAGS="-L$GRPC_BASE_PATH/lib"

AC_CHECK_HEADERS(grpc++/channel.h)
AC_SUBST(GRPC_BASE_PATH)
AC_SUBST(GRPC_INCLUDES)
AC_SUBST(GRPC_LDFLAGS)

#--------------------------------------------------------------------

PKG_CHECK_MODULES(PROTOBUF, protobuf >= 3.12.4)
AC_SUBST(PROTOBUF_LIBS)
AC_SUBST(PROTOBUF_CFLAGS)
AC_SUBST(PROTOBUF_VERSION)

AC_CHECK_PROG([PROTOC], [protoc], [protoc])

if test x"$PROTOC" = x"no"; then
    AC_MSG_ERROR([PROTOC compiler not found])
fi

AC_SUBST(PROTOC)

#--------------------------------------------------------------------

PKG_CHECK_MODULES(GRPC, grpc++ >= 1.30.2)
AC_SUBST(GRPC_LIBS)
AC_SUBST(GRPC_CFLAGS)
AC_SUBST(GRPC_VERSION)

#--------------------------------------------------------------------

AC_ARG_WITH([grpc-cpp-plugin],
    [AC_HELP_STRING([--with-grpc-cpp-plugin=<dir>],
                    [use GRPC CPP Plugin binary rooted at prefix <dir>])],
    [
        GRPC_CPP_PLUGIN_PATH="$withval/bin"
    ],
    [
        GRPC_CPP_PLUGIN_PATH="/usr/bin"
    ])

AC_PATH_PROG(
    [GRPC_CPP_PLUGIN], [grpc_cpp_plugin], [no], [$PATH:$GRPC_CPP_PLUGIN_PATH]
)

if test x"$GRPC_CPP_PLUGIN" = x"no"; then
    AC_MSG_ERROR([grpc_cpp_plugin not found])
fi

AC_SUBST(GRPC_CPP_PLUGIN)

#--------------------------------------------------------------------

AC_CHECK_LIB([dl],
    [dlopen],
    [DL_LIBS="-ldl"])

AC_CHECK_LIB([pthread],
    [pthread_self],
    [PTHREAD_LIBS="-lpthread"])

AC_CHECK_LIB([uuid],
    [uuid_copy],
    [UUID_LIBS="-luuid"],
    [],
    [$LW_LDFLAGS -luuid])

AC_CHECK_LIB([crypto],
    [MD5_Init],
    [CRYPTO_LIBS="-lcrypto -lssl"],
    [],
    [$OPENSSL_LDFLAGS])

AC_CHECK_LIB([jansson],
    [json_object],
    [JANSSON_LIBS="-ljansson"],
    [],
    [$JANSSON_LDFLAGS])

AC_SUBST(DL_LIBS)
AC_SUBST(PTHREAD_LIBS)
AC_SUBST(CRYPTO_LIBS)
AC_SUBST(UUID_LIBS)
AC_SUBST(JANSSON_LIBS)
#--------------------------------------------------------------------

PREFIX=$prefix
AC_SUBST(PREFIX)

systemddir=/lib/systemd/system
AC_SUBST(systemddir)

if test x"$localstatedir" = x"/var"; then
    CSGRPC_COMM_DIR="$localstatedir/lib/csgrpc/comm"
else
    CSGRPC_COMM_DIR="$localstatedir/csgrpc/comm"
fi

AC_SUBST(CSGRPC_COMM_DIR)

AC_DEFINE_UNQUOTED(
    CSGRPC_COMM_PATH,
    "$CSGRPC_COMM_EXP_DIR",
    [Client Server GRPC Communications Path]
)

#--------------------------------------------------------------------

AC_CONFIG_FILES([
    Makefile
    client/src/Makefile
    server/Makefile
    server/csgrpcd/Makefile
    server/utils/src/Makefile
    tools/Makefile
    tools/cli/Makefile
])

AC_OUTPUT
