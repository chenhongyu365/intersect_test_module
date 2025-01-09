/*********************************************************************
 * @file    gme_cstrapi_edge_spring_example.cpp
 * @brief  api_edge_spring demo
 * @details
 * @author  charynnc
 * @date    2023.7.18
 *********************************************************************/
#include "gme_cstrapi_orient_wire_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/coverapi.hxx"
#include "acis/cstrapi.hxx"
#include "acis/eulerapi.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  orient_wire_demo 1:
//
// APIs:
//    gme_api_orient_wire
//
// Description:
//      闭合顺序wire
// **********************************************************************************
outcome aei_ORIENT_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body;

    API_BEGIN
    SPAposition p1(0, 0, 0), p2(1, 0, 0), p3(1, 1, 0), p4(0, 1, 0);
    EDGE *e1, *e2, *e3, *e4;
    api_curve_line(p1, p2, e1);
    api_curve_line(p2, p3, e2);
    api_curve_line(p3, p4, e3);
    api_curve_line(p4, p1, e4);
    EDGE* edges[4] = {e1, e2, e3, e4};
    api_make_ewire(4, edges, body);
    ENTITY_LIST ces;
    api_get_coedges(body, ces);
    COEDGE* ce = (COEDGE*)ces[1];

    acis_api_save_entity("gme_wire.sat", body);
    gme_api_orient_wire(ce);
    acis_api_save_entity("acis_wire.sat", body);

    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  orient_wire_demo 2:
//
// APIs:
//    gme_api_orient_wire
//
// Description:
//      开放顺序wire
// **********************************************************************************
outcome aei_ORIENT_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body;

    API_BEGIN
    SPAposition p1(0, 0, 0), p2(1, 0, 0), p3(1, 1, 0), p4(0, 1, 0);
    EDGE *e1, *e2, *e3, *e4;
    api_curve_line(p1, p2, e1);
    api_curve_line(p2, p3, e2);
    api_curve_line(p3, p4, e3);
    EDGE* edges[3] = {e1, e2, e3};
    api_make_ewire(3, edges, body);
    ENTITY_LIST ces;
    api_get_coedges(body, ces);
    COEDGE* ce1 = (COEDGE*)ces[1];

    acis_api_save_entity("gme_wire.sat", body);
    // api_orient_wire(ce1);
    gme_api_orient_wire(ce1);
    acis_api_save_entity("acis_wire.sat", body);

    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  orient_wire_demo 3:
//
// APIs:
//    gme_api_orient_wire
//
// Description:
//      开放非顺序wire
// **********************************************************************************
outcome aei_ORIENT_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body;

    API_BEGIN
    BODY *body1, *body2;
    SPAposition p1(0, 0, 0), p2(1, 0, 0), p3(1, 1, 0), p4(2, 0, 0), p5(2, 1, 0);
    EDGE *e1, *e2, *e3, *e4;

    api_curve_line(p1, p2, e1);
    api_curve_line(p2, p3, e2);
    api_curve_line(p4, p5, e3);
    api_curve_line(p5, p3, e4);

    ENTITY* edges[4] = {e1, e2, e3, e4};
    ENTITY_LIST edges_list(4, edges);
    FILE* fp = nullptr;
    api_unite_edges(edges_list, body, fp);

    ENTITY_LIST ces;
    api_get_coedges(body, ces);
    COEDGE* ce = (COEDGE*)ces[0];

    acis_api_save_entity("gme_wire.sat", body);
    // api_orient_wire(ce1);
    gme_api_orient_wire(ce);
    acis_api_save_entity("acis_wire.sat", body);

    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}