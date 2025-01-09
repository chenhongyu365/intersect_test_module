#ifndef ListPOfCATFace_h
#define ListPOfCATFace_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

class CATFace;
/**
 * @collection CATLISTP(CATFace)
 * Collection class for pointers to (topological) faces.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_Declare.h"
#include "CATLISTPP_PublicInterface.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATFace, 10)
/** @nodoc */
typedef CATLISTP(CATFace) ListPOfCATFace;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of the faces of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATFace& iToWrite);

#endif
