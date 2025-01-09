/*********************************************************************
 * @file    ewire_examples.cpp
 * @brief   演示 gme_api_make_ewire 接口的使用示例
 * @details 本文件包含两个示例函数，展示如何使用 gme_api_make_ewire 接口创建边线框（ewire）。
 *          示例1创建一个闭合的三边线框，示例2创建一个开放的四边线框。
 * @author  王书瑶
 * @date    2024.11.15
 *********************************************************************/

#include "gme_cstrapi_make_ewire_example.hxx"

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cnstruct.hxx"
#include "acis/cstrapi.hxx"
#include "acis/ewire.hxx"
#include "acis/intdef.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"

// **********************************************************************************
// C++ 示例：
//
// 标题：
//    ewire_demo_1
//
// 接口：
//    gme_api_make_ewire
//
// 描述：
//    使用 gme_api_make_ewire 接口生成一个简单的闭合边线框（ewire），由 3 条直线边组成。
// **********************************************************************************
outcome aei_MAKE_EWIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    /* 初始化区块 */

    const int num_edges = 3;             // 边的数量
    EDGE* edges[num_edges] = {nullptr};  // 边数组初始化为nullptr

    // 定义每条边的起点和终点位置
    SPAposition points[num_edges + 1] = {
      SPAposition(0.0, 0.0, 0.0),  // 点0
      SPAposition(5.0, 0.0, 0.0),  // 点1
      SPAposition(2.5, 5.0, 0.0),  // 点2
      SPAposition(0.0, 0.0, 0.0)   // 点3（与点0相同，闭合线框）
    };

    // 创建边
    for(int i = 0; i < num_edges; ++i) {
        EDGE* edge = nullptr;
        outcome result = api_mk_ed_line(points[i],      // 起点
                                        points[i + 1],  // 终点
                                        edge,           // 返回的边指针
                                        ptrAcisOpt      // ACIS 选项
        );

        if(!result.ok()) {
            return result;  // 如果创建失败，返回错误
        }

        edges[i] = edge;  // 将创建的边存入数组
    }

    BODY* body = nullptr;

    /* API 调用区块 */
    outcome result = gme_api_make_ewire(num_edges, edges, body, ptrAcisOpt);

    if(result.ok()) {
        output_ents.add(body);  // 将创建的 BODY 添加到输出实体列表
    }

    return result;
}

// **********************************************************************************
// C++ 示例：
//
// 标题：
//    ewire_demo_2
//
// 接口：
//    gme_api_make_ewire
//
// 描述：
//    使用 gme_api_make_ewire 接口生成一个开放的边线框（ewire），由 4 条直线边组成。
// **********************************************************************************
outcome aei_MAKE_EWIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    /* 初始化区块 */

    const int num_edges = 4;             // 边的数量
    EDGE* edges[num_edges] = {nullptr};  // 边数组初始化为nullptr

    // 定义每条边的起点和终点位置
    SPAposition points[num_edges + 1] = {
      SPAposition(0.0, 0.0, 0.0),  // 点0
      SPAposition(4.0, 0.0, 0.0),  // 点1
      SPAposition(4.0, 4.0, 0.0),  // 点2
      SPAposition(0.0, 4.0, 0.0),  // 点3
      SPAposition(0.0, 2.0, 0.0)   // 点4（开放线框，不闭合）
    };

    // 创建边
    for(int i = 0; i < num_edges; ++i) {
        EDGE* edge = nullptr;
        outcome result = api_mk_ed_line(points[i],      // 起点
                                        points[i + 1],  // 终点
                                        edge,           // 返回的边指针
                                        ptrAcisOpt      // ACIS 选项
        );

        if(!result.ok()) {
            return result;  // 如果创建失败，返回错误
        }

        edges[i] = edge;  // 将创建的边存入数组
    }

    BODY* body = nullptr;

    /* API 调用区块 */
    outcome result = gme_api_make_ewire(num_edges, edges, body, ptrAcisOpt);

    if(result.ok()) {
        output_ents.add(body);  // 将创建的 BODY 添加到输出实体列表
    }

    return result;
}
