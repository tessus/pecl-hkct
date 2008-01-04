dnl $Id$
dnl config.m4 for extension hkct
dnl Author: Helmut K. C. Tessarek

PHP_ARG_ENABLE(hkct, whether to enable hkct support,
[  --enable-hkct         Enable hkct support], yes)

if test "$PHP_HKCT" != "no"; then
  AC_DEFINE(HAVE_HKCT, 1, [ ])
  PHP_NEW_EXTENSION(hkct, hkct.c, $ext_shared)
fi
