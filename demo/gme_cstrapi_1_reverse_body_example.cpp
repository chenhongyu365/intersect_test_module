/*********************************************************************
 * @file    gme_cstrapi_1_reverse_body.cpp
 * @brief
 * @details
 * @author  Solokey-0731
 * @date    2024.09.14
 *********************************************************************/

#include "gme_cstrapi_1_reverse_body_example.hxx"

#include <acis/eulerapi.hxx>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/splsurf.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 1:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//    长方体Cuboid
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN
    api_make_cuboid(1, 1, 2, gme_body);
    gme_1_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 2:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//    球Sphere
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN
    api_make_sphere(1, gme_body);
    gme_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 3:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//     圆锥Frustum
//
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN
    api_make_frustum(5, 5, 3, 2, gme_body);
    gme_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 4:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//     圆环torus
//
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN
    api_make_torus(2, 1, gme_body);
    gme_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 5:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//    棱柱Prism
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN

    api_make_prism(5, 5, 3, 3, gme_body);
    gme_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 6:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//    曲线形体wiggle
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body;

    API_BEGIN
    api_wiggle(5, 5, 5, 0, 1, 2, -1, 1, gme_body);
    gme_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_api_reverse_body demo 6:
//
// APIs:
//    1_api_reverse_body
//
// Description:
//    多边形polygon
// **********************************************************************************

outcome aei_1_REVERSE_BODY_DEMO7(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = nullptr;

    API_BEGIN
    SPAvector normal1;
    double side_length;
    api_make_polygon(gme_body, SPAposition(0, 0, 0), SPAvector(0, 0, 1), normal1, side_length);
    gme_1_api_reverse_body(gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}
