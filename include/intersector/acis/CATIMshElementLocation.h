#ifndef CATIMshElementLocation_h
#define CATIMshElementLocation_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//
// CATIMshElementLocation :
// Parametric coordinates of the vertices of a mesh element
//
//=============================================================================

#include "ExportedByCATMshMesherCore.h"

#include "CATMshBase.h"
#include "CATIMshMesh.h"
#include "CATSysErrorDef.h"

/**
 * Type that reprensents the type of element location.
 */
typedef enum CATMshElementLocationType_ {
  ElementLocationOnFace = 0,
}CATMshElementLocationType;


/**
 * Interface to get the precise location of a mesh element on an input analytical CAD.
 */
class ExportedByCATMshMesherCore CATIMshElementLocation : public CATMshBase
{

public:

  /**
  * Get the underlying geometric ID of the surface on which lies the mesh element
  * @param oGeomID
  *   The geometric ID of the underlying surface:
  *   For CATBodies input : it corresponds to the PersistentTag of underlying CATFace
  *   For cad_t input : it corresponds to unique ID of the underlying cad_face_t
  *   For CATIMshMesh input : not available
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetSupport(int & oGeomID) = 0;

  /**
  * Assess whether the location is available or not. If not, it means that the element crosses several CAD faces.
  * @return
  *   A boolean.
  *   <br><b>Legal values</b>:
  *   <dl><dt>true</dt><dd>The location is available : the element is not patch independent
  *   <dt>false</dt><dd>The location is not well defined : the element belongs to several underlying surfaces
  *   </dl>
  */
  virtual int IsAvailable() = 0;

  /**
  * Get the uv coordinates of the element's vertices
  * @param ioUVs
  *   An array of size 2 * oSize, containing the UV coordinates of the element's vertices.
  * @param oSize
  *   The number of element's vertices.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT GetVerticesParametric2DCoordinates(double *ioUVs, int & oSize) = 0;

  /**
  * Returns the type of a CATIMshVertexLocation.
  * @return
  *   The type of the current CATIMshVertexLocation object.
  */
  virtual CATMshElementLocationType Type() = 0;

};

#endif
