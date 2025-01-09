/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef SPA_LOP_EXAMPLES1_HXX
#define SPA_LOP_EXAMPLES1_HXX

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_LOP_EDGE_TAPER_FACES1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_EDGE_TAPER_FACES2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_PLANE_TAPER_FACES(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_MOVE_FACES_TRANSLATE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_MOVE_FACES_ROTATE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_OFFSET_FACES(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_LOP_OFFSET_BODY_NEGOFST(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

#endif
