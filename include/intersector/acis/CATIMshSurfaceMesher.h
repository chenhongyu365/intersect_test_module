#ifndef CATIMshSurfaceMesher_h
#define CATIMshSurfaceMesher_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U4
 */
//=============================================================================
//
// CATIMshSurfaceMesher :
// Interface to handle a surface mesher
//
//=============================================================================

#include "CATMshCSMCommonExport.h"

extern "C" {
#include <meshgems/meshgems.h>
}

#include "CATMshBase.h"
#include "CATMshMessage.h"
#include "CATMshInterrupt.h"
#include "CATMshThreads.h"
#include "CATIMshSpec.h"
#include "CATIMshDataOnMesh.h"

class CATIMshMesh;
class CATBody;
class CATMshCSMParameters;
class CATMshMeshAssociativity;

class ExportedByCATMshCSMCommon CATIMshSurfaceMesher : public CATMshBase
{

public:

  /**
  * Sets the support to be meshed - case of a discrete CAD
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetSupport(CATIMshMesh *iMesh) = 0;

  /**
  * Sets the support to be meshed - case of a MeshGems cad_t
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetSupport(cad_t *iCad) = 0;

  /**
  * Sets the support to be meshed - case of a CATBody
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetSupport(int iBodyCount, CATBody **iBodies) = 0;


  /**
  * Set all the CSM parameters to the surface mesher
  * @param iParam
  *   The CATMshCSMParameters object corresponding to the global parameters of CSM.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetParameters(CATMshCSMParameters *iParam) = 0;


  /**
  * Set the interrupt callback function.
  * @param iCallback (in)
  *   The interrupt callback (or nullptr to remove any previous callback)
  * @param iUserData (in)
  *   The user pointer which will be given to iCallback as a parameter
  */
  virtual HRESULT SetInterruptCallback(CATMshInterruptCB iCallback, void *iUserData) = 0;

  /**
  * Set the message callback function.
  * @param iCallback (in)
  *   The message callback (or nullptr to remove any previous callback)
  * @param iUserData (in)
  *   The user pointer which will be given to iCallback as a parameter
  * @return an error code
  */
  virtual HRESULT SetMessageCallback(CATMshMessageCB iCallback, void *iUserData) = 0;


  /**
  * Set the callback to be called by the cadsurf_session on thread creation.
  * @param iCallback (in)
*   The callback
  * @param iUserData (in)
*   The user data pointer to be provided as argument to the iCallback callback.
  */
  virtual HRESULT SetStartThreadCallback(CATMshStartThreadCB iCallback, void *iUserData) = 0;

  /**
    * Set the callback to be called by the cadsurf_session on thread deletion.
    * @param iCallback (in)
  *   The callback
    * @param iUserData (in)
  *   The user data pointer to be provided as argument to the iCallback callback.
    */
  virtual HRESULT SetStopThreadCallback(CATMshStopThreadCB iCallback, void *iUserData) = 0;


  /**
    * Set the list of local specification to the mesher
    * @param iCount (in)
  *   The specification count
    * @param iSpec (in)
  *   An array of specification
  * @return an error code
    */
  virtual HRESULT SetLocalSpecification(int iCount, CATIMshSpec **iSpec) = 0;


  /**
   * Generate the mesh
   */
  virtual HRESULT Mesh() = 0;


  /**
   * Returns the mesh generated
   */
  virtual CATIMshMesh * GetMesh() = 0;


  /**
    * Get the CAD / mesh associativity of the generated mesh
  * @return
    *   The CAD / mesh associativity, or nullptr if an error occurs, or if the MeshAssociativity is not available.
    */
  virtual CATMshMeshAssociativity * GetMeshAssociativity() = 0;


  /**
    * Get some information on the generated surface mesh.
    * @param iDataType (in)
  *   The type of data requested
  * @return
    *   The corresponding data on mesh, or nullptr if the type is not handled by the mesher.
    */
  virtual CATIMshDataOnMesh * GetDataOnMesh(CATMshDataOnMeshType iDataType) = 0;

};

#endif
