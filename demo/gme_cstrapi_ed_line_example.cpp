/*********************************************************************
 * @file    gme_cstrapi_ed_line_example.cpp
 * @brief
 * @details
 * @author  韩昊欣
 * @date    2024.7.22
 *********************************************************************/
#include "gme_cstrapi_ed_line_example.hxx"

#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  ed_line_demo 1:
//
// APIs:
//    gme_api_mk_ed_line
//
// Description:
//	  随机生成起点终点，标注起点终点坐标（红色）。
//
// **********************************************************************************
outcome aei_ED_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // 用于接收创建的edge
    EDGE* edge = nullptr;
    // 用于标注起点
    BODY* start_point = nullptr;
    // 用于标注终点
    BODY* end_point = nullptr;
    // 起点
    SPAposition start;
    // 终点
    SPAposition end;
    // 随机数生成器
    std::default_random_engine generator;
    // 随机数分布
    std::uniform_real_distribution<double> distribution(-5, 5);
    // 标注颜色
    rgb_color red(1, 0, 0);
    API_BEGIN
    generator.seed(std::random_device()());
    // 随机生成不同的起点和终点
    do {
        start = SPAposition(distribution(generator), distribution(generator), distribution(generator));
        end = SPAposition(distribution(generator), distribution(generator), distribution(generator));
    } while(start == end);
    // 在起点绘制球体作为标注
    api_solid_sphere(start, 0.1, start_point);
    result = api_rh_set_entity_rgb(start_point, red);
    if(result.ok()) {
        output_ents.add(start_point);
    }
    // 在终点绘制球体作为标注
    api_solid_sphere(end, 0.1, end_point);
    result = api_rh_set_entity_rgb(end_point, red);
    if(result.ok()) {
        output_ents.add(end_point);
    }
    // 创建直线
    result = gme_api_mk_ed_line(start, end, edge);
    if(result.ok()) {
        output_ents.add(edge);
    }
    API_END

    return result;
}
