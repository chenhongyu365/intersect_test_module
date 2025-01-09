/*********************************************************************
 * @file    gme_cstrapi_make_wire_example.hxx
 * @brief	展示了生成单个的wire_body，有两个wire的body，和有solid有wire的混合body
 * @details DEMO2、DEMO3展示的是一个body，不同部分不同颜色
 * @author  全志成
 * @date    2023.7.24
 *********************************************************************/
#pragma once

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_MAKE_WIRE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_MAKE_WIRE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_MAKE_WIRE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
