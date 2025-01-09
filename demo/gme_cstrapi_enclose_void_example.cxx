/*********************************************************************
 * @file    gme_cstrapi_enclose_void_example.cxx
 * @brief
 * @details
 * @author  罗坤
 * @date    2024.10.9
 *********************************************************************/
#include "gme_cstrapi_enclose_void_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/torus.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  enclose void demo:
//
// APIs:
//    gme_api_enclose_void
//
// Description:
//	  填充一个面
//
// **********************************************************************************
outcome aei_ENCLOSE_VOID_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN
    SPAposition pos1(-50, -50, -50), pos2(50, 50, 50);
    BODY* b;
    api_solid_block(pos1, pos2, b);
    ENTITY_LIST lst;
    api_get_faces(b, lst);
    std::vector<FACE*> face;
    for(int i = 0; i < lst.count(); i++) {
        ENTITY* tmp;
        api_deep_copy_entity(lst[i], tmp);
        face.push_back((FACE*)tmp);
    }
    for(auto e: face) {
        e->set_cont(0);
    }
    gme_api_enclose_void(face[0], true, true);

    if(result.ok()) {
        output_ents.add(face[0]);
    }
    API_END
    return result;
}
