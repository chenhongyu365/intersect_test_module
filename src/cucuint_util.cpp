#include "cucuint_util.hxx"

#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "acis/acistol.hxx"
#include "acis/bs3ccont.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/condef.hxx"
#include "acis/cstrapi.hxx"
#include "acis/cucuint.hxx"
#include "acis/cur.hxx"
#include "acis/curve.hxx"
#include "acis/curve_approx.hxx"
#include "acis/cusfint.hxx"
#include "acis/elldef.hxx"
#include "acis/exct_int.hxx"
#include "acis/geom_utl.hxx"
#include "acis/heldef.hxx"
#include "acis/intcucu.hxx"
#include "acis/intcusf.hxx"
#include "acis/intdef.hxx"
#include "acis/kernapi.hxx"
#include "acis/law.hxx"
#include "acis/math.hxx"
#include "acis/matrix.hxx"
#include "acis/par_int.hxx"
#include "acis/param.hxx"
#include "acis/pcudef.hxx"
#include "acis/pladef.hxx"
#include "acis/rem_api.hxx"
#include "acis/sp3crtn.hxx"
#include "acis/sps2crtn.hxx"
#include "acis/sps3crtn.hxx"
#include "acis/strdef.hxx"
#include "acis/tordef.hxx"
#include "acis/vec.hxx"
#include "acis/vector_utils.hxx"

/*@todo
 * 1.cur2.param_range 解耦导致CircleNURBSIntrTest.TestReverse等4个错误
 * 2.c1.param_range 解耦导致NurbsNurbsIntrTest.TestBug60错误
 * 3.api_nroots_of_law 解耦导致HelixBSplineIntrTest.Reverse1等9个错误
 * 4.param 在求交总耗时中占比达到60%，暂不解耦
 * 5.bs3_curve_knot_mult 求交耗时过长暂不解耦
 * 6.bound 耗时过长暂不解耦
 */

/**
 * @brief 将线线求交的单链表组织的所有交点 按照param1升序输出
 * @return 排序后的所有交点的首节点
 * @param inters 输入所有交点的首节点
 */
curve_curve_int* sort_inters(curve_curve_int* inters) {
    if(inters == nullptr) {
        return nullptr;
    }
    std::vector<std::pair<double, curve_curve_int*>> cucuint_list;
    while(inters) {
        cucuint_list.push_back(std::make_pair(inters->param1, inters));
        inters = inters->next;
    }
    std::sort(cucuint_list.begin(), cucuint_list.end());
    int n = cucuint_list.size();
    for(int i = n - 2; i >= 0; --i) {
        cucuint_list[i].second->next = cucuint_list[i + 1].second;
    }
    cucuint_list[n - 1].second->next = nullptr;
    return cucuint_list[0].second;
}

/**
 * @brief 将线线求交的单链表组织的所有交点 按照param1升序输出
 * @param inters 输入所有交点的首节点
 * @param choose_param 选择按照param1还是param2排序
 * @return 排序后的所有交点的首节点
 */
curve_curve_int* sort_inters_with_param(curve_curve_int* inters, SortParamType choose_param) {
    if(inters == nullptr) {
        return nullptr;
    }
    using PDC = std::pair<double, curve_curve_int*>;
    std::vector<PDC> cucuint_list;
    while(inters) {
        if(choose_param == SortParamType::Param1) {
            cucuint_list.push_back(std::make_pair(inters->param1, inters));
        } else {
            cucuint_list.push_back(std::make_pair(inters->param2, inters));
        }
        inters = inters->next;
    }
    std::sort(cucuint_list.begin(), cucuint_list.end());
    int n = cucuint_list.size();
    for(int i = n - 2; i >= 0; --i) {
        cucuint_list[i].second->next = cucuint_list[i + 1].second;
    }
    cucuint_list[n - 1].second->next = nullptr;
    return cucuint_list[0].second;
}

/**
 * @brief 将椭圆ell转化为0<ratio<1的椭圆new_ell
 * @param ell 待转化的椭圆
 * @param new_ell 转化后的椭圆
 */
void transfer_ellipse(ellipse const& ell, ellipse& new_ell) {
    if(ell.radius_ratio - 1.0 > SPAresabs) {
        // ratio > 1

        SPAvector major_axis = ell.major_axis;
        double a = major_axis.len() * ell.radius_ratio;
        SPAvector minor_axis = normalise(ell.normal * ell.major_axis) * a;

        new_ell.major_axis = minor_axis;
        new_ell.param_off = ell.param_off;
        new_ell.radius_ratio = 1 / ell.radius_ratio;
        new_ell.normal = ell.normal;
        new_ell.centre = ell.centre;
        if(ell.subsetted() && ell.param_range() != SPAinterval{-M_PI, M_PI}) {
            new_ell.limit(recompute_param_range(ell.param_range(), &ell, &new_ell));
        }
    } else if(ell.radius_ratio < -SPAresabs) {
        // ratio < 0

        new_ell = ell;
        new_ell.radius_ratio = -new_ell.radius_ratio;
        new_ell.limit(ell.param_range());
    } else {
        new_ell = ell;
        new_ell.limit(ell.param_range());
    }
}

/**
 * @brief 交换线线求交结果中的param1和param2，并按照新的param1的升序返回求交结果
 * @return  交换后的求交结果
 * @param inters 待交换的求交结果
 */
curve_curve_int* swap_param(curve_curve_int* inters) {
    curve_curve_int* res = inters;
    double param = NAN;
    while(inters) {
        param = inters->param1;
        inters->param1 = inters->param2;
        inters->param2 = param;
        inters = inters->next;
    }
    inters = res = sort_inters(res);
    while(inters) {
        if((inters->low_rel == curve_curve_rel::cur_cur_coin && inters->high_rel == curve_curve_rel::cur_cur_unknown) || (inters->low_rel == curve_curve_rel::cur_cur_unknown && inters->high_rel == curve_curve_rel::cur_cur_coin)) {
            inters->low_rel = curve_curve_rel::cur_cur_unknown;
            inters->high_rel = curve_curve_rel::cur_cur_coin;
            inters = inters->next;
            while(inters) {
                if(inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin) {
                    break;
                }
                inters = inters->next;
            }
            if(!inters) {
                // 异常
                break;
            }
            inters->low_rel = curve_curve_rel::cur_cur_coin;
            inters->high_rel = curve_curve_rel::cur_cur_unknown;
        }
        inters = inters->next;
    }
    return res;
}

/**
 * @brief 将param参数为val，修改为-val 默认val为-M_PI，即将-M_PI调整为M_PI
 * @param param 参数
 * @param tol 容差
 * @param val -pi
 * @return refine后的值
 */
double refine_param(double param, double tol, double val) {
    if(fabs(param - val) < tol) {
        return -val;
    } else {
        return param;
    }
}

/**
 * @brief 获得螺旋线h所在的圆柱或双圆锥
 *        若h为圆柱螺旋线 则返回h所在圆柱为c1，c2为null
 *        若h为圆锥螺旋线 则返回h所在的圆锥c1和c2
 * @return 1: h为圆柱螺旋线，2: h为圆锥螺旋线
 * @param h 输入螺旋线
 * @param c1 输出的圆柱或圆锥
 * @param c2 输出的圆柱或圆锥
 */
int cone_of_helix(const helix& h, cone*& c1, cone*& c2) {
    SPAposition axis_root = h.axis_root();
    SPAunit_vector axis_dir = h.axis_dir();
    SPAvector start_disp = h.start_disp();
    SPAvector start_disp_proj = start_disp - (start_disp % axis_dir) * axis_dir;
    ellipse base(axis_root, axis_dir, start_disp_proj, 1.0);  // 底面为圆
    double taper = h.taper();
    double pitch = h.pitch();
    double hypotenuse = sqrt(taper * taper + pitch * pitch);
    double sin_ang = taper / hypotenuse;
    double cos_ang = fabs(pitch) / hypotenuse;  // cos_ang为正 保证cone为convex
    if(fabs(taper) <= SPAresabs) {              // 返回圆柱
        c1 = ACIS_NEW cone(base, sin_ang, cos_ang);
        c2 = nullptr;
        return 1;
    } else {  // 双圆锥
        double radius = start_disp_proj.len();
        double z = fabs(radius * pitch / taper);
        double sgn_taper = taper > SPAresabs ? 1.0 : -1.0;
        SPAvector vec = -sgn_taper * axis_dir * z;  // vec指向半径减少的方向
        SPAposition centre2 = base.centre + 2 * vec;
        ellipse base2(centre2, -axis_dir, -base.major_axis, 1.0);
        c1 = ACIS_NEW cone(base, sin_ang, cos_ang);
        c2 = ACIS_NEW cone(base2, sin_ang, cos_ang);
        return 2;
    }
}

/**
 * @brief 已知直线cs_line在cs_helix所在的圆柱或圆锥上，求cs_line和cs_helix的所有交点
 * @return cs_line和cs_helix的所有交点
 * @param cs_line 输入直线
 * @param cs_helix 输入螺旋线
 */
curve_curve_int* coin_line_helix_int(straight const& cs_line, helix const& cs_helix) {
    cone *c1 = nullptr, *c2 = nullptr;
    // 获得螺旋线所在的圆柱c1或者双圆锥c1, c2
    cone_of_helix(cs_helix, c1, c2);

    // c1的底面(椭)圆与直线求交
    curve_curve_int* line_ell_inter = nullptr;
    if(!cs_line.param_range().infinite()) {
        curve* unsubset_line = cs_line.unsubset();
        line_ell_inter = int_cur_cur(c1->base, *unsubset_line);
        ACIS_DELETE unsubset_line;
    } else {
        line_ell_inter = int_cur_cur(c1->base, cs_line);
    }

    curve_curve_int *head = nullptr, *end = nullptr, *tmp = nullptr;  // 返回交点结果的头结点，尾结点，临时变量
    head = end = ZeroInter;
    SPAinterval param_range = cs_helix.param_range();  // 待解耦 存在问题 @todo: helix相关问题 ==> 已修复
    double param1 = NAN, param2 = NAN, param = NAN;
    SPAposition int_point;
    const double tol = SPAresabs;
    if(line_ell_inter) {
        param = line_ell_inter->param1;  // 直线与(椭)圆的交点在(椭)圆上的参数
        // 直线方向与螺旋线主轴方向相同 交点顺序为螺旋线的参数从小到大增加
        if(cs_line.direction % cs_helix.axis_dir() > 0) {
            int N = (param_range.start_pt() - param) / (2 * M_PI);
            for(int i = N; param + i * (2 * M_PI) <= param_range.end_pt() + tol; ++i) {
                if(param + i * (2 * M_PI) << param_range) {
                    param2 = param + i * (2 * M_PI);
                    int_point = cs_helix.eval_position(param2);
                    end->next = ACIS_NEW curve_curve_int(nullptr, int_point, 0.0, 0.0);
                    end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_unknown;
                    end = end->next;
                }
            }
        } else {  // 直线方向与螺旋线主轴方向相反 交点顺序为螺旋线的参数从大到小减少
            int N = 1 + (param_range.end_pt() - param) / (2 * M_PI);
            for(int i = N; param + i * (2 * M_PI) >= param_range.start_pt() - tol; --i) {
                if(param + i * (2 * M_PI) << param_range) {
                    param2 = param + i * (2 * M_PI);
                    int_point = cs_helix.eval_position(param2);
                    end->next = ACIS_NEW curve_curve_int(nullptr, int_point, 0.0, 0.0);
                    end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_unknown;
                    end = end->next;
                }
            }
        }

        // 销毁直线与圆求交的辅助交点
        delete_curve_curve_ints(line_ell_inter);
    }
    end->next = nullptr;
    auto ret = head->next;
    ACIS_DELETE head;
    ACIS_DELETE c1;
    ACIS_DELETE c2;
    return ret;
}

/**
 * @brief 将两个次数相同的多项式求和
 * @param paras1 第一个多项式系数数组
 * @param paras2 第二个多项式系数数组
 * @param parasResult 求和的结果
 * @param num 多项式的次数
 */
void AddTwoPoly(double paras1[], double paras2[], double parasResult[], int num) {
    for(int i = 0; i < num; i++) {
        parasResult[i] = paras1[i] + paras2[i];
    }
}

/**
 * @brief 将array的前num个元素设置为0
 * @param array
 * @param num
 */
void SetArrayToZero(double array[], int num) {
    for(int i = 0; i < num; i++) {
        array[i] = 0;
    }
}

/**
 * @brief 计算定义于[u0, u1, u2]的B样条曲线基函数Ni,1(u)，只计算u属于区间[us, ue]的多项式系数
 * @param u0
 * @param u1
 * @param u2 [u0, u1, u2]为B样条曲线基函数Ni,1(u)的参数
 * @param us
 * @param ue [us, ue]为输入的Ni,1(u)的定义域
 * @param paras 输出的多项式系数
 */
void GetLinearPoly(double u0, double u1, double u2, double us, double ue, double paras[2]) {
    double paraTwo1[2], paraTwo2[2];  // paraTwo1为N0,1(u)在[u0,u1)内的分段函数，paraTwo2为N0,1(u)在[u1,u2)内的分段函数
    if(fabs(u0 - u1) < SPAresabs) {   // u0 = u1, N0,1(u) = 0
        paraTwo1[0] = 0;
        paraTwo1[1] = 0;
    } else {
        if(us >= u0 && ue <= u1) {  // u属于[u0,u1), N0,1(u) = (u-ui)/(ui+1-ui)
            paraTwo1[0] = -u0 / (u1 - u0);
            paraTwo1[1] = 1 / (u1 - u0);
        } else {
            paraTwo1[0] = 0;
            paraTwo1[1] = 0;
        }
    }

    if(fabs(u2 - u1) < SPAresabs) {  // u1 = u2, N0,1(u) = 0
        paraTwo2[0] = 0;
        paraTwo2[1] = 0;
    } else {
        if(us >= u1 && ue <= u2) {  // u属于[u1,u2), N0,1(u) = (u2-u)/(u2-u1)
            paraTwo2[0] = u2 / (u2 - u1);
            paraTwo2[1] = -1 / (u2 - u1);
        } else {
            paraTwo2[0] = 0;
            paraTwo2[1] = 0;
        }
    }

    SetArrayToZero(paras, 2);
    AddTwoPoly(paraTwo1, paraTwo2, paras, 2);  // paras = paraTwo1 + paraTwo2，u属于[u_s, u_e]
}

/**
 * @brief 计算两个一元多项式的乘积
 * @param paras1 第一个一元多项式的系数
 * @param num1 paras1系数的个数
 * @param paras2 第二个一元多项式的系数
 * @param num2 paras2系数的个数
 * @param paraResult 输出变量；paraResult为paras1和paras2乘积多项式的多项式系数数组
 * @param num paraResult的系数个数
 */
void GetMultiUniVarPoly(double paras1[], int num1, double paras2[], int num2, double paraResult[], int& num) {
    num = num1 + num2;
    int i = 0;

    for(i = 0; i <= num; i++) {
        paraResult[i] = 0;
    }

    for(i = 0; i <= num1; i++) {
        for(int j = 0; j <= num2; j++) {
            paraResult[i + j] += paras1[i] * paras2[j];
        }
    }
}

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
void GetQuadraticPoly(double u0, double u1, double u2, double u3, double us, double ue, double paras[3]) {
    // Ni,2(u) = Ni,1(u)*(u - ui)/(ui+2 - ui) + Ni+1,1(u)*(ui+3 - u)/(ui+3 - ui+1)
    double paraTwo1[2], paraTwo2[2], paraTwo3[2], paraTwo4[2];
    // paraTwo1代表(u - ui)/(ui+2 - ui) u属于[us, ue]
    // paraTwo2代表(ui+3 - u)/(ui+3 - ui+1) u属于[us, ue]
    // paraTwo3代表Ni,1(u) u属于[us, ue]
    // paraTwo4代表Ni+1,1(u) u属于[us, ue]
    double parasThree1[3], parasThree2[3];
    // parasThree1 = paraTwo1*paraTwo3
    // parasThree2 = paraTwo2*paraTwo4

    // paras=paraTwo1*paraTwo3 + paraTwo2*paraTwo4
    if(fabs(u2 - u0) < SPAresabs) {
        paraTwo1[0] = 0;
        paraTwo1[1] = 0;
    } else {
        if(us >= u0 && ue <= u2) {
            paraTwo1[0] = -u0 / (u2 - u0);
            paraTwo1[1] = 1 / (u2 - u0);
        } else {
            paraTwo1[0] = 0;
            paraTwo1[1] = 0;
        }
    }

    if(fabs(u3 - u1) < SPAresabs) {
        paraTwo2[0] = 0;
        paraTwo2[1] = 0;
    } else {
        if(us >= u1 && ue <= u3) {
            paraTwo2[0] = u3 / (u3 - u1);
            paraTwo2[1] = -1 / (u3 - u1);
        } else {
            paraTwo2[0] = 0;
            paraTwo2[1] = 0;
        }
    }

    GetLinearPoly(u0, u1, u2, us, ue, paraTwo3);
    GetLinearPoly(u1, u2, u3, us, ue, paraTwo4);
    SetArrayToZero(parasThree1, 3);
    SetArrayToZero(parasThree2, 3);
    int num = 0;
    GetMultiUniVarPoly(paraTwo1, 1, paraTwo3, 1, parasThree1, num);
    GetMultiUniVarPoly(paraTwo2, 1, paraTwo4, 1, parasThree2, num);
    SetArrayToZero(paras, 3);
    AddTwoPoly(parasThree1, parasThree2, paras, 3);
}

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
void GetCubicPoly(double u0, double u1, double u2, double u3, double u4, double us, double ue, double paras[4]) {
    // Ni,3(u) = Ni,2(u)*(u - ui)/(ui+3 - ui) + Ni+1,2(u)*(ui+4 - u)/(ui+4 - ui+1)
    double paraTwo1[2], paraTwo2[2];
    // paraTwo1代表(u - ui)/(ui+3 - ui)，u属于[us, ue]
    // paraTwo2代表(ui+4 - u)/(ui+4 - ui+1)，u属于[us, ue]
    double parasThree1[3], parasThree2[3];
    // paraThree1代表Ni,2(u)，u属于[us, ue]
    // paraThree2代表Ni+1,2(u)，u属于[us, ue]
    double parasFour1[4], parasFour2[4];
    // paras=paraTwo1*parasThree1 + paraTwo2*parasThree2
    if(fabs(u3 - u0) < SPAresabs) {
        paraTwo1[0] = 0;
        paraTwo1[1] = 0;
    } else {
        if(us >= u0 && ue <= u3) {
            paraTwo1[0] = -u0 / (u3 - u0);
            paraTwo1[1] = 1 / (u3 - u0);
        } else {
            paraTwo1[0] = 0;
            paraTwo1[1] = 0;
        }
    }

    if(fabs(u4 - u1) < SPAresabs) {
        paraTwo2[0] = 0;
        paraTwo2[1] = 0;
    } else {
        if(us >= u1 && ue <= u4) {
            paraTwo2[0] = u4 / (u4 - u1);
            paraTwo2[1] = -1 / (u4 - u1);
        } else {
            paraTwo2[0] = 0;
            paraTwo2[1] = 0;
        }
    }

    GetQuadraticPoly(u0, u1, u2, u3, us, ue, parasThree1);  // 计算Ni,2(u)
    GetQuadraticPoly(u1, u2, u3, u4, us, ue, parasThree2);  // 计算Ni+1,2(u)
    SetArrayToZero(parasFour1, 4);
    SetArrayToZero(parasFour2, 4);
    int num = 0;
    GetMultiUniVarPoly(paraTwo1, 1, parasThree1, 2, parasFour1, num);  // 计算paraTwo1 * Ni,2(u)
    GetMultiUniVarPoly(paraTwo2, 1, parasThree2, 2, parasFour2, num);  // 计算paraTwo2 * Ni+1,2(u)
    SetArrayToZero(paras, 4);
    // Ni,3(u) = paraTwo1 * Ni,2(u) + paraTwo2 * Ni+1,2(u)
    AddTwoPoly(parasFour1, parasFour2, paras, 4);
}

/**
 * @brief 求一元n次多项式方程的所有根
 * @return 根的个数
 * @param degree 多项式方程的最高次数
 * @param dxyCoef 存储多项式方程的系数，从次数最高的系数开始存储
 * @param root 输出所求得的根，求得的根在[start, end]范围内
 * @param start
 * @param end [start, end]为所需要根的参数范围
 */
int Equatn(int degree, double* dxyCoef, double*& root, double start, double end) {
    std::string expression;
    std::string tmp;
    for(int i = 0; i < degree; ++i) {
        if(i) {
            tmp = std::format("+{}x^{}", dxyCoef[i], degree - i);
        } else {
            tmp = std::format("{}x^{}", dxyCoef[i], degree - i);
        }
        expression += dxyCoef[i] < 0 ? std::format("-{}x^{}", -dxyCoef[i], degree - i) : tmp;  // dxyCoef先从高次系数 再到低次系数
    }

    expression += dxyCoef[degree] < 0 ? std::format("-{}", -dxyCoef[degree]) : std::format("+{}", dxyCoef[degree]);  // 常数项

    int number_roots = 0;
    law* function_law = nullptr;
    api_str_to_law(expression.c_str(), &function_law);
    check_outcome(api_nroots_of_law(function_law, start, end, &number_roots, &root));  // @todo: 存在内存泄漏
    if(function_law) {
        function_law->remove();
    }

    return number_roots;
}

/**
 * @brief 获得样条曲线bs在参数范围[start, end]内的子曲线
 * @return bs在[start,end]的子曲线
 * @param bs 输入的样条曲线 该接口不改变该曲线
 * @param start
 * @param end [start, end]为子曲线的参数范围 要求[start, end]在bs的参数范围内
 */
bs3_curve bs3_curve_split_interval(bs3_curve bs, double start, double end) {
    if(start - end > SPAresabs) {  // 若 start > end, 则交换start 和 end
        double tmp = start;
        start = end;
        end = tmp;
    }
    SPAinterval range = bs3_curve_range(bs);
    if(SPAinterval(start, end) == range) {
        return bs3_curve_copy(bs);
    }

    bs3_curve copy = bs3_curve_copy(bs);
    bs3_curve sub_bs = nullptr;
    if(bs3_curve_closed(copy) || bs3_curve_periodic(copy)) {
        bs3_curve_set_open(copy);
    }
    // @todo: bs3_curve_split函数改为gme版本会出现中断
    sub_bs = bs3_curve_split(copy, start);
    bs3_curve_delete(sub_bs);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    sub_bs = bs3_curve_split(copy, end);
    bs3_curve_delete(copy);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    return sub_bs;
}

/**
 * @brief 设置样条曲线bs的权重为weight
 * @param bs 输入的样条曲线，接口会修改该曲线
 * @param weight 需要设置的曲线权重
 */
void bs3_curve_set_weights(bs3_curve& bs, double* weight) {
    int num_ctrlpts = 0;
    SPAposition* ctrl = nullptr;
    bs3_curve_control_points(bs, num_ctrlpts, ctrl);
    double* pos = ACIS_NEW double[num_ctrlpts * 3];
    for(int i = 0; i < num_ctrlpts; ++i) {
        pos[3 * i] = ctrl[i].x();
        pos[3 * i + 1] = ctrl[i].y();
        pos[3 * i + 2] = ctrl[i].z();
    }
    bs3_curve_set_ctrlpts(bs, num_ctrlpts, pos, weight);
    ACIS_DELETE[] STD_CAST pos;
    ACIS_DELETE[] ctrl;
    pos = nullptr;
    ctrl = nullptr;
}

/**
 * @brief 将样条曲线的权重归一化
 * @param bs 输入的样条曲线，要求该曲线为多段Bezier形式，若不是，则接口会出错
 */
void bs3_curve_normalise_weight(bs3_curve& bs) {
    if(bs && bs3_curve_rational(bs) && check_rational(bs)) {
        double* weight = nullptr;
        int num_ctrlpts = 0, degree = 0, i = 0, j = 0;
        degree = bs3_curve_degree(bs);
        bs3_curve_weights(bs, num_ctrlpts, weight);
        double* new_weight = ACIS_NEW double[num_ctrlpts];
        for(i = 0; i < num_ctrlpts - degree; i += degree) {
            for(j = 0; j < degree; ++j) {
                new_weight[i + j] = (weight[i + j] / weight[i + degree]) * pow(weight[i + degree] / weight[i], 1 - 1.0 * j / degree);
            }
        }
        new_weight[num_ctrlpts - 1] = 1.0;

        bs3_curve_set_weights(bs, new_weight);
        ACIS_DELETE[] STD_CAST weight;
        ACIS_DELETE[] STD_CAST new_weight;
        weight = new_weight = nullptr;
    }
}

// 获得[st, ed]区间内 样条曲线的节点向量个数 只用于debug
int count_bs3_curve_interval(bs3_curve bs, double st, double ed, double tol) {
    bs3_curve bs_1 = bs3_curve_split_interval(bs, st, ed);
    int ans = 0;
    double* knots = nullptr;
    bs3_curve_knots(bs_1, ans, knots);
    bs3_curve_delete(bs_1);
    ACIS_DELETE[] STD_CAST knots;
    return ans;
}

void GetKnotNoRepeat(int n, int& nn, double* knot, double* nknot, double tol) {
    nknot[0] = knot[0];
    nn = 1;
    for(int i = 1; i < n; i++) {
        if(fabs(knot[i] - knot[i - 1]) > tol) {
            nknot[nn] = knot[i];
            nn++;
        }
    }
}

/**
 * @brief 将样条曲线curv1和curv2的节点向量调整到一致
 *        前提：curv1和curv2的次数，有理性，参数范围保持一致，均为多段Bezier形式，且首尾端点距离在容差tol内
 * @param curv1 输入曲线1
 * @param curv2 输入曲线2
 * @param tol 容差
 */
void bs3_curve_normalise_knot(bs3_curve curv1, bs3_curve curv2, double tol) {
    if(!curv1 || !curv2) {
        return;
    }
    //// 重新参数化到[0, 1]
    /// 注: 对曲线重新参数化可能会导致曲线的节点向量重数压缩，导致节点向量的重数非法
    // bs3_curve_reparam(0, 1, curv1);
    // bs3_curve_reparam(0, 1, curv2);

    int pre_i, pre_j;
    int cur_i, cur_j;
    pre_i = pre_j = cur_i = cur_j = 0;
    int degree = bs3_curve_degree(curv1);  // 要求两个曲线的degree一致
    double knot_tol = bs3_curve_knottol();

    double *knots1 = nullptr, *knots2 = nullptr;
    int num_knots1 = 0, num_knots2 = 0;

    bs3_curve_knots(curv1, num_knots1, knots1);
    bs3_curve_knots(curv2, num_knots2, knots2);
    GetKnotNoRepeat(num_knots1, num_knots1, knots1, knots1, knot_tol);
    GetKnotNoRepeat(num_knots2, num_knots2, knots2, knots2, knot_tol);

    SPAposition *ctrlpts1 = nullptr, *ctrlpts2 = nullptr;
    int num_ctrlpts1 = 0, num_ctrlpts2 = 0;

    bs3_curve_control_points(curv1, num_ctrlpts1, ctrlpts1);
    bs3_curve_control_points(curv2, num_ctrlpts2, ctrlpts2);

    if(distance_to_point(ctrlpts1[0], ctrlpts2[0]) > tol || distance_to_point(ctrlpts1[num_ctrlpts1 - 1], ctrlpts2[num_ctrlpts2 - 1]) > tol) {
        ACIS_DELETE[] STD_CAST knots1;
        ACIS_DELETE[] STD_CAST knots2;
        ACIS_DELETE[] ctrlpts1;
        ACIS_DELETE[] ctrlpts2;
        knots1 = knots2 = nullptr;
        ctrlpts1 = ctrlpts2 = nullptr;
        return;
    }
    while(pre_i < num_knots1 - 1 && pre_j < num_knots2 - 1) {
        // find cur_i
        cur_i = pre_i + 1;
        cur_j = pre_j + 1;
        double dis = 0;
        double pre_dis1, pre_dis2;
        while(cur_i < num_knots1 && cur_j < num_knots2 && (dis = distance_to_point(ctrlpts1[degree * cur_i], ctrlpts2[degree * cur_j]), dis > tol)) {
            pre_dis1 = distance_to_point(ctrlpts1[degree * cur_i], ctrlpts1[degree * pre_i]);
            pre_dis2 = distance_to_point(ctrlpts2[degree * cur_j], ctrlpts2[degree * pre_j]);
            if(pre_dis1 > pre_dis2) {
                ++cur_j;
            } else if(pre_dis1 < pre_dis2) {
                ++cur_i;
            } else {
                ++cur_i, ++cur_j;
            }
        }

        if(cur_i == num_knots1) --cur_i;
        if(cur_j == num_knots2) --cur_j;

        // the last bezier LinesegBSplineIntrTest.TestBug58
        if(cur_i == num_knots1 - 1 && cur_j != num_knots2 - 1) {
            cur_j = num_knots2 - 1;
        } else if(cur_i != num_knots1 - 1 && cur_j == num_knots2 - 1) {
            cur_i = num_knots1 - 1;
        }

        double pre_knot_val = knots2[pre_j];
        // insert knot between [pre_i, cur_i], [pre_j, cur_j]
        for(int i = pre_i + 1; i <= cur_i; ++i) {
            double weight = (knots1[i] - knots1[pre_i]) / (knots1[cur_i] - knots1[pre_i]);
            int multi1 = bs3_curve_knot_mult(curv1, knots1[i], knot_tol);
            double knot_val = knots2[pre_j] + weight * (knots2[cur_j] - knots2[pre_j]);
            while(fabs(knot_val - pre_knot_val) <= knot_tol) {
                // 由于数值损失，新添加的节点和之前的节点在容差范围内
                // 通过添加容差补偿
                // ConeCylinderTest
                knot_val += knot_tol;
            }
            pre_knot_val = knot_val;
            int multi2 = bs3_curve_knot_mult(curv2, knot_val, knot_tol);
            int i2 = bs3_curve_add_knot(curv2, knot_val, std::min(degree, std::max(multi1 - multi2, 0)), knot_tol);
        }
        pre_knot_val = knots1[pre_i];
        for(int j = pre_j + 1; j <= cur_j; ++j) {
            double weight = (knots2[j] - knots2[pre_j]) / (knots2[cur_j] - knots2[pre_j]);
            int multi1 = bs3_curve_knot_mult(curv2, knots2[j], knot_tol);
            double knot_val = knots1[pre_i] + weight * (knots1[cur_i] - knots1[pre_i]);
            while(fabs(knot_val - pre_knot_val) <= knot_tol) {
                // 由于数值损失，新添加的节点和之前的节点在容差范围内
                // 通过添加容差补偿
                knot_val += knot_tol;
            }
            pre_knot_val = knot_val;
            int multi2 = bs3_curve_knot_mult(curv1, knot_val, knot_tol);
            int i1 = bs3_curve_add_knot(curv1, knot_val, std::min(degree, std::max(multi1 - multi2, 0)), knot_tol);
        }
        // if(count_bs3_curve_interval(curv1, knots1[pre_i], knots1[cur_i], 1e-10) != count_bs3_curve_interval(curv2, knots2[pre_j], knots2[cur_j], 1e-10)) {
        //     int a;
        //     a = 1;
        // }
        pre_i = cur_i, pre_j = cur_j;
    }
    ACIS_DELETE[] STD_CAST knots1;
    ACIS_DELETE[] STD_CAST knots2;
    ACIS_DELETE[] ctrlpts1;
    ACIS_DELETE[] ctrlpts2;
    knots1 = knots2 = nullptr;
    ctrlpts1 = ctrlpts2 = nullptr;
}

/**
 * @brief 将样条曲线bs转换为多段Bezier形式
 * @param bs 输入的样条曲线
 */
void nurbs_to_multiple_rbeziers(bs3_curve& bs) {
    int num_knots = 0;
    double* knots = nullptr;
    bs3_curve_knots(bs, num_knots, knots);
    const double knottol = bs3_curve_knottol();
    GetKnotNoRepeat(num_knots, num_knots, knots, knots, knottol);
    int degree = bs3_curve_degree(bs);
    for(int i = 0; i < num_knots; ++i) {
        // int mult = bs3_curve_knot_mult(bs, knots[i], knottol);
        if(i == 0 || i == num_knots - 1) {
            bs3_curve_add_knot(bs, knots[i], degree + 1, knottol);
        } else {
            bs3_curve_add_knot(bs, knots[i], degree, knottol);
        }
    }
    ACIS_DELETE[] STD_CAST knots;
    knots = nullptr;
}

/**
 * @brief 检查有理B样条曲线是否可以退化为非有理曲线
 * @return TRUE: 可退化 FALSE: 不可退化
 * @param bs3 输入样条曲线
 */
logical check_rational(bs3_curve bs3) {
    logical rational = FALSE;
    if(bs3 && bs3_curve_rational(bs3)) {
        double* weights = nullptr;
        int num_pts = 0;
        bs3_curve_weights(bs3, num_pts, weights);
        double tol = 1e-10;
        int i = 0;
        for(i = 0; i < num_pts; ++i) {
            if(fabs(weights[i] - 1.0) > tol) {
                rational = TRUE;
                break;
            }
        }
        if(i == num_pts) {
            rational = FALSE;
        }
        ACIS_DELETE[] STD_CAST weights;
        weights = nullptr;
    }
    return rational;
}

/**
 * @brief 判断sub_curv1和sub_curv2是否在容差tol内完全重合
 * @return TRUE: 完全重合 FALSE: 不完全重合
 * @param sub_curv1 输入曲线1
 * @param sub_curv2 输入曲线2
 * @param tol 重合容差
 * @param reversed sub_curv1和sub_curv2是否参数化相反
 */
