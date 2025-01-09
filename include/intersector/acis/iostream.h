#ifndef _CATANSIIOSTREAM_H
#define _CATANSIIOSTREAM_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include "istream.h"
#include <iostream>
#pragma warning(pop)

using std::cin;
using std::cout;
using std::cerr;
using std::clog;

#endif
