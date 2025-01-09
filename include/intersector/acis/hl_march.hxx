/* ORIGINAL: SPAblnd/PublicInterfaces/hl_march.hxx */
// Introduced in R13
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

// Prototype for holdline marching function.

//#include <stdio.h>
#include "acis.hxx"
#include "dcl_blnd.h"
#include "spa_null_base.hxx"

class ATTRIB_BLEND;
class var_blend_spl_sur;
class v_bl_contacts;
class list_of_contacts;
class SPAbox;

DECL_BLND logical holdline_march(ATTRIB_BLEND* att,
						 var_blend_spl_sur* vbss,
						 v_bl_contacts* start_slice,
						 list_of_contacts& slice_list,
						 logical forward, 
						 logical &looped,
						 double **discs = NULL,
						 int &num_discs = SpaAcis::NullObj::get_int());
