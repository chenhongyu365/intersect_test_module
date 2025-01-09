/*********************************************************************
 * @file    gme_cstrapi_1_make_sphere_example.cpp
 * @brief   gem_api_1_make_sphere demo
 * @details 球体创建的测试用例
 * @author  izhaoming
 * @date    2023.9.29
 *********************************************************************/
#include "gme_cstrapi_1_make_sphere_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example 1: 正常创建球体，半径为2.0
//
// Title:
//	  sphere_demo 1:
//
// APIs:
//    gme_1_api_make_sphere
//
// Description:
//	  半径为2.0的正常球体
//
// **********************************************************************************
outcome aei_1_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_sphere(2.0, body);  // 创建半径为2.0的球体
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}

// **********************************************************************************
// C++ Example 2: 半径为负值，测试负半径球体
//
// Title:
//	  sphere_demo 2:
//
// APIs:
//    gme_1_api_make_sphere
//
// Description:
//	  半径为负值 (-1.0)
//
// **********************************************************************************
outcome aei_1_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_sphere(-1.0, body);  // 创建半径为负值的球体，测试处理负半径
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}

// **********************************************************************************
// C++ Example 3: 半径为精度极限值，测试最小精度球体
//
// Title:
//	  sphere_demo 3:
//
// APIs:
//    gme_1_api_make_sphere
//
// Description:
//	  半径为精度极限值 SPAresabs
//
// **********************************************************************************
outcome aei_1_SPHERE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_sphere(SPAresabs, body);  // 创建一个半径为系统最小容差的球体
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}

// **********************************************************************************
// C++ Example 4: 半径为0.5，测试非整数半径
//
// Title:
//	  sphere_demo 4:
//
// APIs:
//    gme_1_api_make_sphere
//
// Description:
//	  半径为0.5的球体
//
// **********************************************************************************
outcome aei_1_SPHERE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_sphere(0.535, body);  // 创建半径为0.535的球体，测试非整数半径
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
