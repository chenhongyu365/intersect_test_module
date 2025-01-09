/*********************************************************************
 * @file    gme_cstrapi_2_api_make_wire_example.cpp
 * @brief   gme_api_make_wire_2 demo
 * @details
 * @author  caoliang
 * @date    2024.8.20
 *********************************************************************/

#include "gme_cstrapi_2_api_make_wire_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/strdef.hxx"

outcome aei_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* in_body = nullptr;   // 初始的body
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const int length_pts = 1;
    SPAposition p1(0.0, 0.0, 10.0);
    SPAposition array_pts[length_pts] = {p1};
    check_outcome(gme_2_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(255.0, 0.0, 0.0));
    if(result.ok()) {
        output_ents.add(gme_body);
    }
    API_END

    return result;
}

outcome aei_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* in_body = nullptr;
    BODY* gme_body = nullptr;

    API_BEGIN
    const int length_pts = 2;
    SPAposition p1(0.0, 0.0, 0.0);
    SPAposition p2(0.0, 0.0, 10.0);
    SPAposition array_pts[length_pts] = {p1, p2};
    check_outcome(gme_2_api_make_wire(in_body, length_pts, array_pts, gme_body));
    if(result.ok()) {
        output_ents.add(gme_body);
    }
    API_END

    return result;
}

outcome aei_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* in_body = nullptr;
    BODY* gme_body = nullptr;
    BODY* acis_body = nullptr;

    API_BEGIN
    const int length_pts = 4;
    SPAposition array_pts[length_pts];
    array_pts[0].set_x(0);
    array_pts[0].set_y(0);
    array_pts[0].set_z(0);
    array_pts[1].set_x(3);
    array_pts[1].set_y(0);
    array_pts[1].set_z(0);
    array_pts[2].set_x(3);
    array_pts[2].set_y(3);
    array_pts[2].set_z(0);
    array_pts[3].set_x(0);
    array_pts[3].set_y(0);
    array_pts[3].set_z(0);
    check_outcome(gme_2_api_make_wire(in_body, length_pts, array_pts, gme_body));
    outcome result_gme = api_rh_set_entity_rgb(gme_body, rgb_color(255.0, 0.0, 0.0));
    check_outcome(api_make_wire(in_body, length_pts, array_pts, acis_body));
    outcome result_acis = api_rh_set_entity_rgb(acis_body, rgb_color(0.0, 255.0, 0.0));
    if(result_gme.ok()) {
        output_ents.add(gme_body);
    }
    /*if(result_acis.ok()) {
        output_ents.add(acis_body);
    }*/
    API_END

    return result;
}
outcome aei_WIRE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* in_body = nullptr;
    BODY* gme_body = nullptr;

    API_BEGIN

    // 圆的参数--半径&&圆心
    double r = 10.0;
    double cx = 0.0, cy = 0.0, cz = 0.0;

    // 构建顶点数组
    const int length_pts = 1000;
    SPAposition array_pts[length_pts];
    // 生成点
    for(int i = 0; i < length_pts; ++i) {
        double theta = (2.0 * M_PI * i) / length_pts;  // 当前点的角度
        double x = cx + r * cos(theta);                // 计算x坐标
        double y = cy + r * sin(theta);                // 计算y坐标
        double z = cz;                                 // z坐标保持不变
        array_pts[i].set_x(x);
        array_pts[i].set_y(y);
        array_pts[i].set_z(z);
    }
    check_outcome(gme_2_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(0.0, 0.0, 255.0));
    if(result.ok()) {
        output_ents.add(gme_body);
    }
    API_END

    return result;
}
