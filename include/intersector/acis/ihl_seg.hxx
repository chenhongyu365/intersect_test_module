/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
/**********************************************************************/
/* Defines a line segment with visibility information.                */
/**********************************************************************/
#if ! defined ( IHL_SEG_INCLUDE )
/**********************************************************************/
#include "en_ihl.hxx"
/**
* @file ihl_seg.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 *! \addtogroup IHLAPI
 *  \brief Declared at <ihl_seg.hxx>
 *  @{
 */

/**********************************************************************/
/**
 * @nodoc
 */
ENTITY_IS_PROTOTYPE(IHL_SEGMENT, IHL )
#if 0
; // semicolon needed for mkman (doc tool) parsing
#endif
extern DECL_IHL int IHL_SEGMENT_TYPE;
/**
 * Identifier that gives number of levels of derivation of this class
 * from ENTITY.
 */
#define IHL_SEGMENT_LEVEL (ENTITY_LEVEL + 2)
/**********************************************************************/
/**
 * Defines a hidden line segment with visibility information.
 * <br>
 * <b>Role:</b> This class specifies a hidden line segment generated by IHL.
 * <br><br>
 * The various start and end methods can be called to obtain the start and end points of the
 * segment in 2D or 3D coordinates.
 * <br><br>
 * The <tt>visible</tt> method can be called to determine if the segment is visible.
 * <br><br>
 * The <tt>on_edge</tt> method can be called to determine if the segment lies on a model edge.
 * <br><br>
 * The <tt>model_ent</tt> method can be called to determine the owning model entity.
 * @see ENTITY
 */
class DECL_IHL IHL_SEGMENT : public ENTITY_IHL
{
private :
    double       x1,            // x-coordinate of start point
                 y1,            // y-coordinate of start point
                 x2,            // x-coordinate of end point
                 y2;            // y-coordinate of end point
    double       tx_1,            // x-coordinate of start point
                 ty_1,            // y-coordinate of start point
                 tz_1,            // y-coordinate of start point
                 tx_2,            // x-coordinate of end point
                 ty_2,            // z-coordinate of end point
                 tz_2;            // z-coordinate of end point
    double       u1,            // u_par of start point
                 v1,            // v_par of start point
                 u2,            // u_par of end point
                 v2;            // v_par of end point
    double       t1,             //edge t-par if on edge of start point
    			 t2;             //edge t-par if on edge of end point
    double		 tpar; 			  //tpar from begin to end point for silh
	IHL_SEGMENT  *pPrevious ;
	IHL_SEGMENT  *pNext ;
    ENTITY       *owner;        // relates line segment to model entity
    unsigned int fVisible : 2,  // TRUE if visible
                 fOnEdge  : 2,  // TRUE if on model edge
                 fOnSil  : 2;  // TRUE if on silhouette edge

public :
/**
 * C++ allocation constructor requests memory for this object but does not populate it.
 * <br><br>
 * <b>Role:</b> The allocation constructor is used primarily by restore. Applications should
 * call this constructor only with the overloaded <tt>new</tt> operator, because this reserves the memory
 * on the heap, a requirement to support roll back and history management.
 */
    IHL_SEGMENT() {}
/**
 * C++ copy constructor requests memory for this object and populates it with the data from the object supplied as an argument.
 * <br><br>
 * <b>Role:</b> Applications should call this constructor only with the overloaded <tt>new</tt> operator,
 * because this reserves the memory on the heap, a requirement to support roll back and history
 * management.
 * <br><br>
 * @param to_cpy
 * IHL_SEGMENT to copy.
 */
    IHL_SEGMENT(
        IHL_SEGMENT& to_cpy);
/**
 * C++ initialize constructor requests memory for this object and populates it with the data supplied as arguments.
 * <br><br>
 * <b>Role:</b> Applications should call this constructor only with the overloaded <tt>new</tt> operator,
 * because this reserves the memory on the heap, a requirement to support roll back and history
 * management.
 * <br><br>
 * @param seg
 * array of 4 doubles with start/end coordinates.
 * @param lseg
 * array of 4 doubles with start/end coordinates.
 * @param lseguv
 * array of 4 doubles with start/end uv-coordinates.
 * @param lsegt
 * array of 2 doubles with start/end tpars.
 * @param ent
 * model entity.
 * @param vis
 * visibility flag.
 * @param seg_tpar
 * tpar from begin to end of segment(silh point).
 * @param onsil
 * if segment on silhouette edge.
 */
    IHL_SEGMENT(
        double *seg,   // array of 4 doubles with start/end coordinates
        double *lseg,   // array of 4 doubles with start/end coordinates
        double *lseguv,   // array of 4 doubles with start/end uv coordinates
        double *lsegt,   // array of 2 doubles with start/end edge tpar
        ENTITY *ent,   // model entity
        int    vis,   // visibility flag
        double seg_tpar,// tpar from begin to end for silh point
        logical onsil);  // if segment on silhouette edge
/**
 * @nodoc
 */
	IHL_SEGMENT& operator=(IHL_SEGMENT const& old);
/**
 * Returns a pointer to the previous <tt>IHL_SEGMENT</tt>.
 */
    IHL_SEGMENT * previous() const { return(pPrevious); }

