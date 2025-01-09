#ifndef CATMshCSMCommon_h
#define CATMshCSMCommon_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshCSMCommon :
// CSM surface meshing component
//
//=============================================================================

#include "CATMshCSMCommonExport.h"

#include "CATMshCSMCommonLite.h"
#include "CATIMshSpec.h"
#include "CATMshThreads.h"

class CATIMshMesh;
class CATIMshSurfaceMesher;
class CATMshMeshAssociativity;
class CATIMshDataOnMesh;

class ExportedByCATMshCSMCommon CATMshCSMCommon : public CATMshCSMCommonLite
{

public:

  /**
  * Set the callback to be called by the CSM on thread creation.
  * @param iCallback (in)
  *   The callback
  * @param iUserData (in)
  *   The user data pointer to be provided as argument to the iCallback callback.
  * @return
  *   an error code
  */
  virtual HRESULT SetStartThreadCallback(CATMshStartThreadCB iCallback, void *iUserData);

  /**
  * Set the callback to be called by the CSM on thread deletion.
  * @param iCallback (in)
  *   The callback
  * @param iUserData (in)
  *   The user data pointer to be provided as argument to the iCallback callback.
  * @return
  *   an error code
  */
  virtual HRESULT SetStopThreadCallback(CATMshStopThreadCB iCallback, void *iUserData);
  
  /**
  * Generate the mesh
  * @return
  *   an error code
  */
  virtual HRESULT Mesh();

  /**
  * Create a new local specification, and add it in the mesher
  * @param iSpecType (in)
  *   The specification type requested
  * @return
  *   The corresponding local specification, or nullptr if the type is not handled by the mesher.
  */
  virtual CATIMshSpec * CreateLocalSpecification(CATMshSpecType iSpecType);  

  /**
  * Get the CAD / mesh associativity of the generated mesh
  * @return
  *   The CAD / mesh associativity, or nullptr if an error occurs, or if the MeshAssociativity is not available.
  */
  virtual CATMshMeshAssociativity * GetMeshAssociativity();

  /**
  * Get some information on the generated surface mesh.
  * @param iDataType (in)
  *   The type of data requested
  * @return
  *   The corresponding data on mesh, or nullptr if the type is not handled by the mesher.
  */
  virtual CATIMshDataOnMesh * GetDataOnMesh(CATMshDataOnMeshType iDataType);

protected:

  /* Constructeur */
  CATMshCSMCommon();

  /* Destructeur */
  virtual ~CATMshCSMCommon();

  virtual HRESULT InitializeMesher();

private:
  
  CATMshStartThreadCB _StartThreadsCB;
  void *_StartThreadsCBUserData;

  CATMshStopThreadCB _StopThreadsCB;
  void *_StopThreadsCBUserData;

  CATIMshSpec **_Specs;

  int _SpecCount;
  int _SpecCountMax;

};

#endif
