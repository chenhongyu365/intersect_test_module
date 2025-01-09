/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "sweep_examples.hxx"

#include "acis/api.err"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/kernapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/surf_utl.hxx"
#include "acis/sweepapi.hxx"

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_pipe_through_e_block: sweep_options
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep options sweep_to_body, bool_type, and keep_law.

outcome aei_SWEEP_PIPE_THROUGH_E_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    ENTITY* ebody_copy = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(-50.0, 0.0, -5.0);
    SPAunit_vector dirct(1.0, 0.0, 0.0);
    double radius(2.0);
    FACE* profile = NULL;
    check_outcome(api_make_planar_disk(origin, dirct, radius, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(-50.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-5.0);
    array_pts[1].set_x(50.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(-5.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Create a e-shaped SPAbox
    BODY* ebody = NULL;
    check_outcome(api_make_cuboid(50.0, 30.0, 30.0, ebody));
    BODY* cutone = NULL;
    check_outcome(api_make_cuboid(10.0, 30.0, 20.0, cutone));
    SPAvector trans_1(-10.0, 0.0, -5.0);
    SPAtransf move_1 = translate_transf(trans_1);
    check_outcome(api_transform_entity((ENTITY*)cutone, move_1));
    check_outcome(api_subtract(cutone, ebody));
    BODY* cuttwo = NULL;
    check_outcome(api_make_cuboid(10.0, 30.0, 20.0, cuttwo));
    SPAvector trans_2(10.0, 0.0, -5.0);
    SPAtransf move_2 = translate_transf(trans_2);
    check_outcome(api_transform_entity((ENTITY*)cuttwo, move_2));
    check_outcome(api_subtract(cuttwo, ebody));
    // Copy made for display
    check_outcome(api_copy_entity((ENTITY*)ebody, ebody_copy));

    // Set sweep options
    sweep_options options;
    options.set_sweep_to_body(ebody);
    options.set_bool_type(LIMIT);
    // local scope for setting the keep law
    {
        char keep_str[11] = "X<2 OR X=Y";
        law* keep_law = NULL;
        check_outcome(api_str_to_law(keep_str, &keep_law));
        options.set_keep_law(keep_law);
        keep_law->remove();
    }
    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));
    // Set the sweep body color to red.
    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(new_body, Red));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END

    if(result.ok()) {
        output_ents.add(new_body);
        output_ents.add(ebody_copy);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  sweep_wedge: sweep_options
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option cut_end_off.

outcome aei_SWEEP_WEDGE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-10.0);
    array_prof_pts[0].set_y(5.0);
    array_prof_pts[0].set_z(5.0);
    array_prof_pts[1].set_x(-10.0);
    array_prof_pts[1].set_y(-5.0);
    array_prof_pts[1].set_z(5.0);
    array_prof_pts[2].set_x(-30.0);
    array_prof_pts[2].set_y(-5.0);
    array_prof_pts[2].set_z(-5.0);
    array_prof_pts[3].set_x(-30.0);
    array_prof_pts[3].set_y(5.0);
    array_prof_pts[3].set_z(-5.0);
    array_prof_pts[4].set_x(-10.0);
    array_prof_pts[4].set_y(5.0);
    array_prof_pts[4].set_z(5.0);
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(-20.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(30.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_cut_end_off(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  sweep_drafted_cone1
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep options draft_angle and to_face.

outcome aei_SWEEP_DRAFTED_CONE1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    BODY* sheet_1 = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, -50.0, 0.0);
    SPAunit_vector dirct(0.0, 1.0, 0.0);
    double radius(2.0);
    FACE* profile = NULL;
    check_outcome(api_make_planar_disk(origin, dirct, radius, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(-50.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(50.0);
    array_pts[1].set_z(0.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Get the surface from a face
    SPAposition forigin(0.0, 0.0, 0.0);
    SPAunit_vector fdirct(0.0, -1.0, 0.0);
    double fradius = 10.0;
    FACE* face_1 = NULL;
    check_outcome(api_make_planar_disk(forigin, fdirct, fradius, face_1));
    FACE* faces[1];
    faces[0] = face_1;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet_1));
    check_outcome(api_body_to_2d(sheet_1));
    surface* surf_1 = get_surface_from_face(face_1);

    sweep_options options;
    options.set_to_face(surf_1);
    options.set_draft_angle(0.044);
    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(new_body);
        output_ents.add(sheet_1);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_box_with_hole: sweep_options
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option draft_hole.
outcome aei_SWEEP_DRAFTED_BOX_WITH_HOLE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a face with hole profile
    BODY* block = NULL;
    check_outcome(api_make_cuboid(50.0, 50.0, 50.0, block));
    BODY* cyl = NULL;
    check_outcome(api_make_frustum(60.0, 10.0, 10.0, 10.0, cyl));
    check_outcome(api_subtract(cyl, block));
    SPAvector trans_1(0.0, 0.0, -40.0);
    SPAtransf move_1 = translate_transf(trans_1);
    check_outcome(api_transform_entity((ENTITY*)block, move_1));
    FACE* profile_face = block->lump()->shell()->face()->next();
    check_outcome(api_unhook_face(profile_face, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    api_get_faces((ENTITY*)sheet, face_list);
    ENTITY* profile = face_list[0];

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-15.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(15.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    sweep_options options;
    options.set_draft_angle(-0.262);
    options.set_draft_hole(NO_DRAFT);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));
    check_outcome(api_del_entity(block));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_deformed_tubing
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep options draft_law, portion, solid,
//    twist_angle, and two_sided.

outcome aei_SWEEP_DEFORMED_TUBING(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-18.0);
    array_prof_pts[0].set_y(22.0);
    array_prof_pts[0].set_z(5.0);
    array_prof_pts[1].set_x(-22.0);
    array_prof_pts[1].set_y(18.0);
    array_prof_pts[1].set_z(5.0);
    array_prof_pts[2].set_x(-22.0);
    array_prof_pts[2].set_y(18.0);
    array_prof_pts[2].set_z(-5.0);
    array_prof_pts[3].set_x(-18.0);
    array_prof_pts[3].set_y(22.0);
    array_prof_pts[3].set_z(-5.0);
    array_prof_pts[4].set_x(-18.0);
    array_prof_pts[4].set_y(22.0);
    array_prof_pts[4].set_z(5.0);
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(-20.0);
    array_pts[0].set_y(20.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(30.0);
    array_pts[1].set_y(-30.0);
    array_pts[1].set_z(0.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Point at end of sweep
    SPAposition end_point(10.10, 0.0, 0.0);
    AcisOptions* ao = NULL;
    law* drafting_law = NULL;
    sweep_options options;

    options.set_solid(FALSE);
    options.set_two_sided(TRUE);
    options.set_sweep_portion(SWEEP_TO, end_point);
    options.set_twist_angle(0.785);

    char draft_str[12] = "(X/10)+0.01";

    check_outcome(api_str_to_law(draft_str, &drafting_law));
    options.set_draft_law(drafting_law);

    // Sweeping operation
    BODY* new_body = NULL;
    outcome out = api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt);
    drafting_law->remove();
    drafting_law = NULL;
    check_outcome(out);
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_degen_draft_box
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option draft_repair.

outcome aei_SWEEP_DEGEN_DRAFT_BOX(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[6];
    array_prof_pts[0].set_x(-30.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(25.0);
    array_prof_pts[1].set_y(0.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(30.0);
    array_prof_pts[2].set_y(5.0);
    array_prof_pts[2].set_z(0.0);
    array_prof_pts[3].set_x(30.0);
    array_prof_pts[3].set_y(60.0);
    array_prof_pts[3].set_z(0.0);
    array_prof_pts[4].set_x(-30.0);
    array_prof_pts[4].set_y(60.0);
    array_prof_pts[4].set_z(0.0);
    array_prof_pts[5].set_x(-30.0);
    array_prof_pts[5].set_y(0.0);
    array_prof_pts[5].set_z(0.0);
    check_outcome(api_make_wire(NULL, 6, array_prof_pts, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(50.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(-0.524);
    options.set_draft_repair_level(FIRST_DEGENERACY);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_pipe_through_slotted_block
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep options end_draft_dist and keep_branches.

outcome aei_SWEEP_PIPE_THROUGH_SLOTTED_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    ENTITY* cutbody_copy = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(-45.0, 0.0, 0.0);
    SPAunit_vector dirct(1.0, 0.0, 0.0);
    double radius = 10.0;
    FACE* profile = NULL;
    check_outcome(api_make_planar_disk(origin, dirct, radius, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(-45.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-5.0);
    array_pts[1].set_x(45.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(-5.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Create a cut-out SPAbox
    BODY* cutbody = NULL;
    check_outcome(api_make_cuboid(70.0, 30.0, 30.0, cutbody));
    BODY* cutone = NULL;
    check_outcome(api_make_cuboid(10.0, 30.0, 10.0, cutone));
    SPAvector trans_1(-20.0, 0.0, -10.0);
    SPAtransf move_1 = translate_transf(trans_1);
    check_outcome(api_transform_entity((ENTITY*)cutone, move_1));
    check_outcome(api_subtract(cutone, cutbody));
    BODY* cuttwo = NULL;
    check_outcome(api_make_cuboid(10.0, 30.0, 10.0, cuttwo));
    SPAvector trans_2(20.0, 0.0, -10.0);
    SPAtransf move_2 = translate_transf(trans_2);
    check_outcome(api_transform_entity((ENTITY*)cuttwo, move_2));
    check_outcome(api_subtract(cuttwo, cutbody));
    BODY* cutthree = NULL;
    check_outcome(api_make_cuboid(10.0, 30.0, 10.0, cutthree));
    SPAvector trans_3(0.0, 0.0, 10.0);
    SPAtransf move_3 = translate_transf(trans_3);
    check_outcome(api_transform_entity((ENTITY*)cutthree, move_3));
    check_outcome(api_subtract(cutthree, cutbody));
    check_outcome(api_copy_entity((ENTITY*)cutbody, cutbody_copy));

    // Set sweep options
    sweep_options options;
    options.set_sweep_to_body(cutbody);
    options.set_bool_type(LIMIT);
    options.set_keep_branches(TRUE);
    options.set_end_draft_dist(5.0);

    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));
    // Set the sweep body color to red.
    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(new_body, Red));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(new_body);
        output_ents.add(cutbody_copy);
    }
    return result;
}
outcome aei_SWEEP_DRAFTED_BOX_CYL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /*******************************************************************/
    // C++ Example:
    //
    // Title:
    //	  sweep_drafted_box_cyl
    //
    // APIs:
    //	  api_sweep_with_options
    //
    // Description:
    //	  Demonstrates the sweep option gap_type.
    BODY* profile = NULL;

    API_BEGIN

    // Create a profile
    EDGE* part[5];
    part[0] = NULL;
    part[1] = NULL;
    part[2] = NULL;
    part[3] = NULL;
    part[4] = NULL;
    SPAposition point_1(-10.0, 10.0, 0.0);
    SPAposition point_2(-30.0, 10.0, 0.0);
    SPAposition point_3(-30.0, -30.0, 0.0);
    SPAposition point_4(10.0, -30.0, 0.0);
    SPAposition point_5(10.0, -10.0, 0.0);
    SPAunit_vector normal(0.0, 0.0, 1.0);
    SPAposition origin_1(10.0, 10.0, 0.0);
    SPAvector major_axis_1(0.0, -20.0, 0.0);
    check_outcome(api_mk_ed_line(point_1, point_2, part[0]));
    check_outcome(api_mk_ed_line(point_2, point_3, part[1]));
    check_outcome(api_mk_ed_line(point_3, point_4, part[2]));
    check_outcome(api_mk_ed_line(point_4, point_5, part[3]));
    check_outcome(api_mk_ed_ellipse(origin_1, normal, major_axis_1, 1.0, 0.0, (1.5 * M_PI), part[4]));
    check_outcome(api_make_ewire(5, part, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(30.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(-0.175);
    options.set_gap_type(1);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
outcome aei_SWEEP_TORUS_THROUGH_E_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /*******************************************************************/
    // C++ Example:
    //
    // Title:
    //	  sweep_torus_through_e_block
    //
    // APIs:
    //	  api_sweep_with_options
    //
    // Description:
    //	  Demonstrates the sweep option keep_start_face.

    BODY* profile = NULL;
    BODY* ebody = NULL;
    API_BEGIN

    // Create a profile
    EDGE* prof_1 = NULL;
    SPAunit_vector prof_normal(0.0, 0.0, 1.0);
    SPAposition prof_origin(30.0, 0.0, -30.0);
    SPAvector prof_major_axis(5.0, 0.0, 0.0);
    check_outcome(api_mk_ed_ellipse(prof_origin, prof_normal, prof_major_axis, 1.0, 0.0, (2 * M_PI), prof_1));
    check_outcome(api_make_ewire(1, &prof_1, profile));

    // Create a path
    EDGE* part_1 = NULL;
    SPAunit_vector normal(0.0, -1.0, 0.0);
    SPAposition origin_1(0.0, 0.0, -30.0);
    SPAvector major_axis_1(30.0, 0.0, 0.0);
    check_outcome(api_mk_ed_ellipse(origin_1, normal, major_axis_1, 1.0, 0.0, (2 * M_PI), part_1));
    BODY* path = NULL;
    check_outcome(api_make_ewire(1, &part_1, path));

    // Set sweep options
    sweep_options options;
    options.set_keep_start_face(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));
    // Set the sweep body color to red.
    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(profile, Red));

    // Clean up memory
    check_outcome(api_del_entity(path));

    // Additional body shown to display why option might be useful.
    // The body intersects the result of the sweep and shows that
    // cellular topogoly could be applied and the cells ordered from
    // the start face.
    check_outcome(api_make_cuboid(25.0, 30.0, 50.0, ebody));
    BODY* cutone = NULL;
    check_outcome(api_make_cuboid(5.0, 30.0, 40.0, cutone));
    SPAvector trans_1(-5.0, 0.0, -5.0);
    SPAtransf move_1 = translate_transf(trans_1);
    check_outcome(api_transform_entity((ENTITY*)cutone, move_1));
    check_outcome(api_subtract(cutone, ebody));
    BODY* cuttwo = NULL;
    check_outcome(api_make_cuboid(5.0, 30.0, 40.0, cuttwo));
    SPAvector trans_2(5.0, 0.0, -5.0);
    SPAtransf move_2 = translate_transf(trans_2);
    check_outcome(api_transform_entity((ENTITY*)cuttwo, move_2));
    check_outcome(api_subtract(cuttwo, ebody));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
        output_ents.add(ebody);
    }
    return result;
}
outcome aei_SWEEP_HEART(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /*******************************************************************/
    // C++ Example:
    //
    // Title:
    //	  sweep_heart: sweep_options
    //
    // APIs:
    //	  api_sweep_with_options
    //
    // Description:
    //	  Demonstrates the sweep option miter.

    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-18.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(2.0);
    array_prof_pts[1].set_x(-22.0);
    array_prof_pts[1].set_y(0.0);
    array_prof_pts[1].set_z(2.0);
    array_prof_pts[2].set_x(-22.0);
    array_prof_pts[2].set_y(0.0);
    array_prof_pts[2].set_z(-2.0);
    array_prof_pts[3].set_x(-18.0);
    array_prof_pts[3].set_y(0.0);
    array_prof_pts[3].set_z(-2.0);
    array_prof_pts[4].set_x(-18.0);
    array_prof_pts[4].set_y(0.0);
    array_prof_pts[4].set_z(2.0);
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, profile));

    // Create a path
    EDGE* part[4];
    part[0] = NULL;
    part[1] = NULL;
    part[2] = NULL;
    part[3] = NULL;
    SPAposition point_1(-20.0, 0.0, 0.0);
    SPAposition point_2(20.0, 40.0, 0.0);
    SPAposition point_3(-20.0, 40.0, 0.0);
    SPAunit_vector normal(0.0, 0.0, 1.0);
    SPAposition origin_1(0.0, 0.0, 0.0);
    SPAvector major_axis_1(-20.0, 0.0, 0.0);
    SPAposition origin_2(20.0, 20.0, 0.0);
    SPAvector major_axis_2(0.0, -20.0, 0.0);
    check_outcome(api_mk_ed_ellipse(origin_1, normal, major_axis_1, 1.0, 0.0, M_PI, part[0]));
    check_outcome(api_mk_ed_ellipse(origin_2, normal, major_axis_2, 1.0, 0.0, M_PI, part[1]));
    check_outcome(api_mk_ed_line(point_2, point_3, part[2]));
    check_outcome(api_mk_ed_line(point_3, point_1, part[3]));
    BODY* path = NULL;
    check_outcome(api_make_ewire(4, part, path));

    // Set sweep options
    sweep_options options;
    options.set_miter(crimp_miter);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_apple_peel
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option rail_law.

// Entities not deleted	BODY *profile = NULL;
outcome aei_SWEEP_APPLE_PEEL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN
    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(1.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(10.0);
    array_prof_pts[1].set_y(0.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(10.0);
    array_prof_pts[2].set_y(0.0);
    array_prof_pts[2].set_z(1.0);
    array_prof_pts[3].set_x(1.0);
    array_prof_pts[3].set_y(0.0);
    array_prof_pts[3].set_z(1.0);
    array_prof_pts[4].set_x(1.0);
    array_prof_pts[4].set_y(0.0);
    array_prof_pts[4].set_z(0.0);
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, profile));

    // Create laws
    char curlaw_str[35] = "VEC((X+1)*COS(X),(X+1)*SIN(X),X*2)";
    law* curlaw = NULL;
    check_outcome(api_str_to_law(curlaw_str, &curlaw));
    law* dcurlaw = curlaw->derivative();
    SPAvector v(0.0, 0.0, 1.0);
    law* veclaw = ACIS_NEW vector_law(v);
    law* vxc = ACIS_NEW cross_law(veclaw, dcurlaw);
    law* rail = ACIS_NEW norm_law(vxc);

    // Create a path
    EDGE* path = NULL;
    check_outcome(api_edge_law(curlaw, 0.0, 20.0, path));

    // Set sweep options
    sweep_options options;
    options.set_rail_law(rail);
    curlaw->remove();
    dcurlaw->remove();
    veclaw->remove();
    vxc->remove();
    rail->remove();
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity((ENTITY*)path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_rigid_tube1: sweep_options
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option rigid.
outcome aei_SWEEP_RIGID_TUBE1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, -20.0);
    SPAposition left(0.0, 10.0, -20.0);
    SPAposition right(10.0, 0.0, -20.0);
    FACE* profile = NULL;
    check_outcome(api_make_plface(origin, left, right, profile));

    // Create a path
    SPAposition array_pts[5];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    array_pts[2].set_x(10.0);
    array_pts[2].set_y(0.0);
    array_pts[2].set_z(10.0);
    array_pts[3].set_x(10.0);
    array_pts[3].set_y(0.0);
    array_pts[3].set_z(20.0);
    array_pts[4].set_x(10.0);
    array_pts[4].set_y(20.0);
    array_pts[4].set_z(30.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 5, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_rigid(TRUE);

    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(new_body);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_ufo1: sweep_options
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep options steps, close_to_axis and sweep_angle.

outcome aei_SWEEP_UFO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[3];
    array_prof_pts[0].set_x(15.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(30.0);
    array_prof_pts[1].set_y(15.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(15.0);
    array_prof_pts[2].set_y(30.0);
    array_prof_pts[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, array_prof_pts, profile));

    // Create a SPAvector
    SPAposition start(0.0, 0.0, 0.0);
    SPAvector axis(0.0, 20.0, 0.0);

    // Set sweep options
    sweep_options options;
    options.set_sweep_angle(4.712);
    options.set_close_to_axis(TRUE);
    options.set_steps(10);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, start, axis, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_twisted_tube
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Demonstrates the sweep option twist_law.

outcome aei_SWEEP_TWISTED_TUBE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-20.0);
    array_prof_pts[0].set_y(5.0);
    array_prof_pts[0].set_z(5.0);
    array_prof_pts[1].set_x(-20.0);
    array_prof_pts[1].set_y(-5.0);
    array_prof_pts[1].set_z(5.0);
    array_prof_pts[2].set_x(-20.0);
    array_prof_pts[2].set_y(-5.0);
    array_prof_pts[2].set_z(-5.0);
    array_prof_pts[3].set_x(-20.0);
    array_prof_pts[3].set_y(5.0);
    array_prof_pts[3].set_z(-5.0);
    array_prof_pts[4].set_x(-20.0);
    array_prof_pts[4].set_y(5.0);
    array_prof_pts[4].set_z(5.0);
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(-20.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(30.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, path));

    // Set sweep options
    sweep_options options;
    char twist_str[11] = "(X/20)^2";
    law* twisting_law = NULL;
    check_outcome(api_str_to_law(twist_str, &twisting_law));
    options.set_twist_law(twisting_law);
    twisting_law->remove();
    twisting_law = NULL;

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_rigid_tube2
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Rigid sweep
outcome aei_SWEEP_RIGID_TUBE2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, -20.0);
    SPAposition left(0.0, 10.0, -20.0);
    SPAposition right(10.0, 0.0, -20.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a path
    SPAposition array_pts[5];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    array_pts[2].set_x(10.0);
    array_pts[2].set_y(0.0);
    array_pts[2].set_z(10.0);
    array_pts[3].set_x(10.0);
    array_pts[3].set_y(0.0);
    array_pts[3].set_z(20.0);
    array_pts[4].set_x(10.0);
    array_pts[4].set_y(20.0);
    array_pts[4].set_z(30.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 5, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_rigid(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_shaft
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Rigid sweep
outcome aei_SWEEP_SHAFT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, -20.0);
    SPAposition left(0.0, 10.0, -20.0);
    SPAposition right(10.0, 0.0, -20.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a SPAvector
    SPAvector dirct(-20.0, -20.0, 50.0);

    // Set sweep options
    sweep_options options;
    options.set_rigid(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, dirct, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
outcome aei_SWEEP_RIGID_PIPE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /*******************************************************************/
    // C++ Example:
    //
    // Title:
    //	  sweep_rigid_pipe
    //
    // APIs:
    //	  api_sweep_with_options
    //
    // Description:
    //	  Rigid sweep of a pipe

    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[11];
    array_prof_pts[0].set_x(5.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(-20.0);
    array_prof_pts[1].set_x(4.045);
    array_prof_pts[1].set_y(2.989);
    array_prof_pts[1].set_z(-20.0);
    array_prof_pts[2].set_x(1.545);
    array_prof_pts[2].set_y(4.755);
    array_prof_pts[2].set_z(-20.0);
    array_prof_pts[3].set_x(-1.545);
    array_prof_pts[3].set_y(4.755);
    array_prof_pts[3].set_z(-20.0);
    array_prof_pts[4].set_x(-4.045);
    array_prof_pts[4].set_y(2.989);
    array_prof_pts[4].set_z(-20.0);
    array_prof_pts[5].set_x(-5.0);
    array_prof_pts[5].set_y(0.0);
    array_prof_pts[5].set_z(-20.0);
    array_prof_pts[6].set_x(-4.045);
    array_prof_pts[6].set_y(-2.989);
    array_prof_pts[6].set_z(-20.0);
    array_prof_pts[7].set_x(-1.545);
    array_prof_pts[7].set_y(-4.755);
    array_prof_pts[7].set_z(-20.0);
    array_prof_pts[8].set_x(1.545);
    array_prof_pts[8].set_y(-4.755);
    array_prof_pts[8].set_z(-20.0);
    array_prof_pts[9].set_x(4.045);
    array_prof_pts[9].set_y(-2.989);
    array_prof_pts[9].set_z(-20.0);
    array_prof_pts[10].set_x(5.0);
    array_prof_pts[10].set_y(0.0);
    array_prof_pts[10].set_z(-20.0);
    check_outcome(api_make_wire(NULL, 11, array_prof_pts, profile));

    // Create a path
    SPAposition array_pts[5];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    array_pts[2].set_x(10.0);
    array_pts[2].set_y(0.0);
    array_pts[2].set_z(10.0);
    array_pts[3].set_x(10.0);
    array_pts[3].set_y(0.0);
    array_pts[3].set_z(20.0);
    array_pts[4].set_x(10.0);
    array_pts[4].set_y(20.0);
    array_pts[4].set_z(30.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 5, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_rigid(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_rigid_pipe_shaft
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Rigid Sweep

outcome aei_SWEEP_RIGID_PIPE_SHAFT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[11];
    array_prof_pts[0].set_x(5.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(-20.0);
    array_prof_pts[1].set_x(4.045);
    array_prof_pts[1].set_y(2.989);
    array_prof_pts[1].set_z(-20.0);
    array_prof_pts[2].set_x(1.545);
    array_prof_pts[2].set_y(4.755);
    array_prof_pts[2].set_z(-20.0);
    array_prof_pts[3].set_x(-1.545);
    array_prof_pts[3].set_y(4.755);
    array_prof_pts[3].set_z(-20.0);
    array_prof_pts[4].set_x(-4.045);
    array_prof_pts[4].set_y(2.989);
    array_prof_pts[4].set_z(-20.0);
    array_prof_pts[5].set_x(-5.0);
    array_prof_pts[5].set_y(0.0);
    array_prof_pts[5].set_z(-20.0);
    array_prof_pts[6].set_x(-4.045);
    array_prof_pts[6].set_y(-2.989);
    array_prof_pts[6].set_z(-20.0);
    array_prof_pts[7].set_x(-1.545);
    array_prof_pts[7].set_y(-4.755);
    array_prof_pts[7].set_z(-20.0);
    array_prof_pts[8].set_x(1.545);
    array_prof_pts[8].set_y(-4.755);
    array_prof_pts[8].set_z(-20.0);
    array_prof_pts[9].set_x(4.045);
    array_prof_pts[9].set_y(-2.989);
    array_prof_pts[9].set_z(-20.0);
    array_prof_pts[10].set_x(5.0);
    array_prof_pts[10].set_y(0.0);
    array_prof_pts[10].set_z(-20.0);
    check_outcome(api_make_wire(NULL, 11, array_prof_pts, profile));

    // Create a SPAvector
    SPAvector dirct(0.0, -40.0, 50.0);

    // Set sweep options
    sweep_options options;
    options.set_rigid(TRUE);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, dirct, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_fin
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//   Rotational Sweep
outcome aei_SWEEP_FIN(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    ENTITY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[2];
    array_prof_pts[0].set_x(15.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(30.0);
    array_prof_pts[1].set_y(15.0);
    array_prof_pts[1].set_z(0.0);
    BODY* body_ptr = NULL;
    check_outcome(api_make_wire(NULL, 2, array_prof_pts, body_ptr));
    LUMP* lump_ptr = body_ptr->lump();
    SHELL* shell_ptr = lump_ptr->shell();
    WIRE* wire_ptr = shell_ptr->wire_list();
    COEDGE* coedge_ptr = wire_ptr->coedge();
    check_outcome(api_get_owner((ENTITY*)coedge_ptr, profile));

    // Create an axis
    SPAposition start(0.0, 0.0, 0.0);
    SPAvector axis(0.0, 20.0, 0.0);

    // Set sweep options
    sweep_options options;
    options.set_sweep_angle(1.047);
    options.set_steps(3);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, start, axis, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_abstract_art
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	Sweep a wire along a multiple edge path
outcome aei_SWEEP_ABSTRACT_ART(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    ENTITY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(0.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(15.0);
    array_prof_pts[1].set_y(0.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(30.0);
    array_prof_pts[2].set_y(15.0);
    array_prof_pts[2].set_z(0.0);
    array_prof_pts[3].set_x(0.0);
    array_prof_pts[3].set_y(15.0);
    array_prof_pts[3].set_z(0.0);
    array_prof_pts[4].set_x(0.0);
    array_prof_pts[4].set_y(0.0);
    array_prof_pts[4].set_z(0.0);
    BODY* body_ptr = NULL;
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, body_ptr));
    LUMP* lump_ptr = body_ptr->lump();
    SHELL* shell_ptr = lump_ptr->shell();
    WIRE* wire_ptr = shell_ptr->wire_list();
    COEDGE* coedge_ptr = wire_ptr->coedge();
    check_outcome(api_get_owner((ENTITY*)coedge_ptr, profile));

    // Create a path
    SPAposition array_pts[4];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    array_pts[2].set_x(-10.0);
    array_pts[2].set_y(10.0);
    array_pts[2].set_z(10.0);
    array_pts[3].set_x(-10.0);
    array_pts[3].set_y(10.0);
    array_pts[3].set_z(30.0);
    BODY* body_ptr2 = NULL;
    check_outcome(api_make_wire(NULL, 4, array_pts, body_ptr2));
    LUMP* lump_ptr2 = body_ptr2->lump();
    SHELL* shell_ptr2 = lump_ptr2->shell();
    WIRE* wire_ptr2 = shell_ptr2->wire_list();
    COEDGE* coedge_ptr2 = wire_ptr2->coedge();
    ENTITY* path = NULL;
    check_outcome(api_get_owner((ENTITY*)coedge_ptr2, path));

    // Set sweep options
    sweep_options options;

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_tube
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	 Sweep with draft angle and up to a face.
outcome aei_SWEEP_DRAFTED_TUBE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    BODY* display_sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(0.0);
    array_prof_pts[0].set_y(-50.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(10.0);
    array_prof_pts[1].set_y(-50.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(10.0);
    array_prof_pts[2].set_y(-50.0);
    array_prof_pts[2].set_z(10.0);
    array_prof_pts[3].set_x(0.0);
    array_prof_pts[3].set_y(-50.0);
    array_prof_pts[3].set_z(10.0);
    array_prof_pts[4].set_x(0.0);
    array_prof_pts[4].set_y(-50.0);
    array_prof_pts[4].set_z(0.0);
    BODY* body_ptr = NULL;
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, body_ptr));
    LUMP* lump_ptr = body_ptr->lump();
    SHELL* shell_ptr = lump_ptr->shell();
    WIRE* wire_ptr = shell_ptr->wire_list();
    COEDGE* coedge_ptr = wire_ptr->coedge();
    ENTITY* profile = NULL;
    check_outcome(api_get_owner((ENTITY*)coedge_ptr, profile));

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(-50.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(50.0);
    array_pts[1].set_z(0.0);
    BODY* body_ptr2 = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, body_ptr2));
    LUMP* lump_ptr2 = body_ptr2->lump();
    SHELL* shell_ptr2 = lump_ptr2->shell();
    WIRE* wire_ptr2 = shell_ptr2->wire_list();
    COEDGE* coedge_ptr2 = wire_ptr2->coedge();
    ENTITY* path = NULL;
    check_outcome(api_get_owner((ENTITY*)coedge_ptr2, path));

    // Get the surface from a face
    SPAposition forigin(0.0, 0.0, 0.0);
    SPAunit_vector fdirct(0.0, -1.0, 0.0);
    double fradius = 30.0;
    FACE* face1 = NULL;
    check_outcome(api_make_planar_disk(forigin, fdirct, fradius, face1));
    ENTITY* face1_copy = NULL;
    check_outcome(api_copy_entity((ENTITY*)face1, face1_copy));

    // Sheet body made for display
    FACE* faces[1];
    faces[0] = (FACE*)face1_copy;
    check_outcome(api_mk_by_faces(NULL, 1, faces, display_sheet));
    check_outcome(api_body_to_2d(display_sheet));
    surface* surf1 = get_surface_from_face(face1);

    // Set sweep options
    sweep_options options;
    options.set_to_face(surf1);
    options.set_draft_angle(0.044);

    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));
    // Set the sweep body color to red.
    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(new_body, Red));

    // Clean up memory
    check_outcome(api_del_entity(path));
    check_outcome(api_del_entity(face1));

    API_END
    if(result.ok()) {
        output_ents.add(new_body);
        output_ents.add(display_sheet);
    }
    return result;
}
outcome aei_SWEEP_DRAFTED_POLYGON1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    ENTITY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-20.0);
    array_prof_pts[0].set_y(-20.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(-10.0);
    array_prof_pts[1].set_y(-20.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(-5.0);
    array_prof_pts[2].set_y(-20.0);
    array_prof_pts[2].set_z(10.0);
    array_prof_pts[3].set_x(-20.0);
    array_prof_pts[3].set_y(-20.0);
    array_prof_pts[3].set_z(10.0);
    array_prof_pts[4].set_x(-20.0);
    array_prof_pts[4].set_y(-20.0);
    array_prof_pts[4].set_z(0.0);
    BODY* body_ptr = NULL;
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, body_ptr));
    LUMP* lump_ptr = body_ptr->lump();
    SHELL* shell_ptr = lump_ptr->shell();
    WIRE* wire_ptr = shell_ptr->wire_list();
    COEDGE* coedge_ptr = wire_ptr->coedge();
    check_outcome(api_get_owner((ENTITY*)coedge_ptr, profile));

    // Create a vector path
    SPAvector dirct(0.0, 25.0, 0.0);

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(0.785);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, dirct, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_polygon2
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//   Sweep with draft angle

outcome aei_SWEEP_DRAFTED_POLYGON2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    ENTITY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[5];
    array_prof_pts[0].set_x(-10.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(-20.0);
    array_prof_pts[1].set_x(5.0);
    array_prof_pts[1].set_y(0.0);
    array_prof_pts[1].set_z(-20.0);
    array_prof_pts[2].set_x(20.0);
    array_prof_pts[2].set_y(15.0);
    array_prof_pts[2].set_z(-20.0);
    array_prof_pts[3].set_x(-10.0);
    array_prof_pts[3].set_y(15.0);
    array_prof_pts[3].set_z(-20.0);
    array_prof_pts[4].set_x(-10.0);
    array_prof_pts[4].set_y(0.0);
    array_prof_pts[4].set_z(-20.0);
    BODY* body_ptr = NULL;
    check_outcome(api_make_wire(NULL, 5, array_prof_pts, body_ptr));
    LUMP* lump_ptr = body_ptr->lump();
    SHELL* shell_ptr = lump_ptr->shell();
    WIRE* wire_ptr = shell_ptr->wire_list();
    COEDGE* coedge_ptr = wire_ptr->coedge();
    check_outcome(api_get_owner((ENTITY*)coedge_ptr, profile));

    // Create a path
    SPAposition array_pts[4];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(0.0);
    array_pts[2].set_x(0.0);
    array_pts[2].set_y(0.0);
    array_pts[2].set_z(20.0);
    array_pts[3].set_x(0.0);
    array_pts[3].set_y(0.0);
    array_pts[3].set_z(25.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 4, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(0.262);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_arch
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	 Rotational sweep, closing the profile to the axis and converting
//   the circular path into several steps

outcome aei_SWEEP_ARCH(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, 0.0);
    SPAposition left(0.0, 10.0, 0.0);
    SPAposition right(10.0, 0.0, 0.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a SPAvector
    SPAposition start(-20.0, 0.0, 0.0);
    SPAvector axis(0.0, 20.0, 0.0);

    // Set sweep options
    sweep_options options;
    options.set_sweep_angle(3.142);
    options.set_steps(5);
    options.set_close_to_axis(TRUE);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, start, axis, &options, new_body, ptrAcisOpt));

    API_END

    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_box1
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//    Sweep with draft angle
outcome aei_SWEEP_DRAFTED_BOX1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, 0.0);
    SPAposition left(0.0, 10.0, 0.0);
    SPAposition right(10.0, 0.0, 0.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Set the distance
    double dist = -30.0;

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(0.349);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, dist, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}

/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_cone2
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//    Sweep with draft angle + to_face operation
outcome aei_SWEEP_DRAFTED_CONE2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* new_body = NULL;
    BODY* display_sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, -50.0, 0.0);
    SPAunit_vector dirct(0.0, 1.0, 0.0);
    double radius(2.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_planar_disk(origin, dirct, radius, fprofile));
    BODY* sheet = NULL;
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a path
    SPAposition array_pts[2];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(-50.0);
    array_pts[0].set_z(0.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(50.0);
    array_pts[1].set_z(0.0);
    BODY* body_ptr2 = NULL;
    check_outcome(api_make_wire(NULL, 2, array_pts, body_ptr2));
    LUMP* lump_ptr2 = body_ptr2->lump();
    SHELL* shell_ptr2 = lump_ptr2->shell();
    WIRE* wire_ptr2 = shell_ptr2->wire_list();
    COEDGE* coedge_ptr2 = wire_ptr2->coedge();
    ENTITY* path = NULL;
    check_outcome(api_get_owner((ENTITY*)coedge_ptr2, path));

    // Get the surface from a face
    SPAposition forigin(0.0, 0.0, 0.0);
    SPAunit_vector fdirct(0.0, -1.0, 0.0);
    double fradius = 10.0;
    FACE* face1 = NULL;
    check_outcome(api_make_planar_disk(forigin, fdirct, fradius, face1));
    ENTITY* face1_copy = NULL;
    check_outcome(api_copy_entity((ENTITY*)face1, face1_copy));
    // Sheet body for display
    FACE* display_faces[1];
    display_faces[0] = (FACE*)face1_copy;
    check_outcome(api_mk_by_faces(NULL, 1, display_faces, display_sheet));
    check_outcome(api_body_to_2d(display_sheet));
    surface* surf1 = get_surface_from_face(face1);

    // Set sweep options
    sweep_options options;
    options.set_to_face(surf1);
    options.set_draft_angle(0.044);

    // Sweeping operation
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));
    // Set the sweep body color to red.
    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(new_body, Red));

    // Clean up memory
    check_outcome(api_del_entity(path));
    check_outcome(api_del_entity(face1));

    API_END
    if(result.ok()) {
        output_ents.add(new_body);
        output_ents.add(display_sheet);
    }
    return result;
}
outcome aei_SWEEP_ANGLED_POLYGON(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, 0.0);
    SPAposition left(0.0, 10.0, 0.0);
    SPAposition right(10.0, 0.0, 0.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a vector path
    SPAvector dirct(-10.0, -10.0, -10.0);

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(0.349);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, dirct, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_drafted_box2
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Sweep with draft angle
outcome aei_SWEEP_DRAFTED_BOX2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sheet = NULL;
    API_BEGIN

    // Create a profile
    SPAposition origin(0.0, 0.0, -20.0);
    SPAposition left(0.0, 10.0, -20.0);
    SPAposition right(10.0, 0.0, -20.0);
    FACE* fprofile = NULL;
    check_outcome(api_make_plface(origin, left, right, fprofile));
    FACE* faces[1];
    faces[0] = fprofile;
    check_outcome(api_mk_by_faces(NULL, 1, faces, sheet));
    check_outcome(api_body_to_2d(sheet));
    ENTITY_LIST face_list;
    check_outcome(api_get_faces((ENTITY*)sheet, face_list));
    ENTITY* profile = face_list[0];

    // Create a path
    SPAposition array_pts[5];
    array_pts[0].set_x(0.0);
    array_pts[0].set_y(0.0);
    array_pts[0].set_z(-20.0);
    array_pts[1].set_x(0.0);
    array_pts[1].set_y(0.0);
    array_pts[1].set_z(20.0);
    array_pts[2].set_x(0.0);
    array_pts[2].set_y(0.0);
    array_pts[2].set_z(30.0);
    array_pts[3].set_x(0.0);
    array_pts[3].set_y(0.0);
    array_pts[3].set_z(40.0);
    array_pts[4].set_x(0.0);
    array_pts[4].set_y(0.0);
    array_pts[4].set_z(60.0);
    BODY* path = NULL;
    check_outcome(api_make_wire(NULL, 5, array_pts, path));

    // Set sweep options
    sweep_options options;
    options.set_draft_angle(0.175);

    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, path, &options, new_body, ptrAcisOpt));

    // Clean up memory
    check_outcome(api_del_entity(path));

    API_END
    if(result.ok()) {
        output_ents.add(sheet);
    }
    return result;
}
/*******************************************************************/
// C++ Example:
//
// Title:
//	  sweep_ufo2
//
// APIs:
//	  api_sweep_with_options
//
// Description:
//	  Rotational sweep with close to axis and step options
outcome aei_SWEEP_UFO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* profile = NULL;
    API_BEGIN

    // Create a profile
    SPAposition array_prof_pts[3];
    array_prof_pts[0].set_x(15.0);
    array_prof_pts[0].set_y(0.0);
    array_prof_pts[0].set_z(0.0);
    array_prof_pts[1].set_x(30.0);
    array_prof_pts[1].set_y(15.0);
    array_prof_pts[1].set_z(0.0);
    array_prof_pts[2].set_x(15.0);
    array_prof_pts[2].set_y(30.0);
    array_prof_pts[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, array_prof_pts, profile));

    // Create an axis
    SPAposition start(0.0, 0.0, 0.0);
    SPAvector axis(0.0, 20.0, 0.0);

    // Set sweep options
    sweep_options options;
    options.set_sweep_angle(4.712);
    options.set_steps(10);
    options.set_close_to_axis(TRUE);
    // Sweeping operation
    BODY* new_body = NULL;
    check_outcome(api_sweep_with_options(profile, start, axis, &options, new_body, ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(profile);
    }
    return result;
}
