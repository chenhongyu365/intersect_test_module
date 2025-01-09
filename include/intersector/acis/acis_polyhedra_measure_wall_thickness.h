/*******************************************************************/
/*    Copyright (c) 1999-2022 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef ACIS_POLYHEDRA_MEASURE_WALL_THICKNESS_H
#define ACIS_POLYHEDRA_MEASURE_WALL_THICKNESS_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"
class polyhedra_measure_wall_thickness_options_impl;

/**
 * @file acis_polyhedra_measure_wall_thickness.h
 * \defgroup ACISPOLYTHICKAPI ACIS Polyhedra Thickness Measure
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
* Defines the accuracy of the tessellation
* @param FINE
*   small deviation between input and tessellated data.
*   This mode is not recommended for good performances.
*
* @param OPTIMIZED
*   recommended, best compromise between performances and precision
*
* @param COARSE
*   high deviation between input and tessellated data:
*   -> speeds up the computation and reduces the number of generated triangles
*   This mode is not recommended for a nice visualisation
*/
enum  DECL_SPAACISPOLY tess_level
{
	FINE = 0,
	OPTIMIZED,
	COARSE
};

/**
* Options for measuring wall thickness of a polyhedral body.
* This class contains parameters that govern the behavior of @href api_measure_wall_thickness_polyhedra.
* <br>
* <b>Technical Article:</b> <i>[Polyhedral Wall Thickness Measurement](https://doc.spatial.com/get_doc_page/articles/p/o/l/Polyhedral_Wall_Thickness_Measurement_2795.html)</i>
* <br>
* <b>Role :</b>  <tt>polyhedra_wall_thickness_options</tt> allows customization of behavior for @href api_measure_wall_thickness_polyhedra.
* The constructor of @href polyhedra_wall_thickness_options initializes all the parameters to their default value.
* You can use the <tt>set</tt> functions to change any of the parameters and the <tt>get</tt> functions
* to obtain the current value of the parameter set into a @href polyhedra_wall_thickness_options object. <br>
* <ul>
* <li> <b>Tessellation Level</b><br>
* The enum that defines the accuracy of the tessellation. By default it is set to OPTIMIZED.
* <li> <b>Sag Tolerance</b><br>
* Sets the maximum distance between the tessellation mesh and the input surface.
* <li> <b>Step Tolerance</b><br>
* Sets the maximum length of a mesh edge (i.e. triangle side) in the resulting mesh.
* <br><br>
* A sample snippet code to illustrate the usage is given below: <br>
* <pre>
* polyhedra_wall_thickness_options opt;
* opt.set_step(30.0);
* opt.set_sag(10.0);
*
* check_outcome(api_measure_wall_thickness_polyhedra(poly_body,outputhandle, &pso));
*
* </pre>
* <br>
*
* @see api_measure_wall_thickness_polyhedra
*/
class DECL_SPAACISPOLY polyhedra_wall_thickness_options: public ACIS_OBJECT
{
	polyhedra_measure_wall_thickness_options_impl* _impl = nullptr;
	tess_level _iTessLevel = OPTIMIZED;
	
public:

	/**
	* Constructor
	*/
	polyhedra_wall_thickness_options(double itolStep = 0.0, double itolSag = 0.0, tess_level iTessLevel = OPTIMIZED);

	/**
	* Copy Constructor
	*/
	polyhedra_wall_thickness_options(const polyhedra_wall_thickness_options& other);

	/**
	* Destructor
	*/
	~polyhedra_wall_thickness_options();

	/**
	* Assignment operator
	*/
	const polyhedra_wall_thickness_options& operator=(const polyhedra_wall_thickness_options& other);

	/**
	* Sets the step value.
	* @param iStep
	* The maximum length of a mesh edge (i.e. triangle side) in the resulting mesh. The
	* step should be larger than the sag. (By default it will be set by analyzing
	* the edge lengths and area of the model.  It will be at most the sqrt(area)/20
	* and no less than sqrt(area)/500.)
	*/
	void set_step(double iStep);

	/**
	* Gets the step value.
	* @return
	* The maximum length of a mesh edge (i.e. triangle side) in the resulting mesh.
	*/
	double get_step() const;

