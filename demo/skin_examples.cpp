/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#include "skin_examples.hxx"

#include "acis/acis.hxx"
#include "acis/add_pcu.hxx"
#include "acis/alltop.hxx"
#include "acis/api.hxx"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/efilter.hxx"
#include "acis/kernapi.hxx"
#include "acis/law.hxx"
#include "acis/lists.hxx"
#include "acis/logical.h"
#include "acis/pcudef.hxx"
#include "acis/pcurve.hxx"
#include "acis/pick_ray.hxx"
#include "acis/point.hxx"
#include "acis/position.hxx"
#include "acis/roll_utl.hxx"
#include "acis/skin.hxx"
#include "acis/skin_intr.hxx"
#include "acis/skin_opts.hxx"
#include "acis/skinapi.hxx"
#include "acis/surdef.hxx"
#include "acis/surf_utl.hxx"
#include "acis/surface.hxx"
#include "acis/trace.hxx"
#include "acis/transf.hxx"
#include "acis/wire_utl.hxx"

//-----------------------------------------------------------------------------------
// transforms
//-----------------------------------------------------------------------------------

SPAtransf rot_about_x(double angle) {
    // SPAvector x_axis(1.0,0.0,0.0);
    return rotate_transf(angle, x_axis);
}
SPAtransf rot_about_y(double angle) {
    // SPAvector y_axis(0.0,1.0,0.0);
    return rotate_transf(angle, y_axis);
}
SPAtransf rot_about_z(double angle) {
    // SPAvector z_axis(0.0,0.0,1.0);
    return rotate_transf(angle, z_axis);
}
SPAtransf move_along_x(double distance) {
    SPAvector direction(distance, 0.0, 0.0);
    return translate_transf(direction);
}
SPAtransf move_along_y(double distance) {
    SPAvector direction(0.0, distance, 0.0);
    return translate_transf(direction);
}
SPAtransf move_along_z(double distance) {
    SPAvector direction(0.0, 0.0, distance);
    return translate_transf(direction);
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_yo_yo: skinning wire bodies
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies.
// **********************************************************************************

outcome aei_SKIN_YO_YO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_yo_yo = NULL;

    // API Call Block
    API_BEGIN

    // Make circular edges
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    EDGE* circle3_edge[1];
    EDGE* circle4_edge[1];
    EDGE* circle5_edge[1];

    check_outcome(api_curve_arc(center, 10, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_curve_arc(center, 1, 0.0, 2 * M_PI, circle3_edge[0]));
    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle4_edge[0]));
    check_outcome(api_curve_arc(center, 10, 0.0, 2 * M_PI, circle5_edge[0]));

    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(-6.0)));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(-3.0)));
    check_outcome(api_transform_entity((ENTITY*)circle4_edge[0], move_along_z(3.0)));
    check_outcome(api_transform_entity((ENTITY*)circle5_edge[0], move_along_z(6.0)));

    // Make wire-bodies from edges
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));
    BODY* circle3 = NULL;
    check_outcome(api_make_ewire(1, circle3_edge, circle3));
    BODY* circle4 = NULL;
    check_outcome(api_make_ewire(1, circle4_edge, circle4));
    BODY* circle5 = NULL;
    check_outcome(api_make_ewire(1, circle5_edge, circle5));

    // Define an array of wire-bodies
    BODY* wires[5];
    wires[0] = circle1;
    wires[1] = circle2;
    wires[2] = circle3;
    wires[3] = circle4;
    wires[4] = circle5;

    // Skin the circles using api_skin_wires

    skin_options opts;
    check_outcome(api_skin_wires(5, wires, skin_yo_yo, &opts, ptrAcisOpt));

    for(int i = 0; i < 5; i++) {
        if(wires[i]) {
            check_outcome(api_del_entity(wires[i]));
        }
    }

    API_END

    if(result.ok()) output_ents.add(skin_yo_yo);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_star_seed1: skinning wire bodies
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies.
// **********************************************************************************

outcome aei_SKIN_STAR_SEED1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_star_seed1 = NULL;

    // API Call Block
    API_BEGIN

    // point1: wire-body
    BODY* point1 = NULL;
    SPAposition p1[1];
    p1[0].set_x(0.0);
    p1[0].set_y(0.0);
    p1[0].set_z(-3.0);
    check_outcome(api_make_wire(NULL, 1, p1, point1));

    // point2: wire-body
    BODY* point2 = NULL;
    SPAposition p2[1];
    p2[0].set_x(0.0);
    p2[0].set_y(0.0);
    p2[0].set_z(6.0);
    check_outcome(api_make_wire(NULL, 1, p2, point2));

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // star2: wire-body
    // Copy star1 and move it up along the z-axis to create star2
    BODY* star2 = NULL;
    check_outcome(api_copy_body(star1, star2));
    check_outcome(api_transform_entity((ENTITY*)star2, move_along_z(3.0)));

    // Define an array of wire-bodies
    BODY* wires[4];
    wires[0] = point1;
    wires[1] = star1;
    wires[2] = star2;
    wires[3] = point2;

    // Skin point1, star1, star2 and point2 using api_skin_wires
    skin_options opts;
    check_outcome(api_skin_wires(4, wires, skin_star_seed1, &opts, ptrAcisOpt));

    // Cleanup
    for(int j = 0; j < 4; j++) {
        if(wires[j]) {
            check_outcome(api_del_entity(wires[j]));
        }
    }

    API_END

    if(result.ok()) output_ents.add(skin_star_seed1);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_star_seed2: skinning an entity list
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of an entity list containing APOINTs and a BODY.
// **********************************************************************************

outcome aei_SKIN_STAR_SEED2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_star_seed2 = NULL;

    // API Call Block
    API_BEGIN

    // apoint1: APOINT
    SPAposition p1[1];
    p1[0].set_x(0.0);
    p1[0].set_y(0.0);
    p1[0].set_z(-3.0);
    APOINT* apoint1 = ACIS_NEW APOINT(p1[0]);

    // apoint2: APOINT
    SPAposition p2[1];
    p2[0].set_x(0.0);
    p2[0].set_y(0.0);
    p2[0].set_z(6.0);
    APOINT* apoint2 = ACIS_NEW APOINT(p2[0]);

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // Put the profiles into an entity list
    ENTITY_LIST entities;
    entities.add(apoint1);  // APOINT*
    entities.add(star1);    // BODY*
    entities.add(apoint2);  // APOINT*

    // Skin apoint1, star1 and apoint2
    skin_options opts;
    check_outcome(api_skin_wires(3, entities, skin_star_seed2, &opts, ptrAcisOpt));

    api_del_entity_list(entities);

    API_END

    if(result.ok()) output_ents.add(skin_star_seed2);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_star_drum: skinning an entity list
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of an entity list containing EDGEs and a BODY.
// **********************************************************************************

outcome aei_SKIN_STAR_DRUM(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_star_drum = NULL;

    // API Call Block
    API_BEGIN

    // circle1/circle2: EDGEs
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1 = NULL;
    EDGE* circle2 = NULL;
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1));
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle2));

    // Move circle2 up along the z-axis
    check_outcome(api_transform_entity((ENTITY*)circle2, move_along_z(20.0)));

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // Move the star up along the z-axis
    check_outcome(api_transform_entity((ENTITY*)star1, move_along_z(3.0)));

    // Put the profiles into an entity list
    ENTITY_LIST entities;
    entities.add(circle1);  // EDGE*
    entities.add(star1);    // BODY*
    entities.add(circle2);  // EDGE*

    // Skin circle1, star1 and circle2
    skin_options opts;
    check_outcome(api_skin_wires(3, entities, skin_star_drum, &opts, ptrAcisOpt));

    ENTITY* thisEnt = NULL;
    entities.init();
    while((thisEnt = entities.next()) != NULL) {
        api_del_entity(thisEnt);
    }

    API_END

    if(result.ok()) output_ents.add(skin_star_drum);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_seed_pod: creating a closed skin
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of an entity list containing EDGEs and a BODY
//    using the closed option.
// **********************************************************************************

outcome aei_SKIN_SEED_POD(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_seed_pod = NULL;

    // API Call Block
    API_BEGIN

    // circle1/circle2: EDGEs
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1 = NULL;
    EDGE* circle2 = NULL;
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1));
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle2));

    // Move circle2 up along the z-axis:
    check_outcome(api_transform_entity((ENTITY*)circle2, move_along_z(20.0)));

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // Move the star up along the z-axis
    check_outcome(api_transform_entity((ENTITY*)star1, move_along_z(3.0)));

    // Put the profiles into an entity list
    ENTITY_LIST entities;
    entities.add(circle1);  // EDGE*
    entities.add(star1);    // BODY*
    entities.add(circle2);  // EDGE*

    // Set the skinning options
    skin_options opts;
    opts.set_closed(TRUE);

    // Skin circle1, star1 and circle2
    check_outcome(api_skin_wires(3, entities, skin_seed_pod, &opts, ptrAcisOpt));

    api_del_entity_list(entities);

    API_END

    if(result.ok()) output_ents.add(skin_seed_pod);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_top: skinning an entity list
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of an entity list containing APOINTs and an EDGE.
// **********************************************************************************

outcome aei_SKIN_TOP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_top = NULL;

    // API Call Block
    API_BEGIN

    // apoint1: APOINT
    SPAposition p1[1];
    p1[0].set_x(0.0);
    p1[0].set_y(0.0);
    p1[0].set_z(-3.0);
    APOINT* apoint1 = ACIS_NEW APOINT(p1[0]);

    // apoint2: APOINT
    SPAposition p2[1];
    p2[0].set_x(0.0);
    p2[0].set_y(0.0);
    p2[0].set_z(6.0);
    APOINT* apoint2 = ACIS_NEW APOINT(p2[0]);

    // circle1: EDGE
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1 = NULL;
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1));

    // Put the profiles into an entity list
    ENTITY_LIST entities;
    entities.add(apoint1);  // APOINT*
    entities.add(circle1);  // EDGE*
    entities.add(apoint2);  // APOINT*

    // Skin apoint1, circle1 and apoint2
    skin_options opts;
    check_outcome(api_skin_wires(3, entities, skin_top, &opts, ptrAcisOpt));

    api_del_entity_list(entities);

    API_END

    if(result.ok()) output_ents.add(skin_top);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_bottle: skinning wires with a path
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies with a path.
// **********************************************************************************

outcome aei_SKIN_BOTTLE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_bottle = NULL;

    // API Call Block
    API_BEGIN

    // circle1/circle2: wire-bodies
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 2, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(20.0)));

    // Make wire-bodies from edges
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));

    // path: BODY
    EDGE* edge_path[1];
    SPAposition path_points[3];
    path_points[0].set_x(0.0);
    path_points[0].set_y(0.0);
    path_points[0].set_z(-10.0);
    path_points[1].set_x(0.0);
    path_points[1].set_y(1.0);
    path_points[1].set_z(25.0);
    path_points[2].set_x(0.0);
    path_points[2].set_y(0.0);
    path_points[2].set_z(25.0);
    check_outcome(api_curve_spline(3, path_points, NULL, NULL, edge_path[0]));

    // Create a wire-body using edge_path
    BODY* path = NULL;
    check_outcome(api_make_ewire(1, edge_path, path));

    // Define an array of wire-bodies
    BODY* wires[2];
    wires[0] = circle1;
    wires[1] = circle2;

    // Skin circle1 and circle2 with a path
    skin_options opts;
    check_outcome(api_skin_wires(2, wires, path, skin_bottle, &opts, ptrAcisOpt));

    api_del_entity(path);
    api_del_entity(circle1);
    api_del_entity(circle2);

    API_END

    if(result.ok()) output_ents.add(skin_bottle);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_vase: skinning wires with draft angles
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies with draft angles.
// **********************************************************************************

