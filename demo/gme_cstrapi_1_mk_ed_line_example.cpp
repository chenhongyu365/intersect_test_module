/*********************************************************************
 * @file    gme_cstrapi_1_mk_ed_line_example.cpp
 * @brief
 * @details
 * @author  MOSSKEER Íõ¿É
 * @date    2024.7.26
 *********************************************************************/

#include "gme_cstrapi_1_mk_ed_line_example.hxx"

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/sp3crtn.hxx"


// **********************************************************************************
// C++ Example:
//
// Title:
//	  mk_ed_line_demo:
//
// APIs:
//    gme_mk_ed_line
//
// Description:
//	  create edge line by call gme_1_api_mk_ed_line.
// **********************************************************************************
outcome aei_1_MK_ED_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt /*= nullptr*/) {
    EDGE* line = nullptr;

    /* API Call Block */
    API_BEGIN

    gme_1_api_mk_ed_line(SPAposition(0, 0, 0), SPAposition(0.001, 0, 0), line);

    API_END
    if(result.ok()) {
        output_ents.add(line);
    }
    return result;
}