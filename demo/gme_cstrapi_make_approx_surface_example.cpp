/*********************************************************************
 * @file    gme_cstrapi_make_approx_surface_example.cpp
 * @brief  api_make_approx_surface demo
 * @details
 * @author  charynnc
 * @date    2023.7.23
 *********************************************************************/
#include "gme_cstrapi_make_approx_surface_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/condef.hxx"
#include "acis/cstrapi.hxx"
#include "acis/faceutil.hxx"
#include "acis/getbox.hxx"
#include "acis/intsfsf.hxx"
#include "acis/law_spl.hxx"
#include "acis/off_spl.hxx"
#include "acis/pladef.hxx"
#include "acis/plane.hxx"
#include "acis/rnd_api.hxx"
#include "acis/sphdef.hxx"
#include "acis/sphere.hxx"
#include "acis/sum_spl.hxx"
#include "acis/tordef.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  approx_surface_demo 1:
//
// APIs:
//    gme_api_make_approx_surface
//
// Description:
//      平面
// **********************************************************************************
outcome aei_APPROX_SURFACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    surface *gme_surface = nullptr, *acis_surface = nullptr;
    FACE *gme_face = nullptr, *acis_face = nullptr;
    VERTEX* ver = nullptr;

    API_BEGIN
    // TODO 1：在平面轴方向不与任意轴垂直时（如（1,1,1）），近似的曲面与ACIS不一致
    plane* plane_surface = ACIS_NEW plane(SPAposition(0, 0, 0), SPAunit_vector(0, 1, 1));
    SPAinterval u_range(0, 2);
    SPAinterval v_range(0, 2);

    api_make_approx_surface(plane_surface, 0.0, u_range, v_range, acis_surface);
    gme_api_make_approx_surface(plane_surface, 0.0, u_range, v_range, gme_surface);
    api_make_face_from_surface(acis_surface, acis_face);
    api_make_face_from_surface(gme_surface, gme_face);

    acis_api_save_entity("acis_face.sat", acis_face);
    acis_api_save_entity("gme_face.sat", gme_face);

    ACIS_DELETE plane_surface;
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_face, rgb_color(1, 0, 0));
        output_ents.add(gme_face);
        output_ents.add(acis_face);
    }
    ACIS_DELETE gme_surface;
    ACIS_DELETE acis_surface;
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  approx_surface_demo 2:
//
// APIs:
//    gme_api_make_approx_surface
//
// Description:
//      锥形面
// **********************************************************************************
outcome aei_APPROX_SURFACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    surface *gme_surface = nullptr, *acis_surface = nullptr;
    FACE *gme_face = nullptr, *acis_face = nullptr;
    VERTEX* ver = nullptr;

    API_BEGIN
    SPAposition center(0, 0, 0);
    SPAunit_vector normal(0, 0, 1);
    SPAvector maj_axis(2, 0, 0);
    ellipse ell(center, normal, maj_axis, 1);
    cone* cone_surface = new cone(ell, 1, -1, 1);
    // TODO 2：近似一个完整圆锥面时（下方u范围改为（0,2）），u方向范围会与ACIS不一致，有可能和TODO 1是一个问题
    SPAinterval u_range(0, 1);
    SPAinterval v_range(0, 2 * M_PI);

    api_make_approx_surface(cone_surface, 0.0, u_range, v_range, acis_surface);
    gme_api_make_approx_surface(cone_surface, 0.0, u_range, v_range, gme_surface);
    api_make_face_from_surface(acis_surface, acis_face);
    api_make_face_from_surface(gme_surface, gme_face);

    acis_api_save_entity("acis_face.sat", acis_face);
    acis_api_save_entity("gme_face.sat", gme_face);
    ACIS_DELETE cone_surface;
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_face, rgb_color(1, 0, 0));
        output_ents.add(gme_face);
        output_ents.add(acis_face);
    }
    ACIS_DELETE gme_surface;
    ACIS_DELETE acis_surface;
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  approx_surface_demo 3:
//
// APIs:
//    gme_api_make_approx_surface
//
// Description:
//      圆环面
// **********************************************************************************
outcome aei_APPROX_SURFACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    surface *gme_surface = nullptr, *acis_surface = nullptr;
    FACE *gme_face = nullptr, *acis_face = nullptr;
    VERTEX* ver = nullptr;

    API_BEGIN
    torus* torus_surface = new torus(SPAposition(0, 0, 0), SPAunit_vector(1, 0, 0), 2, 1);
    SPAinterval u_range(0, 1 * M_PI);
    SPAinterval v_range(0, 2 * M_PI);

    api_make_approx_surface(torus_surface, 0.0, u_range, v_range, acis_surface);
    gme_api_make_approx_surface(torus_surface, 0.0, u_range, v_range, gme_surface);
    api_make_face_from_surface(acis_surface, acis_face);
    api_make_face_from_surface(gme_surface, gme_face);

    acis_api_save_entity("acis_face.sat", acis_face);
    acis_api_save_entity("gme_face.sat", gme_face);

    ACIS_DELETE torus_surface;
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_face, rgb_color(1, 0, 0));
        output_ents.add(gme_face);
        output_ents.add(acis_face);
    }
    ACIS_DELETE gme_surface;
    ACIS_DELETE acis_surface;
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  approx_surface_demo 4:
//
// APIs:
//    gme_api_make_approx_surface
//
// Description:
//      球面
// **********************************************************************************
outcome aei_APPROX_SURFACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    surface *gme_surface = nullptr, *acis_surface = nullptr;
    FACE *gme_face = nullptr, *acis_face = nullptr;
    VERTEX* ver = nullptr;

    API_BEGIN
    // TODO 3：ACIS近似的球面有较大的问题，这里先按照正常的思路近似
    sphere* sphere_surface = new sphere(SPAposition(0, 0, 0), 1);
    SPAinterval u_range(-1 * M_PI, 1 * M_PI);
    SPAinterval v_range(-1 * M_PI, 1 * M_PI);

    api_make_approx_surface(sphere_surface, 0.0, u_range, v_range, acis_surface);
    gme_api_make_approx_surface(sphere_surface, 0.0, u_range, v_range, gme_surface);
    api_make_face_from_surface(acis_surface, acis_face);
    api_make_face_from_surface(gme_surface, gme_face);

    acis_api_save_entity("acis_face.sat", acis_face);
    acis_api_save_entity("gme_face.sat", gme_face);

    ACIS_DELETE sphere_surface;
    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_face, rgb_color(1, 0, 0));
        output_ents.add(gme_face);
        // output_ents.add(acis_face);
    }
    ACIS_DELETE gme_surface;
    ACIS_DELETE acis_surface;
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  approx_surface_demo 5:
//
// APIs:
//    gme_api_make_approx_surface
//
// Description:
//      样条面
// **********************************************************************************
outcome aei_APPROX_SURFACE_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    surface *gme_surface = nullptr, *acis_surface = nullptr;
    FACE *gme_face = nullptr, *acis_face = nullptr;
    VERTEX* ver = nullptr;

    API_BEGIN

    SPAinterval u_range(0, 2);
    SPAinterval v_range(0, 1);
    law* law1 = nullptr;
    api_str_to_law("vec(x,y,sin(x)*cos(y))", &law1);
    curve* cur1;
    api_curve_law(law1, 0, 5, cur1);

    law_spl_sur* law_sur = ACIS_NEW law_spl_sur(law1, u_range, v_range);
    spline* spl_surface = ACIS_NEW spline(law_sur);

    api_make_approx_surface(spl_surface, 0.0, u_range, v_range, acis_surface);
    gme_api_make_approx_surface(spl_surface, 0.0, u_range, v_range, gme_surface);
    api_make_face_from_surface(acis_surface, acis_face);
    api_make_face_from_surface(gme_surface, gme_face);

    acis_api_save_entity("acis_face.sat", acis_face);
    acis_api_save_entity("gme_face.sat", gme_face);

    ACIS_DELETE spl_surface;
    law1->remove();

    API_END

    if(result.ok()) {
        api_rh_set_entity_rgb(gme_face, rgb_color(1, 0, 0));
        output_ents.add(gme_face);
        output_ents.add(acis_face);
    }
    ACIS_DELETE gme_surface;
    ACIS_DELETE acis_surface;
    return result;
}