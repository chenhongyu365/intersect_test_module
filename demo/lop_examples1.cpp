/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "lop_examples1.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/acis_journal.hxx"
#include "acis/add_pcu.hxx"
#include "acis/alltop.hxx"
#include "acis/annotation.hxx"
#include "acis/api.err"
#include "acis/api.hxx"
#include "acis/blendapi.hxx"
#include "acis/blndanno.hxx"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/copyanno.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/efilter.hxx"
#include "acis/geom_utl.hxx"
#include "acis/intrapi.hxx"
#include "acis/kernapi.hxx"
#include "acis/kernopts.hxx"
#include "acis/law.hxx"
#include "acis/lists.hxx"
#include "acis/logical.h"
#include "acis/lop_api.hxx"
#include "acis/lop_opts.hxx"
#include "acis/loptanno.hxx"
#include "acis/option.hxx"
#include "acis/pcudef.hxx"
#include "acis/pcurve.hxx"
#include "acis/pick_ray.hxx"
#include "acis/point.hxx"
#include "acis/position.hxx"
#include "acis/queryapi.hxx"
#include "acis/rem_api.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/roll_utl.hxx"
#include "acis/shl_api.hxx"
#include "acis/splsurf.hxx"
#include "acis/surdef.hxx"
#include "acis/surf_utl.hxx"
#include "acis/surface.hxx"
#include "acis/sweepapi.hxx"
#include "acis/swp_opts.hxx"
#include "acis/trace.hxx"
#include "acis/transf.hxx"
#include "acis/vector.hxx"
#include "acis/wire_utl.hxx"
#include "assert.h"

extern void TrackAnnotations(logical state);

LOCAL_PROC
void delete_ray_params(double* ray_params) {
    if(ray_params) {
        ACIS_DELETE[] STD_CAST ray_params;
        ray_params = NULL;
    }
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Edge Taper Example
//
// APIs:
//	  api_edge_taper_faces
//
// Description:
//	  Demonstrates tapering of faces at supplied edges.
/*
; lop:edge-taper-faces
 ; Create a rotated block
 (define block1 (solid:block (position -5 -5 -5) (position 5 5 5)))
 ;; block1
 (entity:transform block1 (transform:rotation (position 0 0 0) (gvector 1 0 0) 10))
 ;; #[entity 2 1]
 ; OUTPUT Original
 (lop:edge-taper-faces (pick:face (ray (position 0 0 0) (gvector 1 0 0)))
                        (pick:edge (ray (position 5 0 0) (gvector 0 0 -1)))
                        (gvector 0 0 1) 20)
 ;; #[entity 2 1]
 ; OUTPUT result
*/

outcome aei_LOP_EDGE_TAPER_FACES1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    option_header* opts_remove_inv = find_option("rbi_remove_inv_face");
    if(opts_remove_inv) opts_remove_inv->push(TRUE);

    TrackAnnotations(TRUE);
    BODY* block = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());

    const double D = 25.0;

    // Create a block
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, block));

    // transform the block
    SPAvector axis(1.0, 0.0, 0.0);
    SPAtransf rotmat = rotate_transf(degrees_to_radians(10.0), axis);
    check_outcome(api_transform_entity(block, rotmat));

    // taper faces of the block.
    ENTITY_LIST face_list, edge_list;

    // select face to be tapered and the reference for edge taper
    {
        double* ray_params = NULL;
        outcome out = api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, 0.0, 0.0), 0.01, FACE_TYPE, block, face_list, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);
        out = api_get_ents(SPAposition(D, 0.0, 0.0), SPAunit_vector(0.0, 0.0, -1.0), 0.01, EDGE_TYPE, block, edge_list, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);
    }

    FACE* face = (FACE*)face_list.first();
    EDGE* edge = (EDGE*)edge_list.first();
    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);
    SPAunit_vector draft_dir(0.0, 0.0, 1.0);
    double draft_angle = degrees_to_radians(20.0);

    lop_options lopOpts;
    lopOpts.set_repair_self_int(TRUE);

    check_outcome(api_edge_taper_faces(1, &face, &edge, draft_dir, draft_angle, box_l, box_h, &lopOpts, ptrAcisOpt));

    rgb_color Red(1.0, 0.0, 0.0);
    int nFace = face_list.iteration_count();
    for(int i = 0; i < nFace; i++) check_outcome(api_rh_set_entity_rgb(face_list[i], Red));

    API_END

    TrackAnnotations(FALSE);
    api_clear_annotations();
    if(opts_remove_inv) opts_remove_inv->pop();

    if(result.ok()) output_ents.add(block);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Edge Taper Example
