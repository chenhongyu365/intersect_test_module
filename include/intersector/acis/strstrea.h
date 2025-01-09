#ifndef _CATANSISTRSTRSTREAM_H
#define _CATANSISTRSTRSTREAM_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "iostream.h"
#include <strstream>
#pragma warning(pop)

using std::strstreambuf;
using std::istrstream;
using std::ostrstream;
using std::strstream;

#endif
