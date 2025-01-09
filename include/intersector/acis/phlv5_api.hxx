// COPYRIGHT DASSAULT SYSTEMES 1989
#if !defined( PHLV5API_HXX )
#define PHLV5API_HXX
#include "dcl_phlv5.h"
#include "api.hxx"
#include "logical.h"
#include "vector.hxx"
#include "lists.hxx"
#include "vlists.hxx"
#include "asm_api.hxx"

class PHLV5_EDGE;
class phlv5_options;
class PHLV5_CAMERA;
class FACE;

extern option_header use_CGM_hlr;
/**
 * @file phlv5_api.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \defgroup PHLV5API CGM Hidden Line Removal
 *
 * \ingroup VISMODULE
 * @{
 */
/**
 * Initializes the hidden line library.
 * <br><br>
 * <b>Effect:</b> System routine
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
**/
DECL_PHLV5 outcome api_initialize_hidden_line_removal();

/**
 * Terminates the hidden line library.
 * <br><br>
 * <b>Effect:</b> System routine
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
**/
DECL_PHLV5 outcome api_terminate_hidden_line_removal();
/**
 * Defines a phl_body_occurrence.
 * <br>
 * <b>Role:</b> The <tt>phl_body_occurrence</tt> class acts as holder of <tt>BODY</tt> pointer
 * and <tt>VOID_LIST</tt> of <tt>SPAtransf</tt> pointers. The <tt>VOID_LIST</tt> of
 * <tt>phl_body_occurrence</tt> is input to API <tt>api_phlv5_compute</tt> when a body has
 * multiple occurrences as in the case of an assembly.
 * <br><br>
 * @see BODY,SPAtransf,VOID_LIST
 */
class DECL_PHLV5 phl_body_occurrence : public ACIS_OBJECT
{
	
	ENTITY * _body;
	VOID_LIST _trans;
	VOID_LIST _user_data;
public:
	// Main constructor
/**
 * @param Body
 * Body.
 * @param trans
 * VOID_LIST of SPAtransf pointers.
 */
	phl_body_occurrence(ENTITY * body,VOID_LIST &trans)
	{
		_trans = trans;
		_body = body;
	};
/**
 * @param Body
 * Body.
 * @param trans
 * @param user_data
 * VOID_LIST of SPAtransf pointers.
 */
	phl_body_occurrence( ENTITY * body, VOID_LIST & trans, VOID_LIST & user_data)
	{
		_trans = trans;
		_body = body;
		_user_data = user_data;
	};
/**
*  return the BODY pointer
*/
	ENTITY * body(){
		return _body;
	};
/**
*  return the VOID_LIST of SPAtranf pointers.
*/
	VOID_LIST& trans(){
		return _trans;
	};
/**
*  return the VOID_LIST of user data pointers.
*/
	VOID_LIST& user_data(){
		return _user_data;
	};
};

// -----------------------------------------------------------------------------------------------------
//
// API's
//
// -----------------------------------------------------------------------------------------------------
/**
 * Computes hidden line data for the given viewing parameters and list of bodies.
 * <br><br>
 * <b>Role:</b> If the view token is nonzero, the data is stored on the model as
 * attributes and identified by <tt>token</tt>. Make <tt>token</tt> zero if you do not wish to store
 * the view. Existing attributes identified by the same token are replaced. If the
 * perspective projection flag <tt>persp</tt> is TRUE, data is calculated for display in a
 * perspective projection; otherwise, calculations are done for a parallel
 * projection.
 * <br><br>
 * The options argument is of type <tt>phlv5_options</tt> and contains options for the
 * hidden line removal algorithm.
 * <br><br>
 * <i><b>Note</b> All data returned is allocated with</i> <tt>new</tt>.<i>It is the user's responsibility
 * to call</i> <tt>lose</tt> <i>for all the entities in the edge list when they are no longer
 * needed.</i>
 * <br><br>
 * <b>Errors:</b> The distance between eyepos and target is less than <tt>SPAresabs</tt>.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param bodies
 * body list.
 * @param token
 * view token.
 * @param eyepos
 * eye position.
 * @param target
 * target position.
 * @param persp
 * perspective projection flag.
 * @param edges
 * output list of edges.
 * @param phlv5_opts
 * option class.
 * @param ao
 * acis options.
 **/
