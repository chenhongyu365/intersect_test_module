#ifndef CATIMshComplexData_H
#define CATIMshComplexData_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */
//
// CATIMshComplexData.h
// Define the CATIMshComplexData interface : an interface used to define any
// complex information, that is transmitted to a meshing specification
//
//=============================================================================

#include "CATMshBase.h"
#include "ExportedByCATMshMesherCore.h"

/**
 * Type that reprensents the type of a complex data.
 */
typedef enum CATMshComplexDataType_ {
    UnknownCDataType = 0,
    LineDistributionCDataType = 1,
    MeshMatchingTransformationCDataType = 2,
    XYZSizingFunctionCDataType = 3,
} CATMshComplexDataType;

/**
 * Interface use to store complex data and information that can be set as argument to a meshing specification.
 * <b>Role</b>: This interface provides all necessary informations about a complex information.
 */
class ExportedByCATMshMesherCore CATIMshComplexData : public CATMshBase {
  public:
    /**
     * Returns the type of a CATIMshComplexData.
     * @return
     *   The type of the current ComplexData object.
     */
    virtual CATMshComplexDataType Type() = 0;
};

#endif
