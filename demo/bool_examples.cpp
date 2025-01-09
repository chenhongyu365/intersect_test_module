/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "bool_examples.hxx"

#include <cstdio>
#include <iostream>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/api.err"  // API_FAILED definition
#include "acis/boolapi.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/errorbase.hxx"
#include "acis/faceutil.hxx"
#include "acis/fileinfo.hxx"
#include "acis/get_top.hxx"
#include "acis/kernapi.hxx"
#include "acis/lists.hxx"
#include "acis/plane.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis/roll_utl.hxx"
#include "acis/shadow.hxx"
#include "acis/split_api.hxx"
#include "acis/straight.hxx"

LOCAL_PROC BODY* WireFromEdge(EDGE* ptrEdge) {
    BODY* ptrWireBody = NULL;
    EDGE* edgeArray[1];
    edgeArray[0] = ptrEdge;
    check_outcome(api_make_ewire(1, edgeArray, ptrWireBody));
    return ptrWireBody;
}
LOCAL_PROC BODY* WireFromPoints(SPAposition& refStartPoint, SPAposition& refEndPoint) {
    EDGE* ptrEdge = NULL;
    check_outcome(api_curve_line(refStartPoint, refEndPoint, ptrEdge));
    return WireFromEdge(ptrEdge);
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		boolean unite
//
// APIs:
//		api_boolean
//
// Description:
//		Demonstrates union of valid ACIS bodies
//----------------------------------------------------------------------------------
outcome aei_BOOL_UNITE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrTool = NULL;                           // Pointer to tool body
    BODY* ptrBlank = NULL;                          // Pointer to blank body

    /* API Call Block */
    API_BEGIN

    /* Creating Tool & painting with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrTool));
    check_outcome(api_rh_set_entity_rgb(ptrTool, rgb_color(0.9, 1.0, 0.0)));

    /* Creating Blank & painting with some color */
    check_outcome(api_solid_sphere(objFirstCorner, 8.0, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(0.0, 0.8, 1.0)));

    /* Uniting blank with tool */
    check_outcome(api_boolean(ptrTool, ptrBlank, UNION, NDBOOL_KEEP_NEITHER, SpaAcis::NullObj::get_body_ptr(), ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(ptrBlank);
    }
    return result;
}
//**********************************************************************************
// C++ Example:
//
// Title:
//		boolean intersection
//
// APIs:
//		api_boolean
//
// Description:
//		Demonstrates intersection of two valid ACIS bodies as blank & tool
//----------------------------------------------------------------------------------
outcome aei_BOOL_INTERSECTION(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrTool = NULL;                           // Pointer to tool body
    BODY* ptrBlank = NULL;                          // Pointer to blank body
    /* API Call Block */
    API_BEGIN

    /* Creating Tool & painting with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrTool));
    check_outcome(api_rh_set_entity_rgb(ptrTool, rgb_color(0.4, 1.0, 3.0)));

    /* Creating Blank & painting with some color */
    check_outcome(api_solid_sphere(objFirstCorner, 5, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(0.6, 0.0, 1.0)));

    /* performing intersection between blank with tool */
    check_outcome(api_boolean(ptrTool, ptrBlank, INTERSECTION, NDBOOL_KEEP_NEITHER, SpaAcis::NullObj::get_body_ptr(), ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(ptrBlank);
    }
    return result;
}
//**********************************************************************************
// C++ Example:
//
// Title:
//		Boolean subtraction
//
// APIs:
//		api_boolean
//
// Description:
//		Demonstrates subtraction of two valid ACIS bodies as blank & tool
//----------------------------------------------------------------------------------
outcome aei_BOOL_SUBTRACTION(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrTool = NULL;                           // Pointer to tool body
    BODY* ptrBlank = NULL;                          // Pointer to blank body
    /* API Call Block */
    API_BEGIN

    /* Creating Tool & painting with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrTool));
    check_outcome(api_rh_set_entity_rgb(ptrTool, rgb_color(0.9, 0.8, 0.0)));

    /* Creating Blank & painting with some color */
    check_outcome(api_solid_sphere(objFirstCorner, 5, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(0.9, 0.8, 0.0)));

    /* performing subtraction of tool from blank */
    check_outcome(api_boolean(ptrTool, ptrBlank, SUBTRACTION, NDBOOL_KEEP_NEITHER, SpaAcis::NullObj::get_body_ptr(), ptrAcisOpt));

    API_END
    if(result.ok()) {
        output_ents.add(ptrBlank);
    }
    return result;
}
// *********************************************************************************************
// C++ Example:
//
// Title:
//		Boolean Chop
//
// APIs:
//		api_boolean_chop_body
//
// Description:
//		This demonstrates "chops" of the blank body with the tool body,returning the body formed
//		by intersecting the tool with the blank, and the body  formed by   subtracting  the tool
//      from the blank, simultaneously. The intersection result is returned via a modified blank
//      body.   If the tool body  is an incomplete solid,  any  lumps of the blank which are not
//      intersected by the faces of the tool, and which therefore cannot be classified as either
//      inside or outside, will be returned in a newly created body via the pointer 'leftovers',
// ---------------------------------------------------------------------------------------------
outcome aei_BOOL_CHOP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrTool = NULL;                           // Pointer to tool body
    BODY* ptrBlank = NULL;                          // Pointer to blank body
    BODY* ptrOutside = NULL;                        // Pointer to part of tool which is outside blank
    BODY* ptrLeftOver = NULL;                       // Pointer to part of tool which is neither
    // in inside nor outside of blank
    /* API Call Block */
    API_BEGIN

    /* Creating tool & painting with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrTool));
    check_outcome(api_rh_set_entity_rgb(ptrTool, rgb_color(0.2, 0.2, 1.0)));

    /* Creating blank & painting with some color */
    check_outcome(api_solid_sphere(objFirstCorner, 5, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(0.2, 0.3, 0.9)));

    /* Performing chop operation */
    check_outcome(api_boolean_chop_body(ptrTool, ptrBlank, FALSE, ptrOutside, ptrLeftOver, NDBOOL_KEEP_NEITHER, SpaAcis::NullObj::get_body_ptr(), ptrAcisOpt));

    /* Painting Outside for better distinction */
    check_outcome(api_rh_set_entity_rgb(ptrOutside, rgb_color(0.2, 0.5, 1.0)));

    API_END

    if(result.ok()) {
        /* Adding resultant bodies for test output */
        output_ents.add(ptrBlank);
        output_ents.add(ptrOutside);
    }
    return result;
}

outcome aei_BOOL_MAKE_SHADOW(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrBlank = NULL;                          // Pointer to blank body
    BODY* ptrShadow = NULL;                         // Pointer to shadow of blank
    /* API Call Block */
    API_BEGIN

    /* Creating Blank & Painting It Lime */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(0.8, 1.0, 0.8)));

    /* Creating plane on which shadow is expected */
    plane objPlane(SPAposition(10.0, 10.0, 10.0), SPAunit_vector(0.1, 0.1, 0.1));

    /* Creating list & add blank as input for making shadow */
    ENTITY_LIST bodyList;
    bodyList.add(ptrBlank);

    /* Making shadow */
    make_shadow_options mso;
    check_outcome(api_make_shadow(bodyList, objPlane, ptrShadow, &mso, ptrAcisOpt));

    /* Painting Shadow to some color so that is easily identified */
    check_outcome(api_rh_set_entity_rgb(ptrShadow, rgb_color(0.5, 0.6, 0.5)));

    API_END

    if(result.ok()) {
        output_ents.add(ptrShadow);
        output_ents.add(ptrBlank);
    }
    return result;
}
//***************************************************************************************
// C++ Example:
//
// Title:
//		Face Subdivide
//
// APIs:
//		api_sub_divide_face
//
// Description:
//		It demonstrates the sub division of given face.
//---------------------------------------------------------------------------------------
outcome aei_BOOL_SUBDIVIDE_FACE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrBlank = NULL;                          // Pointer to blank body
    FACE* ptrFace = NULL;                           // Face to sub divide
    BODY* ptrWireBody = NULL;                       // Output wire body of face subdivide
    /* API Call Block */
    API_BEGIN

    /* Creating blank & painting it some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrBlank));
    check_outcome(api_rh_set_entity_rgb(ptrBlank, rgb_color(1.0, 0.2, 0.0)));

    /* Selecting face for subdivision */
    {
        ENTITY_LIST faces;
        get_faces(ptrBlank, faces);
        ptrFace = (FACE*)faces.first();
    }

    /* Calculating UV parameters */
    SPApar_box objParBox;
    // sg_get_face_par_box can fail. We need to check the return value, and if it failed, throw a sys_error.
    {
        logical status_ok = sg_get_face_par_box(ptrFace, objParBox);
        if(0 == status_ok) {
            sys_error(API_FAILED);
        }
    }
    SPAinterval objURange = objParBox.u_range();
    SPAinterval objVRange = objParBox.v_range();

    /* Preparing prerequisite object & references  */
    const face_subdivision& objSubDivision = face_subdivision::make(objURange, 8, objVRange, 8);
    subdivide_face_output_handle* ptrHandle = NULL;
    // Use ACIS try-catch macros to manage ownership of subdivide_face_output_handle - check_outcome can throw an exception
    // http://doc.spatial.com/articles/e/r/r/Error_Handling_eab8.html#Exception_Handling_Macros
    EXCEPTION_BEGIN
    EXCEPTION_TRY
    subdivide_face_options sdfOption;

    /* Setting do_split for false. due to which it will return wire body instead of list of subdivided faces */
    sdfOption.do_split(false);

    /* Performing face sub division */
    check_outcome(api_subdivide_face(ptrFace, objSubDivision, ptrHandle, &sdfOption, ptrAcisOpt));

    /* Extracting output wire body */
    subdivide_face_output_query objQuery(ptrHandle);
    ptrWireBody = objQuery.wire();

    // The EXCEPTION_CATCH_TRUE block will be executed if an exception is thrown, but also if not.
    EXCEPTION_CATCH_TRUE
    // Give up ownership of the subdivide_face_output_handle
    ptrHandle->remove_ref();
    ptrHandle = NULL;
    EXCEPTION_END
    /* Setting some color to output wire body for better distinction */
    check_outcome(api_rh_set_entity_rgb(ptrWireBody, rgb_color(0.9, 0.9, 1.0)));

    API_END

    if(result.ok()) {
        output_ents.add(ptrWireBody);
        output_ents.add(ptrBlank);
    }
    return result;
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		Split Wire Body
//
// APIs:
//		api_split_wire_edges
//
// Description:
//		It demonstrates the splitting of a wire edge with respect to given points.
//----------------------------------------------------------------------------------
outcome aei_BOOL_SPLIT_WIRE_EDGE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objStartPoint(0.0, 0.0, 0.0);   // Start point for wire
    SPAposition objEndPoint(10.0, 10.0, 10.0);  // End point for wire
    BODY* ptrWireBody = NULL;                   // Pointer for wire body which is to created
    /* API Call Block */
    API_BEGIN
    /* Creating wire body using start & end points */
    ptrWireBody = WireFromPoints(objStartPoint, objEndPoint);

    /* Preparing list of split points */
    SPAposition_vector positionVector;
    positionVector.push_back(SPAposition(2.0, 2.0, 2.0));
    positionVector.push_back(SPAposition(4.0, 4.0, 4.0));
    positionVector.push_back(SPAposition(6.0, 6.0, 6.0));
    positionVector.push_back(SPAposition(8.0, 8.0, 8.0));

    /* Performing wire edge split */
    check_outcome(api_split_wire_edges(ptrWireBody, positionVector, NULL, ptrAcisOpt));

    /* Setting some color to output wire body for better distinction */
    check_outcome(api_rh_set_entity_rgb(ptrWireBody, rgb_color(1.0, 0.8, 0.0)));

    API_END
    if(result.ok()) {
        output_ents.add(ptrWireBody);
    }
    return result;
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		Project Wire to Body
//
// APIs:
//		api_project_wire_to_body
//
// Description:
//		It demonstrates projection of a wire to given body.
outcome aei_BOOL_PROJECT_WIRE_TO_BODY(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrBlock = NULL;                          // Pointer for block to be created
    BODY* ptrWireBody = NULL;                       // Pointer for wire body to be created
    /* API Call Block */
    API_BEGIN

    /* Creating block and painting it with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrBlock));
    check_outcome(api_rh_set_entity_rgb(ptrBlock, rgb_color(0.7, 0.8, 0.9)));

    /* Creating Wire Body with some start and end point*/
    SPAposition objStartPoint(0, -1, -1);
    SPAposition objEndPoint(9, 12, 10);
    ptrWireBody = WireFromPoints(objStartPoint, objEndPoint);

    /* Projecting newly created wire to block */
    check_outcome(api_project_wire_to_body(ptrWireBody, ptrBlock, NULL, ptrAcisOpt));

    /* Painting output wire body for easy visibility */
    check_outcome(api_rh_set_entity_rgb(ptrBlock, rgb_color(0.0, 0.6, 0.5)));

    API_END
    if(result.ok()) {
        /* Adding resultant bodies for test output */
        output_ents.add(ptrWireBody);
        output_ents.add(ptrBlock);
    }
    return result;
}

