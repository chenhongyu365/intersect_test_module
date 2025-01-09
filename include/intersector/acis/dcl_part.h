/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef DECL_PART

#if defined( __part ) || defined( __SpaACIS ) || defined( __SPAAcisDs )
#define BUILDING_LOCAL_FILE
#endif

#include "importexport.h"
#ifdef IMPORT_EXPORT_SYMBOLS
# ifdef BUILDING_LOCAL_FILE
#  define DECL_PART EXPORT_SYMBOL
# else
#  define DECL_PART IMPORT_SYMBOL
# endif
#else
# define DECL_PART
#endif

/* force link in VC++ */

#if !defined( CONCAT )
#define CONCAT2(a,b) a ## b
#define CONCAT(a,b) CONCAT2(a,b)
#endif

#ifndef SPA_NO_AUTO_LINK
# ifndef BUILDING_LOCAL_FILE
#  if defined(_MSC_VER)
#   if (defined( SPA_INTERNAL_BUILD ) && !defined ( SPAACISDS )) || defined( NOBIGLIB )
#    define spa_lib_name "part"
#   else
#    if defined( SPAACISDS )
#     define spa_lib_name "SPAAcisDs"
#    else
#     define spa_lib_name "SpaACIS"
#    endif
#   endif
#   if defined( SPA_DEBUG ) && !defined( SPA_INTERNAL_BUILD ) && !defined( SPAACISDS )
#    pragma comment( lib, CONCAT( spa_lib_name, "d.lib" ))
#   else
#    pragma comment( lib, CONCAT( spa_lib_name, ".lib" ))
#   endif
#  endif
# endif
#endif

#undef BUILDING_LOCAL_FILE
#undef spa_lib_name

#endif /* DECL_PART */
