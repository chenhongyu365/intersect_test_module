/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
//----------------------------------------------------------------------
// purpose---
//    declare procedures for working with class unstitch_options in scheme
//
//----------------------------------------------------------------------

#ifndef UNSTITCH_NM_SCM_OPTS_HXX
#define UNSTITCH_NM_SCM_OPTS_HXX

#include "logical.h"
#include "scheme.hxx"

class unstitch_nm_options;

logical is_Scm_Unstitch_nm_Opt(ScmObject);
unstitch_nm_options* get_Scm_Unstitch_nm_Opt(ScmObject);
ScmObject make_Scm_Unstitch_nm_Opt(unstitch_nm_options*);

#endif  // UNSTITCH_NM_SCM_OPTS_HXX
