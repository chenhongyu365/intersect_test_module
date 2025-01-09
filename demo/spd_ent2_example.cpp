/*********************************************************************
 * @file    spd_ent2_example.cpp
 * @brief   HD_PEL_ENT2 demo
 * @details
 * @author  葛宏泽
 * @date    2024.7.22
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
//    gme_HD_PEL_ENT2
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT2.
//    创建spd基本体无厚圆饼
// **********************************************************************************

outcome aei_HD_PEL_ENT2_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {1,1,1};
    double w[3] = {1,2,5};
    double r = 1;
    result = gme_HD_PEL_ENT2(p, w, r, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}