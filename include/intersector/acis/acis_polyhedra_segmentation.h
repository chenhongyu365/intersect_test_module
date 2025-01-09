/*******************************************************************/
/*    Copyright (c) 1999-2022 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef ACIS_POLYHEDRA_SEGMENTATION_H
#define ACIS_POLYHEDRA_SEGMENTATION_H

#include "api.hxx"
#include "dcl_acispolyhedra.h"

class polyhedra_segment_options_impl;

/**
 * @file acis_polyhedra_segmentation.h
 * \defgroup ACISPOLYSEGAPI ACIS Polyhedra Segmentation
 * \ingroup ACISPOLYAPI
 * @{
 */

/**
 * Specifies segmentation algorithm to be used.
 * @param DIHEDRAL
 * Dihedral angle based Edge detection algorithm.
 * @param OPTIMIZED
 * Optimized Edge detection algorithm.
 * @param PARTITION_OF_MESH
 * Partition of mesh algorithm.
 **/
enum class DECL_SPAACISPOLY segmentation_algorithm
{
	DIHEDRAL = 0,
	OPTIMIZED,
	PARTITION_OF_MESH
};

/**
* Options for the segmentation of a polyhedral body.
* This class contains parameters that govern the behavior of @href api_segment_polyhedra_body.
* <b>Technical Article:</b> <i>[Polyhedral Segmentation](https://doc.spatial.com/get_doc_page/articles/p/o/l/Polyhedral_Segmentation_and_Canonic_Surface_Recognition_ccbe.html)</i>
* <br><br>
* <br>
* <b>Role :</b>  <tt>polyhedra_segment_options</tt> allows customization of behavior for @href api_segment_polyhedra_body.
* The constructor of @href polyhedra_segment_options initializes all the parameters to their default value.
* You can use the <tt>set</tt> functions to change any of the parameters and the <tt>get</tt> functions
* to obtain the current value of the parameter set into a @href polyhedra_segment_options object. <br>
* <ul>
* <li> <b>Segmentation Algorithm</b><br>
* The algorithm used to segment in the input body.
* <li> <b>Sharp Angle Threshold</b><br>
* The angle threshold in degrees for the <tt>DIHEDRAL</tt> and <tt>OPTIMIZED</tt> algorithms.
* <li> <b>Face Area Threshold</b><br>
* Fractional threshold for the minimum acceptable area of each face in the output body for the <tt>DIHEDRAL</tt> and <tt>OPTIMIZED</tt> algorithms.
* <li> <b>Override Sag Tolerance</b><br>
* The sag tolerance for the <tt>PARTITION_OF_MESH</tt> algorithm.
* <li> <b>Detect Canonics</b><br>
* Detect Canonic geometries for the segmented polyhedral body.
* <br><br>
* A sample snippet code to illustrate the usage is given below: <br>
* <pre>
* polyhedra_segment_options pso;
* pso.set_sharp_angle_threshold(30.0);
* pso.set_face_area_threshold(10.0);
* pso.set_detect_canonics(false);
*
* check_outcome(api_segment_polyhedra_body(poly_body,seg_body, &pso));
*
* </pre>
* <br>
*
* @see api_segment_polyhedra_body
*/
class DECL_SPAACISPOLY polyhedra_segment_options : public ACIS_OBJECT
{
public:

	/**
	* Constructor
	*/
	polyhedra_segment_options(segmentation_algorithm iAlgo = segmentation_algorithm::OPTIMIZED, double iSharpAngThresh = 45.0, double iFaceAreaThresh = 0.0, double iOverrideSagTol = 0.0, bool iDetectCanonics = true);

	polyhedra_segment_options(const polyhedra_segment_options&);

	/**
	* Destructor
	*/
	~polyhedra_segment_options();

	const polyhedra_segment_options& operator=(const polyhedra_segment_options&);

	/**
	* Query the segmentation algorithm to be used.
	*/
	segmentation_algorithm get_segmentation_algorithm() const;

	/**
    * Sets the algorithm used to segment in the input body. Possible values are
    * given by the enum <tt>segmentation_algorithm</tt>:
    * <ul>
    * <li> <tt>DIHEDRAL</tt>: places edges wherever the dihedral angle between facets is sharper than a user-specified threshold.
    * <li> <tt>OPTIMIZED</tt>: uses a statistical method to identify likely edges.
    * <li> <tt>PARTITION_OF_MESH</tt>: iteratively merges facets into patches that can be closely fit by canonic surfaces.
    * </ul>
    * The default algorithm is <tt>OPTIMIZED</tt>.
    * @param iAlgo
    * The selected algorithm.
    **/
	void set_segmentation_algorithm(segmentation_algorithm iAlgo);

