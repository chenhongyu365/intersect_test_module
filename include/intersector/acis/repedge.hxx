/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

// Header for replace edge with tolerant edge.

#if !defined( REPLACE_EDGE )
#define REPLACE_EDGE

#include "dcl_kern.h"
#include "base.hxx"				// For logical
#include "spa_null_base.hxx"	// For Null Objects

class EDGE;
class TEDGE;
class TCOEDGE;
class VERTEX;
class TVERTEX;
class tolerize_options;
class ENTITY_LIST;


// Replace the coedges of an [t]edge with tcoedges.
DECL_KERN void tm_replace_coedges_of_edge(
    EDGE *ed
);

// If the tolerance for this tedge is known already it may be passed as
// the optional final argument, so as to avoid recalculating it again.

DECL_KERN logical replace_edge_with_tedge(
	EDGE *	this_edge,
	logical add_tcoedges,
	logical tangent,
	TEDGE * &this_tedge,
	double const &tol = SpaAcis::NullObj::get_double(),
	tolerize_options* = NULL
);

DECL_KERN void replace_vertex_with_tvertex(
	VERTEX *this_vertex,
	TVERTEX * &this_tvertex
);

// This function replaces a tedge with an edge and the tedge's tvertices 
// with vertices.  Note, if check_tolerance is TRUE, the tedge and 
// tvertices will only be replaced if their tolerance is < SPAresabs/10.  If the
// flag replace_edge_only is TRUE, the tvertices are unchanged.
// Returns TRUE if successful
DECL_KERN logical replace_tedge_with_edge(
	TEDGE *this_tedge,
	EDGE * &this_edge,
    logical check_tolerance = FALSE,
    logical replace_edge_only = FALSE
);

// This function replaces a tvertex with a vertex
// If the check_tolerance flag is TRUE, only replaces tvertices
// whose tolerance is < SPAresabs/10
// Returns TRUE if successful
DECL_KERN logical replace_tvertex_with_vertex(
	TVERTEX *this_tvertex,
	VERTEX * &this_vertex,
    logical check_tolerance = FALSE
);

// This function optimizes the tolerance of the tvertices of an edge or tedge.
DECL_KERN void optimize_tvertex_tolerance (
	EDGE *edge 
);

// This function checks the optimization of the tvertices of an edge or tedge.
DECL_KERN logical is_tvertices_optimized (
	EDGE *edge 
);

// This function updates the parameter range of the tcoedges on a list of tedges.
DECL_KERN void update_tcoedge_param_ranges (
	ENTITY_LIST& tedges
);

// This function determines the start or end parameter value of the given tcoedge,
// given the start or end vertex of its tedge and a guess parameter value. 
// The guess parameter value is typically the corresponding parameter value of tedge, 
// with an reversal thrown in when appropriate.
DECL_KERN double determine_tcoedge_param (
	TCOEDGE* this_tcoedge,
	VERTEX* vertex,
	double guess_param
);


#endif
