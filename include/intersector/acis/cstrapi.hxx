/* ORIGINAL: acis2.1/kernapi/api/kernapi.hxx */
/* $Id: cstrapi.hxx,v 1.62 2002/08/09 17:21:36 jeff Exp $ */
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

/*******************************************************************/
// apc 18/09/02 Add overloaded api_body_mass_pr prototype without
//              projection plane
/*******************************************************************/

// Header for api routines.

// For details of how to call each routine, consult the documentation
// for individual routines.


#if !defined( CSTRAPI_HXX )
#define CSTRAPI_HXX
/**
 * \defgroup CSTRSYSTEMAPI System
 * \defgroup CSTRMAKEAPI Construct Entities
 * \defgroup CSTRMAKEBODYAPI Construct Bodies
 * \defgroup CSTRMAKEWBODYAPI Construct Wire Bodies
 * \defgroup CSTRMAKEFACEAPI Construct Faces
 * \defgroup CSTRMAKEEDGEAPI Construct Edges
 * \defgroup CSTRMAKEOTHERAPI Construct Other Entities
 * \defgroup CSTRMAKEMODIFYAPI Construct or Modify Entities
 * \defgroup CSTRMODIFYAPI Modify Entities
 * \defgroup CSTROTHERSAPI Others
 */
/**
 * @file cstrapi.hxx
 * @CAA2Level L1
 * @CAA2Usage U1
 * \defgroup CSTRAPI Constructors APIs
 *
 * @{
 */
class BODY;
class WIRE;
class SHELL;
class FACE;
class LOOP;
class EDGE;
class COEDGE;
class VERTEX;
class ENTITY;
class ENTITY_LIST;
class APOINT;

class SPAinterval;
class curve;
class plane;
class SPAposition;
class spline;
class surface;
class tensor;
class SPAunit_vector;
class SPAvector;
class curve_curve_int;
class SPAtransf;
class law;

class TEXT_ENT;
class entity_with_ray;
class splsurf;
class splgrid;
class SPAposition_vector;
class straight;

class make_wire_options; // An options object for future expansion.
class segmentation_options;

#include "acis.hxx"
#include "dcl_cstr.h"
#include "api.hxx"
#include "queryapi.hxx"
#include "logical.h"
#include "mk_ewires_opts.hxx"
#include "SPA_edge_line_arc_options.hxx"
#include "formatted_text.hxx"
#include "points_segment_hndl.hxx"
#include "spa_null_kern.hxx"

/**
 * Specifies the direction of an entity as forward or reversed, relative to the direction of some underlying entity.
 * <br>
 * <b>Role:</b> Sense is a relative direction of one entity with respect to another 
 * entity. If the directions are the same, the sense is said to be <i>forward</i>. If the
 * directions are opposite, the sense is said to be <i>reversed</i>. Sense applies to face normals with respect to
 * their underlying %surface normals, coedges with respect to their underlying edges, edges with respect to their
 * underlying curves, etc.
 * <br><br>
 * For example, the normal to a face can be either the same direction as the normal of the
 * underlying %surface at any position, or it can be the reverse of the %surface normal. If it is
 * the same as the %surface normal, the face's sense relative to the %surface normal is forward;
 * otherwise, its sense is reversed.
 * <br>
 * <ul>
 * <li>A value of <tt>TRUE</tt> (or <tt>REVERSED</tt>) means the directions are opposite (reversed).</li>
 * <li>A value of <tt>FALSE</tt> (or <tt>FORWARD</tt>) means the directions are the same.</li>
 * </ul>
 */
typedef logical REVBIT;

#include "bs3curve.hxx"
#include "bl_enum.hxx"
#include "bs2curve.hxx"
#include "bs3surf.hxx"

// Some compilers insists on full knowledge of a class before
// it will accept an array of them, even as a function argument.

#if defined( ultrix ) || defined( osf1 ) || defined( vms ) || defined( mac )
#include "position.hxx"
#include "unitvec.hxx"
#endif



/*! \addtogroup CSTRSYSTEMAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */
/**
* Initializes the constructor library.
* <br><br>
* <b>Effect:</b> System routine
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
**/
DECL_CSTR outcome api_initialize_constructors();
/**
* Terminates the constructor library.
* <br><br>
* <b>Effect:</b> System routine
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
**/

DECL_CSTR outcome api_terminate_constructors();
/*! @} */

/*! \addtogroup CSTRMAKEAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */

/*! \addtogroup CSTRMAKEBODYAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */

//============================================================
// Solid creation

/**
* Creates an empty body.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* empty body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_body(
			BODY*& body,                 // Returns empty body as output
			AcisOptions* ao = NULL
	);

/**
* Creates cuboid of given width (<i>x</i>), depth (<i>y</i>) and height (<i>z</i>).
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i> <br><br>
* <b>Role:</b> This API function constructs a cuboid centered at the origin. All
* arguments must be greater than <tt>SPAresabs</tt>.
* <br><br>
* <b>Errors:</b> Width, depth, or height not greater than <tt>SPAresabs</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param x
* size in x coordinate direction.
* @param y
* size in y coordinate direction.
* @param z
* size in z coordinate direction.
* @param body
* cuboid returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_cuboid(
			double x,				// size in x coordinate direction
			double y,				// size in y coordinate direction
			double z,				// size in z coordinate direction
			BODY*& body,			// body constructed
			AcisOptions* ao = NULL
	);

/**
 * @brief   		根据更定的 x y z 方向上的长度创建立方体 cuboid.
 * @param[in]    	x x坐标长度
 * @param[in]  	    y y坐标长度
 * @param[in]    	z z坐标长度
 * @param[out]  	body 返回 cuboid
 * @param[in]  	    ao ACIS 选项
 * @details
 *          y
 *          |
 *      4---8---5
 *     /|      9|
 *   11 4     / 5
 *   7---10--6  |
 *   |  0---0|--1   --x
 *   7 /     6 1
 *   |3      |/
 *   3---2---2
 *       /
 *      z
 * 处理情况1: 参数合法性检查（调用check系列函数）
 * 处理情况2: 若输入参数z为0，则创建双侧面sheet body
 * 处理情况3: 若输入参数z大于0，则创建solid body
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_make_cuboid(double x,     // size in x coordinate direction
                                      double y,     // size in y coordinate direction
                                      double z,     // size in z coordinate direction
                                      BODY*& body,  // body constructed
                                      AcisOptions* ao = NULL);

/**
 * @brief   		根据更定的 x y z 方向上的长度创建立方体 cuboid.
 * @param[in]    	x x坐标长度
 * @param[in]  	    y y坐标长度
 * @param[in]    	z z坐标长度
 * @param[out]  	body 返回 cuboid
 * @param[in]  	    ao ACIS 选项
 * @details
 *          z
 *          |
 *      4---8---5
 *     /|      9|
 *   11 4     / 5
 *   7---10--6  |
 *   |  0---0|--1   --y
 *   7 /     6 1
 *   |3      |/
 *   3---2---2
 *       /
 *      x
 *
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_1_api_make_cuboid(double x,     // size in x coordinate direction
                                      double y,     // size in y coordinate direction
                                      double z,     // size in z coordinate direction
                                      BODY*& body,  // body constructed
                                      AcisOptions* ao = NULL);
/**
* Creates a solid block given two positions on a diagonal of the block. 
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid <tt>block</tt> aligned with the current WCS with
* corners at the specified points (<tt>pt1</tt> and <tt>pt2</tt>). The edges of the block are
* parallel to the axes of the active WCS. If the <i>Z</i>-coordinates are equal, a sheet body 
* will be created in the <i>XY</i> %plane.
* <br><br>
* <b>Errors:</b> Two given positions are identical. <i>X</i>- and/or <i>Y</i>-coordinates of the two points
* are equal (only <i>Z</i>-coordinates may be equal).
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pt1
* first position.
* @param pt2
* position diagonally opposite pt1.
* @param block
* block returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_solid_block(
		const SPAposition& pt1,  // first position
		const SPAposition& pt2,  // positional diagonally opposite pt1
		BODY*& block,            // block created
		AcisOptions* ao = NULL
	);

/**
 * @brief   		给定两个对角位置，创建一个实心方块(solid block)
 * @param[in]    	pt1 第一个点的位置
 * @param[in]  	    pt2 第二个点的位置（位于pt1的对角）
 * @param[out]  	block 返回 solid block
 * @param[in]  	    ao ACIS 选项
 * @details			传入一个块对角线上的两个位置，创建一个实心块。实心块的边和坐标轴是轴对齐的，若两点的x或者y坐标相同则抛出异常；若z坐标相等则创建一个实体面片
 *					处理情况1：参数容差检查（调用check系列函数）
 *					处理情况2：z坐标相等时，创建一个实体面片
 *					处理情况3：其他情况均正常，创建一个长方形实体块
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_solid_block(
		const SPAposition& pt1,			// 对角位置1
		const SPAposition& pt2,			// 对角位置2
		BODY*& block,					// 构建的BODY指针
		AcisOptions* ao = (AcisOptions*)0
	);

/**
 * @brief   		给定两个对角顶点坐标，创建一个立方体
 * @param[in]    	pt1 第一个顶点的位置
 * @param[in]  	    pt2 pt1的对角顶点
 * @param[out]  	block 返回的立方体
 * @param[in]  	    ao ACIS 选项
 * @details			传入一个立方体上的两个对角顶点位置，创建一个立方体。立方体的边和坐标轴是轴对齐的，若两点的x或者y坐标相同则抛出异常；若z坐标相等则创建一个实体面片
 *					处理情况1：两点的x或者y坐标相同，抛出异常
 *					处理情况2：z坐标相等时，创建一个实体面片
 *					处理情况3：其他情况均正常，创建一个长方形实体块
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_1_api_solid_block(
		const SPAposition& pt1,  // first position
		const SPAposition& pt2,  // positional diagonally opposite pt1
		BODY*& block,            // block created
		AcisOptions* ao = NULL
	);
/**
* Creates a sphere of given radius, centered at the origin.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid sphere centered at the origin. The North Pole is parallel to the 
* <i>z</i>-axis and corresponds to 90 degrees latitude. The Prime Meridian (or line of zero degree longitude) point 
* on the Equator is parallel to <i>x</i>-axis. 
* <br><br>
* Refer to the <i>[Sphere](http://doc.spatial.com/articles/s/p/h/Sphere.html)</i> 
* Technical Article for illustrations and more information.
* <br><br>
* <b>Errors:</b> Radius not greater than <tt>SPAresabs</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param radius
* radius of desired sphere.
* @param sph
* sphere returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_sphere(
			double radius,				// radius of sphere
			BODY*& sph,					// body constructed
			AcisOptions* ao = NULL
	);

/**
 * @brief   	  创建一个实心球体
 * @param[in]	  radius 球体半径
 * @param[out]	  sph 输出创建的球体
 * @param[in]  	  ao ACIS 选项
 * @details       以原点为中心根据给定的半径构造一个实心球体，返回球体指针，测试球体半径为正数，大于零小于容差，负数三种情况
 *				处理情况1：检查输入半径的合法性（调用check函数）
 *				处理情况2：根据给定半径创建球体
 * @note		  radius 不能小于0
 * @return        函数执行结果
 */
DECL_CSTR outcome gme_api_make_sphere(double radius,			// 球半径
									  BODY*& sph,			//输出生成的球体 sph
                                      AcisOptions* ao = NULL);
/**
* @brief    创建一个实心球体
* @param[in]   radius 球体半径
* @param[out]   sph 输出创建的球体
* @param[in]    ao ACIS 选项
* @details       以原点为中心根据给定的半径构造一个实心球体，返回球体指针，测试球体半径为正数，大于零小于容差，负数三种情况
*				处理情况1：检查输入半径的合法性（调用check函数）
*				处理情况2：根据给定半径创建球体
* @note     radius 不能小于0
* @return 函数执行结果
*/
DECL_CSTR outcome gme_1_api_make_sphere(double radius,      // 球半径
                                        BODY*& sph,       // 生成的球体
                                        AcisOptions* ao = NULL);
/**
 * @brief   	  创建一个给定半径、以原点为中心的球体
 * @param[in]	  radius 球体半径
 * @param[out]	  sph    构建的球体
 * @param[in]  	  ao ACIS 选项
 * @details       北极与z轴平行，对应90度纬度。赤道上零度经线上的点与x轴平行测试球体半径为正数，容差附近的半径，负数半径
 *				  处理情况1：对输入的半径进行合法性检查
 *				  处理情况2：根据给定半径创建球体
 * @note		  radius 不能小于SPAreabs
 * @return        执行结果
 */
DECL_CSTR outcome gme_api_2_make_sphere(double radius,			// 球半径
									  BODY*& sph,			//输出生成的球体 sph
                                      AcisOptions* ao = NULL);

/**
* Creates a solid sphere given the center position and radius.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid sphere centered at the given position. The North Pole is parallel to the 
* <i>z</i>-axis and corresponds to 90 degrees latitude. The Prime Meridian (or line of zero degree longitude) point 
* on the Equator is parallel to <i>x</i>-axis. 
* <br><br>
* Refer to the <i>[Sphere](http://doc.spatial.com/articles/s/p/h/Sphere.html)</i> 
* Technical Article for illustrations and more information.
* <br><br>
* To make a spherical face, the API @href api_face_sphere is recommended.  
* To make a partial spherical face, the API @href api_make_spface is recommended. 
* <br><br>
* <b>Errors:</b> Radius is zero.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center position of the sphere.
* @param radius
* radius of the sphere.
* @param sph
* sphere returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_solid_sphere(
		const SPAposition& center, // center of sphere
		double radius,             // radius of sphere
		BODY*& sph,                // sphere created
		AcisOptions* ao = NULL
	);


/**
 * @brief   		创建一个给定中心位置和半径的实心球体
 * @param[in]    	center 球体的中心位置
 * @param[in]           radius 球体的半径
 * @param[out]  	sph 创建球体的指针
 * @param[in]           ao ACIS选项
 * @details                根据提供的参数生成球体，创建一个具有给定中心和半径的实心球体，返回球体的指针，球体半径为正数、零、负数三种测试情况
 			处理情况1 对输入半径合法性检查
			处理情况2 根据半径创建球体
			处理情况3 根据位置对球体进行位移
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_solid_sphere(
		const SPAposition& center, // center of sphere
		double radius,             // radius of sphere
		BODY*& sph,                // sphere created
		AcisOptions* ao = NULL
	);

/**
 * @brief   		给定中心位置和半径创建一个实心球体。
 * @param[in]    	center 球心位置
 * @param[in]       radius 球体的半径
 * @param[out]  	sph 创建出的球体的指针
 * @param[in]       ao ACIS选项
 * @details         该API函数创建一个以给定位置为中心的实心球体。北极与z轴平行，对应于 90 度纬度。赤道平行于x轴。
					处理情况1 输入半径为0;
					处理情况2 输入半径为负;
					处理情况3 输入半径小于容差SPAresabs;
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_2_api_solid_sphere(
		const SPAposition& center, // center of sphere
		double radius,             // radius of sphere
		BODY*& sph,                // sphere created
		AcisOptions* ao = NULL
	);

/**
 * @brief			输入圆心和半径，生成球体
 * @param[in]       center  球心的坐标
 * @param[in]       radius  球体半径
 * @param[out]      sph		返回的球体对象
 * @param[in]		ao		ACIS选项
 * @details			center 参数用于传入球心的三维坐标信息，radius 参数用于传入球体的半径信息。
 *					若传入的球体半径小于或者等于零，则抛出异常；若无异常抛出，则创建带有
 *					transform 的 sphere BODY，并将其保存在 sph 中。参数合法性检查（调用 check_pos_length 函数）,
 *					根据 radius 创建一个原点位于圆心的球体
 *					根据 center 对球体进行偏移
 *					* 已测试：
 *					case1 输入的球心坐标为（10，10，10），半径长度为正数
 *					case2 输入的球心坐标为（10，10，10），半径长度为零
 *					case3 输入的球心坐标为（10，10，10），半径长度为负数
 *					case4 输入的球心坐标为（10，10，10），半径长度为容差的1/2
 *					case5 输入的球心坐标随机，半径为1
 *					case6 输入的球心坐标包含负坐标，半径为正数
 *					case7 输入的球心坐标极小，半径为极小值
 *					case8 输入的球心坐标为（10，10，10），半径为 double 类型的最小正数
 *					case9 输入的球心坐标为（10，10，10），半径为 double 类型的最大正数
 *					case10 输入的球心坐标为（10，10，10），半径为无穷大 (INF)
 *					待测试：
 *					case11 输入的球心坐标为（10，10，10），半径不是数(NaN)
 * @exception		acis_exception(INVALID_RADIUS) 当传入的球体半径小于或等于零时抛出异常
 * @return  		outcome 输出结果，表示函数执行的成功或失败状态
 */
DECL_CSTR outcome gme_4_api_solid_sphere(
		const SPAposition& center, // center of sphere
		double radius,             // radius of sphere
		BODY*& sph,                // sphere created
		AcisOptions* ao = NULL
	);

/**
* Creates an elliptical cone or cylinder of given height and radii.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Centers the frustum at the origin, with main axis along the <i>z</i>-axis and one axis
* (major or minor) of its cross-section in the <i>z</i> = 0 %plane along the <i>x</i>-axis.
* <br><br>
* All arguments must be greater than <tt>SPAresabs</tt>.
* To make a conical face, the API @href api_face_conic is recommended.  
* To make a partial conical face, the API @href api_make_cnface is recommended. 
* <br><br>
* <b>Errors:</b> Either <tt>height</tt>, <tt>radius1</tt>, or <tt>radius2</tt> is not greater than <tt>SPAresabs</tt>, 
* or <tt>top</tt> is not greater than or equal to 0.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param height
* height.
* @param radius1
* radius in x-direction at base.
* @param radius2
* radius in y-direction at base.
* @param top
* radius in x-direction at top.
* @param frust
* frustum returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_frustum(
			double height,				// height of frustum
			double radius1,				// major radius of base
			double radius2,				// minor radius of base
			double top,					// major radius of top
			BODY*& frust,				// body constructed
			AcisOptions* ao = NULL
	);

/**
 * @brief   构造frustum
 * @param[in]	height 椭圆台的高
 * @param[in]	radius1 z=0平面处，椭圆Ox方向对应半轴的长度
 * @param[in]	radius2 z=0平面处，椭圆Oy方向对应半轴的长度
 * @param[in]	top z=height平面处，椭圆Ox方向对应半轴的长度
 * @param[out]	frust 输出生成的体
 * @param[in]	ao ACIS属性
 * @details
 *				根据给定的参数构造一个椭圆台.
 *				椭圆台的底面和顶面都是椭圆. 底面椭圆的两轴分别为radius1和radius2(没有规定谁大谁小), 
 *				其中radius1长度的轴和Ox方向平行.
 *				顶面椭圆和Ox平行的那一轴长度为top.
 *
 *                          z
 *                          |
 *                          |(0,0,height/2)     (0,radius2,height/2)
 *                          .- - - - - - - - - .
 *                         /|
 *                        / |
 *                      2(top,0,height/2)
 *                          |
 *                          |
 *                          |
 *                          |
 *                          |                                     (0,radius2,-height/2)
 *                          O- - - - - - - - - - - - - - - - - - .---------y
 *                         /
 *                        /
 *                       /
 *                      /
 *                     1(radius1,0,-height/2)
 *                    /
 *                   /
 *                  x
 * 				对于构造出来的BODY而言, 它只有一个LUMP, LUMP有一个SHELL.
 * 				SHELL有三个面, 面的顺序是侧面->底面->顶面
 * 				侧面是圆锥面, 它的LOOP的顺序是底面环->顶面环
 * 				底面位于z=-height/2, 顶面位于z=height/2
 * @note		当top==0时，退化成圆锥。
            	当-SPAresabs<=top<=k*SPAresabs并且top!=0时，会构造出一个有错误的圆台（顶面椭圆面积小于容差，或者说“为零”）。可能会因此引发一些惊喜的结果。
 * @return 		函数执行结果
 */
DECL_CSTR outcome gme_api_make_frustum(double height, double radius1, double radius2, double top, BODY*& frust, AcisOptions* ao = NULL);

/**
 * @brief           根据给定的 高 和 椭圆台半轴长 创建椭圆台 frustum
 * @param[in]       height    椭圆台的高
 * @param[in]       radius1   椭圆台底部Ox方向的半轴长度
 * @param[in]       radius2   椭圆台底部Oy方向的半轴长度
 * @param[in]       top       椭圆台顶部Ox方向的半轴长度
 * @param[out]      frust     输出生成的体
 * @param[in]       ao        ACIS属性
 *
 * @details         椭圆台主轴沿z轴
 *                  底面位于 z=-height/2, 顶面位于 z=height/2
 *                  top=0 的时候，椭圆台会退化为圆锥
 * @note 			top 不能小于0
 *					height、radius1、radius2 不能小于等于0
 * @return          函数执行结果
 */
DECL_CSTR outcome gme_1_api_make_frustum(double height,   // height of frustum
                                         double radius1,  // radius of base in x coordinate
                                         double radius2,  // radius of base in y coordinate
                                         double top,      // radius of top in x coordinate
                                         BODY*& frust,    // body constructed
                                         AcisOptions* ao = NULL);

/**
 * @brief           根据给定的 高 和 椭圆台半轴长 创建椭圆台 frustum
 * @param[in]       height    椭圆台的高
 * @param[in]       radius1   椭圆台底部Ox方向的半轴长度
 * @param[in]       radius2   椭圆台底部Oy方向的半轴长度
 * @param[in]       top       椭圆台顶部Ox方向的半轴长度
 * @param[out]      frust     输出生成的体
 * @param[in]       ao        ACIS属性
 *
 * @details         椭圆台主轴沿z轴
 *                  底面位于 z=-height/2, 顶面位于 z=height/2
 *                  top=0 的时候，椭圆台会退化为圆锥
 * @note 			top 不能小于0
 *					height、radius1、radius2 不能小于等于0
 * @return          函数执行结果
 */
DECL_CSTR outcome gme_2_api_make_frustum(double height,   // height of frustum
                                         double radius1,  // radius of base in x coordinate
                                         double radius2,  // radius of base in y coordinate
                                         double top,      // radius of top in x coordinate
                                         BODY*& frust,    // body constructed
                                         AcisOptions* ao = NULL);
/**
 * @brief           根据给定的 高 和 椭圆台半轴长 创建椭圆台 frustum
 * @param[in]       height    椭圆台的高
 * @param[in]       radius1   椭圆台底部Ox方向的半轴长度
 * @param[in]       radius2   椭圆台底部Oy方向的半轴长度
 * @param[in]       top       椭圆台顶部Ox方向的半轴长度
 * @param[out]      frust     输出生成的体
 * @param[in]       ao        ACIS属性
 *
 * @details         椭圆台主轴沿z轴
 *                  底面位于 z=-height/2, 顶面位于 z=height/2
 *                  top=0 的时候，椭圆台会退化为圆锥
 * @note 			top 不能小于0
 *					height、radius1、radius2 不能小于等于0
 * @return          函数执行结果
 */
DECL_CSTR outcome gme_3_api_make_frustum(double height,   // height of frustum
                                         double radius1,  // radius of base in x coordinate
                                         double radius2,  // radius of base in y coordinate
                                         double top,      // radius of top in x coordinate
                                         BODY*& frust,    // body constructed
                                         AcisOptions* ao = NULL);

/**
* Creates a solid cylinder or cone given two positions on the axis.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid cylinder or cone. The cylinder or cone
* may be circular or elliptical.
* <br><br>
* For a circular cylinder or %cone, specify the same values for <tt>major_radius</tt> and
* <tt>minor_radius</tt>. For an elliptical cylinder or %cone, specify two different values.
* <br><br>
* For a cylinder, specify the same values for <tt>top_radius</tt> and <tt>major_radius</tt>. For a
* %cone, specify two different values. 
* <br><br>
* When creating an elliptical %cone or cylinder, control the orientation of the major axis of the 
* %ellipse with <tt>xpt</tt>. If <tt>xpt</tt> is non-<tt>NULL</tt>, then <tt>xpt</tt>
* projects onto the %plane defined by <tt>pt1</tt> and the major axis is in the direction of the
* projection of <tt>xpt</tt>. If <tt>xpt</tt> is <tt>NULL</tt>, the system determines the orientation 
* of the major axis from the active WCS.
* <br><br>
* To make a conical face, the API @href api_face_conic is recommended.  
* To make a partial conical face, the API @href api_make_cnface is recommended. 
* <br><br>
* <b>Errors:</b> Two given positions are identical. Any of the given radii is zero.
* Position in direction of major axis is provided on the %cone axis.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param pt1
* position at the bottom.
* @param pt2
* position at the top.
* @param major_radius
* major radius at the bottom.
* @param minor_radius
* minor radius at the bottom.
* @param top_radius
* major radius at the top.
* @param xpt
* position in direction of the major axis or <tt>NULL</tt>.
* @param cyl_or_cone
* cylinder or %cone returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_solid_cylinder_cone(
		const SPAposition& pt1, // position at bottom
		const SPAposition& pt2, // position at top
		double major_radius,    // major radius at bottom
		double minor_radius,    // minor radius at bottom
		double top_radius,      // major radius at top
		const SPAposition* xpt, // position in direction of major axis (or NULL)
		BODY*& cyl_or_cone,     // cylinder or cone created
		AcisOptions* ao = NULL
	);

/**
* Creates a torus of given major and minor radii centered at the origin.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid torus given the major radius and the minor radius. 
* The torus is centered at the origin; the axis of the torus is parallel to the <i>z</i>-axis 
* of the active working coordinate system.
* <br><br>
* To make a torroidal face, the API @href api_face_torus is recommended.  
* To make a partial torroidal face, the API @href api_make_trface is recommended. 
* <br><br>
* <dl>
* <b>Errors:</b> <tt>minor_radius</tt> not greater than <tt>SPAresabs</tt>.
* <dd>&nbsp;<tt>major_radius</tt> not greater than minus the <tt>minor_radius</tt>, or 0.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param major_radius
* radius of spine of desired torus.
* @param minor_radius
* radius of cross-section of ring.
* @param tor
* torus body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_torus(
			double major_radius,		// radius of spine of torus
			double minor_radius,		// cross-sectional radius
			BODY*& tor,					// body constructed
			AcisOptions* ao = NULL
	);
/**
* @brief	构造一个旋转平面中心为原点，旋转轴平行于z轴的环面
* @param[in]	major_radius	被旋转圆的圆心与旋转轴之间的距离
*				这个值不可以是0
*				这个值可以为负数，但是当它为负时，绝对值不能大于被旋转圆的半径
* @param[in]	minor_radius	被旋转圆的半径，这个值必须大于容差值
* @param[out]	BODY		输出生成的体tor
* @param[in]	ao		ACIS属性
* @details	环面有四种情况：
*		1）当major_radius > minor_radius时，将创建一个donut形状的体
*		2）当minor_radius > major_radius > 0时，将创建一个apple形状的体
*		3）当major_radius < 0，minor_radius > |major_radius|时，将创建一个lemon形状的体
*		4）当major_radius = minor_radius > 0时，将创建一个vortex形状的体
* @return	函数执行结果
* @note		对于apple型和lemon型的环面，当minor_radius-|major_radius|的值小于1e-6时
*		ACIS函数在构建环面时会出现两个VERTEX合并成一个的VERTEX的情况
*		这会从VERTEX层级开始往上，引发一系列的的错误
*		gme函数则没有这方面的问题
**/
DECL_CSTR outcome gme_api_make_torus(
			double major_radius,		// 被旋转圆的圆心与旋转轴之间的距离
			double minor_radius,		// 被旋转圆的半径
			BODY*& tor,					// 输出生成的体tor
			AcisOptions* ao = NULL
	);

/**
* @brief		创建以原点为中心、旋转轴平行于z轴的圆环体
* @param[in]	major_radius	被旋转圆的圆心与旋转轴之间的距离（旋转半径），大于-minor_radius且不等于0
* @param[in]	minor_radius	被旋转圆的半径，大于容差值
* @param[out]	BODY			创建的圆环体
* @param[in]	ao				ACIS选项
* @details		情况一：当major_radius > minor_radius时，创建一个donut torus
*				情况二：当minor_radius > major_radius > 0时，创建一个apple torus
*				情况三：当-minor_radius < major_radius < 0时，创建一个lemon torus
*				情况四：当major_radius = minor_radius > 0时，创建一个vortex torus
*				情况五：minor有error，小于0或小于SPAresabs容差
*				情况六：major有error，等于0或小于-minor
*				情况七：|major-minor| < 1e-6
* @return		函数执行结果
**/
DECL_CSTR outcome gme_1_api_make_torus(
			double major_radius,		// 被旋转圆的圆心与旋转轴之间的距离
			double minor_radius,		// 被旋转圆的半径
			BODY*& tor,					// 输出生成的体tor
			AcisOptions* ao = NULL
	);

 /**
 * @brief   		构造一个部分圆环面，角度制
 * @param[in]    	SPAposition center    几何体的中心点
 * @param[in]    	double major    脊柱半径
 * @param[in]    	double minor    管的半径
 * @param[in]    	double tu_start 管的起始角度，u的起点
 * @param[in]    	double tu_end   管的最终角度，u的终点
 * @param[in]    	double sv_start 脊柱的起始角度，v的起点
 * @param[in]    	double sv_end   脊柱的最终角度，v的终点
 * @param[in]    	SPAvector* normal  几何体的法向量
 * @detail		构造一个部分环面，中心在center处，法向为normal
 *			u方向起点为tu_start，终点为tu_end
 *			v方向起点为sv_start，终点为sv_end
 * @return     		返回一个部分圆环面
*/
DECL_CSTR outcome gme_1_face_torus(const SPAposition& center,
	double major,             // major radius
	double minor,             // minor radius
	double tu_start,          // tube (u)  - start angle
	double tu_end,            // end angle
	double sv_start,          // spine (v) - start angle
	double sv_end,            // end angle
	const SPAvector* normal,  // axis direction
	FACE*& face, AcisOptions* ao=NULL);


/**
 * @brief   		创建一个部分圆环面
 * @param[in]    	major 		主半径，同圆环体构造中major_radius
 * @param[in]  	    minor 		管道半径，同圆环体构造中minor_radius
 * @param[in]    	tu_start 	u方向起始角度
 * @param[in]    	tu_end 		u方向终止角度
 * @param[in]    	sv_start 	v方向起始角度
 * @param[in]    	sv_end 		v方向终止角度
 * @param[in]    	normal 		法向量
 * @param[out]  	face 		返回生成的圆环面
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 * @details         该接口可处理以下情况：
 *                  1)非法输入
 *                  2)不完整，1个 loop，4个 coedge
 *                  3)上奇点，1个loop，3个coedge
 *                  4)下奇点，1个loop，3个coedge
 *                  5)无奇点，双脊柱环，2个loop
 *                  6)上奇点，单脊柱环，2个loop，2coedge
 *                  7)下奇点，单脊柱环，2个loop，2coedge
 *                  8)无奇点，双管loop
 *                  9)双奇点，单loop两个管相接
 *                 10)单奇点，双管loop
 *                 11)脊柱和管都完整
 * 
 */
DECL_CSTR outcome gme_2_api_face_torus(
		const SPAposition&  center,
		double           major,       // 主半径
		double           minor,       // 管道半径
		double           tu_start,    // u方向起始角度
		double           tu_end,      // u方向终止角度
		double           sv_start,    // v方向起始角度
		double           sv_end,      // v方终止角度
		const SPAvector* normal,      // 法向量
		FACE*&           face,
		AcisOptions* ao = NULL
	);



/**
 * @brief  根据给定的主半径和次半径创建环面体。
 *		case1: major > minor 时，创建甜甜圈环面体。
 *		case2: major == minor 时，创建涡轮体
 *		case3: major < minor 时，创建类似苹果或柠檬形状的几何体，其中顶点分别位于正负 z 轴。
 * @param[in]  major   主半径 (外半径)，决定环面体的大小
 * @param[in]  minor   次半径 (内半径)，控制环面体的厚度
 * @param[out] tor     指向生成的环面体的指针
 * @param[in]  ao      ACIS属性
 * @return outcome 返回函数的执行结果，表示创建几何体的成功或失败状态
 */
DECL_CSTR outcome gme_2_api_make_torus(
			double major_radius,		// 主半径
			double minor_radius,		// 此半径
			BODY*& tor,					// 环面体
			AcisOptions* ao = NULL
	);


/**
* @brief	以原点为中心，z轴正方向方向向量为法向量，构造圆环体
*           异常处理
*           case1：minor_radius小于容差
*           case2：major_radius等于0
*           case3：若major_radius小于0，其绝对值不小于minor_radius绝对值
* 
* @param[in]	major_radius	表示环面中心到圆心的半径（主半径）
*				该值不可为零；该值可以为负数但此时其绝对值
* @param[in]	minor_radius	表示环面的截面半径（管道半径）
*               该值需大于容差值
* @param[out]	BODY		输出生成的圆环体
* @param[in]	ao		ACIS属性
* @details	圆环体有以下几种类型
*		(1) donut torus: |major_radius| > |minor_radius|;
*		(2) apple torus: |minor_radius| > major_radius > 0;
*		(3) lemon torus: major_radius < 0，|major_radius| < |minor_radius|;
*		(4) vortex torus: major_radius > 0，|minor_radius| = major_radius;
* @return	返回一个圆环体body
**/
DECL_CSTR outcome gme_3_api_make_torus(
			double major_radius,		// 环面中心到圆心的距离
			double minor_radius,		// 管道半径
			BODY*& tor,					// 输出生成的圆环体
			AcisOptions* ao = NULL
	);


