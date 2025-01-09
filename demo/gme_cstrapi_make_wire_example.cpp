/*********************************************************************
 * @file    gme_cstrapi_make_wire_example.cpp
 * @brief   展示了生成单个的wire_body，有两个个wire的body，和有solid有wire的混合body
 * @details DEMO2、DEMO3展示的是一个body，不同部分不同颜色
 * @author  全志成
 * @date    2023.7.24
 *********************************************************************/
#include "gme_cstrapi_make_wire_example.hxx"

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
//	  make_wire_demo 1:
//
// APIs:
//    gme_api_make_wire
//
// Description:
//	  用随机数生成随机点列，展示该点列生成的wire_body，in_body为空
//
// **********************************************************************************
outcome aei_MAKE_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
	EDGE* my_edge;                       // 用于展示坐标系直线
	BODY* in_body = nullptr;             // 初始的body
	BODY* gme_body = nullptr;            // 用于接收acis api创建的body
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    
	API_BEGIN
	// 生成随机数种子
	std::default_random_engine e;
	std::uniform_real_distribution<double> u(-1000, 1000);  // 左闭右闭区间，取点坐标的大小范围
	std::uniform_real_distribution<double> v(50, 100);    // 左闭右闭区间，取点的数量范围
	std::uniform_real_distribution<double> w(10, 20);      // 左闭右闭区间，length_pts范围
	e.seed(time(0));
	int pts_size = ceil(v(e));
	int length_pts = ceil(w(e));
	SPAposition array_pts[1000];  // 用于存储随机生成的点
	// 生成随机点
	for(int i = 0; i < pts_size; ++i) {
		array_pts[i].set_coordinate(0, u(e));
		array_pts[i].set_coordinate(1, u(e));
		array_pts[i].set_coordinate(2, u(e));
	}
	// 建立三维直角坐标系
    int scale = 1000;  // 坐标系横坐标范围
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
    // 生成wire_body
	check_outcome(gme_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans)); // 珊瑚色 #FF7F50
	if(result.ok()) output_ents.add(gme_body);
	API_END

	return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_wire_demo 2:
//
// APIs:
//    gme_api_make_wire
//
// Description:
//	  用随机数生成两个随机点列，随机点列1生成的wire_body作为in_body传入
//    得到有两个wire(分属不同lump)的body，相当于两个wire_body合并
//
// **********************************************************************************
outcome aei_MAKE_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
	//线框为生成的wire_body，立方体为输入的in_body，这里展示将两者合体
	EDGE* my_edge;                       // 用于展示坐标系直线
	BODY* in_body = nullptr;             // 初始的body
	BODY* gme_body = nullptr;            // 用于接收acis api创建的body
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    
	API_BEGIN
	// 生成随机数种子
	std::default_random_engine e;
	std::uniform_real_distribution<double> u(-1000, 1000);  // 左闭右闭区间，取点坐标的大小范围
	std::uniform_real_distribution<double> v(50, 100);    // 左闭右闭区间，取点的数量范围
	std::uniform_real_distribution<double> w(5, 10);      // 左闭右闭区间，length_pts范围
	e.seed(time(0));
	int pts_size = ceil(v(e));
	int length_pts = ceil(w(e));
	SPAposition array_pts[1000];  // 用于存储随机生成的点
	// 生成随机点
	for(int i = 0; i < pts_size; ++i) {
		array_pts[i].set_coordinate(0, u(e));
		array_pts[i].set_coordinate(1, u(e));
		array_pts[i].set_coordinate(2, u(e));
	}
	// 建立三维直角坐标系
    int scale = 1000;  // 坐标系横坐标范围
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
	// 生成第一个wire_body
	check_outcome(gme_api_make_wire(in_body, length_pts, array_pts, gme_body));
	in_body = gme_body;
	
    pts_size = ceil(v(e));
	length_pts = ceil(w(e));
    // 生成随机点
    for(int i = 0; i < pts_size; ++i) {
		array_pts[i].set_coordinate(0, u(e));
		array_pts[i].set_coordinate(1, u(e));
		array_pts[i].set_coordinate(2, u(e));
	}
    // 生成第二个wire_body，并将第一个wire_body作为in_body输入
    check_outcome(gme_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body->lump(), rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    result = api_rh_set_entity_rgb(gme_body->lump()->next(), rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans));  // 黄褐色 #F0E68C
	if(result.ok()) output_ents.add(gme_body);
	API_END

	return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_wire_demo 3:
//
// APIs:
//    gme_api_make_wire
//
// Description:
//	  用随机数生成随机点列，用api_make_cuboid初始化in_body，展示生成wire_body并和in_body合并
//
// **********************************************************************************
outcome aei_MAKE_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
	//线框为生成的wire_body，立方体为输入的in_body，这里展示将两者合体
	ENTITY* ent = nullptr;
	EDGE* my_edge;
	BODY* in_body = nullptr;             // 初始的body
	BODY* gme_body = nullptr;            // 用于接收acis api创建的body
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    
	API_BEGIN
	api_make_cuboid(300, 400, 500, in_body);  // 这里展示in_body非空时，wire_body和in_body合并
	// 生成随机数种子
	std::default_random_engine e;
	std::uniform_real_distribution<double> u(-1000, 1000);  // 左闭右闭区间，取点坐标的大小范围
	std::uniform_real_distribution<double> v(50, 100);    // 左闭右闭区间，取点的数量范围
	std::uniform_real_distribution<double> w(10, 20);      // 左闭右闭区间，length_pts范围
	e.seed(time(0));
	int pts_size = ceil(v(e));
	int length_pts = ceil(w(e));
	SPAposition array_pts[1000];  // 用于存储随机生成的点
	// 生成随机点
	for(int i = 0; i < pts_size; ++i) {
		array_pts[i].set_coordinate(0, u(e));
		array_pts[i].set_coordinate(1, u(e));
		array_pts[i].set_coordinate(2, u(e));
	}
	// 建立三维直角坐标系
    int scale = 1000;  // 坐标系横坐标范围
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

	// 展示生成wire_body并在gme_api_make_wire中和in_body的长方体合并
	check_outcome(gme_api_make_wire(in_body, length_pts, array_pts, gme_body));
    result = api_rh_set_entity_rgb(gme_body->lump(), rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));           // 珊瑚色 #FF7F50
    result = api_rh_set_entity_rgb(gme_body->lump()->next(), rgb_color(240 * color_trans, 230 * color_trans, 140 * color_trans));  // 黄褐色 #F0E68C
	if(result.ok()) output_ents.add(gme_body);
	API_END

	return result;
}