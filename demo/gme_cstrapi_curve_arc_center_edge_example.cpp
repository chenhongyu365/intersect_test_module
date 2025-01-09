/*********************************************************************
 * @file    gme_cstrapi_curve_arc_center_edge_example.cpp
 * @brief   api_curve_arc_center_edge demo
 * @details
 * @author  evertravel
 * @date    2024.9.22
 *********************************************************************/
#include "gme_cstrapi_curve_arc_center_edge_example.hxx"

#include <vector>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_arc_center_edge_demo 1:
//
// APIs:
//    gme_api_curve_arc_center_edge
//
// Description:
//	  正常情况
//
// **********************************************************************************
outcome aei_CURVE_ARC_CENTER_EDGE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    EDGE* acis_arc = NULL;
    EDGE* gme_arc = NULL;
    SPAposition center = SPAposition(0, 0, 0);
    SPAposition pt1 = SPAposition(1, 5, 0);
    SPAposition pt2 = SPAposition(0, 4, 2);
    SPAunit_vector norm = SPAunit_vector(4, 7, 0);

    API_BEGIN
    gme_api_curve_arc_center_edge(center, pt1, pt2, &norm, gme_arc);
    API_END

    if(result.ok()) {
        output_ents.add(gme_arc);
    }

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_arc_center_edge_demo 1:
//
// APIs:
//    gme_api_curve_arc_center_edge
//
// Description:
//	  pt1 = pt2的情况
//
// **********************************************************************************
outcome aei_CURVE_ARC_CENTER_EDGE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    SPAposition center = SPAposition(0, 0, 0);
    SPAposition pt1 = SPAposition(1, 5, 0);
    SPAposition pt2 = SPAposition(1, 5, 0);
    SPAunit_vector norm = SPAunit_vector(0, 1, 0);

    API_BEGIN
    gme_api_curve_arc_center_edge(center, pt1, pt2, &norm, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_arc_center_edge_demo 1:
//
// APIs:
//    gme_api_curve_arc_center_edge
//
// Description:
//	  norm = NULL 的情况
//
// **********************************************************************************
outcome aei_CURVE_ARC_CENTER_EDGE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    SPAposition center = SPAposition(0, 0, 0);
    SPAposition pt1 = SPAposition(1, 2, 3);
    SPAposition pt2 = SPAposition(8, 4, 7);

    API_BEGIN
    gme_api_curve_arc_center_edge(center, pt1, pt2, NULL, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }

    return result;
}