logical test_coin(bs3_curve sub_curv1, bs3_curve sub_curv2, double tol, logical reversed) {
    if(sub_curv1 == nullptr || sub_curv2 == nullptr) {
        // split得到的子曲线可能因为参数太接近，而返回nullptr
        bs3_curve_delete(sub_curv1);  // 待解耦，存在问题 @todo: bs3_curve相关问题
        bs3_curve_delete(sub_curv2);  // 待解耦，存在问题 @todo: bs3_curve相关问题
        return FALSE;
    }

    // 检查包围盒是否重合
    if(!(bs3_curve_box(sub_curv1, tol) && bs3_curve_box(sub_curv2, tol))) {
        bs3_curve_delete(sub_curv1);
        bs3_curve_delete(sub_curv2);
        return FALSE;
    }

    if(reversed) {
        // reversed
        bs3_curve_reverse(sub_curv2);
    }

    if(bs3_curve_rational(sub_curv1) || bs3_curve_rational(sub_curv2)) {  // 待解耦，存在问题 @todo: bs3_curve相关问题
        // 若两个有一个是rational，则将其转化为nurbs曲线
        bs3_curve_make_rational(sub_curv1);
        bs3_curve_make_rational(sub_curv2);
    }
    SPAinterval range1 = bs3_curve_range(sub_curv1);
    SPAinterval range2 = bs3_curve_range(sub_curv2);

    // 重新参数化
    // 优先重新参数化到大的参数范围，防止节点重数压缩 ConeCylinderTest.Case5
    if(range1.length() > range2.length()) {
        bs3_curve_reparam(range1.start_pt(), range1.end_pt(), sub_curv2);
    } else {
        bs3_curve_reparam(range2.start_pt(), range2.end_pt(), sub_curv1);
    }
    double *knot1 = nullptr, *knot2 = nullptr;
    int num_knot1 = 0, num_knot2 = 0;

    bs3_curve_knots(sub_curv1, num_knot1, knot1);
    bs3_curve_knots(sub_curv2, num_knot2, knot2);
    double knottol = bs3_curve_knottol();

    // 添加权重归一化
    bs3_curve_normalise_weight(sub_curv1);
    bs3_curve_normalise_weight(sub_curv2);

    bs3_curve_normalise_knot(sub_curv1, sub_curv2, tol);

    if(0) {
        int i = 0, j = 0;
        int mul1 = 0, mul2 = 0;  // 重数

        // 调整sub_curv1和sub_curv2的节点向量 使其一致
        for(i = 0; i < num_knot2; ++i) {
            if(i == 0 || (i > 0 && fabs(knot2[i] - knot2[i - 1]) > knottol)) {
                mul1 = bs3_curve_knot_mult(sub_curv1, knot2[i], knottol);
                mul2 = bs3_curve_knot_mult(sub_curv2, knot2[i], knottol);
                bs3_curve_add_knot(sub_curv1, knot2[i], D3_max(mul1, mul2) - mul1, knottol);
            }
        }

        for(i = 0; i < num_knot1; ++i) {
            if(i == 0 || (i > 0 && fabs(knot1[i] - knot1[i - 1]) > knottol)) {
                mul1 = bs3_curve_knot_mult(sub_curv1, knot1[i], knottol);
                mul2 = bs3_curve_knot_mult(sub_curv2, knot1[i], knottol);
                bs3_curve_add_knot(sub_curv2, knot1[i], D3_max(mul1, mul2) - mul2, knottol);
            }
        }
    }

    bs3_curve_normalise_weight(sub_curv1);
    bs3_curve_normalise_weight(sub_curv2);

    logical coin = FALSE;
    // 判断控制多边形是否重合
    if(cucuint_bs3_curve_same(sub_curv1, sub_curv2, tol * 10, TRUE)) {
        coin = TRUE;
    }
    bs3_curve_delete(sub_curv1);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    bs3_curve_delete(sub_curv2);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    ACIS_DELETE[] STD_CAST knot1;
    ACIS_DELETE[] STD_CAST knot2;
    knot1 = knot2 = nullptr;
    return coin;
}

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
logical test_self_inter_point(double param, bs3_curve bs3, double& next_param, double tol) {
    logical is_self_inter_point = FALSE;
    if(bs3) {
        SPAinterval bs3_range = bs3_curve_range(bs3);
        if(param << bs3_range) {
            const double margin = tol * 10;
            // @todo: bs3_curve_split存在问题之后统一解耦
            bs3_curve bs3_copy = bs3_curve_copy(bs3);
            bs3_curve st_curv = bs3_curve_split(bs3_copy, param - margin);
            bs3_curve ed_curv = bs3_copy;
            bs3_copy = bs3_curve_split(ed_curv, param + margin);

            SPAposition pos = bs3_curve_position(param, bs3);
            if(st_curv && bs3_curve_testpt(pos, tol, st_curv)) {
                is_self_inter_point = TRUE;
                next_param = bs3_curve_invert(pos, tol, st_curv);
            }
            if(!is_self_inter_point && ed_curv && bs3_curve_testpt(pos, tol, ed_curv)) {
                is_self_inter_point = TRUE;
                next_param = bs3_curve_invert(pos, tol, ed_curv);
            }
            bs3_curve_delete(bs3_copy);
            bs3_copy = st_curv = ed_curv = nullptr;
            // 存在next_param位于曲线范围外的情况
            if(is_self_inter_point == TRUE && !next_param << bs3_range) {
                is_self_inter_point = FALSE;
            }
        }
    }
    if(!is_self_inter_point) {
        next_param = param;
    }
    return is_self_inter_point;
}

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
int test_coincident(bs3_curve curv1, bs3_curve curv2, double param1, double param2, double tol, logical check_self_point, std::vector<std::tuple<int, double, double>>* records) {
    if(check_self_point && records) {
        records->clear();
        double next_param1 = param1, next_param2 = param2;

        // 暂时不判断自交点
        // int self_point1 = test_self_inter_point(param1, curv1, next_param1, tol);
        // int self_point2 = test_self_inter_point(param2, curv2, next_param2, tol);
        int self_point1 = 0;
        int self_point2 = 0;

        int count1 = self_point1 + 1;
        int count2 = self_point2 + 1;
        double param1_list[3] = {param1, next_param1};
        double param2_list[3] = {param2, next_param2};
        bool is_end1 = 0, is_end2 = 0;
        // check close and periodic curve ends
        // @todo:  bs3_curve_closed、bs3_curve_periodic、bs3_curve_range函数未解耦
        if((bs3_curve_closed(curv1) || bs3_curve_periodic(curv1))) {
            SPAinterval range = bs3_curve_range(curv1);
            if(fabs(param1 - range.start_pt()) <= tol) {
                param1_list[count1++] = range.end_pt();
                is_end1 = true;
            } else if(fabs(param1 - range.end_pt()) <= tol) {
                is_end1 = true;
                param1_list[count1++] = range.start_pt();
            }
        }
        if((bs3_curve_closed(curv2) || bs3_curve_periodic(curv2))) {
            SPAinterval range = bs3_curve_range(curv2);
            if(fabs(param2 - range.start_pt()) <= tol) {
                param2_list[count2++] = range.end_pt();
                is_end2 = true;
            } else if(fabs(param2 - range.end_pt()) <= tol) {
                param2_list[count2++] = range.start_pt();
                is_end2 = true;
            }
        }

        int coin_ret = 0;
        if(is_end1 && is_end2) {
            const double margin = tol * 100;
            SPAinterval range1 = bs3_curve_range(curv1), range2 = bs3_curve_range(curv2);
            // 考虑nurbs曲线参数化的不同,此处反求参数
            SPAposition pos1 = bs3_curve_position(range1.start_pt() + margin, curv1);
            SPAposition pos2 = bs3_curve_position(range1.end_pt() - margin, curv1);
            double st2 = bs3_curve_invert(pos1, SPAresabs, curv2);
            double ed2 = bs3_curve_invert(pos2, SPAresabs, curv2);
            if((coin_ret = test_coincident(curv1, curv2, range1.start_pt() + margin, st2, tol)) != 0) {
                double _st2 = coin_ret == 1 ? range2.start_pt() : range2.end_pt();
                records->push_back({coin_ret, range1.start_pt(), _st2});  // @todo: 端点参数判断
            }
            if((coin_ret = test_coincident(curv1, curv2, range1.end_pt() - margin, ed2, tol)) != 0) {
                double _ed2 = coin_ret == 1 ? range2.end_pt() : range2.start_pt();
                records->push_back({coin_ret, range1.end_pt(), _ed2});
            }
        } else {
            for(int i = 0; i < count1; ++i) {
                for(int j = 0; j < count2; ++j) {
                    if((coin_ret = test_coincident(curv1, curv2, param1_list[i], param2_list[j], tol)) != 0) {
                        records->push_back({coin_ret, param1_list[i], param2_list[j]});
                    }
                }
            }
        }
        return records->empty() ? 0 : 3;  // 3代表混合记录
    } else {
        tol *= 10;  // 调整容差
        double G2_tol = 5 * tol;
        /** @todo: 有容差的重合检测，如何调整容差 */
        if(curv1 && curv2) {
            SPAposition pos_cur1 = bs3_curve_position(param1, curv1), pos_cur2 = bs3_curve_position(param2, curv2);
            if(distance_to_point(pos_cur1, pos_cur2) > tol) {
                return 0;
            }

            logical irr1 = check_irregular_G1(curv1, param1);
            logical irr2 = check_irregular_G1(curv2, param2);

            SPAvector dt_cur1, dt_cur2;
            if(irr1 || irr2) {
                double margin = SPAresabs;
                dt_cur1 = bs3_curve_deriv(param1 - margin, curv1), dt_cur2 = bs3_curve_deriv(param2 - margin, curv2);
                // G1连续即可，不用C1连续(模长不用比较)
                bool flag = false;
                if(biparallel(dt_cur1, dt_cur2, tol)) {
                    flag = true;
                    SPAvector k_cur1 = bs3_curve_curvature(param1 - margin, curv1), k_cur2 = bs3_curve_curvature(param2 - margin, curv2);
                    double angle = VEC_acute_angle(k_cur1, k_cur2);
                    // if(fabs(k_cur1.len() - k_cur2.len()) > C2_tol) {  // C2连续
                    if(fabs(angle) > G2_tol) {  // G2连续
                        return 0;
                    }
                }

                if(!flag && (dt_cur1 = bs3_curve_deriv(param1 + margin, curv1), dt_cur2 = bs3_curve_deriv(param2 + margin, curv2), biparallel(dt_cur1, dt_cur2, tol))) {
                    flag = true;
                    SPAvector k_cur1 = bs3_curve_curvature(param1 + margin, curv1), k_cur2 = bs3_curve_curvature(param2 + margin, curv2);
                    // if(fabs(k_cur1.len() - k_cur2.len()) > C2_tol) {  // C2连续
                    double angle = VEC_acute_angle(k_cur1, k_cur2);
                    if(fabs(angle) > G2_tol) {  // G2连续
                        return 0;
                    }
                }

                if(!flag) {
                    return 0;
                }
            } else {
                dt_cur1 = bs3_curve_deriv(param1, curv1), dt_cur2 = bs3_curve_deriv(param2, curv2);
                // if(dt_cur1.len_sq() - dt_cur2.len_sq() > tol || !biparallel(dt_cur1, dt_cur2, tol)) {
                if(!biparallel(dt_cur1, dt_cur2, tol)) {  // G1连续
                    return 0;
                }
                SPAvector k_cur1 = bs3_curve_curvature(param1, curv1), k_cur2 = bs3_curve_curvature(param2, curv2);
                double k1 = k_cur1.len();
                double k2 = k_cur2.len();
                double angle = VEC_acute_angle(k_cur1, k_cur2);
                if(fabs(angle) > G2_tol) {  // G2连续
                    // if(fabs(k_cur1.len() - k_cur2.len()) > C2_tol) {  // C2连续
                    return 0;
                }
            }
            // parallel存在问题 PlaneTorusInterTest.Case6
            if(parallel(dt_cur1, dt_cur2, tol)) {
                return 1;  // 同向重合
            } else if(antiparallel(dt_cur1, dt_cur2, tol)) {
                return 2;  // 反向重合
            } else {
                return 0;
            }
        }
        return 0;
    }
}

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
int detect_coincident(bs3_curve curv1, bs3_curve curv2, curve_curve_int*& inters, std::vector<SPAinterval>& inter_ints1, std::vector<SPAinterval>& inter_ints2, double tol) {
    inter_ints1.clear();
    inter_ints2.clear();
    if(curv1 == nullptr || curv2 == nullptr) {
        inters = nullptr;
        return 0;
    }
    if(!(bs3_curve_box(curv1, tol) && bs3_curve_box(curv2, tol))) {
        inters = nullptr;
        return 0;
    }
    int degree1 = bs3_curve_degree(curv1), degree2 = bs3_curve_degree(curv2);
    /** @todo: 三次以上的重合判断 有待后续添加 */
    if(degree1 > 3 || degree2 > 3) {
        inters = nullptr;
        return 0;
    }
    int i = 0, j = 0;
    bs3_curve curv1_cp = bs3_curve_copy(curv1), curv2_cp = bs3_curve_copy(curv2);

    // 使curv1_cp和curv2_cp的次数一致
    int degree = D3_max(degree1, degree2);
    for(i = 1; i <= degree - degree1; ++i) {
        bs3_curve_degree_elevate(curv1_cp);  // @todo: 中断 CstrFuncTest.LoopTypeTest16
    }
    for(i = 1; i <= degree - degree2; ++i) {
        bs3_curve_degree_elevate(curv2_cp);
    }

    // 获取curv1_cp的节点向量knot1，curv2_cp的节点向量knot2
    double *knot1 = nullptr, *knot2 = nullptr;
    int num_knot1 = 0, num_knot2 = 0;
    bs3_curve_knots(curv1_cp, num_knot1, knot1);
    bs3_curve_knots(curv2_cp, num_knot2, knot2);

    double *nknot1 = nullptr, *nknot2 = nullptr;
    nknot1 = ACIS_NEW double[num_knot1];
    nknot2 = ACIS_NEW double[num_knot2];
    int distinct_nknot1 = 0, distinct_nknot2 = 0;
    GetKnotNoRepeat(num_knot1, distinct_nknot1, knot1, nknot1);  // 将knot1去重 去重后的节点向量存于nknot1
    GetKnotNoRepeat(num_knot2, distinct_nknot2, knot2, nknot2);  // 将knot2去重 去重后的节点向量存于nknot2

    double param1 = NAN, param2 = NAN, param = NAN;
    std::vector<double> param1_array;  // 可能重合的段在曲线1上的参数
    SPAposition pos1, pos2, pos;
    SPAposition end1 = bs3_curve_end(curv1), end2 = bs3_curve_end(curv2);                // 曲线2的端点
    logical no_open1 = 1 - bs3_curve_open(curv2), no_open2 = 1 - bs3_curve_open(curv2);  // 曲线2是否为闭曲线或者周期曲线
    SPAinterval range1 = bs3_curve_range(curv1), range2 = bs3_curve_range(curv2);

    double invert_tol = tol;  // 1e-10
    double knottol = bs3_curve_knottol();
    for(i = 0; i < distinct_nknot1; ++i) {
        // @todo:bs3_curve_position耗时过长暂不解耦
        pos = bs3_curve_position(nknot1[i], curv1_cp);     // @todo: 耗时较长
        if(bs3_curve_testpt(pos, invert_tol, curv2_cp)) {  // 待解耦，存在问题 @todo: bs3_curve相关问题
            param1_array.push_back(nknot1[i]);
        }
    }

    for(i = 0; i < distinct_nknot2; ++i) {
        // @todo:bs3_curve_position耗时过长暂不解耦
        pos = bs3_curve_position(nknot2[i], curv2_cp);            // @todo: 耗时较长
        if(bs3_curve_testpt(pos, invert_tol, curv1_cp)) {         // 待解耦，存在问题 @todo: bs3_curve相关问题
            param = bs3_curve_invert(pos, invert_tol, curv1_cp);  // 待解耦，存在问题 @todo: bs3_curve相关问题
            param1_array.push_back(param);
            if(no_open1 && is_equal(pos, end1)) {
                param1_array.push_back(range1.end_pt());
            }
        }
    }
    std::sort(param1_array.begin(), param1_array.end());
    auto compare = [knottol](double p1, double p2) { return fabs(p1 - p2) <= knottol; };  // 此处设置为knottol 1e-10
    param1_array.erase(std::unique(param1_array.begin(), param1_array.end(), compare), param1_array.end());

    curve_curve_int *head = nullptr, *end = nullptr, *inter1 = nullptr, *inter2 = nullptr;
    int num_segs = 0;  // 重合的段数
    head = end = ZeroInter;
    double start_param1 = NAN, end_param1 = NAN, start_param2 = NAN, end_param2 = NAN;
    double start_param[4], end_param[4];
    std::vector<std::pair<curve_curve_int*, curve_curve_int*>> inters_list;

    std::vector<std::tuple<int, double, double>> coin_records;  // 重合记录
    std::vector<std::tuple<int, double, double>> tmp_records;
    for(i = 0; i < static_cast<int>(param1_array.size()); ++i) {
        double st1 = param1_array[i];
        // @todo:bs3_curve_position耗时过长暂不解耦
        SPAposition pos = bs3_curve_position(st1, curv1_cp);
        double st2 = bs3_curve_invert(pos, invert_tol, curv2_cp);
        int coin = test_coincident(curv1_cp, curv2_cp, st1, st2, tol, TRUE, &tmp_records);
        if(coin != 0) {
            coin_records.insert(coin_records.end(), tmp_records.begin(), tmp_records.end());
        }
    }
    // sort coin_records
    std::sort(coin_records.begin(), coin_records.end());

    // 对coin_records进行去重
    auto tcompare = [knottol](std::tuple<int, double, double> const& v1, std::tuple<int, double, double> const& v2) {
        return std::get<0>(v1) == std::get<0>(v2) && fabs(std::get<1>(v1) - std::get<1>(v2)) <= knottol && fabs(std::get<2>(v1) - std::get<2>(v2)) <= knottol;
    };
    coin_records.erase(std::unique(coin_records.begin(), coin_records.end(), tcompare), coin_records.end());

    for(int i = 0; i < coin_records.size(); ++i) {
        if(i && std::get<0>(coin_records[i]) == 1 && std::get<2>(coin_records[i]) - std::get<2>(coin_records[i - 1]) < -knottol) {
            // last_i 为 不满足同向重合的点，考虑该点有多个参数 交换同一个点在coin_records的相对顺序
            int last_pos = i - 1, last_i = i;
            double last_param1 = std::get<1>(coin_records[last_i]);
            double last_param2 = std::get<2>(coin_records[last_pos]);
            while(i + 1 < coin_records.size() && fabs(std::get<1>(coin_records[i + 1]) - last_param1) <= knottol && std::get<2>(coin_records[i + 1]) - last_param2 < -knottol) ++i;
            if(i + 1 < coin_records.size() && fabs(std::get<1>(coin_records[i + 1]) - last_param1) <= knottol && std::get<2>(coin_records[i + 1]) - last_param2 >= -knottol) {
                std::swap(coin_records[last_i], coin_records[i + 1]);
            }
            i = last_i;
        }
    }

    if(!coin_records.empty()) {
        auto iter = std::upper_bound(coin_records.begin(), coin_records.end(), 1, [](int val, std::tuple<int, double, double> p) { return val < std::get<0>(p); });
        int non_reverse_num = iter - coin_records.begin();
        int nums[2] = {non_reverse_num, static_cast<int>(coin_records.size()) - non_reverse_num};

        std::vector<std::vector<double>> coin_array;
        std::vector<std::vector<double>> coin_array_source1;
        std::vector<std::vector<double>> coin_array_source2;
        double st1, st2, ed1, ed2;
        auto iter_start = coin_records.begin(), iter_end = coin_records.begin();
        for(int i = 0; i < 2; ++i) {
            if(iter_start == coin_records.end()) {
                break;
            }
            iter_end += nums[i];
            auto iter_next = iter_start + 1;
            auto iter_pre = iter_start;
            bool incresed;
            while(iter_next < iter_end) {
                incresed = false;
                // 单调增加
                while(iter_next != iter_end && std::get<2>(*iter_next) >= std::get<2>(*iter_pre)) {
                    incresed = true;
                    iter_pre = iter_next;
                    iter_next++;
                }
                // 单调减少
                while(!incresed && iter_next != iter_end && std::get<2>(*iter_next) <= std::get<2>(*iter_pre)) {
                    iter_pre = iter_next;
                    iter_next++;
                }
                coin_array.push_back({std::get<1>(*iter_start), std::get<1>(*iter_pre), std::get<2>(*iter_start), std::get<2>(*iter_pre), 1.0 - i});

                auto tmp = iter_start;
                std::vector<double> source1, source2;
                while(tmp <= iter_pre) {
                    source1.push_back(std::get<1>(*tmp));
                    source2.push_back(std::get<2>(*tmp));
                    ++tmp;
                }
                coin_array_source1.push_back(source1);
                coin_array_source2.push_back(source2);
                iter_start = iter_pre;
            }
            iter_start = iter_end;
        }
        for(int i = 0; i < coin_array.size(); ++i) {
            st1 = coin_array[i][0];
            ed1 = coin_array[i][1];
            st2 = coin_array[i][2];
            ed2 = coin_array[i][3];
            logical reversed = fabs(coin_array[i][4]) <= SPAresabs ? TRUE : FALSE;

            auto const& source1 = coin_array_source1[i];
            auto const& source2 = coin_array_source2[i];

            bs3_curve sub_curv1 = bs3_curve_split_interval(curv1_cp, st1, ed1);
            bs3_curve sub_curv2 = bs3_curve_split_interval(curv2_cp, st2, ed2);

            if(sub_curv1 && sub_curv2) {
                nurbs_to_multiple_rbeziers(sub_curv1);
                nurbs_to_multiple_rbeziers(sub_curv2);
                // @todo: 需要测试是否需要下面的部分
                // double knottol = bs3_curve_knottol();  // 调整容差，避免出现在bezier结点附近插入结点
                //// 注意 该容差不能小于1e-10
                for(int i = 0; i < source1.size(); ++i) {
                    int multi1 = bs3_curve_knot_mult(sub_curv1, source1[i], knottol);
                    int i1 = bs3_curve_add_knot(sub_curv1, source1[i], std::max(0, degree - multi1), knottol);
                    int multi2 = bs3_curve_knot_mult(sub_curv2, source2[i], knottol);
                    int i2 = bs3_curve_add_knot(sub_curv2, source2[i], std::max(0, degree - multi2), knottol);
                }
            }

            if(test_coin(sub_curv1, sub_curv2, tol, reversed)) {
                // @todo:bs3_curve_position耗时过长暂不解耦
                pos1 = bs3_curve_position(st1, curv1_cp);
                end->next = ACIS_NEW curve_curve_int(nullptr, pos1, st1, st2);
                end->next->low_rel = curve_curve_rel::cur_cur_unknown;
                end->next->high_rel = curve_curve_rel::cur_cur_coin;
                end = end->next;
                inter1 = end;

                // @todo:bs3_curve_position耗时过长暂不解耦
                pos2 = bs3_curve_position(ed1, curv1_cp);
                end->next = ACIS_NEW curve_curve_int(nullptr, pos2, ed1, ed2);
                end->next->low_rel = curve_curve_rel::cur_cur_coin;
                end->next->high_rel = curve_curve_rel::cur_cur_unknown;
                end = end->next;
                inter2 = end;
                inters_list.push_back(std::make_pair(inter1, inter2));
                num_segs++;
            }
        }
    }

    // 合并与去除重合区间
    num_segs = merge_coin_inters(inters_list, tol);

    if(num_segs > 0) {
        end = head;
        // 重新连接求交结果
        for(i = 0; i < inters_list.size(); ++i) {
            if(inters_list[i].first) {
                end->next = inters_list[i].first;
                end = end->next;
            }
            if(inters_list[i].second) {
                end->next = inters_list[i].second;
                end = end->next;
            }
            if(inters_list[i].first && inters_list[i].second) {
                inter_ints1.push_back(SPAinterval(inters_list[i].first->param1, inters_list[i].second->param1));
                inter_ints2.push_back(SPAinterval(inters_list[i].first->param2, inters_list[i].second->param2));
            }
        }
    }

    end->next = nullptr;

    if(inter_ints1.size() == 1 && inter_ints2.size() == 1 && bs3_curve_periodic(curv1_cp) && bs3_curve_periodic(curv2_cp)) {
        if(inter_ints1[0] == range1 && inter_ints2[0].length() <= SPAresabs) {
            inter_ints2[0] = SPAinterval(inter_ints2[0].start_pt(), inter_ints2[0].start_pt() + bs3_curve_period(curv2_cp));
            if(head->next && head->next->next) {
                head->next->next->param2 = inter_ints2[0].end_pt();
            }
        }
    }
    ACIS_DELETE[] STD_CAST knot1;
    ACIS_DELETE[] STD_CAST knot2;
    ACIS_DELETE[] STD_CAST nknot1;
    ACIS_DELETE[] STD_CAST nknot2;
    bs3_curve_delete(curv1_cp);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    bs3_curve_delete(curv2_cp);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    curv1_cp = curv2_cp = nullptr;
    inters = head->next;
    ACIS_DELETE head;
    knot1 = knot2 = nknot1 = nknot2 = nullptr;
    return num_segs;
}

/**
 * @brief 剔除交点结果inters在所有重合参数区间coin_ints内的交点，只检查param1
 * @return 剔除后的交点结果
 * @param inters 输入交点结果
 * @param coin_ints 所有重合参数区间
 */
curve_curve_int* delete_coin(curve_curve_int* inters, std::vector<SPAinterval> const& coin_ints) {
    if(coin_ints.size() > 0) {
        int i = 0;
        // 剔除重合段范围内的交点
        curve_curve_int *end = nullptr, *head = nullptr, *tmp = nullptr;
        end = head = ZeroInter;
        int has_delete = 0;
        while(inters) {
            has_delete = FALSE;
            for(i = 0; i < coin_ints.size(); ++i) {
                if(inters->param1 << coin_ints[i]) {  // 销毁交点
                    tmp = inters;
                    inters = inters->next;
                    ACIS_DELETE tmp;
                    has_delete = TRUE;
                    break;
                }
            }
            if(!has_delete) {
                end->next = inters;
                end = end->next;
                inters = inters->next;
            }
        }
        end->next = nullptr;
        inters = head->next;
        ACIS_DELETE head;
    }
    return inters;
}

/**
 * @brief ratio>1的椭圆ell和曲线curv求交，返回交点结果
 * @return 线线求交结果
 * @param ell 输入ratio>1的椭圆
 * @param curv 输入曲线
 * @param box 包围盒
 * @param tol 容差
 */
curve_curve_int* irregular_ellipse_inters(ellipse const& ell, curve const& curv, SPAbox const& box, double tol) {
    curve_curve_int* inters = nullptr;
    ellipse new_ell;
    transfer_ellipse(ell, new_ell);
    inters = int_cur_cur(new_ell, curv, box, tol);
    curve_curve_int* tmp = inters;
    while(tmp) {
        tmp->param1 = refine_param(ell.param(tmp->int_point), SPAresabs);
        tmp = tmp->next;
    }
    inters = sort_inters(inters);
    return inters;
}

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
int helix_slove_equat1(double a, double b, double theta, double sgn, double st, double ed, std::vector<double>& roots) {
    roots.clear();
    double tol = SPAresabs;
    SPAinterval t_range(st, ed);
    if(fabs(sgn - 1.0) <= tol) {    // sgn = 1
        if(fabs(a - 1.0) <= tol) {  // a = 1
            double k = (b - theta) / (2 * M_PI);
            if(fabs(k - (int)k) <= tol) {  // k为整数 方程存在无穷个解
                return -1;
            } else {  // k不为整数，方程无解
                return 0;
            }
        } else {  // a != 1
            // k = (t * (a - 1) - theta + b) / (2 * PI)
            // t 在 [st, ed]区间内
            int k_min = (st * (a - 1) - theta + b) / (2 * M_PI);
            int k_max = (ed * (a - 1) - theta + b) / (2 * M_PI);
            if(a < 1.0) {
                std::swap(k_min, k_max);
            }
            --k_min, ++k_max;
            for(int k = k_min; k <= k_max; ++k) {
                double t = (theta - b + k * 2 * M_PI) / (a - 1);
                if(t << t_range) {
                    roots.push_back(t);
                }
            }
        }
    } else if(fabs(sgn + 1.0) <= tol) {  // sgn = -1
        if(fabs(a + 1) <= tol) {         // a = -1
            double k = (theta + b) / (2 * M_PI);
            if(fabs(k - (int)k) <= tol) {  // k为整数 方程存在无穷个解
                return -1;
            } else {
                return 0;
            }
        } else {  // a != -1
            // k = (t * (a + 1) + theta + b) / (2 * PI)
            // t 在 [st, ed]区间内
            int k_min = (st * (a + 1) + theta + b) / (2 * M_PI);
            int k_max = (ed * (a + 1) + theta + b) / (2 * M_PI);
            if(a < -1.0) {
                std::swap(k_min, k_max);
            }
            --k_min, ++k_max;
            for(int k = k_min; k <= k_max; ++k) {
                double t = (k * 2 * M_PI - (theta + b)) / (a + 1);
                if(t << t_range) {
                    roots.push_back(t);
                }
            }
        }
    }

    return roots.size();
}

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
int helix_slove_equat2(double r1, double dr1, double a, double b, double r2, double dr2, double theta, double sgn, double st, double ed, std::vector<double>& roots) {
    roots.clear();

    SPAinterval t_range(st, ed);
    auto eq1 = [&](double t2) {
        double left = (r1 + dr1 * (a * t2 + b)) * cos(a * t2 + b);
        double right = (r2 + dr2 * t2) * cos(t2 + theta);
        return left - right;
    };
    auto eq2 = [&](double t2) {
        double left = (r1 + dr1 * (a * t2 + b)) * sin(a * t2 + b);
        double right = sgn * (r2 + dr2 * t2) * sin(t2 + theta);
        return left - right;
    };

    double tol = SPAresabs;
    if(fabs(sgn - 1.0) <= tol) {    // sgn = 1
        if(fabs(a - 1.0) <= tol) {  // a = 1
            double k = (b - theta) / M_PI;
            // k为整数，判断为无穷解
            if(fabs(k - (int)k) <= tol && fabs((r1 + dr1 * b) * cos(b) - r2 * cos(theta)) <= tol) {
                return -1;
            } else {
                return 0;
            }
        } else {
            int k_min = ((a - 1) * st + b - theta) / (M_PI);
            int k_max = ((a - 1) * ed + b - theta) / (M_PI);
            if(a < 1.0) {
                std::swap(k_min, k_max);
            }
            --k_min, ++k_max;
            for(int k = k_min; k <= k_max; ++k) {
                double t = (theta - b + k * M_PI) / (a - 1);
                if(t << t_range && fabs(eq1(t)) <= tol && fabs(eq2(t)) <= tol) {
                    roots.push_back(t);
                }
            }
        }
    } else if(fabs(sgn + 1.0) <= tol) {  // sgn = -1
        if(fabs(a + 1.0) <= tol) {       // a = -1
            double k = (b + theta) / M_PI;
            // k为整数，判断为无穷解
            if(fabs(k - (int)k) <= tol && fabs((r1 + dr1 * b) * cos(b) - r2 * cos(theta)) <= tol) {
                return -1;
            } else {
                return 0;
            }
        } else {
            int k_min = ((a + 1) * st + b + theta) / (M_PI);
            int k_max = ((a + 1) * ed + b + theta) / (M_PI);
            if(a < -1.0) {
                std::swap(k_min, k_max);
            }
            --k_min, ++k_max;
            for(int k = k_min; k <= k_max; ++k) {
                double t = (k * M_PI - (b + theta)) / (a + 1);
                if(t << t_range && fabs(eq1(t)) <= tol && fabs(eq2(t)) <= tol) {
                    roots.push_back(t);
                }
            }
        }
    }
    // 特判
    double t = -r2 / dr2;
    if(t << t_range && fabs(eq1(t)) <= tol && fabs(eq2(t)) <= tol && std::find(roots.begin(), roots.end(), t) == roots.end()) {
        roots.push_back(t);
    }

    return roots.size();
}

/**
 * @brief 向量的元素相乘
 * @return 输出向量元素相乘的结果
 * @param vec1 输入向量1
 * @param vec2 输入向量2
 */
SPAvector vector_multiple(SPAvector const& vec1, SPAvector const& vec2) {
    return SPAvector(vec1.x() * vec2.x(), vec1.y() * vec2.y(), vec1.z() * vec2.z());
}

/**
 * @brief 共面的(椭)圆与平面螺旋线求交
 * @return (椭)圆与平面螺旋线求交的结果
 * @param ell 输入的(椭)圆
 * @param h 输入的平面螺旋线
 */
curve_curve_int* coplanar_ellipse_planar_helix_int(ellipse const& _ell, helix const& h) {
    // 平面螺旋线的局部坐标系 helix_center, helix_vx, helix_vy, helix_vz
    SPAposition helix_center = h.axis_root();
    SPAunit_vector helix_vx = h.maj_dir();
    SPAunit_vector helix_vz = h.axis_dir();
    SPAunit_vector helix_vy = normalise(helix_vz * helix_vx);

    ellipse ell;
    transfer_ellipse(_ell, ell);
    // (椭)圆的局部坐标系 ell_center, ell_vx, ell_vy, ell_vz
    SPAposition ell_center = ell.centre;
    SPAunit_vector ell_vx = normalise(ell.major_axis);
    SPAunit_vector ell_vz = ell.normal;
    SPAunit_vector ell_vy = normalise(ell_vz * ell_vx);

    // 从世界坐标系转化到平面螺旋线的局部坐标系的过渡矩阵
    SPAmatrix matrix(helix_vx, helix_vy, helix_vz);

    // 将(椭)圆的局部坐标系转化到平面螺旋线的局部坐标系内
    SPAposition ZeroPos(0, 0, 0);
    SPAposition ell_center_loc = ZeroPos + matrix * (ell_center - helix_center);
    SPAunit_vector ell_vx_loc = normalise(matrix * ell_vx);
    SPAunit_vector ell_vy_loc = normalise(matrix * ell_vy);
    SPAunit_vector ell_vz_loc = normalise(matrix * ell_vz);

    double taper = h.taper() / (2 * M_PI);
    double sgn = h.handedness() ? 1.0 : -1.0;
    double r = h.radius();
    std::string expression;
    if(fabs(ell.radius_ratio - 1) <= SPAresabs) {  // 圆和平面螺旋线
        if(is_equal(ell.centre, helix_center)) {   // 圆心和螺旋线的原点重合
            double circle_r_square = ell.major_axis.len_sq();
            double a1 = ell_vx_loc.len_sq();
            double a2 = ell_vy_loc.len_sq();
            double a3 = 2 * ell_vx % ell_vy;
            expression = std::format("({}+{}*x)^2*({}*(cos(x))^2+{}*(sin(x))^2+{}*sin(x)*cos(x))-{}", r, taper, a1, a2, a3, circle_r_square);
            // 方程为(r+taper*x)^2*(a1*(cosx)^2+a2*(sinx)^2+a3*sinx*cosx)-R=0
        } else {
            double m = ell_vx_loc % ell_center_loc;
            double n = ell_vy_loc % ell_center_loc;
            SPAvector vp(m, n, 0);
            SPAvector vp1(ell_vx_loc.x(), ell_vy_loc.x(), 0);
            SPAvector vp2(ell_vx_loc.y(), ell_vy_loc.y(), 0);
            double circle_r_square = ell.major_axis.len_sq();
            double a1 = ell_vx_loc.len_sq();
            double a2 = ell_vy_loc.len_sq();
            double a3 = 2 * sgn * (ell_vx_loc % ell_vy_loc);
            double a4 = -2 * (vp1 % vp);
            double a5 = -2 * sgn * (vp2 % vp);
            double a6 = m * m + n * n - circle_r_square;
            std::string str = std::format("({}+{}*x)", r, taper);
            expression = std::format("{}*{}^2*(cos(x))^2+{}*{}^2*(sin(x))^2+{}*{}^2*sin(x)*cos(x)+{}*{}*cos(x)+{}*{}*sin(x)+{}", a1, str, a2, str, a3, str, a4, str, a5, str, a6);
            // 方程为A(r+p*t)^2*(cost)^2+B(r+p*t)^2*(sint)^2+C(r+p*t)^2*sint*cost+D*(r+p*t)*cost+E*(r+p*t)*sint + F = 0
        }
    } else {  // 椭圆和平面螺旋线
        double a_square = ell.major_axis.len_sq();
        double b_square = ell.major_axis.len_sq() * ell.radius_ratio * ell.radius_ratio;
        if(is_equal(ell.centre, helix_center)) {  // 圆心和螺旋线的原点重合
            SPAvector v1(ell_vx_loc.x(), ell_vy_loc.x(), 0);
            SPAvector v2(ell_vx_loc.y(), ell_vy_loc.y(), 0);
            SPAvector vec1 = vector_multiple(v1, v1);
            SPAvector vec2 = vector_multiple(v2, v2);
            SPAvector vec3 = vector_multiple(v1, v2);
            SPAvector vec4(b_square, a_square, 0);
            double A = vec4 % vec1;
            double B = vec4 % vec2;
            double C = 2 * sgn * vec4 % vec3;
            expression = std::format("({}+{}*x)^2*({}*(cos(x))^2+{}*(sin(x))^2+{}*sin(x)*cos(x))+{}", r, taper, A, B, C, -a_square * b_square);
            // 方程为(r+taper*x)^2*(A* (cos(x))^2 +B* (sin(x))^2 +C*sin(x)*cos(x))+ D = 0
        } else {
            // 公式推导
            SPAvector x_vec(ell_vx_loc.x(), ell_vy_loc.x(), 0);
            SPAvector y_vec(ell_vx_loc.y(), ell_vy_loc.y(), 0);
            SPAvector aabb_vec(b_square, a_square, 0);
            SPAvector xx_vec = vector_multiple(x_vec, x_vec);
            SPAvector yy_vec = vector_multiple(y_vec, y_vec);
            SPAvector xy_vec = vector_multiple(x_vec, y_vec);
            SPAvector x_aabb_vec = vector_multiple(x_vec, aabb_vec);
            SPAvector y_aabb_vec = vector_multiple(y_vec, aabb_vec);
            SPAvector cp_vec(ell_vx_loc % ell_center_loc, ell_vy_loc % ell_center_loc, 0);
            SPAvector cp_square_vec = vector_multiple(cp_vec, cp_vec);
            double A = aabb_vec % xx_vec;
            double B = aabb_vec % yy_vec;
            double C = 2 * sgn * (aabb_vec % xy_vec);
            double D = -2 * (cp_vec % x_aabb_vec);
            double E = -2 * sgn * (cp_vec % y_aabb_vec);
            double F = cp_square_vec % aabb_vec - a_square * b_square;

            std::string str1 = std::format("({}{:+}*x)", r, taper);
            expression = std::format("{}*{}^2*(cos(x))^2+{}*{}^2*(sin(x))^2+{}*{}^2*sin(x)*cos(x)+{}*{}*cos(x)+{}*{}*sin(x)+{}", A, str1, B, str1, C, str1, D, str1, E, str1, F);
            // 公式推导结束，方程为A(r+taper*t)^2*(cost)^2+B(r+taper*t)^2*(sint)^2+C(r+taper*t)^2*sint*cost+D*(r+taper*t)*cost+E*(r+taper*t)*sint + F = 0
        }
    }

    // 方程求根
    law* law_string = nullptr;
    check_outcome(api_str_to_law(expression.c_str(), &law_string));

    double* t = nullptr;
    int root_number = 0;
    double st = h.param_range().start_pt(), ed = h.param_range().end_pt();   // 待解耦，存在问题 @todo: helix相关问题 ==> 已修复
    check_outcome(api_nroots_of_law(law_string, st, ed, &root_number, &t));  // @todo: 存在内存泄漏 EllipseHelixIntrTest.PlaneCoinInter 存在问题@todo: issue 2310
    // @todo: EllipseHelixIntrTest.TestBug14，GME漏根，ACIS根不准确

    // 从根中构造交点
    curve_curve_int *head = nullptr, *end = nullptr;
    head = end = ZeroInter;
    for(int i = 0; i < root_number; ++i) {
        double param2 = t[i];
        SPAposition int_point = h.eval_position(param2);
        double param1 = refine_param(ell.param(int_point), SPAresabs);
        end->next = ACIS_NEW curve_curve_int(nullptr, int_point, param1, param2);
        end = end->next;
    }
    end->next = nullptr;
    curve_curve_int* ret = head->next;

    // 销毁数据
    ACIS_DELETE head;
    ACIS_DELETE[] STD_CAST t;
    if(law_string) {
        law_string->remove();
    }

    return ret;
}

/**
 * @brief 将区间input转化到主参数曲线major_interval中，必要时将返回两个区间
 * @return 转化后的所有区间
 * @param input 输入的区间
 * @param period 周期
 * @param major_interval 主参数区间
 * @param tol 容差
 */
std::vector<SPAinterval> shift_interval_to_major(SPAinterval const& input, double period, SPAinterval const& major_interval, double tol) {
    std::vector<SPAinterval> ans;
    if(fabs(period) <= SPAresabs || major_interval.empty() || !input.finite()) {
        return {input};
    }

    double st = input.start_pt(), ed = input.end_pt();

    // st = ed
    if(fabs(st - ed) <= tol) {
        st = param_change_interval(st, major_interval, period);
        ans.push_back(SPAinterval(st));
    } else {
        if(st > ed + SPAresabs) {  // st > ed
            std::swap(st, ed);     // 要求 st <= ed
        }

        st = param_change_interval(st, major_interval, period);
        ed = param_change_interval(ed, major_interval, period);
        if(st < ed - tol) {  // st < ed
            ans.push_back(SPAinterval(st, ed));
        } else {  // st >= ed
            if(fabs(st - ed) <= tol) {
                // st = ed, 此时圆弧为完整一个周期
                ans.push_back(major_interval);
            } else {
                ans.push_back(SPAinterval(st, major_interval.end_pt()));
                ans.push_back(SPAinterval(major_interval.start_pt(), ed));
            }
        }
    }
    return ans;
}