outcome aei_SKIN_VASE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_vase = NULL;

    // API Call Block
    API_BEGIN

    // circle1/circle2: wire-bodies
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    check_outcome(api_curve_arc(center, 8, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 2, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(20.0)));

    // Make wire-bodies from edges
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));

    // Make an array of wire-bodies
    BODY* wires[2];
    wires[0] = circle1;
    wires[1] = circle2;

    // Skin circle1 and circle2 with draft angles pi/2 and pi/9
    skin_options opts;
    check_outcome(api_skin_wires(2, wires, M_PI / 2.0, M_PI / 9.0, 60, 60, skin_vase, &opts, ptrAcisOpt));

    api_del_entity(circle1);
    api_del_entity(circle2);

    API_END

    if(result.ok()) output_ents.add(skin_vase);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_worm: skinning wires with guides
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies with one guide. Here the body consists
//    of one face and the option virtualGuides is set to FALSE.
// **********************************************************************************

outcome aei_SKIN_WORM(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_worm = NULL;

    // API Call Block
    API_BEGIN

    // circle1/circle2: wire-bodies
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    check_outcome(api_curve_arc(center, 1, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 1, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(9.0)));

    // Make wire-bodies from edges
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));

    // guide1: EDGE
    EDGE* guide1 = NULL;
    SPAposition guide1_points[4];

    guide1_points[0].set_x(1.0);  // on circle1
    guide1_points[0].set_y(0.0);
    guide1_points[0].set_z(0.0);

    guide1_points[1].set_x(-7.0);
    guide1_points[1].set_y(0.0);
    guide1_points[1].set_z(3.0);

    guide1_points[2].set_x(10.0);
    guide1_points[2].set_y(0.0);
    guide1_points[2].set_z(6.0);

    guide1_points[3].set_x(1.0);  // circle2
    guide1_points[3].set_y(0.0);
    guide1_points[3].set_z(9.0);

    check_outcome(api_curve_spline(4, guide1_points, NULL, NULL, guide1));

    // Make an array of wire-bodies
    BODY* wires[2];
    wires[0] = circle1;
    wires[1] = circle2;

    // Make an array of guides
    EDGE* guides[1];
    guides[0] = guide1;

    // Skin circle1 and circle2 with a guide
    skin_options opts;
    check_outcome(api_skin_wires(2, wires, 1, guides, skin_worm, &opts, ptrAcisOpt));

    api_del_entity(circle1);
    api_del_entity(circle2);
    api_del_entity(guide1);

    API_END

    if(result.ok()) output_ents.add(skin_worm);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_nose_star: skinning wires with guides
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies with one guide. Here the body consists
//    of multiple faces. The option virtualGuides is set to FALSE.
// **********************************************************************************

outcome aei_SKIN_NOSE_STAR(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_nose_star = NULL;

    // API Call Block
    API_BEGIN

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // circle1: wire-body
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center, 2, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(6.0)));

    // Make it into a wire-body
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));

    // guide1: EDGE
    EDGE* guide1 = NULL;
    SPAposition guide1_points[3];

    guide1_points[0].set_x(L + 2.0);  // on star1
    guide1_points[0].set_y(0.0);
    guide1_points[0].set_z(0.0);

    guide1_points[1].set_x(10.0);
    guide1_points[1].set_y(0.0);
    guide1_points[1].set_z(3.0);

    guide1_points[2].set_x(2.0);  // on circle1
    guide1_points[2].set_y(0.0);
    guide1_points[2].set_z(6.0);

    check_outcome(api_curve_spline(3, guide1_points, NULL, NULL, guide1));

    // Make an array of wire-bodies
    BODY* wires2[2];
    wires2[0] = star1;
    wires2[1] = circle1;

    // Make an array of guides
    EDGE* guides[1];
    guides[0] = guide1;

    // Skin star1 and circle1 with one guide and virtualGuides set to FALSE
    skin_options opts;
    check_outcome(api_skin_wires(2, wires2, 1, guides, skin_nose_star, &opts, ptrAcisOpt));

    api_del_entity(wires2[0]);
    api_del_entity(wires2[1]);
    api_del_entity(guide1);

    API_END

    if(result.ok()) output_ents.add(skin_nose_star);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_curved_star_body: skinning wires with guides
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of wire bodies with one guide. Here the body consists
//    of multiple faces and the option virtualGuides is set to TRUE.
// **********************************************************************************

outcome aei_SKIN_CURVED_STAR_BODY(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // Initialization Block
    BODY* skin_curved_star_body = NULL;

    // API Call Block
    API_BEGIN

    // star1: wire-body
    // Build star1 from 12 equilateral triangles
    BODY* triangles[12];

    // Make triangle[0]
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Create triangle[1],...,triangle[11] by copying and rotating triangle[0]
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * M_PI / 6.0)));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star
    BODY* star1 = triangles[0];

    // circle1: wire-body
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center, 2, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(6.0)));

    // Make it into a wire-body
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));

    // guide1: EDGE
    EDGE* guide1 = NULL;
    SPAposition guide1_points[3];

    guide1_points[0].set_x(L + 2.0);  // on star1
    guide1_points[0].set_y(0.0);
    guide1_points[0].set_z(0.0);

    guide1_points[1].set_x(6.0);
    guide1_points[1].set_y(0.0);
    guide1_points[1].set_z(3.0);

    guide1_points[2].set_x(2.0);  // on circle1
    guide1_points[2].set_y(0.0);
    guide1_points[2].set_z(6.0);

    check_outcome(api_curve_spline(3, guide1_points, NULL, NULL, guide1));

    // Make an array of wire-bodies
    BODY* wires[2];
    wires[0] = star1;
    wires[1] = circle1;

    // Make an array of guides
    EDGE* guides[1];
    guides[0] = guide1;

    // Set virtualGuides to TRUE
    skin_options opts;
    opts.set_virtualGuides(TRUE);

    // Skin star1 and circle1 with one guide and virtualGuides set to TRUE
    check_outcome(api_skin_wires(2, wires, 1, guides, skin_curved_star_body, &opts, ptrAcisOpt));

    api_del_entity(wires[0]);
    api_del_entity(wires[1]);
    api_del_entity(guide1);

    API_END

    if(result.ok()) output_ents.add(skin_curved_star_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_bad_stirrup: closed and periodic option
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning with closed option set to TRUE but periodic option
//    set to FALSE. Compare this with the test skin_good_stirrup where the periodic
//    option is also set to TRUE.
// **********************************************************************************

outcome aei_SKIN_BAD_STIRRUP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_bad_stirrup = NULL;
    // API Call Block
    API_BEGIN

    // First we make circular edges:
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    EDGE* circle3_edge[1];

    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_curve_arc(center, 0.2, 0.0, 2 * M_PI, circle3_edge[0]));

    // We move the first circle:
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], rot_about_x(M_PI / 2.0)));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], rot_about_z(M_PI / 6.0)));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_x(-4.0)));

    // We move the second circle:
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], rot_about_x(-M_PI / 2)));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], rot_about_z(-M_PI / 6.0)));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_x(4.0)));

    // We move the third circle:
    check_outcome(api_transform_entity((ENTITY*)circle3_edge[0], rot_about_y(M_PI / 2)));
    check_outcome(api_transform_entity((ENTITY*)circle3_edge[0], move_along_y(6.0)));

    // Now we make the edges into wire-bodies:
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));
    BODY* circle3 = NULL;
    check_outcome(api_make_ewire(1, circle3_edge, circle3));

    // Skinning operation:
    // We make an array of wire-bodies:
    BODY* wires[3];
    wires[0] = circle1;
    wires[1] = circle2;
    wires[2] = circle3;

    // We set the option closed to TRUE:
    skin_options opts;
    opts.set_closed(TRUE);

    // We make the body:
    check_outcome(api_skin_wires(3, wires, skin_bad_stirrup, &opts, ptrAcisOpt));

    // Clean-up:
    api_del_entity(circle1);
    api_del_entity(circle2);
    api_del_entity(circle3);

    API_END

    if(result.ok()) output_ents.add(skin_bad_stirrup);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_good_stirrup: closed and periodic option
//
// APIs:
//	  api_skin_wires
//
// Description:
//	  Demonstrates skinning of with closed and periodic option set to TRUE.
//    Compare this with the test skin_bad_stirrup where the periodic option is
//    set to FALSE.
// **********************************************************************************

outcome aei_SKIN_GOOD_STIRRUP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_good_stirrup = NULL;

    // API Call Block
    API_BEGIN

    // First we make circular edges:
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    EDGE* circle2_edge[1];
    EDGE* circle3_edge[1];

    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_curve_arc(center, 3, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_curve_arc(center, 0.2, 0.0, 2 * M_PI, circle3_edge[0]));

    // We move the first circle:
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], rot_about_x(M_PI / 2.0)));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], rot_about_z(M_PI / 6.0)));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_x(-4.0)));

    // We move the second circle:
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], rot_about_x(-M_PI / 2)));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], rot_about_z(-M_PI / 6.0)));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_x(4.0)));

    // We move the third circle:
    check_outcome(api_transform_entity((ENTITY*)circle3_edge[0], rot_about_y(M_PI / 2)));
    check_outcome(api_transform_entity((ENTITY*)circle3_edge[0], move_along_y(6.0)));

    // Now we make the edges into wire-bodies:
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));
    BODY* circle3 = NULL;
    check_outcome(api_make_ewire(1, circle3_edge, circle3));

    // Skinning operation

    // We skin circle1 and circle2 with draft angles pi/2 and pi/9
    // We make an array of wire-bodies:
    BODY* wires[3];
    wires[0] = circle1;
    wires[1] = circle2;
    wires[2] = circle3;

    // We set closed and periodic to TRUE by setting closed to 2:
    skin_options opts;
    opts.set_closed(2);

    // We make the body:
    check_outcome(api_skin_wires(3, wires, skin_good_stirrup, &opts, ptrAcisOpt));

    // Clean-up:
    api_del_entity(wires[0]);
    api_del_entity(wires[1]);
    api_del_entity(wires[2]);

    API_END

    if(result.ok()) output_ents.add(skin_good_stirrup);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_lense_body: lofting wires
//
// APIs:
//	  api_loft_coedges
//
// Description:
//	  Demonstrates lofting of wire bodies.
// **********************************************************************************

