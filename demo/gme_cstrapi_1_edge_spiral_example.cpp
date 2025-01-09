/*********************************************************************
 * @file    gme_1_api_edge_spiral_example.cpp
 * @brief
 * @details
 * @author  MOSSKEER 王可
 * @date    2024.8.3
 *********************************************************************/

#include "gme_cstrapi_1_edge_spiral_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_edge_spiral_demo 1:
//
// APIs:
//    gme_1_api_edge_spiral
//
// Description:
//    构造普通情况下的蚊香
// **********************************************************************************
outcome aei_1_EDGE_SPIRAL_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    EDGE* edge = nullptr;

    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);
    SPAposition start_pos(1, 0, 0);
    double width = 1;
    double angle = 100;
    logical sense = FALSE;
    API_BEGIN
    api_edge_spiral(center, normal, start_pos, width, angle, edge, sense);
    API_END

    if(result.ok()) {
        output_ents.add(edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_edge_spiral_demo 2:
//
// APIs:
//    gme_1_api_edge_spiral
//
// Description:
//    环间距离小于0
// **********************************************************************************
outcome aei_1_EDGE_SPIRAL_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    EDGE* edge = nullptr;

    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);
    SPAposition start_pos(1, 0, 0);
    double width = -5;
    double angle = 100;
    logical sense = FALSE;
    API_BEGIN
    gme_1_api_edge_spiral(center, normal, start_pos, width, angle, edge, sense);
    API_END

    if(result.ok()) {
        output_ents.add(edge);
    }
    return result;
}
