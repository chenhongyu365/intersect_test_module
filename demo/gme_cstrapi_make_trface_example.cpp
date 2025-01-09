/*********************************************************************
 * @file    gme_cstrapi_1_make_trface_example.cpp
 * @brief
 * @details
 * @author  lgr
 * @date    2024.10.20
 *********************************************************************/
#include "gme_cstrapi_make_trface_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"

outcome aei_MAKE_TRFACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = NULL;

    API_BEGIN
    gme_api_make_trface(SPAposition(0, 0, 0), SPAunit_vector(0, 0, 1), -3, 5, SPAposition(1, 0, 0), -M_PI - 1, M_PI + 1, 0, 2, gme_face);
    API_END
    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}

outcome aei_MAKE_TRFACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = NULL;

    API_BEGIN
    gme_api_make_trface(SPAposition(0, 0, 0), SPAunit_vector(0, 0, 1), 5, 3, SPAposition(1, 0, 0), 0, 2 * M_PI, 0, 2, gme_face);
    API_END
    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}

outcome aei_MAKE_TRFACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = NULL;

    API_BEGIN
    gme_api_make_trface(SPAposition(0, 0, 0), SPAunit_vector(0, 0, 1), 2, 5, SPAposition(1, 0, 0), 0, M_PI + 1, 0, 2 * M_PI, gme_face);
    API_END
    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}
