/*********************************************************************
 * @file    gme_cstrapi_1_make_frustum_example.cpp
 * @brief
 * @details
 * @author  linchforever
 * @date    2024.7.26
 *********************************************************************/
#include "gme_cstrapi_1_make_frustum_example.hxx"

#include <vector>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"
#include "template_examples.hxx"
// #include "template_simple_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  1_frustum_demo:
//
// APIs:
//    gme_1_api_make_frustum
//
// Description:
//	  构造上窄下宽的正常圆台
// **********************************************************************************
outcome aei_1_FRUSTUM_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_frustum(4.0, 3.0, 5.0, 2.0, body);
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
//	  1_frustum_demo:
//
// APIs:
//    gme_1_api_make_frustum
//
// Description:
//	  构造上宽下窄的正常圆台
// **********************************************************************************
outcome aei_1_FRUSTUM_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_frustum(4.0, 3.0, 5.0, 10.0, body);
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
//	  1_frustum_demo:
//
// APIs:
//    gme_1_api_make_frustum
//
// Description:
//	  构造正常圆柱
// **********************************************************************************
outcome aei_1_FRUSTUM_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_frustum(4.0, 3.0, 3.0, 3.0, body);
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
//	  1_frustum_demo:
//
// APIs:
//    gme_1_api_make_frustum
//
// Description:
//	  构造圆锥（top = 0）
// **********************************************************************************
outcome aei_1_FRUSTUM_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_frustum(4.0, 3.0, 3.0, 0.0, body);
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
//	  1_frustum_demo:
//
// APIs:
//    gme_1_api_make_frustum
//
// Description:
//	  构造top小于容差时的圆台
// **********************************************************************************
outcome aei_1_FRUSTUM_DEMO5(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    /* Initialization Block */

    BODY* body = NULL;  // Pointer to tool body

    /* API Call Block */
    API_BEGIN
    gme_1_api_make_frustum(4.0, 3.0, 3.0, 0.1 * SPAresabs, body);
    API_END

    if(result.ok()) {
        output_ents.add(body);
    }
    return result;
}