//
// APIs:
//	  api_edge_taper_faces
//
// Description:
//    Demonstrates tapering of faces at supplied edges.
/*
 ; Define some entities
 (part:clear)
 ;; #t
 (define block1 (solid:block (position -25 -25 -25) (position 25 25 25)))
 ;; block1
 (define block2 (solid:block (position -50 -50 0) (position 50 50 100)))
 ;; block2
 (solid:imprint block1 block2)
 ;; #t
 (entity:delete block2)
 ;; ()
 (option:set "annotation" #t)
 ;; #f
 (option:set "unhook_annotations" #f)
 ;; #t
 (define e1 (pick:edge (ray (position 0 0 -25) (gvector 1 0 0))))
 ;; e1
 (define f1 (pick:face (ray (position 0 0 -20) (gvector 1 0 0))))
 ;; f1
 (define e2 (pick:edge (ray (position 0 0 -25) (gvector -1 0 0))))
 ;; e2
 (define f2 (pick:face (ray (position 0 0 -20) (gvector -1 0 0))))
 ;; f2
 (define e3 (pick:edge (ray (position 0 0 -25) (gvector 0 1 0))))
 ;; e3
 (define f3 (pick:face (ray (position 0 0 -20) (gvector 0 1 0))))
 ;; f3
 (define e4 (pick:edge (ray (position 0 0 -25) (gvector 0 -1 0))))
 ;; e4
 (define f4 (pick:face (ray (position 0 0 -20) (gvector 0 -1 0))))
 ;; f4
 ; OUTPUT Original
 (lop:edge-taper-faces (list f1 f2 f3 f4) (list e1 e2 e3 e4) (gvector 0 0 1) 20)
 ;; #[entity 24 1]
 ; OUTPUT Result
 ; Render to see the final result.
 (render)
 ;; ()

 ; OUTPUT Rendered
*/

outcome aei_LOP_EDGE_TAPER_FACES2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    option_header* opts_remove_inv = find_option("rbi_remove_inv_face");

    if(opts_remove_inv) opts_remove_inv->push(TRUE);

    TrackAnnotations(TRUE);
    BODY* block = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());

    const double D = 25.0;
    BODY* block2 = NULL;

    // Create a couple of blocks
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, block));
    SPAposition low2(-2.0 * D, -2.0 * D, 0.0);
    SPAposition high2(2.0 * D, 2.0 * D, 4.0 * D);
    check_outcome(api_solid_block(low2, high2, block2));

    // now imprint one block on other..
    check_outcome(api_imprint(block2, block));
    api_del_entity(block2);

    // pick some faces and edges for tapering..
    ENTITY_LIST face_list3, edge_list3;

    {
        double* ray_params = NULL;

        outcome out = api_get_ents(SPAposition(-D - 5.0, 0.0, -D + 5.0), SPAunit_vector(1.0, 0.0, 0.0), 0.01, FACE_TYPE, block, face_list3, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);

        out = api_get_ents(SPAposition(0.0, -D - 5.0, -D + 5.0), SPAunit_vector(0.0, 1.0, 0.0), 0.01, FACE_TYPE, block, face_list3, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);

        out = api_get_ents(SPAposition(-D - 5.0, 0.0, -D), SPAunit_vector(1.0, 0.0, 0.0), 0.01, EDGE_TYPE, block, edge_list3, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);

        out = api_get_ents(SPAposition(0.0, -D - 5.0, -D), SPAunit_vector(0.0, 1.0, 0.0), 0.01, EDGE_TYPE, block, edge_list3, ray_params);

        delete_ray_params(ray_params);

        check_outcome(out);
    }

    rgb_color Red(1.0, 0.0, 0.0);
    std::vector<FACE*> faces;
    {
        for(ENTITY* ent = face_list3.first(); ent; ent = face_list3.next()) {
            faces.push_back((FACE*)ent);
            ;
            check_outcome(api_rh_set_entity_rgb(ent, Red));
        }
    }

    std::vector<EDGE*> edges;
    {
        for(ENTITY* ent = edge_list3.first(); ent; ent = edge_list3.next()) {
            edges.push_back((EDGE*)ent);
            ;
            check_outcome(api_rh_set_entity_rgb(ent, Red));
        }
    }

    SPAunit_vector draft_dir(0.0, 0.0, 1.0);
    double draft_ang = degrees_to_radians(20.0);
    lop_options lopOpts;
    lopOpts.set_repair_self_int(TRUE);
    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);

    check_outcome(api_edge_taper_faces((int)faces.size(), faces.data(), edges.data(), draft_dir, draft_ang, box_l, box_h, &lopOpts, ptrAcisOpt));

    API_END
    TrackAnnotations(FALSE);
    api_clear_annotations();

    if(opts_remove_inv) opts_remove_inv->pop();

    if(result.ok()) output_ents.add(block);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Plane taper example
