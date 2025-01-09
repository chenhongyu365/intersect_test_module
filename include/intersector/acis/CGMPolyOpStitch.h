/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpStitch_H
#define CGMPolyOpStitch_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
/**
 * This operator stitches the input meshes together with the input tolerance
 * so that they form one mesh.  The output mesh may remain disconnected in
 * places where the tolerance is insufficient. Stitching within each mesh also
 * occurs, so non-watertight regions smaller than the tolerance will also be
 * stitched. The default tolerance is 0, in which case no geometry will be
 * modified.
 * @see Operator
 */
class ExportedByCGMCompPoly Stitch : public Operator
{
public:
  /**
   * Creates a <tt>Stitch</tt> operator.  Meshes must be added with the
   *<tt>AddMesh</tt> method.
   * @return
   *	The <tt>Stitch</tt> operator.
   */
  static Stitch *Create();

  /**
   * Sets the stitch tolerance.
   * @param iTol
   *	The tolerance with which to stitch.
   */
  virtual void SetTolerance(double iTol) = 0;

  /**
   * Gets the stitch tolerance.
   * @return
   *	The stitch tolerance.
   */
  virtual double GetTolerance() const = 0;

  /**
   * Adds a mesh to the <tt>Stitch</tt> operator.
   * @param iMesh
   *	A mesh to be stitched.
   */
  virtual void AddMesh(Mesh const &iMesh) = 0;

protected:
  virtual ~Stitch() {}
  Stitch();

private:
  Stitch &operator=(Stitch const &iOther);
  Stitch(Stitch const &iOther);
};
} // namespace CGMPolyImport
#endif