	/**
	* Sets the maximum distance between the tessellation mesh and the input surface.
	* @param iSag
	* The sag value (The default value is determined by the
	* tess_level enum in the operator's create method.
	* Setting the Sag value will override the value defined by the
	* tess_level enumerator.) The sag should be larger
	* that 10 times the factory resolution and less than the step.
	*/
	void set_sag(double iSag);

	/**
	* Gets the maximum distance between the tessellation mesh and the input surface
	* @return
	* The sag value.
	*/
	double get_sag() const;

	/**
	* Sets the enum that defines the accuracy of the tessellation.
	* @param iTessLevel
	* <ul>
	*	<li>FINE : Use a fine level of detail
	*	<li>OPTIMIZED : Use an optimized level of detail
	*	<li>COARSE : Use a coarse level of detail
	* </ul>
	*/
	void set_tess_level(tess_level iTessLevel);

	/**
	* Gets the tessellation level to be used.
	*/
	tess_level get_tess_level() const;
};

/**
* Represents the results of a wall thickness measurement. This class contains
* mesh data representing the tessellated input body with thickness values
* associated with each of the vertices.
*/
class DECL_SPAACISPOLY polyhedra_wall_thickness_output_handle
{
public:
	/**
	* @nodoc.
	*/
	virtual void add_ref() = 0;

	/**
	* @nodoc.
	*/
	virtual void release() = 0;

	/**
	* Serializes the triangle nodes into an integer buffer.
	* The buffer must be pre-allocated, and its size should be at least
	* get_sizeof_triangle_buffer().
	* @param ioTriangleNodeIndices
	*    The triangle indices buffer.
	*/
	virtual void get_triangles(int* oTriangles)const = 0;
	
	/**
	* Serializes the node position coordinates into a double buffer.
	* The buffer must be pre-allocated, and its size should be at least
	* get_sizeof_node_position_buffer().
	* @param ioNodePositionBuffer
	*    The positions buffer.
	*/
	virtual void get_node_positions(double* ioNodePositionBuffer)const = 0;
	
	/**
	* Serializes the node position coordinates into a float buffer.
	* The buffer must be pre-allocated, and its size should be at least
	* get_sizeof_node_position_buffer().
	* @param ioNodePositionBuffer
	*    The positions buffer.
	*/
	virtual void get_node_positions(float* ioNodePositionBuffer)const = 0;

	/**
	* Serializes the node thickness values into a double buffer.
	* The buffer must be pre-allocated, and its size should be at least
	* <tt>get_num_nodes()</tt>.
	* @param ioThicknessBuffer
	*	The thickness buffer.
	*/
	virtual void get_thickness(double* ioThicknessBuffer)const = 0;
	
	/**
	* Returns the minimum thickness of the input body
	* @return
	*  Minimum thickness
	*/
	virtual double get_min_thickness() const = 0;

	/**
	* Returns the maximum thickness of the body
	* @return
	*  Maximum Thickness
	*/
	virtual double get_max_thickness() const = 0;

	/**
	* Returns the position of the sampled vertex at the given index.
	* @param iSampledVertexIndex
	*     The index of the vertex in the mesh data. It must be greater than or
	*     equal to <tt>0</tt> and less than the value returned by
	*     <tt>get_num_nodes()</tt>.
	* @return
	*     The position at the given index.
	*/
	virtual SPAposition get_position_at(int iSampledVertexIndex) const = 0;

	/**
	* Returns the normal vector of the sampled vertex at the given index.
	* @param iSampledVertexIndex
	*     The index of the vertex in the mesh data. It must be larger than or
	*     equal to <tt>0</tt> and smaller than the value returned by
	*     <tt>get_num_nodes()</tt>.
	* @return
	*     The normal vector at the given index.
	*/
	virtual SPAvector get_normal_at(int iSampledVertexIndex) const = 0;

	/**
	* Returns the thickness of the sampled vertex at the given index.
	* @param iSampledVertexIndex
	*     The index of the vertex in the mesh data. It must be greater than or
	*     equal to <tt>0</tt> and less than the value returned by
	*     <tt>get_num_nodes()</tt>.
	* @return
	*     The position at the given index.
	*/
	virtual double get_thickness_at(int iSampledVertexIndex) const = 0;

