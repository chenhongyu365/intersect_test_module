/*********************************************************************
 * @file    gme_cstrapi_1_curve_spline2_example.cpp
 * @brief   gme_1_api_curve_spline2 demo
 * @details
 * @author  程红
 * @date    2024.8.14
 *********************************************************************/
#include "gme_cstrapi_1_curve_spline2_example.hxx"

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
//	  1_curve_spline2_demo 1:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    一个简单的B样条曲线，给定起点和终点的切线方向。
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 8;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(4, 5, 6));
    pos_data.push_back(SPAposition(2, 8, 9));
    pos_data.push_back(SPAposition(7, 14, 3));
    pos_data.push_back(SPAposition(10, 20, -5));
    pos_data.push_back(SPAposition(5, 10, -12));
    pos_data.push_back(SPAposition(0, 2, -15));
    pos_data.push_back(SPAposition(-3, -5, -10));
    SPAvector* start = ACIS_NEW SPAvector(-1, -1, 0);                      // 起点的切线方向
    SPAvector* end = ACIS_NEW SPAvector(0, 0, 1);                          // 终点的切线方向
    double* params = new double[]{-2, -0.23, 2.3, 3.4, 6, 7.4, 8.2, 9.3};  // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge));
    check_outcome(gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge));

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 0.2, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 0.2, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 0.2, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 0.2, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_curve_spline2_demo 2:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    一个简单的B样条曲线，无起点和终点的切线方向。
//
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 8;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(4, 5, 6));
    pos_data.push_back(SPAposition(2, 8, 9));
    pos_data.push_back(SPAposition(7, 14, 3));
    pos_data.push_back(SPAposition(10, 20, -5));
    pos_data.push_back(SPAposition(5, 10, -12));
    pos_data.push_back(SPAposition(0, 2, -15));
    pos_data.push_back(SPAposition(-3, -5, -10));
    SPAvector* start = nullptr;                                            // 起点切线不定
    SPAvector* end = nullptr;                                              // 终点切线不定
    double* params = new double[]{-2, -0.23, 2.3, 3.4, 6, 7.4, 8.2, 9.3};  // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge));
    check_outcome(gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge));

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 0.2, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 0.2, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 0.2, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 0.2, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_curve_spline2_demo 3:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    给定起点和终点的切线方向，由重合的两个控制点生成一条闭合B样条曲线。
//
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 2;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(0, 0, 0));
    SPAvector* start = ACIS_NEW SPAvector(1, 1, 0);  // 起点的切线方向
    SPAvector* end = ACIS_NEW SPAvector(0, -1, 0);   // 终点的切线方向
    double* params = new double[]{-2, 9.3};          // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge));
    check_outcome(gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge));

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 0.1, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 0.1, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 0.1, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 0.1, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_curve_spline2_demo 4:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    不给定起点和终点的切线方向，由重合的两个控制点，生成edge存在。
//    acis为绿色edge、gme为蓝色edge，acis起点终点用球体可视化，标绿、gme起点终点用球体可视化，标红。
//
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 2;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(0, 0, 0));
    SPAvector* start = nullptr;              // 起点切线不定
    SPAvector* end = nullptr;                // 终点切线不定
    double* params = new double[]{-2, 9.3};  // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge);
    gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge);

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 0.1, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 0.1, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 0.1, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 0.1, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_curve_spline2_demo 5:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    一个常规的闭合B样条曲线，给定起点和终点的切线方向。
//    acis为绿色edge、gme为蓝色edge，acis起点终点标绿、gme起点终点标红。
//
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 8;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(4, 5, 6));
    pos_data.push_back(SPAposition(2, 8, 9));
    pos_data.push_back(SPAposition(7, 14, 3));
    pos_data.push_back(SPAposition(10, 20, -5));
    pos_data.push_back(SPAposition(5, 10, -12));
    pos_data.push_back(SPAposition(0, 2, -15));
    pos_data.push_back(SPAposition(0, 0, 0));
    SPAvector* start = ACIS_NEW SPAvector(1, 1, 0);                        // 起点的切线方向
    SPAvector* end = ACIS_NEW SPAvector(-1, -1, 0);                        // 终点的切线方向
    double* params = new double[]{-2, -0.23, 2.3, 3.4, 6, 7.4, 8.2, 9.3};  // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge));
    check_outcome(gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge));

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 0.3, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 0.3, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 0.3, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 0.3, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_curve_spline2_demo 6:
//
// APIs:
//    gme_1_api_curve_spline2
//
// Description:
//    一个突变的B样条曲线，给定起点和终点的切线方向。
//    acis为绿色edge、gme为蓝色edge，acis起点终点标绿、gme起点终点标红。
//
// **********************************************************************************