/**
 * @brief 以period为周期，调整angle使其位于major_interval中
 * @return 调整后的angle
 * @param angle 输入的angle
 * @param period 输入的周期
 * @param major_interval 输入的主参数范围
 */
double param_change_interval(double angle, const SPAinterval& interval, double period) {
    if(fabs(period) <= SPAresabs) {
        return angle;
    }
    if(!(angle << interval)) {                            // 转化区间
        while(angle < interval.start_pt() - SPAresabs) {  // 小于区间
            angle += period;
        }
        while(angle > interval.end_pt() + SPAresabs) {  // 小于区间
            angle -= period;
        }
    }
    return angle;
}

/**
 * @brief 将区间interval转化到out_interval区间内，只保证interval.start_pt()转化到out_interval中
 *        保证区间长度不发生改变
 * @return 转化后的区间
 * @param interval 待转化的区间
 * @param out_interval 目的区间
 * @param period 周期
 * @param reversed reversed=false,interval代表升序的区间；reversed=true,interval代表降序的区间
 */
SPAinterval param_change_interval(SPAinterval const& interval, SPAinterval const& out_interval, double period, bool reversed) {
    if(fabs(period) <= SPAresabs) {
        return interval;
    }
    // 确保转化后区间左端点位于out_interval内 (若reversed为true，则确保转化后区间右端点位于out_interval内)
    double st = interval.start_pt(), ed = interval.end_pt();
    if(!reversed) {
        st = param_change_interval(st, out_interval, period);
        double offset = st - interval.start_pt();
        ed += offset;
    } else {
        ed = param_change_interval(ed, out_interval, period);
        double offset = ed - interval.end_pt();
        st += offset;
    }
    return SPAinterval(st, ed);
}

/**
 * @brief cur1与cur2重合，返回cur1参数为param处的坐标在cur2上的参数
 * @return cur2的对应参数
 * @param param cur1输入的参数
 * @param cur1
 * @param cur2
 */
double recompute_param(double param, curve const* ell1, curve const* ell2) {
    SPAposition pos = ell1->eval_position(param);
    return ell2->param(pos);  // 待解耦 存在问题(intcurve::param) @todo: intcurve相关问题
}

/**
 * @brief c1和c2重合，求c1在interval表示的曲线段在c2上的参数范围
 * @return c1在interval表示的曲线段在c2上的参数范围
 * @param interval 输入区间
 * @param c1
 * @param c2
 * @param tol 容差
 * @param reversed reversed=false 返回的区间为升序; reversed=true 返回的区间为降序
 */
SPAinterval recompute_param_range(SPAinterval const& interval, curve const* c1, curve const* c2, double tol, bool& reversed) {
    // 注: 若c1或c2是周期曲线且有参数限制(subseted)，则返回的参数区间不能保证在周期曲线的主参数范围内
    SPAinterval ans;

    if(&reversed) {
        reversed = false;
    }
    bool reversed_ans = false;
    if(c1 && c2) {
        // @todo: test_point_tol、param函数未解耦:param、test_point_tol函数耗时过长暂不解耦
        if(interval.length() <= tol) {
            SPAposition pos = c1->eval_position(interval.mid_pt());
            if(c2->test_point_tol(pos, tol)) {
                ans = SPAinterval(c2->param(pos));
            }
        } else {
            if(curve_periodic(*c2)) {
                double st1 = interval.start_pt(), ed1 = interval.end_pt();
                double st2 = recompute_param(st1, c1, c2), ed2 = recompute_param(ed1, c1, c2);
                double period1 = curve_period(*c1), period2 = curve_period(*c2);
                SPAposition mid_pos = c1->eval_position(0.5 * (st1 + ed1));
                bool is_parallel = parallel(c1->point_direction(mid_pos), c2->point_direction(mid_pos));  // 同向重合
                if(fabs(period2) <= tol) {
                    // 周期为0 考虑存在异常
                    return ans;
                }
                if(is_parallel && st2 >= ed2 - tol) {
                    while(st2 >= ed2 - tol) {
                        ed2 += period2;
                    }
                }
                if(!is_parallel && st2 <= ed2 + tol) {
                    while(st2 <= ed2 + tol) {
                        st2 += period2;
                    }
                }
                reversed_ans = st2 > ed2;
                ans = SPAinterval(st2, ed2);
            } else if(curve_closed(*c2)) {
                double st1 = interval.start_pt(), ed1 = interval.end_pt();
                double st2 = recompute_param(st1, c1, c2), ed2 = recompute_param(ed1, c1, c2);
                SPAposition mid_pos = c1->eval_position(0.5 * (st1 + ed1));
                bool is_parallel = parallel(c1->point_direction(mid_pos), c2->point_direction(mid_pos));  // 同向重合
                SPAunit_vector mid_pos_dir1 = c1->point_direction(mid_pos);
                SPAunit_vector mid_pos_dir2 = c2->point_direction(mid_pos);
                SPAinterval range2 = curve_major_interval(*c2);
                if(is_parallel && st2 >= ed2 - tol) {
                    if(fabs(st2 - range2.end_pt()) <= tol) {
                        st2 = range2.start_pt();
                    }
                    if(fabs(ed2 - range2.start_pt()) <= tol) {
                        ed2 = range2.end_pt();
                    }
                }
                if(!is_parallel && st2 <= ed2 + tol) {
                    if(mid_pos_dir1 % mid_pos_dir2 <= 0) {
                        if(fabs(st2 - range2.start_pt()) <= tol) {
                            st2 = range2.end_pt();
                        }
                        if(fabs(ed2 - range2.end_pt()) <= tol) {
                            ed2 = range2.start_pt();
                        }
                    }
                }
                reversed_ans = st2 > ed2;
                ans = SPAinterval(st2, ed2);
            } else {
                double st1 = interval.start_pt(), ed1 = interval.end_pt();
                double st2 = recompute_param(st1, c1, c2), ed2 = recompute_param(ed1, c1, c2);
                reversed_ans = st2 > ed2;
                ans = SPAinterval(st2, ed2);
            }
        }
    }
    if(&reversed) {
        reversed = reversed_ans;
    }
    return ans;
}

/**
 * @brief 重新计算重合结果中的参数
 * @param c1 输入曲线1
 * @param c2 输入曲线2
 * @param inters 待修改的重合结果
 * @param coin_ints1 待修改的在c1上的重合参数范围
 * @param coin_ints2 待修改的在c2上的重合参数范围
 * @param need_sort 是否需要对重合结果排序
 */
void recompute_coin_inters(curve const& c1, curve const& c2, curve_curve_int*& inters, std::vector<SPAinterval>& coin_ints1, std::vector<SPAinterval>& coin_ints2, bool need_sort) {
    if(inters && (&c1) && (&c2)) {
        coin_ints1.clear();
        coin_ints2.clear();
        if(need_sort) {
            for(auto inters_tmp = inters; inters_tmp; inters_tmp = inters_tmp->next) {
                inters_tmp->param1 = c1.param(inters_tmp->int_point);
            }
            inters = sort_inters(inters);
        }
        auto head = inters;
        // 要求inters按照param1有序
        while(inters) {
            if(inters && (inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin)) {
                auto pre = inters;
                auto cur = inters->next;
                while(cur && cur->low_rel != curve_curve_rel::cur_cur_coin && cur->high_rel != curve_curve_rel::cur_cur_coin) cur = cur->next;
                if(!cur) {
                    // 遇到不封闭的重合结果
                    inters = head;
                    return;
                }
                auto next = cur;
                inters = cur;
                // @todo: 未解耦08.29
                SPAinterval param_range1 = c1.param_range();
                // process [pre, next]
                pre->param1 = c1.param(pre->int_point), next->param1 = c1.param(next->int_point);
                if(pre->param1 >= next->param1 - SPAresabs) {
                    if(curve_periodic(c1)) {
                        if(fabs(pre->param1 - param_range1.end_pt()) <= SPAresabs) {
                            pre->param1 = param_range1.start_pt();
                        }
                        next->param1 = pre->param1 + curve_period(c1);
                    } else if(curve_closed(c1)) {
                        SPAinterval range = curve_major_interval(c1);
                        if(fabs(pre->param1 - range.end_pt()) <= SPAresabs) {
                            pre->param1 = range.start_pt();
                        } else if(fabs(next->param1 - range.start_pt()) <= SPAresabs) {
                            next->param1 = range.end_pt();
                        }
                    }
                }
                bool reversed = false;
                SPAinterval range = recompute_param_range({pre->param1, next->param1}, (curve*)&c1, (curve*)&c2, SPAresabs, reversed);
                pre->param2 = range.start_pt(), next->param2 = range.end_pt();
                if(reversed) {
                    std::swap(pre->param2, next->param2);
                }
                coin_ints1.push_back({pre->param1, next->param1});
                coin_ints2.push_back({pre->param2, next->param2});
            }
            inters = inters->next;
        }
        inters = head;
    }
}

/**
 * @brief 判断bs1和bs2的控制多边形是否完全重合
 * @return TRUE: bs1和bs2控制多边形完全重合 FALSE: bs1和bs2控制多边形不完全重合
 * @param bs1 输入的样条曲线
 * @param bs2 输入的样条曲线
 * @param tol 容差
 * @param no_knot_check FALSE: 需要检查节点向量是否完全一致; TRUE: 无需检查节点向量是否完全一致
 */
logical cucuint_bs3_curve_same(bs3_curve bs1, bs3_curve bs2, double tol, logical no_knot_check) {
    double *knot1, *knot2;
    SPAposition *position1, *position2;
    double *weight1, *weight2;
    int num_ctrlpts1, num_ctrlpts2;
    int num_knots1, num_knots2;
    // @todo: 存在中断
    // @todo: bs3_curve_knots、bs3_curve_weights、bs3_curve_control_points、bs3_curve_degree函数未解耦
    bs3_curve_knots(bs1, num_knots1, knot1);
    bs3_curve_knots(bs2, num_knots2, knot2);
    bs3_curve_weights(bs1, num_ctrlpts1, weight1);
    bs3_curve_weights(bs2, num_ctrlpts2, weight2);
    bs3_curve_control_points(bs1, num_ctrlpts1, position1);
    bs3_curve_control_points(bs2, num_ctrlpts2, position2);
    int degree1 = bs3_curve_degree(bs1), degree2 = bs3_curve_degree(bs2);
    logical same = TRUE;
    if(num_ctrlpts1 != num_ctrlpts2 || num_knots1 != num_knots2 || degree1 != degree2) {
        same = FALSE;
    }
    logical rational1 = bs3_curve_rational(bs1), rational2 = bs3_curve_rational(bs2);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    if(same && ((rational1 && !rational2) || (!rational1 && rational2))) {
        ACIS_DELETE[] STD_CAST knot1;
        ACIS_DELETE[] STD_CAST knot2;
        ACIS_DELETE[] STD_CAST weight1;
        ACIS_DELETE[] STD_CAST weight2;
        ACIS_DELETE[] position1;
        ACIS_DELETE[] position2;
        return FALSE;
    }
    if(!no_knot_check) {
        // do not check knots
        for(int i = 0; same && i < num_knots1; ++i) {
            if(fabs(knot1[i] - knot2[i]) > tol) {
                same = FALSE;
                break;
            }
        }
    }
    for(int i = 0; same && i < num_ctrlpts1; ++i) {
        if(fabs(distance_to_point(position1[i], position2[i])) > tol) {
            same = FALSE;
            break;
        }
        if(rational1) {
            if(fabs(weight1[i] - weight2[i]) > tol) {
                same = FALSE;
                break;
            }
        }
    }
    ACIS_DELETE[] STD_CAST knot1;
    ACIS_DELETE[] STD_CAST knot2;
    ACIS_DELETE[] STD_CAST weight1;
    ACIS_DELETE[] STD_CAST weight2;
    ACIS_DELETE[] position1;
    ACIS_DELETE[] position2;
    return same;
}

/**
 * @brief 统计线线求交结果中交点个数
 * @return 求交结果中交点的个数
 * @param inters 求交结果
 */
int count_inters(const curve_curve_int* inters) {
    int count = 0;
    while(inters) {
        count++;
        inters = inters->next;
    }
    return count;
}

/**
 * @brief 将bs3_curve转化为精确(exact_int_cur)的intcurve
 * @return 创建的intcurve
 * @param bs 输入的样条曲线bs3_curve
 */
intcurve* make_exact_intcurve(bs3_curve bs) {
    if(bs) {
        exact_int_cur* eic = ACIS_NEW exact_int_cur(bs);  // 待解耦，存在问题 @todo: int_cur相关问题
        intcurve* ic = ACIS_NEW intcurve(eic);
        return ic;
    } else {
        return nullptr;
    }
}

/**
 * @brief 已知螺旋线h和ic均位于圆锥c上，求h和ic的所有交点
 * @return h和ic的求交结果
 * @param c 圆柱/圆锥
 * @param h 螺旋线
 * @param ic intcurve
 */
curve_curve_int* cone_helix_bs3_int(cone const& c, helix const& h, intcurve* ic) {
    SPAinterval helix_param_range = h.param_range();
    double st = helix_param_range.start_pt(), ed = helix_param_range.end_pt();
    int k_min, k_max;

    straight s;
    double abs_cos = fabs(c.cosine_angle);
    double p = h.pitch() / (2 * M_PI);
    double sgn = h.handedness() ? 1.0 : -1.0;
    // s.direction = SPAunit_vector(p / abs_cos, sgn, 0);
    s.direction = SPAunit_vector(p / (abs_cos * c.u_param_scale), sgn, 0);

    curve_curve_int *head, *end, *ret, *tmp;
    head = end = ZeroInter;
    ret = tmp = nullptr;

    /** @todo: ACIS中pcurve的构造存在拟合误差，导致世界坐标系中的交点在曲面上的参数与实际的曲面参数有偏差 */
    pcurve pcurv(*ic, c, SPAresabs / 10);  // 待解耦，存在问题 @todo: pcurve相关问题

    bs2_curve bs2 = pcurv.cur();
    bs3_curve bs3_cone = bs2_curve_to_bs3_curve(bs2);  // 待解耦，存在问题 @todo: bs3_curve相关问题
    intcurve* bs3_cone_ic = make_exact_intcurve(bs3_cone);

    // k_min = int((st - M_PI) / (2 * M_PI)) - 1;
    // k_max = int((ed + M_PI) / (2 * M_PI)) + 1;
    k_min = static_cast<int>(0.5 * st / (h.pitch() * M_PI) + 0.5) - 1;
    k_max = static_cast<int>(0.5 * ed / (h.pitch() * M_PI) - 0.5) + 1;

    for(int k = k_min; k <= k_max; ++k) {
        s.root_point = SPAposition(2 * k * p * M_PI / (abs_cos * c.u_param_scale), 0, 0);
        double margin = h.pitch() * M_PI;
        SPAinterval range = {(2 * k - 1) * margin, (2 * k + 1) * margin};
        tmp = int_cur_cur(s, *bs3_cone_ic);

        while(tmp) {
            SPAposition int_point = tmp->int_point;
            SPApar_pos pp(int_point.x(), int_point.y());
            c.eval(pp, tmp->int_point);  // 待解耦，接口未实现
            double dis1 = distance_to_curve(tmp->int_point, h);
            double dis2 = distance_to_curve(tmp->int_point, *ic);
            if(dis1 <= 1e-10 && dis2 <= 1e-10) {
                end->next = tmp;
                end = end->next;
                tmp = tmp->next;
            } else {
                // refine 交点求精
                std::vector<SPAposition> points({tmp->int_point});
                end->next = tolerance_int_cur_cur(h, *ic, points, SPAresabs);
                if(end->next) {
                    end = end->next;
                }

                ret = tmp->next;
                ACIS_DELETE tmp;
                tmp = ret;
            }
        }
    }
    SPAposition apex = c.get_apex();
    // @todo: test_point_tol函数未解耦：耗时过长暂不解耦
    if(h.test_point_tol(apex, SPAresabs) && ic->test_point_tol(apex, SPAresabs)) {
        end->next = ACIS_NEW curve_curve_int(nullptr, apex, 0.0, 0.0);
        end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_unknown;
        end = end->next;
    }
    end->next = nullptr;
    ret = head->next;

    ACIS_DELETE head;
    ACIS_DELETE bs3_cone_ic;
    // bs3_ic->set_cur(nullptr, -1, FALSE);
    // ACIS_DELETE ic;

    return ret;
}

// 将螺旋线进行划分
// 若h为圆柱螺旋线则返回1，此时h1=h,h2=nullptr
// 若h为圆锥螺旋线，且h在一个圆锥上，则返回1，此时h1=h，h2=nullptr
// 若h为圆锥螺旋线，且h在两个圆锥上，则返回2，此时h1为h在圆锥c1上的部分螺旋线，h2为h在圆锥c2上的部分螺旋线
// 保证h1和h2的参数化与对应的cone一致(参数为0的点重合，并且参数方向相同)
int helix_split(helix const& h, helix*& h1, helix*& h2) {
    cone *c1, *c2;
    int count = cone_of_helix(h, c1, c2);
    if(count == 1) {
        h1 = ACIS_NEW helix(h);
        h2 = nullptr;
    } else {
        // @todo: test_point_tol函数未解耦：耗时过长暂不解耦
        SPAposition apex = c1->get_apex();
        if(!h.test_point_tol(apex, SPAresabs)) {
            // h不需要分裂为两个螺旋线
            h1 = ACIS_NEW helix(h);
            h2 = nullptr;
            count = 1;
        } else {
            // h需要分裂为两个螺旋线
            // 要求分裂后h1位于c1的局部坐标系内 h2位于c2的局部坐标系内(即：螺旋线的参数零点和参数增加方向和圆锥一致)
            h1 = ACIS_NEW helix(h);
            double range_max = std::max(fabs(h.param_range().start_pt()), fabs(h.param_range().end_pt()));
            h2 = ACIS_NEW helix(c2->base.centre, c2->base.normal, c2->base.major_axis, h.pitch(), h.handedness(), SPAinterval(-range_max, range_max), h.par_scaling(), h.taper());

            double param_apex1 = h1->param(apex);
            double param_apex2 = h2->param(apex);
            SPAinterval param_range1;
            SPAinterval param_range2;
            double st = h.param_range().start_pt(), ed = h.param_range().end_pt();

            if(param_apex1 > SPAresabs) {
                param_range1 = SPAinterval(st, param_apex1);
                param_range2 = SPAinterval(param_apex2, h2->param(h1->eval_position(ed)));
            } else {
                param_range1 = SPAinterval(param_apex1, ed);
                param_range2 = SPAinterval(h2->param(h.eval_position(st)), param_apex2);
            }

            // h1->limit(param_range1);
            // h2->limit(param_range2);
            h1->set_helix_range(param_range1);
            h2->set_helix_range(param_range2);
        }
    }
    ACIS_DELETE c1;
    ACIS_DELETE c2;
    return count;
}

/**
 * @brief 获得包围盒所在的平面
 * @param box 包围盒
 * @param num_planes 包围盒所在的平面数，若包围盒为有界包围盒，num_planes为6
 * @param planes 包围盒所在的平面(bounded)
 */
void planes_of_box(const SPAbox& box, int& num_planes, plane*& planes) {
    if(box.infinite() || box.empty()) {
        // 双边无界或空box 平面数为0
        num_planes = 0;
        planes = nullptr;
    } else {
        bool finite_corners[8] = {false};  // false: corner处无界; true: corner处有界
        // corner index:  4 * x + 2 * y + z
        // corner index的二进制由三位组成
        // 第0位代表z_range
        // 第1位代表y_range
        // 第2位代表x_range
        for(int i = 0; i < 8; ++i) {
            if((i & 1) == 0 && box.z_range().unbounded_below()) continue;
            if((i & 1) == 1 && box.z_range().unbounded_above()) continue;
            if((i >> 1 & 1) == 0 && box.y_range().unbounded_below()) continue;
            if((i >> 1 & 1) == 1 && box.y_range().unbounded_above()) continue;
            if((i >> 2 & 1) == 0 && box.x_range().unbounded_below()) continue;
            if((i >> 2 & 1) == 1 && box.x_range().unbounded_above()) continue;
            finite_corners[i] = true;
        }

        // 组成plane的四个corner点，点的旋转顺序与指向包围盒外的法向量方向满足右手定则
        const std::vector<std::vector<int>> plane_corners = {
          {0, 1, 3, 2},
          {0, 4, 5, 1},
          {4, 6, 7, 5},
          {2, 3, 7, 6},
          {1, 5, 7, 3},
          {0, 2, 6, 4}
        };
        // 表示相邻两个corner点方向向量
        const SPAunit_vector dirs[3] = {
          {0, 0, 1},
          {0, 1, 0},
          {1, 0, 0}
        };

        planes = ACIS_NEW plane[6];
        num_planes = 0;

        // plane的u方向参数范围和v方向参数范围
        SPAinterval u_range;
        SPAinterval v_range;
        for(int i = 0; i < 6; ++i) {
            for(int j = 0; j < 4; ++j) {
                // check corner是否合法
                if(finite_corners[plane_corners[i][j]]) {
                    int cur = plane_corners[i][j], pre = plane_corners[i][(j + 3) % 4], next = plane_corners[i][(j + 1) % 4];

                    auto u_dir = dirs[abs(cur - pre) >> 1];
                    if(cur > pre) u_dir = -u_dir;
                    auto v_dir = dirs[abs(cur - next) >> 1];
                    if(cur > next) v_dir = -v_dir;
                    auto root_point = std::move(box.corner(cur));

                    if(!finite_corners[pre]) {
                        u_range = SPAinterval(interval_type::interval_finite_below, 0, 0);
                    } else {
                        u_range = SPAinterval(interval_type::interval_finite, 0, distance_to_point(root_point, box.corner(pre)));
                    }
                    if(!finite_corners[next]) {
                        v_range = SPAinterval(interval_type::interval_finite_below, 0, 0);
                    } else {
                        v_range = SPAinterval(interval_type::interval_finite, 0, distance_to_point(root_point, box.corner(next)));
                    }

                    // check 平面是否合法
                    if((u_range.unbounded() || !u_range.empty()) && (v_range.unbounded() || !v_range.empty())) {
                        planes[num_planes] = plane(root_point, normalise(u_dir * v_dir));
                        planes[num_planes].u_deriv = u_dir;
                        planes[num_planes].reverse_v = FALSE;
                        planes[num_planes].limit(SPApar_box(u_range, v_range));
                        num_planes++;
                    }
                    break;
                }
            }
        }
    }
}

/**
 * @brief 获得矩形所在的线段
 * @param pln 矩形
 * @param num_lines 矩形所在的线段，若矩形为有界包围盒，num_planes为4
 * @param lines 矩形所在的线段(bounded)
 */
void lines_of_rect(const plane& pln, int& num_lines, straight*& lines) {
    num_lines = 0;
    lines = ACIS_NEW straight[4];
    SPAunit_vector dirs[] = {normalise(pln.u_deriv), normalise(pln.normal * pln.u_deriv)};
    if(pln.reverse_v) {
        dirs[1] = -dirs[1];
    }
    SPAinterval ranges[] = {pln.param_range_u(), pln.param_range_v()};
    int line_code[][5] = {
      {1, 1, 0},
      {1, 1, 1},
      {0, 0, 0},
      {0, 0, 1}
    };  // range_index, dir_index, ed_or_st
    for(int i = 0; i < 4; ++i) {
        int range_index = line_code[i][0];
        int dir_index = line_code[i][1];
        SPAinterval param_range = ranges[range_index];
        SPAinterval param_range_aux = ranges[1 - range_index];
        SPAunit_vector dir = dirs[dir_index];
        if(!param_range.infinite() || !param_range_aux.infinite()) {
            int ed_or_st = line_code[i][2];
            if((param_range_aux.unbounded_above() && ed_or_st) || (param_range_aux.unbounded_below() && !ed_or_st)) {
                // root_point为无限远的点
                continue;
            } else {
                if(param_range.finite() && fabs(param_range.length()) <= SPAresabs) {
                    // 直线退化为点
                    continue;
                }
                double tmp1 = ed_or_st ? param_range_aux.end_pt() : param_range_aux.start_pt();
                double tmp2;
                double u, v;
                if(param_range.unbounded_below()) {
                    tmp2 = param_range.end_pt();
                    param_range = SPAinterval(interval_type::interval_finite_above, 0);
                } else if(param_range.finite()) {
                    tmp2 = param_range.start_pt();
                    param_range -= tmp2;
                } else {
                    tmp2 = param_range.start_pt();
                    param_range = SPAinterval(interval_type::interval_finite_below, 0);
                }
                if(dir_index == 0) {
                    // u_dir
                    u = tmp2;
                    v = tmp1;
                } else {
                    // v_dir
                    u = tmp1;
                    v = tmp2;
                }
                SPAposition root_point(0, 0, 0);
                pln.eval(SPApar_pos(u, v), root_point);
                lines[num_lines] = straight(root_point, dir);
                lines[num_lines].limit(param_range);
                num_lines++;
            }
        }
    }
}

/**
 * @brief 获得直线在包围盒内的参数范围
 * @return 直线在包围盒内的参数范围，若不在包围盒内，返回nullptr
 * @param st 直线
 * @param box 包围盒
 * @param margin 误差
 */
SPAinterval* line_in_box(straight const& str, SPAbox const& _box, double margin) {
    SPAbox box = enlarge_box(_box, margin);
    // @todo: bound耗时过长暂不解耦
    if(str.bound(box).empty()) {
        // 直线不在box内
        return nullptr;
    } else {
        straight st(str.root_point, str.direction);  // 设置直线的参数范围为infinite
        st.param_scale = str.param_scale;
        // 直线在box内
        int num_planes = 0;
        plane* planes = nullptr;
        planes_of_box(box, num_planes, planes);
        double param[6] = {0.0};
        int num_param = 0;
        SPAinterval* ret = nullptr;
        curve_bounds cb(st);
        int i = 0;
        for(i = 0; i < num_planes; ++i) {
            // @todo: int_cur_sur函数未解耦:解耦在IntersectorStraightStraight.BoxCase14会出错
            curve_surf_int* cs_inters = int_cur_sur(st, planes[i], cb, SPAresabs * SPAresabs);  // @todo: 容差设置为0.0,重合判断出错；修改为1e-12可正常判断
            if(cs_inters) {
                // 直线与平面重合
                if(cs_inters->low_rel == curve_surf_rel::curve_dummy_coin || cs_inters->high_rel == curve_surf_rel::curve_dummy_coin) {
                    break;
                } else {  // 直线和平面相交
                    if(cs_inters->surf_param << planes[i].param_range()) {
                        // 交点在曲面上的参数在矩形内
                        param[num_param++] = cs_inters->param;
                    }
                }
                delete_curve_surf_ints(cs_inters);
            }
        }
        num_param = std::unique(param, param + num_param) - param;  // 去重，去除交于面交线的重复交点
        if(i != num_planes) {                                       // 直线与平面重合
            ret = line_in_rect(st, planes[i]);
        } else if(num_param == 2) {
            // 交于线段
            ret = ACIS_NEW SPAinterval(param[0], param[1]);
        } else if(num_param == 1) {
            // 交于射线
            if(st.eval_position(param[0] + SPAresfit) << box) {  // @todo: 容差设置
                ret = ACIS_NEW SPAinterval(interval_type::interval_finite_below, param[0], param[0]);
            } else if(st.eval_position(param[0] - SPAresfit) << box) {
                ret = ACIS_NEW SPAinterval(interval_type::interval_finite_above, param[0], param[0]);
            }
        }
        ACIS_DELETE[] planes;
        return ret;
    }
}

/**
 * @brief 获得直线在矩形内的参数范围
 * @return 直线在矩形内的参数范围
 * @param st 直线
 * @param pln plane类型的矩形，直线在pln平面内
 */
SPAinterval* line_in_rect(straight const& str, plane const& pln) {
    straight st(str.root_point, str.direction);  // 设置直线的参数范围为infinite
    SPAinterval* ret = nullptr;
    SPAinterval u_range = pln.param_range_u();
    SPAinterval v_range = pln.param_range_v();

    SPAposition start_pt, end_pt;
    curve_curve_int *end, *head;
    head = end = ZeroInter;
    logical coin = FALSE;  // st是否和rect的一条边重合
    int inter_num = 0;

    int num_lines = 0;
    straight* param_lines = nullptr;
    lines_of_rect(pln, num_lines, param_lines);

    for(int i = 0; i < num_lines; ++i) {
        if(biparallel(st.direction, param_lines[i].direction) && biparallel(st.root_point - param_lines[i].root_point, st.direction)) {
            // 两个直线重合
            if(param_lines[i].param_range().finite()) {
                // 重合边 有限长
                // start_pt = param_lines[i].root_point;
                // end_pt = start_pt + param_lines[i].direction * param_lines[i].param_range().end_pt();
                start_pt = param_lines[i].eval_position(param_lines[i].param_range().start_pt());
                end_pt = param_lines[i].eval_position(param_lines[i].param_range().end_pt());
                ret = ACIS_NEW SPAinterval(st.param(start_pt), st.param(end_pt));
            } else {
                // 重合边 无限长 构造交点结果
                if(param_lines[i].param_range().infinite()) {
                    ret = ACIS_NEW SPAinterval(interval_infinite);
                } else {
                    if(param_lines[i].param_range().unbounded_below()) {
                        end_pt = param_lines[i].eval_position(param_lines[i].param_range().end_pt());
                        ret = ACIS_NEW SPAinterval(interval_finite_above, st.param(end_pt));
                    } else {
                        start_pt = param_lines[i].eval_position(param_lines[i].param_range().start_pt());
                        ret = ACIS_NEW SPAinterval(interval_finite_below, st.param(start_pt));
                    }
                    if(antiparallel(st.direction, param_lines[i].direction)) {
                        // 直线st与param_lines方向相反
                        if(ret->type() == interval_finite_above) {
                            *ret = SPAinterval(interval_type::interval_finite_below, ret->end_pt());
                        } else {
                            *ret = SPAinterval(interval_type::interval_finite_above, ret->start_pt());
                        }
                    }
                }
            }
            coin = TRUE;
            break;
        } else {
            // 两个直线相交
            curve_curve_int* tmp = int_cur_cur(st, param_lines[i], *static_cast<SPAbox*>(nullptr), 1e-12);
            // 添加容差，避免容差内交点 @todo: 合适的容差
            if(tmp && tmp->param2 << param_lines[i].param_range()) {
                end->next = tmp;
                end = end->next;
                inter_num++;
            } else {
                delete_curve_curve_ints(tmp);
            }
        }
    }
    if(coin) {
        delete_curve_curve_ints(head);
    } else {
        inter_num = CurvCurvIntPointReduce(head->next);
        if(inter_num == 2) {
            // 若矩形是有界的，将返回两个交点
            ret = ACIS_NEW SPAinterval(head->next->param1, head->next->next->param1);
        } else if(inter_num == 1) {
            double param = head->next->param1;
            if(pln.param(st.eval_position(param + 1e-3)) << pln.param_range()) {
                // [param, inf]
                ret = ACIS_NEW SPAinterval(interval_type::interval_finite_below, param);
            } else {
                // [-inf, param]
                ret = ACIS_NEW SPAinterval(interval_type::interval_finite_above, param);
            }
        }
        delete_curve_curve_ints(head);
    }
    ACIS_DELETE[] param_lines;
    return ret;
}

/**
 * @brief 删除包围盒外的交点
 * @return 筛选后的交点结果
 * @param inters 待筛选的交点结果
 * @param box 包围盒
 */
curve_curve_int* points_in_box(curve_curve_int* inters, SPAbox const& box) {
    if(&box) {
        curve_curve_int *head, *end;
        head = end = ZeroInter;
        curve_curve_int* tmp = nullptr;
        while(inters) {
            if(inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin) {
                end->next = inters;
                end = end->next;
                inters = inters->next;  // 该接口不处理重合情况
            } else {
                if(inters->int_point << box) {
                    end->next = inters;
                    end = end->next;
                    inters = inters->next;
                } else {
                    tmp = inters->next;
                    ACIS_DELETE inters;
                    inters = tmp;
                }
            }
        }
        end->next = nullptr;
        inters = head->next;
        ACIS_DELETE head;
    }
    return inters;
}

/**
 * @brief 判断curve是否为周期曲线 不考虑subset
 * @return true: curve为周期曲线; false:curve为非周期曲线
 * @param c 输入曲线
 */
bool curve_periodic(curve const& c) {
    bool periodic = false;
    if(&c) {
        if(c.type() == ellipse_type) {
            periodic = true;
        } else if(c.type() == intcurve_type) {
            intcurve const* ic = static_cast<intcurve const*>(&c);
            periodic = bs3_curve_periodic(ic->cur());
        }
    }
    return periodic;
}

/**
 * @brief 判断curve是否为闭合曲线 不考虑subset
 * @return true: curve为闭合曲线; false:curve为非闭合曲线
 * @param c 输入曲线
 */
bool curve_closed(curve const& c) {
    bool closed = false;
    if(&c) {
        if(c.type() == ellipse_type) {
            closed = true;
        } else if(c.type() == intcurve_type) {
            intcurve const* ic = static_cast<intcurve const*>(&c);
            closed = bs3_curve_closed(ic->cur());
        }
    }
    return closed;
}

/**
 * @brief 判断curve是否为开曲线 不考虑subset
 * @return true: curve为开曲线; false: curve为非开曲线
 * @param c 输入曲线
 */
bool curve_open(curve const& c) {
    return !curve_periodic(c) && !curve_closed(c);
}

/**
 * @brief 返回curve的周期 不考虑subset
 * @return 0: curve为非周期曲线 >0: curve为周期曲线，返回curve的周期
 * @param c 输入曲线
 */
double curve_period(curve const& c) {
    double period = 0.0;
    if(&c) {
        if(c.type() == ellipse_type) {
            period = 2 * M_PI;
        } else if(c.type() == intcurve_type) {
            intcurve const* ic = static_cast<intcurve const*>(&c);
            period = bs3_curve_period(ic->cur());
        }
    }
    return period;
}

/**
 * @brief 返回curve的主参数周期 不考虑subset
 * @return 空区间: curve为开曲线 区间长度不为0: curve为周期曲线或闭曲线，返回curve的主参数周期
 * @param c 输入曲线
 */
SPAinterval curve_major_interval(curve const& c) {
    SPAinterval ans;
    if(&c) {
        if(c.type() == ellipse_type) {
            ans = SPAinterval(-M_PI, M_PI);
        } else if(c.type() == intcurve_type) {
            intcurve const* ic = dynamic_cast<intcurve const*>(&c);
            bs3_curve bs3 = ic->cur();
            if(bs3_curve_closed(bs3) || bs3_curve_periodic(bs3)) {  // 支持闭曲线参数范围
                ans = bs3_curve_range(bs3);
                if(ic->reversed()) {
                    ans = -ans;
                }
            }
        }
    }
    return ans;
}

/**
 * @brief 获得curve在param处的点在range内的有效参数
 * @return 若找到返回true，未找到返回false
 * @param c 输入曲线
 * @param param 输入参数
 * @param range 给定参数区间
 */
bool find_valid_param(curve const& c, double& param, SPAinterval const& range) {
    if(&c == nullptr) return false;
    if(param << range) return true;
    bool found = false;
    if(curve_periodic(c)) {
        // 优先判断周期，因为周期曲线一定是闭合曲线
        double period = curve_period(c);
        double tmp = param_change_interval(param, range, period);
        if(tmp << range) {
            param = tmp, found = true;
        }
    } else if(curve_closed(c)) {
        SPAinterval range;
        if(c.type() == ellipse_type) {
            range = SPAinterval(-M_PI, M_PI);
        } else if(c.type() == intcurve_type) {
            intcurve const* ic = static_cast<intcurve const*>(&c);
            range = bs3_curve_range(ic->cur());
            if(ic->reversed()) {
                range = -range;
            }
        }
        if(is_equal(param, range.start_pt())) {
            param = range.end_pt(), found = true;
        } else if(is_equal(param, range.end_pt())) {
            param = range.start_pt(), found = true;
        }
    }
    return found;
}

/**
 * @brief 删除curve_curve_int存储的交点中(不考虑重合交点)不在cur1和cur2参数范围内的交点
 * @return 删除后的curve_curve_int交点结果
 * @param inters 待删除的curve_curve_int交点结果
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param need_compute_param 是否需要重新计算curve_curve_int的param1和param2
 */
curve_curve_int* filter_normal_inters(curve_curve_int* inters, curve const& cur1, curve const& cur2, bool need_compute_param) {
    curve_curve_int *head, *end;
    head = end = ZeroInter;
    while(inters) {
        if(inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin) {
            // 不处理重合段
            end->next = inters;
            end = end->next;
        } else {
            if(need_compute_param) {
                inters->param1 = cur1.param(inters->int_point);
                inters->param2 = cur2.param(inters->int_point);
                if(cur1.type() == ellipse_type) {
                    inters->param1 = refine_param(inters->param1, SPAresabs);
                }
                if(cur2.type() == ellipse_type) {
                    inters->param2 = refine_param(inters->param2, SPAresabs);
                }
            }
            find_valid_param(cur1, inters->param1, cur1.param_range());
            // @todo: 未解耦08.29
            find_valid_param(cur2, inters->param2, cur2.param_range());
            // @todo: 未解耦08.29
            if(inters->param1 << cur1.param_range() && inters->param2 << cur2.param_range()) {
                end->next = inters;
                end = end->next;
            } else {
                curve_curve_int* next = inters->next;
                ACIS_DELETE inters;
                inters = next;
                continue;
            }
        }
        inters = inters->next;
    }
    end->next = nullptr;
    inters = head->next;
    ACIS_DELETE head;
    return inters;
}

