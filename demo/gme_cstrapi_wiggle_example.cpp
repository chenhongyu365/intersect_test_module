/*********************************************************************
 * @file    gme_cstrapi_wiggle_example.cpp
 * @brief
 * @details
 * @author  韩昊欣
 * @date    2024.7.20
 *********************************************************************/
#include "gme_cstrapi_wiggle_example.hxx"

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
//	  wiggle_demo 1:
//
// APIs:
//    gme_api_wiggle
//
// Description:
//	  常规情况下的wiggle构造结果，四条边的参数分别选取了-2、-1、1、2，高度给定
//
// **********************************************************************************
outcome aei_WIGGLE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_wiggle(2.0, 3.0, 4.0, -2, -1, 1, 2, 1, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  wiggle_demo 2:
//
// APIs:
//    gme_api_wiggle
//
// Description:
//	  四边的参数都为0时，创建立方体
//
// **********************************************************************************
outcome aei_WIGGLE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_wiggle(2.0, 3.0, 4.0, 0, 0, 0, 0, 1, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  wiggle_demo 3:
//
// APIs:
//    gme_api_wiggle
//
// Description:
//	  给定高度为0时，仅创建b样条曲面
//
// **********************************************************************************
outcome aei_WIGGLE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = NULL;
    API_BEGIN
    gme_api_wiggle(2.0, 3.0, 4.0, -2, -1, 1, 2, 0, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}