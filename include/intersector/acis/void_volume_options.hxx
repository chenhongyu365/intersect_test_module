/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef VOID_VOLUME_OPTIONS_CLASS
#define VOID_VOLUME_OPTIONS_CLASS

#include "dcl_hlc.h"
#include "mmgr.hxx"

class FACE;
class void_volume_options_impl;

/**
* @file void_volume_options.hxx
* \addtogroup HLC
* @{
*/

/**
* This class holds optional information that affects the behavior of @href api_void_volume.
* <br>
* <b>Role:</b> A @href void_volume_options object supplies optional information 
* to @href api_void_volume.
* <br><br>
* This class can be used to specify a covering surface for each edge circuit.
*/
class DECL_HLC void_volume_options : public ACIS_OBJECT
{

protected:

	void_volume_options_impl* m_impl;
	
	void_volume_options ( void_volume_options const& input );
	
	void_volume_options& operator= ( void_volume_options const& input );

public:
	// ********************************************************************
	/**
	* Default constructor
	*/
	void_volume_options ();

	/**
	* Destructor.
	*/
	~void_volume_options ();
	
	// ********************************************************************

	/**
	* Set the covering surfaces.
	* <b>Role:</b> This function allows the caller to specify the surfaces to cover one or more edge circuits.
	* It stores an array of FACE pointers, each representing a face whose surface is to be used to cover an edge circuit.
	* The size of the face array MUST be the same as the number of edge circuits. 
	* The surface underlying the i'th face is used to cover the i'th edge circuit.
	* If a surface is to be used to cover more than one edge circuit, its face should be
	* in the array more than once, to maintain a one-to-one relationship between the circuits
	* and the faces.
	* Some elements of the array may be NULL pointers, in which case the ACIS Covering algorithm
	* will attempt to generate a covering surface for that circuit.
	* The options object takes ownership of the given array.
	*/
	void set_surfaces(FACE* surfaces[]);
	
	/**
	* Return the covering surfaces array.
	*/
	FACE** get_surfaces();

	/**
	* Set the value of the separate flag.
	* <b>Role:</b> This function allows the caller to specify if a separate body should be constructed
	* to represent the void volume, or if the void volume region should remain part of the input body.
	* The default behavior is to construct a new body to represent the void volume region.
	*/
	void set_separate(logical new_separate_value);

	/**
	* Return the value of the separate flag.
	*/
	logical get_separate();

};

/** @} */

#endif
