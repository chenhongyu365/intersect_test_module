/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include <vector>

#include "acis/acis.hxx"
#include "acis/api.err"  // API_FAILED definition
#include "acis/blendapi.hxx"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/faceutil.hxx"
#include "acis/kernapi.hxx"
#include "acis/mt_stitch_apis.hxx"
#include "acis/mt_stitch_hndl.hxx"
#include "acis/mt_stitch_opts.hxx"
#include "acis/rayfire_opts.hxx"
#include "acis/raytest.hxx"
#include "acis/sur.hxx"
#include "acis/surface.hxx"
#include "acis/thmgr.hxx"
#include "acis/transf.hxx"

// for enabling thread-hot stitching
LOCAL_PROC
int start_thread_func() {
    outcome result = api_start_modeller();
    return result.ok();
}

LOCAL_PROC
int stop_thread_func() {
    outcome result = api_stop_modeller();
    return result.ok();
}

LOCAL_PROC
BODY* make_cylinder(const SPAposition& p0, const SPAposition& p1, const double radius) {
    BODY* cyl = NULL;
    check_outcome(api_solid_cylinder_cone(p0, p1, radius, radius, radius, NULL, cyl));
    return cyl;
}
LOCAL_PROC
BODY* make_block(const SPAposition& p0, const SPAposition& p1) {
    BODY* blk = NULL;
    check_outcome(api_solid_block(p0, p1, blk));
    return blk;
}
LOCAL_PROC
BODY* make_toycar() {
    BODY *blank, *tool, *toycar;

    // chassis
    blank = make_cylinder(SPAposition(0, 0, 0), SPAposition(0, 5, 0), 10);
    tool = make_block(SPAposition(0, -1, -11), SPAposition(11, 6, 11));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    tool = make_block(SPAposition(-10, -1, -11), SPAposition(1, 6, 0));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    tool = make_cylinder(SPAposition(0, 0, 4), SPAposition(0, 5, 4), 6);
    check_outcome(api_boolean(tool, blank, UNION));
    tool = make_cylinder(SPAposition(6, 0, 0), SPAposition(6, 5, 0), 4);
    check_outcome(api_boolean(tool, blank, UNION));
    tool = make_cylinder(SPAposition(-6, 0, 0), SPAposition(-6, 5, 0), 4);
    check_outcome(api_boolean(tool, blank, UNION));
    tool = make_block(SPAposition(-6, 0, -4), SPAposition(6, 5, 0));
    check_outcome(api_boolean(tool, blank, UNION));
    toycar = blank;

    // windows
    blank = make_cylinder(SPAposition(0, -1, 4), SPAposition(0, 6, 4), 5);
    tool = make_block(SPAposition(-6, -2, -6), SPAposition(0, 7, 6));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    BODY* tl = blank;
    blank = make_cylinder(SPAposition(0, -1, 0), SPAposition(0, 6, 0), 9);
    tool = make_block(SPAposition(0, -2, -10), SPAposition(10, 7, 10));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    check_outcome(api_boolean(tl, blank, UNION));
    tool = make_block(SPAposition(-10, -2, -10), SPAposition(10, 7, 4));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    BODY* windows = blank;

    // vehicle -= windows
    check_outcome(api_boolean(windows, toycar, SUBTRACTION));

    // wheels
    blank = make_cylinder(SPAposition(5, -1.5, -3), SPAposition(5, 6.5, -3), 3);
    tool = make_block(SPAposition(-9, -0.3, -7), SPAposition(9, 5.3, 1));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    tool = make_cylinder(SPAposition(5, -1.5, -3), SPAposition(5, 6.5, -3), 0.2);
    check_outcome(api_boolean(tool, blank, UNION));
    BODY* w0 = blank;
    blank = make_cylinder(SPAposition(-5, -1.5, -3), SPAposition(-5, 6.5, -3), 3);
    tool = make_block(SPAposition(-9, -0.3, -7), SPAposition(9, 5.3, 1));
    check_outcome(api_boolean(tool, blank, SUBTRACTION));
    tool = make_cylinder(SPAposition(-5, -1.5, -3), SPAposition(-5, 6.5, -3), 0.2);
    check_outcome(api_boolean(tool, blank, UNION));
    BODY* w1 = blank;

    // vehicle += wheels
    check_outcome(api_boolean(w0, toycar, UNION));
    check_outcome(api_boolean(w1, toycar, UNION));

    // blend vehicle
    std::vector<ray> rays;
    rays.push_back(ray(SPAposition(281.977, 397.282, 119.205), SPAunit_vector(-0.576357, -0.784505, -0.22883), 0.201327, 1));
    rays.push_back(ray(SPAposition(291.603, 390.746, 117.368), SPAunit_vector(-0.576357, -0.784505, -0.22883), 0.201327, 1));
    rays.push_back(ray(SPAposition(-173.381, 418.639, 217.855), SPAunit_vector(0.355981, -0.831359, -0.426755), 0.201327, 1));
    rays.push_back(ray(SPAposition(395.824, 305.58, 18.6618), SPAunit_vector(-0.788527, -0.61395, -0.0359283), 0.201327, 1));
    rays.push_back(ray(SPAposition(396.278, 304.618, 25.1221), SPAunit_vector(-0.788527, -0.61395, -0.0359283), 0.201327, 1));
    rays.push_back(ray(SPAposition(391.915, 310.278, 24.1726), SPAunit_vector(-0.788527, -0.61395, -0.0359283), 0.201327, 1));
    rays.push_back(ray(SPAposition(390.021, 312.648, 25.237), SPAunit_vector(-0.788527, -0.61395, -0.0359283), 0.201327, 1));
    rays.push_back(ray(SPAposition(-25.7967, -0.808737, 503.098), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-28.1411, 0.361703, 502.998), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-17.8461, -0.806021, 503.43), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-18.0561, 0.373953, 503.419), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-28.4174, 6.05318, 502.979), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-27.8314, 7.26132, 503.002), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-17.1122, 6.0579, 503.451), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rays.push_back(ray(SPAposition(-16.9913, 7.12864, 503.454), SPAunit_vector(0.0416888, -0.00140016, -0.99913), 0.201327, 1));
    rayfire_options rfo;
    rfo.set_entity_type(EDGE_TYPE);
    rfo.set_single_hit_per_entity(TRUE);
    {
        for(std::vector<ray>::iterator it = rays.begin(); it != rays.end(); ++it) {
            entity_hit_list ehl;
            check_outcome(api_ray_fire(toycar, *it, ehl, &rfo));
            if(ehl.count() != 1) {
                sys_error(API_FAILED);
            }
            ENTITY* ent = ehl[0]->hit_entity();
            if(!is_EDGE(ent)) {
                sys_error(API_FAILED);
            }
            ENTITY_LIST el;
            check_outcome(api_smooth_edge_seq(static_cast<EDGE*>(ent), el));
            check_outcome(api_set_const_rounds(el, 0.3));
            ENTITY_LIST bg;
            check_outcome(api_blend_graph(static_cast<EDGE*>(ent), bg));
            check_outcome(api_fix_blends(bg));
        }
    }

    return toycar;
}
LOCAL_PROC
void make_tolerant(BODY* bdy, const double tol) {
    if(NULL == bdy->lump() || NULL == bdy->lump()->shell() || NULL == bdy->lump()->shell()->face()) {
        sys_error(API_FAILED);
    }
    FACE* fac = bdy->lump()->shell()->face();
    SPApar_box pbx;
    sg_get_face_par_box(fac, pbx);
    const surface& srf = fac->geometry()->equation();
    const SPAunit_vector nrml = srf.eval_normal(pbx.mid());
    const SPAvector tr = nrml * tol;
    check_outcome(api_transform_entity(bdy, translate_transf(tr)));
    check_outcome(api_change_body_trans(bdy, NULL));
}
LOCAL_PROC
void make_stitch_input_bodies(ENTITY_LIST& bodies, const double tol) {
    bodies.clear();

    EXCEPTION_BEGIN
    BODY* bdy = NULL;
    EXCEPTION_TRY
    bdy = make_toycar();
    check_outcome(api_change_body_trans(bdy, NULL));
    ENTITY_LIST fl;
    check_outcome(api_get_faces(bdy, fl));
    {
        for(fl.init(); FACE* fac = static_cast<FACE*>(fl.next());) {
            BODY* ub = NULL;
            check_outcome(api_unhook_face(fac, ub));
            make_tolerant(ub, tol);
            bodies.add(ub);
        }
    }
    EXCEPTION_CATCH_TRUE
    bdy->lose();
    EXCEPTION_END
}

