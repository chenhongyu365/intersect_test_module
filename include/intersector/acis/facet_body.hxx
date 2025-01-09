/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef FACET_BODY_HXX
#define FACET_BODY_HXX

//======================================================================

#include "dcl_kern.h"
#include "entity.hxx"
#include "api.hxx"
#include "SPA_raw_mesh.hxx"

 /**
  * @file facet_body.hxx
  * @CAA2Level L1
  * @CAA2Usage U2
  * \addtogroup KERNAPI
  *
  * @{
  */

 // Identifier used to identity the type of an entity pointer.
extern DECL_KERN int FACET_BODY_TYPE;

// Identifier that gives number of levels of derivation of this class from ENTITY.
#define FACET_BODY_LEVEL 1

/**
 * @nodoc
 */
ENTITY_IS_PROTOTYPE(FACET_BODY, KERN)
#if 0
; // semicolon needed for mkman (doc tool) parsing
#endif


/**
* @nodoc
*/
struct FACET_BODY_data;


/**
 * FACET_BODY represents triangular raw mesh. 
 * <br>
 * <b>Role:</b> A <tt>FACET_BODY</tt> is an Entity that wraps raw mesh pointer.
 * <br><br>
 */

class DECL_KERN FACET_BODY : public ENTITY
{
	// allows internal clients to declare themselves friend of FACET_BODY
#ifdef FACET_BODY_FRIENDS
	FACET_BODY_FRIENDS
#endif
	/**
	* @nodoc
	*/
	unsigned int _version;
	
	/**
	* @nodoc
	*/
	FACET_BODY_data* _data;
public:
	/**
	 * C++ constructor, creating a <tt>FACET_BODY</tt>.
	 * <br><br>
	 * <b>Role:</b> Applications should never directly call this constructor.
	 */
	FACET_BODY();

	ENTITY_FUNCTIONS(FACET_BODY, KERN)
#if 0
		; // semicolon needed for mkman (doc tool) parsing)
#endif
	
	/**
	* Returns number of faces.
	*/
	int num_faces() const;
	
	/**
	* Returns SPA_raw_mesh of a face.
	*/
	Spa_raw_mesh const& get_face_mesh(int which_face) const;
	
	/**
	* Returns SPA_raw_mesh of a complete body. 
	* There are not duplicate nodes around a boundary. 
	* This raw mesh might have anomalies with it so it needs to be healed. 
	*/
	Spa_raw_mesh const& get_body_mesh() const;

	FACET_BODY& operator=(FACET_BODY const& other);
};

/** @} */
#endif

