/*********************************************************************
 * @file    gme_cstrapi_2_make_prism.cpp
 * @brief
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
#include "gme_cstrapi_2_make_prism_example.hxx"

 // **********************************************************************************
 // C++ Example:
 //
 // Title:
 //	  2_make_prism_demo 1:
 //
 // APIs:
 //    gme_2_api_make_prism
 //
 // Description:
 //    构造一般情况下的prism
 // **********************************************************************************
outcome aei_2_MAKE_PRISM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;
	double height = 6;
	double radius1 = 6;
	double radius2 = 8;
	int nsides = 6;

	API_BEGIN
		gme_2_api_make_prism(height, radius1, radius2, nsides, body);
	API_END

		if (result.ok()) {
			output_ents.add(body);
		}
	return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  2_make_prism_demo 1:
//
// APIs:
//    gme_2_api_make_prism
//
// Description:
//    height等于0的情况
// **********************************************************************************
outcome aei_2_MAKE_PRISM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;
	double height = 0;
	double radius1 = 6;
	double radius2 = 8;
	int nsides = 6;

	API_BEGIN
		gme_2_api_make_prism(height, radius1, radius2, nsides, body);
	API_END

		if (result.ok()) {
			output_ents.add(body);
		}
	return result;
}