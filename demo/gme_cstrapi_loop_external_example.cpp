/*********************************************************************
 * @file    gme_api_loop_exteranl_example.cpp
 * @brief   查询函数 gme_api_loop_external 的例子演示
 * @details 给出了一个含有多个环的面，为了使用gme_api_loop_external查询每个环是外围环还是内孔环
 * @author  赵川熠
 * @date    2024.10.16
 *********************************************************************/

#include "gme_cstrapi_loop_external_example.hxx"

#include "acis/cstrapi.hxx"
#include "acis/ellipse.hxx"
#include "acis/plane.hxx"
#include "acis/straight.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"

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

FACE* create_face_by_edges(std::vector<EDGE*>& edges, std::vector<REVBIT>& senses, const SPAunit_vector& vec) {
    // 创建PLANE 根据其中一个edge的起始点坐标和法向量
    PLANE* sf = ACIS_NEW PLANE(edges[0]->start()->geometry()->coords(), vec);
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
    // 创建loop与face
    LOOP* loop = ACIS_NEW LOOP(coedges.front(), nullptr);
    FACE* face = ACIS_NEW FACE(loop, nullptr, sf, FORWARD);

    return face;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  api_loop_external_demo:
//
// APIs:
//    gme_api_loop_external
//
// Description:
//	  创建一个边长为2的方形面，其中央挖去一个半径为0.5的圆
//    展示这个面图形
// **********************************************************************************
outcome aei_LOOP_EXTERNAL_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = nullptr;
    BODY* body = nullptr;
    LOOP* inner_loop = nullptr;
    LOOP* outer_loop = nullptr;

    API_BEGIN

    // 创建顶点
    VERTEX* v0 = create_vertex(SPAposition(-1, -1, 0));
    VERTEX* v1 = create_vertex(SPAposition(1, -1, 0));
    VERTEX* v2 = create_vertex(SPAposition(1, 1, 0));
    VERTEX* v3 = create_vertex(SPAposition(-1, 1, 0));
    // 创建边
    EDGE* e0 = create_straight_edge_by_vertexs(v0, v1);
    EDGE* e1 = create_straight_edge_by_vertexs(v1, v2);
    EDGE* e2 = create_straight_edge_by_vertexs(v2, v3);
    EDGE* e3 = create_straight_edge_by_vertexs(v3, v0);
    // 创建面
    std::vector<EDGE*> edges = {e0, e1, e2, e3};
    std::vector<REVBIT> senses = {FORWARD, FORWARD, FORWARD, FORWARD};
    FACE* face = create_face_by_edges(edges, senses, SPAunit_vector(0, 0, 1));

    // 创建圆环
    SPAposition circle_center(0, 0, 0);
    double radius = 0.5;
    SPAunit_vector normal(0, 0, 1);
    SPAposition circle_start = circle_center + SPAvector(radius, 0, 0);  // 圆的起点
                                                                         // 创建圆的几何对象
    ELLIPSE* circle_curve = ACIS_NEW ELLIPSE(circle_center, normal, SPAvector(radius, 0, 0), 1.0);
    // 创建圆的顶点（对于闭合的圆，起点和终点是同一个顶点）
    VERTEX* circle_vertex = create_vertex(circle_start);
    // 创建圆的边（EDGE）
    EDGE* circle_edge = ACIS_NEW EDGE(circle_vertex, circle_vertex, circle_curve, FORWARD);
    // 创建圆的 COEDGE 和 LOOP
    COEDGE* circle_coedge = ACIS_NEW COEDGE(circle_edge, REVERSED, nullptr, nullptr);  // 内环需要 REVERSED
    circle_coedge->set_previous(circle_coedge);
    circle_coedge->set_next(circle_coedge);
    LOOP* inner_loop = ACIS_NEW LOOP(circle_coedge, nullptr);
    // 将圆的 LOOP 连接到 FACE
    inner_loop->set_face(face);
    face->loop()->set_next(inner_loop);

    // 构建 BODY
    SHELL* shell = ACIS_NEW SHELL(face, nullptr, nullptr);
    LUMP* lump = ACIS_NEW LUMP(shell, nullptr);
    body = ACIS_NEW BODY(lump);

    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}