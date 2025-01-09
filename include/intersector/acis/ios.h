#ifndef _CATANSIIOS_H
#define _CATANSIIOS_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable:4530) 
#include <ios>
#pragma warning(pop)

using std::ios;
using std::streamoff;
using std::streamsize;
using std::ios_base;
using std::fpos;
using std::streampos;
using std::boolalpha;
using std::noboolalpha;
using std::showbase;
using std::noshowbase;
using std::showpoint;
using std::noshowpoint;
using std::showpos;
using std::noshowpos;
using std::skipws;
using std::noskipws;
using std::unitbuf;
using std::nounitbuf;
using std::uppercase;
using std::nouppercase;
using std::internal;
using std::left;
using std::right;
using std::dec;
using std::hex;
using std::oct;
using std::fixed;
using std::scientific;
using std::streambuf;

#endif
