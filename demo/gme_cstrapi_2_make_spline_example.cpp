/*********************************************************************
 * @file    gme_cstrapi_2_make_spline_example.cpp
 * @brief   gme_2_api_make_spline demo
 * @details
 * @author  宋羽豪
 * @date    2023.8.24
 *********************************************************************/
#include "gme_cstrapi_2_make_spline_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/spline.hxx"
#include "acis/sps3srtn.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_spline_demo 1:
//
// APIs:
//    gme_2_api_make_spline
//
// Description:
//	  若u为奇数，二维向量空间到三维向量空间的映射为f(u,v)=(u,v,sin(u+v))
//    若u为偶数，二维向量空间到三维向量空间的映射为f(u,v)=(u,v,cos(u+v))
//
// **********************************************************************************
outcome aei_2_SPLINE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* gme_body = NULL;

    API_BEGIN
    // 构建spline
    const int num_u = 5;           // u方向点个数
    const int num_v = 5;           // v方向点个数
    std::vector<SPAposition> pts;  // 控制点数组, 先给出一行u方向的控制点, 然后是下一个v方向的一行u方向控制点

    // 插值点
    for(int u = 1; u <= num_v; ++u) {
        for(int v = 1; v <= num_u; ++v) {
            // 若u为奇数，二维向量空间到三维向量空间的映射为f(u,v)=(u,v,sin(u+v))
            if(u % 2 == 1) {
                double x = u;
                double y = v;
                double z = std::sin(u + v);
                pts.emplace_back(x, y, z);
            } else {
                // 若u为偶数，二维向量空间到三维向量空间的映射为f(u,v)=(u,v,cos(u+v))
                double x = u;
                double y = v;
                double z = std::cos(u + v);
                pts.emplace_back(x, y, z);
            }
        }
    }

    bs3_surface bs3_surf = bs3_surface_intp(num_u, num_v, pts.data(), NULL, NULL, NULL, NULL);
    spline this_spline(bs3_surf);

    // 生成单侧面BODY
    gme_2_api_make_spline(this_spline, gme_body);
    API_END

    if(result.ok()) {
        output_ents.add(gme_body);
    }
    return result;
}