//
// APIs:
//	  api_taper_faces
//
// Description:
//	  Demonstrates tapering of faces with respect to the given plane by a given draft angle.
/*
 ; lop:taper-faces
 ; Create a solid block.
 (define block1 (solid:block (position -30 -5 -10) (position 20 20 10)))
 ;; block1
 ; OUTPUT Original
 ; Taper a face on the body
 (lop:taper-faces (pick:face (ray (position 0 0 0) (gvector 0 0 1))) (position 0 0 0) (gvector 10 20 10) 10)
 ;; #[entity 2 1]
 ; OUTPUT Result


; Example 2
 ; Clear the screen to prepare for the next example.
 (part:clear)
 ;; #t
 (define block2 (solid:block (position -25 -25 -10) (position 25 25 10)))
 ;; block2
 (solid:blend-edges (pick:edge (ray (position 0 0 0) (gvector 1 -1 0))) 20)
 ;; (#[entity 4 1])
 ; OUTPUT Original
 (lop:taper-faces (list (pick:face (ray (position 0 0 0) (gvector 1 0 0)))
                        (pick:face (ray (position 0 0 0) (gvector 0 -1 0)))
                        (pick:face (ray (position 0 0 0) (gvector 1 -1 0))))
                        (position 0 0 -10) (gvector 0 0 1) 45)
 ;; #[entity 4 1]
 ; OUTPUT Result
*/

outcome aei_LOP_PLANE_TAPER_FACES(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    option_header* opts_remove_inv = find_option("rbi_remove_inv_face");

    if(opts_remove_inv) opts_remove_inv->push(TRUE);

    TrackAnnotations(TRUE);
    BODY* block = NULL;
    TrackAnnotations(TRUE);

    API_BEGIN

    lop_options lopOpts;
    lopOpts.set_repair_self_int(TRUE);

    check_outcome(api_clear_annotations());

    const double D = 25.0;
    SPAposition low(-D, -D, -10.0);
    SPAposition high(D, D, 10.0);
    check_outcome(api_solid_block(low, high, block));

    FACE* face[3];
    {
        ENTITY_LIST face_list, edge_list;
        double* ray_params = NULL;
        double radius = 20.0;
        outcome out = api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, -1.0, 0.0), 0.01, EDGE_TYPE, block, edge_list, ray_params);

        delete_ray_params(ray_params);

        ray_params = NULL;
        check_outcome(out);
        check_outcome(api_blend_edges(edge_list, radius));

        // face #1
        out = api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, 0.0, 0.0), 0.01, FACE_TYPE, block, face_list, ray_params);

        delete_ray_params(ray_params);

        ray_params = NULL;
        check_outcome(out);
        face[0] = (FACE*)face_list.first();
        face_list.clear();

        // face #2
        out = api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(0.0, -1.0, 0.0), 0.01, FACE_TYPE, block, face_list, ray_params);

        delete_ray_params(ray_params);

        ray_params = NULL;
        check_outcome(out);
        face[1] = (FACE*)face_list.first();
        face_list.clear();

        // face #3
        out = api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, -1.0, 0.0), 0.01, FACE_TYPE, block, face_list, ray_params);

        delete_ray_params(ray_params);

        ray_params = NULL;
        check_outcome(out);
        face[2] = (FACE*)face_list.first();
    }

    rgb_color Red(1.0, 0.0, 0.0);
    for(int i = 0; i < 3; i++) {
        check_outcome(api_rh_set_entity_rgb(face[i], Red));
    }

    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);
    SPAposition pos(0.0, 0.0, -10.0);
    SPAunit_vector normal(0.0, 0.0, 1.0);
    double draft_angle = degrees_to_radians(45.0);

    // vent_type_id  vent_type=vent_type_add;
    check_outcome(api_taper_faces(3, face, pos, normal, draft_angle, box_l, box_h, &lopOpts, ptrAcisOpt));

    API_END

    TrackAnnotations(FALSE);
    api_clear_annotations();

    if(opts_remove_inv) opts_remove_inv->pop();

    if(result.ok()) output_ents.add(block);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Move faces - Translation
