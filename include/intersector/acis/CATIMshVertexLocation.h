#ifndef CATIMshVertexLocation_h
#define CATIMshVertexLocation_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U3
 */
//=============================================================================
//
// CATIMshVertexLocation :
// Parametric coordinates of a Mesh vertex on an analytical CAD
//
//=============================================================================

#include "ExportedByCATMshMesherCore.h"

#include "CATMshBase.h"
#include "CATIMshMesh.h"
#include "CATSysErrorDef.h"

typedef enum CATMshVertexLocationType_ {
  VertexLocationOnVertex = 0,
  VertexLocationOnEdge = 1,
  VertexLocationOnWire = 2,
  VertexLocationOnFace = 3,
  VertexLocationOnDiscreteEdge = 4,
  VertexLocationOnDiscreteWire = 5,
  VertexLocationOnDiscreteFace = 6,
}CATMshVertexLocationType;

/**
 * Interface to get the precise location of a mesh vertex on an input analytical CAD.
 */
class ExportedByCATMshMesherCore CATIMshVertexLocation : public CATMshBase
{

public:

  /**
  * Get the underlying geometric ID of the curve on which lies this vertex location
  * @param oGeomID
  *   The geometric ID of the underlying curve.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetSupport(int & oGeomID) = 0;

  /**
  * Get the uv coordinates corresponding to this location
  * @param oUV
  *   The uv coordinates
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetParametric2DCoordinates(double oUV[2]) = 0;

  /**
  * Get the corresponding t coordinates
  * @param oT
  *   The t coordinate
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
 */
  virtual HRESULT GetParametric1DCoordinates(double & oT) = 0;

  /**
  * Get whether this location is exact or not.
  * Meaning that the coordinates of the points in the mesh exactly corresponds
  * or not to the image of this location's parametric coordinates.
  * For example, on an edge shared by two cad faces, a vertex may not have all locations exact. When exact is true,
  * it means that ( curve(t) ==  the xyz coordinates of the vertex in the output mesh)
  * @return
  *   A boolean.
  *   <br><b>Legal values</b>:
  *   <dl><dt>true</dt><dd>The location is exactly on the CAD model
  *   <dt>false</dt><dd>The location is not quite exactly on the CAD
  *   </dl>
  */
  virtual int IsExact() = 0;

  /**
  * Get the index of the element in the discrete parameterisation on which belongs the vertex
  * @param oElem
  *   The index of the input mesh element on which lies the vertex.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetSourceElement(CATMshElementIndex & oElem) = 0;

  /**
  * Get the segment of input wire discrete parametrisation on which the location lies
  * @param oV0
  *   The index of the first extremity of the segment on which lies the vertex in this discrete parametrisation
  * @param oV1
  *   The index of the second extremity of the segment on which lies the vertex in this discrete parametrisation
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetSourceEdge(CATMshVertexIndex & oV0, CATMshVertexIndex & oV1) = 0;

  /**
  * Returns the type of a CATIMshVertexLocation.
  * @return
  *   The type of the current CATIMshVertexLocation object.
  */
  virtual CATMshVertexLocationType Type() = 0;

};

#endif