/**
* Creates a solid torus given the center as well as major and minor radii.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a solid torus given the <tt>center</tt>, the major radius,
* and the minor radius. The axis of the torus is parallel to the <i>z</i>-axis of the active
* working coordinate system.
* <br><br>
* To make a torroidal face, the API @href api_face_torus is recommended.  
* To make a partial torroidal face, the API @href api_make_trface is recommended. 
* <br><br>
* <b>Errors:</b> Any of the radii is zero.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center of the torus.
* @param major_radius
* major radius.
* @param minor_radius
* minor radius.
* @param tor
* torus returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_solid_torus(
		const SPAposition& center, // center of torus
		double major_radius,       // major radius
		double minor_radius,       // minor radius
		BODY*& tor,                // torus created
		AcisOptions* ao = NULL
	);

/**
* Creates an elliptical prism of given height, radii, and number of sides.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Centers the prism at the origin, aligned the <i>z</i>-axis, and with one face
* perpendicular to the positive <i>x</i>-axis.
* <br><br>
* <b>Errors:</b> Either <tt>height</tt>, <tt>radius1</tt>, or <tt>radius2</tt> is less than <tt>SPAresabs</tt>
* or <tt>nsides</tt> is less than 3.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param height
* height of prism.
* @param radius1
* major radius of circumscribed elliptical cylinder.
* @param radius2
* minor radius of circumscribed elliptical cylinder.
* @param nsides
* number of sides.
* @param prism
* prism body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_prism(
			double height,			// height
			double radius1,			// major radius of circumscribed
									// elliptical cylinder
			double radius2,			// minor radius
			int nsides,				// number of vertical sides
			BODY*& prism,			// body constructed
			AcisOptions* ao = NULL
	);
/**
 * @brief 构建棱柱
 *
 * @details 根据指定的底面椭圆形状，构建棱柱。
 *			case1： 对输入的两个半径和一个高度以及传入边的数量进行合法性检查
 *			case2： 根据给定底面和顶面半径以及高度创建棱柱和棱台
 *				case2.1： 若高度为0，创建一个单一面片
 *				case2.2： 若高度大于0，创建一个棱柱
 * @param[in]   height 棱锥的高度
 * @param[in]   radius1 底面椭圆的长轴半径
 * @param[in]   radius2 底面椭圆的短轴半径
 * @param[in]   nsides 底面边数，每条边间隔为360/nsides度，第一个间隔被x正方向平分
 * @param[out]  prism 返回构建好的棱柱的BODY指针的引用
 * @param[in]   ao ACIS选项的指针
 *
 * @note   
 * @return outcome 合法性检验结果
 *
 */
DECL_CSTR outcome gme_1_api_make_prism(double height, double radius1, double radius2, int nsides, BODY*& prism, AcisOptions* ao=NULL);

/**  
 * @brief			根据输入的参数创建棱柱
 * @param[in]       height		棱柱的高度
 * @param[in]       radius1		棱柱的底面长轴
 * @param[in]		radius2		棱柱的底面短轴
 * @param[in]		nsides		底面边数，每条边间隔为360/nsides度，第一个间隔被x正方向平分
 * @param[out]      prism		返回的棱柱实体
 * @param[in]		ao			ACIS选项
 * @details			case1：参数合法性检查（调用check系列函数）
					case2：棱柱高度为0，则返回一个平面薄片
					case3：棱柱高度不为0，返回正常棱柱
 * @return  		outcome 输出结果
 */
DECL_CSTR outcome gme_2_api_make_prism(
			double height,			// height
			double radius1,			// major radius of circumscribed
									// elliptical cylinder
			double radius2,			// minor radius
			int nsides,				// number of vertical sides
			BODY*& prism,			// body constructed
			AcisOptions* ao = NULL
	);

/**
* Creates an elliptical pyramid of given height, radii, and number of sides.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Centers the pyramid at the origin, aligned with the <i>z</i>-axis, and with
* one side of the base perpendicular to the positive <i>x</i>-axis. If the <tt>height</tt> is zero,
* the resulting body consists of one polygonal, double-sided, sheet face, lying in
* the <i>xy</i> %plane.
* <br><br>
* <b>Errors:</b> Either <tt>radius1</tt> or <tt>radius2</tt> is less than <tt>SPAresabs</tt> or <tt>height</tt> is greater than
* zero and less than <tt>SPAresabs</tt> or <tt>top</tt> is less than <tt>-SPAresabs</tt> or <tt>nsides</tt> is less
* than 3.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param height
* height of pyramid.
* @param radius1
* major radius of base.
* @param radius2
* minor radius of base.
* @param top
* major radius of top.
* @param nsides
* number of sides.
* @param pyramid
* pyramid body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_pyramid(
			double height,			// height
			double radius1,			// major radius of circumscribed
									// cylinder
			double radius2,			// minor radius
			double top,				// top major radius
			int nsides,				// number of sides
			BODY*& pyramid,			// body constructed
			AcisOptions* ao = NULL
	);

/**
 *	@brief	创建底面和顶面为多边形的棱台
 *	@details 根据指定的顶面和底面的椭圆形状构建多边形棱台
 *		case1：对输入的底面长轴、短轴、边的数量、高度进行合法性检查
 *		case2：使用合法的参数构造多边形棱台
 *			case2.1：高度为0，则创造薄片
 *			case2.2：高度大于0，底面major和minor不等于0，创造棱台
 * @param[in] height		高度
 * @param[in] radius1		底面长轴
 * @param[in] radius2		底面短轴
 * @param[in] top			顶面长轴
 * @param[in] nsides		棱的个数（侧面面数）
 * @param[in] ao				ACIS选项
 * @param[out] pyramid		返回的棱台BODY
 * @return outcome 输出结果
 */
DECL_CSTR outcome gme_1_api_make_pyramid(double height, double radius1, double radius2, double top, int nsides, BODY*& pyramid, AcisOptions* ao = NULL);


/**
* Creates a body having one B-spline face, for testing purposes.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a body having a B-spline %surface patch that is
* sufficiently "interesting" to make the body useful in testing. If a height is provided, the
* resulting body is a block whose other five faces are planes.  Otherwise, the
* body consists of a single B-spline face.
* <br><br>
* The B-spline %surface is derived from the four B-spline curves used to define its edges.
* Each %curve is a cubic B-spline with two spans, passing through three colinear points.
* The curves' shapes are specified by integer arguments, where:
* <br><br>
* <table width = 100%>
* <tr width = 100%>
* <td width = 5%>0</td>
* <td>is a straight line</td>
* </tr>
* <tr>
* <td>1</td>
* <td>is an "s" shape, starting at low parameter value with a 45 degree upward
* (positive z) tangent, and ending at high parameter in the same direction.</td>
* </tr>
* <tr>
* <td>2</td>
* <td>is a double hump, starting going upwards and ending downwards.</td>
* </tr>
* <tr>
* <td>-1</td>
* <td>is the same as 1, but inverted.</td>
* </tr>
* <tr>
* <td>-2</td>
* <td>is the same as 2, but inverted.</td>
* </tr>
* </table>
* <br>
* <dl>
* <b>Errors:</b> Width, depth, or height not greater than zero.
* <dd>&nbsp;Invalid curve specification.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param width
* width of wiggle.
* @param depth
* depth of wiggle.
* @param height
* height of wiggle.
* @param low_v_type
* %spline shape parameter.
* @param high_v_type
* %spline shape parameter.
* @param low_u_type
* %spline shape parameter.
* @param high_u_type
* %spline shape parameter.
* @param height_given
* flags whether the body has a height.
* @param wiggle
* wiggle body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_wiggle(
			double width,			// width of wiggle platform
			double depth,  			// depth of wiggle platform
			double height,			// height of wiggle platform
			int    low_v_type,		// wiggle shape parameter
			int    high_v_type,		// wiggle shape parameter
			int    low_u_type,		// wiggle shape parameter
			int    high_u_type,		// wiggle shape parameter
			logical height_given,   // should wiggle have a height at all?
			BODY*& wiggle,			// the wiggle body returned as output
			AcisOptions* ao = NULL
	);

/**
 * @brief Creates a body having one B-spline face, for testing purposes.
 * @details 根据输入参数先创建出b样条曲面，接着利用这四条边和顶点创建body的剩余部分
 * @param[in] width width of wiggle.
 * @param[in] depth depth of wiggle.
 * @param[in] height height of wiggle.
 * @param[in] low_v_type %spline shape parameter.
 * @param[in] high_v_type %spline shape parameter.
 * @param[in] low_u_type %spline shape parameter.
 * @param[in] high_u_type %spline shape parameter.
 * @param[in] height_given flags whether the body has a height.
 * @param[out] wiggle wiggle body returned.
 * @param[in] ao ACIS options.
 * @return outcome wiggle created.
 * @exception 当输入的low_v_type、high_v_type、low_u_type、high_u_type不属于{-2,-1,0,1,2}时会抛出VALUE_OUT_RANGE
 */
DECL_CSTR outcome gme_api_wiggle(double width, double depth, double height, int low_v_type, int high_v_type, int low_u_type, int high_u_type, logical height_given, BODY*& wiggle, AcisOptions* ao = NULL);

/**
 * @brief Creates a body having one B-spline face, for testing purposes.
 * @details 根据输入参数先创建出b样条曲面，接着利用这四条边和顶点创建body的剩余部分
 * @param[in] width width of wiggle.
 * @param[in] depth depth of wiggle.
 * @param[in] height height of wiggle.
 * @param[in] low_v_type %spline shape parameter.
 * @param[in] high_v_type %spline shape parameter.
 * @param[in] low_u_type %spline shape parameter.
 * @param[in] high_u_type %spline shape parameter.
 * @param[in] height_given flags whether the body has a height.
 * @param[out] wiggle wiggle body returned.
 * @param[in] ao ACIS options.
 * @return outcome wiggle created.
 * @exception 当输入的low_v_type、high_v_type、low_u_type、high_u_type不属于{-2,-1,0,1,2}时会抛出VALUE_OUT_RANGE
 */
DECL_CSTR outcome gme_3_api_wiggle(double width, double depth, double height, int low_v_type, int high_v_type, int low_u_type, int high_u_type, logical height_given, BODY*& wiggle, AcisOptions* ao = NULL);

/**
 * @brief Creates a body having one B-spline face, for testing purposes.
 * @details 根据输入参数先创建出b样条曲面，接着利用这四条边和顶点创建body的剩余部分
 * @param[in] width width of wiggle.
 * @param[in] depth depth of wiggle.
 * @param[in] height height of wiggle.
 * @param[in] low_v_type %spline shape parameter.
 * @param[in] high_v_type %spline shape parameter.
 * @param[in] low_u_type %spline shape parameter.
 * @param[in] high_u_type %spline shape parameter.
 * @param[in] height_given flags whether the body has a height.
 * @param[out] wiggle wiggle body returned.
 * @param[in] ao ACIS options.
 * @return outcome wiggle created.
 * @exception 当输入的low_v_type、high_v_type、low_u_type、high_u_type不属于{-2,-1,0,1,2}时会抛出VALUE_OUT_RANGE
 */
DECL_CSTR outcome gme_1_api_wiggle(double width, double depth, double height, int low_v_type, int high_v_type, int low_u_type, int high_u_type, logical height_given, BODY*& wiggle, AcisOptions* ao = NULL);

/**
 * @brief		创建一个具有一个B样条面的实体，用于测试目的
 * @details		根据输入参数先创建出b样条曲面，接着利用这四条边和顶点创建body的剩余部分
 *				处理情况1：检查参数——width、depth、height为正值，波形曲面形状参数在合法范围内，否则报错
 *				处理情况2：如果height给定，使用已经构造的波形曲面构造一个block，其余五个面为平面
 *				处理情况3：如果height未给定，构造一个只有一个波形曲面的body
 * @param[in]	width wiggle的宽度
 * @param[in]	depth wiggle的深度
 * @param[in]	height wiggle的高度
 * @param[in]	low_v_type spline的形状参数
 * @param[in]	high_v_type spline的形状参数
 * @param[in]	low_u_type spline的形状参数
 * @param[in]	high_u_type spline的形状参数
 * @param[in]	height_given body是否有高度
 * @param[out]	wiggle 输出的wiggle body
 * @param[in]	ao ACIS选项
 * @return		执行结果
 * @exception	width、depth、height非正值
 *				low_v_type、high_v_type、low_u_type、high_u_type不属于{-2,-1,0,1,2}
 */
DECL_CSTR outcome gme_2_api_wiggle(
									double width,			// wiggle的宽度
									double depth,			// wiggle的深度
									double height,			// wiggle的高度
									int low_v_type,			// spline的形状参数
									int high_v_type,		// spline的形状参数
									int low_u_type,			// spline的形状参数
									int high_u_type,		// spline的形状参数
									logical height_given,	// body是否有高度
									BODY*& wiggle,			// 输出的wiggle body
									AcisOptions* ao = NULL);

/**
* Creates a body consisting of a single-sided face that is the whole of a given spline %surface.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param this_spline
* spline %surface; caller retains ownership, and is responsible for deleting.
* @param body
* single-sided face body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_spline(
			const spline& this_spline,	// surface for single body face
			BODY*& body,				// body constructed (with free
										// edges unless surface is closed
										// in both directions)
			AcisOptions* ao = NULL
	);

/**
 * @brief		创建仅由给定样条曲面构成的体
 * @details		根据给定样条面创建仅包含它的体
 * @param[in]	this_spline		传入由此构建体的样条曲面
 * @param[out]	body			返回单面样条曲面体结果
 * @param[in]	ao				ACIS 选项
 * @return		返回由单面样条曲面创建的体
 * @exception	空spline引发NO_SPLINE_APPROX
 */
DECL_CSTR outcome gme_api_make_spline(
			const spline& this_spline,	// 由此构建体的样条曲面
			BODY*& body,				// 返回单面样条曲面体结果
			AcisOptions* ao = NULL
	);
/**
 * @brief		根据输入的样条曲面，创建由单侧面组成的实体
 * @details		根据输入的样条曲面，创建由单侧面组成的实体，该单侧面就是整个输入的spline
 * @param[in]	this_spline		输入的Spline样条曲面，调用者保留所有权，并负责删除。
 * @param[out]	body			创建的单侧面body
 * @return		函数执行结果
 * @note		输入的spline由调用者保留所有权，并负责删除
 * @exception	acis_exception(NO_SPLINE_APPROX)	输入了一个空的spline
 */
DECL_CSTR outcome gme_1_api_make_spline(
			const spline& this_spline,	// 输入的用来创建单侧面的样条曲面
			BODY*& body,				// 创建的BODY
			AcisOptions* ao = NULL
	);
/**
 * @brief		创建由给定样条曲面构成得单侧面body
 * @details
 * @param[in]	this_spline		输入的Spline样条曲面
 * @param[out]	body			创建的单侧面body
 * @param[in]	ao				ACIS 选项
 * @return		outcome 执行结果
 * @exception	acis_exception(NO_SPLINE_APPROX)	当输入空的spline时抛出异常
 */
DECL_CSTR outcome gme_2_api_make_spline(
			const spline& this_spline,	// 输入的给定样条曲面
			BODY*& body,				// 输出创建的BODY
			AcisOptions* ao = NULL
	);

/**
* Creates a sheet body as a copy of a face.
* <br><br>
* <b>Errors:</b> Entity in array is not a <tt>FACE</tt>.
* <br><br>
* <b>Limitations:</b> Currently only handles one face. The face is passed in an array
* to enable future expansion of functionality without changing the function
* signature.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param num_faces
* number of faces (must be 1).
* @param faces
* array containing face.
* @param body
* sheet-body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_sheet_from_ff(
			int num_faces,			// number of faces
			FACE* faces[],			// array of faces
			BODY*& body,			// sheet body constructed
			AcisOptions* ao = NULL
	);

/*! @} */
/*! \addtogroup CSTRMAKEWBODYAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */

/**
* Creates a body that consists of a single wire from a list of edges that are connected
* in the order given, with no branching.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a <tt>BODY</tt> that consists of a single <tt>WIRE</tt>. The
* <tt>COEDGE</tt>s are created from the <tt>EDGE</tt>s in the edge list supplied as input. Duplicate
* <tt>VERTEX</tt>s between adjacent edges are deleted. The edges are assumed to form a
* G<sup>0</sup> continuous geometry that is not self-intersecting, and may be open or closed.
* <br><br>
* A single-point wire can be made; however, such wires are not fully supported by
* Booleans and Offsetting.
* <br><br>
* <b>Errors:</b> A pointer in the edge array is <tt>NULL</tt> or references something other
* than an <tt>EDGE</tt>.
* <br><br>
* <b>Limitations:</b> Wires that are a single isolated point (characterized by an
* edge with NULL geometry) are not fully supported. 
* If the input edges do not match at vertices within SPAresasbs, api_make_ewire will fail. In this case, 
* instead use <tt>api_make_ewires</tt>, and 
* configure the input <tt>make_ewire_opts</tt> using the <tt>set_coin_tol</tt> method.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param num_edges
* number of edges in the list.
* @param edges
* array of edges.
* @param body
* wire-body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_ewire(
			int num_edges,				// number of edges
			EDGE* edges[],				// array of edges
			BODY*& body,				// body constructed
			AcisOptions* ao = NULL
	);

/**
* Separates and sorts a possibly branched list of free edges into a group of non-branched wire bodies.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* Optionally, you may use a <tt>make_ewires_opts</tt> object to specify a tolerance for when start/end vertices
* of the free edges coincide. If this option is used, the vertices are tolerized as necessary.
* <br><br>
* There is also an option indicating whether the input is a single ordered wire.  If this option is set
* the input array of edges must form an unbranched collection, and each edge must share a boundary vertex
* (either its start or its end) with the next edge in the array.  For example, if the single ordered wire
* flag is set, and P, Q, R and S are distinct points with edges indicated by -->, the following input sequence
* of edges is acceptable P-->Q, Q-->R, S-->R, P-->S, while the sequence P-->S, Q-->S, R-->S is not.
* <br><br>
* <b>Role:</b> Input edges need not be ordered.
* <br><br>
* <b>Errors:</b> Pointer in edge array is <tt>NULL</tt> or not to an <tt>EDGE</tt>.
* <br><br>
* <b>Limitations:</b> Wires that are in a single isolated point (characterized by an
* edge with null geometry) are not fully supported.
* <br><br>
* Supplying input edges that intersect somewhere other than at a vertex results in an error outcome.
* <br><br>
* The function will fail if the tolerance for start/end vertex coincidence is larger than 40% of the
* minimum input edge length: tolerizing in this circumstance could damage the model.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param num_edges
* Specifies the edge count.
* @param edges
* Specifies the array of edges.
* @param n_bodies
* Specifies the number of wire bodies created.
* @param bodies
* Holds the wire bodies created.
* @param mew_opts
* Holds tolerance for deciding when edge start/end points coincide.
* @param ao
* Specifies ACIS options.
**/
DECL_CSTR outcome api_make_ewires(
			int num_edges,				// number of unorganized edges
			EDGE* edges[],				// array of edges
			int& n_bodies,				// number of bodies constructed
			BODY**& bodies,				// bodies constructed
			make_ewires_opts *mew_opts,	// options object; holds tolerance for deciding when edge start/end points coincide
			AcisOptions* ao = NULL
	);

/**
* Separates and sorts a possibly branched list of free edges into a group of non-branched wire bodies.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Input edges need not be ordered.
* <br><br>
* <b>Errors:</b> Pointer in edge array is <tt>NULL</tt> or not to an <tt>EDGE</tt>.
* <br><br>
* <b>Limitations:</b> Wires that are in a single isolated point (characterized by an
* edge with null geometry) are not fully supported.
* <br><br>
* Supplying input edges that intersect somewhere other than at a vertex results in an error outcome.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param num_edges
* Specifies the edge count.
* @param edges
* Specifies the array of edges.
* @param n_bodies
* Specifies the number of wire bodies created.
* @param bodies
* Holds the wire bodies created.
* @param ao
* Specifies ACIS options.
**/
DECL_CSTR outcome api_make_ewires(
			int num_edges,			// number of unorganized edges
			EDGE* edges[],			// array of edges
			int& n_bodies,			// number of bodies constructed
			BODY**& bodies,			// bodies constructed
			AcisOptions* ao = NULL
	);

/**
* Creates a polygonal wire body in a %plane orthogonal to a given normal.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function constructs a polygonal wire body. The length of the sum of
* the sides of the polygon is calculated and passed back.
* <br><br>
* Note that both the length of the vector <tt>start</tt> and the double <tt>length</tt> dictate the
* length of the sides of the polygon. If the user passes in <tt>length &lt;= SPAresabs</tt>,
* the length of the sides of the polygon will be determined solely by the vector
* <tt>start</tt> and the number of sides in the polygon and the <tt>oncenter</tt> flag. In this case
* the user is told the computed length of sides by the reference variable <tt>length</tt>.
* If on the other hand <tt>length &gt; SPAresabs</tt>, the polygon
* will be scaled so that the sides each have the proper length.
* <br><br>
* <dl>
* <b>Errors:</b> The start vector must be non-zero.
* <dd>&nbsp;The normal vector must be non-zero.</dd>
* <dd>&nbsp;The start and normals must span a two dimensional space.</dd>
* <dd>&nbsp;The number of sides must be at least 3</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param polygon
* polygon made.
* @param centre
* center of the polygon.
* @param start
* from center to a vertex or the center of an edge of polygon.
* @param normal
* a vector normal to the %plane of the polygon.
* @param side_length
* length of the side (this will scale "start").
* @param number_of_sides
* number of sides.
* @param oncenter
* <tt>TRUE</tt> when the start is a vector to the center of an edge.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_polygon(
	BODY*& polygon,				// new polygonal wire body returned
	SPAposition centre,			// centre of polygon
	SPAvector start,			// centre + start is on edge vertex or edge centre
	SPAvector& normal,			// normal to plane containing polygon
	double& side_length,		// length of side (scales start vector to get this)
	int number_of_sides = 6,	// defaulted to a hexagon
	logical oncenter = FALSE,	// if TRUE, centre + start is on edge centre
	AcisOptions* ao = NULL
	);

/**
* Creates a wire from an instance of formatted_text.
* <b>Technical Article:</b> <i>[Make a Wire Body from Text](http://doc.spatial.com/articles/m/a/k/Make_a_Wire_Body_from_Text_2a9a.html)</i>
* <br><br>
* <b>Role:</b> This API function constructs a topologically valid @href WIRE body from an instance of formatted_text.
* <br><br>
* To conform to valid ACIS topology, the API will resolve any improper intersections between edges.
* <br><br>
* <b>Scope: </b> 
* <ul>
* <li>The API does not check for self-intersecting geometry. If the character outlines contain self-intersections within an edge, they will not be resolved.</li>
* <li>The API only accepts TrueType font information.
* <li>The functionality is only supported on the Windows Operating System. </li>
* </ul>
* <br><br>
* <b>Effect:</b> Creates a wire body, in the shape of the text and font given.
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param text
* an instance of formatted text.
* @param body
* new body containing the wire.
* @param mk_opts
* an object for future expansion.
* @param ao
* ACIS options.
**/

DECL_CSTR outcome api_make_wire(	
			const formatted_text&		text,			// The text that will govern the shape of the wire.
			BODY*&						body,			// New wire body with the wire output.
			make_wire_options*			mk_opts = NULL, // An option for future expansions.
			const AcisOptions*			ao = NULL		
	);

/*! @} */
/*! \addtogroup CSTRMAKEFACEAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */
//============================================================
// Face creation functions


/**
* Creates a face that is a parallelogram specified by three points: origin, left, and right.
* <br><br>
* <b>Role:</b> This API function creates a planar face of the given width and height, 
* relative to the active WCS, with its lower left-hand corner at the given position.
* All positions are relative to the active WCS or, if a <tt>normal</tt> is specified, a temporary coordinate system
* derives from the <tt>normal</tt> and the <i>x</i>-axis.
* <br><br>
* The <tt>normal</tt> becomes the z-axis of an alternate coordinate system, (xyz). 
* If the z-axis and the active x-axis are parallel, the new y-axis is the active y-axis. 
* If they are not parallel, the y-axis is the normal to the %plane defined by the z-axis 
* and the x-axis. The x-axis is then determined as the normal to the %plane defined y-axis and the z-axis.
* <br><br>
* If the <tt>normal</tt> is in the direction of the z-axis, then the width and height are in the 
* direction of the WCS x-axis and y-axis, respectively. Orientation of width and height 
* in any other case is not guaranteed.
* <br><br>
* <b>Errors:</b> <br>
* A face cannot have a zero width or height; therefore, both <tt>(left - origin)</tt> 
* and <tt>(right - origin)</tt> must be greater than <tt>SPAresabs</tt>.<br> 
* A %plane cannot have a zero length normal; therefore, the length of 
* <tt>((left - origin) * (right - origin))</tt> must be greater than <tt>SPAresabs</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param p
* anchor point.
* @param width
* face width.
* @param height
* face height.
* @param normal
* %plane normal.
* @param face
* planar face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_plane(
		const SPAposition&  p,        // anchor point
		double           width,
		double           height,
		const SPAvector* normal,
		FACE*&           face,
		AcisOptions* ao = NULL
	);

/**
* Creates a face that is a parallelogram specified by three points: origin,left, and right.
* <br><br>
* <b>Role:</b> The three points: origin, left, and right, must not be colinear. The normal to the
* %plane is defined by the cross product of the vectors (<tt>right - origin</tt>) and 
* (<tt>left - origin</tt>). The boundary consists of four linear edges starting at the origin and
* going to the right to define a parallelogram ending at the origin.
* <br><br>
* The origin is the root point of the %plane and the normal is in the direction of
* <tt>(right - origin) * (left - origin)</tt>. Left and right are points to the left and
* right of the origin.
* <br><br>
* <b>Errors:</b> A %plane cannot have a zero length or width; therefore, both (<tt>right - origin</tt>)
* and (<tt>left - origin</tt>) must be greater than <tt>SPAresabs</tt>.
* <br><br>
* A %plane cannot have a zero length normal; therefore, the length of 
* <tt>((right - origin) * (left - origin))</tt> must be greater than <tt>SPAresabs</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param origin
* origin of the %plane.
* @param left
* left point on the %plane.
* @param right
* right point on the %plane.
* @param face
* planar face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_plface(
			const SPAposition& origin, 		// origin point
			const SPAposition& left,  		// left point
			const SPAposition& right,  		// right point
			FACE*& face,     				// ouput returned
			AcisOptions* ao = NULL
	);

/**
* Creates a face that is a planar disk.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a single-sided, planar face.  The origin and normal of the
* underlying %plane are specified by <tt>origin</tt> and <tt>normal</tt>. If <tt>half_space</tt>
* is <tt>FALSE</tt>, the face is bounded by a circular edge of the given radius. If <tt>half_space</tt>
* is <tt>TRUE</tt>, the face is unbounded.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param origin
* origin point.
* @param normal
* the normal.
* @param radius
* the radius.
* @param face
* planar disk returned.
* @param half_space
* If set to <tt>TRUE</tt>, a full half space is returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_planar_disk(
			const SPAposition& origin, 		// origin point
			const SPAunit_vector& normal,	// the normal
			double radius,  	    		// the radius
			FACE*& face,   					// output returned
			logical half_space = FALSE,		// If set to true a full half space is returned
			AcisOptions* ao = NULL
	);
	
/**
* Creates a spherical face.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a spherical face aligned with the axes of the
* working coordinate system. 
* <br><br>
* The North Pole is parallel to the <i>z</i>-axis and corresponds to 90 degrees latitude. The Prime Meridian 
* (or line of zero degree longitude) point on the Equator is parallel to <i>x</i>-axis. All positions are relative 
* to the active WCS or, if <tt>normal</tt> is specified, a coordinate system derives from the <tt>normal</tt> as 
* the <i>z</i>-axis.
* <br><br>
* <table width = 100%>
* <tr width = 100%>
* <td width = 20%>Angle ranges:</td>
* <td>&nbsp;</td>
* </tr>
* <tr>
* <td>Latitude</td>
* <td>-90 to 90 degrees,</td>
* </tr>
* <tr>
* <td>&nbsp;</td>
* <td>+90 degrees at the North Pole, 0 degree at the Equator</td>
* </tr>
* <tr>
* <td>Longitude</td>
* <td>0 to 360 degrees,</td>
* </tr>
* <tr>
* <td>&nbsp;</td>
* <td>0 degree is the Prime Meridian (or line of zero degree longitude)</td>
* </tr>
* </table>
* <br>
* To make a partial spherical face, the API @href api_make_spface is recommended. 
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center.
* @param radius
* radius.
* @param lat_start
* latitude start angle (in degrees).
* @param lat_end
* latitude end angle (in degrees).
* @param lo_start
* longitude start angle (in degrees).
* @param lo_end
* longitude end angle (in degrees).
* @param normal
* pole direction.
* @param face
* spherical face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_sphere(
		const SPAposition&  center,
		double           radius,
		double           lat_start,    // latitude - start angle
		double           lat_end,      //             end angle
		double           lo_start,     // longitude  - start angle
		double           lo_end,       //             end angle
		const SPAvector* normal,       // pole direction
		FACE*&           face,
		AcisOptions* ao = NULL
	);

/**
* Creates a face that is a portion of a sphere.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> The sphere is defined by its center and radius. The boundaries of the spherical face lie along 
* latitude and longitude lines.
* <br><br>
* The 'uv_oridir' vector points to the Prime Meridan (or line of zero degree longitude) point on the Equator
* and the 'pole_dir' vector points to the North Pole. The unit vectors defining these directions must be
* perpendicular.
* <br><br>
* Latitude angles lie in the range <tt>[-pi / 2, pi / 2]</tt> from the South Pole to the North Pole.
* <br><br>
* Longitude angles lie in the range <tt>[0, 2 * pi]</tt> with 0 being the Prime Meridian and increasing
* relative to the right hand rule using the 'pole_dir' vector. 
* The subtended longitude angle must be less than or equal to 2 <tt>pi</tt>.
* <br><br>
* Refer to the <i>[Sphere](http://doc.spatial.com/articles/s/p/h/Sphere.html)</i> 
* Technical Article for illustrations and more information.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center of the sphere.
* @param radius
* radius of the sphere.
* @param uv_oridir
* prime meridian point on the equator.
* @param pole_dir
* north pole direction.
* @param slat
* start latitude angle (in radians).
* @param elat
* end latitude angle  (in radians).
* @param slon
* start longitude angle (in radians).
* @param elon
* end longitude angle (in radians).
* @param face
* spherical face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_spface(
			const SPAposition& center,			// center of the sphere.
			double radius,						// radius of the sphere.
			const SPAunit_vector& uv_oridir,    // Prime meridian point on the equator
			const SPAunit_vector& pole_dir,		// North pole direction
			double slat,						// Start and end 
			double elat,						// latitude angles.
			double slon,						// Start and end 
			double elon,						// longitude angles.
			FACE*& face,						// spherical face returned.
			AcisOptions* ao = NULL
	);

/**
 * @brief 构建部分球面 face。
 * @details 构建部分球面 face。球由球心和半径定义，face 的边界是纬线和经线。可以自定义极轴和零度经线的方向向量。
 * @param[in] center 球心坐标
 * @param[in] radius 球半径
 * @param[in] uv_oridir 指向赤道上零度经线的位置，即uv参数方向
 * @param[in] pole_dir 指向北极的方向
 * @param[in] slat 起始纬度角（弧度）
 * @param[in] elat 结束纬度角（弧度）
 * @param[in] slon 起始经度角（弧度）
 * @param[in] elon 结束经度角（弧度）
 * @param[out] face 返回的球面
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 * @exception ZERO_SPHERE 半径为0，或者纬度差为0，或者经度差为0
 */
DECL_CSTR outcome gme_api_make_spface(
			const SPAposition& center,			// center of the sphere.
			double radius,						// radius of the sphere.
			const SPAunit_vector& uv_oridir,    // Prime meridian point on the equator
			const SPAunit_vector& pole_dir,		// North pole direction
			double slat,						// Start and end 
			double elat,						// latitude angles.
			double slon,						// Start and end 
			double elon,						// longitude angles.
			FACE*& face,						// spherical face returned.
			AcisOptions* ao = NULL
	);

/**
 * @brief 构建部分球面 face。
 * @details 构建部分球面 face。球由球心和半径定义，face 的边界是纬线和经线。可以自定义极轴和零度经线的方向向量。
 *			case1:半径为0，返回ZERO_SPHERE
 *			case2:起始、终止经纬度超出边界值，超出下界时取下界，超出上界时取上界
 *			case3:起始终止经纬度相同，返回ZERO_SPHERE
 *			case4:起始(经)纬度小于终止(经)纬度，交换起始、终止(经)纬度
 *			case5:uv_oridir(pole_dir)为0向量，效果等同于向量(1,0,0)和(0,0,1)
 *			case6:uv_oridir与pole_dir平行，将两者都设置为0向量
 *			case7:半径为负，获得反向球面
 * @param[in] center 球心坐标
 * @param[in] radius 球半径
 * @param[in] uv_oridir 指向赤道上零度经线的位置，即uv参数方向
 * @param[in] pole_dir 指向北极的方向
 * @param[in] slat 起始纬度角（弧度）
 * @param[in] elat 结束纬度角（弧度）
 * @param[in] slon 起始经度角（弧度）
 * @param[in] elon 结束经度角（弧度）
 * @param[out] face 返回的球面
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 * @exception ZERO_SPHERE 半径为0，或者纬度差为0，或者经度差为0
 */
DECL_CSTR outcome gme_1_api_make_spface(
			const SPAposition& center,			// center of the sphere.
			double radius,						// radius of the sphere.
			const SPAunit_vector& uv_oridir,    // Prime meridian point on the equator
			const SPAunit_vector& pole_dir,		// North pole direction
			double slat,						// Start and end 
			double elat,						// latitude angles.
			double slon,						// Start and end 
			double elon,						// longitude angles.
			FACE*& face,						// spherical face returned.
			AcisOptions* ao = NULL
	);

/**
* Creates a symmetric face whose cross section is a conic section.
* <br><br>
* <b>Role:</b> This API function creates a face that is rotationally or reflectively
* symmetric (i.e., a "dish" or a "trough"), with a cross section that corresponds to a conic section.
* The latter is determined by the argument <tt>conic_const</tt>, which is the negative
* of the conic constant as usually defined.  That is, <tt>conic_const = 0</tt>
* yields a spherical cross section, <tt>0 < conic_const < 1</tt> yields elliptical,
* <tt>conic_const = 1</tt> yields parabolic, and <tt>conic_const > 1</tt> yields
* hyperbolic.  The argument <tt>extent</tt> determines how far the %surface extends
* perpendicular to the symmetry axis.
* <br><br>
* The argument <tt>length</tt> determines the kind of symmetry characterizing the
* resulting face.  If it is zero, the face is rotationally symmetric about the z-axis;
* if it is positive, the resultant face is reflectively symmetric through the xz-plane,
* forming a trough about the x-axis of length equal to the value of <tt>length</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param radius
* conic section radius of curvature.
* @param conic_const
* the negative of the conic constant.
* @param extent
* the maximum extent of the face perpendicular to the symmetry axis.
* @param length
* if length is greater than 0, then a conic trough of this length is formed.
* @param face
* output face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_conic(
			double radius,			// Vertex radius
			double conic_const,		// Conic constant
			double extent,			// x^2+y^2<extent or y^2<extent if length>0
			double length,			// If length > 0 then a conic trough is formed
			FACE*& face,			// Output face returned
			AcisOptions* ao = NULL
	);

/**
 * @brief 构建切面为圆锥曲线的槽面或碟面。
 * @details 根据圆锥曲线顶点的曲率半径和圆锥常数来构建切面线，通过extent和length控制生成大小
 * @param[in] radius		圆锥曲线顶点处曲率半径
 * @param[in] conic_const	圆锥曲线常数，决定曲线形状。
 * @param[in] extent		向圆锥曲线变化方向所延伸的长度
 * @param[in] length		若length==0，则构建碟形dish，若length>0，则构建槽形trouph，并且trouph底宽等于length
 * @param[out] face			返回构建的圆锥曲线面
 * @param[in] ao ACIS选项
 * @return outcome 执行结果
 * @exception
 */
