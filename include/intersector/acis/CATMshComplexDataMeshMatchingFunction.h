#ifndef CATMshComplexMeshMatchingFunction_H
#define CATMshComplexMeshMatchingFunction_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshComplexDataMeshMatchingFunction.h
// Define the CATMshComplexDataMeshMatchingFunction interface : specify the
// transformation between two sets of CAD entities. 
//
//=============================================================================

#include "CATMshBase.h"
#include "CATIMshComplexData.h"

/**
 * Type for functions that define a periodicity transformation between two set of faces.
 * @param iXYZ : 
 *    a double[3] array filled with the xyz coordinate of a point
 * @param oXYZImage :
 *    a double[3] array filled with the xyz coordinate of the image of xyz by the transformation
 * @param UserData :
 *    a generic user pointer
 * @return 
 *    an HRESULT
 */
typedef HRESULT (*MeshMatchingFunction_t)(double *iXYZ, double *oXYZImage, void *UserData);


/**
 * This object defines mesh matching transformation between to sets of geometric entities.
 * It is used to build CATIMshSpec of type MeshMatchingSpecType.
 */
class ExportedByCATMshMesherCore CATMshComplexDataMeshMatchingFunction : public CATIMshComplexData
{

public:

  /* Constructeur */
  CATMshComplexDataMeshMatchingFunction();

  /* Destructeur */
  ~CATMshComplexDataMeshMatchingFunction();

	/**
	* Returns the type of a CATIMshComplexData.
	* @return
	*   The type of the current specification.
	*/
  CATMshComplexDataType Type() { return MeshMatchingTransformationCDataType; };

  /**
  * Set the mesh matching transformation given by its function
  * @param iFun
  *   The mesh matching function
  * @param iUserData
  *    A generic user pointer
  * @return
  *   A HRESULT
  */
  HRESULT SetTransformationFunction(MeshMatchingFunction_t iFun, void *iUserData);

  
  /**
  * Set the mesh matching transformation given by some points.
  * An affine isometry can be fully defined by a collection of 4 non coplanar points and their images. However,
  * some transformations can be guessed with fewer information. Below is the behavior of this function depending on the
  * number of points given as parameter :
  * - one point (and its image) is provided : we suppose that the transformation is a simple translation.
  * - two points (and their images) are provided : we suppose that the transformation is a simple
  *   translation. If it is not coherent with the given coordinates, an error will occur.
  * - three points (and their images) are provided : we can determine one of the two possible affine
  *   isometries defined by these three couples of points. If the three points are colinear an error occurs.
  *   Please note that this option is adequate for flat periodic entities (plane or edges wich can
  *   be included in a plane).
  * - four points (and their images) are provided : we can determine the unique affine isometry
  *   defined by the four couples of points. If the four points are coplanar, an error occurs.
  * @param iNbSourcePoint
  *   the number of source points used to define the transformation
  * @param iSourcePoint
  *   (size 3 * iNbSourcePoint) : the xyz coordinates of the source points
  * @param iNbImagePoint
  *   the number of image points used to define the transformation
  * @param iImagePoint
  *   (size 3 * iNbImagePoint) : the xyz coordinates of the source points
  * @return
  *   A HRESULT
  */
  HRESULT SetTransformationFunctionUsingPoints(int iNbSourcePoint, double *iSourcePoint, int iNbImagePoint, double *iImagePoint);


  /**
   * @nodoc : intern usage only
   */

  int IsTransformationByPoint();
  HRESULT GetTransformationFunction(MeshMatchingFunction_t *oFun, void **oUserData);
  HRESULT GetTransformationFunctionUsingPoints(int & oNbSourcePoint, double **oSourcePoint, int & oNbImagePoint, double **oImagePoint);

private:

  /* Constructeur recopie */
  CATMshComplexDataMeshMatchingFunction(const CATMshComplexDataMeshMatchingFunction & Source);

  /* Operateur d'affectation */
  CATMshComplexDataMeshMatchingFunction& operator=(const CATMshComplexDataMeshMatchingFunction & Source);

  MeshMatchingFunction_t _Fun;
  void *_UserData;

  double *_Source;
  double *_Image;

  int _NbSource;
  int _NbImage;
  int _FunctionSet;

};

#endif
