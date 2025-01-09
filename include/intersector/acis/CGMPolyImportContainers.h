/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportContainers_H
#define CGMPolyImportContainers_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMCheckAnomaly.h"
#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"

namespace CGMPolyImport
{
typedef CATCGMCheckAnomaly Anomaly;

/** @nodoc */
template <typename T> class ContainerImpl;

/** @nodoc */
template <typename T> class IteratorImpl;

} // namespace CGMPolyImport
#endif