DECL_PHLV5 outcome api_phlv5_compute(
			ENTITY_LIST const& bodies,	 // body list
			int				   token,	 // view token
			SPAposition const&	   eyepos,	 // eye SPAposition
			SPAposition const&	   target,	 // target SPAposition
			logical			   persp,	 // TRUE iff perspective projection
			ENTITY_LIST&	   edges,
			phlv5_options* phlv5_opts = NULL,
			AcisOptions* ao = NULL);


/**
 * Computes hidden line data for the given viewing parameters and void list of occurrences.
 * <br><br>
 * <b>Role:</b> If the view token is nonzero, the data is stored on the model as
 * attributes and identified by <tt>token</tt>. Make <tt>token</tt> zero if you do not wish to store
 * the view. Existing attributes identified by the same token are replaced. If the
 * perspective projection flag <tt>persp</tt> is TRUE, data is calculated for display in a
 * perspective projection; otherwise, calculations are done for a parallel
 * projection.
 * <br><br>
 * The options argument is of type <tt>phlv5_options</tt> and contains options for the
 * hidden line removal algorithm.
 * <br><br>
 * <i><b>Note</b> All data returned is allocated with</i> <tt>new</tt>.<i>It is the user's responsibility
 * to call</i> <tt>lose</tt> <i>for all the entities in the edge list when they are no longer
 * needed.</i>
 * <br><br>
 * <b>Errors:</b> The distance between eyepos and target is less than <tt>SPAresabs</tt>.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param phlv5_occ_list
 * void list of occurrences of type </i><tt>phl_body_occurrence</tt><I>.
 * @param token
 * view token.
 * @param eyepos
 * eye position.
 * @param target
 * target position.
 * @param persp
 * perspective projection flag.
 * @param edges
 * output list of edges.
 * @param phlv5_opts
 * option class.
 * @param ao
 * acis options.
 **/
DECL_PHLV5 outcome api_phlv5_compute(
			VOID_LIST const& phlv5_occ_list,	 // occurrence list
			int				   token,	 // view token
			SPAposition const&	   eyepos,	 // eye SPAposition
			SPAposition const&	   target,	 // target SPAposition
			logical			   persp,	 // TRUE iff perspective projection
			ENTITY_LIST&	   edges,
			phlv5_options* phlv5_opts = NULL,
			AcisOptions* ao = NULL);


/**
 * Computes hidden line data for the given viewing parameters and assembly model.
 * <br><br>
 * <b>Role:</b> If the view token is nonzero, the data is stored on the model as
 * attributes and identified by <tt>token</tt>. Make <tt>token</tt> zero if you do not wish to store
 * the view. Existing attributes identified by the same token are replaced. If the
 * perspective projection flag <tt>persp</tt> is TRUE, data is calculated for display in a
 * perspective projection; otherwise, calculations are done for a parallel
 * projection.
 * <br><br>
 * The options argument is of type <tt>phlv5_options</tt> and contains options for the
 * hidden line removal algorithm.
 * <br><br>
 * <i><b>Note</b> All data returned is allocated with</i> <tt>new</tt>.<i>It is the user's responsibility
 * to call</i> <tt>lose</tt> <i>for all the entities in the edge list when they are no longer
 * needed.</i>
 * <br><br>
 * <b>Errors:</b> The distance between eyepos and target is less than <tt>SPAresabs</tt>.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Not Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param model
 * assembly model.
 * @param token
 * view token.
 * @param eyepos
 * eye position.
 * @param target
 * target position.
 * @param persp
 * perspective projection flag.
 * @param edges
 * output list of edges.
 * @param phlv5_opts
 * option class.
 * @param ao
 * acis options.
 **/
