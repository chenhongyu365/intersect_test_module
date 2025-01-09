/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpSeparate_H
#define CGMPolyOpSeparate_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
/**
 * Identitfies the connected components of the input mesh and creates a separate
 * mesh for each component.
 * @see CGMPolyImportPart::Operator
 */
class ExportedByCGMCompPoly Separate : public Operator
{
public:
  /**
   * Creates a <tt>Separate</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @return
   *	The <tt>Separate</tt> operator.
   */
  static Separate *Create(Mesh const &iMesh);

protected:
  virtual ~Separate() {}
  Separate();

private:
  Separate &operator=(Separate const &iOther);
  Separate(Separate const &iOther);
};
} // namespace CGMPolyImport

#endif
