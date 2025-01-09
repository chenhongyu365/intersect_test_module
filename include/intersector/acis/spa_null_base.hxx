/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
// This header file provides the set of functions which return valid 
// objects which are treated as NULL objects. These NULL objects are 
// supposed to be used as a replacement of NULL_REF usage. 
// e.g. SPAbox &box = *(SPAbox*)NULL_REF;
// Since this concept of NULL_REF is not being supported by modern 
// compilers, we have come up with these replacement objects, which 
// can be accessed by SpaAcis::NullObj::get_***, and compared against other 
// objects by calling SpaAcis::NullObj::check_*** functions.

#ifndef SPA_NULL_BASE_HXX
#define SPA_NULL_BASE_HXX

#include "dcl_base.h"
#include "logical.h"

class SPAparameter;
class SPAvector;
class SPAunit_vector;
class SPApar_pos;
class SPAposition;
class SPAbox;
class SPApar_box;
class SPApar_vec;
class SPAinterval;
class SPApar_transf;
class VOID_LIST;
class SPApar_dir;

/**
 * @file spa_null_base.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup ACISGEOMOPERATORS
 *
 * @{
 */

/**
 * This namespace contains functionality including the definition of null objects.
 */
namespace SpaAcis
{

/**
 * This namespace contains functionality related to the definition of null objects.
 */
	namespace NullObj
	{
		/**
		 * Returns true if the given SPAparameter is same as null SPAparameter object
		 * returned by the function SpaAcis::NullObj::get_parameter
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param parameter
		 * SPAparameter to be checked
		 */
		DECL_BASE bool check_parameter(const SPAparameter& parameter);

		/**
		 * Returns null SPAparameter object. The following function should only be
		 * used for passing default SPAparameter object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAparameter& get_parameter();

		/**
		 * Returns true if the given SPAvector is same as null SPAvector object
		 * returned by the function SpaAcis::NullObj::get_vector
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param vector
		 * SPAvector to be checked
		 */
		DECL_BASE bool check_vector(const SPAvector& vector);

		/**
		 * Returns null SPAvector object. The following function should only be
		 * used for passing default SPAvector object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAvector& get_vector();

		/**
		 * Returns true if the given SPAunit_vector is same as null SPAunit_vector object
		 * returned by the function SpaAcis::NullObj::get_unit_vector
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param vector
		 * SPAunit_vector to be checked
		 */
		DECL_BASE bool check_unit_vector(const SPAunit_vector& vector);

		/**
		 * Returns null SPAunit_vector object. The following function should only be
		 * used for passing default SPAunit_vector object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAunit_vector& get_unit_vector();

		/**
		 * Returns true if the given SPApar_pos is same as null SPApar_pos object
		 * returned by the function SpaAcis::NullObj::get_par_pos
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_pos
		 * SPApar_pos to be checked
		 */
		DECL_BASE bool check_par_pos(const SPApar_pos& par_pos);

		/**
		 * Returns null par_pos object. The following function should only be
		 * used for passing default SPApar_pos object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPApar_pos& get_par_pos();

		/**
		 * Returns true if the given SPAposition is same as null SPAposition object
		 * returned by the function SpaAcis::NullObj::get_position
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param position
		 * SPAposition to be checked
		 */
		DECL_BASE bool check_position(const SPAposition& position);

		/**
		 * Returns null SPAposition object. The following function should only be
		 * used for passing default SPAposition object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAposition& get_position();

		/**
		 * Returns true if the given SPAposition* is same as null SPAposition*
		 * returned by the function SpaAcis::NullObj::get_position_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * SPAposition* to be checked
		 */
		DECL_BASE bool check_position_ptr(const SPAposition* const& val);

		/**
		* @nodoc
		*/
		DECL_BASE bool check_position_ptr(SPAposition* const& val);

		/**
		 * Returns null SPAposition* object as a reference. The following function should only be
		 * used for passing default SPAposition*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAposition*& get_position_ptr();


		/**
		 * Returns true if the given SPAbox is same as null SPAbox object
		 * returned by the function SpaAcis::NullObj::get_box
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param box
		 * SPAbox to be checked
		 */
		DECL_BASE bool check_box(const SPAbox& box);

		/**
		 * Returns null SPAbox object. The following function should only be
		 * used for passing default SPAbox object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAbox& get_box();

		/**
		 * Returns true if the given SPApar_box is same as null SPApar_box object
		 * returned by the function SpaAcis::NullObj::get_par_box
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_box
		 * SPApar_box to be checked
		 */
		DECL_BASE bool check_par_box(const SPApar_box& par_box);

		/**
		 * Returns null SPApar_box object. The following function should only be
		 * used for passing default SPApar_box object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPApar_box& get_par_box();

		/**
		 * Returns true if the given SPApar_vec is same as null SPApar_vec object
		 * returned by the function SpaAcis::NullObj::get_par_vec
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_vec
		 * SPApar_vec to be checked
		 */
		DECL_BASE bool check_par_vec(const SPApar_vec& par_vec);