DECL_CSTR outcome gme_api_face_conic(
			double radius,			// 圆锥曲线顶点处的曲率半径
			double conic_const,		// 圆锥常数的相反数
			double extent,			// 向圆锥曲线变化方向所延伸的长度
			double length,			// 若length==0，则构建碟形dish，若length>0，则构建槽形trouph。
			FACE*& face,			// 返回结果face
			AcisOptions* ao = NULL
	);
	
/**
* Creates a cylindrical or conical face.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a cylindrical or conical face, given the <tt>center</tt>,
* the direction of the %cone/cylinder axis, its height (given by the length of <tt>normal</tt>),
* a <tt>top</tt> radius, and a <tt>bottom</tt> radius. The start angle, <tt>start</tt> (provided in degrees),
* and the end angle, <tt>end</tt> (provided in degrees),
* are defined in the active WCS or, if given, in the coordinate system defined by
* the %cone/cylinder axis, <tt>normal</tt>, and a point, <tt>pt</tt>, on the major axis.
* All positions are relative to the active WCS.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* axis origin.
* @param normal
* axis direction and height.
* @param bottom
* bottom radius.
* @param top
* top radius.
* @param start
* start angle in degrees.
* @param end
* end angle in degrees.
* @param ratio
* elliptical major/minor ratio.
* @param pt
* point defining major axis.
* @param face
* cylindrical or conical face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_cylinder_cone(
		const SPAposition& center,   // center
		const SPAvector&   normal,   // axis and height
		double             bottom,   // bottom radius
		double             top,      // top radius
		double             start,    // start angle
		double             end,      // end angle
		double             ratio,    // elliptical major to minor ratio
		const SPAposition* pt,       // point defining the major axis
		FACE*&             face,
		AcisOptions* ao = NULL
	);

/**
* Creates a face that is a portion of a cone.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> The cone is defined by a base %ellipse, sine, and cosine of the
* coning angle.
* <br><br>
* Specify the base %ellipse by a center point, a unit vector normal to the %plane of
* the %ellipse, the major axis vector, and ratio of the minor to major axis length.
* <br><br>
* The sine and cosine of the coning angle (<tt>sint</tt> and <tt>cost</tt>) specify 
* whether the %surface is a cylinder or a true %cone. If it is a %cone, they specify 
* the direction of the apex.
* <br><br>
* The boundaries of the conical face are specified by <tt>start_ang</tt>, <tt>end_ang</tt>, and
* <tt>height</tt>. The angles (specified in radians) are in the range <tt>[-2 pi, 2 pi]</tt>. 
* The difference between <tt>end_ang</tt> and <tt>start_ang</tt> must be greater than <tt>0.0</tt>
* and less than or equal to <tt>2 pi</tt>.  The end of the major axis is the angular datum (i.e., 0) 
* and the angle increases in compliance to the right hand rule using the %ellipse normal.
* <br><br>
* The <tt>height</tt> can be positive or negative, with the %plane of the %ellipse being 0,
* and positive numbers in the direction of the %ellipse normal.
* <br><br>
* The %cone starts at the %plane of the %ellipse. It has the specified height, but
* never extends past the apex of the %cone. 
* <br><br>
* Refer to the Technical Article <i>[Cone](http://doc.spatial.com/articles/c/o/n/Cone.html)</i> 
* for illustrations and more information.
* <br><br>
* <dl>
* <b>Errors:</b> Zero length normal or major axis vector specified.
* <dd>&nbsp;Major axis not perpendicular to normal.</dd>
* <dd>&nbsp;Zero height specified.</dd>
* <dd>&nbsp;Radius ratio not greater than zero.</dd>
* <dd>&nbsp;Start and end angles equal.</dd>
* <dd>&nbsp;Sine and cosine of half angle both zero.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center of the base %ellipse.
* @param normal_axis
* normal to base %ellipse.
* @param major_axis
* major axis of base %ellipse.
* @param radius_ratio
* ratio of the major to minor axes.
* @param sint
* sine of the half angle of the %cone.
* @param cost
* cosine of the half angle of the %cone.
* @param st_ang
* start angle (radians) of %cone.
* @param end_ang
* end angle (radians) of %cone.
* @param height
* height of %cone.
* @param face
* conical face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_cnface(
			const SPAposition& center,			// center of the base of the cone.
			const SPAunit_vector& normal_axis,	// normal of the cone.
			const SPAvector& major_axis,		// major axis of the cone.
			double radius_ratio,				// radius ratio of the base.
			double sint,						// sine of the half angle of the cone
			double cost,						// cosine of the half angle
			double st_ang,						// start angle of the base ellipse
			double end_ang,						// end angle of the base ellipse
			double height,						// height
			FACE*& face,						// output returned.
			AcisOptions* ao = NULL
	);

DECL_CSTR outcome gme_api_make_cnface(
			const SPAposition& center,			// center of the base of the cone.
			const SPAunit_vector& normal_axis,	// normal of the cone.
			const SPAvector& major_axis,		// major axis of the cone.
			double radius_ratio,				// radius ratio of the base.
			double sint,						// sine of the half angle of the cone
			double cost,						// cosine of the half angle
			double st_ang,						// start angle of the base ellipse
			double end_ang,						// end angle of the base ellipse
			double height,						// height
			FACE*& face,						// output returned.
			AcisOptions* ao = NULL
	);

/**
* Creates a toroidal face.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a toroidal face aligned with the axes of the
* working coordinate system. All positions are relative to the active WCS or, if
* <tt>normal</tt> is specified, a coordinate system defined by the <tt>normal</tt> and the <i>X</i>-axis.
* <br><br>
* <table width = 100%>
* <tr width = 100%>
* <td width = 20%>Angle ranges:</td>
* <td>&nbsp;</td>
* </tr>
* <tr>
* <td>tube, along the minor radius (<i>u</i>)</td>
* <td>= 0 < u_end - u_start <= 360 </td>
* </tr>
* <tr>
* <td>spine, along the major radius (<i>v</i>)
* <td>= 0 < v_end - v_start <= 360 </td>
* </tr>
* <br><br>
* Refer to the Technical Article <i>[Torus](https://doc.spatial.com/get_doc_page/articles/t/o/r/Torus.html)</i> 
* for illustrations and more information.
* <br><br>
* </table>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center.
* @param major
* major radius.
* @param minor
* minor radius.
* @param tu_start
* tube (u) start angle.
* @param tu_end
* tube (u) end angle.
* @param sv_start
* spine (v) start angle.
* @param sv_end
* spine (v) end angle.
* @param normal
* axis direction.
* @param face
* toroidal face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_torus(
		const SPAposition&  center,
		double           major,       // major radius
		double           minor,       // minor radius
		double           tu_start,    // tube (u)  - start angle
		double           tu_end,      //             end angle
		double           sv_start,    // spine (v) - start angle
		double           sv_end,      //             end angle
		const SPAvector* normal,      // axis direction
		FACE*&           face,
		AcisOptions* ao = NULL
	);

/**
 * @brief   		创建环形面，角度制。
 * @param[in]    	major 		主轴半径
 * @param[in]  	    minor 		副轴半径
 * @param[in]    	tu_start 	u方向起始角度
 * @param[in]    	tu_end 		u方向终止角度
 * @param[in]    	sv_start 	v方向起始角度
 * @param[in]    	sv_end 		v方向终止角度
 * @param[in]    	normal 		法向量
 * @param[out]  	face 		返回 face
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 */
DECL_CSTR outcome gme_api_face_torus(
		const SPAposition&  center,
		double           major,       // major radius
		double           minor,       // minor radius
		double           tu_start,    // tube (u)  - start angle
		double           tu_end,      //             end angle
		double           sv_start,    // spine (v) - start angle
		double           sv_end,      //             end angle
		const SPAvector* normal,      // axis direction
		FACE*&           face,
		AcisOptions* ao = NULL
	);

/**
* Creates a face that is a portion of a torus.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> The torus is defined by a %plane specified by a point and unit
* vector normal to the %plane. The major radius gives the distance from the center
* to the spine %curve lying in this %plane around which a circle having the minor
* radius is swept to define the torus.
* <br><br>
* Four classes of tori can be specified: donut, apple, lemon, or vortex depending on 
* the relative magnitudes of the major and minor radii. Also, the signs of the of the
* radii are significant in defining the shape of the tori and the orientation of
* the outward %surface normals.
* <br><br>
* The point defining the origin of a parameterization scheme on the torus is
* projected onto the %plane of the torus. The intersection of the torus and the
* line from the center towards this point that is farthest from the center define
* the (0, 0) of the parameterization scheme. 
* <br><br>
* The boundaries of the face lie on isoparametric curves specified by angles around 
* the tube and around the spine. The angles along and around the spine increase following 
* the right hand rule. However, the surface parameterization for a toroidal surface is 
* left handed. The value for the start angle must be less than the value for the
* end angle. If ths condition is not met, the values for the start and end angle will be
* swapped. The included angle (the angle between the start and end angle values) must be 
* less than or equal to 2 <tt>pi</tt>. 
* <br><br>
* Refer to the Technical Article <i>[Torus](http://doc.spatial.com/articles/t/o/r/Torus.html)</i>
* for illustrations and more information.
* <br><br>
* <b>Limitations:</b> The range of angles (<i>vf</i> to <i>vt</i>) must be &lt;= 2 <tt>pi</tt>.
* <br>
* Donut torus: The range of (<i>uf</i> to <i>ut</i>) must be &lt;= 2 <tt>pi</tt>.
* <br>
* Apples and lemons: The values of the <i>uf</i> and <i>ut</i> should be within the angle
* <tt>acos(fabs(major)/fabs(minor))</tt>, the singularity points. Values larger than 
* that are trimmed to the singularities.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center of the torus.
* @param normal
* normal axis of the torus.
* @param major
* major radius of the torus.
* @param minor
* minor radius of the torus.
* @param pnt
* point defining origin of parameterization.
* @param uf
* start angle in u direction (in radians).
* @param ut
* end angle in u direction (in radians).
* @param vf
* start angle in v direction (in radians).
* @param vt
* end angle in v direction (in radians).
* @param face
* toroidal face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_trface(
			const SPAposition& center,		// center of the torus.
			const SPAunit_vector& normal,	// normal axis of the torus.
			double major,					// major radius of the sphere.
			double minor,					// minor radius of the sphere.
			const SPAposition& pnt,			// point on the torus.
			double uf,						// Start and end angles
			double ut,						// in U direction.
			double vf,						// Start and end angles
			double vt,						// in V direction.
			FACE*& face,					// output returned.
			AcisOptions* ao = NULL
	);
/**
 * @brief   		根据给定的参数构建圆环面的部分面
 * @param[in]		center 		圆环的中心
 * @param[in]  	normal 	圆环所在面的法向量
 * @param[in]    	uf				u参数的起始值
 * @param[in]    	ut 			u参数的结束值
 * @param[in]    	vf				v方向的起始值
 * @param[in]    	vt				v方向的结束值
 * @param[in]    	major		圆环的major
 * @param[in]    	minor		圆环的minor
 * @param[out]  	face 			返回的面
 * @param[in]		ao 			ACIS 选项
 * @return          outcome 	执行结果
 * @details		有以下情况：
 *						case1：torus为apple型或lemon型：有上下两个奇点
 *							case1.1：uf过小而ut正常
 *								case1.1.1：v方向不闭合，一个loop 三个edge 三个vertex：下奇点、{ut,vf}、{ut,vt}
 *								case1.1.2：v方向闭合，则有两个loop 第一个loop的edge为v闭合曲线 第二个loop只含有一个下奇点
 *							case1.2：uf正常而ut过大
 *								case1.2.1：v方向不闭合，一个loop 三个edge 三个vertex：下奇点、{uf,vf}、{uf,vt}
 *								case1.2.2：v方向闭合，则有两个loop 第一个loop的edge为v闭合曲线 第二个loop只含有一个上奇点
 *							case1.3：uf过小而ut过大
 *								case1.3.1：v方向不闭合，一个loop 两个edge 包含上下两个奇点
 *								case1.3.2：v方向闭合，trface为整个torus面
 *							case1.4：uf和ut都正常
 *								case1.4.1：v方向闭合，两个loop，两个edge为u闭合曲线，两个点
 *								case1.4.2：v方向不闭合，一个loop，四个edge，四个点
 *						case2：torus为vortex型：只有center中心点一个奇点
 *							case2.1：uf过小而ut正常
 *								case2.1.1：v方向不闭合，一个loop 三个edge 三个vertex：中心奇点、{ut,vf}、{ut,vt}
 *								case2.1.2：v方向闭合，则有两个loop 第一个loop的edge为v闭合曲线 第二个loop只含中心奇点
 *							case2.2：uf正常而ut过大
 *								case2.2.1：v方向不闭合，一个loop 三个edge 三个vertex：中心奇点、{uf,vf}、{uf,vt}
 *								case2.2.2：v方向闭合，则有两个loop 第一个loop的edge为v闭合曲线 第二个loop只含中心奇点
 *							case2.3：uf过小而ut过大
 *								case2.3.1：v方向不闭合，一个loop 两个edge为两条u闭合曲线 只包含中心点一个奇点
 *								case2.3.2：v方向闭合，trface为整个torus面
 *							case2.4：uf和ut都正常
 *								case2.4.1：v方向闭合，两个loop，两个edge为两条v闭合曲线，两个点
 *								case2.4.2：v方向不闭合，一个loop，四个edge，四个点
 *						case3：torus为donut型：无奇点
 *							case3.1：u方向上闭合v方向上不闭合 两个loop 两个edge为两条u闭合曲线
 *							case3.2：u方向上不闭合v方向上闭合 两个loop 两个edge为两条v闭合曲线
 *							case3.3：u和v方向上都比和 trface为整个torus面
 *							case3.4：u和v方向上都不闭合 一个loop四个edge四个vertex
 */
DECL_CSTR outcome gme_api_make_trface(const SPAposition& center, const SPAunit_vector& normal, double major, double minor, const SPAposition& pnt, double uf, double ut, double vf, double vt, FACE*& face, AcisOptions* ao = NULL);

/**
 * @brief 根据指定的参数生成一个部分圆环面
 *
 * @details 根据给定的圆环中心位置、圆环法向、圆环外半径长度、圆环环半径长度、投影到圆环所在平面的起点位置、
 * 参数u（环上）的起点和终点（弧度制）、参数v（外环上）的起点和终点（弧度制），生成一个部分圆环面。
 *
 * @param center 圆环中心位置
 * @param normal 圆环法向
 * @param major 圆环外半径长度
 * @param minor 圆环环半径长度
 * @param pnt 投影到center与normal定义的面确定参数起点
 * @param uf 参数u（环上）起点，弧度制
 * @param ut 参数u（环上）终点，弧度制
 * @param vf 参数v（外环上）起点，弧度制
 * @param vt 参数v（外环上）终点，弧度制
 * @param face 返回结果
 * @param ao ACIS选项
 *
 * @return outcome 合法性检验结果
 */
DECL_CSTR outcome gme_1_api_make_trface(const SPAposition& center, const SPAunit_vector& normal, double major, double minor, const SPAposition& pnt, double uf, double ut, double vf, double vt, FACE*& face, AcisOptions* ao = NULL);


/**
* Creates a law face.
* <br><br>
* <b>Role:</b> The law must map two dimensional parameter space (<i>u, v</i>) to three
* dimensional object space (<i>x, y, z</i>). The min and max values specify face
* boundaries in parameter space.
* <br><br>
* <b>Errors:</b> Equal min and max values of the face parameter(s).
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_law
* defining law.
* @param minu
* face min boundary u.
* @param maxu
* face max boundary u.
* @param minv
* face min boundary v.
* @param maxv
* face max boundary v.
* @param face
* face returned.
* @param in_law_number
* for future use.
* @param in_other_laws
* for future use.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_law(
		law *        in_law,
		double       minu,
		double       maxu,
		double       minv,
		double       maxv,
		FACE*&       face,
		int          in_law_number = 0,
		law **       in_other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
 * @brief   		根据law : (u, v) -> (x, y, z) 创建面。
 * @param[in]    	in_law 		定义的law
 * @param[in]  	    minu 		u方向最小边界
 * @param[in]    	maxu 		u方向最大边界
 * @param[in]    	minv 		v方向最小边界
 * @param[in]    	maxv 		v方向最大边界
 * @param[out]  	face 		返回的面
 * @param[in]  	    in_law_number 	未来使用
 * @param[in]  	    in_other_laws 	未来使用
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 * @details			在uv的上下界相等时, 会引发错误
 */
