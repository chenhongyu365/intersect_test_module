#pragma once
/*********************************************************************
 * @file    gme_cstrapi_2_face_torus_example.hxx
 * @brief   api_2_face_torus的demo测试相关头文件
 * @details
 * @author  罗坤
 * @date    2024.10.16
 *********************************************************************/

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_2_FACE_TORUS_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_2_FACE_TORUS_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_2_FACE_TORUS_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);