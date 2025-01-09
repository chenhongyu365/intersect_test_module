/*********************************************************************
 * @file    gme_cstrapi_2_solid_sphere_example.cpp
 * @brief   gme_2_api_solid_sphere demo
 * @details
 * @author  杨袁瑞
 * @date    2024.10.08
 *********************************************************************/
#include "gme_cstrapi_2_solid_sphere_example.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_solid_sphere_demo 1:
//
// APIs:
//    gme_2_api_solid_sphere
//
// Description:
//	  一个球心位于原点，半径为正的球
//
// **********************************************************************************
outcome aei_2_SOLID_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const SPAposition center = SPAposition(0, 0, 0);
    const double radius = 10;

    // 生成solid_sphere
    check_outcome(gme_2_api_solid_sphere(center, radius, gme_body));
    if(result.ok()) {
        result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
        output_ents.add(gme_body);
    }

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_solid_sphere_demo 2:
//
// APIs:
//    gme_2_api_solid_sphere
//
// Description:
//	  一个球心不在原点，半径为正的球
//
// **********************************************************************************
outcome aei_2_SOLID_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const SPAposition center = SPAposition(5, 5, 5);
    const double radius = 10;

    // 生成solid_sphere
    check_outcome(gme_2_api_solid_sphere(center, radius, gme_body));
    if(result.ok()) {
        result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
        output_ents.add(gme_body);
    }

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_solid_sphere_demo 3:
//
// APIs:
//    gme_2_api_solid_sphere
//
// Description:
//	  一个球心在原点，半径为SPAresabs的球
//
// **********************************************************************************
outcome aei_2_SOLID_SPHERE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const SPAposition center = SPAposition(0, 0, 0);
    const double radius = SPAresabs;

    // 生成solid_sphere
    check_outcome(gme_2_api_solid_sphere(center, radius, gme_body));
    if(result.ok()) {
        result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
        output_ents.add(gme_body);
    }

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_solid_sphere_demo 4:
//
// APIs:
//    gme_2_api_solid_sphere
//
// Description:
//	  一个球心不在原点，半径为SPAresabs的球
//
// **********************************************************************************
outcome aei_2_SOLID_SPHERE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const SPAposition center = SPAposition(0.0001, 0.0001, 0.0001);
    const double radius = SPAresabs;

    // 生成solid_sphere
    check_outcome(gme_2_api_solid_sphere(center, radius, gme_body));
    if(result.ok()) {
        result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
        output_ents.add(gme_body);
    }

    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_solid_sphere_demo 5:
//
// APIs:
//    gme_2_api_solid_sphere
//
// Description:
//	  输入的球心位置在原点，半径为DBL_MAX; 可以生成BODY，但是输出后报错浮点数溢出异常无法显示
//
// **********************************************************************************
outcome aei_2_SOLID_SPHERE_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* gme_body = nullptr;  // 用于接收gme api创建的body

    API_BEGIN
    const SPAposition center = SPAposition(0, 0, 0);
    const double radius = DBL_MAX;

    // 生成solid_sphere
    check_outcome(gme_2_api_solid_sphere(center, radius, gme_body));
    if(result.ok()) {
        result = api_rh_set_entity_rgb(gme_body, rgb_color(225 / 255.0, 245 / 255.0, 254 / 255.0));  // #e1f5fe
        output_ents.add(gme_body);
    }

    API_END

    return result;
}
