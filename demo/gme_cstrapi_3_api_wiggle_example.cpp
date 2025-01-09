/*********************************************************************
 * @file    gme_cstrapi_3_api_wiggle_example.cpp
 * @brief
 * @details
 * @author  caoliang
 * @date    2024.8.27
 *********************************************************************/
#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "gme_cstrapi_wiggle_example.hxx"

// **********************************************************************************
// APIs:
//    gme_3_api_wiggle
//
// Description:
//	  常规情况下的wiggle构造结果，四条边的参数分别选取了-2、-1、1、2，高度给定
//
// **********************************************************************************
outcome aei_make_wiggle_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_3_api_wiggle(3, 4, 5, -2, -1, 1, 2, 1, body);
    // api_wiggle(3, 4, 5, -2, -1, 1, 2, 1, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// APIs:
//    gme_3_api_wiggle
//
// Description:
//	  常规情况下的wiggle构造结果，四条边的参数分别选取了-2、-1、1、2，高度为0
//
// **********************************************************************************
outcome aei_make_wiggle_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_3_api_wiggle(2.0, 3.0, 4.0, -2, -1, 1, 2, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// APIs:
//    gme_3_api_wiggle
//
// Description:
//	  常规情况下的wiggle构造结果，四条边的参数分别选取了0，0，0，0，高度给定
//
// **********************************************************************************
outcome aei_make_wiggle_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_3_api_wiggle(2.0, 3.0, 4.0, 0, 0, 0, 0, 1, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
