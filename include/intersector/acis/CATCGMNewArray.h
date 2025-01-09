#ifndef CATCGMNewArray_H
#define CATCGMNewArray_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
// CATCGMNewArray : declaration of overloaded methods new/delete for Performance
//=============================================================================

/** @CAA2Required */ 

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "CATIAV5Level.h"

#ifndef CATCGMNewClassArrayDeclare
#define CATCGMNewClassArrayDeclare  void * operator new(size_t); void operator delete(void *) 
#endif

#endif

