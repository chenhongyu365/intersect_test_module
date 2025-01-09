/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#include "blend_examples.hxx"

#include "acis/ablapi.hxx"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/api.err"
#include "acis/bl1_data.hxx"
#include "acis/blendapi.hxx"
#include "acis/blndanno.hxx"
#include "acis/blndopts.hxx"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/ellipse.hxx"
#include "acis/geom_utl.hxx"
#include "acis/intrapi.hxx"
#include "acis/kernapi.hxx"
#include "acis/kernopts.hxx"
#include "acis/law_base.hxx"
#include "acis/lop_api.hxx"
#include "acis/mk_face.hxx"
#include "acis/pladef.hxx"
#include "acis/queryapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/ro_const.hxx"
#include "acis/roll_utl.hxx"
#include "acis/surface.hxx"
#include "acis/transfrm.hxx"
#include "acis/v_bl_att.hxx"
#include "acis/warp_api.hxx"
#include "acis/wire_utl.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_wiggle_const: constant radius blend on a wiggle
//
// APIs:
//    api_set_const_rounds
//    api_fix_blends
//
// Description:
//	  Demonstrates making constant radius blend between a spline and a cylindrical
//    surface.
// **********************************************************************************

outcome aei_BLEND_WIGGLE_CONST(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.0;            // block size
    double const R = H / 2.;          // cylinder radius
    double const blend_radius = 4.0;  // blend radius

    BODY* blend_body = NULL;
    API_BEGIN

    // Create a circular cylinder.

    BODY* cylinder = NULL;
    check_outcome(api_make_frustum(H, R, R, R, cylinder));

    // Cut away half of it with a block. The block is initially created centered
    // at the origin, it needs to be moved so that one of the vertical faces is
    // coincident with a diameter of the base ellipse of the cylinder.

    BODY* block = NULL;
    check_outcome(api_make_cuboid(2 * R, 2 * R, H, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(0, R, 0))));
    check_outcome(api_subtract(block, cylinder));

    // Move the half-cylinder up a little.

    check_outcome(api_apply_transf(cylinder, translate_transf(SPAvector(0, 0, H / 4))));

    // Create a wiggle and place it under the half-cylinder such that the
    // vertical planar face of the half-cylinder is above one of the
    // vertical faces of the wiggle.

    BODY* wiggle = NULL;
    check_outcome(api_wiggle(2 * H, H, H / 2, 1, 2, -1, -2, TRUE, wiggle));
    check_outcome(api_apply_transf(wiggle, translate_transf(SPAvector(0, -H / 2, 0))));

    // Unite wiggle and half-cylinder

    check_outcome(api_unite(cylinder, wiggle));
    blend_body = wiggle;

    // Pick the round edge between the cylindrical face and the wiggle.

    ENTITY_LIST edge_list;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, -R, H / 4), 1, EDGE_TYPE, blend_body, edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Assign a constant radius blend attribute to this edge and
    // fix the blend.

    check_outcome(api_set_const_rounds(edge_list, blend_radius));
    check_outcome(api_fix_blends(edge_list, pAcisOpt));

    // Highlight the new blend surface.

    ENTITY_LIST face_list;
    check_outcome(api_get_ents(SPAposition(0, -R / 10, 0), SPAunit_vector(0, -R, H / 4), 0.1, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_wiggle_var: variable radius blend on a wiggle
//
// APIs:
//    api_set_var_blends
//    api_fix_blends
//
// Description:
//	  Demonstrates making variable radius blend between a spline and a cylindrical
//    surfaces.
// **********************************************************************************

outcome aei_BLEND_WIGGLE_VAR(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.;     // block size
    double const R = H / 2.;  // cylinder radius
    double const r = 1.;      // minimum blend radius

    BODY* blend_body = NULL;
    API_BEGIN

    // Create a circular cylinder.

    BODY* cylinder = NULL;
    check_outcome(api_make_frustum(1.1 * H, R, R, R, cylinder));

    // Cut away half of it with a block. The block is initially created centered
    // at the origin, it needs to be moved so that one of the vertical faces is
    // coincident with a diameter of the base ellipse of the cylinder.

    BODY* block = NULL;
    check_outcome(api_make_cuboid(2 * R, 2 * R, 1.1 * H, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(0, R, 0))));
    check_outcome(api_subtract(block, cylinder));

    // Move the half-cylinder up a little.

    check_outcome(api_apply_transf(cylinder, translate_transf(SPAvector(0, 0, 3. * H / 4))));

    // Create a wiggle and place it under the half-cylinder such that the
    // vertical planar face of the half-cylinder is above one of the
    // vertical faces of the wiggle.

    BODY* wiggle = NULL;
    check_outcome(api_wiggle(2 * H, H, H / 2, 1, 2, -1, -2, TRUE, wiggle));
    check_outcome(api_apply_transf(wiggle, translate_transf(SPAvector(0, -H / 2, 0))));

    // Unite wiggle and half-cylinder

    check_outcome(api_unite(cylinder, wiggle));
    blend_body = wiggle;

    // Pick the round edge between the cylindrical face and the wiggle.

    ENTITY_LIST edge_list;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, -R, H / 4), 1, EDGE_TYPE, blend_body, edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Assign a variable radius blend attribute to this edge and
    // fix the blend.

    check_outcome(api_set_var_blends(edge_list, r, 8 * r, 0., 0.));
    check_outcome(api_fix_blends(edge_list, pAcisOpt));

    // Highlight the new blend surface.

    ENTITY_LIST face_list;
    check_outcome(api_get_ents(SPAposition(0, -R / 10, 0), SPAunit_vector(0, -R, H / 4), 0.1, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_holdline: holdline blend on an elliptical edge.
//
// APIs:
//    api_blend_holdline
//    api_make_radius_holdline
//    api_smooth_edges_to_curve
//    api_set_abh_blends
//    api_fix_blends
//
// Description:
//    Demonstrates implicit variable radius blending with holdline.
// **********************************************************************************

outcome aei_BLEND_HOLDLINE(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    API_BEGIN

    // Create a holdline blend using api_blend_holdline.

    {
        // Create a blend body by uniting a block and a tilted cylinder so that we get
        // elliptical edges for blending.

        BODY *blend_body = NULL, *cyl = NULL;
        check_outcome(api_make_cuboid(50, 50, 10, blend_body));
        check_outcome(api_make_frustum(50, 5, 5, 5, cyl));
        check_outcome(api_apply_transf(cyl, rotate_transf(.349, SPAvector(1, 0, 0))));
        check_outcome(api_unite(cyl, blend_body));

        // Pick one of the elliptical edges between the cylinder and one of the
        // horizontal faces of the block.

        ENTITY_LIST picked_edges;
        double* ray_params = NULL;
        check_outcome(api_get_ents(SPAposition(0, 0, 5), SPAunit_vector(-1, 0, 0), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }
        ENTITY_LIST blend_edges;
        blend_edges.add(picked_edges.first());

        // Create a circular edge coincident with the planar support face.

        SPAposition center(0, -1.819, 5);
        EDGE* circular_edge = NULL;
        check_outcome(api_curve_arc(center, 10, -M_PI, M_PI, circular_edge));
        ENTITY_LIST holdline_edges;
        holdline_edges.add(circular_edge);

        // Create a variable radius blend corresponding to the elliptical edge
        // using this circular edge as a holdline curve.

        check_outcome(api_blend_holdline(blend_edges, holdline_edges, TRUE, TRUE, pAcisOpt));
        check_outcome(api_del_entity(circular_edge));

        output_ents.add(blend_body);

        // Highlight the new blend surface.

        ENTITY_LIST face_list;
        check_outcome(api_get_ents(SPAposition(0, -10., 5), SPAunit_vector(0, 0, 1.), 0.1, FACE_TYPE, blend_body, face_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }
        check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));
    }

    // Now do it with the api for building holdline radius functions.

    {
        // Create a blend body by uniting a block and a tilted cylinder so that we get
        // elliptical edges for blending.

        BODY *blend_body = NULL, *cyl = NULL;
        check_outcome(api_make_cuboid(50, 50, 10, blend_body));
        check_outcome(api_make_frustum(50, 5, 5, 5, cyl));
        check_outcome(api_apply_transf(cyl, rotate_transf(.349, SPAvector(1, 0, 0))));
        check_outcome(api_unite(cyl, blend_body));

        // Pick one of the elliptical edges between the cylinder and one of the
        // horizontal faces of the block.

        ENTITY_LIST picked_edges;
        double* ray_params = NULL;
        check_outcome(api_get_ents(SPAposition(0, 0, 5), SPAunit_vector(-1, 0, 0), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }
        ENTITY_LIST blend_edges;
        blend_edges.add(picked_edges.first());

        // Create a circular edge coincident with the planar support face.

        SPAposition center(0, -1.819, 5);
        EDGE* circular_edge = NULL;
        check_outcome(api_curve_arc(center, 10, -M_PI, M_PI, circular_edge));
        ENTITY_LIST holdline_edges;
        holdline_edges.add(circular_edge);

        // Create a holdline variable radius function.

        var_radius* vrad = NULL;
        check_outcome(api_make_radius_holdline(circular_edge, vrad));

        // Create a calibration curve corresponding to this holdline edge.

        CURVE* calibration_curve = NULL;
        EDGE *first_edge = NULL, *last_edge = NULL;
        check_outcome(api_smooth_edges_to_curve(circular_edge, calibration_curve, first_edge, last_edge));

        // Assign a variable radius holdline blend attribute to the elliptical
        // edge and fix the blend.

        check_outcome(api_set_abh_blends(blend_edges, vrad, NULL, NULL, calibration_curve, first_edge, last_edge));
        if(calibration_curve) calibration_curve->remove();
        check_outcome(api_fix_blends(blend_edges, pAcisOpt));
        check_outcome(api_del_entity(circular_edge));

        output_ents.add(blend_body);

        // Highlight the new blend surface.

        ENTITY_LIST face_list;
        check_outcome(api_get_ents(SPAposition(0, -10., 5), SPAunit_vector(0, 0, 1.), 0.1, FACE_TYPE, blend_body, face_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }
        check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));
    }

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_elliptical: variable radius blend with the elliptical cross section
//
// APIs:
//    api_smooth_edges_to_curve
//    api_make_radius_rot_ellipse
//    api_set_abh_blends
//    api_set_ee_vr_blend
//    api_fix_blends
//
// Description:
//	  Demonstrates making variable radius blend with the elliptical cross section.
// **********************************************************************************

outcome aei_BLEND_ELLIPTICAL(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 60.0;  // block size
    double const r = 10.0;
    double const R = 50.0;
    double const maj_angle = degrees_to_radians(0.);

    BODY* blend_body = NULL;
    API_BEGIN

    // Create a block.

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    {
        // Pick a vertical edge for blending with elliptical cross section.

        ENTITY_LIST edge_list;
        double* ray_params = NULL;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(1, 1, 0), H / 100, EDGE_TYPE, blend_body, edge_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        // Create defining curve for the blend from this edge.

        CURVE* calibration_curve = NULL;
        EDGE *first_edge = NULL, *last_edge = NULL;
        check_outcome(api_smooth_edges_to_curve(edge_list, calibration_curve, first_edge, last_edge));

        // Create a variable radius object.

        var_radius* rad_obj = NULL;
        double const maj_start = R, maj_end = r;
        double const min_start = r, min_end = r;
        double const maj_angle_start = maj_angle, maj_angle_end = maj_angle;
        check_outcome(api_make_radius_rot_ellipse(maj_start, maj_end, min_start, min_end, maj_angle_start, maj_angle_end, TRUE,  // TRUE means left face is reference face
                                                  rad_obj, pAcisOpt));

        // Assign a variable radius elliptical cross section blend attribute to
        // the vertical edge and fix the blend.

        var_cross_section* xSect = ACIS_NEW var_cross_section(ROT_ELLIPSE);
        check_outcome(api_set_abh_blends(edge_list,  // entities to be blended
                                         rad_obj,    // left radius function
                                         NULL,       // right radius function, same as right if NULL
                                         xSect,      // cross section, circular if NULL
                                         calibration_curve, first_edge, last_edge));
        check_outcome(api_fix_blends(edge_list, pAcisOpt));
        if(calibration_curve) calibration_curve->remove();

        // Highlight the new blend surface.

        ENTITY_LIST face_list;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(1, 1, 0), H / 100, FACE_TYPE, blend_body, face_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }
        check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));
    }

    {
        // Pick a vertical edge for blending with elliptical cross section.

        ENTITY_LIST edge_list;
        double* ray_params = NULL;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(-1, 1, 0), H / 100, EDGE_TYPE, blend_body, edge_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        // Create defining curve for the blend from this edge.

        CURVE* calibration_curve = NULL;
        EDGE *first_edge = NULL, *last_edge = NULL;
        check_outcome(api_smooth_edges_to_curve(edge_list, calibration_curve, first_edge, last_edge));

        // Create a variable radius object.

        var_radius* rad_obj = NULL;
        double const maj_start = R, maj_end = R;
        double const min_start = r, min_end = R;
        double const maj_angle_start = maj_angle, maj_angle_end = maj_angle;
        check_outcome(api_make_radius_rot_ellipse(maj_start, maj_end, min_start, min_end, maj_angle_start, maj_angle_end, TRUE,  // TRUE means left face is reference face
                                                  rad_obj, pAcisOpt));

        // Pick the face at X = -H/2, which was not altered by blending yet

        ENTITY_LIST supp_face_list;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(-1, 0, 0), 1, FACE_TYPE, blend_body, supp_face_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        // Pick the diagonal edge made by the previous elliptical edge blending
        // operation.

        ENTITY_LIST supp_edge_list;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, 1, 0), H / 100, EDGE_TYPE, blend_body, supp_edge_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        // Assign a variable radius elliptical cross section blend attribute to
        // the vertical edge and fix the blend.

        var_cross_section* xSect = ACIS_NEW var_cross_section(ROT_ELLIPSE);
        check_outcome(api_set_ee_vr_blend(blend_body, supp_face_list.first(), supp_edge_list.first(), bl_convex, SPAposition(-H / 4, H / 4, 0), calibration_curve->equation(), rad_obj, NULL, xSect, pAcisOpt));

        ENTITY_LIST body_list;
        body_list.add(blend_body);
        check_outcome(api_fix_blends(body_list, pAcisOpt));
        if(calibration_curve) calibration_curve->remove();

        // Highlight the new blend surface.

        ENTITY_LIST face_list;
        check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(-1, 1, 0), H / 100, FACE_TYPE, blend_body, face_list, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(0, 0, 1)));
    }

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_radius_transition1: variable radius blend with smooth radius variation
//
// APIs:
//    api_smooth_edge_seq
//    api_set_const_rounds
//    api_abh_vblend
//    api_fix_blends
//
// Description:
//	  Demonstrates making variable radius blend with smooth radius variation.
// **********************************************************************************

