/*********************************************************************
 * @file    gme_cstrapi_curve_arc_diagonal_example.cpp
 * @brief   api_curve_arc_diagonal demo
 * @details
 * @author  Dubopei
 * @date    2024.9.22
 *********************************************************************/

#include "gme_cstrapi_curve_arc_diagonal_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// 两点间距为sqrt3 * 1e-2绘制的圆几乎只是一个小点，因此无法观测间距sqrt3 * 1e-5时 acis接口只画半圆的bug

// **********************************************************************************
// C++ Example:
//
// Title:
//	  ArcDiagonal_demo 1:
//
// APIs:
//    gme_cstrapi_curve_arc_diagonal
//
// Description:
//	  绘制完整圆弧
//
// **********************************************************************************
outcome aei_ArcDiagonal_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    API_BEGIN
    SPAposition pt1(1.0, 2.0, 0.0);
    SPAposition pt2(3.0, 6.0, 8.0);
    gme_api_curve_arc_diagonal(pt1, pt2, 1, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  ArcDiagonal_demo 2:
//
// APIs:
//    gme_cstrapi_curve_arc_diagonal
//
// Description:
//	  绘制半圆
//
// **********************************************************************************
outcome aei_ArcDiagonal_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    API_BEGIN
    SPAposition pt1(1.0, 2.0, 0.0);
    SPAposition pt2(3.0, 6.0, 8.0);
    gme_api_curve_arc_diagonal(pt1, pt2, 0, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  ArcDiagonal_demo 3:
//
// APIs:
//    gme_api_curve_arc_diagonal
//
// Description:
//	  两点间距sqrt3 * 0.1绘制圆
//
// **********************************************************************************
outcome aei_ArcDiagonal_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    API_BEGIN
    SPAposition pt1(1.0, 2.0, 0.0);
    SPAposition pt2(1.1, 2.1, 0.1);
    gme_api_curve_arc_diagonal(pt1, pt2, 1, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  ArcDiagonal_demo 3:
//
// APIs:
//    gme_cstrapi_api_curve_arc_diagonal
//
// Description:
//	  两点间距sqrt3 * 0.1绘制半圆
//
// **********************************************************************************
outcome aei_ArcDiagonal_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    EDGE* arc = NULL;
    API_BEGIN
    SPAposition pt1(1.0, 2.0, 0.0);
    SPAposition pt2(1.1, 2.1, 0.1);
    gme_api_curve_arc_diagonal(pt1, pt2, 0, arc);
    API_END

    if(result.ok()) {
        output_ents.add(arc);
    }
    return result;
}