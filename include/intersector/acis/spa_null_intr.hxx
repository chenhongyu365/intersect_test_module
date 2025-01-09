/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
// This header file provides the set of functions which return valid 
// objects which are treated as NULL objects in SPAkern. These NULL 
// objects are supposed to be used as a replacement of NULL_REF usage. 
// e.g. SPAbox &box = *(SPAbox*)NULL_REF;
// Since this concept of NULL_REF is not being supported by modern 
// compilers, we have come up with these replacement objects, which 
// can be accessed by SpaAcis::NullObj::get_***, and compared against other 
// objects by calling SpaAcis::NullObj::check_*** functions.

#ifndef SPA_NULL_INTR_HXX
#define SPA_NULL_INTR_HXX

#include "dcl_intr.h"

class param_info;
class insanity_list;

/**
 * @file spa_null_intr.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup ACISGEOMOPERATORS
 *
 * @{
 */

namespace SpaAcis
{
	namespace NullObj
	{
		/**
		 * Returns true if the given param_info is same as null param_info object
		 * returned by the function SpaAcis::NullObj::get_param_info
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_info
		 * param_info to be checked
		 */
		DECL_INTR bool check_param_info(const param_info& par_info);

		/**
		 * Returns null param_info object. The following function should only be
		 * used for passing default param_info object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_INTR param_info& get_param_info();

		/**
		 * Returns true if the given insanity_list* is same as null insanity_list*
		 * returned by the function SpaAcis::NullObj::get_insanity_list_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * insanity_list* to be checked
		 */
		DECL_INTR bool check_insanity_list_ptr(const insanity_list* const& val);

		/**
		* @nodoc
		*/
		DECL_INTR bool check_insanity_list_ptr(insanity_list* const& val);

		/**
		 * Returns null insanity_list* object as a reference. The following function should only be
		 * used for passing default insanity_list*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_INTR insanity_list*& get_insanity_list_ptr();

	}
}

/** @} */
#endif
