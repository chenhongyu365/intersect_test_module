/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpRemeshByVoxel_H
#define CGMPolyOpRemeshByVoxel_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"
namespace CGMPolyImport
{
/**
 * Reconstructs the polyhedral mesh geometry using a voxel approximation of the
 * input mesh. The input to this operator is required to be watertight or
 * approximately so (i.e., with gaps less than the voxel size).
 * @see Operator
 */
class ExportedByCGMCompPoly RemeshByVoxel : public Operator
{
public:
  /**
   * Creates a <tt>RemeshByVoxel</tt> operator.
   * @param iMesh
   *	The mesh to be operated on.
   * @return
   *	The <tt>RemeshByVoxel</tt> operator.
   */
  static RemeshByVoxel *Create(Mesh const &iMesh);

  /**
   * Specifies The number of voxels to be allocated.
   * The level of detail is defined on a logarithmic scale, with recommended
   *values between 6 and 12. A value near 6 will yield a lightweight but
   *coarsely approximated result, while a high value will maintain better
   *fidelity to the original input, but take longer and consume more memory. The
   *relationship between level of detail and (uniform) voxel size is such that
   *if the level of detail increases by 1, the voxel size decreases by a factor
   *of 2.
   * @param iLod
   *	The level of detail.
   **/
  virtual void SetLevelOfDetail(double iLod) = 0;

  /**
   * Returns the level of detail.
   * @return
   *	The level of detail.
   */
  virtual double GetLevelOfDetail() const = 0;

  /**
   * The normal tolerance is an angle used during the step of the algorithm that
   *converts voxels to triangles (a.k.a. contouring). The recommended values are
   *between 0 and 15; lower values will result in more triangles in the output
   *and better preservation of features. A value of 0 will result in no
   *simplification.  The default value is 15.
   * @param iAngleInDegrees
   *	The normal tolerance.
   **/
  virtual void SetNormalTolerance(double iAngleInDegrees) = 0;

  /**
   * Returns the normal tolerance used during the contouring step of the
   *algorithm.
   * @return
   *	The normal tolerance.
   */
  virtual double GetNormalTolerance() const = 0;

  /**
   * Returns the internal voxel size used at the current level of detail.
   * @return
   *	The voxel size.
   */
  virtual double GetVoxelSize() const = 0;

  /**
   * Specifies whether to fix folded-over portions in the output mesh or not.
   * @param iDoFixOverlaps
   * Whether or not to fix overlaps in the output.
   */
  virtual void SetDoFixOverlaps(bool iDoFixOverlaps) = 0;

  /**
   * Returns the toggle specifying whether or not to fix folded-over portions in
   * the output mesh.
   * @return
   * Whether or not to fix overlaps in the output.
   */
  virtual bool GetDoFixOverlaps() const = 0;

protected:
  virtual ~RemeshByVoxel() {}
  RemeshByVoxel();

private:
  RemeshByVoxel &operator=(RemeshByVoxel const &iOther);
  RemeshByVoxel(RemeshByVoxel const &iOther);
};
} // namespace CGMPolyImport
#endif
