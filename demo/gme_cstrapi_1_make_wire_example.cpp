/*********************************************************************
 * @file    gme_cstrapi_1_make_wire_example.cpp
 * @brief   gme_1_api_make_wire demo
 * @details
 * @author  杨袁瑞
 * @date    2023.7.25
 *********************************************************************/
#include "gme_cstrapi_1_make_wire_example.hxx"

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
//	  1_wire_demo 1:
//
// APIs:
//    gme_1_api_make_wire
//
// Description:
//	  一个简单的正方形的wire body(闭合)，位于xOy平面上
//
// **********************************************************************************
outcome aei_1_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    // EDGE* axis_edge = nullptr;  // 用于展示坐标系
    BODY* in_body = nullptr;   // 初始的body
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    // 构建正方形的5个顶点数组
    const int length_pts = 5;
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
    array_pts[3].set_y(3);
    array_pts[3].set_z(0);
    array_pts[4].set_x(0);
    array_pts[4].set_y(0);
    array_pts[4].set_z(0);

    // 生成wire_body
    check_outcome(gme_1_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_wire_demo 2:
//
// APIs:
//    gme_1_api_make_wire
//
// Description:
//	  一个凹凸的由6个顶点构成的5条边
//
// **********************************************************************************
outcome aei_1_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* in_body = nullptr;   // 初始的body
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN

    // 构建顶点数组
    const int length_pts = 6;
    SPAposition p1(0.0, 0.0, 0.0);
    SPAposition p2(3.0, 0.0, 0.5);
    SPAposition p3(4.0, 2.0, 1.0);
    SPAposition p4(2.0, 4.0, 0.5);
    SPAposition p5(0.0, 3.0, -0.5);
    SPAposition p6(-1.0, 1.0, -1.0);
    SPAposition array_pts[length_pts] = {p1, p2, p3, p4, p5, p6};
    // 生成wire_body
    check_outcome(gme_1_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_wire_demo 3:
//
// APIs:
//    gme_1_api_make_wire
//
// Description:
//	  1000个点的近似圆
//
// **********************************************************************************
outcome aei_1_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* in_body = nullptr;   // 初始的body
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN

    // 圆的参数
    double r = 10.0;                      // 半径
    double cx = 0.0, cy = 0.0, cz = 0.0;  // 圆心位置

    // 构建顶点数组
    const int length_pts = 1000;  // 点的数量
    SPAposition array_pts[length_pts];
    // 生成点
    for(int i = 0; i < length_pts; ++i) {
        double theta = (2.0 * M_PI * i) / length_pts;  // 当前点的角度
        double x = cx + r * cos(theta);                // 计算x坐标
        double y = cy + r * sin(theta);                // 计算y坐标
        double z = cz;                                 // z坐标保持不变（假设圆在XY平面上）
        array_pts[i].set_x(x);
        array_pts[i].set_y(y);
        array_pts[i].set_z(z);
    }

    // 生成wire_body
    check_outcome(gme_1_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_wire_demo 4:
//
// APIs:
//    gme_1_api_make_wire
//
// Description:
//	  在已有的正方体上附加新的wire body
//
// **********************************************************************************
outcome aei_1_WIRE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* in_body = nullptr;   // 初始的body
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    // 创建一个正方体，放入in_body里
    check_outcome(gme_api_make_cuboid(4.0, 4.0, 4.0, in_body));

    // 构建顶点数组，用来创建一个与正方体的第一卦限顶点接触的wire body
    const int length_pts = 4;  // 点的数量
    SPAposition p1(2.0, 2.0, 2.0);
    SPAposition p2(4.0, 3.0, 1.0);
    SPAposition p3(1.0, 3.0, 4.0);
    SPAposition p4(2.0, 2.0, 2.0);
    SPAposition array_pts[length_pts] = {p1, p2, p3, p4};

    // 生成wire_body
    check_outcome(gme_1_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}