DECL_PHLV5 outcome api_asm_model_phlv5_compute(
			asm_model *			model, // assembly model
			int					token,	 // view token
			SPAposition const	eyepos,	 // eye SPAposition
			SPAposition const	target,	 // target SPAposition
			logical				persp,	 // TRUE iff perspective projection
			ENTITY_LIST &		edges,
			phlv5_options *		phlv5_opts = NULL,
			AcisOptions *		ao = NULL);


/**
 * Removes PHLV5 attributes from a list of bodies.
 * <br><br>
 * <b>Role:</b> This API removes and deletes any PHLV5 attributes with a
 * matching view token from the bodies list.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param bodies
 * body list.
 * @param token
 * view token.
 * @param ao
 * acis options.
 **/
DECL_PHLV5 outcome api_phlv5_clean(ENTITY_LIST const& bodies,
							   int token,
			AcisOptions* ao = NULL);
/**
 * Retrieves data stored in PHLV5 attributes with a matching view token and returns it as an <tt>ENTITY_LIST</tt> of <tt>PHLV5_EDGEs</tt>.
 * <br><br>
 * <b>Role:</b> Retrieves data stored in PHLV5 attributes with a matching view
 * token and returns it as an <tt>ENTITY_LIST</tt> of <tt>PHLV5_EDGEs</tt>. The attributes are placed
 * on the body by <tt>api_phlv5_compute</tt> when the <tt>api_phlv5_compute's token</tt> is set to
 * TRUE.
 * <br><br>
 * This API also returns the camera definition.
 * <br><br>
 * <i><b>Note</b> All data returned is a copy of the data stored in attributes on the body.
 * It is the user's responsibility to call</i> <tt>lose</tt> <i>for the returned camera and all
 * entities in the list, when they are no longer needed.</i>
 * <br><br>
 * <b>Errors:</b> The bodies in the list did not have matching <tt>PHLV5_CAMERAs</tt>.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
* <b>Journal: </b> Available
* <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param bodies
 * body list.
 * @param token
 * view token.
 * @param edges
 * edge list.
 * @param camera
 * camera definition.
 * @param ao
 * acis options.
 **/
DECL_PHLV5 outcome api_phlv5_retrieve(ENTITY_LIST const& bodies,   // body list
								  int                token,    // view token
								  ENTITY_LIST&       edges,    // edge list
								  PHLV5_CAMERA*&       camera,   // camera definition
								  AcisOptions* ao = NULL);

/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 void draw_phlv5_silhouette(PHLV5_EDGE* HE,
								  float* & listp,
								  long & n);

// -----------------------------------------------------------------------------------------------------
//
// Computer API's; work in progress; not ready for release. gto 01/01/02
//
// -----------------------------------------------------------------------------------------------------

class phlv5_options;
class CATHLRComputerACIS;
/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 outcome api_build_phlv5_computer(CATHLRComputerACIS*& in_computer,
										phlv5_options* phlv5_opts = NULL,
										AcisOptions* ao = NULL);
/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 outcome api_add_bodies_phlv5_computer(CATHLRComputerACIS* in_computer,
											 ENTITY_LIST const& _bodies,
											 phlv5_options* phlv5_opts = NULL,
											 AcisOptions* ao = NULL);
/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 outcome api_set_view_phlv5_computer(CATHLRComputerACIS* in_computer,
										   SPAposition eye, SPAposition target,
										   logical persp,
										   phlv5_options* phlv5_opts = NULL,
										   AcisOptions* ao = NULL);
/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 outcome api_compute_view_phlv5_computer(CATHLRComputerACIS* in_computer,
											   ENTITY_LIST& edges,
											   phlv5_options* phlv5_opts = NULL,
											   AcisOptions* ao = NULL);
/*
// tbrv
*/
/**
 * @nodoc
 */
DECL_PHLV5 outcome api_delete_phlv5_computer(CATHLRComputerACIS* in_computer,
										 phlv5_options* phlv5_opts = NULL,
										 AcisOptions* ao = NULL);

