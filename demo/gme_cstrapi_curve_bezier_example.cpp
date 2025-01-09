/*********************************************************************
 * @file    gme_cstrapi_curve_bezier_example.cpp
 * @brief   gme_api_curve_bezier demo
 * @details
 * @author  赵丛霖
 * @date    2024.9.20
 *********************************************************************/
#include "gme_cstrapi_curve_bezier_example.hxx"

#include <iostream>
#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve bezier 1:
//
// APIs:
//    gme_api_curve_bezier
//
// Description:
//	  正常情况
//
// **********************************************************************************
outcome aei_CURVE_BEZIER_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = nullptr;
    API_BEGIN
    SPAposition p1(0, 0, -40);
    SPAposition p2(30, 40, 60);
    SPAposition p3(60, -20, -80);
    SPAposition p4(100, 100, 100);

    gme_api_curve_bezier(p1, p2, p3, p4, edge);
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
//	  curve bezier 2:
//
// APIs:
//    gme_api_curve_bezier
//
// Description:
//	  直线
//
// **********************************************************************************
outcome aei_CURVE_BEZIER_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = nullptr;
    API_BEGIN
    SPAposition p1(0, 0, 0);
    SPAposition p2(30, 30, 30);
    SPAposition p3(60, 60, 60);
    SPAposition p4(100, 100, 100);

    gme_api_curve_bezier(p1, p2, p3, p4, edge);
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
//	  curve bezier 3:
//
// APIs:
//    gme_api_curve_bezier
//
// Description:
//	  闭合
//
// **********************************************************************************
outcome aei_CURVE_BEZIER_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = nullptr;
    API_BEGIN
    SPAposition p1(0, 0, 0);
    SPAposition p2(60, 60, 100);
    SPAposition p3(-30, 100, 0);

    gme_api_curve_bezier(p1, p2, p3, p1, edge);
    API_END

    if(result.ok()) {
        output_ents.add(edge);
    }
    return result;
}