#ifndef CATIMshSpec_H
#define CATIMshSpec_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U3
 */
//=============================================================================
//
// CATIMshSpec.h
// Define the CATIMshSpec interface : an interface that is used to define
// any local behavior a meshing component may want to obey
//
//=============================================================================

#include "ExportedByCATMshMesherCore.h"
#include "CATMshBase.h"
#include "CATIMshMesh.h"
#include "CATSysErrorDef.h"
#include "CATIMshDataOnMesh.h"
#include "CATIMshComplexData.h"

#include <string>

/**
 * Type that reprensents the type of a CATIMshSpec.
 */
typedef enum CATMshSpecType_ {
  UnknownSpecType = 0,
  LocalSizeSpecType = 1,
  BoundaryLayerSpecType = 2,
  MeshMatchingSpecType = 3,
  RequiredEntitiesSpecType = 4,
  PatchIndependentSpecType = 5,
  LineDistributionSpecType = 6,
  EntitiesPropertySpecType = 7,
  LocalTypeSpecType = 8,
}CATMshSpecType;


/**
 * Interface representing a user mesh specification.
 * <b>Role</b>: This interface provides all necessary informations about a
 * mesh specification.
 * <b>Some rules</b>: 
 *    - As many specification as needed can be created for a meshing session,
 *    - Once the support of a specification has been set, it cannot be modified,
 *    - Only one type of support for a specifications (a single call to SetSupport),
 *    - The information provided in the specifictions have a higher priority than any 
 *    other information provided as a global parameter.
 */
class ExportedByCATMshMesherCore CATIMshSpec: public CATMshBase
{

public:

  /**
  * Sets the support of the specification.
  * Case of a specification on a CATIMshMesh
  * @param iMsh
  *   The mesh on which the specification is applied.
  * @return
  *   An HRESULT.
  */
  virtual HRESULT SetSupport(CATIMshMesh *iMsh) = 0;

  /**
  * Sets the support of the specification. 
  * In this case, the support is the whole 3D domain.
  * @return
  *   An HRESULT.
  */
  virtual HRESULT SetSupport() = 0;

  /**
  * Sets the support of the specification. It corresponds here to parts of an 
  * analytical or discrete CAD, define by their topological IDs.
  * @param iSize
  *   The number of topological IDs that compose the support of the specification.
  * @param iTopoIDs
  *   An array of size iSize of topological ID on which the specification is applied.
  *   For a CATBody it corresponds to the PersistentTag of the topological CAT entities
  *   For a cad_t it corresponds to cad entity id
  *   For a CATIMshMesh it corresponds to the CATMshTag of the mesh entities
  * @param iName
  *   The name of this support (optionnal).
  * @return
  *   An HRESULT.
  */
  virtual HRESULT SetSupport(int iSize, int *iTopoIDs, const char* iName = "") = 0;
  
  /**
  * Sets the support of the specification. 
  * It corresponds here to a geometric entitiy of an analytical CAD, define by its geometric ID.
  * @param iGeomID
  *   The geometric ID on which the specification is applied.
  *   For a CATBody it corresponds to the PersistentTag of the geometric CAT entity
  *   For a cad_t it corresponds to cad entity uid
  *   For a CATIMshMesh it is not relevant
  * @return
  *   An HRESULT.
  */
  virtual HRESULT SetSupport(int iGeomID) = 0;
  
	/**
	* Valuates a global mesh parameter to a real double value.
  * @param iName
  *   Name of the parameter.
  * @param iSize
	*   Number of double values specified.
  * @param iValue
	*   Double values array to be used for the parameter (size iSize).
  * @return
  *   An HRESULT.
  */
	virtual HRESULT SetParameter(const char* iName, int iSize, double *iValue) = 0;

	/**
	* Valuates a global mesh parameter to a integer value.
	* @param iName
	*   Name of the parameter.
  * @param iSize
  *   Number of integer values sepcified.
  * @param iValue
  *   Integer values array to be used for the parameter (size iSize).
  * @return
  *   An HRESULT.
  */
	virtual HRESULT SetParameter(const char* iName, int iSize, int *iValue) = 0;

	/**
	* Valuates a global mesh parameter to a character value.
	* @param iName
	*   Name of the parameter.
  * @param iSize
  *   Number of param values specified.
  * @param iValue
  *   String values array to be used for the parameter (size iSize).
  * @return
  *   An HRESULT.
  */
	virtual HRESULT SetParameter(const char* iName, int iSize, const char** iValue) = 0;

	/**
	* Set a complex data to the specification. It is useful to define complex 
  * expected behavior.
	* @param iComplexData
	*   The complex data specified.
  * @return
  *   An HRESULT.
  */
	virtual HRESULT SetComplexData(CATIMshComplexData * iComplexData) = 0;

	/**
  * Set a CATIMshDataOnMesh object to the specification. It requires that the 
  * support of the specification is a CATIMshMesh.
  * @param iDataOnMesh
	*   The data on mesh specified.
  * @return
  *   An HRESULT.
  */
	virtual HRESULT SetDataOnMesh(CATIMshDataOnMesh * iDataOnMesh) = 0;

	/**
	* Returns the type of the CATIMshSpec.
	* @return
	*   The type of the current specification.
	*/
	virtual CATMshSpecType Type () = 0;



  /* Get methods, should not be used : internal purpose */

  virtual CATIMshMesh * GetSupport() = 0;

  virtual int * GetSupport(const char* iName, int & oSize) = 0;

  virtual HRESULT GetSupport(int & oGeomID) = 0;

  virtual bool SupportIsAll() = 0;

  virtual HRESULT GetParameterSize(const char* iName, int & oSize) = 0;

  virtual HRESULT GetParameter(const char* iName, const char **ioValues) = 0;

  virtual HRESULT GetParameter(const char* iName, int *ioValues) = 0;

  virtual HRESULT GetParameter(const char* iName, double *ioValues) = 0;

  virtual CATIMshComplexData * GetComplexData() = 0;

  virtual CATIMshDataOnMesh * GetDataOnMesh() = 0;

};

#endif
