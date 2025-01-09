/*********************************************************************
 * @file    gme_cstrapi_edge_spring_example.cpp
 * @brief  api_edge_spring demo
 * @details
 * @author  charynnc
 * @date    2023.7.18
 *********************************************************************/
#include "gme_cstrapi_edge_spring_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_demo 1:
//
// APIs:
//    gme_api_edge_spring
//
// Description:
//	  单螺旋
// **********************************************************************************
outcome aei_SPRING_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE *gme_edge = nullptr, *acis_edge = nullptr;

    API_BEGIN
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(5, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 1;
    double thread_distance_array[5] = {1, 0, 0, 0, 0};
    double rotation_angle_array[5] = {20 * M_PI, 0, 0, 0, 0};
    double transition_height_array[5] = {0, 0, 0, 0, 0};
    double transition_angle_array[5] = {0, 0, 0, 0, 0};
    api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

    acis_api_save_entity("acis_edge.sat", acis_edge);
    acis_api_save_entity("gme_edge.sat", gme_edge);
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_edge);
        output_ents.add(acis_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_demo 2:
//
// APIs:
//    gme_api_edge_spring
//
// Description:
//	  多螺旋
// **********************************************************************************
outcome aei_SPRING_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE *gme_edge = nullptr, *acis_edge = nullptr;

    API_BEGIN
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(5.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 3;
    double thread_distance_array[5] = {1, 2, 1, 0, 0};
    double rotation_angle_array[5] = {11 * M_PI, 8.25 * M_PI, 12.75 * M_PI, 0, 0};
    double transition_height_array[5] = {10, 8, 0, 0, 0};
    double transition_angle_array[5] = {M_PI, M_PI, 0, 0, 0};
    api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

    acis_api_save_entity("acis_edge.sat", acis_edge);
    acis_api_save_entity("gme_edge.sat", gme_edge);
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_edge);
        output_ents.add(acis_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_demo 3:
//
// APIs:
//    gme_api_edge_spring
//
// Description:
//	  多螺旋无过渡
// **********************************************************************************
outcome aei_SPRING_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE *gme_edge = nullptr, *acis_edge = nullptr;

    API_BEGIN
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(5.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 2;
    double thread_distance_array[5] = {1, 2, 0, 0, 0};
    double rotation_angle_array[5] = {10 * M_PI, 8 * M_PI, 0, 0, 0};
    double transition_height_array[5] = {0, 0, 0, 0, 0};
    double transition_angle_array[5] = {0 * M_PI, 0, 0, 0, 0};
    api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

    acis_api_save_entity("acis_edge.sat", acis_edge);
    acis_api_save_entity("gme_edge.sat", gme_edge);
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_edge);
        output_ents.add(acis_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_demo 4:
//
// APIs:
//    gme_api_edge_spring
//
// Description:
//	  螺距为0或负值
// **********************************************************************************
outcome aei_SPRING_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE *gme_edge = nullptr, *acis_edge = nullptr;

    API_BEGIN
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(5.0, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 3;
    double thread_distance_array[5] = {1, 0, -1, 0, 0};
    double rotation_angle_array[5] = {10 * M_PI, 8 * M_PI, 12 * M_PI, 0, 0};
    double transition_height_array[5] = {10, 0, 0, 0, 0};
    double transition_angle_array[5] = {2 * M_PI, 2 * M_PI, 0, 0, 0};
    api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

    acis_api_save_entity("acis_edge.sat", acis_edge);
    acis_api_save_entity("gme_edge.sat", gme_edge);
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_edge);
        output_ents.add(acis_edge);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spring_demo 5:
//
// APIs:
//    gme_api_edge_spring
//
// Description:
//	  极小参数
// **********************************************************************************
outcome aei_SPRING_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE *gme_edge = nullptr, *acis_edge = nullptr;

    API_BEGIN
    SPAposition axis_point(0.0, 0.0, 0.0);
    SPAvector axis_vector(0.0, 0.0, 1.0);
    SPAposition start_point(0.0005, 0.0, 0.0);
    logical right_handed = FALSE;
    int helix_count = 3;
    double thread_distance_array[5] = {0.0001, 0.0002, 0.0001, 0, 0};
    double rotation_angle_array[5] = {10 * M_PI, 8 * M_PI, 12 * M_PI, 0, 0};
    double transition_height_array[5] = {0.001, 0.0008, 0, 0, 0};
    double transition_angle_array[5] = {M_PI, M_PI, 0, 0, 0};
    api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, acis_edge);
    gme_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

    acis_api_save_entity("acis_edge.sat", acis_edge);
    acis_api_save_entity("gme_edge.sat", gme_edge);
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_edge, rgb_color(1, 0, 0));
        output_ents.add(gme_edge);
        output_ents.add(acis_edge);
    }
    return result;
}