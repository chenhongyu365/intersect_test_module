/*********************************************************************
 * @file    gme_cstrapi_1_make_torus_example.cpp
 * @brief
 * @details
 * @author  宋羽豪
 * @date    2024.9.28
 *********************************************************************/
#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"
#include "gme_cstrapi_make_torus_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_make_torus_demo 1
//
// APIs:
//    gme_1_api_make_torus
//
// Description:
//	  生成donut torus
//
// **********************************************************************************
outcome aei_1_MAKE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(2, 1, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_make_torus_demo 2:
//
// APIs:
//    gme_1_api_make_torus
//
// Description:
//	  生成apple torus
//
// **********************************************************************************
outcome aei_1_MAKE_TORUS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(1, 2, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_make_torus_demo 3:
//
// APIs:
//    gme_1_api_make_torus
//
// Description:
//	  生成lemon torus
//
// **********************************************************************************
outcome aei_1_MAKE_TORUS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(-1, 2, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_make_torus_demo 4:
//
// APIs:
//    gme_1_api_make_torus
//
// Description:
//	  生成vortex torus
//
// **********************************************************************************
outcome aei_1_MAKE_TORUS_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(1, 1, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}
