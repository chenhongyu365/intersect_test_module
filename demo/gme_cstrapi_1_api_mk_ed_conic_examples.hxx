/*********************************************************************
 * @file    gme_cstrapi_1_api_mk_ed_conic_examples.hxx
 * @brief	gme_1_api_mk_ed_conic demo
 * @details	用于可视化创建 B样条绘制的圆锥曲线
 * @author  赵川熠Ori
 * @date    2024.9.29
 *********************************************************************/
#pragma once
#include "acis/acis_options.hxx"
#include "acis/api.hxx"
#include "acis/lists.hxx"

// 新 demo
outcome aei_MAKE_EDGE_CONIC_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
