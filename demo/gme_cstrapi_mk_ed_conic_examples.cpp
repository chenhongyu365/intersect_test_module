/*********************************************************************
 * @file    gme_cstrapi_mk_ed_conic_examples.cpp
 * @brief
 * @details
 * @author  mshct
 * @date    2024.7.30
 *********************************************************************/

#include "gme_cstrapi_mk_ed_conic_examples.hxx"

#include <ctime>
#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  mk_ed_conic_demo:
//
// APIs:
//    gme_api_mk_ed_conic
//
// Description:
// 生成随机有结果的情况
//
// **********************************************************************************

outcome aei_MK_ED_CONIC_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* edge = nullptr;
    // 生成随机数种子
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(-10000, 10000);  // 点坐标的大小范围
    std::uniform_real_distribution<double> v(-10, 10);        // 方向向量的大小范围
    std::uniform_real_distribution<double> w(0, 1);           // ρ的大小范围
    std::uniform_int_distribution<int> ni(0, 999);
    e.seed(time(0));
    // 生成随机点、方向、ρ
    SPAposition start = {u(e), u(e), u(e)};
    SPAposition end = {u(e), u(e), u(e)};
    SPAunit_vector start_tan = {v(e), v(e), v(e)};
    SPAunit_vector end_tan = {v(e), v(e), v(e)};
    double rho = w(e);
    int i = ni(e);
    if(i % 3 == 0)
        end = start + u(e) * start_tan + u(e) * end_tan;
    else if(i % 3 == 1)
        end_tan = normalise(w(e) * (end - start) + u(e) * start_tan);
    else if(i % 3 == 2)
        start_tan = normalise(w(e) * (end - start) + u(e) * end_tan);
    API_BEGIN
    result = gme_api_mk_ed_conic(start, start_tan, end, end_tan, rho, edge);
    API_END
    if(result.ok()) {
        api_rh_set_entity_rgb(edge, rgb_color(0.0, 0.0, 1.0));
    }
    output_ents.add(edge);
    return result;
}
