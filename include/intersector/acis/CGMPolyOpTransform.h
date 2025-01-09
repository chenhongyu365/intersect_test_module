/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpTransform_H
#define CGMPolyOpTransform_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"
class CATMathTransformation;

namespace CGMPolyImport
{
/**
 * Transforms a Mesh using a <tt>CATMathTransformation</tt>
 * @see CGMPolyImportPart::Operator
 */
class ExportedByCGMCompPoly Transform : public Operator
{
public:
  /**
   * Creates a <tt>Transform</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @param iTrans
   *	The transformation.
   * @return
   *	The <tt>Transform</tt> operator.
   */
  static Transform *Create(Mesh const &iMesh,
                           CATMathTransformation const &iTrans);

protected:
  virtual ~Transform() {}
  Transform();

private:
  Transform &operator=(Transform const &iOther);
  Transform(Transform const &iOther);
};
} // namespace CGMPolyImport

#endif
