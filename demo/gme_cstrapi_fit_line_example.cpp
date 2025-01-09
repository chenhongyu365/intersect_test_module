/*********************************************************************
 * @file    gme_cstrapi_fit_line_example.cpp
 * @brief	为随机生成的散点拟合一条直线，生成的蓝绿长线为api_fit_line，较短黄线为gme_fit_line
 * @details
 * @author  全志成
 * @date    2023.7.24
 *********************************************************************/
#include "gme_cstrapi_fit_line_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/strdef.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  fit_line_demo:
//
// APIs:
//    gme_api_fit_line
//
// Description:
//	  为随机生成的散点拟合一条直线
//
// **********************************************************************************
outcome aei_FIT_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
	// 生成的蓝绿长线为api_fit_line，较短黄线为gme_fit_line，二者重合；待拟合的点用球显示
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN

    // 建立三维直角坐标系
    int scale = 100;  // 坐标系横坐标范围
    SPAposition pos1(scale, 0, 0);
    SPAposition pos2(-1 * scale, 0, 0);
    check_outcome(api_curve_line(pos1, pos2, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1.0, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos3(0, scale, 0);
    SPAposition pos4(0, -1 * scale, 0);
    check_outcome(api_curve_line(pos3, pos4, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1.0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos5(0, 0, scale);
    SPAposition pos6(0, 0, -1 * scale);
    check_outcome(api_curve_line(pos5, pos6, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 1.0));
    if(result.ok()) output_ents.add(my_edge);

    // 点坐标
    SPAposition_vector point_list;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100, 100);  // 左闭右闭区间
    e.seed(time(0));
    // 随机数生成测试用例
    for(int i = 0; i < 10; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }

    // 绘制api_fit_line
    double range = 110; //直线范围
    straight api_straight;
    api_fit_line(point_list, api_straight);
    SPAunit_vector acis_vector = api_straight.direction;
    SPAposition acis_point = api_straight.root_point;
    SPAposition pos9(acis_point.x() - range * acis_vector.x(), acis_point.y() - range * acis_vector.y(), acis_point.z() - range * acis_vector.z());
    SPAposition pos10(acis_point.x() + range * acis_vector.x(), acis_point.y() + range * acis_vector.y(), acis_point.z() + range * acis_vector.z());
    check_outcome(api_curve_line(pos9, pos10, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(51 * color_trans, 161 * color_trans, 201 * color_trans));  // 蓝绿 ##33A1C9
    if(result.ok()) output_ents.add(my_edge);

    // 绘制gme_fit_line
    range = 80; //直线范围，较短可以与api_fit_line对比
    straight gme_straight;
    gme_api_fit_line(point_list, gme_straight);
    SPAunit_vector gme_vector = gme_straight.direction;
    SPAposition gme_point = gme_straight.root_point;
    SPAposition pos11(gme_point.x() - range * gme_vector.x(), gme_point.y() - range * gme_vector.y(), gme_point.z() - range * gme_vector.z());
    SPAposition pos12(gme_point.x() + range * gme_vector.x(), gme_point.y() + range * gme_vector.y(), gme_point.z() + range * gme_vector.z());
    check_outcome(api_curve_line(pos11, pos12, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1, 1, 0));  // 黄 #FFFF00
    if(result.ok()) output_ents.add(my_edge);

    // 绘制point_list,以球的形式表示，改第二个参数改变球的直径
    for(int i = 0; i < point_list.size(); i++) {
        check_outcome(api_solid_sphere(point_list[i], 1, my_body));
        result = api_rh_set_entity_rgb(my_body, rgb_color(128 * color_trans, 42 * color_trans, 42 * color_trans)); // 棕色 #802A2A
        if(result.ok()) output_ents.add(my_body);
    }
    point_list.clear();
    API_END
    return result;
}