/**
 * @brief 处理求交结果inters，不处理重合段，删除param1在range1外或param2在range2外的交点
 * @return 筛选后的交点结果
 * @param inters 输入交点结果
 * @param range1 param1要求的参数范围
 * @param range2 param2要求的参数范围
 */
curve_curve_int* filter_normal_inters(curve_curve_int* inters, std::vector<SPAinterval>* range1, std::vector<SPAinterval>* range2) {
    curve_curve_int *head, *end;
    head = end = ZeroInter;
    while(inters) {
        if(inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin) {
            // 不处理重合段
            end->next = inters;
            end = end->next;
        } else {
            bool param1_in_range1 = range1 == nullptr;
            if(range1) {
                param1_in_range1 = !range1->empty();
                for(auto const& range: *range1) {
                    if(!(inters->param1 << range)) {
                        param1_in_range1 = false;
                        break;
                    }
                }
            }
            bool param2_in_range2 = range2 == nullptr;
            if(range2) {
                param2_in_range2 = !range2->empty();
                for(auto const& range: *range2) {
                    if(!(inters->param2 << range)) {
                        param2_in_range2 = false;
                        break;
                    }
                }
            }
            if(param1_in_range1 && param2_in_range2) {
                end->next = inters;
                end = end->next;
            } else {
                curve_curve_int* next = inters->next;
                ACIS_DELETE inters;
                inters = next;
                continue;
            }
        }
        inters = inters->next;
    }
    end->next = nullptr;
    inters = head->next;
    ACIS_DELETE head;
    return inters;
}

/**
 * @brief 筛选coin_int1和coin_int2所表示的重合区间，将其调整到param_range1和param_range2内
 */
curve_curve_int* filter_coins(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_ints1, std::vector<SPAinterval> const& coin_ints2, SPAinterval const& param_range1, SPAinterval const& param_range2) {
    // 要求输入curve没有参数限制
    curve_curve_int* coins = nullptr;

    double period1 = curve_period(cur1);
    SPAinterval const& major_interval1 = curve_major_interval(cur1);
    double period2 = curve_period(cur2);
    SPAinterval const& major_interval2 = curve_major_interval(cur2);

    std::vector<SPAinterval> range1_on_major = shift_interval_to_major(param_range1, period1, major_interval1);
    std::vector<SPAinterval> range2_on_major = shift_interval_to_major(param_range2, period2, major_interval2);

    if(curve_closed(cur1)) {
        int size_range1_on_major = range1_on_major.size();
        for(int i = 0; i < size_range1_on_major; ++i) {
            if(major_interval1.start_pt() << range1_on_major[i] && !(major_interval1.end_pt() << range1_on_major[i])) {
                range1_on_major.push_back(SPAinterval(major_interval1.end_pt()));
            }
            if(major_interval1.end_pt() << range1_on_major[i] && !(major_interval1.start_pt() << range1_on_major[i])) {
                range1_on_major.push_back(SPAinterval(major_interval1.start_pt()));
            }
        }
    }

    if(curve_closed(cur2)) {
        int size_range2_on_major = range2_on_major.size();
        for(int i = 0; i < size_range2_on_major; ++i) {
            if(major_interval2.start_pt() << range2_on_major[i] && !(major_interval2.end_pt() << range2_on_major[i])) {
                range2_on_major.push_back(SPAinterval(major_interval2.end_pt()));
            }
            if(major_interval2.end_pt() << range2_on_major[i] && !(major_interval2.start_pt() << range2_on_major[i])) {
                range2_on_major.push_back(SPAinterval(major_interval2.start_pt()));
            }
        }
    }

    for(auto const& range1: range1_on_major) {
        for(auto const& range2: range2_on_major) {
            for(int i = 0; i < coin_ints1.size(); ++i) {
                SPAinterval overlap1 = coin_ints1[i] & range1;
                SPAinterval overlap2 = coin_ints2[i] & range2;
                SPAinterval overlap2_on_ell = recompute_param_range(overlap2, &cur2, &cur1, SPAresabs);

                overlap1 &= overlap2_on_ell;
                if(!overlap1.empty()) {
                    bool fully_coin1 = fabs(overlap1.length() - major_interval1.length()) <= SPAresabs && fabs(param_range1.length() - major_interval1.length()) <= SPAresabs;
                    bool fully_coin2 = fabs(overlap2.length() - major_interval2.length()) <= SPAresabs && fabs(param_range2.length() - major_interval2.length()) <= SPAresabs;
                    bool reversed = false;
                    if(fully_coin1 && fully_coin2) {
                        overlap1 = param_range1;
                    }
                    overlap2 = recompute_param_range(overlap1, &cur1, &cur2, SPAresabs, reversed);

                    overlap1 = param_change_interval(overlap1, param_range1, period1, false);
                    overlap2 = param_change_interval(overlap2, param_range2, period2, reversed);
                    if(overlap1.length() <= SPAresabs && !(overlap1 << param_range1)) {
                        double overlap1_mid = overlap1.mid_pt();
                        find_valid_param(cur1, overlap1_mid, param_range1);
                        overlap1 = SPAinterval(overlap1_mid);
                    }
                    if(overlap2.length() <= SPAresabs && !(overlap2 << param_range2)) {
                        double overlap2_mid = overlap2.mid_pt();
                        find_valid_param(cur2, overlap2_mid, param_range2);
                        overlap2 = SPAinterval(overlap2_mid);
                    }

                    std::pair<double, double> overlap2_pair = !reversed ? std::make_pair(overlap2.start_pt(), overlap2.end_pt()) : std::make_pair(overlap2.end_pt(), overlap2.start_pt());
                    auto coins_cur = construct_coin_inters(cur1, cur2, {overlap1}, {overlap2_pair});
                    coins = connect_curve_curve_int(coins, coins_cur);
                }
            }
        }
    }

    CurvCurvIntPointReduce(coins);

    if(curve_periodic(cur1) && curve_periodic(cur2)) {
        // 合并区间
        for(auto coins_tmp = coins; coins_tmp; coins_tmp = coins_tmp->next) {
            if(coins_tmp->next && coins_tmp->next->next && fabs(coins_tmp->next->param1 - coins_tmp->next->next->param1) <= SPAresabs) {
                auto next = coins_tmp->next->next->next;
                ACIS_DELETE coins_tmp->next->next;
                ACIS_DELETE coins_tmp->next;
                coins_tmp->next = next;
            }
        }
    }

    return coins;
}

/**
 * @brief 筛选coin_int1和coin_int2所表示的重合区间，将其调整到param_range1和param_range2内
 */
curve_curve_int* filter_coins_ellipse_ellipse(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_ints1, std::vector<SPAinterval> const& coin_ints2, SPAinterval const& param_range1, SPAinterval const& param_range2) {
    // 要求输入curve没有参数限制
    curve_curve_int* coins = nullptr;

    double period1 = curve_period(cur1);
    SPAinterval major_interval1 = curve_major_interval(cur1);
    double period2 = curve_period(cur2);
    SPAinterval major_interval2 = curve_major_interval(cur2);

    std::vector<SPAinterval> range1_on_major = shift_interval_to_major(param_range1, period1, major_interval1);
    std::vector<SPAinterval> range2_on_major = shift_interval_to_major(param_range2, period2, major_interval2);

    if(curve_closed(cur1)) {
        int size_range1_on_major = range1_on_major.size();
        for(int i = 0; i < size_range1_on_major; ++i) {
            if(major_interval1.start_pt() << range1_on_major[i] && !(major_interval1.end_pt() << range1_on_major[i])) {
                range1_on_major.push_back(SPAinterval(major_interval1.end_pt()));
            }
            if(major_interval1.end_pt() << range1_on_major[i] && !(major_interval1.start_pt() << range1_on_major[i])) {
                range1_on_major.push_back(SPAinterval(major_interval1.start_pt()));
            }
        }
    }

    if(curve_closed(cur2)) {
        int size_range2_on_major = range2_on_major.size();
        for(int i = 0; i < size_range2_on_major; ++i) {
            if(major_interval2.start_pt() << range2_on_major[i] && !(major_interval2.end_pt() << range2_on_major[i])) {
                range2_on_major.push_back(SPAinterval(major_interval2.end_pt()));
            }
            if(major_interval2.end_pt() << range2_on_major[i] && !(major_interval2.start_pt() << range2_on_major[i])) {
                range2_on_major.push_back(SPAinterval(major_interval2.start_pt()));
            }
        }
    }

    SPAinterval overlap1_1, overlap1_2;
    for(auto const& range1: range1_on_major) {
        for(auto const& range2: range2_on_major) {
            for(int i = 0; i < coin_ints1.size(); ++i) {
                SPAinterval overlap1 = coin_ints1[i] & range1;
                SPAinterval overlap2 = coin_ints2[i] & range2;
                SPAinterval overlap2_on_ell = recompute_param_range(overlap2, &cur2, &cur1, SPAresabs);

                overlap1_1 = overlap1, overlap1_2 = overlap1;
                std::vector<SPAinterval> overlap2_on_ell_on_major = shift_interval_to_major(overlap2_on_ell, period1, major_interval1);
                overlap1_1 &= overlap2_on_ell_on_major[0];

                if(!overlap1_1.empty()) {
                    bool fully_coin1 = fabs(overlap1_1.length() - major_interval1.length()) <= SPAresabs && fabs(param_range1.length() - major_interval1.length()) <= SPAresabs;
                    bool fully_coin2 = fabs(overlap2.length() - major_interval2.length()) <= SPAresabs && fabs(param_range2.length() - major_interval2.length()) <= SPAresabs;
                    bool reversed = false;
                    if(fully_coin1 && fully_coin2) {
                        overlap1_1 = param_range1;
                    }
                    overlap2 = recompute_param_range(overlap1_1, &cur1, &cur2, SPAresabs, reversed);

                    overlap1_1 = param_change_interval(overlap1_1, param_range1, period1, false);
                    overlap2 = param_change_interval(overlap2, param_range2, period2, reversed);
                    if(overlap1_1.length() <= SPAresabs && !(overlap1_1 << param_range1)) {
                        double overlap1_mid = overlap1_1.mid_pt();
                        find_valid_param(cur1, overlap1_mid, param_range1);
                        overlap1_1 = SPAinterval(overlap1_mid);
                    }
                    if(overlap2.length() <= SPAresabs && !(overlap2 << param_range2)) {
                        double overlap2_mid = overlap2.mid_pt();
                        find_valid_param(cur2, overlap2_mid, param_range2);
                        overlap2 = SPAinterval(overlap2_mid);
                    }

                    std::pair<double, double> overlap2_pair = !reversed ? std::make_pair(overlap2.start_pt(), overlap2.end_pt()) : std::make_pair(overlap2.end_pt(), overlap2.start_pt());
                    auto coins_cur = construct_coin_inters(cur1, cur2, {overlap1_1}, {overlap2_pair});
                    coins = connect_curve_curve_int(coins, coins_cur);
                }
                if(overlap2_on_ell_on_major.size() == 2) {
                    overlap1_2 &= overlap2_on_ell_on_major[1];
                    if(!overlap1_2.empty()) {
                        bool fully_coin1 = fabs(overlap1_2.length() - major_interval1.length()) <= SPAresabs && fabs(param_range1.length() - major_interval1.length()) <= SPAresabs;
                        bool fully_coin2 = fabs(overlap2.length() - major_interval2.length()) <= SPAresabs && fabs(param_range2.length() - major_interval2.length()) <= SPAresabs;
                        bool reversed = false;
                        if(fully_coin1 && fully_coin2) {
                            overlap1_2 = param_range1;
                        }
                        overlap2 = recompute_param_range(overlap1_2, &cur1, &cur2, SPAresabs, reversed);

                        overlap1_2 = param_change_interval(overlap1_2, param_range1, period1, false);
                        overlap2 = param_change_interval(overlap2, param_range2, period2, reversed);
                        if(overlap1_2.length() <= SPAresabs && !(overlap1_2 << param_range1)) {
                            double overlap1_mid = overlap1_2.mid_pt();
                            find_valid_param(cur1, overlap1_mid, param_range1);
                            overlap1_2 = SPAinterval(overlap1_mid);
                        }
                        if(overlap2.length() <= SPAresabs && !(overlap2 << param_range2)) {
                            double overlap2_mid = overlap2.mid_pt();
                            find_valid_param(cur2, overlap2_mid, param_range2);
                            overlap2 = SPAinterval(overlap2_mid);
                        }

                        std::pair<double, double> overlap2_pair = !reversed ? std::make_pair(overlap2.start_pt(), overlap2.end_pt()) : std::make_pair(overlap2.end_pt(), overlap2.start_pt());
                        auto coins_cur = construct_coin_inters(cur1, cur2, {overlap1_2}, {overlap2_pair});
                        coins = connect_curve_curve_int(coins, coins_cur);
                    }
                }
            }
        }
    }

    CurvCurvIntPointReduce(coins);

    if(curve_periodic(cur1) && curve_periodic(cur2)) {
        // 合并区间
        for(auto coins_tmp = coins; coins_tmp; coins_tmp = coins_tmp->next) {
            if(coins_tmp->next && coins_tmp->next->next && fabs(coins_tmp->next->param1 - coins_tmp->next->next->param1) <= SPAresabs) {
                auto next = coins_tmp->next->next->next;
                ACIS_DELETE coins_tmp->next->next;
                ACIS_DELETE coins_tmp->next;
                coins_tmp->next = next;
            }
        }
    }

    return coins;
}

/**
 * @brief 判断点pos是否在box的一条边上
 */
logical point_on_box_side(SPAposition const pos, SPAbox const& box) {
    logical ans = FALSE;
    if(&box && pos << box) {
        int num_planes = 0;
        plane* planes = nullptr;
        planes_of_box(box, num_planes, planes);
        for(int i = 0; i < num_planes; ++i) {
            int num_lines = 0;
            straight* lines = nullptr;
            lines_of_rect(planes[i], num_lines, lines);
            for(int j = 0; j < num_lines; ++j) {
                // @todo: test_point_tol函数未解耦：耗时过长暂不解耦
                if(lines[j].test_point_tol(pos) && lines[j].param(pos) << lines[j].param_range()) {  // 待解耦，存在问题 @todo: straight相关问题
                    ans = TRUE;
                    break;
                }
            }
            ACIS_DELETE[] lines;
            if(ans) {
                break;
            }
        }
        ACIS_DELETE[] planes;
    }
    return ans;
}

/**
 * 将多个重合段 合并起来，返回合并后的段数(要求各段按照param1有序)
 */
int merge_coin_inters(std::vector<std::pair<curve_curve_int*, curve_curve_int*>>& inters_list, double tol) {
    int i, j;
    int num_segs = inters_list.size();
    for(i = 0; i < inters_list.size(); ++i) {
        if(inters_list[i].first == nullptr || inters_list[i].second == nullptr) {
            continue;
        }
        double s1 = inters_list[i].first->param1, e1 = inters_list[i].second->param1;
        for(j = i + 1; j < inters_list.size(); ++j) {
            double s2 = inters_list[j].first->param1, e2 = inters_list[j].second->param1;
            if(e2 - e1 <= tol) {  // e2 <= e1
                ACIS_DELETE inters_list[j].first;
                ACIS_DELETE inters_list[j].second;
                inters_list[j].first = inters_list[j].second = nullptr;
                num_segs--;
            } else if(s2 - e1 > tol) {  // s2 > e1
                break;
            } else {  // 合并 第i段和第j段
                ACIS_DELETE inters_list[i].second;
                ACIS_DELETE inters_list[j].first;
                inters_list[i].second = inters_list[j].second;
                inters_list[j].first = inters_list[j].second = nullptr;
                e1 = inters_list[i].second->param1;
                num_segs--;
            }
        }
    }
    return num_segs;
};

SPAposition mid_point(SPAposition const& p1, SPAposition const& p2) {
    SPAposition ret;  // 中点
    // 计算中点的每个坐标值
    ret.x() = (p1.x() + p2.x()) / 2;
    ret.y() = (p1.y() + p2.y()) / 2;
    ret.z() = (p1.z() + p2.z()) / 2;
    return ret;  // 返回中点
}

/**
 * @brief 返回点point在直线(起点为root_point，方向为direction)上的投影点
 */
SPAposition PointProjectToLine(const SPAposition& point, const SPAposition& root_point, SPAunit_vector direction) {
    return root_point + direction * ((point - root_point) % direction);
}

/**
 * @brief 得到两条异面直线距离最近的两点
 * @param line1 直线1
 * @param line2 直线2
 * @param comp1 line1上，距离line2距离最近的点
 * @param comp2 line2上，距离line1距离最近的点
 */
void LineLineNearInters(straight line1, straight line2, SPAposition& comp1, SPAposition& comp2) {
    plane pln;

    // 构造过line2的一个特定平面
    SPAvector cv12 = line1.direction * line2.direction;
    pln.normal = normalise(cv12 * line2.direction);
    pln.root_point = line2.root_point;

    double param = NAN;  // 线面求交 交点在直线上的参数值

    // line1和过line2平面求交 得到的交点为comp1
    intersect_line_plane(line1.root_point, line1.direction, pln.root_point, pln.normal, param, comp1);

    // 构造过line1的一个特定平面
    pln.normal = normalise(cv12 * line1.direction);
    pln.root_point = line1.root_point;

    // line2和过line1平面求交 得到的交点为comp2
    intersect_line_plane(line2.root_point, line2.direction, pln.root_point, pln.normal, param, comp2);
}

/**
 * @brief 封装MAF方法，对近似交点结果near_result迭代求精(GEMS版本)
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param near_result 近似交点结果
 * @param refined_result 求精后的交点结果
 * @param total_iter_num 最大迭代次数
 */
void maf(curve const& cur1, curve const& cur2, curve_curve_int* near_result, curve_curve_int*& refined_result, int total_iter_num) {
    // 用MAF方法求精确交点
    int inter_num = 0;                          // inter_num 精确交点个数
    curve_curve_int *inters_end, *inters_head;  // inters_end 返回交点链表尾节点,inters_head 返回交点链表头节点
    inters_head = inters_end = ZeroInter;       // 链表inters头结点占位
    curve_curve_int* tmp = nullptr;

    double dt1 = NAN, dt2 = NAN;  // MAF迭代过程中两个曲线的参数增量
    SPAvector cv1, cv2;           // cv1是cur1在近似交点处的的切线方向；cv2是cur2在近似交点处的的切线方向
    SPAposition cp1, cp2, comp1, comp2;
    // cp1在cur1上的近似交点，cp2在cur2上的近似交点

    // comp1  comp2 为MAF迭代过程中cur1和cur2在cp1和cp2处切线上的近似交点
    // 见函数LineLineNearInters()

    straight line1, line2;                                           // cur1上近似交点处的切线，cur2上近似交点处的切线
    inter_num = 0;                                                   // 精确交点个数
    SPAinterval param_range_cur1(interval_type::interval_infinite);  // cur1的参数范围
    SPAinterval param_range_cur2(interval_type::interval_infinite);  // cur2的参数范围
    if(cur1.type() == intcurve_type) {                               // intcurve
        param_range_cur1 = bs3_curve_range(((intcurve*)&cur1)->cur());
    }
    if(cur2.type() == intcurve_type) {  // intcurve
        param_range_cur2 = bs3_curve_range(((intcurve*)&cur2)->cur());
    }

    int debug = 0;
    std::cout << std::fixed << std::setprecision(16);
    if(debug) {
        std::cout << "param_range1: ";
        param_range_cur1.debug(stdout);
        std::cout << "\nparam_range2: ";
        param_range_cur2.debug(stdout);
        std::cout << std::endl;
    }
    while(near_result) {
        int iter_num = 0;  // MAF算法迭代次数
        while(iter_num < total_iter_num) {
            // 判断param与曲线参数范围的大小关系
            if(near_result->param1 > param_range_cur1) near_result->param1 = param_range_cur1.end_pt();
            if(near_result->param1 < param_range_cur1) near_result->param1 = param_range_cur1.start_pt();
            if(near_result->param2 > param_range_cur2) near_result->param2 = param_range_cur2.end_pt();
            if(near_result->param2 < param_range_cur2) near_result->param2 = param_range_cur2.start_pt();

            cp1 = cur1.eval_position(near_result->param1);
            cp2 = cur2.eval_position(near_result->param2);
            // cp1在cur1上的近似交点，cp2在cur2上的近似交点
            cv1 = cur1.eval_deriv(near_result->param1);
            cv2 = cur2.eval_deriv(near_result->param2);

            if(debug) {
                std::cout << "当前迭代数: " << iter_num;
                std::cout << "\ncp1: ";
                std::cout << cp1.x() << "," << cp1.y() << "," << cp1.z();
                std::cout << "\ncp2: ";
                std::cout << cp2.x() << "," << cp2.y() << "," << cp2.z();
                std::cout << "\ncv1: ";
                std::cout << cv1.x() << "," << cv1.y() << "," << cv1.z();
                std::cout << "\ncv2: ";
                std::cout << cv2.x() << "," << cv2.y() << "," << cv2.z();
                std::cout << "\nparam1: " << near_result->param1 << std::endl;
                std::cout << "param2: " << near_result->param2 << std::endl;
            }

            if(debug) {
                std::cout << "当前交点距离: " << distance_to_point(cp1, cp2) << std::endl;
                std::cout << "是否距离小于1e-6: " << (fabs(distance_to_point(cp1, cp2)) <= SPAresabs) << std::endl;
            }
            // cv1是cur1在近似交点处的的切线方向；cv2是cur2在近似交点处的的切线方向
            if(distance_to_point(cp1, cp2) < SPAresabs) {  // 达到精度要求
                break;
            }
            line1.root_point = cp1;
            line1.direction = normalise(cv1);
            line2.root_point = cp2;
            line2.direction = normalise(cv2);
            // 构造cur1在cp1处,cur2在cp2处的两条切线

            if(cur1.type() == intcurve_type && cur2.type() == intcurve_type) {
                // bspline-bspline
                // 两直线近似平行的时候导致迭代结果不准确，用两曲线的投影点
                // 的中点在直线上的投影再作迭代可以部分解决这个问题，但收敛速度较慢，要增大迭代次
                // 数，目前尚无好的方法解决这个问题
                tmp = nullptr;
                API_BEGIN
                tmp = int_cur_cur(line1, line2);
                API_END
                if(tmp) {
                    SPAposition intpoint = mid_point(line1.root_point, line2.root_point);
                    comp1 = PointProjectToLine(intpoint, line1.root_point, line1.direction);
                    comp2 = PointProjectToLine(intpoint, line2.root_point, line2.direction);
                } else {
                    LineLineNearInters(line1, line2, comp1, comp2);
                }
            } else {
                // eg. circle-nurbs
                LineLineNearInters(line1, line2, comp1, comp2);
            }

            // comp1和comp2为分别为line1和line2上一对最近的点

            dt1 = line1.param(comp1) / cv1.len();
            dt2 = line2.param(comp2) / cv2.len();

            if(debug) {
                std::cout << "dt1: " << dt1 << std::endl;
                std::cout << "dt2: " << dt2 << std::endl;
            }

            near_result->param1 += dt1;
            near_result->param2 += dt2;
            // 在切线方向上改变参数值，使得两个近似交点距离更近
            iter_num++;
        }
        if(iter_num < total_iter_num) {
            if(debug) {
                std::cout << "\n\n最后结果: ";
                std::cout << "param1: " << near_result->param1 << std::endl;
                std::cout << "param2: " << near_result->param2 << std::endl;
                std::cout << "cp: ";
                std::cout << near_result->int_point.x() << "," << near_result->int_point.y() << "," << near_result->int_point.z();
                std::cout << std::endl << std::endl;
            }

            near_result->int_point = mid_point(cp1, cp2);  // 求中点

            if(biparallel(cv1, cv2)) {
                near_result->low_rel = near_result->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                near_result->low_rel = near_result->high_rel = curve_curve_rel::cur_cur_normal;
            }
            // 判断两曲线在近似切点处的切线是否平行
            // 注：需要进一步研究在近似相切情况下，MAF算法是否适用
            inters_end->next = near_result;
            inters_end = inters_end->next;
            inter_num++;
            near_result = near_result->next;
        } else {
            // 销毁 迭代失败的交点结果
            tmp = near_result->next;
            ACIS_DELETE near_result;
            near_result = tmp;
        }
    }
    inters_end->next = nullptr;
    // 交点去重
    if(inter_num != 0) {
        inter_num = CurvCurvIntPointReduce(inters_head->next);
    }
    refined_result = inters_head->next;
    ACIS_DELETE inters_head;
}

/**
 * @brief 构造曲线在给定点处的曲率圆
 * @param cur 线
 * @param param 参数
 * @param ell 圆
 * @param max_lg 返回构造圆时的最大数值差距
 */
logical construct_curvature_circle(curve const& cur, double param, ellipse& ell, double& max_lg) {
    logical success = FALSE;
    SPAvector dv, ddv, curvature;
    SPAposition pos;
    cur.eval(param, pos, dv, ddv);
    max_lg = 0.0;
    double num = pow(dv.len(), 3);
    double temp = fabs(dv.len_sq() * ddv.len_sq() - pow(dv % ddv, 2));
    double den = sqrt(temp);
    if(fabs(den) >= fabs(num) * 1e-14) {
        double curvature_radius = num / den;

        SPAunit_vector tangent = normalise(dv);
        if(is_zero(tangent)) tangent = SPAunit_vector(0, 0, 0);  // 添加向量判0，减少容差带来的负面效果
        SPAunit_vector binormal = normalise(dv * ddv);
        if(is_zero(binormal)) binormal = SPAunit_vector(0, 0, 0);  // 添加向量判0，减少容差带来的负面效果
        SPAunit_vector normal = normalise(binormal * tangent);
        if(is_zero(normal)) normal = SPAunit_vector(0, 0, 0);  // 添加向量判0，减少容差带来的负面效果
        curvature = normal * curvature_radius;

        for(int i = 0; i < 3; ++i) {
            if(pos.coordinate(i) != 0 && curvature.component(i) != 0) {
                double lg_p = log10(abs(pos.coordinate(i)));
                double lg_c = log10(abs(curvature.component(i)));
                max_lg = std::max(max_lg, abs(lg_p - lg_c));
            }
        }

        ell.centre = pos + curvature;  // @todo: 此处会出现数值误差
        ell.major_axis = -curvature;
        ell.normal = normalise(ell.major_axis * tangent);
        ell.radius_ratio = 1.0;
        success = TRUE;
    } else {
        max_lg = 20.0;  // 当曲率圆半径很大时，max_lg设置为20
    }
    return success;
}

logical straight_coef(straight const& st, double& A, double& B, double& C) {
    if(is_zero(st.direction.z()) && is_zero(st.root_point.z())) {
        A = st.direction.y();
        B = -st.direction.x();
        SPAvector normal(A, B, 0);
        C = -normal % st.root_point;
        return TRUE;
    } else {
        return FALSE;
    }
}
// Bezier曲线高度估计
double SPL_BezcHeightEstimate(bs3_curve bs3) {
    if(!bs3 || bs3_curve_periodic(bs3) || bs3_curve_closed(bs3)) {
        return DBL_MAX;  // 周期曲线不计算直线度
    }
    int num_ctrlpts = 0;
    SPAposition* ctrls = nullptr;
    bs3_curve_control_points(bs3, num_ctrlpts, ctrls);
    double maxdist = 0.0;
    SPAposition line_root = ctrls[0];
    SPAunit_vector line_direction = normalise(ctrls[num_ctrlpts - 1] - ctrls[0]);
    // 连接bezier曲线的第一个控制顶点和最后一个控制顶点的直线

    for(int i = 1; i < num_ctrlpts - 1; i++) {
        double dist = distance_to_line(ctrls[i], line_root, line_direction);
        if(dist > maxdist) {
            maxdist = dist;  // 取最大距离为bezier曲线的高度估计
        }
    }
    ACIS_DELETE[] ctrls;
    ctrls = nullptr;
    return maxdist;
}

/**
 * @brief 封装MAF方法，对近似交点结果near_result迭代求精(GME版本)
 * @param cur1 曲线1
 * @param cur2 曲线2
 * @param near_result 近似交点结果
 * @param refined_result 求精后的交点结果
 * @param total_iter_num 最大迭代次数
 * @param quadratic_approximation 是否使用二次近似
 */
void curve_curve_maf(curve const& cur1, curve const& cur2, curve_curve_int* near_result, curve_curve_int*& refined_result, int total_iter_num, logical quadratic_approximation) {
    // 用MAF方法求精确交点
    int inter_num = 0;  // inter_num 精确交点个数
    curve_curve_int* inters = nullptr;

    double dt1 = NAN, dt2 = NAN;  // MAF迭代过程中两个曲线的参数增量
    SPAvector cv1, cv2;           // cv1是cur1在近似交点处的的切线方向；cv2是cur2在近似交点处的的切线方向
    SPAposition cp1, cp2, comp1, comp2;
    // cp1在cur1上的近似交点，cp2在cur2上的近似交点

    // comp1  comp2 为MAF迭代过程中cur1和cur2在cp1和cp2处切线上的近似交点
    // 见函数LineLineNearInters()

    straight line1, line2;  // cur1上近似交点处的切线，cur2上近似交点处的切线
    // SPAinterval param_range_cur1(interval_type::interval_infinite);  // cur1的参数范围
    // SPAinterval param_range_cur2(interval_type::interval_infinite);  // cur2的参数范围
    // if(cur1.type() == intcurve_type && !cur1.periodic()) {              // intcurve
    //     param_range_cur1 = bs3_curve_range(((intcurve*)&cur1)->cur());

    // intcurve const* ic_cur1 = dynamic_cast<intcurve const*>(&cur1);
    // if(ic_cur1->reversed()) {
    //     param_range_cur1 = -param_range_cur1;
    // }
    //}
    // if(cur2.type() == intcurve_type && !cur2.periodic()) {  // intcurve
    // param_range_cur2 = bs3_curve_range(((intcurve*)&cur2)->cur());

    // intcurve const* ic_cur2 = dynamic_cast<intcurve const*>(&cur2);
    // if(ic_cur2->reversed()) {
    //     param_range_cur2 = -param_range_cur2;
    // }
    //}

    curve *curve1 = (curve*)&cur1, *curve2 = (curve*)&cur2;
    // if(cur1.subsetted()) {
    //     curve1 = cur1.unsubset();
    // }
    // if(cur2.subsetted()) {
    //     curve2 = cur2.unsubset();
    // }
    SPAinterval param_range_cur1 = curve1->param_range();
    SPAinterval param_range_cur2 = curve2->param_range();
    bool linear_cur1 = cur1.type() == straight_type || (cur1.type() == intcurve_type && SPL_BezcHeightEstimate(((intcurve*)&cur1)->cur()) <= SPAresabs);
    bool linear_cur2 = cur2.type() == straight_type || (cur2.type() == intcurve_type && SPL_BezcHeightEstimate(((intcurve*)&cur2)->cur()) <= SPAresabs);
    if(linear_cur1 && linear_cur2) {
        quadratic_approximation = FALSE;
    }
    double tol = SPAresabs / 10;  // 要求参数距离在1e-7以内
    int degree = std::max(curve_degree(cur1), curve_degree(cur2));
    double dis_tol = pow(tol, degree);
    std::vector<std::pair<double, curve_curve_int*>> cci_vec;  // distance : inters
    while(near_result) {
        if(!quadratic_approximation) {
            // 对于每个近似交点，用于拉伸的曲线需要重新拷贝
            curve1 = cur1.copy_curve();  // make a copy of curve
            curve2 = cur2.copy_curve();
        }

        double cand_param1, cand_param2;
        double cand_dis = DBL_MAX;
        logical cand_point = FALSE;  // 候选的交点，防止超出迭代出错漏交点的情况，作为一种情况补充

        int iter_num = 0;  // MAF算法迭代次数

        double last_dt1 = NAN, last_dt2 = NAN;

        double true_param1 = 1.5707963391310085, true_param2 = 0.49999999383194521;

        while(iter_num < total_iter_num) {
            // 判断param与曲线参数范围的大小关系
            if(near_result->param1 > param_range_cur1) near_result->param1 = param_range_cur1.end_pt();
            if(near_result->param1 < param_range_cur1) near_result->param1 = param_range_cur1.start_pt();
            if(near_result->param2 > param_range_cur2) near_result->param2 = param_range_cur2.end_pt();
            if(near_result->param2 < param_range_cur2) near_result->param2 = param_range_cur2.start_pt();

            // printf("%d, param1: %.16lf, param2: %.16lf, dt1: %.16lf, dt2: %.16lf\n", iter_num, near_result->param1, near_result->param2, dt1, dt2);
            // printf("%d, param1_dis: %.16lf, param2_dis: %.16lf, dt1: %.16lf, dt2: %.16lf\n", iter_num, true_param1 - near_result->param1, true_param2 - near_result->param2, dt1, dt2);

            // cp1在cur1上的近似交点，cp2在cur2上的近似交点
            // @todo: eval_position 耗时过长暂不解耦
            cp1 = curve1->eval_position(near_result->param1);  // 待解耦，存在问题
            cp2 = curve2->eval_position(near_result->param2);  // 待解耦，存在问题

            // cv1在cur1上的近似交点处的切向量，cv2在cur2上的近似交点处的切向量
            cv1 = curve1->eval_deriv(near_result->param1);  // 待解耦，存在问题
            cv2 = curve2->eval_deriv(near_result->param2);  // 待解耦，存在问题

            // if(tan(angle) <= 0.0015) {  // 0.0015
            //     // 相切求交时，当两个切线的夹角的正切在0.0015内，考虑将这个交点作为候选交点
            //     // get best 靠最近的一对点
            //     cand_point = TRUE;
            //     cand_param1 = near_result->param1;
            //     cand_param2 = near_result->param2;
            //     cand_dis = distance_to_point(cp1, cp2);
            // }

            // if(!isnan(last_dt1) && !isnan(last_dt2)) {
            //     // 二次近似 迭代过程中震荡的情况处理
            //     if(fabs(last_dt1 + dt1) <= dis_tol && fabs(last_dt2 + dt2) <= dis_tol) {
            //         quadratic_approximation = FALSE;
            //     }
            // }

            if(!quadratic_approximation) {
                // @todo: VEC_acute_angle解耦存在中断
                double angle = VEC_acute_angle(cv1, cv2);       // 曲线在两个近似点处切线的夹角
                while(angle >= 1e-10 && tan(angle) <= 0.002) {  // 0.002, 0.02, 0.1
                    // 相切求交
                    SPAunit_vector vz = normalise(cv1);
                    SPAunit_vector vx, vy;
                    compute_axes_from_z(vz, vx, vy);
                    transf_curve(curve1, cp1, vx, vy, vz);
                    transf_curve(curve2, cp1, vx, vy, vz);

                    // 将x和y方向 拉伸1000倍  注: 拉伸操作会影响求交结果
                    extend_curve(curve1, 1000);
                    extend_curve(curve2, 1000);

                    // 重新计算cp1, cp2, cv1, cv2
                    // @todo: eval_position 耗时过长暂不解耦
                    cp1 = curve1->eval_position(near_result->param1);  // 待解耦，存在问题
                    cp2 = curve2->eval_position(near_result->param2);  // 待解耦，存在问题
                    cv1 = curve1->eval_deriv(near_result->param1);     // 待解耦，存在问题
                    cv2 = curve2->eval_deriv(near_result->param2);     // 待解耦，存在问题
                    angle = VEC_acute_angle(cv1, cv2);                 // 待解耦，接口未实现

                    const double MAX_THRESHOLD = 1e16;
                    if(fabs(cp1.x()) >= MAX_THRESHOLD || fabs(cp1.y()) >= MAX_THRESHOLD || fabs(cp1.z()) >= MAX_THRESHOLD) {
                        // 考虑为浮点数溢出
                        iter_num = total_iter_num;
                        break;
                    }
                }
            }

            // cv1是cur1在近似交点处的的切线方向；cv2是cur2在近似交点处的的切线方向
            // 目前测试 仍然需要设置cp1和cp2的距离小于1e-6*1e-6，不然会提前跳出
            if(distance_to_point(cp1, cp2) < dis_tol) {  // 达到精度要求
                break;
            }

            last_dt1 = dt1, last_dt2 = dt2;
            logical quadratic_success = FALSE;
            if(quadratic_approximation) {
                bool cand_point_quad = false;
                quadratic_success = quadratic_approximation_iterate(curve1, curve2, near_result->param1, near_result->param2, dt1, dt2, cand_point_quad);
                // if(quadratic_success && fabs(dt1) <= 1e-16 && fabs(dt2) <= 1e-16) {  // 1.5e-17
                //     quadratic_success = FALSE;
                // }
                if(cand_point_quad) {
                    double dis_cp1_cp2 = distance_to_point(cp1, cp2);
                    if(!cand_point || dis_cp1_cp2 < cand_dis) {
                        cand_point = TRUE;
                        cand_param1 = near_result->param1;
                        cand_param2 = near_result->param2;
                        cand_dis = dis_cp1_cp2;
                    }
                }
            }
            if(!quadratic_success) {
                // 构造cur1在cp1处,cur2在cp2处的两条切线line1, line2
                line1.root_point = cp1;
                line1.direction = normalise(cv1);
                line2.root_point = cp2;
                line2.direction = normalise(cv2);

                LineLineNearInters(line1, line2, comp1, comp2);

                // comp1和comp2为分别为line1和line2上一对最近的点
                dt1 = line1.param(comp1) / cv1.len();
                dt2 = line2.param(comp2) / cv2.len();
            }

            // 判断dt1和dt2是否足够小
            if(fabs(dt1) <= SPAresabs * SPAresabs && fabs(dt2) <= SPAresabs * SPAresabs) {
                if(distance_to_point(cp1, cp2) <= SPAresabs) {
                    // 若此时cp1和cp2已经足够接近，可认为已经收敛
                    break;
                }
            }

            near_result->param1 += dt1;
            near_result->param2 += dt2;
            // 在切线方向上改变参数值，使得两个近似交点距离更近
            iter_num++;
        }
        logical finished = FALSE;
        if(iter_num < total_iter_num) {
            finished = TRUE;
        } else if(cand_point) {
            // @todo: eval_position 耗时过长暂不解耦
            SPAposition cp1 = cur1.eval_position(cand_param1);
            SPAposition cp2 = cur2.eval_position(cand_param2);
            SPAposition int_point = mid_point(cp1, cp2);
            // @todo: test_point_tol函数未解耦：暂不解耦
            if(cur2.test_point_tol(cp1) && cur1.test_point_tol(cp2) && cur1.test_point_tol(int_point) && cur2.test_point_tol(int_point)) {  // @todo: 存在内存泄漏 运行时间较长
                finished = TRUE;
                near_result->param1 = cand_param1;
                near_result->param2 = cand_param2;
            }
        }
        if(finished) {
            // @todo: eval_position 耗时过长暂不解耦
            cp1 = cur1.eval_position(near_result->param1);   // 待解耦，存在问题
            cp2 = cur2.eval_position(near_result->param2);   // 待解耦，存在问题
            cv1 = cur1.eval_direction(near_result->param1);  // 待解耦，存在问题
            cv2 = cur2.eval_direction(near_result->param2);  // 待解耦，存在问题

            SPAposition int_point = mid_point(cp1, cp2);  // 求中点

            inters = ACIS_NEW curve_curve_int(nullptr, int_point, near_result->param1, near_result->param2);
            // double angle = VEC_acute_angle(cv1, cv2);
            if(biparallel(cv1, cv2)) {
                inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_normal;
            }
            cci_vec.push_back(std::make_pair(distance_to_point(cp1, cp2), inters));
        }
        // 销毁拷贝后的曲线
        if(!quadratic_approximation) {
            ACIS_DELETE curve1;
            ACIS_DELETE curve2;
            curve1 = curve2 = nullptr;
        }

        near_result = near_result->next;
    }
    // if(cur1.subsetted()) {
    //     ACIS_DELETE curve1;
    //     curve1 = nullptr;
    // }
    // if(cur2.subsetted()) {
    //     ACIS_DELETE curve2;
    //     curve2 = nullptr;
    // }
    //  按照distance的非递减序对cci_vec排序
    sort(cci_vec.begin(), cci_vec.end());
    inters = nullptr;
    for(int i = cci_vec.size() - 1; i >= 0; --i) {
        cci_vec[i].second->next = inters;
        inters = cci_vec[i].second;
    }

    // 额外判断曲线端点，因为MAF不能很好地处理曲线端点处的交点
    inters = connect_curve_curve_int(inters, judge_curve_ends(cur1, cur2));

    // 交点去重
    inter_num = CurvCurvIntPointReduce(inters);

    refined_result = inters;
}

