/*********************************************************************
 * @file    gme_cstrapi_mk_by_faces_example.cpp
 * @brief
 * @details
 * @author  韩昊欣
 * @date    2024.7.31
 *********************************************************************/
#include "gme_cstrapi_mk_by_faces_example.hxx"

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
//	  mk_by_faces_demo 1:
//
// APIs:
//    gme_api_mk_by_faces
//
// Description:
//	 向已有face(红色)的body中再次加入face(绿色)
//
// **********************************************************************************
outcome aei_MK_BY_FACES_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    // 用于传入需要处理的body
    BODY* in_body = nullptr;
    // 用于接收返回的body
    BODY* body = nullptr;
    // 用于测试的face
    FACE* face_a = NULL;
    FACE* face_b = NULL;
    FACE* face_c = NULL;
    // 用于传入所需的face数组
    FACE* faces[2];
    // 用于构建测试用face的点
    SPAposition a(0.0, 0.0, 0.0);
    SPAposition b(0.0, 1.0, 0.0);
    SPAposition c(1.0, 0.0, 0.0);
    SPAposition d(0.0, 0.0, 1.0);
    // 标注颜色
    rgb_color red(1, 0, 0);
    rgb_color green(0, 255, 0);
    API_BEGIN
    // 构造面
    api_make_plface(a, b, c, face_a);
    api_make_plface(a, b, d, face_b);
    api_make_plface(a, c, d, face_c);
    // 上色
    api_rh_set_entity_rgb(face_a, green);
    api_rh_set_entity_rgb(face_b, green);
    api_rh_set_entity_rgb(face_c, red);
    // 完成参数构造
    faces[0] = face_a;
    faces[1] = face_b;
    in_body = ACIS_NEW BODY(ACIS_NEW LUMP(ACIS_NEW SHELL(face_c, NULL, NULL), NULL));
    // 调用接口
    result = gme_api_mk_by_faces(in_body, 2, faces, body);
    if(result.ok()) {
        output_ents.add(body);
    }
    API_END

    return result;
}
