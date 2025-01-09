/*******************************************************************/
/*    Copyright (c) 2022-2024 by GME Team.                         */
/*    All rights reserved.                                         */
/*******************************************************************/
/**
 * @file   cucuint_util.hxx
 * @brief  线线求交的一些辅助函数，不传递头文件
 */
#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "acis/base.hxx"
#include "acis/bs3curve.hxx"
#include "acis/cucuint.hxx"
#include "acis/curdef.hxx"
#include "acis/dcl_intr.h"
#include "acis/intcucu.hxx"
#include "acis/intdef.hxx"
#include "acis/law_util.hxx"
#include "acis/math.hxx"
#include "acis/param.hxx"
class curve_curve_int;
class ellipse;
class helix;
class straight;
class cone;
class SPAposition;
class SPAinterval;
class curve;
class intcurve;
class SPAbox;
class plane;
class surface;
class EDGE;
class law;
class SPApar_vec;
class torus;
class sphere;
class spline;

#define intcurve_type 11
#define exactcur_type 20
#define surfintcur_type 22
#define parcur_type 25
#define surfcur_type 31

#define GME_INTERSECTOR_INTCUCU_NOINTINTCUR

#define ZeroInter ACIS_NEW curve_curve_int(nullptr, SPAposition(0, 0, 0), 0, 0)

#define cci_check_coin(inter) (inter->low_rel == curve_curve_rel::cur_cur_coin || inter->high_rel == curve_curve_rel::cur_cur_coin)
#define cci_check_tangent(inter) (inter->low_rel == curve_curve_rel::cur_cur_tangent && inter->high_rel == curve_curve_rel::cur_cur_tangent)

/**
 * @brief 将线线求交的单链表组织的所有交点 按照param1升序输出
 * @return 排序后的所有交点的首节点
 * @param inters 输入所有交点的首节点
 */
curve_curve_int* sort_inters(curve_curve_int* inters);

enum class SortParamType { Param1, Param2 };

/**
 * @brief 将线线求交的单链表组织的所有交点 按照param升序输出
 * @flag false 表示按param1排序 true表示按param2排序
 * @return 排序后的所有交点的首节点
 * @param inters 输入所有交点的首节点
 */
curve_curve_int* sort_inters_with_param(curve_curve_int* inters, SortParamType choose_param = SortParamType::Param1);

/**
 * @brief 将param参数为val，修改为-val 默认val为-M_PI，即将-M_PI调整为M_PI
 * @param param 参数
 * @param tol 容差
 * @param val -pi
 * @return refine后的值
 */
double refine_param(double param, double tol, double val = -M_PI);

/**
 * @brief 将椭圆ell转化为0<ratio<1的椭圆new_ell
 * @param ell 待转化的椭圆
 * @param new_ell 转化后的椭圆
 */
void transfer_ellipse(ellipse const& ell, ellipse& new_ell);

/**
 * @brief 交换线线求交结果中的param1和param2，并按照新的param1的升序返回求交结果
 * @return  交换后的求交结果
 * @param inters 待交换的求交结果
 */
curve_curve_int* swap_param(curve_curve_int* inters);

/**
 * @brief 获得螺旋线h所在的圆柱或双圆锥
 *        若h为圆柱螺旋线 则返回h所在圆柱为c1，c2为null
 *        若h为圆锥螺旋线 则返回h所在的圆锥c1和c2
 * @return 1: h为圆柱螺旋线，2: h为圆锥螺旋线
 * @param h 输入螺旋线
 * @param c1 输出的圆柱或圆锥
 * @param c2 输出的圆柱或圆锥
 */
int cone_of_helix(const helix& h, cone*& c1, cone*& c2);

/**
 * @brief 已知直线cs_line在cs_helix所在的圆柱或圆锥上，求cs_line和cs_helix的所有交点
 * @return cs_line和cs_helix的所有交点
 * @param cs_line 输入直线
 * @param cs_helix 输入螺旋线
 */
curve_curve_int* coin_line_helix_int(straight const& cs_line, helix const& cs_helix);

/**
 * @brief 将两个次数相同的多项式求和
 * @param paras1 第一个多项式系数数组
 * @param paras2 第二个多项式系数数组
 * @param parasResult 求和的结果
 * @param num 多项式的次数
 */
void AddTwoPoly(double paras1[], double paras2[], double parasResult[], int num);

/**
 * @brief 将array的前num个元素设置为0
 * @param array
 * @param num
 */
void SetArrayToZero(double array[], int num);

/**
 * @brief 计算定义于[u0, u1, u2]的B样条曲线基函数Ni,1(u)，只计算u属于区间[us, ue]的多项式系数
 * @param u0
 * @param u1
 * @param u2 [u0, u1, u2]为B样条曲线基函数Ni,1(u)的参数
 * @param us
 * @param ue [us, ue]为输入的Ni,1(u)的定义域
 * @param paras 输出的多项式系数
 */
void GetLinearPoly(double u0, double u1, double u2, double us, double ue, double paras[2]);

/**
 * @brief 计算两个一元多项式的乘积
 * @param paras1 第一个一元多项式的系数
 * @param num1 paras1系数的个数
 * @param paras2 第二个一元多项式的系数
 * @param num2 paras2系数的个数
 * @param paraResult 输出变量；paraResult为paras1和paras2乘积多项式的多项式系数数组
 * @param num paraResult的系数个数
 */
void GetMultiUniVarPoly(double paras1[], int num1, double paras2[], int num2, double paraResult[], int& num);

/**
 * @brief 计算定义于[u0, u1, u2, u3]的B样条曲线基函数Ni,2(u)，只计算u属于区间[us, ue]的多项式系数
 * @param u0
 * @param u1
 * @param u2
 * @param u3 [u0, u1, u2, u3]为B样条曲线基函数Ni,2(u)的参数
 * @param us
 * @param ue [us, ue]为输入的Ni,2(u)的定义域
 * @param paras 输出的多项式系数
 */
void GetQuadraticPoly(double u0, double u1, double u2, double u3, double us, double ue, double paras[3]);