	/**
	* Query the sharp angle threshold to be used.
	*/
	double get_sharp_angle_threshold() const;

	/**
    * Sets the dihedral angle threshold for the <tt>DIHEDRAL</tt> and
    * <tt>OPTIMIZED</tt> algorithms. This threshold controls which mesh edges of the
    * input body will be marked as edges during the initial pass.
    * <ul>
    * <li> When <tt>DIHEDRAL</tt> is selected, a mesh edge will be
    * marked as an edge if and only if it has a dihedral angle sharper than the
    * threshold.
    * <li> When <tt>OPTIMIZED</tt> is selected, all mesh edges
    * with dihedral angles sharper than the threshold will be marked as edges,
    * and then the remaining mesh edges will be evaluated by the statistical algorithm.
    * </ul>
    * This setting has no effect when <tt>PARTITION_OF_MESH</tt> is used.
    * @param iAngThresh
    * Angle threshold in degrees. The default value is 45.
    **/
	void set_sharp_angle_threshold(double iAngThresh);
	
	/**
	* Query the face area threshold to be used.
	*/
	double get_face_area_threshold() const;

	/**
	* Sets the minimum face area for the <tt>DIHEDRAL</tt> and <tt>OPTIMIZED</tt>
	* algorithms. The edge detection methods used by these algorithms can
	* sometimes general small "noise" faces. This parameter sets a minimum
	* acceptable area for the faces in the final output.
	* @param iFaceAreaThresh
	* Fractional threshold for the minimum acceptable area of each face in the
	* output body. Any face whose area is less than A x F (where A is the total
	* area of the body and F is the fractional threshold) will be removed by
	* merging it into a neighboring face. The default value is 0, which will keep
	* all of the output faces.
	**/
	void set_face_area_threshold(double iFaceAreaThresh);

	/**
	* Query the sag tolerance to be used.
	*/
	double get_override_sag_tol() const;

	/**
	* Sets the sag tolerance. The <tt>PARTITION_OF_MESH</tt> algorithm attempts to
	* fit canonic surfaces to regions of the input body. This parameter sets the
	* maximum acceptable distance between the fit surfaces and the mesh edges of the
	* input body.
	*
	* If this function is not called, or if the provided sag tolerance is not
	* positive, the algorithm will attempt to automatically estimate the sag by
	* considering the size of the input body and the average size of the
	* tessellation edges.
	*
	* @param iSagTol
	* Sag to use during the patch-fitting procedure.
	**/
	void set_override_sag_tol(double iSagTol);

	/**
	* Query if detection of canonic geometries is set.
	*/
	bool get_detect_canonics() const;

	/**
	* Sets if you want to detect canonic geometries for the segmented polyhedral body.
	* @param iDetect
	* Boolean value to allow detection of canonic geometries.
	**/
	void set_detect_canonics(bool iDetect);
	
private:
	polyhedra_segment_options_impl* _impl = nullptr;
	segmentation_algorithm _algorithm = segmentation_algorithm::OPTIMIZED;
};

/**
* Segement the polyhedral ACIS body.
* <b>Technical Article:</b> <i>[Polyhedral Segmentation](https://doc.spatial.com/get_doc_page/articles/p/o/l/Polyhedral_Segmentation_and_Canonic_Surface_Recognition_ccbe.html)</i>
* <br><br>
* <b>Role: </b> This API segments a single-face polyhedral ACIS Body, producing an output polyhedral ACIS Body with multiple faces.
* <br><br>
* <b>Errors:</b>
* <ul>
* <li><tt>NOT_ACISPOLY_BODY</tt>: Input is not a polyhedral BODY.</li>
* <li><tt>ACISPOLY_ALGO_FAILED</tt>: ACIS Polyhedra operation failed due to algorithmic issues.</li>
* <li><tt>ACISPOLY_INTERNAL_ERROR</tt>: Internal Error in ACIS Polyhedra Component.</li>
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
* @param oBody
* Output Segmented ACIS Polyhedral Body
* @param iSegOpts
* polyhedra_segment_options
* @param ao
* ACIS options.
*/
outcome DECL_SPAACISPOLY api_segment_polyhedra_body(BODY* iBody, 
													BODY*& oBody, 
													polyhedra_segment_options* iSegOpts = nullptr,
													AcisOptions* ao = nullptr);

													
#endif


