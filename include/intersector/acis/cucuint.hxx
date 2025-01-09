/* ORIGINAL: acis2.1/kernint/intcucu/intcucu.hxx */
/* $Id: cucuint.hxx,v 1.12 2002/08/09 17:18:51 jeff Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#if !defined( CURVE_CURVE_INT )
#define CURVE_CURVE_INT

#include "dcl_intr.h"
#include "intcucu.hxx"

class curve;
class SPAbox;

// The general curve-curve intersection routine (in cucuint.cxx).
// It just switches on curve type to code which deals with the
// specific types. The result is a list of curve_curve_ints in
// increasing order of SPAparameter on the first curve.

DECL_INTR curve_curve_int *int_cur_cur(
				curve const &,
				curve const &,
				SPAbox const & = SpaAcis::NullObj::get_box(),
				double = SPAresabs
			);

// 自行完成接口
DECL_INTR curve_curve_int *answer_int_cur_cur(
				curve const &,
				curve const &,
				SPAbox const & = SpaAcis::NullObj::get_box(),
				double = SPAresabs
			);

#endif
