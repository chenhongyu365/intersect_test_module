#ifndef CATMshComplexDataLineDistribution_H
#define CATMshComplexDataLineDistribution_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshComplexDataLineDistribution.h
// Define the CATMshComplexDataLineDistribution interface : specify the
// required discretisation of 1d CAD entity
//
//=============================================================================

#include "CATMshBase.h"
#include "CATIMshComplexData.h"


/**
 * This object defines and stores a line distribution. It is used to build
 * CATIMshSpec of type LineDistributionSpecType.
 */
class ExportedByCATMshMesherCore CATMshComplexDataLineDistribution : public CATIMshComplexData
{

public:

  /* Constructeur */
  CATMshComplexDataLineDistribution();

  /* Destructeur */
  ~CATMshComplexDataLineDistribution();

	/**
	* Returns the type of a CATIMshComplexData.
	* @return
	*   The type of the current specification.
	*/
  CATMshComplexDataType Type() { return LineDistributionCDataType; };

  /**
  * Set the number of vertices in this required line distribution.
  * @param iVertexCount
  *   The number of vertex to be specifiedName of the parameter.
  * @return
  *   A HRESULT
  */
  HRESULT SetNumberOfVertices(int iVertexCount);

  /**
  * Set the coordinates of the vertices composing the line distribution. The coordinates
  * have to be ordered, from the curve's start to the curve's end.
  * @param iTs
  *   An array of size iVertexCount, containing the ordered T parametric coordinates of
  *   the vertices.
  * @param iXYZs
  *   An array of size 3 * iVertexCount, containing the ordered XYZ coordinates of
  *   the vertices.
  * @return
  *   A HRESULT
  */
  HRESULT SetVerticesCoordinates(double *iTs, double *iXYZs);

  /**
  * Set the tags on the vertices of the line distribuion. These tags will be propagated in the
  * final CATIMshMesh.
  * @param iTags
  *   An array of size iVertexCount, containing the ordered tags of the vertices of 
  *   the line distribution
  * @return
  *   A HRESULT
  */
  HRESULT SetVerticesTags(int *iTags);

  /**
   * @nodoc : intern usage only
   */

  HRESULT GetNumberOfVertices(int & oVertexCount);
  HRESULT GetVerticesCoordinates(double **oTs, double **oXYZs);
  HRESULT GetVerticesTags(int ** oTags);

private:

  /* Constructeur recopie */
  CATMshComplexDataLineDistribution(const CATMshComplexDataLineDistribution & Source);

  /* Operateur d'affectation */
  CATMshComplexDataLineDistribution& operator=(const CATMshComplexDataLineDistribution & Source);

  double *_Tcoor;
  double *_XYZcoor;

  int _VertexCount;
  int *_Tags;

};

#endif
