/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef SPA_BLEND_EXAMPLES_HXX
#define SPA_BLEND_EXAMPLES_HXX

class outcome;
class ENTITY_LIST;
class AcisOptions;

// Constant Radius
outcome aei_BLEND_WIGGLE_CONST(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// Variable Radius
outcome aei_BLEND_WIGGLE_VAR(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_HOLDLINE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_ELLIPTICAL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_RADIUS_TRANSITION1(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_RADIUS_TRANSITION2(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_GRIP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// Chamfer
outcome aei_BLEND_PENCIL(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_SPLINE_CHAMFER(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_TWISTED_BAR(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// Entity-Entity
outcome aei_BLEND_WINE_GLASS(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_NUMBER_NINE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// Annotations
outcome aei_BLEND_ANNOTATION(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// Vertex blends
outcome aei_BLEND_DICE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_BRITISH_DICE(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

// End processing
outcome aei_BLEND_MITRE_AND_CAP(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);
outcome aei_BLEND_CLOWN_HAT(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt = nullptr);

#endif
