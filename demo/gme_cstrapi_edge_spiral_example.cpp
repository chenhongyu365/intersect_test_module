/*********************************************************************
 * @file    gme_cstrapi_edge_spiral_example.cpp
 * @brief  api_edge_spiral demo
 * @details
 * @author  葛宏泽
 * @date    2024.7.22
 *********************************************************************/
#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "gme_cstrapi_edge_spiral_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spiral_demo 1:
//
// APIs:
//    gme_api_edge_spiral
//
// Description:
//	  普通螺线
// **********************************************************************************
outcome aei_SPIRAL_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = NULL;
    SPAposition center(0,0,0);
    SPAvector normal(0,0,1);
    SPAposition start_pos(1,0,0);
    double width = 1;
    double angle = 100;
    logical sense = TRUE;
    API_BEGIN
    gme_api_edge_spiral(center, normal, start_pos, width, angle, edge, sense);
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
//	  spiral_demo 2:
//
// APIs:
//    gme_api_edge_spiral
//
// Description:
//	  向内螺线
// **********************************************************************************
outcome aei_SPIRAL_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = NULL;
    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);
    SPAposition start_pos(1, 0, 0);
    double width = -1;
    double angle = 100;
    logical sense = TRUE;
    API_BEGIN
    gme_api_edge_spiral(center, normal, start_pos, width, angle, edge, sense);
    API_END

    if(result.ok()) {
        output_ents.add(edge);
    }
    return result;
}