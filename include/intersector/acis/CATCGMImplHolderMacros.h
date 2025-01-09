#ifndef CATCGMImplHolderMacros_H
#define CATCGMImplHolderMacros_H

// COPYRIGHT DASSAULT SYSTEMES 2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATThrowForNullPointer.h"

/**
 * @nodoc
 * These macros are meant for use by 'pointer-to-impl' classes that are
 * implemented using a data member of type,
 * CATCGMValueClassImplHolder (value class semantics), or
 * CATCGMReferenceClassImplHolder (reference class semantics)
 *
 * These macros will implement the two versions of the GetImpl method (const and non-const)
 *
 * Note:
 *	- The name of the data member in your class has to be _implHolder
 *	- The name of the impl class for CLASSNAME has to be CLASSNAMEImpl
 *
 */
#define DECLARE_USE_COUNTED_GET_IMPL_METHODS(CLASSNAME) \
    CLASSNAME##Impl const* GetImpl() const;             \
    CLASSNAME##Impl* GetImpl();                         \
    CLASSNAME##Impl const& GetImplRef() const;          \
    CLASSNAME##Impl& GetImplRef();

/**
 * @nodoc
 */
#define DEFINE_USE_COUNTED_GET_IMPL_METHODS(CLASSNAME)        \
    CLASSNAME##Impl const* CLASSNAME::GetImpl() const {       \
        return (CLASSNAME##Impl const*)_implHolder.GetImpl(); \
    }                                                         \
    CLASSNAME##Impl* CLASSNAME::GetImpl() {                   \
        return (CLASSNAME##Impl*)_implHolder.GetImpl();       \
    }                                                         \
    CLASSNAME##Impl const& CLASSNAME::GetImplRef() const {    \
        CLASSNAME##Impl const* pImpl = GetImpl();             \
        if(pImpl)                                             \
            return *pImpl;                                    \
        else                                                  \
            CATThrowForNullPointerReturnValue(*pImpl);        \
    }                                                         \
    CLASSNAME##Impl& CLASSNAME::GetImplRef() {                \
        CLASSNAME##Impl* pImpl = GetImpl();                   \
        if(pImpl)                                             \
            return *pImpl;                                    \
        else                                                  \
            CATThrowForNullPointerReturnValue(*pImpl);        \
    }

#endif
