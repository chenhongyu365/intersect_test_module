/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportHoleBoundary_H
#define CGMPolyImportHoleBoundary_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 **/

#include "CATCGMReferenceClassImplHolder.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportOperator.h"
//#include "CGMPolyImportHoleBoundaryImpl.h"

namespace CGMPolyImport
{
class HoleBoundaryImpl;

/**
 * This class represents the boundary of a mesh.  It knows which mesh
 * it cames from as well as a sequence of points and normals.
 **/
class ExportedByCGMCompPoly HoleBoundary
{

public:
  /**
   * Constructors
   **/
  HoleBoundary() = default;
  HoleBoundary(HoleBoundary const &) = default;
  HoleBoundary(HoleBoundaryImpl *impl);

  /**
   * Copy constructor and operators
   **/
  HoleBoundary &operator=(HoleBoundary const &) = default;
  bool operator!=(HoleBoundary const &other) const;
  bool operator==(HoleBoundary const &other) const;

  /**
   * Mesh to whom the boundary belongs
   **/
  Mesh GetMesh() const;

  /**
   * Get number of points (and normals) of the boundary
   **/
  int GetNumberOfPoints() const;

  /**
   * Get coordinates of the boundary points
   * Note: 0<= iWhichPoint< NumberOfPoints
   **/
  CATMathPoint GetPoint(int) const;

  /**
   * Get components of the normals to the boundary
   * Note: 0<= iWhichPoint< NumberOfPoints
   **/
  CATMathVector GetNormal(int iWhichPoint) const;

  /**
   * @nodoc. Internal use only
   **/
  HoleBoundaryImpl &GetImpl();
  /**
   * @nodoc. Internal use only
   **/
  HoleBoundaryImpl const &GetImpl() const;

private:
  CATCGMReferenceClassImplHolder _impl;
};

#include "CATLISTV_Clean.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCGMCompPoly
#define CATLISTV_Append
#include "CATLISTV_Declare.h"
CATLISTV_DECLARE(HoleBoundary)

} // namespace CGMPolyImport
#endif