		/**
		 * Returns null SPApar_vec object. The following function should only be
		 * used for passing default SPApar_vec object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPApar_vec& get_par_vec();

		/**
		 * Returns true if the given SPApar_dir is same as null SPApar_dir object
		 * returned by the function SpaAcis::NullObj::get_par_dir
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_vec
		 * SPApar_dir to be checked
		 */
		DECL_BASE bool check_par_dir(const SPApar_dir& par_vec);

		/**
		 * Returns null SPApar_dir object. The following function should only be
		 * used for passing default SPApar_dir object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPApar_dir& get_par_dir();

		/**
		 * Returns true if the given double is same as null double object
		 * returned by the function SpaAcis::NullObj::get_double
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * double to be checked
		 */
		DECL_BASE bool check_double(const double& val);

		/**
		 * Returns null double object. The following function should only be
		 * used for passing default double object to ACIS interfaces,
		 * wherever applicable. The returned object's value should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE double& get_double();

		 /**
		 * Returns true if the given integer is same as null integer object
		 * returned by the function SpaAcis::NullObj::get_int
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * integer to be checked
		 */
		DECL_BASE bool check_int(const int& val);

		/**
		 * Returns null integer object. The following function should only be
		 * used for passing default integer object to ACIS interfaces,
		 * wherever applicable. The returned object's value should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE int& get_int();

		/**
		 * Returns true if the given unsigned is same as null unsigned object
		 * returned by the function SpaAcis::NullObj::get_unsigned
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * unsigned to be checked
		 */
		DECL_BASE bool check_unsigned(const unsigned& val);

		/**
		 * Returns null unsigned object. The following function should only be
		 * used for passing default integer object to ACIS interfaces,
		 * wherever applicable. The returned object's value should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE unsigned& get_unsigned();

		/**
		 * Returns true if the given logical is same as null logical object
		 * returned by the function SpaAcis::NullObj::get_logical
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * logical to be checked
		 */
		DECL_BASE bool check_logical(const logical& val);

		/**
		 * Returns null logical object. The following function should only be
		 * used for passing default logical object to ACIS interfaces,
		 * wherever applicable. The returned object's value should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE logical& get_logical();
		
		/**
		 * Returns true if the given logical* is same as null logical*
		 * returned by the function SpaAcis::NullObj::get_logical_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * logical* to be checked
		 */
		DECL_BASE bool check_logical_ptr(const logical* const& val);

		/**
		* @nodoc
		*/
		DECL_BASE bool check_logical_ptr(logical* const& val);

		/**
		 * Returns null logical* object as a reference. The following function should only be
		 * used for passing default logical*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE logical*& get_logical_ptr();

		/**
		 * Returns true if the given SPAinterval is same as null SPAinterval object
		 * returned by the function SpaAcis::NullObj::get_interval
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param interval
		 * SPAinterval to be checked
		 */
		DECL_BASE bool check_interval(const SPAinterval& interval);

		/**
		 * Returns null SPAinterval object. The following function should only be
		 * used for passing default SPAinterval object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPAinterval& get_interval();

		/**
		 * Returns true if the given SPApar_transf is same as null SPApar_transf object
		 * returned by the function SpaAcis::NullObj::get_par_transf
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param par_transf
		 * SPApar_transf to be checked
		 */
		DECL_BASE bool check_par_transf(const SPApar_transf& par_transf);

		/**
		 * Returns null SPApar_transf object. The following function should only be
		 * used for passing default SPApar_transf object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE SPApar_transf& get_par_transf();

		/**
		 * Returns true if the given char* is same as null char* 
		 * returned by the function SpaAcis::NullObj::get_const_char_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param ch
		 * const char* to be checked
		 */
		DECL_BASE bool check_const_char_ptr(const char* const & ch);

		/**
		* @nodoc
		*/
		DECL_BASE bool check_const_char_ptr(char* const& ch);

		/**
		 * Returns null const char* object as a reference. The following function should only be
		 * used for passing default const char*& to ACIS interfaces, wherever applicable. 
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE const char*& get_const_char_ptr();

		/**
		 * Returns true if the given VOID_LIST is same as null VOID_LIST object
		 * returned by the function SpaAcis::NullObj::get_void_list.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param list
		 * VOID_LIST to be checked
		 */
		DECL_BASE bool check_void_list( const VOID_LIST& list );

		/**
		 * Returns null VOID_LIST object. The following function should only be
		 * used for passing default VOID_LIST object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE VOID_LIST& get_void_list();

		/**
		 * Returns true if the given double* is same as null double*
		 * returned by the function SpaAcis::NullObj::get_double_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * const double* to be checked
		 */
		DECL_BASE bool check_double_ptr(const double* const& val);

		/**
		* @nodoc
		*/
		DECL_BASE bool check_double_ptr(double* const& val);

		/**
		 * Returns null double* as a reference. The following function should only be
		 * used for passing default double*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_BASE double*& get_double_ptr();

	}
}

/** @} */
#endif
