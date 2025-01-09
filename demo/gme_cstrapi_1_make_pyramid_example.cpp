/*********************************************************************
 * @file    gme_cstrapi_1_make_pyramid_example.cpp
 * @brief
 * @details
 * @author  lgr
 * @date    2024.10.13
 *********************************************************************/
#include "gme_cstrapi_1_make_pyramid_example.hxx"

#include <vector>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"
// #include "template_simple_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  pyramid_demo:
//
// APIs:
//    gme_1_api_make_pyramid
//
// Description:
//	  构造棱台 radius1>radius2
// **********************************************************************************
outcome aei_1_PYRAMID_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_pyramid(6, 8, 6, 6, 12, body);
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
//	  pyramid_demo:
//
// APIs:
//    gme_1_api_make_pyramid
//
// Description:
//	  构造棱台 radius1=radius2
// **********************************************************************************
outcome aei_1_PYRAMID_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_pyramid(20, 6, 6, 12, 24, body);
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
//	  pyramid_demo:
//
// APIs:
//    gme_1_api_make_pyramid
//
// Description:
//	  构造棱台 nsides=3
// **********************************************************************************
outcome aei_1_PYRAMID_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_pyramid(6, 8, 6, 3, 3, body);
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
//	  pyramid_demo:
//
// APIs:
//    gme_1_api_make_pyramid
//
// Description:
//	  构造棱台height=0
// **********************************************************************************
outcome aei_1_PYRAMID_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_pyramid(0, 8, 6, 6, 5, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
