/*********************************************************************
 * @file    gme_cstrapi_2_make_frustum_example.cxx
 * @brief   api_make_FRUSTUM demo
 * @details
 * @author  胡轩頔
 * @date    2023.8.7
 *********************************************************************/
#include "gme_cstrapi_2_make_frustum_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"

// 正圆台
outcome aei_2_FRUSTUM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_2_api_make_frustum(1, 1.5, 1, 1, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
// 正圆锥
outcome aei_2_FRUSTUM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_2_api_make_frustum(1, 2, 1, 0, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
// 正圆柱
outcome aei_2_FRUSTUM_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_2_api_make_frustum(1, 2, 1, 2, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
// 倒圆台
outcome aei_2_FRUSTUM_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_2_api_make_frustum(1, 1, 1.5, 2, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