DECL_CSTR outcome gme_api_face_law(
		law *        in_law,
		double       minu,
		double       maxu,
		double       minv,
		double       maxv,
		FACE*&       face,
		int          in_law_number = 0,
		law **       in_other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
* Creates a B-spline face from the given %spline %surface data structure.
* <br><br>
* <b>Role:</b> This API function creates a B-spline face from a %spline %surface data structure,
* passed as an instance of the <tt>splsurf</tt> class.
* <br><br>
* The <tt>splsurf</tt> contains data such as control points, knot vectors, and weights. 
* The two-dimensional grid of control points is contained in a one-dimensional array in which 
* the <i>v</i> index varies first. That is, a row of <i>v</i> control points is specified 
* for the first <i>u</i> value. Then, the row of <i>v</i> control points for the next 
* <i>u</i> value. If the %surface is rational, its weights are ordered the same as its control points.
* <br><br>
* (This API function is functionally equivalent to @href api_mk_fa_spl_ctrlpts.)
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param surf
* %spline %surface data.
* @param face
* B-spline face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_spl_ctrlpts(
		const splsurf* surf,    // spline surface data
		FACE*& face,
		AcisOptions* ao = NULL
	);

/**
 * @brief   		根据给定的样条曲面数据结构创建B样条曲面。
 * @param[in]    	surf 		样条面数据
 * @param[out]  	face 		返回的B样条面
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 */
DECL_CSTR outcome gme_api_face_spl_ctrlpts(
		const splsurf* surf,    // spline surface data
		FACE*& face,
		AcisOptions* ao = NULL
	);


/**
 * @brief   		根据给定的样条曲面数据结构创建B样条曲面。
 * @param[in]    	surf 		样条面数据
 * @param[out]  	face 		返回的B样条面
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 */
DECL_CSTR outcome gme_1_api_face_spl_ctrlpts(
		const splsurf* surf,    // spline surface data
		FACE*& face,
		AcisOptions* ao = NULL
	);

/**
* Creates a <tt>FACE</tt> based upon a B-spline %surface defined by a sequence of control points and knots.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a B-spline %surface of the specified degree in <i>u</i>
* and <i>v</i>. The B-spline %surface is defined by the given sequence of control points and
* knots. This %surface is used to create a <tt>FACE</tt> that spans the entire %surface.
* <br><br>
* If the argument <tt>rational_u</tt> is <tt>TRUE</tt>, the %surface is rational in the <i>u</i>-parameter.
* If <tt>rational_v</tt> is <tt>TRUE</tt> the %surface is rational in the <i>v</i>-parameter.
* <br><br>
* The argument <tt>form_u</tt> specifies whether the %surface is open (0), closed (1), or
* periodic (2) in the <i>u</i> direction. The value of <tt>form_v</tt> specifies the same thing for the
* <i>v</i>-direction.
* <br><br>
* The argument <tt>pole_u</tt> indicates whether or not the %surface has a singularity at
* the <i>u</i>-minimum or <i>u</i>-maximum parameter boundaries according to the following:
* <br><br>
* 0 => no singularity at <i>u</i>-minimum or <i>u</i>-maximum boundary
* <br>
* 1 => has a singularity at the <i>u</i>-minimum boundary
* <br>
* 2 => has a singularity at the <i>u</i>-maximum boundary
* <br>
* 3 => has a singularity at both boundaries
* <br><br>
* The value of <tt>pole_v</tt> indicates the same thing for <i>v</i> parameter boundaries.
* <br><br>
* The control points are contained in the array <tt>ctrlpts</tt>. The <i>v</i> index varies first.
* That is, a row of <i>v</i> control points for the first <i>u</i> value is found first. Then,
* the row of <i>v</i> control points for the next <i>u</i> value. If the %surface is rational in
* either parameter, it is considered a rational %surface and the associated weights
* are in the array <tt>weights</tt>. In ACIS weight values must be positive.
* <br><br>
* The tolerance <tt>point_tol</tt> determines when two control points are identical, and
* <tt>knot_tol</tt> performs the same function for the knot values.
* <br><br>
* Each of the control points should be unique, except possibly the start and end
* points. The knot sequence in <i>u</i> (and <i>v</i>) should form a non-negative,
* non-decreasing sequence with any knot value appearing at most <tt>degree_u</tt>
* (<tt>degree_v</tt>) times. In ACIS all B-spline surfaces interpolate their boundary 
* control points. To achieve this, the end knot multiplicities are either (a) equal to the degree, 
* or (b) equal to the degree plus one. If the end knot multiplicities are equal to the degree, 
* then the number of knots should be equal to the number of control points plus the degree minus one 
* <tt>num_knots = num_crtlpts + degree - 1</tt>. If the end knot multiplicities are equal to the degree 
* plus one, then the number of knots should be equal to the number of control points plus the degree 
* plus one <tt>num_knots = num_crtlpts + degree + 1</tt>.
* No assumption is made about the relationship between parameter values and object space distances; 
* however, it is advantageous for the parameterization to be as homogeneous as possible. 
* (That is, it is advantageous for the parameterization to be somewhat proportional to arclength.)
* In addition, it is advantageous for the parameterization in the two directions be of similar scale.
* ACIS also prefers that surfaces be G<sup>2</sup> continuous; therefore, it may be advantageous to
* limit the knot multiplicities of interior knots to being less than <tt>degree - 2</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param degree_u
* degree in u.
* @param rational_u
* <tt>TRUE</tt> if rational in u.
* @param form_u
* open, closed, periodic in u.
* @param pole_u
* singularity at u-minimum and/or u-maximum.
* @param num_ctrlpts_u
* number of u control points in array.
* @param degree_v
* degree in v.
* @param rational_v
* <tt>TRUE</tt> if rational in v.
* @param form_v
* open, closed, periodic in v.
* @param pole_v
* singularity at v-minimum and/or v-maximum.
* @param num_ctrlpts_v
* number of v control points in array.
* @param ctrlpts
* array of control points.
* @param weights
* array of weights.
* @param point_tol
* identical points if within this tolerance.
* @param num_knots_u
* number of u knots in array.
* @param knots_u
* array of u knots.
* @param num_knots_v
* number of v knots in array.
* @param knots_v
* array of v knots.
* @param knot_tol
* identical knots if within this tolerance.
* @param face
* face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_fa_spl_ctrlpts(
 			int degree_u,					// degree in u
 			logical rational_u,				// TRUE if rational in u
 			int form_u,						// open/closed/periodic in u
 			int pole_u,						// bit-pattern of singularities in u
 			int num_ctrlpts_u,				// number of u control points in array
 			int degree_v,					// degree in v
 			logical rational_v,				// TRUE if rational in v
 			int form_v,						// open/closed/periodic in v
 			int pole_v,						// bit-pattern of singularities in v
 			int num_ctrlpts_v,				// number of v control points in array
 			const SPAposition ctrlpts[],	// array of control points
 			const double weights[],			// array of weights
 			double point_tol,				// identical points if within this tolerance
 			int num_knots_u,				// number of u knots in array
 			const double knots_u[],			// array of u knots
 			int num_knots_v,				// number of v knots in array
 			const double knots_v[],			// array of v knots
 			double knot_tol,				// identical knots if within this tolerance
 			FACE*& face,					// face returned
 			AcisOptions* ao = NULL
	);

/**
* Creates a B-spline face from the given %spline grid data structure.
* <br><br>
* <b>Role:</b> This API function creates a B-spline face from the grid data, which is an array
* of points that represent a grid-like structure and approximate the %surface.
* A B-spline %surface is created by approximating the points on the <tt>grid</tt> to a
* specified tolerance.
* <br><br>
* The <tt>splgrid</tt> contains data such as a grid of points and boundary tangent vectors. 
* The two-dimensional grid of points is contained in a one-dimensional array in which 
* the <i>v</i> index varies first. That is, a row of <i>v</i> points is specified 
* for the first <i>u</i> value. Then, the row of <i>v</i> points for the next 
* <i>u</i> value. Unit tangent vectors can be specified for the boundary conditions 
* for <i>u</i> at the start and at the end of the %surface. 
* <br><br>
* (This API function is functionally equivalent to @href api_mk_fa_spl_fit.)
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param grid
* %spline %surface grid.
* @param face
* B-spline face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_spl_apprx(
		const splgrid* grid,    // spline surface grid
		FACE*& face,
		AcisOptions* ao = NULL
	);

/**
* Creates a <tt>FACE</tt> that represents a B-spline %surface which is a fit to a grid of points on the %surface.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> The <tt>FACE</tt> is a B-spline %surface fitted to an 
* <tt>[num_pts_u ] x  [num_pts_v]</tt> array of points <tt>pts</tt>.
* <br><br>
* The <i>v</i> index varies first. That is, a row of <i>v</i> control points for the first <i>u</i>
* value is found, then the row of <i>v</i> control points for the next <i>u</i> value.
* <br><br>
* Optional arrays of unit tangent vectors can be specified for the boundary
* conditions for <i>u</i> at the start (<tt>du_s</tt>) and at the end (<tt>du_e</tt>) of the %surface. <tt>NULL</tt>
* pointers can be used for the start and end boundary conditions.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param fittol
* fit tolerance.
* @param num_pts_u
* number of points in u.
* @param num_pts_v
* number of points in v.
* @param pts
* array of points.
* @param du_s
* start boundary conditions, length of this optional array of unit-vectors is num_pts_v.
* @param du_e
* end boundary conditions, length of this optional array of unit-vectors is num_pts_v.
* @param face
* face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_fa_spl_fit(
 			double fittol,					// fit tolerance
			int num_pts_u,					// number of points in u
			int num_pts_v,					// number of points in v
 			const SPAposition pts[],		// array of points (u varies first)
 			const SPAunit_vector du_s[],	// start tangent in u
 			const SPAunit_vector du_e[],	// end tangent in u
 			FACE*& face,					// face created
 			AcisOptions* ao = NULL
	);

/**
 * @brief		根据输入的一系列点拟合B-Spline面。
 * @details		pts的长度为[num_pts_u ] x  [num_pts_v]，v方向点优先
 * @param[in]	fittol  	拟合容差
 * @param[in]	num_pts_u	u方向点数量
 * @param[in]	num_pts_v	v方向点数量
 * @param[in]	pts			拟合点数组
 * @param[in]	du_s		开始边界条件，长度为num_pts_v的单位向量数组，代表起始切线向量
 * @param[in]	du_e		结束边界条件，长度为num_pts_v的单位向量数组，代表结束切线向量
 * @param[out]	face		返回创建的面
 * @param[in]	ao			ACIS options
 * @return		函数执行结果
 */
DECL_CSTR outcome gme_api_mk_fa_spl_fit(
			double fittol,					// fit tolerance
			int num_pts_u,					// number of points in u
			int num_pts_v,					// number of points in v
			const SPAposition pts[],		// array of points (u varies first)
			const SPAunit_vector du_s[],	// start tangent in u
			const SPAunit_vector du_e[],	// end tangent in u
			FACE*& face,					// face created
			AcisOptions* ao = NULL
	);

/**
* Creates a B-spline face from the given %spline grid data structure.
* <br><br>
* <b>Role:</b> This API function creates a B-spline face from the grid data, which is an array
* of points that lie on the B-spline %surface and that represent a grid-like structure.
* The B-spline %surface is created by interpolating the points on the <tt>grid</tt>.
* <br><br>
* The <tt>splgrid</tt> contains data such as a grid of points and boundary tangent vectors. 
* The two-dimensional grid of points is contained in a one-dimensional array in which 
* the <i>u</i> index varies first. That is, a row of <i>u</i> points is specified 
* for the first <i>v</i> value. Then, the row of <i>u</i> points for the next 
* <i>v</i> value. Unit tangent vectors can be specified for the boundary conditions 
* for <i>u</i> and <i>v</i> at the start and at the end of the %surface. All boundary 
* conditions must be specified or all must be <tt>NULL</tt>.
* <br><br>
* (This API function is functionally equivalent to @href api_mk_fa_spl_intp.)
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param grid
* %spline %surface grid.
* @param face
* B-spline face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_face_spl_intrp(
		const splgrid* grid,    // spline surface grid
		FACE*& face,
		AcisOptions* ao = NULL
	);

/**
* Creates a <tt>FACE</tt> that represents a B-spline %surface defined by a grid of points on a %surface.
* <br><br>
* <b>Role:</b> This API function creates a B-spline %surface that interpolates a set of
* points. The interpolation scheme is cubic in both the <i>u</i> and <i>v</i> directions.
* <br><br>
* The points are contained in the array <tt>pts</tt>. The <i>u</i> index varies first. That is, a
* row of <i>u</i> control points for the first <i>v</i> value is found, then the row of <i>u</i>
* control points for the next <i>v</i> value.
* <br><br>
* Optional arrays of unit tangent vectors can be specified for the boundary
* conditions for <i>u</i> at the start (<tt>du_s</tt>) and at the end (<tt>du_e</tt>) of the %surface.
* Similarly, <tt>dv_s</tt> and <tt>dv_e</tt> specify the unit tangent conditions for <i>v</i> at the start
* and end. All boundary conditions must be specified or all must be <tt>NULL</tt>.
* Limitation: when fitting data that is singular (start or end row or column of positions the same), the unit tangent vector pointers must all be NULL.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param num_pts_u
* number of points in u.
* @param num_pts_v
* number of points in v.
* @param pts
* array of points.
* @param du_s
* start tangent in u.
* @param du_e
* end tangent in u.
* @param dv_s
* start tangent in v.
* @param dv_e
* end tangent in v.
* @param face
* B-spline face returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_fa_spl_intp(
 			int num_pts_u,					// number of point in u
 			int num_pts_v,					// number of point in v
 			const SPAposition pts[],		// array of points
 			const SPAunit_vector du_s[],	// start tangent in u
 			const SPAunit_vector du_e[],	// end tangent in u
 			const SPAunit_vector dv_s[],	// start tangent in v
 			const SPAunit_vector dv_e[],	// end tangent in v
 			FACE*& face,					// face created
 			AcisOptions* ao = NULL
	);

/**
 * @brief   		创建一个B样条FACE，在u和v方向上都采用三次插值。
 * @param[in]    	num_pts_u u方向点个数
 * @param[in]  	    num_pts_v v方向点个数
 * @param[in]    	pts 控制点数组, 先给出一行u方向的控制点, 然后是下一个v方向的一行u方向控制点。
 * @param[in]    	du_s u方向起始切线单位向量数组，长度等于v方向点个数
 * @param[in]    	du_e u方向结束切线单位向量数组，长度等于v方向点个数
 * @param[in]    	dv_s v方向起始切线单位向量数组，长度等于u方向点个数
 * @param[in]    	dv_e v方向结束切线单位向量数组，长度等于u方向点个数
 * @param[out]  	face 返回创建的FACE
 * @param[in]  	    ao ACIS 选项
 * @details         根据给定参数，创建一个B样条FACE，在u和v方向上都采用三次插值。
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_mk_fa_spl_intp(
      int num_pts_u,                // number of point in u
      int num_pts_v,                // number of point in v
      const SPAposition pts[],      // array of points
      const SPAunit_vector du_s[],  // start tangent in u
      const SPAunit_vector du_e[],  // end tangent in u
      const SPAunit_vector dv_s[],  // start tangent in v
      const SPAunit_vector dv_e[],  // end tangent in v
      FACE*& face,                  // face created
      AcisOptions* ao = NULL);

// Creates a surface that approximates a given surface to a given tolerance
// over the specified parameter range, which must be contained with the 
// parameter range of the given surface.
/**
* Creates a surface that approximates a given surface.
* <br><br>
* <b>Role:</b> Creates a surface that approximates a given surface to a given
* tolerance over the specified parameter range, which must be contained within 
* the parameter range of the given surface. This function is intended for 
* applications performing translation and needing an approximation of the surface.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param in_surface
* given surface.
* @param tol
* tolerance for approximation.
* @param u_range
* u range for returned surface.
* @param v_range
* v range for returned surface.
* @param out_surface
* resulting approximating surface.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_approx_surface(
		const surface* in_surface,		// given surface
		const double tol,				// specified tolerance
		const SPAinterval& u_range,		// specified u-range for returned surface
		const SPAinterval& v_range,		// specified v-range for returned surface
		surface*& out_surface,			// returned surface
		AcisOptions* ao = NULL
	);

/**
 * @brief   		创建一个近似面，近似给定面。
 * @param[in]    	in_surface 给定面
 * @param[in]    	tol 近似容差
 * @param[in]    	u_range u方向范围
 * @param[in]    	v_range v方向范围
 * @param[out]  	out_surface 返回近似面
 * @param[in]  	    ao ACIS 选项
 * @details         创建一个近似面，根据指定的u和v范围，近似给定面。
 * @return          outcome 执行结果
 * @todo			平面取任意轴方向的情况（demo1）
 * @todo			锥面u方向范围异常（demo2）
 * @todo			球面近似结果与ACIS不一致（demo4）
 * @todo			锥面、圆环面测试未通过（测试case3,4,5）
 */
DECL_CSTR outcome gme_api_make_approx_surface(
		const surface* in_surface,		// given surface
		const double tol,				// specified tolerance
		const SPAinterval& u_range,		// specified u-range for returned surface
		const SPAinterval& v_range,		// specified v-range for returned surface
		surface*& out_surface,			// returned surface
		AcisOptions* ao = NULL
	);

/*! @} */
/*! \addtogroup CSTRMAKEEDGEAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */
//============================================================
// Curve creation

/**
* Creates a linear edge, given its vertex positions.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates and returns a straight edge with start
* and end vertices at the positions <tt>pt1</tt> and <tt>pt2</tt>.  The geometry
* supporting the edge is a <tt>STRAIGHT</tt>`, except if the end points coincide in
* which case the geometry becomes NULL and a warning is created.
* <br><br>
* (This API function is functionally equivalent to @href api_mk_ed_line.)
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pt1
* position of the start vertex.
* @param pt2
* position of the end vertex.
* @param line
* linear edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_line(
		const SPAposition& pt1,		// start of line
		const SPAposition& pt2,		// end of line
		EDGE*& line,				// line created
		AcisOptions* ao = NULL
	);

// Create a line tangent to two curves or through a position and tangent
// to a curve
/**
* Creates a line tangent to two curves or through a position and tangent to a %curve.
* <br><br>
* <b>Role:</b> In this API function, either <tt>pt1</tt> or <tt>eray1</tt> is <tt>NULL</tt>, and either <tt>pt2</tt> or
* <tt>eray2</tt> is <tt>NULL</tt>. If both <tt>pt1</tt> and <tt>pt2</tt> are non-<tt>NULL</tt>, this API function creates 
* a line between the two positions. If one of the positions is non-<tt>NULL</tt> and the other is <tt>NULL</tt>,
* this function creates a line from the given position and tangent to the given %curve.
* If both positions are <tt>NULL</tt>, and both <tt>entity_with_rays</tt> are non-<tt>NULL</tt>, this function 
* creates a line tangent to the two curves.
* <br><br>
* The ray portion of the <tt>entity_with_ray</tt> determines the tangent point to use if
* there is more than one and also determines the start point for computing the
* tangent point.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pt1
* start position or <tt>NULL</tt>.
* @param eray1
* first %curve plus tangent guess or <tt>NULL</tt>.
* @param pt2
* end position or <tt>NULL</tt>.
* @param eray2
* second %curve plus tangent guess or <tt>NULL</tt>.
* @param line
* linear edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_line_tangent(
		const SPAposition* pt1,			// start position or NULL
		const entity_with_ray* eray1,	// first curve + tangent guess (or NULL)
		const SPAposition* pt2,			// end position or NULL
		const entity_with_ray* eray2,	// second curve + tangent guess (or NULL)
		EDGE*& line,					// line created
		AcisOptions* ao = NULL
	);

/**
* Creates a linear edge, given its vertex positions.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates and returns a straight edge with start
* and end vertices at the positions <tt>start_point</tt> and <tt>end_point</tt>.  The geometry
* supporting the edge is a <tt>STRAIGHT</tt>.
* <br><br>
* (This API function is functionally equivalent to @href api_curve_line.)
* <br><br>
* <b>Errors:</b> The distance between the start and end points is less than <tt>SPAresabs</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param start_point
* position of the start vertex.
* @param end_point
* position of the end vertex.
* @param line
* linear edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_line(
			const SPAposition& start_point,	// start point
			const SPAposition& end_point,	// end point
			EDGE*& line,					// edge constructed
			AcisOptions* ao = NULL
	);
/**
 * @brief Creates a linear edge, given its vertex positions.
 * @param[in] start_point	position of the start vertex.
 * @param[in] end_point	position of the end vertex.
 * @param[out] line linear edge returned.
 * @param[in] ao	ACIS options.
 * @return outcome edge created.
 */
DECL_KERN outcome gme_api_mk_ed_line(const SPAposition& start_point, const SPAposition& end_point, EDGE*& line, AcisOptions* ao = NULL);

/**
 * @brief Creates a linear edge, given its vertex positions.
 * @param[in] start_point	position of the start vertex.
 * @param[in] end_point	position of the end vertex.
 * @param[out] line linear edge returned.
 * @param[in] ao	ACIS options.
 * @return outcome edge created.
 */
DECL_KERN outcome gme_1_api_mk_ed_line(const SPAposition& start_point, const SPAposition& end_point, EDGE*& line, AcisOptions* ao = NULL);

/**
 * @brief Creates a linear edge, given its vertex positions.
 * @param[in] start_point	position of the start vertex.
 * @param[in] end_point	position of the end vertex.
 * @param[out] line linear edge returned.
 * @param[in] ao	ACIS options.
 * @return outcome edge created.
 */
DECL_KERN outcome gme_2_api_mk_ed_line(const SPAposition& start_point, const SPAposition& end_point, EDGE*& line, AcisOptions* ao=NULL);
/**
* Creates a circular arc edge given the center, radius, and start and end angles.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates a circular arc parallel to the <i>xy</i>-plane of the active
* WCS, given a <tt>center</tt>, a <tt>radius</tt>, a <tt>start_angle</tt>, and an <tt>end_angle</tt>.
* The direction of the %curve is counter clockwise. The edge has the same direction as the %curve.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param center
* center of the arc.
* @param radius
* radius of the arc.
* @param start_angle
* start angle in radians.
* @param end_angle
* end angle in radians.
* @param arc
* arc edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_arc(
		const SPAposition& center, // center of arc
		double radius,             // radius of arc
		double start_angle,        // start angle in radians
		double end_angle,          // end angle in radians
		EDGE*& arc,                // arc created
		AcisOptions* ao = NULL
	);

/**
* Creates a circle edge or circular arc edge through three positions.
* <br><br>
* <b>Role:</b> This API function creates an edge as an arc passing through three locations. <tt>pt1</tt>
* specifies a starting position and, with the <i>x</i>-axis, defines the arc's start
* angle. <tt>pt2</tt> specifies a the second position. <tt>pt3</tt> specifies the end position. <tt>full</tt>
* specifies whether the arc is a complete or partial circle.
* The edge has the same direction as the underlying ellipse %curve.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param pt1
* first position.
* @param pt2
* second position.
* @param pt3
* third position.
* @param full
* <tt>TRUE</tt> (full circle) or <tt>FALSE</tt> (circular arc).
* @param arc
* arc edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_arc_3pt(
		const SPAposition& pt1,    // first position
		const SPAposition& pt2,    // second position
		const SPAposition& pt3,    // third position
		logical full,              // == TRUE to get a full circle
		EDGE*& arc,                // arc created
		AcisOptions* ao = NULL
	);

// Create a circle or circular arc given a center and two edge points
//    If the optional SPAunit_vector* norm is not NULL, then the arc is
//  created in the plane defined by center and norm.  pt1 and pt2 are
//  projected onto this plane to determine the start and end of the
//  arc.
//    If a normal is not given, then the arc is created in the plane
//  defined by the first of the following cases which defines a valid
//  plane normal vector:
//    1. (pt1-center)*(pt2-center)         ( plane defined by points )
//    2. ((pt1-center)*zaxis)*(pt1-center) ( usually XY plane of active WCS)
//    3. ((pt1-center)*yaxis)*(pt1-center) ( XZ plane of active WCS)
//  where zaxis and yaxis are the z and y axes of the active WCS
//    If pt2 == pt1, a full circle is created.
/**
* Creates a circular or circular arc edge given the center and two end positions.
* <br><br>
* <b>Role:</b> This API function creates a circular edge or circular arc edge, given the center
* and two end positions. If the optional <tt>norm</tt> is non-<tt>NULL</tt>, the arc is created in the %plane
* defined by <tt>center</tt> and <tt>norm</tt>. The projections of <tt>pt1</tt> and <tt>pt2</tt> onto this %plane
* determine the start and end of the arc. If <tt>norm</tt> is not specified, the arc is
* created in the %plane defined by the first of the following cases that defines a
* valid %plane normal vector (where <tt>zaxis</tt> and <tt>yaxis</tt> are the <i>z</i>-axis and <i>y</i>-axis of
* the active WCS):
* <br><br>
* 1. The %plane defined by points.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;(pt1-center) * (pt2-center)</tt>
* <br><br>
* 2. (Usually) the <i>xy</i>-plane of active WCS.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;((pt1-center) * zaxis) * (pt1-center)</tt>
* <br><br>
* 3. The <i>xz</i>-plane of active WCS.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;((pt1-center) * yaxis) * (pt1-center)</tt>
* <br><br>
* If <tt>pt1</tt> equals <tt>pt2</tt>, this function creates a full circle.
* The distance from the center point, <tt>center</tt>, to the first point on the arc, <tt>pt1</tt>, 
* defines the radius of the arc. The second point on the arc, <tt>pt2</tt>, is used to trim the arc, 
* not to define the radius of the arc.
* The direction of the %curve is counter clockwise. The edge has the same direction as the %curve.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param center
* center position.
* @param pt1
* start position.
* @param pt2
* end position.
* @param norm
* optional arc %plane normal or <tt>NULL</tt>.
* @param arc
* arc edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_arc_center_edge(
		const SPAposition& center,    // center position
		const SPAposition& pt1,       // start position
		const SPAposition& pt2,       // end position
		const SPAunit_vector* norm,   // optional normal vector or NULL
		EDGE*& arc,                 // the arc created
		AcisOptions* ao = NULL
	);


/** 
* @brief		根据中心和两个边缘点生成一段圆弧
* @param[in]  center	圆弧所在圆的圆心
* @param[in]  pt1		圆弧初始位置
* @param[in]  pt2		结束位置
* @param[in]  norm		圆弧所在圆的法向量
* @param[out] arc		生成的圆弧
* @details		若norm参数不为NULL，则先以center和norm生成一个面，再将pt1和pt2投射到生成的面上形成pt1'
*				和pt2'，最后在面上以center，pt1'和pt2'生成一段逆时针圆弧。
*				若norm参数为NULL，则以center,pt1和pt2生成一段逆时针的圆弧。此时应依次选择以下式子生成
*				平面法向量，直到有式子能够生成合法的平面法向量为止：
*				1.通常情况：(pt1-center) * (pt2-center)
*				2.xy平面的活跃WCS：((pt1-center) * zaxis) * (pt2-center)
*				3.xz平面的活跃WCS：((pt1-center) * yaxis) * (pt2-center)
*				特别地：若pt1 = pt2，则此函数生成一个完整的圆。
*				注意：
*				1.生成圆的过程实际上是生成一个离心率为1的椭圆。
*				2.生成的圆的半径等于center到pt1的距离，pt2仅用于修剪(trim)。	
* 		处理情况1: 重合点检查（调用check系列函数）
* 		处理情况2: 若输入参数pt1=pt2（包括pt1、pt2、center共线的情况），则创建整圆
* 		处理情况3: 若输入参数norm=NULL，则创建的edge所在平面由center、pt1、pt2确定
* @return          outcome 执行结果			
**/
DECL_CSTR outcome gme_api_curve_arc_center_edge(
		const SPAposition& center,    // center position
		const SPAposition& pt1,       // start position
		const SPAposition& pt2,       // end position
		const SPAunit_vector* norm,   // optional normal vector or NULL
		EDGE*& arc,                 // the arc created
		AcisOptions* ao = NULL
	);


/**
* Creates a circular edge or a circular arc edge given two points on the diameter.
* <br><br>
* <b>Role:</b> This API function creates a full or partial arc passing through two
* positions. The diameter of the arc is defined by the start and end positions.
* <tt>full</tt> determines whether the arc is complete or partial. The arc is created in
* the %plane defined by the first of the following cases that defines a valid plane
* normal vector (where <tt>zaxis</tt> and <tt>yaxis</tt> are the <i>z</i>-axis and <i>y</i>-axis of the active
* WCS):
* <br><br>
* 1. The %plane defined by points.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;(pt1-center) * (pt2-center)</tt>
* <br><br>
* 2. (Usually) the <i>xy</i>-plane of active WCS.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;((pt1-center) * zaxis) * (pt1-center)</tt>
* <br><br>
* 3. The <i>xz</i>-plane of active WCS.
* <br>
* <tt>&nbsp;&nbsp;&nbsp;&nbsp;((pt1-center) * yaxis) * (pt1-center)</tt>
* <br>
* The direction of the %curve is counter clockwise. The edge has the same direction as the %curve.
* <br><br>
* <b>Errors:</b> The two given positions, <tt>pt1</tt> and <tt>pt2</tt>, are equal.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pt1
* first point on the diameter.
* @param pt2
* second point on the diameter.
* @param full
* <tt>TRUE</tt> (full circle) or <tt>FALSE</tt> (circular arc).
* @param arc
* arc edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_arc_diagonal(
		const SPAposition& pt1,    // first point on diagonal
		const SPAposition& pt2,    // second point on diagonal
		logical full,              // == TRUE to create full circle
		EDGE*& arc,                // the arc created
		AcisOptions* ao = NULL
	);

/**
 * @brief   	  创建一段圆弧或部分圆弧
 * @param[in]	  pt1 输入直径上的第一个点
 * @param[in]	  pt2 输入直径上的第二个点
 * @param[in]	  full 判断绘制完整圆弧还是部分圆弧
 * @param[out]	  arc 输出创建的圆弧
 * @param[in]  	  ao ACIS 选项
 * @details       直径上给定两个点创建逆时针圆弧，通过full参数指定是否创建完整圆，测试不同点绘制完整或部分圆弧
 *				处理情况1：检查两个点之差是否小于容差（调用check函数）
 *				处理情况2：full为TURE 根据给定直径上的两点绘制完整圆弧
 *				处理情况3：full为FALSE 根据给定直径上的两点绘制部分圆弧
 * @note		1.通过the xy-plane of active WCS：((pt1-center) * zaxis) * (pt1-center)确定法向量方向
 *				2.两点不能相等（ACIS文档描述），gme接口通过两点间距是否小于容差判断两点是否相等
 *				测试矛盾1：acis并不是通过两点间距离是否在容差内判断两点是否相等
 *						   经测试发现，acis在两点距离小于sqrt3 * 1e-6时（目前没有更精确测试acsi的判断边界值），开始报错Coincident points
 *				测试矛盾2：且当调用acis接口绘制半圆时，第二个点pt2的坐标值会被改变，但在两点间距sqrt3 * 1e-4的情况下same_edge可通过，即变化差值可能仍在容差内
 *				测试矛盾3：当两点间距在sqrt3 * 1e-5的情况下，acis接口崩溃，指定full参数为1绘制圆但结果仍绘制半圆，第二个点pt2坐标值被改变，
 *						   且在此范围内acis绘制半圆的情况也无法通过same_edge，应该是pt2值变化范围超出容差
 *				注：目前两个接口在两点间距大于sqrt3 * 1e-4和小于容差的情况下same_edge均可通过，在此范围内有上述问题
 *					关于矛盾1，我的理解是acis可能提高两点间距判断边界值以避免绘制直径小于sqrt3 * 1e-4的圆
 *					关于矛盾2，我猜测acis的此接口可能进行其他操作而改变了第二个点的坐标值，且此操作改变pt2的范围与半径长度呈负相关，即半径越小，pt2坐标值被改变越多，在qrt3 * 1e-5时无法通过same_edge检查
 *					关于矛盾3，我认为可能acis的其他操作在两点间距在qrt3 * 1e-5时出现bug，导致acis接口在此范围无法绘制一个完整的圆
 *					以上结果均为保存对比edge的SAT文件得出
 *					在demo中，两点间距为sqrt3 * 1e-2绘制的圆几乎只是一个小点，因此无法通过demo观测间距sqrt3 * 1e-5时 acis接口只画半圆的bug
 * @return        函数执行结果
 */
DECL_CSTR outcome gme_api_curve_arc_diagonal(
		const SPAposition& pt1,		//	直径的第一个点
		const SPAposition& pt2,		//直径的第二个点
		logical full,				//判断是否绘制完整圆弧
		EDGE*& arc,					//输出创建的圆弧
		AcisOptions* ao = NULL);

/**
* Creates a circular edge tangent to three curves.
* <br><br>
* <b>Role:</b> This API function creates an edge defined by a circular arc tangent to
* three given curves approximately at those points specified by <tt>pick_ray</tt> inputs,
* together with a specification whether the desired result is a full circle.
* The edge has the same direction as the underlying ellipse %curve.
* <br><br>
* <b>Errors:</b> The three curves must all lie in a common %plane.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param crv1
* first %curve plus a <tt>pick_ray</tt> specifying the approximate tangent location.
* @param crv2
* second %curve plus a <tt>pick_ray</tt> specifying the approximate tangent location.
* @param crv3
* third %curve plus a <tt>pick_ray</tt> specifying the approximate tangent location.
* @param full
* <tt>TRUE</tt> (full circle) or <tt>FALSE</tt> (circular arc).
* @param arc
* arc edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_arc_3curve(
		const entity_with_ray& crv1,    // first curve + approximate tangent
		const entity_with_ray& crv2,    // second curve + approximate tangent
		const entity_with_ray& crv3,    // third curve + approximate tangent
		logical full,                   // == TRUE for full circle
		EDGE*& arc,						// circle created
		AcisOptions* ao = NULL
	);

/**
* Creates a fillet edge between two curves.
* <br><br>
* <b>Role:</b> This API function creates an edge defined by a circular arc of the given
* <tt>radius</tt> tangent to the two curves, <tt>crv1</tt> and <tt>crv2</tt>. Each curve may optionally be
* trimmed at the tangent point. The selection rays determine the portions of the entities that remain: 
* it is recommended that the origin of each selection ray is on the curve and the ray direction is not tangent to the curve at that location.
* The new edge is tangent to the entities. If <tt>trim1</tt> or <tt>trim2</tt> is <tt>FALSE</tt>, 
* the corresponding input curve is not trimmed; if the value is <tt>TRUE</tt>, the %curve is trimmed to the fillet. Only
* fillets less than or equal to 180 degrees are created.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param crv1
* first %curve and the approximate tangent location.
* @param crv2
* second %curve and the approximate tangent location.
* @param radius
* fillet radius.
* @param trim1
* whether to trim first %curve.
* @param trim2
* whether to trim second %curve.
* @param arc
* fillet edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_fillet(
		const entity_with_ray& crv1, // first curve + approximate tangent location
		const entity_with_ray& crv2, // second curve + approximate tangent location
		double radius,               // fillet radius
		logical trim1,               // request to trim first curve
		logical trim2,               // request to trim second curve
		EDGE*& arc,                  // fillet created
		AcisOptions* ao = NULL
	);

/**
* Creates an elliptical edge parallel to the <i>xy</i>-plane of the active working coordinate system.
* <br><br>
* <b>Role:</b> This API function creates an edge that represents a bounded elliptical
* %curve with the specified <tt>center</tt>, position on major axis (<tt>pt1</tt>), and <tt>ratio</tt>. By
* default, the direction of the edge is always in the direction indicated by the
* right-hand rule relative to the normal. To create either a full or partial ellipse,
* specify <tt>start_angle</tt> and <tt>end_angle</tt> in radians. The difference between
* <tt>end_angle</tt> and <tt>start_angle</tt> must be greater than <tt>0.0</tt> and 
* less than or equal to <tt>2 * pi</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param center
* center of the ellipse.
* @param major
* position on ellipse on major axis.
* @param ratio
* ratio between the ellipse major and minor radii.
* @param start_angle
* start angle in radians.
* @param end_angle
* end angle in radians.
* @param ell
* elliptical edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_ellipse(
		const SPAposition& center,	// center of the ellipse
		const SPAposition& major,	// position on ellipse on major axis
		double ratio,				// ratio between major and minor axis length
		double start_angle,			// end angle in radians
		double end_angle,			// start angle in radians
		EDGE*& ell,                 // ellipse created
		AcisOptions* ao = NULL
	);

/**
* Creates an <tt>EDGE</tt> that represents a bounded elliptical arc.
* <br><br>
* <b>Role:</b> Creates the underlying <tt>ELLIPSE</tt> with the specified center, normal, major axis,
* and radius ratio. 
* <br><br>
* By default, the direction of the <tt>ELLIPSE</tt> is always in the direction indicated by
* the right hand rule relative to the normal.
* <br><br>
* The start and end angles (measured in radians) specify the start and end points
* of the elliptical arc. They are used to create vertices on the edge. The difference between
* <tt>end_angle</tt> and <tt>start_angle</tt> must be greater than <tt>0.0</tt> and 
* less than or equal to <tt>2 * pi</tt>.
* <br><br>
* <dl>
* <b>Errors:</b> Zero length normal vector.
* <dd>&nbsp;Zero length major axis.</dd>
* <dd>&nbsp;Major axis not perpendicular to normal vector.</dd>
* <dd>&nbsp;Radius ratio less than <tt>SPAresabs</tt> or greater than 1.0.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* center of arc.
* @param normal
* normal.
* @param major_axis
* major axis of ellipse.
* @param radius_ratio
* ratio of lengths of minor axis to major axis of the ellipse.
* @param start_angle
* starting angle of arc ( in degrees ) in relation to the major axis.
* @param end_angle
* ending angle of arc ( in degrees ) in relation to the major axis.
* @param ell
* edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_ellipse(
			const SPAposition& center,		// centre
			const SPAunit_vector& normal,	// normal
			const SPAvector& major_axis,	// major axis
			double radius_ratio,			// ratio of major to minor radii
			double start_angle,				// starting angle of arc
			double end_angle,				// ending angle of arc
			EDGE*& ell,					// edge constructed
			AcisOptions* ao = NULL
	);

/**
* Creates a B-spline edge defined by a conic section.
* <br><br>
* <b>Role:</b> Creates a B-spline edge from a conic, where <tt>rho</tt> determines the
* type of conic.  If <tt>rho = 0.5</tt>, the edge is parabolic.  If it is less than 0.5,
* the conic is a segment of an %ellipse, becoming more and more flattened as <tt>rho</tt>
* tends toward 0.0.  If <tt>rho > 0.5</tt>, the conic is a segment of one branch of a hyperbola, with an
* increasingly sharp bend near the tangent intersection point as <tt>rho</tt> nears 1.0.
* <br><br>
* For more information on the definition of <tt>rho</tt> refer to the 
* <i>[Conic Sections](http://doc.spatial.com/articles/c/u/r/Curve.html#Conic_Sections)</i>
* section of the Technical Article <i>[Curve](http://doc.spatial.com/articles/c/u/r/Curve.html)</i>.
* <br><br>
* <b>Errors:</b> Start/end tangents are collinear or parallel (fail to intersect)
* <br><br>
* <b>Limitations:</b> Cannot make ellipses whose angular extent is 180 degrees or more.
* The B-spline %curve is always rational, even though parabolas do not need to be rational.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param start
* start point of conic.
* @param start_tan
* tangent at start point.
* @param end
* end point of conic.
* @param end_tan
* tangent at end point.
* @param rho
* type of conic (0 &lt; rho &lt; 1.0).
* @param edge
* conic edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_conic(
			const SPAposition& start,			// start position
			const SPAunit_vector& start_tan,	// start tangent
			const SPAposition& end,				// end position
			const SPAunit_vector& end_tan,		// end tangent
			double rho,							// rho (0.0 < rho < 1.0)
			EDGE*& edge,						// resulting edge
			AcisOptions* ao = NULL
	);

/** 
* @brief           根据起点、终点及曲线在这两处的方向以及ρ，生成一个包含一段圆锥曲线的edge
* @param[in]       start  曲线起点的位置
* @param[in]       start_tan  曲线起点的方向
* @param[in]       end  曲线终点的位置
* @param[in]       end_tan  曲线终点的方向
* @param[in]       rho  控制曲线的形状与种类（若ρ=0.5，曲线对应抛物线的一部分，ρ<0.5对应椭圆，ρ>0.5对应双曲线）
* @param[out]      edge  生成的edge
* @return          执行结果
* @see             api_mk_ed_bs3_curve,由bs3_curve生成edge
* @see             bs3_curve_make_rho_conic,由三个点和ρ生成bs3_curve
**/
DECL_CSTR outcome gme_api_mk_ed_conic(
			const SPAposition& start,			// 起点
			const SPAunit_vector& start_tan,	// 起点方向
			const SPAposition& end,				// 终点
			const SPAunit_vector& end_tan,		// 终点方向
			double rho,							// ρ (0.0 < rho < 1.0)
			EDGE*& edge,						// 返回的edge
			AcisOptions* ao = NULL
	);


/** 
* @brief			根据起点、终点的位置及方向构造一条圆锥曲线，曲线在这两处的方向以及ρ，生成一个包含一段圆锥曲线的edge
* @param[in]       start  曲线起点的位置
* @param[in]       start_tan  曲线起点的方向
* @param[in]       end  曲线终点的位置
* @param[in]       end_tan  曲线终点的方向
* @param[in]       rho  控制曲线的形状与种类（若ρ=0.5，曲线对应抛物线的一部分，ρ<0.5对应椭圆，ρ>0.5对应双曲线）
* @param[out]      edge  生成的edge
* @return          函数执行结果
* @details			根据起点终点及其切线方向确定切线交点，随后使用起点、终点、交点、ρ 生成B样条曲线，该样条曲线即为所求的圆锥曲线
*					处理情况1：检查两个点之差是否小于容差（调用same_point函数），若小于容差则抛出API_FAILED
*					处理情况2：检查切线是否为0，为0则抛出API_FAILED
*					处理情况3：检查ρ是否满足在区间内，0 < ρ < 1，否则抛出VALUE_OUT_RANGE
*					处理情况4：检查切线和两点连线是否平行，平行则抛出API_FAILED
*					处理情况5：（ACIS文档描述）检查切线能否相交，即：是否在一个平面内。若不能相交则抛出API_FAILED
* @see             bs3_curve_make_rho_conic,由三个点和ρ生成bs3_curve
* @see             api_mk_ed_bs3_curve,由bs3_curve生成edge
**/
DECL_CSTR outcome gme_1_api_mk_ed_conic(
			const SPAposition& start,			// 起点
			const SPAunit_vector& start_tan,	// 起点切线方向
			const SPAposition& end,				// 终点
			const SPAunit_vector& end_tan,		// 终点切线方向
			double rho,							// ρ (0.0 < rho < 1.0)
			EDGE*& edge,						// 返回的edge
			AcisOptions* ao = nullptr			// ACIS参数设置
	);


/**
 * Creates an edge that is a helix.
 * <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
 * <br><br>
 * <b>Role:</b> Creates a helical edge along an axis specified by a start position and an end position.
 * The <tt>start_dir</tt> and <tt>radius</tt> arguments specify where the edge
 * starts in relation to the <tt>axis_start</tt> position. The <tt>thread_distance</tt>
 * argument specifies how close together the turns of the helix are spaced. The
 * <tt>right_handed</tt> argument specifies either a right-hand or left-hand twist.
 * <br><br>
 * <b>Effect:</b> Changes model
 * <br><br>
 * <b>Journal: </b> Available
 * <br><br>
 * <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param axis_start
 * axis start position.
 * @param axis_end
 * axis end position.
 * @param start_dir
 * vector from axis_start to helix start.
 * @param radius
 * radius of helix.
 * @param thread_distance
 * distance between threads along axis.
 * @param right_handed
 * <tt>TRUE</tt> is right-handed, <tt>FALSE</tt> is left-handed.
 * @param hlx
 * helical edge returned.
 * @param ao
 * ACIS options.
 **/
DECL_CSTR outcome api_edge_helix(
    const SPAposition	&axis_start,
	const SPAposition	&axis_end,
	const SPAvector     &start_dir,
	double		radius,
	double		thread_distance,
	logical		right_handed,	  
    EDGE		*&hlx,
    AcisOptions *ao = NULL);

/**
* Creates an edge from a spiral definition.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates an Archimedian spiral edge. This implies that
* the radius expands at a constant rate. The resulting <tt>edge</tt> is perpendicular to
* the normal axis specified by the <tt>center</tt> and <tt>normal</tt> arguments.
* The resulting edge has an underlying intcurve that is based upon a law; that is,
* it is a procedural %curve not a B-spline %curve. 
* <br><br>
* The <tt>edge</tt> returned has information associated with it that indicates where the
* axis of the spiral is located. If the edge is then swept, a rail law is created
* that orients the profile relative to the center axis, rather than using a
* minimum rotation rail. This improves the speed of sweeping, and results in the
* intuitive sweeping of a spiral.
* <br><br>
* The <tt>start_position</tt> is the position where the
* spiral will start. It should be noted that the resulting edge will be perpendicular to the
* axis, but will not necessarily be in the %plane of the center position, depending
* on the starting position specified.
* <br><br>
* The rate at which the spiral expands is specified with the <tt>width</tt> argument. The
* width is the perpendicular distance between consecutive loops of the spiral. The
* <tt>angle</tt> argument specifies how many revolutions the spiral should make, in radians.
* <br><br>
* The optional argument <tt>right_handed</tt> determines whether the direction of movement is
* right handed or left handed with respect to the normal vector. The default of
* <tt>TRUE</tt> is specifies right-handed.
* <br><br>
* The optional argument <tt>start_radius</tt> allows a specification of the start point at
* a desired distance in the start direction. One use for this argument would be to
* specify a zero start radius so that the spiral begins at the center.
* <br><br>
* Refer to the documentation of the Scheme extension <tt>edge:spiral</tt> in the
* Constructors component for illustrations and examples.
* <br><br>
* <b>Errors:</b> Specifying a starting position or direction on the normal axis.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* start of normal axis.
* @param normal
* normal axis.
* @param start_position
* starting position of spiral.
* @param width
* distance between loops.
* @param angle
* radians turned.
* @param spiral
* spiral edge returned.
* @param right_handed
* right or left handed
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_spiral(
			SPAposition& center,
			SPAvector& normal,
			SPAposition& start_position,
			double width,
			double angle,
			EDGE*& spiral,
			logical right_handed = TRUE,
			AcisOptions* ao = NULL
	);
/**
 * @brief   		根据给定轴心和方向，按照给定的间距和长度创建螺线
 * @param[in]    	center 轴中心点
 * @param[in]  	    normal 轴法向量
 * @param[in]    	start_position 螺线起始位置点
 * @param[in]		width 每圈螺线间距
 * @param[in]		angle 螺线延伸长度，单位rad
 * @param[out]  	spiral 返回螺线edge
 * @param[in]		right_handed 螺线旋转方向
 * @param[in]  	    ao ACIS 选项
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_edge_spiral(
			SPAposition& center,			//轴中心
			SPAvector& normal,				//轴法向量
			SPAposition& start_position,	//螺线起始位置
			double width,					//螺线间距
			double angle,					//螺线延伸长度
			EDGE*& spiral,					//返回的EDGE
			logical right_handed = TRUE,	//螺线旋转方向
			AcisOptions* ao = NULL
	);

/**
 * @brief   		根据给定轴心和方向，按照给定的间距和长度创建螺线
 * @param[in]    	center 轴中心点
 * @param[in]  	    normal 轴法向量
 * @param[in]    	start_position 螺线起始位置点
 * @param[in]		width 每圈螺线间距
 * @param[in]		angle 螺线延伸长度，单位rad
 * @param[out]  	spiral 返回螺线edge
 * @param[in]		right_handed 螺线旋转方向
 * @param[in]  	    ao ACIS 选项
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_1_api_edge_spiral(
			SPAposition& center,			//轴中心
			SPAvector& normal,				//轴法向量
			SPAposition& start_position,	//螺线起始位置
			double width,					//螺线间距
			double angle,					//螺线延伸长度
			EDGE*& spiral,					//返回的EDGE
			logical right_handed = TRUE,	//螺线旋转方向
			AcisOptions* ao = NULL
	);


/**
 * @brief   		根据给定轴心和方向，按照给定的间距和长度创建螺线
 * @param[in]    	center 轴中心点
 * @param[in]  	    normal 轴法向量
 * @param[in]    	start_position 螺线起始位置点
 * @param[in]		width 每圈螺线间距
 * @param[in]		angle 螺线延伸长度，单位rad
 * @param[out]  	spiral 返回螺线edge
 * @param[in]		right_handed 螺线旋转方向
 * @param[in]  	    ao ACIS 选项
 * @return          outcome 执行结果
 * @detail			case1：参数合法性检查（调用check系列函数）
 *					case2：如果edge两个端点在容差范围内，则构造一个闭合曲线
 *					case3：否则，构造一条open曲线
 */
 DECL_CSTR outcome gme_2_api_edge_spiral(SPAposition& center,          // 轴中心
                                        SPAvector& normal,            // 轴法向量
                                        SPAposition& start_position,  // 螺线起始位置
                                        double width,                 // 螺线间距
                                        double angle,                 // 螺线延伸长度
                                        EDGE*& spiral,                // 返回的EDGE
                                        logical right_handed = TRUE,  // 螺线旋转方向
                                        AcisOptions* ao = NULL
	);

  /**
* Creates an edge from a spiral definition.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates an Archimedian spiral edge. This implies that
* the radius expands at a constant rate. The resulting <tt>edge</tt> is perpendicular to
* the normal axis specified by the <tt>center</tt> and <tt>normal</tt> arguments.
* The resulting edge has an underlying intcurve that is based upon a law; that is,
* it is a procedural %curve not a B-spline %curve. 
* <br><br>
* The <tt>edge</tt> returned has information associated with it that indicates where the
* axis of the spiral is located. If the edge is then swept, a rail law is created
* that orients the profile relative to the center axis, rather than using a
* minimum rotation rail. This improves the speed of sweeping, and results in the
* intuitive sweeping of a spiral.
* <br><br>
* The <tt>start_direction</tt> is a vector specifying an offset from the
* center. It should be noted that the resulting edge will be perpendicular to the
* axis, but will not necessarily be in the %plane of the center position, depending
* on the starting direction specified.
* <br><br>
* The rate at which the spiral expands is specified with the <tt>width</tt> argument. The
* width is the perpendicular distance between consecutive loops of the spiral. The
* <tt>angle</tt> argument specifies how many revolutions the spiral should make, in radians.
* <br><br>
* The optional argument <tt>right_handed</tt> determines whether the direction of movement is
* right handed or left handed with respect to the normal vector. The default of
* <tt>TRUE</tt> specifies right-handed.
* <br><br>
* The optional argument <tt>start_radius</tt> allows a specification of the start point at
* a desired distance in the start direction. One use for this argument would be to
* specify a zero start radius so that the spiral begins at the center.
* <br><br>
* Refer to the documentation of the Scheme extension <tt>edge:spiral</tt> in the
* Constructors component for illustrations and examples.
* <br><br>
* <b>Errors:</b> Specifying a starting position or direction on the normal axis.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param center
* start of normal axis.
* @param normal
* normal axis.
* @param start_direction
* spiral start direction.
* @param width
* distance between loops.
* @param angle
* radians turned.
* @param spiral
* spiral edge returned.
* @param right_handed
* right or left handed.
* @param start_radius
* length out start direction.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_spiral(
			SPAposition& center,
			SPAvector& normal,
			SPAvector& start_direction,
			double width,
			double angle,
			EDGE*& spiral,
			logical right_handed = TRUE,
			double start_radius = -1.0,
			AcisOptions* ao = NULL
	);

/**
* Creates an edge from a helical spring definition.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function combines several helix pieces into a "spring"
* edge. Transition pieces between the helix pieces ensure G<sup>2</sup> continuity. The final
* edge consists of a helix followed by zero or more transition/helix pairs. The
* resulting "spring" edge is returned in <tt>spring</tt>.
* <br><br>
* The <tt>EDGE</tt> returned has information associated with it that indicates where the
* axis of the helix is located. If the edge is then swept, a rail law is created
* that orients the profile relative to the center axis, rather than using a
* minimum rotation rail. This improves the speed of sweeping, and results in the
* intuitive sweeping of a spring.
* <br><br>
* The <tt>axis_point</tt>, <tt>axis_vector</tt>, and <tt>start_position</tt> arguments determine the location
* of the multi-helix. The radius of the helix is calculated as the distance from
* the start position to the axis.
* <br><br>
* The <tt>right_handed</tt> argument determines the spring direction with respect to the axis
* vector. <tt>TRUE</tt> specifies right-handed, and <tt>FALSE</tt> specifies left-handed.
* <br><br>
* The <tt>rotation_angle_array</tt> argument determines how far the given spring section
* rotates about the axis and can be greater than one revolution (<tt>2 pi</tt> radians).
* The <tt>thread_distance_array</tt> argument determines the distance between adjacent
* loops, assuming that the rotation is greater than one revolution.
* <br><br>
* The <tt>transition_height_array</tt> argument determines the height distance for a
* transition piece, while <tt>transition_angle_array</tt> dictates the rotation (in
* radians) that occurs over the transition piece.
* <br><br>
* The specification of a transition region and second spring area is optional. The
* parameters are supplied in arrays so that any number of additional transition
* regions and additional <tt>api_edge_spring</tt> can be specified as long as the set of
* all four parameters is given for each section.
* <br><br>
* Refer to the documentation of the Scheme extension <tt>edge:spring</tt> in the
* Constructors component for illustrations and examples.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param axis_point
* axis start.
* @param axis_vector
* axis direction.
* @param start_position
* spring start position.
* @param right_handed
* right-handed (<tt>TRUE</tt>) or left-handed (<tt>FALSE</tt>).
* @param helix_count
* number of helical sections.
* @param thread_distance_array
* pitch array.
* @param rotation_angle_array
* radians for helical section.
* @param transition_height_array
* height of transition.
* @param transition_angle_array
* radians of transition.
* @param spring
* spring edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_spring(
			SPAposition& axis_point,
			SPAvector& axis_vector,
			SPAposition& start_position,
			logical right_handed,
			int helix_count,
			double* thread_distance_array,
			double* rotation_angle_array,
			double* transition_height_array,
			double* transition_angle_array,
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
 * @brief   创建弹簧.
 * @details	根据给定的参数构建一个包含一个或多个多个螺旋线的弹簧，每个螺旋线之间可以通过过渡部分连接，过渡部分旋转角度大于0时，可以保证G2连续性.
 * @param[in] axis_point 主轴起点
 * @param[in] axis_vector 主轴方向
 * @param[in] start_position 弹簧起点
 * @param[in] right_handed true为右手螺旋，false为左手
 * @param[in] helix_count helix数
 * @param[in] thread_distance_array 每个helix里，每个loop的距离，顺序设置
 * @param[in] rotation_angle_array 每个helix的旋转弧度
 * @param[in] transition_height_array 挨个定义每个transition的长度
 * @param[in] transition_angle_array 挨个定义每个transition旋转的弧度
 * @param[out] spring 返回实体
 * @param[in] ao ACIS选项
 * @return 函数执行结果
 * @note 请确保弹簧和过渡部分的旋转角度非负，主轴起点与弹簧起点不重合，且helix_count>0;参数范围小于1e-3量级时，生成的曲线不准确
 * @exception 主轴起点和弹簧起点重合时，会构建出错误的曲线，导致helix::convert_to_law_curve抛出异常
 */
DECL_KERN outcome gme_api_edge_spring(
			SPAposition& axis_point, 
			SPAvector& axis_vector, 
			SPAposition& start_position, 
			logical right_handed, 
			int helix_count, double* 
			thread_distance_array, 
			double* rotation_angle_array, 
			double* transition_height_array,
            double* transition_angle_array, 
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
 * @brief   创建弹簧.
 * @param[in] axis_point 主轴起点
 * @param[in] axis_vector 主轴方向
 * @param[in] start_position 弹簧起点
 * @param[in] right_handed true为右手螺旋，false为左手
 * @param[in] helix_count helix数
 * @param[in] thread_distance_array 每个helix里，每个loop的距离，顺序设置
 * @param[in] rotation_angle_array 每个helix的旋转弧度
 * @param[in] transition_height_array 挨个定义每个transition的长度
 * @param[in] transition_angle_array 挨个定义每个transition旋转的弧度
 * @param[out] spring 返回实体
 * @param[in] ao ACIS选项
 * @return 函数执行结果
 * @TODO 此函数只能完成部分功能:中心需要在原点，起点要在(x,0,0)上，normal为(0,0,z)
 */
DECL_KERN outcome gme_1_api_edge_spring(
	SPAposition& axis_point,
	SPAvector& axis_vector,
	SPAposition& start_position,
	logical right_handed,
	int helix_count, double*
	thread_distance_array,
	double* rotation_angle_array,
	double* transition_height_array,
	double* transition_angle_array,
	EDGE*& spring,
	AcisOptions* ao = NULL
);

/**
* Creates an edge from a tapered spring definition.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function combines several helix pieces into a "spring"
* edge. Transition pieces between the helix pieces ensure G<sup>2</sup> continuity. This function 
* differs from <tt>api_edge_spring</tt> in that an angle can be used to specify the taper
* of the helix. For example, a conical spring can be created. Like <tt>api_edge_spring</tt>,
* the final edge consists of a helix followed by zero or more transition/helix
* pairs. The resulting "spring" edge is returned in <tt>spring</tt>.
* <br><br>
* The <tt>EDGE</tt> returned has information associated with it that indicates where the
* axis of the helix is located. If the edge is then swept, a rail law is created
* that orients the profile relative to the center axis, rather than using a
* minimum rotation rail. This improves the speed of sweeping, and results in the
* intuitive sweeping of a spring.
* <br><br>
* The <tt>axis_point</tt>, <tt>axis_vector</tt>, and <tt>start_position</tt> arguments determine the location
* of the multi-helix. The radius of the helix is calculated as the distance from
* the start position to the axis.
* <br><br>
* The <tt>taper_angle</tt> argument gives the angle by which the spring radius changes in
* relation to the height of the spring. The radius increases for positive angles
* and decreases for negative angles.
* <br><br>
* The <tt>right_handed</tt> argument determines the spring direction with respect to the axis
* vector. <tt>TRUE</tt> specifies right-handed, and <tt>FALSE</tt> specifies left-handed.
* <br><br>
* The <tt>rotation_angle_array</tt> argument determines how far the given spring section
* rotates about the axis and can be greater than one revolution (<tt>2 pi</tt> radians).
* The <tt>thread_distance_array</tt> argument determines the distance between adjacent
* loops, assuming that the rotation is greater than one revolution.
* <br><br>
* The <tt>transition_height_array</tt> argument determines the distance for a transition
* piece, while <tt>transition_angle_array</tt> dictates the rotation (in radians) that
* occurs over the transition piece.
* <br><br>
* The specification of a transition region and second spring area is optional. The
* parameters are supplied in arrays so that any number of additional transition
* regions and additional spring areas can be specified as long as the set of all
* four parameters is given for each section.
* <br><br>
* Refer to the documentation of the Scheme extension <tt>edge:spring-taper</tt> in the
* Constructors component for illustrations and examples.
* <br><br>
* <b>Errors:</b> A negative <tt>taper_angle</tt> could result in a self-intersecting edge.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param axis_point
* axis point.
* @param axis_vector
* axis direction.
* @param start_position
* start position.
* @param taper_angle
* radius angle in radians.
* @param right_handed
* right-handed (<tt>TRUE</tt>) or left-handed (<tt>FALSE</tt>).
* @param helix_count
* thread dist.
* @param thread_distance_array
* array thread distance.
* @param rotation_angle_array
* array of rotation angle.
* @param transition_height_array
* array heights for transition.
* @param transition_angle_array
* array angles for transition.
* @param spring
* spring edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_spring_taper(
			SPAposition& axis_point,
			SPAvector& axis_vector,
			SPAposition& start_position,
			double taper_angle,
			logical right_handed,
			int helix_count,
			double* thread_distance_array,
			double* rotation_angle_array,
			double* transition_height_array,
			double* transition_angle_array,
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
 * @brief   创建锥形弹簧.
 * @details	根据给定的参数构建一个包含一个或多个多个锥形螺旋线的弹簧，每个螺旋线之间可以通过过渡部分连接，过渡部分旋转角度大于0时，可以保证G2连续性.
 * @param[in] axis_point 主轴起点
 * @param[in] axis_vector 主轴方向
 * @param[in] start_position 弹簧起点
 * @param[in] taper_angle 弹簧半径变化角度
 * @param[in] right_handed true为右手螺旋，false为左手
 * @param[in] helix_count helix数
 * @param[in] thread_distance_array 每个helix里，每个loop的距离，顺序设置
 * @param[in] rotation_angle_array 每个helix的旋转弧度
 * @param[in] transition_height_array 挨个定义每个transition的长度
 * @param[in] transition_angle_array 挨个定义每个transition旋转的弧度
 * @param[out] spring 返回实体
 * @param[in] ao ACIS选项
 * @return 函数执行结果
 * @note 请确保弹簧和过渡部分的旋转角度非负，主轴起点与弹簧起点不重合，taper_angle的tan值存在，且helix_count>0;参数范围小于1e-3量级时，生成的曲线不准确
 * @exception 主轴起点和弹簧起点重合时，会构建出错误的曲线
 */
DECL_KERN outcome gme_api_edge_spring_taper(
			SPAposition& axis_point, 
			SPAvector& axis_vector, 
			SPAposition& start_position, 
			double taper_angle,
			logical right_handed, 
			int helix_count, double* 
			thread_distance_array, 
			double* rotation_angle_array, 
			double* transition_height_array,
            double* transition_angle_array, 
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
* Creates an edge from a spring definition and a radius law.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function combines several helix pieces into a "spring"
* edge. Transition pieces between the helix pieces ensure G<sup>2</sup> continuity. This function 
* differs from <tt>api_edge_spring</tt> in that a law can be used to specify the radius of
* the helix. For example, a spring that expands and contracts can be created. Like
* <tt>api_edge_spring</tt>, the final edge consists of a helix followed by zero or more
* transition/helix pairs. The resulting "spring" edge is returned in <tt>spring</tt>.
* <br><br>
* The <tt>EDGE</tt> returned has information associated with it that indicates where the
* axis of the helix is located. If the edge is then swept, a rail law is created
* that orients the profile relative to the center axis, rather than using a
* minimum rotation rail. This improves the speed of sweeping, and results in the
* intuitive sweeping of a spring.
* <br><br>
* The <tt>axis_point</tt>, <tt>axis_vector</tt>, and <tt>start_position</tt> arguments determine the location
* of the multi-helix. The radius of the helix is calculated as the distance from
* the start position to the axis.
* <br><br>
* The <tt>radius_law</tt> argument allows specification of the radius as a function of the
* height of the spring. While this extension accepts a start position, the actual
* spring may start in a different position, depending on the starting value of the
* law function.
* <br><br>
* The <tt>right_handed</tt> argument determines the spring direction with respect to the axis
* vector. <tt>TRUE</tt> specifies right-handed, and <tt>FALSE</tt> specifies left handed.
* <br><br>
* The <tt>rotation_angle_array</tt> argument determines how far the given spring section
* rotates about the axis and can be greater than one revolution (<tt>2 pi</tt> radians).
* The <tt>thread_distance_array</tt> argument determines the distance between adjacent
* loops, assuming that the rotation is greater than one revolution.
* <br><br>
* The <tt>transition_height_array</tt> argument determines the distance for a transition
* piece, while <tt>transition_angle_array</tt> dictates the rotation (in radians) that
* occurs over the transition piece.
* <br><br>
* The specification of a transition region and second spring area is optional. The
* parameters are supplied in arrays so that any number of additional transition
* regions and additional spring areas can be specified as long as the set of all
* four parameters is given for each section.
* <br><br>
* Refer to the documentation of the Scheme extension <tt>edge:spring-law</tt> in the
* Constructors component for illustrations and examples.
* <br><br>
* <b>Errors:</b> An incorrect law could result in a self-intersecting edge.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param axis_point
* axis point.
* @param axis_vector
* axis direction.
* @param start_position
* start position.
* @param variable_radius_law
* law specifying spring radius.
* @param right_handed
* right-handed (<tt>TRUE</tt>) or left-handed (<tt>FALSE</tt>).
* @param helix_count
* thread dist.
* @param thread_distance_array
* array thread distance.
* @param rotation_angle_array
* array of rotation angle.
* @param transition_height_array
* array heights for transition.
* @param transition_angle_array
* array angles for transition.
* @param spring
* spring edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_spring_law(
			SPAposition& axis_point,
			SPAvector& axis_vector,
			SPAposition& start_position,
			law* variable_radius_law,
			logical right_handed,
			int helix_count,
			double* thread_distance_array,
			double* rotation_angle_array,
			double* transition_height_array,
			double* transition_angle_array,
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
 * @brief   创建弹簧.
 * @details	根据给定的参数构建一个包含一个或多个多个螺旋线的弹簧，每个螺旋线之间可以通过过渡部分连接，过渡部分旋转角度大于0时，可以保证G2连续性. 有一个额外的law*参数，可以指定螺旋线的半径.
 * @param[in] axis_point 主轴起点
 * @param[in] axis_vector 主轴方向
 * @param[in] start_position 弹簧起点
 * @param[in] variable_radius_law 螺旋线半径的law
 * @param[in] right_handed true为右手螺旋，false为左手
 * @param[in] helix_count helix数
 * @param[in] thread_distance_array 每个helix里，每个loop的距离，顺序设置
 * @param[in] rotation_angle_array 每个helix的旋转弧度
 * @param[in] transition_height_array 挨个定义每个transition的长度
 * @param[in] transition_angle_array 挨个定义每个transition旋转的弧度
 * @param[out] spring 返回实体
 * @param[in] ao ACIS选项
 * @note 不正确的law可能导致自交
 * @return 函数执行结果
 */
DECL_CSTR outcome gme_api_edge_spring_law(
			SPAposition& axis_point,
			SPAvector& axis_vector,
			SPAposition& start_position,
			law* variable_radius_law,
			logical right_handed,
			int helix_count,
			double* thread_distance_array,
			double* rotation_angle_array,
			double* transition_height_array,
			double* transition_angle_array,
			EDGE*& spring,
			AcisOptions* ao = NULL
	);

/**
* Creates an edge from a law.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates and returns an edge created from a law that
* takes one value and returns three values. Such a law maps a parameter value
* into a three-dimensional position. 
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param inlaw
* defining law.
* @param start
* start parameter value of edge.
* @param end
* end parameter value of edge.
* @param edge
* edge returned.
* @param law_number
* for future use.
* @param other_laws
* for future use.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_law(
		law*  inlaw,
		double start,
		double end,
		EDGE*& edge,
		int law_number = 0,
		law** other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
 * @brief 根据 law 创建 edge。
 * @details 根据 law 创建 edge，该 law 接受一个值并返回三个值，将一个参数值映射到三维位置坐标。
 * @param[in] inlaw 定义的 law
 * @param[in] start 边的起始参数值
 * @param[in] end 边的结束参数值
 * @param[out] edge 返回的边
 * @param[in] law_number 未来使用
 * @param[in] other_laws 未来使用
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 */
DECL_CSTR outcome gme_api_edge_law(
		law*  inlaw,
		double start,
		double end,
		EDGE*& edge,
		int law_number = 0,
		law** other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
* Creates a curve from a law.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function creates and returns a curve created from a law that
* takes one value and returns three values. Such a law maps a parameter value
* into a three-dimensional position. 
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param in_law
* defining law.
* @param start
* start parameter value of %curve.
* @param end
* end parameter value of %curve.
* @param crv
* curve returned.
* @param law_number
* for future use.
* @param other_laws
* for future use.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_law(
		law* in_law,
		double start,
		double end,
		curve*& crv,
		int law_number = 0,
		law** other_laws = NULL,
		AcisOptions* ao = NULL
	);
/**
 * @brief		创建由给定规则（方程）表示的曲线
 * @details
 * @param[in]	in_law			输入的规则（方程）
 * @param[in]	start			输入的参数起始值
 * @param[in]	end				输入的参数终止值
 * @param[out]	crv				创建的曲线
 * @param[in]	law_number		acis目前未用到,若改为非默认值会报错
 * @param[in]	other_law		acis目前未用到
 * @param[in]	ao				ACIS 选项
 * @return		outcome 执行结果
 */
DECL_CSTR outcome gme_api_curve_law(
		law* in_law,
		double start,
		double end,
		curve*& crv,
		int law_number = 0,
		law** other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
* Creates an edge from a R2 law and a face.
* <br><br>
* <b>Role:</b> This API function creates and returns an edge created from a law that
* takes one value and returns two values. Such a law maps a parameter value
* into a two-dimensional position in the parameter space of the given %surface.
* The resulting edge represents the mapping of the parameter space %curve defined
* by the law into a model space %curve using the %surface underlying the given face. 
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param in_face
* given face.
* @param in_law
* defining law.
* @param start
* start parameter value of edge.
* @param end
* end parameter value of edge.
* @param edge
* edge returned.
* @param law_number
* for future use.
* @param other_laws
* for future use.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_plaw(
		FACE* in_face,
		law*  in_law,
		double start,
		double end,
		EDGE*& edge,
		int law_number = 0,
		law** other_laws = NULL,
		AcisOptions* ao = NULL
	);

/**
* Creates an <tt>EDGE</tt> on a cubic Bezier %curve, given four control points.
* <br><br>
* <b>Role:</b> This API function creates an edge defined by a cubic Bezier %curve
* specified by four control points, <tt>pt1</tt>, <tt>pt2</tt>, <tt>pt3</tt>, and <tt>pt4</tt>. 
* The Bezier %curve is created inside the control points. The curve is represented internally as a
* B-spline intcurve.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pt1
* first control point.
* @param pt2
* second control point.
* @param pt3
* third control point.
* @param pt4
* last control point.
* @param edge
* B-spline edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_bezier(
		const SPAposition& pt1,    // first control point
		const SPAposition& pt2,    // second control point
		const SPAposition& pt3,    // third control point
		const SPAposition& pt4,    // last control point
		EDGE*& edge,               // Bezier curve created
		AcisOptions* ao = NULL
	);

/**
* @breif		创建贝塞尔曲线
* @detail		通过四个控制点创建贝塞尔曲线，贝塞尔曲线在控制点内部创建，曲线内部表示为B样条曲线
*				处理情况1：利用bs3_curve_from_ctrlpts和合适的权重、节点创建贝塞尔曲线
*				处理情况2：根据1、4控制点是否重合决定是否构造第二个VERTEX
* @param[in]	pt1 第一个控制点
* @param[in]	pt2 第二个控制点
* @param[in]	pt3 第三个控制点
* @param[in]	pt4 第四个控制点
* @param[out]	edge 创建的贝塞尔曲线
* @param[in]	ao ACIS选项
* @return		执行结果
**/
DECL_CSTR outcome gme_api_curve_bezier(
		const SPAposition& pt1,    // 第一个控制点
		const SPAposition& pt2,    // 第二个控制点
		const SPAposition& pt3,    // 第三个控制点
		const SPAposition& pt4,    // 第四控制点
		EDGE*& edge,               // 创建的贝塞尔曲线
		AcisOptions* ao = NULL);

/**
* Creates an <tt>EDGE</tt> on a B-spline %curve, given a sequence of control points and knots.
* <br><br>
* <b>Role:</b> This API function creates an edge with an underlying <tt>bs3_curve</tt>, as specified
* by the caller's input.  The positions of the curve's control points are passed in using the arguments
* <tt>num_ctrlpts</tt> and <tt>ctrlpts</tt>; the corresponding knot values are likewise given
* by <tt>num_knots</tt> and <tt>knots</tt>. In ACIS all B-spline curves interpolate their boundary 
* control points. To achieve this, the end knot multiplicities are either (a) equal to the degree, 
* or (b) equal to the degree plus one. If the end knot multiplicities are equal to the degree, 
* then the number of knots should be equal to the number of control points plus the degree minus one 
* <tt>num_knots = num_crtlpts + degree - 1</tt>. If the end knot multiplicities are equal to the degree 
* plus one, then the number of knots should be equal to the number of control points plus the degree 
* plus one <tt>num_knots = num_crtlpts + degree + 1</tt>. 
* No assumption is made about the relationship between parameter values and object space distances; 
* however, it is advantageous for the parameterization to be as homogeneous as possible. 
* (That is, it is advantageous for the parameterization to be somewhat proportional to arclength.)
* ACIS also prefers that curves be G<sup>2</sup> continuous; therefore, it may be advantageous to
* limit the knot multiplicities of interior knots to being less than <tt>degree - 2</tt>.
* <br><br>
* Setting the values of <tt>closed</tt> and <tt>periodic</tt>
* to <tt>FALSE</tt> ensures that the function will determine the correct values of both settings.  
* If a rational B-spline is intended, <tt>rational</tt> should be set to <tt>TRUE</tt>
* and the associated weights passed in through <tt>weights</tt>. (In ACIS, weights must be positive values.)
* The tolerance <tt>point_tol</tt> determines when two control points are identical, and
* <tt>knot_tol</tt> performs the same function for the knot values.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param degree
* degree.
* @param rational
* <tt>TRUE</tt> if rational control points.
* @param closed
* <tt>TRUE</tt> if closed %curve.
* @param periodic
* <tt>TRUE</tt> if periodic %curve.
* @param num_ctrlpts
* number of control points in array.
* @param ctrlpts
* array of control points.
* @param weights
* array of weights.
* @param point_tol
* identical points if within this tolerance.
* @param num_knots
* number of knots in array.
* @param knots
* array of knots.
* @param knot_tol
* identical knots if within this tolerance.
* @param edge
* edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_int_ctrlpts(
 			int degree,						// degree
 			logical rational,				// TRUE if rational control points
 			logical closed,					// TRUE if closed curve
 			logical periodic,				// TRUE if periodic curve
 			int num_ctrlpts,				// number of control points in array
 			const SPAposition ctrlpts[],	// array of control points
 			const double weights[],			// array of weights
 			double point_tol,				// identical points if within this tolerance
 			int num_knots,					// number of knots in array
 			const double knots[],			// array of knots
 			double knot_tol,				// identical knots if within this tolerance
 			EDGE*& edge,					// edge returned
 			AcisOptions* ao = NULL
	);

/**
* Creates an <tt>EDGE</tt> that represents a cubic B-spline %curve interpolating or fitting a sequence of points.
* <br><br>
* <b>Role:</b> This API function creates and returns an <tt>EDGE</tt> with an <tt>INTCURVE</tt> as the
* geometry supporting the edge. The edge is given start and end directions.
* <br><br>
* If the fit tolerance is 0, the %curve interpolates the sequence of points and has
* tangents at the start and end points in the direction of the unit vectors. If
* the fit tolerance is greater than 0, the %curve is a fit to the sequence of
* points.
* <br><br>
* If the start and end tangent directions are identical and the start and end
* points are identical, the %curve is marked as a <i>periodic</i> intcurve.
* <br><br>
* If the start and end directions are (0, 0, 0), default tangent directions are
* calculated using up to three points at the ends of the point array. Also, this
* condition can be specified by passing the <tt>NULL_unitvec</tt> found in <tt>unitvec.hxx</tt>.
* <br><br>
* No check is made to determine if the edge is self-intersecting.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param npts
* number of points in array.
* @param pts
* array of points.
* @param start_dir
* start direction.
* @param end_dir
* end direction.
* @param fitol
* fit tolerance, or 0 for interpolation.
* @param edge
* B-spline edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_cubic(
			int npts,							// number of points to be interpolated
												// or fitted
			const SPAposition pts[],			// points to be interpolated or fitted
			const SPAunit_vector& start_dir,	// direction at start of curve
			const SPAunit_vector& end_dir,		// direction at end of curve
			double fitol,						// 0 for interpolation, or permitted
												// fit tolerance
			EDGE*& edge,						// edge constructed
			AcisOptions* ao = NULL
	);

/**
 * @brief           创建一个三次 B 样条曲线 EDGE, 可以拟合或插值
 * @param[in]       npts 点的数量
 * @param[in]       pts 点的数组
 * @param[in]       start_dir 起始方向
 * @param[in]       end_dir 终止方向
 * @param[in]       fitol 拟合公差, 0 表示插值
 * @param[out]      edge 返回创建的 B 样条 EDGE 对象
 * @param[in]       ao ACIS 选项
 * @details         该函数创建一个三次 B 样条曲线 EDGE, 可以通过输入fitol选择插值或拟合
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_mk_ed_cubic(int npts,                         // number of points to be interpolated
                                                                        // or fitted
                                      const SPAposition pts[],          // points to be interpolated or fitted
                                      const SPAunit_vector& start_dir,  // direction at start of curve
                                      const SPAunit_vector& end_dir,    // direction at end of curve
                                      double fitol,                     // 0 for interpolation, or permitted
                                                                        // fit tolerance
                                      EDGE*& edge,                      // edge constructed
                                      AcisOptions* ao = NULL);


/**
* Creates a B-spline edge that passes through the given positions.
* <br><br>
* <b>Role:</b> This API function creates an edge that interpolates a series of <tt>numpts</tt> points,
* whose positions are passed as <tt>pts</tt> array. The <tt>start</tt> and <tt>end</tt> vectors specify
* the tangent directions at the ends of the edge.
* <br><br>
* If <tt>approx_ok</tt> flag is <tt>TRUE</tt> (default), then the %curve will be within <tt>SPAresfit</tt> of
* the points. Set <tt>approx_ok</tt> to <tt>FALSE</tt> to force the %curve through each point as
* tightly as possible.
* <br><br>
* If the <tt>periodic</tt> flag is set to <tt>TRUE</tt>, then the %curve will be made periodic, as
* long as the first point is within <tt>SPAresabs</tt> of the last point (i.e., the %curve is
* closed) so that no end conditions are imposed.
* <br><br>
* If the <tt>start</tt> or <tt>end</tt> vector is not specified, a free end
* condition is used at that end. A "free" or "natural" end condition means that
* the second derivative at that end is 0.
* <br><br>
* <b>Limitations:</b> <tt>numpts</tt> must be at least 2.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param numpts
* number of positions.
* @param pts
* array of positions.
* @param start
* tangent direction at start or <tt>NULL</tt>.
* @param end
* tangent direction at end or <tt>NULL</tt>.
* @param edge
* B-spline edge returned.
* @param approx_ok
* <tt>TRUE</tt> if <tt>SPAresfit</tt> position approximation is ok.
* @param periodic
* make periodic flag.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_curve_spline(
		int numpts,                // number of positions in pts
		const SPAposition* pts,       // array of positions
		const SPAunit_vector* start,  // direction at start or NULL
		const SPAunit_vector* end,    // direction at end or NULL
		EDGE*& edge,                // B-spline edge created
		logical approx_ok = TRUE,  // approximation ok?
		logical periodic = FALSE,  // Periodic if closed and no end conds
		AcisOptions* ao = NULL
	);

/**
* Creates a B-spline edge that interpolates an array of positions at specified parameter values.
* <br><br>
* <b>Role:</b> This API function creates an edge that interpolates a series of <tt>numpts</tt> points, whose
* positions are passed in <tt>pts</tt> array and whose parameters along the B-spline %curve are given
* by the <tt>params</tt> array. No assumption is made about the relationship between parameter values 
* and object space distances; however, it is advantageous for the parameterization to be as homogeneous as possible. 
* (That is, it is advantageous for the parameterization to be somewhat proportional to arclength.)
* <br><br>
* The <tt>start</tt> and <tt>end</tt> vectors specify the derivative of 
* %curve with respect to its parameter at these ends.
* If either <tt>start</tt> or <tt>end</tt> vector is not specified, a free end
* condition is used at that end. A "free" or "natural" end condition means that
* the second derivative at that end is 0.
* <br><br>
* <b>Limitations:</b> The number of points specified must be at least 2. Parameter
* values and positions must be distinct. Parameter values must be monotonically increasing.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param numpts
* number of positions.
* @param pts
* array of positions.
* @param params
* array of parameter values (1 for each position).
* @param start
* derivative at start or <tt>NULL</tt>.
* @param end
* derivative at end or <tt>NULL</tt>.
* @param edge
* B-spline edge returned.
* @param ao
* ACIS options such asversion and journal.
**/
DECL_CSTR outcome api_curve_spline2(
		int numpts,                // number of positions in pts
		const SPAposition* pts,       // array of positions
		const double* params,      // array of parameters corresponding to positions
		const SPAvector* start,       // derivative at start or NULL
		const SPAvector* end,         // derivative at end or NULL
		EDGE*& edge,                // B-spline edge created
		AcisOptions* ao = NULL
	);

/**
 * @brief		创建一条 B 样条边，该边在指定参数值处对位置数组进行插值
 * @details		创建一条 B 样条边，该边在指定参数值处对位置数组进行插值。
 *				该API函数创建一条插入pts数组中numpts个点的边，在params数组中给出B样条曲线的参数。
 *				没有对参数值和物体空间距离之间的关系做出任何假设；
 *				然而，参数化尽可能同质是有利的。（也就是说，参数化与弧长成一定比例是有利的。）
 *				start向量和end向量用于指定曲线在起始点和终止点的导数（切线方向）。
 *				如果未指定start或end向量，则在该端使用自由结束条件（意味着该端的二阶导数为 0）。
 * @param[in]	numpts		控制点个数（至少为2）
 * @param[in]	pts			控制点坐标数组，传入首个元素的指针（至少两个控制点）
 * @param[in]	params		每个控制点的参数（必须单调递增）
 * @param[in]	start		指定起始点的切线方向
 * @param[in]	end			指定终止点的切线方向
 * @param[out]	edge		创建的B样条边edge
 * @return		函数执行结果
 * @note		指定的点数必须至少为 2。参数值和位置不能重复。参数值必须单调递增。
 *				目前该api对于非递增参数、参数非常接近的情况，生成结果与acis不一致。
 * @exception	acis_exception(EMPTY_ARRAY)	传入的控制点数量numpts<=0
 *				acis_exception(ACIS_EXCEPTION_ACCESS_VIOLATION)	传入的控制点数量numpts=1
 *				acis_exception(EVALUATE_FAILED)	传入的控制点数量numpts=2，且两个param相同
 */
DECL_CSTR outcome gme_api_curve_spline2(
		int numpts,                // 控制点的数量
		const SPAposition* pts,       // 控制点数组，传入收个元素的指针
		const double* params,      // 每个控制点的参数（必须单调递增）
		const SPAvector* start,       // 指定起始点的切线方向，或者为NULL不指定
		const SPAvector* end,         // 指定终止点的切线方向，或者为NULL不指定
		EDGE*& edge,                // 返回创建的B样条边
		AcisOptions* ao = NULL
	);
/**
 * @brief		创建一条 B 样条边，该边在指定参数值处对位置数组进行插值
 * @details		创建一条 B 样条边，该边在指定参数值处对位置数组进行插值。
 *				该API函数创建一条插入pts数组中numpts个点的边，在params数组中给出B样条曲线的参数。
 *				没有对参数值和物体空间距离之间的关系做出任何假设；
 *				然而，参数化尽可能同质是有利的。（也就是说，参数化与弧长成一定比例是有利的。）
 *				start向量和end向量用于指定曲线在起始点和终止点的导数（切线方向）。
 *				如果未指定start或end向量，则在该端使用自由结束条件（意味着该端的二阶导数为 0）。
 * @param[in]	numpts		控制点个数（至少为2）
 * @param[in]	pts			控制点坐标数组，传入首个元素的指针（至少两个控制点）
 * @param[in]	params		每个控制点的参数（必须单调递增）
 * @param[in]	start		指定起始点的切线方向
 * @param[in]	end			指定终止点的切线方向
 * @param[out]	edge		创建的B样条边edge
 * @return		函数执行结果
 * @note		指定的点数必须至少为 2。参数值和位置不能重复。参数值必须单调递增。
 *				目前该api对于非递增参数、参数非常接近的情况，生成结果与acis不一致。
 * @exception	acis_exception(EMPTY_ARRAY)	传入的控制点数量numpts<=0
 *				acis_exception(ACIS_EXCEPTION_ACCESS_VIOLATION)	传入的控制点数量numpts=1
 */
DECL_CSTR outcome gme_1_api_curve_spline2(
		int numpts,                // 控制点的数量
		const SPAposition* pts,       // 控制点数组，传入收个元素的指针
		const double* params,      // 每个控制点的参数（必须单调递增）
		const SPAvector* start,       // 指定起始点的切线方向，或者为NULL不指定
		const SPAvector* end,         // 指定终止点的切线方向，或者为NULL不指定
		EDGE*& edge,                // 返回创建的B样条边
		AcisOptions* ao = NULL
	);

/**
* Creates a periodic B-spline edge that interpolates an array of positions at specified parameter values.
* <br><br>
* <b>Role:</b> This API function creates an edge that interpolates a series of <tt>numpts</tt> points, whose
* positions are passed in <tt>pts</tt> array and whose parameters along the B-spline %curve are given
* by the <tt>params</tt> array.  The result is periodic in the sense that it is both closed and 
* in having its first and second derivatives match at the end-points.  The number of
* positions in the <tt>pts</tt> array must be at least four and must be equal to the
* number of reals in <tt>params</tt>.
* <br><br>
* <b>Errors:</b> The first and last input positions are not the same.
* The total number of input positions is less than four. Parameter values are not
* monotonically increasing.
* <br><br>
* <b>Limitations:</b> Parameter
* values and positions should be distinct. Parameter values must be monotonically increasing.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param numpts
* number of positions.
* @param pts
* array of positions.
* @param params
* array of parameter values (1 for each position).
* @param edge
* periodic B-spline edge returned.
* @param ao
* ACIS options such asversion and journal.
**/
DECL_CSTR outcome api_curve_spline2_periodic(
		int numpts,					// number of positions in pts
		const SPAposition* pts,		// array of positions
		const double* params,		// array of parameters corresponding to positions
		EDGE*& edge,				// B-spline edge created
		AcisOptions* ao = NULL
	);

/**
 * @nodoc
 */
DECL_CSTR outcome api_edge(
			EDGE* in_edge,						// The edge to be copied
			EDGE*& out_edge,					// The copied edge
			AcisOptions* ao = NULL
	);

/**
* Creates a new arc length parameterized edge from the geometry underlying the specified edge.
* <br><br>
* <b>Role:</b> This API function creates a new <tt>EDGE</tt> pointing to a new start <tt>VERTEX</tt>, a
* new end <tt>VERTEX</tt>, and an arc length parameterized <tt>CURVE</tt> that is based upon the
* <tt>CURVE</tt> underlying the input edge. The new <tt>EDGE</tt> is returned in <tt>out_edge</tt>.
* <br><br>
* <b>Errors:</b> Pointer to edge is <tt>NULL</tt>, pointer is not to an <tt>EDGE</tt>, or <tt>EDGE</tt> is not part
* of a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_edge
* edge to copy.
* @param approx_ok
* approximation ok.
* @param tol
* tolerance.
* @param out_edge
* arc length parameterized edge.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_arclength_param(
	EDGE* in_edge,					// The input edge
	logical approx_ok,				// Approximation ok
	double tol,						// tolerance
	EDGE*& out_edge,				// The arc length edge
	AcisOptions* ao = NULL
	);

/**
 * @brief		从现有边创建新的弧长参数化边
 * @param[in]	in_edge  	输入边
 * @param[in]	approx_ok	是否可以使用 B 样条近似来计算精确曲线（默认false）
 * @param[in]	tol			指定与新曲线关联的拟合公差（默认值为 SPAresfit）
 * @param[out]	out_edge	返回边
 * @param[in]	ao			ACIS options
 * @return		函数执行结果
 */
DECL_CSTR outcome gme_api_edge_arclength_param(
	EDGE* in_edge,					// The input edge
	logical approx_ok,				// Approximation ok
	double tol,						// tolerance
	EDGE*& out_edge,				// The arc length edge
	AcisOptions* ao = NULL
	);

/**
* Performs an (in-place) arclength parameterization of the geometry underlying the given edge.
* <br><br>
* <b>Role:</b> This API function performs an arclength parameterization of the given <tt>EDGE</tt>.
* <br><br>
* <b>Errors:</b> Pointer to edge is <tt>NULL</tt>, pointer is not to an <tt>EDGE</tt>, or <tt>EDGE</tt> is not part
* of a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Changes model.
* <br><br>
* <b>Journal:</b> Available.
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler.
* <br><br>
* @param edge
* edge to be re-parameterized
* @param approx_ok
* approximation ok
* @param tol
* tolerance
* @param ao
* ACIS options
**/
DECL_CSTR outcome api_edge_arclength_param(
	EDGE*& edge,			// The edge whose curve will be reparameterized
	logical approx_ok,	// Approximation ok
	double tol,			// tolerance
	AcisOptions* ao = NULL
);

/**
 * @brief		对现有边进行就地弧长参数化
 * @param[in&out]	edge  		输入边
 * @param[in]		approx_ok	是否可以使用 B 样条近似来计算精确曲线（默认false）
 * @param[in]		tol			指定与新曲线关联的拟合公差（默认值为 SPAresfit）
 * @param[in]		ao			ACIS options
 * @return			函数执行结果
 */
DECL_CSTR outcome gme_api_edge_arclength_param(
	EDGE*& edge,			// The edge whose curve will be reparameterized
	logical approx_ok,	// Approximation ok
	double tol,			// tolerance
	AcisOptions* ao = NULL
);


/**
* Creates a new edge which is a transformed copy of the specified edge.
* <br><br>
* <b>Role:</b> This API function creates a new <tt>EDGE</tt> pointing to a new start <tt>VERTEX</tt>, a
* new end <tt>VERTEX</tt>, and a new <tt>CURVE</tt>, all transformed from the input edge by the
* specified transform.
* <br><br>
* <b>Errors:</b> Pointer to edge is <tt>NULL</tt> or not to an <tt>EDGE</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_edge
* edge to be copied and transformed.
* @param t
* transform to be applied.
* @param out_edge
* copied and transformed edge.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_trans_edge(
			EDGE* in_edge,				// The edge to be copied
			const SPAtransf& t,			// The transform to be applied
			EDGE*& out_edge,			// The copied edge
			AcisOptions* ao = NULL
	);

/**
 * @brief		创建一个新的边，该边是对指定边进行变换后的拷贝。
 * @details  	创建一个新的EDGE，指向新的VERTEX和CURVE。
 * @param[in]	in_edge 输入边
 * @param[in]	t 变换
 * @param[out]	out_edge 变换结果拷贝edge
 * @param[in]	ao ACIS options
 * @return		函数执行结果
 */
DECL_CSTR outcome gme_api_trans_edge(
			EDGE* in_edge,				// The edge to be copied
			const SPAtransf& t,			// The transform to be applied
			EDGE*& out_edge,			// The copied edge
			AcisOptions* ao = NULL
	);

/**
* Creates an edge using a copy of the input curve.
* <br><br>
* <b>Role:</b> This is a convenient way to create model topology (an
* <tt>EDGE</tt>) from construction geometry (a <tt>curve</tt>).
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param cur
* given curve.
* @param edge
* returned edge.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_edge_from_curve(
		const curve* cur,	// given curve
		EDGE*& edge,		// returned edge
		AcisOptions* ao = NULL
	);

/**
* Creates an <tt>EDGE</tt> defined by a 3D NURBS %curve.
* <br><br>
* <b>Role:</b> This API function copies the <tt>NURBS</tt> %curve to create an <tt>INTCURVE</tt> supported
* by the <tt>NURBS</tt> %curve.
* <br><br>
* Creates an <tt>EDGE</tt> with supporting <tt>VERTEXs</tt> that represents the bounded edge.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param bs
* given bs3_curve.
* @param edge
* new edge returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_ed_bs3_curve(
			bs3_curve bs,			// spline curve
			EDGE*& edge,			// edge constructed
			AcisOptions* ao = NULL
	);

/**
* Splits a lone edge at a position or its intersection with another edge.
* <br><br>
* <b>Role:</b> To split an edge at a position, specify the position in <tt>split_pt</tt>
* and <tt>NULL</tt> for <tt>split_ed</tt>.
* <br><br>
* To split an edge with another edge, specify <tt>NULL</tt> for <tt>split_pt</tt> and a pointer to the
* edge to split with in <tt>split_ed</tt>. This API function splits the original edge at all
* intersections between the bounded portions of the edges. The original edge,
* and all new edges created as the result of splitting, are added to
* the entity list, <tt>new_eds</tt>.
* <br><br>
* <b>Note:</b> The seam vertex is removed when a periodic edge is split at a location other than its seam.
* These vertices can be forced into the answer by attaching <tt>NO_MERGE_ATTRIB</tt> attributes to them.
* Refer to @href api_set_no_merge_attrib for more information.
* <br><br>
* <b>Limitations:</b> The edge cannot be owned by another entity, otherwise an error is thrown.  To split an edge
* which is part of a larger model, use @href sg_split_edge_at_vertex. 
* <br><br>
* Do not specify end points of the edge; using them causes no
* error, but returns the original edge as the only item in the entity list.
* <br><br>
* <b>Errors:</b>The <tt>EDGE</tt> to be split is owned by another <tt>ENTITY</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param edge
* edge to split.
* @param split_pt
* position to split at or <tt>NULL</tt>.
* @param split_ed
* edge to split with or <tt>NULL</tt>.
* @param new_eds
* returned edges created by the split.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_split_curve(
		EDGE* edge,						// edge to split
		const SPAposition* split_pt,	// position to split at or NULL
		EDGE* split_ed,					// edge to split with or NULL
		ENTITY_LIST& new_eds,			// edges created by the split
		AcisOptions* ao = NULL
	);

/**
* Splits an edge at G1 or G2 discontinuities.
* <br><br>
* <b>Role:</b> The input edge and its underlying intcurve are split at the G<sup>1</sup> or G<sup>2</sup> 
* discontinuity (<tt>disc_order</tt> = 1 or 2) by accessing the <tt>discontinuity_info</tt> stored in the edge's %curve. 
* The result is a list of the split edges, including the original. For example, if the original edge is
* split once, the list will contain the original edge and one additional edge.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D InterOp
 * <br><br>
* @param edge
* edge to be split.
* @param new_edges
* resulting edges.
* @param cont_order
* G1 or G2.
* @param ao
* ACIS options such as version and journal.
**/

DECL_CSTR outcome api_split_edge_at_disc(
		EDGE* edge,				// edge to be split
		ENTITY_LIST& new_edges,		// resulting edges
		int cont_order = 1,			// G1 or G2
		AcisOptions* ao = NULL
	);

/**
 * @brief    在G1或者G2不连续点分割曲线
 * @details  输入边及其下方的intcurve在G1或G2不连续点（disc_order = 1或2）处被分割，
 *           通过访问存储在边曲线中的discontinuity_info来实现。结果是一个分割边的列表，包括原始边。
 *           例如，如果原始边被分割一次，列表将包含原始边和一个额外的边。
 * @param[in] edge 待分割的edge
 * @param[out] new_edges 分割结果组成的entity_list
 * @param[in] cont_order 表示G1或G2.
 * @return 函数执行结果
 * @see   api_split_curve()  该函数根据输入的分割点/边将输入的待分割edge分割
 * @note   输入cont_order默认为1，若不为1或2，可能出现意想不到的结果
 */
DECL_CSTR outcome gme_api_split_edge_at_disc(EDGE* edge,              // edge to be split
                                             ENTITY_LIST& new_edges,  // result edges
                                             int cont_order = 1       // G1 or G2
);

/**
* Creates vertex and edge entities corresponding to a list of <tt>edge-edge</tt> intersections as produced by @href api_inter_ed_ed.
* <br><br>
* <b>Errors:</b> Pointer to edge is <tt>NULL</tt> or not to an <tt>EDGE</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param edge1
* first edge supplied to @href api_inter_ed_ed.
* @param inters
* list of intersection information from @href api_inter_ed_ed.
* @param ents
* returned vertices and edges corresponding to intersections.
* @param ao
* ACIS options.
**/

DECL_CSTR outcome api_ed_inters_to_ents(
			EDGE* edge1,				// first edge
			curve_curve_int* inters,	// list of curve/curve intersections
			ENTITY_LIST& ents,			// list of intersection points or
										// overlapping edges
			AcisOptions* ao = NULL
	);

// STI let (10/99): Moved api_edge_to_spline() from oper to cstr

// Create a spline edge using a given edge.

/**
* Creates a B-spline edge using a given edge.
* <br><br>
* <b>Role:</b> This function creates an edge (<tt>edge2</tt>) that is a B-spline representation 
* of the given edge (<tt>edge1</tt>). The given edge may have an analytic or procedural definition. 
* The new edge will have an B-spline representation. If you want the 
* new B-spline edge to replace the original edge, specify <tt>edge2</tt> as <tt>NULL</tt>.
* <br><br>
* To ensure that the new edge has the same direction as the input edge, set 
* the global option <tt>spl_edges_forward</tt> to <tt>FALSE</tt> before calling <tt>api_edge_to_spline</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param edge1
* given edge.
* @param edge2
* new B-spline edge.
* @param ao
* ACIS options.
* <br><br>
* @see api_convert_to_spline
**/
DECL_CSTR outcome api_edge_to_spline(
		EDGE*  edge1,
		EDGE*& edge2,
		AcisOptions* ao = NULL
	);


/**
* Creates a curve that approximates a given curve.
* <br><br>
* <b>Role:</b> Creates a curve that approximates a given curve to a given
* tolerance over the specified parameter range, which must be contained within 
* the parameter range of the given curve. This function is intended for 
* applications performing translation and needing an approximation of the curve.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_curve
* given curve.
* @param tol
* tolerance for approximation.
* @param range
* parameter range for approximating curve.
* @param crv
* approximating curve returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_approx_curve(
		const curve* in_curve,		// given curve
		double const tol,			// specified tolerance
		SPAinterval range,			// specified range for returned curve
		curve*& crv,				// returned curve
		AcisOptions* ao = NULL
	);


/*! @} */
/*! \addtogroup CSTRMAKEOTHERAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */
//============================================================
// Point creation
/**
* Creates a point entity at the specified position.
* <br><br>
* <b>Role:</b> This API function creates an instance of <tt>APOINT</tt> with a use count of 1.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param pos
* position of point.
* @param pnt
* <tt>APOINT</tt> returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_create_point(
		const SPAposition& pos,		// position of APOINT
		APOINT*& pnt,				// APOINT created
		AcisOptions* ao = NULL
	);

//============================================================
// TEXT_ENT creation
/**
* Creates a text entity at given position.
* <br><br>
* <b>Role:</b> This API function creates a <tt>TEXT_ENT</tt> at given <tt>location</tt>, with a given
* text <tt>string</tt>, <tt>font</tt>, and <tt>size</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param location
* baseline position of first character.
* @param string
* string to be displayed.
* @param font
* font name.
* @param size
* font size in points.
* @param text
* text entity returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_create_text(
		const SPAposition& location,	// baseline of first character
		const char* string,				// string to be displayed
		const char* font,				// font name
		int size,						// font size in points
		TEXT_ENT*& text,				// TEXT_ENT created
		AcisOptions* ao = NULL
	);

/**
 * @brief 根据给定信息创建一个TEXT_ENT
 * @param[in] location 第一个字符的基线位置
 * @param[in] string 要显示的字符串
 * @param[in] font 字体名称
 * @param[in] size 字体大小, 单位是pt
 * @param[out] text 生成的TEXT_ENT
 * @param[in] ao ACIS选项
 * @return outcome 执行结果
 */
DECL_CSTR outcome gme_api_create_text(
		const SPAposition& location,	// 第一个字符的基线位置
		const char* string,				// 要显示的字符串
		const char* font,				// 字体名称
		int size,						// 字体大小, 单位是pt
		TEXT_ENT*& text,				// 生成的TEXT_ENT
		AcisOptions* ao = NULL
	);

/*! @} */
/*! @} */
/*! \addtogroup CSTRMAKEMODIFYAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */

/**
* Adds each <tt>FACE</tt> in the array to a <tt>SHELL</tt> within a <tt>LUMP</tt> within a <tt>BODY</tt>.
* <br><br>
* <b>Role:</b> For each <tt>FACE</tt> in an array, the API function makes a new <tt>LUMP</tt> consisting
* of a single <tt>SHELL</tt>. The <tt>FACE</tt> is attached to the <tt>SHELL</tt>. No attempt is made to
* stitch the faces into larger sheets, and no check is made for mutually
* intersecting or self-intersecting faces.  This function should not be used on faces that are already
* contained within a shell (i.e., with a non-<tt>NULL</tt> shell pointer); it should only be used on
* "free" faces to wrap those faces in a body.
* <br><br>
* If the <tt>in_body</tt> is <tt>NULL</tt>, a new <tt>BODY</tt> is created and returned. Otherwise, the
* old <tt>BODY</tt> is used and the <tt>LUMP</tt> is added to the list of lumps in the body. In
* either case, the <tt>BODY</tt> pointer is updated on return.
* <br><br>
* When ACIS makes a <tt>BODY</tt> from a single-sided <tt>FACE</tt> using 
* <tt>api_mk_by_faces</tt>, it makes a single-sided face body. 
* An open, single-sided face body is an incomplete solid, not a sheet (infinitely thin) body. 
* <br><br>
* <dl>
* <b>Errors:</b> Pointer to body is not to a <tt>BODY</tt>.
* <dd>&nbsp;A pointer in the face array is <tt>NULL</tt> or not to a <tt>FACE</tt>.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_body
* body to which to add.
* @param num_faces
* number of faces in array.
* @param faces
* array of faces.
* @param body
* body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_mk_by_faces(
			BODY* in_body,				// input body (may be NULL)
			int num_faces,				// number of faces
			FACE* faces[],				// array of faces
			BODY*& body,				// resultant body
			AcisOptions* ao = NULL
	);

/**
 * @brief  Adds each FACE in the array to a SHELL within a LUMP within a BODY.
 * @param[in]  in_body body to which to add.
 * @param[in]  num_faces	number of faces in array.
 * @param[in]  faces  array of faces.
 * @param[out]  body	 body returned.
 * @param[in]  ao  ACIS options.
 * @return outcome body created
 */
DECL_CSTR outcome gme_api_mk_by_faces(BODY* in_body,  // input body (may be NULL)
                                      int num_faces,  // number of faces
                                      FACE* faces[],  // array of faces
                                      BODY*& body,    // resultant body
                                      AcisOptions* ao = NULL);

/**
* Creates a wire from an array of positions and an array of pointers to curves.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function constructs a wire from the position array <tt>points</tt> 
* and the curve array <tt>curves</tt>.  The positions define the vertex locations of
* the wire.  A curve indexed by <tt>i</tt> should pass through the corresponding positions
* <tt>points[i]</tt> and <tt>points[i + 1]</tt>.  The only exception to this occurs for closed
* wires, when the final curve should pass through <tt>points[num_points - 1]</tt> and <tt>points[0]</tt>.
* <br><br>
* If the wire being created is closed, set <tt>closed</tt> to <tt>TRUE</tt> and furnish position and
* <tt>curves</tt> arrays of the same length <tt>num_points</tt>.  Otherwise, set
* <tt>closed</tt> to <tt>FALSE</tt> and provide a <tt>curves</tt> array of length <tt>num_points - 1</tt>.
* <br><br>
* The function does not determine if the wire is self-intersecting.
* <br><br>
* If the given body is <tt>NULL</tt>, the API function makes a new body. The new wires are placed in a shell.
* <br><br>
* The API function returns the body in the last argument.
* <br><br>
* <b>Errors:</b> The pointer to <tt>in_body</tt> points to an object this is not a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param in_body
* body to add wire to.
* @param closed
* build a closed wire if <tt>TRUE</tt>.
* @param num_points
* number of positions.
* @param points
* array of positions.
* @param curves
* array of pointers to span curves.
* @param body
* returned wire body.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_build_wire(
			BODY* in_body,			// body to which wire is to be added,
									// or NULL for a new body
			logical closed,			// TRUE if wire is closed
			int num_points,			// number of span end-points
			SPAposition points[],	// array of span end-points
			curve* curves[],		// array of span geometries
			BODY*& body,			// original body with extra wire, or
									// new body returned
			AcisOptions* ao = NULL
	);

/**
* @brief		根据给定的位置数组和曲线指针数组创建一个wire
* @details		情况一：指向in_body的指针不是BODY类型
*				情况二：给定的实体in_body = NULL，API函数将创建一个新body；
*				情况三：给定的实体in_body中已经存在其他实体，将向in_body中添加wire
*				情况四：如果num_points<0，会创建points[0]构成的null edge；
*				情况五：如果0<num_points<points.length，会创建前num_points个点和其对应edge构成的wire
*				情况六：curves乱序或与points不匹配
*				情况七：wire有分支
*				情况八：存在两个位置小于容差
* @param[in]	in_body		需要添加wire的body
* @param[in]	closed		wire是否闭合
* @param[in]	num_points	点位置的数量
* @param[in]	points		给定点位置的数组
* @param[in]	curves		给定曲线的数组
* @param[out]	body		返回的wire body
* @param[in]	ao			ACIS选项
* @return		函数执行结果
* @note			当num_points大于points数组的长度，则数组会越界（acis的api同样也是）；
*				当0<num_points<points.size，acis也会报错error，因为acis的api不验证用户输入
* 
**/
DECL_CSTR outcome gme_api_build_wire(
			BODY* in_body,
			logical closed,
			int num_points,
			SPAposition points[],
			curve* curves[],
			BODY*& body,
			AcisOptions* ao = NULL
	);

/**
 * @brief		   创建一个由点和曲线定义的WIRE，并将其加入到指定的BODY中。
 * @param[in] in_body 输入的BODY对象，可以为空；若为空，将创建一个新BODY。
 * @param[in] closed  指定WIRE是否为闭合的（TRUE为闭合，FALSE为开放）。
 * @param[in] num_points 点数组的大小。
 * @param[in] points 点数组，定义WIRE的顶点位置。
 * @param[in] curves 曲线数组，每条曲线依次连接点数组中的点。
 * @param[out] body 返回生成的WIRE所在的BODY对象。
 * @param[in] ao   ACIS选项（可选）。
 * @details		   根据输入的点和曲线构造一个WIRE：
 *				   处理情况1：检查输入参数的合法性，包括点数组和曲线数组是否为空，
 *						       以及曲线数量是否与点数组匹配；
 *				   处理情况2：若num_points为1且closed为FALSE，创建一个自循环的WIRE；
 *				   处理情况3：若closed为TRUE，则创建闭合WIRE，并连接首尾顶点；
 *				   处理情况4：若closed为FALSE，则创建开放WIRE；
 *				   处理情况5：若in_body不为空，将生成的WIRE合并到in_body中；
 *				   处理情况6：若in_body为空，将生成的WIRE置于新创建的BODY中。
 * @return outcome 函数执行结果。
 */
DECL_CSTR outcome gme_1_api_build_wire(
			BODY* in_body,
			logical closed,
			int num_points,
			SPAposition points[],
			curve* curves[],
			BODY*& body,
			AcisOptions* ao = NULL
	);


/**
* Creates a wire from an array of positions and bulges.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function constructs an open or closed <i>kwire</i> wire containing
* straight or circular arc edges defined by an array of positions and bulge factors. The
* bulge of a circular arc is the maximum distance between the arc and the chord 
* divided by one half the length of the chord. For a straight line the bulge factor
* is 0.0.  For a semi-circular arc the bulge factor is 1.0.
* <br><br>
* Every arc lies in a %plane with the given normal.
* <br><br>
* Bulge factors are positive for arcs directed counterclockwise with respect to
* the normal.
* <br><br>
* An array of <i>n</i> positions requires an array of <i>n-1</i> bulge factors.
* <br><br>
* The wire is closed if the first and last points coincide within <tt>SPAresabs</tt>.
* <br><br>
* Rejects open wires of less than 2 positions and closed wires of less than 3
* positions.
* <br><br>
* Determines that the chord of each segment is perpendicular to the normal, and
* that no segment has chord length less than <tt>SPAresabs</tt>.
* <br><br>
* Does not check that points other than first and last are distinct, or that
* segments do not intersect one another.
* <br><br>
* If given body is <tt>NULL</tt>, makes a new body.
* <br><br>
* Leaves new wire as first in wire list of <tt>body</tt>, new or old. Returns the body.
* <br><br>
* <dl>
* <b>Errors:</b> Pointer to given body is not to a <tt>BODY</tt>.
* <dd>&nbsp;Zero length normal vector.</dd>
* <dd>&nbsp;(Refer to the Role for other errors)</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param in_body
* existing body to add to, or <tt>NULL</tt> to create a new body.
* @param normal
* normal to %plane of wire.
* @param length_pts
* number of positions in array.
* @param array_pts
* array of positions.
* @param array_bulges
* array of bulge factors.
* @param body
* body containing wire returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_kwire(
			BODY* in_body,					// body to which wire is to be added,
											// or NULL for a new body
			const SPAunit_vector& normal,	// normal to plane of wire
			int length_pts,					// number of span end-points
			SPAposition array_pts[],		// array of span end-points
			double array_bulges[],			// array of "bulge factors", one for
											// each span
			BODY*& body,					// original body with extra wire, or
											// new body returned
			AcisOptions* ao = NULL
	);

/**
* Creates a polygonal wire from an array of positions.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function constructs a polygonal wire from an array of positions.
* The wire is considered closed if the first and last points coincide.
* <br><br>
* Does not check that points other than adjacent points are distinct.
* <br><br>
* If given body is <tt>NULL</tt>, makes a new body. It leaves the new wire as first in wire
* list of <tt>body</tt>, new or old. Returns the body.
* <br><br>
* A degenerate, single point wire can be made. However, such wires are not fully supported by
* Booleans and offsetting.
* <br><br>
* <b>Errors:</b> Pointer to given body is not to a <tt>BODY</tt>. Distance between adjacent points
* in list less than <tt>SPAresabs</tt>.
* <br><br>
* <b>Limitations:</b> Wires that are in single isolated point (characterized by an
* edge with null geometry) are not fully supported.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param in_body
* body to add wire to, or <tt>NULL</tt> for new body.
* @param length_pts
* number of span end points in array.
* @param array_pts
* array of points.
* @param body
* wire body returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_make_wire(
			BODY* in_body,				// body to which wire is to be added,
										// or NULL for a new body
			int length_pts,				// number of span end-points
			SPAposition array_pts[],	// array of span end-points
			BODY*& body,				// original body with extra wire, or
										// new body returned
			AcisOptions* ao = NULL
	);

/**
 * @brief     	根据给点的点列按顺序创建一个wire_body，若in_body非空还会将两个body合并
 * @details     异常情况优先检测是否存在相同的边(起终点相同)，然后检测相邻点是否小于容差
 * @param[in]	in_body			输入in_body，若为空则结果保持空，若非空则将生成的wire_body和in_body合并，并赋给in_body
 * @param[in]	length_pts		函数实际的遍历数组的长度，需要大于等于一才能正常产生body
 * @param[in]	array_pts[]     SPAposition数组，未赋值部分系统默认全部赋为SPAposition(-9.2559631349317831e+61, -9.2559631349317831e+61, -9.2559631349317831e+61)
 * @param[out]	body			输出结果存入body，发生异常的情况下，不会改变传入的body
 * @return		函数执行结果
 * @exception   acis_exception(WIRE_DUP_VERT)  如果有重复边，抛出异常WIRE_DUP_VERT
 *				acis_exception(ENDS_TOO_CLOSE) 如果有重复点，抛出异常ENDS_TOO_CLOSE
 * @note		如果in_body非空，则得到的新body会将生成的wire_body存在body->lump()，将in_body存在body->lump()->next()
 */
DECL_CSTR outcome gme_api_make_wire(BODY* in_body,            // 输入in_body，若为空则结果保持空，若非空则将生成的wire_body和in_body合并，并赋给in_body
                                    int length_pts,           // 函数实际的遍历数组的长度，需要大于等于一才能正常产生body
                                    SPAposition array_pts[],  // SPAposition数组
                                    BODY*& body,              // 输出结果存入body，发生异常的情况下，不会改变传入的body
                                    AcisOptions* ao = NULL);

/**
 * @brief		根据输入的顶点，创建wire body，in_body为空则创建新的body，非空则将创建的wire body合并到in_body
 * @details		根据输入的顶点创建wire body；in_body为空则创建新的body，非空则将创建的wire body合并到in_body；如果起点和重点重合，则创建闭合的body；相邻点不能是重合的（距离小于SPAresabs）
 * @param[in]	in_body			给定的需要添加wire的body，如果为空则会创建新的body
 * @param[in]	length_pts		给定的顶点数组的长度
 * @param[in]	array_pts[]		给定的顶点数组，未赋值部分默认为SPAposition(-9.2559631349317831e+61, -9.2559631349317831e+61, -9.2559631349317831e+61)
 * @param[out]	body			创建的wire body
 * @return		函数执行结果
 * @exception	acis_exception(WIRE_DUP_VERT)	如果有重复边，抛出异常WIRE_DUP_VERT
 *				acis_exception(ENDS_TOO_CLOSE)	如果有重复点，抛出异常ENDS_TOO_CLOSE
 *				acis_exception(NOT_BODY)	    in_body不指向一个BODY
 */
DECL_CSTR outcome gme_1_api_make_wire(BODY* in_body,            // 输入的in_body，为空则创建新的body（in_body将保持为空），非空则将创建的wire body合并到in_body
                                      int length_pts,           // 给定的顶点数组的长度（实际遍历的数组长度），>=1时可以正常产生body
                                      SPAposition array_pts[],  // 顶点数组
                                      BODY*& body,              // 输出结果body
                                      AcisOptions* ao = NULL);

/**
 * @brief		根据输入的顶点，创建wire body，in_body为空则创建新的body，非空则将创建的wire body合并到in_body
 * @details		根据输入的顶点创建wire body；in_body为空则创建新的body，非空则将创建的wire body合并到in_body；如果起点和重点重合，则创建闭合的body；相邻点不能是重合的（距离小于SPAresabs）
 * @param[in]	in_body			给定的需要添加wire的body，如果为空则会创建新的body
 * @param[in]	length_pts		给定的顶点数组的长度
 * @param[in]	array_pts[]		给定的顶点数组，未赋值部分默认为SPAposition(-9.2559631349317831e+61, -9.2559631349317831e+61, -9.2559631349317831e+61)
 * @param[out]	body			创建的wire body
 * @return		函数执行结果
 * @exception	acis_exception(WIRE_DUP_VERT)	如果有重复边，抛出异常WIRE_DUP_VERT
 *				acis_exception(ENDS_TOO_CLOSE)	如果有重复点，抛出异常ENDS_TOO_CLOSE
 *				acis_exception(NOT_BODY)	    in_body不指向一个BODY
 */
DECL_CSTR outcome gme_2_api_make_wire(BODY* in_body,            // 输入的in_body，为空则创建新的body（in_body将保持为空），非空则将创建的wire body合并到in_body
                                      int length_pts,           // 给定的顶点数组的长度（实际遍历的数组长度），>=1时可以正常产生body
                                      SPAposition array_pts[],  // 顶点数组
                                      BODY*& body,              // 输出结果body
                                      AcisOptions* ao = NULL);

/*! @} */
/*! \addtogroup CSTRMODIFYAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */
/**
* Reverses the orientations of all coedges in the body.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Also reverses face orientations, the orientation of loops within the faces, 
* and the containment of double-sided faces. 
* <br><br>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param body
* body to be reversed.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_reverse_body(
			BODY* body,				// body to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief   对body取反
 * @details	将输入的body进行取反，并使用原指针返回
 * @param[in] body 要取反的body
 * @param[in] ao ACIS选项
 * @return 函数执行结果
 */
DECL_CSTR outcome gme_api_reverse_body(
			BODY* body,				
			AcisOptions* ao = NULL
	);

/**
 * @brief   对body取反
 * @param[in] body 要取反的body
 * @param[in] ao ACIS选项
 * @details	将输入的body进行取反，并使用原指针返回
			处理情况1：检查指针是否为空或不是指向body
			处理情况2：查找body的所有lump(>=0)
			处理情况3：处理每个lump
			处理情况4：处理每个lump中的每个shell(>=1)
			处理情况5：处理每个shell中的face和wire(>=0)
			处理情况6：对face和wire进行取反
 * @return outcome 函数执行结果
 */
DECL_CSTR outcome gme_1_api_reverse_body(
			BODY* body,				
			AcisOptions* ao = NULL
	);

/**
* Reverses the direction (sense) of a wire body.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function reverses the sense of a wire body by negating the sense
* of each coedge of each wire. If a wire has no branches or loops, and the first coedge of
* the wire was the start of the chain of coedges, then the first coedge of the
* reversed wire will be the new start of the chain of coedges. Otherwise, the
* wire's first coedge will not be changed.
* <br><br>
* <b>Errors:</b> Entity <tt>NULL</tt> or not a wire.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param body
* wire body to reverse.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_reverse_wire(
			ENTITY* body,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief 反转 wire body 的方向。
 * @details 反转 wire body 的方向，需要反转这个 wire body 中每个 wire 的方向。
 * @param[in] body 要反转的 wire body
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 * @exception NOT_WIRE 传入的实体不是 wire body
 */
DECL_CSTR outcome gme_api_reverse_wire(
			ENTITY* body,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief 反转 wire body 的方向。
 * @details 反转 wire body 的方向，需要反转这个 wire body 中每个 wire 的方向。
 *			case1:对body的合法性检查
 *			case2:检查是否是wire
 * @param[in] body 要反转的 wire body
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 * @exception NOT_WIRE 传入的实体不是 wire body
 */
DECL_CSTR outcome gme_1_api_reverse_wire(
			ENTITY* body,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
* Converts a double-sided body to a single-sided body.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> When <tt>fix_normals</tt> is set to <tt>FALSE</tt>, this function
* merely marks the faces as single-sided, without checking to see if the faces
* on the resulting single-sided body have consistent normal directions.  For
* performance purposes, the user may want to use this setting when confident
* that no such inconsistencies exist.  To guard against the creation of an
* <i>invalid body</i>; however, we recommend that this flag be set to
* <tt>TRUE</tt>.  In that case, the user may provide a list of faces (one on each
* shell of the body) via the argument <tt>ref_faces</tt>, which specifies
* those faces whose normals are to remain unchanged if any face normals are found
* to have an inconsistent orientation.  If this argument is not provided, or if
* any of the body's shells is not represented in the list, this function uses the
* first face on each of the unrepresented shells to determine the orientation of the
* result.
* <br><br>
* <b>Note:</b> Support for the <tt>fix_normals</tt> option does not extend to either
* non-manifold bodies or to non-orientable manifold sheets (for example, a Moebius
* strip). If this option is nevertheless used in conjunction with such objects,
* undesirable results can occur.  In the case of non-manifold bodies, face
* normals may be partially adjusted; in the case of non-orientable sheets, a system
* error (<tt>UNSUPPORTED_TOPOLOGY</tt>) will be thrown.
* <br><br>
* <b>Limitations:</b> The <tt>fix_normals</tt> option is not supported for
* non-manifold bodies or for non-orientable sheets.
* <br><br>
* <b>Errors:</b> The pointer to the body is <tt>NULL</tt>, one of more of the
* entities in <tt>ref_faces</tt> is not a face, one or more of the
* faces in <tt>ref_faces</tt> is owned by another body, or two or more of the
* faces in <tt>ref_faces</tt> belong to the same shell.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler 
 * <br><br>
* @param body
* the body to be modified.
* @param fix_normals
* flag to check and fix inconsistent face normals.
* @param ref_faces
* optional list of faces whose normals are to remain unchanged by the operation.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_body_to_1d(
		BODY*               body,
		logical             fix_normals,
		const ENTITY_LIST&  ref_faces = SpaAcis::NullObj::get_ENTITY_LIST(),
		AcisOptions*        ao = NULL
	);

/**
 * @brief				将双面body改为单面body，调整face的sense
 * @details				通过改变sides改为单面face，并根据需要调整提供的ref_faces的sense
 * @param[in]			body		所需转变的body
 * @param[in]			fix_normals	是否需要调整face的标志位
 * @param[in]			ref_faces	提供的需要调整face的列表
 * @param[in]			ao ACIS选项
 * @return outcome		执行结果
 */
DECL_CSTR outcome gme_api_body_to_1d(
		BODY*               body,
		logical             fix_normals,
		const ENTITY_LIST&  ref_faces = SpaAcis::NullObj::get_ENTITY_LIST(),
		AcisOptions*        ao = NULL
	);
/**
* Converts single-sided faces to double-sided faces.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function converts every single-sided face in the given body
* into a double-sided face; that is, a sheet face. Each shell will be owned by a separate lump.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param body
* body to be converted.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_body_to_2d(
			BODY* body,			// Body to convert to DOUBLE-SIDED
			AcisOptions* ao = NULL
	);
/**
 * @brief   		Converts single-sided faces to double-sided faces.
 * @param[out]  	body		body to be converted
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 **/
DECL_CSTR outcome gme_api_body_to_2d(
			BODY* body,			// Body to convert to DOUBLE-SIDED
			AcisOptions* ao = NULL
	);
/**
* Reverses the direction (sense) of a wire.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function reverses the sense of a wire by negating the sense
* of each coedge. If the wire has no branches or loops, and the first coedge of
* the wire was the start of the chain of coedges, then the first coedge of the
* reversed wire will be the new start of the chain of coedges. Otherwise, the
* wire's first coedge will not be changed.
* <br><br>
* <b>Errors:</b> Entity <tt>NULL</tt> or not a wire.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param wire
* wire to reverse.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_reverse_wire(
			WIRE* wire,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief 反转 wire 的方向。
 * @details 反转 wire 的方向，需要修改 wire 中每个 coedge 的方向。
 * @param[in] wire 要反转的 wire
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 */
DECL_CSTR outcome gme_api_reverse_wire(
			WIRE* wire,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief 反转 wire 的方向。
 * @details 反转 wire 的方向，需要修改 wire 中每个 coedge 的方向。
 *			case1:wire为单链，将coedge反转后，把wire的首个coedge设置为原wire的最后一个coedge
 *			case2:wire为环或者带分支，将coedge反转后，把wire的首个coedge设置为第二个coedge
 * @param[in] wire 要反转的 wire
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 */
DECL_CSTR outcome gme_1_api_reverse_wire(
			WIRE* wire,					// wire to reverse
			AcisOptions* ao = NULL
	);

/**
* Reverses the sense of a face.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> This API function reverses the sense of a face; i.e., makes the
* face material void (flips the normal). Also, alters the senses of the coedges to
* avoid changing the shape of the face.
* <br><br>
* <b>Errors:</b> Pointer to face is <tt>NULL</tt> or not to a <tt>FACE</tt>.
* <br><br>
* <b>Limitations:</b> The function does not check to see if the face belongs to a solid,
* nor does it compensate for side effects caused by reversal of the face. The user
* must ensure that the function is called only for independent faces.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param face
* same face is modified.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_reverse_face(
			FACE*& face, 				// face to reverse
			AcisOptions* ao = NULL
	);

/**
 * @brief     	翻转面的方向，并翻转面中所有loop的coedge的方向
 * @details     面中可以有多个loop，函数会遍历所有的loop和所有的coedge;
 *				经过测试发现翻转的是面的sense，而face对应的surface方向不会变化
 * @param[out]	face        想要反转的面face
 * @exception	指向面的指针为NULL   报错NULL_FACE
 *			    传入的指针不指向face 报错ACIS_EXCEPTION_ACCESS_VIOLATION
*/
DECL_CSTR outcome gme_api_reverse_face(
			FACE*& face, 				// 想要反转的面face
			AcisOptions* ao = NULL
	);

/**
* Modifies an enclosing set of faces from void bounding to material bounding.
* <br><br>
* <b>Role:</b> This API function walks outward from the face along the closest radial
* enclosing faces until a volume is enclosed or <tt>NULL</tt> coedges are encountered.
* Changes the containment data on the faces that are detected so they no longer
* contain a void. A double-sided, <tt>OUTSIDE</tt> face is changed to single-sided (unless it is
* detected twice in the search) and a single-sided face is changed to double-sided, <tt>INSIDE</tt>. If
* the lumps argument is <tt>TRUE</tt>, search for lumps that contain or are contained by
* the face group detected, and change the face containment information to reflect
* a filling of the void. Does not change any lumps that are not directly contained
* or containing; i.e., are walled-off from the void, containment-wise, by another
* lump. Merges any changed lumps into the original lump. Requires no action if the
* side of the face given is already a material containing.
* <br><br>
* <b>Errors:</b> Pointer to face is <tt>NULL</tt> or not to a <tt>FACE</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param face
* input face.
* @param sense
* inside/outside sense with respect to the input face.
* @param lumps
* search for lumps if <tt>TRUE</tt>.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_enclose_void(
			FACE* face,				// Face from which to begin enclosing
			REVBIT sense,			// Side of face to enclose upon
			logical lumps,			// If TRUE, look for lumps inside volume
			AcisOptions* ao = NULL
	);

/**
* @brief	将一组空心的封闭面转换为实体面
* @param[in]	face    该面为封闭操作的起点，操作将从这个面开始沿径向向外扩展，直到找到一个封闭体或遇到 NULL 的 coedges
* @param[in]	sense	表示面的一侧的参数，指定应该封闭哪一侧        
* @param[in]	lumps   如果该参数为 TRUE，则函数会查找并处理包含或被封闭体所包含的块体（lumps）
* @param[in]	ao		ACIS属性
* @return	封闭操作完毕的一系列面
* @details         该接口可处理以下情况：
*                  1)非法输入
*                  2）block实体
*                  3）sphere实体
*                  4）cuboid实体
*                  5）pyramid实体 
* 
**/
DECL_CSTR outcome gme_api_enclose_void(
			FACE* face,				   // 系列需要封闭的面里的第一个
			REVBIT sense,			   // 要封闭的面的一侧
			logical lumps,			   // 如果为真，找到volume中的lumps
			AcisOptions* ao = NULL     // acis选项
	); 


// Recomputes the bs3_surface approximation (to a requested tolerance),
// always using the newer, more robust approach.
// It also removes internal double knots whenever possible.
/**
* Recomputes the 3D B-spline %surface approximation, using the newer algorithm.
* <br><br>
* <b>Role:</b> Recomputes the 3D B-spline %surface approximation (to a requested
* tolerance), always using the newer, more robust approach. It also removes
* internal double knots whenever possible. If the requested tolerance is
* non-positive, <tt>SPAresfit</tt> is used.
* <br><br>
* The 3D B-spline %surface is returned, if requested. It is still owned by the face's
* <tt>surface</tt>, however.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param face
* input %spline face.
* @param requested_tol
* requested fit tolerance.
* @param fit_sur
* output bs3_surface.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_accurate_bs3_approximation(
		FACE* face,
		double requested_tol,
		bs3_surface& fit_sur = SpaAcis::NullObj::get_bs3_surface(),
		AcisOptions* ao = NULL
	);

// Recomputes the bs3_surface approximation (to a requested tolerance)
// using the default method for the particular spl_sur on the spline of the face.
/**
* Recomputes the <tt>bs3_surface</tt> approximation, using the default algorithm.
* <br><br>
* <b>Role:</b> Recomputes the <tt>bs3_surface</tt> approximation (to a requested tolerance)
* using the default method for the particular <tt>spl_sur</tt> on the <tt>spline</tt> of the face.
* If a non-negative <tt>requested_tol</tt> is supplied, the
* new <tt>bs3_surface</tt> approximation will be computed to that fit tolerance,
* otherwise a default tolerance is used if there is not already an
* approximation there.
* <br><br>
* The fit tolerance of the <tt>bs3_surface</tt> approximation is returned.  Also,
* the <tt>bs3_surface</tt> is returned, if requested.  It is still owned by
* the face's <tt>surface</tt>, however. The <tt>achieved_tol</tt> is returned as -1
* either if it failed to refit the entire B-spline to the requested
* tolerance, or if the fit was already good enough.
* The face's <tt>SURFACE</tt> is replaced if the B-spline was successfully
* refitted. This is so that applications can roll back to the state
* before the improved fit was created.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param face
* input %spline face.
* @param achieved_tol
* achieved fit tolerance.
* @param requested_tol
* requested fit tolerance.
* @param fit_sur
* output bs3_surface.
* @param force_regeneration
* always recompute.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_reset_bs3_approximation(
		FACE* face,
		double& achieved_tol,
		double requested_tol,
		bs3_surface& fit_sur = SpaAcis::NullObj::get_bs3_surface(),
		logical force_regeneration = FALSE,
		AcisOptions* ao = NULL
	);

/**
* Checks the wire and reorients it to make all coedges tip-to-tail. For closed wires, the given coedge becomes the starting coedge of the wire.
* <b>Technical Article:</b> <i>[Constructors](http://doc.spatial.com/articles/c/o/n/Component~Constructors_faba.html)</i>
* <br><br>
* <b>Role:</b> Orients the input wire so all the coedges are arranged tip-to-tail.
* In case of a closed input wire, the given coedge also becomes the starting coedge.
* If the wire is branched or has bad start/end topology connections, api_orient_wire fails, and 
* appropriate error messages are thrown.
* <br><br>
* <b>Limitations:</b> For wires with branches or bad start/end topology connections, nothing is done to modify (fix)
* the wire.
* <br><br>
* <b>Errors:</b> Wire is branched or has bad start/end topology connections.
* <br><br>
* <b>Effect:</b> Wire coedges are arranged tip-to-tail. Closed wires are also oriented such that given coedge is made the start pointer.
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param coed
* the coedge to be checked.
* @param ao
* ACIS options.
 */
DECL_CSTR outcome api_orient_wire(COEDGE* coed, AcisOptions* ao = NULL);

/**
 * @brief 检查wire并重新定向，使所有coedge按顺序排列。
 * @details 将输入的wire定向，使所有的coedge按顺序排列。对于闭合输入的wire，给定的coedge也成为起始coedge。如果wire是分支的或者有不良的起始/结束拓扑连接，gme_api_orient_wire将失败，并抛出适当的错误消息。
 * @param[in] coed 需要检查的coedge
 * @param[in] ao ACIS选项
 * @return outcome 执行结果
 */
DECL_CSTR outcome gme_api_orient_wire(COEDGE* coed, AcisOptions* ao = NULL);

/**
 * @brief 检查wire并重新定向，使所有coedge按顺序排列。
 * @details 将输入的wire定向，使所有的coedge按顺序排列。对于闭合输入的wire，给定的coedge也成为起始coedge。如果wire是分支的或者有不良的起始/结束拓扑连接，gme_api_orient_wire将失败，并抛出适当的错误消息。
 * @param[in] coed 需要检查的coedge
 * @param[in] ao ACIS选项
 * @details		case1：参数合法性检查（调用check系列函数）
                case2：传入的wire存在分支
                case3：传入的wire是环
                case4：传入的wire是开放的
 * @return outcome	输出结果
 */
 DECL_CSTR outcome gme_1_api_orient_wire(COEDGE* coed, AcisOptions* ao = NULL);

/**
* Recalculates pcurve on a coedge so that <tt>bs2_curve</tt> has a given tolerance.
* <br><br>
* <b>Role:</b> Recalculates pcurve (or adds one if not present) on a given
* coedge so that the pcurve's <tt>bs2_curve</tt> lies within a specified fit tolerance.
* It is the caller's responsibility to delete the requested <tt>bs2_curve</tt>.
* When the logical <tt>force_regeneration</tt> is <tt>TRUE</tt>, a new pcurve will be
* created even when the fit tolerance of the original pcurve is zero.
* Otherwise, we assume pcurves with fit tolerance of zero are precise.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param coed
* input coedge.
* @param tol
* fit tolerance.
* @param fit_cur
* output bs2_curve.
* @param use_approx_surf
* use %surface approx.
* @param force_regeneration
* always recompute.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_set_pcurve_tightness(
		COEDGE* coed,
		double tol,
		bs2_curve& fit_cur = SpaAcis::NullObj::get_bs2_curve(),
		logical use_approx_surf = FALSE,
		logical force_regeneration = FALSE,
		AcisOptions* ao = NULL
	);

//============================================================
// Curve modification

// Modify line endpoints
/**
* Modifies a linear edge to pass through two given points.
* <br><br>
* <b>Role:</b> Modifies a linear edge to pass through two given end points.
* This involves changing the positions of the two edge vertices as well as
* modifying the straight line, which serves as the edge geometry.
* <br><br>
* <dl>
* <b>Errors:</b> The entity is not a linear edge.
* <dd>&nbsp;The entity is not top level, i.e., it has an owner.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param line
* linear edge to modify.
* @param st_pt
* new start position.
* @param end_pt
* new end position.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_modify_line(
		EDGE* line,					// the line to modify
		const SPAposition& st_pt,	// new start position
		const SPAposition& end_pt,	// new end position
		AcisOptions* ao = NULL
	);

/**
 * @brief 修改直线 edge，使其通过两个给定的点。
 * @details 修改一条直线 edge，使其通过两个给定的点。需要修改 edge 的两个 vertex，修改EDGE的底层几何。
 * @param[in] line 需要修改的直线 edge
 * @param[in] st_pt 新的起点
 * @param[in] end_pt 新的终点
 * @param[in] ao ACIS 选项
 * @return outcome 执行结果
 * @exception NOT_TOP_LEVEL 传入的 edge 不是顶层实体
 * @exception NOT_A_LINE 传入的 edge 的几何类型不是直线
 */
DECL_CSTR outcome gme_api_modify_line(
		EDGE* line,					// the line to modify
		const SPAposition& st_pt,	// new start position
		const SPAposition& end_pt,	// new end position
		AcisOptions* ao = NULL
	);

// Modify arc parameters
/**
* Modifies an elliptical edge.
* <br><br>
* <b>Role:</b>  Modifies an elliptical edge according to the given ellipse and edge parameters.
* This involves changing the positions of the edge vertices as well as
* modifying the curve that serves as the edge geometry.
* <br>
* The specified start and end angles are for the edge. 
* If the sense of the edge is <tt>FORWARD</tt> these will be the same as the underlying
* curve's parameter values at the start and end of the edge.
* If the sense of the edge is <tt>REVERSED</tt> these will be negation of the underlying
* curve's parameter values at the start and end of the edge.
* <br><br>
* <dl>
* <b>Errors:</b> The entity is not a elliptical edge.
* <dd>&nbsp;The entity is not top level, i.e., it has an owner.</dd>
* </dl>
* <br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param ell
* elliptical edge to modify.
* @param center
* new center.
* @param normal
* new normal.
* @param major_axis
* new major axis.
* @param radius_ratio
* radius ratio.
* @param start_angle
* new edge start angle in radians.
* @param end_angle
* new edge end angle in radians.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_modify_ellipse(
		EDGE* ell,						// elliptical edge to modify
		const SPAposition& center,		// new center
		const SPAunit_vector& normal,	// new normal
		const SPAvector& major_axis,	// new major axis
		double radius_ratio,			// radius ratio
		double start_angle,				// new start angle in radians
		double end_angle,				// new end angle in radians
		AcisOptions* ao = NULL
	);

/**
 * @brief   		根据输入参数修改一个椭圆边。
 * @param[in]    	ell 			需要修改的椭圆边
 * @param[in]  	    center 			中心点
 * @param[in]    	normal 			法向
 * @param[in]    	major_axis 		主轴
 * @param[in]    	radius_ratio 	半径比
 * @param[in]    	start_angle 	起始角度
 * @param[in]    	end_angle 		终止角度
 * @param[in]  	    ao 				ACIS 选项
 * @details			若EDGE的sense为REVERSED，几何的参数值是原来的相反值；
 *					输入边非椭圆边或不是顶级实体将返回错误。
 * @return          outcome 		执行结果
 */
DECL_CSTR outcome gme_api_modify_ellipse(
		EDGE* ell,						// elliptical edge to modify
		const SPAposition& center,		// new center
		const SPAunit_vector& normal,	// new normal
		const SPAvector& major_axis,	// new major axis
		double radius_ratio,			// radius ratio
		double start_angle,				// new start angle in radians
		double end_angle,				// new end angle in radians
		AcisOptions* ao = NULL
	);

//======================================================================
// curve trimming

// trim one end of a curve at a position or its intersection with
// another curve
/**
* Trims one end of an edge at a given position or at the intersection with another edge.
* <br><br>
* <b>Role:</b> The edge is trimmed either at a given position or at the intersection
* with another edge. To trim to a position, specify a position in <tt>trim_pt</tt> and
* <tt>NULL</tt> for <tt>eray2</tt>. The edge is trimmed to the normal projection of the position
* onto the edge's %curve. To trim to the intersection with another edge, specify <tt>NULL</tt> for
* <tt>trim_pt</tt> and an <tt>entity_with_ray</tt> for <tt>eray2</tt>. The edge is trimmed to the
* intersection with the edge given in <tt>eray2</tt> that is closest to the ray given in
* <tt>eray2</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param eray1
* edge to trim and a position on the part to keep.
* @param trim_pt
* position to trim to or <tt>NULL</tt>.
* @param eray2
* edge to trim to or <tt>NULL</tt> returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_trim_curve(
		const entity_with_ray& eray1, // edge to trim + position on part to keep
		const SPAposition*   trim_pt, // position to trim to or NULL
		const entity_with_ray* eray2, // edge to trim to or NULL
		AcisOptions* ao = NULL
	);

DECL_CSTR outcome gme_api_trim_curve(
		const entity_with_ray& eray1, // edge to trim + position on part to keep
		const SPAposition*   trim_pt, // position to trim to or NULL
		const entity_with_ray* eray2, // edge to trim to or NULL
		AcisOptions* ao = NULL
	);

// trim the middle of a curve
/**
* Trims the middle of an edge.
* <br><br>
* <b>Role:</b> Using the trim data, this API function computes two trim points on the
* edge to be trimmed. If <tt>trim_pt1</tt> or <tt>trim_pt2</tt> is non-<tt>NULL</tt>, the corresponding trim
* point is the normal projection of the position on the edge's %curve; otherwise, the trim
* point is the intersection of the edges closest to the ray associated with
* <tt>trim_r1</tt> or <tt>trim_r2</tt>. The action performed depends on whether the edge is closed
* and periodic.
* <br><br>
* For a closed periodic edge, only a single edge results from the trim. The part
* of the edge on which the pick was made is removed. The <tt>edge</tt> is <tt>NULL</tt>.
* <br><br>
* For a non-periodic edge, the part of the edge between the trim points is
* removed. If the trim points are both on the interior of the edge; i.e., they
* are not the start or end points, the trim results in two edges. The original
* edge is modified as the first edge, and the second edge is returned in
* <tt>edge</tt>. If one of the trim points is not in the interior of the edge, the
* original edge is modified, and <tt>edge</tt> is <tt>NULL</tt>.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param crv
* edge to trim and a position on the part to keep.
* @param trim_pt1
* position to trim to or <tt>NULL</tt>.
* @param trimr1
* edge to trim to or <tt>NULL</tt>.
* @param trim_pt2
* position to trim to or <tt>NULL</tt>.
* @param trimr2
* edge to trim to or <tt>NULL</tt>.
* @param edge
* newly created edge or <tt>NULL</tt> returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_trim_middle(
		const entity_with_ray&  crv,   // edge to trim + position on part to trim
		const SPAposition* trim_pt1,   // position to trim to or NULL
		const entity_with_ray* trimr1, // edge to trim to or NULL
		const SPAposition* trim_pt2,   // position to trim to or NULL
		const entity_with_ray* trimr2, // edge to trim to or NULL
		EDGE*& edge,				   // new EDGE created (may be NULL)
		AcisOptions* ao = NULL
	);

// Trim two curve to their intersection

/**
 * @brief      根据给定的点或者曲线，计算出要修剪边上的修剪点，并返回修剪后的曲线
 * @param[in]  crv       要修剪的曲线实体，包含曲线及其射线信息
 * @param[in]  trim_pt1  第一个修剪点位置，如果不为 NULL，则优先使用该点进行修剪
 * @param[in]  trimr1    第一个修剪参考曲线，如果 trim_pt1 为 NULL，则使用该曲线与目标曲线的交点进行修剪
 * @param[in]  trim_pt2  第二个修剪点位置，如果不为NULL，则优先使用该点进行修剪
 * @param[in]  trimr2    第二个修剪参考曲线，如果 trim_pt2 为 NULL，则使用该曲线与目标曲线的交点进行修剪
 * @param[out] edge      用于存储修剪后新生成的边，如果未生成新边则返回 NULL
 * @param[in]  ao        ACIS 的选项参数，用于控制操作的选项
 * @details   如果 trim_pt1 或 trim_pt2 为非 NULL，则相应的修剪点是边曲线上位置的法向投影。否则，修剪点是与trim_r1或关联的射线最接近的边的交点
 *			  对于封闭的周期性边，修剪只会产生一条边。边的起点时距离 crv 所含射线最近的修剪点，边的终点为另一个修剪点；edge 返回 NULL
 *            对于非周期性边，将移除修剪点之间的边的部分。
 *			  如果两个修剪点都在边的内部（即它们不是边的起点或终点）则修剪会产生两条边；原始边被修改为第一条边，其终点改为距离原始边起点最近的修剪点；第二条边返回 edge，其起点为另一个修剪点，终点为原始边的终点。
 *			  如果其中一个修剪点不在边的内部，则修改原始边，edge 为 NULL。如果其中一个修剪点为 crv 的起点，则将曲线内的修剪点作为曲线起点；反之则曲线内的修剪点作为曲线终点
 * @exception acis_exception(NOT_A_CURVE)  crv 中的 ENTITY 不为 CURVE的时候报错 NOT_A_CURVE
 *			  acis_exception(NO_INTERSECTIONS);  当trimr1的曲线或者trimr2的曲线在crv上没有交点的时候报错 NO_INTERSECTIONS
 *			  acis_exception(NO_TRIM_ITEM);  // 当trim_pt1和trimr1，或者trim_pt2和trimr2都为NULL时报错 NO_TRIM_ITEM
 * @return     outcome   执行结果
 */
DECL_CSTR outcome gme_api_trim_middle(
		const entity_with_ray&  crv,   // edge to trim + position on part to trim
		const SPAposition* trim_pt1,   // position to trim to or NULL
		const entity_with_ray* trimr1, // edge to trim to or NULL
		const SPAposition* trim_pt2,   // position to trim to or NULL
		const entity_with_ray* trimr2, // edge to trim to or NULL
		EDGE*& edge,				   // new EDGE created (may be NULL)
		AcisOptions* ao = NULL
	);

/**
* Trims two edges to their intersection.
* <br><br>
* <b>Role:</b> This API function trims the two edges, <tt>crv1</tt> and <tt>crv2</tt>, to the intersection
* that is the closest to the average of the two rays.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param crv1
* edge to trim and a position on the part to keep.
* @param crv2
* edge to trim and a position on the part to keep.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_trim_2curves(
		const entity_with_ray& crv1,	// edge to trim + position on part to keep
		const entity_with_ray& crv2,	// edge to trim + position on part to keep
		AcisOptions* ao = NULL
	);

// Trim a list of curves so that they form a connected chain
/**
* Trims a list of edges so that they form a contiguous chain.
* <br><br>
* <b>Role:</b> This API function adds all edges in the input list to the entity list
* <tt>trimmed_crvs</tt>. If an edge appears in the input list more than once, it is copied
* and the copy is added to <tt>trimmed_crvs</tt>. Each pair of edges is then trimmed using
* <tt>api_trim_2curves</tt>. If <tt>close</tt> is <tt>TRUE</tt>, the first and last edges are also trimmed.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param num_crv
* number of edges.
* @param crvs
* array of edges.
* @param close
* whether to form a closed chain or not.
* @param trimmed_crvs
* list of trimmed edges returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_trim_chain(
		int num_crv,                 // number of edges
		const entity_with_ray* crvs, // array of edges
		logical close,               // == TRUE to form a closed chain
		ENTITY_LIST& trimmed_crvs,   // list of edges trimmed
		AcisOptions* ao = NULL
	);


/**
* Fillets a wire at a given vertex.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param vert
* vertex to fillet at.
* @param radius
* radius of fillet.
* @param edge1
* for future use.
* @param edge2
* for future use.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_fillet_vertex(
		VERTEX* vert,
		double radius,
		EDGE* edge1 = NULL,
		EDGE* edge2 = NULL,
		AcisOptions* ao = NULL
	);

/**
 * Set specific options for <tt>api_chamfer_wire_vertex</tt>.
 * <br><br>
 * <b>Limitations: </b> Not implemented yet.
 **/
class DECL_CSTR chamfer_wire_options : public ACIS_OBJECT
{
	private:

		logical	check_self_int;

	public:

		/**
		 * Default constructor
		 */
		chamfer_wire_options() : check_self_int( FALSE ) {}

		/**
		 * Destructor
		 */
		virtual ~chamfer_wire_options() {}

		// Not implemented yet
//		logical get_self_int() const { return check_self_int; }

//		void set_self_int( logical flag ) { check_self_int = flag; }
};

// Chamfers a wire at a given vertex
/**
* Chamfers a wire at a given vertex.
* <br><br>
* <b>Role:</b> Replaces a vertex with a linear edge at a given offset.
* The offset is calculated relative to the incoming pair of edges, not the vertex.
* The new edge and vertices will meet the two edges that are connected to the 
* given vertex.
* <br><br>
* <b>Limitations:</b> The vertex is connected to two edges.
* <br><br>
* The vertex is not smooth, i.e. the tangential directions of the edges are different.
* <br><br>
* Different offsets from the vertex are not supported.
* <br><br>
* The operation should be performed for one vertex at a time and only that vertex will be removed.
* <br><br>
* <tt>wire-body</tt> self-intersection is not detected.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param ver
* vertex to chamfer.
* @param offset
* offset of the chamfer.
* @param co
* for future use, pass <tt>NULL</tt> if <tt>ao</tt> is passed.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_chamfer_wire_vertex(
		VERTEX* ver,
		double offset,
		chamfer_wire_options* co = NULL,
		AcisOptions* ao = NULL
	);

/*! @} */
/*! \addtogroup CSTROTHERSAPI
 *  \brief Defined at <cstrapi.hxx>, SPAcstr
 *  @{
 */

/**
* Determines if a wire or a single-wire body is closed.
* <br><br>
* <b>Role:</b> The API function returns a successful outcome if the wire is closed. It
* does not alter the model.
* <br><br>
* The wire is considered to be closed if it contains no terminal vertices.  Accordingly,
* a wire with a "tadpole" topology is considered to be open.
* <br><br>
* This function is overloaded. This signature of the API function will be removed in a future
* release. The signature of <tt>api_closed_wire</tt> that takes a <tt>WIRE</tt> instead of a <tt>BODY</tt> should
* be used instead.
* <br><br>
* <b>Errors:</b> The pointer to a body is <tt>NULL</tt> or does not point to a wire body.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param body
* wire body to be examined.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_closed_wire(
			BODY* body,				
			AcisOptions* ao = NULL
	);

/**
 * @brief Determines if a wire or a single-wire body is closed.
 * @param[in] body wire body to be examined.
 * @param[in] ao ACIS options.
 **/
DECL_KERN outcome gme_api_closed_wire(BODY* body, AcisOptions* ao = NULL);

/**
 * @brief		   检测WIRE对象是否是闭的。
 * @param[in] wire 被检测的WIRE对象。
 * @param[in] ao   ACIS选项。
 * @details		   将BODY转换为WIER对象，再利用第二个重载进行判断。
				   处理情况1：参数合法性检查（调用check系列函数）
				   处理情况2：将BODY对象转换为WIRE对象
 * @return  	   outcome 输出结果
 **/
DECL_KERN outcome gme_1_api_closed_wire(BODY* body, AcisOptions* ao = NULL);

/**
* Determines if a wire or a single-wire body is closed.
* <br><br>
* <b>Role:</b> The API function returns a successful outcome if the wire is closed. It
* does not alter the model.
* <br><br>
* The wire body is considered to be closed if it contains no terminal vertices.  Accordingly,
* a wire with a "tadpole" topology is considered to be open.
* <br><br>
* This function is overloaded. This signature of the API function will persist in the future
* and should be used instead of the one that takes a <tt>BODY</tt>.
* <br><br>
* <b>Errors:</b> The pointer to a body is <tt>NULL</tt> or does not point to a wire body.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param wire
* wire to be examined.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_closed_wire(
			WIRE* wire,				// wire to be tested for being closed.
			AcisOptions* ao = NULL
	);

/**
 * @brief Determines if a wire or a single-wire body is closed.
 * @param[in] wire wire to be examined.
 * @param[in] ao ACIS options.
 **/
DECL_KERN outcome gme_api_closed_wire(WIRE* wire, AcisOptions* ao = NULL);

/**
 * @brief		   检测WIRE对象是否是闭的。
 * @param[in] wire 被检测的WIRE对象。
 * @param[in] ao   ACIS选项。
 * @details		   先取WIRE中所有的EDGE，若只有一个EDGE，则判断该EDGE是否是闭的；
 *				   若有多个EDGE，则取WIRE中所有点进行判断，若存在一个点的关联实体
 *				   仅有一个，则被检测WIRE是开的。
				   处理情况1：参数合法性检查（调用check系列函数）
				   处理情况2：根据EDGE的个数进行分类检测
				   处理情况3：根据VERTEX关联的实体数进行结果判断
 * @return  	   outcome 输出结果
 **/
DECL_KERN outcome gme_1_api_closed_wire(WIRE* wire, AcisOptions* ao = NULL);

/**
* Determines if a wire or a single-wire body is closed.
* <br><br>
* <b>Role:</b> The API function returns <tt>TRUE</tt> via the <tt>is_closed</tt> argument if the wire is closed. It
* does not alter the model.
* <br><br>
* The wire body is considered to be closed if it contains no terminal vertices.  Accordingly,
* a wire with a "tadpole" topology is considered to be open.
* <br><br>
* <b>Errors:</b> The pointer to a body is <tt>NULL</tt> or does not point to a wire body.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param wire
* wire to be examined.
* @param is_closed
* logical used to return result
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_closed_wire(
			WIRE* wire,				// wire to be tested for being closed.
			logical& is_closed,
			AcisOptions* ao = NULL
	);

/**
 * @brief Determines if a wire or a single-wire body is closed.
 * @param[in] wire wire to be examined.
 * @param[out] is_closed logical used to return result
 * @param[in] ao ACIS options.
 **/
DECL_KERN outcome gme_api_closed_wire(WIRE* wire, logical& is_closed, AcisOptions* ao = NULL);

/**
 * @brief		   检测WIRE对象是否是闭的。
 * @param[in] wire 被检测的WIRE对象。
 * @param[in] ao   ACIS选项。
 * @details		   先取WIRE中所有的EDGE，若只有一个EDGE，则判断该EDGE是否是闭的；
 *				   若有多个EDGE，则取WIRE中所有点进行判断，若存在一个点的关联实体
 *				   仅有一个，则被检测WIRE是开的。
				   处理情况1：参数合法性检查（调用check系列函数）
				   处理情况2：根据EDGE的个数进行分类检测
				   处理情况3：根据VERTEX关联的实体数进行结果判断，得出is_closed的值
 * @return  	   outcome 输出结果
 **/
DECL_KERN outcome gme_1_api_closed_wire(WIRE* wire, logical& is_closed, AcisOptions* ao = NULL);

/**
* Finds a planar face with the given normal direction.
* <br><br>
* <b>Role:</b> Given a direction <i>d</i>, finds the planar face with normal <i>n</i> so that <i>d.n</i>
* is positive and has greatest value for any face of the body. If several faces
* have equal greatest value of <i>d.n</i>, it returns the face with greatest value of <i>p.d</i>,
* where <i>p</i> is a point on the face. Takes account of the body transformation.
* <br><br>
* Retrieves <tt>NULL</tt> if no face found with <i>d.n</i> positive.
* <br><br>
* <dl>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a <tt>BODY</tt>.
* <dd>&nbsp;Zero length direction vector specified.</dd>
* </dl>
* <br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* body containing face sought.
* @param direction
* approximate direction of face normal.
* @param face
* found face returned or <tt>NULL</tt> returned if no face found.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_find_face(
			BODY* body,							// body containing face to be selected
			const SPAunit_vector& direction,	// normal direction of face desired
			FACE*& face,						// face returned
			AcisOptions* ao = NULL
	);

/**
 * @brief     	给定方向d，找到具有法向量n的平面，使得d.n为正，并且对body的任何面都具有最大值。
 * @details     如果多个面具有相等的最大d.n值，则返回具有最大p.d值的面，其中p是面上的一个点。
 *				考虑到body本身，如果找不到d.n为正的面，则返回NULL。
 * @param[in]	body			传入的待寻找适合的平面的body
 * @param[in]	direction       所需面的法向
 * @param[out]	face			输出找到的面，若找不到适合的面返回NULL
 * @return		函数执行结果	
 * @exception	acis_exception(NULL_BODY)	body为空的情况，报错NULL_BODY
 *				acis_exception(API_FAILED)	body中不具有平面法向量为n，使得d.n为正的平面，报错API_FAILED
 * @note		对于多个面具有相等的最大d.n值的情况，应该返回具有最大p.d值的面，其中p是面上的一个点，
 *				经测试这种情况下api_find_face找到的面可能不是具有最大p.d值的面，而gme_api_find_face对于边缘为直线的面，
 *				找到的一定是具有最大p.d值的面
 */
DECL_CSTR outcome gme_api_find_face(
			BODY* body,							// body containing face to be selected
			const SPAunit_vector& direction,	// normal direction of face desired
			FACE*& face,						// face returned
			AcisOptions* ao = NULL
	);

/**
* Finds the vertex closest to given position.
* <br><br>
* <b>Role:</b> Given a position and a body, finds the vertex of the body
* closest to that position. If several vertices are equidistant from the given
* position, any one may be returned.
* <br><br>
* Returns <tt>NULL</tt> if no vertex found.
* <br><br>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* body containing vertex sought.
* @param pos
* given position in global coordinates.
* @param vertex
* found vertex returned or <tt>NULL</tt> returned if no vertex found.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_find_vertex(
			BODY* body,				// body containing vertex to be
									// selected
			const SPAposition& pos,	// point near to desired vertex
			VERTEX*& vertex,		// vertex found
			AcisOptions* ao = NULL
	);

DECL_CSTR outcome gme_api_find_vertex(
			BODY* body,				// body containing vertex to be
									// selected
			const SPAposition& pos,	// point near to desired vertex
			VERTEX*& vertex,		// vertex found
			AcisOptions* ao = NULL
	);
/**
* Gets a list of the coedges of a body that is a single unbranched wire.
* <br><br>
* <b>Role:</b> This API function returns a list of the coedges of a body that is a single
* unbranched wire in a list supplied by the caller.
* <br><br>
* The sequence of the edges and coedges of the wire can be forward or backward.
* <br><br>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a wire body.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* wire body to be examined.
* @param list
* list of coedges returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_wire_to_chain(
			BODY* body,				// wire to be expanded
			ENTITY_LIST& list,		// list of coedges returned
			AcisOptions* ao = NULL
	);

/**
 * @brief   		  获取一个单一无分支 wire body 的所有 coedges 列表.
 * @param[in]     body wire body
 * @param[out]  	list 返回 coedge 列表
 * @param[in]  	  ao ACIS 选项
 * @details       获取一个单一无分支 wire body 的所有 coedges 列表.
 * @return        outcome 执行结果
 */
DECL_CSTR outcome gme_api_wire_to_chain(BODY* body,         // wire to be expanded
                                        ENTITY_LIST& list,  // list of coedges returned
                                        AcisOptions* ao = NULL);

/**
* Computes and returns the value of the arclength metric for the given edge.
* <br><br>
* <b>Role:</b> This API function computes and returns the value of the arclength metric.
* <br><br>
* A metric value of zero indicates 100% arc length parameterized. A metric value greater than one may
* cause unpredictable results. A metric value over 100 is typically a bad %curve.
* <br><br>
* <b>Errors:</b> Pointer to edge is <tt>NULL</tt>, pointer is not to an <tt>EDGE</tt>, or <tt>EDGE</tt> is not part
* of a <tt>BODY</tt>.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param edge
* input edge.
* @param metric
* returned edge geometry metric value.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_arclength_metric(
	EDGE* edge,					// The input edge
	double& metric,				// The edge geometry metric
	AcisOptions* ao = NULL
	);

/** 
* @brief       计算并返回给定边的弧长度量的值
* @param[in]   edge  需要计算的edge
* @param[out]  metric  计算结果（弧长参数化的度量值）
* @details     此API的结果表示输入edge的弧长参数化程度，若度量值为0，表示其100%弧长参数化，
*              若度量值大于1，结果可能不可预测，度量值大于100通常是较差的曲线。
* @return      执行结果
* @see         sg_curve_arclength_metric 底层计算方法
*/
DECL_CSTR outcome gme_api_edge_arclength_metric(
	EDGE* edge,					// 输入的 edge
	double& metric,				// edge 弧长参数化的度量值
	AcisOptions* ao = NULL
);

/** 
* @brief       计算并返回给定边的弧长度量的值
* @param[in]   edge  输入的edge
* @param[out]  metric  输出弧长参数化的度量值
* @param[in]    ao ACIS选项
* @details     此API的结果表示输入edge的弧长参数化程度，若度量值为0，表示其100%弧长参数化，若度量值大于1，结果可能不可预测，度量值大于100通常是较差的曲线。
*               处理情况1：使用check_edge检查edge是否为NULL指针或ENTITY是否为EDGE，
*				处理情况2：使用check_edge_geom检查或if判断（ACIS_api使用逻辑）edge的几何指针是否为NULL
*               处理情况3：使用gme_1_api_edge_arclenth_metric计算不同sat文件的弧长度量值
*               处理情况4：使用api_edge_arclength_param进行弧长参数化，再通过gme_1_api_edge_arclenth_metric计算弧长度量值
* @return      执行结果
* @note           1.输入的edge不能为空且必须为有效的EDGE指针
*				  2.输入的edge的几何指针不能为空
* @see         sg_curve_arclength_metric 底层计算方法
*/
DECL_CSTR outcome gme_1_api_edge_arclength_metric(
    EDGE* edge,                    // 输入的 edge
    double& metric,                // edge 弧长参数化的度量值
    AcisOptions* ao = NULL
);

/**
* Determines if a loop is internal or external.
* <br><br>
* <b>Role:</b> Sets <tt>if_external</tt> to <tt>FALSE</tt> if the loop is a hole loop.
* Sets it to <tt>TRUE</tt> if the loop is not a hole loop. 
* <br><br>
* For more information on the clasification of loops refer to the 
* <i>[Classification of Loops](http://doc.spatial.com/articles/l/o/o/Loop.html#Classification_of_Loops)</i>
* section in the Technical Article <i>[Loop](http://doc.spatial.com/articles/l/o/o/Loop.html)</i>.
* <br><br>
* <b>Errors:</b> Pointer to loop is <tt>NULL</tt> or not to a <tt>LOOP</tt>.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param loop
* loop to be examined.
* @param if_external
* <tt>TRUE</tt> returned if external loop.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_loop_external(
			LOOP* loop,					// loop to examine for external/internal
			logical* if_external, 				// T or F answer
			AcisOptions* ao = NULL
	);

/**
 * @brief   		确定环是内部环（孔洞）还是外部环（边界或u、v分离边）
 * @param[in]    	loop 待检测的环
 * @param[out]  	if_external 若为孔洞环则将if_external置为FALSE，否则将其置为TRUE
 * @param[in]  	    ao ACIS 选项
 * @details
 * 处理情况1: 参数合法性检查，是否为空环，返回错误信息
 * 处理情况2: 如果环对应的面只有一个环，该环一定为外环
 * 处理情况3: 多个环，检查其loop_type，如果是外环、u分离环、v分离环、uv分离环，则将if_external置为true
 *								     如果是孔环则置为false
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_loop_external(LOOP* loop,
										logical* if_external,
										AcisOptions* ao = NULL
	);


/**
* Classifies regions on a given body as being either manifold or nonmanifold.
* <br><br>
* <b>Role:</b> Returns all nonmanifold edges and vertices.
* <br><br>
* <b>Definition of Nonmanifold</b>
* <br><br>
* Formally, a nonmanifold edge has more than two faces around it, and a
* nonmanifold vertex has elements that can only be connected topologically through
* that vertex. For example, two cones meeting at their apexes, or a vertex of a
* block with a dangling edge. For the purposes of this API function, three or more wire
* edges meeting at a vertex are also defined as nonmanifold.
* <br><br>
* <b>Information Returned</b>
* <br><br>
* The first three output arguments (<tt>mani_shells</tt>, <tt>mani_sheets</tt>, <tt>wire_edges</tt>) return
* the detected manifold shells, manifold sheets and the wire edges. Wire edges are
* returned in an entity list. Manifold sheets and shells are returned in arrays of
* entity lists, one list for each shell or sheet that contains its faces. Each
* array is terminated by an empty list.
* <br><br>
* The next output argument, <tt>lamina_faces</tt>, returns all laminar (covered on both
* sides) faces. Only planar laminar faces or laminar faces that use the same
* geometry are detected. The entity list stores them in pairs (first two are one
* face, next two are the second face, etc.). Detects laminar faces of opposing and
* same orientation.
* <br><br>
* The next two output arguments (<tt>edge_arcs</tt>, <tt>vertex_arcs</tt>) return all detected
* nonmanifold edges and nonmanifold vertices and all elements connected to them,
* whether sheets, lamina, manifold shells, or wire edges. Each list in either
* array begins with the nonmanifold edge or vertex, followed by the elements
* connected to them. The manifold shells and sheets are represented by a pointer
* that references the first face field to the entity list (in either return
* argument) that represents the shell or sheet. Before using this pointer, cast
* the contained face pointer to an <tt>ENTITY_LIST</tt>. The wire edges are stored in the
* list. Each lamina is stored as two sequential faces in the list. The arrays are
* terminated by empty lists.
* <br><br>
* Note that arguments <tt>mani_shells</tt>, <tt>mani_sheets</tt>, <tt>edge_arcs</tt>, and <tt>vertex_arcs</tt> are
* allocated by the API function and must be deleted via <tt>ACIS_DELETE</tt> at some point.
* <br><br>
* Locates all entities if connected to coedge graph, even if not in any shell or
* wire.
* <br><br>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a <tt>BODY</tt>.
* <br><br>
* <b>Limitations:</b> This API function assumes that the input body is more or less sane other
* than nonmanifold regions. Internal dangling sheet faces attached to a shell cause
* the shell to be interpreted as a sheet. Void shells that touch their peripheral
* shell or other void shells in a nonmanifold edge will be interpreted as part of
* the adjacent shell.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* Body to examine for manifold pieces.
* @param mani_shells
* Array of lists of faces returned (each list represents a manifold shell) Terminated by an empty list.
* @param mani_sheets
* Array of lists of manifold sheets returned Terminated by an empty list.
* @param wire_edges
* List of wire edges detected and returned.
* @param lamina_faces
* List of lamina (doubly covered) faces in pairs returned.
* @param edge_arcs
* Array of lists returned, each containing one nonmanifold edge followed by all elements connected to it. Terminated by an empty list.
* @param vertex_arcs
* Array of lists returned, each containing one nonmanifold vertex followed by all elements connected to it Terminated by an empty list.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_manifold_class(
			BODY* body,							//	Body to be classified
			ENTITY_LIST*& mani_shells,			//	Manifold shells
			ENTITY_LIST*& mani_sheets,			//	Manifold sheets
			ENTITY_LIST& wire_edges,			//	Wire edges
			ENTITY_LIST& lamina_faces,			//	Lamina faces in pairs
			ENTITY_LIST*& edge_arcs,			//	non-manifold edges
			ENTITY_LIST*& vertex_arcs,			//	non-manifold vertices
			AcisOptions* ao = NULL
	);

/**
* Gets a list of edges that share a given vertex.
* <br><br>
* <b>Role:</b> This API function returns a list of edges that share a specified vertex.
* <br><br>
* <b>Errors:</b> Pointer to vertex is <tt>NULL</tt> or not to a <tt>VERTEX</tt>.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param vertex
* vertex to be examined.
* @param edge_list
* list of edges returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_q_edges_around_vertex(
			VERTEX* vertex,				// the given vertex
			ENTITY_LIST* edge_list,		// the list of edges around the vertex
			AcisOptions* ao = NULL
	);

/**
 * @brief   		获取与给定 VERTEX 相关联的所有 EDGE 的列表
 * @param[in]    	vertex 给定顶点
 * @param[out]  	edge_list 与给定顶点相关联的所有 EDGE 的列表
 * @param[in]  	    ao ACIS 选项
 * @details         获取与给定 VERTEX 相关联的所有 EDGE 的列表
 * @return          outcome 执行结果
 */
DECL_CSTR outcome gme_api_q_edges_around_vertex(VERTEX* vertex,          // the given vertex
                                                ENTITY_LIST* edge_list,  // the list of edges around the vertex
                                                AcisOptions* ao = NULL);
												
/**
* Determines whether a shell is internal or external.
* <br><br>
* <b>Role:</b> The returned <tt>external</tt> argument will be set to: 0 for void, 1 for external, or 2 for unknown.
* <br><br>
* <b>Errors:</b> Pointer to shell is <tt>NULL</tt> or not to a <tt>SHELL</tt>.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param shell
* shell to be examined.
* @param external
* internal or external flag returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_shell_external(
			SHELL* shell, 						// shell to examine for internal/external
			int& external,						// enumerated answer
			AcisOptions* ao = NULL
	);

/**
* Determines the length of a wire body.
* <br><br>
* <b>Role:</b> This API function is overloaded. The signature of <tt>api_wire_len</tt> that takes a <tt>WIRE</tt> instead
* of a <tt>BODY</tt> may also be used.
* <br><br>
* <b>Errors:</b> Pointer to body is <tt>NULL</tt> or not to a wire body.
* <br><br>
* <b>Limitations:</b> Returns zero length if there is any error condition. If the
* given body has more than one wire, the function considers only the first wire.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param body
* given wire body.
* @param length
* length of the wire returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_wire_len(
			BODY* body,					// Wire body whose length is to be found
			double& length,				// Length of the wire body returned
			AcisOptions* ao = NULL
	);

/**
 * @brief     	根据给定的body计算body中所有的wire的长度和返回
 * @details     若输入的body为空或body中没有wire抛出异常，len = 0
 * @param[in]	body			输入待计算的body
 * @param[out]	length			输出wire中所有edge长度和的计算结果
 * @return		函数执行结果
 * @exception   acis_exception(NULL_BODY) body为空的情况，报错NULL_BODY
 *				acis_exception(NOT_WIRE_BODY) body非空但没有wire的情况，报错NOT_WIRE_BODY
 * @note		api_wire_len定义的注释中说如果一个body中有多个wire，则只计算第一个wire，
 *				但是测试中发现api_wire_len计算的实际上是body中所有wire的len和，因此我的
 *				gme_api_wire_len也遵循了计算所有wire的逻辑。这也符合这个函数名体现的作用。
 */
DECL_CSTR outcome gme_api_wire_len(BODY* body,      // 输入待计算的body
                                   double& length,  // 输出wire中所有edge长度和的计算结果
                                   AcisOptions* ao = NULL);

/**
 * @brief		计算一个wire body的长度
 * @details		根据输入的body计算其中第一个wire的所有edge的长度和
 *				处理情况1：使用check_wire_body函数进行参数合法性检查
 *				处理情况2：利用api_get_wires获取该body中的第一个wire
 *				处理情况3：使用gme_1_api_wire_len的重载计算该wire的长度
 * @param[in]	body 输入的body
 * @param[out]	length 输出第一个wire的长度
 * @param[in]	ao ACIS选项
 * @return		执行结果
 * @exception	当输入的body为空或者不是wire body时会抛出异常(由check_wire_body函数判断)
 * @note		文档说明如果该body中有多个wire，则只计算第一个wire；而ACIS实现中计算的是所有wire的长度和
 *				实现遵循文档逻辑
 */

DECL_CSTR outcome gme_1_api_wire_len(
									BODY* body,		// 输入的wire body
									double& length, // 输出第一个wire的长度
									AcisOptions* ao = NULL
									);

/**
* Determines the length of a wire.
* <br><br>
* <b>Role:</b> This API function is overloaded. The signature of <tt>api_wire_len</tt> that takes a <tt>BODY</tt> instead
* of a <tt>WIRE</tt> may also be used.
* <br><br>
* <b>Errors:</b> Pointer to wire is <tt>NULL</tt> or not to a wire.
* <br><br>
* <b>Limitations:</b> Returns zero length if there is any error condition.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param wire
* given wire.
* @param length
* length of wire returned.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_wire_len(
			WIRE* wire,					// Wire whose length is to be found
			double& length,				// Length of the wire body returned
			AcisOptions* ao = NULL
	);

/**
 * @brief     	根据给定的wire计算wire中所有edge长度和返回
 * @details     若输入的wire为空抛出异常，len = 0
 * @param[in]	wire			输入待计算的wire
 * @param[out]	length			输出wire中所有edge长度和的计算结果
 * @return		函数执行结果
 * @exception   acis_exception(NULL_WIRE) wire为空的情况，报错NULL_WIRE
 */
DECL_CSTR outcome gme_api_wire_len(WIRE* wire,      // 输入待计算的wire
                                   double& length,  // 输出wire中所有edge长度和的计算结果
                                   AcisOptions* ao = NULL);


/**
 * @brief		计算一个wire的长度.
 * @details		计算该wire包含的所有edge的长度和.
 *				处理情况1：使用check_wire函数进行参数合法性检查
 *				处理情况2：使用api_get_edges获取该wire的所有edge并遍历来计算长度和
 * @param[in]	wire 输入的wire
 * @param[out]	length 输出该wire的长度
 * @param[in]	ao ACIS选项
 * @return		执行结果
 * @exception	当输入的wire为空时会抛出异常(由check_wire函数判断)
 */
DECL_CSTR outcome gme_1_api_wire_len(
									WIRE* wire,		// 输入的wire
									double& length, // 输出该wire的长度
									AcisOptions* ao = NULL);

// Calculates pcurve's bs2_curve tolerance
/**
* Calculates a pcurve's <tt>bs2_curve</tt> tolerance.
* <br><br>
* <b>Role:</b> Calculates the fit tolerance of a pcurve's <tt>bs2_curve</tt> to the pcurve.
* This API function returns the fit tolerance of a pcurve's <tt>bs2_curve</tt> to the
* exact pcurve as a distance in 3-space. The logical <tt>use_approx_surf</tt> controls when
* the <tt>bs2_curve</tt> is evaluated through the face's approximating %surface to
* compute the tolerance. The logical <tt>approx_ok</tt> can be set to <tt>TRUE</tt> to use a
* quicker but less accurate computation.
* <br><br>
* <b>Effect:</b> Changes model
* <br><br>
* <b>Journal: </b> Not Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param coed
* input coedge.
* @param tol
* computed fit tolerance.
* @param use_approx_surf
* use %surface approx.
* @param approx_ok
* for quick tolerance calculation.
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_compute_pcurve_tightness(
		COEDGE* coed,
		double& tol,
		logical use_approx_surf = FALSE,
		logical approx_ok = TRUE,
		AcisOptions* ao = NULL
	);

// Recomputes bs3_surface approximation and bs2_curves on pcurves
// so that the bs2_curves lie within the given tolerance.
// tbrv
/**
 * @nodoc
 */
DECL_CSTR outcome api_set_edge_tightness(
		EDGE* edge,
		double requested_tol,
		double& achieved_tol,
		logical use_approx_surf = FALSE,
		logical force_regen = FALSE,
		AcisOptions* ao = NULL
	);
// STI end
// tbrv
/**
 * @nodoc
 */
DECL_CSTR outcome api_simplify_pcurve(
		COEDGE* coed,
		double fit = -1.0,
		AcisOptions* ao = NULL
	);

// Tighten up pcurve and surface fit tolerances as necessary so that
// their sum is less than requested_tol. Optionally perform extra
// calculations to see what tolerance we really achieved.
// tbrv
/**
 * @nodoc
 */
DECL_CSTR outcome api_set_coedge_tightness(
		COEDGE* coed,
		double requested_tol,
		double& achieved_tol = SpaAcis::NullObj::get_double(),
		AcisOptions* ao = NULL
	);



/**
* 
* Approximates the input EDGE(s) with a series of straight or circular edges.
* <br><br>
* <b>NOTE:</b> The signature of this API function may change in future releases of ACIS.
* <br><br>
* <b>Role:</b> This API function generates a series of straight or circular edges that approximate the given input edge.
* It also returns the tolerances achieved with each output edge with respect to the original edge. The function supports 
* two distinct workflows:
* <br><br>
* 1. A single edge can be approximated by the function. The output edges will span the length of the input edge from start to end.
* <br>
* 2. When two edges are used as input, the function returns matching lists of approximating edges. The number of edges returned will 
* be the same for both edges. Also, the normalized (0 to 1) parameter values at which each edge is split will match.
* Additionally, when two edges are used as input, 
* the direction of the approximation for the second edge will be reversed if the function checks and detects that the second edge 
* needs reversal. 
* The check for edge reversal is performed only if it is specified in the options object.
* <br><br>
* The approximating direction for the second edge will be reversed in the following cases:
* <br><br>
* 1. If the two input edges belong to the same <tt>FACE</tt> on the original <tt>BODY</tt>, the function uses the coedge sense bits 
* to check if the second edge is oriented in the same direction as the first edge. If it is not oriented correctly, the function 
* will reverse the approximation direction of the second edge.
* <br>
* 2. If the two input edges do not belong to the same face, then two checks are performed to see if the second edge needs 
* to be reversed. First, if either edge is closed, the start direction and end direction of the second edge is compared to 
* the start direction of the first edge. If both edges are not closed, then the start position and end position of the second edge 
* is compared to the start position of the first edge.
* <br><br>
* When the approximating direction is reversed, the sequence of approximating edges will stretch from the end of the second edge 
* to the start.
* <br>
* The actual achieved tolerances are also returned in two arrays of doubles. 
* The length of these arrays will match the number of edges returned in the <tt>ENTITY_LIST</tt> objects.
* The user is responsible for deleting the memory referenced by these pointers using <tt>ACIS_DELETE []</tt>.
* <br>
* <dl>
* <b>Errors:</b>
* </dl>
* <br>
* <b>Limitations:</b> Returns zero edges if there is any error condition.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param firstEdge
* first input Edge to be approximated.
* @param secondEdge
* optional second input Edge to be approximated. The parameter values at the splits for the second edge will 
* match the param values for the splits for the first edge.
* @param inputOpts
* options object that specifies the behavior of the API function.
* @param edgeList1 
* output list of edges created by approximating <tt>firstEdge</tt>.
* @param edgeList2
* output list of edges created by approximating <tt>secondEdge</tt> (if it was provided).
* @param actualFirstTol 
* list of doubles specifying the approximation error of each edge in <tt>edgeList1</tt> with respect to <tt>firstEdge</tt>.
* @param actualSecondTol 
* list of doubles specifying the approximation error of each edge in <tt>edgeList2</tt> with respect to <tt>secondEdge</tt> (if it was provided).
* @param ao
* ACIS options.
**/
DECL_CSTR outcome api_edge_approx_line_arc(EDGE *firstEdge, EDGE* secondEdge,
                                 SPA_edge_line_arc_options* inputOpts,
								 ENTITY_LIST& edgeList1,
								 ENTITY_LIST& edgeList2,
								 double*& actualFirstTol,
								 double*& actualSecondTol,
								 AcisOptions *ao = NULL);




/**
* Create points_segment_handle (Linked-List) from input vector of points.
* <br><br>
* <b>Role:</b> This API returns points_segment_handle list from vector of SPAposition.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param points
* Input vector of SPAposition
* @param segmentsHandle
* Returned linked list of points_segment_handle.
* @param opts
* segmentation_options
* @param ao
* ACIS options.
**/

DECL_CSTR outcome api_compute_points_segments ( const SPAposition_vector & points,
												points_segment_handle*& segmentsHandle,
												segmentation_options * opts = NULL ,
												AcisOptions *ao = NULL );

/**
 * @brief		根据输入的点数组创建链表结构的points_segment_handle。
 * @details		segmentation_options限定直线和圆弧的识别。
 * @param[in]	points  		输入点数组
 * @param[out]	segmentsHandle  返回points_segment_handle
 * @param[in]	opts         	分段选项
 * @param[in]	ao          	ACIS option
 * @return		函数执行结果
 */
DECL_CSTR outcome gme_api_compute_points_segments ( const SPAposition_vector & points,
												points_segment_handle*& segmentsHandle,
												segmentation_options * opts = NULL ,
												AcisOptions *ao = NULL );


/**
* Create wire body from input points_segment_handle (Linked-List).
* <br><br>
* <b>Role:</b> This API creates a wirebody from input points_segment_handle list.
* Geometry of edges in wirebody depending on points_segment_handle type while be
* either Straight or Circular Arc.
* <br><br>
* <b>Effect:</b> Read-only
* <br><br>
* <b>Journal: </b> Available
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
 * <br><br>
* @param segmentsHandle
* Linked list of points_segment_handle.
* @param wireBody
* Returned Wire body.
* @param opts
* segmentation_options
* @param ao
* ACIS options.
**/


DECL_CSTR outcome api_make_wire_from_points_segments ( points_segment_handle * segmentsHandle ,
													  BODY  *&wireBody,
													  segmentation_options * opts = NULL ,
													  AcisOptions *ao = NULL );

/**
 * @brief		根据输入的points_segment_handle创建直线和圆弧构成的线体
 * @details		创建的线体类型根据points_segment_handle的type确定
 * @param[in]	segmentsHandle	points_segment_handle
 * @param[out]	wireBody		返回的线体
 * @param[in]	opts			分段设置
 * @param[in]	ao 				ACIS options
 * @return		函数执行结果
 */
DECL_CSTR outcome gme_api_make_wire_from_points_segments ( points_segment_handle * segmentsHandle ,
													  BODY  *&wireBody,
													  segmentation_options * opts = NULL ,
													  AcisOptions *ao = NULL );


class fit_plane_options;

    
/**
* Creates a plane with least-square fit for a given set of points.
* <br><br>
* <b>Role:</b> This API creates a plane that fits to the given set of points in 3D.
* The plane is fit using least-square algorithim. At least 3 points should be supplied. 
* For cases with multiple possibilities of best-fit plane, any one of the possible planes is returned,
* for example: vertices of a cube or any regular solid, set of collinear points.
* <br><br>
* <b>Effect:</b> Read-only on input, new geometry is created.
* <br><br>
* <b>Journal:</b> Available
* <br><br>
* <b>Errors:</b> 
* <br>
* <tt>PLANE_FIT_INSUFFICIENT_POINTS:</tt> Not even 3 points supplied for fitting a plane.
* <br>
* <tt>NON_UNIQUE_FITPTS:</tt> Coincident fit points
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param points	
* the points unto which a plane is to be fitted
* @param fitting_plane
* the plane that is constructed
* @param fpo
* to be implemented in future
* @param ao
* ACIS options such as version and journal
**/

DECL_CSTR outcome api_fit_plane ( const SPAposition_vector & points,
								  plane					   & fitting_plane,
								  fit_plane_options		   * fpo=NULL,
								  const AcisOptions*       ao=NULL
								);

/**
 * @brief     输入空间中的一系列点，得到拟合的平面
 * @details     平面的质心为拟合平面上的点 平面的法向量由QR分解向量得出
 * @param[in]	points	空间中的点的vector
 * @param[out]	fitting_plane	得到的拟合平面
 * @param[in]	flo         
 * @param[in]	ao          
 * @return		函数执行结果
 * @exception	
 */
DECL_CSTR outcome gme_1_api_fit_plane(const SPAposition_vector& points, plane& fitting_plane, fit_plane_options* flo=NULL, const AcisOptions* ao=NULL);

/**
 * @brief     	输入用于拟合的点列，返回一个拟合的平面
 * @details     拟合平面以点集的质心为平面的根位置，其法向量方向与平均向量方向一致
 * @param[in]	point_list  用于拟合的点列
 * @param[out]	fitting_plane        返回的拟合平面
 * @param[in]	flo         
 * @param[in]	ao          
 * @return		函数执行结果
 * @exception	acis_exception(PLANE_FIT_INSUFFICIENT_POINTS) 当点列中不同的点数量小于3时抛出异常
 *				acis_exception(NON_UNIQUE_FITPTS) 当点列长度大于等于3但点列中不同的点小于3时抛出异常
 */
DECL_CSTR outcome gme_api_fit_plane ( const SPAposition_vector & points,
								  plane					   & fitting_plane,
								  fit_plane_options		   * fpo=NULL,
								  const AcisOptions*       ao=NULL
								);

class fit_line_options;

/**
* Fits a line in 3D from given points.
* <br><br>
* <b>Role:</b> This API constructs a line that best fits the given set of points. 
* At least 2 non-coincident points should be supplied.     
* <br><br>
* <b>Effect:</b> Read-only on input, new geometry is created.
* <br><br>
* <b>Journal:</b> Available
* <br><br>
* <b>Errors:</b> 
* <br>
* <tt>FIT_NO_SPAN:</tt> Attempt to fit curve to zero or one point.
* <br>
* <tt>NON_UNIQUE_FITPTS:</tt> Coincident fit points.
* <br><br>
* <b>Product(s):</b> 3D ACIS Exchange, 3D Viz Exchange, 3D ACIS Modeler
* <br><br>
* @param point_list	
* list of input positions
* @param line
* returned line that best fits the input list of points
* @param flo
* fit line specific options( for future use )
* @param ao
* ACIS options such as version and journal
**/

DECL_CSTR outcome api_fit_line ( const SPAposition_vector & point_list,
								  straight				  & line,
								  fit_line_options		  * flo = NULL,
								  const AcisOptions*      ao = NULL
								);



/**
 * @brief			输入圆心和半径，生成球体
 * @param[in]       center  球心的坐标
 * @param[in]       radius  球体半径
 * @param[out]      sph		返回的球体对象
 * @param[in]		ao		ACIS选项
 * @details			center参数用于传入球心的三维坐标信息，radius参数用于传入球体的半径信息。
 *					若传入的球体半径小于或者等于零，则抛出异常；若无异常抛出，则创建带有
 *					transform的sphere BODY，并将其保存在sph中。
					处理情况1：参数合法性检查（调用check系列函数）
					处理情况2：根据radius创建一个原点位于圆心的球体
					处理情况3：根据center对球体进行偏移
 * @return  		outcome 输出结果
 */
DECL_CSTR outcome gme_1_api_solid_sphere(		
		const SPAposition&   center,    // 球心坐标
		double               radius,    // 球体半径
		BODY*&               sph,       // 用以接收返回的球体对象
		AcisOptions*         ao = NULL  
	);

/**
 * @brief			输入圆心和半径，生成球体
 * @param[in]       center  球心的坐标
 * @param[in]       radius  球体半径
 * @param[out]      sph		返回的球体对象
 * @param[in]		ao		ACIS选项
 * @details			center 参数用于传入球心的三维坐标信息，radius 参数用于传入球体的半径信息。
 *					若传入的球体半径小于或者等于零，则抛出异常；若无异常抛出，则创建带有
 *					transform 的 sphere BODY，并将其保存在 sph 中。参数合法性检查（调用 check_pos_length 函数）,
 *					根据 radius 创建一个原点位于圆心的球体
 *					根据 center 对球体进行偏移
 *					处理情况1：正常的三维坐标和正半径，生成标准球体。
 *					处理情况2：半径为零，抛出 `acis_exception(INVALID_RADIUS)` 异常。
 *					处理情况3：半径为负数，抛出 `acis_exception(INVALID_RADIUS)` 异常。
 *					处理情况4：球心坐标为原点 `(0, 0, 0)`，生成位于原点的球体。
 *					处理情况5：球心坐标包含负值，生成位于相应位置的球体
 * @exception		acis_exception(INVALID_RADIUS) 当传入的球体半径小于或等于零时抛出异常
 * @return  		outcome 输出结果，表示函数执行的成功或失败状态
 */
DECL_CSTR outcome gme_3_api_solid_sphere(const SPAposition& center,  // 球体中心坐标
                               double radius,              // 球体半径
                               BODY*& sph,                 // 用以接收返回的球体对象
                               AcisOptions* ao = NULL      // ACIS选项，默认为 NULL
                               );

/**
 * @brief       根据给定的边创建一个线框。
 * @param[in]   num_edges 边的数量
 * @param[in]   edges 指向边的指针数组
 * @param[out]  body 创建出的线框的指针
 * @param[in]   ao ACIS选项
 * @details     该API函数根据给定的边列表创建一个线框。处理情况包括：
 *              处理情况1：输入的边数组为null或包含null指针；
 *              处理情况2：输入的边无效或几何无效；
 *              处理情况3：边数为0时触发错误；
 *              处理情况4：边的连接不连续或顺序不正确时触发错误。
 * @return      outcome 执行结果
 */
DECL_CSTR outcome gme_api_make_ewire(int num_edges,            // 边的数量
    EDGE* edges[],            // 边的指针数组
    BODY*& body,              // 创建出的线框体的指针
    AcisOptions* ao = NULL    // ACIS选项
);


/**
 * @brief     	输入待拟合的点列，支持任意长度，返回一条拟合的直线
 * @details     line传递地址，直接赋值，outcome返回值用于处理点数量小于二的情况
 * @param[in]	point_list  输入待拟合的点列，支持任意长度
 * @param[out]	line        返回拟合的直线
 * @param[in]	flo         
 * @param[in]	ao          
 * @return		函数执行结果
 * @exception	acis_exception(FIT_NO_SPAN) 当点列长度小于2时抛出异常
 *				acis_exception(NON_UNIQUE_FITPTS) 当点列长度大于等于2但点列中不同的点只有一个时抛出异常
 */

DECL_CSTR outcome gme_api_fit_line(const SPAposition_vector& point_list,  // 输入待拟合的点列，支持任意长度
                                   straight& line,                        // 返回拟合的直线
                                   fit_line_options* flo = NULL,          
                                   const AcisOptions* ao = NULL           
);

/**
 * @brief 创建一个新的边缘，该边缘是指定边缘经过变换后的副本。
 * 
 * @param[in] in_edge     要复制和变换的边缘
 * @param[in] t           要应用的变换
 * @param[out] out_edge   复制并变换后的边缘
 * @param[in] ao          ACIS选项
 * 
 * @return 返回操作的结果。如果操作成功，则返回表示成功的outcome对象；如果操作失败，则返回包含错误信息的outcome对象。
 * 
 * @exception 如果in_edge为NULL或不是指向EDGE的指针，函数将返回错误结果。
 * 
 * @details 此API函数用于创建一个新的EDGE对象，该对象指向一个新的起始VERTEX、一个新的结束VERTEX以及一个新的CURVE。
 * 			所有这些新对象都是通过对输入边缘应用指定的变换得到的。该函数适用于需要对边缘进行变换的场景，
 * 			例如旋转、平移或缩放边缘。以下是一些已测试的不同输入情况：
 * 			- case1: 传入无效值（例如NULL指针），函数应返回错误结果。
 * 			- case2: 传入椭圆Edge，测试平移操作，验证变换后的边缘是否符合预期。
 * 			- case3: 传入样条Edge，测试平移操作，验证变换后的边缘是否符合预期。
 * 			- case4: 传入直线Edge，测试反射操作，验证变换后的边缘是否符合预期。
 * 			- case5: 传入直线Edge，测试剪切操作，验证变换后的边缘是否符合预期。
 * 			- case6: 传入椭圆Edge，测试缩放操作，验证变换后的边缘是否符合预期。
 * 			- case7: 传入螺旋Edge，测试旋转操作，验证变换后的边缘是否符合预期。
 * 			- case8: 传入弹簧Edge，测试旋转操作，验证变换后的边缘是否符合预期。
 */
DECL_CSTR outcome gme_1_api_trans_edge(EDGE* in_edge, 
                                       const SPAtransf& t, 
                                       EDGE*& out_edge, 
                                       AcisOptions* ao = NULL);
/**
 * @brief   		创建环形面，弧度制。
 * @param[in]    	major 		主轴半径
 * @param[in]  	    minor 		副轴半径
 * @param[in]    	tu_start 	u方向起始角度
 * @param[in]    	tu_end 		u方向终止角度
 * @param[in]    	sv_start 	v方向起始角度
 * @param[in]    	sv_end 		v方向终止角度
 * @param[in]    	normal 		法向量
 * @param[out]  	face 		返回 face
 * @param[in]  	    ao 			ACIS 选项
 * @return          outcome 	执行结果
 * @details			该API函数根据输入生成不同状态的环面。处理情况包括：
 *					处理情况1：输入的半径、角度处于比较常规，生成对应四种圆环
 *					处理情况2：major和minor极端大
 *					处理情况3：ut - uf =  0 或 vt - vf =  0
 *					处理情况4：法向量为零或未标准化
 */
DECL_CSTR outcome gme_2_api_make_trface(
								const SPAposition& center,     // 圆环中心坐标
                                const SPAunit_vector& normal,  // 法线
                                double major,                  // 圆环外半径
                                double minor,                  // 圆环内半径
                                const SPAposition& pnt,        // 坐标
                                double uf,                     // u方向起点（弧度制）
                                double ut,                     // u方向终点（弧度制）
                                double vf,                     // v方向起点（弧度制）
                                double vt,                     // v方向终点（弧度制）
                                FACE*& face,                   // 圆环
                                AcisOptions* ao = NULL               // ACIS options
);

/*! @} */

/** @} */

#endif
