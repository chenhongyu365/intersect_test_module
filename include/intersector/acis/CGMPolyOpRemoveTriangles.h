/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpRemoveTriangles_H
#define CGMPolyOpRemoveTriangles_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"
namespace CGMPolyImport
{
/**
 * Removes the input triangles from the Mesh.
 * @see Operator
 */
class ExportedByCGMCompPoly RemoveTriangles : public Operator
{
public:
  /**
   * Creates a <tt>RemoveTriangles</tt> operator.
   * @param iTriangles
   *	The triangles to be removed.
   * @return
   *	The <tt>RemoveTriangles</tt> operator.
   */
  static RemoveTriangles *Create(TriangleContainer const &iTriangles);

protected:
  virtual ~RemoveTriangles() {}
  RemoveTriangles();

private:
  RemoveTriangles &operator=(RemoveTriangles const &iOther);
  RemoveTriangles(RemoveTriangles const &iOther);
};
} // namespace CGMPolyImport
#endif
