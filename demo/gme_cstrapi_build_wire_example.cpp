/*********************************************************************
 * @file    gme_cstrapi_build_wire_example.cpp
 * @brief   gme_api_build_wire demo
 * @details
 * @author  宋羽豪
 * @date    2023.9.24
 *********************************************************************/
#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/elldef.hxx"
#include "acis/law_base.hxx"
#include "acis_utils.hpp"
#include "gme_cstrapi_curve_law_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  build_wire_demo 1:
//
// APIs:
//    gme_api_build_wire
//
// Description:
//	  初始的in_body是2*2*2的cuboid，需要添加以原点为圆心、2为半径的闭合圆形wire
//
// **********************************************************************************
outcome aei_BUILD_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = nullptr;
    BODY* gme_in_body = nullptr;

    API_BEGIN
    // 给in_body赋值
    api_make_cuboid(2, 2, 2, gme_in_body);
    // demo数据：中心为原点、半径为2的圆
    SPAposition* centre = ACIS_NEW SPAposition(0, 0, 0);
    SPAunit_vector* normal = ACIS_NEW SPAunit_vector(0, 0, 1);
    SPAvector* maj_axis = ACIS_NEW SPAvector(2, 0, 0);
    double ratio = 1.0;
    ellipse* ell = ACIS_NEW ellipse(*centre, *normal, *maj_axis, ratio);
    // 一个点（2，0，0）
    SPAposition* points = ACIS_NEW SPAposition[1];
    points[0] = *(ACIS_NEW SPAposition(2, 0, 0));
    // 一条curve：圆
    curve** curves = ACIS_NEW curve* [1];
    curves[0] = ell;

    // 创建wire body
    gme_api_build_wire(gme_in_body, true, 1, points, curves, gme_body);

    ACIS_DELETE curves[0];
    ACIS_DELETE[] STD_CAST curves;
    ACIS_DELETE[] points;
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  build_wire_demo 2:
//
// APIs:
//    gme_api_build_wire
//
// Description:
//	  初始的 in_body 的 wire 为空，需要添加多条edge构成的开放wire
//
// **********************************************************************************
outcome aei_BUILD_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = nullptr;
    BODY* gme_in_body = nullptr;

    API_BEGIN
    // 给in_body赋值
    SHELL* gme_shell = ACIS_NEW SHELL((WIRE*)nullptr, nullptr, nullptr);
    LUMP* gme_lump = ACIS_NEW LUMP(gme_shell, nullptr);
    gme_in_body = ACIS_NEW BODY(gme_lump);

    // demo数据
    std::vector<double> u{-4.0, 4.0, -4.0, 4};
    SPAposition* points = ACIS_NEW SPAposition[u.size()];
    std::vector<std::string> law_str{"VEC(u, u*u/8+2, u)", "VEC(4, u, 4)", "VEC(-u, -u*u/8-2, -u)"};
    curve** curves = ACIS_NEW curve * [law_str.size()];
    law* law = nullptr;
    curve* curve = nullptr;
    api_str_to_law(law_str[0].c_str(), &law);
    points[0] = law->evaluateR_P(u[0]);
    law->remove();
    for(int i = 0; i < law_str.size(); ++i) {
        law = nullptr;
        api_str_to_law(law_str[i].c_str(), &law);
        points[i + 1] = law->evaluateR_P(u[i + 1]);
        api_curve_law(law, u[i], u[i + 1], curve);
        curves[i] = curve;
        law->remove();
    }

    gme_api_build_wire(gme_in_body, false, u.size(), points, curves, gme_body);

    for(int i = 0; i < law_str.size(); ++i) {
        ACIS_DELETE curves[i];
    }
    ACIS_DELETE[] STD_CAST curves;
    ACIS_DELETE[] points;
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  build_wire_demo 3:
//
// APIs:
//    gme_api_build_wire
//
// Description:
//	  初始的 in_body 的 wire 为空，0 < num_points < points.size()
//
// **********************************************************************************
outcome aei_BUILD_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = nullptr;
    BODY* gme_in_body = nullptr;

    API_BEGIN
    // 给in_body赋值
    SHELL* gme_shell = ACIS_NEW SHELL((WIRE*)nullptr, nullptr, nullptr);
    LUMP* gme_lump = ACIS_NEW LUMP(gme_shell, nullptr);
    gme_in_body = ACIS_NEW BODY(gme_lump);

    // demo数据
    std::vector<double> u{-4.0, 4.0, -4.0, 4};
    SPAposition* points = ACIS_NEW SPAposition[u.size()];
    std::vector<std::string> law_str{"VEC(u, u*u/8+2, u)", "VEC(4, u, 4)", "VEC(-u, -u*u/8-2, -u)"};
    curve** curves = ACIS_NEW curve * [law_str.size()];
    law* law = nullptr;
    curve* curve = nullptr;
    api_str_to_law(law_str[0].c_str(), &law);
    points[0] = law->evaluateR_P(u[0]);
    law->remove();
    for(int i = 0; i < law_str.size(); ++i) {
        law = nullptr;
        api_str_to_law(law_str[i].c_str(), &law);
        points[i + 1] = law->evaluateR_P(u[i + 1]);
        api_curve_law(law, u[i], u[i + 1], curve);
        curves[i] = curve;
        law->remove();
    }

    gme_api_build_wire(gme_in_body, false, 3, points, curves, gme_body);

    for(int i = 0; i < law_str.size(); ++i) {
        ACIS_DELETE curves[i];
    }
    ACIS_DELETE[] STD_CAST curves;
    ACIS_DELETE[] points;
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  build_wire_demo 3:
//
// APIs:
//    gme_api_build_wire
//
// Description:
//	  初始的 in_body 为空，存在两个位置<容差SPAresabs
//
// **********************************************************************************
outcome aei_BUILD_WIRE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = nullptr;
    BODY* gme_in_body = nullptr;

    API_BEGIN
    // demo数据
    std::vector<double> u{0, 1e-7, 2e-7, 3e-6, 4e-6};
    SPAposition* points = ACIS_NEW SPAposition[u.size()];
    std::vector<std::string> law_str{"VEC(u, u, u)", "VEC(u, u, u)", "VEC(u, u, u)", "VEC(u, u, u)"};
    curve** curves = ACIS_NEW curve * [law_str.size()];
    law* law = nullptr;
    curve* curve = nullptr;
    api_str_to_law(law_str[0].c_str(), &law);
    points[0] = law->evaluateR_P(u[0]);
    law->remove();
    for(int i = 0; i < law_str.size(); ++i) {
        law = nullptr;
        api_str_to_law(law_str[i].c_str(), &law);
        points[i + 1] = law->evaluateR_P(u[i + 1]);
        api_curve_law(law, u[i], u[i + 1], curve);
        curves[i] = curve;
        law->remove();
    }

    gme_api_build_wire(gme_in_body, false, u.size(), points, curves, gme_body);

    for(int i = 0; i < law_str.size(); ++i) {
        ACIS_DELETE curves[i];
    }
    ACIS_DELETE[] STD_CAST curves;
    ACIS_DELETE[] points;
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}