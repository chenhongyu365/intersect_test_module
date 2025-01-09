/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef SPA3dPmACIS_h
#define SPA3dPmACIS_h

#ifndef DECL_SPA3dpm
#    include "importexport.h"

#    ifdef _WINDOWS_SOURCE
#        if defined(__SPA3dPmAcis) || defined(__SPA3dPmAcisDs)
#            define DECL_SPA3dpm __declspec(dllexport)
#        else
#            define DECL_SPA3dpm __declspec(dllimport)
#        endif
#    else
#        define DECL_SPA3dpm EXPORT_SYMBOL
#    endif
#endif

#endif
