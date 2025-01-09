/*********************************************************************
 * @file    gme_cstrapi_1_solid_sphere_example.cpp
 * @brief   api_solid_sphere demo
 * @details
 * @author  evertravel
 * @date    2024.9.19
 *********************************************************************/
#include "gme_cstrapi_1_solid_sphere_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_solid_sphere_demo 1:
//
// APIs:
//    gme_1_api_solid_sphere
//
// Description:
//	  创建一个以原点为球心，半径长度为1的球体
//
// **********************************************************************************
outcome aei_1_SOLID_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = NULL;

    API_BEGIN
    gme_1_api_solid_sphere(SPAposition(0, 0, 0), 1, sph);
    API_END

    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_solid_sphere_demo 2:
//
// APIs:
//    gme_1_api_solid_sphere
//
// Description:
//	  在(10,10,10)点处创建一个半径为1的球体
//
// **********************************************************************************
outcome aei_1_SOLID_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = NULL;
    API_BEGIN
    gme_1_api_solid_sphere(SPAposition(10, 0, 0), 1, sph);
    API_END

    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}