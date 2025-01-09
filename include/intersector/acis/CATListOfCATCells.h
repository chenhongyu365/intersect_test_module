#ifndef CATListOfCATCells_h
#define CATListOfCATCells_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

class CATCell;
/**
 * @collection CATLISTP(CATCell)
 * Collection class for pointers to (topological) cells.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */

#include "CATGMModelInterfaces.h"
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_Declare.h"
#include "CATLISTPP_PublicInterface.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATCell, 10)
/** @nodoc */
typedef CATLISTP(CATCell) ListPOfCATCell;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cells of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCell& iToWrite);

#endif
