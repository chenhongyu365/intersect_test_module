/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#pragma once

/**
 * @file spa_null_blnd.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \addtogroup ACISGEOMOPERATORS
 *
 * @details This header file provides the set of functions which return valid
 * objects which are treated as NULL objects in `SPAblnd`. These NULL
 * objects are supposed to be used as a replacement of NULL_REF usage.
 * e.g. SPA_blend_face_info &info = *(SPA_blend_face_info*)NULL_REF;
 * Since this concept of NULL_REF is not being supported by modern
 * compilers, we have come up with these replacement objects, which
 * can be accessed by SpaAcis::NullObj::get_***, and compared against other
 * objects by calling SpaAcis::NullObj::check_*** functions.*
 * @{
 */

#include "dcl_blnd.h"

class SPA_blend_face_info;
class bl_sided_par_pos;

namespace SpaAcis {
    namespace NullObj {

        /**
         * Returns true if the given SPA_blend_face_info is same as null SPA_blend_face_info object
         * returned by the function SpaAcis::NullObj::get_SPA_blend_face_info
         * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
         * <br><br>
         * @param info
         * SPA_blend_face_info to be checked
         */
        DECL_BLND bool check_SPA_blend_face_info(const SPA_blend_face_info& info);

        /**
         * Returns null SPA_blend_face_info object. The following function should only be
         * used for passing default SPA_blend_face_info object to ACIS interfaces,
         * wherever applicable. The returned object's data should not be overwritten.
         * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
         */
        DECL_BLND SPA_blend_face_info& get_SPA_blend_face_info();

        /**
         * Returns true if the given bl_sided_par_pos is same as null bl_sided_par_pos object
         * returned by the function SpaAcis::NullObj::get_bl_sided_par_pos
         * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
         * <br><br>
         * @param pos
         * bl_sided_par_pos to be checked
         */
        DECL_BLND bool check_bl_sided_par_pos(const bl_sided_par_pos& pos);

        /**
         * Returns null bl_sided_par_pos object. The following function should only be
         * used for passing default bl_sided_par_pos object to ACIS interfaces,
         * wherever applicable. The returned object's data should not be overwritten.
         * <br><b>Technical Article:</b> <i>[NULL_REF Removal](http://doc.spatial.com/articles/n/u/l/NULL_REF_Removal_701d.html)</i>
         */
        DECL_BLND bl_sided_par_pos& get_bl_sided_par_pos();

    }  // namespace NullObj
}  // namespace SpaAcis

/** @} */
