/*********************************************************************
 * @file    gme_cstrapi_curve_spline2_example.cpp
 * @brief   gme_api_curve_spline2 demo
 * @details
 * @author  杨袁瑞
 * @date    2023.8.2
 *********************************************************************/
#include "gme_cstrapi_curve_spline2_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/spline.hxx"
#include "acis/strdef.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_spline2_demo 1:
//
// APIs:
//    gme_api_curve_spline2
//
// Description:
//    一个简单的B样条曲线，给定起点和终点的切线方向
//
// **********************************************************************************
outcome aei_CURVE_SPLINE2_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;  // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;   // 用于接收gme api创建的edge

    int numpts = 7;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(2, 3, 0));
    pos_data.push_back(SPAposition(5, 5, -1));
    pos_data.push_back(SPAposition(7, 6, 0));
    pos_data.push_back(SPAposition(9, 5, 1));
    pos_data.push_back(SPAposition(11, 2, -1));
    pos_data.push_back(SPAposition(13, 0, 0));
    SPAvector start = SPAvector(1, 1, 0);              // 起点的切线方向
    SPAvector end = SPAvector(-1, -1, 0);              // 终点的切线方向
    double params[] = {0, 1, 3.33, 5.0, 8, 8.33, 10};  // 参数数据，每个点一个

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, &start, &end, acis_edge));
    check_outcome(gme_api_curve_spline2(numpts, pos_data.data(), params, &start, &end, gme_edge));

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, rgb_color(0 / 255.0, 255 / 255.0, 0 / 255.0));  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, rgb_color(0 / 255.0, 0 / 255.0, 255 / 255.0));  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致
    // api_rh_set_material_transp(output_ents, 0.6);

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_spline2_demo 2:
//
// APIs:
//    gme_api_curve_spline2
//
// Description:
//    一个简单的B样条曲线，不指定起点和终点的切线方向
//
// **********************************************************************************
outcome aei_CURVE_SPLINE2_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;  // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;   // 用于接收gme api创建的edge

    int numpts = 7;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(1, 2, 1));
    pos_data.push_back(SPAposition(3, 5, 0));
    pos_data.push_back(SPAposition(5, 6, -1));
    pos_data.push_back(SPAposition(7, 5, 0));
    pos_data.push_back(SPAposition(8, 2, 1));
    pos_data.push_back(SPAposition(10, 0, 0));
    double params[] = {-2, 0.1, 3, 5, 7.9, 8.5, 9.5};  // 参数数据，每个点一个

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, nullptr, nullptr, acis_edge));
    check_outcome(gme_api_curve_spline2(numpts, pos_data.data(), params, nullptr, nullptr, gme_edge));

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, rgb_color(0 / 255.0, 255 / 255.0, 0 / 255.0));  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    result = api_rh_set_entity_rgb(gme_edge, rgb_color(0 / 255.0, 0 / 255.0, 255 / 255.0));  // 蓝
    if(result.ok()) output_ents.add(gme_edge);

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_spline2_demo 3:
//
// APIs:
//    gme_api_curve_spline2
//
// Description:
//    一个闭合的B样条曲线
//
// **********************************************************************************
outcome aei_CURVE_SPLINE2_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;  // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;   // 用于接收gme api创建的edge

    int numpts = 7;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(2, 3, 1));
    pos_data.push_back(SPAposition(5, 5, -1));
    pos_data.push_back(SPAposition(7, 6, 0));
    pos_data.push_back(SPAposition(4, 4, 3));
    pos_data.push_back(SPAposition(-2, 2, 1));
    pos_data.push_back(SPAposition(0, 0, 0));
    SPAvector start = SPAvector(1, 0, 0);               // 起点的切线方向
    SPAvector end = SPAvector(0, 1, 0);                 // 终点的切线方向
    double params[] = {0, 0.25, 0.5, 0.75, 1, 1.5, 2};  // 参数数据，每个点一个

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, &start, &end, acis_edge));
    check_outcome(gme_api_curve_spline2(numpts, pos_data.data(), params, &start, &end, gme_edge));

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, rgb_color(0 / 255.0, 255 / 255.0, 0 / 255.0));  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    result = api_rh_set_entity_rgb(gme_edge, rgb_color(0 / 255.0, 0 / 255.0, 255 / 255.0));  // 蓝
    if(result.ok()) output_ents.add(gme_edge);

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  curve_spline2_demo 4:
//
// APIs:
//    gme_api_curve_spline2
//
// Description:
//    在输入非递增的参数的情况下，对比两边api生成结果
//
// **********************************************************************************
outcome aei_CURVE_SPLINE2_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;  // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;   // 用于接收gme api创建的edge

    int numpts = 7;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(2, 3, 0));
    pos_data.push_back(SPAposition(5, 5, -1));
    pos_data.push_back(SPAposition(7, 6, 0));
    pos_data.push_back(SPAposition(9, 5, 1));
    pos_data.push_back(SPAposition(11, 2, -1));
    pos_data.push_back(SPAposition(13, 0, 0));
    SPAvector start = SPAvector(1, 0, 0);               // 起点的切线方向
    SPAvector end = SPAvector(-1, -1, 0);               // 终点的切线方向
    double params[] = {0, 1.1, 1.5, 0.2, 0.3, 0.1, 1};  // 参数数据，每个点一个

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, &start, &end, acis_edge));
    check_outcome(gme_api_curve_spline2(numpts, pos_data.data(), params, &start, &end, gme_edge));

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, rgb_color(0 / 255.0, 255 / 255.0, 0 / 255.0));  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    result = api_rh_set_entity_rgb(gme_edge, rgb_color(0 / 255.0, 0 / 255.0, 255 / 255.0));  // 蓝
    if(result.ok()) output_ents.add(gme_edge);

    API_END

    return result;
}
