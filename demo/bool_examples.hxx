/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef SPA_BOOL_EXAMPLES_HXX
#define SPA_BOOL_EXAMPLES_HXX

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_BOOL_PROJECT_WIRE_TO_BODY(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_PROJECT_EDGE_TO_FACE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_UNITE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_INTERSECTION(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_SUBTRACTION(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_CHOP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_SPLIT_WIRE_EDGE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_SUBDIVIDE_FACE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BOOL_MAKE_SHADOW(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

#endif  // SPA_BOOL_EXAMPLES_HXX
