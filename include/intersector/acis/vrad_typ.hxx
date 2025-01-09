/* ORIGINAL: abl2.1/scmext/scmext/vrad_typ.hxx */
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
//    Declare procedures for working with var_radius objects in scheme
//
//----------------------------------------------------------------------

#ifndef vrad_typ_hxx
#define vrad_typ_hxx

//======================================================================

#include "scheme.hxx"
#include "logical.h"

class var_radius;

//======================================================================

logical is_Scm_Vradius(ScmObject);
var_radius* get_Scm_Vradius(ScmObject);
ScmObject make_Scm_Vradius(var_radius*);
//======================================================================
#endif




