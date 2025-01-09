#ifndef CATMshMDataMeshMatching_H
#define CATMshMDataMeshMatching_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshMDataMeshMatching.h
// Define the CATMshMDataMeshMatching object : define the periodic IDs use to 
// descibe mesh matching corresponding mesh entities
//
//=============================================================================

#include "CATMshBase.h"
#include "CATIMshMesh.h"
#include "CATIMshDataOnMesh.h"
#include <map>

/**
 * Object use to store mesh matching label on the entities of a CATIMshMesh.
 */
class ExportedByCATMshMesherCore CATMshMDataMeshMatching : public CATIMshDataOnMesh
{
public:

  /**
 * Constructeur
 */
  CATMshMDataMeshMatching();

  /**
   * Destructeur
   */
  virtual ~CATMshMDataMeshMatching();

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
  HRESULT SetMesh(CATIMshMesh *iMsh);

  /**
  * Returns the type of a CATIMshDataOnMesh.
  * @return
  *   The type of the current DataOnMesh object.
  */
  CATMshDataOnMeshType Type() { return MeshMatchingOnMeshType; };

  /**
  * Set the periodic ID to a mesh vertex.
  * @param iVtx
  *   The CATIndex of the mesh vertex
  * @param iPid
  *   The associated periodic ID
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT SetMeshVertexPeriodicID(CATMshVertexIndex &iVtx, int iPid);

  /**
  * Set the periodic ID to a mesh element.
  * @param iElem
  *   The CATIndex of the mesh vertex
  * @param iPid
  *   The associated periodic ID
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT SetMeshElementPeriodicID(CATMshElementIndex &iElem, int iPid);


  /**
  * Get the periodic ID of a mesh vertex.
  * @param iVtx
  *   The CATIndex of the mesh vertex on which the Pid is required
  * @param oPid
  *   The associated periodic ID
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT GetMeshVertexPeriodicID(CATMshVertexIndex &iVtx, int & oPid);

  /**
  * Get the periodic ID to a mesh element.
  * @param iElem
  *   The CATIndex of the mesh element on which the Pid is required
  * @param oPid
  *   The associated periodic ID
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT GetMeshElementPeriodicID(CATMshElementIndex &iElem, int & oPid);

private:

  /* Constructeur recopie */
  CATMshMDataMeshMatching(const CATMshMDataMeshMatching & Source);

  /* Operateur d'affectation */
  CATMshMDataMeshMatching& operator=(const CATMshMDataMeshMatching & Source);

  CATIMshMesh *_WorkingMesh;

  std::map<unsigned int, int> _VertexPID;
  std::map<unsigned int, int>::iterator _VertexIterator;

  std::map<unsigned int, int> _ElementPID;
  std::map<unsigned int, int>::iterator _ElementIterator;

};

#endif
