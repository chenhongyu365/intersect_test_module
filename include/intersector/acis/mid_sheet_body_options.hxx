/*******************************************************************/
/*    Copyright (c) 1989-2021 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef MID_SHEET_BODY_OPTIONS
#define MID_SHEET_BODY_OPTIONS

#include "dcl_shl.h"
#include "mmgr.hxx"

/**
 * @file mid_sheet_body_options.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \defgroup SHLAPI Shelling
 *
 * \ingroup LOCALOPS
 * @{
 */

 /**
  * This class contains parameters that govern the behavior of @href api_make_mid_sheet_body and
  * @href api_detect_mid_sheet_face_pairs.
  * <br><br>
  * <b>Technical Articles:</b> <i>[Mid Sheet Body](https://doc.spatial.com/articles/m/i/d/Mid_Sheet_Generation_90eb.html)</i>
  * <br><br>
  * <b>Role:</b> Below are lists of parameters available in the @href mid_sheet_body_options class.
  * The constructor of @href mid_sheet_body_options initializes all the parameters to their default value. 
  * User can use the <tt>set</tt> functions to change any of the parameters and the <tt>get</tt> functions
  * to obtain the current value of the parameter set into a @href mid_sheet_body_options object. <br>
  * <br><br>
  * <ul>
  * <li> <b>Maximum Face Pair Distance</b><br>
  * It provides control over the face pair detection.
  * A face pair is considered as valid if minimum distance between them is less than or equal to the max_face_pair_distance value.
  * The default value is -1.0, which indicates that it should be calculated internally.
  * </li>
  * <br>
  * <li> <b>Pair Detection Mode</b><br>
  * It provides control over face pair detection. 
  * There are two modes available for face pair detection SHEET_METAL and REGULAR.
  * The SHEET_METAL mode provides significantly improved performance in comparison to the REGULAR mode. 
  * For more details refer @href pair_detection_mode documentation.
  * By default, the mid_sheet_body_options::pair_detection_mode setting differs for face pair detection and mid-sheet generation. 
  * The default mode for face pair detection is SHEET_METAL, while the default mode for mid-sheet generation is REGULAR.
  * It is recommended to use the SHEET_METAL mode for uniform thickness model with one-to-one mapping.
  * </li><br>
  * <li> <b>Progenitor Information flag</b><br>
  * It provides control over the caching progenitor information of mid sheet face.
  * The progenitor information consists of a pair of faces from which mid sheet created and the corresponding distance between them. 
  * Prior to using the this API, users are required to call the @api_make_mid_sheet_body to cache the progenitor information. 
  * To access the cached progenitor information of a mid sheet face, the @api_get_mid_sheet_progenitor_info API is used. 
  * The @api_cleanup_mid_sheet_progenitor_info API is available to clean up the progenitor information for all mid sheet faces within the mid sheet body.
  * It is important to note that the progenitor body, which is the original body from which the mid sheet was created,
  * must be present and should not be modified or deleted during the usage of these APIs.
  * In "REGULAR" and "SHEET_METAL" modes, the face pairs within the mid sheet face may vary, 
  * leading to potentially different progenitor information in each mode.
  * The default value is "false".
  * </li><br>
  * <li> <b>Offset Ratio</b><br>
  * The 'offset_ratio' parameter is utilized to generate the mid-sheet. 
  * The mid-sheet is positioned at a distance multiplied by the 'offset_ratio' from the left faces. 
  * The distance used for mid-sheet generation in both modes is different. 
  * The 'SHEET_METAL' mode uses the distance from the 'mid_sheet_face_pair' class.
  * The 'REGULAR' mode uses the minimum distance between the face-pair. 
  * The default value is "0.5". 
  * </li><br>
  * </ul>
  * A sample snippet code to illustrate the usage is given below: <br>
  * <pre>
  * mid_sheet_body_options mopt;
  * mopts.set_progenitor_info_flag(true); //set progenitor information flag. 
  * outcome result = api_make_mid_sheet_body(thin_block, mid_sheet_body, &mopts);
  * </pre>
  * <br>
  * @see api_make_mid_sheet_body, api_detect_mid_sheet_face_pairs, api_get_mid_sheet_progenitor_info and
  * api_cleanup_mid_sheet_progenitor_info
 **/
class DECL_SHL mid_sheet_body_options : public ACIS_OBJECT
{
public:

	/**
    *  This enum class can be used for specifying face pair detection mode.
    *
    * @param SHEET_METAL
    * It is faster compared to Regular mode. There are the following assumptions about input and output.
    *	1. The input must be a thin walled model. It must have constant thickness.
    *	2. It supports only one-one mapping between face-pairs (One left face has only one right face).
    *	3. The mid sheet body generated from these pairs is always manifold.
    *		The T and X types of model configurations are not supported for face pair detection.
	*   4. The offset distance used for generating the mid sheet is the same as the output thickness of mid_sheet_face_pair structure. 
    *
    * @param REGULAR
    * There are the following assumptions about input and output.
    *   1. The input must be a thin walled model. It must have constant thickness.
    *	2. It supports both one-one and one-many mapping between face-pairs (One left face can have multiple right faces).
    *	3. The mid-sheet body generated from these pairs can be manifold or non-manifold, depending on the model configuration.
	*	4. The offset distance used for generating the mid sheet is the minimum distance between the left and right face of the face pair.
    *
    * @see api_detect_mid_sheet_face_pairs.
    **/

	enum class pair_detection_mode
	{
		SHEET_METAL,
		REGULAR,
		NONE
	};

public:

	/**
	 * Constructs an instance of <tt>mid_sheet_body_options</tt>
	 **/
	mid_sheet_body_options();

	/**
	* Destructs an <tt>mid_sheet_body_options</tt> object.
	**/
	~mid_sheet_body_options();

	/**
	* Copy Constructor of an <tt>mid_sheet_body_options</tt> object.
	**/
	mid_sheet_body_options(const mid_sheet_body_options&);

	/**
	* Assignment operator of an <tt>mid_sheet_body_options</tt> object.
	**/
	const mid_sheet_body_options& operator=(const mid_sheet_body_options&);

	/**
	 * Get max_face_pair_distance value that user has provided using "set_max_face_pair_distance" function.
	 **/
	double get_max_face_pair_distance() const;

	/**
	 * It provides control over the face pair detection. 
	 * A face pair is considered as valid if minimum distance between them is less than or equal to the max_face_pair_distance value.
	 * The default value is -1.0, which indicates that it should be calculated internally.
	 **/
	void set_max_face_pair_distance( double max_face_pair_distance);

	/**
	 * Get pair detection mode that user has provided using "set_pair_detection_mode" function.
	 **/
	mid_sheet_body_options::pair_detection_mode get_pair_detection_mode()const;

	/**
    * It provides control over face pair detection.
    * There are two modes available for face pair detection SHEET_METAL and REGULAR.
    * The SHEET_METAL mode provides significantly improved performance in comparison to the REGULAR mode.
    * For more details refer @href pair_detection_mode documentation.
    * By default, the mid_sheet_body_options::pair_detection_mode setting differs for face pair detection and mid-sheet generation.
    * The default mode for face pair detection is SHEET_METAL, while the default mode for mid-sheet generation is REGULAR.
    * It is recommended to use the SHEET_METAL mode for uniform thickness model with one-to-one mapping.
	 **/
	void set_pair_detection_mode(mid_sheet_body_options::pair_detection_mode pdmode);

	/**
	 * Get progenitor info flag that user has provided using "set_progenitor_info_flag" function.
	 **/
	bool get_progenitor_info_flag() const;

	/**
	 * It provides control over the caching progenitor information of mid sheet face.
	 * The progenitor information consists of a pair of faces from which mid sheet created and the corresponding distance between them. 
	 * Prior to using the this API, users are required to call the @api_make_mid_sheet_body to cache the progenitor information. 
	 * To access the cached progenitor information of a mid sheet face, the @api_get_mid_sheet_progenitor_info API is used. 
     * The @api_cleanup_mid_sheet_progenitor_info API is available to clean up the progenitor information for all mid sheet faces within the mid sheet body.
     * It is important to note that the progenitor body, which is the original body from which the mid sheet was created,
     * must be present and should not be modified or deleted during the usage of these APIs.
     * In "REGULAR" and "SHEET_METAL" modes, the face pairs within the mid sheet face may vary, 
     * leading to potentially different progenitor information in each mode.
	 * The default value is "false".
	 **/
	void set_progenitor_info_flag(bool prog_info_flag);

	/**
	 * Get offset ratio value that user has provided using "set_offset_ratio" function.
	 **/
	double get_offset_ratio()const;

	/**
	* The 'offset_ratio' parameter is utilized to generate the mid-sheet. 
	* The mid-sheet is positioned at a distance multiplied by the 'offset_ratio' from the left faces. 
	* The distance used for mid-sheet generation in both modes is different. 
	* The 'SHEET_METAL' mode uses the distance from the 'mid_sheet_face_pair' class.
	* The 'REGULAR' mode uses the minimum distance between the face-pair. 
	* The default value is "0.5". 
	**/
	void set_offset_ratio(double offset_ratio);

private:

	class mid_sheet_body_options_impl;
	mid_sheet_body_options_impl* m_impl = nullptr;
	
};
/*! @} */
#endif
