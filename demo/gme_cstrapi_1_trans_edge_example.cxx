/*********************************************************************
 * @file    gme_cstrapi_1_trans_edge_example.cxx
 * @brief   gme_1_api_trans_edge demo
 * @details
 * @author  王菲
 * @date    2024.12.3
 *********************************************************************/
#include "gme_cstrapi_1_trans_edge_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
// Title:
//    1_trans_edge_demo 1:
// APIs:
//    gme_1_api_trans_edge
// Description:
//    创建一个直线，进行平移变换
// **********************************************************************************
outcome aei_1_TRANS_EDGE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* line = NULL;
    EDGE* transformed_line = NULL;

    API_BEGIN
    // 创建直线边缘
    outcome res = api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(2, 0, 0), line);

    // 变换：平移
    SPAtransf translation_trans = translate_transf(SPAvector(0, 2, 0));
    outcome trans_res = gme_1_api_trans_edge(line, translation_trans, transformed_line, ptrAcisOpt);

    if(res.ok() && trans_res.ok()) {
        output_ents.add(transformed_line);
    }
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
// Title:
//    1_trans_edge_demo 2:
// APIs:
//    gme_1_api_trans_edge
// Description:
//    创建一个椭圆，进行缩放变换
// **********************************************************************************
outcome aei_1_TRANS_EDGE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* ellipse = NULL;
    EDGE* transformed_ellipse = NULL;

    API_BEGIN
    // 创建椭圆
    SPAposition center(0, 0, 0);     // 椭圆的中心
    SPAunit_vector normal(0, 0, 1);  // 法向量
    SPAvector major_axis(2, 0, 0);   // 长轴方向
    double radius_ratio = 0.5;       // 半径比
    double start_angle = 0;
    double end_angle = M_PI * 2;
    outcome res = api_mk_ed_ellipse(center, normal, major_axis, radius_ratio, start_angle, end_angle, ellipse);

    // 变换：缩放
    SPAtransf scale_trans = scale_transf(1.5);  // 定义缩放变换（放大1.5倍）
    outcome trans_res = gme_1_api_trans_edge(ellipse, scale_trans, transformed_ellipse, ptrAcisOpt);

    if(res.ok() && trans_res.ok()) {
        output_ents.add(transformed_ellipse);
    }
    API_END

    return result;
}
