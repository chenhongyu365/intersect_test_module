#ifndef _CATANSIIOSFWD_H
#define _CATANSIIOSFWD_H

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */
#pragma warning(push)
/* Disable W4530 : C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc */
#pragma warning(disable : 4530)
#pragma warning(disable : 4577)
#include <iosfwd>
#pragma warning(pop)

using std::filebuf;
using std::fstream;
using std::ifstream;
using std::ios;
using std::iostream;
using std::istream;
using std::istringstream;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::streambuf;
using std::stringbuf;
using std::stringstream;

// For classes that are not defined in iosfwd
namespace std {
    class strstreambuf;
    class istrstream;
    class ostrstream;
    class strstream;
}  // namespace std
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::strstreambuf;

#endif