/**
 * @brief 计算定义于[u0, u1, u2, u3, u4]的B样条曲线基函数Ni,3(u)，只计算u属于区间[us, ue]的多项式系数
 * @param u0
 * @param u1
 * @param u2
 * @param u3
 * @param u4 [u0, u1, u2, u3, u4]为B样条曲线基函数Ni,3(u)的参数
 * @param us
 * @param ue [us, ue]为输入的Ni,3(u)的定义域
 * @param paras 输出的多项式系数
 */
void GetCubicPoly(double u0, double u1, double u2, double u3, double u4, double us, double ue, double paras[4]);

/**
 * @brief 求一元n次多项式方程的所有根
 * @return 根的个数
 * @param degree 多项式方程的最高次数
 * @param dxyCoef 存储多项式方程的系数，从次数最高的系数开始存储
 * @param root 输出所求得的根，求得的根在[start, end]范围内
 * @param start
 * @param end [start, end]为所需要根的参数范围
 */
int Equatn(int degree, double* dxyCoef, double*& root, double start, double end);

/**
 * @brief 获得样条曲线bs在参数范围[start, end]内的子曲线
 * @return bs在[start,end]的子曲线
 * @param bs 输入的样条曲线 该接口不改变该曲线
 * @param start
 * @param end [start, end]为子曲线的参数范围 要求[start, end]在bs的参数范围内
 */
bs3_curve bs3_curve_split_interval(bs3_curve bs, double start, double end);

/**
 * @brief 设置样条曲线bs的权重为weight
 * @param bs 输入的样条曲线，接口会修改该曲线
 * @param weight 需要设置的曲线权重
 */
void bs3_curve_set_weights(bs3_curve& bs, double* weight);

/**
 * @brief 将样条曲线的权重归一化
 * @param bs 输入的样条曲线，要求该曲线为多段Bezier形式，若不是，则接口会出错
 */
void bs3_curve_normalise_weight(bs3_curve& bs);

/**
 * @brief 去掉自由曲线节点向量中的重复的部分
 * @param n 原曲线的顶点数
 * @param nn 去掉重复后的节点
 * @param knot 原曲线的节点向量
 * @param nknot 去掉重复后的节点向量
 */
void GetKnotNoRepeat(int n, int& nn, double* knot, double* nknot, double tol = SPAresabs);

/**
 * @brief 将样条曲线curv1和curv2的节点向量调整到一致
 *        前提：curv1和curv2的次数，有理性，参数范围保持一致，均为多段Bezier形式，且首尾端点距离在容差tol内
 * @param curv1 输入曲线1
 * @param curv2 输入曲线2
 * @param tol 容差
 */
void bs3_curve_normalise_knot(bs3_curve curv1, bs3_curve curv2, double tol = SPAresabs);

/**
 * @brief 将样条曲线bs转换为多段Bezier形式
 * @param bs 输入的样条曲线
 */
void nurbs_to_multiple_rbeziers(bs3_curve& bs);

/**
 * @brief 检查有理B样条曲线是否可以退化为非有理曲线
 * @return TRUE: 可退化 FALSE: 不可退化
 * @param bs3 输入样条曲线
 */
logical check_rational(bs3_curve bs3);

/**
 * @brief 判断sub_curv1和sub_curv2是否在容差tol内完全重合
 * @return TRUE: 完全重合 FALSE: 不完全重合
 * @param sub_curv1 输入曲线1
 * @param sub_curv2 输入曲线2
 * @param tol 重合容差
 * @param reversed sub_curv1和sub_curv2是否参数化相反
 */
logical test_coin(bs3_curve sub_curv1, bs3_curve sub_curv2, double tol, logical reversed);

/**
 * @brief 判断bs3在param处的点是否为bs3的一个自交点
 * @return FALSE: 该点不是自交点
 *         TRUE: 该点是自交点
 * @param param 输入参数
 * @param bs3 输入曲线
 * @param next_param 输出的参数 若该点不为自交点 next_param为param值
 *                              若该点为自交点 next_param为bs在该自交点处的另一个参数
 * @param tol 容差
 */
logical test_self_inter_point(double param, bs3_curve bs3, double& next_param, double tol = SPAresabs);

/**
 * @brief 检查曲线curv1在param1，curv2在param2上是否重合
 * @return 0: 不重合 1: 正向重合(切向方向相同) 2: 反向重合(切向方向相反) 3: 多种重合情况(自交点或闭曲线端点)
 * @param curv1 输入曲线1
 * @param curv2 输入曲线2
 * @param param1 输入参数1
 * @param param2 输入参数2
 * @param tol 容差
 * @param check_self_point 是否检查曲线在参数处的自交点和闭曲线的端点
 * @param records 返回的重合记录，包括参数所在点处的所有重合记录 记录格式为<重合关系, param1, param2>
 */
int test_coincident(bs3_curve curv1, bs3_curve curv2, double param1, double param2, double tol, logical check_self_point = FALSE, std::vector<std::tuple<int, double, double>>* records = nullptr);

/**
 * @brief 样条曲线重合检测
 * @return 返回重合的段数 返回0：不重合
 * @param curv1 输入曲线1
 * @param curv2 输入曲线2
 * @param inters 重合的交点结果
 * @param inter_ints1 所有重合段在curv1的参数区间
 * @param inter_ints2 所有重合段在curv2的参数区间
 * @param tol 重合检测容差
 */
int detect_coincident(bs3_curve curv1, bs3_curve curv2, curve_curve_int*& inters, std::vector<SPAinterval>& inter_ints1, std::vector<SPAinterval>& inter_ints2, double tol = SPAresabs);

/**
 * @brief 剔除交点结果inters在所有重合参数区间coin_ints内的交点，只检查param1
 * @return 剔除后的交点结果
 * @param inters 输入交点结果
 * @param coin_ints 所有重合参数区间
 */
curve_curve_int* delete_coin(curve_curve_int* inters, std::vector<SPAinterval> const& coin_ints);

