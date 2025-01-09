/*********************************************************************
 * @file    gme_cstrapi_solid_sphere_example.hxx
 * @brief
 * @details
 * @author  Solokey-0731
 * @date    2024.9.12
 *********************************************************************/

#include "gme_cstrapi_solid_sphere_example.hxx"

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
//	  solid_sphere demo 1:
//
// APIs:
//    api_solid_sphere
//
// Description:
//
// **********************************************************************************
outcome aei_SOLID_SPHERE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = nullptr;
    API_BEGIN
    SPAposition center1 = SPAposition(1, 0, 0);
    double radius1 = 1.0;
    gme_api_solid_sphere(center1, radius1, sph);
    API_END
    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  solid_sphere demo 2:
//
// APIs:
//    api_solid_sphere
//
// Description:
//
// **********************************************************************************
outcome aei_SOLID_SPHERE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = nullptr;
    API_BEGIN
    SPAposition center2 = SPAposition(0, 0, 0);
    double radius2 = 0;
    gme_api_solid_sphere(center2, radius2, sph);
    API_END
    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  solid_sphere demo 3:
//
// APIs:
//    api_solid_sphere
//
// Description:
//
// **********************************************************************************
outcome aei_SOLID_SPHERE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* sph = nullptr;
    API_BEGIN
    SPAposition center3 = SPAposition(3, -2, 1);
    double radius3 = -1;
    gme_api_solid_sphere(center3, radius3, sph);
    API_END
    if(result.ok()) {
        output_ents.add(sph);
    }
    return result;
}
