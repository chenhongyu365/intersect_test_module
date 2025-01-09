#ifndef _CATANSIFSTREAM_H
#define _CATANSIFSTREAM_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */


#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "ios.h"
#include "istream.h"
#include <fstream>
#pragma warning(pop)

using std::filebuf;
using std::ifstream;
using std::ofstream;
using std::fstream;

#endif