/**
* Creates a list of endpoints (positions) of hatch lines for a given planar face.
* <br><br>
* <b>Role:</b> Creates list of hatch line positions when provided with a planar face, a direction normal 
* to the hatch lines, spacing between the lines, and a starting point. 
* If the input face is not a plane, hatch lines are not created. Also, if the starting point does not lie
* on the input face or if the input hatch normal is not parallel to the face, no hatching is done.
* Appropriate error messages are thrown for each case.
* <br><br>
* <b>Limitations:</b> Hatch lines are not created for the following instances:<br>
* <ul>
* <li>If the input face is not planar, or</li>
* <li>If hatch normal is not parallel to the input face, or</li>
* <li>If the hatch starting point does not lie on the input face.</li>
* </ul>
* <br><br>
* <b>Errors:</b> 
* <br><br>
* <b>Effect:</b> Returns a list of hatch line positions (in the model space) and the number of hatch lines.
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param in_face
* Specifies the input face that needs to be hatched.
* @param hatchNormal
* Specifies the direction perpendicular to hatch lines (has to be parallel to input face).
* @param spacing
* Specifies the spacing between hatch lines.
* @param hatch_start_point
* Specifies the start point for creating hatch lines (must lie on the input face).
* @param do_hlr
* Indicates the logical parameter is not being used.
* @param number_of_hatch_lines
* Returns the number of hatch lines.
* @param hatch_line_list
* Returns the list of hatch line positions.
* @param ao
* Specifies ACIS options such as versioning and journaling.
 */
DECL_PHLV5 outcome api_create_hatch_lines(	FACE*			in_face, 
											SPAunit_vector	hatchNormal, 
											double			spacing, 
											SPAposition		hatch_start_point, 
											logical			do_hlr, 
											int&			number_of_hatch_lines, 
											SPAposition*&	hatch_line_list,
											AcisOptions*	ao = NULL);

/**
* Creates a list of endpoints (positions) of visible hatch lines for a given planar face.
* <br><br>
* <b>Role:</b> Creates list of visible hatch line positions when provided with a planar face, a direction normal 
* to the hatch lines, spacing between the lines, a starting point, and a list of bodies. 
* If the input face is not a plane, hatch lines are not created. Also, if the starting point does not lie
* on the input face or if the input hatch normal is not parallel to the face, no hatching is done.
* Appropriate error messages are thrown for each case.
* <br><br>
* <b>Limitations:</b> Hatch lines are not created for the following instances:<br>
* <ul>
* <li>If the input face is not planar, or</li>
* <li>If hatch normal is not parallel to the input face, or</li>
* <li>If the hatch starting point does not lie on the input face.</li>
* </ul>
* <br><br>
* <b>Errors:</b> 
* <br><br>
* <b>Effect:</b> Returns a list of visible hatch line positions (in the model space) and the number of visible hatch lines.
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
* @param in_face
* Specifies the input face that needs to be hatched.
* @param hatchNormal
* Specifies the direction perpendicular to hatch lines (has to be parallel to the input face).
* @param spacing
* Specifies the spacing between hatch lines.
* @param hatch_start_point
* Specifies the start point for creating hatch lines (must lie on the input face).
* @param bodies
* Specifies the list of bodies to be used for determining visibility of the hatch lines.
* @param eyepos
* Specifies the view eye position.
* @param target
* Specifies the view target position.
* @param persp
* Indicates the logical for perspective view.
* @param nHatchLines
* Returns the number of visible hatch lines.
* @param hatchLinePos
* Returns list of visible hatch line positions.
* @param phlv5_opts
* Specifies PHL V5 options.
* @param ao
* Specifies ACIS options.
 */
DECL_PHLV5 outcome api_create_hatch_lines(	FACE*				  in_face, 
											const SPAunit_vector& hatchNormal, 
											const double&		spacing, 
											const SPAposition&	hatch_start_point, 
				   							ENTITY_LIST&		bodies, 
											SPAposition const&  eyepos,  
											SPAposition const&  target, 
											const logical&      persp,  
											int&                nHatchLines,
											SPAposition*&       hatchLinePos,
											phlv5_options*		phlv5_opts = NULL,
											AcisOptions*		ao = NULL);

