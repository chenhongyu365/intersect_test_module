/*********************************************************************
 * @file    gme_cstrapi_2_ed_line_example.cpp
 * @brief
 * @details
 * @author  程红
 * @date    2024.8.5
 *********************************************************************/

#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "gme_cstrapi_2_ed_line_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_ed_line_demo 1:
//
// APIs:
//    gme_2_api_mk_ed_line
//
// Description:
//	  起点终点为固定值，标注：红色点为起点坐标，蓝色点终点坐标。
//
// **********************************************************************************
outcome aei_2_MK_ED_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN

    // 用于接收创建的edge
    EDGE* edge = nullptr;

    // 用于储存起点球体
    BODY* start_body = nullptr;
    // 用于储存终点球体
    BODY* end_body = nullptr;

    // 创建两个空间点
    // 起点
    SPAposition pos_start(5, 2, -7);
    // 终点
    SPAposition pos_end(-3, 4, 5);
    rgb_color blue(0, 0, 1);
    rgb_color red(1, 0, 0);

    // 在起点绘制球体，并result、output呈现，标注红色起点
    api_solid_sphere(pos_start, 0.1, start_body);
    result = api_rh_set_entity_rgb(start_body, red);
    if(result.ok()) {
        output_ents.add(start_body);
    }
    // 在终点绘制球体，并result、output呈现，标注蓝色终点
    api_solid_sphere(pos_end, 0.1, end_body);
    result = api_rh_set_entity_rgb(end_body, blue);
    if(result.ok()) {
        output_ents.add(end_body);
    }
    // 创建并呈现直线
    result = gme_2_api_mk_ed_line(pos_start, pos_end, edge);
    if(result.ok()) {
        output_ents.add(edge);
    }
    API_END

    return result;
}