/**
 * @brief ratio>1的椭圆ell和曲线curv求交，返回交点结果
 * @return 线线求交结果
 * @param ell 输入ratio>1的椭圆
 * @param curv 输入曲线
 * @param box 包围盒
 * @param tol 容差
 */
curve_curve_int* irregular_ellipse_inters(ellipse const& ell, curve const& curv, SPAbox const& box, double tol);

/**
 * @brief 求解方程组
 *          {   cos(a * t + b) = cos(t + theta)         ;
 *              sin(a * t + b) = sgn * sin(t + theta)   ;
 *          }
 *        其中sgn = {1.0, -1.0} t的参数范围为[st, ed]
 *        求方程组的所有解
 * @return 若存在无穷个解，返回-1；反之，返回方程组解的个数
 * @param roots 存储所有解
 */
int helix_slove_equat1(double a, double b, double theta, double sgn, double st, double ed, std::vector<double>& roots);

/**
 * @brief   求解方程组
 *          { (r1 + dr1 * t1) * cos(t1) = (r2 + dr2 * t2) * cos(t2 + theta)
 *            (r1 + dr1 * t1) * sin(t1) = sgn * (r2 + dr2 * t2) * sin(t2 + theta)
 *            t1 = a * t2 + b
 *          }
 *          其中 sgn = {-1, 1}, t2的参数范围为[st, ed]
 *          求方程组中所有解(t2)
 * @return -1: 方程组存在无穷个解; 反之，返回方程组解的个数
 * @param roots 存储所有解(t2)
 */
int helix_slove_equat2(double r1, double dr1, double a, double b, double r2, double dr2, double theta, double sgn, double st, double ed, std::vector<double>& roots);

/**
 * @brief 向量的元素相乘
 * @return 输出向量元素相乘的结果
 * @param vec1 输入向量1
 * @param vec2 输入向量2
 */
SPAvector vector_multiple(SPAvector const& vec1, SPAvector const& vec2);

/**
 * @brief 共面的(椭)圆与平面螺旋线求交
 * @return (椭)圆与平面螺旋线求交的结果
 * @param ell 输入的(椭)圆
 * @param h 输入的平面螺旋线
 */
curve_curve_int* coplanar_ellipse_planar_helix_int(ellipse const& ell, helix const& h);

/**
 * @brief 将区间input转化到主参数曲线major_interval中，必要时将返回两个区间
 * @return 转化后的所有区间
 * @param input 输入的区间
 * @param period 周期
 * @param major_interval 主参数区间
 * @param tol 容差
 */
std::vector<SPAinterval> shift_interval_to_major(SPAinterval const& input, double period, SPAinterval const& major_interval, double tol = SPAresabs);

/**
 * @brief 以period为周期，调整angle使其位于major_interval中
 * @return 调整后的angle
 * @param angle 输入的angle
 * @param period 输入的周期
 * @param major_interval 输入的主参数范围
 */
double param_change_interval(double angle, const SPAinterval& interval, double period = 2 * M_PI);

/**
 * @brief 将区间interval转化到out_interval区间内，只保证interval.start_pt()转化到out_interval中
 *        保证区间长度不发生改变
 * @return 转化后的区间
 * @param interval 待转化的区间
 * @param out_interval 目的区间
 * @param period 周期
 * @param reversed reversed=false,interval代表升序的区间；reversed=true,interval代表降序的区间
 */
SPAinterval param_change_interval(SPAinterval const& interval, SPAinterval const& out_interval, double period = 2 * M_PI, bool reversed = false);

/**
 * @brief cur1与cur2重合，返回cur1参数为param处的坐标在cur2上的参数
 * @return cur2的对应参数
 * @param param cur1输入的参数
 * @param cur1
 * @param cur2
 */
double recompute_param(double param, curve const* cur1, curve const* cur2);

/**
 * @brief c1和c2重合，求c1在interval表示的曲线段在c2上的参数范围
 * @return c1在interval表示的曲线段在c2上的参数范围
 * @param interval 输入区间
 * @param c1
 * @param c2
 * @param tol 容差
 * @param reversed reversed=false 返回的区间为升序; reversed=true 返回的区间为降序
 */
SPAinterval recompute_param_range(SPAinterval const& interval, curve const* c1, curve const* c2, double tol = SPAresabs, bool& reversed = *(bool*)nullptr);

/**
 * @brief 重新计算重合结果中的参数
 * @param c1 输入曲线1
 * @param c2 输入曲线2
 * @param inters 待修改的重合结果
 * @param coin_ints1 待修改的在c1上的重合参数范围
 * @param coin_ints2 待修改的在c2上的重合参数范围
 * @param need_sort 是否需要对重合结果排序
 */
void recompute_coin_inters(curve const& c1, curve const& c2, curve_curve_int*& inters, std::vector<SPAinterval>& coin_ints1, std::vector<SPAinterval>& coin_ints2, bool need_sort = false);

/**
 * @brief 判断bs1和bs2的控制多边形是否完全重合
 * @return TRUE: bs1和bs2控制多边形完全重合 FALSE: bs1和bs2控制多边形不完全重合
 * @param bs1 输入的样条曲线
 * @param bs2 输入的样条曲线
 * @param tol 容差
 * @param no_knot_check FALSE: 需要检查节点向量是否完全一致; TRUE: 无需检查节点向量是否完全一致
 */
logical cucuint_bs3_curve_same(bs3_curve bs1, bs3_curve bs2, double tol, logical no_knot_check);

/**
 * @brief 统计线线求交结果中交点个数
 * @return 求交结果中交点的个数
 * @param inters 求交结果
 */
int count_inters(const curve_curve_int* inters);

/**
 * @brief 将bs3_curve转化为精确(exact_int_cur)的intcurve
 * @return 创建的intcurve
 * @param bs 输入的样条曲线bs3_curve
 */
intcurve* make_exact_intcurve(bs3_curve bs);

