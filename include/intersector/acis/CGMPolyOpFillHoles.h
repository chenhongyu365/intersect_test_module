/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpFillHoles_H
#define CGMPolyOpFillHoles_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"
namespace CGMPolyImport
{
/**
 * Where possible, fills holes in the input mesh using Delaunay triangulation.
 * @see Operator
 */
class ExportedByCGMCompPoly FillHoles : public Operator
{
public:
  /**
   * Creates a <tt>FillHoles</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @return
   *	The <tt>FillHoles</tt> operator.
   */
  static FillHoles *Create(Mesh const &iMesh);

  /**
   * Set intersection checking mode. If true (default) the hole will not be
   * filled if new intersections are created
   * @param doCheck
   *	Flag to determine whether intersection checking is on.
   */
  virtual void SetIntersectionChecking(bool doCheck) = 0;

protected:
  virtual ~FillHoles() {}
  FillHoles();

private:
  FillHoles &operator=(FillHoles const &iOther);
  FillHoles(FillHoles const &iOther);
};
} // namespace CGMPolyImport
#endif
