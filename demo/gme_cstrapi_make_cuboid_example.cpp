/*********************************************************************
 * @file    gme_cstrapi_make_cuboid_example.cpp
 * @brief   api_make_cuboid demo
 * @details
 * @author  CastaneaG
 * @date    2023.7.20
 *********************************************************************/
#include "gme_cstrapi_make_cuboid_example.hxx"

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
//    gme_api_make_cuboid
//
// Description:
//	  正常情况
//
// **********************************************************************************
outcome aei_CUBOID_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_cuboid(2.0, 3.0, 4.0, body);
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
//    gme_api_make_cuboid
//
// Description:
//	  z(height)小于容差
//
// **********************************************************************************
outcome aei_CUBOID_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_cuboid(2.0, 3.0, 1e-7, body);
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
//    gme_api_make_cuboid
//
// Description:
//	  z(height)为0
//
// **********************************************************************************
outcome aei_CUBOID_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_cuboid(2.0, 3.0, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}