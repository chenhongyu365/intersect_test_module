#ifndef CATListVOfLong_h_
#define CATListVOfLong_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include <CATCollec.h>
#include <CATRCOLL_AllFunct.h>
#include <CATRCOLL_Clean.h>
//
#define CATRCOLL_ValCompare
#define CATRCOLL_ValQuickSort

#include <CATGMModelInterfaces.h>
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

#include <CATRCOLL_Declare.h>

#include "CATDataType.h"

#ifdef PLATEFORME_DS64
/**
 * Defines the collection class CATListOfLong
 *  for CATLONG32 values.
 * All the methods of values collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */
CATRCOLL_DECLARE(CATLONG32)

typedef CATRCOLL(CATLONG32) CATListOfLong;

#else
/**
 * Defines the collection class CATListOfLong
 *  for long values.
 * All the methods of values collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */
CATRCOLL_DECLARE(long)

typedef CATRCOLL(long) CATListOfLong;

#endif
////////////
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy
#endif
