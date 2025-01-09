/*********************************************************************
 * @file    gme_cstrapi_1_reverse_wire_example.cpp
 * @brief
 * @details
 * @author  李雪鹏
 * @date    2024.7.29
 *********************************************************************/
#include "gme_cstrapi_1_reverse_wire_example.hxx"

#include <random>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_wire_demo 1:
//
// APIs:
//    gme_1_api_reverse_wire
//
// Description:
//    随机生成线段，组成一个开放的wire，分别将反转前后的COEDGE的中点和终点连线画成红色和绿色。
// **********************************************************************************
outcome aei_1_REVERSE_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* body = nullptr;                                        // 用于接收创建的BODY
    WIRE* wire = nullptr;                                        // 用于接收创建的WIRE
    std::default_random_engine generator;                        // 随机数生成器
    std::uniform_real_distribution<double> distribution(-5, 5);  // 随机数生成器
    SPAposition_vector positions;                                // 用于存储随机生成的点
    const int num = 10;                                          // 生成线段的数量
    EDGE* edges[num];                                            // 存储EDGE
    rgb_color red(1, 0, 0);                                      // 红色，用于指示反转前COEDGE的方向
    rgb_color green(0, 1, 0);                                    // 绿色，用于指示反转后COEDGE的方向

    API_BEGIN
    generator.seed(std::random_device()());
    for(int i = 0; i < num + 1; ++i) {
        positions.push_back(SPAposition(distribution(generator), distribution(generator), distribution(generator)));
    }
    for(int i = 0; i < num; ++i) {
        api_mk_ed_line(positions[i], positions[i + 1], edges[i]);
    }
    result = api_make_ewire(num, edges, body);
    wire = body->lump()->shell()->wire();
    ENTITY_LIST old_coedges;
    // 获取反转前的所有COEDGE，将他的中点和终点连线，描成红色
    api_get_coedges(wire, old_coedges);
    for(ENTITY* entity: old_coedges) {
        COEDGE* coedge = (COEDGE*)entity;
        SPAposition mid = coedge->edge()->mid_pos();
        SPAposition end = coedge->end_pos();
        EDGE* dir_edge = nullptr;
        api_mk_ed_line(mid, end, dir_edge);
        api_rh_set_entity_rgb(dir_edge, red);
        output_ents.add(dir_edge);
    }
    gme_1_api_reverse_wire(wire);
    ENTITY_LIST new_coedges;
    // 获取反转后的所有COEDGE，将他的中点和终点连线，描成绿色
    api_get_coedges(wire, new_coedges);
    for(ENTITY* entity: new_coedges) {
        COEDGE* coedge = (COEDGE*)entity;
        SPAposition mid = coedge->edge()->mid_pos();
        SPAposition end = coedge->end_pos();
        EDGE* dir_edge = nullptr;
        api_mk_ed_line(mid, end, dir_edge);
        api_rh_set_entity_rgb(dir_edge, green);
        output_ents.add(dir_edge);
    }
    API_END

    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  reverse_wire_demo 2:
//
// APIs:
//    gme_1_api_reverse_wire
//
// Description:
//    随机生成线段，组成一个有分支的wire，分别将反转前后的COEDGE的中点和终点连线画成红色和绿色。
// **********************************************************************************
outcome aei_1_REVERSE_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* body = nullptr;                                        // 用于接收创建的BODY
    WIRE* wire = nullptr;                                        // 用于接收创建的WIRE
    std::default_random_engine generator;                        // 随机数生成器
    std::uniform_real_distribution<double> distribution(-5, 5);  // 随机数生成器
    std::uniform_int_distribution<int> index_distribution;       // 随机数生成器，用于生成随机点的索引
    SPAposition_vector positions;                                // 用于存储随机生成的点
    const int num = 10;                                          // 生成线段的数量
    ENTITY_LIST edges;                                           // 用于存储创建的边
    rgb_color red(1, 0, 0);                                      // 红色，用于指示反转前COEDGE的方向
    rgb_color green(0, 1, 0);                                    // 绿色，用于指示反转后COEDGE的方向

    API_BEGIN
    generator.seed(std::random_device()());
    positions.push_back(SPAposition(distribution(generator), distribution(generator), distribution(generator)));

    for(int i = 0; i < num; ++i) {
        // 从已有点集合中随机选取一个点
        index_distribution = std::uniform_int_distribution<int>(0, positions.size() - 1);
        SPAposition start = positions[index_distribution(generator)];
        // 生成一个新的随机点
        SPAposition end(distribution(generator), distribution(generator), distribution(generator));
        // 将新点加入到点集合中
        positions.push_back(end);
        EDGE* edge;
        // 创建边并加入到边集合中
        api_mk_ed_line(start, end, edge);
        edges.add(edge);
    }
    api_unite_edges(edges, body, nullptr);

    wire = body->lump()->shell()->wire();
    ENTITY_LIST old_coedges;
    // 获取反转前的所有COEDGE，将他的中点和终点连线，描成红色
    api_get_coedges(wire, old_coedges);
    for(ENTITY* entity: old_coedges) {
        COEDGE* coedge = (COEDGE*)entity;
        SPAposition mid = coedge->edge()->mid_pos();
        SPAposition end = coedge->end_pos();
        EDGE* dir_edge = nullptr;
        api_mk_ed_line(mid, end, dir_edge);
        api_rh_set_entity_rgb(dir_edge, red);
        output_ents.add(dir_edge);
    }
    gme_1_api_reverse_wire(wire);
    ENTITY_LIST new_coedges;
    // 获取反转后的所有COEDGE，将他的中点和终点连线，描成绿色
    api_get_coedges(wire, new_coedges);
    for(ENTITY* entity: new_coedges) {
        COEDGE* coedge = (COEDGE*)entity;
        SPAposition mid = coedge->edge()->mid_pos();
        SPAposition end = coedge->end_pos();
        EDGE* dir_edge = nullptr;
        api_mk_ed_line(mid, end, dir_edge);
        api_rh_set_entity_rgb(dir_edge, green);
        output_ents.add(dir_edge);
    }
    API_END

    return result;
}