/**
 * @brief 已知螺旋线h和ic均位于圆锥c上，求h和ic的所有交点
 * @return h和ic的求交结果
 * @param c 圆柱/圆锥
 * @param h 螺旋线
 * @param ic intcurve
 */
curve_curve_int* cone_helix_bs3_int(cone const& c, helix const& h, intcurve* ic);

// 将螺旋线进行划分
// 若h为圆柱螺旋线则返回1，此时h1=h,h2=nullptr
// 若h为圆锥螺旋线，且h在一个圆锥上，则返回1，此时h1=h，h2=nullptr
// 若h为圆锥螺旋线，且h在两个圆锥上，则返回2，此时h1为h在圆锥c1上的部分螺旋线，h2为h在圆锥c2上的部分螺旋线
// 保证h1和h2的参数化与对应的cone一致(参数为0的点重合，并且参数方向相同)
int helix_split(helix const& h, helix*& h1, helix*& h2);

/**
 * @brief 获得包围盒所在的平面
 * @param box 包围盒
 * @param num_planes 包围盒所在的平面数，若包围盒为有界包围盒，num_planes为6
 * @param planes 包围盒所在的平面(bounded)
 */
void planes_of_box(const SPAbox& box, int& num_planes, plane*& planes);

/**
 * @brief 获得矩形所在的线段
 * @param pln 矩形
 * @param num_lines 矩形所在的线段，若矩形为有界包围盒，num_planes为4
 * @param lines 矩形所在的线段(bounded)
 */
void lines_of_rect(const plane& pln, int& num_lines, straight*& lines);

/**
 * @brief 获得直线在包围盒内的参数范围
 * @return 直线在包围盒内的参数范围，若不在包围盒内，返回nullptr
 * @param st 直线
 * @param box 包围盒
 * @param margin 误差
 */
SPAinterval* line_in_box(straight const& st, SPAbox const& box, double margin = 1e-6);

/**
 * @brief 获得直线在矩形内的参数范围
 * @return 直线在矩形内的参数范围
 * @param st 直线
 * @param pln plane类型的矩形，直线在pln平面内
 */
SPAinterval* line_in_rect(straight const& st, plane const& pln);

/**
 * @brief 删除包围盒外的交点
 * @return 筛选后的交点结果
 * @param inters 待筛选的交点结果
 * @param box 包围盒
 */
curve_curve_int* points_in_box(curve_curve_int* inters, SPAbox const& box);

/**
 * @brief 判断curve是否为周期曲线 不考虑subset
 * @return true: curve为周期曲线; false: curve为非周期曲线
 * @param c 输入曲线
 */
bool curve_periodic(curve const& c);

/**
 * @brief 判断curve是否为闭合曲线 不考虑subset
 * @return true: curve为闭合曲线; false: curve为非闭合曲线
 * @param c 输入曲线
 */
bool curve_closed(curve const& c);

/**
 * @brief 判断curve是否为开曲线 不考虑subset
 * @return true: curve为开曲线; false: curve为非开曲线
 * @param c 输入曲线
 */
bool curve_open(curve const& c);

/**
 * @brief 返回curve的周期 不考虑subset
 * @return 0: curve为非周期曲线 >0: curve为周期曲线，返回curve的周期
 * @param c 输入曲线
 */
double curve_period(curve const& c);

// 返回curve的主参数周期 不考虑subset

/**
 * @brief 返回curve的主参数周期 不考虑subset
 * @return 空区间: curve为开曲线 区间长度不为0: curve为周期曲线或闭曲线，返回curve的主参数周期
 * @param c 输入曲线
 */
SPAinterval curve_major_interval(curve const& c);

/**
 * @brief 获得curve在param处的点在range内的有效参数
 * @return 若找到返回true，未找到返回false
 * @param c 输入曲线
 * @param param 输入参数
 * @param range 给定参数区间
 */
bool find_valid_param(curve const& c, double& param, SPAinterval const& range);

/**
 * @brief 删除curve_curve_int存储的交点中(不考虑重合交点)不在cur1和cur2参数范围内的交点
 * @return 删除后的curve_curve_int交点结果
 * @param inters 待删除的curve_curve_int交点结果
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param need_compute_param 是否需要重新计算curve_curve_int的param1和param2
 */
curve_curve_int* filter_normal_inters(curve_curve_int* inters, curve const& cur1, curve const& cur2, bool need_compute_param = false);

/**
 * @brief 处理求交结果inters，不处理重合段，删除param1在range1外或param2在range2外的交点
 * @return 筛选后的交点结果
 * @param inters 输入交点结果
 * @param range1 param1要求的参数范围
 * @param range2 param2要求的参数范围
 */
curve_curve_int* filter_normal_inters(curve_curve_int* inters, std::vector<SPAinterval>* range1 = nullptr, std::vector<SPAinterval>* range2 = nullptr);

/**
 * @brief 筛选coin_int1和coin_int2所表示的重合区间，将其调整到param_range1和param_range2内
 */
curve_curve_int* filter_coins(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_ints1, std::vector<SPAinterval> const& coin_ints2, SPAinterval const& param_range1, SPAinterval const& param_range2);

/**
 * @brief 筛选coin_int1和coin_int2所表示的重合区间，将其调整到param_range1和param_range2内
 */
curve_curve_int* filter_coins_ellipse_ellipse(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_ints1, std::vector<SPAinterval> const& coin_ints2, SPAinterval const& param_range1, SPAinterval const& param_range2);

/**
 * @brief 判断点pos是否在box的一条边上
 */
logical point_on_box_side(SPAposition pos, SPAbox const& box);

/**
 * 将多个重合段 合并起来，返回合并后的段数(要求各段按照param1有序)
 */
int merge_coin_inters(std::vector<std::pair<curve_curve_int*, curve_curve_int*>>& inter_list, double tol = SPAresabs);

/**
 * @brief 封装MAF方法，对近似交点结果near_result迭代求精(GEMS版本)
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param near_result 近似交点结果
 * @param refined_result 求精后的交点结果
 * @param total_iter_num 最大迭代次数
 */
