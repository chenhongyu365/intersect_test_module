/*********************************************************************
 * @file    gme_cstrapi_face_law_example.cpp
 * @brief   api_face_law demo
 * @details
 * @author  hosimiAKE
 * @date    2023.7.31
 *********************************************************************/
#include "gme_cstrapi_face_law_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_law_demo 1:
//
// APIs:
//    gme_api_face_law
//
// Description:
//	  平凡情况
//
// **********************************************************************************
outcome aei_FACE_LAW_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = nullptr;
    // 得到law
    law* in_law = nullptr;
    std::string law_str = "VEC(u, v, u^2 + v^2)";  // 一个抛物面的law对应的字符串
    // 创建一个抛物面的law
    api_str_to_law(law_str.c_str(), &in_law);
    // 设uv的上下限
    double minu = -0.5;
    double maxu = 0.5;
    double minv = -0.5;
    double maxv = 0.5;
    API_BEGIN
    outcome result = gme_api_face_law(in_law, minu, maxu, minv, maxv, gme_face);
    API_END

    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_law_demo 2:
//
// APIs:
//    gme_api_face_law
//
// Description:
//	  次平凡情况
//
// **********************************************************************************
outcome aei_FACE_LAW_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = nullptr;
    // 得到law
    law* in_law = nullptr;
    std::string law_str = "VEC(u^3, u - v, u + v)";  // 一个law对应的字符串
    // 创建一个抛物面的law
    api_str_to_law(law_str.c_str(), &in_law);
    // 设uv的上下限
    double minu = -1;
    double maxu = 1;
    double minv = -1;
    double maxv = 1;
    API_BEGIN
    outcome result = gme_api_face_law(in_law, minu, maxu, minv, maxv, gme_face);
    API_END

    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_law_demo 3:
//
// APIs:
//    gme_api_face_law
//
// Description:
//	  非平凡情况
//
// **********************************************************************************
outcome aei_FACE_LAW_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* gme_face = nullptr;
    // 得到law
    law* in_law = nullptr;
    std::string law_str = "VEC(Cos(u) * Cos(v) * Sin(v), Cos(u) * Sin(v), Sin(u))";
    // 创建一个抛物面的law
    api_str_to_law(law_str.c_str(), &in_law);
    // 设uv的上下限
    double minu = -M_PI / 2.0;
    double maxu = M_PI / 3.0;
    double minv = M_PI / 6.0;
    double maxv = 1.5 * M_PI;
    API_BEGIN
    outcome result = gme_api_face_law(in_law, minu, maxu, minv, maxv, gme_face);
    API_END

    if(result.ok()) {
        output_ents.add(gme_face);
    }
    return result;
}