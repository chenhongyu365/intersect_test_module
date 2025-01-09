#ifndef _CATANSIIOMANIP_H
#define _CATANSIIOMANIP_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "istream.h"
#include <iomanip>
#pragma warning(pop)

using std::resetiosflags;
using std::setiosflags;
using std::setbase;
using std::setfill;
using std::setprecision;
using std::setw;
using std::streamsize;


#endif

