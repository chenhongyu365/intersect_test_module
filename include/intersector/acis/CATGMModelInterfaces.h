#ifdef _STATIC_SOURCE
#    define ExportedByCATGMModelInterfaces
#elif defined __CATGMModelInterfaces

// COPYRIGHT DASSAULT SYSTEMES 2006

/** @CAA2Required */

/*---------------------------------------------------------------------*/

/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */

/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */

/*---------------------------------------------------------------------*/
#    define ExportedByCATGMModelInterfaces DSYExport
#else
#    define ExportedByCATGMModelInterfaces DSYImport
#endif
#include "DSYExport.h"
