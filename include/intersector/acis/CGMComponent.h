/*******************************************************************/
/*    Copyright (c) 2010-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CGM APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
#ifdef __CGMComponent
#define ExportedByCGMComponent DSYExport
#else
#define ExportedByCGMComponent DSYImport
#endif
#include "DSYExport.h"

#ifndef NULL
#define NULL 0
#endif

#ifdef _MSC_VER
#include "windows.h"
#endif

#ifdef _DS_PLATEFORME_64
#ifdef _WIN64
#define PTRtoINT(SPAptr) ((int)((__int64)(SPAptr)))
#else
#define PTRtoINT(SPAptr) ((int)((long)(SPAptr)))
#endif
#else
#define PTRtoINT(SPAptr) ((int)(SPAptr))
#endif