/**
 * Defines a hlr_view.
 * <br>
 * <b>Role:</b> The <tt>hlr_view</tt> class acts as holder of single view definition
 * for computation of hidden line data. This is input to API <tt>api_multi_view_hlr_compute</tt> when hidden line data
 * computation of multiple views is required for the same input models.
 * <br><br>
 * <i><b>Note</b> All data stored in <tt>m_out_phlv5_edges</tt> is allocated with</i> <tt>new</tt>.<i>It is the user's responsibility
 * to call</i> <tt>lose</tt> <i>for all the entities in the list when they are no longer needed.</i>
 * <br><br>
 * @see SPAposition,ENTITY_LIST
 */
struct DECL_PHLV5 hlr_view : public ACIS_OBJECT
{
	SPAposition m_eye;
	SPAposition m_target;
	bool m_persp;
	ENTITY_LIST* m_out_phlv5_edges = nullptr;

/**
 * @param iEye
 * SPAposition of the view eye position.
 * @param iTarget
 * SPAposition of the view target position.
 * @param iPersp
 * boolean if the view is perspective.
 * @param iEdges
 * ENTITY_LIST which would be populated with the output <tt>PHLV5_EDGE</tt>s for this view definition.
 */
	hlr_view(SPAposition const& iEye, SPAposition const& iTarget, bool iPersp, ENTITY_LIST& iEdges);

	~hlr_view();
};

/**
 * A handle to the input hlr data.
 * <br>
 * <b>Role:</b> The <tt>hlr_input_handle</tt> class acts as a handle to input hlr data consumed by multi-API's individual
 * stages for computation of hidden line data. This will own the input asm_model / bodies and that would be deleted when this
 * handle is cleaned up using <tt>api_cleanup_hlr_input_handle</tt>.
 * <br><br>
 * <i><b>Note</b> This owns <tt>asm_model</tt> / <tt>BODY</tt>s used for computing hidden line data. It is the user's responsibility
 * to call</i> <tt>api_cleanup_hlr_input_handle</tt> <i>for cleaning up the input handle when they are no longer needed.</i>
 * <br><br>
 * @see api_create_hlr_input_handle, api_add_asm_model_to_hlr_handle, api_add_bodies_to_hlr_handle, api_compute_hlr_view, api_cleanup_hlr_input_handle
 */
class DECL_PHLV5 hlr_input_handle : public ACIS_OBJECT
{
public:

	virtual ~hlr_input_handle() = 0;
};

/**
 * Constructs <tt>hlr_input_handle</tt> consumed by multi-API individual stages for computation of hidden line data.
 * <br><br>
 * <b>Role:</b> Constructs <tt>hlr_input_handle</tt> which would maintain the input required for computing hidden line data. 
 * <br><br>
 * The options argument is of type <tt>phlv5_options</tt> and contains options for the
 * hidden line removal algorithm.
 * <br><br>
 * <b>Errors:</b> 
 * <br><br>
 * <b>Effect:</b>
 * <br><br>
 * <b>Journal: </b> Not Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
 * @param ioHandle
 * <tt>hlr_input_handle</tt> handle for maintaining inputs of hidden line data computation.
 * @param iPhlv5Opts
 * option class.
 * @param iAo
 * acis options.
 * <br><br>
 * @see api_add_asm_model_to_hlr_handle, api_add_bodies_to_hlr_handle, api_compute_hlr_view, api_cleanup_hlr_input_handle
 **/
outcome DECL_PHLV5 api_create_hlr_input_handle(hlr_input_handle*& ioHandle, phlv5_options* iOpts = nullptr, AcisOptions* iAo = nullptr);

/**
 * Adds <tt>asm_model</tt> to <tt>hlr_input_handle</tt> for computation of hidden line data.
 * <br><br>
 * <b>Role:</b> The input <tt>asm_modle</tt> will be owned by <tt>hlr_input_handle</tt>. This would be deleted when this
 * handle is cleaned up using <tt>api_cleanup_hlr_input_handle</tt>. This API should not be used along with <tt>api_add_bodies_to_hlr_handle</tt>,
 * both of them should be used in a mutually exclusive manner else the API would raise an error of mixed input.
 * <br><br>
 * <b>Errors:</b>
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Not Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
 * @param iHandle
 * <tt>hlr_input_handle</tt> handle for maintaining inputs of hidden line data computation.
 * @param iModel
 * <tt>asm_model</tt> whose hidden line data needs to be calculated.
 * @param iAo
 * acis options.
 * <br><br>
 * @see api_create_hlr_input_handle, api_add_bodies_to_hlr_handle, api_compute_hlr_view, api_cleanup_hlr_input_handle
 **/
