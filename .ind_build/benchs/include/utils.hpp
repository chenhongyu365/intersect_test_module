/*********************************************************************
 * @file    utils.hpp
 * @brief   自动化测试相关函数
 * @details
 * @author  Shivelino
 * @date    2023.10.2
 * @version 0.2.0
 * @par Copyright(c):
 * @par todo:
 * @par history:
 *********************************************************************/
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>

#include "acis/cstrapi.hxx"
#include "acis/curve.hxx"
#include "acis/kernapi.hxx"
#include "acis/point.hxx"
#include "acis/surface.hxx"
#include "acis/transfrm.hxx"
#include "acis_utils/acis_utils.hpp"

// 用于输出错误发生的编译模式
#ifdef _DEBUG
const std::string OPER_MODE = "DEBUG";
#else
const std::string OPER_MODE = "RELEASE";
#endif


/**
 * @brief 模板方法类，该方法用于判断经过ACIS和GME Debug函数所得结果是否一致
 */
class EqualDebug {
    static const int DEFAULT_STR_SIZE = 256;  // 考虑到有多个参数的情况，开辟较大空间用于存储字符串

    /**
     * @brief 调用ACIS中的方法，将参数写入文件
     * 该方法需由子类重写
     * @param fp 待写入文件
     */
    inline void acis_debug(FILE* fp) {}

    /**
     * @brief 调用ACIS中的方法，将参数写入字符串
     * 该方法需由子类重写
     * @param s 待写入字符串
     */
    inline void acis_debug_str(char* s) {}

    /**
     * @brief 调用GME中的方法，将参数写入文件
     * 该方法需由子类重写
     * @param fp 待写入文件
     */
    inline void gme_debug(FILE* fp) {}

    /**
     * @brief 调用GME中的方法，将参数写入字符串
     * 该方法需由子类重写
     * @param s 待写入字符串
     */
    inline void gme_debug_str(char* s) {}

  public:
    /**
     * @brief 用于判断参数写入文件后，文件内容是否相等
     * @return 文件内容相等情况
     */
    inline bool is_equal(std::string test_name){
        std::string acis_file = "acis_debug" + test_name + ".txt";
        std::string gme_file = "gme_debug" + test_name + ".txt";
        // 通过acis将参数写入到文件中，再读取至字符串中
        // 写入实数到文件需要用gme_fopen()，以避免跨模块操纵指针
        FILE* acis_w_fp = acis_fopen(acis_file.c_str(), "w");
        acis_debug(acis_w_fp);
        if(acis_w_fp) acis_fclose(acis_w_fp);

        std::ifstream acis_r_ifs(acis_file);
        std::string acis_str(std::istreambuf_iterator<char>{acis_r_ifs}, {});
        // 关闭文件流并删除文件
        acis_r_ifs.close();
        remove(acis_file.c_str());

        // 使用GME做同样操作
        FILE* gme_w_fp = acis_fopen(gme_file.c_str(), "w");
        gme_debug(gme_w_fp);
        if(gme_w_fp) acis_fclose(gme_w_fp);

        std::ifstream gme_r_ifs(gme_file);
        std::string gme_str(std::istreambuf_iterator<char>{gme_r_ifs}, {});
        gme_r_ifs.close();
        remove(gme_file.c_str());

        // 比较二者是否相等
        return gme_str == acis_str;
    }

    /**
     * @brief 用于判断参数写入字符串后，字符串内容是否相等
     * @return 字符串内容相等情况
     */
    inline bool is_equal_str(){
        char acis_str[DEFAULT_STR_SIZE] = {'\0'};
        char gme_str[DEFAULT_STR_SIZE] = {'\0'};

        acis_debug_str(acis_str);
        gme_debug_str(gme_str);
        return 0 == strcmp(acis_str, gme_str);
    }
};

/**
 * @brief 打印实体的所有点坐标
 */
