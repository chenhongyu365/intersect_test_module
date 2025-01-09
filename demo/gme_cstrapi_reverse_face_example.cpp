/*********************************************************************
 * @file    gme_cstrapi_reverse_face_example.cpp
 * @brief	创建各种类型的face，分别绘制原face、经过api_reverse_face和
 *			gme_reverse_face翻转得到的face，进行对比
 * @details
 * @author  全志成
 * @date    2023.7.29
 *********************************************************************/
#include "gme_cstrapi_reverse_face_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/point.hxx"
#include "acis/strdef.hxx"
#include "acis/vector.hxx"
#include "acis/plane.hxx"
#include "acis/straight.hxx"

namespace {

    /**
     * @brief   		创建 vertex
     * @param[in]    	pos 位置
     * @return     		VERTEX 创建的vertex
     */
    VERTEX* create_vertex(const SPAposition& pos);

    /**
     * @brief   		根据起点与终点 vertex 构建 edge
     * @param[in]    	v1 起始vertex
     * @param[in]    	v2 终点vertex
     * @return     		EDGE 创建的edge
     */
    EDGE* create_straight_edge_by_vertexs(VERTEX* v1, VERTEX* v2);

    VERTEX* create_vertex(const SPAposition& pos) {
        APOINT* apoint = ACIS_NEW APOINT(pos);     // 根据SPAposition创建APOINT
        VERTEX* vertex = ACIS_NEW VERTEX(apoint);  // 根据APOINT创建VERTEX
        return vertex;
    }

    EDGE* create_straight_edge_by_vertexs(VERTEX* v1, VERTEX* v2) {
        // v2-v1的得到直线方向非单位向量vec
        SPAvector vec = v2->geometry()->coords() - v1->geometry()->coords();
        // 根据vec单位化方向向量以及v1点坐标，构建直线
        STRAIGHT* straight = ACIS_NEW STRAIGHT(v1->geometry()->coords(), normalise(vec));
        // 根据两个点以及直线构建edge 方向与straignt相同

        EDGE* edge = ACIS_NEW EDGE(v1, v2, straight, FORWARD);
        return edge;
    }
}


// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_face_demo 1:
//
// APIs:
//    gme_api_reverse_face
//
// Description:
//	  部分球面，两侧分别为acis和gme调用reverse_face，中间为face原型
//
// **********************************************************************************
outcome aei_REVERSE_FACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    SPAposition center = SPAposition(0, 0, 0);
    double radius = 2.5;
    SPAunit_vector uv_oridir = SPAunit_vector(1, 0, 0);
    SPAunit_vector pole_dir = SPAunit_vector(0, 0, 1);
    double slat = -3 * M_PI / 8;
    double elat = 3 * M_PI / 8;
    double slon = -1 * M_PI / 8;
    double elon = 2 * M_PI / 3;
    result = api_make_spface(center, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    if(result.ok()) {
        output_ents.add(face);
    }
    SPAposition center1 = SPAposition(0, 3, 0);
    result = api_make_spface(center1, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    api_reverse_face(face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    if(result.ok()) {
        output_ents.add(face);
    }
    SPAposition center2 = SPAposition(0, -3, 0);
    result = api_make_spface(center2, radius, uv_oridir, pole_dir, slat, elat, slon, elon, face);
    gme_api_reverse_face(face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    if(result.ok()) {
        output_ents.add(face);
    }
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_face_demo 2:
//
// APIs:
//    gme_api_reverse_face
//
// Description:
//	  平面，两侧分别为acis和gme调用reverse_face，中间为face原型
//
// **********************************************************************************
outcome aei_REVERSE_FACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* acis_face = nullptr;
    FACE* gme_face = nullptr;
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    API_BEGIN
    // 构造待测试的平面
    SPAposition p1(0, 8, 0);
    SPAposition p2(-8, 0, 0);
    SPAposition p3(8, 0, 0);
    api_make_plface(p1, p2, p3, acis_face);
    api_rh_set_entity_rgb(acis_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(acis_face);
    SPAposition p4(0, 8, 5);
    SPAposition p5(-8, 0, 5);
    SPAposition p6(8, 0, 5);
    api_make_plface(p4, p5, p6, gme_face);
    gme_api_reverse_face(gme_face);
    api_rh_set_entity_rgb(gme_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(gme_face);

	SPAposition p7(0, 8, -5);
    SPAposition p8(-8, 0, -5);
    SPAposition p9(8, 0, -5);
    api_make_plface(p7, p8, p9, acis_face);
    api_reverse_face(acis_face);
    api_rh_set_entity_rgb(acis_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
	output_ents.add(acis_face);

    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_face_demo 2:
//
// APIs:
//    gme_api_reverse_face
//
// Description:
//	  有两个loop的矩形平面，分别为face原型和gme调用reverse_face得到的face
//
// **********************************************************************************
outcome aei_REVERSE_FACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;
    FACE* gme_face = nullptr;
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色
    // 创建 vertex
    VERTEX* v0 = create_vertex(SPAposition(10, -10, 5));
    VERTEX* v1 = create_vertex(SPAposition(10, 10, 5));
    VERTEX* v2 = create_vertex(SPAposition(-10, 10, 5));
    VERTEX* v3 = create_vertex(SPAposition(-10, -10, 5));
    VERTEX* v4 = create_vertex(SPAposition(4, -4, 5));
    VERTEX* v5 = create_vertex(SPAposition(-4, -4, 5));
    VERTEX* v6 = create_vertex(SPAposition(-4, 4, 5));
    VERTEX* v7 = create_vertex(SPAposition(4, 4, 5));
    // 根据 vertex 创建 edge
    EDGE* e0 = create_straight_edge_by_vertexs(v0, v1);
    EDGE* e1 = create_straight_edge_by_vertexs(v1, v2);
    EDGE* e2 = create_straight_edge_by_vertexs(v2, v3);
    EDGE* e3 = create_straight_edge_by_vertexs(v3, v0);
    EDGE* e4 = create_straight_edge_by_vertexs(v4, v5);
    EDGE* e5 = create_straight_edge_by_vertexs(v5, v6);
    EDGE* e6 = create_straight_edge_by_vertexs(v6, v7);
    EDGE* e7 = create_straight_edge_by_vertexs(v7, v4);
    // 创建 外圈loop
    std::vector<EDGE*> edges{e0, e1, e2, e3};
    std::vector<REVBIT> senses{FORWARD, FORWARD, FORWARD, FORWARD};
    std::vector<COEDGE*> coedges(edges.size());
    // 根据 edges vector 和 senses vector 构建 coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges[i] = ACIS_NEW COEDGE(edges[i], senses[i], nullptr, nullptr);
    }
    // 将coedges中每个coedge的next与previous指针指向对应coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges[i]->set_next(coedges[(i + 1) % edges.size()]);

        coedges[i]->set_previous(coedges[(i - 1 + edges.size()) % edges.size()]);
    }
    LOOP* loop = ACIS_NEW LOOP(coedges.front(), nullptr);
    // 创建 内圈loop
    std::vector<EDGE*> edges1{e4, e5, e6, e7};
    std::vector<REVBIT> senses1{FORWARD, FORWARD, FORWARD, FORWARD};
    std::vector<COEDGE*> coedges1(edges1.size());
    // 根据 edges vector 和 senses vector 构建 coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges1[i] = ACIS_NEW COEDGE(edges1[i], senses1[i], nullptr, nullptr);
    }
    // 将coedges中每个coedge的next与previous指针指向对应coedge
    for(int i = 0; i < edges1.size(); ++i) {
        coedges1[i]->set_next(coedges1[(i + 1) % edges1.size()]);

        coedges1[i]->set_previous(coedges1[(i - 1 + edges1.size()) % edges1.size()]);
    }
    LOOP* loop1 = ACIS_NEW LOOP(coedges1.front(), nullptr);
    loop->set_next(loop1);
    // 创建 surface
    PLANE* sf = ACIS_NEW PLANE(v0->geometry()->coords(), SPAunit_vector(0, 0, 1));
    // 创建face
    face = ACIS_NEW FACE(loop, nullptr, sf, FORWARD);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    API_BEGIN
    // 创建 vertex
    VERTEX* v0 = create_vertex(SPAposition(10, -10, -5));
    VERTEX* v1 = create_vertex(SPAposition(10, 10, -5));
    VERTEX* v2 = create_vertex(SPAposition(-10, 10, -5));
    VERTEX* v3 = create_vertex(SPAposition(-10, -10, -5));
    VERTEX* v4 = create_vertex(SPAposition(4, -4, -5));
    VERTEX* v5 = create_vertex(SPAposition(-4, -4, -5));
    VERTEX* v6 = create_vertex(SPAposition(-4, 4, -5));
    VERTEX* v7 = create_vertex(SPAposition(4, 4, -5));
    // 根据 vertex 创建 edge
    EDGE* e0 = create_straight_edge_by_vertexs(v0, v1);
    EDGE* e1 = create_straight_edge_by_vertexs(v1, v2);
    EDGE* e2 = create_straight_edge_by_vertexs(v2, v3);
    EDGE* e3 = create_straight_edge_by_vertexs(v3, v0);
    EDGE* e4 = create_straight_edge_by_vertexs(v4, v5);
    EDGE* e5 = create_straight_edge_by_vertexs(v5, v6);
    EDGE* e6 = create_straight_edge_by_vertexs(v6, v7);
    EDGE* e7 = create_straight_edge_by_vertexs(v7, v4);
    // 创建 外圈loop
    std::vector<EDGE*> edges{e0, e1, e2, e3};
    std::vector<REVBIT> senses{FORWARD, FORWARD, FORWARD, FORWARD};
    std::vector<COEDGE*> coedges(edges.size());
    // 根据 edges vector 和 senses vector 构建 coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges[i] = ACIS_NEW COEDGE(edges[i], senses[i], nullptr, nullptr);
    }
    // 将coedges中每个coedge的next与previous指针指向对应coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges[i]->set_next(coedges[(i + 1) % edges.size()]);

        coedges[i]->set_previous(coedges[(i - 1 + edges.size()) % edges.size()]);
    }
    LOOP* loop = ACIS_NEW LOOP(coedges.front(), nullptr);
    // 创建 内圈loop
    std::vector<EDGE*> edges1{e4, e5, e6, e7};
    std::vector<REVBIT> senses1{FORWARD, FORWARD, FORWARD, FORWARD};
    std::vector<COEDGE*> coedges1(edges1.size());
    // 根据 edges vector 和 senses vector 构建 coedge
    for(int i = 0; i < edges.size(); ++i) {
        coedges1[i] = ACIS_NEW COEDGE(edges1[i], senses1[i], nullptr, nullptr);
    }
    // 将coedges中每个coedge的next与previous指针指向对应coedge
    for(int i = 0; i < edges1.size(); ++i) {
        coedges1[i]->set_next(coedges1[(i + 1) % edges1.size()]);

        coedges1[i]->set_previous(coedges1[(i - 1 + edges1.size()) % edges1.size()]);
    }
    LOOP* loop1 = ACIS_NEW LOOP(coedges1.front(), nullptr);
    loop->set_next(loop1);
    // 创建 surface
    PLANE* sf = ACIS_NEW PLANE(v0->geometry()->coords(), SPAunit_vector(0, 0, 1));
    // 创建face
    gme_face = ACIS_NEW FACE(loop, nullptr, sf, FORWARD);
    gme_api_reverse_face(gme_face);
    api_rh_set_entity_rgb(gme_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(gme_face);
    API_END
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_face_demo 4:
//
// APIs:
//    gme_api_reverse_face
//
// Description:
//	  圆环面，两侧分别为acis和gme调用reverse_face，中间为face原型
//
// **********************************************************************************
outcome aei_REVERSE_FACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* acis_face = nullptr;
    FACE* gme_face = nullptr;
    FACE* face = nullptr;
    double color_trans = 1.0 / 255;  // 用于计算rgb颜色

    /* API Call Block */
    API_BEGIN

	double major = 10;
    double minor = 5;

    double us = 0;
    double ue = 360;
    double vs = 0;
    double ve = 120;

    api_face_torus(SPAposition(0, 12, 0), major, minor, us, ue, vs, ve, nullptr, acis_face);
    api_face_torus(SPAposition(0, -12, 0), major, minor, us, ue, vs, ve, nullptr,gme_face);
    api_face_torus(SPAposition(0, 0, 0), major, minor, us, ue, vs, ve, nullptr, face);

	api_reverse_face(acis_face);
    api_rh_set_entity_rgb(acis_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(acis_face);
    gme_api_reverse_face(gme_face);
    api_rh_set_entity_rgb(gme_face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(gme_face);
    api_rh_set_entity_rgb(face, rgb_color(255 * color_trans, 127 * color_trans, 80 * color_trans));  // 珊瑚色 #FF7F50
    output_ents.add(face);
    API_END

    return result;
}
