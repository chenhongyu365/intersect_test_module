/*********************************************************************
 * @file    gme_cstrapi_1_orient_wire_example.cpp
 * @brief  api_orient_wire demo
 * @details
 * @author  姚威
 * @date    2023.10.9
 *********************************************************************/
#include "gme_cstrapi_1_orient_wire_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/eulerapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/boolapi.hxx"

 // **********************************************************************************
 // C++ Example:
 //
 // Title:
 //	  1_orient_wire_demo 1:
 //
 // APIs:
 //    gme_1_api_orient_wire
 //
 // Description:
 //      闭合顺序wire
 // **********************************************************************************
outcome aei_1_ORIENT_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;

	SPAposition p1(1, 0, 0), p2(0, 1, 0), p3(-1, 0, 0), p4(0, -1, 0);
	SPAposition pos[4] = { p1, p2, p3, p4 };

	EDGE* edge[4] = { nullptr };
	API_BEGIN
		for (int i = 0; i < 4; i++) {
			api_curve_line(pos[i], pos[(i + 1) % 4], edge[i]);
		}
	api_make_ewire(4, edge, body);
	COEDGE* co = body->lump()->shell()->wire()->coedge()->next();

	acis_api_save_entity("gme_wire.sat", body);
	gme_1_api_orient_wire(co);
	acis_api_save_entity("acis_wire.sat", body);
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
//	  1_orient_wire_demo 2:
//
// APIs:
//    gme_1_api_orient_wire
//
// Description:
//      开放顺序wire
// **********************************************************************************
outcome aei_1_ORIENT_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;


	SPAposition p1(-1, 0, 0), p2(-1, -1, 0), p3(0, -1, 0), p4(1, -1, 0), p5(0, 1, 0);
	SPAposition pos[5] = { p1, p2, p3, p4, p5 };

	EDGE* edge[4] = { nullptr };
	API_BEGIN

		for (int i = 0; i < 4; i++) {
			api_curve_line(pos[i], pos[i + 1], edge[i]);
		}
	api_make_ewire(4, edge, body);

	COEDGE* co = body->lump()->shell()->wire()->coedge()->next();

	acis_api_save_entity("gme_wire.sat", body);
	gme_1_api_orient_wire(co);
	acis_api_save_entity("acis_wire.sat", body);
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
//	  1_orient_wire_demo 3:
//
// APIs:
//    gme_1_api_orient_wire
//
// Description:
//      开放非顺序wire
// **********************************************************************************
outcome aei_1_ORIENT_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;
	FILE* fp = nullptr;

	SPAposition p1(2, 0, 0), p2(0, 2, 0), p3(-2, 0, 0), p4(-2, -2, 0), p5(2, -2, 0);
	SPAposition pos[5] = { p1, p2, p3, p4, p5 };

	EDGE* edge[4] = { nullptr };
	API_BEGIN

		for (int i = 0; i < 4; i++) {
			api_curve_line(pos[i], pos[i + 1], edge[i]);
		}
	ENTITY_LIST lst(4, (ENTITY**)edge);
	api_unite_edges(lst, body, fp);

	COEDGE* co = body->lump()->shell()->wire()->coedge()->next();

	acis_api_save_entity("gme_wire.sat", body);
	gme_1_api_orient_wire(co);
	acis_api_save_entity("acis_wire.sat", body);
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
//	  1_orient_wire_demo 4:
//
// APIs:
//    gme_1_api_orient_wire
//
// Description:
//      闭合非顺序wire
// **********************************************************************************
outcome aei_1_ORIENT_WIRE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
	BODY* body;
	FILE* fp = nullptr;

	SPAposition p11(0, 1, 0), p12(-1, 1, 0), p13(-2, 0, 0), p14(-1, -1, 0), p15(0, -1, 0);
	SPAposition p21(0, 1, 0), p22(1, 1, 0), p23(2, 0, 0), p24(1, -1, 0), p25(0, -1, 0);

	SPAposition pos1[5] = { p11,p12,p13,p14,p15 };
	SPAposition pos2[5] = { p21,p22,p23,p24,p25 };

	EDGE* edge1[4] = { nullptr };
	API_BEGIN
		for (int i = 0; i < 4; i++) {
			api_curve_line(pos1[i], pos1[i + 1], edge1[i]);
		}
	api_make_ewire(4, edge1, body);

	EDGE* edge2[4] = { nullptr };
	for (int i = 0; i < 4; i++) {
		api_curve_line(pos2[i], pos2[i + 1], edge2[i]);
	}
	BODY* b = nullptr;
	api_make_ewire(4, edge2, b);
	api_unite_wires(b, body);

	COEDGE* co = body->lump()->shell()->wire()->coedge()->next();

	acis_api_save_entity("gme_wire.sat", body);
	gme_1_api_orient_wire(co);
	acis_api_save_entity("acis_wire.sat", body);

	API_END
		if (result.ok()) {
			output_ents.add(body);
		}

	return result;
}

