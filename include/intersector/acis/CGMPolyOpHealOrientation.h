/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpHealOrientation_H
#define CGMPolyOpHealOrientation_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
/**
 * Heals badly oriented triangles on the input mesh.  Note that some meshes may
 * be non-orientable.
 * @see Operator
 */
class ExportedByCGMCompPoly HealOrientation : public Operator
{
public:
  /**
   * Creates a <tt>HealOrientation</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @return
   *	The <tt>HealOrientation</tt> operator.
   */
  static HealOrientation *Create(Mesh const &iMesh);

protected:
  virtual ~HealOrientation() {}
  HealOrientation();
  HealOrientation &operator=(HealOrientation const &iOther);
  HealOrientation(HealOrientation const &iOther);
};
} // namespace CGMPolyImport
#endif
