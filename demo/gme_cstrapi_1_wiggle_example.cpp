/*********************************************************************
 * @file    gme_cstrapi_1_wiggle_example.cpp
 * @brief
 * @details
 * @author  MOSSKEER 王可
 * @date    2024.7.29
 *********************************************************************/

#include "gme_cstrapi_1_wiggle_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_wiggle_demo 1:
//
// APIs:
//    gme_1_api_wiggle
//
// Description:
//    构造给定高度，各参数在合法范围内的块，样条面四边参数值分别为1，-2，2，0
// **********************************************************************************
outcome aei_1_WIGGLE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* body = nullptr;

    /* API Call Block */
    API_BEGIN

    gme_1_api_wiggle(3, 4, 5, 1, -2, 2, 0, 1, body);

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
//	  1_wiggle_demo 2:
//
// APIs:
//    gme_1_api_wiggle
//
// Description:
//    不给定高度，各参数在合法范围，仅创建样条面
// **********************************************************************************
outcome aei_1_WIGGLE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* body = nullptr;

    /* API Call Block */
    API_BEGIN

    gme_1_api_wiggle(3, 4, 5, 1, -2, 2, 0, 0, body);

    API_END
    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}
