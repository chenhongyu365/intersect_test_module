/*********************************************************************
 * @file    gme_cstrapi_fit_plane_example.cpp
 * @brief	为随机生成的散点拟合一个平面，生成的黄色平面为api_fit_plane，蓝绿平面为gme_fit_plane
 * @details
 * @author  linchforever
 * @date    2023.8.5
 *********************************************************************/
#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/pladef.hxx"
#include "acis/rnd_api.hxx"
#include "gme_cstrapi_fit_line_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  fit_plane_demo:
//
// APIs:
//    gme_api_fit_plane
//
// Description:
//	  为随机生成的散点拟合一个平面
//
// **********************************************************************************
outcome aei_FIT_PLANE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* my_face = ACIS_NEW FACE;
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
    for(int i = 0; i < 16; i++) {
        // 根据生成随机数生成点
        SPAposition temp_pos;
        temp_pos.set_x(u(e));
        temp_pos.set_y(u(e));
        temp_pos.set_z(u(e));
        point_list.push_back(temp_pos);
    }

    SPApar_pos acis_vecpoint = SPApar_pos(1.0, 1.0);
    // 绘制api_fit_plane
    plane p1;
    api_fit_plane(point_list, p1);
    SPAposition acis_point;
    p1.eval(acis_vecpoint, acis_point);
    SPAunit_vector acis_vector_ori = p1.point_normal(acis_point);
    SPAunit_vector* acis_vector = &acis_vector_ori;

    SPAposition pos9(acis_point.x(), acis_point.y(), acis_point.z());
    SPAposition pos10(acis_point.x() + 100 * acis_vector->x(), acis_point.y() + 100 * acis_vector->y(), acis_point.z() + 100 * acis_vector->z());
    check_outcome(api_curve_line(pos9, pos10, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1, 1, 0));  // 黄
    if(result.ok()) output_ents.add(my_edge);

    check_outcome(api_face_plane(acis_point, 100, 100, (SPAvector*)acis_vector, my_face));
    result = api_rh_set_entity_rgb(my_face, rgb_color(1, 1, 0));  // 黄
    if(result.ok()) output_ents.add(my_face);

    // 绘制gme_fit_plane
    SPApar_pos gme_vecpoint = SPApar_pos(5.0, 5.0);
    plane p2;
    gme_api_fit_plane(point_list, p2);
    SPAposition gme_point;
    p2.eval(gme_vecpoint, gme_point);
    SPAunit_vector gme_vector_ori = p2.point_normal(gme_point);
    SPAunit_vector* gme_vector = &gme_vector_ori;

    SPAposition pos11(gme_point.x(), gme_point.y(), gme_point.z());
    SPAposition pos12(gme_point.x() + 100 * gme_vector->x(), gme_point.y() + 100 * gme_vector->y(), gme_point.z() + 100 * gme_vector->z());
    check_outcome(api_curve_line(pos11, pos12, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1, 1));  // 蓝绿
    if(result.ok()) output_ents.add(my_edge);

    check_outcome(api_face_plane(gme_point, 100, 100, (SPAvector*)gme_vector, my_face));
    result = api_rh_set_entity_rgb(my_face, rgb_color(0, 1, 1));  // 蓝绿
    if(result.ok()) output_ents.add(my_face);

    // 绘制point_list,以球的形式表示
    for(int i = 0; i < point_list.size(); i++) {
        check_outcome(api_solid_sphere(point_list[i], 1, my_body));
        result = api_rh_set_entity_rgb(my_body, rgb_color(128 * color_trans, 42 * color_trans, 42 * color_trans));
        if(result.ok()) output_ents.add(my_body);
    }
    point_list.clear();
    API_END
    return result;
}
