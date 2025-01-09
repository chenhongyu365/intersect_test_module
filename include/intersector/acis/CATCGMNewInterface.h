#ifndef CATCGMNewInterface_H
#define CATCGMNewInterface_H

/** @CAA2Required */

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
// CATCGMNewInterface
//=============================================================================

/**
 * Interface defining overloading of new and delete for performance optimization.
 * Do not use nor modify it.
 */
#include "CATCGMNewArray.h"
#include "CATCGMBOAObject.h"

#ifndef CATCGMBOAObject 
#define CATCGMCompactObject
#endif


class CATCGMCompactObjectImplement;


#define CATNewInterfaceDeclareBASIC \
CATCGMNewClassArrayDeclare;         \
virtual CATBaseUnknown * __stdcall GetImpl(int iFlag = 0) const;  \
virtual int                        IsNull() const

#if defined ( CATCGMCompactObject ) 

#if defined ( _WINDOWS_SOURCE )
#define CATCGMCompactObjectwithDelete
#else
#undef  CATCGMCompactObjectwithDelete
#endif


#if defined ( CATCGMCompactObjectwithDelete )
#define CATNewInterfaceDeclare \
  void * operator new    (size_t iSize,  CATCGMCompactObjectImplement * iMemoryImplementation); \
  void   operator delete (void *iBuffer, CATCGMCompactObjectImplement * iMemoryImplementation); \
  CATNewInterfaceDeclareBASIC
#else
#define CATNewInterfaceDeclare \
  void * operator new    (size_t iSize,  CATCGMCompactObjectImplement * iMemoryImplementation); \
  CATNewInterfaceDeclareBASIC
#endif

#else

#define CATNewInterfaceDeclare  CATNewInterfaceDeclareBASIC

#endif

#endif

