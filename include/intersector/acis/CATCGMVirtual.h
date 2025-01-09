#ifndef CATCGMVirtual_h
#define CATCGMVirtual_h
// COPYRIGHT DASSAULT SYSTEMES  2001
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#include "CATCGMNewArray.h"
#include "CATCGMVirtualMacros.h"
#include "CATMathematics.h"

class CATCGMVirtualMetaClass;

/**
 * Generic virtual class for geometrical modeler.
 */
class ExportedByCATMathematics CATCGMVirtual {
    CATCGMVirtualDeclareClass(CATCGMVirtual);

  public:
    /** @nodoc  */
    CATCGMNewClassArrayDeclare;

    virtual ~CATCGMVirtual();

    /** @nodoc  */
    size_t GetEstimatedMemoryBytes() const;

  protected:
    /** @nodoc  */
    virtual size_t GetDynamicMemoryBytes() const;

    /** @nodoc  */
    virtual size_t GetStaticMemoryBytes() const;
};

#endif
