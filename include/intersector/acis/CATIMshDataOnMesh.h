#ifndef CATIMshDataOnMesh_H
#define CATIMshDataOnMesh_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//
// CATIMshDataOnMesh.h
// Define the CATIMshDataOnMesh interface : An interface used to attach various 
// properties on mesh entities.
//
//=============================================================================

#include "CATMshBase.h"
#include "CATIMshMesh.h"
#include "ExportedByCATMshMesherCore.h"


/**
 * Type that reprensents the type of a CATIMshDataOnMesh.
 */
typedef enum CATMshDataOnMeshType_ {
  UnknownOnMeshType = 0,
  LocalSizeOnMeshType = 1,
  BoundaryLayerOnMeshType = 2,
  MeshMatchingOnMeshType = 3,
  InternalEdgeOnMeshType = 4,
  RequiredEntitiesOnMeshType = 5,
  IntersectingEntitiesOnMeshType = 6,
}CATMshDataOnMeshType;


/**
 * Interface use to store data and information relative to a CATIMshMesh.
 * <b>Role</b>: This interface provides all necessary informations about a data on mesh.
 * It can be returned by @href CATMshCSMCommon#GetDataOnMesh, or set to a CATIMshSpec with 
 * @href CATIMshSpec#SetDataOnMesh
 */
class ExportedByCATMshMesherCore CATIMshDataOnMesh : public CATMshBase
{

public:
	
	/**
	* Provide the mesh on which the attached data are specified.
	* @param iMsh
	*   The working CATIMshMesh
	* @return
	*   An HRESULT.
	*   <br><b>Legal values</b>:
	*   <dl><dt>S_OK</dt><dd>The Compute is OK.
	*   <dt>E_FAIL</dt><dd>The Compute failed.
	*   </dl>
	*/
	virtual HRESULT SetMesh (CATIMshMesh *iMsh) = 0;

  /**
  * Returns the type of a CATIMshDataOnMesh.
  * @return
  *   The type of the current DataOnMesh object.
  */
  virtual CATMshDataOnMeshType Type() = 0;

};

#endif
