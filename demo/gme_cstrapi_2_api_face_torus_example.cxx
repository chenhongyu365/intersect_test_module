/*********************************************************************
 * @file    gme_cstrapi_2_api_face_torus_example.cxx
 * @brief
 * @details
 * @author  罗坤
 * @date    2024.10.16
 *********************************************************************/
#include "gme_cstrapi_2_api_face_torus_example.hxx"

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
//	  api_2_face_torus_demo 1
//
// APIs:
//    gme_2_api_face_torus
//
// Description:
//	   major_radius<minor_radius时
//
// **********************************************************************************
outcome aei_2_FACE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* torus_face = NULL;

    API_BEGIN
    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);

    gme_2_api_face_torus(center, 1, 3, 0, 60, 0, 100, &normal, torus_face);

    API_END
    if(result.ok()) {
        output_ents.add(torus_face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  api_2_face_torus_demo 2
//
// APIs:
//    gme_2_api_face_torus
//
// Description:
//	   major_radius>minor_radius时
//
// **********************************************************************************
outcome aei_2_FACE_TORUS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* torus_face = NULL;

    API_BEGIN
    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);

    gme_2_api_face_torus(center, 3, 1, 0, 60, 0, 100, &normal, torus_face);

    API_END
    if(result.ok()) {
        output_ents.add(torus_face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  api_2_face_torus_demo 1
//
// APIs:
//    gme_2_api_face_torus
//
// Description:
//	   major_radius=minor_radius时
//
// **********************************************************************************
outcome aei_2_FACE_TORUS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* torus_face = NULL;

    API_BEGIN
    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);

    gme_2_api_face_torus(center, 3, 3, 0, 60, 0, 100, &normal, torus_face);

    API_END
    if(result.ok()) {
        output_ents.add(torus_face);
    }
    return result;
}