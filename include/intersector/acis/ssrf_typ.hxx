/* ORIGINAL: 3dt2.1/scheme/ssrf_typ.hxx */
// $Id: ssrf_typ.hxx,v 1.3 2000/12/26 18:31:01 products Exp $
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
//    Define scheme spline surface data type
//
//----------------------------------------------------------------------

#ifndef ssrf_typ_hxx
#define ssrf_typ_hxx

#include "scheme.hxx"

#include "splsurf.hxx"

//======================================================================

logical     is_Scm_Splsurf(ScmObject s);
splsurf   *get_Scm_Splsurf(ScmObject scmsurf);
ScmObject make_Scm_Splsurf(splsurf   *surf);

//======================================================================
#endif
