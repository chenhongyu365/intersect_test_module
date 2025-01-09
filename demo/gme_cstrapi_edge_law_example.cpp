/*********************************************************************
 * @file    gme_cstrapi_edge_law_example.cpp
 * @brief
 * @details
 * @author  杨楠
 * @date    2024.8.5
 *********************************************************************/
#include "gme_cstrapi_edge_law_example.hxx"

#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/cstrapi.hxx"
#include "acis/law.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  edge_law_demo 1:
//
// APIs:
//    gme_api_edge_law
//
// Description:
//    绘制抛物线
// **********************************************************************************
outcome aei_EDGE_LAW_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_edge = nullptr;
    law* in_law = nullptr;
    EDGE* axis_x_pos = nullptr;
    EDGE* axis_y_pos = nullptr;
    EDGE* axis_z_pos = nullptr;
    rgb_color red(1, 0, 0);
    rgb_color green(0, 1, 0);
    rgb_color blue(0, 0, 1);

    std::string law_str = "VEC(t, t ^ 2, 0)";
    api_str_to_law(law_str.c_str(), &in_law);
    API_BEGIN
    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(5, 0, 0), axis_x_pos);
    api_rh_set_entity_rgb(axis_x_pos, red);
    output_ents.add(axis_x_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 5, 0), axis_y_pos);
    api_rh_set_entity_rgb(axis_y_pos, green);
    output_ents.add(axis_y_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 0, 5), axis_z_pos);
    api_rh_set_entity_rgb(axis_z_pos, blue);
    output_ents.add(axis_z_pos);

    result = gme_api_edge_law(in_law, -2, 2, gme_edge);
    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    in_law->remove();
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  edge_law_demo 2:
//
// APIs:
//    gme_api_edge_law
//
// Description:
//    绘制椭圆弧
// **********************************************************************************
outcome aei_EDGE_LAW_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_edge = nullptr;
    law* in_law = nullptr;
    EDGE* axis_x_pos = nullptr;
    EDGE* axis_y_pos = nullptr;
    EDGE* axis_z_pos = nullptr;
    rgb_color red(1, 0, 0);
    rgb_color green(0, 1, 0);
    rgb_color blue(0, 0, 1);

    std::string law_str = "VEC(3 * COS(x), 4 * SIN(x), 2)";
    api_str_to_law(law_str.c_str(), &in_law);
    API_BEGIN
    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(5, 0, 0), axis_x_pos);
    api_rh_set_entity_rgb(axis_x_pos, red);
    output_ents.add(axis_x_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 5, 0), axis_y_pos);
    api_rh_set_entity_rgb(axis_y_pos, green);
    output_ents.add(axis_y_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 0, 5), axis_z_pos);
    api_rh_set_entity_rgb(axis_z_pos, blue);
    output_ents.add(axis_z_pos);

    result = gme_api_edge_law(in_law, 0, M_PI, gme_edge);
    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    in_law->remove();
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  edge_law_demo 3:
//
// APIs:
//    gme_api_edge_law
//
// Description:
//    绘制多项式曲线
// **********************************************************************************
outcome aei_EDGE_LAW_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_edge = nullptr;
    law* in_law = nullptr;
    EDGE* axis_x_pos = nullptr;
    EDGE* axis_y_pos = nullptr;
    EDGE* axis_z_pos = nullptr;
    rgb_color red(1, 0, 0);
    rgb_color green(0, 1, 0);
    rgb_color blue(0, 0, 1);

    std::string law_str = "VEC(2 * x ^ 4 - 3 * x - 1, 3 * x ^ 3 - 2 * x ^ 2, 2 * x + 2)";
    api_str_to_law(law_str.c_str(), &in_law);
    API_BEGIN
    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(5, 0, 0), axis_x_pos);
    api_rh_set_entity_rgb(axis_x_pos, red);
    output_ents.add(axis_x_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 5, 0), axis_y_pos);
    api_rh_set_entity_rgb(axis_y_pos, green);
    output_ents.add(axis_y_pos);

    api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0, 0, 5), axis_z_pos);
    api_rh_set_entity_rgb(axis_z_pos, blue);
    output_ents.add(axis_z_pos);

    result = gme_api_edge_law(in_law, -1, 1, gme_edge);
    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    in_law->remove();
    API_END
    return result;
}
