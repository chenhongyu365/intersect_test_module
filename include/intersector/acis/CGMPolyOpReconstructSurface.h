/*******************************************************************/
/*    Copyright (c) 2016-2024 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyOpReconstructSurface_H
#define CGMPolyOpReconstructSurface_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 **/

#include "CATCGMReferenceClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"

namespace CGMPolyImport
{
/**
 * This operator allows the user to: <br>
 *
 *    (1) Resurface a polyhedral mesh. <br>
 *
 *    (2) Reconstruct a surface from a list of point coordinates. <br><br>
 *
 *    (3) Reconstruct a surface from a list of point coordinates and a
 *        list of globally consistent oriented point normal vectors. <br><br>
 *
 * The output is a polyhedral surface mesh. <br><br>
 *
 * <b>A few observations about the limitations and the parameters used by
 *    this operator:</b> <br>
 *      (i) Input points are not kept in the reconstructed mesh. <br>
 *     (ii) The algorithm is very sensitive to the orientation of the normal
 *          vectors, then providing consistently oriented normal vectors is
 *          crucial to minimize artifacts and generate reasonable
 *          surfaces. <br>
 *    (iii) Globally consistent orientation of normal vectors means that
 *          all normal vectors are pointing inwards or outwards of the
 *          surface. <br>
 *     (iv) The parameter level of detail can help generating smoother
 *          surfaces but at the cost of compromising quality and fidelity. <br>
 *      (v) The parameter screening factor can help to recover open boundaries
 *          and remove innacurate extensions of the surface created during the
 *          reconstruction process. <br>
 *     (vi) Locality is a desired property when computing point normal vectors.
 *          For uniformly distributed point clouds, locality usually decreases
 *          as the number of nearest neighbors used to estimate the normal
 *          vectors increases. Notice that noisy point clouds may require
 *          decreasing locality to improve the accuracy of the
 *          calculations. <br>
 *    (vii) Non-locality is a desired property when computing the globally
 *          consistent orientation of the point normal vectors. In practice,
 *          it means that the number of nearest neighbors used to orient
 *          consistently normal vectors is usually larger than the one used
 *          to compute them. <br><br>
 *
 * @see Operator <br>
 **/
class ExportedByCGMCompPoly ReconstructSurface : public Operator
{
public:
  /**
   * Creates a <tt>ReconstructSurface</tt> operator to resurface
   * an input polyhedral mesh. <br>
   * The operator uses the points and oriented point normal vectors from
   * the input mesh to perform the calculations. <br>
   *
   * @param iMesh <br>
   *	The mesh to be operated on. <br>
   * @return <br>
   *	A pointer to the <tt>ReconstructSurface</tt> operator that needs
   *  to be released. <br>
   **/
  static ReconstructSurface *Create(Mesh &iMesh);

  /**
   * Creates a <tt>ReconstructSurface</tt> operator to reconstruct a surface
   * from a list of point coordinates. <br>
   * Globally consistent oriented point normal vectors are estimated internally
   * by the operator. <br>
   *
   * @param iNbPts <br>
   *  The number of points.
   *  Notice that <tt>iNbPts</tt> is NOT the length of <tt>iPoints</tt> buffer,
   *  which must be <tt>3*iNbPts</tt> as we are operating on a 3D space. <br>
   * @param iPoints <br>
   *  A pointer to the buffer containing the list of point coordinates. The
   *  length of this buffer must be <tt>3*iNbPts</tt>. <br>
   * @param iKnnToComputeNormals <br>
   *  Number of nearest neighbors used to estimate each point normal, i.e. the
   *  normal of the plane tangent to the surface at a given point. Calculations
   *  become more expensive as the value increases. Smallest values increase
   *  locality (desired property when computing normal vectors) but can lead
   *  to innacurate estimations for noisy point clouds.
   *  Value must be larger than or equal to 3 (DEFAULT is 10). <br>
   * @param iKnnToOrientNormals <br>
   *  Number of nearest neighbors used to estimate the globally consistent
   *  orientation of normal vectors. The value is usually larger than
   *  <tt>iKnnToComputeNormals</tt> as non-locality is a desired property
   *  for calculations. Computational cost increases as the number of
   *  nearest neighbors increases. Notice that globally consistent orientation
   *  of normal vectors is crucial to minimize artifacts in the reconstructed
   *  surface.
   *  Value must be larger than or equal to 3 (DEFAULT is 20). <br>
   * @return <br>
   *	A pointer to the <tt>ReconstructSurface</tt> operator that needs
   *  to be released. <br>
   **/
  static ReconstructSurface *Create(int iNbPts,
                                    double *iPoints,
                                    int iKnnToComputeNormals = 10,
                                    int iKnnToOrientNormals = 20);

  /**
   * Creates a <tt>ReconstructSurface</tt> operator to reconstruct a surface
   * from two input buffers, one containing a list of point coordinates and
   * the other a list of oriented normal vectors (one for each point). <br>
   *
   * @param iNbPts <br>
   *  The number of points and oriented point normal vectors.
   *  Notice that <tt>iNbPts</tt> is NOT the length of the input buffers,
   *  which must be <tt>3*iNbPts</tt> as we are operating on a 3D space. <br>
   * @param iPoints <br>
   *  A pointer to the buffer containing the list of point coordinates. The
   *  length of this buffer must be 3<tt>iNbPts</tt>. <br>
   * @param iOrientedNormals <br>
   *  A pointer to the buffer containing the list of globally consistent
   *  oriented normal vectors (one for each point). The length of this
   *  buffer must be 3<tt>iNbPts</tt>. <br>
   * @return <br>
   *	A pointer to the <tt>ReconstructSurface</tt> operator that needs
   *  to be released. <br>
   **/
  static ReconstructSurface *
  Create(int iNbPts, double *iPoints, double *iOrientedNormals);

  /**
   * Sets the level of detail. <br>
   * This parameter is an indicator of the spatial resolution used to
   * reconstruct the surface. <br>
   * More details are captured as the level increases, but computational
   * cost is also more expensive. <br>
   * Decreasing the level of detail acts as a low-pass filter and denoises
   * the point cloud, but quality and accuracy of the reconstruction can
   * be compromised in the process. <br>
   *
   * @param iLevelOfDetail specifies the level of detail. <br>
   *        Value must be between 3 and 20 (DEFAULT is 9). <br>
   **/
  virtual void SetLevelOfDetail(int iLevelOfDetail = 9) = 0;

  /**
   * Sets the screening factor. <br>
   * This parameter allows filtering out triangles from the reconstructed
   * surface mesh. <br>
   * The number of removed triangles increases as the value tends to one.
   * No triangles are filtered out when the value is zero and no mesh is
   * created if the value is one. <br>
   * The screening factor parameter internally uses the point density to 
   * determine which triangles are removed. The relationship between the 
   * value of the parameter and the number of triangles removed is not 
   * linear. <br>
   * Increasing the value of the parameter could help to recover open
   * boundaries and to remove inaccurate extensions of the surface added
   * during the reconstruction process. <br>
   *
   * @param iScreeningFactor specifies the screening factor. <br>
   *        Value must be between 0 and 1 (DEFAULT is 0). <br>
   **/
  virtual void SetScreeningFactor(double iScreeningFactor = 0.) = 0;

protected:
  virtual ~ReconstructSurface() {}
  ReconstructSurface();

public:
  ReconstructSurface &operator=(ReconstructSurface const &iOther) = delete;
  ReconstructSurface(ReconstructSurface const &iOther) = delete;
};
} // namespace CGMPolyImport
#endif
