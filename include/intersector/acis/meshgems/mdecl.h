#ifndef __MESHGEMS_MDECL_H__
#define __MESHGEMS_MDECL_H__
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
/** @CAA2Required */

#ifndef MESHGEMS_METHOD_DECL
#    include "DSYExport.h"

#    ifdef MESHGEMS_DLL_BUILD
#        define MESHGEMS_METHOD_DECL DSYExport
#    endif

#    ifdef MESHGEMS_DLL
#        define MESHGEMS_METHOD_DECL DSYImport
#    endif

#    ifdef MESHGEMS_MACOS_BUILD
#        define MESHGEMS_METHOD_DECL __attribute__((visibility("default")))
#    endif

#    ifdef MESHGEMS_LINUX_BUILD
#        define MESHGEMS_METHOD_DECL DSYExport
#    endif

#endif /* MESHGEMS_METHOD_DECL */

#ifndef MESHGEMS_METHOD_DECL
#    define MESHGEMS_METHOD_DECL
#endif /* MESHGEMS_METHOD_DECL */

/**
 * This macro allows to internally define the visibility, export/import attribute of a MeshGems API method.
 */
#define MESHGEMS_METHOD MESHGEMS_METHOD_DECL

#endif /* __MDECL_H__ */