void maf(curve const& cur1, curve const& cur2, curve_curve_int* near_result, curve_curve_int*& refined_result, int total_iter_num);

/**
 * @brief 构造曲线在给定点处的曲率圆
 * @param cur 线
 * @param param 参数
 * @param ell 圆
 * @param max_lg 返回构造圆时的最大数值差距
 */
logical construct_curvature_circle(curve const& cur, double param, ellipse& ell, double& max_lg);

/**
 * @brief 封装MAF方法，对近似交点结果near_result迭代求精(GME版本)
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param near_result 近似交点结果
 * @param refined_result 求精后的交点结果
 * @param total_iter_num 最大迭代次数
 * @param quadratic_approximation 是否使用二次近似
 */
void curve_curve_maf(curve const& cur1, curve const& cur2, curve_curve_int* near_result, curve_curve_int*& refined_result, int total_iter_num, logical quadratic_approximation = FALSE);

/**
 * @brief 获得曲线的degree
 * @return 将曲线拟合为多项式，多项式的最高次数
 * @param cur 输入的曲线
 */
int curve_degree(curve const& cur);

/** 二次迭代获得在圆上的下一个参数 */
logical quadratic_approximation_circle_iterate(curve* curv, ellipse const& cir, double t, SPAposition const& int_point, double& dt);

/** 二次迭代得到下一个交点 */
logical quadratic_approximation_iterate(curve* cur1, curve* cur2, double param1, double param2, double& dt1, double& dt2, bool& cand_point);

// 将曲线所在的x轴和y轴拉伸extend_magnitude倍
void extend_curve(curve*& curve1, double extend_magnitude = 1000);

/**
 * @brief 已知cur1和cur2完全重合(参数范围内)，求cur1在coin_int1和cur2在coin_int2的重合段
 */
std::vector<SPAinterval> get_coincident_segment(curve const& cur1, curve const& cur2, SPAinterval const& coin_int1, SPAinterval const& coin_int2);

/**
 * @brief 二元二次非线性方程组的牛顿迭代法
 * @return TRUE: 收敛 False: 发散
 * @param x_init 初始解[u0, v0]
 * @param F_array 数组[F1(u, v), F2(u, v)]
 * @param Jacob_array 数组[F1u(u, v), F1v(u, v), F2u(u, v), F2v(u, v)]
 * @param x_out 若收敛，输出收敛解[u, v]
 * @param tol 跳出容差
 * @param max_count 牛顿迭代的最大迭代次数
 */
logical bivariant_newton_iterate(const double* x_init, law** F_array, law** Jacob_array, double** x_out, double tol, int max_count = 100);

// 将curve1转化到 (cp, vx, vy, vz)的局部坐标系中
void transf_curve(curve*& curve1, SPAposition cp, SPAunit_vector vx, SPAunit_vector vy, SPAunit_vector vz);

// 构造坐标系变换的SPAtransf
SPAtransf cucuint_coordinate_transf(SPAposition const& root, SPAvector const& vx, SPAvector const& vy, SPAvector const& vz);

/**
 * @brief 椭圆和B样条曲线的隐式化方法(解方程法)
 * @return curve_curve_int*的交点结果
 * @param ell 椭圆
 * @param bs3 B样条曲线
 * @param tol 容差
 */
curve_curve_int* ellipse_bspline_int_implicitization(ellipse const& ell, bs3_curve bs3, double tol = SPAresabs);

/**
 * @brief 尝试将law_int_cur所代表的law曲线转化为简单的曲线(直线/圆/螺旋线)，若转化失败，返回nullptr
 * @return 转化后的曲线
 * @param law_ic 输入的law_int_cur
 */
curve* law_int_cur_to_curve(intcurve const& law_ic);

/**
 * @brief Nurbs曲线细分，转化为控制多边形点数组
 * @param curv 输入的Nurbs曲线
 * @param points 输出的控制多变形点数组
 * @param splitpara [splitpara[i], splitpara[i+1]]为两个控制点在曲线的近似参数区间
 * @param num_points 输出的控制多边形点数组的点的个数
 */
void NurbsSubdivision(bs3_curve curv, SPAposition*& points, double*& splitpara, int& num_points);

/**
 * @brief 曲线cur和面交线计算重合段，输入cur在面交线所在两个面的重合区间，返回cur与面交线实际的重合区间(在cur上的参数区间)
 * @return 实际的重合段(在cur上的参数区间)
 * @param cur 输入曲线
 * @param iic 输入面交线
 * @param int1 输入曲线cur与面交线的第一个面重合的区间
 * @param int2 输入曲线cur与面交线的第二个面重合的区间
 */
std::vector<SPAinterval> int_int_cur_coin_detect(curve const& cur, intcurve const& iic, std::vector<SPAinterval> const& int1, std::vector<SPAinterval> const& int2);

/**
 * @brief 检测两个椭圆是否重合
 * @return  重合标志，true表示重合，false表示不重合
 * @param cci_ellipse1 输入椭圆1
 * @param cci_ellipse2 输入椭圆2
 */
bool ellipse_ellipse_coin_detect(ellipse const& cci_ellipse1, ellipse const& cci_ellipse2);

/**
 * @brief 构造两个重合(椭)圆的求交结果类
 * @return 线线求交结果类
 * @param cci_ellipse1 输入椭圆1
 * @param cci_ellipse2 输入椭圆2
 * @param box 包围盒
 * @param tol 容差
 */
curve_curve_int* ellipse_ellipse_coin(ellipse const& cci_ellipse1, ellipse const& cci_ellipse2, SPAbox const& box, double tol);

/**
 * @brief 根据重合的参数区间(cur1上的参数区间)构造线线求交结果类
 * @return 线线求交结果类
 * @param cur1 输入曲线1
 * @param cur2 输入曲线2
 * @param coin_int_array 重合段在cur1上的参数区间
 */
curve_curve_int* construct_coin_inters(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_int1_array, std::vector<std::pair<double, double>> const& coin_int2_array = *(std::vector<std::pair<double, double>>*)nullptr);
curve_curve_int* construct_coin_inters(curve const& cur1, curve const& cur2, int num_arr, SPAinterval* coin_int_array);

