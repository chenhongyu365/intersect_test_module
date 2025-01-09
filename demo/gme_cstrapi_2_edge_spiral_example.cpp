/*********************************************************************
 * @file    gme_cstrapi_2_edge_spiral_example.cpp
 * @brief	gme_2_edge_spiral demo
 * @details
 * @author  姚威
 * @date    2024.10.5
 *********************************************************************/

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"
#include "gme_cstrapi_2_edge_spiral_example.hxx"

 // **********************************************************************************
 // C++ Example:
 //
 // Title:
 //	  2_edge_spiral_demo 1:
 //
 // APIs:
 //    gme_2_api_edge_spiral
 //
 // Description:
 //    构造一般情况下的spiral（right_handed）
 // **********************************************************************************
outcome aei_2_EDGE_SPIRAL_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	EDGE* e = nullptr;
	SPAposition center(0, 0, 0);
	SPAvector normal(0, 0, 1);
	SPAposition start_pos(1, 1, 0);
	double width = 10;
	double angle = 10;
	API_BEGIN
		gme_2_api_edge_spiral(center, normal, start_pos, width, angle, e);
	API_END

		if (result.ok()) {
			output_ents.add(e);
		}
	return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_edge_spiral_demo 2:
//
// APIs:
//    gme_2_api_edge_spiral
//
// Description:
//    width < 0
// **********************************************************************************
outcome aei_2_EDGE_SPIRAL_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	EDGE* e = nullptr;
	SPAposition center(0, 0, 0);
	SPAvector normal(0, 0, 1);
	SPAposition start_pos(1, 0, 0);
	double width = -10;
	double angle = 10;
	API_BEGIN
		gme_2_api_edge_spiral(center, normal, start_pos, width, angle, e);
	API_END

		if (result.ok()) {
			output_ents.add(e);
		}
	return result;
}
