/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef MT_EXAMPLES_HXX
#define MT_EXAMPLES_HXX

class outcome;
class ENTITY_LIST;
class AcisOptions;
outcome aei_MT_EGG_SLICE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);
outcome aei_PROCESS_MT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);
outcome aei_MT_WORK_PACKET_QUEUE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

#endif //MT_EXAMPLES_HXX
