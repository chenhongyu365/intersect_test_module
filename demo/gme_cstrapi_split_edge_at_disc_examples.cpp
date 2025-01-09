/*********************************************************************
 * @file    splitedgeatdisc_examples.cpp
 * @brief
 * @details
 * @author  mshct
 * @date    2024.7.23
 *********************************************************************/

#include "gme_cstrapi_split_edge_at_disc_examples.hxx"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "access.hpp"
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"

// **********************************************************************************
// C++ Example:
//
// Title:
//	  splitedgeatdisc_demo:
//
// APIs:
//    gme_api_split_edge_at_disc
//
// Description:
//
// **********************************************************************************

outcome aei_SPLIT_EDGE_AT_DISC_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
    using namespace std::filesystem;
    path test_path = current_path();
    test_path = test_path.parent_path().parent_path() / "tests" / "split_edge_at_disc" / "edgeof4_order2.sat";
    ENTITY* ent = nullptr;
    acis_api_restore_entity(test_path.string().c_str(), ent);
    ENTITY_LIST list;
    rgb_color colors[6] = {
      rgb_color(0.0, 0.0, 1.0),  // Blue
      rgb_color(1.0, 0.0, 0.0),  // Red
      rgb_color(0.0, 1.0, 0.0),  // Green
      rgb_color(1.0, 1.0, 0.0),  // Yellow
      rgb_color(1.0, 0.0, 1.0),  // Magenta
      rgb_color(1.0, 0.5, 0.0)   // Orange
    };

    API_BEGIN
    check_outcome(gme_api_split_edge_at_disc(((BODY*)ent)->lump()->shell()->wire()->coedge()->edge(), list, 2));
    API_END

    if(result.ok()) {
        for(int i = 0; i < list.iteration_count(); i++) {
            api_rh_set_entity_rgb(list[i], colors[i % 6]);
        }
        output_ents.add(list);
    }
    return result;
}