    // Returns next IHL_SEGMENT in a list
/**
 * Returns a pointer to the next <tt>IHL_SEGMENT</tt>.
 */
    IHL_SEGMENT * next() const { return(pNext); }

    // Sets prevoius IHL_SEGMENT pointer
/**
 * Sets previous <tt>IHL_SEGMENT</tt> pointer.
 * <br><br>
 * @param prev
 * pointer to segment.
 */
    void set_previous(IHL_SEGMENT *prev) { pPrevious = prev; }

    // Sets next IHL_SEGMENT pointer
/**
 * Sets next <tt>IHL_SEGMENT</tt> pointer.
 * <br><br>
 * @param next
 * pointer to segment.
 */
    void set_next(IHL_SEGMENT *next) { pNext = next; }

    // Inquiry functions

    // Returns TRUE if visible
/**
 * Returns <tt>TRUE</tt> if the segment is visible.
 */
    logical visible() const { return(fVisible); }

    // Returns TRUE if on model edge
/**
 * Returns <tt>TRUE</tt> if the segment is on a model edge.
 */
    logical on_edge() const { return(fOnEdge); }
    // Returns TRUE if on silh edge
/**
 * Returns <tt>TRUE</tt> if the segment is on a silhouette edge.
 */
    logical on_sil() const { return(fOnSil); }

    // Returns tpar of segment which denotes silh point
/**
 * Returns t-parameter of segment which denotes the silhouette point.
 */
    double get_tpar() const { return(tpar); }

    // Returns pointer to related model entity
/**
 * Returns a pointer to the related model entity.
 */
    ENTITY * model_ent() const { return(owner); }

    // Returns x & y -coordinates of start point and end point
/**
 * Returns 2D <i>x</i>-coordinate of the start point.
 */
    double x_start() const { return(x1); }
/**
 * Returns 2D <i>y</i>-coordinate of the start point.
 */
    double y_start() const { return(y1); }
/**
 * Returns 2D <i>x</i>-coordinate of the end point.
 */
    double x_end() const { return(x2); }
/**
 * Returns 2D <i>y</i>-coordinate of the end point.
 */
    double y_end() const { return(y2); }
    // Returns x y and z-3Dcoordinate of start point
/**
 * Returns 3D <i>x</i>-coordinate of the start point.
 */
    double x3_start() const { return(tx_1); }
/**
 * Returns 3D <i>y</i>-coordinate of the start point.
 */
    double y3_start() const { return(ty_1); }
/**
 * Returns 3D <i>z</i>-coordinate of the start point.
 */
    double z3_start() const { return(tz_1); }
    // Returns x y and z-coordinate of end point
/**
 * Returns 3D <i>x</i>-coordinate of the end point.
 */
    double x3_end() const { return(tx_2); }
/**
 * Returns 3D <i>y</i>-coordinate of the end point.
 */
    double y3_end() const { return(ty_2); }
/**
 * Returns 3D <i>z</i>-coordinate of the end point.
 */
    double z3_end() const { return(tz_2); }
/**
 * Returns segment start point.
 */
    double u_start() const { return(u1); }
/**
 * Returns segment start point.
 */
    double v_start() const { return(v1); }
/**
 * Returns t-parameter edge start point.
 */
    double t_start() const { return(t1); }
/**
 * Returns segment end point.
 */
    double u_end() const { return(u2); }
/**
 * Returns segment end point.
 */
    double v_end() const { return(v2); }
/**
 * Returns t-parameter edge end point.
 */
    double t_end() const { return(t2); }




    // Returns segment coordinates for update
/**
 * Returns 2D segment coordinates for update.
 */
    double * coords() { return(&x1); }
/**
 * Returns 3D segment coordinates for update.
 */
    double * coords3() { return(&tx_1); }
/**
 * Returns segment coordinates for update.
 */
    double * uvcoords() { return(&u1); }
/**
 * Returns t-parameter edge coordinates for update.
 */
    double * tpars() { return(&t1); }

    // Returns segment coordinates read only
/**
 * Returns 2D segment coordinates read only.
 */
    const double * coords() const { return(&x1); }
    // Returns segment coordinates read only
/**
 * Returns 3D segment coordinates read only.
 */
    const double * coords3() const { return(&tx_1); }
    // Returns segment coordinates read only
/**
 * Returns segment coordinates read only.
 */
    const double * uvcoords() const { return(&u1); }
    // Returns segment edge tpars read only
/**
 * Returns t-parameter edge coordinates and this is read only.
 */
    const double * tpars() const { return(&t1); }

    // Include the standard member functions for all entities.
    /**
     * @nodoc
     */
    ENTITY_FUNCTIONS( IHL_SEGMENT, IHL )
#if 0
; // semicolon needed for mkman (doc tool) parsing)
#endif
// Because mkman isn't aware that ENTITY_FUNCTIONS changes access to "public", do so
// explicitly here:
public:

};

/**********************************************************************/
#define IHL_SEG_INCLUDE
/* @} */
#endif
/**********************************************************************/
