/* ORIGINAL: acis2.1/kernint/intcusf/intcusf.hxx */
/* $Id: intcusf.hxx,v 1.16 2002/08/09 17:18:52 jeff Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

// STL AL  26Oct05 - Added special intersectors involving helix.

// Header file for curve-surface intersection.

// Intersect a curve with a surface.  Only a bounded portion of the
// curve is of interest, given by start and end SPAparameter values,
// further delimited by a bounding SPAbox.

// The routine returns all intersections inside the SPAbox and none
// outside, and takes special action at the end points.  If an end
// point lies on the surface, the intersection is first coerced to that
// point, and only then checked against the SPAbox.  This way a vertex is
// treated the same for every edge running through it.

#if !defined(INT_CURVE_SURF)
#    define INT_CURVE_SURF

#    include <stddef.h>

#    include "acis.hxx"
#    include "cusfint.hxx"
#    include "dcl_intr.h"
#    include "logical.h"
#    include "param.hxx"
#    include "position.hxx"

class curve;
class surface;
class SPAbox;

// This is the general (lower-case) curve-surface intersection
// routine (in intcusf.cxx).  Depending on the curve and surface types,
// it calls the specific routines below, returning a pointer to a
// chain of curve_surf_int's on the heap.

DECL_INTR curve_surf_int* int_cur_sur(curve const&, surface const&, curve_bounds&, SPAbox const& = SpaAcis::NullObj::get_box());

// Tolerant intersection version, internally both use the same code

DECL_INTR curve_surf_int* int_cur_sur(curve const&, surface const&, curve_bounds&, double const, SPAbox const& = SpaAcis::NullObj::get_box());

#endif
