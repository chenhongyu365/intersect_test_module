/*********************************************************************
 * @file    spd_ent7_example.cpp
 * @brief   HD_PEL_ENT6 demo
 * @details
 * @author  caoliang
 * @date    2024.11.7
 *********************************************************************/

#include "spd_ent6_example.hxx"

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT6
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT6.
//    直角偏心圆台
// **********************************************************************************
outcome aei_HD_PEL_ENT6_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal_w[3] = {0, 0, 1};  // 法向量
    double normal_u[3] = {1, 0, 0};  // 偏心向量
    gme_HD_PEL_ENT6(center, normal_w, 20, 10, 10, normal_u, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}

outcome aei_HD_PEL_ENT6_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal_w[3] = {0, 0, 1};
    double normal_u[3] = {1, 0, 0};
    gme_HD_PEL_ENT6(center, normal_w, 10, 10, 10, normal_u, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}
outcome aei_HD_PEL_ENT6_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal_w[3] = {0, 0, 1};
    double normal_u[3] = {1, 0, 0};
    gme_HD_PEL_ENT6(center, normal_w, 10, 20, 10, normal_u, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}
outcome aei_HD_PEL_ENT6_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal_w[3] = {0, 0, 1};
    double normal_u[3] = {1, 0, 0};
    gme_HD_PEL_ENT6(center, normal_w, 20, 10, 1, normal_u, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}