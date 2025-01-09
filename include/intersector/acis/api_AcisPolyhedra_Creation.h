/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef API_ACISPOLYHEDRA_CREATION_H
#define API_ACISPOLYHEDRA_CREATION_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"
#include "CGMPolyImportPart.h"
#include "CGMPolyImportMesh.h"
#include "CGMContainer.h"
#include "CGMPolyImportMeshContainer.h"

#include <vector>

class option_header;
class polyhedra_body_options_impl;

// SESSION_GLOBAL_VAR option_header optimize_polyhedra_tracking( "optimize_polyhedra_tracking", FALSE );
extern DECL_SPAACISPOLY option_header optimize_polyhedra_tracking;

/**
 * @file api_AcisPolyhedra_Creation.h
 * \defgroup ACISPOLYCRTAPI ACIS Polyhedra Creation
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
* Options for the creation of a polyhedral body.
* <br>
* <b>Role :</b> <tt>polyhedra_body_options</tt> allows customization of behavior for <tt>api_create_polyhedra_mesh_body</tt>.
* <br>
*/

class DECL_SPAACISPOLY polyhedra_body_options : public ACIS_OBJECT
{
public:

	// ********************************************************************

	//Constructors

	polyhedra_body_options();

	polyhedra_body_options(const polyhedra_body_options&);

	//Destructor

	~polyhedra_body_options();

	// Operator

	const polyhedra_body_options& operator=(const polyhedra_body_options&);

	// ********************************************************************

	/**
	* The surface tolerance controls the maximum deviation between the polybody and the B-rep body.
	*
	* The unset/unspecified value for surf_tol is -1; if unset, the API will use as a default value
	* 1/500 of the bounding box diagonal for the body.
	*/
	void set_surface_tolerance(double surf_tol);
	/**
	* Returns the surface tolerance used.
	*/
	double get_surface_tolerance() const;

	/**
	* Specifies the maximum length of a facet edge. The default is 0, which means that
	* no prespecified upper bound on facet edge length is used.
	*/
	void set_max_edge_length(double max_edge_length);
	/**
	* Returns the maximum edge length.
	*/
	double get_max_edge_length() const;

	/**
	* Returns the list of Mesh which has anomalies.
	*/	
	CGMPolyImport::MeshContainer get_meshes_with_anomalies() const;
	/** 
	* @nodoc 
	*/
	void add_mesh_with_anomalies(CGMPolyImport::MeshContainer meshes);
private:
	polyhedra_body_options_impl* _impl = nullptr;
};


/**
* Makes an ACIS BODY that contains polyhedral mesh geometry.
* <b>Technical Article:</b> <i>[Creating Polyhedral Bodies](http://doc.spatial.com/articles/c/r/e/Creating_Polyhedral_Bodies_d4f0.html)</i>
* <br><br>
* <b>Role:</b> This API constructs an ACIS body with polyhedral mesh geometry using an input ACIS body.
* The input ACIS body can have one or more faces with each surface geometry being an analytic or spline surface.
* The new ACIS body created will have faces with each surface geometry being a polyhedral mesh. The topology
* of the input body and output body will be similar, but not necessarily the same. Sliver faces in the input body
* may not have corresponding entities in the output body. Also, the edge count in the output may be different from that of the input.
* The quality of the polyhedral mesh is controlled by the <tt>polyhedra_body_options</tt> object.
* <br><br>
* <b>Errors:</b>
* <ul>
* <li><tt>ACISPOLY_BAD_INPUT</tt>: Bad input to the ACIS Polyhedra functionality. Input maybe non-manifold or wire-body.</li>
* <li><tt>ACISPOLY_POLYBODY_FAILURE</tt>: Failed to create polyhedral BODY.</li>
* <li><tt>ACISPOLY_BAD_POLYMESH</tt>: Polyhedral Mesh with anomalies detected.</li>
* </ul>
* <br><br>
* <b>Limitations:</b> 
* <ul>
* <li>Non-manifold input body is not supported. </li>
* <li>Wire input body is not supported. </li>
* </ul>
* <br><br>
* <b>Journal:</b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iBody
* Input ACIS BODY
* @param ioBody
* Output ACIS body with polyhedral geometry
* @param iMakeOpts
* Option polyhedra_body_options. A NULL argument will cause the API to use default settings.
* @param ao
* ACIS options.
*/

