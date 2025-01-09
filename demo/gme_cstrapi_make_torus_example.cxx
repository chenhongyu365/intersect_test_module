/*********************************************************************
 * @file    gme_cstrapi_make_torus_example.cpp
 * @brief
 * @details
 * @author  胡轩頔
 * @date    2024.7.26
 *********************************************************************/
#include "gme_cstrapi_make_torus_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo 1:
//
// APIs:
//    gme_api_make_torus
//
// Description:
//	  生成donut的情况
//
// **********************************************************************************
outcome aei_MAKE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(8, 5, tor);

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
//	  cuboid_demo 2:
//
// APIs:
//    gme_api_make_torus
//
// Description:
//	  生成apple的情况
//
// **********************************************************************************
outcome aei_MAKE_TORUS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(3, 5, tor);

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
//	  cuboid_demo 3:
//
// APIs:
//    gme_api_make_torus
//
// Description:
//	  生成lemon的情况
//
// **********************************************************************************
outcome aei_MAKE_TORUS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(-3, 5, tor);

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
//	  cuboid_demo 4:
//
// APIs:
//    gme_api_make_torus
//
// Description:
//	  生成vortex的情况
//
// **********************************************************************************
outcome aei_MAKE_TORUS_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_api_make_torus(5, 5, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}
