/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "incr_examples.hxx"

#include <string>
#include <vector>

#include "acis/api.err"
#include "acis/body.hxx"
#include "acis/bool_api_options.hxx"
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/entity.hxx"
#include "acis/hlc_api.err"
#include "acis/incr_bool_api.hxx"
#include "acis/kernapi.hxx"
#include "acis/lists.hxx"
#include "acis/position.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/skin_opts.hxx"
#include "acis/skinapi.hxx"
#include "acis/sliver_ents.hxx"
#include "acis/transf.hxx"

LOCAL_PROC
void make_tool_and_blank(BODY*& tool, BODY*& blank) {
    EXCEPTION_BEGIN

    BODY *b1 = NULL, *b2 = NULL, *t1 = NULL, *t2 = NULL;

    EXCEPTION_TRY

    // (define b1 (wire-body:points(list(position 0 0 0) (position 10 0 0) (position 10 6 0) (position 0 6 0) (position 0 0 0))))
    std::vector<SPAposition> pts;
    pts.push_back(SPAposition(0.0, 0.0, 0.0));
    pts.push_back(SPAposition(10.0, 0.0, 0.0));
    pts.push_back(SPAposition(10.0, 6.0, 0.0));
    pts.push_back(SPAposition(0.0, 6.0, 0.0));
    pts.push_back(SPAposition(0.0, 0.0, 0.0));
    check_outcome(api_make_wire(NULL, static_cast<int>(pts.size()), &(pts[0]), b1));

    // (define b2 (wire-body:points(list(position 2 2 5) (position 8 2.997 5) (position 8 3.003 5) (position 2 4 5) (position 2 2 5))))
    pts.clear();
    pts.push_back(SPAposition(2.0, 2.0, 5.0));
    pts.push_back(SPAposition(8.0, 2.997, 5.0));
    pts.push_back(SPAposition(8.0, 3.003, 5.0));
    pts.push_back(SPAposition(2.0, 4.0, 5.0));
    pts.push_back(SPAposition(2.0, 2.0, 5.0));
    check_outcome(api_make_wire(NULL, static_cast<int>(pts.size()), &(pts[0]), b2));

    // (define t2 (wire-body:points(list(position 2 2 5) (position 8 2.993 5) (position 8 3.007 5) (position 2 4 5) (position 2 2 5))))
    pts.clear();
    pts.push_back(SPAposition(2.0, 2.0, 5.0));
    pts.push_back(SPAposition(8.0, 2.993, 5.0));
    pts.push_back(SPAposition(8.0, 3.007, 5.0));
    pts.push_back(SPAposition(2.0, 4.0, 5.0));
    pts.push_back(SPAposition(2.0, 2.0, 5.0));
    check_outcome(api_make_wire(NULL, static_cast<int>(pts.size()), &(pts[0]), t2));

    // (define t1 (entity:copy b1))
    ENTITY* _t1;
    check_outcome(api_copy_entity(b1, _t1));
    t1 = static_cast<BODY*>(_t1);
    // (define t1 (entity:reflect t1 5 3 5 0 0 1 #t))
    const SPAvector orig0(5.0, 3.0, 5.0);
    const SPAvector norm(0.0, 0.0, 1.0);
    check_outcome(api_transform_entity(t1, translate_transf(-orig0)));
    check_outcome(api_transform_entity(t1, reflect_transf(norm)));
    check_outcome(api_transform_entity(t1, translate_transf(orig0)));
    check_outcome(api_change_body_trans(t1, NULL));

    // (define blank(sheet:skin-wires(list wb-b1 wb-b2) (skin:options "solid" #t)))
    skin_options sop;
    sop.set_solid(TRUE);
    ENTITY_LIST wbl;
    wbl.add(b1);
    wbl.add(b2);
    check_outcome(api_skin_wires(wbl.iteration_count(), wbl, NULL, blank, &sop));
    // (define tool(sheet:skin-wires(list wb-t1 wb-t2) (skin:options "solid" #t)))
    ENTITY_LIST wtl;
    wtl.add(t1);
    wtl.add(t2);
    check_outcome(api_skin_wires(wtl.iteration_count(), wtl, NULL, tool, &sop));
    // (entity:rotate tool 8 0 5 0 1 0 - 20 #t)
    const SPAvector orig1(8.0, 0.0, 5.0);
    const SPAvector ax(0.0, 1.0, 0.0);
    const double turn = -0.34906585039886590;
    check_outcome(api_transform_entity(tool, translate_transf(-orig1)));
    check_outcome(api_transform_entity(tool, rotate_transf(turn, ax)));
    check_outcome(api_transform_entity(tool, translate_transf(orig1)));
    check_outcome(api_change_body_trans(tool, NULL));
    // (tolerant:detect-short-edges tool 0.02 #t)
    ENTITY_LIST sel;
    api_detect_short_edges(tool, sel, 0.02, TRUE);

    //// (entity:set-color tool BLUE)
    // const rgb_color blue(0.0, 0.0, 1.0);
    // api_rh_set_entity_rgb(tool, blue);

    EXCEPTION_CATCH_TRUE

    ENTITY_LIST wbl;
    wbl.add(b1);
    wbl.add(b2);
    wbl.add(t1);
    wbl.add(t2);
    api_del_entity_list(wbl);

    EXCEPTION_END
}

outcome aei_INCR_BOOL(ENTITY_LIST& output_ents, AcisOptions* ao) {
    API_BEGIN

    outcome res_bool = result;

    // create an exemplary tool and blank to be used for booleans
    BODY* blank = NULL;
    BODY* tool = NULL;
    make_tool_and_blank(tool, blank);
    if(NULL == tool || NULL == blank) {
        sys_error(NULL_ENTITY);
    }

    // call boolean (UNION here)
    BODY* dummy = NULL;
    const BOOL_TYPE op = UNION;
    const NDBOOL_KEEP nd = NDBOOL_KEEP_NEITHER;
    {
        API_TRIAL_BEGIN
        check_outcome(api_boolean(tool, blank, op, nd, dummy, ao));
        API_TRIAL_END
        res_bool = result;
    }

    // if failed start incremental booleans
    if(!res_bool.ok()) {
        EXCEPTION_BEGIN

        incr_bool_handle* ibh = NULL;

        EXCEPTION_TRY

        // create incremental boolean handle
        ibh = incr_bool_handle::make(tool, blank, NULL, NULL, ao);
        bool_base_options* bo = const_cast<bool_base_options*>(ibh->get_bool_options());

        // keep going until boolean succeeds
        while(!res_bool.ok()) {
            // keep going if failure is added successfully
            const bool keep_going = ibh->update(res_bool);
            if(!keep_going) {
                sys_warning(INCR_NO_PROGRESS);
                break;
            }

            // keep going if preparation of tool and blank based on failure succeeded
            {
                API_TRIAL_BEGIN
                check_outcome(api_incr_bool_prepare(ibh, ao));
                API_TRIAL_END
                if(!result.ok()) {
                    sys_warning(result.error_number());
                    break;
                }
            }

            // call boolean again
            {
                API_TRIAL_BEGIN
                check_outcome(api_boolean(tool, blank, op, nd, dummy, static_cast<BoolOptions*>(bo), ao));
                API_TRIAL_END
                res_bool = result;
            }
        }

        check_outcome(res_bool);

        EXCEPTION_CATCH_TRUE

        ACIS_DELETE ibh;
        ibh = NULL;

        EXCEPTION_END
    }

    if(res_bool.ok()) {
        output_ents.add(blank);
    }

    API_END

    return result;
}
