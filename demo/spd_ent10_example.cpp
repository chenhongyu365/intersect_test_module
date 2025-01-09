/*********************************************************************
 * @file    spd_ent10_example.cpp
 * @brief   HD_PEL_ENT10 demo
 * @details
 * @author  杨楠
 * @date    2023.7.22
 *********************************************************************/

#include <random>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT10
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT10.
//    直角三棱柱，底面在xy平面，u，v分别为x，y方向
// **********************************************************************************
outcome aei_HD_PEL_ENT10_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* axis_x = nullptr;
    EDGE* axis_y = nullptr;
    EDGE* axis_z = nullptr;
    rgb_color red(1, 0, 0);
    rgb_color green(0, 1, 0);
    rgb_color blue(0, 0, 1);
    API_BEGIN
    api_mk_ed_line(SPAposition(-5, 0, 0), SPAposition(5, 0, 0), axis_x);
    api_rh_set_entity_rgb(axis_x, red);
    output_ents.add(axis_x);
    api_mk_ed_line(SPAposition(0, -5, 0), SPAposition(0, 5, 0), axis_y);
    api_rh_set_entity_rgb(axis_y, green);
    output_ents.add(axis_y);
    api_mk_ed_line(SPAposition(0, 0, -5), SPAposition(0, 0, 5), axis_z);
    api_rh_set_entity_rgb(axis_z, blue);
    output_ents.add(axis_z);
    double p[3] = {0, 0, 0};
    double u[3] = {1, 0, 0};
    double v[3] = {0, 1, 0};
    double lu = 3;
    double lw = 3;
    double lv = 3;
    result = gme_HD_PEL_ENT10(p, u, v, lu, lw, lv, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT10
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT10.
//    直角三棱柱，随机生成参数
// **********************************************************************************
outcome aei_HD_PEL_ENT10_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-4, 4);
    std::uniform_real_distribution<double> distribution_positive(0, 4);
    EDGE* axis_x = nullptr;
    EDGE* axis_y = nullptr;
    EDGE* axis_z = nullptr;
    rgb_color red(1, 0, 0);
    rgb_color green(0, 1, 0);
    rgb_color blue(0, 0, 1);
    API_BEGIN
    generator.seed(std::random_device()());
    api_mk_ed_line(SPAposition(-5, 0, 0), SPAposition(5, 0, 0), axis_x);
    api_rh_set_entity_rgb(axis_x, red);
    output_ents.add(axis_x);
    api_mk_ed_line(SPAposition(0, -5, 0), SPAposition(0, 5, 0), axis_y);
    api_rh_set_entity_rgb(axis_y, green);
    output_ents.add(axis_y);
    api_mk_ed_line(SPAposition(0, 0, -5), SPAposition(0, 0, 5), axis_z);
    api_rh_set_entity_rgb(axis_z, blue);
    output_ents.add(axis_z);
    double p[3] = {distribution(generator), distribution(generator), distribution(generator)};
    double u[3], v[3];
    double cross_product[3];
    do {
        u[0] = distribution(generator);
        u[1] = distribution(generator);
        u[2] = distribution(generator);
        v[0] = distribution(generator);
        v[1] = distribution(generator);
        v[2] = distribution(generator);
        cross_product[0] = u[1] * v[2] - u[2] * v[1];
        cross_product[1] = u[2] * v[0] - u[0] * v[2];
        cross_product[2] = u[0] * v[1] - u[1] * v[0];
    } while(u[0] == 0 && u[1] == 0 && u[2] == 0 && v[0] == 0 && v[1] == 0 && v[2] == 0 && cross_product[0] == 0 && cross_product[1] == 0 && cross_product[2] == 0);
    double lu = distribution_positive(generator);
    double lw = distribution_positive(generator);
    double lv = distribution_positive(generator);
    result = gme_HD_PEL_ENT10(p, u, v, lu, lw, lv, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}