DECL_SPAACISPOLY outcome api_create_polyhedra_body(	BODY* iBody, 
													BODY*& ioBody, 
													polyhedra_body_options* iMakeOpts = nullptr, 
													AcisOptions* ao = nullptr);

/**
* Makes a CGMPolyImport::OperationResult that contains polyhedral mesh data.
* <b>Technical Article:</b> <i>[Creating Polyhedral Bodies](http://doc.spatial.com/articles/c/r/e/Creating_Polyhedral_Bodies_d4f0.html)</i>
* <br><br>
* <b>Role:</b> Makes a CGMPolyImport::OperationResult from input triangles.
* The input triangles are provided in the form of a double array that stores the position coordinates, 
* along with an integer array that stores the triangle connectivity information. 
* The array of position coordinates is of size three times the number of triangle vertices. 
* Similarly, the size of the array of triangle connectivity is three times the number of triangles.
* <br><br>
* <b>Errors:</b>
* <ul>
* <li><tt>ACISPOLY_POLYMESH_FAILURE</tt>: Failed to create polyhedral Mesh. Input may not be clean.</li>
* <li><tt>ACISPOLY_POLYBODY_FAILURE</tt>: Failed to create polyhedral BODY.</li>
* <li><tt>ACISPOLY_BAD_POLYMESH</tt>: Polyhedral Mesh with anomalies detected.</li>
* </ul>
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iNumPoints
* Number of positions
* @param iPointCoords
* Position coordinates; the size of this array is three times the number of vertices
* @param iNumTriangles
* Number of triangles
* @param iTriangleConnectivity
* Triangle connectivity; the size of this array is three times the number of triangles
* @param ioPart
* CGMPolyImport::Part
* @param ioResultOfAddingMesh
* CGMPolyImport::OperationResult, It contains polyhedral mesh data.
* @param ao
* ACIS options.
*/

DECL_SPAACISPOLY outcome api_create_polyhedra_mesh(	int iNumPoints, double const* iPointCoords,
													int iNumTriangles, int const* iTriangleConnectivity,
													CGMPolyImport::Part& ioPart, 
													CGMPolyImport::OperationResult& ioResultOfAddingMesh,
													AcisOptions* ao = nullptr);


/**
* Makes an ACIS body that contains polyhedral mesh geometry.
* <b>Technical Article:</b> <i>[Creating Polyhedral Bodies](http://doc.spatial.com/articles/c/r/e/Creating_Polyhedral_Bodies_d4f0.html)</i>
* <br><br>
* <b>Role:</b> Makes an ACIS BODY from CATBody (Polyhedral body). The face(s) of the constructed ACIS body has polyhedral mesh geometry. 
* <br><br>
* <b>Errors:</b>
* <ul>
* <li><tt>ACISPOLY_BAD_INPUT</tt>: Bad input to the ACIS Polyhedra functionality. Input may not be polyhedral CATBody.</li>
* <li><tt>ACISPOLY_POLYBODY_FAILURE</tt>: Failed to create polyhedral BODY.</li>
* <li><tt>ACISPOLY_BAD_POLYMESH</tt>: Polyhedral Mesh with anomalies detected.</li>
* </ul>
* <br><br>
* <b>Limitations:</b>
* <ul>
* <li>Non-Polyhedral input CATBody is not supported. </li>
* </ul>
* <br><br>
* <b>Journal:</b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iCatbody
* Input CATBody
* @param ioAcisBody
* Output ACIS body with polyhedral geometry
* @param ao
* ACIS options.
*/

DECL_SPAACISPOLY outcome api_create_polyhedra_body(	CATBody* iCatbody, 
													BODY*& ioAcisBody, 
													AcisOptions* ao = nullptr);

#endif

