#include "gme_cstrapi_1_solid_block_examples.hxx"

#include "access.hpp"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "template_examples.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  solid_block_demo:
//
// APIs:
//    gme_1_api_solid_block
//
// Description:
//	  创建一个长方形的实体块
// **********************************************************************************
outcome aei_1_SOLID_BLOCK_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* acis_block = nullptr;
    BODY* gme_block = nullptr;
    SPAposition pt1(-3.0, -3.0, 1.0);
    SPAposition pt2(4.0, 4.0, 8.0);

    API_BEGIN
    check_outcome(gme_1_api_solid_block(pt1, pt2, gme_block, nullptr));

    API_END

    if(result.ok()) {
        output_ents.add(gme_block);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  solid_block_demo:
//
// APIs:
//    gme_1_api_solid_block
//
// Description:
//	  当z坐标相同的时候，创建一个长方形实体面片
// **********************************************************************************
outcome aei_1_SOLID_BLOCK_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* acis_block = nullptr;
    BODY* gme_block = nullptr;
    SPAposition pt1(-4.0, -4.0, -1.0);
    SPAposition pt2(4.0, 4.0, -1.0);

    API_BEGIN
    check_outcome(gme_1_api_solid_block(pt1, pt2, gme_block, nullptr));

    API_END

    if(result.ok()) {
        output_ents.add(gme_block);
    }
    return result;
}
