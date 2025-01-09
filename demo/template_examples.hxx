/*********************************************************************
 * @file    template_examples.hxx
 * @brief
 * @details
 * @author  CastaneaG
 * @date    2023.6.17
 *********************************************************************/
#pragma once
#include "acis/acis_options.hxx"
#include "acis/api.hxx"
#include "acis/lists.hxx"

// 新 demo
outcome aei_CUBOID_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_FACE_TORUS(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_FACE_SPL_INTP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_SPD_ENT98(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_EDGE_CUBIC(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);