/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef API_ACISPOLYHEDRA_QUERY_H
#define API_ACISPOLYHEDRA_QUERY_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"
#include "SPA_raw_mesh.hxx"

class BODY;
class FACE;

/**
 * @file api_AcisPolyhedra_Query.h
 * \defgroup ACISPOLYQRYAPI ACIS Polyhedra Query
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
* Determines whether an ACIS body is polyhedral or not.
* <br><br>
* <b>Role:</b> Determines whether an ACIS body is polyhedral or not, 
* which is useful for polyhedral-specific operations such as <tt>api_acispolyhedra_decimate</tt>.
* ACIS body whose all faces have polyhedral geometry will return TRUE, 
* while ACIS body where faces have exact geometry ( analytical surfaces and/or splines ) will return FALSE.
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iBody
* any ACIS BODY
*/
DECL_SPAACISPOLY bool is_polyhedra_body(BODY* iBody);


/**
* Determines whether an ACIS polyhedral body is watertight or not.
* <br><br>
* <b>Role:</b> Determines whether or not a polyhedral body is watertight, which is important for many modeling operations.  
* In a watertight polyhedral mesh every facet bar is shared by exactly two facets.
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iBody
* ACIS BODY with polyhedral geometry
*/
DECL_SPAACISPOLY bool is_polyhedra_body_watertight(BODY const* iBody);

/**
* Gets the mesh geometry (triangles) of a given BODY.
* <br><br>
* <b>Role:</b> Retrieves the polyhedral global mesh geometry of the input BODY.
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param body
* Input ACIS Polyhedral BODY
* @param output_mesh
* Spa_raw_mesh_sptr object that holds the global polyhedral mesh geometry
* @param ao
* ACIS options
*/
DECL_SPAACISPOLY outcome api_polyhedra_get_mesh(BODY const* body, Spa_raw_mesh_sptr& output_mesh, AcisOptions* ao = NULL);

/**
* Gets the mesh geometry (triangles) of a given FACE.
* <br><br>
* <b>Role:</b> Retrieves the polyhedral global mesh geometry of the input FACE.
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param face
* Input ACIS Polyhedral FACE
* @param output_mesh
* Spa_raw_mesh_sptr object that holds the global polyhedral mesh geometry
* @param ao
* ACIS options
*/
DECL_SPAACISPOLY outcome api_polyhedra_get_mesh(FACE const* face, Spa_raw_mesh_sptr& output_mesh, AcisOptions* ao = nullptr);

#endif

