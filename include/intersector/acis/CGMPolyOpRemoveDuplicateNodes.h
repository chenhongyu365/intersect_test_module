/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpRemoveDuplicateNodes_H
#define CGMPolyOpRemoveDuplicateNodes_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
/**
 *  Removes duplicate nodes from a mesh.
 *  @see Operator
 **/
class ExportedByCGMCompPoly RemoveDuplicateNodes : public Operator
{
public:
  /**
   * Creates a <tt>RemoveDuplicateNodes</tt> operator.
   * @param iMesh
   * The mesh to be operated on.
   * @return
   *	The <tt>RemoveDuplicateNodes</tt> operator.
   */
  static RemoveDuplicateNodes *Create(Mesh const &iMesh);

  /**
   * Sets the snap tolerance.  Two nodes within this distance are considered to
   *be duplicate.
   * @param iSnapTol
   *	The tolerance defining whether two nodes are physically the same or not.
   **/
  virtual void SetSnapTolerance(double iSnapTol) = 0;

  /**
   * Gets the snap tolerance.
   * @return
   *	The snap tolerance.
   **/
  virtual double GetSnapTolerance() const = 0;

protected:
  virtual ~RemoveDuplicateNodes() {}
  RemoveDuplicateNodes() {}

private:
  RemoveDuplicateNodes(RemoveDuplicateNodes const &other);
  RemoveDuplicateNodes &operator=(RemoveDuplicateNodes const &other);
};
} // namespace CGMPolyImport
#endif
