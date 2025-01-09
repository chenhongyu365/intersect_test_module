/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportGeometryContainers_H
#define CGMPolyImportGeometryContainers_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMMeshGeometry.h"

/**
 *  Namespace for all functionality related to importing meshes into a
 * <tt>CGMPart</tt>.
 */
namespace CGMPolyImport {
    class Mesh;

    typedef CGMPolyMeshTools::Triangle Triangle;
    typedef CGMPolyMeshTools::Bar Bar;
    typedef CGMPolyMeshTools::Node Node;

    /** @nodoc */
    template <typename T> class GeometryContainerImpl;

    /** @nodoc */
    template <typename T> class GeometryIteratorImpl;
}  // namespace CGMPolyImport
#endif
