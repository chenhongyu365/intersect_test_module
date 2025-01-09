/*********************************************************************
 * @file    gme_cstrapi_2_make_torus_example.cpp
 * @brief   gme_cstrapi_2_make_torus的可视化测例
 * 已测试
 *      case1:Donut 形状 (major > minor)
 *      case2:Apple 形状 (major < minor)
 *      case3:Lemon 形状 (负 major 且 |major| < |minor|)
 *      case4:Vortex 形状 (|major| = |minor|)
 * @details
 * @author  lichenyu
 * @date    2024.9.29
 *********************************************************************/
#include "gme_cstrapi_2_make_torus_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"

outcome aei_2_MAKE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_2_api_make_torus(100, 50, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}

outcome aei_2_MAKE_TORUS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_2_api_make_torus(50, 100, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}

outcome aei_2_MAKE_TORUS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_2_api_make_torus(-50, 100, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}

outcome aei_2_MAKE_TORUS_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* tor = NULL;
    API_BEGIN

    gme_2_api_make_torus(100, 100, tor);

    API_END
    if(result.ok()) {
        output_ents.add(tor);
    }
    return result;
}