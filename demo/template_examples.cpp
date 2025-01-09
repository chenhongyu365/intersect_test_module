/*********************************************************************
 * @file    template_examples.cpp
 * @brief
 * @details
 * @author  CastaneaG
 * @date    2023.6.17
 *********************************************************************/
#include "template_examples.hxx"

#include <vector>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cnstruct.hxx"
#include "acis/cstrapi.hxx"
#include "acis/ewire.hxx"
#include "acis/intdef.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"

// #include "template_simple_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  cuboid_demo:
//
// APIs:
//    gme_api_make_cuboid
//
// Description:
//	  create cuboid by call gme_api_make_cuboid.
//    Save the cuboid entity to .sat file, then restore it.
// **********************************************************************************
outcome aei_CUBOID_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_api_make_cuboid(2.0, 2.0, 2.0, body);
    // acis_api_save_entity("C:\\Users\\Lenovo\\Desktop\\cuboid.sat", body);
    API_END

    if(result.ok()) {
        // ENTITY* ent = nullptr;
        // acis_api_restore_entity("C:\\Users\\Lenovo\\Desktop\\cuboid.sat", ent);
        // for(int i = 0; i < faces.size(); i++) {
        output_ents.add(body);
        //}
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  face_torus:
//
// APIs:
//    gme_api_face_torus
//
// Description:
//	  create torus face by call gme_api_face_torus.
// **********************************************************************************
outcome aei_FACE_TORUS(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    FACE* face = nullptr;

    /* API Call Block */
    API_BEGIN

    double major = 10;
    double minor = 5;

    double us = 0;
    double ue = 360;
    double vs = 0;
    double ve = 360;

    result = gme_api_face_torus(SPAposition(0, 0, 0), major, minor, us, ue, vs, ve, nullptr, face);

    API_END

    if(result.ok()) {
        output_ents.add(face);
        // acis_api_save_entity("D:\\Users\\13062\\Desktop\\test\\tortest.sat", face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  SPLINE INTERPOLATE:
//
// APIs:
//    gme_api_mk_fa_spl_intp
//
// Description:
//	  create spline face by call gme_api_mk_fa_spl_intp.
// **********************************************************************************
outcome aei_FACE_SPL_INTP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    FACE* face = nullptr;
    API_BEGIN

    std::vector<SPAposition> poses;

    poses.push_back(SPAposition(0, 1, -1));  // 0
    poses.push_back(SPAposition(1, 0, 1));   // 1
    poses.push_back(SPAposition(3, 0, 1));   // 2
    poses.push_back(SPAposition(5, 0, 1));   // 3
    poses.push_back(SPAposition(6, 0, 2));   // 4

    poses.push_back(SPAposition(0, 1.3, -1));  // 0
    poses.push_back(SPAposition(1, 1, 0));     // 1
    poses.push_back(SPAposition(3, 1, 0));     // 2
    poses.push_back(SPAposition(5, 1, 0));     // 3
    poses.push_back(SPAposition(6, 1, 2));     // 4

    poses.push_back(SPAposition(0, 1.7, -1));  // 0
    poses.push_back(SPAposition(1, 2, 0));     // 1
    poses.push_back(SPAposition(3, 2, 0));     // 2
    poses.push_back(SPAposition(5, 2, 0));     // 3
    poses.push_back(SPAposition(6, 2, 2));     // 4

    poses.push_back(SPAposition(0, 2, -1));  // 0
    poses.push_back(SPAposition(1, 3, 1));   // 1
    poses.push_back(SPAposition(3, 3, 1));   // 2
    poses.push_back(SPAposition(5, 3, 1));   // 3
    poses.push_back(SPAposition(6, 3, 2));   // 4
    std::vector<SPAunit_vector> usvec_data;
    usvec_data.push_back(SPAunit_vector(10, -1, -5));
    usvec_data.push_back(SPAunit_vector(10, 0, -5));
    usvec_data.push_back(SPAunit_vector(10, 0, -5));
    usvec_data.push_back(SPAunit_vector(10, 1, -5));
    outcome gme_res = gme_api_mk_fa_spl_intp(5, 4, poses.data(), usvec_data.data(), NULL, NULL, NULL, face);

    api_rh_set_entity_rgb(face, rgb_color(0.2, 0.5, 0.5));

    API_END if(result.ok()) {
        output_ents.add(face);
    }
    return result;
}

// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT98
//
// Description:
//	  create spd entity by call gme_HD_PEL_ENT98.
// **********************************************************************************
outcome aei_SPD_ENT98(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    BODY* body = nullptr;

    /* API Call Block */
    API_BEGIN

    double p[3] = {1, 2, 4};
    double e[3] = {M_PI / 3, M_PI / 3, M_PI / 2};
    double a = M_PI;

    // 类似长方形包长方形
    // int n = 10;
    // double s[10][3] = {
    //  {4,   1,   0  },
    //  {0,   5,   0  },
    //  {1.5, 5,   2  },
    //  {0,   1,   2  },
    //  {1.5, 1,   0  },
    //  {2,   1.5, 0.5},
    //  {0,   4.5, 0.5},
    //  {0,   4.5, 1.5},
    //  {0,   1.5, 1.5},
    //  {0,   1.5, 0.5}
    //};

    // 长方形上面有两个孔
    // int n = 11;
    // double s[11][3] = {
    //  {4,   1, 0  },
    //  {0,   5, 0  },
    //  {1.5, 5, 2  },
    //  {0,   1, 2  },
    //  {1.5, 1, 0  },
    //  {2,   2, 0.5},
    //  {0.5, 2, 1.5},
    //  {0.5, 2, 0.5},
    //  {2,   4, 0.5},
    //  {0.5, 4, 1.5},
    //  {0.5, 4, 0.5}
    //};

    // 单纯类长方形面
    int n = 5;
    double s[5][3] = {
      {4,   1, 0},
      {0,   5, 0},
      {1.5, 5, 2},
      {0,   1, 2},
      {1.5, 1, 0}
    };

    result = gme_HD_PEL_ENT98(p, e, a, n, s, body);

    API_END

    if(result.ok()) {
        output_ents.add(body);
        // acis_api_save_entity("D:\\Users\\13062\\Desktop\\test\\ent98.sat", body);
    }
    return result;
}

outcome aei_EDGE_CUBIC(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    std::vector<SPAposition> poses;
    poses.push_back(SPAposition(0, -1, 0));
    poses.push_back(SPAposition(-1, 0, 0));
    poses.push_back(SPAposition(-2, 1, 0));
    poses.push_back(SPAposition(-1, 2, 0));
    poses.push_back(SPAposition(-0.1, 1.5, 0));
    poses.push_back(SPAposition(0, 1.4, 0));
    poses.push_back(SPAposition(0.1, 1.5, 0));
    poses.push_back(SPAposition(1, 2, 0));
    poses.push_back(SPAposition(2, 1, 0));
    poses.push_back(SPAposition(1, 0, 0));
    poses.push_back(SPAposition(0, -1, 0));
    EDGE* edge = nullptr;
    API_BEGIN
    gme_api_mk_ed_cubic(11, poses.data(), SPAunit_vector(-1, 1, 0), SPAunit_vector(-1, -1, 0), 0, edge);
    API_END
    if(result.ok()) {
        output_ents.add(edge);
    }

    return result;
}