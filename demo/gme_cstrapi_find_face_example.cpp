/*********************************************************************
 * @file    gme_cstrapi_find_face_example.cpp
 * @brief   展示了寻找body中与给定单位向量和平面法向量点乘最大的平面，
 *          若有多个相同，则找平面上点p与给定单位向量点乘最大的平面
 * @details DEMO1展示立方体平面，DEMO2展示一系列随机生成的平面，DEMO3展示一系列平行平面
 * @author  全志成
 * @date    2023.8.1
 *********************************************************************/
#include "gme_cstrapi_find_face_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/acistol.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/plane.hxx"
#include "acis/rnd_api.hxx"
#include "acis/strdef.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_find_face_demo 1:
//
// APIs:
//    gme_api_find_face
//
// Description:
//	  展示找立方体body中的面
//
// **********************************************************************************
outcome aei_FIND_FACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    FACE* face = nullptr;
    EDGE* my_edge;  // 用于展示坐标系直线
    ENTITY* ent = nullptr;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e2, 1e2);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    const SPAunit_vector unit_vector(u(e), u(e), u(e));
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 100;  // 坐标系横坐标范围
    SPAposition pos0(0, 0, 0);
    SPAposition pos1(scale, 0, 0);
    SPAposition pos2(-1 * scale, 0, 0);
    check_outcome(api_curve_line(pos1, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1.0, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos2, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0.4, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos3(0, scale, 0);
    SPAposition pos4(0, -1 * scale, 0);
    check_outcome(api_curve_line(pos3, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1.0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos4, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0.4, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos5(0, 0, scale);
    SPAposition pos6(0, 0, -1 * scale);
    check_outcome(api_curve_line(pos5, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 1.0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos6, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 0.4));
    if(result.ok()) output_ents.add(my_edge);

	SPAposition pos7(100 * unit_vector.x(), 100 * unit_vector.y(), 100 * unit_vector.z());
    SPAposition pos8(-100 * unit_vector.x(), -100 * unit_vector.y(), -100 * unit_vector.z());
    check_outcome(api_curve_line(pos7, pos8, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans)); // 黄色
    if(result.ok()) output_ents.add(my_edge);
    
    api_make_cuboid(50, 50, 50, body);
    output_ents.add(body);

    gme_api_find_face(body, unit_vector, face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_find_face_demo 2:
//
// APIs:
//    gme_api_find_face
//
// Description:
//	  随机生成法向量不同的平面构成body
//
// **********************************************************************************
outcome aei_FIND_FACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    FACE* face = nullptr;
    EDGE* my_edge;  // 用于展示坐标系直线
    ENTITY* ent = nullptr;
    //  生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e5, 1e5);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    const SPAunit_vector unit_vector(u(e), u(e), u(e));
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 2e5;  // 坐标系横坐标范围
    SPAposition pos0(0, 0, 0);
    SPAposition pos1(scale, 0, 0);
    SPAposition pos2(-1 * scale, 0, 0);
    check_outcome(api_curve_line(pos1, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1.0, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos2, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0.4, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos3(0, scale, 0);
    SPAposition pos4(0, -1 * scale, 0);
    check_outcome(api_curve_line(pos3, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1.0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos4, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0.4, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos5(0, 0, scale);
    SPAposition pos6(0, 0, -1 * scale);
    check_outcome(api_curve_line(pos5, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 1.0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos6, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 0.4));
    if(result.ok()) output_ents.add(my_edge);

    SPAposition pos7(2e5 * unit_vector.x(), 2e5 * unit_vector.y(), 2e5 * unit_vector.z());
    SPAposition pos8(-2e5 * unit_vector.x(), -2e5 * unit_vector.y(), -2e5 * unit_vector.z());
    check_outcome(api_curve_line(pos7, pos8, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans));
    if(result.ok()) output_ents.add(my_edge);

	std::vector<FACE*> body_faces;
    for(int i = 0; i < 10; i++) {
		FACE* face = nullptr;
		SPAposition p1(u(e), u(e), u(e));
		SPAposition p2(u(e), u(e), u(e));
		SPAposition p3(u(e), u(e), u(e));
		api_make_plface(p1, p2, p3, face);  // 构建一个法向量为(0, 0, 1)的plane_face
		SPAunit_vector temp_vector = dynamic_cast<PLANE*>(face->geometry())->normal();
		body_faces.push_back(face);
    }
    for(int i = 0; i < body_faces.size() - 1; ++i) {
		int j = (i + 1) % body_faces.size();
		body_faces[i]->set_next(body_faces[j]);
    }
    // 构建SHELL, LUMP, BODY
    SHELL* shell = ACIS_NEW SHELL(body_faces[0], nullptr, nullptr);
    LUMP* lump = ACIS_NEW LUMP(shell, nullptr);
    body = ACIS_NEW BODY(lump);
    output_ents.add(body);

    gme_api_find_face(body, unit_vector, face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    API_END
    return result;	
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_find_face_demo 3:
//
// APIs:
//    gme_api_find_face
//
// Description:
//	  随机生成法向量相同的平行平面构成body
//
// **********************************************************************************
outcome aei_FIND_FACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    FACE* face = nullptr;
    EDGE* my_edge;  // 用于展示坐标系直线
    ENTITY* ent = nullptr;
    //  生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e5, 1e5);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    const SPAunit_vector unit_vector(u(e), u(e), u(e));
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 2e5;  // 坐标系横坐标范围
    SPAposition pos0(0, 0, 0);
    SPAposition pos1(scale, 0, 0);
    SPAposition pos2(-1 * scale, 0, 0);
    check_outcome(api_curve_line(pos1, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1.0, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos2, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0.4, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos3(0, scale, 0);
    SPAposition pos4(0, -1 * scale, 0);
    check_outcome(api_curve_line(pos3, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1.0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos4, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0.4, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos5(0, 0, scale);
    SPAposition pos6(0, 0, -1 * scale);
    check_outcome(api_curve_line(pos5, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 1.0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos6, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 0.4));
    if(result.ok()) output_ents.add(my_edge);

    SPAposition pos7(2.5e5 * unit_vector.x(), 2.5e5 * unit_vector.y(), 2.5e5 * unit_vector.z());
    SPAposition pos8(-2.5e5 * unit_vector.x(), -2.5e5 * unit_vector.y(), -2.5e5 * unit_vector.z());
    check_outcome(api_curve_line(pos7, pos8, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans));
    if(result.ok()) output_ents.add(my_edge);

	std::vector<FACE*> body_faces;
    double same_x = -1e5;
    for(int i = 0; i < 100; i++) {
       FACE* face = nullptr;
       SPAposition p1(same_x + i * 2e3, u(e), u(e));
       SPAposition p2(same_x + i * 2e3, u(e), u(e));
       SPAposition p3(same_x + i * 2e3, u(e), u(e));
       api_make_plface(p1, p2, p3, face);  // 构建一个法向量为(0, 0, 1)的plane_face
       SPAunit_vector temp_vector = dynamic_cast<PLANE*>(face->geometry())->normal();
       if(is_positive(temp_vector.x() * unit_vector.x() + temp_vector.y() * unit_vector.y() + temp_vector.z() * unit_vector.z())) {
           body_faces.push_back(face);
       }
    }
    for(int i = 0; i < body_faces.size() - 1; ++i) {
       int j = (i + 1) % body_faces.size();
       body_faces[i]->set_next(body_faces[j]);
    }
    // 构建SHELL, LUMP, BODY
    SHELL* shell = ACIS_NEW SHELL(body_faces[0], nullptr, nullptr);
    LUMP* lump = ACIS_NEW LUMP(shell, nullptr);
    body = ACIS_NEW BODY(lump);
    output_ents.add(body);

    gme_api_find_face(body, unit_vector, face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    API_END
    return result;	
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_find_face_demo 4:
//
// APIs:
//    gme_api_find_face
//
// Description:
//	  
//
// **********************************************************************************
outcome aei_FIND_FACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    FACE* face = nullptr;
    EDGE* my_edge;  // 用于展示坐标系直线
    ENTITY* ent = nullptr;
    //  生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-1e5, 1e5);  // 左闭右闭区间，取点坐标的大小范围
    e.seed(time(0));
    const SPAunit_vector unit_vector(u(e), u(e), u(e));
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    // 建立三维直角坐标系
    int scale = 2e5;  // 坐标系横坐标范围
    SPAposition pos0(0, 0, 0);
    SPAposition pos1(scale, 0, 0);
    SPAposition pos2(-1 * scale, 0, 0);
    check_outcome(api_curve_line(pos1, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(1.0, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos2, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0.4, 0, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos3(0, scale, 0);
    SPAposition pos4(0, -1 * scale, 0);
    check_outcome(api_curve_line(pos3, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 1.0, 0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos4, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0.4, 0));
    if(result.ok()) output_ents.add(my_edge);
    SPAposition pos5(0, 0, scale);
    SPAposition pos6(0, 0, -1 * scale);
    check_outcome(api_curve_line(pos5, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 1.0));
    if(result.ok()) output_ents.add(my_edge);
    check_outcome(api_curve_line(pos6, pos0, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(0, 0, 0.4));
    if(result.ok()) output_ents.add(my_edge);

    SPAposition pos7(2.5e5 * unit_vector.x(), 2.5e5 * unit_vector.y(), 2.5e5 * unit_vector.z());
    SPAposition pos8(-2.5e5 * unit_vector.x(), -2.5e5 * unit_vector.y(), -2.5e5 * unit_vector.z());
    check_outcome(api_curve_line(pos7, pos8, my_edge));
    result = api_rh_set_entity_rgb(my_edge, rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans));
    if(result.ok()) output_ents.add(my_edge);

	std::vector<FACE*> body_faces;
    double same_x = -1e5;
    for(int i = 0; i < 100; i++) {
       FACE* face = nullptr;
       SPAposition p1(same_x + i * 2e3, u(e), u(e));
       SPAposition p2(same_x + i * 2e3, u(e), u(e));
       SPAposition p3(same_x + i * 2e3, u(e), u(e));
       api_make_plface(p1, p2, p3, face);  // 构建一个法向量为(0, 0, 1)的plane_face
       SPAunit_vector temp_vector = dynamic_cast<PLANE*>(face->geometry())->normal();
       if(is_positive(temp_vector.x() * unit_vector.x() + temp_vector.y() * unit_vector.y() + temp_vector.z() * unit_vector.z())) {
           body_faces.push_back(face);
       }
    }
    for(int i = 0; i < body_faces.size() - 1; ++i) {
       int j = (i + 1) % body_faces.size();
       body_faces[i]->set_next(body_faces[j]);
    }
    // 构建SHELL, LUMP, BODY
    SHELL* shell = ACIS_NEW SHELL(body_faces[0], nullptr, nullptr);
    LUMP* lump = ACIS_NEW LUMP(shell, nullptr);
    body = ACIS_NEW BODY(lump);
    output_ents.add(body);

    gme_api_find_face(body, unit_vector, face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    api_find_face(body, unit_vector, face);
    api_rh_set_entity_rgb(face, rgb_color(0 * color_trans, 127 * color_trans, 80 * color_trans));  // #007F50
    output_ents.add(face);
    API_END
    return result;	
}