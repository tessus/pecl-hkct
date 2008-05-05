dnl $Id$
dnl config.m4 for extension hkct
dnl Author: Helmut K. C. Tessarek

PHP_ARG_WITH(hkct, for hkct support,
[  --with-hkct[=DIR]       Include hkct support
                          DIR is the location of APR config utils])

if test "$PHP_HKCT" != "no"; then
  if test -r $PHP_HKCT/apr-1-config && test -r $PHP_HKCT/apu-1-config ; then
    APR_DIR=$PHP_HKCT
  else
    AC_MSG_CHECKING(for APR config utilities in default path)
    for i in /usr/local/apache/bin /usr/local/bin /usr/bin; do
      if test -r $i/apr-1-config; then
        APR_DIR=$i
        AC_MSG_RESULT(found in $i)
        break
      fi
    done
  fi
  
  HKCTFLAGS=`${APR_DIR}/apr-1-config --cppflags`
 
  APR_LD=`${APR_DIR}/apr-1-config --link-ld`
  APU_LD=`${APR_DIR}/apu-1-config --link-ld`

  APRLIBS="$APR_LD $APU_LD"
  
  APR_LIBS=`${APR_DIR}/apr-1-config --libs`
  APU_LIBS=`${APR_DIR}/apu-1-config --libs`
  
  APR_INCDIR=`${APR_DIR}/apr-1-config --includedir`
  APU_INCDIR=`${APR_DIR}/apu-1-config --includedir`
  
  A_LIBS="$APR_LIBS $APU_LIBS"
  
  HKCT_CFLAGS=$HKCTFLAGS
  
  AC_DEFINE(HAVE_HKCT, 1, [ ])
  PHP_NEW_EXTENSION(hkct, hkct.c, $ext_shared,, \\$(HKCT_CFLAGS))
  PHP_ADD_INCLUDE($APR_INCDIR)
  PHP_ADD_INCLUDE($APU_INCDIR)
  PHP_EVAL_LIBLINE($A_LIBS, HKCT_SHARED_LIBADD)
  PHP_EVAL_LIBLINE($APRLIBS, HKCT_SHARED_LIBADD)
  PHP_SUBST(HKCT_CFLAGS)
fi