/**
 * @brief 判断nurbs曲线的节点向量重数是否大于degree+1
 * @return TRUE:nurbs曲线节点向量重数异常, FALSE:无异常
 * @param curv 输入曲线
 */
logical illegal_knot_mul(bs3_curve curv);

/**
 * @brief 判断曲线的端点是否在另一个曲线上，若在其上，构造交点结果
 * @return 交点结果
 * @param cur1 曲线1
 * @param cur2 曲线2
 */
curve_curve_int* judge_curve_ends(curve const& cur1, curve const& cur2);

/**
 * @brief 拟合法求平面螺旋线和nurbs曲线求交，返回求交结果
 * @return 交点结果
 * @param hel 平面螺旋线
 * @param bs3 nurbs曲线
 */
curve_curve_int* fit_coplnar_helix_nurbs_int(helix const& hel, bs3_curve bs3);

/**
 * @brief MAF迭代法求平面螺旋线和nurbs曲线求交，返回求交结果
 */
curve_curve_int* maf_coplnar_helix_bs3_int(helix const& hel, intcurve const& ic, SPAinterval const& range);

// 直线-nurbs曲线 迭代求交
void line_nurbs_iterate(straight const& st, bs3_curve nurbs, curve_curve_int* near_result, curve_curve_int*& refine_result);

// curve-nurbs曲线 迭代求交
void curve_nurbs_iterate(curve const& curv, bs3_curve nurbs, curve_curve_int* near_result, curve_curve_int*& refine_result);

// curve-curve 迭代求交
void curve_curve_iterate_minimize(curve const& curv, curve const& nurbs, curve_curve_int* near_result, curve_curve_int*& refine_result);

template <size_t ROWS, size_t COLS> class Matrix;
template <size_t n> using Vector = Matrix<n, 1>;

