#ifndef CATMshMDataRequiredEntities_H
#define CATMshMDataRequiredEntities_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshMDataRequiredEntities.h
// Define the CATIMshRequiredEntitiesOnMesh object : define frozen entities on a mesh
//
//=============================================================================

#include "CATIMshMesh.h"
#include "CATIMshDataOnMesh.h"
#include <map>

/**
 * Object use to store required entities on a CATIMshMesh.
 */
class ExportedByCATMshMesherCore CATMshMDataRequiredEntities : public CATIMshDataOnMesh
{

public:

  /**
 * Constructeur
 */
  CATMshMDataRequiredEntities();

  /**
   * Destructeur
   */
  virtual ~CATMshMDataRequiredEntities();
	
	/**
	* Provide the mesh on which the attached data are specified.
	* @param iMsh
	*   The working CATIMesh
	* @return
	*   An HRESULT.
	*   <br><b>Legal values</b>:
	*   <dl><dt>S_OK</dt><dd>The Compute is OK.
	*   <dt>E_FAIL</dt><dd>The Compute failed.
	*   </dl>
	*/
	HRESULT SetMesh (CATIMshMesh *iMsh);

  /**
  * Returns the type of a CATIMshDataOnMesh.
  * @return
  *   The type of the current DataOnMesh object.
  */
  CATMshDataOnMeshType Type() { return RequiredEntitiesOnMeshType; };

  /**
* Set a mesh vertex to be frozen : it should be kept in the resulting mesh (while potentially renumbered)
* @param iVtx
*   The CATMshVertexIndex of the frozen mesh vertex
* @return
*   An HRESULT.
*   <br><b>Legal values</b>:
*   <dl><dt>S_OK</dt><dd>All went fine.
*   <dt>E_FAIL</dt><dd>A problem occured.
*   </dl>
*/
  HRESULT SetRequiredMeshVertex(CATMshVertexIndex &iVtx);

  /**
  * Set a mesh element to be frozen : it should be kept in the resulting mesh (while potentially renumbered)
  * @param iElem
  *   The CATMshElementIndex of the frozen mesh element
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT SetRequiredMeshElement(CATMshElementIndex &iElem);

  /**
  * Ask whether a given mesh vertex is frozen
  * @param iVtx
  *   The CATMshVertexIndex of the mesh vertex for which the request is done
    * @return
    *   A boolean.
    *   <br><b>Legal values</b>:
    *   <dl><dt>true</dt><dd>The mesh vertex is frozen
    *   <dt>false</dt><dd>The mesh vertex is not frozen
    *   </dl>
  */
  bool MeshVertexIsRequired(CATMshVertexIndex &iVtx);

  /**
  * Ask whether a given mesh element is frozen
  * @param iElem
  *   The CATMshElementIndex of the mesh element for which the request is done
    * @return
    *   A boolean.
    *   <br><b>Legal values</b>:
    *   <dl><dt>true</dt><dd>The mesh element is frozen
    *   <dt>false</dt><dd>The mesh element is not frozen
    *   </dl>
  */
  bool MeshElementIsRequired(CATMshElementIndex &iElem);

private:

  /* Constructeur recopie */
  CATMshMDataRequiredEntities(const CATMshMDataRequiredEntities & Source);

  /* Operateur d'affectation */
  CATMshMDataRequiredEntities& operator=(const CATMshMDataRequiredEntities & Source);

  CATIMshMesh *_WorkingMesh;

  std::map<unsigned int, bool> _RequiredVertex;
  std::map<unsigned int, bool>::iterator _VertexIterator;

  std::map<unsigned int, bool> _RequiredElement;
  std::map<unsigned int, bool>::iterator _ElementIterator;

};

#endif
