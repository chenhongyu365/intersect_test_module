/* ORIGINAL: acis2.1/kernutil/acisio/acisio.h */
/* $Id: acisio.h,v 1.6 2001/05/15 21:07:09 acisdev Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
/**
 * @file acisio.h
 */

/* Redefine several stdio functions so we can redirect I/O to windows		*/
/* and/or other files.														*/

#ifndef ACISIO_H
#define ACISIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef __cplusplus
#include <cstdio>
#endif
#if (_MSC_VER >= 1900)
#include <process.h>
#endif
#include "dcl_base.h"

/* This file should automatically redirect I/O when building the ACIS product.	*/
/* Care must be taken to keep redirection from unintentionally 'bleeding over' into application code. */
/* SKY 5/20/03-Removing BUILDING_ACIS from our builds; use _MK_FWNAME_ instead.*/
/* Leaving the BUILDING_ACIS here in case some customers are using it.*/

#if defined(_MK_FWNAME_) || defined(BUILDING_ACIS) || defined(ACIS_IO_REDIRECTION)

/* Define this symbol in files where the standard I/O functions are needed,	*/
/* such as implementations of I/O redirection classes						*/

#ifndef NO_ACIS_IO_REDIRECTION

/* Redefine stdout, stderr and stdin so they have definitions that are		*/
/* compatible across DLLs.													*/

/* Redefine exit() so we can ensure certain termination operations occur	*/
/* before static destructors are called.									*/

#ifdef exit
#undef exit
#endif
#define exit    acis_exit

/* Redefine output functions so we can redirect output to windows, etc.		*/

#ifdef putchar
#undef putchar
#endif
#define putchar acis_putchar

#ifdef putc
#undef putc
#endif
#define putc    acis_putc

#ifdef fputc
#undef fputc
#endif
#define fputc   acis_putc

#ifdef printf
#undef printf
#endif
#define printf  acis_printf

#ifdef fprintf
#undef fprintf
#endif
#define fprintf acis_fprintf

#ifdef vfprintf
#undef vfprintf
#endif
#define vfprintf acis_vfprintf

#ifdef fwrite
#undef fwrite
#endif
#define fwrite  acis_fwrite

#ifdef fflush
#undef fflush
#endif
#define fflush  acis_fflush

/* Redefine input functions so we can get input from windows, etc.			*/

#ifdef getchar
#undef getchar
#endif
#define getchar    acis_getchar

#ifdef getc
#undef getc
#endif
#define getc    acis_getc

#ifdef ungetc
#undef ungetc
#endif
#define ungetc  acis_ungetc

#ifdef feof
#undef feof
#endif
#define feof acis_feof

#ifdef ferror
#undef ferror
#endif
#define ferror acis_ferror

#ifdef clearerr
#undef clearerr
#endif
#define clearerr acis_clearerr

#endif

#endif /* #ifdef _MK_FWNAME_ */

/* Declare the redirection variables and functions.							*/

#ifdef __cplusplus
extern "C" {
#endif

DECL_BASE void acis_exit( int status );
DECL_BASE int acis_putchar( int c );
DECL_BASE int acis_putc(int c, FILE *fp );
DECL_BASE int acis_printf( const char *format, ...);
DECL_BASE int acis_fprintf( FILE *fp, const char *format, ...);
DECL_BASE int acis_vfprintf( FILE *fp, const char *format, va_list ap );
DECL_BASE int acis_fwrite(const void *SPAptr, int size, int nitems, FILE *fp);
DECL_BASE int acis_vsnprintf( char * target_buffer, int target_buffer_len, const char *format, va_list ap);

DECL_BASE int acis_fflush( FILE *fp );
DECL_BASE int acis_getchar();
DECL_BASE int acis_getc(FILE*);
DECL_BASE int acis_ungetc(int, FILE*);
DECL_BASE int acis_feof(FILE*);
DECL_BASE int acis_ferror(FILE*);
DECL_BASE void acis_clearerr(FILE*);

/**
 * Opens the file whose name is specified in the parameter filename and associates it 
 * with a stream that can be identified in future operations by the FILE pointer returned.
 * <br><br>
 * @param filename
 * name of the input file.
 * @param mode
 * denotes the file access mode.
 */
DECL_BASE FILE* acis_fopen( const char *filename, const char *mode );

/**
* Closes the file associated with the stream
* <br><br>
* @param stream
* Pointer to a FILE object that specifies the stream to be closed.
*/
DECL_BASE int acis_fclose( FILE *stream );

#ifdef _MSC_VER
#ifdef __cplusplus
/**
 * The wfopen function opens the file whose name is the wide character string pointed to by path
 * and associates a stream with it.
 * <br><br>
 * @param filename
 * name of the input file.
 * @param mode
 * denotes the file access mode.
 */

DECL_BASE FILE* acis_wfopen( const SPAWCHAR_T* filename, const SPAWCHAR_T* mode);
#endif
#endif

#ifdef __cplusplus
}
#endif

#ifdef _M_AMD64
# define acis_stat _stat64
# define acis_fstat _fstat64
# define acis_stat_struct struct __stat64
#else
# define acis_stat stat
# define acis_fstat fstat
# define acis_stat_struct struct stat
#endif

#endif
