/*********************************************************************
 * @file    gme_cstrapi_1_api_mk_ed_conic_examples.cpp
 * @brief	gme_1_api_mk_ed_conic demo
 * @details 用于可视化创建 B样条绘制的圆锥曲线
 * @author  赵川熠Ori
 * @date    2024.9.22
 *********************************************************************/
#include "access.hpp"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "gme_cstrapi_1_api_mk_ed_conic_examples.hxx"
#include "template_examples.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  make_edge_conic_demo:
//
// APIs:
//    gme_1_api_mk_ed_conic
//
// Description:
//	  起点在(-5, -8, 0) 切线方法为(1, -0.618, 0)
//    终点在(3, 7, 0)  切线方向为(-1, sqrt(3), 0)
//    rho = 0.4
// **********************************************************************************
outcome aei_MAKE_EDGE_CONIC_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* gme_conic = nullptr;
    SPAposition start(-5, -8, 0);
    SPAunit_vector start_tan(1, -0.618, 0);
    SPAposition end(3, 7, 0);
    SPAunit_vector end_tan(-1, sqrt(3), 0);
    double rho = 0.4;

    API_BEGIN
    check_outcome(gme_1_api_mk_ed_conic(start, start_tan, end, end_tan, rho, gme_conic));
    // check_outcome(api_mk_ed_conic(start, start_tan, end, end_tan, rho, acis_conic));

    API_END

    if(result.ok()) {
        output_ents.add(gme_conic);
    }
    return result;
}