/**
 * @brief 获得曲线的degree
 * @return 将曲线拟合为多项式，多项式的最高次数
 * @param cur 输入的曲线
 */
int curve_degree(curve const& cur) {
    int degree = 3;
    if(cur.type() == straight_type) {
        degree = 1;
    } else if(cur.type() == ellipse_type) {
        degree = 2;
    } else if(cur.type() == helix_type) {
        degree = 3;
    } else if(cur.type() == intcurve_type) {
        bs3_curve bs3 = ((intcurve const*)&cur)->cur();
        degree = bs3_curve_degree(bs3);
    }
    return degree;
}

/** 二次迭代获得在圆上的下一个参数 */
logical quadratic_approximation_circle_iterate(curve* _curv, ellipse const& cir, double t, SPAposition const& int_point, double& dt) {
    double _dt = 1e8;
    logical success = FALSE;
    curve* curv = _curv->copy_curve();
    // 将曲线转化到圆的局部坐标系
    SPAtransf transf = std::move(cucuint_coordinate_transf(cir.centre, cir.major_axis, cir.normal * cir.major_axis, cir.normal));
    (*curv) *= transf;

    SPAposition cp;
    SPAvector cv, cvv;
    curv->eval(t, cp, cv, cvv);
    // ACIS的eval() 二次nurbs，cvv可能得到的值为零向量，EllipseNURBSIntrTest.Degree2Inters1
    if(is_zero(cvv) && curv->type() == intcurve_type) {
        bs3_curve_eval(t, ((intcurve*)curv)->cur(), cp, cv, cvv);
    }

    straight str(int_point * transf, normalise((cir.normal * transf) * cv));
    SPAvector str_vec(0, 0, 0);
    double D = 0.0;
    straight_coef(str, str_vec.x(), str_vec.y(), D);
    double A = 0.5 * cvv % str_vec;
    double B = (cv - t * cvv) % str_vec;
    double C = (cp - cv * t + 0.5 * cvv * t * t) % str_vec + D;
    double coef[] = {A, B, C};
    double* roots = nullptr;
    int num_root = Equatn(2, coef, roots, -1e8, 1e8);

    if(num_root == 0) {
        success = FALSE;
    }
    for(int i = 0; i < num_root; ++i) {
        double tmp = roots[i] - t;
        if(fabs(tmp) < fabs(_dt)) {
            _dt = tmp;
            success = TRUE;
        }
    }

    //(*curv) *= (transf.inverse());  // restore存在精度问题
    ACIS_DELETE curv;
    ACIS_DELETE[] STD_CAST roots;
    roots = nullptr;
    curv = nullptr;
    if(success) {
        dt = _dt;
    }
    return success;
}

/** 二次迭代得到下一个交点 */
logical quadratic_approximation_iterate(curve* cur1, curve* cur2, double param1, double param2, double& dt1, double& dt2, bool& cand_point) {
    logical success = FALSE;  // 迭代成功

    // 二次近似 尝试将曲线近似为圆
    ellipse cir1, cir2;
    double max_lg1 = 0.0, max_lg2 = 0.0;
    logical can_cir1 = construct_curvature_circle(*cur1, param1, cir1, max_lg1);
    logical can_cir2 = construct_curvature_circle(*cur2, param2, cir2, max_lg2);
    cand_point = false;
    // printf("%.16lf, %.16lf\n", max_lg1, max_lg2);
    if(max_lg1 > 14.0 || max_lg2 > 14.0) {  // 14.15 14.7  20
        cand_point = true;
    }
    if((can_cir1 && is_zero(cir1.major_axis)) || (can_cir2 && is_zero(cir2.major_axis))) {
        // 当曲率圆曲率半径为0时，返回FALSE
        return FALSE;
    }
    double _dt1 = 1e8, _dt2 = 1e8;
    // @todo: eval_position耗时过长暂不解耦
    SPAposition cp1 = cur1->eval_position(param1), cp2 = cur2->eval_position(param2);
    std::vector<SPAposition> pos1_array, pos2_array;
    if(can_cir1 && can_cir2) {
        bool coin = circle_circle_closest_points(cir1, cir2, pos1_array, pos2_array);
        if(coin) {
            return FALSE;
        }
        int num_pos = pos1_array.size();
        if(num_pos > 0) {
            SPAposition pos1 = pos1_array[0], pos2 = pos2_array[0];
            double _param1 = cir1.param(pos1), _param2 = cir2.param(pos2);
            // if(num_pos == 2) {
            //     pos1 = distance_to_point(pos1, cp1) < distance_to_point(pos1_array[1], cp1) ? pos1 : pos1_array[1];
            //     pos2 = distance_to_point(pos2, cp2) < distance_to_point(pos2_array[1], cp2) ? pos2 : pos2_array[1];
            // }
            // logical success1 = quadratic_approximation_circle_iterate(cur1, cir1, param1, pos1, _dt1);
            // logical success2 = quadratic_approximation_circle_iterate(cur2, cir2, param2, pos2, _dt2);
            // success = (success1 == TRUE && success2 == TRUE);

            if(num_pos == 2) {
                double _param1_next = cir1.param(pos1_array[1]), _param2_next = cir2.param(pos2_array[1]);
                if(fabs(_param1) * cir1.major_axis.len() + fabs(_param2) * cir2.major_axis.len() > fabs(_param1_next) * cir1.major_axis.len() + fabs(_param2_next) * cir2.major_axis.len()) {
                    pos1 = pos1_array[1], pos2 = pos2_array[1];
                    _param1 = _param1_next, _param2 = _param2_next;
                }
            }

            SPAposition cp;
            SPAvector cv1, cvv1;
            // @todo: eval、is_zero、bs3_curve_eval、cur、numerically_stable_len、VEC_acute_angle函数未解耦
            cur1->eval(param1, cp, cv1, cvv1);
            if(is_zero(cvv1) && cur1->type() == intcurve_type) {
                bs3_curve_eval(param1, ((intcurve*)cur1)->cur(), cp, cv1, cvv1);
            }
            SPAvector cv2, cvv2;
            cur2->eval(param2, cp, cv2, cvv2);
            if(is_zero(cvv2) && cur2->type() == intcurve_type) {
                bs3_curve_eval(param2, ((intcurve*)cur2)->cur(), cp, cv2, cvv2);
            }
            double cv1_len = cv1.numerically_stable_len();
            double cvv1_len = cvv1.numerically_stable_len();
            double fsin_cv1_cvv1 = fabs(sin(VEC_acute_angle(cv1, cvv1)));
            double cv2_len = cv2.numerically_stable_len();
            double cvv2_len = cvv2.numerically_stable_len();
            double fsin_cv2_cvv2 = fabs(sin(VEC_acute_angle(cv2, cvv2)));

            if(cvv1_len * fsin_cv1_cvv1 > 0 && cv1_len > 1e-16 * (cvv1_len * fsin_cv1_cvv1)) {
                _dt1 = cv1_len * _param1 / (cvv1_len * fsin_cv1_cvv1);
                success = TRUE;
            } else {
                _dt1 = 0.0;
            }
            if(cvv2_len * fsin_cv2_cvv2 > 0 && cv2_len > 1e-16 * (cvv2_len * fsin_cv2_cvv2)) {
                _dt2 = cv2_len * _param2 / (cvv2_len * fsin_cv2_cvv2);
                success = TRUE;
            } else {
                _dt2 = 0.0;
            }

            // if(cvv1_len * fsin_cv1_cvv1 > 0 && cv1_len > 1e-16 * (cvv1_len * fsin_cv1_cvv1) && cvv2_len * fsin_cv2_cvv2 > 0 && cv2_len > 1e-16 * (cvv2_len * fsin_cv2_cvv2)) {
            //     //_dt1 = cv1_len_sq * _param1 / cv1_cvv1_len;
            //     //_dt2 = cv2_len_sq * _param2 / cv2_cvv2_len;
            //     _dt1 = cv1_len * _param1 / (cvv1_len * fsin_cv1_cvv1);
            //     _dt2 = cv2_len * _param2 / (cvv2_len * fsin_cv2_cvv2);
            //     success = TRUE;
            // } else {
            //     _dt1 = _dt2 = 0.0;
            //     success = FALSE;
            // }
        }
    } else if(can_cir1 || can_cir2) {
        SPAvector cv;
        straight st;
        ellipse cir;
        curve* cur = nullptr;
        double t = 0.0;
        if(!can_cir1) {
            // @todo: param函数未解耦:param耗时过长暂不解耦
            cv = cur1->eval_deriv(param1);
            st.root_point = cp1;
            st.direction = normalise(cv);
            cir = cir2;
            t = param2;
            cur = cur2;
        } else {
            cv = cur2->eval_deriv(param2);
            st.root_point = cp2;
            st.direction = normalise(cv);
            cir = cir1;
            t = param1;
            cur = cur1;
        }
        line_circle_closest_points(st, cir, pos1_array, pos2_array);
        int num_points = pos1_array.size();
        if(num_points > 0) {
            SPAposition pos1 = pos1_array[0], pos2 = pos2_array[0];
            double _param1 = st.param(pos1), _param2 = cir.param(pos2);
            if(num_points == 2) {
                double _param1_next = st.param(pos1_array[1]), _param2_next = cir.param(pos2_array[1]);
                if(fabs(_param1) + fabs(_param2) * cir.major_axis.len() > fabs(_param1_next) + fabs(_param2_next) * cir.major_axis.len()) {
                    pos1 = pos1_array[1], pos2 = pos2_array[1];
                    _param1 = _param1_next, _param2 = _param2_next;
                }
            }
            SPAposition cp;
            SPAvector cv2, cvv2;
            cur->eval(t, cp, cv2, cvv2);
            if(is_zero(cvv2) && cur->type() == intcurve_type) {
                bs3_curve_eval(t, ((intcurve*)cur)->cur(), cp, cv2, cvv2);
            }

            double cv2_len_sq = cv2.len_sq();
            double cv2_cvv2_len = (cv2 * cvv2).len();
            if(fabs(cv2_cvv2_len) > 0 && cv2_len_sq > 1e-16 * cv2_cvv2_len) {
                _dt2 = cv2_len_sq * _param2 / cv2_cvv2_len;
                //_dt2 = cv2_len * _param2 / (cvv2_len * fsin_cv2_cvv2);  // NurbsNurbsIntrTest.TestMAF3 FAIL
                _dt1 = _param1 / cv.len();
                if(!can_cir2) {
                    std::swap(_dt1, _dt2);
                }
                success = TRUE;
            } else {
                _dt1 = _dt2 = 0;
                success = FALSE;
            }
            // success = quadratic_approximation_circle_iterate(cur, cir, t, pos2, _dt2);
        }

        // auto inters = int_cur_cur(st, cir);

        // if(inters) {
        //     SPAposition pos = inters->int_point;
        //     if(inters->next && distance_to_point(pos, cp1) + distance_to_point(pos, cp2) > distance_to_point(inters->next->int_point, cp1) + distance_to_point(inters->next->int_point, cp2)) {
        //         pos = inters->next->int_point;
        //     }
        //     success = quadratic_approximation_circle_iterate(cur, cir, t, pos, _dt2);
        //     _dt1 = st.param(pos) / cv.len();
        //     if(!can_cir2) {
        //         std::swap(_dt1, _dt2);
        //     }
        //     delete_curve_curve_ints(inters);
        // } else {
        //     double t1 = param1, t2 = param2;
        //     if(!can_cir2) {
        //         std::swap(t1, t2);
        //     }
        //     // try MinDistancePointPair
        //     SPAposition pos1, pos2;
        //     MinDistancePointPair_Impl(st, cir, Vector<2>({t1, t2}), pos1, pos2);
        //     success = quadratic_approximation_circle_iterate(cur, cir, t, pos2, _dt2);
        //     _dt1 = st.param(pos1) / cv.len();
        //     if(!can_cir2) {
        //         std::swap(_dt1, _dt2);
        //     }
        // }
    }
    if(success) {
        dt1 = _dt1, dt2 = _dt2;
    }
    return success;
}

// 将曲线所在的x轴和y轴拉伸extend_magnitude倍
void extend_curve(curve*& curve1, double extend_magnitude) {
    if(!curve1) {
        return;
    }
    bool extended = false;
    if(curve1->type() == intcurve_type) {
        // 样条曲线
        intcurve* ic = static_cast<intcurve*>(curve1);
        int_cur const* intc = &ic->get_int_cur();
        if(intc->type() == exactcur_type || intc->type() == parcur_type) {  // exact_int_cur 与 par_int_cur
            // exact_int_cur
            // @todo: cur、bs3_curve_copy、 bs3_curve_weights、bs3_curve_control_points、bs3_curve_set_ctrlpts函数未解耦
            bs3_curve bs = ic->cur();
            bs3_curve bs_new = bs3_curve_copy(bs);  // @todo: 执行时间较长
            SPAposition* ctrlpts = nullptr;
            int num_ctrlpts = 0;
            double* weights = nullptr;
            bs3_curve_weights(bs, num_ctrlpts, weights);         // @todo: 执行时间较长
            bs3_curve_control_points(bs, num_ctrlpts, ctrlpts);  // @todo: 执行时间较长
            double* pos = ACIS_NEW double[num_ctrlpts * 3];

            for(int i = 0; i < num_ctrlpts; ++i) {
                // 在x和y方向拉伸
                pos[3 * i] = ctrlpts[i].x() * extend_magnitude;
                pos[3 * i + 1] = ctrlpts[i].y() * extend_magnitude;
                pos[3 * i + 2] = ctrlpts[i].z();
            }
            bs3_curve_set_ctrlpts(bs_new, num_ctrlpts, pos, weights);  // @todo: 执行时间较长

            ACIS_DELETE[] STD_CAST weights;
            ACIS_DELETE[] STD_CAST pos;
            ACIS_DELETE[] ctrlpts;
            weights = pos = nullptr;
            ctrlpts = nullptr;

            ACIS_DELETE curve1;
            curve1 = make_exact_intcurve(bs_new);
            extended = true;
        }
    }
    if(!extended) {
        SPAtransf transf = std::move(scale_transf(extend_magnitude, extend_magnitude, 1));
        // curve1->debug("");
        API_BEGIN

          (*curve1) *= transf;
        API_END
        if(!result.ok()) {
            // printf("%s\n", result.get_error_info()->error_message());
            if(curve1->type() == intcurve_type) {
                intcurve* ic = static_cast<intcurve*>(curve1);
                int_cur const* intc = &ic->get_int_cur();
                // logical ok = intc->mult_ref();
                // multi_ref未实现，此处总是执行复制操作
                bs3_curve bs3 = bs3_curve_copy(ic->cur());
                ACIS_DELETE ic;
                bs3_curve_trans(bs3, transf);
                exact_int_cur* eic = ACIS_NEW exact_int_cur(bs3);
                curve1 = ACIS_NEW intcurve(eic);
            }
        }
    }
}

// 将curve1转化到 (cp, vx, vy, vz)的局部坐标系中
void transf_curve(curve*& curve1, SPAposition cp, SPAunit_vector vx, SPAunit_vector vy, SPAunit_vector vz) {
    if(curve1 != nullptr) {
        bool transfered = false;
        if(curve1->type() == intcurve_type) {
            intcurve* ic = static_cast<intcurve*>(curve1);
            int_cur const* intc = &ic->get_int_cur();
            if(intc->type() == exactcur_type || intc->type() == parcur_type) {  // exact_int_cur 与 par_int_cur
                SPAmatrix transfer_matrix(vx, vy, vz);
                // exact_int_cur
                bs3_curve bs = ic->cur();
                // @todo: bs3_curve_copy、 bs3_curve_weights、bs3_curve_control_points、bs3_curve_set_ctrlpts函数未解耦
                bs3_curve bs_new = bs3_curve_copy(bs);  // @todo: 执行时间较长
                SPAposition* ctrlpts = nullptr;
                int num_ctrlpts = 0;
                double* weights = nullptr;
                bs3_curve_weights(bs, num_ctrlpts, weights);         // @todo: 执行时间较长
                bs3_curve_control_points(bs, num_ctrlpts, ctrlpts);  // @todo: 执行时间较长
                double* pos = ACIS_NEW double[num_ctrlpts * 3];

                for(int i = 0; i < num_ctrlpts; ++i) {
                    SPAposition int_point = transfer_matrix * (ctrlpts[i] - cp) + SPAposition(0, 0, 0);
                    pos[3 * i] = int_point.x();
                    pos[3 * i + 1] = int_point.y();
                    pos[3 * i + 2] = int_point.z();
                }
                bs3_curve_set_ctrlpts(bs_new, num_ctrlpts, pos, weights);  // @todo: 执行时间较长

                ACIS_DELETE[] weights;
                ACIS_DELETE[] pos;
                ACIS_DELETE[] ctrlpts;
                weights = pos = nullptr;
                ctrlpts = nullptr;

                ACIS_DELETE curve1;
                curve1 = make_exact_intcurve(bs_new);
                transfered = TRUE;
            }
        }
        if(!transfered) {
            SPAtransf transf = std::move(cucuint_coordinate_transf(cp, vx, vy, vz));
            (*curve1) *= transf;
        }
    }
}

// 构造坐标系变换的SPAtransf
SPAtransf cucuint_coordinate_transf(SPAposition const& root, SPAvector const& vx, SPAvector const& vy, SPAvector const& vz) {
    // 要求vx，vy，vz两两正交，且不为零向量
    SPAmatrix mat(normalise(vx), normalise(vy), normalise(vz));
    SPAposition origin(0, 0, 0);
    SPAvector translate_vec = mat * (origin - root);
    return SPAtransf(mat.transpose(), translate_vec, 1.0, FALSE, FALSE, FALSE);
}

/**
 * @brief 已知cur1和cur2完全重合(参数范围内)，求cur1在coin_int1和cur2在coin_int2的重合段
 */
std::vector<SPAinterval> get_coincident_segment(curve const& cur1, curve const& cur2, SPAinterval const& coin_int1, SPAinterval const& coin_int2) {
    std::vector<SPAinterval> ans;
    if(fabs(coin_int1.end_pt() - coin_int1.start_pt()) <= SPAresabs) {
        // @todo: test_point_tol函数未解耦：暂不解耦耗时过长
        if(cur2.test_point_tol(cur1.eval_position(coin_int1.mid_pt()))) {
            ans.push_back(coin_int1);
            return ans;
        } else {
            return ans;  // empty interval
        }
    }
    double st1 = coin_int1.start_pt();
    double ed1 = coin_int1.end_pt();
    SPAposition start_pos1 = cur1.eval_position(st1);
    SPAposition end_pos1 = cur1.eval_position(ed1);

    double st2 = coin_int2.start_pt();
    double ed2 = coin_int2.end_pt();
    SPAposition start_pos2 = cur2.eval_position(st2);
    SPAposition end_pos2 = cur2.eval_position(ed2);

    logical unbound_left = TRUE;
    double st2_1, ed2_1;
    logical unbound_right = TRUE;
    // @todo: test_point_tol、param函数未解耦：暂不解耦耗时过长
    if(cur1.test_point_tol(start_pos2) && cur1.param(start_pos2) << coin_int1) {
        unbound_left = FALSE;
        st2_1 = cur1.param(start_pos2);
    }
    if(cur1.test_point_tol(end_pos2) && cur1.param(end_pos2) << coin_int1) {
        unbound_right = FALSE;
        ed2_1 = cur1.param(end_pos2);
    }
    if(!unbound_left && !unbound_right && cur1.periodic() && fabs(coin_int2.length() - cur2.param_period()) <= SPAresabs) {
        // 待测试
        st2_1 = cur1.param_range().start_pt();
        ed2_1 = cur1.param_range().end_pt();
    }

    SPAinterval coin_int2_1;
    if(!unbound_left && !unbound_right) {
        // 补充判断，如果原本完整曲线为闭曲线，则当曲线1端点都在曲线2上时
        // 还需要判断曲线中的采样点(中点)也在其上，才可以认为是重合段
        double mid_point = (st2 + ed2) / 2;
        if(distance_to_curve(cur2.eval_position(mid_point), cur1) <= SPAresabs) {  // @todo: ACIS面交线的test_point_tol存在问题，可能会中断
            if((cur1.periodic() || cur1.closed()) && (cur2.periodic() || cur2.closed()) && fabs(ed2_1 - st2_1) <= SPAresabs && fabs(ed2 - st2) > SPAresabs) {
                coin_int2_1 = cur1.param_range();
            } else {
                coin_int2_1 = SPAinterval(interval_finite, st2_1, ed2_1);
            }
            ans.push_back(coin_int2_1);
        } else {
            coin_int2_1 = SPAinterval(interval_finite, st2_1, st2_1);
            ans.push_back(coin_int2_1);
            coin_int2_1 = SPAinterval(interval_finite, ed2_1, ed2_1);
            ans.push_back(coin_int2_1);
        }
    } else if(!unbound_left && unbound_right) {
        coin_int2_1 = SPAinterval(st2_1);
        double st2_delta = st2 + SPAresabs;
        SPAposition point = cur2.eval_position(st2_delta);
        if(cur1.test_point_tol(point)) {
            double st2_delta_1 = cur1.param(point);
            if(st2_delta_1 - st2_1 >= -SPAresabs && cur2.test_point_tol(end_pos1)) {
                coin_int2_1 = SPAinterval(interval_finite_below, st2_1);
            } else if(st2_delta_1 - st2_1 < -SPAresabs && cur2.test_point_tol(start_pos1)) {
                coin_int2_1 = SPAinterval(interval_finite_above, st2_1);
            }
        }
        ans.push_back(coin_int2_1);
    } else if(unbound_left && !unbound_right) {
        coin_int2_1 = SPAinterval(ed2_1);
        double ed2_delta = ed2 - SPAresabs;
        SPAposition point = cur2.eval_position(ed2_delta);
        // @todo: test_point_tol、param函数未解耦:暂不解耦耗时过长
        if(cur1.test_point_tol(point)) {
            double ed2_delta_1 = cur1.param(point);
            if(ed2_delta_1 - ed2_1 <= SPAresabs && cur2.test_point_tol(start_pos1)) {
                coin_int2_1 = SPAinterval(interval_finite_above, ed2_1);
            } else if(ed2_delta_1 - ed2_1 > SPAresabs && cur2.test_point_tol(end_pos1)) {
                coin_int2_1 = SPAinterval(interval_finite_below, ed2_1);
            }
        }
        ans.push_back(coin_int2_1);
    }
    for(int i = 0; i < ans.size(); ++i) {
        ans[i] &= coin_int1;
    }
    return ans;
}

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
logical bivariant_newton_iterate(const double* x_init, law** F_array, law** Jacob_array, double** x_out, double tol, int max_count) {
    logical result = TRUE;
    if(!x_init || !x_out) {
        return FALSE;
    }
    int iter_num = 1;
    *x_out = ACIS_NEW double[2];
    (*x_out)[0] = x_init[0];
    (*x_out)[1] = x_init[1];

    double F_value[2];
    double Jacob_value[4];
    double Jacob_invert_value[4];
    double x_delta[2];
    int i = 0;
    while(iter_num <= max_count) {
        // 计算F
        for(i = 0; i < 2; ++i) {
            F_array[i]->evaluate(*x_out, &F_value[i]);  // @todo: 存在内存泄漏问题 EllipseHelixIntrTest.TestBug1
        }
        if(fabs(F_value[0]) <= tol && fabs(F_value[1]) <= tol) {
            // 若函数值在容差范围内等于0，找到给定根，停止迭代
            result = TRUE;
            break;
        }

        // 计算Jacob
        for(i = 0; i < 4; ++i) {
            Jacob_array[i]->evaluate(*x_out, &Jacob_value[i]);  // @todo: 存在内存泄漏问题 EllipseHelixIntrTest.TestBug1
        }
        double det = Jacob_value[0] * Jacob_value[3] - Jacob_value[1] * Jacob_value[2];
        if(fabs(det) <= tol) {
            // 若矩阵的行列式为0，牛顿法失效，停止迭代
            result = FALSE;
            break;
        }

        // 逆矩阵
        Jacob_invert_value[0] = Jacob_value[3] / det;
        Jacob_invert_value[1] = -Jacob_value[1] / det;
        Jacob_invert_value[2] = -Jacob_value[2] / det;
        Jacob_invert_value[3] = Jacob_value[0] / det;

        // x_delta = Jacob_invert*F
        x_delta[0] = Jacob_invert_value[0] * F_value[0] + Jacob_invert_value[1] * F_value[1];
        x_delta[1] = Jacob_invert_value[2] * F_value[0] + Jacob_invert_value[3] * F_value[1];

        if(fabs(x_delta[0]) <= tol && fabs(x_delta[1]) <= tol) {
            // x_delta容差范围内为0，可以认为收敛
            result = TRUE;
            break;
        }
        (*x_out)[0] -= x_delta[0];
        (*x_out)[1] -= x_delta[1];
        iter_num++;
    }
    if(iter_num == max_count + 1) {
        // 达到最大迭代次数 迭代失败
        result = FALSE;
    }
    if(!result) {
        // 销毁结果
        ACIS_DELETE[] STD_CAST* x_out;
        *x_out = nullptr;
    }
    return result;
}

/**
 * @brief 椭圆和B样条曲线的隐式化方法(解方程法)
 * @return curve_curve_int*的交点结果
 * @param ell 椭圆
 * @param bs3 B样条曲线
 * @param tol 容差
 */
curve_curve_int* ellipse_bspline_int_implicitization(ellipse const& ell, bs3_curve bs3, double tol) {
    curve_curve_int* inters = nullptr;  // 最终交点返回值初始化为空指针

    logical rat = bs3_curve_rational(bs3);  // rat标识intcurve是b-spline还是nurbs  // 待解偶，存在问题
    if(rat) {
        // 有理的情况不处理
        return inters;
    }

    bs3_curve tmp = bs3_curve_copy(bs3);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(tmp);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree = bs3_curve_degree(bs3);  // B样条曲线的次数
    logical copyed = FALSE;              // 是否拷贝并修改了原来的B样条曲线
    if(degree != 3) {
        // GMES中只处理三次样条
        if(degree > 3) {
            // 高于三次的样条不做处理
            return inters;
        } else {
            // 对低于三次的样条作升阶处理
            bs3_curve tmp = bs3_curve_copy(bs3);
            for(int i = 0; i < 3 - degree; ++i) {  // 将低于三次的样条升阶到三次
                bs3_curve_degree_elevate(tmp);
            }
            bs3 = tmp;
            copyed = TRUE;
        }
    }
    int dim, num_ctrlpts, num_knots;  // B-样条的维度，控制顶点个数，节点个数

    SPAposition* ctrlpts;  // 控制顶点数组
    double* knots;         // 节点数组
    double* weights;       // 权重数组

    bs3_curve_to_array(bs3, dim, degree, rat, num_ctrlpts, ctrlpts, weights, num_knots, knots);  // 此函数用来获取B-样条曲线的数据信息 // 待解偶，存在问题

    SPAunit_vector vx, vy, vz;
    double A = NAN, B = NAN;
    SPAposition p, center, tmpP;
    int i = 0, j = 0;
    int numSeg = 0;                    // 样条的段数
    std::vector<SPAposition> intPnts;  // 交点向量
    std::vector<double> intT;          // 交点在B样条曲线上的参数的数组

    // 获得椭圆的局部坐标系
    vx = normalise(ell.major_axis);
    vz = normalise(ell.normal);
    vy = normalise(vz * vx);
    A = ell.major_axis.len();                     // 椭圆的长轴
    B = ell.major_axis.len() * ell.radius_ratio;  // 椭圆的短轴
    center = ell.centre;
    // 椭圆所在的平面
    plane pln;
    pln.root_point = center;
    pln.normal = vz;

    numSeg = num_ctrlpts - degree;  // 最大段数

    // 将控制顶点转化到椭圆的局部坐标系
    for(i = 0; i < num_ctrlpts; i++) {
        tmpP = ctrlpts[i];
        p.x() = (tmpP - center) % vx;
        p.y() = (tmpP - center) % vy;
        p.z() = (tmpP - center) % vz;
        ctrlpts[i] = p;
    }

    // 样条的表示
    double di[4];   // Ni, k -对应基的系数
    double di1[4];  // Ni-1, k -对应基的系数
    double di2[4];  // Ni-2, k -对应基的系数
    double di3[4];  // Ni-3, k -对应基的系数
    double x = NAN, y = NAN, z = NAN;
    double xCoef[4], yCoef[4], zCoef[4];
    double x2Coef[7], y2Coef[7];  // 平方后的系数,最作为7个系数
    double dxyCoef[7], xyCoef[4];
    int xNum = 0, yNum = 0;
    double* u;
    int solution = -1;

    for(i = 3; i < num_ctrlpts; i++) {
        if(fabs(knots[i + 1] - knots[i]) <= tol) {  // 排除 端点相同的区间
            continue;
        }
        // 求解 Ni-3, k
        GetCubicPoly(knots[i - 3], knots[i - 2], knots[i - 1], knots[i], knots[i + 1], knots[i], knots[i + 1], di3);
        // 求解 Ni-2, k
        GetCubicPoly(knots[i - 2], knots[i - 1], knots[i], knots[i + 1], knots[i + 2], knots[i], knots[i + 1], di2);
        // 求解 Ni-1, k
        GetCubicPoly(knots[i - 1], knots[i], knots[i + 1], knots[i + 2], knots[i + 3], knots[i], knots[i + 1], di1);
        // 求解 Ni, k
        GetCubicPoly(knots[i], knots[i + 1], knots[i + 2], knots[i + 3], knots[i + 4], knots[i], knots[i + 1], di);

        // 计算 三次B样条曲线x = x(u) 的u^3的系数
        xCoef[3] = di[3] * ctrlpts[i].x() + di1[3] * ctrlpts[i - 1].x() + di2[3] * ctrlpts[i - 2].x() + di3[3] * ctrlpts[i - 3].x();
        // 计算 三次B样条曲线 x = x(u) 的u^2的系数
        xCoef[2] = di[2] * ctrlpts[i].x() + di1[2] * ctrlpts[i - 1].x() + di2[2] * ctrlpts[i - 2].x() + di3[2] * ctrlpts[i - 3].x();
        // 计算  三次B样条曲线x = x(u) 的u的系数
        xCoef[1] = di[1] * ctrlpts[i].x() + di1[1] * ctrlpts[i - 1].x() + di2[1] * ctrlpts[i - 2].x() + di3[1] * ctrlpts[i - 3].x();
        // 计算  三次B样条曲线x = x(u) 的常系数
        xCoef[0] = di[0] * ctrlpts[i].x() + di1[0] * ctrlpts[i - 1].x() + di2[0] * ctrlpts[i - 2].x() + di3[0] * ctrlpts[i - 3].x();

        // 计算  三次B样条曲线y = y(u) 的u^3的系数
        yCoef[3] = di[3] * ctrlpts[i].y() + di1[3] * ctrlpts[i - 1].y() + di2[3] * ctrlpts[i - 2].y() + di3[3] * ctrlpts[i - 3].y();
        // 计算  三次B样条曲线y = y(u) 的u^2的系数
        yCoef[2] = di[2] * ctrlpts[i].y() + di1[2] * ctrlpts[i - 1].y() + di2[2] * ctrlpts[i - 2].y() + di3[2] * ctrlpts[i - 3].y();
        // 计算  三次B样条曲线y = y(u) 的u的系数
        yCoef[1] = di[1] * ctrlpts[i].y() + di1[1] * ctrlpts[i - 1].y() + di2[1] * ctrlpts[i - 2].y() + di3[1] * ctrlpts[i - 3].y();
        // 计算  三次B样条曲线y = y(u) 的常系数
        yCoef[0] = di[0] * ctrlpts[i].y() + di1[0] * ctrlpts[i - 1].y() + di2[0] * ctrlpts[i - 2].y() + di3[0] * ctrlpts[i - 3].y();

        // 计算  三次B样条曲线z = z(u) 的u^3的系数
        zCoef[3] = di[3] * ctrlpts[i].z() + di1[3] * ctrlpts[i - 1].z() + di2[3] * ctrlpts[i - 2].z() + di3[3] * ctrlpts[i - 3].z();
        // 计算  三次B样条曲线z = z(u) 的u^2的系数
        zCoef[2] = di[2] * ctrlpts[i].z() + di1[2] * ctrlpts[i - 1].z() + di2[2] * ctrlpts[i - 2].z() + di3[2] * ctrlpts[i - 3].z();
        // 计算  三次B样条曲线z = z(u) 的u的系数
        zCoef[1] = di[1] * ctrlpts[i].z() + di1[1] * ctrlpts[i - 1].z() + di2[1] * ctrlpts[i - 2].z() + di3[1] * ctrlpts[i - 3].z();
        // 计算  三次B样条曲线z = z(u) 的常系数
        zCoef[0] = di[0] * ctrlpts[i].z() + di1[0] * ctrlpts[i - 1].z() + di2[0] * ctrlpts[i - 2].z() + di3[0] * ctrlpts[i - 3].z();

        // 如果此段在平面上，那么四个控制点的z坐标为0；
        if(fabs(ctrlpts[i].z()) < 1e-8 && fabs(ctrlpts[i - 1].z()) < 1e-8 && fabs(ctrlpts[i - 2].z()) < 1e-8 && fabs(ctrlpts[i - 3].z()) < 1e-8) {
            // 注意，这里的系数必须先用低次的开始，paras1[0]+paras1[1]x+.....
            for(j = 0; j < 7; j++) {
                x2Coef[j] = 0.0;
                y2Coef[j] = 0.0;
            }

            // x2Coef = xCoef * xCoef
            GetMultiUniVarPoly(xCoef, 3, xCoef, 3, x2Coef, xNum);
            // y2Coef = yCoef * yCoef
            GetMultiUniVarPoly(yCoef, 3, yCoef, 3, y2Coef, yNum);

            // 计算一段B样条曲线代入椭圆隐式方程得到的一元六次方程
            // B*B*xCoef*xCoef + A*A*yCoef*yCoef - A*A*B*B = 0
            for(j = 0; j < 7; j++) {
                dxyCoef[j] = x2Coef[6 - j] * (B * B) + y2Coef[6 - j] * (A * A);  // 变换系数顺序 从低位开始存储高次项系数
            }
            dxyCoef[6] -= A * A * B * B;  // 减去常数项A*A*B*B

            // 解方程求解参数
            // 返回高次方程的实根
            // 系数必须先用高次的开始
            solution = Equatn(6, dxyCoef, u, knots[i], knots[i + 1]);

            for(j = 0; j < solution; j++) {
                x = (di[3] * u[j] * u[j] * u[j] + di[2] * u[j] * u[j] + di[1] * u[j] + di[0]) * ctrlpts[i].x() + (di1[3] * u[j] * u[j] * u[j] + di1[2] * u[j] * u[j] + di1[1] * u[j] + di1[0]) * ctrlpts[i - 1].x() +
                    (di2[3] * u[j] * u[j] * u[j] + di2[2] * u[j] * u[j] + di2[1] * u[j] + di2[0]) * ctrlpts[i - 2].x() + (di3[3] * u[j] * u[j] * u[j] + di3[2] * u[j] * u[j] + di3[1] * u[j] + di3[0]) * ctrlpts[i - 3].x();
                y = (di[3] * u[j] * u[j] * u[j] + di[2] * u[j] * u[j] + di[1] * u[j] + di[0]) * ctrlpts[i].y() + (di1[3] * u[j] * u[j] * u[j] + di1[2] * u[j] * u[j] + di1[1] * u[j] + di1[0]) * ctrlpts[i - 1].y() +
                    (di2[3] * u[j] * u[j] * u[j] + di2[2] * u[j] * u[j] + di2[1] * u[j] + di2[0]) * ctrlpts[i - 2].y() + (di3[3] * u[j] * u[j] * u[j] + di3[2] * u[j] * u[j] + di3[1] * u[j] + di3[0]) * ctrlpts[i - 3].y();

                // 转换坐标系，逆变换
                //  将B样条曲线从椭圆的局部坐标系变换回世界坐标系
                z = 0;
                double delt = vx.x() * vy.y() * vz.z() + vx.y() * vy.z() * vz.x() + vy.x() * vz.y() * vx.z() - vz.x() * vy.y() * vx.z() - vx.y() * vy.x() * vz.z() - vx.x() * vz.y() * vy.z();
                p.x() = center.x() + (x * vy.y() * vz.z() + vx.y() * vy.z() * z + y * vz.y() * vx.z() - z * vy.y() * vx.z() - vx.y() * y * vz.z() - x * vz.y() * vy.z()) / delt;
                p.y() = center.y() + (vx.x() * y * vz.z() + x * vy.z() * vz.x() + vy.x() * z * vx.z() - vz.x() * y * vx.z() - x * vy.x() * vz.z() - vx.x() * z * vy.z()) / delt;
                p.z() = center.z() + (vx.x() * vy.y() * z + vx.y() * y * vz.x() + vy.x() * vz.y() * x - vz.x() * vy.y() * x - vx.y() * vy.x() * z - vx.x() * vz.y() * y) / delt;

                // 判断交点是否在椭圆上
                if(ell.test_point_tol(p, tol) && ic->test_point_tol(p, tol)) {  // @todo: 耗时
                    intPnts.push_back(p);
                    intT.push_back(u[j]);
                }
            }
            ACIS_DELETE[] STD_CAST u;
        } else  // 转化为椭圆所在的平面与样条求交，然后判断点是否在椭圆上
        {
            double a0 = NAN, b0 = NAN, c0 = NAN, d0 = NAN;

            // 一段B样条曲线的参数方程代入平面的隐式方程，得到一元三次方程
            a0 = pln.normal.x();
            b0 = pln.normal.y();
            c0 = pln.normal.z();
            d0 = -(pln.root_point - SPAposition(0, 0, 0)) % pln.normal;

            xyCoef[0] = a0 * xCoef[3] + b0 * yCoef[3] + c0 * zCoef[3];
            xyCoef[1] = a0 * xCoef[2] + b0 * yCoef[2] + c0 * zCoef[2];
            xyCoef[2] = a0 * xCoef[1] + b0 * yCoef[1] + c0 * zCoef[1];
            xyCoef[3] = a0 * xCoef[0] + b0 * yCoef[0] + c0 * zCoef[0] - d0;

            // 求解3次方程
            solution = Equatn(3, xyCoef, u, knots[i], knots[i + 1]);

            for(j = 0; j < solution; j++) {
                x = (di[3] * u[j] * u[j] * u[j] + di[2] * u[j] * u[j] + di[1] * u[j] + di[0]) * ctrlpts[i].x() + (di1[3] * u[j] * u[j] * u[j] + di1[2] * u[j] * u[j] + di1[1] * u[j] + di1[0]) * ctrlpts[i - 1].x() +
                    (di2[3] * u[j] * u[j] * u[j] + di2[2] * u[j] * u[j] + di2[1] * u[j] + di2[0]) * ctrlpts[i - 2].x() + (di3[3] * u[j] * u[j] * u[j] + di3[2] * u[j] * u[j] + di3[1] * u[j] + di3[0]) * ctrlpts[i - 3].x();
                y = (di[3] * u[j] * u[j] * u[j] + di[2] * u[j] * u[j] + di[1] * u[j] + di[0]) * ctrlpts[i].y() + (di1[3] * u[j] * u[j] * u[j] + di1[2] * u[j] * u[j] + di1[1] * u[j] + di1[0]) * ctrlpts[i - 1].y() +
                    (di2[3] * u[j] * u[j] * u[j] + di2[2] * u[j] * u[j] + di2[1] * u[j] + di2[0]) * ctrlpts[i - 2].y() + (di3[3] * u[j] * u[j] * u[j] + di3[2] * u[j] * u[j] + di3[1] * u[j] + di3[0]) * ctrlpts[i - 3].y();
                z = (di[3] * u[j] * u[j] * u[j] + di[2] * u[j] * u[j] + di[1] * u[j] + di[0]) * ctrlpts[i].z() + (di1[3] * u[j] * u[j] * u[j] + di1[2] * u[j] * u[j] + di1[1] * u[j] + di1[0]) * ctrlpts[i - 1].z() +
                    (di2[3] * u[j] * u[j] * u[j] + di2[2] * u[j] * u[j] + di2[1] * u[j] + di2[0]) * ctrlpts[i - 2].z() + (di3[3] * u[j] * u[j] * u[j] + di3[2] * u[j] * u[j] + di3[1] * u[j] + di3[0]) * ctrlpts[i - 3].z();

                // 转换坐标系，逆变换
                //  将B样条曲线从椭圆的局部坐标系变换回世界坐标系
                z = 0;
                double delt = vx.x() * vy.y() * vz.z() + vx.y() * vy.z() * vz.x() + vy.x() * vz.y() * vx.z() - vz.x() * vy.y() * vx.z() - vx.y() * vy.x() * vz.z() - vx.x() * vz.y() * vy.z();
                p.x() = center.x() + (x * vy.y() * vz.z() + vx.y() * vy.z() * z + y * vz.y() * vx.z() - z * vy.y() * vx.z() - vx.y() * y * vz.z() - x * vz.y() * vy.z()) / delt;
                p.y() = center.y() + (vx.x() * y * vz.z() + x * vy.z() * vz.x() + vy.x() * z * vx.z() - vz.x() * y * vx.z() - x * vy.x() * vz.z() - vx.x() * z * vy.z()) / delt;
                p.z() = center.z() + (vx.x() * vy.y() * z + vx.y() * y * vz.x() + vy.x() * vz.y() * x - vz.x() * vy.y() * x - vx.y() * vy.x() * z - vx.x() * vz.y() * y) / delt;

                // 判断交点是否在椭圆上
                if(ell.test_point_tol(p, tol) && ic->test_point_tol(p, tol)) {  // @todo: 耗时
                    intPnts.push_back(p);
                    intT.push_back(u[j]);
                }
            }
            ACIS_DELETE[] STD_CAST u;
        }
    }
    /////////////////////////////////
    // 处理求交结果
    int num_inters = intPnts.size();
    curve_curve_int *head, *end;
    head = end = ZeroInter;

    double param1, param2;
    for(i = 0; i < num_inters; ++i) {
        tmpP = intPnts[i];
        param2 = intT[i];
        param1 = refine_param(ell.param(tmpP), tol);
        end->next = ACIS_NEW curve_curve_int(nullptr, tmpP, param1, param2);
        if(biparallel(bs3_curve_deriv(param2, bs3), ell.eval_direction(param1))) {
            end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_tangent;
        } else {
            end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_normal;
        }
        end = end->next;
    }
    end->next = nullptr;
    num_inters = CurvCurvIntPointReduce(head->next);  // 去重根

    inters = head->next;

    // 销毁数据
    ACIS_DELETE ic;
    ACIS_DELETE head;
    ACIS_DELETE[] ctrlpts;
    ACIS_DELETE[] STD_CAST knots;
    ACIS_DELETE[] STD_CAST weights;
    if(copyed) {
        bs3_curve_delete(bs3);  // 待解偶，存在问题
    }
    return inters;
}

