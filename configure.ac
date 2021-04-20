AC_INIT([lc-coreutils],[1.0])
AC_CONFIG_SRCDIR([try_compile.c])
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_FUNC(error,[
    error=
],[
    error=error
])

AC_ARG_ENABLE(coreutils,[
    if xyes \= x$ac_enable
    then
        coreutils=echo,false,true,hashfile,nohup,mkdir,pwd,link,yes,dirname,basename,chmod,mkfifo,mknod,which,arch,unlink,rmdir
    elif xno \= x$ac_enable -o x \= x$ac_enable
    then
        coreutils= # just build chmod-parse, and possibly error
    else
        coreutils=$ac_enable
    endif
],[
    coreutils=echo,false,true,hashfile,nohup,mkdir,pwd,link,yes,dirname,basename,chmod,mkfifo,mknod,which,arch,unlink,rmdir
])


AC_SUBST(error coreutils)
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
