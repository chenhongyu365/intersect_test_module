/*********************************************************************
 * @file    gme_cstrapi_edge_spring_law_example.cpp
 * @brief  演示api_edge_spring_law接口
 * @details
 * @author  charynnc
 * @date    2023.7.19
 *********************************************************************/

#include "gme_cstrapi_edge_spring_law_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/insanity_list.hxx"
#include "acis/intrapi.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_law_demo:
//
// APIs:
//    gme_api_edge_spring_law
//
// Description:
//	  单螺旋
// **********************************************************************************
outcome aei_SPRING_LAW_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* acis_edge = nullptr;
    EDGE* gme_edge = nullptr;
    std::string acis_info, gme_info;
    // 一系列参数
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(1.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 1;
    double thread_distance_array[5] = {1, 0, 0, 0, 0};
    double rotation_angle_array[5] = {4 * M_PI, 0, 0, 0, 0};
    double transition_height_array[5] = {0, 0, 0, 0, 0};
    double transition_angle_array[5] = {0, 0, 0, 0, 0};
    // 初始的law
    std::string law_str = "x^2 + Sqrt(x) + 1 + Sin(1 + x^3)";
    law* radius_law = nullptr;
    api_str_to_law(law_str.c_str(), &radius_law);
    API_BEGIN
    result = api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    result = gme_api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);
    API_END

    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_law_demo:
//
// APIs:
//    gme_api_edge_spring_law
//
// Description:
//	  三螺旋
// **********************************************************************************
outcome aei_SPRING_LAW_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* acis_edge = nullptr;
    EDGE* gme_edge = nullptr;
    std::string acis_info, gme_info;
    // 一系列参数
    SPAposition axis_point = SPAposition(0.0, 0.0, 0.0);
    SPAvector axis_vector = SPAvector(1.0, 1.0, 1.0);
    SPAposition start_point = SPAposition(1.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 2;
    double thread_distance_array[5] = {1, 2, 3, 0, 0};
    double rotation_angle_array[5] = {4 * M_PI, 6 * M_PI, 8 * M_PI, 0, 0};
    double transition_height_array[5] = {5, 5, 0, 0, 0};
    double transition_angle_array[5] = {2 * M_PI, 2 * M_PI, 0, 0, 0};
    // 初始的law
    std::string law_str = "10 + 5 * Sin(x)";
    law* radius_law = nullptr;
    api_str_to_law(law_str.c_str(), &radius_law);
    API_BEGIN
    result = api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    result = gme_api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);
    API_END

    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    return result;
}
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_law_demo:
//
// APIs:
//    gme_api_edge_spring_law
//
// Description:
//	  较复杂数据
// **********************************************************************************
outcome aei_SPRING_LAW_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* acis_edge = nullptr;
    EDGE* gme_edge = nullptr;
    std::string acis_info, gme_info;
    // 一系列参数
    SPAposition axis_point = SPAposition(0.0, 0.0, 0.0);
    SPAvector axis_vector = SPAvector(0.0, 0.0, 1.0);
    SPAposition start_point = SPAposition(1.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 5;
    double thread_distance_array[5] = {1, 2, 3, 2, 1};
    double rotation_angle_array[5] = {8 * M_PI, 6 * M_PI, 5 * M_PI, 4 * M_PI, 10 * M_PI};
    double transition_height_array[5] = {5, 5, 5, 5, 5};
    double transition_angle_array[5] = {4 * M_PI, 2 * M_PI, 2 * M_PI, 2 * M_PI, 2 * M_PI};
    // 初始的law
    std::string law_str = "Exp(0.01 * x + Sin(x))";
    law* radius_law = nullptr;
    api_str_to_law(law_str.c_str(), &radius_law);
    API_BEGIN
    result = api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    result = gme_api_edge_spring_law(axis_point, axis_vector, start_point, radius_law, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);
    API_END

    if(result.ok()) {
        output_ents.add(gme_edge);
    }
    return result;
}