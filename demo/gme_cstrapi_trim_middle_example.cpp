/*********************************************************************
 * @file   gme_api_trim_middle_example.cpp
 * @brief
 * @details
 * @author  linchforever
 * @date    2023.8.10
 *********************************************************************/
#include <ctime>
#include <random>
#include <vector>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/entwray.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trim_middle_demo:  TRIM_MIDDLE_DEMO1
//
// APIs:
//    gme_api_trim_middle
//
// Description:
//	  根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
// **********************************************************************************
outcome aei_TRIM_MIDDLE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* crv_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;

    API_BEGIN
    api_curve_bezier(SPAposition(-9.0, 2.0, 0.0), SPAposition(0.0, 3.0, 0.0), SPAposition(3.0, 1.0, 0.0), SPAposition(9.0, 2.0, 0.0), crv_edge);
    api_curve_bezier(SPAposition(6.0, 6.0, 0.0), SPAposition(4.0, 3.0, 0.0), SPAposition(6.0, -2.0, 0.0), SPAposition(3.0, -5.0, 0.0), trimr1_edge);
    api_curve_bezier(SPAposition(-4.0, 4.0, 0.0), SPAposition(-2.0, -4.0, 0.0), SPAposition(2.0, 9.0, 0.0), SPAposition(5.0, -1.0, 0.0), trimr2_edge);
    result = api_rh_set_entity_rgb(trimr1_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    result = api_rh_set_entity_rgb(trimr2_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 3; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    SPAposition p2 = randpoint[1];
    SPAposition p3 = randpoint[2];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    SPAunit_vector v2 = randunit_vector[1];
    SPAunit_vector v3 = randunit_vector[2];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);
    entity_with_ray e1 = entity_with_ray(trimr1_edge, p2, v2);
    entity_with_ray* trimr1 = &e1;
    entity_with_ray e2 = entity_with_ray(trimr2_edge, p3, v3);
    entity_with_ray* trimr2 = &e2;

    gme_api_trim_middle(gme_crv, NULL, trimr1, NULL, trimr2, gme_edge);
    result = api_rh_set_entity_rgb(gme_crv.entity(), rgb_color(1, 0, 0));  // 红
    if(gme_edge) {
        result = api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 1));  // 粉
        if(result.ok()) output_ents.add(gme_edge);
    }
    API_END

    if(result.ok()) {
        output_ents.add(crv_edge);
        output_ents.add(trimr1_edge);
        output_ents.add(trimr2_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trim_middle_demo:  TRIM_MIDDLE_DEMO2
//
// APIs:
//    gme_api_trim_middle
//
// Description:
//	  根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
// **********************************************************************************
outcome aei_TRIM_MIDDLE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* crv_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;

    API_BEGIN
    api_curve_line(SPAposition(-8.0, 4.0, 0.0), SPAposition(8.0, 4.0, 0.0), crv_edge);
    api_curve_line(SPAposition(4.0, 5.0, 0.0), SPAposition(4.0, -5.0, 0.0), trimr1_edge);
    api_curve_line(SPAposition(-4.0, 5.0, 0.0), SPAposition(-4.0, -5.0, 0.0), trimr2_edge);
    result = api_rh_set_entity_rgb(trimr1_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    result = api_rh_set_entity_rgb(trimr2_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 3; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    SPAposition p2 = randpoint[1];
    SPAposition p3 = randpoint[2];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    SPAunit_vector v2 = randunit_vector[1];
    SPAunit_vector v3 = randunit_vector[2];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);
    entity_with_ray e1 = entity_with_ray(trimr1_edge, p2, v2);
    entity_with_ray* trimr1 = &e1;
    entity_with_ray e2 = entity_with_ray(trimr2_edge, p3, v3);
    entity_with_ray* trimr2 = &e2;

    gme_api_trim_middle(gme_crv, NULL, trimr1, NULL, trimr2, gme_edge);
    result = api_rh_set_entity_rgb(gme_crv.entity(), rgb_color(1, 0, 0));  // 红
    if(gme_edge) {
        result = api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 1));  // 粉
        if(result.ok()) output_ents.add(gme_edge);
    }
    API_END

    if(result.ok()) {
        output_ents.add(crv_edge);
        output_ents.add(trimr1_edge);
        output_ents.add(trimr2_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trim_middle_demo:  TRIM_MIDDLE_DEMO3
//
// APIs:
//    gme_api_trim_middle
//
// Description:
//	  根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
// **********************************************************************************
outcome aei_TRIM_MIDDLE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* crv_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;

    API_BEGIN
    api_curve_ellipse(SPAposition(0.0, 0.0, 0.0), SPAposition(0.0, 3.0, 0.0), 1.0, 0, 2 * M_PI, crv_edge);
    api_curve_ellipse(SPAposition(4.0, -0.5, 0.0), SPAposition(2.5, -0.5, 0.0), 1.0, 0, 2 * M_PI, trimr1_edge);
    api_curve_ellipse(SPAposition(-8.0, 4.0, 0.0), SPAposition(-4.0, -1.0, 0.0), 2, 1.5, 2 * M_PI, trimr2_edge);
    result = api_rh_set_entity_rgb(trimr1_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    result = api_rh_set_entity_rgb(trimr2_edge, rgb_color(0.7, 0.7, 0.7));  // 灰
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 3; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    SPAposition p2 = randpoint[1];
    SPAposition p3 = randpoint[2];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    SPAunit_vector v2 = randunit_vector[1];
    SPAunit_vector v3 = randunit_vector[2];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);
    entity_with_ray e1 = entity_with_ray(trimr1_edge, p2, v2);
    entity_with_ray* trimr1 = &e1;
    entity_with_ray e2 = entity_with_ray(trimr2_edge, p3, v3);
    entity_with_ray* trimr2 = &e2;

    gme_api_trim_middle(gme_crv, NULL, trimr1, NULL, trimr2, gme_edge);
    result = api_rh_set_entity_rgb(gme_crv.entity(), rgb_color(1, 0, 0));  // 红
    if(result.ok()) output_ents.add(gme_crv.entity());
    if(gme_edge) {
        result = api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 1));  // 粉
        if(result.ok()) output_ents.add(gme_edge);
    }

    API_END

    if(result.ok()) {
        output_ents.add(crv_edge);
        output_ents.add(trimr1_edge);
        output_ents.add(trimr2_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trim_middle_demo:  TRIM_MIDDLE_DEMO4
//
// APIs:
//    gme_api_trim_middle
//
// Description:
//	  根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
// **********************************************************************************
outcome aei_TRIM_MIDDLE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* crv_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;
    BODY* my_body = nullptr;

    API_BEGIN
    api_edge_helix(SPAposition(0.0, 0.0, 1.0), SPAposition(0.0, 1, 1.0), SPAvector(1.0, 0.0, 0.0), 1, 0.1, TRUE, crv_edge);
    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-20.5, 20.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-20.5, 20.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-20.5, 20.5);  // 点z轴区间
    std::uniform_real_distribution<double> x_v(-20.5, 20.5);  // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-20.5, 20.5);  // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-20.5, 20.5);  // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 1; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);

    SPAposition pt1 = SPAposition(0.4, 0.5, 0.0);
    check_outcome(api_solid_sphere(pt1, 0.03, my_body));
    result = api_rh_set_entity_rgb(my_body, rgb_color(128 / 255, 42 / 255, 42 / 255));  // 棕色 #802A2A
    if(result.ok()) output_ents.add(my_body);
    SPAposition* trim_pt1 = &pt1;
    SPAposition pt2 = SPAposition(-0.1, 0.2, 0.0);
    check_outcome(api_solid_sphere(pt2, 0.03, my_body));
    result = api_rh_set_entity_rgb(my_body, rgb_color(128 / 255, 42 / 255, 42 / 255));  // 棕色 #802A2A
    if(result.ok()) output_ents.add(my_body);
    SPAposition* trim_pt2 = &pt2;

    gme_api_trim_middle(gme_crv, trim_pt1, NULL, trim_pt2, NULL, gme_edge);
    result = api_rh_set_entity_rgb(gme_crv.entity(), rgb_color(1, 0, 0));  // 红
    if(gme_edge) {
        result = api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 1));  // 粉
        if(result.ok()) output_ents.add(gme_edge);
    }
    API_END

    if(result.ok()) {
        output_ents.add(crv_edge);
        output_ents.add(trimr1_edge);
        output_ents.add(trimr2_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  trim_middle_demo:  TRIM_MIDDLE_DEMO5
//
// APIs:
//    gme_api_trim_middle
//
// Description:
//	  根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
// **********************************************************************************
outcome aei_TRIM_MIDDLE_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* crv_edge = nullptr;
    EDGE* gme_edge = nullptr;
    EDGE* trimr1_edge = nullptr;
    EDGE* trimr2_edge = nullptr;
    BODY* my_body = nullptr;

    API_BEGIN
    api_curve_bezier(SPAposition(-9.0, 2.0, 0.0), SPAposition(0.0, 3.0, 0.0), SPAposition(3.0, 1.0, 0.0), SPAposition(9.0, 2.0, 0.0), crv_edge);

    // 点坐标
    SPAposition_vector randpoint;
    std::vector<SPAunit_vector> randunit_vector;
    std::default_random_engine e;
    std::uniform_real_distribution<double> x_p(-10.5, 10.5);  // 点x轴区间
    std::uniform_real_distribution<double> y_p(-10.5, 10.5);  // 点y轴区间
    std::uniform_real_distribution<double> z_p(-5, 5);        // 点z轴区间
    std::uniform_real_distribution<double> x_v(-1, 1);        // 向量x轴区间
    std::uniform_real_distribution<double> y_v(-1, 1);        // 向量y轴区间
    std::uniform_real_distribution<double> z_v(-1, 1);        // 向量z轴区间
    e.seed(time(0));
    for(int i = 0; i < 1; i++) {
        SPAposition tmp_pos;
        tmp_pos.set_x(x_p(e));
        tmp_pos.set_y(y_p(e));
        tmp_pos.set_z(z_p(e));
        randpoint.push_back(tmp_pos);
        SPAunit_vector tmp_vec;
        tmp_vec.set_x(x_v(e));
        tmp_vec.set_y(y_v(e));
        tmp_vec.set_z(z_v(e));
        randunit_vector.push_back(tmp_vec);
    }
    // pick_ray的起始点
    SPAposition p1 = randpoint[0];
    // pick_ray的方向
    SPAunit_vector v1 = randunit_vector[0];
    // entity_with_ray
    entity_with_ray gme_crv = entity_with_ray(crv_edge, p1, v1);

    SPAposition pt1 = SPAposition(3.0, 0.0, 0.0);
    check_outcome(api_solid_sphere(pt1, 0.1, my_body));
    result = api_rh_set_entity_rgb(my_body, rgb_color(128 / 255, 42 / 255, 42 / 255));  // 棕色 #802A2A
    if(result.ok()) output_ents.add(my_body);
    SPAposition* trim_pt1 = &pt1;
    SPAposition pt2 = SPAposition(-2.0, 1.0, 0.0);
    check_outcome(api_solid_sphere(pt2, 0.1, my_body));
    result = api_rh_set_entity_rgb(my_body, rgb_color(128 / 255, 42 / 255, 42 / 255));  // 棕色 #802A2A
    if(result.ok()) output_ents.add(my_body);
    SPAposition* trim_pt2 = &pt2;

    gme_api_trim_middle(gme_crv, trim_pt1, NULL, trim_pt2, NULL, gme_edge);
    result = api_rh_set_entity_rgb(gme_crv.entity(), rgb_color(1, 0, 0));  // 红
    if(gme_edge) {
        result = api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 1));  // 粉
        if(result.ok()) output_ents.add(gme_edge);
    }
    API_END

    if(result.ok()) {
        output_ents.add(crv_edge);
        output_ents.add(trimr1_edge);
        output_ents.add(trimr2_edge);
    }
    return result;
}