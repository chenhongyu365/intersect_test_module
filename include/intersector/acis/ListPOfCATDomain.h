#ifndef ListPOfCATDomain_h
#define ListPOfCATDomain_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATDomain;
/** 
 * @collection CATLISTP(CATDomain)
 * Collection class for pointers to (topological) domains.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATDomain, 10)
/** @nodoc */
typedef CATLISTP(CATDomain) ListPOfCATDomain;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of the domains of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATDomain& iToWrite);

#endif