outcome aei_BLEND_RADIUS_TRANSITION1(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 100.0;             // block size
    double const bottom_rad = 20.0;     // const blend radius (at the bottom of the block)
    double const top_rad_small = 2.0;   // small blend radius (on top)
    double const top_rad_large = 36.0;  // large blend radius (on top)
    BODY* blend_body = NULL;

    API_BEGIN

    // Join a block and cylinder such that the top and bottom planar faces
    // have one edge which is semi-circular.

    BODY* cylinder = NULL;
    check_outcome(api_make_cuboid(H / 2, H, H, blend_body));
    check_outcome(api_apply_transf(blend_body, translate_transf(SPAvector(-H / 4, 0, 0))));
    check_outcome(api_make_frustum(H, H / 2, H / 2, H / 2, cylinder));
    check_outcome(api_unite(cylinder, blend_body));

    // Pick round edge on the bottom face.

    ENTITY_LIST picked_edges;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(H / 2, 0, -H / 2), SPAunit_vector(1, 0, -1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Find the sequence of smooth edges containing the bottom edge, apply
    // constant radius blend attributes on this sequence and fix them.

    ENTITY_LIST bottom_edge_list;
    EDGE* bottom_circ_edge = (EDGE*)picked_edges.first();
    check_outcome(api_smooth_edge_seq(bottom_circ_edge, bottom_edge_list));
    check_outcome(api_set_const_rounds(bottom_edge_list, bottom_rad));
    check_outcome(api_fix_blends(bottom_edge_list, pAcisOpt));

    // Pick the circular edge on the top planar face and it's immediate
    // neighbouring edges on the top face.

    ENTITY_LIST top_edge_list;
    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition(-H / 4, -H / 2, H / 2), SPAunit_vector(0, -1, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_left_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_left_edge);

    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition(-H / 4, H / 2, H / 2), SPAunit_vector(0, 1, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_right_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_right_edge);

    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition(H / 2, 0, H / 2), SPAunit_vector(1, 0, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_circ_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_circ_edge);

    // Now, blend the top edges : small on left, large on right, and smooth
    // transition on the round edge

    check_outcome(api_set_const_rounds(top_left_edge, top_rad_small));
    check_outcome(api_set_const_rounds(top_right_edge, top_rad_large));
    check_outcome(api_abh_vblend(top_circ_edge, top_rad_small, top_rad_large));
    check_outcome(api_fix_blends(top_edge_list, pAcisOpt));

    // Highlight the new upper blend faces.

    ENTITY_LIST face_list;
    check_outcome(api_get_ents(SPAposition(-H / 4, 0, 0), SPAunit_vector(0, -1, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(0, 0, 1)));

    face_list.clear();
    check_outcome(api_get_ents(SPAposition(-H / 4, 0, 0), SPAunit_vector(0, 1, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(0, 0, 1)));

    face_list.clear();
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(1, 0, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_radius_transition2: variable radius blend with smooth radius variation
//
// APIs:
//    api_blend_edges_pos_rad
//
// Description:
//	  Demonstrates making variable radius blend with blend simplification and
//    radius function optimization (inside api_blend_edges_pos_rad).
// **********************************************************************************

outcome aei_BLEND_RADIUS_TRANSITION2(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 100.0;             // block size
    double const top_rad_small = 2.0;   // small blend radius (on top)
    double const top_rad_large = 36.0;  // large blend radius (on top)
    BODY* blend_body = NULL;

    API_BEGIN

    // Join a block and cylinder such that the top and bottom planar faces
    // have one edge which is semi-circular.

    BODY* cylinder = NULL;
    check_outcome(api_make_cuboid(H / 2, H, H, blend_body));
    check_outcome(api_apply_transf(blend_body, translate_transf(SPAvector(-H / 4, 0, 0))));
    check_outcome(api_make_frustum(H, H / 2, H / 2, H / 2, cylinder));
    check_outcome(api_unite(cylinder, blend_body));

    // Pick the circular edge on the top planar face and it's immediate
    // neighbouring edges on the top face.

    double* ray_params = NULL;
    ENTITY_LIST top_edge_list, picked_edges;
    check_outcome(api_get_ents(SPAposition(-H / 4, -H / 2, H / 2), SPAunit_vector(0, -1, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_left_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_left_edge);

    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition(-H / 4, H / 2, H / 2), SPAunit_vector(0, 1, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_right_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_right_edge);

    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition(H / 2, 0, H / 2), SPAunit_vector(1, 0, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_circ_edge = (EDGE*)picked_edges.first();
    top_edge_list.add(top_circ_edge);

    // Now apply a variable radius blend : small on left, large on right,
    // and smooth transition on the round edge.

    SPAposition fix_pos[] = {SPAposition(0, -H / 2, H / 2), SPAposition(0, H / 2, H / 2)};
    double fix_radii[] = {top_rad_small, top_rad_large};
    check_outcome(api_blend_edges_pos_rad(top_edge_list, 2, fix_pos, fix_radii, NULL, NULL, pAcisOpt));

    // Highlight the new upper blend faces.

    ENTITY_LIST face_list;
    check_outcome(api_get_ents(SPAposition(-H / 4, 0, 0), SPAunit_vector(0, -1, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(0, 0, 1)));

    face_list.clear();
    check_outcome(api_get_ents(SPAposition(-H / 4, 0, 0), SPAunit_vector(0, 1, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(0, 0, 1)));

    face_list.clear();
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(1, 0, 1), 0.01, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(face_list.first(), rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_grip: different blend types
//
// APIs:
//    api_smooth_edges_to_curve
//    api_make_radius_constant
//    api_make_radius_fixed_width
//    api_make_radius_param_rads
//    api_make_radius_param_rads_tan
//    api_set_abh_blends
//    api_fix_blends
//
// Description:
//	  Blend edges of a cube with different blend types.
// **********************************************************************************

outcome aei_BLEND_GRIP(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20;
    double const R = 8;
    double const r = 2;

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a block and blend the vertical edges with different blend types.

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    int caseN = -1;
    for(int ix = -1; ix <= 1; ix += 2) {
        for(int iy = -1; iy <= 1; iy += 2) {
            SPAposition origin(0, 0, 0);
            SPAunit_vector vect(ix * H, iy * H, 0);

            // Pick an unblended vertical edge of the block.

            ENTITY_LIST edge_list;
            double* ray_params = NULL;
            check_outcome(api_get_ents(origin, vect, H / 100, EDGE_TYPE, blend_body, edge_list, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            // Create a defining curve for the vertex blend from the geometry
            // of the edge.

            CURVE* calibration_curve = NULL;
            EDGE *first_edge = NULL, *last_edge = NULL;
            check_outcome(api_smooth_edges_to_curve(edge_list, calibration_curve, first_edge, last_edge));

            // Assign a blend type radius object to this vertical edge.

            var_radius *rad_obj1 = NULL, *rad_obj2 = NULL;
            switch(++caseN) {
                case 0: {
                    check_outcome(api_make_radius_constant(R, rad_obj1));
                    break;
                }
                case 1: {
                    check_outcome(api_make_radius_fixed_width(R, rad_obj1));
                    break;
                }
                case 2: {
                    double fix_params[] = {0, 0.25, 0.5, 0.75, 1.0};
                    double fix_radii[] = {r, R, r, R, r};

                    check_outcome(api_make_radius_param_rads(5, fix_params, fix_radii, rad_obj1));
                    break;
                }
                case 3: {
                    double start_slope = 2.0, stop_slope = 0.5;
                    double fix_params[] = {0, 0.25, 0.5, 0.75, 1.0};
                    double fix_radii[] = {r, R, r, R, r};

                    check_outcome(api_make_radius_param_rads_tan(5, fix_params, fix_radii, &start_slope, &stop_slope, rad_obj1));
                    break;
                }
            }

            // Attach a variable radius blend attribute and fix the blend.

            var_cross_section* cross_sec = NULL;
            check_outcome(api_set_abh_blends(edge_list, rad_obj1, rad_obj2, cross_sec, calibration_curve, first_edge, last_edge));
            check_outcome(api_fix_blends(edge_list, pAcisOpt));
            if(calibration_curve) calibration_curve->remove();

            // Highlight the new blend face.

            ENTITY_LIST picked_faces;
            check_outcome(api_get_ents(origin, vect, H / 100, FACE_TYPE, blend_body, picked_faces, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            // Color the blend faces with alternative RED and BLUE

            check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color((1 - ix * iy) / 2, 0, (1 + ix * iy) / 2)));
        }
    }

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_pencil: constant chamfer
//
// APIs:
//    api_set_const_chamfers
//    api_fix_blends
//
// Description:
//	  Demonstrates making constant chamfers.
// **********************************************************************************

outcome aei_BLEND_PENCIL(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.0;  // block size
    double const c = 4;     // chamfer size
    double const d = 0.75;  // chamfer size increment
    int const N = 8;        // number of sides in the prizm

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a circular prism with N sides.

    check_outcome(api_make_prism(H, H / 2, H / 2, N, blend_body));

    // Pick the edges of the bottom polygon for chamfering.

    ENTITY_LIST face_list;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, 0, 1), 0.1, FACE_TYPE, blend_body, face_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    ENTITY_LIST edge_list;
    check_outcome(api_get_edges(face_list.first(), edge_list));

    // Add chamfer attributes of various sizes on the edges of the bottom
    // polygon and .

    for(int i = 0; i < edge_list.count(); ++i) {
        EDGE* poly_edge = (EDGE*)edge_list[i];
        check_outcome(api_set_const_chamfers(poly_edge, c, c + d * i));
    }

    check_outcome(api_fix_blends(edge_list, pAcisOpt));

    // Highlight the chamfer faces with alernating BLUE and RED.

    double R = H / 2 - c / 2;
    for(int j = 0; j < N; ++j) {
        ENTITY_LIST picked_faces;
        double a = (2 * M_PI * j) / N;
        check_outcome(api_get_ents(SPAposition(R * cos(a), R * sin(a), 0), SPAunit_vector(0, 0, 1), H / 100, FACE_TYPE, blend_body, picked_faces, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color(1 - j % 2, 0, j % 2)));
    }

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_spline_chamfer: chamfering a spline edge
//
// APIs:
//    api_chamfer_edges
//    api_abh_chamfer_edges
//
// Description:
//	  Demonstrates making chamfer on a spline edge.
// **********************************************************************************

outcome aei_BLEND_SPLINE_CHAMFER(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.;  // block size
    double const c = 4.;   // right chamfer offset
    double const C = 6.;   // left chamfer offset

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a block with a spline surface on top.

    check_outcome(api_wiggle(2 * H, H, H / 2, 1, 2, -1, -2, TRUE, blend_body));

    // Pick a wavy edge.

    ENTITY_LIST edge_list;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, -H / 2, H / 4), H / 8, EDGE_TYPE, blend_body, edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Chamfer the spline edge.

    check_outcome(api_chamfer_edges(edge_list, C, c, pAcisOpt));

    // Pick another wavy edge.

    edge_list.clear();
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, H / 2, H / 4), H / 8, EDGE_TYPE, blend_body, edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Apply a variable width flat chamfer to this spline edge.

    check_outcome(api_abh_chamfer_edges(edge_list, C, c, C / 10, c / 10, 0, 0, pAcisOpt));

    // Highlight the new chamfer faces.

    ENTITY_LIST picked_faces;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, -H / 2, H / 4), 0.1, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color(1, 0, 0)));

    picked_faces.clear();
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, H / 2, H / 4), 0.1, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color(0, 0, 1)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_twisted_bar: variable chamfer
//
// APIs:
//    api_abh_chamfer_edges
//
// Description:
//	  Demonstrates convex and concave round chamfers with variable chamfer
//    offsets along the edge.
// **********************************************************************************

outcome aei_BLEND_TWISTED_BAR(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.;      // block size
    double const R = H / 2;    // chamfer range at start.
    double const r = 0.5;      // chamfer range at end, should be non-zero
    double const R_r = H - r;  // chamfer right range at end.

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a block and blend the vertical edges with rounded chamfers.

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    for(int ix = -1; ix <= 1; ix += 2) {
        for(int iy = -1; iy <= 1; iy += 2) {
            // Pick a vertical edge of the block.

            double* ray_params = NULL;
            ENTITY_LIST edge_list;
            check_outcome(api_get_ents(SPAposition(0., 0., 0.), SPAunit_vector(ix * H, iy * H, 0), H / 100, EDGE_TYPE, blend_body, edge_list, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            // Apply a variable range rounded chamfer.

            check_outcome(api_abh_chamfer_edges(edge_list, R, R, r, R_r, ix * iy > 0 ? .1 : -1, ix * iy > 0 ? .1 : -1, pAcisOpt));

            // Highlight the new chamfer faces with alternate RED and BLUE
            // colors.

            ENTITY_LIST picked_faces;
            check_outcome(api_get_ents(SPAposition(0., 0., 0.), SPAunit_vector(ix * H, iy * H, 0), H / 100, FACE_TYPE, blend_body, picked_faces, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color((1 - ix * iy) / 2, 0, (1 + ix * iy) / 2)));
        }
    }

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_wine_glass: blend disjoined entities
//
// APIs:
//    api_set_ee_cr_blend
//    api_fix_blends
//
// Description:
//	  Demonstrates enity-entity blending of disjoined faces.
// **********************************************************************************

outcome aei_BLEND_WINE_GLASS(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    // Note: R, r, and a  must satisfy the following conditions:
    // r * ( 1 + cos( a ) ) - R * ( 1 - cos( a ) ) > 0 ( sphere above the base )
    // R * sin( a ) - r * ( 1 - sin( a ) ) > 0 ( valid stem of the glass )

    double const R = 50.0;                      // sphere radius
    double const r = 25.0;                      // blend radius
    double const a = degrees_to_radians(20.0);  // angle between stem axis and spring

    double const h = 5;  // thickness of the base
    double const t = 1;  // thickness of the "glass" for shelling

    double const H = r * (1 + cos(a)) - R * (1 - cos(a));  // distance between the sphere and base
    double const Rb = (R + r) * sin(a);                    // radius of the spring curve on base.

    BODY* wine_glass = NULL;

    API_BEGIN

    // Create a sphere and chop its top.

    check_outcome(api_make_sphere(R, wine_glass));
    check_outcome(api_apply_transf(wine_glass, translate_transf(SPAvector(0, 0, H + R))));
    BODY* block = NULL;
    check_outcome(api_make_cuboid(2 * R, 2 * R, 2 * R, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(0, 0, H + R * 2.5))));
    check_outcome(api_subtract(block, wine_glass));

    // Remove a smaller concentric sphere to "hollow" the glass.

    BODY* inner_sphere = NULL;
    check_outcome(api_make_sphere(R - t, inner_sphere));
    check_outcome(api_apply_transf(inner_sphere, translate_transf(SPAvector(0, 0, H + R))));
    check_outcome(api_subtract(inner_sphere, wine_glass));

    // Add the base of the glass.

    BODY* base = NULL;
    check_outcome(api_make_frustum(h, Rb + r, Rb + r, Rb + r, base));
    check_outcome(api_apply_transf(base, translate_transf(SPAvector(0, 0, -h / 2))));
    check_outcome(api_unite(base, wine_glass));

    // Find the two faces to blend : the outer sphere and the flat top of the base.

    ENTITY_LIST picked_faces;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(0, 0, 1), 1, FACE_TYPE, wine_glass, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Set the constant radius entity-entity blend between the two
    // disjoined faces.

    FACE *face1 = (FACE*)picked_faces[0], *face2 = (FACE*)picked_faces[1];
    check_outcome(api_set_ee_cr_blend(wine_glass, face1, face2, bl_concave, SPAposition(Rb, 0, r), r));

    // Fix the first blend, generates the stem of the wine glass.

    check_outcome(api_fix_blends(wine_glass, pAcisOpt));

    // Set the blend between the top planar face and the bottom edge of the
    // base of the wine glass.

    picked_faces.clear();
    check_outcome(api_get_ents(SPAposition(Rb + r / 2, 0, 0), SPAunit_vector(1, 0, 1), 1, FACE_TYPE, wine_glass, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    FACE* top_planar_face = (FACE*)picked_faces.first();

    ENTITY_LIST picked_edges;
    check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(Rb + r, 0, -h), h / 100, EDGE_TYPE, wine_glass, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    EDGE* bottom_edge = (EDGE*)picked_edges.first();
    check_outcome(api_set_ee_cr_blend(wine_glass, bottom_edge, top_planar_face, bl_convex, SPAposition(Rb, 0, -r), r / 2));

    // Finally, fix the second blend

    check_outcome(api_fix_blends(wine_glass, pAcisOpt));

    // Highlight the new blend faces.

    picked_faces.clear();
    check_outcome(api_get_ents(SPAposition(0, 0, H / 2), SPAunit_vector(1, 0, 0), 0.1, FACE_TYPE, wine_glass, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    FACE* stem = (FACE*)picked_faces.first();
    check_outcome(api_rh_set_entity_rgb(stem, rgb_color(1, 0, 0)));

    picked_faces.clear();
    check_outcome(api_get_ents(SPAposition(Rb + 0.9 * r, 0, -0.9 * h), SPAunit_vector(1, 0, 1), h / 100, FACE_TYPE, wine_glass, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    FACE* base_blend = (FACE*)picked_faces.first();
    check_outcome(api_rh_set_entity_rgb(base_blend, rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(wine_glass);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_number_nine: blend instruction attributes
//
// APIs:
//    api_set_inst_blend
//    api_set_ee_cr_blend
//    api_fix_blends
//
// Description:
//	  Demonstrates the effect of blend instruction attributes on the
//    entity-entity blend propagation.
// **********************************************************************************

outcome aei_BLEND_NUMBER_NINE(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const W = 40.0;  // Width of the base block.
    double const w = 20.0;  // Width of the top block.
    double const H = 5.0;   // Height of the base block.
    double const h = 5.0;   // Height of the top block.
    double const r = 10.0;  // blend radius.

    BODY* blend_body = NULL;

    API_BEGIN

    // Create the top block and join with a half cylinder.

    BODY* cyl = NULL;
    check_outcome(api_make_frustum(h, w / 2, w / 2, w / 2, cyl));
    check_outcome(api_apply_transf(cyl, translate_transf(SPAvector(0, w / 2, h / 2))));

    check_outcome(api_make_cuboid(w, w, h, blend_body));
    check_outcome(api_apply_transf(blend_body, translate_transf(SPAvector(0, 0, h / 2))));
    check_outcome(api_unite(cyl, blend_body));

    // Add the base.

    BODY* base = NULL;
    check_outcome(api_make_cuboid(W, W + r, H, base));
    check_outcome(api_apply_transf(base, translate_transf(SPAvector(0, r / 2, -H / 2))));
    check_outcome(api_unite(base, blend_body));

    // Pick the lower right corner vertex and assign rollon attribute to
    // it, the blend would then propagate smoothly at this vertex.

    ENTITY_LIST picked_vertices;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(w / 2, -w / 2, h), SPAunit_vector(1, -1, 1), h / 10, VERTEX_TYPE, blend_body, picked_vertices, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    VERTEX* rollon_v = (VERTEX*)picked_vertices.first();
    check_outcome(api_set_inst_blend(blend_body, rollon_v, blend_rollon, SPAposition(w / 2 + r / sqrt(2.0), -w / 2 - r / sqrt(2.0), r)));

    // Pick the vertex at upper left circle and straight edge junction and assign cap
    // attribute to it, the blend would then stop propagation on reaching this vertex.

    picked_vertices.clear();
    check_outcome(api_get_ents(SPAposition(-w / 2, w / 2, h), SPAunit_vector(-1, 0, 1), h / 10, VERTEX_TYPE, blend_body, picked_vertices, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    VERTEX* cap_v = (VERTEX*)picked_vertices.first();
    check_outcome(api_set_inst_blend(blend_body, cap_v, blend_cap, SPAposition(-w / 2 - r, w / 2, r)));

    // Pick the top face of the base and a straight edge on the top face of
    // the pad to start edge-face blending.

    ENTITY_LIST picked_faces;
    check_outcome(api_get_ents(SPAposition(W / 2 - 0.1, -W / 2 + 0.1, 0), SPAunit_vector(0, 0, 1), 0.01, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    FACE* top_base_face = (FACE*)picked_faces.first();

    ENTITY_LIST picked_edges;
    check_outcome(api_get_ents(SPAposition(0, -w / 2, h), SPAunit_vector(0, -1, 1), 0.1, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* top_pad_edge = (EDGE*)picked_edges.first();

    check_outcome(api_set_ee_cr_blend(blend_body, top_base_face, top_pad_edge, bl_concave, SPAposition(0, -(w / 2 + r), r), r));

    // Fix the entity-entity blend.

    check_outcome(api_fix_blends(blend_body, pAcisOpt));

    // Highlight the new entity-entity blend faces.

    picked_faces.clear();
    check_outcome(api_get_ents(SPAposition(0, -w / 2, 0), SPAunit_vector(0, -1, 1), 0.01, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_get_ents(SPAposition(w / 2, -w / 2, 0), SPAunit_vector(1, -1, 1), 0.01, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_get_ents(SPAposition(w / 2, 0, 0), SPAunit_vector(1, 0, 1), 0.01, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_get_ents(SPAposition(0, w, 0), SPAunit_vector(0, 1, 1), 0.01, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    rgb_color fillet_color(0, 0.1, 0.9);
    for(int i = 0; i < picked_faces.count(); ++i) check_outcome(api_rh_set_entity_rgb(picked_faces[i], fillet_color));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_annotation: use of annotations
//
// APIs:
//    api_clear_annotations
//    api_find_annotations
//    api_smooth_edge_seq
//    api_blend_edges
//
// Description:
//    Demonstrates the use of annotations to locate blend faces.
// **********************************************************************************

outcome aei_BLEND_ANNOTATION(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const B = 100.0;  // large block size
    double const b = 50.0;   // small block size
    double const h = 50.0;   // height of the blocks
    double const r = 30.0;   // blend radius

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a body with mixed convexity vertices.

    check_outcome(api_make_cuboid(B, B, h, blend_body));
    BODY* top = NULL;
    check_outcome(api_make_cuboid(b, B, h, top));
    check_outcome(api_apply_transf(top, translate_transf(SPAvector((b - B) / 2, 0, h))));
    check_outcome(api_unite(top, blend_body));

    // Save the edges of the body to be blended.

    ENTITY_LIST original_edges;
    check_outcome(api_get_edges(blend_body, original_edges));

    // Turn on annotations.

    annotations.push(TRUE);

    // Clear off annotations (just in case there are some already).

    check_outcome(api_clear_annotations());

    // Blend the long horizontal concave edge first.

    ENTITY_LIST picked_edges;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0, 0, h / 2), SPAunit_vector(1, 0, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    EDGE* horizontal_edge = (EDGE*)picked_edges.first();
    check_outcome(api_blend_edges(horizontal_edge, r));

    // Blend the side edges : two straight convex edges and the circular
    // edge generated by the concave blend.

    picked_edges.clear();
    check_outcome(api_get_ents(SPAposition((r + B / 2) / 2, -B / 2, h / 2), SPAunit_vector(0, -1, 1), 0.01, EDGE_TYPE, blend_body, picked_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // Find all the edges in the sequence and fix the convex blend.

    EDGE* seed_edge = (EDGE*)picked_edges.first();
    ENTITY_LIST seq_edges;
    check_outcome(api_smooth_edge_seq(seed_edge, seq_edges, pAcisOpt));
    check_outcome(api_blend_edges(seq_edges, r, pAcisOpt));

    // Now, find all blend edges by looking at annotations. The blend faces
    // corresponding to the original edges are marked BLUE, the vertex blend
    // is marked RED.

    ENTITY_LIST annos;
    check_outcome(api_find_annotations(annos, is_BLEND_ANNO_EDGE));
    for(int i = 0; i < annos.count(); ++i) {
        BLEND_ANNO_EDGE* a = (BLEND_ANNO_EDGE*)annos[i];
        FACE* f = (FACE*)a->blend_face();
        if(f != NULL) {
            rgb_color face_color(1, 0, 0);
            ENTITY* edge = (*(ATTRIB_TAG*)a->edge()).origin();
            if(edge != NULL && original_edges.lookup(edge) != -1) face_color = rgb_color(0, 0, 1);
            check_outcome(api_rh_set_entity_rgb(f, face_color));
        }
    }

    // Restore annotations

    annotations.pop();

    // Clear off annotations

    check_outcome(api_clear_annotations());

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_dice: blending vertices
//
// APIs:
//    api_set_const_rounds
//    api_set_vblend
//    api_set_vblend_autoblend
//    api_fix_blends
//
// Description:
//	  Sets an implicit blend on all vertices and them marks one of the vertices
//    with autosetback attribute.
// **********************************************************************************

outcome aei_BLEND_DICE(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20;  // Size of the block.
    double const R = 4;   // edge blend radius.

    BODY* blend_body = NULL;

    API_BEGIN

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    // Create implicit blends on all edges by attaching a blend attribute.

    ENTITY_LIST edge_list;
    check_outcome(api_get_edges(blend_body, edge_list));
    check_outcome(api_set_const_rounds(edge_list, R, 0, 0));

    // Set an implicit blend on all the vertices with large setback.

    ENTITY_LIST vertex_list;
    check_outcome(api_get_vertices(blend_body, vertex_list));
    for(int i = 0; i < vertex_list.count(); ++i) {
        VERTEX* v = (VERTEX*)vertex_list[i];
        check_outcome(api_set_vblend(v, 2, 2 * R));
    }

    // Set autoblend back on the first vertex with default setback.

    VERTEX* first_v = (VERTEX*)vertex_list.first();
    SPAposition P = first_v->geometry()->coords();
    check_outcome(api_set_vblend_autoblend(first_v, 1));

    // Fix the edge and vertex blends.

    check_outcome(api_fix_blends(edge_list, pAcisOpt));

    // Highlight all vertex blends BLUE.

    for(int ix = -1; ix <= 1; ix += 2) {
        for(int iy = -1; iy <= 1; iy += 2) {
            for(int iz = -1; iz <= 1; iz += 2) {
                ENTITY_LIST picked_faces;
                double* ray_params = NULL;
                check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(ix, iy, iz), R / 10, FACE_TYPE, blend_body, picked_faces, ray_params));
                if(ray_params) {
                    ACIS_DELETE[] STD_CAST ray_params;
                    ray_params = NULL;
                }

                FACE* f = (FACE*)picked_faces.first();
                check_outcome(api_rh_set_entity_rgb(f, rgb_color(0, 0, 1)));
            }
        }
    }

    // Mark the first, auto-blended, vertex RED.

    ENTITY_LIST picked_faces;
    double* ray_params = NULL;
    SPAunit_vector P_vec(P.x(), P.y(), P.z());
    check_outcome(api_get_ents(SPAposition(0, 0, 0), P_vec, R / 10, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    FACE* f = (FACE*)picked_faces.first();
    check_outcome(api_rh_set_entity_rgb(f, rgb_color(1, 0, 0)));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_british_dice: blending vertices
//
// APIs:
//    api_set_const_rounds
//    api_set_vblend
//    api_make_VBL_output_surfaces
//    api_fix_blends
//
// Description:
//	  Blends all the vertices with large setbacks. Then, approximates a 6-sided
//    VBL_SURF by 6 four-sided bs3_surfaces, which enables ACIS to output vertex
//    blend surfaces in a form that can be read and used by most other packages.
// **********************************************************************************

outcome aei_BLEND_BRITISH_DICE(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20;  // size of the block.
    double const R = 6;   // blend radius.

    BODY* blend_body = NULL;

    API_BEGIN

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    // Create implicit blends on all edges by attaching a blend attribute.

    ENTITY_LIST edge_list;
    check_outcome(api_get_edges(blend_body, edge_list));
    check_outcome(api_set_const_rounds(edge_list, R, 0, 0));

    // Set an implicit blend on all the vertices with large setback.

    ENTITY_LIST vertex_list;
    check_outcome(api_get_vertices(blend_body, vertex_list));
    for(int i = 0; i < vertex_list.count(); ++i) {
        VERTEX* v = (VERTEX*)vertex_list[i];
        check_outcome(api_set_vblend(v, 2, 1.5 * R));
    }

    // Remember first vertex location and fix the edge and vertex blends.

    VERTEX* first_v = (VERTEX*)vertex_list.first();
    SPAposition P = first_v->geometry()->coords();
    check_outcome(api_fix_blends(edge_list, pAcisOpt));

    // Highlight all vertex blends yellow.

    for(int ix = -1; ix <= 1; ix += 2) {
        for(int iy = -1; iy <= 1; iy += 2) {
            for(int iz = -1; iz <= 1; iz += 2) {
                ENTITY_LIST picked_faces;
                double* ray_params = NULL;
                check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(ix, iy, iz), R / 10, FACE_TYPE, blend_body, picked_faces, ray_params));
                if(ray_params) {
                    ACIS_DELETE[] STD_CAST ray_params;
                    ray_params = NULL;
                }

                FACE* f = (FACE*)picked_faces.first();
                rgb_color yellow_color(0.9, 0.9, 0.1);
                check_outcome(api_rh_set_entity_rgb(f, yellow_color));
            }
        }
    }

    // Pick a vertex blend surface to split.

    ENTITY_LIST picked_faces;
    double* ray_params = NULL;
    SPAunit_vector P_vec(P.x(), P.y(), P.z());
    check_outcome(api_get_ents(SPAposition(0, 0, 0), P_vec, R / 10, FACE_TYPE, blend_body, picked_faces, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    FACE* bl_face = (FACE*)picked_faces.first();
    surface const& vbl_sf = bl_face->geometry()->equation();

    // Now, split the approximating surface for a VBL_SURF into N
    // four-sided bs3_surface patches.

    int n_bs3 = 0;
    bs3_surface* bs3_array = NULL;
    double interior_fit = 0.001, boundary_fit = 0.001;  // desired fit tolerances

    check_outcome(api_make_VBL_output_surfaces(&vbl_sf, interior_fit, boundary_fit,  // achieved interior and boundary fit tolerances
                                               bs3_array, n_bs3));

    // Create new faces from the approximate surfaces

    for(int i = 0; i < n_bs3; ++i) {
        // Create an exact spline surface, it will own the bs3_surface from
        // this point.

        surface* surf = ACIS_NEW spline(bs3_array[i]);

        // Create a sheet body from the current parameter box of the
        // surface.

        curve* bndry[4];
        SPApar_box dm = surf->param_range();
        bndry[0] = surf->u_param_line(dm.v_range().start_pt());
        bndry[1] = surf->v_param_line(dm.u_range().end_pt());
        bndry[2] = surf->u_param_line(dm.v_range().end_pt());
        bndry[3] = surf->v_param_line(dm.u_range().start_pt());

        FACE* new_face = nullptr;
        check_outcome(api_make_face_spline(surf, new_face, bndry[0], bndry[2], bndry[3], bndry[1], &dm));
        for(int j = 0; j < 4; ++j) ACIS_DELETE bndry[j];

        BODY* new_body = NULL;
        check_outcome(api_sheet_from_ff(1, &new_face, new_body));

        // Find coordinates of the center of the new face.

        ENTITY_LIST sheet_vertices;
        check_outcome(api_get_vertices(new_body, sheet_vertices));

        double sum_x = 0, sum_y = 0, sum_z = 0;
        for(int j = 0; j < sheet_vertices.count(); ++j) {
            VERTEX* v = (VERTEX*)sheet_vertices[j];
            SPAposition P = v->geometry()->coords();
            sum_x += P.x() / sheet_vertices.count();
            sum_y += P.y() / sheet_vertices.count();
            sum_z += P.z() / sheet_vertices.count();
        }

        // Translate the new sheet a bit so that the approximate surface is
        // visible.

        double sc = H / 15 / sqrt(sum_x * sum_x + sum_y * sum_y + sum_z * sum_z);
        SPAposition cen((1 + sc) * sum_x, (1 + sc) * sum_y, (1 + sc) * sum_z);
        check_outcome(api_apply_transf(new_body, translate_transf(SPAvector(sc * sum_x, sc * sum_y, sc * sum_z))));

        check_outcome(api_unite(new_body, blend_body));

        // Now, highlight the newly created sheet in alternate red and blue.

        ENTITY_LIST sheet_picked_faces;
        SPAunit_vector cen_vec(cen.x(), cen.y(), cen.z());
        check_outcome(api_get_ents(cen, cen_vec, R / 10, FACE_TYPE, blend_body, sheet_picked_faces, ray_params));
        if(ray_params) {
            ACIS_DELETE[] STD_CAST ray_params;
            ray_params = NULL;
        }

        FACE* f = (FACE*)sheet_picked_faces.first();
        check_outcome(api_rh_set_entity_rgb(f, rgb_color(1 - i % 2, 0, i % 2)));

        // Cleen up memory.

        ENTITY_LIST del_faces(new_face);
        api_del_entity_list(del_faces);
        ACIS_DELETE surf;
    }

    ACIS_DELETE[] STD_CAST bs3_array;

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_mitre_and_cap: mitre and cap generation.
//
// APIs:
//    api_blend_edges
//    api_set_const_rounds
//    api_fix_blends
//
// Description:
//	  Demonstrates blending a sequence of edges with mitre and side cap.
// **********************************************************************************

outcome aei_BLEND_MITRE_AND_CAP(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.0;  // height of the base cylinder.
    double const R = 50.0;  // radius of the (quarter) base cylinder.
    double const h = 20.0;  // height of the top block.
    double const w = 28.0;  // width  of the top block.
    double const d = 10.0;  // offset of the top block from Y-axis.

    double const r_vert = 2.50;  // fillet radius of vertical edge on top block.
    double const r_top = 6.0;    // fillet radius of the concave edges on the top block.

    BODY* blend_body = NULL;

    API_BEGIN

    // Prepare the part : create a quarter cylinder with a small block on
    // top so that we can blend the concave edges on the planar face of the
    // quarter cylinder.

    // Create a quarter cylinder.

    BODY* block = NULL;
    check_outcome(api_make_cuboid(2 * R, 2 * R, 2 * R, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(-R, 0, 0))));
    check_outcome(api_make_frustum(H, R, R, R, blend_body));
    check_outcome(api_subtract(block, blend_body));

    check_outcome(api_make_cuboid(2 * R, 2 * R, 2 * R, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(0, -R, 0))));
    check_outcome(api_subtract(block, blend_body));

    // Create an upper (small) block and unite with the quarter cylinder.

    check_outcome(api_make_cuboid(w, w, h, block));
    check_outcome(api_apply_transf(block, translate_transf(SPAvector(w / 2 + d, w / 2, (H + h) / 2))));
    check_outcome(api_unite(block, blend_body));

    // Pick vertical edge of the top block and blend it first.

    ENTITY_LIST vertical_edges;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(d + w, w, (H + h) / 2), SPAunit_vector(1, 1, 0), 0.01, EDGE_TYPE, blend_body, vertical_edges, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
    check_outcome(api_blend_edges(vertical_edges, r_vert, pAcisOpt));

    // Pick all the concave edges on the top planar face of the cylinder
    // and blend them.

    ENTITY_LIST concave_edge_list;
    check_outcome(api_get_ents(SPAposition(d, w / 2, H / 2), SPAunit_vector(-1, 0, 1), 0.01, EDGE_TYPE, blend_body, concave_edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    check_outcome(api_get_ents(SPAposition(d + w / 2, w, H / 2), SPAunit_vector(0, 1, 1), 0.01, EDGE_TYPE, blend_body, concave_edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    check_outcome(api_get_ents(SPAposition(d + w - r_vert * (1 - sqrt(2.0) / 2), w - r_vert * (1 - sqrt(2.0) / 2), H / 2), SPAunit_vector(1, 1, 1), 0.01 * r_vert, EDGE_TYPE, blend_body, concave_edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    check_outcome(api_get_ents(SPAposition(d + w, w / 2, H / 2), SPAunit_vector(1, 0, 1), 0.01, EDGE_TYPE, blend_body, concave_edge_list, ray_params));
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }

    // The concave blend sequence interferes with the convex circular edge
    // on the cylinder and that requires sidecap processing. The two smooth
    // convex edge sequences are mitred.

    check_outcome(api_blend_edges(concave_edge_list, r_top, pAcisOpt));

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  blend_clown_hat: effect of blending sequence
//
// APIs:
//    api_make_radius_two_ends
//    api_set_abh_blends
//    api_fix_blends
//
// Description:
//	  Demonstrates the influence of the radius specification on the blend shape of two
//    adjacent edges.
// **********************************************************************************

outcome aei_BLEND_CLOWN_HAT(ENTITY_LIST& output_ents, AcisOptions* pAcisOpt) {
    double const H = 20.1;  // Don't make H==R, as api_fix_blends doesn't eliminates zero-area faces
    double const R = 20;
    double const r = 0;

    BODY* blend_body = NULL;

    API_BEGIN

    // Create a block and apply variable radius blends to its vertical edges.

    check_outcome(api_make_cuboid(H, H, H, blend_body));

    for(int ix = -1; ix <= 1; ix += 2) {
        for(int iy = -1; iy <= 1; iy += 2) {
            // Pick a vertical edge of the block.

            ENTITY_LIST edge_list;
            double* ray_params = NULL;
            check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(ix * H, iy * H, 0), H / 100, EDGE_TYPE, blend_body, edge_list, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            // create var_radius object

            var_radius* rad_obj = NULL;
            if(ix * iy > 0)
                check_outcome(api_make_radius_two_ends(R, r, rad_obj));
            else
                check_outcome(api_make_radius_two_ends(r, R, rad_obj));

            // Assign variable radius blend attribute and fix the blend.

            check_outcome(api_set_abh_blends(edge_list, rad_obj));
            check_outcome(api_fix_blends(edge_list, pAcisOpt));

            // Pick the blend face and color them with alternative
            // RED and BLUE.

            ENTITY_LIST picked_faces;
            check_outcome(api_get_ents(SPAposition(0, 0, 0), SPAunit_vector(ix * H, iy * H, 0), H / 100, FACE_TYPE, blend_body, picked_faces, ray_params));
            if(ray_params) {
                ACIS_DELETE[] STD_CAST ray_params;
                ray_params = NULL;
            }

            check_outcome(api_rh_set_entity_rgb(picked_faces.first(), rgb_color((1 - ix * iy) / 2, 0, (1 + ix * iy) / 2)));
        }
    }

    API_END

    if(result.ok()) output_ents.add(blend_body);

    return result;
}
