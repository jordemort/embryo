/*
 * Things needed to compile under linux.
 *
 * Should be reworked totally to use GNU's 'configure'
 */

/*
 * Getchar is not a 'cool' replacement for MSDOS getch: Linux/unix depends on the features activated or not about the
 * controlling terminal's tty. This means that ioctl(2) calls must be performed, for instance to have the controlling terminal tty's
 * in 'raw' mode, if we want to be able to fetch a single character. This also means that everything must be put back
 * correctly when the program ends.
 *
 * For interactive use of SRUN/SDBG if would be much better to use GNU's readline package: the user would be able to have
 * a complete emacs/vi like line editing system.
 *
 * So we stick to getchar at the moment... (one needs to key ctrl-d to terminate input if getch is called with a controlling
 * terminal driven by a tty having -raw)
 */
#if defined LINUX
  #include "config.h"
#endif

/* Linux NOW has these */
#if !defined BIG_ENDIAN
  #define BIG_ENDIAN    4321
#endif
#if !defined LITTLE_ENDIAN
  #define LITTLE_ENDIAN 1234
#endif

/* educated guess, BYTE_ORDER is undefined, i386 is common => little endian */
#ifdef WORDS_BIGENDIAN
# undef BYTE_ORDER
# define BYTE_ORDER BIG_ENDIAN
#else
# undef BYTE_ORDER
# define BYTE_ORDER LITTLE_ENDIAN
#endif

#define getch           getchar
#define	stricmp(a,b)    strcasecmp(a,b)
#define	strnicmp(a,b,c) strncasecmp(a,b,c)

/*
 * WinWorld wants '\'. Unices do not.
 */
#define	DIRECTORY_SEP_CHAR      '/'
#define	DIRECTORY_SEP_STR       "/"

/*
 * SC assumes that a computer is Little Endian unless told otherwise. It uses
 * (and defines) the macros BYTE_ORDER and BIG_ENDIAN.
 * For Linux, we must overrule these settings with those defined in glibc.
 */
#if !defined __BYTE_ORDER
# include <stdlib.h>
#endif

#ifndef __BYTE_ORDER
# define __BYTE_ORDER    BYTE_ORDER
#endif
#ifndef __LITTLE_ENDIAN
# define __LITTLE_ENDIAN LITTLE_ENDIAN
#endif
#ifndef __BIG_ENDIAN
# define __BIG_ENDIAN    BIG_ENDIAN
#endif

#if !defined __BYTE_ORDER
# error	"Can't figure computer byte order (__BYTE_ORDER macro not found)"
#endif

