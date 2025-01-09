#ifndef CATMshMDataVertexSize_H
#define CATMshMDataVertexSize_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshMDataVertexSize.h
// Define the CATMshMDataVertexSize object : define size on mesh vertices
//
//=============================================================================

#include "CATIMshMesh.h"
#include "CATIMshDataOnMesh.h"
#include <map>

/**
 * Object use to store size on the verices of a CATIMshMesh.
 */
class ExportedByCATMshMesherCore CATMshMDataVertexSize : public CATIMshDataOnMesh
{

public:

  /**
  * Constructeur
  */
  CATMshMDataVertexSize();

  /**
   * Destructeur
   */
  virtual ~CATMshMDataVertexSize();

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
  CATMshDataOnMeshType Type() { return LocalSizeOnMeshType; };

  /**
  * Set a size to a mesh vertex.
  * @param iVtx
  *   The CATIndex of the frozen mesh vertex
  * @param iSize
  *   The associated size
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT SetMeshVertexSize(CATMshVertexIndex &iVtx, double iSize);

  /**
  * Set a metric to a mesh vertex.
  * @param iVtx
  *   The CATIndex of the frozen mesh vertex
  * @param iMet
  *   The associated metric
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT SetMeshVertexMetric(CATMshVertexIndex &iVtx, double iMet[6]);

  /**
  * Get the isotropic size on a mesh vertex
  * @param iVtx
  *   The CATIndex of the mesh vertex for which the request is done
  * @param oSize
  *   The size on the mesh vertex
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT GetMeshVertexSize(CATMshVertexIndex &iVtx, double & oSize);


  /**
  * Get the anisotropic metric on a mesh vertex
  * @param iVtx
  *   The CATIndex of the mesh vertex for which the request is done
  * @param ioMet
  *   The metric on the mesh vertex (a double[6] array)
  * @return
  *   An HRESULT.
  *   <br><b>Legal values</b>:
  *   <dl><dt>S_OK</dt><dd>All went fine.
  *   <dt>E_FAIL</dt><dd>A problem occured.
  *   </dl>
  */
  HRESULT GetMeshVertexMetric(CATMshVertexIndex &iVtx, double *ioMet);

private:

  /* Constructeur recopie */
  CATMshMDataVertexSize(const CATMshMDataVertexSize & Source);

  /* Operateur d'affectation */
  CATMshMDataVertexSize& operator=(const CATMshMDataVertexSize & Source);

  std::map<unsigned int, int> _VertexIndex;
  std::map<unsigned int, int>::iterator _IndexIterator;

  std::map<unsigned int, double> _VertexSize;
  std::map<unsigned int, double>::iterator _SizeIterator;

  CATIMshMesh *_WorkingMesh;
  
  double *_Metric;

  int _CurrentIndex;
  std::size_t _VertexCount;

};

#endif