outcome aei_STITCH_FULL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    ENTITY_LIST bodies;

    API_BEGIN

    EXCEPTION_BEGIN
    stitch_input_handle* sih = NULL;
    stitch_output_handle* soh = NULL;
    EXCEPTION_TRY

    //
    // make a bunch of disconnected faces
    //
    make_stitch_input_bodies(bodies, 0.02);  // create toycar

    //
    // make stitch input
    //
    mt_stitch_options sop;
    sop.set_max_stitch_tol(1.0);  // set max stitch tol
    check_outcome(api_stitch_make_input(bodies, sih, &sop));

    //
    // stitch
    //
    bodies.clear();
    sop.set_heal_type(heal_option::HEAL_ALL);                       // set heal option
    sop.set_validation_type(validation_option::SHEETS_AND_SOLIDS);  // set validation option
    const int n_threads = 4;                                        // *** number of worker threads ***
    thread_work_base::initialize(n_threads, start_thread_func, stop_thread_func);
    outcome out = api_stitch(sih, soh, bodies, &sop);
    thread_work_base::terminate();
    check_outcome(out);

    EXCEPTION_CATCH_TRUE
    ACIS_DELETE sih;
    sih = NULL;
    ACIS_DELETE soh;
    soh = NULL;
    EXCEPTION_END

    API_END

    if(result.ok()) {
        output_ents.add(bodies);
    }
    return result;
}