//**********************************************************************************
// C++ Example:
//
// Title:
//		Project Edge to Face
//
// APIs:
//		api_project_edge_to_face
//
// Description:
//		It demonstrates projection of a edge to given face.
//----------------------------------------------------------------------------------
outcome aei_BOOL_PROJECT_EDGE_TO_FACE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */
    SPAposition objFirstCorner(0.0, 0.0, 0.0);      // First Sample Point
    SPAposition objSecondCorner(10.0, 10.0, 10.0);  // Second Sample Point
    BODY* ptrBlock = NULL;                          // Pointer to body, from which face will picked
    FACE* ptrFace = NULL;                           // Pointer to face on which edge will project
    EDGE* ptrEdge = NULL;                           // Pointer to edge which will project on face
    ENTITY_LIST projectedEntityList;                // List to collect projected entities
    /* API Call Block */
    API_BEGIN

    /* Creating block and painting it with some color */
    check_outcome(api_solid_block(objFirstCorner, objSecondCorner, ptrBlock));
    check_outcome(api_rh_set_entity_rgb(ptrBlock, rgb_color(1.0, 0.0, 0.8)));

    /* Choosing first face of newly created block as target face on which projection is to do */
    {
        ENTITY_LIST faces;
        get_faces(ptrBlock, faces);
        ptrFace = (FACE*)faces.first();
    }
    /* Creating sample edge which will use for projection */
    check_outcome(api_curve_line(SPAposition(-5, 5, 5), SPAposition(15, 5, 5), ptrEdge));

    /* Performing projection of edge on face & retrieving projected entities */
    check_outcome(api_project_edge_to_face(ptrEdge, ptrFace, &projectedEntityList, NULL, ptrAcisOpt));

    API_END

    if(result.ok()) {
        /* Adding resultant bodies for test output */
        output_ents.add(WireFromEdge(ptrEdge));
        output_ents.add(WireFromEdge((EDGE*)projectedEntityList[0]));
        output_ents.add(ptrBlock);
    }

    return result;
}
