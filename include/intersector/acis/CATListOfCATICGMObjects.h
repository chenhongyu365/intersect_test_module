#ifndef CATListOfCATICGMObjects_h
#define CATListOfCATICGMObjects_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
/**
 * @collection CATLISTP(CATICGMObject)
 * Collection class for pointers to CGM objects.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_Declare.h"
#include "CATLISTPP_PublicInterface.h"
#include "YP00IMPL.h"

class CATICGMObject;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYP00IMPL

CATLISTPP_DECLARE_TS(CATICGMObject, 10)

#endif
