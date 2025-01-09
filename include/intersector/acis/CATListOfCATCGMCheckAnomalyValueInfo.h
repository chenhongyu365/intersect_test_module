#ifndef CATListofCATCGMCheckAnomalyValueInfo_H
#define CATListofCATCGMCheckAnomalyValueInfo_H

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMCheckAnomalyValueInfo.h"
#include "CATLISTV_Clean.h"

// Define the appropriate export declaration
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

 
// See CATLISTV_AllFunct.h for a list of all methods that have been implemented.
// If you want full functionality, you need only include CATLISTV_AllFunct.h at this
// point. If you want a narrower interface, use some subset of the defines listed in
// CATLISTV_AllFunct.h, as in the following lines.
#define	CATLISTV_Append
#define	CATLISTV_Locate
#define	CATLISTV_RemoveValue
#define CATLISTV_RemoveAll
#define	CATLISTV_RemoveDuplicatesCount
 
#include  "CATLISTV_Declare.h"

CATLISTV_DECLARE(CATCGMCheckAnomalyValueInfo)

#endif
