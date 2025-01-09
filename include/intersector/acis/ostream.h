#ifndef _CATANSIOSTREAM_H_
#define _CATANSIOSTREAM_H_

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "ios.h"
#include <ostream>
#pragma warning(pop)

using std::ostream;
using std::flush;
using std::endl;
using std::ends;


#endif
