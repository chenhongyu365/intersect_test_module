/** @CAA2Required */
#if !defined(CVM_FOR_CSM)
#if defined(__CATMshCVMCore)
#define ExportedByCATMshCVMCore DSYExport
#else
#define ExportedByCATMshCVMCore DSYImport
#endif
#else
#define ExportedByCATMshCVMCore
#endif
#include "DSYExport.h"
