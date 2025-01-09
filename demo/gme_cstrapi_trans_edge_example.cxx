/*********************************************************************
 * @file    gme_cstrapi_trans_edge_example.cxx
 * @brief   api_trans_edge demo
 * @details
 * @author  CastaneaG
 * @date    2023.9.9
 *********************************************************************/
#include "gme_cstrapi_trans_edge_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trans_edge_demo 1:
//
// APIs:
//    gme_api_trans_edge
//
// Description:
//	  直线位置变换
//
// **********************************************************************************
outcome aei_TRANS_EDGE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_in_edge = nullptr;
    EDGE* gme_out_edge = nullptr;
    API_BEGIN
    SPAtransf gme_trans = translate_transf(SPAvector(0, 2, 0));
    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(2, 0, 0), gme_in_edge);
    gme_api_trans_edge(gme_in_edge, gme_trans, gme_out_edge);
    api_rh_set_entity_rgb(gme_out_edge, rgb_color(0.2, 0.5, 0.5));

    API_END

    if(result.ok()) {
        output_ents.add(gme_in_edge);
        output_ents.add(gme_out_edge);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  trans_edge_demo 2:
//
// APIs:
//    gme_api_trans_edge
//
// Description:
//	  半椭圆位置变换
//
// **********************************************************************************
outcome aei_TRANS_EDGE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_in_edge = nullptr;
    EDGE* gme_out_edge = nullptr;
    API_BEGIN
    SPAtransf gme_trans = translate_transf(SPAvector(0, 2, 0));
    api_mk_ed_ellipse(SPAposition(0, 0, 0), SPAunit_vector(0, 1, 0), SPAvector(2, 0, 0), 0.5, 0, M_PI, gme_in_edge);
    gme_api_trans_edge(gme_in_edge, gme_trans, gme_out_edge);
    api_rh_set_entity_rgb(gme_out_edge, rgb_color(0.2, 0.5, 0.5));

    API_END

    if(result.ok()) {
        output_ents.add(gme_in_edge);
        output_ents.add(gme_out_edge);
    }
    return result;
}
