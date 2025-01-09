/*********************************************************************
 * @file    spd_ent11_example.cpp
 * @brief   HD_PEL_ENT11 demo
 * @details
 * @author  全志成
 * @date    2023.7.24
 *********************************************************************/
#include "spd_ent11_example.hxx"

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "access.hpp"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，正常构建，中心角大于π小于2π
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {2, 1, 1};						// 中心点坐标
    double w[3] = {0.88, -0.07, 0};                 // 中心线法向 单位向量
    w[2] = sqrt((1 - w[0] * w[0] - w[1] * w[1]));   // 计算w[2]值，使w为单位向量
    double u[3] = {1.8, -1.45, 0};                  // 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 6;									// 柱体内半径
    double a = 1.56 * M_PI;							// 中心角 弧度
    double h = 10;									// 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;					// 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(238 * color_trans, 92 * color_trans, 66 * color_trans));  // Tomato2 #EE5C42
    if(result.ok()) output_ents.add(body);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，正常构建，中心角大于0小于π
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {1, 2, 3};						// 中心点坐标
    double w[3] = {0.65, -0.37, 0};					// 中心线法向 单位向量
    w[2] = sqrt((1 - w[0] * w[0] - w[1] * w[1]));   // 计算w[2]值，使w为单位向量
    double u[3] = {2.6, 1, 0};						// 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 6;									// 柱体内半径
    double a = 0.67 * M_PI;							// 中心角 弧度
    double h = 3;									// 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;					// 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(238 * color_trans, 126 * color_trans, 173 * color_trans));  // Pink1 #FFB5C5
    if(result.ok()) output_ents.add(body);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，传入参数h极小，需要大于SPAresabs
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {1, 2, 3};                        // 中心点坐标
    double w[3] = {-0.17, 0.78, 0};                 // 中心线法向 单位向量
    w[2] = sqrt((1 - w[0] * w[0] - w[1] * w[1]));   // 计算w[2]值，使w为单位向量
    double u[3] = {1.5, -2.6, 0};                   // 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 6.5;                                 // 柱体内半径
    double a = 1.3 * M_PI;							// 中心角 弧度
    double h = 20 * SPAresabs;                      // 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;   				// 用于计算rgb颜色                                                                              // 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(205 * color_trans, 104 * color_trans, 57 * color_trans));  // Sienna3 #CD6839
    if(result.ok()) output_ents.add(body);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，a极小，需要大于等于一倍容差SPAresabs
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {1.2, -3.6, 2.3};                 // 中心点坐标
    double w[3] = {0.55, -0.66, 0};                 // 中心线法向 单位向量
    w[2] = -sqrt((1 - w[0] * w[0] - w[1] * w[1]));  // 计算w[2]值，使w为单位向量
    double u[3] = {-0.7, 0.53, 0};                  // 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 4.6;                                 // 柱体内半径
    double a = 20 * SPAresabs;                       // 中心角 弧度
    double h = 6.5;                                 // 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;                 // 用于计算rgb颜色                                                                              // 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(255 * color_trans, 251 * color_trans, 0 * color_trans));  // Gold1	#FFD700
    if(result.ok()) output_ents.add(body);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，传入角度a = 2π
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {-2, 2, -3};                      // 中心点坐标
    double w[3] = {0.33, 0.46, 0};                  // 中心线法向 单位向量
    w[2] = sqrt((1 - w[0] * w[0] - w[1] * w[1]));   // 计算w[2]值，使w为单位向量
    double u[3] = {-4, 3, 0};                       // 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 8;                                   // 柱体内半径
    double a = 2.5 * M_PI;							// 中心角 弧度
    double h = 12;                                  // 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;                 // 用于计算rgb颜色                                                                                  // 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(46 * color_trans, 139 * color_trans, 87 * color_trans));  // SeaGreen #2E8B57
    output_ents.add(body);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT11
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT11.
//    空心圆柱片实体，厚度极小，半径r减去u[3]的模长需要大于容差
// **********************************************************************************
outcome aei_HD_PEL_ENT11_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    ENTITY* ent = nullptr;
    EDGE* my_edge = ACIS_NEW EDGE;
    BODY* my_body = ACIS_NEW BODY;
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 10;  // 坐标系横坐标范围
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

    double p[3] = {0, 0, 0};                        // 中心点坐标
    double w[3] = {0, 0, 1};						// 中心线法向 单位向量
    w[2] = sqrt((1 - w[0] * w[0] - w[1] * w[1]));   // 计算w[2]值，使w为单位向量
    double u[3] = {5, 0, 0};                        // 开始轴方向
    u[2] = (0 - w[0] * u[0] - w[1] * u[1]) / w[2];  // 计算u[2]值，使w和u垂直
    double r = 5 + 100 * SPAresabs;                  // 柱体内半径
    double a = 2 * M_PI;							// 中心角 弧度
    double h = 12;									// 高度
    result = gme_HD_PEL_ENT11(p, w, r, u, a, h, body);
    double color_trans = 1.0 / 255;                 // 用于计算rgb颜色                                                                           // 用于计算rgb颜色
    result = api_rh_set_entity_rgb(body, rgb_color(67 * color_trans, 110 * color_trans, 238 * color_trans));  // 	RoyalBlue2	#436EEE
    if(result.ok()) output_ents.add(body);
    API_END
    return result;
}