	/**
	* Returns the number of nodes in the serialized data.
	* @return
	*   The number of the triangle nodes (i.e., triangle vertices).
	*/
	virtual int get_num_nodes() const = 0;

	/**
	* Returns the number of triangles in the serialized data.
	* @return
	*   The number of the triangles.
	*/
	virtual int get_num_triangles() const = 0;

	/**
	* Returns the number of float or double values in the node position buffer.
	* @return
	*   The size of the node positions buffer.
	*/
	virtual int get_sizeof_node_position_buffer() const = 0;

	/**
	* Returns the number of integers in the triangle index buffer.
	* The size of the buffer is equal to 3 times the number of triangles.
	* @return
	*   The size of the triangle indices buffer.
	*/
	virtual int get_sizeof_triangle_buffer() const = 0;

	/**
	* Directs this object to serialize the size of each triangular polygon
	* (that is, the number "3" preceding the triangle's data).  This method must
	* Make sure you call this function (if necessary) before calling
	* get_sizeof_triangle_buffer and get_triangles.
	* @param iDoIncludePolygonSize
	* When this flag is set to <tt>true</tt>, the triangles are serialized as
	* follows: <br> <tt>3 t0v0 t0v1 t0v2 3 t1v0 t1v1 t1v2 ... 3 tnv0 tnv1
	* tnv2</tt>. <br> Otherwise, the triangles are serialized as follows: <br>
	* <tt>t0v0 t0v1 t0v2 t1v0 t1v1 t1v2 ... tnv0 tnv1 tnv2</tt>.
	* <br>
	* By default this flag is set to <tt>false</tt>.
	*/
	virtual void serialize_polygon_size(bool iDoIncludePolygonSize = false) = 0;

	/**
	* Serializes the node normal coordinates into a double buffer.
	* The buffer must be pre-allocated, and its size should be at least
	* get_sizeof_node_position_buffer().
	* @param ioNodeNormalBuffer
	*    The Node Normal Buffer.
	*/
	virtual void get_node_normals(double* ioNodeNormalBuffer) const = 0;
};

/**
* Measures the wall thickness of the polyhedral ACIS body.
* <br>
* <b>Technical Article:</b> <i>[Polyhedral Wall Thickness Measurement](https://doc.spatial.com/get_doc_page/articles/p/o/l/Polyhedral_Wall_Thickness_Measurement_2795.html)</i>
* <br>
* <b>Role: </b> This API measures the thickness of an input body and return an instance of the <b>polyhedra_wall_thickness_output_handle</b>.
* <br><br>
* <b>Errors:</b>
* <ul>
* <li><tt>NOT_ACISPOLY_BODY</tt>: Input is not a polyhedral BODY.</li>
* <li><tt>ACISPOLY_ALGO_FAILED</tt>: ACIS Polyhedra operation failed due to algorithmic issues.</li>
* <li><tt>ACISPOLY_INTERNAL_ERROR</tt>: Internal Error in ACIS Polyhedra Component.</li>
* <li><tt>ACISPOLY_MWT_SAG_ERR</tt>: The sag value must be larger than or equal to 10 times the factory resolution.</li>
* <li><tt>ACISPOLY_MWT_STEP_ERR</tt>: The step value should be larger than or equal to the sag value.</li>
* </ul>
* <br><br>
* <b>Limitations:</b>
* <ul>
* <li>Non-polyhredral ACIS input body is not supported. </li>
* </ul>
* <br><br>
* <b>Journal:</b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Polyhedral
* <br><br>
* @param iBody
* ACIS BODY with polyhedra mesh geometry
* @param oHandle
* Handle to the output of measure wall thickness operation
* @param iOpts
* polyhedra_wall_thickness_options
* @param ao
* ACIS options.
*/
outcome DECL_SPAACISPOLY 
api_measure_wall_thickness_polyhedra(const BODY* iBody,
									 polyhedra_wall_thickness_output_handle*& oHandle,
									 polyhedra_wall_thickness_options* iOpts = nullptr,
									 AcisOptions* ao = nullptr);

#endif
