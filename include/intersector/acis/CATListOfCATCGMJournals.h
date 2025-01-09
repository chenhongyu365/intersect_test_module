#ifndef CATListOfCATCGMJournals_H_
#define CATListOfCATCGMJournals_H_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/** 
 * @collection CATLISTP(CATCGMJournal)
 * Collection class for pointers to CGM journals.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "YP00IMPL.h"
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATCGMJournal ;

#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByYP00IMPL

CATLISTPP_DECLARE_TS( CATCGMJournal , 10)


#endif


