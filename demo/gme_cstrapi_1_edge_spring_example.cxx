/*********************************************************************
 * @file    gme_cstrapi_1_api_edge_spring_example.cxx
 * @brief
 * @details cstrapi_1_api_edge_spring demo
 * @author  胡轩頔
 * @date    2024.8.12
 *********************************************************************/
#include "gme_cstrapi_1_edge_spring_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/point.hxx"
#include "acis/rnd_api.hxx"
#include "acis/sp3crtn.hxx"

outcome aei_1_SPRING_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	EDGE* gme_edge = nullptr;

	API_BEGIN
		SPAposition axis_point(0.0, 0.0, 0.0);
	SPAvector axis_vector(0.0, 0.0, 1.0);
	SPAposition start_point(5.0, 0.0, 0.0);
	logical right_handed = FALSE;
	int helix_count = 3;
	double thread_distance_array[3] = { 1, 2, 1 };
	double rotation_angle_array[3] = { 11 * M_PI, 8.25 * M_PI, 12.75 * M_PI };
	double transition_height_array[2] = { 10, 8 };
	double transition_angle_array[2] = { M_PI, M_PI };
	gme_1_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

	API_END

		if (result.ok()) {
			output_ents.add(gme_edge);
		}
	return result;
}

outcome aei_1_SPRING_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	EDGE* gme_edge = nullptr;

	API_BEGIN
		SPAposition axis_point(3.0, 6.0, 9.0);
	SPAvector axis_vector(0.0, 0.0, 1.0);
	SPAposition start_point(6.0, 0.0, 0.0);
	logical right_handed = TRUE;
	int helix_count = 1;
	double thread_distance_array[1] = { 1 };
	double rotation_angle_array[1] = { 10 * M_PI };
	double transition_height_array[1] = { 0 };
	double transition_angle_array[1] = { 0 };
	gme_1_api_edge_spring(axis_point, axis_vector, start_point, right_handed, helix_count, thread_distance_array, rotation_angle_array, transition_height_array, transition_angle_array, gme_edge);

	API_END

		if (result.ok()) {
			output_ents.add(gme_edge);
		}
	return result;
}
