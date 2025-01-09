/*********************************************************************
 * @file    gme_cstrapi_build_wire_example.cpp
 * @brief   gme_api_build_wire demo
 * @details
 * @author  王书瑶
 * @date    2023.11.21
 *********************************************************************/
#include "gme_cstrapi_1_api_build_wire_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/elldef.hxx"
#include "acis/law_base.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//    gme_1_api_build_wire Demo 1:
//
// APIs:
//    gme_1_api_build_wire
//
// Description:
//    初始的 in_body 是一个尺寸为 3*3*3 的立方体，需要添加一个以原点为中心、长轴为 3、短轴为 2 的闭合椭圆线框
//
// **********************************************************************************
outcome aei_1_BUILD_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ao) {
    BODY* in_body = nullptr;
    BODY* result_body = nullptr;

    API_BEGIN
    // 创建初始立方体
    api_make_cuboid(3, 3, 3, in_body);

    // 定义椭圆的参数
    SPAposition center(0, 0, 0);
    SPAunit_vector normal(0, 0, 1);
    SPAvector major_axis(3, 0, 0);
    double ratio = 2.0 / 3.0;  // 短轴与长轴之比

    // 创建椭圆曲线
    ellipse* ellipse_curve = new ellipse(center, normal, major_axis, ratio);

    // 定义点和曲线数组
    int num_points = 1;  // 闭合椭圆只需要一个点
    SPAposition* points = new SPAposition[num_points];
    points[0] = SPAposition(3, 0, 0);  // 椭圆上的一点

    curve** curves = new curve*[num_points];
    curves[0] = ellipse_curve;

    // 调用 gme_1_api_build_wire 函数
    outcome result = gme_1_api_build_wire(in_body, TRUE, num_points, points, curves, result_body, ao);

    // 清理内存
    delete curves[0];
    delete[] curves;
    delete[] points;

    API_END

    if(result.ok()) {
        output_ents.add(result_body);
    }

    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//    gme_1_api_build_wire Demo 2:
//
// APIs:
//    gme_1_api_build_wire
//
// Description:
//    初始的 in_body 为空，创建一个由多段曲线组成的开放三维螺旋线框
//
// **********************************************************************************
outcome aei_1_BUILD_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ao) {
    BODY* in_body = nullptr;  // 初始的 in_body 为空
    BODY* result_body = nullptr;

    API_BEGIN
    // 定义参数 u 的取值范围
    std::vector<double> u_values = {0.0, M_PI / 2, M_PI, 3 * M_PI / 2, 2 * M_PI};
    int num_points = u_values.size();

    // 定义点数组
    SPAposition* points = new SPAposition[num_points];

    // 定义曲线数组
    int num_curves = num_points - 1;
    curve** curves = new curve*[num_curves];

    // 定义参数化曲线表达式（螺旋线）
    std::vector<std::string> law_str = {"VEC(2*cos(u), 2*sin(u), u)", "VEC(2*cos(u), 2*sin(u), u)", "VEC(2*cos(u), 2*sin(u), u)", "VEC(2*cos(u), 2*sin(u), u)"};

    // 生成点和曲线
    for(int i = 0; i < num_curves; ++i) {
        law* lw = nullptr;
        api_str_to_law(law_str[i].c_str(), &lw);

        // 计算点
        points[i] = lw->evaluateR_P(u_values[i]);

        // 创建曲线
        curve* crv = nullptr;
        api_curve_law(lw, u_values[i], u_values[i + 1], crv);
        curves[i] = crv;

        lw->remove();  // 删除 law 对象
    }
    // 最后一个点
    law* lw = nullptr;
    api_str_to_law(law_str.back().c_str(), &lw);
    points[num_points - 1] = lw->evaluateR_P(u_values.back());
    lw->remove();

    // 调用 gme_1_api_build_wire 函数
    outcome result = gme_1_api_build_wire(in_body, FALSE, num_points, points, curves, result_body, ao);

    // 清理内存
    for(int i = 0; i < num_curves; ++i) {
        delete curves[i];
    }
    delete[] curves;
    delete[] points;

    API_END

    if(result.ok()) {
        output_ents.add(result_body);
    }

    return result;
}