inline void gme_print_all_vertex(ENTITY* entity, const char* front_string = ""){
    if(entity == nullptr) {
        return;
    }

    ENTITY_LIST vertex_list;
    api_get_vertices(entity, vertex_list);
    int n = vertex_list.iteration_count();
    for(int i = 0; i < n; i++) {
        auto* vertex = (VERTEX*)vertex_list[i];
        SPAposition pos = vertex->geometry()->coords();
        printf("%s vertex %d: (%f, %f, %f)\n", front_string, i, pos.x(), pos.y(), pos.z());
    }
}

/**
 * @brief 打印body的所有点信息
 * @param body 待打印的body
 */
inline void printVertTopo(BODY* b){
    ENTITY_LIST b_verts;
    api_get_vertices(b, b_verts);
    for(auto v: b_verts) {
        auto* b_vert = (VERTEX*)v;
        ENTITY_LIST edges;
        api_get_edges(b_vert, edges);
        std::cout << "(" << b_vert->geometry()->coords().x() << "," << b_vert->geometry()->coords().y() << "," << b_vert->geometry()->coords().z() << ")" << b_vert->count_edges() << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief 打印body的所有面信息
 * @param body 待打印的body
 */
inline void printFaceTopo(BODY* b){
    ENTITY_LIST b_faces;
    api_get_faces(b, b_faces);
    int i = 0;
    for(auto f: b_faces) {
        FACE* b_face = (FACE*)f;
        ENTITY_LIST coedges;
        api_get_coedges(b_face, coedges);
        const char* surf_type = b_face->geometry()->type_name();
        std::cout << "FACE " << i++ << "(" << surf_type << "):" << std::endl;
        int j = 0;
        for(auto ce: coedges) {
            auto* coedge = (COEDGE*)ce;
            auto start_coord = coedge->start()->geometry()->coords();
            auto end_coord = coedge->end()->geometry()->coords();
            if(is_BODY(b) && b->transform()) {
                start_coord *= b->transform()->transform();
                end_coord *= b->transform()->transform();
            }
            std::cout << "COEDGE " << j++ << ":(" << start_coord.x() << "," << start_coord.y() << "," << start_coord.z() << ")";
            std::cout << "->(" << end_coord.x() << "," << end_coord.y() << "," << end_coord.z() << ") ";

            if(coedge->edge()->geometry())
                std::cout << coedge->edge()->geometry()->type_name() << std::endl;
            else
                std::cout << "None type" << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * @brief 打印body的所有线信息
 * @param body 待打印的body
 */
inline void printWireTopo(BODY* b){
    ENTITY_LIST b_wires;
    api_get_wires(b, b_wires);
    int i = 0;
    for(auto w: b_wires) {
        WIRE* b_wire = (WIRE*)w;
        ENTITY_LIST coedges;
        api_get_coedges(b_wire, coedges);
        std::cout << "WIRE " << i++ << ":" << std::endl;
        int j = 0;
        for(auto ce: coedges) {
            auto* coedge = (COEDGE*)ce;
            auto start_coord = coedge->start()->geometry()->coords();
            auto end_coord = coedge->end()->geometry()->coords();
            if(is_BODY(b) && b->transform()) {
                start_coord *= b->transform()->transform();
                end_coord *= b->transform()->transform();
            }
            std::cout << "COEDGE " << j++ << ":(" << start_coord.x() << "," << start_coord.y() << "," << start_coord.z() << ")";
            std::cout << "->(" << end_coord.x() << "," << end_coord.y() << "," << end_coord.z() << ") ";

            if(coedge->edge()->geometry())
                std::cout << coedge->edge()->geometry()->type_name() << std::endl;
            else
                std::cout << "None type" << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * @brief 获取当前线程ID
 */
inline std::string get_pid_string(){
    std::thread::id this_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << this_id;
    return ss.str();
}

/**
 * @brief 生成随机数字符串
 */
inline std::string get_rand_string(){
    // 生成随机整数
    std::random_device rd;                                     // 获取一个随机数生成器的种子
    std::mt19937 gen(rd());                                    // 使用 Mersenne Twister 引擎
    std::uniform_int_distribution<int> distribution(1, 1e+6);  // 范围为 [1, 1e+6] 的整数
    int randomInt = distribution(gen);
    return std::to_string(randomInt);
}

