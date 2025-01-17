/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

//----------------------------------------------------------------------------

#if !defined	ATTRIB_HH_ENT_GEOMBUILD_SHELL_CLASS
#define			ATTRIB_HH_ENT_GEOMBUILD_SHELL_CLASS
//----------------------------------------------------------------------------

#include	"dcl_heal.h"
#include	"entgmbld.hxx"

class ATTRIB_HH_AGGR_GEOMBUILD_BASE;
class SHELL;
//----------------------------------------------------------------------------
/**
 * @nodoc
 */
ENTITY_IS_PROTOTYPE(ATTRIB_HH_ENT_GEOMBUILD_SHELL, HEAL )
#if 0
; // semicolon needed for mkman (doc tool) parsing
#endif

DECL_HEAL extern int ATTRIB_HH_ENT_GEOMBUILD_SHELL_TYPE;
/**
 * @nodoc
 */
#define ATTRIB_HH_ENT_GEOMBUILD_SHELL_LEVEL (ATTRIB_HH_ENT_GEOMBUILD_BASE_LEVEL + 1 )

//----------------------------------------------------------------------------

class DECL_HEAL ATTRIB_HH_ENT_GEOMBUILD_SHELL : public ATTRIB_HH_ENT_GEOMBUILD_BASE {
	protected:

	int closure;			// = 1 -> shell is open
	int faces_orient;		// = 1 -> shell faces inconsistently oriented
	int fafa_inter;			// = 1 -> shell faces intersect
	int single_volume;		// = 1 -> shell not composed of a single volume
// STI cpp begin
		logical save_sw;
// STI cpp end


	public:
		ATTRIB_HH_ENT_GEOMBUILD_SHELL( SHELL *e=NULL);
		/**
		 * @nodoc
		 */
		ATTRIB_FUNCTIONS( ATTRIB_HH_ENT_GEOMBUILD_SHELL, HEAL )
#if 0
; // semicolon needed for mkman (doc tool) parsing)
#endif
// Because mkman isn't aware that ATTRIB_FUNCTIONS changes access to "public", we do so
// explicitly here:
public:


    virtual logical pattern_compatible() const;
                                    // returns TRUE
	// Set functions
	void set_closure (int q) {closure = q;}
	void set_faces_orient (int q) {faces_orient = q;}
	void set_fafa_inter (int q) {fafa_inter = q;}
	void set_single_volume (int q) {single_volume = q;}

	// Get functions
	int get_closure () const {return closure;}
	int get_faces_orient () const {return faces_orient;}
	int get_fafa_inter () const {return fafa_inter;}
	int get_single_volume () const {return single_volume;}
	int get_quality () const;

	// Reset attribute
	void reset() ;
	int adv_check() ;

};

#endif  //ATTRIB_HH_ENT_GEOMBUILD_SHELL_CLASS