/**
 * @brief 尝试将law_int_cur所代表的law曲线转化为简单的曲线(直线/圆/螺旋线)，若转化失败，返回nullptr
 * @return 转化后的曲线
 * @param law_ic 输入的law_int_cur
 */
curve* law_int_cur_to_curve(intcurve const& law_ic) {
    curve* ret_curv = nullptr;
    int_cur const& ic = law_ic.get_int_cur();
    if(ic.type() == 59) {  // law_int_cur
        intcurve* _law_ic = (intcurve*)&law_ic;
        law* ic_law = _law_ic->law_form();

        SPAtransf* transf = nullptr;
        if(ic_law->isa(TRANSFORM_LAW_ID)) {  // 待解耦，接口未实现
            transform_law* trans_law = static_cast<transform_law*>(ic_law);
            logical iden;
            transf = ACIS_NEW SPAtransf(trans_law->get_trans(iden));  // 待解耦，接口未实现
            char* str_law = trans_law->fsubs()[0]->string();          // 待解耦，接口未实现
            api_str_to_law(str_law, &ic_law);
            ACIS_DELETE[] STD_CAST str_law;
        }

        SPAinterval law_interval = bs3_curve_range(law_ic.cur());
        CURVE* ic_CURVE = simplify_curve_law(ic_law, law_interval);  // 待解耦，接口未实现
        if(ic_CURVE) {
            ret_curv = (curve*)(&(ic_CURVE->equation()));
            // @todo: ic_CURVE是否需要释放
        } else {
            SPAvector hel_axis_dir;
            SPAposition hel_root;
            double hel_pitch, hel_radius;
            logical hel_handed;
            logical law_is_helix = is_helix(ic_law, law_interval, hel_axis_dir, hel_root, hel_pitch, hel_radius, hel_handed);  // 待解耦，接口未实现
            if(law_is_helix) {
                SPAposition start_pos = ic_law->evaluateR_P(law_interval.start_pt());  // 待解耦，接口未实现
                /** @todo: 若公式线对于起点的估计有误差，则可能会出错*/

                SPAposition foot = proj_pt_to_plane(hel_root, start_pos, normalise(hel_axis_dir));
                hel_root = foot;                              // hel_root投影到(start_pt,hel_axis_dir)所在平面的点，作为helix的axis_root
                SPAvector start_disp = start_pos - hel_root;  // 构建start_disp

                ret_curv = ACIS_NEW helix(hel_root, normalise(hel_axis_dir), start_disp, hel_pitch, hel_handed, law_interval);

            } else {
                // 针对 平面螺旋线 或 圆锥螺旋线的处理
                logical ok = TRUE;
                double radius = 0.0;
                bool check_radius = false;
                double pitch = 0.0;
                bool check_taper = false;
                double taper = 0.0;
                logical handness = TRUE;
                double base_z = 0.0;
                if(ic_law->isa(VECTOR_LAW_ID)) {  // 待解耦，接口未实现
                    vector_law* vec_l = static_cast<vector_law*>(ic_law);
                    law* l1 = vec_l->fsub()[0];
                    law* l2 = vec_l->fsub()[1];
                    law* laws[2] = {l1, l2};
                    for(int i = 0; i < 2; ++i) {
                        law* l = laws[i];
                        if(l->isa(TIMES_LAW_ID)) {  // 待解耦，接口未实现
                            times_law* tl = static_cast<times_law*>(l);
                            law* tl_left = tl->fleft();
                            law* tl_right = tl->fright();
                            if(tl_left->isa(NEGATE_LAW_ID)) {  // 待解耦，接口未实现
                                handness = FALSE;
                                negate_law* nl = static_cast<negate_law*>(tl->fleft());
                                tl_left = nl->fsub();
                            }
                            if(tl_left->isa(PLUS_LAW_ID) && ((i == 0 && tl_right->isa(COS_LAW_ID)) || (i == 1 && tl_right->isa(SIN_LAW_ID)))) {  // 待解耦，接口未实现
                                plus_law* pl = static_cast<plus_law*>(tl_left);
                                if(pl->fleft()->isa(CONSTANT_LAW_ID) && pl->fright()->isa(TIMES_LAW_ID)) {  // 待解耦，接口未实现
                                    if(!check_radius) {
                                        radius = ((constant_law*)pl->fleft())->eval(0);
                                        check_radius = true;
                                    } else {
                                        double tmp_radius = ((constant_law*)pl->fleft())->eval(0);
                                        if(fabs(radius - tmp_radius) > SPAresabs) {
                                            ok = FALSE;
                                        }
                                    }
                                    times_law* tl1 = static_cast<times_law*>(pl->fright());
                                    if(tl1->fright()->isa(IDENTITY_LAW_ID)) {  // 待解耦，接口未实现
                                        if(!check_taper) {
                                            taper = tl1->fleft()->eval(0);
                                            check_taper = true;
                                        } else {
                                            double tmp_taper = tl1->fleft()->eval(0);
                                            if(fabs(taper - tmp_taper) > SPAresabs) {
                                                ok = FALSE;
                                            }
                                        }
                                    }
                                }
                            } else {
                                ok = FALSE;
                            }
                        } else {
                            ok = FALSE;
                        }
                    }
                    law* l3 = vec_l->fsub()[2];
                    if(l3->isa(CONSTANT_LAW_ID)) {  // 待解耦，接口未实现
                        pitch = 0.0;
                        base_z = l3->eval(0);
                    } else if(l3->isa(TIMES_LAW_ID)) {  // 待解耦，接口未实现
                        times_law* tl = static_cast<times_law*>(l3);
                        if(tl->fleft()->isa(CONSTANT_LAW_ID) && tl->fright()->isa(IDENTITY_LAW_ID)) {  // 待解耦，接口未实现
                            pitch = tl->fleft()->eval(0);
                        }
                    } else {
                        ok = FALSE;
                    }
                } else {
                    ok = FALSE;
                }
                // 构造曲线
                if(ok) {
                    SPAposition hel_root(0, 0, base_z);
                    SPAunit_vector hel_normal(0, 0, 1);
                    SPAvector hel_start = SPAvector(1, 0, 0) * radius;
                    ret_curv = ACIS_NEW helix(hel_root, hel_normal, hel_start, pitch * 2 * M_PI, handness, law_interval, 1.0, taper * 2 * M_PI);
                } else {
                    ret_curv = nullptr;
                }
            }
        }
        if(transf && ret_curv) {
            (*ret_curv) *= (*transf);
        }
        if(transf) {
            ACIS_DELETE transf;
        }
        if(ic_law) {
            ic_law->remove();
        }
    }
    return ret_curv;
}

/**
 * @brief 将有理Bezier曲线curve 分裂为四条子曲线，保存于rcurve中
 */
void SubdRbezcToNCurve(bs3_curve rbezier, bs3_curve sub_rbezier[]) {
    bs3_curve tmp1 = nullptr;
    bs3_curve tmp2 = bs3_curve_copy(rbezier);

    bs3_curve_set_open(tmp2);
    tmp1 = bs3_curve_split(tmp2, 0.5);
    bs3_curve_reparam(0, 1, tmp1);
    bs3_curve_reparam(0, 1, tmp2);

    sub_rbezier[0] = bs3_curve_split(tmp1, 0.5);
    sub_rbezier[1] = tmp1;

    sub_rbezier[2] = bs3_curve_split(tmp2, 0.5);
    sub_rbezier[3] = tmp2;

    for(int i = 0; i < 4; ++i) {
        bs3_curve_reparam(0, 1, sub_rbezier[i]);
    }
}

void NurbscMultiSplit(bs3_curve nurbs, int n, double t[], bs3_curve sub_nurbs[]) {
    bs3_curve nurbs_copy = bs3_curve_copy(nurbs);
    bs3_curve_set_open(nurbs_copy);
    int degree = bs3_curve_degree(nurbs_copy);
    for(int i = 0; i < n; ++i) {
        bs3_curve_add_knot(nurbs_copy, t[i], degree, SPAresabs);  // 插入多重节点
    }
    sub_nurbs[0] = bs3_curve_split(nurbs_copy, t[0]);
    for(int i = 1; i < n; i++) {
        sub_nurbs[i] = bs3_curve_split(nurbs_copy, t[i]);
    }
    sub_nurbs[n] = nurbs_copy;
}

int NurbscToRBezier(bs3_curve nurbs, bs3_curve*& rbezier, double*& t) {
    int i = 0, k = 0;
    int number = bs3_curve_num_ctlpts(nurbs);
    int order = bs3_curve_degree(nurbs) + 1;
    int bez_num = number - order + 1;  // 曲线段数
    double* knots = nullptr;
    bs3_curve_knots(nurbs, k, knots);
    if(bez_num == 1) {
        rbezier = ACIS_NEW bs3_curve[1];
        // 为bezier赋予空间
        t = nullptr;
        rbezier[0] = bs3_curve_copy(nurbs);
        bs3_curve_reparam(0, 1, rbezier[0]);
        ACIS_DELETE[] STD_CAST knots;
        knots = nullptr;
        return bez_num;
    }
    t = ACIS_NEW double[bez_num - 1];
    for(k = 0; k <= bez_num - 2; k++) {
        if(fabs(knots[order + k] - knots[order - 1]) > SPAresabs) {
            break;
        }
    }
    int temp = 1;
    t[0] = knots[order + k];
    for(i = k + 1; i <= bez_num - 2; i++) {
        if(fabs(knots[order + i] - t[temp - 1]) > SPAresabs) {
            t[temp] = knots[order + i];
            temp++;
        }
    }
    bez_num = temp + 1;
    bs3_curve* sub_nurbs = ACIS_NEW bs3_curve[bez_num];
    NurbscMultiSplit(nurbs, bez_num - 1, t, sub_nurbs);

    // 处理split后为nullptr的bezier曲线,并调整
    int new_bez_num = 0;
    for(int i = 0; i < bez_num; ++i) {
        if(sub_nurbs[i]) {
            if(i != bez_num - 1) {
                t[new_bez_num++] = t[i];
            } else {
                new_bez_num++;
            }
        }
    }
    bez_num = new_bez_num;

    // 为beizer数组赋予空间
    rbezier = ACIS_NEW bs3_curve[bez_num];
    // 填 rbezier[i] 结构
    for(i = 0; i < bez_num; i++) {
        rbezier[i] = sub_nurbs[i];
        bs3_curve_reparam(0, 1, rbezier[i]);
        sub_nurbs[i] = nullptr;
    }

    ACIS_DELETE[] sub_nurbs;
    ACIS_DELETE[] STD_CAST knots;
    sub_nurbs = nullptr;
    knots = nullptr;
    return bez_num;
}

/**
 * @brief Nurbs曲线细分，转化为控制多边形点数组
 * @param curv 输入的Nurbs曲线
 * @param points 输出的控制多变形点数组
 * @param splitpara [splitpara[i], splitpara[i+1]]为两个控制点在曲线的近似参数区间
 * @param num_points 输出的控制多边形点数组的点的个数
 */
void NurbsSubdivision(bs3_curve curv, SPAposition*& points, double*& splitpara, int& num_points) {
    if(curv == nullptr) {
        points = nullptr;
        num_points = 0;
        return;
    }
    SPAinterval param_range = bs3_curve_range(curv);
    int degree = bs3_curve_degree(curv);
    int num_ctrlpts = bs3_curve_num_ctlpts(curv);
    int max_segs = num_ctrlpts - degree + 1;
    // 将nurbs曲线转化为多段Rbezier曲线
    bs3_curve* rbeziers = nullptr;
    double* split_paras = nullptr;
    int num_rbeziers = NurbscToRBezier(curv, rbeziers, split_paras);

    points = ACIS_NEW SPAposition[max_segs * 4 * (degree + 1)];
    splitpara = ACIS_NEW double[max_segs * 4 * (degree + 1)];
    num_points = 0;
    for(int i = 0; i < num_rbeziers; ++i) {
        bs3_curve sub_rbeziers[4];
        double start = i ? split_paras[i - 1] : param_range.start_pt();
        double end = i < num_rbeziers - 1 ? split_paras[i] : param_range.end_pt();
        SubdRbezcToNCurve(rbeziers[i], sub_rbeziers);
        for(int j = 0; j < 4; ++j) {
            double sub_start = start + (end - start) * j / 4;
            double sub_end = sub_start + (end - start) / 4;
            SPAposition* control_points = nullptr;
            int num_pts = 0;
            bs3_curve_control_points(sub_rbeziers[j], num_pts, control_points);
            for(int k = 0; k < num_pts - 1; ++k) {
                splitpara[num_points] = sub_start + (sub_end - sub_start) * k / (num_pts - 1);
                points[num_points++] = control_points[k];
            }
            if(i == num_rbeziers - 1 && j == 3) {
                splitpara[num_points] = sub_end;
                points[num_points++] = control_points[num_pts - 1];
            }
            ACIS_DELETE[] control_points;
            control_points = nullptr;
            bs3_curve_delete(sub_rbeziers[j]);  // 待解耦，存在问题 @todo: bs3_curve相关问题
            sub_rbeziers[j] = nullptr;
        }
        bs3_curve_delete(rbeziers[i]);
        rbeziers[i] = nullptr;
    }
    ACIS_DELETE[] STD_CAST split_paras;
    ACIS_DELETE[] rbeziers;
    split_paras = nullptr;
    rbeziers = nullptr;
}

/** 使用最优化方法求cur1和cur2的最近点对  */
double MinDistancePointPair_Impl(curve const& cur1, curve const& cur2, Vector<2> const& vec0, SPAposition& pt1, SPAposition& pt2, int maxiter) {
    std::vector<void const*> params = {&cur1, &cur2};
    Vector<2> output = minimize(distanceF, vec0, params, 1e-12, maxiter);

    pt1 = cur1.eval_position(output(0, 0));
    pt2 = cur2.eval_position(output(1, 0));
    return distance_to_point(pt1, pt2);
}

/** 使用最优化方法求cur1和cur2的最近点对  */
double cur1_cur2_MinDistancePointPair_Impl(curve const& cur1, curve const& cur2, Vector<2> const& vec0, SPAposition& pt1, SPAposition& pt2, int maxiter) {
    maxiter = 100;
    Vector<2> output = vec0;
    double dis, dis_to_cur1, dis_to_cur2;
    while(maxiter--) {
        SPAposition p1, p2;
        SPAvector u1, v1, u2, v2;
        cur1.eval(output(0, 0), p1, u1, u2);
        cur2.eval(output(1, 0), p2, v1, v2);
        double Hessian[2][2], grad[2], inverse_Hessian[2][2], delta;
        Hessian[0][0] = 2 * u1 % u1 + 2 * (p1 - p2) % u2;
        Hessian[0][1] = -2 * u1 % v1;
        Hessian[1][0] = -2 * u1 % v1;
        Hessian[1][1] = 2 * v1 % v1 + 2 * (p1 - p2) % v2;
        grad[0] = 2 * (p1 - p2) % u1;
        grad[1] = -2 * (p1 - p2) % v1;
        delta = Hessian[0][0] * Hessian[1][1] - Hessian[0][1] * Hessian[1][0];
        if(fabs(delta) == 0) break;
        inverse_Hessian[0][0] = Hessian[1][1] / delta;
        inverse_Hessian[0][1] = -Hessian[0][1] / delta;
        inverse_Hessian[1][0] = -Hessian[1][0] / delta;
        inverse_Hessian[1][1] = Hessian[0][0] / delta;
        output(0, 0) = output(0, 0) - (inverse_Hessian[0][0] * grad[0] + inverse_Hessian[0][1] * grad[1]);
        output(1, 0) = output(1, 0) - (inverse_Hessian[1][0] * grad[0] + inverse_Hessian[1][1] * grad[1]);
        if(fabs((inverse_Hessian[0][0] * grad[0] + inverse_Hessian[0][1] * grad[1])) < 1e-7 && fabs(inverse_Hessian[1][0] * grad[0] + inverse_Hessian[1][1] * grad[1]) < 1e-7) {
            break;
        }
    }
    pt1 = cur1.eval_position(output(0, 0));
    pt2 = cur2.eval_position(output(1, 0));
    dis = distance_to_point(pt1, pt2);
    return dis;
}

// 定义二元目标函数
Vector<2> objF(Vector<2> const& input, std::vector<void const*> const& params) {
    curve const* cur1 = static_cast<curve const*>(params[0]);
    curve const* cur2 = static_cast<curve const*>(params[1]);

    double u = input(0, 0), v = input(1, 0);
    SPAvector dis_vec = cur1->eval_position(u) - cur2->eval_position(v);
    return Vector<2>({dis_vec % cur1->eval_deriv(u), -dis_vec % cur2->eval_deriv(v)});
}

// 定义二元距离函数
double distanceF(Vector<2> const& input, std::vector<void const*> const& params) {
    curve const* cur1 = static_cast<curve const*>(params[0]);
    curve const* cur2 = static_cast<curve const*>(params[1]);
    SPAvector distance_vec = cur1->eval_position(input(0, 0)) - cur2->eval_position(input(1, 0));
    return 0.5 * distance_vec.len_sq();
}

// 直线椭圆求交牛顿迭代求精接口
void Newton_str_ell(straight const& str, ellipse const& ell, SPAposition& int_point, double& param_str, double& param_ell, int maxiter) {
    double sint, cost;
    double Hessian[2][2], grad[2], inverse_Hessian[2][2], delta;
    SPAvector r;
    // maxiter = 5;
    while(maxiter--) {
        sint = std::clamp(sin(param_ell), -1.0, 1.0);
        cost = std::clamp(cos(param_ell), -1.0, 1.0);
        r = str.eval_position(param_str) - ell.eval_position(param_ell);
        grad[0] = 2 * r % str.direction * str.param_scale;
        grad[1] = 2 * r % (ell.major_axis * sint - ell.minor_axis * cost);
        if(grad[0] * grad[0] + grad[1] * grad[1] < 1e-8) break;
        Hessian[0][0] = 2 * str.direction.len_sq() * str.param_scale;
        Hessian[0][1] = 2 * (ell.major_axis * sint - ell.minor_axis * cost) % str.direction * str.param_scale;
        Hessian[1][0] = 2 * (ell.major_axis * sint - ell.minor_axis * cost) % str.direction * str.param_scale;
        Hessian[1][1] = 2 * (ell.major_axis * sint - ell.minor_axis * cost) % (ell.major_axis * sint - ell.minor_axis * cost) + 2 * r % (ell.major_axis * cost + ell.minor_axis * sint);
        delta = Hessian[0][0] * Hessian[1][1] - Hessian[0][1] * Hessian[1][0];
        // if(!is_valid_divisor(delta)) break;
        if(fabs(delta) == 0) break;
        inverse_Hessian[0][0] = Hessian[1][1] / delta;
        inverse_Hessian[0][1] = -Hessian[0][1] / delta;
        inverse_Hessian[1][0] = -Hessian[1][0] / delta;
        inverse_Hessian[1][1] = Hessian[0][0] / delta;
        param_str = param_str - (inverse_Hessian[0][0] * grad[0] + inverse_Hessian[0][1] * grad[1]);
        param_ell = param_ell - (inverse_Hessian[1][0] * grad[0] + inverse_Hessian[1][1] * grad[1]);
    }
    // int_point = mid_point(str.eval_position(param_str), ell.eval_position(param_ell));
    int_point = str.eval_position(param_str);
    // int_point = ell.eval_position(param_ell);
}

// 定义二元Jacob矩阵
Matrix<2, 2> Jacobin(Vector<2> const& input, std::vector<void const*> const& params) {
    curve const* cur1 = static_cast<curve const*>(params[0]);
    curve const* cur2 = static_cast<curve const*>(params[1]);

    double u = input(0, 0), v = input(1, 0);
    SPAvector dis_vec = cur1->eval_position(u) - cur2->eval_position(v);
    double duu = cur1->eval_deriv(u).len_sq() + dis_vec % cur1->eval_curvature(u);
    double duv = -cur1->eval_deriv(u) % cur2->eval_deriv(v);
    double dvu = duv;
    double dvv = cur2->eval_deriv(v).len_sq() + dis_vec % cur2->eval_curvature(v);
    return Matrix<2, 2>({duu, duv, dvu, dvv});
}

/**
 * @brief 曲线cur和面交线计算重合段，输入cur在面交线所在两个面的重合区间，返回cur与面交线实际的重合区间(在cur上的参数区间)
 * @return 实际的重合段(在cur上的参数区间)
 * @param cur 输入曲线
 * @param iic 输入面交线
 * @param int1 输入曲线cur与面交线的第一个面重合的区间
 * @param int2 输入曲线cur与面交线的第二个面重合的区间
 */
std::vector<SPAinterval> int_int_cur_coin_detect(curve const& cur, intcurve const& iic, std::vector<SPAinterval> const& int1, std::vector<SPAinterval> const& int2) {
    SPAinterval coin_int;
    std::vector<SPAinterval> coin_int_array;
    SPAbox iic_box = bs3_curve_box(iic.cur(), 0);
    SPAinterval iic_range = bs3_curve_range(iic.cur());
    for(int i = 0; i < int1.size(); ++i) {
        for(int j = 0; j < int2.size(); ++j) {
            coin_int = int1[i] & int2[j];
            if(coin_int.end_pt() - coin_int.start_pt() > SPAresabs) {
                // 判断coin_int与面交线iic是否重合
                bs3_curve bs3_coin = bs3_curve_make_cur(cur, coin_int.start_pt(), coin_int.end_pt());
                if(bs3_curve_box(bs3_coin, 0) && iic_box) {
                    // coin_int与面交线的包围盒重合
                    std::vector<SPAinterval> coin_ints = get_coincident_segment(cur, iic, coin_int, iic_range);
                    for(int i = 0; i < coin_ints.size(); ++i) {
                        coin_int_array.push_back(coin_ints[i]);
                    }
                }
                bs3_curve_delete(bs3_coin);
                // ACIS的bs3_curve_delete处理bs3_curve_make_cur会在release下抛异常spaacis/src:BAD_DISCARD_SIZE
            } else if(fabs(coin_int.end_pt() - coin_int.start_pt()) <= SPAresabs) {
                // 重合于一点
                // 判断该点是否在面交线上
                if(iic.test_point_tol(cur.eval_position(coin_int.mid_pt()), SPAresabs)) {
                    coin_int_array.push_back(coin_int);
                }
            }
        }
    }
    return coin_int_array;
}

/**
 * @brief 检测两个椭圆是否重合
 * @return  重合标志，true表示重合，false表示不重合
 * @param cci_ellipse1 输入椭圆1
 * @param cci_ellipse2 输入椭圆2
 */
bool ellipse_ellipse_coin_detect(ellipse const& cci_ellipse1, ellipse const& cci_ellipse2) {
    ////取点法
    // cci_ellipse2.minor_axis = cci_ellipse2.normal * cci_ellipse2.major_axis * cci_ellipse2.radius_ratio;
    // ellipse* ell1 = (ellipse*)cci_ellipse1.unsubset();
    // ellipse* ell2 = (ellipse*)cci_ellipse2.unsubset();
    // double param1_st = -M_PI, param1_ed = M_PI;
    // SPAposition p1(0, 0, 0), p2(0, 0, 0);
    // double distance = 0.0;
    // double param1 = 0.0, param2 = 0.0;
    // curve_curve_int* inters = nullptr;
    // for(int i = 1; i < 6; i++) {
    //     param1 = i * param1_st / 6 + (6 - i) * param1_ed / 6;
    //     p1 = ell1->eval_position(param1);
    //     param2 = ell2->param(p1);
    //     p2 = ell2->eval_position(param2);
    //     distance = distance_to_point(p1, p2);
    //     if(distance > 10 * SPAresabs) return false;
    //     // if(!ell2->test_point_tol(p1)) return false;
    // };
    // return true;
    // 对比轴线法(前提是共面下)
    if(fabs(cci_ellipse1.radius_ratio - 1.0) <= SPAresabs && fabs(cci_ellipse2.radius_ratio - 1.0) <= SPAresabs) {
        // 圆圆重合判断
        double a = cci_ellipse1.major_axis.len() - cci_ellipse2.major_axis.len();
        if(same_point(cci_ellipse1.centre, cci_ellipse2.centre) && is_zero(fabs(cci_ellipse1.major_axis.len() - cci_ellipse2.major_axis.len()))) {
            return true;
        }
    } else {
        // 椭圆椭圆重合判断
        if(same_point(cci_ellipse1.centre, cci_ellipse2.centre, SPAresfit)) {
            bool same_major = same_vector(cci_ellipse1.major_axis, cci_ellipse2.major_axis, SPAresfit) || same_vector(cci_ellipse1.major_axis, -cci_ellipse2.major_axis, SPAresfit);
            double ratio_diff = fabs(cci_ellipse1.radius_ratio - cci_ellipse2.radius_ratio);
            if(same_major && is_zero(ratio_diff)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 构造两个重合(椭)圆的求交结果类
 * @return 线线求交结果类
 * @param cci_ellipse1 输入椭圆1
 * @param cci_ellipse2 输入椭圆2
 * @param box 包围盒
 * @param tol 容差
 */
curve_curve_int* ellipse_ellipse_coin(ellipse const& cci_ellipse1, ellipse const& cci_ellipse2, SPAbox const& box, double tol) {
    curve_curve_int *coin_head, *coin_end;
    coin_head = coin_end = ZeroInter;
    SPAposition int_point_st, int_point_ed, int_point;
    double pa1_st, pa1_ed, pa2_st, pa2_ed, pa1, pa2;
    std::vector<SPAinterval> param2_array;   // 存放ellipse2在ellipse1上的对应多段参数区间
    std::vector<SPAinterval> overlap_array;  // 存放ellipse1和ellipse2的多段重合区间
    SPAinterval overlap1, overlap2, overlap;
    double param1_st = cci_ellipse1.param_range().start_pt();
    double param1_ed = cci_ellipse1.param_range().end_pt();
    double param2_st = cci_ellipse2.param_range().start_pt();
    double param2_ed = cci_ellipse2.param_range().end_pt();
    double param2_0 = cci_ellipse1.param(cci_ellipse2.eval_position(param2_st));
    double param2_1 = cci_ellipse1.param(cci_ellipse2.eval_position(param2_ed));
    bool same_normal = is_equal(cci_ellipse1.normal, cci_ellipse2.normal);
    bool same_major = cci_ellipse1.major_axis % cci_ellipse2.major_axis > 0 ? true : false;
    if(!same_normal) std::swap(param2_0, param2_1);  // 法向量相反时，区间为reverse
    //(param1_st,param1_ed)(param2_0,param2_1)取交
    SPAinterval interval1(param1_st, param1_ed);
    if(param2_0 >= param2_1 - SPAresnor) param2_1 += 2 * M_PI;
    auto Inrange = [&param1_st, &param1_ed](const double& res) { return res >= (param1_st - SPAresnor) && res <= (param1_ed + SPAresnor); };
    if(!Inrange(param2_0)) {
        while(param2_0 < param1_st - SPAresnor) {
            param2_0 += 2 * M_PI;
        }
        while(param2_0 > param1_ed + SPAresnor) {
            param2_0 -= 2 * M_PI;
        }
    }
    if(!Inrange(param2_0)) param2_0 += 2 * M_PI;
    if(param2_0 >= param2_1 - SPAresnor) param2_1 += 2 * M_PI;
    SPAinterval interval2(interval_type::interval_finite, param2_0, param2_1);  // 左端点在ellipse1参数区间内
    param2_array.push_back(interval2);
    overlap1 = interval1 & interval2;
    interval2 -= 2 * M_PI;  // 右端点在ellipse1参数区间内，确保不丢
    overlap2 = interval1 & interval2;
    if(!overlap1.empty()) overlap_array.push_back(overlap1);
    if(!overlap2.empty() && !(overlap2 << overlap1)) overlap_array.push_back(overlap2);
    for(auto overlap: overlap_array) {
        if(overlap.end_pt() - overlap.start_pt() > SPAresnor) {
            pa1_st = overlap.start_pt();
            int_point_st = cci_ellipse1.eval_position(pa1_st);
            pa2_st = cci_ellipse2.param(int_point_st);
            pa1_ed = overlap.end_pt();
            int_point_ed = cci_ellipse1.eval_position(pa1_ed);
            pa2_ed = cci_ellipse2.param(int_point_ed);
            if(is_zero(fabs(pa2_ed - pa2_st))) {
                if(same_normal && same_major) {
                    pa2_ed += 2 * M_PI;
                } else {
                    pa2_ed -= 2 * M_PI;
                }
            }
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point_st, pa1_st, pa2_st);
            coin_end->next->low_rel = curve_curve_rel::cur_cur_unknown;
            coin_end->next->high_rel = curve_curve_rel::cur_cur_coin;
            coin_end = coin_end->next;
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point_ed, pa1_ed, pa2_ed);
            coin_end->next->low_rel = curve_curve_rel::cur_cur_coin;
            coin_end->next->high_rel = curve_curve_rel::cur_cur_unknown;
            coin_end = coin_end->next;
        } else if(fabs(overlap.end_pt() - overlap.start_pt()) <= SPAresnor) {
            pa1 = overlap.mid_pt();
            int_point = cci_ellipse1.eval_position(pa1);
            pa2 = cci_ellipse2.param(int_point);
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point, pa1, pa2);
            if(biparallel(cci_ellipse1.point_direction(int_point), cci_ellipse2.point_direction(int_point))) {
                coin_end->next->low_rel = coin_end->next->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                coin_end->next->low_rel = coin_end->next->high_rel = curve_curve_rel::cur_cur_normal;
            }
            coin_end = coin_end->next;
        }
    }
    curve_curve_int* coin_inters = coin_head->next;
    ACIS_DELETE coin_head;
    return coin_inters;
}

/**
 * @brief 根据重合的参数区间(cur1上的参数区间)构造线线求交结果类
 * @return 线线求交结果类
 * @param cur1 输入曲线1
 * @param cur2 输入曲线2
 * @param coin_int_array 重合段在cur1上的参数区间
 */
curve_curve_int* construct_coin_inters(curve const& cur1, curve const& cur2, std::vector<SPAinterval> const& coin_int1_array, std::vector<std::pair<double, double>> const& coin_int2_array) {
    curve_curve_int *coin_head, *coin_end;
    coin_head = coin_end = ZeroInter;
    double param1, param2, param2_st, param2_ed;
    SPAposition int_point;
    for(int i = 0; i < coin_int1_array.size(); ++i) {
        if(coin_int1_array[i].end_pt() - coin_int1_array[i].start_pt() > SPAresabs) {
            if((&coin_int2_array) && i < coin_int2_array.size()) {
                param2_st = coin_int2_array[i].first;
                param2_ed = coin_int2_array[i].second;
            } else {
                bool reversed = false;
                auto range2 = std::move(recompute_param_range(coin_int1_array[i], &cur1, &cur2, SPAresabs, reversed));
                param2_st = range2.start_pt(), param2_ed = range2.end_pt();
                if(reversed) {
                    std::swap(param2_st, param2_ed);
                }
            }

            param1 = coin_int1_array[i].start_pt();
            int_point = cur1.eval_position(param1);
            param2 = param2_st;  // 待解耦，存在问题 @todo: intcurve相关问题
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point, param1, param2);
            coin_end->next->low_rel = curve_curve_rel::cur_cur_unknown;
            coin_end->next->high_rel = curve_curve_rel::cur_cur_coin;
            coin_end = coin_end->next;

            param1 = coin_int1_array[i].end_pt();
            int_point = cur1.eval_position(param1);
            param2 = param2_ed;  // 待解耦，存在问题 @todo: intcurve相关问题 NurbsNurbsIntrTest.TestBug30
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point, param1, param2);
            coin_end->next->low_rel = curve_curve_rel::cur_cur_coin;
            coin_end->next->high_rel = curve_curve_rel::cur_cur_unknown;
            coin_end = coin_end->next;
        } else if(fabs(coin_int1_array[i].end_pt() - coin_int1_array[i].start_pt()) <= SPAresabs) {
            param1 = coin_int1_array[i].mid_pt();
            int_point = cur1.eval_position(param1);
            double param2 = 0.0;
            if((&coin_int2_array) && i < coin_int2_array.size()) {
                param2 = 0.5 * (coin_int2_array[i].first + coin_int2_array[i].second);
            } else {
                param2 = cur2.param(int_point);
            }
            coin_end->next = ACIS_NEW curve_curve_int(nullptr, int_point, param1, param2);
            if(biparallel(cur1.point_direction(int_point), cur2.point_direction(int_point))) {
                coin_end->next->low_rel = coin_end->next->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                coin_end->next->low_rel = coin_end->next->high_rel = curve_curve_rel::cur_cur_normal;
            }
            coin_end = coin_end->next;
        }
    }
    curve_curve_int* coin_inters = coin_head->next;
    ACIS_DELETE coin_head;
    return coin_inters;
}

