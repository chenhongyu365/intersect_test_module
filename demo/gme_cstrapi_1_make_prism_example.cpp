/*********************************************************************
 * @file    gme_cstrapi_1_make_prism_example.hxx
 * @brief   api_make_prism demo
 * @details
 * @author  THEYIG
 * @date    2024.9.25
 *********************************************************************/
#include "gme_cstrapi_1_make_prism_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  prism_demo 1:
//
// APIs:
//    gme_api_make_prism
//
// Description:
//	  三棱柱
//
// **********************************************************************************
outcome aei_PRISM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_prism(1.0, 1.0, 2.0, 3, body);
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
//	  prism_demo 2:
//
// APIs:
//    gme_api_make_prism
//
// Description:
//	  四棱柱
//
// **********************************************************************************
outcome aei_PRISM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_prism(1.0, 1.0, 2.0, 4, body);
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
//	  prism_demo 3:
//
// APIs:
//    gme_api_make_prism
//
// Description:
//	 五棱柱
//
// **********************************************************************************
outcome aei_PRISM_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_1_api_make_prism(1.0, 1.0, 2.0, 5, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
