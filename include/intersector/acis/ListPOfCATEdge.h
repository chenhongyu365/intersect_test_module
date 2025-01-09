#ifndef ListPOfCATEdge_h
#define ListPOfCATEdge_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATEdge;
/** 
 * @collection CATLISTP(CATEdge)
 * Collection class for pointers to (topological) edges.
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
CATLISTPP_DECLARE_TS(CATEdge, 10)
/** @nodoc */
typedef CATLISTP(CATEdge) ListPOfCATEdge;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of the edges of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATEdge& iToWrite);

#endif
