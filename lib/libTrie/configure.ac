# Process this file with autoconf to produce a configure script.
AC_INIT(libTrie, 0.1, rbtcollins@squid-cache.org)
AC_CONFIG_SRCDIR([src/Trie.cc])
AM_CONFIG_HEADER([config.h])
AC_CONFIG_AUX_DIR(cfgaux)

SquidInline="yes"

AC_ARG_ENABLE(optimizations,
  AC_HELP_STRING([--disable-optimizations],
                 [Don't compile Squid with compiler optimizations enabled.
                  Optimization is good for production builds, but not
                  good for debugging. During development, use
                  --disable-optimizations to reduce compilation times
                  and allow easier debugging. This option implicitly
                  also enabled --disable-inline]),
[ if test "$enableval" = "no" ; then
        AC_MSG_NOTICE([Disabling compiler optimizations (-O flag)])
        CFLAGS="`echo $CFLAGS | sed -e 's/-O[[0-9]]*//'`"
        CXXFLAGS="`echo $CXXFLAGS | sed -e 's/-O[[0-9]]*//'`"
        SquidInline="no"
  fi
])

AC_ARG_ENABLE(inline,
  AC_HELP_STRING([--disable-inline],
                 [Don't compile trivial methods as inline. Squid
                  is coded with much of the code able to be inlined.
                  Inlining is good for production builds, but not
                  good for development. During development, use
                  --disable-inline to reduce compilation times and
                  allow incremental builds to be quick. For
                  production builds, or load tests, use
                  --enable-inline to have squid make all trivial
                  methods inlinable by the compiler.]),
[ if test "$enableval" = "no" ; then
     SquidInline="no"
   fi
])

if test "$SquidInline" = "yes" ; then
    AC_DEFINE(_SQUID_INLINE_, inline, [Keyword used by squid for inlining methods])
    AC_DEFINE(_USE_INLINE_,, [Include inline methods into header file])
else
    AC_MSG_NOTICE([Inlining optimization disabled])
    AC_DEFINE(_SQUID_INLINE_,, [Keyword used by squid for inlining methods])
fi


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG_CPLUSPLUS
AC_PROG_MAKE_SET
# for old automakes - like squid-cache.orgs!
AM_INIT_AUTOMAKE(libTrie, 0.1)
AM_MAINTAINER_MODE
AC_PROG_RANLIB

dnl set useful flags
TRIE_CFLAGS=
TRIE_CXXFLAGS=
if test "$GCC" = "yes"; then
  TRIE_CFLAGS="-Wall -Wpointer-arith -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations -Wcomments"
  TRIE_CXXFLAGS="-Wall -Wpointer-arith -Wwrite-strings -Wcomments"

  AC_ARG_ENABLE(strict-error-checking,
    AS_HELP_STRING([--disable-strict-error-checking],[By default compile
                   with all possible static compiler error-checks enabled.
                   This flag disables the behavior]), [
    case $enableval in
      yes|1|true)
	enable_strict_error_checking=yes
	;;
      *)
	enable_strict_error_checking=no
	;;
    esac
  ])
  AC_MSG_NOTICE([strict error checking enabled: ${enable_strict_error_checking:=yes}])
  if test "x${enable_strict_error_checking:=yes}" = "xyes"; then
     TRIE_CFLAGS="-Werror $TRIE_CFLAGS"
     TRIE_CXXFLAGS="-Werror $TRIE_CXXFLAGS"
  fi

  AC_TEST_CHECKFORHUGEOBJECTS
  TRIE_CXXFLAGS="$TRIE_CXXFLAGS $HUGE_OBJECT_FLAG"
fi

AC_SUBST(TRIE_CFLAGS)
AC_SUBST(TRIE_CXXFLAGS)

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS( \
	iostream \
)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
