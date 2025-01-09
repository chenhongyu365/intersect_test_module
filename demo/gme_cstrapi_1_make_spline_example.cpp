/*********************************************************************
 * @file    gme_cstrapi_1_make_spline_example.cpp
 * @brief   gme_1_api_make_spline demo
 * @details
 * @author  杨袁瑞
 * @date    2023.7.30
 *********************************************************************/
#include "gme_cstrapi_1_make_spline_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/spline.hxx"
#include "acis/sps3srtn.hxx"
#include "acis/strdef.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_spline_demo 1:
//
// APIs:
//    gme_1_api_make_spline
//
// Description:
//    一个波浪形的曲面
//
// **********************************************************************************
outcome aei_1_SPLINE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    // 构建spline
    const int num_u = 5;                  // u方向点个数
    const int num_v = 5;                  // v方向点个数
    std::vector<SPAposition> pts;         // 控制点数组, 先给出一行u方向的控制点, 然后是下一个v方向的一行u方向控制点
    std::vector<SPAunit_vector> uvec_us;  // u方向起始切线单位向量数组，长度等于v方向点个数
    std::vector<SPAunit_vector> uvec_ue;  // u方向结束切线单位向量数组，长度等于v方向点个数
    std::vector<SPAunit_vector> uvec_vs;  // v方向起始切线单位向量数组，长度等于u方向点个数
    std::vector<SPAunit_vector> uvec_ve;  // v方向结束切线单位向量数组，长度等于u方向点个数

    // 控制点 (生成有波浪形的曲面)
    for(int j = 0; j < num_v; ++j) {
        for(int i = 0; i < num_u; ++i) {
            double x = i;
            double y = j;
            double z = std::sin(x + y);  // 波浪形的z值
            pts.emplace_back(x, y, z);
        }
    }

    // bs3_surface bs3_surf = bs3_surface_intp(num_u, num_v, pts.data(), uvec_us.data(), uvec_ue.data(), uvec_vs.data(), uvec_ve.data());
    bs3_surface bs3_surf = bs3_surface_intp(num_u, num_v, pts.data(), NULL, NULL, NULL, NULL);
    spline this_spline(bs3_surf);
    // 生成单侧面BODY
    check_outcome(gme_1_api_make_spline(this_spline, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_spline_demo 2:
//
// APIs:
//    gme_1_api_make_spline
//
// Description:
//    一个类似椭球圆顶的曲面
//
// **********************************************************************************
outcome aei_1_SPLINE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    // 构建spline
    const int num_u = 5;                  // u方向点个数
    const int num_v = 5;                  // v方向点个数
    std::vector<SPAposition> pts;         // 控制点数组, 先给出一行u方向的控制点, 然后是下一个v方向的一行u方向控制点
    std::vector<SPAunit_vector> uvec_us;  // u方向起始切线单位向量数组，长度等于v方向点个数
    std::vector<SPAunit_vector> uvec_ue;  // u方向结束切线单位向量数组，长度等于v方向点个数
    std::vector<SPAunit_vector> uvec_vs;  // v方向起始切线单位向量数组，长度等于u方向点个数
    std::vector<SPAunit_vector> uvec_ve;  // v方向结束切线单位向量数组，长度等于u方向点个数

    // 椭球参数
    double a = 5.0;  // 椭球在x方向的半轴长度
    double b = 5.0;  // 椭球在y方向的半轴长度
    double c = 7.0;  // 椭球在z方向的半轴长度

    // 计算椭球顶部的控制点
    for(int j = 0; j < num_v; ++j) {
        for(int i = 0; i < num_u; ++i) {
            double u = static_cast<double>(i) / (num_u - 1);  // [0, 1] 归一化
            double v = static_cast<double>(j) / (num_v - 1);  // [0, 1] 归一化

            // 椭圆方程
            double theta = u * 2 * M_PI;    // u方向的角度
            double phi = v * (M_PI / 2.0);  // v方向的角度，确保在0到π/2范围内

            double x = a * std::cos(theta) * std::sin(phi);
            double y = b * std::sin(theta) * std::sin(phi);
            double z = c * std::cos(phi);

            pts.emplace_back(x, y, z);
        }
    }

    // bs3_surface bs3_surf = bs3_surface_intp(num_u, num_v, pts.data(), uvec_us.data(), uvec_ue.data(), uvec_vs.data(), uvec_ve.data());
    bs3_surface bs3_surf = bs3_surface_intp(num_u, num_v, pts.data(), NULL, NULL, NULL, NULL);

    std::string err_info_1 = process(result);
    spline this_spline(bs3_surf);
    // 生成单侧面BODY
    check_outcome(gme_1_api_make_spline(this_spline, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
    if(result.ok()) output_ents.add(gme_body);
    API_END

    return result;
}
