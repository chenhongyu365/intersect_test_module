#ifndef CATMshComplex3DSizingFunction_H
#define CATMshComplex3DSizingFunction_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//=============================================================================
//
// CATMshComplexData3DSizingFunction.h
// Define the CATMshComplexData3DSizingFunction interface : specify a 3D
// sizing function to be respected by the mesher
//
//=============================================================================

#include "CATIMshComplexData.h"
#include "CATMshBase.h"

/**
 * Type for functions that define isometric sizemap at a specific 3d space point
 * @param iXYZ :
 *    the coordinates of the point we are querying a size for
 * @param oSize :
 *    the associated size.
 * @param iUserData :
 *    a generic user pointer
 * @return
 *    an HRESULT
 */
typedef HRESULT (*SizingFunction3DIso)(double* iXYZ, double& oSize, void* iUserData);

/**
 * Type for functions that define anisotropic sizemap at a specific 3d space point
 * @param iXYZ :
 *    the coordinates of the point we are querying a size for
 * @param oSize :
 *    the associated metric (6 double array).
 * @param iUserData :
 *    a generic user pointer
 * @return
 *    an HRESULT
 */
typedef HRESULT (*SizingFunction3DAniso)(double* iXYZ, double* met, void* iUserData);

/**
 * This object defines callback function to specify a size in the 3D space. It is used to build
 * some CATIMshSpec of type LocalSizeSpecType.
 */
class ExportedByCATMshMesherCore CATMshComplexData3DSizingFunction : public CATIMshComplexData {
  public:
    /* Constructeur */
    CATMshComplexData3DSizingFunction();

    /* Destructeur */
    ~CATMshComplexData3DSizingFunction();

    /**
     * Returns the type of a CATIMshComplexData.
     * @return
     *   The type of the current specification.
     */
    CATMshComplexDataType Type() { return XYZSizingFunctionCDataType; };

    /**
     * Set the 3d sizing function for isotropic case.
     * @param iFun
     *   The 3d sizing function
     * @param iUserData
     *    A generic user pointer
     * @return
     *   A HRESULT
     */
    HRESULT SetSizingFunctionIso(SizingFunction3DIso iFun, void* iUserData);

    /**
     * Set the 3d sizing function for anisotropic case.
     * @param iFun
     *   The 3d sizing function
     * @param iUserData
     *    A generic user pointer
     * @return
     *   A HRESULT
     */
    HRESULT SetSizingFunctionAniso(SizingFunction3DAniso iFun, void* iUserData);

    /**
     * @nodoc : intern usage only
     */

    HRESULT GetSizingFunctionIso(SizingFunction3DIso* oFun, void** oUserData);
    HRESULT GetSizingFunctionAniso(SizingFunction3DAniso* oFun, void** oUserData);

  private:
    /* Constructeur recopie */
    CATMshComplexData3DSizingFunction(const CATMshComplexData3DSizingFunction& Source);

    /* Operateur d'affectation */
    CATMshComplexData3DSizingFunction& operator=(const CATMshComplexData3DSizingFunction& Source);

    SizingFunction3DIso _FunIso;
    SizingFunction3DAniso _FunAniso;

    void* _UserDataAniso;
    void* _UserDataIso;
};

#endif
