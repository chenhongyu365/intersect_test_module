/*********************************************************************
 * @file    gme_cstrapi_make_spface_example.cpp
 * @brief
 * @details
 * @author  杨楠
 * @date    2024.7.19
 *********************************************************************/
#include "gme_cstrapi_make_spface_example.hxx"

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
//	  spface_demo 1:
//
// APIs:
//    gme_api_make_spface
//
// Description:
//	  常规的部分球面
//
// **********************************************************************************
outcome aei_SPFACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    double radius = 1;
    SPAunit_vector uv_oridir = SPAunit_vector(1, 0, 0);
    SPAunit_vector pole_dir = SPAunit_vector(0, 0, 1);
    double slat = -M_PI / 3;
    double elat = M_PI / 3;
    double slon = 0;
    double elon = M_PI / 2;
    result = gme_api_make_spface(center, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spface_demo 2:
//
// APIs:
//    gme_api_make_spface
//
// Description:
//	  部分球面，北纬达到北极点
//
// **********************************************************************************
outcome aei_SPFACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    double radius = 1;
    SPAunit_vector uv_oridir = SPAunit_vector(1, 0, 0);
    SPAunit_vector pole_dir = SPAunit_vector(0, 0, 1);
    double slat = 0;
    double elat = M_PI / 2;
    double slon = 0;
    double elon = M_PI / 2;
    result = gme_api_make_spface(center, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spface_demo 3:
//
// APIs:
//    gme_api_make_spface
//
// Description:
//	  部分球面，北纬南纬都到达极点
//
// **********************************************************************************
outcome aei_SPFACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    double radius = 1;
    SPAunit_vector uv_oridir = SPAunit_vector(1, 0, 0);
    SPAunit_vector pole_dir = SPAunit_vector(0, 0, 1);
    double slat = -M_PI / 2;
    double elat = M_PI / 2;
    double slon = 0;
    double elon = M_PI / 2;
    result = gme_api_make_spface(center, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spface_demo 4:
//
// APIs:
//    gme_api_make_spface
//
// Description:
//	  部分球面，经度横跨0到2pi
//
// **********************************************************************************
outcome aei_SPFACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    double radius = 1;
    SPAunit_vector uv_oridir = SPAunit_vector(1, 0, 0);
    SPAunit_vector pole_dir = SPAunit_vector(0, 0, 1);
    double slat = -M_PI / 4;
    double elat = M_PI / 4;
    double slon = 0;
    double elon = 2 * M_PI;
    result = gme_api_make_spface(center, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}