outcome DECL_PHLV5 api_add_asm_model_to_hlr_handle(hlr_input_handle* iHandle, asm_model* iModel, AcisOptions* iAo = nullptr);

/**
 * Adds <tt>ENTITY_LIST</tt> of <tt>BODY</tt>s to <tt>hlr_input_handle</tt> for computation of hidden line data.
 * <br><br>
 * <b>Role:</b> The input list of <tt>BODY</tt>s will be owned by <tt>hlr_input_handle</tt>. This would be deleted when this
 * handle is cleaned up using <tt>api_cleanup_hlr_input_handle</tt>. This API should not be used along with <tt>api_add_asm_model_to_hlr_handle</tt>,
 * both of them should be used in a mutually exclusive manner else the API would raise an error of mixed input.
 * <br><br>
 * <b>Errors:</b>
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Not Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
 * @param iHandle
 * <tt>hlr_input_handle</tt> handle for maintaining inputs of hidden line data computation.
 * @param iBodies
 * List of <tt>BODY</tt>s whose hidden line data needs to be calculated.
 * @param iAo
 * acis options.
 * <br><br>
 * @see api_create_hlr_input_handle, api_add_asm_model_to_hlr_handle, api_compute_hlr_view, api_cleanup_hlr_input_handle
 **/
outcome DECL_PHLV5 api_add_bodies_to_hlr_handle(hlr_input_handle* iHandle, ENTITY_LIST& iBodies, AcisOptions* iAo = nullptr);

/**
 * Computes hidden line data for input data provided by <tt>hlr_input_handle</tt>.
 * <br><br>
 * <b>Role:</b> Computes hidden line data for input data provided by <tt>hlr_input_handle</tt> for the view definition provided
 * by <tt>hlr_view</tt> object. The output list of <tt>PHLV5_EDGE</tt>s would be populated in <tt>hlr_view</tt> object. 
 * It is the user's responsibility to call <tt>lose</tt> for all the output entities in the list when they are no longer needed.
 * <br><br>
 * <b>Errors:</b>
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Not Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
 * @ioView
 * <tt>hlr_view</tt> object for input view definition for computing hidden line data and storing the output list of <tt>PHLV5_EDGE</tt>s.
 * @param iHandle
 * <tt>hlr_input_handle</tt> handle for maintaining inputs of hidden line data computation.
 * @param iAo
 * acis options.
 * <br><br>
 * @see api_create_hlr_input_handle, api_add_asm_model_to_hlr_handle, api_add_bodies_to_hlr_handle, api_cleanup_hlr_input_handle
 **/
outcome DECL_PHLV5 api_compute_hlr_view(hlr_view* ioView, hlr_input_handle* iHandle, AcisOptions* iAo = nullptr);

/**
 * Cleans up <tt>hlr_input_handle</tt>.
 * <br><br>
 * <b>Role:</b> This will clean up memory of <tt>hlr_input_handle</tt>. This will also delete / lose the <tt>asm_model</tt> or list of <tt>BODY</tt>s 
 * owned by the input handle which was used for generating hidden line data.
 * <br><br>
 * <b>Errors:</b>
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Not Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS PHL V5
 * <br><br>
 * @param iHandle
 * <tt>hlr_input_handle</tt> handle whose memory needs to be cleaned.
 * @param iAo
 * acis options.
 * <br><br>
 * @see api_create_hlr_input_handle, api_add_asm_model_to_hlr_handle, api_add_bodies_to_hlr_handle, api_compute_hlr_view
 **/
outcome DECL_PHLV5 api_cleanup_hlr_input_handle(hlr_input_handle*& iHandle, AcisOptions* iAo = nullptr);

/** @} */
#endif
