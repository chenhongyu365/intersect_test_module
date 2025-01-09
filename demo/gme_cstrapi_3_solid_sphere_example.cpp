/*********************************************************************
 * @file    gme_cstrapi_3_solid_sphere_example.cpp
 * @brief   api_solid_sphere demo
 * @details
 * @author  王书瑶
 * @date    2024.10.21
 *********************************************************************/
#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "gme_cstrapi_3_solid_sphere_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_solid_sphere_demo 1:
//
// APIs:
//    gme_3_api_solid_sphere
//
// Description:
//	  创建一个以原点为球心，半径长度为1的球体
//
// **********************************************************************************
outcome aei_3_SOLID_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = NULL;

    API_BEGIN
    gme_3_api_solid_sphere(SPAposition(0, 0, 0), 1, sph);
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
//	  solid_sphere_demo 2:
//
// APIs:
//    gme_3_api_solid_sphere
//
// Description:
//	  在(10,10,10)点处创建一个半径为1的球体
//
// **********************************************************************************
outcome aei_3_SOLID_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = NULL;
    API_BEGIN
    gme_3_api_solid_sphere(SPAposition(10, 0, 0), 1, sph);
    API_END

    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}