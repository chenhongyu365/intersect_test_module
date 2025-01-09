#ifndef CATMshMDataIntersectingEntities_H
#define CATMshMDataIntersectingEntities_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshMDataIntersectingEntities.h
// Define the CATMshMDataIntersectingEntities object : define intersecting 
// entities of a mesh
//
//=============================================================================

#include "CATIMshMesh.h"
#include "CATIMshDataOnMesh.h"
#include <map>

/**
 * classe use to store entities of a CATIMshMesh that are intersecting.
 */
class ExportedByCATMshMesherCore CATMshMDataIntersectingEntities : public CATIMshDataOnMesh
{

public:

  /**
  * Constructeur
  */
  CATMshMDataIntersectingEntities();

  /**
  * Destructeur
  */
  virtual ~CATMshMDataIntersectingEntities();
	
	/**
	* Provide the mesh on which the attached data are specified.
	* @param iMsh
	*   The working CATIMesh
	* @return
	*   An HRESULT.
	*/
	HRESULT SetMesh (CATIMshMesh *iMsh);

  /**
  * Returns the type of a CATIMshDataOnMesh.
  * @return
  *   The type of the current CATIMshDataOnMesh object.
  */
  CATMshDataOnMeshType Type() { return IntersectingEntitiesOnMeshType; };

  /**
  * Set a mesh element to be frozen : it should be kept in the resulting mesh (while potentially renumbered)
  * @param iElem
  *   The CATIndex of the frozen mesh element
  * @return
  *   An HRESULT.
  */
  HRESULT SetIntersectingMeshElement(CATMshElementIndex &iElem);

  /**
  * Ask whether a given mesh element is frozen
  * @param iElem
  *   The CATIndex of the mesh element for which the request is done
    * @return
    *   A boolean.
    *   <br><b>Legal values</b>:
    *   <dl><dt>true</dt><dd>The mesh element is frozen
    *   <dt>false</dt><dd>The mesh element is not frozen
    *   </dl>
  */
  bool MeshElementIsIntersecting(CATMshElementIndex &iElem);

private:

  /* Constructeur recopie */
  CATMshMDataIntersectingEntities(const CATMshMDataIntersectingEntities & Source);

  /* Operateur d'affectation */
  CATMshMDataIntersectingEntities& operator=(const CATMshMDataIntersectingEntities & Source);

  CATIMshMesh *_WorkingMesh;

  std::map<unsigned int, int> _Intersecting;
  std::map<unsigned int, int>::iterator _Iterator;

};

#endif
