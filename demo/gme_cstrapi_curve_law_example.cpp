/*********************************************************************
 * @file    gme_cstrapi_curve_law_example.cpp
 * @brief   gme_api_curve_law demo
 * @details
 * @author  宋羽豪
 * @date    2023.9.8
 *********************************************************************/
#include "gme_cstrapi_curve_law_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/spline.hxx"
#include "acis/sps3srtn.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_law_demo 1:
//
// APIs:
//    gme_api_curve_law
//
// Description:
//	  法则law为(x, sin(x), cos(x))，参数范围(start, end) = (-10, 10)
//
// **********************************************************************************
outcome aei_CURVE_LAW_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    curve* gme_curve = NULL;
    EDGE* gme_edge = NULL;

    API_BEGIN
    // 指定law
    law* in_law = nullptr;
    std::string law_str = "VEC(x, sin(x), cos(x))";
    // 创建law
    api_str_to_law(law_str.c_str(), &in_law);
    // 设param: x的上下限
    double start = -10;
    double end = 10;

    // 生成curve
    gme_api_curve_law(in_law, start, end, gme_curve);
    api_make_edge_from_curve(gme_curve, gme_edge);

    API_END

    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_law_demo 2:
//
// APIs:
//    gme_api_curve_law
//
// Description:
//	  法则law为(x, sin(x), cos(x))，参数范围(start, end) = (-SPAresabs, SPAresabs)
//
// **********************************************************************************
outcome aei_CURVE_LAW_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    curve* gme_curve = NULL;
    EDGE* gme_edge = NULL;

    API_BEGIN
    // 指定law
    law* in_law = nullptr;
    std::string law_str = "VEC(x, sin(x)^2, cos(x)^2)";
    // 创建law
    api_str_to_law(law_str.c_str(), &in_law);
    // 设param: x的上下限
    double start = -SPAresabs;
    double end = SPAresabs;

    // 生成curve
    api_curve_law(in_law, start, end, gme_curve);
    api_make_edge_from_curve(gme_curve, gme_edge);

    API_END

    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    return result;
}