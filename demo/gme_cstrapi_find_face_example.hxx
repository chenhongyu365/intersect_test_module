/*********************************************************************
 * @file    gme_cstrapi_find_face_example.hxx
 * @brief	展示了寻找body中与给定单位向量和平面法向量点乘最大的平面，
 *          若有多个相同，则找平面上点p与给定单位向量点乘最大的平面
 * @details DEMO1展示立方体平面，DEMO2展示一系列随机生成的平面，DEMO3展示一系列平行平面
 * @author  全志成
 * @date    2023.8.1
 *********************************************************************/
#pragma once

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_FIND_FACE_DEMO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_FIND_FACE_DEMO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_FIND_FACE_DEMO3(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_FIND_FACE_DEMO4(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
