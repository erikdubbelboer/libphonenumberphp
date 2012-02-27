dnl $Id$
dnl config.m4 for extension libphonenumber

PHP_ARG_ENABLE(libphonenumberphp, whether to enable libphonenumberphp support,
[  --enable-libphonenumberphp     Enable libphonenumberphp support])

if test "$PHP_LIBPHONENUMBERPHP" != "no"; then
  PHP_REQUIRE_CXX()
  AC_LANG_CPLUSPLUS()
  CXXFLAGS="$CXXFLAGS -Wno-write-strings"
  PHP_SUBST(LIBPHONENUMBERPHP_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(phonenumber, /usr/local/lib/, LIBPHONENUMBERPHP_SHARED_LIBADD)
  PHP_NEW_EXTENSION(libphonenumberphp, libphonenumberphp.cc, $ext_shared)
fi
