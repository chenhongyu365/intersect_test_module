/*********************************************************************
 * @file    gme_cstrapi_1_fit_plane_example.hxx
 * @brief	为随机生成的散点拟合一个平面，生成的黄色平面为api_fit_plane，蓝绿平面为gme_fit_plane
 * @details
 * @author  lgr
 * @date    2024.10.20
 *********************************************************************/
#pragma once

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_1_FIT_PLANE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
