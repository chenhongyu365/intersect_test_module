// $Id: initkern.hxx,v 1.5 2000/12/26 18:48:24 products Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#if !defined(INIT_ASM_HXX)
#define INIT_ASM_HXX

#include "dcl_asm.h"
#include "logical.h"

DECL_ASM logical initialize_assembly_modeling();
DECL_ASM logical terminate_assembly_modeling();

#endif