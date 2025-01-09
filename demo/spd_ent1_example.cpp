/*********************************************************************
 * @file    spd_ent1_example.hxx
 * @brief
 * @details
 * @author  韩昊欣
 * @date    2024.7.23
 *********************************************************************/
#include "spd_ent1_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "gme_spd_cstrapi.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd_ent1_demo 1:
//
// APIs:
//     gme_HD_PEL_ENT1
//
// Description:
//	  随机生成起点终点，标注起点终点坐标（红色）。
//
// **********************************************************************************
outcome aei_HD_PEL_ENT1_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* edge = nullptr;
    BODY* start_point = nullptr;
    BODY* end_point = nullptr;
    SPAposition start;
    SPAposition end;
    double head[3] = {0.0, 0.0, 0.0};
    double direction[3] = {0.0, 0.0, 1.0};
    double length = 10.0;
    rgb_color red(1, 0, 0);
    API_BEGIN
    start = SPAposition(head);
    end = SPAposition(head[0] + length * direction[0], head[1] + length * direction[1], head[2] + length * direction[2]);
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
    result = gme_HD_PEL_ENT1(head, direction, length, edge);
    if(result.ok()) {
        output_ents.add(edge);
    }
    API_END

    return result;
}
