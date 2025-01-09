/*********************************************************************
 * @file    gme_cstrapi_face_conic_example.cpp
 * @brief   api_face_conic demo
 * @details
 * @author  ghzico
 * @date    2024.8.1
 *********************************************************************/
#include "gme_cstrapi_face_conic_example.hxx"

#include <vector>

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic ellipse trough demo 1:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  椭圆槽形内面
//
// **********************************************************************************
outcome aei_FACE_CONIC_DEMO1_1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 5, b = 4, c = 3;
    double radius = (b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 3.99;
    double length = 2;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic ellipse trough demo 2:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  椭圆槽形外面
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO1_2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 5, b = 4, c = 3;
    double radius = -(b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 3;
    double length = 2;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic parabola trough demo 3:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  抛物线槽形
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 5, b = 2, c = 5;
    double radius = (b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 10;
    double length = 2;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic hyperbola trough demo 4:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  双曲线槽形
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 3, b = 4, c = 5;
    double radius = (b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 10;
    double length = 2;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic ellipse dish demo 5:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  椭圆碟形
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 5, b = 4, c = 3;
    double radius = (b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 2;
    double length = 0;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic parabola dish demo 6:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  抛物线碟形
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO6(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 5, b = 4, c = 5;
    double radius = (b * b) / a;
    double conic_const = -(c * c) / (a * a);
    double extent = 20;
    double length = 0;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_conic hyperbola dish demo 7:
//
// APIs:
//    gme_api_face_conic
//
// Description:
//	  双曲线碟形
//
// **********************************************************************************

outcome aei_FACE_CONIC_DEMO7(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = NULL;
    API_BEGIN

    double a = 3, b = 4, c = 5;
    double radius = (b * b) / a;
    double conic_const = (c * c) / (a * a);
    double extent = 20;
    double length = 0;

    gme_api_face_conic(radius, conic_const, extent, length, face);
    // api_face_conic(radius, conic_const, extent, length, face);
    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}