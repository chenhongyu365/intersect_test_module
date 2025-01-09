/*********************************************************************
 * @file    gme_cstrapi_make_sphere_example.cpp
 * @brief   api_make_sphere demo
 * @details
 * @author  Dubopei
 * @date    2023.9.19
 *********************************************************************/
#include "gme_cstrapi_make_sphere_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  sphere_demo 1:
//
// APIs:
//    gme_api_make_sphere
//
// Description:
//	  正常情况
//
// **********************************************************************************
outcome aei_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_sphere(1.0, body);
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
//	  sphere_demo 2:
//
// APIs:
//    gme_api_make_sphere
//
// Description:
//	  radius小于容差
//
// **********************************************************************************
outcome aei_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_sphere(SPAresabs, body);
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
//	  sphere_demo 3:
//
// APIs:
//    gme_api_make_sphere
//
// Description:
//	  radius为0
//
// **********************************************************************************
outcome aei_SPHERE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_sphere(0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}