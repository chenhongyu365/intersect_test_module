/*********************************************************************
 * @file    gme_cstrapi_fit_line_example.hxx
 * @brief	为随机生成的散点拟合一条直线，生成的蓝绿长线为api_fit_line，较短黄线为gme_fit_line
 * @details
 * @author  全志成
 * @date    2023.7.24
 *********************************************************************/
#pragma once

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_FIT_LINE_DEMO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);