curve_curve_int* construct_coin_inters(curve const& cur1, curve const& cur2, int num_arr, SPAinterval* coin_int_array) {
    std::vector<SPAinterval> coin_vector;
    for(int i = 0; i < num_arr; ++i) {
        coin_vector.push_back(coin_int_array[i]);
    }
    return construct_coin_inters(cur1, cur2, coin_vector);
}

/**
 * @brief 判断nurbs曲线的节点向量重数是否大于degree+1
 * @return TRUE:nurbs曲线节点向量重数异常, FALSE:无异常
 * @param curv 输入曲线
 */
logical illegal_knot_mul(bs3_curve curv) {
    if(!curv) {
        return TRUE;
    }
    double* knots = nullptr;
    int num_knots = 0;
    double knot_tol = bs3_curve_knottol();  // 待解耦，接口未实现
    bs3_curve_knots(curv, num_knots, knots);
    int degree = bs3_curve_degree(curv);  // 待解耦，访问冲突

    logical error_knot_mults = FALSE;
    for(int i = 0; i < num_knots; ++i) {
        if(bs3_curve_knot_mult(curv, knots[i], knot_tol) > degree + 1) {  // @todo: 耗时较长
            error_knot_mults = TRUE;
            break;
        }
    }
    ACIS_DELETE[] STD_CAST knots;
    return error_knot_mults;
}

/**
 * @brief 判断曲线的端点是否在另一个曲线上，若在其上，构造交点结果
 * @return 交点结果
 * @param cur1 曲线1
 * @param cur2 曲线2
 */
curve_curve_int* judge_curve_ends(curve const& cur1, curve const& cur2) {
    curve_curve_int *pre = nullptr, *ret = nullptr;
    SPAinterval param_range1, param_range2;
    SPAposition point;
    if(!cur1.periodic()) {
        param_range1 = cur1.param_range();  // 待解偶，存在问题
        point = cur1.eval_position(param_range1.start_pt());
        if(cur2.test_point_tol(point)) {
            ret = ACIS_NEW curve_curve_int(pre, point, param_range1.start_pt(), cur2.param(point));
            pre = ret;
        }
        point = cur1.eval_position(param_range1.end_pt());
        if(cur2.test_point_tol(point)) {
            ret = ACIS_NEW curve_curve_int(pre, point, param_range1.end_pt(), cur2.param(point));
            pre = ret;
        }
    }
    if(!cur2.periodic()) {
        // @todo: 未解耦08.29
        param_range2 = cur2.param_range();  // 待解偶，存在问题
        point = cur2.eval_position(param_range2.start_pt());
        if(cur1.test_point_tol(point)) {  // @todo: 存在内存泄漏问题
            ret = ACIS_NEW curve_curve_int(pre, point, cur1.param(point), param_range2.start_pt());
            pre = ret;
        }
        point = cur2.eval_position(param_range2.end_pt());
        if(cur1.test_point_tol(point)) {  // @todo: 存在内存泄漏问题
            ret = ACIS_NEW curve_curve_int(pre, point, cur1.param(point), param_range2.end_pt());
            pre = ret;
        }
    }
    pre = ret;
    while(pre) {
        if(parallel(cur1.point_direction(pre->int_point), cur2.point_direction(pre->int_point))) {  // 待解耦 @todo: NurbsNurbsIntrTest.TestBug77
            pre->low_rel = pre->high_rel = curve_curve_rel::cur_cur_tangent;
        } else {
            pre->low_rel = pre->high_rel = curve_curve_rel::cur_cur_normal;
        }
        pre = pre->next;
    }
    return ret;
}

/**
 * @brief 拟合法求平面螺旋线和nurbs曲线求交，返回求交结果
 * @return 交点结果
 * @param hel 平面螺旋线
 * @param bs3 nurbs曲线
 */
curve_curve_int* fit_coplnar_helix_nurbs_int(helix const& hel, bs3_curve bs3) {
    SPAinterval interval = hel.param_range();
    double actual_tol = 0.0;
    // @todo: bs3_curve_make_cur函数未解耦:该函数统一解耦
    bs3_curve curv = bs3_curve_make_cur(hel, interval.start_pt(), interval.end_pt(), 0, actual_tol);
    curve_curve_int* ret = nullptr;
#ifdef USE_CURVE_TO_BS3_CURVE
    if(!curv || fabs(actual_tol) > SPAresabs) {
        bs3_curve_delete(curv);
        curv = curve_to_bs3_curve(&hel, interval, SPAresabs, actual_tol);
    }
#endif
    if(curv) {
        exact_int_cur* cur = ACIS_NEW exact_int_cur(curv);
        intcurve* ic_helix = ACIS_NEW intcurve(cur);
        // curve_curve_int* ret = int_cur_cur(*ic, bs3, box, tol);
        intcurve* ic2 = make_exact_intcurve(bs3);
        ret = int_cur_cur(*ic_helix, *ic2);

        ACIS_DELETE ic_helix;
        ic2->set_cur(nullptr, -1, FALSE);
        ACIS_DELETE ic2;
    }
    return ret;
}

/**
 * @brief MAF迭代法求平面螺旋线和nurbs曲线求交，返回求交结果
 */
curve_curve_int* maf_coplnar_helix_bs3_int(helix const& hel, intcurve const& ic, SPAinterval const& range) {
    bs3_curve bs3 = bs3_curve_split_interval(ic.cur(), range.start_pt(), range.end_pt());
    if(!bs3) {
        return nullptr;
    }
    if(ic.reversed()) {
        bs3_curve_reverse(bs3);
    }
    curve_curve_int* interp = nullptr;
    SPAposition* points = nullptr;
    int num_points = 0;
    double* splitpara = nullptr;
    NurbsSubdivision(bs3, points, splitpara, num_points);
    curve_curve_int *head, *end;
    head = end = ZeroInter;

    // 求近似交点
    for(int i = 0; i < num_points - 1; ++i) {
        double dis = distance_to_point(points[i], points[i + 1]);
        straight lineseg(points[i], normalise(points[i + 1] - points[i]));
        lineseg.limit(SPAinterval(0, dis));

        end->next = int_cur_cur(hel, lineseg);

        double st = splitpara[i];
        double ed = splitpara[i + 1];
        // 确定近似交点的参数
        while(end->next) {
            end->next->param2 = st * (distance_to_point(end->next->int_point, points[i + 1]) / dis) + ed * (distance_to_point(end->next->int_point, points[i]) / dis);
            end = end->next;
        }
    }
    end->next = nullptr;
    interp = head->next;

    // MAF迭代求精
    curve_curve_int* ret = nullptr;

#ifdef INTERSECTOR_INTCUCU_NOINTINTCUR
    curve_curve_maf(hel, ic, interp, ret, 300, TRUE);
#else
    curve_curve_maf(hel, ic, interp, ret, 300, FALSE);

    curve_curve_int* ret1 = nullptr;
    curve_nurbs_iterate(hel, bs3, interp, ret1);

    if(ret1) {
        curve_curve_int* ret1_end = ret1;
        while(ret1_end->next) {
            ret1_end = ret1_end->next;
        }
        ret1_end->next = ret;
        ret = ret1;
        CurvCurvIntPointReduce(ret);
    }
#endif

    delete_curve_curve_ints(interp);
    bs3_curve_delete(bs3);
    ACIS_DELETE head;
    ACIS_DELETE[] points;
    ACIS_DELETE[] STD_CAST splitpara;

    return ret;
}

// 直线-nurbs曲线 迭代求交
void line_nurbs_iterate(straight const& st, bs3_curve nurbs, curve_curve_int* near_result, curve_curve_int*& refine_result) {
    // 只能处理二次相切，不能处理三次相切
    curve_curve_int* ret = nullptr;
    curve_curve_int *head, *end;
    head = end = ZeroInter;

    SPAposition root = st.root_point;
    SPAunit_vector dir = st.direction;
    int inters_num = 0;  // 精确交点个数
    SPAinterval range_nurbs = bs3_curve_range(nurbs);
    while(near_result) {
        int iter_num = 0;
        while(iter_num < 300) {
            if(near_result->param2 > range_nurbs.end_pt()) near_result->param2 = range_nurbs.end_pt();
            if(near_result->param2 < range_nurbs.start_pt()) near_result->param2 = range_nurbs.start_pt();
            SPAvector cur = bs3_curve_curvature(near_result->param2, nurbs);
            SPAvector deriv = bs3_curve_deriv(near_result->param2, nurbs);
            SPAposition pos = bs3_curve_position(near_result->param2, nurbs);

            SPAposition pos_st = st.eval_position(near_result->param1);
            SPAvector r = pos - pos_st;
            double f = r % deriv;
            double g = r % dir;

            // if(distance_to_point(pos_st, pos) <= 1e-12) {
            //     // Point Coincidence
            //     break;
            // }
            // if(perpendicular(r, deriv) && perpendicular(r, dir)) {
            //     // Perpendicularity
            //     break;
            // }

            double J11 = deriv.len_sq() + r % cur;
            double J12 = -dir % deriv;
            double J21 = dir % deriv;
            double J22 = -dir % dir;

            double base = J11 * J22 - J12 * J21;

            if(fabs(base) <= 1e-16) {
                break;
            }

            double dt2 = (J12 * g - J22 * f) / base;
            double dt1 = -(J11 * g - J21 * f) / base;

            if(fabs(dt1) <= 1e-16 && fabs(dt2) <= 1e-16) {
                break;
            }

            near_result->param1 += dt1;
            near_result->param2 += dt2;

            ++iter_num;
        }
        if(iter_num < 300) {
            // 收敛
            SPAposition cp1 = st.eval_position(near_result->param1);
            SPAposition cp2 = bs3_curve_position(near_result->param2, nurbs);
            SPAvector deriv = bs3_curve_deriv(near_result->param2, nurbs);
            // @todo:test_point_tol函数未解耦：耗时过长暂不解耦
            if(bs3_curve_testpt(cp1, SPAresabs, nurbs) && st.test_point_tol(cp2)) {
                ++inters_num;
                end->next = ACIS_NEW curve_curve_int(nullptr, mid_point(cp1, cp2), near_result->param1, near_result->param2);
                double angle = VEC_acute_angle(deriv, dir);
                // 部分用例 biparallel通不过，通过计算夹角判断相切
                if(fabs(angle) <= 1e-7) {
                    end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_tangent;
                } else {
                    end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_normal;
                }
                end = end->next;
            }
        }
        near_result = near_result->next;
    }
    ret = head->next;
    inters_num = CurvCurvIntPointReduce(ret);
    ACIS_DELETE head;
    refine_result = ret;
}

// curve-nurbs曲线 迭代求交
void curve_nurbs_iterate(curve const& curv, bs3_curve nurbs, curve_curve_int* near_result, curve_curve_int*& refine_result) {
    if(curv.type() == straight_type) {
        straight* st = (straight*)&curv;
        line_nurbs_iterate(*st, nurbs, near_result, refine_result);
    } else {
        curve_curve_int* ret = nullptr;
        curve_curve_int *head, *end;
        head = end = ZeroInter;

        int debug = 0;
        int inters_num = 0;  // 精确交点个数

        SPAinterval range1 = curv.param_range();
        SPAinterval range2 = bs3_curve_range(nurbs);

        while(near_result) {
            int iter_num = 0;
            while(iter_num < 300) {
                if(range1.finite()) {
                    if(near_result->param1 > range1.end_pt()) near_result->param1 = range1.end_pt();
                    if(near_result->param1 < range1.start_pt()) near_result->param1 = range1.start_pt();
                }
                if(near_result->param2 > range2.end_pt()) near_result->param2 = range2.end_pt();
                if(near_result->param2 < range2.start_pt()) near_result->param2 = range2.start_pt();
                SPAvector nurbs_cur = bs3_curve_curvature(near_result->param2, nurbs);
                SPAvector nurbs_deriv = bs3_curve_deriv(near_result->param2, nurbs);
                SPAposition nurbs_pos = bs3_curve_position(near_result->param2, nurbs);

                SPAposition cur_pos = curv.eval_position(near_result->param1);
                SPAvector cur_deriv = curv.eval_deriv(near_result->param1);
                SPAvector cur_cur = curv.eval_curvature(near_result->param1);

                SPAvector r = nurbs_pos - cur_pos;
                double f = r % nurbs_deriv;
                double g = r % cur_deriv;

                // if(!debug) {
                //     if(distance_to_point(nurbs_pos, cur_pos) <= 1e-12) {
                //         // Point Coincidence
                //         break;
                //     }
                //     if(perpendicular(r, nurbs_deriv) && perpendicular(r, cur_deriv)) {
                //         // Perpendicularity
                //         break;
                //     }
                // }

                double J11 = nurbs_deriv.len_sq() + r % nurbs_cur;
                double J12 = -cur_deriv % nurbs_deriv;
                double J21 = nurbs_deriv % cur_deriv;
                double J22 = -cur_deriv.len_sq() + r % cur_cur;

                double base = J11 * J22 - J12 * J21 + DBL_MIN;

                if(fabs(base) <= 1e-16) {
                    break;
                }

                double dt2 = (J12 * g - J22 * f) / base;
                double dt1 = -(J11 * g - J21 * f) / base;

                near_result->param1 += dt1;
                near_result->param2 += dt2;

                // if(!debug) {
                if(fabs(dt1) <= 1e-12 && fabs(dt2) <= 1e-12) {
                    break;
                }
                //}

                if(debug) {
                    std::cout << "param1: " << near_result->param1 << std::endl;
                    std::cout << "param2: " << near_result->param2 << std::endl;
                    std::cout << "dt1: " << dt1 << std::endl;
                    std::cout << "dt2: " << dt2 << std::endl;
                    std::cout << std::endl;
                }
                ++iter_num;
            }
            if(iter_num < 300) {
                // 收敛
                SPAposition cp1 = curv.eval_position(near_result->param1);
                SPAposition cp2 = bs3_curve_position(near_result->param2, nurbs);
                SPAvector deriv2 = bs3_curve_deriv(near_result->param2, nurbs);
                SPAvector deriv1 = curv.eval_deriv(near_result->param1);
                // @todo:test_point_tol函数未解耦:test_point_tol耗时过长暂不解耦
                if(bs3_curve_testpt(cp1, SPAresabs, nurbs) && curv.test_point_tol(cp2)) {
                    ++inters_num;
                    end->next = ACIS_NEW curve_curve_int(nullptr, mid_point(cp1, cp2), near_result->param1, near_result->param2);
                    double angle = VEC_acute_angle(deriv1, deriv2);
                    // 部分用例 biparallel通不过，通过计算夹角判断相切
                    if(fabs(angle) <= 1e-7) {
                        end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_tangent;
                    } else {
                        end->next->low_rel = end->next->high_rel = curve_curve_rel::cur_cur_normal;
                    }
                    end = end->next;
                }
            }
            near_result = near_result->next;
        }
        end->next = nullptr;
        ret = head->next;
        inters_num = CurvCurvIntPointReduce(ret);
        ACIS_DELETE head;
        refine_result = ret;
    }
}

double intersectF(Vector<2> const& vec0, std::vector<void const*> const& params) {
    curve const* cur1 = static_cast<curve const*>(params[0]);
    curve const* cur2 = static_cast<curve const*>(params[1]);

    double u = vec0(0, 0), v = vec0(1, 0);
    SPAvector ndistance_vec = normalise(cur1->eval_position(u) - cur2->eval_position(v));
    double f1 = ndistance_vec % normalise(cur1->eval_deriv(u));
    double f2 = ndistance_vec % normalise(cur2->eval_deriv(v));
    return 0.5 * (f1 * f1 + f2 * f2);
}

// curve-curve 迭代求交
void curve_curve_iterate_minimize(curve const& curv, curve const& curve2, curve_curve_int* near_result, curve_curve_int*& refine_result) {
    std::vector<void const*> params = {&curv, &curve2};
    refine_result = nullptr;
    curve_curve_int* pre = nullptr;
    while(near_result) {
        double param1 = near_result->param1;
        double param2 = near_result->param2;
        // double param1 = curv.param_range().infinite() ? 0.0 : curv.param_range().mid_pt();
        // double param2 = curve2.param_range().infinite() ? 0.0 : curve2.param_range().mid_pt();
        Vector<2> v0({param1, param2});
        Vector<2> output = minimize(intersectF, v0, params, 1e-12);
        param1 = output(0, 0);
        param2 = output(1, 0);

        SPAposition pos1 = curv.eval_position(param1);
        // SPAposition pos2 = bs3_curve_position(param2, nurbs);
        SPAposition pos2 = curve2.eval_position(param2);
        SPAposition pos = mid_point(pos1, pos2);
        SPAposition int_point = pos;
        // std::vector<SPAposition> pos_array = {pos, pos1, pos2};
        // for(SPAposition const& int_point: pos_array) {
        if(curv.test_point_tol(int_point) && curve2.test_point_tol(int_point)) {
            param1 = curv.param(int_point);
            param2 = curve2.param(int_point);
            refine_result = ACIS_NEW curve_curve_int(pre, int_point, param1, param2);
            if(biparallel(curv.point_direction(int_point), curve2.point_direction(int_point))) {
                refine_result->low_rel = refine_result->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                refine_result->low_rel = refine_result->high_rel = curve_curve_rel::cur_cur_normal;
            }
            // double angle = VEC_acute_angle(curv.eval_direction(param1), curve2.eval_direction(param2));
            //// 部分用例 biparallel通不过，通过计算夹角判断相切
            // if(fabs(angle) <= 1e-7) {
            //     refine_result->low_rel = refine_result->high_rel = curve_curve_rel::cur_cur_tangent;
            // } else {
            //     refine_result->low_rel = refine_result->high_rel = curve_curve_rel::cur_cur_normal;
            // }
            pre = refine_result;
            break;
        }
        //}

        near_result = near_result->next;
    }
    // ic->set_cur(nullptr, -1, FALSE);
    // ACIS_DELETE ic;
    CurvCurvIntPointReduce(refine_result);
}

/** 使用最优化方法求cur1和cur2容差内的交点  */
curve_curve_int* tolerance_int_cur_cur(curve const& cur1, curve const& cur2, std::vector<SPAposition>& cand_points, double tol, int maxiter) {
    // 包围盒初筛
    SPAbox box1 = enlarge_box(bound_of_curve(cur1), 1e-3);
    SPAbox box2 = enlarge_box(bound_of_curve(cur2), 1e-3);
    if(!(box1 && box2)) {
        return nullptr;
    }

    if(cand_points.empty()) {
        SPAbox int_box = box1 & box2;  // 考虑无穷包围盒
        cand_points.push_back(int_box.mid());
    }
    // 求两曲线无精确交点的情况下的一个容差内的交点
    curve_curve_int* inters = nullptr;
    API_BEGIN
    for(SPAposition const& pos: cand_points) {
        SPAposition foot;
        // @todo: point_perp函数耗时过长
        cur2.point_perp(pos, foot);  // foot为pos在cur2上的垂足
                                     // Vector<2> x0({cur1.param(pos), cur2.param(pos)});
        Vector<2> x0({cur1.param(pos), cur2.param(foot)});
        SPAposition pt1, pt2;
        double dis = MinDistancePointPair_Impl(cur1, cur2, x0, pt1, pt2, maxiter);
        SPAposition int_point = mid_point(pt1, pt2);
        // HelixBSplineIntrTest.taperDegree1NoInters test_point_tol抛出异常
        double dis_to_cur1 = distance_to_curve(int_point, cur1);
        double dis_to_cur2 = distance_to_curve(int_point, cur2);
        if(dis_to_cur1 <= tol && dis_to_cur2 <= tol && dis <= tol) {  // ACIS test_point_tol设置容差不起作用 IntersectorStraightStraight.TestBug18
            inters = ACIS_NEW curve_curve_int(nullptr, int_point, cur1.param(int_point), cur2.param(int_point));
            inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_normal;  // 容差内的交点关系可能为tangent
            SPAvector dir1 = cur1.point_direction(int_point);
            SPAvector dir2 = cur2.point_direction(int_point);
            double angle = VEC_acute_angle(dir1, dir2);
            if(angle <= 1e-8) {  // 6.0807e-09
                inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_tangent;
            }
            break;
        }
    }
    API_END
    return inters;
}

/** 使用最优化方法求cur1和cur2容差内的交点  */
curve_curve_int* cur1_cur2_tolerance_newton(curve const& cur1, curve const& cur2, std::vector<SPAposition>& cand_points, double tol, int maxiter) {
    // 求两曲线无精确交点的情况下的一个容差内的交点
    curve_curve_int* inters = nullptr;
    API_BEGIN
    for(SPAposition const& pos: cand_points) {
        SPAposition foot;

        Vector<2> x0({cur1.param(pos), cur2.param(pos)});

        SPAposition pt1, pt2;

        double dis = cur1_cur2_MinDistancePointPair_Impl(cur1, cur2, x0, pt1, pt2, maxiter);
        SPAposition int_point = mid_point(pt1, pt2);
        // HelixBSplineIntrTest.taperDegree1NoInters test_point_tol抛出异常
        double dis_to_cur1 = distance_to_curve(int_point, cur1);
        double dis_to_cur2 = distance_to_curve(int_point, cur2);
        if(dis_to_cur1 <= tol && dis_to_cur2 <= tol && dis <= tol) {  // ACIS test_point_tol设置容差不起作用 IntersectorStraightStraight.TestBug18
            inters = ACIS_NEW curve_curve_int(nullptr, int_point, cur1.param(int_point), cur2.param(int_point));
            inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_normal;  // 容差内的交点关系可能为tangent
            SPAvector dir1 = cur1.point_direction(int_point);
            SPAvector dir2 = cur2.point_direction(int_point);
            double angle = VEC_acute_angle(dir1, dir2);
            if(angle <= 1e-8) {  // 6.0807e-09
                inters->low_rel = inters->high_rel = curve_curve_rel::cur_cur_tangent;
            }
            break;
        }
    }
    API_END
    return inters;
}

/**
 * @brief 获得曲线的包围盒
 */
SPAbox bound_of_curve(curve const& curv) {
    SPAinterval inf_interval(interval_infinite, 0.0, 0.0);
    SPAbox box(inf_interval, inf_interval, inf_interval);  // infinite box
    if(curv.type() == straight_type) {
        if(curv.param_range().finite()) {
            SPAinterval param_range = curv.param_range();
            box = SPAbox(curv.eval_position(param_range.start_pt()), curv.eval_position(param_range.end_pt()));
        }
    } else if(curv.type() == ellipse_type) {
        ellipse const* ell = static_cast<ellipse const*>(&curv);
        // @todo: bound耗时过长暂不解耦
        box = ell->bound(-M_PI, M_PI);
    } else if(curv.type() == helix_type) {
        helix const* hel = static_cast<helix const*>(&curv);
        SPAinterval helix_range = hel->param_range();
        if(helix_range.finite()) {
            // @todo: bound耗时过长暂不解耦
            box = hel->bound(helix_range);  // 不支持infinite helix
            // release下ACIS的hel->bound会抛出异常,考虑hel->bound
        }
    } else if(curv.type() == intcurve_type) {
        intcurve const* ic = static_cast<intcurve const*>(&curv);
        bs3_curve bs3 = ic->cur();
        // @todo: bound耗时过长暂不解耦
        box = ic->bound(bs3_curve_range(bs3));  // box = bs3_curve_box(bs3,;
    }
    return box;
}

/**
 * @brief 给定初始值_x0, 求func的最小值
 */
Vector<2> minimize(ScalarFunc2dType const& func, Vector<2> const& _x0, std::vector<void const*> const& params, double tol, int maxiter, bool adaptive) {
    const int N = 2;
    Vector<N> x0 = _x0;
    double rho, chi, psi, sigma;
    if(adaptive) {
        double dim = static_cast<float>(N);
        rho = 1;
        chi = 1 + 2 / dim;
        psi = 0.75 - 1 / (2 * dim);
        sigma = 1 - 1 / dim;
    } else {
        rho = 1;
        chi = 2;
        psi = 0.5;
        sigma = 0.5;
    }
    //
    double nonzdelt = 0.05;
    double zdelt = 0.00025;
    int ncalls = 0;
    Matrix<N + 1, N> sim;

    sim.set_row(0, x0);
    for(int k = 0; k < N; ++k) {
        Vector<2> y = x0;
        if(fabs(y(k, 0)) > 2.22e-16) {  // toler
            y(k, 0) = (1 + nonzdelt) * y(k, 0);
        } else {
            y(k, 0) = zdelt;
        }
        sim.set_row(k + 1, y);
    }

    double xatol, fatol;
    xatol = fatol = tol;
    if(maxiter == -1) {  // 默认最大迭代次数
        maxiter = N * 300;
    }
    int maxfun = N * 300;  // 手动设置上界，防止无限循环

    std::vector<int> one2np1(N);  //= list(range(1, N + 1))
    for(int i = 0; i < N; ++i) {
        one2np1[i] = i + 1;
    }
    Vector<N + 1> fsim(std::vector<double>(N + 1, DBL_MAX));
    for(int k = 0; k < N + 1; ++k) {
        fsim(k, 0) = func(sim.get_row(k), params);  // Minimal Question
        ncalls++;
    }
    std::vector<int> ind = argsort(fsim);
    Vector<N + 1> copy_fsim = fsim;
    Matrix<N + 1, N> copy_sim = sim;
    for(int i = 0; i < N + 1; ++i) {
        fsim(i, 0) = copy_fsim(ind[i], 0);
        sim.set_row(i, copy_sim.get_row(ind[i]));  // sort so sim[0,:] has the lowest function value
    }

    int iterations = 1;
    auto abs = [](double a) { return fabs(a); };
    while(ncalls < maxfun && iterations < maxiter) {
        Vector<N> fsim_except0;
        for(int i = 0; i < N; ++i) {
            fsim_except0(i, 0) = fsim(i + 1, 0);
        }
        double maxval = -DBL_MAX;
        for(int i = 0; i < N; ++i) {
            maxval = D3_max(maxval, max(apply(abs, sim.get_row(i + 1) - sim.get_row(0))));
        }
        double maxfval = max(apply(abs, fsim_except0 - fsim(0, 0)));
        if(maxval <= xatol && maxfval <= fatol) {
            break;
        }
        Vector<N> xbar;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                xbar(i, 0) += sim(j, i) / N;
            }
        }
        Vector<N> xr = (1 + rho) * xbar - rho * sim.get_row(N);
        double fxr = func(xr, params);
        ncalls++;
        int doshrink = 0;

        if(fxr < fsim(0, 0)) {
            Vector<N> xe = (1 + rho * chi) * xbar - rho * chi * sim.get_row(N);
            double fxe = func(xe, params);
            ncalls++;

            if(fxe < fxr) {
                sim.set_row(N, xe);
                fsim(N, 0) = fxe;
            } else {
                sim.set_row(N, xr);
                fsim(N, 0) = fxr;
            }
        } else {  // fsim[0] <= fxr
            if(fxr < fsim(N - 1, 0)) {
                sim.set_row(N, xr);
                fsim(N, 0) = fxr;
            } else {  // fxr >= fsim[-2]
                // Perform contraction
                if(fxr < fsim(N, 0)) {
                    Vector<N> xc = (1 + psi * rho) * xbar - psi * rho * sim.get_row(N);
                    double fxc = func(xc, params);
                    ncalls++;

                    if(fxc <= fxr) {
                        sim.set_row(N, xc);
                        fsim(N, 0) = fxc;
                    } else {
                        doshrink = 1;
                    }
                } else {
                    // Perform an inside contraction
                    Vector<N> xcc = (1 - psi) * xbar + psi * sim.get_row(N);
                    double fxcc = func(xcc, params);
                    ncalls++;

                    if(fxcc < fsim(N, 0)) {
                        sim.set_row(N, xcc);
                        fsim(N, 0) = fxcc;
                    } else {
                        doshrink = 1;
                    }
                }

                if(doshrink) {
                    for(int j: one2np1) {
                        sim.set_row(j, sim.get_row(0) + sigma * (sim.get_row(j) - sim.get_row(0)));
                        fsim(j, 0) = func(sim.get_row(j), params);
                        ncalls++;
                    }
                }
            }
        }
        std::vector<int> ind = argsort(fsim);
        Vector<N + 1> copy_fsim = fsim;
        Matrix<N + 1, N> copy_sim = sim;
        for(int i = 0; i < N + 1; ++i) {
            fsim(i, 0) = copy_fsim(ind[i], 0);
            sim.set_row(i, copy_sim.get_row(ind[i]));
        }
        iterations += 1;
    }

    Vector<N> x = sim.get_row(0);
    double fval = min(fsim);
    // if(iterations >= maxiter) {
    //     std::cout << "error" << std::endl;
    // } else {
    //     std::cout << "success" << std::endl;
    // }
    return x;
}

/**
 * @brief 计算三维点到曲线的最短距离
 */
double distance_to_curve(SPAposition const& pos, curve const& cur) {
    double distance = DBL_MAX;
    API_BEGIN
    SPAposition foot;
    // @todo: point_perp函数未解耦:point_perp解耦后存在问题
    cur.point_perp(pos, foot);
    distance = distance_to_point(pos, foot);
    API_END
    return distance;
}

/**
 * @brief 两个nurbs曲线的近似求交
 */
curve_curve_int* nurbs_nurbs_near_inters(bs3_curve nurbs1, bs3_curve nurbs2, SPAinterval const& range1, SPAinterval const& range2, double tol) {
    if(!nurbs1 || !nurbs2) {
        return nullptr;
    }

    // SPAinterval range1 = bs3_curve_range(nurbs1);
    // SPAinterval range2 = bs3_curve_range(nurbs2);
    intcurve* ic1 = make_exact_intcurve(nurbs1);
    intcurve* ic2 = make_exact_intcurve(nurbs2);
    int level = 0;
    std::queue<std::pair<SPAinterval, SPAinterval>>*q, *new_q;
    q = new std::queue<std::pair<SPAinterval, SPAinterval>>();
    new_q = new std::queue<std::pair<SPAinterval, SPAinterval>>();
    q->push(std::make_pair(range1, range2));
    const int split_num = 2;
    const int max_level = 5;
    const double margin1 = tol;
    const double margin2 = tol;
    int num_calls = 0;
    std::unordered_map<double, SPAbox> box_map1;
    std::unordered_map<double, SPAbox> box_map2;
    std::unordered_map<double, SPAbox>::iterator iter;

    while(!q->empty()) {
        ++level;
        if(level > max_level) {
            break;
        }
        while(!q->empty()) {
            const auto& cell = q->front();
            q->pop();
            auto sub_range1 = cell.first, sub_range2 = cell.second;
            // printf("%d\t{%lf, %lf}, {%lf, %lf}\n", level, sub_range1.start_pt(), sub_range1.end_pt(), sub_range2.start_pt(), sub_range2.end_pt());
            SPAinterval subs1[split_num] = {
              {sub_range1.start_pt(), sub_range1.mid_pt()},
              {sub_range1.mid_pt(),   sub_range1.end_pt()}
            };
            SPAinterval subs2[split_num] = {
              {sub_range2.start_pt(), sub_range2.mid_pt()},
              {sub_range2.mid_pt(),   sub_range2.end_pt()}
            };
            for(int i = 0; i < split_num; ++i) {
                for(int j = 0; j < split_num; ++j) {
                    // printf("\tsubset: {%lf, %lf}, {%lf, %lf}\n", subs1[i].start_pt(), subs1[i].end_pt(), subs2[j].start_pt(), subs2[j].end_pt());
                    SPAbox box1;
                    SPAbox box2;
                    if((iter = box_map1.find(subs1[i].mid_pt())) != box_map1.end()) {
                        box1 = iter->second;
                    } else {
                        // @todo: bound耗时较长暂不解耦
                        box1 = enlarge_box(std::move(ic1->bound(subs1[i])), margin1);
                        box_map1.insert(std::make_pair(subs1[i].mid_pt(), box1));
                        ++num_calls;
                    }
                    if((iter = box_map2.find(subs2[j].mid_pt())) != box_map2.end()) {
                        box2 = iter->second;
                    } else {
                        // @todo: bound耗时较长暂不解耦
                        box2 = enlarge_box(std::move(ic2->bound(subs2[j])), margin2);
                        box_map2.insert(std::make_pair(subs2[j].mid_pt(), box2));
                        ++num_calls;
                    }
                    if(box1 && box2) {
                        new_q->push(std::make_pair(subs1[i], subs2[j]));
                    }
                }
            }
        }
        // exchange q and new_q
        auto* tmp = new_q;
        new_q = q;
        q = tmp;
    }

    curve_curve_int *pre = nullptr, *ret = nullptr;
    // std::cout << "final queue\n";
    while(!q->empty()) {
        const auto& front = q->front();
        q->pop();
        // printf("{%lf, %lf}, {%lf, %lf}\n", front.first.start_pt(), front.first.end_pt(), front.second.start_pt(), front.second.end_pt());
        ret = ACIS_NEW curve_curve_int(pre, {0, 0, 0}, front.first.mid_pt(), front.second.mid_pt());
        pre = ret;
    }

    // std::cout << "number of count: " << num_calls << std::endl;
    ic1->set_cur(nullptr, -1, FALSE);
    ic2->set_cur(nullptr, -1, FALSE);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
    delete q;
    delete new_q;
    return ret;
}

// 获得区间range去除exclude_ranges后的集合
void interval_exclude(SPAinterval const& range, std::vector<SPAinterval> const& exclude_ranges, std::vector<SPAinterval>& left_ranges) {
    std::vector<std::pair<double, int>> interval;             // (val, label)
    interval.push_back(std::make_pair(range.start_pt(), 0));  // 0代表端点
    interval.push_back(std::make_pair(range.end_pt(), 0));
    for(auto const& exclude_range: exclude_ranges) {
        interval.push_back(std::make_pair(exclude_range.start_pt(), 1));  // 1代表start
        interval.push_back(std::make_pair(exclude_range.end_pt(), 2));    // 2代表end
    }
    std::sort(interval.begin(), interval.end());
    left_ranges.clear();
    for(int i = 1; i < interval.size(); ++i) {
        if((interval[i - 1].second == 0 && interval[i].second == 1) || (interval[i - 1].second == 2 && interval[i].second == 0) || (interval[i - 1].second == 2 && interval[i].second == 1) || (interval[i - 1].second == 0 && interval[i].second == 0)) {
            if(interval[i].first - interval[i - 1].first > SPAresabs) {
                left_ranges.push_back(SPAinterval(interval[i - 1].first, interval[i].first));
            }
        }
    }
}

