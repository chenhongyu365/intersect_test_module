/*********************************************************************
 * @file    gme_cstrapi_2_make_trface_example.cpp
 * @brief
 * @details
 * @author  王菲
 * @date    2024.11.20
 *********************************************************************/
#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "gme_cstrapi_make_trface_example.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//    trface_demo 1:
//
// APIs:
//    api_2_make_trface
//
// Description:
//    u、v不完整的甜甜圈环面
//
// **********************************************************************************

outcome aei_2_MAKE_TRFACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    API_BEGIN
    FACE* face = NULL;
    outcome result;

    // API调用块
    SPAposition center(0.0, 0.0, 0.0);
    SPAunit_vector normal(0.0, 0.0, 1.0);
    double major = 3.0;
    double minor = 1.0;
    SPAposition pnt(1.0, 0.0, 0.0);
    double uf = 0.0;
    double ut = 1.5 * M_PI;
    double vf = 0.0;
    double vt = 1.5 * M_PI;

    // 调用api_make_trface生成环面片段
    // result = api_make_trface(center, normal, major, minor, pnt, uf, ut, vf, vt, face, ptrAcisOpt);
    result = gme_2_api_make_trface(center, normal, major, minor, pnt, uf, ut, vf, vt, face, ptrAcisOpt);

    // 如果生成成功，将结果添加到output_ents中
    if(result.ok()) {
        output_ents.add(face);  // 将生成的face添加到ENTITY_LIST中
    } else {
        std::cerr << "Failed to generate torus face." << std::endl;
    }
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//    trface_demo 2:
//
// APIs:
//    api_2_make_trface
//
// Description:
//    漩涡形状的部分环面，u 和 v 范围均非完整
//
// **********************************************************************************
outcome aei_2_MAKE_TRFACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    SPAunit_vector normal = SPAunit_vector(0, 0, 1);
    double major = 1.0;
    double minor = 1.0;
    SPAposition pnt = SPAposition(1, 0, 0);
    double uf = M_PI / 4;
    double ut = 3 * M_PI / 2;  // u 范围为部分区域
    double vf = M_PI / 6;
    double vt = M_PI / 2;  // v 范围为部分区域
    result = api_make_trface(center, normal, major, minor, pnt, uf, ut, vf, vt, face, ptrAcisOpt);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}
