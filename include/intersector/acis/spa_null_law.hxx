/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef SPA_NULL_LAW_HXX
#define SPA_NULL_LAW_HXX

#include "dcl_law.h"

class law_data_node;

/**
 * @file spa_null_law.hxx
 * @CAA2Level L1
 * @CAA2Usage U2
 * \addtogroup ACISKERNLAWS
 *
 * @{
 */

namespace SpaAcis
{
	namespace NullObj
	{
		/**
		 * Returns true if the given law_data_node* is same as null
		 * law_data_node* returned by the function 
		 * SpaAcis::NullObj::get_law_data_node_ptr.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param node
		 * law_data_node* to be checked
		 */
		DECL_LAW bool check_law_data_node_ptr( const law_data_node* const& node );


		/**
		* @nodoc
		*/
		DECL_LAW bool check_law_data_node_ptr(law_data_node* const& node);

		/**
		 * Returns null law_data_node* as a reference. The following function
		 * should only be used for passing default law_data_node* to ACIS
		 * interfaces, wherever applicable. The returned pointer should
		 * not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_LAW law_data_node*& get_law_data_node_ptr();
	}
}

/** @} */
#endif
