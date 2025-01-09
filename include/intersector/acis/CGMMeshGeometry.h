/*******************************************************************/
/*    Copyright (c) 2015-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMMeshGeometry_DoNotUse_H
#define CGMMeshGeometry_DoNotUse_H


/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATDataType.h"
#include "CATGMModelCmpInterfaces.h"

#ifndef _WINDOWS_SOURCE
#include <values.h>
#endif

namespace CGMPolyMeshTools
{
/**
 * Class defining triangle, bar, and node handles on a CGMPolyImport::Mesh.
 *
 **/
template <int dimension> class CGMMeshGeometry
{
public:
  CGMMeshGeometry() : _index(0) {}

private:
  friend class Helpers;
  CATULONG64 _index;
  CGMMeshGeometry(CATULONG64 index) : _index(index) {}

public:
  /**
   * @nodoc
   **/
  bool operator<(CGMMeshGeometry other) const { return _index < other._index; }
  /**
   * @nodoc
   **/
  bool operator==(CGMMeshGeometry other) const
  {
    return _index == other._index;
  }
  /**
   * @nodoc
   **/
  bool operator!=(CGMMeshGeometry other) const { return !(*this == other); }
  /**
   * @nodoc
   **/
  operator CATULONG64() const { return _index; }
};

typedef CGMMeshGeometry<0> Node;
typedef CGMMeshGeometry<2> Triangle;

class Bar
{
public:
  Bar() {}

private:
  friend class Helpers;
  Bar(Node n1, Node n2) : _n1(n1), _n2(n2) {}
  Node _n1;
  Node _n2;

public:
  bool operator<(Bar const &other) const
  {
    if (_n1 < other._n1)
      return true;
    else if (other._n1 < _n1)
      return false;
    return _n2 < other._n2;
  }
  bool operator==(Bar const &other) const
  {
    return (_n1 == other._n1 && _n2 == other._n2);
  }
  bool operator!=(Bar const &other) const { return !(*this == other); }
};

} // namespace CGMPolyMeshTools

#endif