outcome aei_1_CURVE_SPLINE2_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    EDGE* acis_edge = nullptr;   // 用于接收acis api创建的edge
    EDGE* gme_edge = nullptr;    // 用于接收gme api创建的edge
    BODY* acis_start = nullptr;  // 用于存储acis起点body
    BODY* acis_end = nullptr;    // 用于存储acis终点body
    BODY* gme_start = nullptr;   // 用于存储gme起点body
    BODY* gme_end = nullptr;     // 用于存储gme终点

    int numpts = 8;  // 控制点个数

    std::vector<SPAposition> pos_data;  // 控制点数据
    pos_data.push_back(SPAposition(0, 0, 0));
    pos_data.push_back(SPAposition(4e2, 50, 600));
    pos_data.push_back(SPAposition(2e5, 8e3, 90));
    pos_data.push_back(SPAposition(700, 140, 320));
    pos_data.push_back(SPAposition(10, 20, -5));
    pos_data.push_back(SPAposition(5e5, 1e3, -12e2));
    pos_data.push_back(SPAposition(0, 2, -15));
    pos_data.push_back(SPAposition(-3e5, -5e5, -10e5));
    SPAvector* start = ACIS_NEW SPAvector(1, 1, 0);                        // 起点的切线方向
    SPAvector* end = ACIS_NEW SPAvector(-1, -1, 0);                        // 终点的切线方向
    double* params = new double[]{-2, -0.23, 2.3, 3.4, 6, 7.4, 8.2, 9.3};  // 参数数据，每个点一个

    rgb_color green(0, 1, 0);  // 绿
    rgb_color blue(0, 0, 1);   // 蓝

    check_outcome(api_curve_spline2(numpts, pos_data.data(), params, start, end, acis_edge));
    check_outcome(gme_1_api_curve_spline2(numpts, pos_data.data(), params, start, end, gme_edge));

    // 在起点绘制球体，并result、output呈现，标注acis绿色起点
    api_solid_sphere(gme_edge->start_pos(), 1, acis_start);
    result = api_rh_set_entity_rgb(acis_start, green);
    if(result.ok()) {
        output_ents.add(acis_start);
    }
    // 在终点绘制球体，并result、output呈现，标注acis绿色终点
    api_solid_sphere(acis_edge->end_pos(), 1, acis_end);
    result = api_rh_set_entity_rgb(acis_end, green);
    if(result.ok()) {
        output_ents.add(acis_end);
    }

    // 在起点绘制球体，并result、output呈现，标注gme蓝色起点
    api_solid_sphere(gme_edge->start_pos(), 1, gme_start);
    result = api_rh_set_entity_rgb(gme_start, blue);
    if(result.ok()) {
        output_ents.add(gme_start);
    }
    // 在起点绘制球体，并result、output呈现，标注gme蓝色终点
    api_solid_sphere(gme_edge->end_pos(), 1, gme_end);
    result = api_rh_set_entity_rgb(gme_end, blue);
    if(result.ok()) {
        output_ents.add(gme_end);
    }

    // 分别用不同颜色显示acis和gme的edge
    result = api_rh_set_entity_rgb(acis_edge, green);  // 绿
    if(result.ok()) output_ents.add(acis_edge);
    // api_rh_create_material
    result = api_rh_set_entity_rgb(gme_edge, blue);  // 蓝
    if(result.ok()) output_ents.add(gme_edge);
    // 不支持直接调整EDGE的透明度，如果只看得到蓝色的（gme_edge），说明和acis的结果一致

    API_END
    return result;
}
