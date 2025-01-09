/*********************************************************************
 * @file    gme_cstrapi_modify_line_example.cpp
 * @brief
 * @details
 * @author  杨楠
 * @date    2024.7.20
 *********************************************************************/
#include "gme_cstrapi_modify_line_example.hxx"

#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  modify_line_demo 1:
//
// APIs:
//    gme_api_modify_line
//
// Description:
//	  随机生成起点终点，修改直线，显示修改后的直线，标注修改前后的起点终点坐标（红色为修改前，绿色为修改后）。
//
// **********************************************************************************
outcome aei_MODIFY_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    EDGE* edge = nullptr;                                        // 用于接收创建的EDGE
    BODY* start_point = nullptr;                                 // 标记起点
    BODY* end_point = nullptr;                                   // 标记终点
    BODY* new_start_point = nullptr;                             // 标记新起点
    BODY* new_end_point = nullptr;                               // 标记新终点
    SPAposition start;                                           // 起点坐标
    SPAposition end;                                             // 终点坐标
    std::default_random_engine generator;                        // 随机数生成器
    std::uniform_real_distribution<double> distribution(-5, 5);  // 随机数分布
    rgb_color red(1, 0, 0);                                      // 红色，标注修改前的点
    rgb_color green(0, 1, 0);                                    // 绿色，标注修改后的点

    /* API Call Block */
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
    result = api_mk_ed_line(start, end, edge);
    // 随机生成新的起点和终点
    do {
        start = SPAposition(distribution(generator), distribution(generator), distribution(generator));
        end = SPAposition(distribution(generator), distribution(generator), distribution(generator));
    } while(start == end);
    // 在新的起点绘制球体作为标注
    api_solid_sphere(start, 0.1, new_start_point);
    result = api_rh_set_entity_rgb(new_start_point, green);
    if(result.ok()) {
        output_ents.add(new_start_point);
    }
    // 在新的终点绘制球体作为标注
    api_solid_sphere(end, 0.1, new_end_point);
    result = api_rh_set_entity_rgb(new_end_point, green);
    if(result.ok()) {
        output_ents.add(new_end_point);
    }
    // 修改直线
    result = gme_api_modify_line(edge, start, end);
    if(result.ok()) {
        output_ents.add(edge);
    }
    API_END

    return result;
}