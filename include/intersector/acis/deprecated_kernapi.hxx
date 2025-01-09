/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
//         ACIS Kernel Component - Deprecated Interfaces
/*******************************************************************/
#ifndef DEPRECATED_KERNAPI_HXX
#define DEPRECATED_KERNAPI_HXX

#include "api.hxx"
#include "dcl_kern.h"
#include "entity.hxx"



// This function is for internal use only.
// It was deprecated in R16.

/**
 * @nodoc
 * Creates a copy of an <tt>ENTITY</tt> all its associated subentities.
 * <br><br>
 * <b>Role:</b> This API copies the given <tt>ENTITY</tt> and all its associated
 * subentities, if any. Subentities are those that are <i>below</i> the given
 * <tt>ENTITY</tt> in the topological hierarchy. It <i>does not</i> copy entities
 * that are above the given <tt>ENTITY</tt>. The optional transformation is applied
 * to the copied entity, if applicable.
 * <br><br>
 * <b>Note:</b> This special-case function only operates on <tt>VERTEX</tt>, <tt>EDGE</tt>, <tt>COEDGE</tt>, <tt>WIRE</tt>,
 * <tt>LOOP</tt>, <tt>FACE</tt>, <tt>SHELL</tt>, and <tt>LUMP</tt> entities; for all other entity types, it calls
 * <tt>api_copy_entity</tt>.
 * <br><br>
 * <b>Note:</b> @href api_copy_entity copies all entities <b>above</b> and <b>below</b>
 * the input entity, while <tt>api_copy_entity_contents</tt> only copies all entities <b>below</b>
 * the input entity. If @href api_copy_entity is incorrectly used where <tt>api_copy_entity_contents</tt>
 * is intended, memory requirements could become unnecessarily and  adversely large.
 * <br><br>
 * <b>Important: This function was deprecated in R16. The API has been replaced by @href api_down_copy_entity.</b>
 * <br><br>
 * <b>Errors:</b> The pointer to an original entity is <tt>NULL</tt>.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
 * @param in_ent
 * entity to be copied.
 * @param copy
 * copy returned.
 * @param tr
 * optional transformation.
 * @param ao
 * ACIS options.
 * <br><br>
 * @see api_copy_entity, api_deep_copy_entity
 **/
DECL_KERN outcome api_copy_entity_contents(
	ENTITY* in_ent,
	ENTITY*& copy,
	const SPAtransf& tr = SPAtransf(),
	AcisOptions* ao = nullptr);


#endif  // DEPRECATED_KERNAPI_HXX