template <size_t ROWS, size_t COLS> class Matrix {
  private:
    double _data[ROWS][COLS]{};

  public:
    Matrix() { std::memset(_data[0], 0, sizeof(double) * ROWS * COLS); }

    Matrix(std::vector<double> const& vec) {
        std::memset(_data[0], 0, sizeof(double) * ROWS * COLS);
        std::copy(vec.begin(), vec.end(), _data[0]);
    }

    Matrix(const std::initializer_list<double>& list) {
        int i = 0;
        double* st = _data[0];
        for(auto const& val: list) {
            st[i++] = val;
        }
    }

    static int rows() { return ROWS; }

    static int cols() { return COLS; }

    double& operator()(size_t i, size_t j) {
        // no check
        return _data[i][j];
    }
    double operator()(size_t i, size_t j) const {
        // no check
        return _data[i][j];
    }
    // dot product
    template <size_t _ROWS, size_t _COLS> Matrix<ROWS, _COLS> operator%(Matrix<_ROWS, _COLS> const& mat) const {
        // no check
        // assert(COLS == _ROWS)
        Matrix<ROWS, _COLS> ret;
        for(int i = 0; i < ROWS; ++i) {
            for(int j = 0; j < _COLS; ++j) {
                double val = 0;
                for(int k = 0; k < COLS; ++k) {
                    val += this->_data[i][k] * mat(k, j);
                }
                ret(i, j) = val;
            }
        }
        return ret;
    }
    // transpose
    [[nodiscard]] Matrix<COLS, ROWS> T() const {
        Matrix<COLS, ROWS> ret;
        for(int i = 0; i < COLS; ++i) {
            for(int j = 0; j < ROWS; ++j) {
                ret(i, j) = this->_data[j][i];
            }
        }
        return ret;
    }

    [[nodiscard]] Vector<COLS> get_row(size_t row) const {
        // 基于复制，可优化
        Vector<COLS> ret;
        for(int i = 0; i < COLS; ++i) {
            ret(i, 0) = this->_data[row][i];
        }
        return ret;
    }

    [[nodiscard]] Vector<ROWS> get_col(size_t col) const {
        // 基于复制，可优化
        Vector<ROWS> ret;
        for(int i = 0; i < ROWS; ++i) {
            ret(i, 0) = this->_data[i][col];
        }
        return ret;
    }
    void set_row(size_t row, Vector<COLS> const& vec) {
        for(int i = 0; i < COLS; ++i) {
            this->_data[row][i] = vec(i, 0);
        }
    }
    void set_col(size_t col, Vector<ROWS> const& vec) {
        for(int i = 0; i < ROWS; ++i) {
            this->_data[i][col] = vec(i, 0);
        }
    }

    [[nodiscard]] double len_sq() const {
        // for vector
        double sum = 0;
        for(int i = 0; i < ROWS; ++i) {
            sum += this->_data[i][0] * this->_data[i][0];
        }
        return sum;
    }

    [[nodiscard]] double len() const {
        // for vector
        return sqrt(len_sq());
    }
};
template <size_t ROWS, size_t COLS> double reduce(std::function<double(double, double)> const& func, Matrix<ROWS, COLS> const& mat) {
    double ret = mat(0, 0);
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            if(i == 0 && j == 0) continue;
            ret = func(ret, mat(i, j));
        }
    }
    return ret;
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> apply(std::function<double(double)> const& func, Matrix<ROWS, COLS> const& mat) {
    Matrix<ROWS, COLS> ret;
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            ret(i, j) = func(mat(i, j));
        }
    }
    return ret;
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> apply(std::function<double(double, double)> const& func, Matrix<ROWS, COLS> const& mat1, Matrix<ROWS, COLS> const& mat2) {
    Matrix<ROWS, COLS> ret;
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            ret(i, j) = func(mat1(i, j), mat2(i, j));
        }
    }
    return ret;
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator+(Matrix<ROWS, COLS> const& mat1, Matrix<ROWS, COLS> const& mat2) {
    auto plus_func = [](double a, double b) { return a + b; };
    return apply(plus_func, mat1, mat2);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator+(Matrix<ROWS, COLS> const& mat1, double val) {
    auto plus_func = [val](double a) { return a + val; };
    return apply(plus_func, mat1);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator-(Matrix<ROWS, COLS> const& mat1, Matrix<ROWS, COLS> const& mat2) {
    auto sub_func = [](double a, double b) { return a - b; };
    return apply(sub_func, mat1, mat2);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator-(Matrix<ROWS, COLS> const& mat1, double val) {
    auto sub_func = [&](double a) { return a - val; };
    return apply(sub_func, mat1);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator/(Matrix<ROWS, COLS> const& mat1, Matrix<ROWS, COLS> const& mat2) {
    auto div_func = [](double a, double b) { return a / b; };
    return apply(div_func, mat1, mat2);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator/(Matrix<ROWS, COLS> const& mat1, double val) {
    auto div_func = [val](double a) { return a / val; };
    return apply(div_func, mat1);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator*(Matrix<ROWS, COLS> const& mat1, Matrix<ROWS, COLS> const& mat2) {
    auto mul_func = [&](double a, double b) { return a * b; };
    return apply(mul_func, mat1, mat2);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator*(Matrix<ROWS, COLS> const& mat1, double val) {
    auto mul_func = [&](double a) { return a * val; };
    return apply(mul_func, mat1);
}
template <size_t ROWS, size_t COLS> Matrix<ROWS, COLS> operator*(double val, Matrix<ROWS, COLS> const& mat) {
    return operator*(mat, val);
}
template <size_t ROWS, size_t COLS> double max(Matrix<ROWS, COLS> const& mat) {
    auto max_func = [](double a, double b) { return D3_max(a, b); };
    return reduce(max_func, mat);
}
template <size_t ROWS, size_t COLS> double min(Matrix<ROWS, COLS> const& mat) {
    auto min_func = [](double a, double b) { return D3_min(a, b); };
    return reduce(min_func, mat);
}
template <size_t ROWS, size_t COLS> double sum(Matrix<ROWS, COLS> const& mat) {
    auto add_func = [](double a, double b) { return a + b; };
    return reduce(add_func, mat);
}
template <size_t N> std::vector<int> argsort(Vector<N> const& array) {
    std::vector<int> array_index(N, 0);
    for(int i = 0; i < N; ++i) array_index[i] = i;

    std::sort(array_index.begin(), array_index.end(), [&array](int pos1, int pos2) { return (array(pos1, 0) < array(pos2, 0)); });

    return array_index;
}

using ParamType = std::vector<void const*>;
using Func2dType = std::function<Vector<2>(Vector<2> const&, std::vector<void const*>)>;
using Jcob2dType = std::function<Matrix<2, 2>(Vector<2> const&, std::vector<void const*>)>;
using ScalarFunc2dType = std::function<double(Vector<2> const&, std::vector<void const*>)>;

// 定义二元目标函数
Vector<2> objF(Vector<2> const& input, std::vector<void const*> const& params);

// 定义二元距离函数
double distanceF(Vector<2> const& input, std::vector<void const*> const& params);

// 直线椭圆求交牛顿迭代求精接口
void Newton_str_ell(straight const& str, ellipse const& ell, SPAposition& int_point, double& param_str, double& param_ell, int maxiter = -1);

// 定义二元Jacob矩阵
Matrix<2, 2> Jacobin(Vector<2> const& input, std::vector<void const*> const& params);

/** 使用最优化方法求cur1和cur2容差内的交点  */
curve_curve_int* tolerance_int_cur_cur(curve const& cur1, curve const& cur2, std::vector<SPAposition>& cand_points, double tol, int maxiter = -1);

/** 使用最优化方法求cur1和cur2的精确交点  */
curve_curve_int* cur1_cur2_tolerance_newton(curve const& cur1, curve const& cur2, std::vector<SPAposition>& cand_points, double tol, int maxiter = -1);

/** 使用最优化方法求cur1和cur2的最近点对  */
double MinDistancePointPair_Impl(curve const& cur1, curve const& cur2, Vector<2> const& vec0, SPAposition& pt1, SPAposition& pt2, int maxiter = -1);

/** 使用最优化方法求cur1和cur2的最近点对  */
double cur1_cur2_MinDistancePointPair_Impl(curve const& cur1, curve const& cur2, Vector<2> const& vec0, SPAposition& pt1, SPAposition& pt2, int maxiter = -1);

/**
 * @brief 给定初始值_x0, 求func的最小值
 */
Vector<2> minimize(ScalarFunc2dType const& func, Vector<2> const& _x0, std::vector<void const*> const& params, double tol = 1e-10, int maxiter = -1, bool adaptive = false);

/**
 * @brief 获得曲线的包围盒
 */
SPAbox bound_of_curve(curve const& curv);

/**
 * @brief 计算三维点到曲线的最短距离
 */
DECL_INTR double distance_to_curve(SPAposition const& pos, curve const& curv);

/**
 * @brief 两个nurbs曲线的近似求交
 */
curve_curve_int* nurbs_nurbs_near_inters(bs3_curve nurbs1, bs3_curve nurbs2, SPAinterval const& range1, SPAinterval const& range2, double tol = 0.0);

// 获得区间range去除exclude_ranges后的集合
void interval_exclude(SPAinterval const& range, std::vector<SPAinterval> const& exclude_ranges, std::vector<SPAinterval>& left_ranges);

// 连接两个线线求交结果
curve_curve_int* connect_curve_curve_int(curve_curve_int* inter1, curve_curve_int* inter2);

/**
 * @brief 检验curv是否在param处非G1连续
 * @return curv在param处G1不连续，返回FALSE;curv在param处G1连续，返回TRUE
 * @param curv 输入的曲线
 * @param param 输入的曲线参数
 */
logical check_irregular_G1(bs3_curve curv, double param);

/**
 * @brief 返回两个圆的最近的一对点(无交的情况) 或者 所有交点(有交的情况)
 * @return true: 两个圆重合 false: 两个圆不重合
 * @param cir1 输入的圆1
 * @param cir2 输入的圆2
 * @param pos1_array cir1上的最近点
 * @param pos2_array cir2上的最近点
 */
bool circle_circle_closest_points(ellipse const& cir1, ellipse const& cir2, std::vector<SPAposition>& pos1_array, std::vector<SPAposition>& pos2_array);

/**
 * @brief 返回直线和圆最近的一对点(无交的情况) 或者 所有交点(有交的情况)
 * @param line 输入的直线
 * @param cir 输入的圆
 * @param pos1_array line上的最近点
 * @param pos2_array cir上的最近点
 */
void line_circle_closest_points(straight const& line, ellipse const& cir, std::vector<SPAposition>& pos1_array, std::vector<SPAposition>& pos2_array);

/**
 * @brief 判断一个bs3_curve在[st, ed]内是否为平面曲线
 * @return TRUE: bs3_curve在[st, ed]内为平面曲线, FALSE: bs3_curve在[st, ed]内不是平面曲线
 * @param curv 输入的nurbs曲线
 * @param interval 输入的曲线 [st, ed]
 * @param center 若bs3_curve在[st, ed]内为平面曲线，返回所在平面上一点
 * @param normal 若bs3_curve在[st, ed]内为平面曲线，返回所在平面的法向量
 */
int bs3_curve_is_planar(bs3_curve curv, SPAinterval const& interval, SPAposition& center = *static_cast<SPAposition*>(nullptr), SPAunit_vector& normal = *static_cast<SPAunit_vector*>(nullptr), double tol = SPAresabs);

/**
 * @brief 弦截法 求解一元非线性方程的最小值, sol在[a, b]内，要求func(a)*func(b) < 0
 * @param func 一元非线性方程
 * @param a 区间左端
 * @param b 区间右端
 * @param sol 解
 * @param tol 误差
 */
void Secant(std::function<double(double)> const& func, double a, double b, double& sol, double tol = SPAresabs);

/**
 * @brief 判断曲线是否为退化的曲线
 * @return true: 曲线退化 false: 曲线非退化
 * @param cur 输入的曲线
 */
bool is_degenerate(curve const& cur);

/**
 * @brief 考虑容差的向量归一化
 */
SPAunit_vector cucuint_normalise(SPAvector const& vec, double tol = 1e-16);

/**
 * @brief 验证重合结果的有效性
 */
int validate_coin_result(curve const& cur1, curve const& cur2, std::vector<SPAinterval>& coin_int1, std::vector<SPAinterval>& coin_int2, curve_curve_int*& coins, double tol);

/**
 * @brief 判断val在容差tol内是否位于区间range
 */
bool double_in_range(double val, SPAinterval const& range, double tol);

/**
 * @brief 判断交点是否容差tol内位于包围盒box中
 */
bool point_in_box(SPAposition const& pos, SPAbox const& box, double tol);

/**
 * @brief 求直线和圆柱螺旋线的最近点对(pt1, pt2)
 * @return TRUE: 求得的最近点对收敛 FALSE: 求得的最近点对不收敛
 * @param cci_straight 直线
 * @param cci_helix 圆柱螺旋线
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(straight const& cci_straight, helix const& cci_helix, SPAposition const& init_pos, SPAposition& pt1, SPAposition& pt2);

/**
 * @brief 求圆和圆柱螺旋线的最近点对(pt1, pt2)
 * @return TRUE: 求得的最近点对收敛 FALSE: 求得的最近点对不收敛
 * @param cci_ellipse 椭圆
 * @param cci_helix 圆柱螺旋线
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(ellipse const& cci_ellipse, helix const& cci_helix, SPAposition const& init_pos, SPAposition& pt1, SPAposition& pt2);

/**
 * @brief 求直线和intcurve的最近点对(pt1, pt2)  注意: 该接口目前只支持直线和(圆环-平面)面交线求最近点对
 * @return TRUE: 求得的最近点对收敛  FALSE: 求得的最近点对不收敛
 * @param cci_straight 直线
 * @param cci_intcurve intcurve
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(straight const& cci_straight, intcurve const& cci_intcurve, SPAposition const& init_pos, SPAposition& pt1, SPAposition& pt2);

/**
 * @brief 确定unknown:unknown的实际交点关系
 * @param inters 输入/输出 修改后的交点关系
 */
void compute_normal_rel(curve_curve_int*& inters, curve const& cur1, curve const& cur2);

/**
 * @brief 确定unknown:unknown的实际交点关系
 * @param inters 输入/输出 修改后的交点关系
 */
void compute_normal_rel_intcurve(curve_curve_int*& inters, curve const& cur1, curve const& cur2);

//////////////////////////////线线求交debug辅助函数//////////////////////////////
/**
 * @brief 保存模型(存放于elist)到文件中(文件路径file_name)
 */
void my_save_entity_list(ENTITY_LIST& elist,    // (in) List of the entities to save
                         const char* file_name  // (in) Name of the SAT file
);

/**
 * @brief 保存两个曲线的模型到路径file_name中
 */
DECL_INTR void save_curve_curve_models(curve const& cur1, curve const& cur2, std::string const& file_name);

/**
 * @brief 求两个曲线的最近点对(使用api_entity_entity_distance)
 * @return 最近点对的距离
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param pt1 最近点对在曲线1上的点
 * @param pt2 最近点对在曲线2上的点
 */
double MinDistancePointPair(curve const& cur1, curve const& cur2, SPAposition& pt1, SPAposition& pt2);

/**
 * @brief 判断平面intcurve是否为圆
 * @return true表示是圆
 * @param cur1 曲线1
 * @param tol 容差
 */
bool intcurve_is_circle(bs3_curve curv1, double tol);

/**
 * @brief 剔除重复的交点(暴力剔除，待优化)
 * @param rn 待剔除重复交点的所有交点个数
 * @param rt_raw 待剔除重复交点的所有交点
 */
int CurvCurvIntPointReduce(curve_curve_int*& rt_raw);
