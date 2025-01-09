/*********************************************************************
 * @file    spd_ent99_example.cpp
 * @brief   HD_PEL_ENT99 demo
 * @details
 * @author  charynnc
 * @date    2023.8.1
 *********************************************************************/

#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/insanity_list.hxx"
#include "acis/intrapi.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"
// **********************************************************************************
// C++ Example:
//
// Title:
//	  spd entity:
//
// APIs:
//    gme_HD_PEL_ENT99
//
// Description:
//      普通平面
// **********************************************************************************
outcome aei_HD_PEL_ENT99_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {1, 1, 1};
    double e[3] = {M_PI / 2, 0, 0};
    double h = 5;

    int n = 5;
    double s[5][3] = {
      {4,   1, 0},
      {0,   5, 0},
      {1.5, 5, 2},
      {0,   1, 2},
      {1.5, 1, 0}
    };

    result = gme_HD_PEL_ENT99(p, e, h, n, s, body);

    API_END if(result.ok()) {
        output_ents.add(body);
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
//    gme_HD_PEL_ENT99
//
// Description:
//      带孔平面
// **********************************************************************************
outcome aei_HD_PEL_ENT99_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {1, 1, 1};
    double e[3] = {M_PI / 2, M_PI/3, M_PI/4};
    double h = 5;

    int n = 10;
    double s[10][3] = {
      {4,   1,   0  },
      {0,   5,   0  },
      {1.5, 5,   2  },
      {0,   1,   2  },
      {1.5, 1,   0  },
      {2,   1.5, 0.5},
      {0,   4.5, 0.5},
      {0,   4.5, 1.5},
      {0,   1.5, 1.5},
      {0,   1.5, 0.5}
    };

    result = gme_HD_PEL_ENT99(p, e, h, n, s, body);

    API_END if(result.ok()) {
        output_ents.add(body);
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
//    gme_HD_PEL_ENT99
//
// Description:
//      高度为0
// **********************************************************************************
outcome aei_HD_PEL_ENT99_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    BODY* body = nullptr;
    API_BEGIN
    double p[3] = {1, 1, 1};
    double e[3] = {M_PI / 2, M_PI/3, M_PI/4};
    double h = 0;

    int n = 5;
    double s[5][3] = {
      {4,   1, 0},
      {0,   5, 0},
      {1.5, 5, 2},
      {0,   1, 2},
      {1.5, 1, 0}
    };

    result = gme_HD_PEL_ENT99(p, e, h, n, s, body);

    API_END if(result.ok()) {
        output_ents.add(body);
    }

    return result;
}