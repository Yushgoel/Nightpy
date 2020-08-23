/* port/misc/udposix.h.  Generated automatically by configure.  */
/*
 * $Id: udposix.h.in,v 1.2 1997/05/02 22:37:36 steve Exp $
 *
 * Configuration header file.
 */

#ifndef UD_config_h
#define UD_config_h


/*
 * General environmental macros:
 */
/* #undef	_ALL_SOURCE */	/* AIX */
/* #undef	_HPUX_SOURCE */


/*
 * The following directives specify aspects of the C compiler.  Other
 * aspects of the compilation environment (e.g. the existance and
 * contents of header files) are specified in the respective header files
 * of this directory.
 */


/*
 * Variadic functions.  Define the following if your compiler doesn't
 * support <stdarg.h>.
 */
/* #undef UD_NO_STDARG */


/*
 * Compiler keywords.  Define whatever your compiler doesn't support.
 */
/* #undef UD_NO_CONST */
/* #undef UD_NO_SIGNED */
/* #undef UD_NO_VOLATILE */


/*
 * Function prototyping.  Define the following if your compiler 
 * doesn't support function prototyping.
 */
/* #undef	UD_NO_PROTOTYPES */


/*
 * String generation.  Define the following if your compiler
 * doesn't support Standard C stringization.
 */
/* #undef	UD_NO_HASH */


/*
 * Token pasting.  Define the following if your compiler doesn't support
 * Standard C token pasting.
 */
/* #undef	UD_NO_HASHHASH */


/*
 * Void pointer type.  Define the following if your compiler doesn't
 * support the void pointer type.
 */
/* #undef	UD_NO_VOIDSTAR */


/*
 * Size of various pointers:
 */
/* #undef SIZEOF_CHARP */


/*****************************************************************************
 * The following directives elaborate the above definitions or stand
 * alone.  You shouldn't need to change them.
 *****************************************************************************/


/*
 * Compiler keywords:
 */
#ifdef	UD_NO_CONST
#define	const
#else
/* #undef	const */
#endif

#ifdef	UD_NO_SIGNED
#define signed
#else
/* #undef	signed */
#endif

#ifdef	UD_NO_VOLATILE
#define	volatile
#else
/* #undef	volatile */
#endif


/*
 * Function prototyping:
 */
#ifdef UD_NO_PROTOTYPES
#define UD_PROTO(args)		()
#else
#define UD_PROTO(args)		args
#endif
/*
 * Additional macro support for function prototyping:
 */
#define UD_EXTERN_FUNC(type_name,args)	extern type_name UD_PROTO(args)


/*
 * String-generation macro:
 */
#ifdef	UD_NO_HASH
#define MAKESTRING_UD(x)	"x"
#else
#define MAKESTRING_UD(x)	#x
#endif
/*
 * Macro used in programs:
 */
#define UD_MAKESTRING(x)	MAKESTRING_UD(x)
/*
 * Macro for backwards compatibility:
 */
#define MAKESTRING(x)		UD_MAKESTRING(x)


/*
 * Token-pasting macro:
 */
#ifdef	UD_NO_HASHHASH
#define	GLUE_UD(a,b)	a/**/b
#else
#define GLUE_UD(a,b)	a##b
#endif
/*
 * Macro used in programs:
 */
#define UD_GLUE(a,b)	GLUE_UD(a,b)
/*
 * Macro for backwards compatibility:
 */
#define GLUE(a,b)	UD_GLUE(a,b)


/*
 * Pointer-to-void type:
 */
#ifndef UD_FORTRAN_SOURCE
#   ifdef	UD_NO_VOIDP
	typedef char	*voidp;
#   else
	typedef void	*voidp;
#   endif
#endif


/*
 * Statement macro:
 */
#ifdef lint
      extern int	UD_ZERO;
#else
#     define UD_ZERO	0
#endif
#define UD_STMT(stuff) do {stuff} while (UD_ZERO)


#endif /* UD_config_h */
