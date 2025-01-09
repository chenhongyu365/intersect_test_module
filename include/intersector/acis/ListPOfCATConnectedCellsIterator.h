#ifndef ListPOfCATConnectedCellsIterator_h
#define ListPOfCATConnectedCellsIterator_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/** @CAA2Required */

class CATConnectedCellsIterator;
//
// clean previous functions requests
#include "CATLISTPP_Clean.h"
//
/** 
 * @collection CATLISTP(CATConnectedCellsIterator)
 * Collection class for pointers to iterators on the connected cells.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li> 
 * <li><tt>Size</tt></li>
 * <li><tt>InsertAt</tt></li> 
 * <li><tt>Locate</tt></li> 
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>RemoveAll</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
*/
#define CATLISTPP_Append
#define CATLISTPP_Size
#define CATLISTPP_ReSize
#define	CATLISTPP_AppendList
#define	CATLISTPP_InsertAt
#define	CATLISTPP_Locate
#define	CATLISTPP_RemovePosition
#define	CATLISTPP_RemoveAll
//
// generate interface of collection class
//
// get macros
#include "CATLISTPP_Declare.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
CATLISTPP_DECLARE_TS(CATConnectedCellsIterator, 10)
typedef CATLISTP(CATConnectedCellsIterator) ListPOfCATConnectedCellsIterator;
/**
 * Writes the pointers of the CATConnectedCellsIterators of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
class CATCGMOutput;
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATConnectedCellsIterator& iToWrite);

#endif
