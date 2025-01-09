#ifndef _CATANSISSTREAM_H_
#define _CATANSISSTREAM_H_

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "istream.h"
#include <sstream>
#pragma warning(pop)

using std::stringbuf;
using std::istringstream;
using std::ostringstream;
using std::stringstream;


//NB: Has no equivalent in the old stream library

#endif
