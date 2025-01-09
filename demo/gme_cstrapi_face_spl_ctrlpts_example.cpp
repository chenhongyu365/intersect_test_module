/*********************************************************************
 * @file    gme_cstrapi_face_spl_ctrlpts_example.cpp
 * @brief
 * @details
 * @author  MOSSKEER 王可
 * @date    2024.8.7
 *********************************************************************/

#include "gme_cstrapi_face_spl_ctrlpts_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/splsurf.hxx"
#include "acis_utils.hpp"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_spl_ctrlpts demo 1:
//
// APIs:
//    api_face_spl_ctrlpts
//
// Description:
//
// **********************************************************************************
outcome aei_FACE_SPL_CTRLPTS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    API_BEGIN

    splsurf surf = splsurf();
    SPAposition* ctrlpoints1 =
      ACIS_NEW SPAposition[15]{SPAposition(-10, -10, 20), SPAposition(-5, 0, 10),  SPAposition(-20, 20, 30), SPAposition(-20, -15, 10), SPAposition(-30, -10, 0), SPAposition(-30, 25, -30), SPAposition(0, -10, -20), SPAposition(5, -12, -30),
                               SPAposition(0, 15, 15),    SPAposition(30, -6, -5), SPAposition(25, -10, 0),  SPAposition(30, 25, -30),  SPAposition(10, -10, 10), SPAposition(25, -10, 20),  SPAposition(20, 20, 30)};
    surf.set_ctrlpt_array(ctrlpoints1, 5, 3);
    surf.set_u_param(3, 0, 0, 0);
    surf.set_v_param(2, 0, 0, 0);
    double* uknots = new double[9]{0, 0, 0, 0, 0.5, 1, 1, 1, 1};
    surf.set_u_knot_array(uknots, 9);
    double* vknots = new double[6]{0, 0, 0, 1, 1, 1};
    surf.set_v_knot_array(vknots, 6);

    gme_api_face_spl_ctrlpts(&surf, face);

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
//	  face_spl_ctrlpts demo 2:
//
// APIs:
//    api_face_spl_ctrlpts
//
// Description:
//
// **********************************************************************************
outcome aei_FACE_SPL_CTRLPTS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    API_BEGIN

    SPAposition* ctrlpoints2 = ACIS_NEW SPAposition[16]{
      SPAposition(0, 0, 0), SPAposition(1, 0, 1), SPAposition(2, 0, 1), SPAposition(3, 0, 0), SPAposition(0, 1, 1), SPAposition(1, 1, 2), SPAposition(2, 1, 2), SPAposition(3, 1, 1),
      SPAposition(0, 2, 1), SPAposition(1, 2, 2), SPAposition(2, 2, 2), SPAposition(3, 1, 2), SPAposition(0, 3, 0), SPAposition(1, 3, 1), SPAposition(2, 3, 1), SPAposition(3, 3, 0),
    };
    splsurf surf2 = splsurf();
    surf2.set_ctrlpt_array(ctrlpoints2, 4, 4);
    surf2.set_u_param(3, 0, 0, 0);
    surf2.set_v_param(3, 0, 0, 0);

    double* uknots2 = new double[8]{0, 0, 0, 0, 1, 1, 1, 1};
    surf2.set_u_knot_array(uknots2, 8);

    double* vknots2 = new double[8]{0, 0, 0, 0, 1, 1, 1, 1};
    surf2.set_v_knot_array(vknots2, 8);

    gme_api_face_spl_ctrlpts(&surf2, face);

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
//	  face_spl_ctrlpts demo 3:
//
// APIs:
//    api_face_spl_ctrlpts
//
// Description:
//
// **********************************************************************************
outcome aei_FACE_SPL_CTRLPTS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    API_BEGIN

    SPAposition* ctrlpoints3 = ACIS_NEW SPAposition[15]{SPAposition(0, 0, 0),  SPAposition(0, 0, -1),  SPAposition(0, 1, -1),   SPAposition(1, 0.5, 0),  SPAposition(1, 0.5, -1), SPAposition(1, 1.5, -1), SPAposition(2, 0, 0), SPAposition(2, 0, -1),
                                                        SPAposition(2, 1, -1), SPAposition(3, 0.5, 0), SPAposition(3, 0.5, -1), SPAposition(3, 1.5, -1), SPAposition(4, 0, 0),    SPAposition(4, 0, -1),   SPAposition(4, 1, -1)};
    splsurf surf3 = splsurf();
    surf3.set_ctrlpt_array(ctrlpoints3, 5, 3);
    surf3.set_u_param(3, 0, 0, 0);
    surf3.set_v_param(2, 0, 0, 0);

    double* uknots3 = new double[7]{0, 0, 0, 2, 4, 4, 4};
    surf3.set_u_knot_array(uknots3, 7);

    double* vknots3 = new double[4]{0, 0, 1, 1};
    surf3.set_v_knot_array(vknots3, 4);
    outcome acis_res;
    acis_res = gme_api_face_spl_ctrlpts(&surf3, face);

    std::string acis_err_info;  // acis result的err info
    acis_err_info = process(acis_res);

    API_END

    if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}