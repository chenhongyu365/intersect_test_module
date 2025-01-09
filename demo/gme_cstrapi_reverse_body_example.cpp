/*********************************************************************
 * @file    gme_cstrapi_reverse_body_example.cpp
 * @brief  api_reverse_body demo
 * @details
 * @author  charynnc
 * @date    2023.7.18
 *********************************************************************/
#include "gme_cstrapi_reverse_body_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 1:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      长方体
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_make_cuboid(1, 1, 2, acis_body);
    api_reverse_body(acis_body);
    api_make_cuboid(1, 1, 2, gme_body);
    gme_api_reverse_body(gme_body);

    acis_api_save_entity("acis_edge.sat", acis_body);
    acis_api_save_entity("gme_edge.sat", gme_body);
    acis_api_save_entity("gme_edge.sat", gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 2:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      球
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_make_sphere(1, acis_body);
    api_reverse_body(acis_body);
    api_make_sphere(1, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 3:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      圆锥体
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_make_frustum(5, 5, 3, 2, acis_body);
    api_reverse_body(acis_body);
    api_make_frustum(5, 5, 3, 2, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 4:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      圆环
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_make_torus(2, 1, acis_body);
    api_reverse_body(acis_body);
    api_make_torus(2, 1, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 5:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      棱柱
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_make_prism(5, 5, 3, 3, acis_body);
    api_reverse_body(acis_body);
    api_make_prism(5, 5, 3, 3, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 6:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      wiggle
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;

    API_BEGIN
    api_wiggle(5, 5, 5, 0, 1, 2, -1, 1, acis_body);
    api_reverse_body(acis_body);
    api_wiggle(5, 5, 5, 0, 1, 2, -1, 1, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_body_demo 7:
//
// APIs:
//    gme_api_reverse_body
//
// Description:
//      sheet
// **********************************************************************************
outcome aei_REVERSE_BODY_DEMO7(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY *acis_body, *gme_body;
    FACE* face1;

    API_BEGIN
    SPAvector normal(0, 0, 1);
    api_face_plane(SPAposition(0, 0, 0), 2, 2, &normal, face1);
    api_sheet_from_ff(2, &face1, acis_body);
    api_reverse_body(acis_body);
    api_sheet_from_ff(1, &face1, gme_body);
    gme_api_reverse_body(gme_body);

    API_END

    if(result.ok()) {
        // api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_body);
        // output_ents.add(acis_body);
    }
    return result;
}