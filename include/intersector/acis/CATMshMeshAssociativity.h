#ifndef CATMshMeshAssociativity_h
#define CATMshMeshAssociativity_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshMeshAssociativity :
// Object to store mesh associativity with input geometry
//
//=============================================================================

#include "ExportedByCATMshMesherCore.h"

#include "CATIMshMesh.h"
#include "CATIMshVertexLocation.h"
#include "CATIMshElementLocation.h"
#include <map>

struct CATMshVl_;
typedef struct CATMshVl_ CATMshVl;

struct CATMshFl_;
typedef struct CATMshFl_ CATMshFl;

/**
 * Object to get the location of vertex and element on an analytical CAD.
 */
class ExportedByCATMshMesherCore CATMshMeshAssociativity : public CATMshBase
{

public:

  /* Constructeur */
  CATMshMeshAssociativity(CATIMshMesh *iMsh);

  /* Destructeur */
  virtual ~CATMshMeshAssociativity();

  /**
  * Get the vertex location of a mesh vertex.
  * @param iIndex
  *   The mesh vertex index for which the locations are required.
  * @param iType
  *   The type of location requested (see CATIMshVertexLocation) for possible values.
  * @param oSize
  *   The number of location of the given type.
  * @return
  *   An array of size oSize containing all the locations.
  */
  CATIMshVertexLocation ** GetVertexLocation(CATMshVertexIndex &iIndex, CATMshVertexLocationType iType, int & oSize);

  /**
  * Get the element location of a mesh element (only triangle and quadrangle).
  * @param iIndex
  *   The mesh element index for which the locations are required.
  * @param iType
  *   The type of location requested (see CATIMshElementLocation) for possible values.
  * @param oSize
  *   The number of location of the given type.
  * @return
  *   An array of size oSize containing all the locations.
  */
  CATIMshElementLocation ** GetElementLocation(CATMshElementIndex &iIndex, CATMshElementLocationType iType, int & oSize);

protected:

  /**
  * @nodoc : intern usage only
  */

  CATIMshMesh *_iMsh;
  int _nv;
  CATMshVl *_Vl;
  int _nf;
  CATMshFl *_Fl;

  int _VIndex;
  int _EIndex;
  std::map<unsigned int, int> _Vertex2Index;
  std::map<unsigned int, int> _Element2Index;

  int _Initialized;

private:

  /* Constructeur */
  CATMshMeshAssociativity();

  /* Constructeur recopie */
  CATMshMeshAssociativity(const CATMshMeshAssociativity & Source);

  /* Operateur d'affectation */
  CATMshMeshAssociativity& operator=(const CATMshMeshAssociativity & Source);

};

#endif
