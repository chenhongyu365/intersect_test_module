/*********************************************************************
 * @file    gme_cstrapi_1_face_torus_example.cpp
 * @brief
 * @details
 * @author  胡轩頔
 * @date    2024.08.01
 *********************************************************************/
#include "gme_cstrapi_1_face_torus_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"

outcome aei_1_FACE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* torus_face = NULL;

    API_BEGIN
    SPAposition center(0, 0, 0);
    SPAvector normal(0, 0, 1);

    gme_1_face_torus(center, 1, 3, 0, 90, 0, 90, &normal, torus_face);

    int b = 1;
    API_END
    if(result.ok()) {
        output_ents.add(torus_face);
    }
    return result;
}