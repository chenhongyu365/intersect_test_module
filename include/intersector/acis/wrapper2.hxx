/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

#ifndef BHL_WRAPPERS
#define BHL_WRAPPERS

#include "curextnd.hxx"
#include "bs3cutil.hxx"
#include "bs3surf.hxx"
#include "pcudef.hxx"
#include "edge.hxx"

#include "dcl_stitch.h"
#include "spa_null_base.hxx"

DECL_STITCH logical
hh_surf_point_perp( const surface &surf,
				    SPAposition const &pos,
					SPAposition& foot,
					SPAunit_vector& norm,
					SPApar_pos const &param_guess = SpaAcis::NullObj::get_par_pos(),
					SPApar_pos &param_actual = SpaAcis::NullObj::get_par_pos(),
					logical f_weak = FALSE) ;

DECL_STITCH logical
hh_curve_point_perp( const curve & cur,
					 SPAposition const &pos,
					 SPAposition &foot,
					 SPAunit_vector &norm,
					 SPAparameter const &param_guess = SpaAcis::NullObj::get_parameter(),
					 SPAparameter &param_actual = SpaAcis::NullObj::get_parameter(),
					 logical f_weak=FALSE
				   );


DECL_STITCH logical
hh_bs3_curve_invert( double& ,
					 SPAposition const &,	// given point
					 double,				// given tolerance
					 bs3_curve,			// given curve
					 SPAparameter const &param = SpaAcis::NullObj::get_parameter()	// SPAparameter guess
					 );

DECL_STITCH logical
hh_bs3_curve_perp (
				    SPAposition const &,	// given point
					bs3_curve,			// curve
					SPAposition &,			// (returned) foot of perpendicular
					SPAunit_vector &,		// (returned) curve tangent
					SPAparameter const & param1= SpaAcis::NullObj::get_parameter(),
										// supplied approximate SPAparameter
					SPAparameter & param2 = SpaAcis::NullObj::get_parameter()
										// (returned) actual SPAparameter
				);

DECL_STITCH logical
hh_eval_position( const curve &cur,
				double parval,
			    SPAposition& ret_pos
				);

DECL_STITCH logical
hh_eval_position( const pcurve &,
			    SPApar_pos& ,
				SPAposition const & ,
				double &
				);

DECL_STITCH logical
hh_extend_curve_approx(
		const curve &old_cur,
		curve*& extended_cur,
		SPAinterval const &new_range,
		SPAinterval &actual_range_achieved = SpaAcis::NullObj::get_interval(),
		logical = TRUE,
		extension_info & = SpaAcis::NullObj::get_extension_info(),
		logical f_rebuild_bs = FALSE
	);

DECL_STITCH logical
hh_surf_param ( const surface &surf,
			    SPApar_pos& ,
			    SPAposition const &,
				SPApar_pos const & = SpaAcis::NullObj::get_par_pos());

DECL_STITCH logical
hh_curve_param( const curve & ,
			    double&  ,
				SPAposition const & ,
				SPAparameter const &param = SpaAcis::NullObj::get_parameter());

DECL_STITCH logical
hh_new_intcurve( intcurve*& ,
				bs3_curve ,
				double ,
				surface const & ,
				surface const &,
				bs2_curve bs2_cur1 = NULL,
				bs2_curve bs2_cur2 = NULL,
				const SPAinterval& inter= SpaAcis::NullObj::get_interval(),
				logical parametric_primary = FALSE
				);

DECL_STITCH logical
hh_curve_subset( bs3_curve & ,     //
				bs3_curve&,				// given curve
				SPAinterval const &,		// required bounds
				double = 0,				// required fit tolerance
				double & = SpaAcis::NullObj::get_double()
									// returns actual fit tolerance
				);

#endif //BHL_WRAPPERS

