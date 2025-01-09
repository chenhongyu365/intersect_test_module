/*********************************************************************
 * @file    spd_ent8_example.cpp
 * @brief   HD_PEL_ENT8 demo
 * @details
 * @author  hosimiAKE
 * @date    2023.7.25
 *********************************************************************/

#include "access.hpp"
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
//    gme_HD_PEL_ENT8
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT8.
//    一个高大于底面半径的旋转半椭球体
// **********************************************************************************
outcome aei_HD_PEL_ENT8_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {0, 0, 0};
    const double one_over_sqrt3 = std::sqrt(1.0 / 3.0);
    double w[3] = {one_over_sqrt3, one_over_sqrt3, one_over_sqrt3};
    double r = 10;
    double h = 20;
    gme_HD_PEL_ENT8(p, w, r, h, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }
    // acis_api_save_entity("C:\\Users\\86139\\Desktop\\test.sat", body);

    return result;
}  // **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT8
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT8.
//    一个高小于底面半径的旋转半椭球体
// **********************************************************************************
outcome aei_HD_PEL_ENT8_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {0, 0, 0};
    double w[3] = {0, 0, -1};
    double r = 20;
    double h = 10;
    gme_HD_PEL_ENT8(p, w, r, h, body);
    API_END
    if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}
