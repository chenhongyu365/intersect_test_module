/*******************************************************************/
/*    Copyright (c) 1989-2023 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef DEPRECATED_WRAP_API_HXX
#define DEPRECATED_WRAP_API_HXX

#include "dcl_warp.h"
#include "api.hxx"

class AcisOptions;
class BODY;
class FACE;

// Replace all faces and edges of the body to contain analytics or bsplines.
/**
 * @nodoc
 * <b>Obsolete:</b> Instead, use @href api_simplify_entity.<br><br>
 * Simplifies the faces and edges of a body.
 * <br><br>
 * <b>Role:</b> The faces and edges of an entity are replaced by analytic surfaces and curves,
 * if possible. Otherwise, they are replaced by their B-spline approximations.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS Modeler
 * <br><br>
* @param in_body
 * body to be simplified.
 * @param ao
 * ACIS options.
 */
DECL_WARP outcome api_simplify_body(
	BODY* in_body,					// Body to be simplified
	AcisOptions* ao = NULL
);


// Replace face and edges of the face to contain analytics or bsplines.
/**
 * @nodoc
 * <b>Obsolete:</b> Instead, use @href api_simplify_entity.<br><br>
 * Simplifies the face and the edges of the face.
 * <br><br>
 * <b>Role:</b> The face and edges of the face are replaced by analytic surfaces and curves,
 * if possible. Otherwise, they are replaced by their B-spline approximations.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS Modeler
 * <br><br>
* @param in_face
 * face to be simplified.
 * @param reparam
 * for future use.
 * @param ao
 * ACIS options.
 */
DECL_WARP outcome api_simplify_face(
	FACE* in_face,				// Face to be simplified
	logical reparam = FALSE,    // For future use
	AcisOptions* ao = NULL
);

#endif

