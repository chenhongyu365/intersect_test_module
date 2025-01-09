#ifndef CATMshCSMCommonLite_h
#define CATMshCSMCommonLite_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATEMshCSMMesher :
// CSM surface meshing component
//
//=============================================================================

#include "CATMshCSMCommonExport.h"

#include "CATIMshMesher.h"

class CATIMshMesh;
class CATIMshSurfaceMesher;
class CATMshCSMParameters;

class ExportedByCATMshCSMCommon CATMshCSMCommonLite : public CATIMshMesher
{

public:
  
  /**
  * Sets the support to be meshed - case of a discrete CAD
  * @param iMesh
  *   The input mesh.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetSupport(CATIMshMesh *iMesh);
  
  /**
  * Valuates a global mesh parameter to a real double value.
  * @param iName
  *   Name of the parameter.
  * @param iValue
  *   Real double value to be used for the parameter.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetParameter(const char* iName, double iValue);

  /**
  * Valuates a global mesh parameter to a integer value.
  * @param iName
  *   Name of the parameter.
  * @param iValue
  *   Integer value to be used for the parameter.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetParameter(const char* iName, int iValue);

  /**
  * Valuates a global mesh parameter to a character value.
  * @param iName
  *   Name of the parameter.
  * @param iValue
  *   Character value to be used for the parameter.
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>The Compute is OK.
  *   <dt>E_FAIL</dt><dd>The Compute failed.
  *   </dl>
  */
  virtual HRESULT SetParameter(const char* iName, const char* iValue);
  
  /**
  * Set the interrupt callback function.
  * @param iCallback (in)
  *   The interrupt callback (or nullptr to remove any previous callback)
  * @param iUserData (in)
  *   The user pointer which will be given to iCallback as a parameter
  * @return
  *   an error code
  */
  virtual HRESULT SetInterruptCallback(CATMshInterruptCB iCallback, void *iUserData);

  /**
  * Set the message callback function.
  * @param iCallback (in)
  *   The message callback (or nullptr to remove any previous callback)
  * @param iUserData (in) 
  *   The user pointer which will be given to iCallback as a parameter
  * @return 
  *   an error code
  */
  virtual HRESULT SetMessageCallback(CATMshMessageCB iCallback, void *iUserData);
 
  /**
   * Unlock CSM component
   */
  virtual HRESULT UnlockProduct(const char * key);
 
  /**
  * Generate the mesh
  * @return
  *   an error code
  */
  virtual HRESULT Mesh();
  
  /**
  * Returns the mesh generated
  * The CATIMshMesh can only be used until CSM is released.
  * The CATIMshMesh has to be released as well.
  * @return
  *   The generated surface mesh
  */
  virtual CATIMshMesh * GetMesh();

protected:

  /* Constructeur */
  CATMshCSMCommonLite();

  /* Destructeur */
  virtual ~CATMshCSMCommonLite();

  /* Input geometry */
  CATIMshMesh *_iMsh;
  CATIMshSurfaceMesher *_Mesher;
  CATIMshMesh *_oMsh;
  CATMshCSMParameters *_Param;

  int _Updatable;

private:

  /* Copy constructor */
  CATMshCSMCommonLite(const CATMshCSMCommonLite & Spec);

  /* Assignment operator */
  CATMshCSMCommonLite & operator = (const CATMshCSMCommonLite & Spec);

  virtual HRESULT InitializeMesher();

	CATMshInterruptCB _InterruptCB;
	void *_InterruptCBUserData;

	CATMshMessageCB _MessageCB;
	void *_MessageCBUserData;

};

#endif