//
// APIs:
//	  api_move_faces
//
// Description:
//	  Demonstrates the moving of an array of faces through a translation transform.
/*
; lop:move-faces
 ; Create a solid block.
 (define block1 (solid:block (position -20 -20 -20) (position 20 20 20)))
 ;; block1
 ; OUTPUT Original
 ; List the faces of the block
 (entity:faces block1)
 ;; (#[entity 3 1] #[entity 4 1] #[entity 5 1]
 ;; #[entity 6 1] #[entity 7 1] #[entity 8 1])
 ; Move a face on the body
 (lop:move-faces (entity 4) (gvector 10 10 20))
 ;; #[entity 2 1]
 ; OUTPUT Result
*/

outcome aei_LOP_MOVE_FACES_TRANSLATE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* block = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());
    TrackAnnotations(TRUE);

    // Create a block
    double D = 25.0;
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, block));

    // move faces on the block
    ENTITY_LIST face_list;

    // Select the face to be translated
    check_outcome(api_get_faces(block, face_list));
    FACE* face = (FACE*)face_list[2];

    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(face, Red));

    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);
    SPAvector disp(D / 2.0, D, D);
    SPAtransf translation = translate_transf(disp);
    check_outcome(api_move_faces(1, &face, translation, box_l, box_h, NULL, ptrAcisOpt));

    TrackAnnotations(FALSE);
    check_outcome(api_clear_annotations());

    API_END

    if(result.ok()) output_ents.add(block);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Body Offset - negative offset on block with blends
//
// APIs:
//	  api_offset_body
//
// Description:
//	  Demonstrates offsetting of all faces of a body for the given distance.
/*
 ; Example 2
 ; Clear the previous part
 (part:clear)
 ;; #t
 (define block2 (solid:block (position -25 -25 -25) (position 25 25 25)))
 ;; block2
 (define edge1 (blend:const-rad-on-edge (pick:edge (ray (position 0 0 0) (gvector 1 -1 0))) 10))
 ;; edge1
 (define edge2 (blend:const-rad-on-edge (pick:edge (ray (position 0 0 0) (gvector 1 0 1))) 15))
 ;; edge2
 (define edge3 (blend:const-rad-on-edge (pick:edge (ray (position 0 0 0) (gvector 0 -1 1))) 20))
 ;; edge3
 (define vertex1 (blend:on-vertex (pick:vertex (ray (position 0 0 0) (gvector 1 -1 1))) 20))
 ;; vertex1
 (blend:network (list edge1 edge2 edge3 vertex1))
 ;; #[entity 3 1]
 ; OUTPUT Original
 (lop:offset-body block2 -10)
 ;; #[entity 3 1]
 ; OUTPUT Result
*/

outcome aei_LOP_OFFSET_BODY_NEGOFST(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());
    TrackAnnotations(TRUE);

    // Create a block
    const double D = 25.0;
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, body));

    ENTITY_LIST all_list, edge_list;
    double* ray_params = NULL;

    // top horizontal edge - || y axis
    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, -1.0, 0.0), 0.01, EDGE_TYPE, body, edge_list, ray_params));

    delete_ray_params(ray_params);

    check_outcome(api_set_const_rounds(edge_list, D / 5.0 /*rad*/));
    all_list.add(edge_list[0]);

    // vertical edge
    edge_list.clear();
    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, 0.0, 1.0), 0.01, EDGE_TYPE, body, edge_list, ray_params));

    delete_ray_params(ray_params);

    check_outcome(api_set_const_rounds(edge_list, D / 3.5 /*rad*/));
    all_list.add(edge_list[0]);

    // top horizontal edge - || x axis
    edge_list.clear();
    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(0.0, -1.0, 1.0), 0.01, EDGE_TYPE, body, edge_list, ray_params));

    delete_ray_params(ray_params);

    check_outcome(api_set_const_rounds(edge_list, D / 2.5 /*rad*/));
    all_list.add(edge_list[0]);

    // select the common vertex..
    ENTITY_LIST vert_list;
    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(1.0, -1.0, 1.0), 0.01, VERTEX_TYPE, body, vert_list, ray_params));

    delete_ray_params(ray_params);

    check_outcome(api_set_vblend_auto((VERTEX*)vert_list[0], 1.0 /*bulge factor*/));
    all_list.add(vert_list[0]);

    // apply the blend..
    check_outcome(api_fix_blends(all_list));

    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);

    // Perform offsetting of the entire body
    check_outcome(api_offset_body(body, -D / 4.0, box_l, box_h, NULL, ptrAcisOpt));
    TrackAnnotations(FALSE);
    check_outcome(api_clear_annotations());

    API_END

    if(result.ok()) output_ents.add(body);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Face Offsetting