// 连接两个线线求交结果
curve_curve_int* connect_curve_curve_int(curve_curve_int* inter1, curve_curve_int* inter2) {
    curve_curve_int* ret = inter1;
    curve_curve_int* end = ret;
    while(end && end->next) {
        end = end->next;
    }

    if(end) {
        end->next = inter2;
    } else {
        ret = inter2;
    }
    return ret;
}

/**
 * @brief 检验curv是否在param处非G1连续
 * @return curv在param处G1不连续，返回FALSE;curv在param处G1连续，返回TRUE
 * @param curv 输入的曲线
 * @param param 输入的曲线参数
 */
logical check_irregular_G1(bs3_curve curv, double param) {
    logical is_G1 = FALSE;
    if(curv) {
        SPAinterval range = bs3_curve_range(curv);
        if(param << range) {
            double tol = 0.01;  // margin
            if(param + tol << range && param - tol << range) {
                SPAvector left_tangent = bs3_curve_deriv(param - tol, curv);
                SPAvector right_tangent = bs3_curve_deriv(param + tol, curv);

                double angle = VEC_acute_angle(left_tangent, right_tangent);

                double k_left = bs3_curve_curvature(param - tol, curv).numerically_stable_len();
                double k_right = bs3_curve_curvature(param + tol, curv).numerically_stable_len();

                double k = D3_max(k_left, k_right);    // 曲率
                if(angle > k * 2 * tol + SPAresabs) {  // 0.0050000100476310996 > 0.0049999938677502305
                    // G1不连续
                    is_G1 = TRUE;
                }
                // if(is_G1) {
                //     printf("G1不连续 %.16lf, %.16lf\n", angle, k * 2 * tol);
                // }
            }
        }
    }
    return is_G1;
}

/**
 * @brief 返回两个圆的最近的一对点(无交的情况) 或者 所有交点(有交的情况)
 * @return true: 两个圆重合 false: 两个圆不重合
 * @param cir1 输入的圆1
 * @param cir2 输入的圆2
 * @param pos1_array cir1上的最近点
 * @param pos2_array cir2上的最近点
 */
bool circle_circle_closest_points(ellipse const& cir1, ellipse const& cir2, std::vector<SPAposition>& pos1_array, std::vector<SPAposition>& pos2_array) {
    pos1_array.clear();
    pos2_array.clear();
    curve_curve_int* inters = nullptr;
    API_BEGIN
    inters = int_cur_cur(cir1, cir2, *(SPAbox*)nullptr, 1e-16);  // 1e-15
    API_END
    if(inters && inters->next && (inters->low_rel == curve_curve_rel::cur_cur_coin || inters->high_rel == curve_curve_rel::cur_cur_coin)) {
        delete_curve_curve_ints(inters);
        return true;
    }
    for(auto inters_tmp = inters; inters_tmp; inters_tmp = inters_tmp->next) {
        pos1_array.push_back(inters_tmp->int_point);
        pos2_array.push_back(inters_tmp->int_point);
    }
    if(inters) {
        delete_curve_curve_ints(inters);
    } else {
        if(biparallel(cir1.normal, cir2.normal) && (is_equal(cir1.centre, cir2.centre) || perpendicular(cir1.centre - cir2.centre, cir1.normal))) {
            // coplanar
            SPAunit_vector direction = normalise(cir1.centre - cir2.centre);
            double cc = distance_to_point(cir1.centre, cir2.centre);
            double r1 = cir1.major_axis.numerically_stable_len();
            double r2 = cir2.major_axis.numerically_stable_len();
            if(cc > (r1 + r2)) {
                // 外离
                pos1_array.push_back(cir1.centre - r1 * direction);
                pos2_array.push_back(cir2.centre + r2 * direction);
                return false;
            } else if(cc - fabs(r1 - r2) < 0) {
                // 内含
                if(r1 < r2) {
                    direction = -direction;
                }
                pos1_array.push_back(cir1.centre - r1 * direction);
                pos2_array.push_back(cir2.centre - r2 * direction);
                return false;
            }
        }
        SPAposition pos1, pos2;
        double dis = MinDistancePointPair_Impl(cir1, cir2, {0, 0}, pos1, pos2);
        pos1_array.push_back(pos1);
        pos2_array.push_back(pos2);
    }
    return false;
}

/**
 * @brief 返回直线和圆最近的一对点(无交的情况) 或者 所有交点(有交的情况)
 * @param line 输入的直线
 * @param cir 输入的圆
 * @param pos1_array line上的最近点
 * @param pos2_array cir上的最近点
 */
void line_circle_closest_points(straight const& line, ellipse const& cir, std::vector<SPAposition>& pos1_array, std::vector<SPAposition>& pos2_array) {
    pos1_array.clear();
    pos2_array.clear();

    curve_curve_int* inters = nullptr;
    API_BEGIN
    inters = int_cur_cur(line, cir, *(SPAbox*)nullptr);
    API_END
    if(inters) {
        pos1_array.push_back(inters->int_point), pos2_array.push_back(inters->int_point);
        if(inters->next) {
            pos1_array.push_back(inters->next->int_point), pos2_array.push_back(inters->next->int_point);
        }
        delete_curve_curve_ints(inters);
    } else {
        if(perpendicular(cir.normal, line.direction) && (is_equal(cir.centre, line.root_point) || perpendicular(cir.centre - line.root_point, cir.normal))) {
            // coplanar
            SPAposition foot = proj_pt_to_line(cir.centre, line.root_point, line.direction);
            double center_to_line = distance_to_point(cir.centre, foot);
            double radius = cir.major_axis.len();
            if(center_to_line > radius) {
                SPAunit_vector dir = normalise(foot - cir.centre);
                pos1_array.push_back(foot);
                pos2_array.push_back(cir.centre + dir * radius);
                return;
            }
        }
        SPAposition pos1, pos2;
        double dis = MinDistancePointPair_Impl(line, cir, {0, 0}, pos1, pos2);
        pos1_array.push_back(pos1);
        pos2_array.push_back(pos2);
    }
}

/**
 * @brief 判断一个bs3_curve在[st, ed]内是否为平面曲线
 * @return TRUE: bs3_curve在[st, ed]内为平面曲线, FALSE: bs3_curve在[st, ed]内不是平面曲线
 * @param curv 输入的nurbs曲线
 * @param interval 输入的曲线 [st, ed]
 * @param center 若bs3_curve在[st, ed]内为平面曲线，返回所在平面上一点
 * @param normal 若bs3_curve在[st, ed]内为平面曲线，返回所在平面的法向量
 */
int bs3_curve_is_planar(bs3_curve curv, SPAinterval const& interval, SPAposition& center, SPAunit_vector& normal, double tol) {
    bool is_planar = 0;
    if(interval.unbounded()) {
        return 0;
    }
    double st = interval.start_pt(), ed = interval.end_pt();
    if(curv && st <= ed) {
        bs3_curve sub_curve = bs3_curve_split_interval(curv, st, ed);
        if(sub_curve) {
            double height = SPL_BezcHeightEstimate(sub_curve);
            if(height <= tol) {
                // nurbs曲线为线段或退化为线段
                SPAposition cp = bs3_curve_position(st, sub_curve), cp1 = bs3_curve_position(ed, sub_curve);
                if(is_equal(cp, cp1)) {
                    // 退化为点
                    return -1;
                }

                if(&center) {
                    center = cp;
                }
                if(&normal) {
                    SPAvector cv = cp - cp1;
                    normal = normalise(cv.make_ortho());
                }
                bs3_curve_delete(sub_curve);
                return -1;
            }
            double mid = 0.5 * (st + ed);
            SPAposition cp = bs3_curve_position(mid, sub_curve);
            SPAposition cp1 = bs3_curve_position(st, sub_curve);
            while(is_equal(cp, cp1)) {
                st = 0.5 * (st + mid);
                cp1 = bs3_curve_position(st, sub_curve);
            }
            SPAposition cp2 = bs3_curve_position(ed, sub_curve);
            SPAunit_vector vx = normalise(cp - cp1), vy = normalise(cp - cp2);
            while(is_equal(cp, cp2) || biparallel(vx, vy)) {
                ed = 0.5 * (ed + mid);
                cp2 = bs3_curve_position(ed, sub_curve);
                vy = normalise(cp - cp2);
            }
            SPAunit_vector vz = normalise(vx * vy);
            compute_axes_from_z(vz, vx, vy);

            SPAtransf transf = std::move(cucuint_coordinate_transf(cp, vx, vy, vz));
            bs3_curve_trans(sub_curve, transf);

            SPAposition* ctrlpts = nullptr;
            int num_ctrlpts = 0;
            bs3_curve_control_points(sub_curve, num_ctrlpts, ctrlpts);
            int i = 0;
            for(i = 0; i < num_ctrlpts; ++i) {
                if(fabs(ctrlpts[i].z()) > SPAresabs) {
                    break;
                }
            }
            if(i == num_ctrlpts) {
                is_planar = 1;
                if(&center) {
                    center = cp;
                }
                if(&normal) {
                    normal = vz;
                }
            }
            ACIS_DELETE[] ctrlpts;
            ctrlpts = nullptr;
        }
        bs3_curve_delete(sub_curve);
        sub_curve = nullptr;
    }
    return is_planar;
}

/**
 * @brief 弦截法 求解一元非线性方程的最小值, sol在[a, b]内，要求func(a)*func(b) < 0
 * @param func 一元非线性方程
 * @param a 区间左端
 * @param b 区间右端
 * @param sol 解
 * @param tol 误差
 */
void Secant(std::function<double(double)> const& func, double x1, double x2, double& sol, double tol) {
    double xm1, xm2, k, f1, f2;
    int iter_no = 0;
    do {
        ++iter_no;
        f1 = func(x1);
        f2 = func(x2);

        xm1 = (x1 * f2 - x2 * f1) / (f2 - f1);

        k = func(xm1);

        x1 = x2;
        x2 = xm1;

        if(fabs(k) <= tol) break;

        xm2 = (x1 * f2 - x2 * f1) / (f2 - f1);

    } while(fabs(xm2 - xm1) >= tol && iter_no <= 300);
    sol = xm1;
}

/**
 * @brief 考虑容差的向量归一化
 */
SPAunit_vector cucuint_normalise(SPAvector const& vec, double tol) {
    SPAunit_vector unit_vec(0, 0, 0);
    int zero_counts = 0;
    for(int i = 0; i < 3; ++i) {
        if(fabs(vec.component(i)) <= tol) {
            ++zero_counts;
            unit_vec.component(i) = 0.0;
        } else {
            unit_vec.component(i) = 1.0;
        }
    }
    if(zero_counts < 2) {
        unit_vec = normalise(vec);
    }
    return unit_vec;
}

/**
 * @brief 验证重合结果的有效性
 */
int validate_coin_result(curve const& cur1, curve const& cur2, std::vector<SPAinterval>& coin_ints1, std::vector<SPAinterval>& coin_ints2, curve_curve_int*& coins, double tol) {
    curve const* curve1 = &cur1;
    curve const* curve2 = &cur2;
    int num_coin_segs = 0;
    auto tmp_coins = ZeroInter, head = tmp_coins;
    for(int i = 0; i < coin_ints1.size(); ++i) {
        auto const& r1 = coin_ints1[i];
        auto const& r2 = coin_ints2[i];
        double dis_e1_to_e2_st = distance_to_curve(curve1->eval_position(r1.start_pt()), *curve2);
        double dis_e1_to_e2_ed = distance_to_curve(curve1->eval_position(r1.end_pt()), *curve2);
        double dis_e2_to_e1_st = distance_to_curve(curve2->eval_position(r2.start_pt()), *curve1);
        double dis_e2_to_e1_ed = distance_to_curve(curve2->eval_position(r2.start_pt()), *curve1);
        if(dis_e1_to_e2_st <= tol && dis_e1_to_e2_ed <= tol && dis_e2_to_e1_st <= tol && dis_e2_to_e1_ed <= tol) {
            coin_ints1[num_coin_segs] = r1;
            coin_ints2[num_coin_segs] = r2;
            ++num_coin_segs;
            tmp_coins = tmp_coins->next = coins;
            tmp_coins = tmp_coins->next = coins->next;
            coins = coins->next->next;
        } else {
            auto next = coins->next->next;
            ACIS_DELETE coins->next;
            ACIS_DELETE coins;
            coins = next;
        }
    }
    coin_ints1.erase(coin_ints1.begin() + num_coin_segs, coin_ints1.end());
    coin_ints2.erase(coin_ints2.begin() + num_coin_segs, coin_ints2.end());
    coins = head->next;
    ACIS_DELETE head;
    return num_coin_segs;
}

/**
 * @brief 判断val在容差tol内是否位于区间range
 */
bool double_in_range(double val, SPAinterval const& range, double tol) {
    bool in_range = false;
    if(&range) {
        if(range.infinite()) {
            in_range = true;
        } else if(range.unbounded_below() && val <= range.end_pt() + tol) {
            in_range = true;
        } else if(range.unbounded_above() && val >= range.start_pt() - tol) {
            in_range = true;
        } else {
            in_range = range.start_pt() - tol <= val && val <= range.end_pt() + tol;
        }
    }
    return in_range;
}

/**
 * @brief 判断交点是否容差tol内位于包围盒box中
 */
bool point_in_box(SPAposition const& pos, SPAbox const& box, double tol) {
    return double_in_range(pos.x(), box.x_range(), tol) && double_in_range(pos.y(), box.y_range(), tol) && double_in_range(pos.z(), box.z_range(), tol);
}

/**
 * @brief 判断曲线是否为退化的曲线
 * @return true: 曲线退化 false: 曲线非退化
 * @param cur 输入的曲线
 */
bool is_degenerate(curve const& cur) {
    if(&cur) {
        if(cur.type() == straight_type && fabs(((straight const*)&cur)->param_scale) <= SPAresabs) {
            return true;
        }
        if(cur.type() == ellipse_type && is_zero(((ellipse const*)&cur)->major_axis)) {
            return true;
        }
        if(cur.type() == ellipse_type && is_zero(((ellipse const*)&cur)->radius_ratio)) {
            return true;
        }
    }
    return false;  // CUR_is_degenerate(cur) 未实现
}

/**
 * @brief 求直线和圆柱螺旋线的最近点对(pt1, pt2)
 * @return TRUE: 求得的最近点对收敛 FALSE: 求得的最近点对不收敛
 * @param cci_straight 直线
 * @param cci_helix 圆柱螺旋线
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(straight const& cci_straight, helix const& cci_helix, SPAposition const& init_pos, SPAposition& pt1, SPAposition& pt2) {
    // 不检查输入是否为圆柱螺旋线，需要外部确认
    //
    // 螺旋线的局部坐标系
    SPAposition helix_center = cci_helix.axis_root();
    SPAunit_vector helix_vx = cci_helix.maj_dir();
    SPAunit_vector helix_vz = cci_helix.axis_dir();
    SPAunit_vector helix_vy = normalise(helix_vz * helix_vx);

    // 公式推导
    SPAposition ZeroPos(0, 0, 0);
    SPAmatrix trans_mat(helix_vx, helix_vy, helix_vz);
    SPAposition p2 = ZeroPos + trans_mat * (cci_straight.root_point - helix_center);
    SPAunit_vector d2 = normalise(trans_mat * cci_straight.direction);

    double r = cci_helix.radius();
    double p = cci_helix.pitch() / (2 * M_PI);
    double a = d2.z() * p;
    double b = d2 % p2;
    double c = p * p;
    double d = p * p2.z();
    double e = 1.0;
    double f = r * r + (p2 - ZeroPos) % (p2 - ZeroPos);

    std::string str_Du = std::format("{}*cos(v)+{}*sin(v)+{}*v+{}*u+{}", -2 * r * d2.x(), -2 * r * d2.y(), -2 * a, 2, 2 * b);
    std::string str_Dv = std::format("{}*({}*u+{})*sin(v)+{}*({}*u+{})*cos(v)+{}*u+{}*v+{}", 2 * r, d2.x(), p2.x(), -2 * r, d2.y(), p2.y(), -2 * a, 2 * c, -2 * d);
    std::string str_Duu = std::format("2");
    std::string str_Duv = std::format("{}*sin(v)+{}*cos(v)+{}", 2 * r * d2.x(), -2 * r * d2.y(), -2 * a);
    std::string str_Dvu = str_Duv;
    std::string str_Dvv = std::format("{}*({}*u+{})*cos(v)+{}*({}*u+{})*sin(v)+{}", 2 * r, d2.x(), p2.x(), 2 * r, d2.y(), p2.y(), 2 * c);
    std::vector<std::string> str_Fs = {str_Du, str_Dv};
    std::vector<std::string> str_Js = {str_Duu, str_Duv, str_Dvu, str_Dvv};
    law* law_Fs[2] = {nullptr};
    law* law_Js[4] = {nullptr};
    for(int i = 0; i < 2; ++i) {
        api_str_to_law(str_Fs[i].c_str(), &law_Fs[i]);
    }
    for(int i = 0; i < 4; ++i) {
        api_str_to_law(str_Js[i].c_str(), &law_Js[i]);
    }
    double x_init[2] = {cci_straight.param(init_pos), cci_helix.param(init_pos)};
    double* x_out = nullptr;
    logical converged = bivariant_newton_iterate(x_init, law_Fs, law_Js, &x_out, 1e-6);
    pt1 = cci_straight.eval_position(x_out[0]);
    pt1 = cci_helix.eval_position(x_out[1]);
    // 销毁law和收敛结果
    ACIS_DELETE[] STD_CAST x_out;
    for(int i = 0; i < 2; ++i) {
        if(law_Fs[i]) {
            law_Fs[i]->remove();
            law_Fs[i] = nullptr;
        }
    }
    for(int i = 0; i < 4; ++i) {
        if(law_Js[i]) {
            law_Js[i]->remove();
            law_Js[i] = nullptr;
        }
    }
    return converged;
}

/**
 * @brief 求圆和圆柱螺旋线的最近点对(pt1, pt2)
 * @return TRUE: 求得的最近点对收敛 FALSE: 求得的最近点对不收敛
 * @param cci_ellipse 椭圆
 * @param cci_helix 圆柱螺旋线
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(ellipse const& cci_ellipse, helix const& cci_helix, SPAposition const& init_pos, SPAposition& pt1, SPAposition& pt2) {
    // 令param1为圆上参数，param2为螺旋线上参数
    // 获得初始参数
    SPAposition foot;

    // @todo: param函数未解耦:耗时过长暂不解耦
    cci_ellipse.closest_point(init_pos, foot);
    double init_param1 = cci_ellipse.param(foot);
    double init_param2 = cci_helix.param(init_pos);

    SPAunit_vector hel_vx = cci_helix.maj_dir();
    SPAunit_vector hel_vz = cci_helix.axis_dir();
    SPAunit_vector hel_vy = normalise(hel_vz * hel_vx);

    SPAmatrix trans_mat(hel_vx, hel_vy, hel_vz);
    SPAposition ell_center_loc = SPAposition(0, 0, 0) + trans_mat * (cci_ellipse.centre - cci_helix.axis_root());
    SPAunit_vector ell_vx_loc = normalise(trans_mat * cci_ellipse.major_axis);
    SPAunit_vector ell_vz_loc = normalise(trans_mat * cci_ellipse.normal);
    SPAunit_vector ell_vy_loc = normalise(trans_mat * (cci_ellipse.normal * cci_ellipse.major_axis));

    double x0 = ell_center_loc.coordinate(0), y0 = ell_center_loc.coordinate(1), z0 = ell_center_loc.coordinate(2);
    double r1 = cci_helix.radius();
    double r2 = cci_ellipse.major_axis.len() * cci_ellipse.radius_ratio;
    double p = cci_helix.pitch() / (2 * M_PI);

    std::string str_t1 = std::format("(({}-{}*cos(v))^2+({}-{}*sin(v))^2+({}-{}*v)^2)", x0, r1, y0, r1, z0, p);
    std::string str_t2 = std::format("({}*({}-{}*cos(v))+{}*({}-{}*sin(v))+{}*({}-{}*v))", ell_vx_loc.x(), x0, r1, ell_vx_loc.y(), y0, r1, ell_vx_loc.z(), z0, p);
    std::string str_t3 = std::format("({}*({}-{}*cos(v)+{}*({}-{}*sin(v))+{}*({}-{}*v)))", ell_vy_loc.x(), x0, r1, ell_vy_loc.y(), y0, r1, ell_vy_loc.z(), z0, p);

    std::string str_t1t = std::format("({}*sin(v)-{}*cos(v)+{}*v-{})", 2 * x0 * r1, 2 * y0 * r1, 2 * p * p, 2 * p * z0);
    std::string str_t2t = std::format("({}*sin(v)-{}*cos(v)-{})", r1 * ell_vx_loc.x(), r1 * ell_vx_loc.y(), p * ell_vx_loc.z());
    std::string str_t3t = std::format("({}*sin(v)-{}*cos(v)-{})", r1 * ell_vy_loc.x(), r1 * ell_vy_loc.y(), p * ell_vy_loc.z());

    std::string str_t1tt = std::format("({}*cos(v)+{}*sin(v)+{})", 2 * x0 * r1, 2 * y0 * r1, 2 * p * p);
    std::string str_t2tt = std::format("({}*cos(v)+{}*sin(v))", r1 * ell_vx_loc.x(), r1 * ell_vx_loc.y());
    std::string str_t3tt = std::format("({}*cos(v)+{}*sin(v))", r1 * ell_vy_loc.x(), r1 * ell_vy_loc.y());

    // 构造方程组law
    double x_init[2] = {init_param1, init_param2};
    std::vector<std::string> str_F(2);
    str_F[0] = std::format("-{}*{}*sin(u)+{}*{}*cos(u)", 2 * r2, str_t2, 2 * r2, str_t3);
    str_F[1] = std::format("{}+{}*{}*cos(u)+{}*{}*sin(u)", str_t1t, 2 * r2, str_t2t, 2 * r2, str_t3t);
    std::vector<std::string> str_J(4);
    str_J[0] = std::format("-{}*{}*cos(u)-{}*{}*sin(u)", 2 * r2, str_t2, 2 * r2, str_t3);
    str_J[1] = std::format("-{}*{}*sin(u)-{}*{}*cos(u)", 2 * r2, str_t2t, 2 * r2, str_t3t);
    str_J[2] = str_J[1];
    str_J[3] = std::format("{}+{}*{}*cos(u)+{}*{}*sin(u)", str_t1tt, 2 * r2, str_t2tt, 2 * r2, str_t3tt);

    law* law_F[2] = {nullptr};
    law* law_J[4] = {nullptr};
    for(int i = 0; i < 2; ++i) {
        api_str_to_law(str_F[i].c_str(), &law_F[i]);
    }
    for(int i = 0; i < 4; ++i) {
        api_str_to_law(str_J[i].c_str(), &law_J[i]);
    }

    // 牛顿迭代，获得局部最小值点对
    double* answer = nullptr;
    logical converged = bivariant_newton_iterate(x_init, law_F, law_J, &answer, SPAresabs / 100);
    pt1 = cci_ellipse.eval_position(answer[0]);
    pt2 = cci_helix.eval_position(answer[1]);

    ACIS_DELETE[] STD_CAST answer;
    // 销毁law
    for(int i = 0; i < 2; ++i) {
        if(law_F[i]) {
            law_F[i]->remove();
        }
    }
    for(int i = 0; i < 4; ++i) {
        if(law_J[i]) {
            law_J[i]->remove();
        }
    }
    return converged;
}

/**
 * @brief 求直线和intcurve的最近点对(pt1, pt2)  注意: 该接口目前只支持直线和(圆环-平面)面交线求最近点对
 * @return TRUE: 求得的最近点对收敛  FALSE: 求得的最近点对不收敛
 * @param cci_straight 直线
 * @param cci_intcurve intcurve
 * @param init_pos 初始近似点
 * @param pt1
 * @param pt2
 */
logical MinDistancePointPair(straight const& cci_straight, intcurve const& cci_intcurve, SPAposition const& int_point, SPAposition& pt1, SPAposition& pt2) {
    int_cur const& intc = cci_intcurve.get_int_cur();
    surface const *surf1 = nullptr, *surf2 = nullptr;
    double tol = SPAresabs;
    if(intc.type() == surfintcur_type) {  // cci_intcurve为两个面的交线
        surf1 = &cci_intcurve.surf1();
        surf1 = &cci_intcurve.surf2();
    }
    logical converged = FALSE;
    if(surf1 && surf2 && surf1->type() == torus_type && surf2->type() == plane_type) {  // torus and plane
        // 面交线所在的两个面分别为圆环面和平面
        torus const* tor = dynamic_cast<torus const*>(surf1);
        plane const* pln = dynamic_cast<plane const*>(surf2);

        SPAposition torus_root = tor->centre;
        SPAunit_vector torus_vz = tor->normal;
        SPAunit_vector torus_vx, torus_vy;
        compute_axes_from_z(torus_vz, torus_vx, torus_vy);

        SPAmatrix trans_mat(torus_vx, torus_vy, torus_vz);
        // 平面转化到圆环所在的局部系
        SPAunit_vector pln_normal_loc = normalise(trans_mat * pln->normal);
        SPAposition pln_root_loc = trans_mat * (pln->root_point - torus_root) + SPAposition(0, 0, 0);
        double A = pln_normal_loc.x(), B = pln_normal_loc.y(), C = pln_normal_loc.z();
        double D = -pln_normal_loc % pln_root_loc;

        // 直线转化到圆环所在的局部系
        SPAunit_vector line_dir_loc = normalise(trans_mat * cci_straight.direction);
        SPAposition line_root_loc = trans_mat * (cci_straight.root_point - torus_root) + SPAposition(0, 0, 0);

        double c = tor->major_radius;
        double a = tor->minor_radius;
        double b = line_dir_loc % line_root_loc;
        // A = -1, B = 0, C = 0
        std::string str_Dx, str_Dy;
        int order = 0;

        double x_init[2] = {0};
        /** @todo: 需要添加其他例子 */
        if(fabs(C) > tol) {
            order = 3;  // 解为 x, y
            x_init[0] = int_point.x();
            x_init[1] = int_point.y();

            std::string str_Pxy = std::format("(({}*x+{}*y+{})/{})", A, B, D, C);
            std::string str_Qxy = std::format("((x^2+y^2+{}^2+{})*({}*x+{}*y+{}))", str_Pxy, c * c - a * a, A, B, D);
            std::string str_Rxy = std::format("({}*x+{}*y-{}*{}+{})", line_dir_loc.x(), line_dir_loc.y(), line_dir_loc.z(), str_Pxy, -b);

            str_Dx = std::format("{}^2+{}*(x^2+y^2)", str_Qxy, -4 * c * c);
            str_Dy = std::format("({}*{}*{}+{}*y*{}+{}*y)*({}*{}-x+{})+({}*{}*{}+{}*x*{}+{}*x)*({}*{}-y+{})+({}*{}*y+{}*y+{}*{}*x+{}*x)*({}*{}+{}+{})", -B, str_Qxy, str_Pxy, -C, str_Qxy, 2 * c * c * C, line_dir_loc.x(), str_Rxy, line_root_loc.x(), A,
                                 str_Qxy, str_Pxy, c, str_Pxy, -2 * c * c * C, line_dir_loc.y(), str_Rxy, line_root_loc.y(), A, str_Qxy, -2 * A * c * c, -B, str_Qxy, 2 * B * c * c, line_dir_loc.z(), str_Rxy, line_root_loc.z(), str_Pxy);
        } else if(fabs(B) <= tol && fabs(C) <= tol) {
            // B=0且C=0

            order = 1;  // 解为y, z
            x_init[0] = int_point.y();
            x_init[1] = int_point.z();

            std::string str_Qxy = std::format("(y^2+z^2+{})", c * c - a * a + (D * D) / (A * A));
            std::string str_Rxy = std::format("({}*y+{}*z+{})", line_dir_loc.y(), line_dir_loc.z(), -D * line_dir_loc.x() / A - b);

            str_Dx = std::format("{}^2+{}*({}+y^2)", str_Qxy, -4 * c * c, (D * D) / (A * A));
            str_Dy = std::format("{}*{}*z*({}*{}-y+{})+{}*(4*{}*y+{}*y)*({}*{}-z+{})", -4 * A, str_Qxy, line_dir_loc.y(), str_Rxy, line_root_loc.y(), A, str_Qxy, -8 * c * c, line_dir_loc.z(), str_Rxy, line_root_loc.z());
        }
        law* law_Fs[2] = {nullptr};
        law* law_Js[4] = {nullptr};
        api_str_to_law(str_Dx.c_str(), &law_Fs[0]);
        api_str_to_law(str_Dy.c_str(), &law_Fs[1]);

        law_Js[0] = law_Fs[0]->derivative(0);
        law_Js[1] = law_Fs[0]->derivative(1);
        law_Js[2] = law_Fs[1]->derivative(0);
        law_Js[3] = law_Fs[1]->derivative(1);

        double* x_out = nullptr;
        converged = bivariant_newton_iterate(x_init, law_Fs, law_Js, &x_out, 1e-16);
        // @todo: 需要二元方程组求根，得到正确的根，使用牛顿法需要一个好的初始解，而且容易得到错误的局部最小解
        for(int i = 0; i < 2; ++i) {
            if(law_Fs[i]) law_Fs[i]->remove();
        }
        for(int i = 0; i < 4; ++i) {
            if(law_Js[i]) law_Js[i]->remove();
        }
        if(converged) {
            SPAposition point_in_bs3;
            if(order == 1) {
                point_in_bs3.x() = -(B * x_out[0] + C * x_out[1] + D) / A;
                point_in_bs3.y() = x_out[0];
                point_in_bs3.z() = x_out[1];
            } else if(order == 2) {
                point_in_bs3.x() = x_out[0];
                point_in_bs3.y() = -(A * x_out[0] + C * x_out[1] + D) / B;
                point_in_bs3.z() = x_out[1];
            } else if(order == 3) {
                point_in_bs3.x() = x_out[0];
                point_in_bs3.y() = x_out[1];
                point_in_bs3.z() = -(A * x_out[0] + B * x_out[1] + D) / C;
            }
            double t = point_in_bs3 % line_dir_loc - b;
            SPAposition point_in_str = cci_straight.eval_position(t);
            pt1 = point_in_str;
            pt2 = point_in_bs3;
        }
    }
    return converged;
}

/**
 * @brief 确定unknown:unknown的实际交点关系
 * @param inters 输入/输出 修改后的交点关系
 */
void compute_normal_rel(curve_curve_int*& inters, curve const& cur1, curve const& cur2) {
    auto cci_cur = inters;
    while(cci_cur) {
        if((cci_cur->low_rel == curve_curve_rel::cur_cur_unknown && cci_cur->high_rel == curve_curve_rel::cur_cur_unknown)) {
            if(biparallel(cur1.point_direction(cci_cur->int_point), cur2.point_direction(cci_cur->int_point), SPAresabs / 1000.0)) {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_normal;
            }
        } else if((cci_cur->low_rel == curve_curve_rel::cur_cur_normal && cci_cur->high_rel == curve_curve_rel::cur_cur_normal)) {
            if(biparallel(cur1.point_direction(cci_cur->int_point), cur2.point_direction(cci_cur->int_point))) {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_tangent;
            }
        }
        cci_cur = cci_cur->next;
    }
}

/**
 * @brief 确定unknown:unknown的实际交点关系
 * @param inters 输入/输出 修改后的交点关系
 */
void compute_normal_rel_intcurve(curve_curve_int*& inters, curve const& cur1, curve const& cur2) {
    auto cci_cur = inters;
    while(cci_cur) {
        if((cci_cur->low_rel == curve_curve_rel::cur_cur_unknown && cci_cur->high_rel == curve_curve_rel::cur_cur_unknown)) {
            if(biparallel(cur1.point_direction(cci_cur->int_point), cur2.point_direction(cci_cur->int_point), SPAresabs)) {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_tangent;
            } else {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_normal;
            }
        } else if((cci_cur->low_rel == curve_curve_rel::cur_cur_normal && cci_cur->high_rel == curve_curve_rel::cur_cur_normal)) {
            if(biparallel(cur1.point_direction(cci_cur->int_point), cur2.point_direction(cci_cur->int_point), SPAresabs)) {
                cci_cur->low_rel = cci_cur->high_rel = curve_curve_rel::cur_cur_tangent;
            }
        }
        cci_cur = cci_cur->next;
    }
}

void my_save_entity_list(ENTITY_LIST& elist,    // (in) List of the entities to save
                         const char* file_name  // (in) Name of the SAT file
) {
    API_NOP_BEGIN

    // Set the units and product_id.
    std::string root_dir = "/";
    std::string path = root_dir + file_name;
    FileInfo fileinfo;
    fileinfo.set_units(1.0);
    fileinfo.set_product_id("Example Application");
    check_outcome(api_set_file_info((FileIdent | FileUnits), fileinfo));

    // Also set the option to produce sequence numbers in the SAT file.
    check_outcome(api_set_int_option("sequence_save_files", 1));

    // Open a file for writing, save the list of entities, and close the file.
    FILE* save_file = fopen(path.c_str(), "wb");
    check_outcome(api_save_entity_list(save_file, TRUE, elist));
    fclose(save_file);

    API_NOP_END
}

void save_curve_curve_models(curve const& cur1, curve const& cur2, std::string const& file_name) {
    EDGE *e1 = nullptr, *e2 = nullptr;
    api_make_edge_from_curve(&cur1, e1);
    api_make_edge_from_curve(&cur2, e2);

    ENTITY_LIST edge_list;
    edge_list.add(e1), edge_list.add(e2);

    my_save_entity_list(edge_list, file_name.c_str());
}

double MinDistancePointPair(curve const& cur1, curve const& cur2, SPAposition& pt1, SPAposition& pt2) {
    eed_output_handle* eoh = nullptr;

    // Call EED for two given entities
    EDGE *e1 = nullptr, *e2 = nullptr;
    api_make_edge_from_curve(&cur1, e1);
    api_make_edge_from_curve(&cur2, e2);
    outcome res = api_entity_entity_distance(e1, e2, eoh);

    // Create query object and query EED results from output handle
    const eed_output_query eoq(eoh);
    const double dist = eoq.get_distance();
    pt1 = eoq.get_position(0);
    pt2 = eoq.get_position(1);

    // Delete EED output handle
    ACIS_DELETE eoh;
    api_remove_wire_edges(0, &e1, e1->start_pos(), e1->end_pos(), nullptr);
    api_remove_wire_edges(0, &e2, e2->start_pos(), e2->end_pos(), nullptr);
    return dist;
}

/**
 * @brief 判断平面intcurve是否为圆
 * @return true表示是圆
 * @param cur1 曲线1
 * @param tol 容差
 */
bool intcurve_is_circle(bs3_curve curv1, double tol) {
    bs3_curve curv1_cp = bs3_curve_copy(curv1);
    // 获取curv1_cp的节点向量knot1，curv2_cp的节点向量knot2
    double* knot1 = nullptr;
    int num_knot1 = 0;
    bs3_curve_knots(curv1_cp, num_knot1, knot1);

    double* nknot1 = nullptr;
    nknot1 = ACIS_NEW double[num_knot1];
    int distinct_nknot1 = 0;
    GetKnotNoRepeat(num_knot1, distinct_nknot1, knot1, nknot1);  // 将knot1去重 去重后的节点向量存于nknot1

    SPAposition pos1 = bs3_curve_start(curv1);
    SPAposition pos2 = bs3_curve_end(curv1);

    if(!same_point(pos1, pos2)) {
        ACIS_DELETE[] STD_CAST knot1;
        ACIS_DELETE[] STD_CAST nknot1;
        bs3_curve_delete(curv1_cp);
        return false;
    }

    double knottol = bs3_curve_knottol();
    SPAvector dir1 = bs3_curve_deriv(nknot1[0], curv1_cp);
    double dir1_len = dir1.len();
    int delt = distinct_nknot1 / 50;
    delt = std::max(delt, 1);
    int max_i = 0;
    bool flag = true;
    for(int i = 1; i < distinct_nknot1; i += delt) {
        SPAvector dir2 = bs3_curve_deriv(nknot1[i], curv1_cp);
        if(fabs(dir1_len - dir2.len()) > tol) {
            flag = false;
            break;
        }
        max_i = i;
    }
    if(max_i != distinct_nknot1 - 1) {
        SPAvector dir2 = bs3_curve_deriv(nknot1[distinct_nknot1 - 1], curv1_cp);
        if(fabs(dir1_len - dir2.len()) > tol) {
            flag = false;
        }
    }
    ACIS_DELETE[] STD_CAST knot1;
    ACIS_DELETE[] STD_CAST nknot1;
    bs3_curve_delete(curv1_cp);
    return flag;
}

int CurvCurvIntPointReduce(curve_curve_int*& rt_raw) {
    // 交点剔除策略
    // 1, 当两个交点距离在容差内(SPAresabs)，则需要剔除其中一个交点
    // 2, 交点关系为normal的交点和交点关系为tangent的交点，优先剔除交点关系为normal的交点
    // 3，多个交点关系为tangent的交点，保留第一个交点
    // 4，优先保留交点关系为coin的交点，若多个交点关系为coin的交点则不处理
    curve_curve_int* ret = nullptr;
    for(auto cur = rt_raw; cur; cur = cur->next) {
        for(auto next = cur->next, next_pre = cur; next; next_pre = next, next = next->next) {
            if((!cci_check_coin(cur) || !cci_check_coin(next)) && distance_to_point(cur->int_point, next->int_point) <= SPAresabs) {
                if(!cci_check_tangent(cur) && !cci_check_coin(cur) && cci_check_tangent(next) || cci_check_coin(next)) {
                    auto cur_next = cur->next;
                    *cur = *next;
                    cur->next = cur_next;
                }
                next_pre->next = next->next;
                ACIS_DELETE next;
                next = next_pre;
            }
        }
    }
    return count_inters(rt_raw);
}
