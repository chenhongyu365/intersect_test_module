

#include <random>
#include "acis/acis.hxx"
#include "acis/alltop.hxx"
#include "acis/cstrapi.hxx"
#include "acis/rgbcolor.hxx"
#include "acis/rnd_api.hxx"
#include "acis_utils.hpp"
#include "gme_spd_cstrapi.hxx"

outcome aei_HD_PEL_ENT13_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr){
    BODY* body = nullptr;

    API_BEGIN
    
    double p[4][3] ={
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    result = gme_HD_PEL_ENT13(p, body);

    API_END

    if(result.ok()) {
        output_ents.add(body);
    }

    return result;

}