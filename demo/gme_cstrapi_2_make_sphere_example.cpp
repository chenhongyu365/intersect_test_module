/*********************************************************************
 * @file    gme_cstrapi_2_make_sphere_example.cpp
 * @brief   api_make_sphere demo
 * @details
 * @author  HelenABCD
 * @date    2023.9.22
 *********************************************************************/
#include "gme_cstrapi_2_make_sphere_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_sphere_demo 1:
//
// APIs:
//    gme_api_2_make_sphere
//
// Description:
//	  正常情况:radius为1
//
// **********************************************************************************
outcome aei_MAKE_SPHERE_DEMO01(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_2_make_sphere(1.0, body);
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
//	  make_sphere_demo 2:
//
// APIs:
//    gme_api_2_make_sphere
//
// Description:
//	  radius为SPAreadbs
//
// **********************************************************************************
outcome aei_MAKE_SPHERE_DEMO02(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_2_make_sphere(SPAresabs, body);
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
//	  make_sphere_demo 3:
//
// APIs:
//    gme_api_2_make_sphere
//
// Description:
//	  radius为0
//
// **********************************************************************************
outcome aei_MAKE_SPHERE_DEMO03(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_2_make_sphere(0, body);
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
//	  make_sphere_demo 4:
//
// APIs:
//    gme_api_2_make_sphere
//
// Description:
//	  异常情况：radiusxia小于容差
//
// **********************************************************************************
outcome aei_MAKE_SPHERE_DEMO04(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_2_make_sphere(1e-8, body);
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
//	  make_sphere_demo 5:
//
// APIs:
//    gme_api_2_make_sphere
//
// Description:
//	  radius为1000
//
// **********************************************************************************
outcome aei_MAKE_SPHERE_DEMO05(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_2_make_sphere(1000, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}