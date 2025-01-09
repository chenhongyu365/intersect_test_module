/*********************************************************************
 * @file        gme_cstrapi_3_make_frustum_example.cpp
 * @brief       api_make_frustum demo
 * @details
 * @author      lbx990704
 * @date        2024.10.10
 *********************************************************************/
#include "gme_cstrapi_3_make_frustum_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"

// 圆锥
outcome aei_3_FRUSTUM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_3_api_make_frustum(1, 2, 1, 0, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}

// 倒圆台
outcome aei_3_FRUSTUM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_3_api_make_frustum(1, 1, 1.5, 2, frustum);
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}

// 顶部和底部半径相等的圆台（圆柱）
outcome aei_3_FRUSTUM_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_3_api_make_frustum(5, 3, 3, 3, frustum);  // 顶部和底部半径相等
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
// 极小半径的圆台
outcome aei_3_FRUSTUM_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_3_api_make_frustum(1e-5, 1e-5, 1e-5, 2e-5, frustum);  // 极小半径
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
// 高度极大的圆台
outcome aei_3_FRUSTUM_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* frustum = NULL;
    API_BEGIN
    gme_3_api_make_frustum(1e5, 1e5, 1e5, 1e5, frustum);  // 高度极大
    API_END

    if(result.ok()) {
        output_ents.add(frustum);
    }
    return result;
}
