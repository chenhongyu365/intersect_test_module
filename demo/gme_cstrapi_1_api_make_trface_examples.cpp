/*********************************************************************
 * @file    gme_cstrapi_1_api_make_trface_examples.cpp
 * @brief
 * @details
 * @author  王康力
 * @date    2024.10.19
 *********************************************************************/

#include "gme_cstrapi_1_api_make_trface_examples.hxx"

#include "access.hpp"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/ellipse.hxx"
#include "acis/torus.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"
#include "template_examples.hxx"
// 甜甜圈
// uf和ut之间小于 resnor :  Cannot make zero area Torus
// uf和ut之间 大于等于 resnor 且 小于1.9999991 * resnor : 中断
// uf和ut之间 大于等于 1.9999991 * resnor 且小于 5 * 1e-7 - 1e-16 :生成实体绘制异常
outcome aei_1_MAKE_TRFACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = nullptr;
    API_BEGIN

    SPAposition center(0, 0, 0);
    SPAunit_vector normal(0, 1, 0);
    double major = 5;
    double minor = 2;
    SPAposition pnt(7, 1, 0);
    double uf = 1;
    double ut = 1 + 1.9999991 * SPAresnor;

    // 脊柱
    double vf = -M_PI_2;
    double vt = M_PI;
    result = api_make_trface(center, normal, major, minor, pnt, uf, ut, vf, vt, face);
    std::string res_str = process(result);
    std::cout << res_str << std::endl;
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// minor < resnor Cannot make zero area Torus
// normal == 0 operation unsuccessful API_FAILED
// major<0 且 major>minor  Cannot make zero area Torus
// ut-uf>2PI Difference between the tube angles is greater than 360, torus with complete cross section generated  TORUS_WRONG_TUBE_INPUT
// vt-vf>2PI Difference between the spine angles is greater than 360, complete torus generated                    TORUS_WRONG_SPINE_INPUT
outcome aei_1_MAKE_TRFACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN
    API_END
    return result;
}

// 苹果
// uf与ut在内部被裁切部分则 Cannot make zero area Torus
outcome aei_1_MAKE_TRFACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN
    API_END
    return result;
}

// 涡流
outcome aei_1_MAKE_TRFACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN

    API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO7(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO8(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO9(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO10(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO11(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO12(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO13(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO14(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO15(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO16(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO17(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO18(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}
outcome aei_1_MAKE_TRFACE_DEMO19(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    API_BEGIN API_END return result;
}