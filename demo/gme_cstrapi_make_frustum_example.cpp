/*********************************************************************
 * @file    gme_cstrapi_make_frustum_example.cpp
 * @brief   api_make_frustum demo
 * @details
 * @author  hosimiAKE
 * @date    2023.7.20
 *********************************************************************/
#include "gme_cstrapi_make_frustum_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  frustum_demo 1:
//
// APIs:
//    gme_api_make_frustum
//
// Description:
//	  正常情况
//
// **********************************************************************************
outcome aei_FRUSTUM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_frustum(4.0, 3.0, 4.0, 6.0, body);
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
//	  frustum_demo 2:
//
// APIs:
//    gme_api_make_frustum
//
// Description:
//	  top为0
//
// **********************************************************************************
outcome aei_FRUSTUM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_frustum(4.0, 6.0, 3.0, 0.0, body);
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
//	  frustum_demo 3:
//
// APIs:
//    gme_api_make_frustum
//
// Description:
//	  top小于容差
//
// **********************************************************************************
outcome aei_FRUSTUM_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_make_frustum(4.0, 6.0, 3.0, 0.1*SPAresabs, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}