//
// APIs:
//	  api_offset_faces
//
// Description:
//	  Demonstrates the Offsetting of an array of faces based on a given distance.
/*
 ; lop:offset-faces
 ; Create a solid block.
 (define block1 (solid:block (position -10 -10 -20) (position 5 30 20)))
 ;; block1
 ; OUTPUT Original
 ; Offset a face on the body
 (lop:offset-faces (pick:face (ray (position 0 0 0) (gvector 0 0 1))) 10)
 ;; #[entity 2 1]
 ; OUTPUT Result
*/
outcome aei_LOP_OFFSET_FACES(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());
    TrackAnnotations(TRUE);

    // Create a block
    double D = 25.0;
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, body));

    // pick a face for offsetting..
    ENTITY_LIST face_list;
    double* ray_params = NULL;
    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(0.0, 0.0, 1), 0.01, FACE_TYPE, body, face_list, ray_params));

    delete_ray_params(ray_params);

    // offset the face.
    FACE* face = (FACE*)face_list[0];

    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(face, Red));

    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);
    double offset_dist = D / 2;
    check_outcome(api_offset_faces(1, &face, offset_dist, box_l, box_h, NULL, ptrAcisOpt));

    TrackAnnotations(FALSE);
    check_outcome(api_clear_annotations());

    API_END

    if(result.ok()) output_ents.add(body);

    return result;
}

/***********************************************************************************************/
// C++ Example:
//
// Title:
//	  Move faces - Rotation
//
// APIs:
//	  api_move_faces
//
// Description:
//	  Demonstrates the moving of an array of faces through a rotation transform.
/*
; lop:rotate-faces
 ; Create a solid block.
 (define block1 (solid:block (position -20 -20 -20) (position 20 20 20)))
 ;; block1
 ; OUTPUT Original
 ; Rotate a face on the body
 (lop:rotate-faces (pick:face (ray (position 0 0 0) (gvector 0 0 1))) (position 0 0 0) (gvector 10 20 10) 10)
 ;; #[entity 2 1]
 ; OUTPUT Result
*/

outcome aei_LOP_MOVE_FACES_ROTATE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;

    API_BEGIN

    check_outcome(api_clear_annotations());
    TrackAnnotations(TRUE);

    // Create a block
    double D = 25.0;
    SPAposition low(-D, -D, -D);
    SPAposition high(D, D, D);
    check_outcome(api_solid_block(low, high, body));

    ENTITY_LIST face_list;
    FACE* face = NULL;
    double* ray_params = NULL;

    check_outcome(api_get_ents(SPAposition(0.0, 0.0, 0.0), SPAunit_vector(0.0, 0.0, 1.0), 0.01, FACE_TYPE, body, face_list, ray_params));
    face = (FACE*)face_list[0];
    face_list.clear();

    delete_ray_params(ray_params);

    rgb_color Red(1.0, 0.0, 0.0);
    check_outcome(api_rh_set_entity_rgb(face, Red));

    double angle = degrees_to_radians(10.0);
    SPAvector axis(10.0, 20.0, 10.0);
    SPAtransf rotation = rotate_transf(angle, axis);
    SPAposition box_l(0.0, 0.0, 0.0);
    SPAposition box_h(0.0, 0.0, 0.0);

    check_outcome(api_move_faces(1, &face, rotation, box_l, box_h, NULL, ptrAcisOpt));

    TrackAnnotations(FALSE);
    check_outcome(api_clear_annotations());

    API_END

    if(result.ok()) output_ents.add(body);

    return result;
}
