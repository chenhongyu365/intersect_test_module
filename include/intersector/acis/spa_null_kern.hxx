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

#ifndef SPA_NULL_KERN_HXX
#define SPA_NULL_KERN_HXX

#include "dcl_kern.h"
#include "bl_enum.hxx"  // Needed to declare bl_ed_convexity on Linux and MAC.


class surf_princurv;
class ENTITY_LIST;
class scan_list;
class curve;
class intcurve;
class pcurve;
class surface;
class spline;
class check_fix;
class plane;
class extension_info;
class outcome;
class discontinuity_info;
class BODY;
class list_of_contacts;
class EDGE;

using bs2_curve = class bs2_curve_def*;
using bs3_surface = class bs3_surf_def*;

class ELEM2D;
class cu_clash_list;
class sf_clash_list;
class blend_section;
class gedge;
enum error_type:int;
/**
 * @file spa_null_kern.hxx
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
		 * Returns true if the given surf_princurv is same as null surf_princurv object
		 * returned by the function SpaAcis::NullObj::get_surf_princurv
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param surf_prin_crv
		 * surf_princurv to be checked
		 */
		DECL_KERN bool check_surf_princurv(const surf_princurv& surf_prin_crv);

		/**
		 * Returns null surf_princurv object. The following function should only be
		 * used for passing default surf_princurv object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN surf_princurv& get_surf_princurv();

		/**
		 * Returns true if the given ENTITY_LIST is same as null ENTITY_LIST object
		 * returned by the function SpaAcis::NullObj::get_ENTITY_LIST
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param list
		 * ENTITY_LIST to be checked
		 */
		DECL_KERN bool check_ENTITY_LIST(const ENTITY_LIST& list);

		/**
		 * Returns null outcome object. The following function should only be
		 * used for passing default outcome object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN outcome& get_outcome();

		/**
		* Returns true if the given outcome is same as null outcome object
		* returned by the function SpaAcis::NullObj::get_outcome
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param outc
		* outcome to be checked
		*/
		DECL_KERN bool check_outcome(const outcome& outc);

		/**
		 * Returns null ENTITY_LIST object. The following function should only be
		 * used for passing default ENTITY_LIST object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN ENTITY_LIST& get_ENTITY_LIST();

		/**
		 * Returns true if the given scan_list is same as null scan_list object
		 * returned by the function SpaAcis::NullObj::get_scan_list().
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param list
		 * scan_list to be checked
		 */
		DECL_KERN bool check_scan_list( const scan_list& list );

		/**
		 * Returns null scan_list object. The following function should only be
		 * used for passing default scan_list object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN scan_list& get_scan_list();

		/**
		 * Returns true if the given intcurve is same as null intcurve object
		 * returned by the function SpaAcis::NullObj::get_intcurve().
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param icurv
		 * intcurve to be checked
		 */
		DECL_KERN bool check_intcurve(const intcurve& icurv);

		/**
		 * Returns null intcurve object. The following function should only be
		 * used for passing default intcurve object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN intcurve& get_intcurve();

		/**
		 * Returns true if the given curve is same as null curve object
		 * returned by the function SpaAcis::NullObj::get_curve
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param curv
		 * curve to be checked
		 */
		DECL_KERN bool check_curve(const curve& curv);

		/**
		 * Returns null curve object. The following function should only be
		 * used for passing default curve object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN curve& get_curve();

		/**
		 * Returns true if the given pcurve is same as null pcurve object
		 * returned by the function SpaAcis::NullObj::get_pcurve
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param pcur
		 * pcurve to be checked
		 */
		DECL_KERN bool check_pcurve(const pcurve& pcur);

		/**
		 * Returns null pcurve object. The following function should only be
		 * used for passing default pcurve object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN pcurve& get_pcurve();

		/**
		 * Returns true if the given pcurve* is same as null pcurve*
		 * returned by the function SpaAcis::NullObj::get_pcurve_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * pcurve* to be checked
		 */
		DECL_KERN bool check_pcurve_ptr(const pcurve* const& val);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_pcurve_ptr(pcurve* const& val);

		/**
		 * Returns null pcurve* object as a reference. The following function should only be
		 * used for passing default pcurve*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN pcurve*& get_pcurve_ptr();


		/**
		 * Returns true if the given surface is same as null surface object
		 * returned by the function SpaAcis::NullObj::get_surface
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param surf
		 * surface to be checked
		 */
		DECL_KERN bool check_surface(const surface& surf);

		/**
		 * Returns null surface object. The following function should only be
		 * used for passing default surface object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN surface& get_surface();

		/**
		 * Returns true if the given spline is same as null spline object
		 * returned by the function SpaAcis::NullObj::get_spline().
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param spl
		 * spline to be checked
		 */
		DECL_KERN bool check_spline( const spline& spl );

		/**
		 * Returns null spline object. The following function should only be
		 * used for passing default spline object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN spline& get_spline();

		/**
		* Returns true if the given check_fix is same as null check_fix object
		* returned by the function SpaAcis::NullObj::get_check_fix
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param chk_fix
		* check_fix to be checked
		*/
		DECL_KERN bool check_check_fix(const check_fix& chk_fix);

		/**
		 * Returns null check_fix object. The following function should only be
		 * used for passing default char object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN check_fix& get_check_fix();

		/**
		 * Returns true if the given plane is same as null plane object
		 * returned by the function SpaAcis::NullObj::get_plane
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param pl
		 * plane to be checked
		 */
		DECL_KERN bool check_plane(const plane& pl);

		/**
		 * Returns null plane object. The following function should only be
		 * used for passing default plane object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN plane& get_plane();

		/** 
		Returns true if the given bs2_curve is same as null bs2_curve object
		* returned by the function SpaAcis::NullObj::get_bs2_curve
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param bs2cur
		* char to be checked
		*/
		DECL_KERN bool check_bs2_curve(const bs2_curve& bs2cur);

		/**
		 * Returns null bs2_curve object. The following function should only be
		 * used for passing default char object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN bs2_curve& get_bs2_curve();

		/** 
		Returns true if the given bs3_surface is same as null bs3_surface object
		* returned by the function SpaAcis::NullObj::get_bs3_surface
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param bs3surf
		* char to be checked
		*/
		DECL_KERN bool check_bs3_surface(const bs3_surface& bs3surf);

		/**
		 * Returns null bs3_surface object. The following function should only be
		 * used for passing default char object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN bs3_surface& get_bs3_surface();

		/**
		* Returns true if the given extension_info is same as null extension_info object
		* returned by the function SpaAcis::NullObj::get_extension_info
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param info
		* extension_info to be checked
		*/
		DECL_KERN bool check_extension_info(const extension_info& info);

		/**
		 * Returns null extension_info object. The following function should only be
		 * used for passing default extension_info object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN extension_info& get_extension_info();

		/**
		* Returns true if the given bl_ed_convexity is same as null bl_ed_convexity object
		* returned by the function SpaAcis::NullObj::get_bl_ed_convexity
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param cvxty
		* bl_ed_convexity to be checked
		*/
		DECL_KERN bool check_bl_ed_convexity(const bl_ed_convexity& cvxty);

		/**
		 * Returns null bl_ed_convexity object. The following function should only be
		 * used for passing default bl_ed_convexity object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN bl_ed_convexity& get_bl_ed_convexity();

		/**
		* Returns true if the given discontinuity_info is same as null discontinuity_info object
		* returned by the function SpaAcis::NullObj::get_discontinuity_info
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param disc
		* discontinuity_info to be checked
		*/
		DECL_KERN bool check_discontinuity_info(const discontinuity_info& disc);

		/**
		 * Returns null discontinuity_info object. The following function should only be
		 * used for passing default discontinuity_info object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN discontinuity_info& get_discontinuity_info();

		/**
		 * Returns true if the given surface* is same as null surface*
		 * returned by the function SpaAcis::NullObj::get_surface_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param surf
		 * const surface* to be checked
		 */
		DECL_KERN bool check_surface_ptr(const surface* const& surf);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_surface_ptr(surface* const& surf);

		/**
		 * Returns null surface* as a reference. The following function should only be
		 * used for passing default surface*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN surface*& get_surface_ptr();
		

		/**
		 * Returns true if the given ELEM2D* is same as null ELEM2D*
		 * returned by the function SpaAcis::NullObj::get_ELEM2D_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * ELEM2D* to be checked
		 */
		DECL_KERN bool check_ELEM2D_ptr(const ELEM2D* const& val);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_ELEM2D_ptr(ELEM2D* const& val);

		/**
		 * Returns null ELEM2D* object as a reference. The following function should only be
		 * used for passing default ELEM2D*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN ELEM2D*& get_ELEM2D_ptr();

		/**
		 * Returns true if the given cu_clash_list* is same as null cu_clash_list*
		 * returned by the function SpaAcis::NullObj::get_cu_clash_list_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * cu_clash_list* to be checked
		 */
		DECL_KERN bool check_cu_clash_list_ptr(const cu_clash_list* const& val);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_cu_clash_list_ptr(cu_clash_list* const& val);
		
		/**
		 * Returns null cu_clash_list* object as a reference. The following function should only be
		 * used for passing default cu_clash_list*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN cu_clash_list*& get_cu_clash_list_ptr();
		
		/**
		 * Returns true if the given sf_clash_list* is same as null sf_clash_list*
		 * returned by the function SpaAcis::NullObj::get_sf_clash_list_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param val
		 * sf_clash_list* to be checked
		 */
		DECL_KERN bool check_sf_clash_list_ptr(const sf_clash_list* const& val);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_sf_clash_list_ptr(sf_clash_list* const& val);

		/**
		 * Returns null sf_clash_list* object as a reference. The following function should only be
		 * used for passing default sf_clash_list*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN sf_clash_list*& get_sf_clash_list_ptr();

		/**
		 * Returns true if the given blend_section is same as null blend_section object
		 * returned by the function SpaAcis::NullObj::get_blend_section
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param blend_sect
		 * blend_section to be checked
		 */
		DECL_KERN bool check_blend_section(const blend_section& blend_sect);

		/**
		 * Returns null blend_section object. The following function should only be
		 * used for passing default blend_section object to ACIS interfaces,
		 * wherever applicable. The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN blend_section& get_blend_section();

		/**
		 * Returns true if the given error_type is same as null error_type enum
		 * returned by the function SpaAcis::NullObj::get_error_type
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param error_typ
		 * error_type to be checked
		 */
		DECL_KERN bool check_error_type(const error_type& error_typ);

		/**
		 * Returns null error_type enum. The following function should only be
		 * used for passing default error_type enum to ACIS interfaces,
		 * wherever applicable. The returned enum should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN error_type& get_error_type();
	
		/**
		 * Returns true if the given BODY* is same as null BODY*
		 * returned by the function SpaAcis::NullObj::get_body_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param body
		 * const BODY* to be checked
		 */
		DECL_KERN bool check_body_ptr(const BODY* const& body);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_body_ptr(BODY* const& body);

		/**
		 * Returns null BODY* as a reference. The following function should only be
		 * used for passing default BODY*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN BODY*& get_body_ptr();

		/**
		 * Returns true if the given EDGE* is same as null EDGE*
		 * returned by the function SpaAcis::NullObj::get_edge_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param edge
		 * const EDGE* to be checked
		 */
		DECL_KERN bool check_edge_ptr(const EDGE* const& edge);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_edge_ptr(EDGE* const& edge);

		/**
		 * Returns null EDGE* as a reference. The following function should only be
		 * used for passing default EDGE*& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN EDGE*& get_edge_ptr();

		/**
		* Returns true if the given list_of_contacts is same as null list_of_contacts object
		* returned by the function SpaAcis::NullObj:: get_list_of_contacts
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		* <br><br>
		* @param list_of_contacts
		* list_of_contacts to be checked
		*/
		DECL_KERN bool check_list_of_contacts(const list_of_contacts& list_contacts);

	   /**
		* Returns null list_of_contacts object. The following function should only be
		* used for passing default list_of_contacts object to ACIS interfaces,
		* wherever applicable. The returned object's data should not be overwritten.
		* <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		*/
		DECL_KERN list_of_contacts& get_list_of_contacts();

		/**
		 * Returns true if the given gedge** is same as null gedge**
		 * returned by the function SpaAcis::NullObj::get_gedge_ptr_ptr
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 * <br><br>
		 * @param gedge_ptr
		 * const gedge** to be checked
		 */
		DECL_KERN bool check_gedge_ptr_ptr(const gedge*const*const& gedge_ptr);

		/**
		* @nodoc
		*/
		DECL_KERN bool check_gedge_ptr_ptr(gedge**& gedge_ptr);
		/**
		* @nodoc
		*/
		DECL_KERN bool check_gedge_ptr_ptr(gedge** const& gedge_ptr);
		/**
		* @nodoc
		*/
		DECL_KERN bool check_gedge_ptr_ptr(gedge* const* const& gedge_ptr);


		/**
		 * Returns null gedge** as a reference. The following function should only be
		 * used for passing default gedge**& to ACIS interfaces, wherever applicable.
		 * The returned object's data should not be overwritten.
		 * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
		 */
		DECL_KERN gedge**& get_gedge_ptr_ptr();

	} // namespace `NullObj`

} // namespace `SpaAcis


/** @} */
#endif
