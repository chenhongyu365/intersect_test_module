/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpRemoveIntersectingSlivers_H
#define CGMPolyOpRemoveIntersectingSlivers_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportAnomalyContainer.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport {
    class RemoveIntersectingSliversImpl;
    /**
     * Removes sliver triangles involved in bad intersections
     */
    class ExportedByCGMCompPoly RemoveIntersectingSlivers : public Operator {
      public:
        /**
         * Creates a <tt>RemoveIntersectingSlivers</tt> operator.
         * @param iMesh
         *	The mesh to be operated on.
         * @return
         *	The <tt>RemoveIntersectingSlivers</tt> operator.
         */
        static RemoveIntersectingSlivers* Create(Mesh const& iMesh);
        /**
         * Creates a <tt>RemoveIntersectingSlivers</tt> operator.
         * @param iMesh
         *	The mesh to be operated on.
         * @param errors
         *	List of errors obtained by checking the mesh.  This is a performance
         *optimization, so that you can use the information already obtained from
         *checking.
         * @return
         *	The <tt>RemoveIntersectingSlivers</tt> operator.
         */
        static RemoveIntersectingSlivers* Create(Mesh const& iMesh, AnomalyContainer const& errors);

        /**
         * Sets the maximum deformation of the mesh from a single flip or collapse
         * move
         */
        virtual void SetTolerance(double tol) = 0;

        /**
         * @nodoc
         **/
        virtual RemoveIntersectingSliversImpl* GetImpl() = 0;

      protected:
        virtual ~RemoveIntersectingSlivers() {}
        RemoveIntersectingSlivers();

      private:
        RemoveIntersectingSlivers& operator=(RemoveIntersectingSlivers const& iOther);
        RemoveIntersectingSlivers(RemoveIntersectingSlivers const& iOther);
    };
}  // namespace CGMPolyImport

#endif