outcome aei_SKIN_LENSE_BODY(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_lense_body = NULL;

    // API Call Block
    API_BEGIN

    // debug file (api_unite_edges wants one)
    FILE* fp = NULL;  // fopen("d:/head6x/skin/debug_msgs.txt","a"); // (api_unite_edges wants one)

    // shape1: wire-body

    // First arc of the shape:
    SPAposition arc1_p1(0.0, 6.0, -6.0);
    SPAposition arc1_p2(3.0, 6.0, 0.0);
    SPAposition arc1_p3(0.0, 6.0, 6.0);
    EDGE* arc1 = NULL;
    check_outcome(api_curve_arc_3pt(arc1_p1, arc1_p2, arc1_p3, FALSE, arc1));

    // Second arc of the shape:
    SPAposition arc2_p1(0.0, 6.0, -6.0);
    SPAposition arc2_p2(-3.0, 6.0, 0.0);
    SPAposition arc2_p3(0.0, 6.0, 6.0);
    EDGE* arc2 = NULL;
    check_outcome(api_curve_arc_3pt(arc2_p1, arc2_p2, arc2_p3, FALSE, arc2));

    // We put the arcs into an entity list:
    ENTITY_LIST arcs;
    arcs.add(arc1);
    arcs.add(arc2);

    // We unite the arcs to make the shape:
    BODY* shape1 = NULL;
    check_outcome(api_unite_edges(arcs, shape1, fp));

    // shape2: wire-body

    // First arc of the shape:
    SPAposition arc3_p1(0.0, -6.0, -6.0);
    SPAposition arc3_p2(3.0, -6.0, 0.0);
    SPAposition arc3_p3(0.0, -6.0, 6.0);
    EDGE* arc3 = NULL;
    check_outcome(api_curve_arc_3pt(arc3_p1, arc3_p2, arc3_p3, FALSE, arc3));

    // Second arc of the shape:
    SPAposition arc4_p1(0.0, -6.0, -6.0);
    SPAposition arc4_p2(-3.0, -6.0, 0.0);
    SPAposition arc4_p3(0.0, -6.0, 6.0);
    EDGE* arc4 = NULL;
    check_outcome(api_curve_arc_3pt(arc4_p1, arc4_p2, arc4_p3, FALSE, arc4));

    // We put the arcs into an entity list:
    arcs.clear();
    arcs.add(arc3);
    arcs.add(arc4);

    // We unite the arcs to make the shape:
    BODY* shape2 = NULL;
    check_outcome(api_unite_edges(arcs, shape2, fp));

    // Skinning operation:
    // We loft the two shapes:

    // Sections:

    // A section is an object of type Loft_Connected_Coedge_List and is
    // associated with a lofting profile.
    // It contains information about
    //     - the number of coedges in the profile:         int
    //     - the coedges:                                  COEDGE **
    //     - the coedge orientation:                       FORWARD or REVERSE
    //     - the tangent factor:                           double
    //     - the laws that are to be used on the coedges:  law **

    // First we need to define an array of sections that holds as many
    // sections as there are profiles:
    Loft_Connected_Coedge_List* shape_sections = ACIS_NEW Loft_Connected_Coedge_List[2];

    // Next we need to get the profile coedges:
    ENTITY_LIST shape1_entlist;
    ENTITY_LIST shape2_entlist;
    check_outcome(api_get_coedges(shape1, shape1_entlist));
    check_outcome(api_get_coedges(shape2, shape2_entlist));

    // and convert the resulting ENTITY_LIST into a list of COEDGES:
    COEDGE* shape1_coedges[2];
    COEDGE* shape2_coedges[2];
    shape1_coedges[0] = (COEDGE*)shape1_entlist[0];
    shape1_coedges[1] = (COEDGE*)shape1_entlist[1];
    shape2_coedges[0] = (COEDGE*)shape2_entlist[0];
    shape2_coedges[1] = (COEDGE*)shape2_entlist[1];

    // Now we can make the sections:

    // section for shape1:
    shape_sections[0].n_list = 2;
    shape_sections[0].coedge_list = shape1_coedges;
    shape_sections[0].coedge_orient = FORWARD;
    shape_sections[0].cross_tg_attr = 10.0;
    shape_sections[0].law_list = NULL;

    // section for shape2:
    shape_sections[1].n_list = 2;
    shape_sections[1].coedge_list = shape2_coedges;
    shape_sections[1].coedge_orient = FORWARD;
    shape_sections[1].cross_tg_attr = 10.0;
    shape_sections[1].law_list = NULL;

    skin_options opts;

    // We make the body:
    check_outcome(api_loft_coedges(2, shape_sections, skin_lense_body, &opts, ptrAcisOpt));

    // Clean-up:
    api_del_entity(shape1);
    api_del_entity(shape2);
    ACIS_DELETE[] shape_sections;

    API_END

    if(result.ok()) output_ents.add(skin_lense_body);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_balloon: lofting wires with laws
//
// APIs:
//	  api_loft_coedges
//
// Description:
//	  Demonstrates lofting of wire bodies with laws.
// **********************************************************************************

outcome aei_SKIN_BALLOON(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_balloon = NULL;

    // API Call Block
    API_BEGIN

    // point: wire-body
    BODY* point = NULL;
    SPAposition p[1];
    p[0].set_x(0.0);
    p[0].set_y(0.0);
    p[0].set_z(10.0);
    check_outcome(api_make_wire(NULL, 1, p, point));

    // square: wire-body
    BODY* square = NULL;
    SPAposition q[5];

    q[0].set_x(1.0);
    q[0].set_y(1.0);
    q[0].set_z(0.0);

    q[1].set_x(-1.0);
    q[1].set_y(1.0);
    q[1].set_z(0.0);

    q[2].set_x(-1.0);
    q[2].set_y(-1.0);
    q[2].set_z(0.0);

    q[3].set_x(1.0);
    q[3].set_y(-1.0);
    q[3].set_z(0.0);

    q[4].set_x(1.0);
    q[4].set_y(1.0);
    q[4].set_z(0.0);

    check_outcome(api_make_wire(NULL, 5, q, square));

    // Skinning operation:

    // Laws:
    // A circular SPAvector law for the point:
    //   DOMAIN(VEC(COS(T),SIN(T),0),0,2*PI)

    law* Asub1[3];
    law* Asub6 = ACIS_NEW pi_law();               // PI
    law* Asub5 = ACIS_NEW constant_law(2);        // 2
    Asub1[2] = ACIS_NEW times_law(Asub5, Asub6);  // 2*PI

    Asub1[1] = ACIS_NEW constant_law(0);  // 0

    law* Asub2[3];
    Asub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Asub4 = ACIS_NEW identity_law(0);     // T
    Asub2[1] = ACIS_NEW sin_law(Asub4);        // SIN(T);
    law* Asub3 = ACIS_NEW identity_law(0);     // T
    Asub2[0] = ACIS_NEW cos_law(Asub3);        // COS(T);
    Asub1[0] = ACIS_NEW vector_law(Asub2, 3);  // VEC(COS(T),SIN(T),0)

    law* circular_vector_law = ACIS_NEW domain_law(Asub1, 3);

    // clean up
    Asub1[0]->remove();
    Asub1[1]->remove();
    Asub1[2]->remove();
    Asub2[0]->remove();
    Asub2[1]->remove();
    Asub2[2]->remove();
    Asub3->remove();
    Asub4->remove();
    Asub5->remove();
    Asub6->remove();

    // A constant SPAvector law for the square:
    // DOMAIN(VEC(0,0,1),0,1)

    law* Bsub1[3];
    Bsub1[2] = ACIS_NEW constant_law(1);  // 1
    Bsub1[1] = ACIS_NEW constant_law(0);  // 0
    law* Bsub2[3];
    Bsub2[2] = ACIS_NEW constant_law(1);       // 1
    Bsub2[1] = ACIS_NEW constant_law(0);       // 0
    Bsub2[0] = ACIS_NEW constant_law(0);       // 0
    Bsub1[0] = ACIS_NEW vector_law(Bsub2, 3);  // VEC(0,0,1)

    law* constant_vector_law = ACIS_NEW domain_law(Bsub1, 3);

    // clean up
    Bsub1[0]->remove();
    Bsub1[1]->remove();
    Bsub1[2]->remove();
    Bsub2[0]->remove();
    Bsub2[1]->remove();
    Bsub2[2]->remove();

    // Sections:

    // A section is an object of type Loft_Connected_Coedge_List and is
    // associated with a lofting profile.
    // It contains information about
    //     - the number of coedges in the profile:         int
    //     - the coedges:                                  COEDGE **
    //     - the coedge orientation:                       FORWARD or REVERSE
    //     - the tangent factor:                           double
    //     - the laws that are to be used on the coedges:  law **

    // First we need to define an array of sections that holds as many
    // sections as there are profiles:
    Loft_Connected_Coedge_List* sections = ACIS_NEW Loft_Connected_Coedge_List[2];

    // Next we need to get the profile coedges:
    ENTITY_LIST point_entlist;
    ENTITY_LIST square_entlist;
    check_outcome(api_get_coedges(point, point_entlist));
    check_outcome(api_get_coedges(square, square_entlist));

    // and convert the resulting ENTITY_LIST into a list of COEDGES:
    COEDGE* point_coedges[1];
    COEDGE* square_coedges[4];
    point_coedges[0] = (COEDGE*)point_entlist[0];
    square_coedges[0] = (COEDGE*)square_entlist[0];
    square_coedges[1] = (COEDGE*)square_entlist[1];
    square_coedges[2] = (COEDGE*)square_entlist[2];
    square_coedges[3] = (COEDGE*)square_entlist[3];

    // We want to loft with laws, so:

    // we add the circular SPAvector law to point section:
    law* point_law_list[1];
    point_law_list[0] = circular_vector_law;

    // and the constant SPAvector law to square section:
    law* square_law_list[4];
    square_law_list[0] = constant_vector_law;
    square_law_list[1] = constant_vector_law;
    square_law_list[2] = constant_vector_law;
    square_law_list[3] = constant_vector_law;

    // Now we can make the sections:

    // section for point:
    sections[0].n_list = 1;
    sections[0].coedge_list = point_coedges;
    sections[0].coedge_orient = FORWARD;
    sections[0].cross_tg_attr = 20.0;
    sections[0].law_list = point_law_list;

    // section for square:
    sections[1].n_list = 4;
    sections[1].coedge_list = square_coedges;
    sections[1].coedge_orient = FORWARD;
    sections[1].cross_tg_attr = 1.0;
    sections[1].law_list = square_law_list;

    skin_options opts;

    // We loft the square and the point:
    check_outcome(api_loft_coedges(2, sections, skin_balloon, &opts, ptrAcisOpt));

    check_outcome(api_body_to_2d(skin_balloon));

    // Clean-up:
    circular_vector_law->remove();
    constant_vector_law->remove();
    ACIS_DELETE[] sections;
    api_del_entity(point);
    api_del_entity(square);

    API_END

    if(result.ok()) output_ents.add(skin_balloon);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_twisted_star_seed: skinning interface with mapping curves
//
// APIs:
//	  api_create_si,api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_add_mapping_curve_sli,api_breakup_wires_sli,api_build_body_sli,
//    api_delete_sli
//
// Description:
//	  Demonstrates the use of the skinning interface with one mapping curve.
//    Adding the mapping cure to the interface allows to create a twisted body.
// **********************************************************************************

outcome aei_SKIN_TWISTED_STAR_SEED(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_twisted_star_seed = NULL;
    API_BEGIN

    // point1: wire-body
    BODY* point1 = NULL;
    SPAposition p1[1];
    p1[0].set_x(0.0);
    p1[0].set_y(0.0);
    p1[0].set_z(-5.0);
    check_outcome(api_make_wire(NULL, 1, p1, point1));

    // point2: wire-body
    BODY* point2 = NULL;
    SPAposition p2[1];
    p2[0].set_x(0.0);
    p2[0].set_y(0.0);
    p2[0].set_z(10.0);
    check_outcome(api_make_wire(NULL, 1, p2, point2));

    // star1: wire-body
    // We build star1 from 12 equilateral triangles:
    BODY* triangles[12];

    // First we make triangle[0]:
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(1.0);
    points[0].set_z(0.0);
    points[1].set_x(L + 2.0);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-1);
    points[2].set_z(0.0);
    check_outcome(api_make_wire(NULL, 3, points, triangles[0]));

    // Now we obtain triangle[1],...,triangle[11]
    // by copying and rotating triangle[0]:
    for(int i = 1; i < 12; i++) {
        check_outcome(api_copy_body(triangles[0], triangles[i]));
        check_outcome(api_transform_entity((ENTITY*)triangles[i], rot_about_z(i * (M_PI / 6.0))));

        // Simultaneously, we also unite the new triangle with triangle[0]
        // s.t. when we are done triangle[0] will be a star.
        check_outcome(api_unite(triangles[i], triangles[0]));
    }

    // We obtain a star:
    BODY* star1 = triangles[0];

    // star2: wire-body

    // To make a second star, we copy star1 and move it up along the z-axis:
    BODY* star2 = NULL;
    check_outcome(api_copy_body(star1, star2));
    check_outcome(api_transform_entity((ENTITY*)star2, move_along_z(5.0)));

    // mapping_curve
    SPAposition mapping_curve[4];

    mapping_curve[0].set_x(0.0);
    mapping_curve[0].set_y(0.0);
    mapping_curve[0].set_z(-5.0);

    mapping_curve[1].set_x(L);
    mapping_curve[1].set_y(1.0);
    mapping_curve[1].set_z(0.0);

    mapping_curve[2].set_x(L + 2);
    mapping_curve[2].set_y(0.0);
    mapping_curve[2].set_z(5.0);

    mapping_curve[3].set_x(0.0);
    mapping_curve[3].set_y(0.0);
    mapping_curve[3].set_z(10.0);

    EDGE* false_mapping_curve = NULL;
    SPAunit_vector start(0, 0, 1);
    SPAunit_vector end(0, 0, 1);
    check_outcome(api_curve_spline(4, mapping_curve, &start, &end, false_mapping_curve));

    // Skinning operation:

    // We skin point1, star1, star2 and point2 using
    // the interactive interface

    // First we define an entity list of wire-bodies:
    ENTITY_LIST wire_list;
    wire_list.add(point1);
    wire_list.add(star1);
    wire_list.add(star2);
    wire_list.add(point2);

    const char* name = "star";

    // We declare an interface object:
    AcisSkinningInterface* the_interface = NULL;
    skin_options opts;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We build the interface:
    check_outcome(api_create_si(wire_list, the_interface, wire_bodies, (BODY*)NULL, &opts, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // We add the mapping curve:
    check_outcome(api_add_mapping_curve_sli(the_interface, 4, mapping_curve, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // We make the body:
    check_outcome(api_build_body_sli(the_interface, skin_twisted_star_seed, ptrAcisOpt));

    // Clean-up:
    check_outcome(api_delete_sli(the_interface, ptrAcisOpt));
    api_del_entity_list(wire_list);
    api_del_entity(false_mapping_curve);

    API_END

    if(result.ok()) output_ents.add(skin_twisted_star_seed);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_balloon_on_cylindrical_face1: skinning interface with vertex modification
//
// APIs:
//	  api_create_si,api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_breakup_wires_sli,api_build_body_sli,api_delete_sli
//
// Description:
//	  Demonstrates vertex modification using the skinning interface.
//    This test creates a skin without vertex modification. Its purpose is to
//    serve as comparison to the test skin_balloon_on_cylindrical_face2 where
//    vertex modification is used to create a symmetrical skin.
// **********************************************************************************

outcome aei_SKIN_BALLOON_ON_CYLINDRICAL_FACE1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_balloon_on_cylindrical_face1 = NULL;

    // API Call Block
    API_BEGIN

    // debug file (api_unite_edges wants one)
    FILE* fp = NULL;  // fopen("d:/head6x/skin/debug_msgs.txt","a"); // (api_unite_edges wants one)

    // cylindrical_wire
    SPAposition p1(2.0, -2.0, 0.0);
    SPAposition p2(0.0, -2.0, -2.0);
    SPAposition p3(-2.0, -2.0, 0.0);
    SPAposition p4(-2.0, 2.0, 0.0);
    SPAposition p5(0.0, 2.0, -2.0);
    SPAposition p6(2.0, 2.0, 0.0);

    EDGE* edge1 = NULL;
    EDGE* edge2 = NULL;
    EDGE* edge3 = NULL;
    EDGE* edge4 = NULL;

    check_outcome(api_curve_arc_3pt(p1, p2, p3, FALSE, edge1));
    check_outcome(api_curve_line(p3, p4, edge2));
    check_outcome(api_curve_arc_3pt(p4, p5, p6, FALSE, edge3));
    check_outcome(api_curve_line(p6, p1, edge4));

    ENTITY_LIST edges;
    edges.add(edge1);
    edges.add(edge2);
    edges.add(edge3);
    edges.add(edge4);

    BODY* cylindrical_wire = NULL;
    check_outcome(api_unite_edges(edges, cylindrical_wire, fp));

    // circle1

    // We make a circular edge:
    const SPAposition center1(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center1, 6, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(8.0)));

    // and make it into a wire-body:
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));

    // circle2

    // We make a circular edge:
    const SPAposition center2(0.0, 0.0, 0.0);
    EDGE* circle2_edge[1];
    check_outcome(api_curve_arc(center2, 0.5, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(12.0)));

    // and make it into a wire-body:
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));

    // Skinning operation:

    // First we put the profiles into an entity list:
    ENTITY_LIST entities;
    entities.add(cylindrical_wire);
    entities.add(circle1);
    entities.add(circle2);

    // We declare an interface object:
    AcisSkinningInterface* the_interface = NULL;
    skin_options opts;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We build the interface:
    check_outcome(api_create_si(entities, the_interface, wire_bodies, (BODY*)NULL, &opts, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // We make the body:
    check_outcome(api_build_body_sli(the_interface, skin_balloon_on_cylindrical_face1, ptrAcisOpt));

    // Clean-up:
    check_outcome(api_delete_sli(the_interface, ptrAcisOpt));
    api_del_entity_list(entities);

    API_END

    if(result.ok()) output_ents.add(skin_balloon_on_cylindrical_face1);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_balloon_on_cylindrical_face2: skinning interface with vertex modification
//
// APIs:
//	  api_create_si,api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_breakup_wires_sli,api_build_body_sli,api_delete_sli,api_modify_wire_sli
//
// Description:
//	  Demonstrates vertex modification using the skinning interface. The body is
//    the same as in the test skin_balloon_on_cylindrical_face1 exept that we have
//    moved the vertices on the middle circle to create a symmetrical skin.
// **********************************************************************************

outcome aei_SKIN_BALLOON_ON_CYLINDRICAL_FACE2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_balloon_on_cylindrical_face2 = NULL;

    // API Call Block
    API_BEGIN

    // debug file (api_unite_edges wants one)
    FILE* fp = NULL;  // fopen("d:/head6x/skin/debug_msgs.txt","a"); // (api_unite_edges wants one)

    // cylindrical_wire
    SPAposition p1(2.0, -2.0, 0.0);
    SPAposition p2(0.0, -2.0, -2.0);
    SPAposition p3(-2.0, -2.0, 0.0);
    SPAposition p4(-2.0, 2.0, 0.0);
    SPAposition p5(0.0, 2.0, -2.0);
    SPAposition p6(2.0, 2.0, 0.0);

    EDGE* edge1 = NULL;
    EDGE* edge2 = NULL;
    EDGE* edge3 = NULL;
    EDGE* edge4 = NULL;

    check_outcome(api_curve_arc_3pt(p1, p2, p3, FALSE, edge1));
    check_outcome(api_curve_line(p3, p4, edge2));
    check_outcome(api_curve_arc_3pt(p4, p5, p6, FALSE, edge3));
    check_outcome(api_curve_line(p6, p1, edge4));

    ENTITY_LIST edges;
    edges.add(edge1);
    edges.add(edge2);
    edges.add(edge3);
    edges.add(edge4);

    BODY* cylindrical_wire = NULL;
    check_outcome(api_unite_edges(edges, cylindrical_wire, fp));

    // circle1

    // We make a circular edge:
    const SPAposition center1(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center1, 6, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(8.0)));

    // and make it into a wire-body:
    BODY* circle1 = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle1));

    // circle2

    // We make a circular edge:
    const SPAposition center2(0.0, 0.0, 0.0);
    EDGE* circle2_edge[1];
    check_outcome(api_curve_arc(center2, 0.5, 0.0, 2 * M_PI, circle2_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle2_edge[0], move_along_z(12.0)));

    // and make it into a wire-body:
    BODY* circle2 = NULL;
    check_outcome(api_make_ewire(1, circle2_edge, circle2));

    // Skinning operation:

    // First we put the profiles into an entity list:
    ENTITY_LIST entities;
    entities.add(cylindrical_wire);
    entities.add(circle1);
    entities.add(circle2);

    // We declare an interface object:
    AcisSkinningInterface* the_interface = NULL;
    skin_options opts;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We build the interface:
    check_outcome(api_create_si(entities, the_interface, wire_bodies, (BODY*)NULL, &opts, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli(the_interface, 0, 0, ptrAcisOpt));

    // Vertex modification:

    // The wires have now been broken up into an equal number of
    // coedges. In order to demonstrate how we can use vertex
    // modification to chenge the shape of a body we will move the
    // vertices on the middle circle into places.

    // It is helpful to look at the start points and end points of
    // the wire coedges (we need to take into account the coedge sense)
    // in order to determine in what oder we should pass coedges and
    // vertices into the api (the rule is: first coedge, second coedge,
    // replacement for the vertex that joins the two).

    // We need to make new positions for vertices:

    double a = 6.0 * cos((5.0 * M_PI) / 12.0);
    double b = 6.0 * sin((5.0 * M_PI) / 12.0);

    SPAposition nice_points[4];

    nice_points[0].set_x(a);
    nice_points[0].set_y(-b);
    nice_points[0].set_z(8.0);

    nice_points[1].set_x(-a);
    nice_points[1].set_y(-b);
    nice_points[1].set_z(8.0);

    nice_points[2].set_x(-a);
    nice_points[2].set_y(b);
    nice_points[2].set_z(8.0);

    nice_points[3].set_x(a);
    nice_points[3].set_y(b);
    nice_points[3].set_z(8.0);

    // We need the coedges of the circle after breakup:
    ENTITY_LIST coedges;
    check_outcome(api_get_coedges((ENTITY*)wire_bodies[1], coedges));

    // Before we can modify the wire we heve to turn it into a WIRE*:
    WIRE* wire_circle1 = (wire_bodies[1]->wire() != NULL) ? wire_bodies[1]->wire() : wire_bodies[1]->lump()->shell()->wire();

    check_outcome(api_modify_wire_sli(the_interface, (COEDGE*)coedges[0], (COEDGE*)coedges[1], nice_points[0], wire_circle1, ptrAcisOpt));
    check_outcome(api_modify_wire_sli(the_interface, (COEDGE*)coedges[1], (COEDGE*)coedges[2], nice_points[1], wire_circle1, ptrAcisOpt));
    check_outcome(api_modify_wire_sli(the_interface, (COEDGE*)coedges[2], (COEDGE*)coedges[3], nice_points[2], wire_circle1, ptrAcisOpt));
    check_outcome(api_modify_wire_sli(the_interface, (COEDGE*)coedges[3], (COEDGE*)coedges[0], nice_points[3], wire_circle1, ptrAcisOpt));

    // We make the body:
    check_outcome(api_build_body_sli(the_interface, skin_balloon_on_cylindrical_face2, ptrAcisOpt));

    // Clean-up:
    check_outcome(api_delete_sli(the_interface, ptrAcisOpt));

    api_del_entity_list(entities);

    API_END

    if(result.ok()) output_ents.add(skin_balloon_on_cylindrical_face2);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_robot_tooth: perpendicular option
//
// APIs:
//	  api_create_si,api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_breakup_wires_sli,api_build_body_sli,api_delete_sli
//
// Description:
//	  Demonstrates the use of the perpendicular option.
// **********************************************************************************

outcome aei_SKIN_ROBOT_TOOTH(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_robot_tooth = NULL;

    // API Call Block
    API_BEGIN

    // debug file (api_unite_edges wants one)
    FILE* fp = NULL;  // fopen("d:/head6x/skin/debug_msgs.txt","a"); // (api_unite_edges wants one)

    // wire1
    SPAposition p1(4.0, 0.0, 0.0);
    SPAposition p2(0.0, 0.0, 4.0);
    SPAposition p3(-4.0, 0.0, 0.0);

    EDGE* circle_edge = NULL;
    EDGE* line_edge = NULL;
    check_outcome(api_curve_arc_3pt(p1, p2, p3, FALSE, circle_edge));
    check_outcome(api_curve_line(p3, p1, line_edge));

    ENTITY_LIST edges;
    edges.add(circle_edge);
    edges.add(line_edge);
    BODY* circle1 = NULL;
    check_outcome(api_unite_edges(edges, circle1, fp));
    FACE* face1 = NULL;
    WIRE* wire1 = (circle1->wire() != NULL) ? circle1->wire() : circle1->lump()->shell()->wire();
    check_outcome(api_cover_wire(wire1, SpaAcis::NullObj::get_surface(), face1));

    // wire2

    // points to construct the first profile
    SPAposition p4(4.0, 0.0, 10.0);
    SPAposition p5(-4.0, 0.0, 10.0);
    EDGE* edge3[1];
    check_outcome(api_curve_line(p4, p5, edge3[0]));
    BODY* wire2 = NULL;
    check_outcome(api_make_ewire(1, edge3, wire2));

    // Skinning operation:

    //-----------------------------------------------------------------------
    // Sections:

    // A section is an object of type Loft_Connected_Coedge_List and is
    // associated with a lofting profile.
    // It contains information about
    //     - the number of coedges in the profile:         int
    //     - the coedges:                                  COEDGE **
    //     - the coedge orientation:                       FORWARD or REVERSE
    //     - the tangent factor:                           double
    //     - the laws that are to be used on the coedges:  law **

    // First we need to define an array of sections that holds as many
    // sections as there are profiles:
    Loft_Connected_Coedge_List* sections = ACIS_NEW Loft_Connected_Coedge_List[2];

    // Next we need to get the profile coedges:
    ENTITY_LIST wire1_entlist;
    ENTITY_LIST wire2_entlist;
    check_outcome(api_get_coedges(circle1, wire1_entlist));
    check_outcome(api_get_coedges(wire2, wire2_entlist));

    // and convert the resulting ENTITY_LIST into a list of COEDGES:
    COEDGE* wire1_coedges[1];
    COEDGE* wire2_coedges[1];

    // we want the half circle
    for(int i = 0; i < 1; i++) wire1_coedges[i] = (COEDGE*)wire1_entlist[i + 1];
    for(int j = 0; j < 1; j++) wire2_coedges[j] = (COEDGE*)wire2_entlist[j];

    // Now we can make the sections:

    // section for wire1:
    sections[0].n_list = 1;
    sections[0].coedge_list = wire1_coedges;
    sections[0].coedge_orient = FORWARD;
    sections[0].cross_tg_attr = 1.0;
    sections[0].law_list = NULL;

    // section for wire2:
    sections[1].n_list = 1;
    sections[1].coedge_list = wire2_coedges;
    sections[1].coedge_orient = FORWARD;
    sections[1].cross_tg_attr = 1.0;
    sections[1].law_list = NULL;

    // We loft wire1 and wire12 using the lofting interface

    // We declare an interface object:
    AcisLoftingInterface* the_interface = NULL;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We set perpendicular to TRUE:
    skin_options opts;
    opts.set_perpendicular(TRUE);
    opts.set_solid(FALSE);

    // We build the interface:
    check_outcome(api_create_li(2, sections, the_interface, wire_bodies, &opts, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // We make the sheet-body, thicken it:
    check_outcome(api_build_body_sli((AcisSLInterface*)the_interface, skin_robot_tooth, ptrAcisOpt));
    SPAposition box_start(-10.0, -10.0, -10.0);
    SPAposition box_end(10.0, 10.0, 10.0);
    check_outcome(api_body_to_2d(skin_robot_tooth));

    // Clean-up:
    check_outcome(api_delete_sli((AcisSLInterface*)the_interface, ptrAcisOpt));
    ACIS_DELETE[] sections;
    api_del_entity(circle1);
    api_del_entity(wire2);

    API_END

    if(result.ok()) output_ents.add(skin_robot_tooth);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_bad_square_egg: lofting with laws and estimating tangent factors
//
// APIs:
//	  api_loft_coedges
//
// Description:
//	  Demonstrates tangent factor estimation. This test is to be compared to
//    the test skin_good_square_egg where the tangent factors are optimized.
// **********************************************************************************

outcome aei_SKIN_BAD_SQUARE_EGG(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_bad_square_egg = NULL;

    // API Call Block
    API_BEGIN

    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center, .1, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(10.0)));

    // Now we make the edges into wire-bodies:
    BODY* circle = NULL;
    check_outcome(api_make_ewire(1, circle1_edge, circle));

    // square: wire-body
    BODY* square = NULL;
    double t = M_PI / 4.0;
    SPAposition q[5];

    q[0].set_x(t);
    q[0].set_y(t);
    q[0].set_z(0.0);

    q[1].set_x(-t);
    q[1].set_y(t);
    q[1].set_z(0.0);

    q[2].set_x(-t);
    q[2].set_y(-t);
    q[2].set_z(0.0);

    q[3].set_x(t);
    q[3].set_y(-t);
    q[3].set_z(0.0);

    q[4].set_x(t);
    q[4].set_y(t);
    q[4].set_z(0.0);

    check_outcome(api_make_wire(NULL, 5, q, square));

    // Skinning operation:

    // Laws:
    // <>?<>?
    // A circular SPAvector law for the circle:
    // DOMAIN(VEC(COS(T),SIN(T),0),0,2*PI)
    law* Asub1[3];

    law* Asub6 = ACIS_NEW pi_law();               // PI
    law* Asub5 = ACIS_NEW constant_law(2);        // 2
    Asub1[2] = ACIS_NEW times_law(Asub5, Asub6);  // 2*PI

    Asub1[1] = ACIS_NEW constant_law(0);  // 0

    law* Asub2[3];
    Asub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Asub4 = ACIS_NEW identity_law(0);     // T
    Asub2[1] = ACIS_NEW sin_law(Asub4);        // SIN(T);
    law* Asub3 = ACIS_NEW identity_law(0);     // T
    Asub2[0] = ACIS_NEW cos_law(Asub3);        // COS(T);
    Asub1[0] = ACIS_NEW vector_law(Asub2, 3);  // VEC(COS(T),SIN(T),0)

    law* circular_vector_law = ACIS_NEW domain_law(Asub1, 3);

    // clean up
    Asub1[0]->remove();
    Asub1[1]->remove();
    Asub1[2]->remove();
    Asub2[0]->remove();
    Asub2[1]->remove();
    Asub2[2]->remove();
    Asub3->remove();
    Asub4->remove();
    Asub5->remove();
    Asub6->remove();

    // A second circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),-PI/4,PI/4)
    law* Bsub1[3];

    law* Bsub9 = ACIS_NEW pi_law();               // PI
    law* Bsub8 = ACIS_NEW constant_law(0.25);     // .25
    Bsub1[2] = ACIS_NEW times_law(Bsub8, Bsub9);  // 0.25*PI

    law* Bsub7 = ACIS_NEW pi_law();               // PI
    law* Bsub6 = ACIS_NEW constant_law(0.25);     // .25
    law* Bsub5 = ACIS_NEW negate_law(Bsub6);      // -
    Bsub1[1] = ACIS_NEW times_law(Bsub5, Bsub7);  // -0.25*PI

    law* Bsub2[3];
    Bsub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Bsub4 = ACIS_NEW identity_law(0);     // T
    Bsub2[1] = ACIS_NEW sin_law(Bsub4);        // SIN(T);
    law* Bsub3 = ACIS_NEW identity_law(0);     // T
    Bsub2[0] = ACIS_NEW cos_law(Bsub3);        // COS(T);
    Bsub1[0] = ACIS_NEW vector_law(Bsub2, 3);  // VEC(COS(T),SIN(T),0.5)

    law* second_circular_vector_law = ACIS_NEW domain_law(Bsub1, 3);

    // clean up
    Bsub1[0]->remove();
    Bsub1[1]->remove();
    Bsub1[2]->remove();
    Bsub2[0]->remove();
    Bsub2[1]->remove();
    Bsub2[2]->remove();
    Bsub3->remove();
    Bsub4->remove();
    Bsub5->remove();
    Bsub6->remove();
    Bsub7->remove();
    Bsub8->remove();
    Bsub9->remove();

    // A third circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),PI/4,3/4*PI)
    law* Csub1[3];

    law* Csub8 = ACIS_NEW pi_law();               // PI
    law* Csub7 = ACIS_NEW constant_law(0.75);     // .75
    Csub1[2] = ACIS_NEW times_law(Csub7, Csub8);  // 0.75*PI

    law* Csub6 = ACIS_NEW pi_law();               // PI
    law* Csub5 = ACIS_NEW constant_law(0.25);     // .25
    Csub1[1] = ACIS_NEW times_law(Csub5, Csub6);  // 0.25*PI

    law* Csub2[3];
    Csub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Csub4 = ACIS_NEW identity_law(0);     // T
    Csub2[1] = ACIS_NEW sin_law(Csub4);        // SIN(T);
    law* Csub3 = ACIS_NEW identity_law(0);     // T
    Csub2[0] = ACIS_NEW cos_law(Csub3);        // COS(T);
    Csub1[0] = ACIS_NEW vector_law(Csub2, 3);  // VEC(COS(T),SIN(T),0.5)

    law* third_circular_vector_law = ACIS_NEW domain_law(Csub1, 3);

    // clean up
    Csub1[0]->remove();
    Csub1[1]->remove();
    Csub1[2]->remove();
    Csub2[0]->remove();
    Csub2[1]->remove();
    Csub2[2]->remove();
    Csub3->remove();
    Csub4->remove();
    Csub5->remove();
    Csub6->remove();
    Csub7->remove();
    Csub8->remove();

    // A fourth circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),3/4*PI,5/4*PI)
    law* Dsub1[3];

    law* Dsub8 = ACIS_NEW pi_law();               // PI
    law* Dsub7 = ACIS_NEW constant_law(1.25);     // 1.25
    Dsub1[2] = ACIS_NEW times_law(Dsub7, Dsub8);  // 1.25*PI

    law* Dsub6 = ACIS_NEW pi_law();               // PI
    law* Dsub5 = ACIS_NEW constant_law(0.75);     // 0.75
    Dsub1[1] = ACIS_NEW times_law(Dsub5, Dsub6);  // 0.75*PI

    law* Dsub2[3];
    Dsub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Dsub4 = ACIS_NEW identity_law(0);     // T
    Dsub2[1] = ACIS_NEW sin_law(Dsub4);        // SIN(T);
    law* Dsub3 = ACIS_NEW identity_law(0);     // T
    Dsub2[0] = ACIS_NEW cos_law(Dsub3);        // COS(T);
    Dsub1[0] = ACIS_NEW vector_law(Dsub2, 3);  // VEC(COS(T),SIN(T),0.5)

    law* fourth_circular_vector_law = ACIS_NEW domain_law(Dsub1, 3);

    // clean up
    Dsub1[0]->remove();
    Dsub1[1]->remove();
    Dsub1[2]->remove();
    Dsub2[0]->remove();
    Dsub2[1]->remove();
    Dsub2[2]->remove();
    Dsub3->remove();
    Dsub4->remove();
    Dsub5->remove();
    Dsub6->remove();
    Dsub7->remove();
    Dsub8->remove();

    // A fifth circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),5/4*PI,7/4*PI)
    law* Esub1[3];

    law* Esub8 = ACIS_NEW pi_law();               // PI
    law* Esub7 = ACIS_NEW constant_law(1.75);     // 1.75
    Esub1[2] = ACIS_NEW times_law(Esub7, Esub8);  // 1.75*PI

    law* Esub6 = ACIS_NEW pi_law();               // PI
    law* Esub5 = ACIS_NEW constant_law(1.25);     // 1.25
    Esub1[1] = ACIS_NEW times_law(Esub5, Esub6);  // 1.25*PI

    law* Esub2[3];
    Esub2[2] = ACIS_NEW constant_law(0);       // 0
    law* Esub4 = ACIS_NEW identity_law(0);     // T
    Esub2[1] = ACIS_NEW sin_law(Esub4);        // SIN(T);
    law* Esub3 = ACIS_NEW identity_law(0);     // T
    Esub2[0] = ACIS_NEW cos_law(Esub3);        // COS(T);
    Esub1[0] = ACIS_NEW vector_law(Esub2, 3);  // VEC(COS(T),SIN(T),0.5)

    law* fifth_circular_vector_law = ACIS_NEW domain_law(Esub1, 3);

    // clean up
    Esub1[0]->remove();
    Esub1[1]->remove();
    Esub1[2]->remove();
    Esub2[0]->remove();
    Esub2[1]->remove();
    Esub2[2]->remove();
    Esub3->remove();
    Esub4->remove();
    Esub5->remove();
    Esub6->remove();
    Esub7->remove();
    Esub8->remove();

    // Sections:

    // A section is an object of type Loft_Connected_Coedge_List and is
    // associated with a lofting profile.
    // It contains information about
    //     - the number of coedges in the profile:         int
    //     - the coedges:                                  COEDGE **
    //     - the coedge orientation:                       FORWARD or REVERSE
    //     - the tangent factor:                           double
    //     - the laws that are to be used on the coedges:  law **

    // First we need to define an array of sections that holds as many
    // sections as there are profiles:
    Loft_Connected_Coedge_List* sections = ACIS_NEW Loft_Connected_Coedge_List[2];

    // Next we need to get the profile coedges:
    ENTITY_LIST circle_entlist;
    ENTITY_LIST square_entlist;
    check_outcome(api_get_coedges(circle, circle_entlist));
    check_outcome(api_get_coedges(square, square_entlist));

    // and convert the resulting ENTITY_LIST into a list of COEDGES:
    COEDGE* circle_coedges[1];
    COEDGE* square_coedges[4];
    circle_coedges[0] = (COEDGE*)circle_entlist[0];
    square_coedges[0] = (COEDGE*)square_entlist[0];
    square_coedges[1] = (COEDGE*)square_entlist[1];
    square_coedges[2] = (COEDGE*)square_entlist[2];
    square_coedges[3] = (COEDGE*)square_entlist[3];

    // We want to loft with laws, so:

    // We add the circular SPAvector law to the circle section:
    law* circle_law_list[1];
    circle_law_list[0] = circular_vector_law;

    // and more circular SPAvector laws to square section:

    // Remark: it helps to look at start and end point and sense of each coedge
    // to determine where the laws should go. Also note that the SPAparameter ranges
    // of the law and the coedge have to be the same.
    law* square_law_list[4];
    square_law_list[0] = fifth_circular_vector_law;
    square_law_list[1] = second_circular_vector_law;
    square_law_list[2] = third_circular_vector_law;
    square_law_list[3] = fourth_circular_vector_law;

    // Now we can make the sections:

    // section for circle:
    sections[0].n_list = 1;
    sections[0].coedge_list = circle_coedges;
    sections[0].coedge_orient = FORWARD;
    sections[0].cross_tg_attr = 10.0;
    sections[0].law_list = circle_law_list;

    // section for square:
    sections[1].n_list = 4;
    sections[1].coedge_list = square_coedges;
    sections[1].coedge_orient = FORWARD;
    sections[1].cross_tg_attr = 10.0;
    sections[1].law_list = square_law_list;

    skin_options opts;

    // We make the body:
    check_outcome(api_loft_coedges(2, sections, skin_bad_square_egg, &opts, ptrAcisOpt));
    check_outcome(api_body_to_2d(skin_bad_square_egg));

    // Clean-up:
    circular_vector_law->remove();
    second_circular_vector_law->remove();
    third_circular_vector_law->remove();
    fourth_circular_vector_law->remove();
    fifth_circular_vector_law->remove();
    ACIS_DELETE[] sections;
    api_del_entity(circle);
    api_del_entity(square);

    API_END

    if(result.ok()) output_ents.add(skin_bad_square_egg);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_good_square_egg: lofting with laws and estimating tangent factors
//
// APIs:
//	  api_create_li,api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_breakup_wires_sli,api_build_body_sli,api_delete_sli,
//    api_estimate_tangent_factor_scale_li,api_set_tangent_factors_li
//
// Description:
//	  Demonstrates tangent factor estimation. This test is to be compared to
//    the test skin_bad_square_egg where the tangent factors have not been optimized.
// **********************************************************************************

outcome aei_SKIN_GOOD_SQUARE_EGG(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_good_square_egg = NULL;

    // API Call Block
    API_BEGIN

    EXCEPTION_BEGIN

    BODY* circle = NULL;
    BODY* square = NULL;
    law* circular_vector_law = NULL;
    law* second_circular_vector_law = NULL;
    law* third_circular_vector_law = NULL;
    law* fourth_circular_vector_law = NULL;
    law* fifth_circular_vector_law = NULL;
    skin_options opts;
    Loft_Connected_Coedge_List* sections = NULL;

    EXCEPTION_TRY

    // circle
    const SPAposition center(0.0, 0.0, 0.0);
    EDGE* circle1_edge[1];
    check_outcome(api_curve_arc(center, .1, 0.0, 2 * M_PI, circle1_edge[0]));
    check_outcome(api_transform_entity((ENTITY*)circle1_edge[0], move_along_z(10.0)));

    // Now we make the edges into wire-bodies:
    check_outcome(api_make_ewire(1, circle1_edge, circle));

    // square: wire-body
    double t = M_PI / 4.0;
    SPAposition q[5];

    q[0].set_x(t);
    q[0].set_y(t);
    q[0].set_z(0.0);

    q[1].set_x(-t);
    q[1].set_y(t);
    q[1].set_z(0.0);

    q[2].set_x(-t);
    q[2].set_y(-t);
    q[2].set_z(0.0);

    q[3].set_x(t);
    q[3].set_y(-t);
    q[3].set_z(0.0);

    q[4].set_x(t);
    q[4].set_y(t);
    q[4].set_z(0.0);

    check_outcome(api_make_wire(NULL, 5, q, square));

    // Skinning operation:
    // Laws:
    // <>?<>?
    // A circular SPAvector law for the circle:
    // DOMAIN(VEC(COS(T),SIN(T),0),0,2*PI)

    EXCEPTION_BEGIN

    law* Asub1[3];
    law* Asub2[3];
    law* Asub3 = NULL;
    law* Asub4 = NULL;
    law* Asub5 = NULL;
    law* Asub6 = NULL;

    EXCEPTION_TRY
    Asub6 = ACIS_NEW pi_law();                    // PI
    Asub5 = ACIS_NEW constant_law(2);             // 2
    Asub1[1] = ACIS_NEW constant_law(0);          // 0
    Asub1[2] = ACIS_NEW times_law(Asub5, Asub6);  // 2*PI

    Asub2[2] = ACIS_NEW constant_law(0);       // 0
    Asub4 = ACIS_NEW identity_law(0);          // T
    Asub2[1] = ACIS_NEW sin_law(Asub4);        // SIN(T);
    Asub3 = ACIS_NEW identity_law(0);          // T
    Asub2[0] = ACIS_NEW cos_law(Asub3);        // COS(T);
    Asub1[0] = ACIS_NEW vector_law(Asub2, 3);  // VEC(COS(T),SIN(T),0)

    circular_vector_law = ACIS_NEW domain_law(Asub1, 3);

    EXCEPTION_CATCH_TRUE

    // clean up
    Asub1[0]->remove();
    Asub1[1]->remove();
    Asub1[2]->remove();
    Asub2[0]->remove();
    Asub2[1]->remove();
    Asub2[2]->remove();
    Asub3->remove();
    Asub4->remove();
    Asub5->remove();
    Asub6->remove();

    EXCEPTION_END

    // A second circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),-PI/4,PI/4)
    EXCEPTION_BEGIN

    law* Bsub1[3];
    law* Bsub2[3];
    law* Bsub3 = NULL;
    law* Bsub4 = NULL;
    law* Bsub5 = NULL;
    law* Bsub6 = NULL;
    law* Bsub7 = NULL;
    law* Bsub8 = NULL;
    law* Bsub9 = NULL;

    EXCEPTION_TRY

    Bsub9 = ACIS_NEW pi_law();                    // PI
    Bsub8 = ACIS_NEW constant_law(0.25);          // .25
    Bsub1[2] = ACIS_NEW times_law(Bsub8, Bsub9);  // 0.25*PI

    Bsub7 = ACIS_NEW pi_law();                    // PI
    Bsub6 = ACIS_NEW constant_law(0.25);          // .25
    Bsub5 = ACIS_NEW negate_law(Bsub6);           // -
    Bsub1[1] = ACIS_NEW times_law(Bsub5, Bsub7);  // -0.25*PI

    Bsub2[2] = ACIS_NEW constant_law(0);       // 0
    Bsub4 = ACIS_NEW identity_law(0);          // T
    Bsub2[1] = ACIS_NEW sin_law(Bsub4);        // SIN(T);
    Bsub3 = ACIS_NEW identity_law(0);          // T
    Bsub2[0] = ACIS_NEW cos_law(Bsub3);        // COS(T);
    Bsub1[0] = ACIS_NEW vector_law(Bsub2, 3);  // VEC(COS(T),SIN(T),0.5)

    second_circular_vector_law = ACIS_NEW domain_law(Bsub1, 3);

    EXCEPTION_CATCH_TRUE
    // clean up
    Bsub1[0]->remove();
    Bsub1[1]->remove();
    Bsub1[2]->remove();
    Bsub2[0]->remove();
    Bsub2[1]->remove();
    Bsub2[2]->remove();
    Bsub3->remove();
    Bsub4->remove();
    Bsub5->remove();
    Bsub6->remove();
    Bsub7->remove();
    Bsub8->remove();
    Bsub9->remove();

    EXCEPTION_END

    // A third circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),PI/4,3/4*PI)

    EXCEPTION_BEGIN

    law* Csub1[3];
    law* Csub2[3];
    law* Csub3 = NULL;
    law* Csub4 = NULL;
    law* Csub5 = NULL;
    law* Csub6 = NULL;
    law* Csub7 = NULL;
    law* Csub8 = NULL;

    EXCEPTION_TRY

    Csub8 = ACIS_NEW pi_law();                    // PI
    Csub7 = ACIS_NEW constant_law(0.75);          // .75
    Csub1[2] = ACIS_NEW times_law(Csub7, Csub8);  // 0.75*PI

    Csub6 = ACIS_NEW pi_law();                    // PI
    Csub5 = ACIS_NEW constant_law(0.25);          // .25
    Csub1[1] = ACIS_NEW times_law(Csub5, Csub6);  // 0.25*PI

    Csub2[2] = ACIS_NEW constant_law(0);       // 0
    Csub4 = ACIS_NEW identity_law(0);          // T
    Csub2[1] = ACIS_NEW sin_law(Csub4);        // SIN(T);
    Csub3 = ACIS_NEW identity_law(0);          // T
    Csub2[0] = ACIS_NEW cos_law(Csub3);        // COS(T);
    Csub1[0] = ACIS_NEW vector_law(Csub2, 3);  // VEC(COS(T),SIN(T),0.5)

    third_circular_vector_law = ACIS_NEW domain_law(Csub1, 3);

    EXCEPTION_CATCH_TRUE

    // clean up
    Csub1[0]->remove();
    Csub1[1]->remove();
    Csub1[2]->remove();
    Csub2[0]->remove();
    Csub2[1]->remove();
    Csub2[2]->remove();
    Csub3->remove();
    Csub4->remove();
    Csub5->remove();
    Csub6->remove();
    Csub7->remove();
    Csub8->remove();

    EXCEPTION_END

    // A fourth circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),3/4*PI,5/4*PI)
    EXCEPTION_BEGIN

    law* Dsub1[3];
    law* Dsub2[3];
    law* Dsub3 = NULL;
    law* Dsub4 = NULL;
    law* Dsub5 = NULL;
    law* Dsub6 = NULL;
    law* Dsub7 = NULL;
    law* Dsub8 = NULL;

    EXCEPTION_TRY

    Dsub8 = ACIS_NEW pi_law();                    // PI
    Dsub7 = ACIS_NEW constant_law(1.25);          // 1.25
    Dsub1[2] = ACIS_NEW times_law(Dsub7, Dsub8);  // 1.25*PI

    Dsub6 = ACIS_NEW pi_law();                    // PI
    Dsub5 = ACIS_NEW constant_law(0.75);          // 0.75
    Dsub1[1] = ACIS_NEW times_law(Dsub5, Dsub6);  // 0.75*PI

    Dsub2[2] = ACIS_NEW constant_law(0);       // 0
    Dsub4 = ACIS_NEW identity_law(0);          // T
    Dsub2[1] = ACIS_NEW sin_law(Dsub4);        // SIN(T);
    Dsub3 = ACIS_NEW identity_law(0);          // T
    Dsub2[0] = ACIS_NEW cos_law(Dsub3);        // COS(T);
    Dsub1[0] = ACIS_NEW vector_law(Dsub2, 3);  // VEC(COS(T),SIN(T),0.5)

    fourth_circular_vector_law = ACIS_NEW domain_law(Dsub1, 3);

    EXCEPTION_CATCH_TRUE

    // clean up
    Dsub1[0]->remove();
    Dsub1[1]->remove();
    Dsub1[2]->remove();
    Dsub2[0]->remove();
    Dsub2[1]->remove();
    Dsub2[2]->remove();
    Dsub3->remove();
    Dsub4->remove();
    Dsub5->remove();
    Dsub6->remove();
    Dsub7->remove();
    Dsub8->remove();

    EXCEPTION_END

    // A fifth circular SPAvector law:
    // DOMAIN(VEC(COS(T),SIN(T),0),5/4*PI,7/4*PI)

    EXCEPTION_BEGIN

    law* Esub1[3];
    law* Esub2[3];
    law* Esub3 = NULL;
    law* Esub4 = NULL;
    law* Esub5 = NULL;
    law* Esub6 = NULL;
    law* Esub7 = NULL;
    law* Esub8 = NULL;

    EXCEPTION_TRY

    Esub8 = ACIS_NEW pi_law();                    // PI
    Esub7 = ACIS_NEW constant_law(1.75);          // 1.75
    Esub1[2] = ACIS_NEW times_law(Esub7, Esub8);  // 1.75*PI

    Esub6 = ACIS_NEW pi_law();                    // PI
    Esub5 = ACIS_NEW constant_law(1.25);          // 1.25
    Esub1[1] = ACIS_NEW times_law(Esub5, Esub6);  // 1.25*PI

    Esub2[2] = ACIS_NEW constant_law(0);       // 0
    Esub4 = ACIS_NEW identity_law(0);          // T
    Esub2[1] = ACIS_NEW sin_law(Esub4);        // SIN(T);
    Esub3 = ACIS_NEW identity_law(0);          // T
    Esub2[0] = ACIS_NEW cos_law(Esub3);        // COS(T);
    Esub1[0] = ACIS_NEW vector_law(Esub2, 3);  // VEC(COS(T),SIN(T),0.5)

    fifth_circular_vector_law = ACIS_NEW domain_law(Esub1, 3);

    EXCEPTION_CATCH_TRUE

    // clean up
    Esub1[0]->remove();
    Esub1[1]->remove();
    Esub1[2]->remove();
    Esub2[0]->remove();
    Esub2[1]->remove();
    Esub2[2]->remove();
    Esub3->remove();
    Esub4->remove();
    Esub5->remove();
    Esub6->remove();
    Esub7->remove();
    Esub8->remove();

    EXCEPTION_END

    //-----------------------------------------------------------------------
    // Sections:

    // A section is an object of type Loft_Connected_Coedge_List and is
    // associated with a lofting profile.
    // It contains information about
    //     - the number of coedges in the profile:         int
    //     - the coedges:                                  COEDGE **
    //     - the coedge orientation:                       FORWARD or REVERSE
    //     - the tangent factor:                           double
    //     - the laws that are to be used on the coedges:  law **

    // First we need to define an array of sections that holds as many
    // sections as there are profiles:
    sections = ACIS_NEW Loft_Connected_Coedge_List[2];

    // Next we need to get the profile coedges:
    ENTITY_LIST circle_entlist;
    ENTITY_LIST square_entlist;
    check_outcome(api_get_coedges(circle, circle_entlist));
    check_outcome(api_get_coedges(square, square_entlist));

    // and convert the resulting ENTITY_LIST into a list of COEDGES:
    COEDGE* circle_coedges[1];
    COEDGE* square_coedges[4];
    circle_coedges[0] = (COEDGE*)circle_entlist[0];
    square_coedges[0] = (COEDGE*)square_entlist[0];
    square_coedges[1] = (COEDGE*)square_entlist[1];
    square_coedges[2] = (COEDGE*)square_entlist[2];
    square_coedges[3] = (COEDGE*)square_entlist[3];

    // We want to loft with laws, so:

    // We add the circular SPAvector law to the circle section:
    law* circle_law_list[1];
    circle_law_list[0] = circular_vector_law;

    // and more circular SPAvector laws to square section:

    // Remark: it helps to look at start and end point and sense of each coedge
    // to determine where the laws should go. Also note that the SPAparameter ranges
    // of the law and the coedge have to be the same.
    law* square_law_list[4];
    square_law_list[0] = fifth_circular_vector_law;
    square_law_list[1] = second_circular_vector_law;
    square_law_list[2] = third_circular_vector_law;
    square_law_list[3] = fourth_circular_vector_law;

    // Now we can make the sections:

    // section for circle:
    sections[0].n_list = 1;
    sections[0].coedge_list = circle_coedges;
    sections[0].coedge_orient = FORWARD;
    sections[0].cross_tg_attr = 1.0;
    sections[0].law_list = circle_law_list;

    // section for square:
    sections[1].n_list = 4;
    sections[1].coedge_list = square_coedges;
    sections[1].coedge_orient = FORWARD;
    sections[1].cross_tg_attr = 1.0;
    sections[1].law_list = square_law_list;

    // We loft the square and the circle using the loftomg interface:

    // We declare an interface object:
    AcisLoftingInterface* the_interface = NULL;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We build the interface:
    check_outcome(api_create_li(2, sections, the_interface, wire_bodies, &opts, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli((AcisSLInterface*)the_interface, 0, 1, ptrAcisOpt));

    // Tangent factor estimation:
    SPAinterval range;
    double optimum = 0.0;
    check_outcome(api_estimate_tangent_factor_scale_li(the_interface, range, optimum, SpaAcis::NullObj::get_double(), ptrAcisOpt));

    // Redo the tangent factors
    double new_factors[2];
    new_factors[0] = sections[0].cross_tg_attr * optimum;
    new_factors[1] = sections[1].cross_tg_attr * optimum;

    check_outcome(api_set_tangent_factors_li(the_interface, new_factors, ptrAcisOpt));

    // We make the body:
    check_outcome(api_build_body_sli((AcisSLInterface*)the_interface, skin_good_square_egg, ptrAcisOpt));
    check_outcome(api_body_to_2d(skin_good_square_egg));

    // Clean-up:
    check_outcome(api_delete_sli((AcisSLInterface*)the_interface, ptrAcisOpt));

    EXCEPTION_CATCH_TRUE
    if(circular_vector_law) circular_vector_law->remove();

    if(second_circular_vector_law) second_circular_vector_law->remove();

    if(third_circular_vector_law) third_circular_vector_law->remove();

    if(fourth_circular_vector_law) fourth_circular_vector_law->remove();

    if(fifth_circular_vector_law) fifth_circular_vector_law->remove();
    if(circle) {
        api_del_entity(circle);
        circle = NULL;
    }
    if(square) {
        api_del_entity(square);
        square = NULL;
    }
    if(sections) {
        ACIS_DELETE[] sections;
        sections = NULL;
    }
    EXCEPTION_END

    API_END

    if(result.ok()) output_ents.add(skin_good_square_egg);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_dented_doughnut: closed skin with guide curve
//
// APIs:
//	  api_create_li, api_align_wires_sli,api_minimize_twist_wires_sli,
//    api_breakup_wires_sli, api_build_body_sli,api_delete_sli
//
// Description:
//	  Demonstrates using the skinning interface to create a closed skin with
//    guide curve where the virtualGuide option is set to TRUE.
// **********************************************************************************

outcome aei_SKIN_DENTED_DOUGHNUT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_dented_doughnut = NULL;

    // API Call Block
    API_BEGIN

    // wire0
    SPAposition p0[5];

    p0[0].set_x(10.0);
    p0[0].set_y(0.0);
    p0[0].set_z(0.0);

    p0[1].set_x(20.0);
    p0[1].set_y(0.0);
    p0[1].set_z(0.0);

    p0[2].set_x(20.0);
    p0[2].set_y(10.0);
    p0[2].set_z(0.0);

    p0[3].set_x(10.0);
    p0[3].set_y(10.0);
    p0[3].set_z(0.0);

    p0[4].set_x(10.0);
    p0[4].set_y(0.0);
    p0[4].set_z(0.0);

    BODY* wire0 = NULL;
    check_outcome(api_make_wire(NULL, 5, p0, wire0));

    // wire1
    SPAposition p1[5];

    p1[0].set_x(0.0);
    p1[0].set_y(0.0);
    p1[0].set_z(10.0);

    p1[1].set_x(0.0);
    p1[1].set_y(0.0);
    p1[1].set_z(20.0);

    p1[2].set_x(0.0);
    p1[2].set_y(10.0);
    p1[2].set_z(20.0);

    p1[3].set_x(0.0);
    p1[3].set_y(10.0);
    p1[3].set_z(10.0);

    p1[4].set_x(0.0);
    p1[4].set_y(0.0);
    p1[4].set_z(10.0);

    BODY* wire1 = NULL;
    check_outcome(api_make_wire(NULL, 5, p1, wire1));

    // wire2
    SPAposition p2[5];

    p2[0].set_x(-10.0);
    p2[0].set_y(0.0);
    p2[0].set_z(0.0);

    p2[1].set_x(-20.0);
    p2[1].set_y(0.0);
    p2[1].set_z(0.0);

    p2[2].set_x(-20.0);
    p2[2].set_y(10.0);
    p2[2].set_z(0.0);

    p2[3].set_x(-10.0);
    p2[3].set_y(10.0);
    p2[3].set_z(0.0);

    p2[4].set_x(-10.0);
    p2[4].set_y(0.0);
    p2[4].set_z(0.0);

    BODY* wire2 = NULL;
    check_outcome(api_make_wire(NULL, 5, p2, wire2));

    // wire3
    SPAposition p3[5];

    p3[0].set_x(0.0);
    p3[0].set_y(0.0);
    p3[0].set_z(-10.0);

    p3[1].set_x(0.0);
    p3[1].set_y(0.0);
    p3[1].set_z(-20.0);

    p3[2].set_x(0.0);
    p3[2].set_y(10.0);
    p3[2].set_z(-20.0);

    p3[3].set_x(0.0);
    p3[3].set_y(10.0);
    p3[3].set_z(-10.0);

    p3[4].set_x(0.0);
    p3[4].set_y(0.0);
    p3[4].set_z(-10.0);

    BODY* wire3 = NULL;
    check_outcome(api_make_wire(NULL, 5, p3, wire3));

    // guide
    SPAposition p[9];

    p[0].set_x(15.0);
    p[0].set_y(10.0);
    p[0].set_z(0.0);

    p[1].set_x(7.0);
    p[1].set_y(5.0);
    p[1].set_z(7.0);

    p[2].set_x(0.0);
    p[2].set_y(10.0);
    p[2].set_z(15.0);

    p[3].set_x(-7.0);
    p[3].set_y(5.0);
    p[3].set_z(7.0);

    p[4].set_x(-15.0);
    p[4].set_y(10.0);
    p[4].set_z(0.0);

    p[5].set_x(-7.0);
    p[5].set_y(5.0);
    p[5].set_z(-7.0);

    p[6].set_x(0.0);
    p[6].set_y(10.0);
    p[6].set_z(-15.0);

    p[7].set_x(7.0);
    p[7].set_y(5.0);
    p[7].set_z(-7.0);

    p[8].set_x(15.0);
    p[8].set_y(10.0);
    p[8].set_z(0.0);

    SPAunit_vector start(0, 0, 1);
    SPAunit_vector end(0, 0, 1);

    EDGE* guide = NULL;
    check_outcome(api_curve_spline(9, p, &start, &end, guide));

    // Skinning operation:

    // First we put the profiles into an entity list:
    ENTITY_LIST entities;
    entities.add(wire0);
    entities.add(wire1);
    entities.add(wire2);
    entities.add(wire3);

    // We declare an interface object:
    AcisSkinningInterface* the_interface = NULL;

    // We declare an array of BODY*'s in which wire copies will be returned:
    BODY** wire_bodies = NULL;

    // We set the skinning options:
    skin_options opts;
    opts.set_arc_length(FALSE);
    opts.set_no_twist(TRUE);
    opts.set_align(TRUE);
    opts.set_simplify(FALSE);
    opts.set_closed(FALSE);
    opts.set_solid(TRUE);
    opts.set_virtualGuides(TRUE);

    // We build the interface:
    check_outcome(api_create_si(entities, the_interface, wire_bodies, (BODY*)NULL, &opts, ptrAcisOpt));

    // We add the guide curve:
    check_outcome(api_add_guide_curve_si(the_interface, guide, ptrAcisOpt));

    // We align the wires:
    check_outcome(api_align_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // and minimize the twist of the wires:
    check_outcome(api_minimize_twist_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // We perform a breakup of the wires into equal numbers of coedges:
    check_outcome(api_breakup_wires_sli(the_interface, 0, 3, ptrAcisOpt));

    // We make the body:
    check_outcome(api_build_body_sli(the_interface, skin_dented_doughnut, ptrAcisOpt));

    // Clean-up:
    check_outcome(api_delete_sli(the_interface, ptrAcisOpt));

    api_del_entity_list(entities);
    api_del_entity(guide);

    check_outcome(api_transform_entity((ENTITY*)skin_dented_doughnut, rot_about_y(M_PI / 2.0)));

    API_END

    if(result.ok()) output_ents.add(skin_dented_doughnut);

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  skin_flower: covering a non-planar wire
//
// APIs:
//	  api_cover_wires
//
// Description:
//	  Demonstrates covering of a non-planar wire.
// **********************************************************************************

outcome aei_SKIN_FLOWER(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* skin_flower = NULL;

    // API Call Block
    API_BEGIN

    // flower: wire-body

    // We build flower from 4 equilateral petals:
    BODY* petals[4];

    // First we make petals[0]:
    double L = cos(M_PI / 12.0) / sin(M_PI / 12.0);
    SPAposition points[3];
    points[0].set_x(L);
    points[0].set_y(L);
    points[0].set_z(0.0);
    points[1].set_x(2 * L);
    points[1].set_y(0);
    points[1].set_z(0);
    points[2].set_x(L);
    points[2].set_y(-L);
    points[2].set_z(0.0);

    EDGE* petal[1];
    check_outcome(api_curve_arc_3pt(points[0], points[1], points[2], FALSE, petal[0]));

    BODY* tool_petal1 = NULL;  // for odd numbered petals
    check_outcome(api_make_ewire(1, petal, tool_petal1));
    BODY* tool_petal2 = NULL;  // for even numbered petals
    check_outcome(api_copy_body(tool_petal1, tool_petal2));

    // Bending angles:
    double angle_odd = 1.0;
    double angle_even = 1.0;

    // We bend the tool-petals:

    // tool_petal1
    check_outcome(api_transform_entity((ENTITY*)tool_petal1, move_along_x(-L)));
    check_outcome(api_transform_entity((ENTITY*)tool_petal1, rot_about_y(angle_odd)));
    check_outcome(api_transform_entity((ENTITY*)tool_petal1, move_along_x(L)));

    // tool_petal2
    check_outcome(api_transform_entity((ENTITY*)tool_petal2, move_along_x(-L)));
    check_outcome(api_transform_entity((ENTITY*)tool_petal2, rot_about_y(angle_even)));
    check_outcome(api_transform_entity((ENTITY*)tool_petal2, move_along_x(L)));

    // We make the petals:

    // even numbered petals
    for(int i = 0; i <= 2; i += 2) {
        check_outcome(api_copy_body(tool_petal2, petals[i]));
        check_outcome(api_transform_entity((ENTITY*)petals[i], rot_about_z(i * (M_PI / 2.0))));
    }

    // odd numbered petals
    for(int j = 1; j <= 3; j += 2) {
        check_outcome(api_copy_body(tool_petal1, petals[j]));
        check_outcome(api_transform_entity((ENTITY*)petals[j], rot_about_z(j * (M_PI / 2.0))));
    }
    api_del_entity(tool_petal1);
    api_del_entity(tool_petal2);

    // We unite the petals to obtain a flower:
    BODY* flower_wire_body = petals[0];
    for(int k = 1; k < 4; k++) check_outcome(api_unite(petals[k], flower_wire_body));

    // Skinning operation:

    // We cover the flower
    FACE* flower_face[1];
    WIRE* flower_wire = (flower_wire_body->wire() != NULL) ? flower_wire_body->wire() : flower_wire_body->lump()->shell()->wire();

    check_outcome(api_cover_wire(flower_wire, SpaAcis::NullObj::get_surface(), flower_face[0]));

    // api_cover_wire should already put the cover face into a body if result is OK
    if(flower_face[0] && flower_face[0]->shell() && flower_face[0]->shell()->lump()) skin_flower = flower_face[0]->shell()->lump()->body();

    // We make the resulting face into a body and display it
    if(!skin_flower) check_outcome(api_mk_by_faces(NULL, 1, flower_face, skin_flower));

    check_outcome(api_transform_entity((ENTITY*)skin_flower, rot_about_y(angle_odd)));
    check_outcome(api_body_to_2d(skin_flower));

    API_END

    if(result.ok()) output_ents.add(skin_flower);

    return result;
}
