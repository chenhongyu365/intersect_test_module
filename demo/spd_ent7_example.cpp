/*********************************************************************
 * @file    spd_ent7_example.cpp
 * @brief   HD_PEL_ENT7 demo
 * @details
 * @author  CastaneaG
 * @date    2023.7.22
 *********************************************************************/

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
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
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    完整甜甜圈圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 2*M_PI, 3, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    部分甜甜圈圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 1.2*M_PI, 3, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    完整苹果圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 2*M_PI, 15, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    部分苹果圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 1.2*M_PI, 15, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    完整柠檬圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, -10, start, 2*M_PI, 15, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    部分柠檬圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, -10, start, 1.2*M_PI, 15, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    完整漩涡圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO7(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 2*M_PI, 10, body);
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
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT7
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT7.
//    部分漩涡圆环
// **********************************************************************************
outcome aei_HD_PEL_ENT7_DEMO8(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double center[3] = {0, 0, 0};
    double normal[3] = {0, 0, 1};
    double start[3] = {0, 1, 0};
    gme_HD_PEL_ENT7(center, normal, 10, start, 1.2*M_PI, 10, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}