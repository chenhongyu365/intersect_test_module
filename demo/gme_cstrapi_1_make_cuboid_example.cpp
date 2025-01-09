/*********************************************************************
 * @file    gme_cstrapi_1_make_cuboid_example.cpp
 * @brief   api_make_cuboid demo
 * @details
 * @author  DDong 卢骏东
 * @date    2024.8.12
 *********************************************************************/
#include "gme_cstrapi_1_make_cuboid_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 1:
//
// APIs:
//    gme_1_api_make_cuboid
//
// Description:
//	  正常情况,绘制一个长宽高为1的正方体
//
// **********************************************************************************
outcome aei_CUBOID_DEMO01(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_cuboid(1, 1, 1, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 2:
//
// APIs:
//    gme_1_api_make_cuboid
//
// Description:
//	  z(height)小于容差,当z小于容差1e-6时仍可画出一个长方体
//
// **********************************************************************************
outcome aei_CUBOID_DEMO02(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_cuboid(5.0, 2.0, 1e-11, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 3:
//
// APIs:
//    gme_1_api_make_cuboid
//
// Description:
//	  z(height)为0
//
// **********************************************************************************
outcome aei_CUBOID_DEMO03(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_cuboid(5.0, 2.0, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 3:
//
// APIs:
//    gme_1_api_make_cuboid
//
// Description:
//	  x为1e-4,z为0,画出一个看似直线的二维小平面
//
// **********************************************************************************
outcome aei_CUBOID_DEMO04(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_cuboid(1e-4, 3.0, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 3:
//
// APIs:
//    gme_1_api_make_cuboid
//
// Description:
//	  x,y均为1e-6,z为0,画出一个边长为1e-6的正方形
//
// **********************************************************************************
outcome aei_CUBOID_DEMO05(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_cuboid(1e-6, 1e-6, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}