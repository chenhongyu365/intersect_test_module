/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef SPA_SWEEP_EXAMPLES_HXX
#define SPA_SWEEP_EXAMPLES_HXX

class outcome;
class ENTITY_LIST;
class AcisOptions;

outcome aei_SWEEP_PIPE_THROUGH_E_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_WEDGE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_CONE1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_BOX_WITH_HOLE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DEFORMED_TUBING(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DEGEN_DRAFT_BOX(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_PIPE_THROUGH_SLOTTED_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_BOX_CYL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_TORUS_THROUGH_E_BLOCK(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_HEART(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_APPLE_PEEL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_RIGID_TUBE1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_UFO1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_TWISTED_TUBE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_RIGID_TUBE2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_SHAFT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_RIGID_PIPE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_RIGID_PIPE_SHAFT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_FIN(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_ABSTRACT_ART(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_TUBE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_POLYGON1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_POLYGON2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_ARCH(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_BOX1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_CONE2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_ANGLED_POLYGON(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_DRAFTED_BOX2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

outcome aei_SWEEP_UFO2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt);

#endif
