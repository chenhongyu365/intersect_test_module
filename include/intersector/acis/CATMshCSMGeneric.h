#ifndef CATMshCSMGeneric_h
#define CATMshCSMGeneric_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
//
// CATMshCSMGeneric :
// CSM surface meshing component
//
//=============================================================================

#include "CATMshCSMGenericExport.h"
#include "CATMshCSMCommon.h"

extern "C" {
#include <meshgems/meshgems.h>
}

class CATIMshMesh;

/**
 * The CSM generic mesher object. This mesher is able to mesh cad_t and CATIMshMesh inputs.
 * @ingroup CSMGeneric
 */
class ExportedByCATMshCSMGeneric CATMshCSMGeneric : public CATMshCSMCommon
{

public:

  /* Constructeur */
  CATMshCSMGeneric();

  /* Destructeur */
  virtual ~CATMshCSMGeneric();

  /**
  * Sets the support to be meshed - case of a discrete CAD
  * @param iMesh (in)
  *   The input mesh
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetSupport(CATIMshMesh *iMesh);

  /**
  * Sets the support to be meshed - case of a cad_t.
  * @param iCad (in)
  *   The input cad
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  HRESULT SetSupport(cad_t *iCad);
  
  /**
   * Generate the mesh
   */
  virtual HRESULT Mesh();


private:

  virtual HRESULT InitializeMesher();

	/* Input geometry */
  cad_t *_Cadt;

};

#endif
