/*******************************************************************/
/*    Copyright (c) 2022-2024 by GME Team.                         */
/*    All rights reserved.                                         */
/*******************************************************************/
/**
 * @file   intersector_nurbs_nurbs_test.cpp
 * @brief nurbs曲线和nurbs曲线求交的测试用例
 */
#include <gtest/gtest.h>

#include "../intersector/cucuint_util.hxx"
#include "acis/bnd_crv.hxx"
#include "acis/bnd_line.hxx"
#include "acis/condef.hxx"
#include "acis/cstrapi.hxx"
#include "acis/cucuint.hxx"
#include "acis/curve.hxx"
#include "acis/curve_approx.hxx"
#include "acis/edge.hxx"
#include "acis/elldef.hxx"
#include "acis/exct_int.hxx"
#include "acis/fit.hxx"
#include "acis/heldef.hxx"
#include "acis/intcucu.hxx"
#include "acis/intcurve.hxx"
#include "acis/intdef.hxx"
#include "acis/intrapi.hxx"
#include "acis/intsfsf.hxx"
#include "acis/kernapi.hxx"
#include "acis/off_int.hxx"
#include "acis/par_int.hxx"
#include "acis/pladef.hxx"
#include "acis/point.hxx"
#include "acis/position.hxx"
#include "acis/sphdef.hxx"
#include "acis/spldef.hxx"
#include "acis/sps2crtn.hxx"
#include "acis/sps3crtn.hxx"
#include "acis/sps3srtn.hxx"
#include "acis/strdef.hxx"
#include "acis/surface.hxx"
#include "acis/tordef.hxx"
#include "acis/unitvec.hxx"
#include "acis/vector.hxx"
#include "acis/vector_utils.hxx"
#include "acis_utils.hpp"
#include "same_entity.hpp"

/**
 * 已测试:
 * case1: 一次nurbs曲线与一次nurbs曲线相交,交于零交点
 * case2: 一次nurbs曲线与一次nurbs曲线相交,交于一交点
 * case3: 一次nurbs曲线与二次nurbs曲线相交,交于一交点
 * case4: 二次nurbs曲线与二次nurbs曲线相交,交于零交点
 * case5: 二次nurbs曲线与二次nurbs曲线相交,交于一交点
 * case6: 二次nurbs曲线与二次nurbs曲线相交,交于二交点
 * case7: 二次nurbs曲线与二次nurbs曲线相交,交于三交点
 * case8: 二次nurbs曲线与三次nurbs曲线相交,交于一交点
 * case9: 二次nurbs曲线与三次nurbs曲线相交,交于二交点
 * case10: 二次nurbs曲线与三次nurbs曲线相交,交于三交点
 */

class NurbsNurbsIntrTest : public ::testing::Test {
  private:
    int level;

  protected:
    void SetUp() override { level = initialize_acis(); }

    void TearDown() override { terminate_acis(level); }
    void judge(curve_curve_int* gme_inters, curve_curve_int* acis_inters) {
        curve_curve_int *tmp_gme = gme_inters, *tmp_acis = acis_inters, *tmp = nullptr;

        while(gme_inters && acis_inters) {
            SPAposition gme_int = gme_inters->int_point;
            SPAposition acis_int = acis_inters->int_point;
            EXPECT_TRUE(fabs(gme_int.x() - acis_int.x()) < 1e-6);              EXPECT_TRUE(fabs(gme_int.y() - acis_int.y()) < 1e-6);
            EXPECT_TRUE(fabs(gme_int.z() - acis_int.z()) < 1e-6);

            EXPECT_TRUE(fabs(gme_inters->param1 - acis_inters->param1) < 1e-6);              EXPECT_TRUE(fabs(gme_inters->param2 - acis_inters->param2) < 1e-6);  
            EXPECT_EQ(gme_inters->high_rel, acis_inters->high_rel);              EXPECT_EQ(gme_inters->low_rel, acis_inters->low_rel);    
            gme_inters = gme_inters->next;
            acis_inters = acis_inters->next;
        }
        EXPECT_TRUE(gme_inters == nullptr && acis_inters == nullptr);  
                while(tmp_gme) {
            tmp = tmp_gme->next;
            ACIS_DELETE tmp_gme;
            tmp_gme = tmp;
        }
        while(tmp_acis) {
            tmp = tmp_acis->next;
            ACIS_DELETE tmp_acis;
            tmp_acis = tmp;
        }
    }
    void pop_cache(curve_curve_int* ptr) {
        curve_curve_int* tmp = nullptr;
        while(ptr) {
            tmp = ptr->next;
            ACIS_DELETE ptr;
            ptr = tmp;
        }
    }
    void pop_cache(surf_surf_int* ptr) {
        surf_surf_int* tmp = nullptr;
        while(ptr) {
            tmp = ptr->next;
            ACIS_DELETE ptr;
            ptr = tmp;
        }
    }
};

TEST_F(NurbsNurbsIntrTest, Degree11NoInters) {
    int degree = 1;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 2;
    SPAposition ctrlpts[] = {
      {5, 5, 0},
      {2, 2, 0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 4;
    double knots[] = {0, 0, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 2;
    SPAposition ctrlpts2[] = {
      {-2, 2,  0},
      {2,  -2, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 4;
    double knots2[] = {0, 0, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree11OneInters) {
    int degree = 1;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 2;
    SPAposition ctrlpts[] = {
      {1,  1,  0},
      {-1, -1, 0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 4;
    double knots[] = {0, 0, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 2;
    SPAposition ctrlpts2[] = {
      {-2, 2,  0},
      {2,  -2, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 4;
    double knots2[] = {0, 0, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree12OneInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 2;
    SPAposition ctrlpts2[] = {
      {3, -2, 0},
      {3, 1,  0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 4;
    double knots2[] = {0, 0, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree22NoInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, -5, 0},
      {1, -1, 0},
      {2, -3, 0},
      {3, -4, 0},
      {4, -3, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree22OneInters) {
    /* @todo: failed case
    * SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    SPAposition ctrlpts2[] = {
      {0, -2,  0},
      {1, -1,  0},
      {2, 0,  0},
      {3, -2, 0},
      {4, -1,  0}
    };
    */
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, -2, 0},
      {1, -1, 0},
      {2, 0,  0},
      {3, -2, 0},
      {4, -1, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree22TwoInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, 1,  0},
      {1, -1, 0},
      {2, -1, 0},
      {3, 1,  0},
      {4, 2,  0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree33ThreeInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, 1,    0},
      {1, -1,   0},
      {2, 0.1,  0},
      {3, 1,    0},
      {4, -0.5, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree23NoInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, -5,   0},
      {1, -6,   0},
      {2, -4.1, 0},
      {3, -3,   0},
      {4, -3.5, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 9;
    double knots2[] = {0, 0, 0, 0, 0.5, 1, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree23OneInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, -6,  0},
      {1, -3,  0},
      {2, 0,   0},
      {3, 3,   0},
      {4, 3.5, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 9;
    double knots2[] = {0, 0, 0, 0, 0.5, 1, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree23ThreeInters) {
    int degree = 2;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 5;
    SPAposition ctrlpts[] = {
      {0, 0,  0},
      {1, 1,  0},
      {2, 0,  0},
      {3, -1, 0},
      {4, 0,  0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0, 0, 0, 0.5, 0.5, 1, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {0, 1,    0},
      {1, -1,   0},
      {2, 0.1,  0},
      {3, 1,    0},
      {4, -0.5, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 9;
    double knots2[] = {0, 0, 0, 0, 0.5, 1, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
        judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree11Coin) {
    int degree = 1;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {1, 1, 0},
      {2, 2, 0},
      {4, 2, 0}
    };
    double weights[] = {1, 1, 1, 1, 1};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 5;
    double knots[] = {0, 0, 0.5, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {3, 2, 0},
      {5, 2, 0},
      {6, 1, 0}
    };
    double weights2[] = {1, 1, 1, 1, 1};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 5;
    double knots2[] = {0, 0, 0.5, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, Degree11BCoin) {
    int degree = 1;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {1, 1, 0},
      {2, 2, 0},
      {4, 2, 0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 5;
    double knots[] = {0, 0, 0.5, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {3, 2, 0},
      {5, 2, 0},
      {6, 1, 0},
      {0, 1, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0, 0, 0.5, 0.5, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, BoxTest1) {
    int degree = 1;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {1, 1, 0},
      {2, 2, 0},
      {4, 2, 0}
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 5;
    double knots[] = {0, 0, 0.5, 1, 1};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 1;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {3, 2, 0},
      {5, 2, 0},
      {6, 1, 0},
      {0, 1, 0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0, 0, 0.5, 0.5, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    SPAposition start_pt(1, 1, 0);
    SPAposition end_pt(3.5, 2, 0);
    SPAbox box(start_pt, end_pt);
        curve_curve_int* acis_inters = int_cur_cur(*ic, *ic2, box);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic, *ic2, box);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestMAF1) {
        int degree1 = 1;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    const int num_ctrlpts1 = 2;
    SPAposition ctrlpts1[] = {
      {-1, 0, 0},
      {1,  0, 0},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 4;
    double knots1[] = {0, 0, 1, 1};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;
    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    const int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {-1, 1,  0},
      {0,  -1, 0},
      {1,  1,  0}
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0, 0, 0, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;
    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    curve_curve_int* acis_inters = int_cur_cur(*ic1, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestMAF2) {
        int degree1 = 1;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    const int num_ctrlpts1 = 2;
    SPAposition ctrlpts1[] = {
      {-1, 0, 0},
      {1,  0, 0},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 4;
    double knots1[] = {0, 0, 1, 1};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;
    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    const int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {-1.0000000000000000, -1.0000000000000000, 0.0000000000000000},
      {-0.3333333333333327, 1.0000000000001497,  0.0000000000000000},
      {0.3333333333333327,  -1.0000000000001497, 0.0000000000000000},
      {1.0000000000000000,  1.0000000000000000,  0.0000000000000000},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0, 0, 0, 0, 1, 1, 1, 1};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;
    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    curve_curve_int* acis_inters = int_cur_cur(*ic1, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestMAF3) {
        int degree1 = 4;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 5;
    SPAposition ctrlpts1[] = {
      {-1,   1,  0},
      {-0.5, -1, 0},
      {0,    1,  0},
      {0.5,  -1, 0},
      {1,    1,  0}
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 10;
    double knots1[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs3_ic = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic_ic = ACIS_NEW exact_int_cur(bs3_ic);
    intcurve* ic = ACIS_NEW intcurve(eic_ic);

    straight st(SPAposition(0, 0, 0), SPAunit_vector(1, 0, 0));
    bs3_curve bs3_line = bs3_curve_make_cur(st, -1, 1);
    exact_int_cur* eic_line = ACIS_NEW exact_int_cur(bs3_line);
    intcurve* ic_line = ACIS_NEW intcurve(eic_line);

    curve_curve_int* acis_inters = int_cur_cur(*ic_line, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic_line, *ic);

            ACIS_DELETE ic;
    ACIS_DELETE ic_line;
}

TEST_F(NurbsNurbsIntrTest, TestBug1) {
        SPAposition base_center1(0, 0, 0);
    SPAunit_vector base_normal1(0, 0, 1);
    SPAvector base_major1(1, 0, 0);
    double base_ratio1 = 1;
    ellipse base1(base_center1, base_normal1, base_major1, base_ratio1);
    cone c1(base1, 0, 1);
    c1.u_param_scale = 1.0;

    SPAposition base_center2(2.5, 0, 0);
    SPAunit_vector base_normal2(-1, 0, 0);
    SPAvector base_major2(0, 0, 5);
    double base_ratio2 = 1;
    ellipse base2(base_center2, base_normal2, base_major2, base_ratio2);
    cone c2(base2, 0.70710678118654757, -0.70710678118654757);
    c2.u_param_scale = 5;

    surf_surf_int* ssi_inters = int_surf_surf(c1, c2, SPAresabs);
    intcurve* ic1 = (intcurve*)ssi_inters->cur;
    intcurve* ic2 = (intcurve*)ssi_inters->cur;
    curve_curve_int* acis_inters = int_cur_cur(*ic1, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug2) {
        SPAposition base_center1(0, 0, 0);
    SPAunit_vector base_normal1(0, 0, 1);
    SPAvector base_major1(1, 0, 0);
    double base_ratio1 = 1;
    ellipse base1(base_center1, base_normal1, base_major1, base_ratio1);
    cone c1(base1, 0, 1);
    c1.u_param_scale = 1.0;

    SPAposition base_center2(2.5, 0, 0);
    SPAunit_vector base_normal2(-1, 0, 0);
    SPAvector base_major2(0, 0, 5);
    double base_ratio2 = 1;
    ellipse base2(base_center2, base_normal2, base_major2, base_ratio2);
    cone c2(base2, 0.70710678118654757, -0.70710678118654757);
    c2.u_param_scale = 5;

    surf_surf_int* ssi_inters = int_surf_surf(c1, c2, SPAresabs);
    intcurve* ic1 = (intcurve*)ssi_inters->cur;
    intcurve* ic2 = (intcurve*)ssi_inters->next->cur;
    curve_curve_int* acis_inters = int_cur_cur(*ic1, *ic2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug3) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {-0.2699999999999998, 0.2530000000000001,  -0.2580741172609141},
      {-0.2699999999999998, 0.1501441177694531,  -0.3325036501812380},
      {-0.2699999999999997, -0.0229999999999999, -0.4344332514898003},
    };
    double weights[] = {1.0000000000000000, 1.0204670657718538, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 6;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.3276189713954389, 0.3276189713954389, 0.3276189713954389};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);
    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, 0.0348670831951338, 0.3059269414085936);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {-0.2580741172609141, 0.2530000000000001,  -0.2699999999999998},
      {-0.3325036501812380, 0.1501441177694531,  -0.2699999999999998},
      {-0.4344332514898003, -0.0229999999999999, -0.2699999999999997},
    };
    double weights2[] = {1.0000000000000000, 1.0204670657718538, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.3276189713954389, 0.3276189713954389, 0.3276189713954389};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);
    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0.0348670831951338, 0.3059269414085936);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug4) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
      {0.5000000000000000, 0.4999999999999999, 0.0000000000000000},
      {1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
    };
    double weights[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 6;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);
    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, 0.0000000000000000, 1.1180339887498949);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {0.0100000000000000, 0.0050000000000000, 0.0000000000000000},
      {0.5100000000000000, 0.5049999999999999, 0.0000000000000000},
      {1.0100000000000000, 0.0050000000000000, 0.0000000000000000},
    };
    double weights2[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);
    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 1.1180339887498949);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug5) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
      {0.5000000000000000, 0.4999999999999999, 0.0000000000000000},
      {1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
    };
    double weights[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 6;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);
    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, 0.0000000000000000, 1.1180339887498949);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {0.0100000000000000, 0.0050000000000000, 0.0000000000000000},
      {0.5100000000000000, 0.5049999999999999, 0.0000000000000000},
      {1.0100000000000000, 0.0050000000000000, 0.0000000000000000},
    };
    double weights2[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);
    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 1.1180339887498949);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug6) {
        int degree = 3;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 4;
    SPAposition ctrlpts[] = {
      {-5.0000000000000000, -4.0000000000000000, 0.0000000000000000},
      {-1.0000000000000000, 3.0000000000000000,  0.0000000000000000},
      {1.0000000000000000,  2.5000000000000000,  0.0000000000000000},
      {4.0000000000000000,  -6.0000000000000000, 0.0000000000000000},
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);
    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, 0.0000000000000000, 80.0000000000000000);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {0.4800000804662687, -0.0199999195337313, 0.0000000000000000},
      {0.9800000804662687, 0.4800000804662687,  0.0000000000000000},
      {1.4800000804662687, -0.0199999195337313, 0.0000000000000000},
    };
    double weights2[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);
    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0, 1.1180339887498949);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug7) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {0.4142463136162469,  -0.2799999850988388, -0.5000000000000000},
      {0.0000000000000000,  -0.2799999850988388, 0.1864000333786002 },
      {-0.4142463136162469, -0.2799999850988388, -0.5000000000000000},
    };
    double weights[] = {1.0000000000000000, 1.7857143807472045, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 6;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.2086356515851986, 1.2086356515851986, 1.2086356515851986};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);
    INTCURVE* intc = ACIS_NEW INTCURVE(*ic);
    ic = (intcurve*)(intc->trans_curve(*(SPAtransf*)nullptr, TRUE));

    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, -1.2086356515851986, -0.1329871980830162);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {0.2799999850988388, 0.4142463136162469,  -0.5000000000000000},
      {0.2799999850988388, 0.0000000000000000,  0.1864000333786002 },
      {0.2799999850988388, -0.4142463136162469, -0.5000000000000000},
    };
    double weights2[] = {1.0000000000000000, 1.7857143807472045, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.2086356515851986, 1.2086356515851986, 1.2086356515851986};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);
    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 1.0756484535021815);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug8) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 3;
    SPAposition ctrlpts[] = {
      {-0.2300000134110452, 0.4439594506606646, 1.0000000000000000},
      {-0.2300000134110451, 0.5987449035666372, 0.7251261414304039},
      {-0.2300000134110451, 0.8804544292392156, 0.1799999910593033},
    };
    double weights[] = {1.0000000000000000, 1.0516614365569177, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 6;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.9289715959599044, 0.9289715959599044, 0.9289715959599044};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    EDGE* e1 = nullptr;
    bounded_curve bnd_curve1(ic, 0.0000000000000000, 0.7431480464793411);
    e1 = bnd_curve1.make_edge();

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 3;
    SPAposition ctrlpts2[] = {
      {-0.4849742558002882, 0.7699999865889549, 0.1799999910593033},
      {0.0000000000000000,  0.7699999865889549, 0.6969231287156331},
      {0.4849742558002882,  0.7699999865889549, 0.1799999910593033},
    };
    double weights2[] = {1.0000000000000000, 1.1818182082074884, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 6;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1200000871717919, 1.1200000871717919, 1.1200000871717919};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    EDGE* e2 = nullptr;
    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 1.0756484535021815);
    e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic2);
    gme_inters = answer_int_cur_cur(*ic, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug10) {
        const char* law_str =
      "PIECEWISE(X<=1,VEC((5+4*(1+(-5+0.25*X)^2)^-1)O(0.1591549430918953*X)*COS(X),(5+4/(1+(X/4-5)^2))O(0.1591549430918953*(X-0)+0)*SIN(X),0.1591549430918953*X),X<=2,VEC((5+4/(1+(X/"
      "4-5)^2))O(((((-23.8380275608647+92.30703990201039*X)-137.98309502374*X^2)+99.44225092635639*X^3)-34.33661881284312*X^4)+4.567605512172958*X^5)*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(((((-23.8380275608647+92.30703990201039*X)-137.98309502374*X^2)+99.44225092635639*X^3)-34.33661881284312*X^4)+4.567605512172958*X^5)*SIN(X),((((-23.8380275608647+92.30703990201039*X)-137.98309502374*X^2)+99.44225092635639*X^3)-34."
      "33661881284312*X^4)+4.567605512172958*X^5),X<=4,VEC((5+4*(1+(-5+0.25*X)^2)^-1)O(1.159154943091895+0.3183098861837907*(-2+X))*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(0.3183098861837907*(X-2)+1.159154943091895)*SIN(X),1.159154943091895+0.3183098861837907*(-2+X)),X<=6,VEC((5+4/(1+(X/"
      "4-5)^2))O(((((-621.1337686929605+655.0563019446372*X)-272.3830835094442*X^2)+55.89436308886397*X^3)-5.654753205226936*X^4)+0.2257922408513477*X^5)*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(((((-621.1337686929605+655.0563019446372*X)-272.3830835094442*X^2)+55.89436308886397*X^3)-5.654753205226936*X^4)+0.2257922408513477*X^5)*SIN(X),((((-621.1337686929605+655.0563019446372*X)-272.3830835094442*X^2)+55.89436308886397*X^3)-5."
      "654753205226936*X^4)+0.2257922408513477*X^5),X<=9,VEC((5+4*(1+(-5+0.25*X)^2)^-1)O(3.795774715459477+0.477464829275686*(-6+X))*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(0.477464829275686*(X-6)+3.795774715459477)*SIN(X),3.795774715459477+0.477464829275686*(-6+X)),X<=12,VEC((5+4/(1+(X/"
      "4-5)^2))O(((((-5953.253277191299+2919.595655734413*X)-568.79997697141*X^2)+55.04506820917178*X^3)-2.645122481763335*X^4)+0.05049556398638586*X^5)*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(((((-5953.253277191299+2919.595655734413*X)-568.79997697141*X^2)+55.04506820917178*X^3)-2.645122481763335*X^4)+0.05049556398638586*X^5)*SIN(X),((((-5953.253277191299+2919.595655734413*X)-568.79997697141*X^2)+55.04506820917178*X^3)-2."
      "645122481763335*X^4)+0.05049556398638586*X^5),VEC((5+4*(1+(-5+0.25*X)^2)^-1)O(8.228169203286534+0.1591549430918953*(-12+X))*COS(X),(5+4/(1+(X/"
      "4-5)^2))O(0.1591549430918953*(X-12)+8.228169203286534)*SIN(X),8.228169203286534+0.1591549430918953*(-12+X)))";
    law* curv_law = nullptr;
    api_str_to_law(law_str, &curv_law);
    curve* ic = nullptr;
    EDGE* e1 = nullptr;
    api_curve_law(curv_law, 0, 13, ic);

    SPAmatrix affine_mat(SPAvector(0, -1, 0), SPAvector(1, 0, 0), SPAvector(0, 0, 1));
    SPAvector translate_vec(0, 10, 0);
    SPAtransf transf(affine_mat, translate_vec, 1.0, TRUE, FALSE, FALSE);
    (*ic) *= transf;

    bounded_curve bnd_curv(ic, 0, 13);
    e1 = bnd_curv.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *ic);
    gme_inters = answer_int_cur_cur(*ic, *ic);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
}


TEST_F(NurbsNurbsIntrTest, TestBug12) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 12;
    SPAposition ctrlpts1[] = {
      {-0.5000000000000000, -0.0000000000000001, -0.0000000000000001},
      {-0.5000000000000000, 0.0002721655698160,  0.0001924501200224 },
      {-0.4999998888888539, 0.0005443311320739,  0.0003849002347009 },
      {-0.4998795442001527, 0.1479358523117443,  0.1046063922393884 },
      {-0.4672943582509727, 0.2935925320258120,  0.2076775486696102 },
      {-0.3629816616558060, 0.5318779927671833,  0.3509165170571031 },
      {-0.3091250794673812, 0.6244493646441580,  0.3999257339287915 },
      {-0.1699664764308801, 0.8190952020303495,  0.4779107959948102 },
      {-0.0861703731330847, 0.9137528646477214,  0.4998466809364790 },
      {-0.0005962444763305, 0.9994036221785692,  0.4999997333097786 },
      {-0.0002981555828332, 0.9997018444171667,  0.5000000000000000 },
      {0.0000000000000001,  1.0000000000000000,  0.5000000000000000 },
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 16;
    double knots1[] = {-1.1589238018614014, -1.1589238018614014, -1.1589238018614014, -1.1589238018614014, -1.1580327610224805, -1.1580327610224805, -0.6763797678503988, -0.6763797678503988,
                       -0.3619581939755130, -0.3619581939755130, -0.0000000000000000, -0.0000000000000000, 0.0012649670068202,  0.0012649670068202,  0.0012649670068202,  0.0012649670068202};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition base_center1(0, 0.5, 0);
    SPAunit_vector base_normal1(0, 1, 0);
    SPAvector base_maj1(0.5, 0, 0);
    double base_ratio1 = 1.0;
    ellipse base1(base_center1, base_normal1, base_maj1, base_ratio1);
    cone c1(base1, 0, 1);
    c1.u_param_scale = 0.5;

    SPAposition tor_center1(0, 0, 0);
    SPAunit_vector tor_normal1(0, 0, 1);
    torus tor1(tor_center1, tor_normal1, 1, 0.5);

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0000322294188268, c1, tor1);
    INTCURVE* intc = ACIS_NEW INTCURVE(*ic1);
    ic1 = (intcurve*)intc->trans_curve(*((SPAtransf*)nullptr), TRUE);

    bounded_curve bnd_curve1(ic1, -0.0012649670068202, 1.1589238018614014);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 12;
    SPAposition ctrlpts2[] = {
      {0.0000000000000001,  1.0000000000000000,  -0.5000000000000000},
      {-0.0002981555828815, 0.9997018444171185,  -0.5000000000000000},
      {-0.0005962444762823, 0.9994036221786179,  -0.4999997333097787},
      {-0.0861703731957244, 0.9137528645849931,  -0.4998466809363669},
      {-0.1699664764838051, 0.8190952019563250,  -0.4779107959651547},
      {-0.3091250794674014, 0.6244493646441268,  -0.3999257339287768},
      {-0.3629816616558271, 0.5318779927671446,  -0.3509165170570819},
      {-0.4672943582509793, 0.2935925320257817,  -0.2076775486695886},
      {-0.4998795442001528, 0.1479358523117293,  -0.1046063922393779},
      {-0.4999998888888539, 0.0005443311320740,  -0.0003849002347010},
      {-0.5000000000000000, 0.0002721655698159,  -0.0001924501200224},
      {-0.5000000000000000, -0.0000000000000001, -0.0000000000000001},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 16;
    double knots2[] = {-1.3010603550489723, -1.3010603550489723, -1.3010603550489723, -1.3010603550489723, -1.2996407038398978, -1.2996407038398978, -0.8934211066206694, -0.8934211066206694,
                       -0.5405510588828307, -0.5405510588828307, -0.0000000000000000, -0.0000000000000000, 0.0010000001574045,  0.0010000001574045,  0.0010000001574045,  0.0010000001574045};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    SPAposition base_center2(0, 0.5, 0);
    SPAunit_vector base_normal2(0, 1, 0);
    SPAvector base_maj2(0.5, 0, 0);
    double base_ratio2 = 1.0;
    ellipse base2(base_center2, base_normal2, base_maj2, base_ratio2);
    cone c2(base2, 0, 1);
    c2.u_param_scale = 0.5;

    SPAposition tor_center2(0, 0, 0);
    SPAunit_vector tor_normal2(0, 0, 1);
    torus tor2(tor_center2, tor_normal2, 1, 0.5);

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0000322294188268, c2, tor2);

    bounded_curve bnd_curve2(ic2, -1.3010603550489723, 0.0010000001574045);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug13) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 23;
    SPAposition ctrlpts1[] = {
      {0.4612785735530810,  0.8872553621031745, -0.1929302401927570},
      {0.4869427922383796,  0.8739127179764675, -0.1315693006316425},
      {0.5000000000000000,  0.8660254037844386, -0.0641525334802454},
      {0.5000000000000000,  0.8660254037844386, 0.0641525334802456 },
      {0.4869427922383797,  0.8739127179764679, 0.1315693006316428 },
      {0.4356143548681130,  0.9005980062303398, 0.2542911797539109 },
      {0.3973779140655170,  0.9188502337744185, 0.3097288671210305 },
      {0.3098483349031312,  0.9519333050352490, 0.3972584462834162 },
      {0.2543703790571872,  0.9691324205197391, 0.4355825399622905 },
      {0.1314725377444275,  0.9932959841753269, 0.4869819529345641 },
      {0.0639776505543443,  1.0000000000000000, 0.5000000000000000 },
      {-0.0639776505543445, 1.0000000000000000, 0.5000000000000000 },
      {-0.1314725377444278, 0.9932959841753271, 0.4869819529345640 },
      {-0.2543703790571875, 0.9691324205197391, 0.4355825399622903 },
      {-0.3098483349031315, 0.9519333050352490, 0.3972584462834161 },
      {-0.3973779140655173, 0.9188502337744184, 0.3097288671210303 },
      {-0.4356143548681131, 0.9005980062303395, 0.2542911797539106 },
      {-0.4869427922383797, 0.8739127179764675, 0.1315693006316425 },
      {-0.5000000000000000, 0.8660254037844386, 0.0641525334802454 },
      {-0.5000000000000000, 0.8660254037844386, 0.0000000000000000 },
      {-0.5000000000000000, 0.8660254037844386, -0.0641525334802457},
      {-0.4869427922383796, 0.8739127179764679, -0.1315693006316429},
      {-0.4612785735530807, 0.8872553621031742, -0.1929302401927577},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 27;
    double knots1[] = {-1.7300198088558161, -1.7300198088558161, -1.7300198088558161, -1.7300198088558161, -1.5375622084150797, -1.5375622084150797, -1.3451046079743429, -1.3451046079743429, -1.1526470075336064,
                       -1.1526470075336064, -0.9607140558705729, -0.9607140558705729, -0.7687811042075396, -0.7687811042075396, -0.5768481525445064, -0.5768481525445064, -0.3849152008814731, -0.3849152008814731,
                       -0.1924576004407363, -0.1924576004407363, 0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.1924576004407370,  0.1924576004407370,  0.1924576004407370,  0.1924576004407370};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition base_center11(0, 0.5, 0);
    SPAunit_vector base_normal11(0, 1, 0);
    SPAvector base_maj11(0.5, 0, 0);
    double base_ratio11 = 1.0;
    ellipse base11(base_center11, base_normal11, base_maj11, base_ratio11);
    cone c11(base11, 0, 1);
    c11.u_param_scale = 0.5;

    SPAposition base_center12(0, 0, 0);
    SPAunit_vector base_normal12(0, 0, 1);
    SPAvector base_maj12(1, 0, 0);
    double base_ratio12 = 1.0;
    ellipse base12(base_center12, base_normal12, base_maj12, base_ratio12);
    cone c12(base12, 0, 1);
    c12.u_param_scale = 1;

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0002946213969872, c11, c12);
    INTCURVE* intc = ACIS_NEW INTCURVE(*ic1);
    ic1 = (intcurve*)intc->trans_curve(*((SPAtransf*)nullptr), TRUE);

    bounded_curve bnd_curve1(ic1, 0.7687811042075396, 1.5375622084150797);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 23;
    SPAposition ctrlpts2[] = {
      {0.4612785735530810,  0.8872553621031745, -0.1929302401927570},
      {0.4869427922383796,  0.8739127179764675, -0.1315693006316425},
      {0.5000000000000000,  0.8660254037844386, -0.0641525334802454},
      {0.5000000000000000,  0.8660254037844386, 0.0641525334802456 },
      {0.4869427922383797,  0.8739127179764679, 0.1315693006316428 },
      {0.4356143548681130,  0.9005980062303398, 0.2542911797539109 },
      {0.3973779140655170,  0.9188502337744185, 0.3097288671210305 },
      {0.3098483349031312,  0.9519333050352490, 0.3972584462834162 },
      {0.2543703790571872,  0.9691324205197391, 0.4355825399622905 },
      {0.1314725377444275,  0.9932959841753269, 0.4869819529345641 },
      {0.0639776505543443,  1.0000000000000000, 0.5000000000000000 },
      {-0.0639776505543445, 1.0000000000000000, 0.5000000000000000 },
      {-0.1314725377444278, 0.9932959841753271, 0.4869819529345640 },
      {-0.2543703790571875, 0.9691324205197391, 0.4355825399622903 },
      {-0.3098483349031315, 0.9519333050352490, 0.3972584462834161 },
      {-0.3973779140655173, 0.9188502337744184, 0.3097288671210303 },
      {-0.4356143548681131, 0.9005980062303395, 0.2542911797539106 },
      {-0.4869427922383797, 0.8739127179764675, 0.1315693006316425 },
      {-0.5000000000000000, 0.8660254037844386, 0.0641525334802454 },
      {-0.5000000000000000, 0.8660254037844386, 0.0000000000000000 },
      {-0.5000000000000000, 0.8660254037844386, -0.0641525334802457},
      {-0.4869427922383796, 0.8739127179764679, -0.1315693006316429},
      {-0.4612785735530807, 0.8872553621031742, -0.1929302401927577},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 27;
    double knots2[] = {-1.7300198088558161, -1.7300198088558161, -1.7300198088558161, -1.7300198088558161, -1.5375622084150797, -1.5375622084150797, -1.3451046079743429, -1.3451046079743429, -1.1526470075336064,
                       -1.1526470075336064, -0.9607140558705729, -0.9607140558705729, -0.7687811042075396, -0.7687811042075396, -0.5768481525445064, -0.5768481525445064, -0.3849152008814731, -0.3849152008814731,
                       -0.1924576004407363, -0.1924576004407363, 0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.1924576004407370,  0.1924576004407370,  0.1924576004407370,  0.1924576004407370};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    SPAposition base_center21(0, 0.5, 0);
    SPAunit_vector base_normal21(0, 1, 0);
    SPAvector base_maj21(0.5, 0, 0);
    double base_ratio21 = 1.0;
    ellipse base21(base_center21, base_normal21, base_maj21, base_ratio21);
    cone c21(base21, 0, 1);
    c21.u_param_scale = 0.5;

    SPAposition base_center22(0, 0, 0);
    SPAunit_vector base_normal22(0, 0, 1);
    SPAvector base_maj22(1, 0, 0);
    double base_ratio22 = 1.0;
    ellipse base22(base_center22, base_normal22, base_maj22, base_ratio22);
    cone c22(base22, 0, 1);
    c22.u_param_scale = 1;

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0002946213969872, c21, c22);

    bounded_curve bnd_curve2(ic2, -0.7687811042075396, 0.0000000000000000);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug14) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = TRUE;
    int num_ctrlpts1 = 40;
    SPAposition ctrlpts1[] = {
      {0.1286724217339934,  0.9891783983354827,  0.0704947100962910 },
      {0.1452559167417971,  0.9863557409547101,  0.0798326198854881 },
      {0.1616995213610047,  0.9829850910720617,  0.0892400238163372 },
      {0.2679104848775904,  0.9574197206092965,  0.1513045085001104 },
      {0.3507176472209139,  0.9196387392333923,  0.2065159328727125 },
      {0.4927388059833653,  0.8147320031192798,  0.3231468123955867 },
      {0.5501149391354220,  0.7497161059913756,  0.3824130745256417 },
      {0.6522388633419938,  0.5772369061891965,  0.5088293937662806 },
      {0.6886073278604391,  0.4650970760259099,  0.5718956732332461 },
      {0.7312414040885659,  0.2286122848299073,  0.6540405545853599 },
      {0.7397566526262108,  0.1086705139088038,  0.6751322567038195 },
      {0.7383278768104534,  -0.1365776569536579, 0.6718976820659549 },
      {0.7281557523868739,  -0.2573417905655433, 0.6470502689980444 },
      {0.6806777995690483,  -0.4930082066995721, 0.5580527266019150 },
      {0.6411072577867230,  -0.6037511587832117, 0.4922145508729633 },
      {0.5328355353729674,  -0.7709311080533053, 0.3639435046634583 },
      {0.4734310898985825,  -0.8326893850882384, 0.3053794743479692 },
      {0.3267940123012751,  -0.9321686517746876, 0.1895280973180395 },
      {0.2409730842239938,  -0.9671605203319977, 0.1345306445557818 },
      {0.0492870290702904,  -1.0052365143078004, 0.0250882185709501 },
      {-0.0551952180353867, -1.0048504510754415, -0.0282258616067216},
      {-0.2462841768779460, -0.9653353039160281, -0.1377933605708417},
      {-0.3315192192392675, -0.9297919629071976, -0.1928316362366655},
      {-0.4772399923218128, -0.8292592284888882, -0.3088273046409860},
      {-0.5362419287053930, -0.7668883555242608, -0.3675205630608542},
      {-0.6428826570500548, -0.5993662933881920, -0.4949372170927820},
      {-0.6817046799648948, -0.4892398378783872, -0.5598477595687791},
      {-0.7283293895588197, -0.2552248795588263, -0.6474984132422479},
      {-0.7383409565045876, -0.1354364076318069, -0.6719272858136908},
      {-0.7397577608230015, 0.1099717680394934,  -0.6751347726612253},
      {-0.7310731733096858, 0.2310522341244645,  -0.6535925776956597},
      {-0.6877042814031166, 0.4684289356306250,  -0.5702935642805590},
      {-0.6509526159016097, 0.5804491656371248,  -0.5068663006223088},
      {-0.5480756952227674, 0.7523117149123189,  -0.3801913652579798},
      {-0.4904647466248732, 0.8169248309463861,  -0.3210147780167564},
      {-0.3479022332051305, 0.9211767670516180,  -0.2044831168747394},
      {-0.2647359355960937, 0.9586330008370352,  -0.1492970672960852},
      {-0.0759264790753317, 1.0031217693355470,  -0.0392912416130301},
      {0.0284557032907541,  1.0062361693214845,  0.0140642244988961 },
      {0.1286724217339934,  0.9891783983354827,  0.0704947100962910 },
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 44;
    double knots1[] = {-6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.2834587115005531, -6.2834587115005531, -5.9642626015625284, -5.9642626015625284, -5.6504872402244830, -5.6504872402244830, -5.2533556164226081,
                       -5.2533556164226081, -4.8894252073663855, -4.8894252073663855, -4.5209261151345768, -4.5209261151345768, -4.1209388660240132, -4.1209388660240132, -3.8108511013907038, -3.8108511013907038, -3.4882221161548381, -3.4882221161548381,
                       -3.1388992525516919, -3.1388992525516919, -2.8170816882659140, -2.8170816882659140, -2.5065422298125397, -2.5065422298125397, -2.1102152537052965, -2.1102152537052965, -1.7450999860042791, -1.7450999860042791, -1.3779713307773203,
                       -1.3779713307773203, -0.9808041568975095, -0.9808041568975095, -0.6679383193330120, -0.6679383193330120, -0.3488105806905831, -0.3488105806905831, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition sph_center1(0, 0, 0);
    double sph_radius1 = 1.0;
    sphere sph1(sph_center1, sph_radius1);
    sph1.uv_oridir = SPAunit_vector(1, 0, 0);
    sph1.pole_dir = SPAunit_vector(0, 0, 1);

    const char* sur1_str = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur1_law = nullptr;
    api_str_to_law(sur1_str, &sur1_law);
    FACE* face1 = nullptr;
    api_face_law(sur1_law, -10, 10, -10, 10, face1);
    surface const& sur1 = face1->geometry()->equation();

    bs2_curve pcurve1 = nullptr;
    int degree_p1 = 3;
    logical rational_p1 = FALSE;
    logical closed_p1 = FALSE;
    logical periodic_p1 = TRUE;
    const int num_ctrlpts_p1 = 58;
    SPAposition ctrlpts_p1[] = {
      {0.1286724217339934,  0.9891783983354827,  0.0000000000000000},
      {0.1452559167417971,  0.9863557409547101,  0.0000000000000000},
      {0.1616995213610047,  0.9829850910720617,  0.0000000000000000},
      {0.1779643804637043,  0.9790700795260054,  0.0000000000000000},
      {0.2679104848775904,  0.9574197206092965,  0.0000000000000000},
      {0.3507176472209139,  0.9196387392333923,  0.0000000000000000},
      {0.4223363590634470,  0.8667361621134280,  0.0000000000000000},
      {0.4927388059833653,  0.8147320031192798,  0.0000000000000000},
      {0.5501149391354220,  0.7497161059913756,  0.0000000000000000},
      {0.5951897124728500,  0.6735883925598163,  0.0000000000000000},
      {0.6522388633419938,  0.5772369061891965,  0.0000000000000000},
      {0.6886073278604391,  0.4650970760259099,  0.0000000000000000},
      {0.7108543185008536,  0.3416963740103007,  0.0000000000000000},
      {0.7312414040885659,  0.2286122848299072,  0.0000000000000000},
      {0.7397566526262108,  0.1086705139088038,  0.0000000000000000},
      {0.7390467208632714,  -0.0131886779797092, 0.0000000000000000},
      {0.7383278768104534,  -0.1365776569536579, 0.0000000000000000},
      {0.7281557523868739,  -0.2573417905655433, 0.0000000000000000},
      {0.7053894628991095,  -0.3703468704778530, 0.0000000000000000},
      {0.6806777995690483,  -0.4930082066995721, 0.0000000000000000},
      {0.6411072577867230,  -0.6037511587832116, 0.0000000000000000},
      {0.5801174925274122,  -0.6979240936431736, 0.0000000000000000},
      {0.5328355353729674,  -0.7709311080533053, 0.0000000000000000},
      {0.4734310898985825,  -0.8326893850882384, 0.0000000000000000},
      {0.4015658143010707,  -0.8814431180035438, 0.0000000000000000},
      {0.3267940123012751,  -0.9321686517746876, 0.0000000000000000},
      {0.2409730842239938,  -0.9671605203319977, 0.0000000000000000},
      {0.1489375052387469,  -0.9854422161402390, 0.0000000000000000},
      {0.0492870290702904,  -1.0052365143078004, 0.0000000000000000},
      {-0.0551952180353867, -1.0048504510754415, 0.0000000000000000},
      {-0.1546553899040291, -0.9842831542954738, 0.0000000000000000},
      {-0.2462841768779460, -0.9653353039160281, 0.0000000000000000},
      {-0.3315192192392675, -0.9297919629071976, 0.0000000000000000},
      {-0.4056790728867057, -0.8786290935816599, 0.0000000000000000},
      {-0.4772399923218128, -0.8292592284888882, 0.0000000000000000},
      {-0.5362419287053930, -0.7668883555242608, 0.0000000000000000},
      {-0.5830911669915615, -0.6932928247263330, 0.0000000000000000},
      {-0.6428826570500548, -0.5993662933881920, 0.0000000000000000},
      {-0.6817046799648948, -0.4892398378783872, 0.0000000000000000},
      {-0.7059726140275231, -0.3674361928234529, 0.0000000000000000},
      {-0.7283293895588195, -0.2552248795588263, 0.0000000000000000},
      {-0.7383409565045876, -0.1354364076318069, 0.0000000000000000},
      {-0.7390474108318958, -0.0130697085707094, 0.0000000000000000},
      {-0.7397577608230015, 0.1099717680394934,  0.0000000000000000},
      {-0.7310731733096858, 0.2310522341244645,  0.0000000000000000},
      {-0.7102409741035878, 0.3450758698520300,  0.0000000000000000},
      {-0.6877042814031166, 0.4684289356306250,  0.0000000000000000},
      {-0.6509526159016097, 0.5804491656371248,  0.0000000000000000},
      {-0.5934069311448411, 0.6765829536318009,  0.0000000000000000},
      {-0.5480756952227674, 0.7523117149123189,  0.0000000000000000},
      {-0.4904647466248732, 0.8169248309463861,  0.0000000000000000},
      {-0.4198897568693383, 0.8685343259400575,  0.0000000000000000},
      {-0.3479022332051305, 0.9211767670516180,  0.0000000000000000},
      {-0.2647359355960937, 0.9586330008370352,  0.0000000000000000},
      {-0.1745265058482310, 0.9798888558688201,  0.0000000000000000},
      {-0.0759264790753317, 1.0031217693355470,  0.0000000000000000},
      {0.0284557032907541,  1.0062361693214845,  0.0000000000000000},
      {0.1286724217339934,  0.9891783983354827,  0.0000000000000000},
    };
    double* weights_p1 = nullptr;
    double ctrlpt_tol_p1 = SPAresabs;
    int num_knots_p1 = 62;
    double knots_p1[] = {-6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.2834587115005531, -6.2834587115005531, -6.2834587115005531, -5.9642626015625284, -5.9642626015625284, -5.9642626015625284, -5.6504872402244830,
                         -5.6504872402244830, -5.6504872402244830, -5.2533556164226081, -5.2533556164226081, -5.2533556164226081, -4.8894252073663855, -4.8894252073663855, -4.8894252073663855, -4.5209261151345768, -4.5209261151345768, -4.5209261151345768,
                         -4.1209388660240132, -4.1209388660240132, -4.1209388660240132, -3.8108511013907038, -3.8108511013907038, -3.8108511013907038, -3.4882221161548381, -3.4882221161548381, -3.4882221161548381, -3.1388992525516919, -3.1388992525516919,
                         -3.1388992525516919, -2.8170816882659140, -2.8170816882659140, -2.8170816882659140, -2.5065422298125397, -2.5065422298125397, -2.5065422298125397, -2.1102152537052965, -2.1102152537052965, -2.1102152537052965, -1.7450999860042791,
                         -1.7450999860042791, -1.7450999860042791, -1.3779713307773203, -1.3779713307773203, -1.3779713307773203, -0.9808041568975095, -0.9808041568975095, -0.9808041568975095, -0.6679383193330120, -0.6679383193330120, -0.6679383193330120,
                         -0.3488105806905831, -0.3488105806905831, -0.3488105806905831, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000};
    double knot_tol_p1 = SPAresabs;
    const int dimension_p1 = 2;
    bs2_curve pcurve12 = bs2_curve_from_ctrlpts(degree_p1, rational_p1, closed_p1, periodic_p1, num_ctrlpts_p1, ctrlpts_p1, weights_p1, ctrlpt_tol_p1, num_knots_p1, knots_p1, knot_tol_p1);

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0001542923958404, sph1, sur1, pcurve1, pcurve12);

    bounded_curve bnd_curve1(ic1, -3.2372152064450330, -2.2634510335697047);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = TRUE;
    int num_ctrlpts2 = 40;
    SPAposition ctrlpts2[] = {
      {0.1286724217339934,  0.9891783983354827,  0.0704947100962910 },
      {0.1452559167417971,  0.9863557409547101,  0.0798326198854881 },
      {0.1616995213610047,  0.9829850910720617,  0.0892400238163372 },
      {0.2679104848775904,  0.9574197206092965,  0.1513045085001104 },
      {0.3507176472209139,  0.9196387392333923,  0.2065159328727125 },
      {0.4927388059833653,  0.8147320031192798,  0.3231468123955867 },
      {0.5501149391354220,  0.7497161059913756,  0.3824130745256417 },
      {0.6522388633419938,  0.5772369061891965,  0.5088293937662806 },
      {0.6886073278604391,  0.4650970760259099,  0.5718956732332461 },
      {0.7312414040885659,  0.2286122848299073,  0.6540405545853599 },
      {0.7397566526262108,  0.1086705139088038,  0.6751322567038195 },
      {0.7383278768104534,  -0.1365776569536579, 0.6718976820659549 },
      {0.7281557523868739,  -0.2573417905655433, 0.6470502689980444 },
      {0.6806777995690483,  -0.4930082066995721, 0.5580527266019150 },
      {0.6411072577867230,  -0.6037511587832117, 0.4922145508729633 },
      {0.5328355353729674,  -0.7709311080533053, 0.3639435046634583 },
      {0.4734310898985825,  -0.8326893850882384, 0.3053794743479692 },
      {0.3267940123012751,  -0.9321686517746876, 0.1895280973180395 },
      {0.2409730842239938,  -0.9671605203319977, 0.1345306445557818 },
      {0.0492870290702904,  -1.0052365143078004, 0.0250882185709501 },
      {-0.0551952180353867, -1.0048504510754415, -0.0282258616067216},
      {-0.2462841768779460, -0.9653353039160281, -0.1377933605708417},
      {-0.3315192192392675, -0.9297919629071976, -0.1928316362366655},
      {-0.4772399923218128, -0.8292592284888882, -0.3088273046409860},
      {-0.5362419287053930, -0.7668883555242608, -0.3675205630608542},
      {-0.6428826570500548, -0.5993662933881920, -0.4949372170927820},
      {-0.6817046799648948, -0.4892398378783872, -0.5598477595687791},
      {-0.7283293895588197, -0.2552248795588263, -0.6474984132422479},
      {-0.7383409565045876, -0.1354364076318069, -0.6719272858136908},
      {-0.7397577608230015, 0.1099717680394934,  -0.6751347726612253},
      {-0.7310731733096858, 0.2310522341244645,  -0.6535925776956597},
      {-0.6877042814031166, 0.4684289356306250,  -0.5702935642805590},
      {-0.6509526159016097, 0.5804491656371248,  -0.5068663006223088},
      {-0.5480756952227674, 0.7523117149123189,  -0.3801913652579798},
      {-0.4904647466248732, 0.8169248309463861,  -0.3210147780167564},
      {-0.3479022332051305, 0.9211767670516180,  -0.2044831168747394},
      {-0.2647359355960937, 0.9586330008370352,  -0.1492970672960852},
      {-0.0759264790753317, 1.0031217693355470,  -0.0392912416130301},
      {0.0284557032907541,  1.0062361693214845,  0.0140642244988961 },
      {0.1286724217339934,  0.9891783983354827,  0.0704947100962910 },
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 44;
    double knots2[] = {-6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.2834587115005531, -6.2834587115005531, -5.9642626015625284, -5.9642626015625284, -5.6504872402244830, -5.6504872402244830, -5.2533556164226081,
                       -5.2533556164226081, -4.8894252073663855, -4.8894252073663855, -4.5209261151345768, -4.5209261151345768, -4.1209388660240132, -4.1209388660240132, -3.8108511013907038, -3.8108511013907038, -3.4882221161548381, -3.4882221161548381,
                       -3.1388992525516919, -3.1388992525516919, -2.8170816882659140, -2.8170816882659140, -2.5065422298125397, -2.5065422298125397, -2.1102152537052965, -2.1102152537052965, -1.7450999860042791, -1.7450999860042791, -1.3779713307773203,
                       -1.3779713307773203, -0.9808041568975095, -0.9808041568975095, -0.6679383193330120, -0.6679383193330120, -0.3488105806905831, -0.3488105806905831, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    bs2_curve pcurve2 = nullptr;
    int degree_p2 = 3;
    logical rational_p2 = FALSE;
    logical closed_p2 = FALSE;
    logical periodic_p2 = TRUE;
    const int num_ctrlpts_p2 = 58;
    SPAposition ctrlpts_p2[] = {
      {0.1286724217339934,  0.9891783983354827,  0.0000000000000000},
      {0.1452559167417971,  0.9863557409547101,  0.0000000000000000},
      {0.1616995213610047,  0.9829850910720617,  0.0000000000000000},
      {0.1779643804637043,  0.9790700795260054,  0.0000000000000000},
      {0.2679104848775904,  0.9574197206092965,  0.0000000000000000},
      {0.3507176472209139,  0.9196387392333923,  0.0000000000000000},
      {0.4223363590634470,  0.8667361621134280,  0.0000000000000000},
      {0.4927388059833653,  0.8147320031192798,  0.0000000000000000},
      {0.5501149391354220,  0.7497161059913756,  0.0000000000000000},
      {0.5951897124728500,  0.6735883925598163,  0.0000000000000000},
      {0.6522388633419938,  0.5772369061891965,  0.0000000000000000},
      {0.6886073278604391,  0.4650970760259099,  0.0000000000000000},
      {0.7108543185008536,  0.3416963740103007,  0.0000000000000000},
      {0.7312414040885659,  0.2286122848299072,  0.0000000000000000},
      {0.7397566526262108,  0.1086705139088038,  0.0000000000000000},
      {0.7390467208632714,  -0.0131886779797092, 0.0000000000000000},
      {0.7383278768104534,  -0.1365776569536579, 0.0000000000000000},
      {0.7281557523868739,  -0.2573417905655433, 0.0000000000000000},
      {0.7053894628991095,  -0.3703468704778530, 0.0000000000000000},
      {0.6806777995690483,  -0.4930082066995721, 0.0000000000000000},
      {0.6411072577867230,  -0.6037511587832116, 0.0000000000000000},
      {0.5801174925274122,  -0.6979240936431736, 0.0000000000000000},
      {0.5328355353729674,  -0.7709311080533053, 0.0000000000000000},
      {0.4734310898985825,  -0.8326893850882384, 0.0000000000000000},
      {0.4015658143010707,  -0.8814431180035438, 0.0000000000000000},
      {0.3267940123012751,  -0.9321686517746876, 0.0000000000000000},
      {0.2409730842239938,  -0.9671605203319977, 0.0000000000000000},
      {0.1489375052387469,  -0.9854422161402390, 0.0000000000000000},
      {0.0492870290702904,  -1.0052365143078004, 0.0000000000000000},
      {-0.0551952180353867, -1.0048504510754415, 0.0000000000000000},
      {-0.1546553899040291, -0.9842831542954738, 0.0000000000000000},
      {-0.2462841768779460, -0.9653353039160281, 0.0000000000000000},
      {-0.3315192192392675, -0.9297919629071976, 0.0000000000000000},
      {-0.4056790728867057, -0.8786290935816599, 0.0000000000000000},
      {-0.4772399923218128, -0.8292592284888882, 0.0000000000000000},
      {-0.5362419287053930, -0.7668883555242608, 0.0000000000000000},
      {-0.5830911669915615, -0.6932928247263330, 0.0000000000000000},
      {-0.6428826570500548, -0.5993662933881920, 0.0000000000000000},
      {-0.6817046799648948, -0.4892398378783872, 0.0000000000000000},
      {-0.7059726140275231, -0.3674361928234529, 0.0000000000000000},
      {-0.7283293895588195, -0.2552248795588263, 0.0000000000000000},
      {-0.7383409565045876, -0.1354364076318069, 0.0000000000000000},
      {-0.7390474108318958, -0.0130697085707094, 0.0000000000000000},
      {-0.7397577608230015, 0.1099717680394934,  0.0000000000000000},
      {-0.7310731733096858, 0.2310522341244645,  0.0000000000000000},
      {-0.7102409741035878, 0.3450758698520300,  0.0000000000000000},
      {-0.6877042814031166, 0.4684289356306250,  0.0000000000000000},
      {-0.6509526159016097, 0.5804491656371248,  0.0000000000000000},
      {-0.5934069311448411, 0.6765829536318009,  0.0000000000000000},
      {-0.5480756952227674, 0.7523117149123189,  0.0000000000000000},
      {-0.4904647466248732, 0.8169248309463861,  0.0000000000000000},
      {-0.4198897568693383, 0.8685343259400575,  0.0000000000000000},
      {-0.3479022332051305, 0.9211767670516180,  0.0000000000000000},
      {-0.2647359355960937, 0.9586330008370352,  0.0000000000000000},
      {-0.1745265058482310, 0.9798888558688201,  0.0000000000000000},
      {-0.0759264790753317, 1.0031217693355470,  0.0000000000000000},
      {0.0284557032907541,  1.0062361693214845,  0.0000000000000000},
      {0.1286724217339934,  0.9891783983354827,  0.0000000000000000},
    };
    double* weights_p2 = nullptr;
    double ctrlpt_tol_p2 = SPAresabs;
    int num_knots_p2 = 62;
    double knots_p2[] = {-6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.3411786070769347, -6.2834587115005531, -6.2834587115005531, -6.2834587115005531, -5.9642626015625284, -5.9642626015625284, -5.9642626015625284, -5.6504872402244830,
                         -5.6504872402244830, -5.6504872402244830, -5.2533556164226081, -5.2533556164226081, -5.2533556164226081, -4.8894252073663855, -4.8894252073663855, -4.8894252073663855, -4.5209261151345768, -4.5209261151345768, -4.5209261151345768,
                         -4.1209388660240132, -4.1209388660240132, -4.1209388660240132, -3.8108511013907038, -3.8108511013907038, -3.8108511013907038, -3.4882221161548381, -3.4882221161548381, -3.4882221161548381, -3.1388992525516919, -3.1388992525516919,
                         -3.1388992525516919, -2.8170816882659140, -2.8170816882659140, -2.8170816882659140, -2.5065422298125397, -2.5065422298125397, -2.5065422298125397, -2.1102152537052965, -2.1102152537052965, -2.1102152537052965, -1.7450999860042791,
                         -1.7450999860042791, -1.7450999860042791, -1.3779713307773203, -1.3779713307773203, -1.3779713307773203, -0.9808041568975095, -0.9808041568975095, -0.9808041568975095, -0.6679383193330120, -0.6679383193330120, -0.6679383193330120,
                         -0.3488105806905831, -0.3488105806905831, -0.3488105806905831, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, -0.0000000000000000};
    double knot_tol_p2 = SPAresabs;
    const int dimension_p2 = 2;
    bs2_curve pcurve22 = bs2_curve_from_ctrlpts(degree_p2, rational_p2, closed_p2, periodic_p2, num_ctrlpts_p2, ctrlpts_p2, weights_p2, ctrlpt_tol_p2, num_knots_p2, knots_p2, knot_tol_p2);

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0001542923958404, sph1, sur1, pcurve1, pcurve22);

    bounded_curve bnd_curve2(ic2, -1.2005229688686814, 0.7587086828911849);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug15) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = TRUE;
    int num_ctrlpts1 = 66;
    SPAposition ctrlpts1[] = {
      {0.2696708804254828,  1.4755601025544651, 0.0000000000000000 },
      {0.2790948951729667,  1.4738377854833427, -0.0300171356715677},
      {0.2877253149875571,  1.4692325035443339, -0.0631519840349865},
      {0.3002506847457984,  1.4536253951666411, -0.1287636721615046},
      {0.3041233228341474,  1.4426150284745949, -0.1612427376202824},
      {0.3069761767018783,  1.4182313025234015, -0.2177853355758441},
      {0.3064087761491310,  1.4028822083706025, -0.2470189067330696},
      {0.3002391455792485,  1.3674023253220384, -0.3018173989789809},
      {0.2946325107091682,  1.3472703733487859, -0.3273810709868121},
      {0.2804585318034962,  1.3067775072327676, -0.3710890713591583},
      {0.2704838229732704,  1.2826766738799944, -0.3930183105525621},
      {0.2464077552620240,  1.2317776630912545, -0.4306768862271024},
      {0.2323314111598780,  1.2049785694445188, -0.4464209713346291},
      {0.2025337437850187,  1.1515815963641260, -0.4716872379173250},
      {0.1837673425815108,  1.1199709837018563, -0.4827587274670743},
      {0.1442053445064962,  1.0561394592449269, -0.4968967100387808},
      {0.1234507147883063,  1.0239013196669058, -0.5000000000000000},
      {0.0844621921977367,  0.9641468933529945, -0.5000000000000000},
      {0.0625593420628343,  0.9310659643202881, -0.4966650802168001},
      {0.0194458184867616,  0.8658967152302935, -0.4828918545634597},
      {-0.0017414770266791, 0.8337870623495711, -0.4724813404942929},
      {-0.0402843960695877, 0.7745985559708679, -0.4478832290754690},
      {-0.0612118174794205, 0.7419942865493541, -0.4310279800911438},
      {-0.1004771665613426, 0.6792600487190217, -0.3909093336413769},
      {-0.1188120558774501, 0.6491252109123078, -0.3676505771470091},
      {-0.1491180904400712, 0.5981934081717439, -0.3219101882528121},
      {-0.1640952089736873, 0.5723938635375331, -0.2953612385529549},
      {-0.1911649678219194, 0.5252662443233964, -0.2373755167404718},
      {-0.2032787686794009, 0.5039811816858004, -0.2059136779723206},
      {-0.2215630655041609, 0.4731538757716908, -0.1500777688076259},
      {-0.2298019844157692, 0.4598214086939268, -0.1211314134571730},
      {-0.2444233042776357, 0.4394898295409945, -0.0607847363932748},
      {-0.2508328408788557, 0.4325730786311349, -0.0293632737998206},
      {-0.2610339356151146, 0.4264917918696723, 0.0282929450051987 },
      {-0.2657751443474610, 0.4265518705274096, 0.0595763839166594 },
      {-0.2734307086744715, 0.4351155127754019, 0.1211749169355121 },
      {-0.2763475624665270, 0.4436267724240912, 0.1514886303566771 },
      {-0.2802406378217464, 0.4661995471909260, 0.2072830086653558 },
      {-0.2813925009853793, 0.4827813020143170, 0.2373477259707135 },
      {-0.2809960839392629, 0.5226899593939751, 0.2927522188389913 },
      {-0.2794304758483865, 0.5459570116336527, 0.3181349556238725 },
      {-0.2739936423605009, 0.5952590476700779, 0.3635310663094740 },
      {-0.2692808547993008, 0.6263315440031832, 0.3869907692158938 },
      {-0.2562161009879748, 0.6920166778659637, 0.4270707124973213 },
      {-0.2478520733693769, 0.7266064400492638, 0.4437244993980257 },
      {-0.2290315159899740, 0.7941830375979730, 0.4700665360605638 },
      {-0.2165608756716464, 0.8335559289697895, 0.4816174920729548 },
      {-0.1879127357666116, 0.9125248879026855, 0.4965785064259332 },
      {-0.1717304772678124, 0.9521170620502215, 0.5000000000000000 },
      {-0.1402408945712874, 1.0222446906843201, 0.5000000000000000 },
      {-0.1220990778707386, 1.0593409092682029, 0.4968093369472868 },
      {-0.0835569828897010, 1.1308826829433891, 0.4830156009525323 },
      {-0.0631585083178793, 1.1653284216388393, 0.4724084407678253 },
      {-0.0252722494580486, 1.2244350014697436, 0.4478131432873043 },
      {-0.0042867775005392, 1.2547020125395152, 0.4317117500358297 },
      {0.0381918691513788,  1.3104170082207423, 0.3931441135968521 },
      {0.0596771894242580,  1.3358628943356115, 0.3706661893126904 },
      {0.0975841553389271,  1.3767709932933005, 0.3262152018923917 },
      {0.1175565316217857,  1.3962946343238263, 0.3003699394435081 },
      {0.1560833958477968,  1.4292252405998007, 0.2441630909032554 },
      {0.1746233649221572,  1.4426259863482871, 0.2137879109217496 },
      {0.2053712066445095,  1.4610874797323286, 0.1576234919165348 },
      {0.2205915300942560,  1.4682964017935998, 0.1268727159932904 },
      {0.2479722698505948,  1.4764106156450838, 0.0632874331199373 },
      {0.2601130616448559,  1.4773068734254426, 0.0304433249257103 },
      {0.2696708804254828,  1.4755601025544651, 0.0000000000000000 },
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 70;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0945265136129340, 0.0945265136129340, 0.1890530272258679, 0.1890530272258679, 0.2794533430622066, 0.2794533430622066,
                       0.3698536588985454, 0.3698536588985454, 0.4631886652724858, 0.4631886652724858, 0.5565236716464261, 0.5565236716464261, 0.6616771976350108, 0.6616771976350108, 0.7668307236235954, 0.7668307236235954,
                       0.8757245457173920, 0.8757245457173920, 0.9846183678111886, 0.9846183678111886, 1.1001017433769711, 1.1001017433769711, 1.2155851189427533, 1.2155851189427533, 1.3246951247076812, 1.3246951247076812,
                       1.4338051304726089, 1.4338051304726089, 1.5237443233318269, 1.5237443233318269, 1.6136835161910450, 1.6136835161910450, 1.7003443107170748, 1.7003443107170748, 1.7870051052431046, 1.7870051052431046,
                       1.8812843273668711, 1.8812843273668711, 1.9755635494906376, 1.9755635494906376, 2.0830007397626455, 2.0830007397626455, 2.1904379300346535, 2.1904379300346535, 2.3077949018460036, 2.3077949018460036,
                       2.4251518736573541, 2.4251518736573541, 2.5384142918508124, 2.5384142918508124, 2.6516767100442706, 2.6516767100442706, 2.7615845529312444, 2.7615845529312444, 2.8714923958182181, 2.8714923958182181,
                       2.9755394738151715, 2.9755394738151715, 3.0795865518121253, 3.0795865518121253, 3.1754551716397961, 3.1754551716397961, 3.2713237914674664, 3.2713237914674664, 3.2713237914674664, 3.2713237914674664};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition tor_center1(0, 0, 0);
    SPAunit_vector tor_normal1(0, 0, 1);
    torus tor1(tor_center1, tor_normal1, 1, -0.5);

    SPAposition sph_center1(0.71129945821979046, 0.59848974839584623, 0.18897564163524283);
    double sph_radius1 = 1.0;
    sphere sph1(sph_center1, sph_radius1);
    sph1.uv_oridir = SPAunit_vector(1, 0, 0);
    sph1.pole_dir = SPAunit_vector(0, 0, 1);

    bs2_curve pcurve11 = nullptr;
    bs2_curve pcurve12 = nullptr;

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0001483608101440, tor1, sph1, pcurve11, pcurve12);

    bounded_curve bnd_curve1(ic1, 1.1966683709665311, 3.2713237914674664);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = TRUE;
    int num_ctrlpts2 = 66;
    SPAposition ctrlpts2[] = {
      {0.2696708804254828,  1.4755601025544651, 0.0000000000000000 },
      {0.2790948951729667,  1.4738377854833427, -0.0300171356715677},
      {0.2877253149875571,  1.4692325035443339, -0.0631519840349865},
      {0.3002506847457984,  1.4536253951666411, -0.1287636721615046},
      {0.3041233228341474,  1.4426150284745949, -0.1612427376202824},
      {0.3069761767018783,  1.4182313025234015, -0.2177853355758441},
      {0.3064087761491310,  1.4028822083706025, -0.2470189067330696},
      {0.3002391455792485,  1.3674023253220384, -0.3018173989789809},
      {0.2946325107091682,  1.3472703733487859, -0.3273810709868121},
      {0.2804585318034962,  1.3067775072327676, -0.3710890713591583},
      {0.2704838229732704,  1.2826766738799944, -0.3930183105525621},
      {0.2464077552620240,  1.2317776630912545, -0.4306768862271024},
      {0.2323314111598780,  1.2049785694445188, -0.4464209713346291},
      {0.2025337437850187,  1.1515815963641260, -0.4716872379173250},
      {0.1837673425815108,  1.1199709837018563, -0.4827587274670743},
      {0.1442053445064962,  1.0561394592449269, -0.4968967100387808},
      {0.1234507147883063,  1.0239013196669058, -0.5000000000000000},
      {0.0844621921977367,  0.9641468933529945, -0.5000000000000000},
      {0.0625593420628343,  0.9310659643202881, -0.4966650802168001},
      {0.0194458184867616,  0.8658967152302935, -0.4828918545634597},
      {-0.0017414770266791, 0.8337870623495711, -0.4724813404942929},
      {-0.0402843960695877, 0.7745985559708679, -0.4478832290754690},
      {-0.0612118174794205, 0.7419942865493541, -0.4310279800911438},
      {-0.1004771665613426, 0.6792600487190217, -0.3909093336413769},
      {-0.1188120558774501, 0.6491252109123078, -0.3676505771470091},
      {-0.1491180904400712, 0.5981934081717439, -0.3219101882528121},
      {-0.1640952089736873, 0.5723938635375331, -0.2953612385529549},
      {-0.1911649678219194, 0.5252662443233964, -0.2373755167404718},
      {-0.2032787686794009, 0.5039811816858004, -0.2059136779723206},
      {-0.2215630655041609, 0.4731538757716908, -0.1500777688076259},
      {-0.2298019844157692, 0.4598214086939268, -0.1211314134571730},
      {-0.2444233042776357, 0.4394898295409945, -0.0607847363932748},
      {-0.2508328408788557, 0.4325730786311349, -0.0293632737998206},
      {-0.2610339356151146, 0.4264917918696723, 0.0282929450051987 },
      {-0.2657751443474610, 0.4265518705274096, 0.0595763839166594 },
      {-0.2734307086744715, 0.4351155127754019, 0.1211749169355121 },
      {-0.2763475624665270, 0.4436267724240912, 0.1514886303566771 },
      {-0.2802406378217464, 0.4661995471909260, 0.2072830086653558 },
      {-0.2813925009853793, 0.4827813020143170, 0.2373477259707135 },
      {-0.2809960839392629, 0.5226899593939751, 0.2927522188389913 },
      {-0.2794304758483865, 0.5459570116336527, 0.3181349556238725 },
      {-0.2739936423605009, 0.5952590476700779, 0.3635310663094740 },
      {-0.2692808547993008, 0.6263315440031832, 0.3869907692158938 },
      {-0.2562161009879748, 0.6920166778659637, 0.4270707124973213 },
      {-0.2478520733693769, 0.7266064400492638, 0.4437244993980257 },
      {-0.2290315159899740, 0.7941830375979730, 0.4700665360605638 },
      {-0.2165608756716464, 0.8335559289697895, 0.4816174920729548 },
      {-0.1879127357666116, 0.9125248879026855, 0.4965785064259332 },
      {-0.1717304772678124, 0.9521170620502215, 0.5000000000000000 },
      {-0.1402408945712874, 1.0222446906843201, 0.5000000000000000 },
      {-0.1220990778707386, 1.0593409092682029, 0.4968093369472868 },
      {-0.0835569828897010, 1.1308826829433891, 0.4830156009525323 },
      {-0.0631585083178793, 1.1653284216388393, 0.4724084407678253 },
      {-0.0252722494580486, 1.2244350014697436, 0.4478131432873043 },
      {-0.0042867775005392, 1.2547020125395152, 0.4317117500358297 },
      {0.0381918691513788,  1.3104170082207423, 0.3931441135968521 },
      {0.0596771894242580,  1.3358628943356115, 0.3706661893126904 },
      {0.0975841553389271,  1.3767709932933005, 0.3262152018923917 },
      {0.1175565316217857,  1.3962946343238263, 0.3003699394435081 },
      {0.1560833958477968,  1.4292252405998007, 0.2441630909032554 },
      {0.1746233649221572,  1.4426259863482871, 0.2137879109217496 },
      {0.2053712066445095,  1.4610874797323286, 0.1576234919165348 },
      {0.2205915300942560,  1.4682964017935998, 0.1268727159932904 },
      {0.2479722698505948,  1.4764106156450838, 0.0632874331199373 },
      {0.2601130616448559,  1.4773068734254426, 0.0304433249257103 },
      {0.2696708804254828,  1.4755601025544651, 0.0000000000000000 },
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 70;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0945265136129340, 0.0945265136129340, 0.1890530272258679, 0.1890530272258679, 0.2794533430622066, 0.2794533430622066,
                       0.3698536588985454, 0.3698536588985454, 0.4631886652724858, 0.4631886652724858, 0.5565236716464261, 0.5565236716464261, 0.6616771976350108, 0.6616771976350108, 0.7668307236235954, 0.7668307236235954,
                       0.8757245457173920, 0.8757245457173920, 0.9846183678111886, 0.9846183678111886, 1.1001017433769711, 1.1001017433769711, 1.2155851189427533, 1.2155851189427533, 1.3246951247076812, 1.3246951247076812,
                       1.4338051304726089, 1.4338051304726089, 1.5237443233318269, 1.5237443233318269, 1.6136835161910450, 1.6136835161910450, 1.7003443107170748, 1.7003443107170748, 1.7870051052431046, 1.7870051052431046,
                       1.8812843273668711, 1.8812843273668711, 1.9755635494906376, 1.9755635494906376, 2.0830007397626455, 2.0830007397626455, 2.1904379300346535, 2.1904379300346535, 2.3077949018460036, 2.3077949018460036,
                       2.4251518736573541, 2.4251518736573541, 2.5384142918508124, 2.5384142918508124, 2.6516767100442706, 2.6516767100442706, 2.7615845529312444, 2.7615845529312444, 2.8714923958182181, 2.8714923958182181,
                       2.9755394738151715, 2.9755394738151715, 3.0795865518121253, 3.0795865518121253, 3.1754551716397961, 3.1754551716397961, 3.2713237914674664, 3.2713237914674664, 3.2713237914674664, 3.2713237914674664};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    SPAposition tor_center2(0, 0, 0);
    SPAunit_vector tor_normal2(0, 0, 1);
    torus tor2(tor_center2, tor_normal2, 1, -0.5);

    SPAposition sph_center2(0.71129945821979046, 0.59848974839584623, 0.18897564163524283);
    double sph_radius2 = 1.0;
    sphere sph2(sph_center1, sph_radius1);
    sph2.uv_oridir = SPAunit_vector(1, 0, 0);
    sph2.pole_dir = SPAunit_vector(0, 0, 1);

    bs2_curve pcurve21 = nullptr;
    bs2_curve pcurve22 = nullptr;

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0001483608101440, tor2, sph2, pcurve21, pcurve22);

    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 0.3793612655131673);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug16) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = TRUE;
    int num_ctrlpts1 = 54;
    SPAposition ctrlpts1[] = {
      {-0.4878994916163494, 0.0000000000000001,  -0.1899940781187794},
      {-0.4878994916163494, -0.0580290154368698, -0.1899940781187794},
      {-0.4857012295499578, -0.1216884442195982, -0.1868852660908381},
      {-0.4726439920259415, -0.2451593339860212, -0.1684195436972474},
      {-0.4614387246244676, -0.3048601790498862, -0.1525729025680658},
      {-0.4327456915693305, -0.3936342246561252, -0.1119948260758715},
      {-0.4138566899994536, -0.4346311931714067, -0.0852817438760649},
      {-0.3849225367439876, -0.4750158963485048, -0.0443626719264033},
      {-0.3739966429810265, -0.4874511993056940, -0.0289111247857760},
      {-0.3507028997946205, -0.5069038052977135, 0.0040312027468753 },
      {-0.3383275606599544, -0.5138941909396904, 0.0215325751900865 },
      {-0.3087200393264290, -0.5232148578398074, 0.0634039334082089 },
      {-0.2869414949119267, -0.5214459161842838, 0.0942034462879429 },
      {-0.2616529637800087, -0.5061990765283417, 0.1299668299871955 },
      {-0.2524723449276690, -0.4979979926093429, 0.1429501856791526 },
      {-0.2388978651788164, -0.4808516890402840, 0.1621473990421388 },
      {-0.2318956287022353, -0.4688991847814530, 0.1720500568342634 },
      {-0.2219985988056198, -0.4459426556075234, 0.1860465707412690 },
      {-0.2173062174968207, -0.4306110798343042, 0.1926826000279987 },
      {-0.2113376132626792, -0.4017903044924289, 0.2011234810843591 },
      {-0.2092495413311096, -0.3827406384650404, 0.2040764607291954 },
      {-0.2073621975150574, -0.3288806746052448, 0.2067455679507174 },
      {-0.2129296883824615, -0.2845565870564512, 0.1988719468576462 },
      {-0.2267325176161287, -0.2096923593365462, 0.1793517985562741 },
      {-0.2367396552142332, -0.1682935343395444, 0.1651995688445012 },
      {-0.2521950383811116, -0.0839895406951830, 0.1433423563582287 },
      {-0.2570992563973904, -0.0407880570498776, 0.1364067447267725 },
      {-0.2570992563973904, 0.0407880570498777,  0.1364067447267725 },
      {-0.2521950383811116, 0.0839895406951831,  0.1433423563582287 },
      {-0.2367396552142331, 0.1682935343395445,  0.1651995688445012 },
      {-0.2267325176161287, 0.2096923593365462,  0.1793517985562741 },
      {-0.2129296883824614, 0.2845565870564513,  0.1988719468576462 },
      {-0.2073621975150573, 0.3288806746052448,  0.2067455679507174 },
      {-0.2092495413311095, 0.3827406384650404,  0.2040764607291954 },
      {-0.2113376132626791, 0.4017903044924290,  0.2011234810843591 },
      {-0.2173062174968206, 0.4306110798343043,  0.1926826000279987 },
      {-0.2219985988056196, 0.4459426556075236,  0.1860465707412690 },
      {-0.2318956287022351, 0.4688991847814531,  0.1720500568342635 },
      {-0.2388978651788163, 0.4808516890402840,  0.1621473990421388 },
      {-0.2524723449276688, 0.4979979926093430,  0.1429501856791526 },
      {-0.2616529637800086, 0.5061990765283418,  0.1299668299871956 },
      {-0.2869414949119266, 0.5214459161842840,  0.0942034462879429 },
      {-0.3087200393264289, 0.5232148578398075,  0.0634039334082089 },
      {-0.3383275606599543, 0.5138941909396906,  0.0215325751900864 },
      {-0.3507028997946204, 0.5069038052977137,  0.0040312027468753 },
      {-0.3739966429810265, 0.4874511993056942,  -0.0289111247857761},
      {-0.3849225367439875, 0.4750158963485049,  -0.0443626719264033},
      {-0.4138566899994535, 0.4346311931714069,  -0.0852817438760649},
      {-0.4327456915693304, 0.3936342246561254,  -0.1119948260758715},
      {-0.4614387246244674, 0.3048601790498863,  -0.1525729025680658},
      {-0.4726439920259414, 0.2451593339860214,  -0.1684195436972474},
      {-0.4857012295499577, 0.1216884442195984,  -0.1868852660908381},
      {-0.4878994916163494, 0.0580290154368700,  -0.1899940781187794},
      {-0.4878994916163494, 0.0000000000000001,  -0.1899940781187794},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 58;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1740870463106097, 0.1740870463106097, 0.3481740926212193, 0.3481740926212193, 0.4793022400658903, 0.4793022400658903,
                       0.5412603928105706, 0.5412603928105706, 0.6032185455552510, 0.6032185455552510, 0.6976260447616172, 0.6976260447616172, 0.7423550248096709, 0.7423550248096709, 0.7849252832860460, 0.7849252832860460,
                       0.8283067700294906, 0.8283067700294906, 0.8767816287792375, 0.8767816287792375, 0.9901839987034646, 0.9901839987034646, 1.1125481698530977, 1.1125481698530977, 1.2349123410027305, 1.2349123410027305,
                       1.3572765121523633, 1.3572765121523633, 1.4796406833019964, 1.4796406833019964, 1.5930430532262236, 1.5930430532262236, 1.6415179119759706, 1.6415179119759706, 1.6848993987194152, 1.6848993987194152,
                       1.7274696571957904, 1.7274696571957904, 1.7721986372438443, 1.7721986372438443, 1.8666061364502105, 1.8666061364502105, 1.9285642891948909, 1.9285642891948909, 1.9905224419395711, 1.9905224419395711,
                       2.1216505893842421, 2.1216505893842421, 2.2957376356948518, 2.2957376356948518, 2.4698246820054615, 2.4698246820054615, 2.4698246820054615, 2.4698246820054615};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition tor_center1(0, 0, 0);
    SPAunit_vector tor_normal1(0, 0, 1);
    torus tor1(tor_center1, tor_normal1, 0.41039134083406159, 0.2051956704170308);

    SPAposition pln_root1(-0.35355339059327384, -0.35355339059327373, 0);
    SPAunit_vector pln_normal1(0.81649658092772615, 0, -0.57735026918962584);
    plane pln1(pln_root1, pln_normal1);
    pln1.u_deriv = SPAunit_vector(-0.57735026918962584, 0, -0.81649658092772615);

    bs2_curve pcurve11 = nullptr;
    bs2_curve pcurve12 = nullptr;

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0005069338685136, tor1, pln1, pcurve11, pcurve12);

    bounded_curve bnd_curve1(ic1, 2.0484157169117632, 2.8912336470990745);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = TRUE;
    int num_ctrlpts2 = 54;
    SPAposition ctrlpts2[] = {
      {0.0000000000000000,  -0.4878994916163493, -0.1899940781187794},
      {0.0580290154368698,  -0.4878994916163493, -0.1899940781187794},
      {0.1216884442195982,  -0.4857012295499576, -0.1868852660908381},
      {0.2451593339860211,  -0.4726439920259414, -0.1684195436972474},
      {0.3048601790498860,  -0.4614387246244676, -0.1525729025680659},
      {0.3936342246561251,  -0.4327456915693306, -0.1119948260758717},
      {0.4346311931714066,  -0.4138566899994537, -0.0852817438760651},
      {0.4750158963485048,  -0.3849225367439877, -0.0443626719264035},
      {0.4874511993056939,  -0.3739966429810265, -0.0289111247857763},
      {0.5069038052977135,  -0.3507028997946205, 0.0040312027468750 },
      {0.5138941909396904,  -0.3383275606599546, 0.0215325751900862 },
      {0.5232148578398075,  -0.3087200393264292, 0.0634039334082085 },
      {0.5214459161842840,  -0.2869414949119268, 0.0942034462879426 },
      {0.5061990765283421,  -0.2616529637800089, 0.1299668299871952 },
      {0.4979979926093432,  -0.2524723449276692, 0.1429501856791522 },
      {0.4808516890402843,  -0.2388978651788166, 0.1621473990421385 },
      {0.4688991847814534,  -0.2318956287022354, 0.1720500568342631 },
      {0.4459426556075238,  -0.2219985988056199, 0.1860465707412688 },
      {0.4306110798343047,  -0.2173062174968207, 0.1926826000279986 },
      {0.4017903044924294,  -0.2113376132626792, 0.2011234810843590 },
      {0.3827406384650410,  -0.2092495413311096, 0.2040764607291954 },
      {0.3288806746052456,  -0.2073621975150573, 0.2067455679507175 },
      {0.2845565870564521,  -0.2129296883824613, 0.1988719468576464 },
      {0.2096923593365471,  -0.2267325176161285, 0.1793517985562744 },
      {0.1682935343395452,  -0.2367396552142329, 0.1651995688445014 },
      {0.0839895406951836,  -0.2521950383811115, 0.1433423563582289 },
      {0.0407880570498777,  -0.2570992563973898, 0.1364067447267739 },
      {-0.0407880570498777, -0.2570992563973898, 0.1364067447267739 },
      {-0.0839895406951837, -0.2521950383811115, 0.1433423563582289 },
      {-0.1682935343395452, -0.2367396552142329, 0.1651995688445015 },
      {-0.2096923593365471, -0.2267325176161285, 0.1793517985562744 },
      {-0.2845565870564521, -0.2129296883824613, 0.1988719468576464 },
      {-0.3288806746052456, -0.2073621975150573, 0.2067455679507175 },
      {-0.3827406384650410, -0.2092495413311096, 0.2040764607291954 },
      {-0.4017903044924294, -0.2113376132626792, 0.2011234810843590 },
      {-0.4306110798343047, -0.2173062174968207, 0.1926826000279986 },
      {-0.4459426556075238, -0.2219985988056199, 0.1860465707412688 },
      {-0.4688991847814534, -0.2318956287022354, 0.1720500568342631 },
      {-0.4808516890402843, -0.2388978651788166, 0.1621473990421385 },
      {-0.4979979926093432, -0.2524723449276692, 0.1429501856791522 },
      {-0.5061990765283421, -0.2616529637800089, 0.1299668299871952 },
      {-0.5214459161842840, -0.2869414949119268, 0.0942034462879426 },
      {-0.5232148578398075, -0.3087200393264292, 0.0634039334082085 },
      {-0.5138941909396904, -0.3383275606599546, 0.0215325751900861 },
      {-0.5069038052977134, -0.3507028997946205, 0.0040312027468750 },
      {-0.4874511993056937, -0.3739966429810266, -0.0289111247857763},
      {-0.4750158963485048, -0.3849225367439878, -0.0443626719264035},
      {-0.4346311931714066, -0.4138566899994537, -0.0852817438760651},
      {-0.3936342246561251, -0.4327456915693306, -0.1119948260758717},
      {-0.3048601790498861, -0.4614387246244676, -0.1525729025680659},
      {-0.2451593339860213, -0.4726439920259414, -0.1684195436972474},
      {-0.1216884442195984, -0.4857012295499576, -0.1868852660908381},
      {-0.0580290154368699, -0.4878994916163494, -0.1899940781187794},
      {0.0000000000000000,  -0.4878994916163493, -0.1899940781187794},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 58;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1740870463106096, 0.1740870463106096, 0.3481740926212191, 0.3481740926212191, 0.4793022400658901, 0.4793022400658901,
                       0.5412603928105704, 0.5412603928105704, 0.6032185455552508, 0.6032185455552508, 0.6976260447616169, 0.6976260447616169, 0.7423550248096706, 0.7423550248096706, 0.7849252832860458, 0.7849252832860458,
                       0.8283067700294904, 0.8283067700294904, 0.8767816287792372, 0.8767816287792372, 0.9901839987034641, 0.9901839987034641, 1.1125481698530972, 1.1125481698530972, 1.2349123410027303, 1.2349123410027303,
                       1.3572765121523633, 1.3572765121523633, 1.4796406833019964, 1.4796406833019964, 1.5930430532262232, 1.5930430532262232, 1.6415179119759700, 1.6415179119759700, 1.6848993987194145, 1.6848993987194145,
                       1.7274696571957897, 1.7274696571957897, 1.7721986372438434, 1.7721986372438434, 1.8666061364502096, 1.8666061364502096, 1.9285642891948900, 1.9285642891948900, 1.9905224419395702, 1.9905224419395702,
                       2.1216505893842412, 2.1216505893842412, 2.2957376356948505, 2.2957376356948505, 2.4698246820054601, 2.4698246820054601, 2.4698246820054601, 2.4698246820054601};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    SPAposition tor_center2(0, 0, 0);
    SPAunit_vector tor_normal2(0, 0, 1);
    torus tor2(tor_center2, tor_normal2, 0.41039134083406159, 0.2051956704170308);

    SPAposition pln_center2(0.35355339059327373, -0.35355339059327373, 0);
    SPAunit_vector pln_normal2(0, 0.81649658092772615, -0.57735026918962573);
    plane pln2(pln_center2, pln_normal2);
    pln2.u_deriv = SPAunit_vector(-1, 0, 0);

    bs2_curve pcurve21 = nullptr;
    bs2_curve pcurve22 = nullptr;

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0005069338685136, tor2, pln2, pcurve21, pcurve22);

    bounded_curve bnd_curve2(ic2, 2.0484157169117627, 2.8912336470991584);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug17) {
        int degree1 = 2;
    logical rational1 = TRUE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 3;
    SPAposition ctrlpts1[] = {
      {0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
      {0.5000000000000000, 0.4999999999999999, 0.0000000000000000},
      {1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
    };
    double weights1[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 6;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    bounded_curve bnd_curve1(ic1, 0.0000000000000000, 1.1180339887498949);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {-4.0846086443841578, -3.2676869155073272, 0.0000000000000000},
      {-0.8169217288768318, 2.4507651866304956,  0.0000000000000000},
      {0.8169217288768318,  2.0423043221920789,  0.0000000000000000},
      {3.2676869155073272,  -4.9015303732609912, 0.0000000000000000},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 80.0000000000000000);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug18) {
        int degree1 = 2;
    logical rational1 = TRUE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 3;
    SPAposition ctrlpts1[] = {
      {0.0000000000000000, 0.0000000000000000, 0.0000000000000000},
      {0.5000000000000000, 0.4999999999999999, 0.0000000000000000},
      {1.0000000000000000, 0.0000000000000000, 0.0000000000000000},
    };
    double weights1[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 6;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.1180339887498949, 1.1180339887498949, 1.1180339887498949};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    bounded_curve bnd_curve1(ic1, 0, 1.1180339887498949);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {-4.2602907366157359, -3.4082325892925889, 0.0000000000000000},
      {-0.8520581473231472, 2.5561744419694419,  0.0000000000000000},
      {0.8520581473231472,  2.1301453683078679,  0.0000000000000000},
      {3.4082325892925889,  -5.1123488839388838, 0.0000000000000000},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    bounded_curve bnd_curve2(ic2, 0.0000000000000000, 80.0000000000000000);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug19) {
        int degree1 = 2;
    logical rational1 = TRUE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 5;
    SPAposition ctrlpts1[] = {
      {10.0000000000000000, 10.0000000000000000, 0.0000000000000000},
      {5.0000000000000000,  8.0000000000000000,  0.0000000000000000},
      {0.0000000000000000,  3.0000000000000000,  0.0000000000000000},
      {0.0000000000000000,  2.2500000000000000,  0.0000000000000000},
      {0.2272727272727273,  1.6875000000000000,  0.0000000000000000},
    };
    double weights1[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 8;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1250000000000000, 0.1250000000000000, 0.1250000000000000};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    int degree2 = 2;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 5;
    SPAposition ctrlpts2[] = {
      {4.9305555555555562,  -0.8179012345679015, 0.0000000000000000},
      {5.0000000000000000,  -0.5555555555555557, 0.0000000000000000},
      {5.0000000000000000,  0.0000000000000000,  0.0000000000000000},
      {0.0000000000000000,  5.0000000000000000,  0.0000000000000000},
      {-5.0000000000000000, 15.0000000000000000, 0.0000000000000000},
    };
    double weights2[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0.8750000000000000, 0.8750000000000000, 0.8750000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug20) {
        std::string str1 = "VEC((5+0.3183098861837907*X)*COS(X),(5+(2/(2*3.141592653589793))*X)*SIN(X),0)";
    law* l1 = nullptr;
    api_str_to_law(str1.c_str(), &l1);
    curve* cur1 = nullptr;
    api_curve_law(l1, 0, 50, cur1);
    SPAmatrix trans1_mat(SPAvector(1, 0, 0), SPAvector(0, 1, 0), SPAvector(0, 0, 1));
    SPAvector trans1_translate(0, 0, 5);
    SPAtransf trans1(trans1_mat, trans1_translate, 1, FALSE, FALSE, FALSE);
    (*cur1) *= trans1;

    std::string str2 = "VEC((5+0.3183098861837907*X)*COS(X),(5+(2/(2*3.141592653589793))*X)*SIN(X),0)";
    law* l2 = nullptr;
    api_str_to_law(str2.c_str(), &l2);
    curve* cur2 = nullptr;
    api_curve_law(l2, 0, 50, cur2);
    SPAmatrix trans2_mat(SPAvector(1, 0, 0), SPAvector(0, 1, 0), SPAvector(0, 0, 1));
    SPAvector trans2_translate(0, 0, 5.0000000000000009);
    SPAtransf trans2(trans2_mat, trans2_translate, 1.0000000000000002, FALSE, FALSE, FALSE);
    (*cur2) *= trans2;

    curve_curve_int* acis_inters = int_cur_cur(*cur1, *cur2);
    curve_curve_int* gme_inters = answer_int_cur_cur(*cur1, *cur2);

    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug21) {
        int degree1 = 3;
    logical rational1 = TRUE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 4;
    SPAposition ctrlpts1[] = {
      {1.1250000000000000, 0.0000000000000000, 0.4921875000000001},
      {1.2500000000000000, 0.0000000000000000, 0.5000000000000001},
      {1.3750000000000000, 0.0000000000000000, 0.5000000000000002},
      {1.5000000000000002, 0.0000000000000000, 0.5000000000000002},
    };
    double weights1[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 8;
    double knots1[] = {0.3750000000000000, 0.3750000000000000, 0.3750000000000000, 0.3750000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    int degree2 = 3;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {1.5000000000000002, 0.0000000000000000, 0.5000000000000002},
      {1.6250000000000004, 0.0000000000000000, 0.5000000000000002},
      {1.7500000000000004, 0.0000000000000000, 0.5000000000000002},
      {1.8750000000000004, 0.0000000000000000, 0.5078125000000002},
    };
    double weights2[] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.6250000000000000, 0.6250000000000000, 0.6250000000000000, 0.6250000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug22) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 4;
    SPAposition ctrlpts1[] = {
      {1.1250000000000000, 0.0000000000000000, 0.4921875000000001},
      {1.2500000000000000, 0.0000000000000000, 0.5000000000000001},
      {1.3750000000000000, 0.0000000000000000, 0.5000000000000002},
      {1.5000000000000002, 0.0000000000000000, 0.5000000000000002},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 8;
    double knots1[] = {0.3750000000000000, 0.3750000000000000, 0.3750000000000000, 0.3750000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);
    exact_int_cur* eic1 = ACIS_NEW exact_int_cur(bs1);
    intcurve* ic1 = ACIS_NEW intcurve(eic1);

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 4;
    SPAposition ctrlpts2[] = {
      {1.5000000000000002, 0.0000000000000000, 0.5000000000000002},
      {1.6250000000000004, 0.0000000000000000, 0.5000000000000002},
      {1.7500000000000004, 0.0000000000000000, 0.5000000000000002},
      {1.8750000000000004, 0.0000000000000000, 0.5078125000000002},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 8;
    double knots2[] = {0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.5000000000000000, 0.6250000000000000, 0.6250000000000000, 0.6250000000000000, 0.6250000000000000};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* eic2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(eic2);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug23) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 22;
    SPAposition ctrlpts1[] = {
      {1.0682794281414034,  1.0529857849989597,  -0.0000000000000014},
      {1.0661969081854208,  1.0550985516282565,  -0.0000907400199455},
      {1.0641081075479866,  1.0572051182333155,  -0.0001814798387081},
      {0.9218667825634648,  1.1998052642792543,  -0.0063420630344577},
      {0.7551577696385492,  1.3110150838726000,  -0.0123442140465962},
      {0.3911715088529372,  1.4606455666018281,  -0.0234192489800027},
      {0.1979624861798401,  1.4988370468196663,  -0.0283997875608767},
      {-0.1924657839732612, 1.4990309816492173,  -0.0367872822074442},
      {-0.3859489941404984, 1.4609543854147364,  -0.0401122961077020},
      {-0.7475900399434856, 1.3127633004690127,  -0.0446492755135978},
      {-0.9122825544619674, 1.2040146307871475,  -0.0458165864810662},
      {-1.1907356225359256, 0.9295479371980478,  -0.0458165864810647},
      {-1.3018476245924742, 0.7664405477425688,  -0.0446492755135984},
      {-1.4552376658554240, 0.4069738053195448,  -0.0401122961077037},
      {-1.4961000628994394, 0.2140597200244583,  -0.0367872822074445},
      {-1.5015355813084574, -0.1763307599889198, -0.0283997875608770},
      {-1.4661338768359504, -0.3700703659655072, -0.0234192489800055},
      {-1.3217671247946439, -0.7361762526606044, -0.0123442140478360},
      {-1.2129725781650815, -0.9044714266485352, -0.0063420630426037},
      {-1.0724381781145944, -1.0487540611079080, -0.0001814798382773},
      {-1.0703619480977125, -1.0508730183693313, -0.0000907400199567},
      {-1.0682794281414028, -1.0529857849989603, 0.0000000000000016 },
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 26;
    double knots1[] = {-0.0089039403374796, -0.0089039403374796, -0.0089039403374796, -0.0089039403374796, 0.0000000000000000, 0.0000000000000000, 0.5956191284852781, 0.5956191284852781, 1.1810859487910621,
                       1.1810859487910621,  1.7671508097850157,  1.7671508097850157,  2.3536029436043724,  2.3536029436043724, 2.9400550774237302, 2.9400550774237302, 3.5261199384176924, 3.5261199384176924,
                       4.1115867587234591,  4.1115867587234591,  4.7072058870763636,  4.7072058870763636,  4.7161098274112234, 4.7161098274112234, 4.7161098274112234, 4.7161098274112234};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition tor_center11(0, 0, 0);
    SPAunit_vector tor_normal11(-0.042903830158257709, 0.043526968549329859, 0.99813058482678363);
    torus tor11(tor_center11, tor_normal11, 1, 0.5);

    SPAposition tor_center12(0, 0, 0);
    SPAunit_vector tor_normal12(0, 0, 1);
    torus tor12(tor_center12, tor_normal12, 1, 0.5);

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0000007562384047, tor11, tor12);

    bounded_curve bnd_curve1(ic1, -0.0089039403374796, 4.7161098274112234);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 22;
    SPAposition ctrlpts2[] = {
      {1.0682794281414034,  1.0529857849989597,  -0.0000000000000014},
      {1.0703619480976543,  1.0508730183693895,  0.0000907400199544 },
      {1.0724381781145831,  1.0487540611079189,  0.0001814798374357 },
      {1.2129725781632905,  0.9044714266503937,  0.0063420630558933 },
      {1.3217671247938840,  0.7361762526625332,  0.0123442140477918 },
      {1.4661338768359513,  0.3700703659655037,  0.0234192489800095 },
      {1.5015355813084577,  0.1763307599889167,  0.0283997875608768 },
      {1.4961000628994392,  -0.2140597200244591, 0.0367872822074435 },
      {1.4552376658554240,  -0.4069738053195446, 0.0401122961077045 },
      {1.3018476245924746,  -0.7664405477425691, 0.0446492755136003 },
      {1.1907356225359249,  -0.9295479371980485, 0.0458165864810634 },
      {0.9122825544619677,  -1.2040146307871471, 0.0458165864810635 },
      {0.7475900399434855,  -1.3127633004690125, 0.0446492755135953 },
      {0.3859489941404995,  -1.4609543854147358, 0.0401122961076996 },
      {0.1924657839732626,  -1.4990309816492171, 0.0367872822074459 },
      {-0.1979624861798391, -1.4988370468196668, 0.0283997875608792 },
      {-0.3911715088529357, -1.4606455666018283, 0.0234192489800030 },
      {-0.7551577695990399, -1.3110150838888417, 0.0123442140478036 },
      {-0.9218667825327516, -1.1998052643100765, 0.0063420630493635 },
      {-1.0641081075483620, -1.0572051182329387, 0.0001814798378393 },
      {-1.0661969081851610, -1.0550985516285201, 0.0000907400199570 },
      {-1.0682794281414028, -1.0529857849989603, 0.0000000000000016 },
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 26;
    double knots2[] = {-0.0089039403386295, -0.0089039403386295, -0.0089039403386295, -0.0089039403386295, 0.0000000000000000, 0.0000000000000000, 0.5956191286155751, 0.5956191286155751, 1.1810859491734094,
                       1.1810859491734094,  1.7671508104196976,  1.7671508104196976,  2.3536029444915534,  2.3536029444915534, 2.9400550785634123, 2.9400550785634123, 3.5261199398096936, 3.5261199398096936,
                       4.1115867603675493,  4.1115867603675493,  4.7072058889810728,  4.7072058889810728,  4.7161098293195991, 4.7161098293195991, 4.7161098293195991, 4.7161098293195991};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    SPAposition tor_center21(0, 0, 0);
    SPAunit_vector tor_normal21(-0.042903830158257709, 0.043526968549329859, 0.99813058482678363);
    torus tor21(tor_center21, tor_normal21, 1, 0.5);

    SPAposition tor_center22(0, 0, 0);
    SPAunit_vector tor_normal22(0, 0, 1);
    torus tor22(tor_center22, tor_normal22, 1, 0.5);

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0000007562383222, tor21, tor22);

    bounded_curve bnd_curve2(ic2, -0.0089039403386295, 4.7161098293195991);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);
}

TEST_F(NurbsNurbsIntrTest, TestBug24) {
        EDGE *e1, *e2;

    const std::string law_str = "VEC((5+0.3183098861837907*X)*COS(X),(5+(2/(2*3.141592653589793))*X)*SIN(X),0)";
    law* l = nullptr;
    api_str_to_law(law_str.c_str(), &l);
    curve* c = nullptr;
    api_curve_law(l, 0, 50, c);

    SPAmatrix affine_mat(SPAvector(1, 0, 0), SPAvector(0, 1, 0), SPAvector(0, 0, 1));
    SPAvector translate_vec(0, 0, 5);
    SPAtransf transf(affine_mat, translate_vec, 1, FALSE, FALSE, FALSE);
    (*c) *= transf;
    api_make_edge_from_curve(c, e1);

    int degree = 3;
    logical rational = FALSE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 4;
    SPAposition ctrlpts[] = {
      {-8.9742836097920176, -7.5241341286473951, 5.0000000000059615},
      {-4.9742836097920176, -0.5241341286473968, 5.0000000000059615},
      {-2.9742836097920176, -1.0241341286473968, 5.0000000000059615},
      {0.0257163902079824,  -9.5241341286473933, 5.0000000000059615},
    };
    double* weights = nullptr;
    double ctrlpt_tol = SPAresabs;
    int num_knots = 8;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000, 80.0000000000000000};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* eic = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(eic);
    bounded_curve bnd_curve(ic, 0, 80);
    e2 = bnd_curve.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic, *c);
    gme_inters = answer_int_cur_cur(*ic, *c);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
}

TEST_F(NurbsNurbsIntrTest, TestBug25) {
        int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = TRUE;
    logical periodic1 = FALSE;
    int num_ctrlpts1 = 85;
    SPAposition ctrlpts1[] = {
      {0.1218306973471696,  -0.5587203684554429, -0.2582375630052519},
      {0.1158364071175898,  -0.5782244708772042, -0.2877151101851657},
      {0.1126901034241456,  -0.6001470887173972, -0.3156565405785541},
      {0.1124004530632308,  -0.6612627921168874, -0.3799082296120652},
      {0.1188598197674361,  -0.7021781246878904, -0.4120841843207977},
      {0.1455634342138971,  -0.7912479201868063, -0.4633483806796680},
      {0.1659980857155789,  -0.8380766072962069, -0.4809564714463314},
      {0.2218838779088664,  -0.9327444395718196, -0.5013780654166684},
      {0.2577280668552913,  -0.9787284275529344, -0.5023835641615304},
      {0.3463419374401943,  -1.0647400425298723, -0.4890453447738097},
      {0.3993969354814406,  -1.1013393059148082, -0.4726230456754076},
      {0.5199201459527986,  -1.1575778327019060, -0.4259843237421270},
      {0.5896710210519972,  -1.1746728222981639, -0.3935421558297346},
      {0.7449938384636744,  -1.1793459755003215, -0.3146637442035141},
      {0.8294284903926380,  -1.1625795024580612, -0.2679693587441526},
      {1.0060957059410947,  -1.0844772988177480, -0.1650455443997642},
      {1.0950758744310816,  -1.0180477291367469, -0.1099071459389600},
      {1.2623547037281613,  -0.8279569437675700, 0.0015734057516187 },
      {1.3346723243628056,  -0.6999716629387742, 0.0553953887889247 },
      {1.4403499717471062,  -0.3807627151551180, 0.1536551014592661 },
      {1.4605742012788525,  -0.1955903232217363, 0.1922495821279789 },
      {1.4483348987633797,  0.0754686569315649,  0.2229726598787194 },
      {1.4380482183418433,  0.1623357702372453,  0.2286541567808897 },
      {1.4152185395227814,  0.3007279312017944,  0.2264548999540009 },
      {1.4047620070884270,  0.3544665617818669,  0.2225924129109133 },
      {1.3800828858482255,  0.4687756722779527,  0.2050242734589310 },
      {1.3660044319095386,  0.5273851772468787,  0.1898664557564019 },
      {1.3187201012657441,  0.6927272884615383,  0.1276303282388058 },
      {1.2804961770593322,  0.7873160329108353,  0.0673362866545781 },
      {1.2240496100417322,  0.8670078155107266,  -0.0000000000000001},
      {1.1827647320756145,  0.9252941860266355,  -0.0492495916777190},
      {1.1329453700905914,  0.9741089815046828,  -0.1012956322672009},
      {1.0183920389367462,  1.0487389775953873,  -0.2017118916296536},
      {0.9558358363742698,  1.0745641721967234,  -0.2490015094221152},
      {0.8047585178317574,  1.1079736082254719,  -0.3456359249383071},
      {0.7150159882966791,  1.1093876200227601,  -0.3919182268708882},
      {0.5358503876635718,  1.0801224418778075,  -0.4612587437066329},
      {0.4482499225021915,  1.0509796234650601,  -0.4845665416587339},
      {0.2876290290447969,  0.9708924834919259,  -0.5038832567470664},
      {0.2154338599060448,  0.9222110959501129,  -0.5014934189488796},
      {0.0956611234291023,  0.8191896620131340,  -0.4714821804635600},
      {0.0471881587591901,  0.7669604518390503,  -0.4470815746377671},
      {-0.0251166042662293, 0.6720921785860730,  -0.3809322567163477},
      {-0.0509199548903752, 0.6300580735945467,  -0.3429393398174367},
      {-0.0863253421056849, 0.5608461016708530,  -0.2554594651287492},
      {-0.0966830074991004, 0.5338175211060898,  -0.2086732092236436},
      {-0.1081939855692605, 0.4959160663391256,  -0.1033377043799270},
      {-0.1086525697092620, 0.4870159535608739,  -0.0469761536929415},
      {-0.1046923669172162, 0.4903139350630308,  0.0743737683827886 },
      {-0.0997842216707899, 0.5055127678871780,  0.1375482365081755 },
      {-0.0895735958793272, 0.5586326857037045,  0.2563988138088175 },
      {-0.0844995465801277, 0.5973996529412384,  0.3110013225635331 },
      {-0.0719203353790397, 0.6865643092914654,  0.3967005146547136 },
      {-0.0647776280599648, 0.7325072320619854,  0.4270694849339581 },
      {-0.0422517871991355, 0.8166530210216179,  0.4674284981588251 },
      {-0.0283303968397066, 0.8551881138723338,  0.4801055298715742 },
      {0.0115132048819597,  0.9273639329260477,  0.4959851697068532 },
      {0.0359428526467824,  0.9591979462444726,  0.4992157326024575 },
      {0.1022109937029126,  1.0201671448549847,  0.5006809264570034 },
      {0.1445386657990955,  1.0450829515971352,  0.4976920799513918 },
      {0.2483951326259535,  1.0839365160792243,  0.4886346587181238 },
      {0.3142546835267542,  1.0938471630142135,  0.4816118170411127 },
      {0.4728444663189106,  1.0877747810904048,  0.4660926534943401 },
      {0.5650395610857977,  1.0645311683453023,  0.4579297603366160 },
      {0.7478849497237814,  0.9800178030196229,  0.4449954666426134 },
      {0.8345039483899432,  0.9181978378991682,  0.4404916863734766 },
      {0.9633501889758949,  0.7862184875771689,  0.4382553100317517 },
      {1.0129773198096963,  0.7175541803748506,  0.4394658276437951 },
      {1.0726501102496657,  0.5857332877530339,  0.4488264242662711 },
      {1.0884791888159266,  0.5259828534351514,  0.4554572428976438 },
      {1.0968382911734464,  0.3964231384006245,  0.4727749674746213 },
      {1.0868148475720845,  0.3305327238315798,  0.4828897502615476 },
      {1.0409847813190765,  0.1875259810685900,  0.4989532934603778 },
      {0.9984096494278163,  0.1088334592012232,  0.5035120766162733 },
      {0.8801092504566266,  -0.0484932600774465, 0.4892157331149556 },
      {0.8038028608562982,  -0.1232116023429733, 0.4683514781857012 },
      {0.6229008226884470,  -0.2607390612083300, 0.3843000837209090 },
      {0.5260370990780983,  -0.3130473675310542, 0.3208878212650599 },
      {0.3416035187100891,  -0.3966570831099139, 0.1558098812600524 },
      {0.2659009007843257,  -0.4221841278053540, 0.0618203935777754 },
      {0.1775921128762149,  -0.4741724654203085, -0.0908140531171005},
      {0.1510196271191268,  -0.4971903177190504, -0.1511588975165620},
      {0.1290535491820602,  -0.5385717292651930, -0.2263063087392444},
      {0.1250328935899370,  -0.5483011259594233, -0.2424904291144498},
      {0.1218306973471696,  -0.5587203684554429, -0.2582375630052519}
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 89;
    double knots1[] = {-3.9318542827171239, -3.9318542827171239, -3.9318542827171239, -3.9318542827171239, -3.7998866587883322, -3.7998866587883322, -3.6043448048734246, -3.6043448048734246, -3.4003268516542815, -3.4003268516542815,
                       -3.1767795955957263, -3.1767795955957263, -2.9186179228091813, -2.9186179228091813, -2.6231581008508149, -2.6231581008508149, -2.2876721496369861, -2.2876721496369861, -1.9023602124223904, -1.9023602124223904,
                       -1.4596210680512587, -1.4596210680512587, -0.9445012141116640, -0.9445012141116640, -0.6992356021357558, -0.6992356021357558, -0.5419493978848400, -0.5419493978848400, -0.3558658957838390, -0.3558658957838390,
                       -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, 0.2602794262963446,  0.2602794262963446,  0.5088864220542426,  0.5088864220542426,  0.8169243731267404,  0.8169243731267404,  1.1124403212971146,
                       1.1124403212971146,  1.3878439502576452,  1.3878439502576452,  1.6309864811227364,  1.6309864811227364,  1.8369866904086845,  1.8369866904086845,  2.0241711275203436,  2.0241711275203436,  2.2215253257283081,
                       2.2215253257283081,  2.4460683999468671,  2.4460683999468671,  2.6817407456458948,  2.6817407456458948,  2.8926115036307838,  2.8926115036307838,  3.0685191606240672,  3.0685191606240672,  3.2373852346059167,
                       3.2373852346059167,  3.4444180324763636,  3.4444180324763636,  3.7080719390948893,  3.7080719390948893,  4.0407591922348791,  4.0407591922348791,  4.3924191141453726,  4.3924191141453726,  4.6786206171303153,
                       4.6786206171303153,  4.9019012787700849,  4.9019012787700849,  5.1456603595981738,  5.1456603595981738,  5.4509732660189218,  5.4509732660189218,  5.7867397480743401,  5.7867397480743401,  6.1663459186762504,
                       6.1663459186762504,  6.5675281605923850,  6.5675281605923850,  6.8175858453019584,  6.8175858453019584,  6.8880839715732556,  6.8880839715732556,  6.8880839715732556,  6.8880839715732556};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition cone_ellipse_center1(0.74959089574962068, 0.21020215569773665, -0.37937915434207209);
    SPAunit_vector cone_ellipse_normal1(-0.37438634362443102, 0.43469676645339483, 0.81906873151310799);
    SPAvector cone_ellipse_major1(0.89948262861839312, -0.044381550769525178, 0.43469676645339478);
    double cone_ellipse_ratio1 = 1.0;
    ellipse cone_ellipse1(cone_ellipse_center1, cone_ellipse_normal1, cone_ellipse_major1, cone_ellipse_ratio1);
    cone c1(cone_ellipse1, -0.44721359549995798, 0.89442719099991597);
    c1.u_param_scale = 1;

    SPAposition torus_center1(0, 0, 0);
    SPAunit_vector torus_normal1(0, 0, 0.99999999999999989);
    torus t1(torus_center1, torus_normal1, 1, 0.5);

    bs2_curve pcurve11 = nullptr;
    bs2_curve pcurve12 = nullptr;

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0003425939015354, c1, t1, pcurve11, pcurve12);

    bounded_curve bnd_curve1(ic1, -3.9318542827171239, 6.8880839715732556);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = TRUE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 85;
    SPAposition ctrlpts2[] = {
      {0.1218306973471696,  -0.5587203684554429, -0.2582375630052519},
      {0.1158364071175898,  -0.5782244708772042, -0.2877151101851657},
      {0.1126901034241456,  -0.6001470887173972, -0.3156565405785541},
      {0.1124004530632308,  -0.6612627921168874, -0.3799082296120652},
      {0.1188598197674361,  -0.7021781246878904, -0.4120841843207977},
      {0.1455634342138971,  -0.7912479201868063, -0.4633483806796680},
      {0.1659980857155789,  -0.8380766072962069, -0.4809564714463314},
      {0.2218838779088664,  -0.9327444395718196, -0.5013780654166684},
      {0.2577280668552913,  -0.9787284275529344, -0.5023835641615304},
      {0.3463419374401943,  -1.0647400425298723, -0.4890453447738097},
      {0.3993969354814406,  -1.1013393059148082, -0.4726230456754076},
      {0.5199201459527986,  -1.1575778327019060, -0.4259843237421270},
      {0.5896710210519972,  -1.1746728222981639, -0.3935421558297346},
      {0.7449938384636744,  -1.1793459755003215, -0.3146637442035141},
      {0.8294284903926380,  -1.1625795024580612, -0.2679693587441526},
      {1.0060957059410947,  -1.0844772988177480, -0.1650455443997642},
      {1.0950758744310816,  -1.0180477291367469, -0.1099071459389600},
      {1.2623547037281613,  -0.8279569437675700, 0.0015734057516187 },
      {1.3346723243628056,  -0.6999716629387742, 0.0553953887889247 },
      {1.4403499717471062,  -0.3807627151551180, 0.1536551014592661 },
      {1.4605742012788525,  -0.1955903232217363, 0.1922495821279789 },
      {1.4483348987633797,  0.0754686569315649,  0.2229726598787194 },
      {1.4380482183418433,  0.1623357702372453,  0.2286541567808897 },
      {1.4152185395227814,  0.3007279312017944,  0.2264548999540009 },
      {1.4047620070884270,  0.3544665617818669,  0.2225924129109133 },
      {1.3800828858482255,  0.4687756722779527,  0.2050242734589310 },
      {1.3660044319095386,  0.5273851772468787,  0.1898664557564019 },
      {1.3187201012657441,  0.6927272884615383,  0.1276303282388058 },
      {1.2804961770593322,  0.7873160329108353,  0.0673362866545781 },
      {1.2240496100417322,  0.8670078155107266,  -0.0000000000000001},
      {1.1827647320756145,  0.9252941860266355,  -0.0492495916777190},
      {1.1329453700905914,  0.9741089815046828,  -0.1012956322672009},
      {1.0183920389367462,  1.0487389775953873,  -0.2017118916296536},
      {0.9558358363742698,  1.0745641721967234,  -0.2490015094221152},
      {0.8047585178317574,  1.1079736082254719,  -0.3456359249383071},
      {0.7150159882966791,  1.1093876200227601,  -0.3919182268708882},
      {0.5358503876635718,  1.0801224418778075,  -0.4612587437066329},
      {0.4482499225021915,  1.0509796234650601,  -0.4845665416587339},
      {0.2876290290447969,  0.9708924834919259,  -0.5038832567470664},
      {0.2154338599060448,  0.9222110959501129,  -0.5014934189488796},
      {0.0956611234291023,  0.8191896620131340,  -0.4714821804635600},
      {0.0471881587591901,  0.7669604518390503,  -0.4470815746377671},
      {-0.0251166042662293, 0.6720921785860730,  -0.3809322567163477},
      {-0.0509199548903752, 0.6300580735945467,  -0.3429393398174367},
      {-0.0863253421056849, 0.5608461016708530,  -0.2554594651287492},
      {-0.0966830074991004, 0.5338175211060898,  -0.2086732092236436},
      {-0.1081939855692605, 0.4959160663391256,  -0.1033377043799270},
      {-0.1086525697092620, 0.4870159535608739,  -0.0469761536929415},
      {-0.1046923669172162, 0.4903139350630308,  0.0743737683827886 },
      {-0.0997842216707899, 0.5055127678871780,  0.1375482365081755 },
      {-0.0895735958793272, 0.5586326857037045,  0.2563988138088175 },
      {-0.0844995465801277, 0.5973996529412384,  0.3110013225635331 },
      {-0.0719203353790397, 0.6865643092914654,  0.3967005146547136 },
      {-0.0647776280599648, 0.7325072320619854,  0.4270694849339581 },
      {-0.0422517871991355, 0.8166530210216179,  0.4674284981588251 },
      {-0.0283303968397066, 0.8551881138723338,  0.4801055298715742 },
      {0.0115132048819597,  0.9273639329260477,  0.4959851697068532 },
      {0.0359428526467824,  0.9591979462444726,  0.4992157326024575 },
      {0.1022109937029126,  1.0201671448549847,  0.5006809264570034 },
      {0.1445386657990955,  1.0450829515971352,  0.4976920799513918 },
      {0.2483951326259535,  1.0839365160792243,  0.4886346587181238 },
      {0.3142546835267542,  1.0938471630142135,  0.4816118170411127 },
      {0.4728444663189106,  1.0877747810904048,  0.4660926534943401 },
      {0.5650395610857977,  1.0645311683453023,  0.4579297603366160 },
      {0.7478849497237814,  0.9800178030196229,  0.4449954666426134 },
      {0.8345039483899432,  0.9181978378991682,  0.4404916863734766 },
      {0.9633501889758949,  0.7862184875771689,  0.4382553100317517 },
      {1.0129773198096963,  0.7175541803748506,  0.4394658276437951 },
      {1.0726501102496657,  0.5857332877530339,  0.4488264242662711 },
      {1.0884791888159266,  0.5259828534351514,  0.4554572428976438 },
      {1.0968382911734464,  0.3964231384006245,  0.4727749674746213 },
      {1.0868148475720845,  0.3305327238315798,  0.4828897502615476 },
      {1.0409847813190765,  0.1875259810685900,  0.4989532934603778 },
      {0.9984096494278163,  0.1088334592012232,  0.5035120766162733 },
      {0.8801092504566266,  -0.0484932600774465, 0.4892157331149556 },
      {0.8038028608562982,  -0.1232116023429733, 0.4683514781857012 },
      {0.6229008226884470,  -0.2607390612083300, 0.3843000837209090 },
      {0.5260370990780983,  -0.3130473675310542, 0.3208878212650599 },
      {0.3416035187100891,  -0.3966570831099139, 0.1558098812600524 },
      {0.2659009007843257,  -0.4221841278053540, 0.0618203935777754 },
      {0.1775921128762149,  -0.4741724654203085, -0.0908140531171005},
      {0.1510196271191268,  -0.4971903177190504, -0.1511588975165620},
      {0.1290535491820602,  -0.5385717292651930, -0.2263063087392444},
      {0.1250328935899370,  -0.5483011259594233, -0.2424904291144498},
      {0.1218306973471696,  -0.5587203684554429, -0.2582375630052519},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 89;
    double knots2[] = {-3.9318542827171239, -3.9318542827171239, -3.9318542827171239, -3.9318542827171239, -3.7998866587883322, -3.7998866587883322, -3.6043448048734246, -3.6043448048734246, -3.4003268516542815, -3.4003268516542815,
                       -3.1767795955957263, -3.1767795955957263, -2.9186179228091813, -2.9186179228091813, -2.6231581008508149, -2.6231581008508149, -2.2876721496369861, -2.2876721496369861, -1.9023602124223904, -1.9023602124223904,
                       -1.4596210680512587, -1.4596210680512587, -0.9445012141116640, -0.9445012141116640, -0.6992356021357558, -0.6992356021357558, -0.5419493978848400, -0.5419493978848400, -0.3558658957838390, -0.3558658957838390,
                       -0.0000000000000000, -0.0000000000000000, -0.0000000000000000, 0.2602794262963446,  0.2602794262963446,  0.5088864220542426,  0.5088864220542426,  0.8169243731267404,  0.8169243731267404,  1.1124403212971146,
                       1.1124403212971146,  1.3878439502576452,  1.3878439502576452,  1.6309864811227364,  1.6309864811227364,  1.8369866904086845,  1.8369866904086845,  2.0241711275203436,  2.0241711275203436,  2.2215253257283081,
                       2.2215253257283081,  2.4460683999468671,  2.4460683999468671,  2.6817407456458948,  2.6817407456458948,  2.8926115036307838,  2.8926115036307838,  3.0685191606240672,  3.0685191606240672,  3.2373852346059167,
                       3.2373852346059167,  3.4444180324763636,  3.4444180324763636,  3.7080719390948893,  3.7080719390948893,  4.0407591922348791,  4.0407591922348791,  4.3924191141453726,  4.3924191141453726,  4.6786206171303153,
                       4.6786206171303153,  4.9019012787700849,  4.9019012787700849,  5.1456603595981738,  5.1456603595981738,  5.4509732660189218,  5.4509732660189218,  5.7867397480743401,  5.7867397480743401,  6.1663459186762504,
                       6.1663459186762504,  6.5675281605923850,  6.5675281605923850,  6.8175858453019584,  6.8175858453019584,  6.8880839715732556,  6.8880839715732556,  6.8880839715732556,  6.8880839715732556};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    bs2_curve pcurve21 = nullptr;
    bs2_curve pcurve22 = nullptr;

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0003425939015354, c1, t1, pcurve21, pcurve22);

    bounded_curve bnd_curve2(ic2, -3.9318542827171239, 6.8880839715732556);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug26) {
    int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = TRUE;
    int num_ctrlpts1 = 58;
    SPAposition ctrlpts1[] = {
      {-0.4542126335031718, -0.8635220311045143, 0.2191359974154113 },
      {-0.4391624509346332, -0.8805163809743942, 0.1833636343612489 },
      {-0.4163170039982675, -0.8972174414795010, 0.1529925695848732 },
      {-0.3595729082137143, -0.9285616427552063, 0.1010262873898775 },
      {-0.3256605642394095, -0.9431431326504154, 0.0794088601953259 },
      {-0.2139670944982423, -0.9803841131394698, 0.0241501252829262 },
      {-0.1261153989860074, -0.9956278158004623, -0.0002647041768550},
      {0.0205036679909458,  -1.0013723639756464, -0.0342578399761619},
      {0.0912703700519284,  -0.9972578234149370, -0.0478698424987686},
      {0.2302778611793204,  -0.9729774982270906, -0.0737011752077266},
      {0.2984884257094377,  -0.9528043817917691, -0.0860760192562133},
      {0.4712521417702915,  -0.8824829869644365, -0.1202441218027387},
      {0.5818558288298954,  -0.8107315496676848, -0.1460323548903482},
      {0.7606749853583750,  -0.6290892449347527, -0.2068516096194783},
      {0.8289096328034360,  -0.5192690190305979, -0.2420371020185662},
      {0.9105007420818723,  -0.2967769321384710, -0.3134091629989608},
      {0.9288811147209093,  -0.1704052892821463, -0.3539904122207537},
      {0.9081585772546363,  0.0790685780386860,  -0.4314666364511693},
      {0.8690281573189194,  0.2022187237701089,  -0.4681998523884262},
      {0.7819946080862904,  0.3656762773589488,  -0.5090244634945946},
      {0.7429204549589851,  0.4249557021979067,  -0.5221367803608448},
      {0.6534309350724398,  0.5357067163002596,  -0.5396214375223809},
      {0.6030731379863685,  0.5872455416418965,  -0.5438621841938266},
      {0.4913818347018766,  0.6882351612854816,  -0.5404222116277838},
      {0.4182325442817663,  0.7435710850255767,  -0.5288683539340889},
      {0.3192499802384612,  0.8154736353843983,  -0.4847285208800759},
      {0.2881763240828370,  0.8377959880083892,  -0.4655942441401615},
      {0.2350684150199172,  0.8790557643900149,  -0.4168087268928136},
      {0.2130642087965921,  0.8980508175063062,  -0.3871735398854907},
      {0.1829638436595153,  0.9320395172460663,  -0.3156288137771658},
      {0.1762240006554358,  0.9455016404479359,  -0.2769430644817675},
      {0.1749050829341549,  0.9656994930662142,  -0.1963629611631244},
      {0.1802967514673501,  0.9723767011466797,  -0.1544544312129377},
      {0.2073288488147673,  0.9817191057086814,  -0.0275771882387713},
      {0.2393161454160929,  0.9728624403505126,  0.0587057597151184 },
      {0.2919750693556838,  0.9385309428705675,  0.1955782183279028 },
      {0.3174798652119751,  0.9150556042203384,  0.2588913768407666 },
      {0.3633106136302984,  0.8536031573507253,  0.3801473614495031 },
      {0.3834954252341373,  0.8156531799918592,  0.4381572321995212 },
      {0.4264706721631802,  0.7019453354587277,  0.5837028045549305 },
      {0.4426651245728428,  0.6046940022478110,  0.6749518878980511 },
      {0.4335381868852798,  0.3889255349702319,  0.8233765047686589 },
      {0.4081266718859465,  0.2704933103044611,  0.8806698819698034 },
      {0.3265355626075100,  0.0480012234123341,  0.9520419429501980 },
      {0.2653320575227455,  -0.0697584206823745, 0.9705153073699336 },
      {0.1163623761481023,  -0.2851061254585596, 0.9603861694588721 },
      {0.0286946566145523,  -0.3827563752758174, 0.9316585351406182 },
      {-0.1000107571427154, -0.5028274791588583, 0.8611056764379031 },
      {-0.1493319801493664, -0.5443300430742718, 0.8285829666026215 },
      {-0.2446806998085360, -0.6179089354948579, 0.7506429718643787 },
      {-0.2905944006397387, -0.6500869627469754, 0.7051825625455678 },
      {-0.3781810882717913, -0.7110005367354313, 0.5988632671660471 },
      {-0.4248707899652413, -0.7422360924563658, 0.5254412909782434 },
      {-0.4646137930105206, -0.7862400668881343, 0.4096829498624636 },
      {-0.4728441493623962, -0.8006581376973809, 0.3702575703669145 },
      {-0.4751614183627489, -0.8307715654215799, 0.2928582319959193 },
      {-0.4692628160717102, -0.8465276812346344, 0.2549083604695738 },
      {-0.4542126335031718, -0.8635220311045143, 0.2191359974154113 },
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 62;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1271015378818262, 0.1271015378818262, 0.2542030757636523, 0.2542030757636523, 0.5084061515273046, 0.5084061515273046, 0.7060560997079376,
                       0.7060560997079376, 0.9037060478885706, 0.9037060478885706, 1.2749486506375676, 1.2749486506375676, 1.6461912533865646, 1.6461912533865646, 2.0174338561355611, 2.0174338561355611, 2.3886764588845582, 2.3886764588845582,
                       2.5863264070651910, 2.5863264070651910, 2.7839763552458239, 2.7839763552458239, 3.0381794310094765, 3.0381794310094765, 3.1652809688913024, 3.1652809688913024, 3.2923825067731287, 3.2923825067731287, 3.4194840446549550,
                       3.4194840446549550, 3.5465855825367809, 3.5465855825367809, 3.8007886583004336, 3.8007886583004336, 3.9984386064810664, 3.9984386064810664, 4.1960885546616993, 4.1960885546616993, 4.5673311574106963, 4.5673311574106963,
                       4.9385737601596933, 4.9385737601596933, 5.3098163629086903, 5.3098163629086903, 5.6810589656576873, 5.6810589656576873, 5.8787089138383202, 5.8787089138383202, 6.0763588620189539, 6.0763588620189539, 6.3305619377826066,
                       6.3305619377826066, 6.4576634756644324, 6.4576634756644324, 6.5847650135462583, 6.5847650135462583, 6.5847650135462583, 6.5847650135462583};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    SPAposition base_center1(-0.15215353064525641, -0.065962377703595768, -0.37956704690170506);
    SPAunit_vector base_normal1(-0.35523211172782593, 0.40112063519673408, 0.84434138997016961);
    SPAvector base_maj1(0.87471675961981055, -0.17591099063474069, 0.4515815693915361);
    double base_ratio1 = 1.0;
    ellipse base1(base_center1, base_normal1, base_maj1, base_ratio1);
    cone c1(base1, 0, 1);
    c1.u_param_scale = 1;

    SPAposition sph_center1(0, 0, 0);
    double sph_radius1 = 1;
    sphere sph1(sph_center1, sph_radius1);
    sph1.uv_oridir = SPAunit_vector(1, 0, 0);
    sph1.pole_dir = SPAunit_vector(0, 0, 1);

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0004037172652866, c1, sph1);
    INTCURVE* intc = ACIS_NEW INTCURVE(*ic1);
    ic1 = (intcurve*)intc->trans_curve(*((SPAtransf*)nullptr), TRUE);

    bounded_curve bnd_curve1(ic1, -4.4998022457664835, -2.9544387909211638);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = TRUE;
    int num_ctrlpts2 = 58;
    SPAposition ctrlpts2[] = {
      {-0.4542126335031718, -0.8635220311045143, 0.2191359974154113 },
      {-0.4391624509346332, -0.8805163809743942, 0.1833636343612489 },
      {-0.4163170039982675, -0.8972174414795010, 0.1529925695848732 },
      {-0.3595729082137143, -0.9285616427552063, 0.1010262873898775 },
      {-0.3256605642394095, -0.9431431326504154, 0.0794088601953259 },
      {-0.2139670944982423, -0.9803841131394698, 0.0241501252829262 },
      {-0.1261153989860074, -0.9956278158004623, -0.0002647041768550},
      {0.0205036679909458,  -1.0013723639756464, -0.0342578399761619},
      {0.0912703700519284,  -0.9972578234149370, -0.0478698424987686},
      {0.2302778611793204,  -0.9729774982270906, -0.0737011752077266},
      {0.2984884257094377,  -0.9528043817917691, -0.0860760192562133},
      {0.4712521417702915,  -0.8824829869644365, -0.1202441218027387},
      {0.5818558288298954,  -0.8107315496676848, -0.1460323548903482},
      {0.7606749853583750,  -0.6290892449347527, -0.2068516096194783},
      {0.8289096328034360,  -0.5192690190305979, -0.2420371020185662},
      {0.9105007420818723,  -0.2967769321384710, -0.3134091629989608},
      {0.9288811147209093,  -0.1704052892821463, -0.3539904122207537},
      {0.9081585772546363,  0.0790685780386860,  -0.4314666364511693},
      {0.8690281573189194,  0.2022187237701089,  -0.4681998523884262},
      {0.7819946080862904,  0.3656762773589488,  -0.5090244634945946},
      {0.7429204549589851,  0.4249557021979067,  -0.5221367803608448},
      {0.6534309350724398,  0.5357067163002596,  -0.5396214375223809},
      {0.6030731379863685,  0.5872455416418965,  -0.5438621841938266},
      {0.4913818347018766,  0.6882351612854816,  -0.5404222116277838},
      {0.4182325442817663,  0.7435710850255767,  -0.5288683539340889},
      {0.3192499802384612,  0.8154736353843983,  -0.4847285208800759},
      {0.2881763240828370,  0.8377959880083892,  -0.4655942441401615},
      {0.2350684150199172,  0.8790557643900149,  -0.4168087268928136},
      {0.2130642087965921,  0.8980508175063062,  -0.3871735398854907},
      {0.1829638436595153,  0.9320395172460663,  -0.3156288137771658},
      {0.1762240006554358,  0.9455016404479359,  -0.2769430644817675},
      {0.1749050829341549,  0.9656994930662142,  -0.1963629611631244},
      {0.1802967514673501,  0.9723767011466797,  -0.1544544312129377},
      {0.2073288488147673,  0.9817191057086814,  -0.0275771882387713},
      {0.2393161454160929,  0.9728624403505126,  0.0587057597151184 },
      {0.2919750693556838,  0.9385309428705675,  0.1955782183279028 },
      {0.3174798652119751,  0.9150556042203384,  0.2588913768407666 },
      {0.3633106136302984,  0.8536031573507253,  0.3801473614495031 },
      {0.3834954252341373,  0.8156531799918592,  0.4381572321995212 },
      {0.4264706721631802,  0.7019453354587277,  0.5837028045549305 },
      {0.4426651245728428,  0.6046940022478110,  0.6749518878980511 },
      {0.4335381868852798,  0.3889255349702319,  0.8233765047686589 },
      {0.4081266718859465,  0.2704933103044611,  0.8806698819698034 },
      {0.3265355626075100,  0.0480012234123341,  0.9520419429501980 },
      {0.2653320575227455,  -0.0697584206823745, 0.9705153073699336 },
      {0.1163623761481023,  -0.2851061254585596, 0.9603861694588721 },
      {0.0286946566145523,  -0.3827563752758174, 0.9316585351406182 },
      {-0.1000107571427154, -0.5028274791588583, 0.8611056764379031 },
      {-0.1493319801493664, -0.5443300430742718, 0.8285829666026215 },
      {-0.2446806998085360, -0.6179089354948579, 0.7506429718643787 },
      {-0.2905944006397387, -0.6500869627469754, 0.7051825625455678 },
      {-0.3781810882717913, -0.7110005367354313, 0.5988632671660471 },
      {-0.4248707899652413, -0.7422360924563658, 0.5254412909782434 },
      {-0.4646137930105206, -0.7862400668881343, 0.4096829498624636 },
      {-0.4728441493623962, -0.8006581376973809, 0.3702575703669145 },
      {-0.4751614183627489, -0.8307715654215799, 0.2928582319959193 },
      {-0.4692628160717102, -0.8465276812346344, 0.2549083604695738 },
      {-0.4542126335031718, -0.8635220311045143, 0.2191359974154113 },
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 62;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1271015378818262, 0.1271015378818262, 0.2542030757636523, 0.2542030757636523, 0.5084061515273046, 0.5084061515273046, 0.7060560997079376,
                       0.7060560997079376, 0.9037060478885706, 0.9037060478885706, 1.2749486506375676, 1.2749486506375676, 1.6461912533865646, 1.6461912533865646, 2.0174338561355611, 2.0174338561355611, 2.3886764588845582, 2.3886764588845582,
                       2.5863264070651910, 2.5863264070651910, 2.7839763552458239, 2.7839763552458239, 3.0381794310094765, 3.0381794310094765, 3.1652809688913024, 3.1652809688913024, 3.2923825067731287, 3.2923825067731287, 3.4194840446549550,
                       3.4194840446549550, 3.5465855825367809, 3.5465855825367809, 3.8007886583004336, 3.8007886583004336, 3.9984386064810664, 3.9984386064810664, 4.1960885546616993, 4.1960885546616993, 4.5673311574106963, 4.5673311574106963,
                       4.9385737601596933, 4.9385737601596933, 5.3098163629086903, 5.3098163629086903, 5.6810589656576873, 5.6810589656576873, 5.8787089138383202, 5.8787089138383202, 6.0763588620189539, 6.0763588620189539, 6.3305619377826066,
                       6.3305619377826066, 6.4576634756644324, 6.4576634756644324, 6.5847650135462583, 6.5847650135462583, 6.5847650135462583, 6.5847650135462583};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0004037172652866, c1, sph1);

    bounded_curve bnd_curve2(ic2, 6.0069373760607023, 6.9227087293982237);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
    ACIS_DELETE ic1;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug27) {
    int degree1 = 3;
    logical rational1 = FALSE;
    logical closed1 = FALSE;
    logical periodic1 = TRUE;
    int num_ctrlpts1 = 36;
    SPAposition ctrlpts1[] = {
      {-1.0000000000000000, 0.0000000000000000,  1.0000000000000000},
      {-1.0000000000000000, -0.1309632330281509, 1.0000000000000000},
      {-0.9742729478713059, -0.2606598722647817, 1.0000000553585191},
      {-0.8742938317175466, -0.5027540792716754, 0.9999996631540577},
      {-0.8010086375566914, -0.6128103365001154, 0.9999991389288483},
      {-0.6161905615282453, -0.7984112726431887, 0.9999991291085898},
      {-0.5064450359108883, -0.8721609780073001, 0.9999996513896536},
      {-0.2647755904056850, -0.9731625019126522, 1.0000000542919496},
      {-0.1351888480849031, -0.9994375024556952, 0.9999999999999997},
      {0.1282363147557017,  -1.0005509764976397, 1.0000000000000000},
      {0.2595000388993531,  -0.9747853681251377, 1.0000019994737284},
      {0.5029591316729203,  -0.8741760331474620, 0.9999948870374301},
      {0.6129980998649147,  -0.8008647797568589, 1.0000192730814976},
      {0.7985541456427949,  -0.6160051007198883, 0.9996432259721454},
      {0.8722743323129283,  -0.5062462144893916, 0.9992498007423847},
      {0.9731856472359715,  -0.2646477270867758, 0.9962239813998045},
      {0.9994178084569771,  -0.1352046382419663, 0.9934483914843394},
      {1.0005633455539495,  0.1265219753747244,  0.9848886508106695},
      {0.9754232359782700,  0.2562502662264583,  0.9791759216250971},
      {0.8766658796369882,  0.4985781307498067,  0.9695975265355838},
      {0.8039603309359515,  0.6089457170923076,  0.9661605623065445},
      {0.6205779486578944,  0.7948674845962964,  0.9659463173141397},
      {0.5120903610746099,  0.8687076418955053,  0.9691329382266052},
      {0.2721983999804456,  0.9710999482903730,  0.9784836615835737},
      {0.1429102088557661,  0.9983593262229338,  0.9842410050201565},
      {-0.1188799659434090, 1.0014963065239115,  0.9930129217011334},
      {-0.2487780211380572, 0.9773691299399863,  0.9959339897587564},
      {-0.4919107169921526, 0.8804199330873255,  0.9991508556918658},
      {-0.6027580160992265, 0.8085799010815222,  0.9995949910113208},
      {-0.7905768396674775, 0.6262085826517980,  1.0000171538226972},
      {-0.8657005495692096, 0.5174090083414606,  0.9999934246733000},
      {-0.9697422418678405, 0.2770403351733375,  1.0000024069980651},
      {-0.9976511360926827, 0.1477956490751922,  0.9999999999998017},
      {-0.9999526683217077, 0.0112345702405419,  1.0000000000000040},
      {-1.0000000000000000, 0.0056173349725972,  1.0000000000000000},
      {-1.0000000000000000, 0.0000000000000000,  1.0000000000000000},
    };
    double* weights1 = nullptr;
    double ctrlpt_tol1 = SPAresabs;
    int num_knots1 = 40;
    double knots1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.3928896990844548, 0.3928896990844548, 0.7857796551961505, 0.7857796551961505, 1.1786698683086234, 1.1786698683086234,
                       1.5715603385107186, 1.5715603385107186, 1.9689544847736551, 1.9689544847736551, 2.3618484303764720, 2.3618484303764720, 2.7547417087100605, 2.7547417087100605, 3.1474170648294031, 3.1474170648294031,
                       3.5403053611958804, 3.5403053611958804, 3.9332915392858423, 3.9332915392858423, 4.3235695357944373, 4.3235695357944373, 4.7165828385522746, 4.7165828385522746, 5.1093969583642718, 5.1093969583642718,
                       5.5019186904114825, 5.5019186904114825, 5.8947870312915018, 5.8947870312915018, 6.2876764420589746, 6.2876764420589746, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644};
    double knot_tol1 = SPAresabs;
    const int& dimension1 = 3;

    bs3_curve bs1 = bs3_curve_from_ctrlpts(degree1, rational1, closed1, periodic1, num_ctrlpts1, ctrlpts1, weights1, ctrlpt_tol1, num_knots1, knots1, knot_tol1, dimension1);

    logical rationalu = FALSE;
    int degreeu = 3;
    int num_ctrlptsu = 4;
    int formu = 0;
    int poleu = 0;
    logical rationalv = FALSE;
    int degreev = 3;
    int num_ctrlptsv = 4;
    int formv = 0;
    int polev = 0;
    const SPAposition ctrlpts_sur[] = {
      {-4.0000000000000000, -4.0000000000000000, 0.0000000000000000},
      {-4.0000000000000000, -2.0000000000000000, 2.0000000000000000},
      {-4.0000000000000000, 0.0000000000000000,  0.0000000000000000},
      {-4.0000000000000000, 2.0000000000000000,  2.0000000000000000},

      {-2.0000000000000000, -4.0000000000000000, 2.0000000000000000},
      {-2.0000000000000000, -2.0000000000000000, 0.0000000000000000},
      {-2.0000000000000000, 0.0000000000000000,  2.0000000000000000},
      {-2.0000000000000000, 2.0000000000000000,  0.0000000000000000},

      {0.0000000000000000,  -4.0000000000000000, 0.0000000000000000},
      {0.0000000000000000,  -2.0000000000000000, 2.0000000000000000},
      {0.0000000000000000,  0.0000000000000000,  0.0000000000000000},
      {0.0000000000000000,  2.0000000000000000,  2.0000000000000000},

      {2.0000000000000000,  -4.0000000000000000, 2.0000000000000000},
      {2.0000000000000000,  -2.0000000000000000, 0.0000000000000000},
      {2.0000000000000000,  0.0000000000000000,  2.0000000000000000},
      {2.0000000000000000,  2.0000000000000000,  0.0000000000000000},
    };
    const double* weights_sur = nullptr;
    double ctrlpt_tol_sur = SPAresabs;
    int num_knotsu = 8;
    double knotsu[] = {
      0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000,
    };
    int num_knotsv = 8;
    double knotsv[] = {
      0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000, 1.0000000000000000,
    };
    double knot_tol_sur = 0.0000000001000000;
    bs3_surface bss = bs3_surface_from_ctrlpts(degreeu, rationalu, formu, poleu, num_ctrlptsu, degreev, rationalv, formv, polev, num_ctrlptsv, ctrlpts_sur, weights_sur, ctrlpt_tol_sur, num_knotsu, knotsu, num_knotsv, knotsv, ctrlpt_tol_sur);
    spline spline_sur(bss);

    int degree_p1 = 3;
    logical rational_p1 = FALSE;
    logical closed_p1 = FALSE;
    logical periodic_p1 = TRUE;
    const int num_ctrlpts_p1 = 52;
    SPAposition ctrlpts_p1[] = {
      {0.5000000000000000, 0.6666666666666667, 0.0000000000000000},
      {0.5000000000000000, 0.6448394611619748, 0.0000000000000000},
      {0.5042878420214491, 0.6232233546225364, 0.0000000000000000},
      {0.5126194323090119, 0.6030488439710135, 0.0000000000000000},
      {0.5209510280470756, 0.5828743201213875, 0.0000000000000000},
      {0.5331652270738847, 0.5645316105833140, 0.0000000000000000},
      {0.5485667283723030, 0.5490648709633473, 0.0000000000000000},
      {0.5639682397452924, 0.5335981212261351, 0.0000000000000000},
      {0.5822591606815186, 0.5213065036654499, 0.0000000000000000},
      {0.6023982745512220, 0.5128897127604547, 0.0000000000000000},
      {0.6225374015990525, 0.5044729163478914, 0.0000000000000000},
      {0.6441351919858495, 0.5000937495907175, 0.0000000000000000},
      {0.6659621882213862, 0.5000014888762898, 0.0000000000000000},
      {0.6880393857926170, 0.4999081705837267, 0.0000000000000000},
      {0.7099166731498922, 0.5042024386458104, 0.0000000000000000},
      {0.7303204599289409, 0.5126342922088878, 0.0000000000000000},
      {0.7504931886121533, 0.5209706611420897, 0.0000000000000000},
      {0.7688330166441525, 0.5331892033738568, 0.0000000000000000},
      {0.7842960335897399, 0.5485941897084238, 0.0000000000000000},
      {0.7997590242737992, 0.5639991498800186, 0.0000000000000000},
      {0.8120457220521546, 0.5822922975851014, 0.0000000000000000},
      {0.8204573310875803, 0.6024310899606723, 0.0000000000000000},
      {0.8288642745393286, 0.6225587121522040, 0.0000000000000000},
      {0.8332363014094962, 0.6441325602930056, 0.0000000000000000},
      {0.8333317369578184, 0.6659371993108262, 0.0000000000000000},
      {0.8334272242589916, 0.6877536625624541, 0.0000000000000000},
      {0.8292372059963783, 0.7093750443710765, 0.0000000000000000},
      {0.8210084513314088, 0.7295665178928830, 0.0000000000000000},
      {0.8127776466061647, 0.7497630217916345, 0.0000000000000000},
      {0.8006600551559919, 0.7681576195153846, 0.0000000000000000},
      {0.7853253520256758, 0.7837046697539095, 0.0000000000000000},
      {0.7700963247763157, 0.7991445807660494, 0.0000000000000000},
      {0.7520150601791017, 0.8114512736492508, 0.0000000000000000},
      {0.7320938733354099, 0.8199541691099622, 0.0000000000000000},
      {0.7120330666634076, 0.8285166580483956, 0.0000000000000000},
      {0.6904850348092944, 0.8330598877038223, 0.0000000000000000},
      {0.6686636572666885, 0.8333213689895270, 0.0000000000000000},
      {0.6468533390094319, 0.8335827177539852, 0.0000000000000000},
      {0.6252036631436572, 0.8295615216566644, 0.0000000000000000},
      {0.6049350617774724, 0.8214794139957615, 0.0000000000000000},
      {0.5846815471679745, 0.8134033221812209, 0.0000000000000000},
      {0.5662069973167956, 0.8014299835135871, 0.0000000000000000},
      {0.5505623360460578, 0.7862390806630317, 0.0000000000000000},
      {0.5349038600554203, 0.7710347637752997, 0.0000000000000000},
      {0.5223832417384651, 0.7529015013902435, 0.0000000000000000},
      {0.5137133332011304, 0.7328713157447959, 0.0000000000000000},
      {0.5050429596886933, 0.7128400558622229, 0.0000000000000000},
      {0.5003914773178861, 0.6912992748458653, 0.0000000000000000},
      {0.5000236649990640, 0.6694751846012962, 0.0000000000000000},
      {0.5000078886130487, 0.6685390950400902, 0.0000000000000000},
      {0.5000000000000000, 0.6676028891620995, 0.0000000000000000},
      {0.5000000000000000, 0.6666666666666667, 0.0000000000000000},
    };
    double* weights_p1 = nullptr;
    double ctrlpt_tol_p1 = SPAresabs;
    int num_knots_p1 = 56;
    double knots_p1[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.3928896990844548, 0.3928896990844548, 0.3928896990844548, 0.7857796551961505, 0.7857796551961505, 0.7857796551961505,
                         1.1786698683086234, 1.1786698683086234, 1.1786698683086234, 1.5715603385107186, 1.5715603385107186, 1.5715603385107186, 1.9689544847736551, 1.9689544847736551, 1.9689544847736551, 2.3618484303764720,
                         2.3618484303764720, 2.3618484303764720, 2.7547417087100605, 2.7547417087100605, 2.7547417087100605, 3.1474170648294031, 3.1474170648294031, 3.1474170648294031, 3.5403053611958804, 3.5403053611958804,
                         3.5403053611958804, 3.9332915392858423, 3.9332915392858423, 3.9332915392858423, 4.3235695357944373, 4.3235695357944373, 4.3235695357944373, 4.7165828385522746, 4.7165828385522746, 4.7165828385522746,
                         5.1093969583642718, 5.1093969583642718, 5.1093969583642718, 5.5019186904114825, 5.5019186904114825, 5.5019186904114825, 5.8947870312915018, 5.8947870312915018, 5.8947870312915018, 6.2876764420589746,
                         6.2876764420589746, 6.2876764420589746, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644};
    double knot_tol_p1 = SPAresabs;
    const int dimension_p1 = 2;
    bs2_curve pcurve12 = bs2_curve_from_ctrlpts(degree_p1, rational_p1, closed_p1, periodic_p1, num_ctrlpts_p1, ctrlpts_p1, weights_p1, ctrlpt_tol_p1, num_knots_p1, knots_p1, knot_tol_p1);

    SPAposition base_center1(0, 0, 0);
    SPAunit_vector base_normal1(0, 0, 1);
    SPAvector base_maj1(1, 0, 0);
    double base_ratio1 = 1.0;
    ellipse base1(base_center1, base_normal1, base_maj1, base_ratio1);
    cone c1(base1, 0, 1);
    c1.u_param_scale = 1;

    intcurve* ic1 = ACIS_NEW intcurve(bs1, 0.0000500215841095, spline_sur, c1, pcurve12, nullptr);
    bounded_curve bnd_curve1(ic1, 0.0000000000000000, 1.5757876743983688);
    EDGE* e1 = bnd_curve1.make_edge();

    int degree2 = 3;
    logical rational2 = FALSE;
    logical closed2 = FALSE;
    logical periodic2 = TRUE;
    int num_ctrlpts2 = 36;
    SPAposition ctrlpts2[] = {
      {-1.0000000000000000, 0.0000000000000000,  1.0000000000000000},
      {-1.0000000000000000, -0.1309632330281509, 1.0000000000000000},
      {-0.9742729478713059, -0.2606598722647817, 1.0000000553585191},
      {-0.8742938317175466, -0.5027540792716754, 0.9999996631540577},
      {-0.8010086375566914, -0.6128103365001154, 0.9999991389288483},
      {-0.6161905615282453, -0.7984112726431887, 0.9999991291085898},
      {-0.5064450359108883, -0.8721609780073001, 0.9999996513896536},
      {-0.2647755904056850, -0.9731625019126522, 1.0000000542919496},
      {-0.1351888480849031, -0.9994375024556952, 0.9999999999999997},
      {0.1282363147557017,  -1.0005509764976397, 1.0000000000000000},
      {0.2595000388993531,  -0.9747853681251377, 1.0000019994737284},
      {0.5029591316729203,  -0.8741760331474620, 0.9999948870374301},
      {0.6129980998649147,  -0.8008647797568589, 1.0000192730814976},
      {0.7985541456427949,  -0.6160051007198883, 0.9996432259721454},
      {0.8722743323129283,  -0.5062462144893916, 0.9992498007423847},
      {0.9731856472359715,  -0.2646477270867758, 0.9962239813998045},
      {0.9994178084569771,  -0.1352046382419663, 0.9934483914843394},
      {1.0005633455539495,  0.1265219753747244,  0.9848886508106695},
      {0.9754232359782700,  0.2562502662264583,  0.9791759216250971},
      {0.8766658796369882,  0.4985781307498067,  0.9695975265355838},
      {0.8039603309359515,  0.6089457170923076,  0.9661605623065445},
      {0.6205779486578944,  0.7948674845962964,  0.9659463173141397},
      {0.5120903610746099,  0.8687076418955053,  0.9691329382266052},
      {0.2721983999804456,  0.9710999482903730,  0.9784836615835737},
      {0.1429102088557661,  0.9983593262229338,  0.9842410050201565},
      {-0.1188799659434090, 1.0014963065239115,  0.9930129217011334},
      {-0.2487780211380572, 0.9773691299399863,  0.9959339897587564},
      {-0.4919107169921526, 0.8804199330873255,  0.9991508556918658},
      {-0.6027580160992265, 0.8085799010815222,  0.9995949910113208},
      {-0.7905768396674775, 0.6262085826517980,  1.0000171538226972},
      {-0.8657005495692096, 0.5174090083414606,  0.9999934246733000},
      {-0.9697422418678405, 0.2770403351733375,  1.0000024069980651},
      {-0.9976511360926827, 0.1477956490751922,  0.9999999999998017},
      {-0.9999526683217077, 0.0112345702405419,  1.0000000000000040},
      {-1.0000000000000000, 0.0056173349725972,  1.0000000000000000},
      {-1.0000000000000000, 0.0000000000000000,  1.0000000000000000},
    };
    double* weights2 = nullptr;
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 40;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.3928896990844548, 0.3928896990844548, 0.7857796551961505, 0.7857796551961505, 1.1786698683086234, 1.1786698683086234,
                       1.5715603385107186, 1.5715603385107186, 1.9689544847736551, 1.9689544847736551, 2.3618484303764720, 2.3618484303764720, 2.7547417087100605, 2.7547417087100605, 3.1474170648294031, 3.1474170648294031,
                       3.5403053611958804, 3.5403053611958804, 3.9332915392858423, 3.9332915392858423, 4.3235695357944373, 4.3235695357944373, 4.7165828385522746, 4.7165828385522746, 5.1093969583642718, 5.1093969583642718,
                       5.5019186904114825, 5.5019186904114825, 5.8947870312915018, 5.8947870312915018, 6.2876764420589746, 6.2876764420589746, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644, 6.3045284469767644};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);

    intcurve* ic2 = ACIS_NEW intcurve(bs2, 0.0000500215841095, spline_sur, c1, pcurve12, nullptr);

    bounded_curve bnd_curve2(ic2, 1.5757876743983688, 6.3045284469767644);
    EDGE* e2 = bnd_curve2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(*ic1, *ic2);
    gme_inters = answer_int_cur_cur(*ic1, *ic2);

    judge(gme_inters, acis_inters);
}



TEST_F(NurbsNurbsIntrTest, TestBug30) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 16;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.3949155745080013,      -0.10000075912362227, 0.3828081850341658   },
      {0.3948554827288249,      -0.09984591768552523, 0.3827589430218397   },
      {0.394795400148365,       -0.09969107583623282, 0.3827096910605595   },
      {0.39089661974808915,     -0.08964176854189403, 0.37951257966720847  },
      {0.387095019361145,       -0.07974454074941655, 0.3763238147799424   },
      {0.37572849646897544,     -0.04987239118822327, 0.3665876576110055   },
      {0.3682677474299672,      -0.02988316391172019, 0.3599219004657436   },
      {0.33100905993264496,     0.07163732978044149,  0.3254206044984594   },
      {0.30293315611105404,     0.15382481212093152,  0.29537292591572745  },
      {0.19124868330509276,     0.4891897146495362,   0.1695831196655615   },
      {0.11302338946109512,     0.7376251920637067,   0.066640768647696    },
      {0.01010337916684472,     0.9768692198477829,   0.005629104113179225 },
      {0.006450789077530798,    0.9852844447988268,   0.0035389976594767374},
      {0.0018455688400169693,   0.9957998878376213,   0.001002062594600703 },
      {0.000923809311963928,    0.9978999421986211,   0.00049913630143657  },
      {-1.1789772747560903e-29, 1,                    -6.37004140116851e-30},
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 20;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0005197162859582544,
      0.0005197162859582544,
      0.03372973865624184,
      0.03372973865624184,
      0.10075475140775494,
      0.10075475140775494,
      0.37427199592706006,
      0.37427199592706006,
      1.2276694580129779,
      1.2276694580129779,
      1.2587808600289019,
      1.2587808600289019,
      1.2665446884922236,
      1.2665446884922236,
      1.2665446884922236,
      1.2665446884922236,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);

    const char* law_str_surf1_cur1 = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur_law_surf1_cur1 = nullptr;
    api_str_to_law(law_str_surf1_cur1, &sur_law_surf1_cur1);
    FACE* face_surf1_cur1 = nullptr;
    api_face_law(sur_law_surf1_cur1, -10, 10, -10, 10, face_surf1_cur1);
    spline spl_surf1_cur1 = *(spline*)&face_surf1_cur1->geometry()->equation();

    int bs2_degree_pcurve1_cur1 = 3;
    logical bs2_rational_pcurve1_cur1 = 0;
    logical bs2_closed_pcurve1_cur1 = FALSE;
    logical bs2_periodic_pcurve1_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur1 = 22;
    const SPAposition bs2_ctrlpts_pcurve1_cur1[] = {
      {0.3949155745080013,    -0.10000075912362227,  0},
      {0.3948554827288249,    -0.09984591768552523,  0},
      {0.394795400148365,     -0.09969107583623282,  0},
      {0.3947353267606033,    -0.09953623358510555,  0},
      {0.39089661974808915,   -0.08964176854189403,  0},
      {0.387095019361145,     -0.07974454074941655,  0},
      {0.3833290459261818,    -0.06984725529458302,  0},
      {0.37572849646897544,   -0.04987239118822327,  0},
      {0.3682677474299672,    -0.029883163911720193, 0},
      {0.3609345488289293,    -0.009902053670691302, 0},
      {0.33100905993264496,   0.0716373297804415,    0},
      {0.30293315611105404,   0.15382481212093152,   0},
      {0.27582584348266437,   0.23522235135833824,   0},
      {0.1912486833050928,    0.4891897146495362,    0},
      {0.11302338946109511,   0.7376251920637067,    0},
      {0.01372345121552776,   0.9684541350132658,    0},
      {0.01010337916684472,   0.9768692198477829,    0},
      {0.006450789077530798,  0.9852844447988268,    0},
      {0.0027652840293317382, 0.9936998335109308,    0},
      {0.0018455688400169693, 0.9957998878376213,    0},
      {0.0009238093119639279, 0.9978999421986211,    0},
      {0,                     1,                     0},
    };
    const double* bs2_weights_pcurve1_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur1 = 1e-06;
    int bs2_num_knots_pcurve1_cur1 = 26;
    const double bs2_knots_pcurve1_cur1[] = {
      0,
      0,
      0,
      0,
      0.0005197162859582544,
      0.0005197162859582544,
      0.0005197162859582544,
      0.03372973865624184,
      0.03372973865624184,
      0.03372973865624184,
      0.10075475140775494,
      0.10075475140775494,
      0.10075475140775494,
      0.37427199592706006,
      0.37427199592706006,
      0.37427199592706006,
      1.2276694580129779,
      1.2276694580129779,
      1.2276694580129779,
      1.2587808600289019,
      1.2587808600289019,
      1.2587808600289019,
      1.2665446884922236,
      1.2665446884922236,
      1.2665446884922236,
      1.2665446884922236,
    };
    double bs2_knot_tol_pcurve1_cur1 = 1e-10;
    bs2_curve bs2_pcurve1_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur1, bs2_rational_pcurve1_cur1, bs2_closed_pcurve1_cur1, bs2_periodic_pcurve1_cur1, bs2_num_ctrlpts_pcurve1_cur1, bs2_ctrlpts_pcurve1_cur1, bs2_weights_pcurve1_cur1,
                                                        bs2_ctrlpt_tol_pcurve1_cur1, bs2_num_knots_pcurve1_cur1, bs2_knots_pcurve1_cur1, bs2_knot_tol_pcurve1_cur1);
    SPAposition c_base_center_surf2_cur1(0, 0.5, 0);
    SPAunit_vector c_base_normal_surf2_cur1(0, 1, 0);
    SPAvector c_base_major_surf2_cur1(0.25, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, -0.4472135954999579, 0.8944271909999159);
    c_surf2_cur1.u_param_scale = 0.25;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.0007681136763327489, spl_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 0.11182320761881359, 1.2665446884922236);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 6;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.39491527990290015,  -0.09999999999999998, 0.3828079436208371 },
      {0.298950067847776,    0.14727839995680514,  0.30416947252827364},
      {0.22316494070421655,  0.40517990701073503,  0.19719334675615074},
      {0.10715692829692705,  0.735101542067369,    0.07805224228547608},
      {0.07337268408423359,  0.8254406977477795,   0.04731787016166726},
      {0.036438299123789264, 0.9146369299445531,   0.02222529622207053},
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 10;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 0, 0.8299755679005419, 0.8299755679005419, 1.1360166414735497, 1.1360166414735497, 1.1360166414735497, 1.1360166414735497,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);

    const char* law_str_surf1_cur2 = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur_law_surf1_cur2 = nullptr;
    api_str_to_law(law_str_surf1_cur2, &sur_law_surf1_cur2);
    FACE* face_surf1_cur2 = nullptr;
    api_face_law(sur_law_surf1_cur2, -10, 10, -10, 10, face_surf1_cur2);
    spline spl_surf1_cur2 = *(spline*)&face_surf1_cur2->geometry()->equation();

    int bs2_degree_pcurve1_cur2 = 3;
    logical bs2_rational_pcurve1_cur2 = 0;
    logical bs2_closed_pcurve1_cur2 = FALSE;
    logical bs2_periodic_pcurve1_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur2 = 7;
    const SPAposition bs2_ctrlpts_pcurve1_cur2[] = {
      {0.3949152799029001,   -0.09999999999999964, 0},
      {0.2989500678477759,   0.14727839995680547,  0},
      {0.22316494070421655,  0.40517990701073503,  0},
      {0.13840930204221458,  0.6462211791382444,   0},
      {0.10715692829692705,  0.735101542067369,    0},
      {0.07337268408423359,  0.8254406977477795,   0},
      {0.036438299123789264, 0.9146369299445531,   0},
    };
    const double* bs2_weights_pcurve1_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur2 = 1e-06;
    int bs2_num_knots_pcurve1_cur2 = 11;
    const double bs2_knots_pcurve1_cur2[] = {
      0, 0, 0, 0, 0.8299755679005419, 0.8299755679005419, 0.8299755679005419, 1.1360166414735497, 1.1360166414735497, 1.1360166414735497, 1.1360166414735497,
    };
    double bs2_knot_tol_pcurve1_cur2 = 1e-10;
    bs2_curve bs2_pcurve1_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur2, bs2_rational_pcurve1_cur2, bs2_closed_pcurve1_cur2, bs2_periodic_pcurve1_cur2, bs2_num_ctrlpts_pcurve1_cur2, bs2_ctrlpts_pcurve1_cur2, bs2_weights_pcurve1_cur2,
                                                        bs2_ctrlpt_tol_pcurve1_cur2, bs2_num_knots_pcurve1_cur2, bs2_knots_pcurve1_cur2, bs2_knot_tol_pcurve1_cur2);
    SPAposition c_base_center_surf2_cur2(0, 0.5, 0);
    SPAunit_vector c_base_normal_surf2_cur2(0, 1, 0);
    SPAvector c_base_major_surf2_cur2(0.25, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, -0.4472135954999579, 0.8944271909999159);
    c_surf2_cur2.u_param_scale = 0.25;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00010163242766327534, spl_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0.11131763632212936, 1.1360166414735497);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}


TEST_F(NurbsNurbsIntrTest, TestBug39) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 6;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.24928990588176173, 0.03915836684661168, -8.304266969473277e-19 },
      {0.2445844339504596,  0.03915836684661168, -8.304266969473277e-19 },
      {0.23987896201915743, 0.03915836684661171, -1.3672325639285028e-20},
      {0.2350990604184602,  0.03915836684661168, -1.3672325639285028e-20},
      {0.23502463074906516, 0.03915836684661168, -4.557502819313009e-21 },
      {0.23495020107967007, 0.03915836684661168, 5.608124625975387e-34  },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 10;
    const double bs3_knots_cur1[] = {
      0, 0, 0, 0, 0.014116415793906434, 0.014116415793906434, 0.014339704802091652, 0.014339704802091652, 0.014339704802091652, 0.014339704802091652,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAmatrix affine_mat_surf1_cur1(SPAvector(1, 0, 0), SPAvector(0, 1, 0), SPAvector(0, 0, 1));
    SPAvector translate_vec_surf1_cur1(0, 0, 0);
    SPAtransf transf_surf1_cur1(affine_mat_surf1_cur1, translate_vec_surf1_cur1, 0.024928990588176173, FALSE, FALSE, FALSE);

    const char* law_str_surf1_cur1 = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur_law_surf1_cur1 = nullptr;
    api_str_to_law(law_str_surf1_cur1, &sur_law_surf1_cur1);
    FACE* face_surf1_cur1 = nullptr;
    api_face_law(sur_law_surf1_cur1, -10, 10, -10, 10, face_surf1_cur1);
    spline spl_surf1_cur1 = *(spline*)&face_surf1_cur1->geometry()->equation();
    spl_surf1_cur1 *= transf_surf1_cur1;
    int bs2_degree_pcurve1_cur1 = 3;
    logical bs2_rational_pcurve1_cur1 = 0;
    logical bs2_closed_pcurve1_cur1 = FALSE;
    logical bs2_periodic_pcurve1_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur1 = 7;
    const SPAposition bs2_ctrlpts_pcurve1_cur1[] = {
      {10,                1.5707963267948966, 0},
      {9.811244987451119, 1.5707963267948966, 0},
      {9.622489974902237, 1.570796326794898,  0},
      {9.433734962353356, 1.5707963267948966, 0},
      {9.430749295158696, 1.5707963267948966, 0},
      {9.427763627964039, 1.5707963267948966, 0},
      {9.42477796076938,  1.5707963267948966, 0},
    };
    const double* bs2_weights_pcurve1_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur1 = 1e-06;
    int bs2_num_knots_pcurve1_cur1 = 11;
    const double bs2_knots_pcurve1_cur1[] = {
      0, 0, 0, 0, 0.014116415793906434, 0.014116415793906434, 0.014116415793906434, 0.014339704802091652, 0.014339704802091652, 0.014339704802091652, 0.014339704802091652,
    };
    double bs2_knot_tol_pcurve1_cur1 = 1e-10;
    bs2_curve bs2_pcurve1_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur1, bs2_rational_pcurve1_cur1, bs2_closed_pcurve1_cur1, bs2_periodic_pcurve1_cur1, bs2_num_ctrlpts_pcurve1_cur1, bs2_ctrlpts_pcurve1_cur1, bs2_weights_pcurve1_cur1,
                                                        bs2_ctrlpt_tol_pcurve1_cur1, bs2_num_knots_pcurve1_cur1, bs2_knots_pcurve1_cur1, bs2_knot_tol_pcurve1_cur1);
    SPAposition pln_root_surf2_cur1(0, 0, 0);
    SPAunit_vector pln_dir_surf2_cur1(0, 0, 1);
    plane pln_surf2_cur1(pln_root_surf2_cur1, pln_dir_surf2_cur1);
    pln_surf2_cur1.u_deriv = SPAvector(1, 0, 0);
    pln_surf2_cur1.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 1e-11, spl_surf1_cur1, pln_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 0, 0.014339704802091652);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 12;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.1566334673864467,  0.03915836684661168,  -3.738749750650258e-34},
      {0.15670789705584182, 0.03915836684661168,  4.557502819315462e-21 },
      {0.15678232672523693, 0.03915836684661168,  1.3672325639290637e-20},
      {0.17242647814966763, 0.03915836684661178,  1.3672325639290637e-20},
      {0.1879961999047032,  0.03915836684660545,  7.419312023765436e-15 },
      {0.20875994531932054, 0.039158366846603364, 7.419312023765436e-15 },
      {0.21395396897890231, 0.039158366846606445, 4.328510969429832e-15 },
      {0.22434096578281765, 0.0391583668466023,   4.328510969429832e-15 },
      {0.22953393892715127, 0.03915836684661171,  1.367232563928615e-20 },
      {0.23480134174087994, 0.03915836684661168,  1.367232563928615e-20 },
      {0.234875771410275,   0.03915836684661168,  4.55750281931413e-21  },
      {0.23495020107967007, 0.03915836684661168,  5.608124625975387e-34 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 16;
    const double bs3_knots_cur2[] = {
      -0.00022328900818532893, -0.00022328900818532893, -0.00022328900818532893, -0.00022328900818532893, 0, 0, 0.04670916526510677, 0.04670916526510677, 0.06229123624385202, 0.06229123624385202, 0.07787015567685282, 0.07787015567685282,
      0.07809344468503804,     0.07809344468503804,     0.07809344468503804,     0.07809344468503804,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAmatrix affine_mat_surf1_cur2(SPAvector(1, 0, 0), SPAvector(0, 1, 0), SPAvector(0, 0, 1));
    SPAvector translate_vec_surf1_cur2(0, 0, 0);
    SPAtransf transf_surf1_cur2(affine_mat_surf1_cur2, translate_vec_surf1_cur2, 0.024928990588176173, FALSE, FALSE, FALSE);

    const char* law_str_surf1_cur2 = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur_law_surf1_cur2 = nullptr;
    api_str_to_law(law_str_surf1_cur2, &sur_law_surf1_cur2);
    FACE* face_surf1_cur2 = nullptr;
    api_face_law(sur_law_surf1_cur2, -10, 10, -10, 10, face_surf1_cur2);
    spline spl_surf1_cur2 = *(spline*)&face_surf1_cur2->geometry()->equation();
    spl_surf1_cur2 *= transf_surf1_cur2;
    int bs2_degree_pcurve1_cur2 = 3;
    logical bs2_rational_pcurve1_cur2 = 0;
    logical bs2_closed_pcurve1_cur2 = FALSE;
    logical bs2_periodic_pcurve1_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur2 = 16;
    const SPAposition bs2_ctrlpts_pcurve1_cur2[] = {
      {6.283185307179586, 1.5707963267948966, 0},
      {6.286170974374246, 1.5707963267948966, 0},
      {6.289156641568906, 1.5707963267948966, 0},
      {6.292142308763566, 1.5707963267948966, 0},
      {6.916705172629394, 1.5707963267949008, 0},
      {7.541268036495223, 1.570796326794647,  0},
      {8.165830900361051, 1.570796326794584,  0},
      {8.374183646983903, 1.5707963267945628, 0},
      {8.582536393606757, 1.5707963267946865, 0},
      {8.79088914022961,  1.5707963267946035, 0},
      {8.999199746548207, 1.5707963267945204, 0},
      {9.207510352866805, 1.570796326794898,  0},
      {9.415820959185403, 1.5707963267948966, 0},
      {9.418806626380062, 1.5707963267948966, 0},
      {9.42179229357472,  1.5707963267948966, 0},
      {9.42477796076938,  1.5707963267948966, 0},
    };
    const double* bs2_weights_pcurve1_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur2 = 1e-06;
    int bs2_num_knots_pcurve1_cur2 = 20;
    const double bs2_knots_pcurve1_cur2[] = {
      -0.00022328900818532893,
      -0.00022328900818532893,
      -0.00022328900818532893,
      -0.00022328900818532893,
      0,
      0,
      0,
      0.04670916526510677,
      0.04670916526510677,
      0.04670916526510677,
      0.06229123624385202,
      0.06229123624385202,
      0.06229123624385202,
      0.07787015567685282,
      0.07787015567685282,
      0.07787015567685282,
      0.07809344468503804,
      0.07809344468503804,
      0.07809344468503804,
      0.07809344468503804,
    };
    double bs2_knot_tol_pcurve1_cur2 = 1e-10;
    bs2_curve bs2_pcurve1_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur2, bs2_rational_pcurve1_cur2, bs2_closed_pcurve1_cur2, bs2_periodic_pcurve1_cur2, bs2_num_ctrlpts_pcurve1_cur2, bs2_ctrlpts_pcurve1_cur2, bs2_weights_pcurve1_cur2,
                                                        bs2_ctrlpt_tol_pcurve1_cur2, bs2_num_knots_pcurve1_cur2, bs2_knots_pcurve1_cur2, bs2_knot_tol_pcurve1_cur2);
    SPAposition pln_root_surf2_cur2(0, 0, 0);
    SPAunit_vector pln_dir_surf2_cur2(0, 0, 1);
    plane pln_surf2_cur2(pln_root_surf2_cur2, pln_dir_surf2_cur2);
    pln_surf2_cur2.u_deriv = SPAvector(1, 0, 0);
    pln_surf2_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 1e-11, spl_surf1_cur2, pln_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, -0.00022328900818532893, 0.07809344468503804);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;

    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    judge(gme_inters, acis_inters);
}


TEST_F(NurbsNurbsIntrTest, TestBug42) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 4;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {5.493117424269991e-23, 1.1500000000000001,   2.2438694791162213e-23},
      {5.493117424269991e-23, 0.7166666666666668,   4.4165679310620625e-23},
      {0,                     0.2833333333333334,   0                     },
      {0,                     -0.15000000000000002, 0                     },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 8;
    const double bs3_knots_cur1[] = {
      -1.3000000000000003, -1.3000000000000003, -1.3000000000000003, -1.3000000000000003, -0, -0, -0, -0,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition pln_root_surf1_cur1(0, 0.5, 0.5);
    SPAunit_vector pln_dir_surf1_cur1(1, 0, 0);
    plane pln_surf1_cur1(pln_root_surf1_cur1, pln_dir_surf1_cur1);
    pln_surf1_cur1.u_deriv = SPAvector(0, 0, -1);
    pln_surf1_cur1.reverse_v = FALSE;
    bs2_curve bs2_pcurve1_cur1 = nullptr;

    const char* law_str_surf2_cur1 = "VEC(X,Y,SIN(X)*COS(Y))";
    law* sur_law_surf2_cur1 = nullptr;
    api_str_to_law(law_str_surf2_cur1, &sur_law_surf2_cur1);
    FACE* face_surf2_cur1 = nullptr;
    api_face_law(sur_law_surf2_cur1, -10, 10, -10, 10, face_surf2_cur1);
    spline spl_surf2_cur1 = *(spline*)&face_surf2_cur1->geometry()->equation();

    int bs2_degree_pcurve2_cur1 = 3;
    logical bs2_rational_pcurve2_cur1 = 0;
    logical bs2_closed_pcurve2_cur1 = FALSE;
    logical bs2_periodic_pcurve2_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve2_cur1 = 4;
    const SPAposition bs2_ctrlpts_pcurve2_cur1[] = {
      {0, 1.1500000000000004,   0},
      {0, 0.716666666666667,    0},
      {0, 0.28333333333333305,  0},
      {0, -0.15000000000000036, 0},
    };
    const double* bs2_weights_pcurve2_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve2_cur1 = 1e-06;
    int bs2_num_knots_pcurve2_cur1 = 8;
    const double bs2_knots_pcurve2_cur1[] = {
      -1.3000000000000003, -1.3000000000000003, -1.3000000000000003, -1.3000000000000003, -0, -0, -0, -0,
    };
    double bs2_knot_tol_pcurve2_cur1 = 1e-10;
    bs2_curve bs2_pcurve2_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve2_cur1, bs2_rational_pcurve2_cur1, bs2_closed_pcurve2_cur1, bs2_periodic_pcurve2_cur1, bs2_num_ctrlpts_pcurve2_cur1, bs2_ctrlpts_pcurve2_cur1, bs2_weights_pcurve2_cur1,
                                                        bs2_ctrlpt_tol_pcurve2_cur1, bs2_num_knots_pcurve2_cur1, bs2_knots_pcurve2_cur1, bs2_knot_tol_pcurve2_cur1);
    intcurve ic_cur1(bs3_cur1, 1e-11, pln_surf1_cur1, spl_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, -1.3000000000000003, -0);
    e1 = bnd_curv1.make_edge();

    SPAposition str_root_point_cur2(0, 0.5, 0);
    SPAunit_vector str_direction_cur2(0, 1, 0);
    straight str_cur2(str_root_point_cur2, str_direction_cur2, 1);
    bounded_curve bnd_curv2(&str_cur2, -0.5, 0.5);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur1);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur1);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug43) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 22;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {-0.3410817883244348,  -0.9400336236930068,  0                   },
      {-0.3410817883244348,  -0.9400336236930068,  -0.10041638058683144},
      {-0.3463881553432441,  -0.9207886322253785,  -0.20747617429033216},
      {-0.36866066785830065, -0.8623598965622978,  -0.35092082632711863},
      {-0.37854502247186217, -0.8381681604970771,  -0.39593780086951336},
      {-0.4051777636592395,  -0.7819263268006237,  -0.4764568613829008 },
      {-0.4218944929616961,  -0.7499208650027838,  -0.5120005814592496 },
      {-0.4588754473554504,  -0.6896847263564362,  -0.5613040155195843 },
      {-0.47823715913733145, -0.6608105849603103,  -0.5797517326112426 },
      {-0.5226633474607935,  -0.6025474858705688,  -0.6043616744410626 },
      {-0.5477980794007085,  -0.573187261879329,   -0.6104650053996536 },
      {-0.5974986360937775,  -0.5211734383503279,  -0.6104650053996536 },
      {-0.6256858277317129,  -0.49472991872692185, -0.6043616744410626 },
      {-0.6818689821344129,  -0.4477009054919503,  -0.5797517326112426 },
      {-0.7098330469526865,  -0.42704653541374404, -0.5613040155195843 },
      {-0.7683256763490295,  -0.38736535986163834, -0.5120005814592496 },
      {-0.7995380702603646,  -0.36921088135664526, -0.47645686138290055},
      {-0.8545109752975973,  -0.3400488088572371,  -0.39593780086951313},
      {-0.8782283359442677,  -0.32907486863816793, -0.35092082632711874},
      {-0.9355841066732593,  -0.30416909563264016, -0.20747617429033227},
      {-0.9545679619182585,  -0.2979932987152937,  -0.10041638058683144},
      {-0.9545679619182585,  -0.2979932987152937,  0                   },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 26;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.30124914176049417,
      0.30124914176049417,
      0.4518737126407413,
      0.4518737126407413,
      0.6024982835209883,
      0.6024982835209883,
      0.710410572630435,
      0.710410572630435,
      0.8183228617398818,
      0.8183228617398818,
      0.9262351508493287,
      0.9262351508493287,
      1.0341474399587756,
      1.0341474399587756,
      1.1847720108390227,
      1.1847720108390227,
      1.3353965817192697,
      1.3353965817192697,
      1.6366457234797638,
      1.6366457234797638,
      1.6366457234797638,
      1.6366457234797638,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(-1.2956497502426934, -1.2380269224083005, -1.1168073534242673);
    SPAunit_vector c_base_normal_surf1_cur1(0, 0, 1);
    SPAvector c_base_major_surf1_cur1(1, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition sph_center_surf2_cur1(0, 0, 0);
    double sph_radius_surf2_cur1 = 1;
    sphere sph_surf2_cur1(sph_center_surf2_cur1, sph_radius_surf2_cur1);
    sph_surf2_cur1.uv_oridir = SPAunit_vector(1, 0, 0);
    sph_surf2_cur1.pole_dir = SPAunit_vector(0, 0, 1);
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.00031741862671127655, c_surf1_cur1, sph_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    INTCURVE* intcurve1 = ACIS_NEW INTCURVE(ic_cur1);
    ic_cur1 = *(intcurve*)intcurve1->trans_curve(*(SPAtransf*)nullptr, TRUE);
    bounded_curve bnd_curv1(&ic_cur1, -1.6366457234797638, -0);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 22;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.3410817883244348,  -0.9400336236930068,  0                   },
      {-0.3410817883244348,  -0.9400336236930068,  -0.10041638058683144},
      {-0.3463881553432441,  -0.9207886322253785,  -0.20747617429033216},
      {-0.36866066785830065, -0.8623598965622978,  -0.35092082632711863},
      {-0.37854502247186217, -0.8381681604970771,  -0.39593780086951336},
      {-0.4051777636592395,  -0.7819263268006237,  -0.4764568613829008 },
      {-0.4218944929616961,  -0.7499208650027838,  -0.5120005814592496 },
      {-0.4588754473554504,  -0.6896847263564362,  -0.5613040155195843 },
      {-0.47823715913733145, -0.6608105849603103,  -0.5797517326112426 },
      {-0.5226633474607935,  -0.6025474858705688,  -0.6043616744410626 },
      {-0.5477980794007085,  -0.573187261879329,   -0.6104650053996536 },
      {-0.5974986360937775,  -0.5211734383503279,  -0.6104650053996536 },
      {-0.6256858277317129,  -0.49472991872692185, -0.6043616744410626 },
      {-0.6818689821344129,  -0.4477009054919503,  -0.5797517326112426 },
      {-0.7098330469526865,  -0.42704653541374404, -0.5613040155195843 },
      {-0.7683256763490295,  -0.38736535986163834, -0.5120005814592496 },
      {-0.7995380702603646,  -0.36921088135664526, -0.47645686138290055},
      {-0.8545109752975973,  -0.3400488088572371,  -0.39593780086951313},
      {-0.8782283359442677,  -0.32907486863816793, -0.35092082632711874},
      {-0.9355841066732593,  -0.30416909563264016, -0.20747617429033227},
      {-0.9545679619182585,  -0.2979932987152937,  -0.10041638058683144},
      {-0.9545679619182585,  -0.2979932987152937,  0                   },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 26;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.30124914176049417,
      0.30124914176049417,
      0.4518737126407413,
      0.4518737126407413,
      0.6024982835209883,
      0.6024982835209883,
      0.710410572630435,
      0.710410572630435,
      0.8183228617398818,
      0.8183228617398818,
      0.9262351508493287,
      0.9262351508493287,
      1.0341474399587756,
      1.0341474399587756,
      1.1847720108390227,
      1.1847720108390227,
      1.3353965817192697,
      1.3353965817192697,
      1.6366457234797638,
      1.6366457234797638,
      1.6366457234797638,
      1.6366457234797638,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(-1.2956497502426934, -1.2380269224083005, -1.1168073534242673);
    SPAunit_vector c_base_normal_surf1_cur2(0, 0, 1);
    SPAvector c_base_major_surf1_cur2(1, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition sph_center_surf2_cur2(0, 0, 0);
    double sph_radius_surf2_cur2 = 1;
    sphere sph_surf2_cur2(sph_center_surf2_cur2, sph_radius_surf2_cur2);
    sph_surf2_cur2.uv_oridir = SPAunit_vector(1, 0, 0);
    sph_surf2_cur2.pole_dir = SPAunit_vector(0, 0, 1);
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00031741862671127655, c_surf1_cur2, sph_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0, 1.6366457234797638);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}



TEST_F(NurbsNurbsIntrTest, TestBug53) {
        EDGE *e1, *e2;
    SPAposition str_root_point_cur1(-0.9848077530122081, -0.17364817766693008, 0);
    SPAunit_vector str_direction_cur1(0.44041941610082413, 0.0776578258864433, 0.8944271909999159);
    straight str_cur1(str_root_point_cur1, str_direction_cur1, 1);
    bounded_curve bnd_curv1(&str_cur1, 0, 1.118033988749895);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 39;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.6521162689192904,   -0.11498569276940773,  0.6756475729914232},
      {-0.6453879604531642,   -0.15428467240340504,  0.675251361280394 },
      {-0.6350643876784756,   -0.19298197786276983,  0.6749444099636743},
      {-0.591823673636346,    -0.31003370495822696,  0.6745564770340559},
      {-0.5472689597937159,   -0.38261940724611027,  0.6752670913543158},
      {-0.43177446243398876,  -0.5079917149583406,   0.6776869985262209},
      {-0.36166101772240733,  -0.5592253353849064,   0.6791153471931362},
      {-0.20450970321281803,  -0.6335692142721794,   0.6802011769825481},
      {-0.11784873302630716,  -0.6554727526814056,   0.6797493960204051},
      {0.05413967573151757,   -0.6628268078440875,   0.680587298321142 },
      {0.13735365332298377,   -0.6498740513857485,   0.6822121738276501},
      {0.2936107091671911,    -0.5919466150052756,   0.6888361253532465},
      {0.36449609552035733,   -0.5483607173936655,   0.6934690227610181},
      {0.491863983196422,     -0.4338827502573149,   0.7002958780573786},
      {0.5461281605989625,    -0.3618827719411407,   0.7018342812637725},
      {0.6210297638330098,    -0.20924296529983244,  0.6994112824899813},
      {0.6438025469701647,    -0.13065721778962658,  0.696178545914755 },
      {0.6599108900329296,    0.0347390318405284,    0.689359900929483 },
      {0.6515216631555281,    0.11991155576466239,   0.6860665942621476},
      {0.6018974779720709,    0.2809908611235664,    0.6819918870544909},
      {0.5619703004079564,    0.35500849255391853,   0.6810693156757911},
      {0.45521099911872653,   0.4853258556567288,    0.6801305794952891},
      {0.38881845483817257,   0.5400183554102242,    0.6800770838369515},
      {0.23805568864954219,   0.6215895204727473,    0.6799965505822787},
      {0.15483544966934448,   0.6473549486194472,    0.6800022589413534},
      {-0.016924745195636692, 0.6654200622749489,    0.6799995828704731},
      {-0.10382455506067756,  0.6574879913650342,    0.6800000721778108},
      {-0.26963212989823004,  0.6085807954234403,    0.679999876084212 },
      {-0.3469183733339096,   0.5680817621346288,    0.6800061677059703},
      {-0.48162254747874456,  0.4595221025613172,    0.6799561441797907},
      {-0.5376636572315743,   0.392517690153944,     0.6799085180991958},
      {-0.586615056268903,    0.3033261545025552,    0.6795555532436397},
      {-0.5934634744814624,   0.2897675615284956,    0.679494729100217 },
      {-0.5998425762831712,   0.2759871066341516,    0.6794243689203966},
      {-0.6364868872237073,   0.19682623261971166,   0.6790201897134618},
      {-0.6572814596075685,   0.11113168296065057,   0.6782311924774731},
      {-0.6629157136426918,   -0.022594145825669765, 0.6766849103893381},
      {-0.6599554637975453,   -0.06919820228521434,  0.6761092017695094},
      {-0.6521162689192904,   -0.11498569276940773,  0.6756475729914232},
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 43;
    const double bs3_knots_cur2[] = {
      0.40174957040761594, 0.40174957040761594, 0.40174957040761594, 0.40174957040761594, 0.5219563869545957, 0.5219563869545957, 0.7760731567722017, 0.7760731567722017, 1.0334509648011414, 1.0334509648011414, 1.29807125573173,
      1.29807125573173,    1.550317914445492,   1.550317914445492,   1.7982270307739523,  1.7982270307739523, 2.065021089150116,  2.065021089150116,  2.3083670060308994, 2.3083670060308994, 2.5639936292975634, 2.5639936292975634,
      2.8142080114882617,  2.8142080114882617,  3.0697203690676718,  3.0697203690676718,  3.328581161698648,  3.328581161698648,  3.5878952648085756, 3.5878952648085756, 3.8472431004326726, 3.8472431004326726, 4.106913106893674,
      4.106913106893674,   4.152469549325219,   4.152469549325219,   4.152469549325219,   4.414165395182223,  4.414165395182223,  4.554219119732835,  4.554219119732835,  4.554219119732835,  4.554219119732835,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    logical bss_rationalu_surf1_cur2 = FALSE;
    int bss_degreeu_surf1_cur2 = 3;
    int bss_num_ctrlptsu_surf1_cur2 = 4;
    int bss_formu_surf1_cur2 = 0;
    int bss_poleu_surf1_cur2 = 0;
    logical bss_rationalv_surf1_cur2 = FALSE;
    int bss_degreev_surf1_cur2 = 3;
    int bss_num_ctrlptsv_surf1_cur2 = 4;
    int bss_formv_surf1_cur2 = 0;
    int bss_polev_surf1_cur2 = 0;
    const SPAposition bss_ctrlpts_surf1_cur2[] = {
      {-1.6400000178813934, -0.7111957715011026, 0.1799999910593033},
      {-1.6400000178813934, 0.2888042284988974,  1.1799999910593033},
      {-1.6400000178813934, 1.2888042284988974,  0.1799999910593033},
      {-1.6400000178813934, 2.2888042284988974,  1.1799999910593033},
      {-0.6400000178813934, -0.7111957715011026, 1.1799999910593033},
      {-0.6400000178813934, 0.2888042284988974,  0.1799999910593033},
      {-0.6400000178813934, 1.2888042284988974,  1.1799999910593033},
      {-0.6400000178813934, 2.2888042284988974,  0.1799999910593033},
      {0.3599999821186066,  -0.7111957715011026, 0.1799999910593033},
      {0.3599999821186066,  0.2888042284988974,  1.1799999910593033},
      {0.3599999821186066,  1.2888042284988974,  0.1799999910593033},
      {0.3599999821186066,  2.2888042284988974,  1.1799999910593033},
      {1.3599999821186066,  -0.7111957715011026, 1.1799999910593033},
      {1.3599999821186066,  0.2888042284988974,  0.1799999910593033},
      {1.3599999821186066,  1.2888042284988974,  1.1799999910593033},
      {1.3599999821186066,  2.2888042284988974,  0.1799999910593033},
    };
    const double* bss_weights_surf1_cur2 = nullptr;
    double bss_ctrlpt_tol_surf1_cur2 = 1e-06;
    int bss_num_knotsu_surf1_cur2 = 8;
    double bss_knotsu_surf1_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf1_cur2 = 8;
    double bss_knotsv_surf1_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf1_cur2 = 1e-10;
    bs3_surface bss_surf1_cur2 = bs3_surface_from_ctrlpts(bss_degreeu_surf1_cur2, bss_rationalu_surf1_cur2, bss_formu_surf1_cur2, bss_poleu_surf1_cur2, bss_num_ctrlptsu_surf1_cur2, bss_degreev_surf1_cur2, bss_rationalv_surf1_cur2, bss_formv_surf1_cur2,
                                                          bss_polev_surf1_cur2, bss_num_ctrlptsv_surf1_cur2, bss_ctrlpts_surf1_cur2, bss_weights_surf1_cur2, bss_ctrlpt_tol_surf1_cur2, bss_num_knotsu_surf1_cur2, bss_knotsu_surf1_cur2,
                                                          bss_num_knotsv_surf1_cur2, bss_knotsv_surf1_cur2, bss_ctrlpt_tol_surf1_cur2);
    spline spl_surf1_cur2(bss_surf1_cur2);
    int bs2_degree_pcurve1_cur2 = 3;
    logical bs2_rational_pcurve1_cur2 = 0;
    logical bs2_closed_pcurve1_cur2 = TRUE;
    logical bs2_periodic_pcurve1_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur2 = 55;
    const SPAposition bs2_ctrlpts_pcurve1_cur2[] = {
      {0.3292945829873668,  0.19873669291056442,  0},
      {0.3315374284049218,  0.18563704138833736,  0},
      {0.33497814295159795, 0.17273786376019767,  0},
      {0.33960678837208375, 0.16020822792655748,  0},
      {0.3493917278345244,  0.13372062367500334,  0},
      {0.36424330900707125, 0.10952539124521704,  0},
      {0.38336967930678717, 0.08876322703830963,  0},
      {0.4027414951331256,  0.06773462543383375,  0},
      {0.426112653617211,   0.05065675368432094,  0},
      {0.4519411486709398,  0.038438023332562916, 0},
      {0.4784964446685205,  0.025875464014624105, 0},
      {0.5073834438981868,  0.018574286089075378, 0},
      {0.5367344111802432,  0.01731926924000588,  0},
      {0.5647129286283165,  0.016122936919101986, 0},
      {0.5924509292793979,  0.020440523773065603, 0},
      {0.6187196345445968,  0.03017882619095169,  0},
      {0.6445366326471486,  0.039749672279727796, 0},
      {0.6681651044311515,  0.05427830644514102,  0},
      {0.688614221011162,   0.07265791863393618,  0},
      {0.7106210874119921,  0.09243763226387715,  0},
      {0.7287091572082771,  0.11643762683188373,  0},
      {0.7417665656671784,  0.14304692235154629,  0},
      {0.753676377500537,   0.16731756561547637,  0},
      {0.761267313771925,   0.1935128162272424,   0},
      {0.7638859686983043,  0.22040040399424257,  0},
      {0.7666367767862776,  0.24864490201896822,  0},
      {0.7638403757277643,  0.2770357446578109,   0},
      {0.7554811949382051,  0.3041695414840417,   0},
      {0.7472989984590143,  0.3307288494411039,   0},
      {0.7339899488928001,  0.35540139487194267,  0},
      {0.7163831430250756,  0.37689342371184503,  0},
      {0.6984035351491519,  0.39884051927832964,  0},
      {0.6762726972803996,  0.417071354251777,    0},
      {0.6513091503756862,  0.4305780489021762,   0},
      {0.6260184615031279,  0.44426174591060874,  0},
      {0.598278391046122,   0.4528502235096925,   0},
      {0.569676743158179,   0.4558584431764892,   0},
      {0.5410250087871842,  0.45887193076155225,  0},
      {0.5120584135067111,  0.4562279084737781,   0},
      {0.4844256240524929,  0.44807724081133177,  0},
      {0.45678924002532,    0.43992551288062726,  0},
      {0.43102716882621755, 0.4264258367930372,   0},
      {0.4085904192588929,  0.40834379299714146,  0},
      {0.3861257979864965,  0.39023928706205485,  0},
      {0.36744543845920064, 0.36790448467643133,  0},
      {0.35356372204490766, 0.3426113892361862,   0},
      {0.35112831711194037, 0.33817397475754424,  0},
      {0.34884551276431325, 0.3336544440564551,   0},
      {0.3467191471994073,  0.32906095937841806,  0},
      {0.33450427512416875, 0.30267398423263403,  0},
      {0.32757265742081154, 0.274109118584232,    0},
      {0.3263492111696622,  0.24507319450842693,  0},
      {0.32569445028226707, 0.22953382169466285,  0},
      {0.3266814812148613,  0.2139991887036588,   0},
      {0.3292945829873668,  0.19873669291056442,  0},
    };
    const double* bs2_weights_pcurve1_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur2 = 1e-06;
    int bs2_num_knots_pcurve1_cur2 = 59;
    const double bs2_knots_pcurve1_cur2[] = {
      0.40174957040761594, 0.40174957040761594, 0.40174957040761594, 0.40174957040761594, 0.5219563869545957, 0.5219563869545957, 0.5219563869545957, 0.7760731567722017, 0.7760731567722017, 0.7760731567722017, 1.0334509648011414, 1.0334509648011414,
      1.0334509648011414,  1.29807125573173,    1.29807125573173,    1.29807125573173,    1.550317914445492,  1.550317914445492,  1.550317914445492,  1.7982270307739523, 1.7982270307739523, 1.7982270307739523, 2.065021089150116,  2.065021089150116,
      2.065021089150116,   2.3083670060308994,  2.3083670060308994,  2.3083670060308994,  2.5639936292975634, 2.5639936292975634, 2.5639936292975634, 2.8142080114882617, 2.8142080114882617, 2.8142080114882617, 3.0697203690676718, 3.0697203690676718,
      3.0697203690676718,  3.328581161698648,   3.328581161698648,   3.328581161698648,   3.5878952648085756, 3.5878952648085756, 3.5878952648085756, 3.8472431004326726, 3.8472431004326726, 3.8472431004326726, 4.106913106893674,  4.106913106893674,
      4.106913106893674,   4.152469549325219,   4.152469549325219,   4.152469549325219,   4.414165395182223,  4.414165395182223,  4.414165395182223,  4.554219119732835,  4.554219119732835,  4.554219119732835,  4.554219119732835,
    };
    double bs2_knot_tol_pcurve1_cur2 = 1e-10;
    bs2_curve bs2_pcurve1_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur2, bs2_rational_pcurve1_cur2, bs2_closed_pcurve1_cur2, bs2_periodic_pcurve1_cur2, bs2_num_ctrlpts_pcurve1_cur2, bs2_ctrlpts_pcurve1_cur2, bs2_weights_pcurve1_cur2,
                                                        bs2_ctrlpt_tol_pcurve1_cur2, bs2_num_knots_pcurve1_cur2, bs2_knots_pcurve1_cur2, bs2_knot_tol_pcurve1_cur2);
    SPAposition c_base_center_surf2_cur2(0, 0, 0);
    SPAunit_vector c_base_normal_surf2_cur2(0, 0, 1);
    SPAvector c_base_major_surf2_cur2(0, 1, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, -0.447213595499958, 0.894427190999916);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 8.363846649065175e-05, spl_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 3.397890778763782, 4.554219119732835);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur2, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur2, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug54) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 49;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {2.152832687852806,  0.9988240662307368, 0.3326873808372892    },
      {2.1472470559911216, 0.9897968037205497, 0.3426346291299886    },
      {2.1411343128368103, 0.9807557744002062, 0.3522999215476715    },
      {2.1081485004151514, 0.9357778782195337, 0.398755596026928     },
      {2.0752445632329914, 0.9017765114272271, 0.4284233634153183    },
      {2.0067108920139303, 0.8465817108809446, 0.4692955305255657    },
      {1.9720063202949338, 0.8243347203056229, 0.4824978221572066    },
      {1.9150081040584848, 0.7985185134702295, 0.4948977583180825    },
      {1.8935771421986187, 0.7908556516361479, 0.4977962667953474    },
      {1.8506442872098976, 0.7806144875682421, 0.5003655831736842    },
      {1.8296445527431948, 0.7777852929646425, 0.500247693402842     },
      {1.7782589224428262, 0.7770454706409047, 0.49723813093576075   },
      {1.7489932976858646, 0.7816642954069133, 0.4933324860210578    },
      {1.6833673886547422, 0.8036667876456409, 0.4823687262435091    },
      {1.6494085715044804, 0.8239542215216829, 0.47512668873993713   },
      {1.5776691277632773, 0.8830209920476435, 0.46190230058576287   },
      {1.5390617434082483, 0.9284861544702452, 0.45664889129837494   },
      {1.4767648701312934, 1.0339042615465335, 0.4590253178083298    },
      {1.454435602113667,  1.0890544795237116, 0.46582441112958917   },
      {1.43220575270862,   1.194800654039255,  0.48188830161827373   },
      {1.4296540604688166, 1.24361574153288,   0.49020804820848124   },
      {1.4412605489913897, 1.3476111412639595, 0.5009649806289802    },
      {1.456630571506755,  1.3996555575856795, 0.5022247662158817    },
      {1.5002917835752063, 1.5006837562131412, 0.48765592279634185   },
      {1.5274867315702143, 1.5472306021645983, 0.47195023283229054   },
      {1.5847691425844694, 1.6314546902287654, 0.42177559970494366   },
      {1.614328146754295,  1.6682340436530896, 0.3873048453343994    },
      {1.6703921836864695, 1.7249312345705201, 0.3039607283120493    },
      {1.695665607285525,  1.7434097433293114, 0.25714447341531266   },
      {1.7384483102233799, 1.7561015573502372, 0.17258955652997143   },
      {1.7565990877969775, 1.7548251361300595, 0.1349038771669263    },
      {1.7952932025128494, 1.7364250733395294, 0.06192307295538446   },
      {1.815062898771891,  1.7194707420702313, 0.02839547772891471   },
      {1.8368646127532695, 1.6958562422607568, -2.220446049250313e-16},
      {1.8498343410063505, 1.6818080969808533, -0.01689232461608281  },
      {1.8632011859892759, 1.6657619906895378, -0.031537519097527666 },
      {1.8899761859943394, 1.6321288556143771, -0.05509610225777073  },
      {1.9032135542662076, 1.6148697036159818, -0.06429791163261023  },
      {1.9469373637658056, 1.5572694185465172, -0.08699896297482113  },
      {1.9786441822622496, 1.5149717296033722, -0.09208333347529718  },
      {2.044621528305065,  1.4278866128944254, -0.08227256975905695  },
      {2.078265844678403,  1.3839142407263771, -0.06575221297779488  },
      {2.138107823884768,  1.297858043844244,  -0.012051986821486116 },
      {2.1626910034884665, 1.2573816296455118, 0.025050607462077212  },
      {2.194517324648178,  1.1748069295391341, 0.11557634914264564   },
      {2.1992672188633886, 1.1347790359119727, 0.16766349546596104   },
      {2.1856567131024263, 1.0621645270684543, 0.2590320283876799    },
      {2.17250914425887,   1.0306243247594529, 0.29764629645537183   },
      {2.152832687852806,  0.9988240662307368, 0.3326873808372892    },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 53;
    const double bs3_knots_cur1[] = {
      -2.1443069030984354,
      -2.1443069030984354,
      -2.1443069030984354,
      -2.1443069030984354,
      -2.1025909088488044,
      -2.1025909088488044,
      -1.936796409220939,
      -1.936796409220939,
      -1.79329797549456,
      -1.79329797549456,
      -1.7131461990188281,
      -1.7131461990188281,
      -1.6391376958984314,
      -1.6391376958984314,
      -1.534716414966826,
      -1.534716414966826,
      -1.397855014197452,
      -1.397855014197452,
      -1.214786826596091,
      -1.214786826596091,
      -1.0434587321666573,
      -1.0434587321666573,
      -0.8990326492336005,
      -0.8990326492336005,
      -0.740737075282355,
      -0.740737075282355,
      -0.5812341739598664,
      -0.5812341739598664,
      -0.418305200914895,
      -0.418305200914895,
      -0.25535772228760123,
      -0.25535772228760123,
      -0.1286598709896648,
      -0.1286598709896648,
      -0,
      -0,
      -0,
      0.07653909987249907,
      0.07653909987249907,
      0.14702326503279117,
      0.14702326503279117,
      0.30241045222065344,
      0.30241045222065344,
      0.47097772202894683,
      0.47097772202894683,
      0.647549509499298,
      0.647549509499298,
      0.8389010409709452,
      0.8389010409709452,
      0.9858536083105682,
      0.9858536083105682,
      0.9858536083105682,
      0.9858536083105682,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(2.241794400370852, 1.6992793162695259, 0.2946314167980957);
    SPAunit_vector c_base_normal_surf1_cur1(0.5039180420229519, 0.6169791581624748, -0.6044860009271334);
    SPAvector c_base_major_surf1_cur1(0.30848957908123725, 0.11633024998614426, 0.3759008546630904);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition tor_center_surf2_cur1(0, 0, 0);
    SPAunit_vector tor_normal_surf2_cur1(-1.1102230246251565e-16, -2.7755575615628914e-17, 0.9999999999999996);
    torus tor_surf2_cur1(tor_center_surf2_cur1, tor_normal_surf2_cur1, 2, 0.5);
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 9.726067055673381e-05, c_surf1_cur1, tor_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, -0.5754789119655621, 0.9858536083105682);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 8;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {2.2424341057817783, 0.8810489885417575, 0.287172683792824  },
      {2.138198431573508,  1.027085752573118,  0.3493335987176287 },
      {2.003367803572367,  1.1776889668178203, 0.3906504501184776 },
      {1.7104660594874606, 1.4645667558551785, 0.43928539509043096},
      {1.5530687395277754, 1.6013452311164929, 0.4476795005286812 },
      {1.2589388833942592, 1.8415759410884864, 0.4476795005286811 },
      {1.0934830899876258, 1.9684879107898625, 0.4392853950904312 },
      {0.9236870613032031, 2.083343833692143,  0.4149679226044544 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 12;
    const double bs3_knots_cur2[] = {
      2.6958879298104304, 2.6958879298104304, 2.6958879298104304, 2.6958879298104304, 3.265538808977868, 3.265538808977868, 3.835189688145306, 3.835189688145306, 4.4048405673127435, 4.4048405673127435, 4.4048405673127435, 4.4048405673127435,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition tor_center_surf1_cur2(0, 0, 0);
    SPAunit_vector tor_normal_surf1_cur2(-1.1102230246251565e-16, -2.7755575615628914e-17, 0.9999999999999996);
    torus tor_surf1_cur2(tor_center_surf1_cur2, tor_normal_surf1_cur2, 2, -0.5);
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition pln_root_surf2_cur2(1.9898353793593762, 1.390789737188289, 0.5968744172616618);
    SPAunit_vector pln_dir_surf2_cur2(-0.5039180420229519, -0.6169791581624748, 0.6044860009271334);
    plane pln_surf2_cur2(pln_root_surf2_cur2, pln_dir_surf2_cur2);
    pln_surf2_cur2.u_deriv = SPAvector(-0.6169791581624745, -0.23266049997228852, -0.7518017093261808);
    pln_surf2_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.0003255588404838168, tor_surf1_cur2, pln_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 2.848002628560742, 3.641299883398255);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug55) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 39;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {2.323647307155281,  2.083607838438223,  0.4951246067978213 },
      {2.29415782682497,   2.0484310980645875, 0.4965298630548783 },
      {2.2613741133758367, 2.0160154340625764, 0.4974293426578864 },
      {2.159411098579702,  1.9320876438816148, 0.4992504417428075 },
      {2.0831092415990975, 1.8887063599361742, 0.4995517455051256 },
      {1.9346930384852603, 1.8386655093730697, 0.49989250594396273},
      {1.864231272069923,  1.8269468807950315, 0.499932569391678  },
      {1.7347296075336427, 1.830583066743554,  0.49998371281002074},
      {1.6763401444106485, 1.8420174346943963, 0.49999171460514025},
      {1.5714058754849014, 1.8849190493023942, 0.5000002765287109 },
      {1.5256254582866366, 1.9143092848397723, 0.4999999228363924 },
      {1.4499139617741106, 1.9873177833435542, 0.5000000914516676 },
      {1.4204361677449737, 2.0288539744108625, 0.5000010263632635 },
      {1.373134234869806,  2.129248541939261,  0.5000176691866012 },
      {1.3593157977141141, 2.1880657564903965, 0.5000378971213923 },
      {1.3519993336371248, 2.322088196837995,  0.5000757050207693 },
      {1.364132830792627,  2.396360085490457,  0.5000789755845552 },
      {1.4166575885416277, 2.547135114911166,  0.5000270849375312 },
      {1.4609943970157344, 2.621904803616875,  0.5000030914439003 },
      {1.5770968473734404, 2.7572180985932886, 0.49999593596728165},
      {1.651031748199838,  2.8160474323410316, 0.500201369750812  },
      {1.7977152590578556, 2.893028224965179,  0.4973467728934429 },
      {1.868505384744103,  2.917298400789487,  0.49468095047264865},
      {2.007517097689297,  2.9372607565835853, 0.4838716122611776 },
      {2.074359062340301,  2.9348779349028766, 0.4760857983227777 },
      {2.1940472539950604, 2.9039790169266357, 0.4598766146483304 },
      {2.2456018241147007, 2.879593074023541,  0.4521790864290688 },
      {2.337504453036003,  2.8119098341029494, 0.4417033560370194 },
      {2.3764067527353325, 2.7696434632782405, 0.43929199226201987},
      {2.4066154978422607, 2.7211863651031836, 0.44042861381234316},
      {2.4301394019124527, 2.68345225450193,   0.44131371434264577},
      {2.4479197386920974, 2.6426774331108853, 0.4442491850896571 },
      {2.476323422350896,  2.539364501725026,  0.4542129849012365 },
      {2.4810445823608154, 2.4741026369186896, 0.46241894246424925},
      {2.4617781404924686, 2.3286591916472625, 0.4786513773517795 },
      {2.43447670384338,   2.2541300324386424, 0.48546031621578417},
      {2.3746777187750436, 2.150030256648316,  0.49213565679364857},
      {2.3505289970091043, 2.1156738570387796, 0.49384361905425217},
      {2.323647307155281,  2.083607838438223,  0.4951246067978213 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 43;
    const double bs3_knots_cur1[] = {
      -2.6872415942409638,
      -2.6872415942409638,
      -2.6872415942409638,
      -2.6872415942409638,
      -2.5607134509716722,
      -2.5607134509716722,
      -2.3213689223171645,
      -2.3213689223171645,
      -2.1238710575407582,
      -2.1238710575407582,
      -1.957106630720514,
      -1.957106630720514,
      -1.8027694668766345,
      -1.8027694668766345,
      -1.6572913665265745,
      -1.6572913665265745,
      -1.4847816901575663,
      -1.4847816901575663,
      -1.2712323485286416,
      -1.2712323485286416,
      -1.0243708683790396,
      -1.0243708683790396,
      -0.7557910855625873,
      -0.7557910855625873,
      -0.5407370885972579,
      -0.5407370885972579,
      -0.3422405308538938,
      -0.3422405308538938,
      -0.17134046509006737,
      -0.17134046509006737,
      -0,
      -0,
      -0,
      0.13342482946093437,
      0.13342482946093437,
      0.32275580352414357,
      0.32275580352414357,
      0.5392730939474233,
      0.5392730939474233,
      0.6546122001997996,
      0.6546122001997996,
      0.6546122001997996,
      0.6546122001997996,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(2.2120712628979056, 2.6564876963478934, 0.8943231222625845);
    SPAunit_vector c_base_normal_surf1_cur1(0.3692764666688846, 0.34279479622902365, 0.8637862113062732);
    SPAvector c_base_major_surf1_cur1(0.08569869905725587, 0.20342322502971774, -0.11736577226092185);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, -0.4472135954999579, 0.8944271909999159);
    c_surf1_cur1.u_param_scale = 0.25;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    logical bss_rationalu_surf2_cur1 = FALSE;
    int bss_degreeu_surf2_cur1 = 3;
    int bss_num_ctrlptsu_surf2_cur1 = 4;
    int bss_formu_surf2_cur1 = 0;
    int bss_poleu_surf2_cur1 = 0;
    logical bss_rationalv_surf2_cur1 = FALSE;
    int bss_degreev_surf2_cur1 = 3;
    int bss_num_ctrlptsv_surf2_cur1 = 4;
    int bss_formv_surf2_cur1 = 0;
    int bss_polev_surf2_cur1 = 0;
    const SPAposition bss_ctrlpts_surf2_cur1[] = {
      {0,                      0,                  0                      },
      {-4.440892098500626e-16, 1,                  0.9999999999999993     },
      {-4.440892098500626e-16, 1.9999999999999991, -5.551115123125783e-17 },
      {-4.440892098500626e-16, 2.9999999999999982, 0.9999999999999994     },
      {0.9999999999999993,     0,                  0.9999999999999993     },
      {0.9999999999999991,     0.9999999999999996, -1.6653345369377348e-16},
      {0.9999999999999987,     1.999999999999999,  0.9999999999999994     },
      {0.9999999999999987,     2.9999999999999982, -1.1102230246251565e-16},
      {1.9999999999999987,     0,                  5.551115123125783e-17  },
      {1.9999999999999984,     0.9999999999999996, 0.9999999999999993     },
      {1.9999999999999982,     1.9999999999999987, -1.6653345369377348e-16},
      {1.999999999999998,      2.9999999999999982, 0.9999999999999994     },
      {2.999999999999998,      0,                  0.9999999999999994     },
      {2.9999999999999973,     0.9999999999999991, -1.6653345369377348e-16},
      {2.9999999999999973,     1.9999999999999982, 0.999999999999999      },
      {2.9999999999999973,     2.9999999999999982, -1.6653345369377348e-16},
    };
    const double* bss_weights_surf2_cur1 = nullptr;
    double bss_ctrlpt_tol_surf2_cur1 = 1e-06;
    int bss_num_knotsu_surf2_cur1 = 8;
    double bss_knotsu_surf2_cur1[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf2_cur1 = 8;
    double bss_knotsv_surf2_cur1[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf2_cur1 = 1e-10;
    bs3_surface bss_surf2_cur1 = bs3_surface_from_ctrlpts(bss_degreeu_surf2_cur1, bss_rationalu_surf2_cur1, bss_formu_surf2_cur1, bss_poleu_surf2_cur1, bss_num_ctrlptsu_surf2_cur1, bss_degreev_surf2_cur1, bss_rationalv_surf2_cur1, bss_formv_surf2_cur1,
                                                          bss_polev_surf2_cur1, bss_num_ctrlptsv_surf2_cur1, bss_ctrlpts_surf2_cur1, bss_weights_surf2_cur1, bss_ctrlpt_tol_surf2_cur1, bss_num_knotsu_surf2_cur1, bss_knotsu_surf2_cur1,
                                                          bss_num_knotsv_surf2_cur1, bss_knotsv_surf2_cur1, bss_ctrlpt_tol_surf2_cur1);
    spline spl_surf2_cur1(bss_surf2_cur1);
    int bs2_degree_pcurve2_cur1 = 3;
    logical bs2_rational_pcurve2_cur1 = 0;
    logical bs2_closed_pcurve2_cur1 = TRUE;
    logical bs2_periodic_pcurve2_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve2_cur1 = 55;
    const SPAposition bs2_ctrlpts_pcurve2_cur1[] = {
      {0.7745491023850924,  0.6945359461460721, 0},
      {0.7647189378022579,  0.6828106766452666, 0},
      {0.7537901657296674,  0.6720061287978903, 0},
      {0.7420363804289786,  0.6623313172833977, 0},
      {0.7198025585296696,  0.6440301461611035, 0},
      {0.6943686476649941,  0.629569684328683,  0},
      {0.6672631001060815,  0.6204305804052458, 0},
      {0.644896648712459,   0.6128893446770042, 0},
      {0.6214094217106826,  0.6089831119074816, 0},
      {0.598004789487191,   0.6096402543625639, 0},
      {0.5782422463219372,  0.6101951362342495, 0},
      {0.5587791161368869,  0.6140065724692252, 0},
      {0.540613237489391,   0.6214335493294232, 0},
      {0.5238010777102033,  0.6283070688586969, 0},
      {0.5085409646857115,  0.6381037927769151, 0},
      {0.495549549434857,   0.6506314016809055, 0},
      {0.48330385070305376, 0.6624399168815902, 0},
      {0.47347794396159787, 0.6762852938187704, 0},
      {0.4662644874386711,  0.6915953086550677, 0},
      {0.4577106841701539,  0.7097501078877981, 0},
      {0.4531045636149786,  0.7293558255275896, 0},
      {0.4520148031977755,  0.7493183580629037, 0},
      {0.4506657912204462,  0.7740299323345031, 0},
      {0.4547103202059593,  0.7987872041135041, 0},
      {0.4628310912120763,  0.8220981761891369, 0},
      {0.47221864321871976, 0.8490454897534009, 0},
      {0.48699762063917945, 0.8739686856344588, 0},
      {0.5055327343417735,  0.8955706216967708, 0},
      {0.5256985245237984,  0.9190730461840364, 0},
      {0.5503435374598463,  0.9386827865495493, 0},
      {0.5774965125472147,  0.952932848240288,  0},
      {0.5992381185638866,  0.9643429874974568, 0},
      {0.6228348600579969,  0.9724330192191585, 0},
      {0.6469311159933687,  0.9758932615400117, 0},
      {0.6691721527802623,  0.9790870928537257, 0},
      {0.6914528316456826,  0.9782927993809487, 0},
      {0.7128911480783426,  0.972758229554847,  0},
      {0.73134894769895,    0.9679931174641971, 0},
      {0.7485338307137984,  0.9598644483511812, 0},
      {0.7638312529023981,  0.9485984017628627, 0},
      {0.7791680956400477,  0.9373033232411465, 0},
      {0.7921355569926654,  0.923214510008885,  0},
      {0.802205165947421,   0.9070621217010618, 0},
      {0.8100463792022785,  0.8944841567622022, 0},
      {0.8159730739142282,  0.8808926183864256, 0},
      {0.8198869522296739,  0.8666564185572779, 0},
      {0.8254407790310426,  0.846455129250776,  0},
      {0.8270143983840813,  0.8247012564883289, 0},
      {0.8240183125106021,  0.8020845614291101, 0},
      {0.8205920142072689,  0.7762203014643524, 0},
      {0.8114913888704852,  0.751377367962742,  0},
      {0.7984860975661305,  0.7287377798668109, 0},
      {0.7915581581269124,  0.7166776351467202, 0},
      {0.7835100788039187,  0.7052242499699071, 0},
      {0.7745491023850924,  0.6945359461460721, 0},
    };
    const double* bs2_weights_pcurve2_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve2_cur1 = 1e-06;
    int bs2_num_knots_pcurve2_cur1 = 59;
    const double bs2_knots_pcurve2_cur1[] = {
      -2.6872415942409638,
      -2.6872415942409638,
      -2.6872415942409638,
      -2.6872415942409638,
      -2.5607134509716722,
      -2.5607134509716722,
      -2.5607134509716722,
      -2.3213689223171645,
      -2.3213689223171645,
      -2.3213689223171645,
      -2.1238710575407582,
      -2.1238710575407582,
      -2.1238710575407582,
      -1.957106630720514,
      -1.957106630720514,
      -1.957106630720514,
      -1.8027694668766345,
      -1.8027694668766345,
      -1.8027694668766345,
      -1.6572913665265745,
      -1.6572913665265745,
      -1.6572913665265745,
      -1.4847816901575663,
      -1.4847816901575663,
      -1.4847816901575663,
      -1.2712323485286416,
      -1.2712323485286416,
      -1.2712323485286416,
      -1.0243708683790396,
      -1.0243708683790396,
      -1.0243708683790396,
      -0.7557910855625873,
      -0.7557910855625873,
      -0.7557910855625873,
      -0.5407370885972579,
      -0.5407370885972579,
      -0.5407370885972579,
      -0.3422405308538938,
      -0.3422405308538938,
      -0.3422405308538938,
      -0.17134046509006737,
      -0.17134046509006737,
      -0.17134046509006737,
      -0,
      -0,
      -0,
      0.13342482946093437,
      0.13342482946093437,
      0.13342482946093437,
      0.32275580352414357,
      0.32275580352414357,
      0.32275580352414357,
      0.5392730939474233,
      0.5392730939474233,
      0.5392730939474233,
      0.6546122001997996,
      0.6546122001997996,
      0.6546122001997996,
      0.6546122001997996,
    };
    double bs2_knot_tol_pcurve2_cur1 = 1e-10;
    bs2_curve bs2_pcurve2_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve2_cur1, bs2_rational_pcurve2_cur1, bs2_closed_pcurve2_cur1, bs2_periodic_pcurve2_cur1, bs2_num_ctrlpts_pcurve2_cur1, bs2_ctrlpts_pcurve2_cur1, bs2_weights_pcurve2_cur1,
                                                        bs2_ctrlpt_tol_pcurve2_cur1, bs2_num_knots_pcurve2_cur1, bs2_knots_pcurve2_cur1, bs2_knot_tol_pcurve2_cur1);
    intcurve ic_cur1(bs3_cur1, 7.387068677875177e-05, c_surf1_cur1, spl_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, -0.8567095450612241, 0.6546122001997996);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 8;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {2.6808803293723575, 1.6876970129163693, 0.49952201727756845},
      {2.5870057166072216, 1.7905157491574095, 0.49885050571734463},
      {2.5011787210341727, 1.8865961614275542, 0.4974126780934873 },
      {2.1398056525225413, 2.2884421845940723, 0.49242978338967747},
      {1.9624023353120768, 2.469603979665622,  0.4963769979714288 },
      {1.6295667640961302, 2.8184098234400423, 0.5002431346803595 },
      {1.5407186110899713, 2.914847843866425,  0.4999549620453216 },
      {1.461547861441574,  2.999999999999998,  0.500008422823941  },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 12;
    const double bs3_knots_cur2[] = {
      -0.9872416889602176, -0.9872416889602176, -0.9872416889602176, -0.9872416889602176, -0.8395119093466039, -0.8395119093466039, -0.34881241573267413, -0.34881241573267413, -0, -0, -0, -0,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition pln_root_surf1_cur2(2.027433029563463, 2.4850902982333816, 0.4624300166094482);
    SPAunit_vector pln_dir_surf1_cur2(-0.3692764666688846, -0.34279479622902365, -0.8637862113062732);
    plane pln_surf1_cur2(pln_root_surf1_cur2, pln_dir_surf1_cur2);
    pln_surf1_cur2.u_deriv = SPAvector(-0.3427947962290235, -0.813692900118871, 0.4694630890436874);
    pln_surf1_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    logical bss_rationalu_surf2_cur2 = FALSE;
    int bss_degreeu_surf2_cur2 = 3;
    int bss_num_ctrlptsu_surf2_cur2 = 4;
    int bss_formu_surf2_cur2 = 0;
    int bss_poleu_surf2_cur2 = 0;
    logical bss_rationalv_surf2_cur2 = FALSE;
    int bss_degreev_surf2_cur2 = 3;
    int bss_num_ctrlptsv_surf2_cur2 = 4;
    int bss_formv_surf2_cur2 = 0;
    int bss_polev_surf2_cur2 = 0;
    const SPAposition bss_ctrlpts_surf2_cur2[] = {
      {0,                      0,                  0                      },
      {-4.440892098500626e-16, 1,                  0.9999999999999993     },
      {-4.440892098500626e-16, 1.9999999999999991, -5.551115123125783e-17 },
      {-4.440892098500626e-16, 2.9999999999999982, 0.9999999999999994     },
      {0.9999999999999993,     0,                  0.9999999999999993     },
      {0.9999999999999991,     0.9999999999999996, -1.6653345369377348e-16},
      {0.9999999999999987,     1.999999999999999,  0.9999999999999994     },
      {0.9999999999999987,     2.9999999999999982, -1.1102230246251565e-16},
      {1.9999999999999987,     0,                  5.551115123125783e-17  },
      {1.9999999999999984,     0.9999999999999996, 0.9999999999999993     },
      {1.9999999999999982,     1.9999999999999987, -1.6653345369377348e-16},
      {1.999999999999998,      2.9999999999999982, 0.9999999999999994     },
      {2.999999999999998,      0,                  0.9999999999999994     },
      {2.9999999999999973,     0.9999999999999991, -1.6653345369377348e-16},
      {2.9999999999999973,     1.9999999999999982, 0.999999999999999      },
      {2.9999999999999973,     2.9999999999999982, -1.6653345369377348e-16},
    };
    const double* bss_weights_surf2_cur2 = nullptr;
    double bss_ctrlpt_tol_surf2_cur2 = 1e-06;
    int bss_num_knotsu_surf2_cur2 = 8;
    double bss_knotsu_surf2_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf2_cur2 = 8;
    double bss_knotsv_surf2_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf2_cur2 = 1e-10;
    bs3_surface bss_surf2_cur2 = bs3_surface_from_ctrlpts(bss_degreeu_surf2_cur2, bss_rationalu_surf2_cur2, bss_formu_surf2_cur2, bss_poleu_surf2_cur2, bss_num_ctrlptsu_surf2_cur2, bss_degreev_surf2_cur2, bss_rationalv_surf2_cur2, bss_formv_surf2_cur2,
                                                          bss_polev_surf2_cur2, bss_num_ctrlptsv_surf2_cur2, bss_ctrlpts_surf2_cur2, bss_weights_surf2_cur2, bss_ctrlpt_tol_surf2_cur2, bss_num_knotsu_surf2_cur2, bss_knotsu_surf2_cur2,
                                                          bss_num_knotsv_surf2_cur2, bss_knotsv_surf2_cur2, bss_ctrlpt_tol_surf2_cur2);
    spline spl_surf2_cur2(bss_surf2_cur2);
    int bs2_degree_pcurve2_cur2 = 3;
    logical bs2_rational_pcurve2_cur2 = 0;
    logical bs2_closed_pcurve2_cur2 = FALSE;
    logical bs2_periodic_pcurve2_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve2_cur2 = 10;
    const SPAposition bs2_ctrlpts_pcurve2_cur2[] = {
      {0.8936267764574534,  0.5625656709721236, 0},
      {0.8623352388690747,  0.5968385830524703, 0},
      {0.833726240344725,   0.6288653871425185, 0},
      {0.8058528506531617,  0.6598605325357753, 0},
      {0.713268550840848,   0.7628140615313581, 0},
      {0.6541341117706929,  0.823201326555208,  0},
      {0.5892860159370544,  0.8911609941525787, 0},
      {0.5431889213653773,  0.9394699411466815, 0},
      {0.5135728703633243,  0.9716159479554757, 0},
      {0.48718262048052524, 1,                  0},
    };
    const double* bs2_weights_pcurve2_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve2_cur2 = 1e-06;
    int bs2_num_knots_pcurve2_cur2 = 14;
    const double bs2_knots_pcurve2_cur2[] = {
      -0.9872416889602176, -0.9872416889602176, -0.9872416889602176, -0.9872416889602176, -0.8395119093466039, -0.8395119093466039, -0.8395119093466039, -0.34881241573267413, -0.34881241573267413, -0.34881241573267413, -0, -0, -0, -0,
    };
    double bs2_knot_tol_pcurve2_cur2 = 1e-10;
    bs2_curve bs2_pcurve2_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve2_cur2, bs2_rational_pcurve2_cur2, bs2_closed_pcurve2_cur2, bs2_periodic_pcurve2_cur2, bs2_num_ctrlpts_pcurve2_cur2, bs2_ctrlpts_pcurve2_cur2, bs2_weights_pcurve2_cur2,
                                                        bs2_ctrlpt_tol_pcurve2_cur2, bs2_num_knots_pcurve2_cur2, bs2_knots_pcurve2_cur2, bs2_knot_tol_pcurve2_cur2);
    intcurve ic_cur2(bs3_cur2, 0.0006580082079820754, pln_surf1_cur2, spl_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, -0.7818004240074343, -0.23212811840105152);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug56) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 2;
    logical bs3_rational_cur1 = 1;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 3;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.9462393799965578, 0.32346720968860077, 0                 },
      {0.5701421745694584, 0.3564071524214275,  0.6904459902373737},
      {0.3526395766656378, 0.3544648487072865,  0.9999999999999997},
    };
    const double bs3_weights_cur1[] = {
      1,
      1.051655353000835,
      1,
    };
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 6;
    const double bs3_knots_cur1[] = {
      0, 0, 0, 1.1637838487115073, 1.1637838487115073, 1.1637838487115073,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    intcurve ic_cur1(ACIS_NEW exact_int_cur(bs3_cur1));
    bounded_curve bnd_curv1(&ic_cur1, 0.1363031219651307, 0.9196380204047937);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 2;
    logical bs3_rational_cur2 = 1;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 3;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.7716697067526848, 0.6360234773027049,   4.85722573273506e-17 },
      {0.8302740446922965, 0.3238219841402681,   0.30668857405594907  },
      {0.9985201616742343, 0.054382779719873264, 8.326672684688674e-17},
    };
    const double bs3_weights_cur2[] = {
      1,
      1.1220979660317725,
      1,
    };
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 6;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 0.7062805248595092, 0.7062805248595092, 0.7062805248595092,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));
    bounded_curve bnd_curv2(&ic_cur2, 0, 0.35690549943837596);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug57) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 2;
    logical bs3_rational_cur1 = 1;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 3;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {-0.5353527152394588,  0.8446285990219246, 0                 },
      {-0.16848941080367588, 0.6234525585403337, 0.766425750721198 },
      {0.018847155082394984, 0.5087156835551989, 0.9818706134292499},
    };
    const double bs3_weights_cur1[] = {
      1,
      1.1047802005153702,
      1,
    };
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 6;
    const double bs3_knots_cur1[] = {
      0, 0, 0, 1.1785489245893257, 1.1785489245893257, 1.1785489245893257,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    intcurve ic_cur1(ACIS_NEW exact_int_cur(bs3_cur1));
    bounded_curve bnd_curv1(&ic_cur1, 0, 1.0688764407123885);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 2;
    logical bs3_rational_cur2 = 1;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 3;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.03350847022598802,   0.9994384335331087,  -5.551115123125783e-17},
      {-0.004833110118125594, 0.6668336439451429,  0.6674055551896171    },
      {-0.023995874144979723, 0.49942386609374034, 1.0000000000000004    },
    };
    const double bs3_weights_cur2[] = {
      1,
      1.060366728200753,
      1,
    };
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 6;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 1.1195188203148814, 1.1195188203148814, 1.1195188203148814,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));
    bounded_curve bnd_curv2(&ic_cur2, 1.0176501488755116, 1.092333281060976);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug58) {
        EDGE *e1, *e2;
    SPAposition ell_center_cur1(1.569582197531906, 1.429180892870365, -0.4938154520113551);
    SPAunit_vector ell_normal_cur1(-0.08697774691488246, 0.08852388391204367, 0.9922693150141939);
    SPAvector ell_major_axis_cur1(0.9959800438073808, -0.013684820589789558, 0.08852388391204367);
    double ell_ratio_cur1 = 1;
    ellipse ell_cur1(ell_center_cur1, ell_normal_cur1, ell_major_axis_cur1, ell_ratio_cur1, 0);
    bounded_curve bnd_curv1(&ell_cur1, 7.546047120499111e-17, 6.283185307179586);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 43;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {1.6415823517676484, 0.4363002669233016,  -0.39892582977058527 },
      {1.6786972470507247, 0.4222309338242718,  -0.42329813720887094 },
      {1.7160494662292918, 0.41289466555621535, -0.4429822741433651  },
      {1.7967733052944492, 0.4026396975965092,  -0.4762572691807255  },
      {1.8416266017005196, 0.4032541571831534,  -0.4888378057270548  },
      {1.930683157792171,  0.4189915311463537,  -0.501438515839378   },
      {1.9725760480085657, 0.43339463176544424, -0.5014307467378132  },
      {2.05736405037053,   0.4771104707356928,  -0.489913807779531   },
      {2.0970834939618714, 0.5076134440880016,  -0.47662282792754    },
      {2.174362376916918,  0.5862781067359301,  -0.43588819641967613 },
      {2.209458766335152,  0.639052332462308,   -0.40428998855053455 },
      {2.2694998807938176, 0.7750594970887305,  -0.3132258204757431  },
      {2.2834099831412313, 0.8565887958092436,  -0.2515788186634545  },
      {2.2799899611118306, 0.9984209621136704,  -0.1259439886244369  },
      {2.265160501246991,  1.0591602203699897,  -0.0631027555402231  },
      {2.2418583141737796, 1.1063775572425059,  0                    },
      {2.2216324391351763, 1.1473613478300035,  0.054772045393773894 },
      {2.1937564485430894, 1.1807727126996341,  0.11330178982071426  },
      {2.132715367278657,  1.2114948075748204,  0.217586003597385    },
      {2.104079906157552,  1.2151101402910385,  0.2606015165230994   },
      {2.0343613163689325, 1.2029712092648863,  0.34855330473419     },
      {1.9949946414854223, 1.184541732016421,   0.38824175448670883  },
      {1.907663438824672,  1.1377418424408272,  0.45257512549357404  },
      {1.857313046132278,  1.107659699315923,   0.4772710583784956   },
      {1.744520737789692,  1.0489816041567814,  0.5029043971448152   },
      {1.6863377481982829, 1.0227946451928611,  0.503071645677224    },
      {1.5558447071453845, 0.9753815482502958,  0.47851578286029695  },
      {1.4918614022691858, 0.9593783660147197,  0.4497743523567237   },
      {1.4017962028581,    0.9372504927201222,  0.39190259036882824  },
      {1.3680171548447824, 0.9291101654909842,  0.3629869423909745   },
      {1.3220317276803544, 0.9118273481502422,  0.3093327415419943   },
      {1.3060325808987994, 0.9032665672058093,  0.28484555324565486  },
      {1.2849152688764018, 0.8825367530383859,  0.2366919560197296   },
      {1.2790971747705542, 0.8716042021103156,  0.21469464024305962  },
      {1.271885545832966,  0.8395501843528228,  0.15748614780050174  },
      {1.2737327492196109, 0.8104919010989075,  0.11243280936354316  },
      {1.3156912240983782, 0.7126736129876634,  -0.020489455156124714},
      {1.3580661882603815, 0.6497196950912951,  -0.10001713136250551 },
      {1.4569490384546775, 0.5458569371563031,  -0.23685040578738942 },
      {1.5120704494512327, 0.50086988156157,    -0.29806041315253007 },
      {1.597065680555165,  0.4549182719546626,  -0.3679425767236818  },
      {1.6192806990011408, 0.4447542684511995,  -0.38428096189579797 },
      {1.6415823517676484, 0.4363002669233016,  -0.39892582977058527 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 47;
    const double bs3_knots_cur2[] = {
      -1.2241389492562584,
      -1.2241389492562584,
      -1.2241389492562584,
      -1.2241389492562584,
      -1.1140602867869724,
      -1.1140602867869724,
      -0.9851515523681341,
      -0.9851515523681341,
      -0.8590985311584507,
      -0.8590985311584507,
      -0.7099959932075354,
      -0.7099959932075354,
      -0.5146450719787768,
      -0.5146450719787768,
      -0.24655595556479828,
      -0.24655595556479828,
      -0,
      -0,
      -0,
      0.21400609014122107,
      0.21400609014122107,
      0.37380350451442057,
      0.37380350451442057,
      0.5613562350853267,
      0.5613562350853267,
      0.7631687924702306,
      0.7631687924702306,
      0.9644828253339752,
      0.9644828253339752,
      1.2113737508562656,
      1.2113737508562656,
      1.399380846040442,
      1.399380846040442,
      1.5393089550293308,
      1.5393089550293308,
      1.6594461372746439,
      1.6594461372746439,
      1.85072902618988,
      1.85072902618988,
      2.0758907922144405,
      2.0758907922144405,
      2.264941270287221,
      2.264941270287221,
      2.33108549859954,
      2.33108549859954,
      2.33108549859954,
      2.33108549859954,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(1.569582197531906, 1.429180892870365, -0.49381545201135507);
    SPAunit_vector c_base_normal_surf1_cur2(-0.08697774691488243, 0.08852388391204366, 0.9922693150141938);
    SPAvector c_base_major_surf1_cur2(0.9959800438073808, -0.013684820589789494, 0.08852388391204369);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, -0.447213595499958, 0.894427190999916);
    c_surf1_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition tor_center_surf2_cur2(0, 0, 0);
    SPAunit_vector tor_normal_surf2_cur2(0, 1.3877787807814457e-17, 0.9999999999999999);
    torus tor_surf2_cur2(tor_center_surf2_cur2, tor_normal_surf2_cur2, 2, 0.5);
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.0001084441530814353, c_surf1_cur2, tor_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, -0.5213606154982516, 2.33108549859954);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur2, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur2, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug60) {
        EDGE *e1, *e2;
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = TRUE;
    int bs3_num_ctrlpts_cur1 = 78;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {-0.4114378277661478,   0.9114378277661475,    -0.5                 },
      {-0.439424158109317,    0.849441097242813,     -0.5                 },
      {-0.4563302430702456,   0.7877703595171448,    -0.49398853904242895 },
      {-0.4695593779392301,   0.6828636986736643,    -0.4710698544524662  },
      {-0.4693704779190375,   0.6366579034643504,    -0.45613600900613105 },
      {-0.4571558407996834,   0.5575069484041423,    -0.41641882913359346 },
      {-0.4469493818767203,   0.5246615074846319,    -0.3937521189978113  },
      {-0.4186718151594151,   0.4691026414980209,    -0.33751060990997916 },
      {-0.4012286433099106,   0.44836800758003353,   -0.305158842556857   },
      {-0.3585641086725895,   0.41731213330983774,   -0.22465566697637274 },
      {-0.3337531141201866,   0.41181937724458456,   -0.1768061025081789  },
      {-0.2709032739508488,   0.4168342344601367,    -0.050751206186849696},
      {-0.23217165538584306,  0.43995935377785755,   0.03199846352237634  },
      {-0.15614604423619327,  0.5084075311742536,    0.18946142835132462  },
      {-0.11797052853190193,  0.5585440473193095,    0.26576156630330316  },
      {-0.03738421947735049,  0.6677825325249833,    0.379706469363601    },
      {0.0013525390187488773, 0.7204283322841246,    0.418025649157554    },
      {0.09156072632089685,   0.8191399666145401,    0.47112331652230666  },
      {0.1409983598201776,    0.8641767856989263,    0.4865381823255752   },
      {0.25482567217887203,   0.9400379076883574,    0.5017074466034055   },
      {0.3165029510890621,    0.9693188908064001,    0.5013417684761126   },
      {0.4434464858269481,    1.00489002775685,      0.4919774938716077   },
      {0.507016464460778,     1.0120740050931245,    0.48352527477396345  },
      {0.6358143311189315,    1.0037671828303545,    0.4648158186144644   },
      {0.7003692942394204,    0.9872514953140825,    0.45460046384758535  },
      {0.7934727082105812,    0.9405421769502217,    0.4440604783393699   },
      {0.825220319966222,     0.9193115328296628,    0.44145827613366895  },
      {0.8789320082489372,    0.8721455721656368,    0.43985373961877405  },
      {0.9011683184425782,    0.8476030494426934,    0.44043553022912674  },
      {0.9476208452595605,    0.7831166126333317,    0.4447839640788249   },
      {0.968425019218742,     0.7418067864686496,    0.44967707557194503  },
      {1.0040089443929232,    0.6359058676759696,    0.4642743182695481   },
      {1.0119856548657995,    0.5699146102317443,    0.4749107990971474   },
      {1.0040098794191084,    0.4308814236659656,    0.49315405176685834  },
      {0.9852939271525116,    0.35900045705915573,   0.5001845090684554   },
      {0.9233714574423899,    0.22346185330053175,   0.49980582450343203  },
      {0.8811542607188346,    0.1627082416913912,    0.4922851783262584   },
      {0.7793763562788183,    0.05049677146276821,   0.45315286902683816  },
      {0.7209081604149435,    0.0028519433512635417, 0.42035227060350033  },
      {0.5918504840229768,    -0.09424439697574327,  0.3092525717172091   },
      {0.5286984902322048,    -0.13762522130406496,  0.22666557329932902  },
      {0.44954698509124574,   -0.2194149047730325,   0.05903824462030827  },
      {0.42503845678952407,   -0.25540084018677023,  -0.01819421711431224 },
      {0.4113025033673631,    -0.31445583481045003,  -0.13853270390679906 },
      {0.4120221277872185,    -0.3382546041138239,   -0.1855302940250686  },
      {0.4309203775084426,    -0.3803156112317564,   -0.26592981322353154 },
      {0.4453792310316275,    -0.3983631639002536,   -0.2994900002068687  },
      {0.48964708503544174,   -0.43118678157133505,  -0.361916295594631   },
      {0.5187354094925387,    -0.4448421654748249,   -0.388843132347414   },
      {0.592930768096598,     -0.4649769939712227,   -0.4373041864349269  },
      {0.637907493202794,     -0.4694429327467393,   -0.4562152266999145  },
      {0.7424853589232988,    -0.4650165947065965,   -0.4867341043197976  },
      {0.8053837279874152,    -0.4527105287338131,   -0.4962058123132598  },
      {0.944178196982509,     -0.4007951449045358,   -0.5023973241756085  },
      {1.018345897275695,     -0.3579546874246349,   -0.4967785516903265  },
      {1.1630028625585496,    -0.23449612276447573,  -0.4687556339897254  },
      {1.2290555975808006,    -0.15233803818109704,  -0.4449237087164143  },
      {1.3324122995556134,    0.04709500699709329,   -0.38112599895074106 },
      {1.3632796036197117,    0.15970695162748189,   -0.3421338286022164  },
      {1.3807109297431763,    0.39158299357307913,   -0.25943864255231613 },
      {1.3657311107047145,    0.5097237676917197,    -0.21573294253572128 },
      {1.2930475989766848,    0.7344920307834625,    -0.13758641853965414 },
      {1.2366905268733284,    0.8379315573700523,    -0.10432769275491305 },
      {1.1344838856888575,    0.9731324712451179,    -0.07937557342711776 },
      {1.0995018678966315,    1.0134386786534546,    -0.07497148214151306 },
      {1.0249925646942957,    1.0888103898584274,    -0.07427509309267089 },
      {0.9863375602144594,    1.123265966919311,     -0.07776417280041609 },
      {0.8619745796048396,    1.2204722825338166,    -0.09857975282519987 },
      {0.7713674500318127,    1.273028214755315,     -0.12608006758118773 },
      {0.5560857036556138,    1.3569428558367462,    -0.1985753424119277  },
      {0.4287384020695506,    1.3790492617687538,    -0.2459798207136582  },
      {0.18652055180418425,   1.3684891790119598,    -0.3327193025417068  },
      {0.07279208164487216,   1.3410099459374858,    -0.3724039248624268  },
      {-0.12216959731303223,  1.247804248623254,     -0.4356033882584972  },
      {-0.20482360945596978,  1.1886921088200573,    -0.46047183619672744 },
      {-0.3337754035382414,   1.051768737971838,     -0.49215493796166415 },
      {-0.3794302858996158,   0.9823425488739673,    -0.5                 },
      {-0.4114378277661478,   0.9114378277661475,    -0.5                 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 82;
    const double bs3_knots_cur1[] = {
      -9.25296264694092,
      -9.25296264694092,
      -9.25296264694092,
      -9.25296264694092,
      -9.04890024585993,
      -9.04890024585993,
      -8.884107077351386,
      -8.884107077351386,
      -8.742163070452753,
      -8.742163070452753,
      -8.595160913304468,
      -8.595160913304468,
      -8.41089366604092,
      -8.41089366604092,
      -8.109052243847165,
      -8.109052243847165,
      -7.761976989369277,
      -7.761976989369277,
      -7.470060344931845,
      -7.470060344931845,
      -7.196087813402479,
      -7.196087813402479,
      -6.926020126620186,
      -6.926020126620186,
      -6.671572591943743,
      -6.671572591943743,
      -6.405774290785613,
      -6.405774290785613,
      -6.2521763755939075,
      -6.2521763755939075,
      -6.118721451903966,
      -6.118721451903966,
      -5.931726246217316,
      -5.931726246217316,
      -5.663595387335693,
      -5.663595387335693,
      -5.36452816035192,
      -5.36452816035192,
      -5.061766015646357,
      -5.061766015646357,
      -4.732098991179782,
      -4.732098991179782,
      -4.3203436681329865,
      -4.3203436681329865,
      -4.030841999925104,
      -4.030841999925104,
      -3.8510011251016976,
      -3.8510011251016976,
      -3.707445791518917,
      -3.707445791518917,
      -3.5590507898311348,
      -3.5590507898311348,
      -3.387568322979763,
      -3.387568322979763,
      -3.175507649399919,
      -3.175507649399919,
      -2.9296445663736543,
      -2.9296445663736543,
      -2.6537554493816193,
      -2.6537554493816193,
      -2.354730860203135,
      -2.354730860203135,
      -2.0462724007685877,
      -2.0462724007685877,
      -1.739642289366219,
      -1.739642289366219,
      -1.5992728496031257,
      -1.5992728496031257,
      -1.4628127682513308,
      -1.4628127682513308,
      -1.1817405592870924,
      -1.1817405592870924,
      -0.8270724684313902,
      -0.8270724684313902,
      -0.5064267233453028,
      -0.5064267233453028,
      -0.23338307544772746,
      -0.23338307544772746,
      -0,
      -0,
      -0,
      -0,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf1_cur1(0, 0, 1);
    SPAvector c_base_major_surf1_cur1(1, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, -0.447213595499958, 0.894427190999916);
    c_surf1_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition tor_center_surf2_cur1(0, 0, 0);
    SPAunit_vector tor_normal_surf2_cur1(0, 0, 1);
    torus tor_surf2_cur1(tor_center_surf2_cur1, tor_normal_surf2_cur1, 1, 0.5);
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.00017184224853394715, c_surf1_cur1, tor_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    INTCURVE* intcurve1 = ACIS_NEW INTCURVE(ic_cur1);
    ic_cur1 = *(intcurve*)intcurve1->trans_curve(*(SPAtransf*)nullptr, TRUE);
    bounded_curve bnd_curv1(&ic_cur1, 0, 3.129478564285593);
    e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = TRUE;
    int bs3_num_ctrlpts_cur2 = 78;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.4114378277661478,   0.9114378277661475,    -0.5                 },
      {-0.439424158109317,    0.849441097242813,     -0.5                 },
      {-0.4563302430702456,   0.7877703595171448,    -0.49398853904242895 },
      {-0.4695593779392301,   0.6828636986736643,    -0.4710698544524662  },
      {-0.4693704779190375,   0.6366579034643504,    -0.45613600900613105 },
      {-0.4571558407996834,   0.5575069484041423,    -0.41641882913359346 },
      {-0.4469493818767203,   0.5246615074846319,    -0.3937521189978113  },
      {-0.4186718151594151,   0.4691026414980209,    -0.33751060990997916 },
      {-0.4012286433099106,   0.44836800758003353,   -0.305158842556857   },
      {-0.3585641086725895,   0.41731213330983774,   -0.22465566697637274 },
      {-0.3337531141201866,   0.41181937724458456,   -0.1768061025081789  },
      {-0.2709032739508488,   0.4168342344601367,    -0.050751206186849696},
      {-0.23217165538584306,  0.43995935377785755,   0.03199846352237634  },
      {-0.15614604423619327,  0.5084075311742536,    0.18946142835132462  },
      {-0.11797052853190193,  0.5585440473193095,    0.26576156630330316  },
      {-0.03738421947735049,  0.6677825325249833,    0.379706469363601    },
      {0.0013525390187488773, 0.7204283322841246,    0.418025649157554    },
      {0.09156072632089685,   0.8191399666145401,    0.47112331652230666  },
      {0.1409983598201776,    0.8641767856989263,    0.4865381823255752   },
      {0.25482567217887203,   0.9400379076883574,    0.5017074466034055   },
      {0.3165029510890621,    0.9693188908064001,    0.5013417684761126   },
      {0.4434464858269481,    1.00489002775685,      0.4919774938716077   },
      {0.507016464460778,     1.0120740050931245,    0.48352527477396345  },
      {0.6358143311189315,    1.0037671828303545,    0.4648158186144644   },
      {0.7003692942394204,    0.9872514953140825,    0.45460046384758535  },
      {0.7934727082105812,    0.9405421769502217,    0.4440604783393699   },
      {0.825220319966222,     0.9193115328296628,    0.44145827613366895  },
      {0.8789320082489372,    0.8721455721656368,    0.43985373961877405  },
      {0.9011683184425782,    0.8476030494426934,    0.44043553022912674  },
      {0.9476208452595605,    0.7831166126333317,    0.4447839640788249   },
      {0.968425019218742,     0.7418067864686496,    0.44967707557194503  },
      {1.0040089443929232,    0.6359058676759696,    0.4642743182695481   },
      {1.0119856548657995,    0.5699146102317443,    0.4749107990971474   },
      {1.0040098794191084,    0.4308814236659656,    0.49315405176685834  },
      {0.9852939271525116,    0.35900045705915573,   0.5001845090684554   },
      {0.9233714574423899,    0.22346185330053175,   0.49980582450343203  },
      {0.8811542607188346,    0.1627082416913912,    0.4922851783262584   },
      {0.7793763562788183,    0.05049677146276821,   0.45315286902683816  },
      {0.7209081604149435,    0.0028519433512635417, 0.42035227060350033  },
      {0.5918504840229768,    -0.09424439697574327,  0.3092525717172091   },
      {0.5286984902322048,    -0.13762522130406496,  0.22666557329932902  },
      {0.44954698509124574,   -0.2194149047730325,   0.05903824462030827  },
      {0.42503845678952407,   -0.25540084018677023,  -0.01819421711431224 },
      {0.4113025033673631,    -0.31445583481045003,  -0.13853270390679906 },
      {0.4120221277872185,    -0.3382546041138239,   -0.1855302940250686  },
      {0.4309203775084426,    -0.3803156112317564,   -0.26592981322353154 },
      {0.4453792310316275,    -0.3983631639002536,   -0.2994900002068687  },
      {0.48964708503544174,   -0.43118678157133505,  -0.361916295594631   },
      {0.5187354094925387,    -0.4448421654748249,   -0.388843132347414   },
      {0.592930768096598,     -0.4649769939712227,   -0.4373041864349269  },
      {0.637907493202794,     -0.4694429327467393,   -0.4562152266999145  },
      {0.7424853589232988,    -0.4650165947065965,   -0.4867341043197976  },
      {0.8053837279874152,    -0.4527105287338131,   -0.4962058123132598  },
      {0.944178196982509,     -0.4007951449045358,   -0.5023973241756085  },
      {1.018345897275695,     -0.3579546874246349,   -0.4967785516903265  },
      {1.1630028625585496,    -0.23449612276447573,  -0.4687556339897254  },
      {1.2290555975808006,    -0.15233803818109704,  -0.4449237087164143  },
      {1.3324122995556134,    0.04709500699709329,   -0.38112599895074106 },
      {1.3632796036197117,    0.15970695162748189,   -0.3421338286022164  },
      {1.3807109297431763,    0.39158299357307913,   -0.25943864255231613 },
      {1.3657311107047145,    0.5097237676917197,    -0.21573294253572128 },
      {1.2930475989766848,    0.7344920307834625,    -0.13758641853965414 },
      {1.2366905268733284,    0.8379315573700523,    -0.10432769275491305 },
      {1.1344838856888575,    0.9731324712451179,    -0.07937557342711776 },
      {1.0995018678966315,    1.0134386786534546,    -0.07497148214151306 },
      {1.0249925646942957,    1.0888103898584274,    -0.07427509309267089 },
      {0.9863375602144594,    1.123265966919311,     -0.07776417280041609 },
      {0.8619745796048396,    1.2204722825338166,    -0.09857975282519987 },
      {0.7713674500318127,    1.273028214755315,     -0.12608006758118773 },
      {0.5560857036556138,    1.3569428558367462,    -0.1985753424119277  },
      {0.4287384020695506,    1.3790492617687538,    -0.2459798207136582  },
      {0.18652055180418425,   1.3684891790119598,    -0.3327193025417068  },
      {0.07279208164487216,   1.3410099459374858,    -0.3724039248624268  },
      {-0.12216959731303223,  1.247804248623254,     -0.4356033882584972  },
      {-0.20482360945596978,  1.1886921088200573,    -0.46047183619672744 },
      {-0.3337754035382414,   1.051768737971838,     -0.49215493796166415 },
      {-0.3794302858996158,   0.9823425488739673,    -0.5                 },
      {-0.4114378277661478,   0.9114378277661475,    -0.5                 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 82;
    const double bs3_knots_cur2[] = {
      -9.25296264694092,
      -9.25296264694092,
      -9.25296264694092,
      -9.25296264694092,
      -9.04890024585993,
      -9.04890024585993,
      -8.884107077351386,
      -8.884107077351386,
      -8.742163070452753,
      -8.742163070452753,
      -8.595160913304468,
      -8.595160913304468,
      -8.41089366604092,
      -8.41089366604092,
      -8.109052243847165,
      -8.109052243847165,
      -7.761976989369277,
      -7.761976989369277,
      -7.470060344931845,
      -7.470060344931845,
      -7.196087813402479,
      -7.196087813402479,
      -6.926020126620186,
      -6.926020126620186,
      -6.671572591943743,
      -6.671572591943743,
      -6.405774290785613,
      -6.405774290785613,
      -6.2521763755939075,
      -6.2521763755939075,
      -6.118721451903966,
      -6.118721451903966,
      -5.931726246217316,
      -5.931726246217316,
      -5.663595387335693,
      -5.663595387335693,
      -5.36452816035192,
      -5.36452816035192,
      -5.061766015646357,
      -5.061766015646357,
      -4.732098991179782,
      -4.732098991179782,
      -4.3203436681329865,
      -4.3203436681329865,
      -4.030841999925104,
      -4.030841999925104,
      -3.8510011251016976,
      -3.8510011251016976,
      -3.707445791518917,
      -3.707445791518917,
      -3.5590507898311348,
      -3.5590507898311348,
      -3.387568322979763,
      -3.387568322979763,
      -3.175507649399919,
      -3.175507649399919,
      -2.9296445663736543,
      -2.9296445663736543,
      -2.6537554493816193,
      -2.6537554493816193,
      -2.354730860203135,
      -2.354730860203135,
      -2.0462724007685877,
      -2.0462724007685877,
      -1.739642289366219,
      -1.739642289366219,
      -1.5992728496031257,
      -1.5992728496031257,
      -1.4628127682513308,
      -1.4628127682513308,
      -1.1817405592870924,
      -1.1817405592870924,
      -0.8270724684313902,
      -0.8270724684313902,
      -0.5064267233453028,
      -0.5064267233453028,
      -0.23338307544772746,
      -0.23338307544772746,
      -0,
      -0,
      -0,
      -0,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf1_cur2(0, 0, 1);
    SPAvector c_base_major_surf1_cur2(1, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, -0.447213595499958, 0.894427190999916);
    c_surf1_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition tor_center_surf2_cur2(0, 0, 0);
    SPAunit_vector tor_normal_surf2_cur2(0, 0, 1);
    torus tor_surf2_cur2(tor_center_surf2_cur2, tor_normal_surf2_cur2, 1, 0.5);
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00017184224853394715, c_surf1_cur2, tor_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, -5.368423130340127, -3.1294785642855936);
    e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}


TEST_F(NurbsNurbsIntrTest, TestBug63) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = 0;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.35457960436924557,   0.5,                  0.433855350519332  },
      {0.3473900552551292,    0.4868791384200881,   0.4441410688035163 },
      {0.34183055581637206,   0.47236583148177935,  0.4528396354693747 },
      {0.3345796142598263,    0.43912323028775757,  0.4680604675985849 },
      {0.3333252162434478,    0.4211887352195374,   0.4740148454275786 },
      {0.33591271427728586,   0.35379809660149414,  0.4913601472062532 },
      {0.3518075703808671,    0.2989479536990145,   0.4963325124563524 },
      {0.3924022577281992,    0.19274119426713765,  0.5005227302297373 },
      {0.41594165390033405,   0.14209919566455545,  0.49985405472828526},
      {0.45626598117299966,   0.04603831298355339,  0.4988183187961426 },
      {0.4674644748663432,    0.013213408857412793, 0.49886026215514556},
      {0.47499484690152133,   -0.03355531292213382, 0.5021389436279184 },
      {0.4759332559885691,    -0.05060611104179667, 0.5039809801505626 },
      {0.4726084642690918,    -0.080319480943948,   0.5087063542187323 },
      {0.4694196898525879,    -0.09288955142978905, 0.5112495418795917 },
      {0.4557112087839662,    -0.12397612184549325, 0.5188304861364957 },
      {0.4436173494395821,    -0.1378411770721635,  0.5233749713995862 },
      {0.41457536994772926,   -0.16491660880404319, 0.5322277485822807 },
      {0.3910150339513758,    -0.17902521427448698, 0.5371022741328089 },
      {0.3419240982944151,    -0.1991224432696732,  0.5419697224006395 },
      {0.31645375731957337,   -0.20575173610815287, 0.5423716139355463 },
      {0.2663656312069188,    -0.2100305139121565,  0.5393338268622963 },
      {0.24213302266746187,   -0.20792565778856337, 0.5361106216321926 },
      {0.19450687813776305,   -0.19303439065700054, 0.52770122331938   },
      {0.1729801427899661,    -0.1804247383196734,  0.5228590626050389 },
      {0.11383370536094999,   -0.13079746755548022, 0.5096269231674527 },
      {0.08501430752914664,   -0.08424648806719169, 0.5040832364252362 },
      {0.031800363259837726,  0.013170969728227629, 0.4982820000706169 },
      {0.0039659455141837635, 0.08237806723837549,  0.49896112422672007},
      {-0.06653056799039775,  0.2300241236920345,   0.5040773366741349 },
      {-0.08481380930028477,  0.26658190070496884,  0.5057814125176614 },
      {-0.11417164216747547,  0.33010729059156474,  0.509970789053468  },
      {-0.126921016776858,    0.36057663415913643,  0.5127717325639916 },
      {-0.13828276628026534,  0.4084694445757947,   0.5191888981786609 },
      {-0.1400395409739966,   0.42674721551566847,  0.5222263158418593 },
      {-0.136046528039724,    0.4645403424975125,   0.529136237055408  },
      {-0.12970580273233132,  0.4824648296432519,   0.5327385240491013 },
      {-0.1202688651910597,   0.5,                  0.5356410494519438 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      -1.1136174496672835,
      -1.1136174496672835,
      -1.1136174496672835,
      -1.1136174496672835,
      -1.0941053945679309,
      -1.0941053945679309,
      -1.0735884191223044,
      -1.0735884191223044,
      -1.0192487767320177,
      -1.0192487767320177,
      -0.9688247054059743,
      -0.9688247054059743,
      -0.914973121446694,
      -0.914973121446694,
      -0.8853210497317903,
      -0.8853210497317903,
      -0.861832789271507,
      -0.861832789271507,
      -0.8242781227461268,
      -0.8242781227461268,
      -0.760300727783412,
      -0.760300727783412,
      -0.7014459145776499,
      -0.7014459145776499,
      -0.6445248807292913,
      -0.6445248807292913,
      -0.5854189482366197,
      -0.5854189482366197,
      -0.46526461107560446,
      -0.46526461107560446,
      -0.275242973933472,
      -0.275242973933472,
      -0.1959802288745366,
      -0.1959802288745366,
      -0.11552300336654361,
      -0.11552300336654361,
      -0.0603710509251717,
      -0.0603710509251717,
      -0,
      -0,
      -0,
      -0,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition tor_center_surf1_cur1(-1.6132064036473022, -0.7104341870635003, 0.041765422279353426);
    SPAunit_vector tor_normal_surf1_cur1(0, 0, 1);
    torus tor_surf1_cur1(tor_center_surf1_cur1, tor_normal_surf1_cur1, 2, 0.5);
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    logical bss_rationalu_surf2_cur1 = FALSE;
    int bss_degreeu_surf2_cur1 = 3;
    int bss_num_ctrlptsu_surf2_cur1 = 5;
    int bss_formu_surf2_cur1 = 0;
    int bss_poleu_surf2_cur1 = 0;
    logical bss_rationalv_surf2_cur1 = FALSE;
    int bss_degreev_surf2_cur1 = 3;
    int bss_num_ctrlptsv_surf2_cur1 = 5;
    int bss_formv_surf2_cur1 = 0;
    int bss_polev_surf2_cur1 = 0;
    const SPAposition bss_ctrlpts_surf2_cur1[] = {
      {-0.5,                -0.5,                0.5                },
      {-0.5,                -0.3821488698022421, 0.38214886980224205},
      {-0.5,                0,                   0.6178511301977578 },
      {-0.5,                0.3821488698022421,  0.38214886980224205},
      {-0.5,                0.5,                 0.5                },
      {-0.3821488698022421, -0.5,                0.38214886980224205},
      {-0.3821488698022421, -0.3821488698022421, 0.3428651597363227 },
      {-0.382148869802242,  0,                   0.5785674201318385 },
      {-0.3821488698022421, 0.3821488698022421,  0.5                },
      {-0.3821488698022421, 0.5,                 0.6178511301977578 },
      {0,                   -0.5,                0.5                },
      {0,                   -0.382148869802242,  0.5                },
      {0,                   0,                   0.5                },
      {0,                   0.382148869802242,   0.5                },
      {0,                   0.5,                 0.5                },
      {0.3821488698022421,  -0.5,                0.6178511301977578 },
      {0.3821488698022421,  -0.3821488698022421, 0.6571348402636774 },
      {0.382148869802242,   0,                   0.4214325798681614 },
      {0.3821488698022421,  0.3821488698022421,  0.5                },
      {0.3821488698022421,  0.5,                 0.38214886980224205},
      {0.5,                 -0.5,                0.5                },
      {0.5,                 -0.3821488698022421, 0.6178511301977578 },
      {0.5,                 0,                   0.38214886980224216},
      {0.5,                 0.3821488698022421,  0.6178511301977578 },
      {0.5,                 0.5,                 0.5                },
    };
    const double* bss_weights_surf2_cur1 = nullptr;
    double bss_ctrlpt_tol_surf2_cur1 = 1e-06;
    int bss_num_knotsu_surf2_cur1 = 9;
    double bss_knotsu_surf2_cur1[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf2_cur1 = 9;
    double bss_knotsv_surf2_cur1[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf2_cur1 = 1e-10;
    bs3_surface bss_surf2_cur1 = bs3_surface_from_ctrlpts(bss_degreeu_surf2_cur1, bss_rationalu_surf2_cur1, bss_formu_surf2_cur1, bss_poleu_surf2_cur1, bss_num_ctrlptsu_surf2_cur1, bss_degreev_surf2_cur1, bss_rationalv_surf2_cur1, bss_formv_surf2_cur1,
                                                          bss_polev_surf2_cur1, bss_num_ctrlptsv_surf2_cur1, bss_ctrlpts_surf2_cur1, bss_weights_surf2_cur1, bss_ctrlpt_tol_surf2_cur1, bss_num_knotsu_surf2_cur1, bss_knotsu_surf2_cur1,
                                                          bss_num_knotsv_surf2_cur1, bss_knotsv_surf2_cur1, bss_ctrlpt_tol_surf2_cur1);
    spline spl_surf2_cur1(bss_surf2_cur1);
    int bs2_degree_pcurve2_cur1 = 3;
    logical bs2_rational_pcurve2_cur1 = 0;
    logical bs2_closed_pcurve2_cur1 = FALSE;
    logical bs2_periodic_pcurve2_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve2_cur1 = 55;
    const SPAposition bs2_ctrlpts_pcurve2_cur1[] = {
      {0.8271815934759383,  1,                   0},
      {0.8196793913622147,  0.9814442996036685,  0},
      {0.8139739044032258,  0.962196458854196,   0},
      {0.8103568930975241,  0.9420194031863478,  0},
      {0.8065535965320025,  0.9208031779556175,  0},
      {0.8052838974622909,  0.8997813435904867,  0},
      {0.8060061702760439,  0.8791174303301427,  0},
      {0.8079191250637309,  0.8243886200370861,  0},
      {0.8239802051492686,  0.769829949431837,   0},
      {0.8464886875746861,  0.7180031459232408,  0},
      {0.8673752682243799,  0.6699108449480426,  0},
      {0.8936381278702319,  0.6246875870064743,  0},
      {0.9168207291809615,  0.583729460457416,   0},
      {0.9415791385685526,  0.5399872569290738,  0},
      {0.9562513330112236,  0.511532700152144,   0},
      {0.9625546081699978,  0.4852154687996606,  0},
      {0.9660253541222075,  0.470724522126827,   0},
      {0.9672605854979206,  0.45583171731471267, 0},
      {0.9648409076638135,  0.4412928908791869,  0},
      {0.9629242111259148,  0.42977626750838743, 0},
      {0.9587577545955622,  0.41871684737220555, 0},
      {0.9520580722201785,  0.408146534792635,   0},
      {0.9413461534785182,  0.39124598293329077, 0},
      {0.9264823312496077,  0.3788742479055749,  0},
      {0.9137783431770119,  0.36990620075160974, 0},
      {0.8921360777085435,  0.35462841112123916, 0},
      {0.8656578228916344,  0.3418450373687633,  0},
      {0.8385995884781114,  0.3323031639038064,  0},
      {0.8137078695668662,  0.32352529508404054, 0},
      {0.7879758787510163,  0.3174222591591354,  0},
      {0.7631290291865382,  0.31542044193792346, 0},
      {0.7390985669686024,  0.31348439797481603, 0},
      {0.7162235359114691,  0.31543461124079925, 0},
      {0.6945877041385369,  0.3221316214004251,  0},
      {0.6721213867557473,  0.3290856945019803,  0},
      {0.652634504186372,   0.3406031898821936,  0},
      {0.6351339422396262,  0.3553490902643064,  0},
      {0.5995576754931832,  0.3853255039935848,  0},
      {0.574333308208048,   0.42639752920446916, 0},
      {0.5562650807225228,  0.45939746732049624, 0},
      {0.5276905469339087,  0.5115861973701934,  0},
      {0.5035332182080907,  0.5701924223750132,  0},
      {0.4600351190632404,  0.6650299041225451,  0},
      {0.4418909814012346,  0.7045889735571667,  0},
      {0.42583277786840373, 0.7391344925867092,  0},
      {0.41297543535242237, 0.7700947719406521,  0},
      {0.39992433416393025, 0.8015216191425564,  0},
      {0.3885916610913603,  0.8328316208297124,  0},
      {0.38258485623221417, 0.8639306141563111,  0},
      {0.3784673016704636,  0.885248403703413,   0},
      {0.3768963614319031,  0.9061617839575152,  0},
      {0.37859759352677463, 0.9280463194381287,  0},
      {0.3804598153500946,  0.9520018159797662,  0},
      {0.38611978058461766, 0.9752015242629641,  0},
      {0.39449414086914564, 1,                   0},
    };
    const double* bs2_weights_pcurve2_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve2_cur1 = 1e-06;
    int bs2_num_knots_pcurve2_cur1 = 59;
    const double bs2_knots_pcurve2_cur1[] = {
      -1.1136174496672835,
      -1.1136174496672835,
      -1.1136174496672835,
      -1.1136174496672835,
      -1.0941053945679309,
      -1.0941053945679309,
      -1.0941053945679309,
      -1.0735884191223044,
      -1.0735884191223044,
      -1.0735884191223044,
      -1.0192487767320177,
      -1.0192487767320177,
      -1.0192487767320177,
      -0.9688247054059743,
      -0.9688247054059743,
      -0.9688247054059743,
      -0.914973121446694,
      -0.914973121446694,
      -0.914973121446694,
      -0.8853210497317903,
      -0.8853210497317903,
      -0.8853210497317903,
      -0.861832789271507,
      -0.861832789271507,
      -0.861832789271507,
      -0.8242781227461268,
      -0.8242781227461268,
      -0.8242781227461268,
      -0.760300727783412,
      -0.760300727783412,
      -0.760300727783412,
      -0.7014459145776499,
      -0.7014459145776499,
      -0.7014459145776499,
      -0.6445248807292913,
      -0.6445248807292913,
      -0.6445248807292913,
      -0.5854189482366197,
      -0.5854189482366197,
      -0.5854189482366197,
      -0.46526461107560446,
      -0.46526461107560446,
      -0.46526461107560446,
      -0.275242973933472,
      -0.275242973933472,
      -0.275242973933472,
      -0.1959802288745366,
      -0.1959802288745366,
      -0.1959802288745366,
      -0.11552300336654361,
      -0.11552300336654361,
      -0.11552300336654361,
      -0.0603710509251717,
      -0.0603710509251717,
      -0.0603710509251717,
      -0,
      -0,
      -0,
      -0,
    };
    double bs2_knot_tol_pcurve2_cur1 = 1e-10;
    bs2_curve bs2_pcurve2_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve2_cur1, bs2_rational_pcurve2_cur1, bs2_closed_pcurve2_cur1, bs2_periodic_pcurve2_cur1, bs2_num_ctrlpts_pcurve2_cur1, bs2_ctrlpts_pcurve2_cur1, bs2_weights_pcurve2_cur1,
                                                        bs2_ctrlpt_tol_pcurve2_cur1, bs2_num_knots_pcurve2_cur1, bs2_knots_pcurve2_cur1, bs2_knot_tol_pcurve2_cur1);
    intcurve ic_cur1(bs3_cur1, 0.0001929647208468102, tor_surf1_cur1, spl_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = 0;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 5;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.5,                0.5, 0.5                },
      {-0.3821488698022421, 0.5, 0.6178511301977578 },
      {0,                   0.5, 0.5                },
      {0.3821488698022421,  0.5, 0.38214886980224205},
      {0.5,                 0.5, 0.5                },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 9;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));

    SPAinterval x_range(-0.47530235115258901, 0.58866385010478084);
    SPAinterval y_range(-0.59999999999999998, 0.59999999999999998);
    SPAinterval z_range(0.3309015842416248, 0.47446449017799958);
    SPAbox box(x_range, y_range, z_range);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2, box);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2, box);

    EXPECT_FALSE(acis_inters->next->int_point << box);
    pop_cache(gme_inters);
}


TEST_F(NurbsNurbsIntrTest, TestBug66) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {1,                    0,                     0.5                 },
      {1,                    0.0006249997656334716, 0.4995580584274806  },
      {0.999999250001052,    0.0013749992552364498, 0.4990277287467089  },
      {0.9998175759725777,   0.09221189994463322,   0.4347964366338888  },
      {0.9867863822700842,   0.1904142641940922,    0.365275151719122   },
      {0.9295213648006644,   0.38209304450765214,   0.23424998932144597 },
      {0.8852276720791057,   0.475622881144775,     0.17285046064027565 },
      {0.7919993220009852,   0.614282158113922,     0.09100709875613006 },
      {0.743462718590307,    0.6732976631783631,    0.05903439448142206 },
      {0.6302450210669235,   0.780293423064928,     0.013419097077998043},
      {0.5654436246041212,   0.8282415095025044,    0                   },
      {0.4423457742403266,   0.8993120865467055,    0                   },
      {0.37700933068347936,  0.9285332180136783,    0.01074067877010737 },
      {0.2523798109280394,   0.9698527565503943,    0.06047108290824116 },
      {0.19326525960798324,  0.9822874153827149,    0.09962795920546919 },
      {0.10221998102671837,  0.9957660061387714,    0.19067323778673406 },
      {0.0637039405308753,   0.9982964366389695,    0.24683061842658444 },
      {0.012595714975741634, 1.0002476240636176,    0.3700536372052049  },
      {0,                    1,                     0.43711233697675206 },
      {0,                    1,                     0.5628876630232479  },
      {0.012595714975741523, 1.0002476240636173,    0.6299463627947949  },
      {0.06370394053087514,  0.9982964366389694,    0.7531693815734153  },
      {0.10221998102671837,  0.9957660061387714,    0.8093267622132658  },
      {0.19326525960798335,  0.9822874153827149,    0.9003720407945308  },
      {0.2523798109280394,   0.969852756550394,     0.9395289170917589  },
      {0.3770093306834794,   0.928533218013678,     0.9892593212298927  },
      {0.44234577424032673,  0.8993120865467055,    1                   },
      {0.5654436246041212,   0.8282415095025043,    1                   },
      {0.6302450210669234,   0.7802934230649278,    0.986580902922002   },
      {0.7434627185903067,   0.6732976631783631,    0.940965605518578   },
      {0.791999322000985,    0.6142821581139222,    0.90899290124387    },
      {0.8852276720791056,   0.47562288114477524,   0.8271495393597245  },
      {0.9295213648006642,   0.3820930445076524,    0.7657500106785544  },
      {0.9867863822700842,   0.19041426419409233,   0.6347248482808784  },
      {0.9998175759725777,   0.09221189994463326,   0.5652035633661112  },
      {0.999999250001052,    0.0013749992552364498, 0.500972271253291   },
      {1,                    0.0006249997656334716, 0.5004419415725194  },
      {1,                    0,                     0.5                 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0.5, 0.5, 0.5);
    SPAunit_vector c_base_normal_surf1_cur1(0, 1, 0);
    SPAvector c_base_major_surf1_cur1(0.5, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(0, 0, 0);
    SPAunit_vector c_base_normal_surf2_cur1(0, 0, 1);
    SPAvector c_base_major_surf2_cur1(1, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, -0, -1);
    c_surf2_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.0003094793078785314, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 2.672155403962507, 3.7907784653516345);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 38;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {1,                    0,                     0.5                 },
      {1,                    0.0006249997656334716, 0.4995580584274806  },
      {0.999999250001052,    0.0013749992552364498, 0.4990277287467089  },
      {0.9998175759725777,   0.09221189994463322,   0.4347964366338888  },
      {0.9867863822700842,   0.1904142641940922,    0.365275151719122   },
      {0.9295213648006644,   0.38209304450765214,   0.23424998932144597 },
      {0.8852276720791057,   0.475622881144775,     0.17285046064027565 },
      {0.7919993220009852,   0.614282158113922,     0.09100709875613006 },
      {0.743462718590307,    0.6732976631783631,    0.05903439448142206 },
      {0.6302450210669235,   0.780293423064928,     0.013419097077998043},
      {0.5654436246041212,   0.8282415095025044,    0                   },
      {0.4423457742403266,   0.8993120865467055,    0                   },
      {0.37700933068347936,  0.9285332180136783,    0.01074067877010737 },
      {0.2523798109280394,   0.9698527565503943,    0.06047108290824116 },
      {0.19326525960798324,  0.9822874153827149,    0.09962795920546919 },
      {0.10221998102671837,  0.9957660061387714,    0.19067323778673406 },
      {0.0637039405308753,   0.9982964366389695,    0.24683061842658444 },
      {0.012595714975741634, 1.0002476240636176,    0.3700536372052049  },
      {0,                    1,                     0.43711233697675206 },
      {0,                    1,                     0.5628876630232479  },
      {0.012595714975741523, 1.0002476240636173,    0.6299463627947949  },
      {0.06370394053087514,  0.9982964366389694,    0.7531693815734153  },
      {0.10221998102671837,  0.9957660061387714,    0.8093267622132658  },
      {0.19326525960798335,  0.9822874153827149,    0.9003720407945308  },
      {0.2523798109280394,   0.969852756550394,     0.9395289170917589  },
      {0.3770093306834794,   0.928533218013678,     0.9892593212298927  },
      {0.44234577424032673,  0.8993120865467055,    1                   },
      {0.5654436246041212,   0.8282415095025043,    1                   },
      {0.6302450210669234,   0.7802934230649278,    0.986580902922002   },
      {0.7434627185903067,   0.6732976631783631,    0.940965605518578   },
      {0.791999322000985,    0.6142821581139222,    0.90899290124387    },
      {0.8852276720791056,   0.47562288114477524,   0.8271495393597245  },
      {0.9295213648006642,   0.3820930445076524,    0.7657500106785544  },
      {0.9867863822700842,   0.19041426419409233,   0.6347248482808784  },
      {0.9998175759725777,   0.09221189994463326,   0.5652035633661112  },
      {0.999999250001052,    0.0013749992552364498, 0.500972271253291   },
      {1,                    0.0006249997656334716, 0.5004419415725194  },
      {1,                    0,                     0.5                 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 42;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0.5, 0.5, 0.5);
    SPAunit_vector c_base_normal_surf1_cur2(0, 1, 0);
    SPAvector c_base_major_surf1_cur2(0.5, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(0, 0, 0);
    SPAunit_vector c_base_normal_surf2_cur2(0, 0, 1);
    SPAvector c_base_major_surf2_cur2(1, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, -0, -1);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.0003094793078785314, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0, 1.118623061389128);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    if(acis_inters && gme_inters)
    if(gme_inters&&acis_inters)EXPECT_TRUE(acis_inters->int_point == gme_inters->int_point);     
}

TEST_F(NurbsNurbsIntrTest, TestBug67) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.5,                   0,                     0                     },
      {0.5,                   0.0006249997656334716, -0.0004419415725194307},
      {0.49999925000105205,   0.0013749992552364498, -0.0009722712532910651},
      {0.4998175759725777,    0.09221189994463322,   -0.06520356336611119  },
      {0.4867863822700842,    0.1904142641940922,    -0.134724848280878    },
      {0.4295213648006644,    0.38209304450765214,   -0.265750010678554    },
      {0.38522767207910563,   0.475622881144775,     -0.32714953935972435  },
      {0.2919993220009852,    0.614282158113922,     -0.40899290124386994  },
      {0.24346271859030696,   0.6732976631783631,    -0.44096560551857794  },
      {0.13024502106692348,   0.780293423064928,     -0.48658090292200196  },
      {0.06544362460412126,   0.8282415095025044,    -0.5                  },
      {-0.057654225759673404, 0.8993120865467055,    -0.5                  },
      {-0.12299066931652063,  0.9285332180136783,    -0.48925932122989263  },
      {-0.24762018907196062,  0.9698527565503943,    -0.43952891709175884  },
      {-0.30673474039201676,  0.9822874153827149,    -0.4003720407945308   },
      {-0.39778001897328163,  0.9957660061387714,    -0.30932676221326594  },
      {-0.4362960594691247,   0.9982964366389695,    -0.25316938157341556  },
      {-0.48740428502425837,  1.0002476240636176,    -0.12994636279479507  },
      {-0.5,                  1,                     -0.06288766302324793  },
      {-0.5,                  1,                     0.06288766302324787   },
      {-0.4874042850242585,   1.0002476240636173,    0.12994636279479485   },
      {-0.43629605946912486,  0.9982964366389694,    0.25316938157341534   },
      {-0.39778001897328163,  0.9957660061387714,    0.3093267622132658    },
      {-0.30673474039201665,  0.9822874153827149,    0.4003720407945308    },
      {-0.2476201890719606,   0.969852756550394,     0.43952891709175895   },
      {-0.1229906693165206,   0.928533218013678,     0.4892593212298927    },
      {-0.057654225759673265, 0.8993120865467055,    0.5                   },
      {0.06544362460412129,   0.8282415095025043,    0.5                   },
      {0.13024502106692334,   0.7802934230649278,    0.48658090292200196   },
      {0.24346271859030666,   0.6732976631783631,    0.440965605518578     },
      {0.291999322000985,     0.6142821581139222,    0.40899290124387      },
      {0.3852276720791056,    0.47562288114477524,   0.32714953935972446   },
      {0.4295213648006642,    0.3820930445076524,    0.2657500106785544    },
      {0.48678638227008414,   0.19041426419409233,   0.13472484828087836   },
      {0.4998175759725777,    0.09221189994463326,   0.06520356336611122   },
      {0.49999925000105205,   0.0013749992552364498, 0.0009722712532910651 },
      {0.5,                   0.0006249997656334716, 0.0004419415725194307 },
      {0.5,                   0,                     0                     },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0, 0.5, 0);
    SPAunit_vector c_base_normal_surf1_cur1(0, 1, 0);
    SPAvector c_base_major_surf1_cur1(0.5, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(-0.5, 0, -0.5);
    SPAunit_vector c_base_normal_surf2_cur1(0, 0, 1);
    SPAvector c_base_major_surf2_cur1(1, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, -0, -1);
    c_surf2_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.0003094793078785314, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 0, 1.118623061389128);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 38;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.5,                   0,                     0                     },
      {0.5,                   0.0006249997656334716, -0.0004419415725194307},
      {0.49999925000105205,   0.0013749992552364498, -0.0009722712532910651},
      {0.4998175759725777,    0.09221189994463322,   -0.06520356336611119  },
      {0.4867863822700842,    0.1904142641940922,    -0.134724848280878    },
      {0.4295213648006644,    0.38209304450765214,   -0.265750010678554    },
      {0.38522767207910563,   0.475622881144775,     -0.32714953935972435  },
      {0.2919993220009852,    0.614282158113922,     -0.40899290124386994  },
      {0.24346271859030696,   0.6732976631783631,    -0.44096560551857794  },
      {0.13024502106692348,   0.780293423064928,     -0.48658090292200196  },
      {0.06544362460412126,   0.8282415095025044,    -0.5                  },
      {-0.057654225759673404, 0.8993120865467055,    -0.5                  },
      {-0.12299066931652063,  0.9285332180136783,    -0.48925932122989263  },
      {-0.24762018907196062,  0.9698527565503943,    -0.43952891709175884  },
      {-0.30673474039201676,  0.9822874153827149,    -0.4003720407945308   },
      {-0.39778001897328163,  0.9957660061387714,    -0.30932676221326594  },
      {-0.4362960594691247,   0.9982964366389695,    -0.25316938157341556  },
      {-0.48740428502425837,  1.0002476240636176,    -0.12994636279479507  },
      {-0.5,                  1,                     -0.06288766302324793  },
      {-0.5,                  1,                     0.06288766302324787   },
      {-0.4874042850242585,   1.0002476240636173,    0.12994636279479485   },
      {-0.43629605946912486,  0.9982964366389694,    0.25316938157341534   },
      {-0.39778001897328163,  0.9957660061387714,    0.3093267622132658    },
      {-0.30673474039201665,  0.9822874153827149,    0.4003720407945308    },
      {-0.2476201890719606,   0.969852756550394,     0.43952891709175895   },
      {-0.1229906693165206,   0.928533218013678,     0.4892593212298927    },
      {-0.057654225759673265, 0.8993120865467055,    0.5                   },
      {0.06544362460412129,   0.8282415095025043,    0.5                   },
      {0.13024502106692334,   0.7802934230649278,    0.48658090292200196   },
      {0.24346271859030666,   0.6732976631783631,    0.440965605518578     },
      {0.291999322000985,     0.6142821581139222,    0.40899290124387      },
      {0.3852276720791056,    0.47562288114477524,   0.32714953935972446   },
      {0.4295213648006642,    0.3820930445076524,    0.2657500106785544    },
      {0.48678638227008414,   0.19041426419409233,   0.13472484828087836   },
      {0.4998175759725777,    0.09221189994463326,   0.06520356336611122   },
      {0.49999925000105205,   0.0013749992552364498, 0.0009722712532910651 },
      {0.5,                   0.0006249997656334716, 0.0004419415725194307 },
      {0.5,                   0,                     0                     },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 42;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0, 0.5, 0);
    SPAunit_vector c_base_normal_surf1_cur2(0, 1, 0);
    SPAvector c_base_major_surf1_cur2(0.5, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(-0.5, 0, -0.5);
    SPAunit_vector c_base_normal_surf2_cur2(0, 0, 1);
    SPAvector c_base_major_surf2_cur2(1, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, -0, -1);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.0003094793078785314, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 2.672155403962507, 3.7907784653516345);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    if(gme_inters&&acis_inters)EXPECT_TRUE(acis_inters->int_point == gme_inters->int_point);                  }


TEST_F(NurbsNurbsIntrTest, TestBug70) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur1(0, 0, 1);
    SPAvector c_base_major_surf1_cur1(0.5, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur1(0, -1, 0);
    SPAvector c_base_major_surf2_cur1(1, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, 0, 1);
    c_surf2_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.00030947930787848197, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    INTCURVE* intcurve_cur1 = ACIS_NEW INTCURVE(ic_cur1);
    ic_cur1 = *(intcurve*)intcurve_cur1->trans_curve(*(SPAtransf*)nullptr, TRUE);
    bounded_curve bnd_curv1(&ic_cur1, -3.7907784653516345, -2.672155403962507);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 38;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 42;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur2(0, 0, 1);
    SPAvector c_base_major_surf1_cur2(0.5, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur2(0, -1, 0);
    SPAvector c_base_major_surf2_cur2(1, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, 0, 1);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00030947930787848197, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0, 1.118623061389128);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    if(gme_inters&&acis_inters)EXPECT_TRUE(acis_inters->int_point == gme_inters->int_point);      /*if(gme_inters) {
        auto& cur1 = ic_cur1;
        auto& cur2 = ic_cur2;
        logical tangent1 = biparallel(cur1.point_direction(acis_inters->int_point), cur2.point_direction(acis_inters->int_point));
        logical tangent2 = biparallel(cur1.point_direction(gme_inters->int_point), cur2.point_direction(gme_inters->int_point));
        acis_inters->low_rel = acis_inters->high_rel = curve_curve_rel::cur_cur_tangent;
    }
    judge(gme_inters, acis_inters);*/
}

TEST_F(NurbsNurbsIntrTest, TestBug71) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur1(0, 0, 1);
    SPAvector c_base_major_surf1_cur1(0.5, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur1(0, -1, 0);
    SPAvector c_base_major_surf2_cur1(1, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, 0, 1);
    c_surf2_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.00030947930787848197, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 2.672155403962507, 3.7907784653516345);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 38;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 42;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur2(0, 0, 1);
    SPAvector c_base_major_surf1_cur2(0.5, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur2(0, -1, 0);
    SPAvector c_base_major_surf2_cur2(1, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, 0, 1);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00030947930787848197, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0, 1.118623061389128);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    if(gme_inters&&acis_inters)EXPECT_TRUE(acis_inters->int_point == gme_inters->int_point);      /*auto& cur1 = ic_cur1;
    auto& cur2 = ic_cur2;
    logical tangent1 = biparallel(cur1.point_direction(acis_inters->int_point), cur2.point_direction(acis_inters->int_point));
    logical tangent2 = biparallel(cur1.point_direction(gme_inters->int_point), cur2.point_direction(gme_inters->int_point));
    acis_inters->low_rel = acis_inters->high_rel = curve_curve_rel::cur_cur_tangent;
    judge(gme_inters, acis_inters);*/
}

TEST_F(NurbsNurbsIntrTest, TestBug72) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 38;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 42;
    const double bs3_knots_cur1[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur1(0, 0, 1);
    SPAvector c_base_major_surf1_cur1(0.5, 0, 0);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, 0, 1);
    c_surf1_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur1(0, -1, 0);
    SPAvector c_base_major_surf2_cur1(1, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, 0, 1);
    c_surf2_cur1.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 0.00030947930787848197, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, 2.672155403962507, 3.7907784653516345);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 38;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.5,                  0,                      -0.5                 },
      {0.5,                  -0.000441941572519422,  -0.49937500023436654 },
      {0.49999925000105205,  -0.0009722712532910238, -0.49862500074476357 },
      {0.4998175759725776,   -0.06520356336611122,   -0.4077881000553668  },
      {0.4867863822700842,   -0.13472484828087805,   -0.3095857358059079  },
      {0.4295213648006644,   -0.2657500106785542,    -0.11790695549234792 },
      {0.3852276720791057,   -0.32714953935972435,   -0.024377118855224977},
      {0.2919993220009852,   -0.40899290124387,      0.11428215811392195  },
      {0.2434627185903071,   -0.440965605518578,     0.17329766317836304  },
      {0.1302450210669236,   -0.48658090292200207,   0.2802934230649279   },
      {0.06544362460412123,  -0.5,                   0.3282415095025044   },
      {-0.05765422575967338, -0.5,                   0.39931208654670547  },
      {-0.12299066931652064, -0.4892593212298926,    0.4285332180136783   },
      {-0.24762018907196065, -0.4395289170917589,    0.46985275655039427  },
      {-0.30673474039201676, -0.4003720407945308,    0.4822874153827149   },
      {-0.39778001897328163, -0.30932676221326594,   0.4957660061387714   },
      {-0.43629605946912475, -0.2531693815734155,    0.4982964366389695   },
      {-0.4874042850242584,  -0.1299463627947951,    0.5002476240636176   },
      {-0.5,                 -0.062887663023248,     0.5                  },
      {-0.5,                 0.06288766302324783,    0.5                  },
      {-0.4874042850242585,  0.12994636279479488,    0.5002476240636173   },
      {-0.43629605946912486, 0.2531693815734154,     0.4982964366389694   },
      {-0.39778001897328163, 0.3093267622132658,     0.4957660061387714   },
      {-0.30673474039201665, 0.4003720407945308,     0.4822874153827149   },
      {-0.2476201890719606,  0.43952891709175895,    0.46985275655039394  },
      {-0.12299066931652058, 0.48925932122989274,    0.42853321801367794  },
      {-0.05765422575967327, 0.5,                    0.39931208654670547  },
      {0.06544362460412123,  0.5,                    0.3282415095025043   },
      {0.13024502106692337,  0.486580902922002,      0.28029342306492766  },
      {0.24346271859030666,  0.44096560551857805,    0.17329766317836304  },
      {0.2919993220009851,   0.40899290124387006,    0.11428215811392217  },
      {0.38522767207910547,  0.32714953935972446,    -0.024377118855224755},
      {0.42952136480066416,  0.2657500106785541,     -0.11790695549234742 },
      {0.4867863822700842,   0.13472484828087805,    -0.30958573580590754 },
      {0.4998175759725776,   0.06520356336611122,    -0.40778810005536675 },
      {0.49999925000105205,  0.0009722712532910793,  -0.49862500074476357 },
      {0.5,                  0.000441941572519422,   -0.49937500023436654 },
      {0.5,                  0,                      -0.5                 },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 42;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.0022963957727416186,
      0.0022963957727416186,
      0.333756362889329,
      0.333756362889329,
      0.6652163300059163,
      0.6652163300059163,
      0.8919196956975222,
      0.8919196956975222,
      1.118623061389128,
      1.118623061389128,
      1.318343157962729,
      1.318343157962729,
      1.51806325453633,
      1.51806325453633,
      1.7067262436060737,
      1.7067262436060737,
      1.8953892326758175,
      1.8953892326758175,
      2.0840522217455613,
      2.0840522217455613,
      2.2727152108153055,
      2.2727152108153055,
      2.4724353073889063,
      2.4724353073889063,
      2.672155403962507,
      2.672155403962507,
      2.8988587696541126,
      2.8988587696541126,
      3.1255621353457186,
      3.1255621353457186,
      3.4570221024623056,
      3.4570221024623056,
      3.788482069578893,
      3.788482069578893,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
      3.7907784653516345,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(0, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur2(0, 0, 1);
    SPAvector c_base_major_surf1_cur2(0.5, 0, 0);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, 0, 1);
    c_surf1_cur2.u_param_scale = 0.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(-0.5, 0.5, -0.5);
    SPAunit_vector c_base_normal_surf2_cur2(0, -1, 0);
    SPAvector c_base_major_surf2_cur2(1, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, 0, 1);
    c_surf2_cur2.u_param_scale = 1;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.00030947930787848197, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0, 1.118623061389128);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    if(gme_inters&&acis_inters)EXPECT_TRUE(acis_inters->int_point == gme_inters->int_point);      /*auto& cur1 = ic_cur1;
    auto& cur2 = ic_cur2;
    logical tangent1 = biparallel(cur1.point_direction(acis_inters->int_point), cur2.point_direction(acis_inters->int_point));
    logical tangent2 = biparallel(cur1.point_direction(gme_inters->int_point), cur2.point_direction(gme_inters->int_point));
    acis_inters->low_rel = acis_inters->high_rel = curve_curve_rel::cur_cur_tangent;
    judge(gme_inters, acis_inters);*/
}


TEST_F(NurbsNurbsIntrTest, TestBug76) {
        int degree = 2;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 8;
    SPAposition ctrlpts[] = {
      {-0.0514340365405739, -0.1000000000000000, 0.5475897550951285 },
      {-0.0162360293255957, 0.2830554288102315,  0.3585251015470036 },
      {0.0165506885613765,  0.6318216392975380,  0.1840380564963251 },
      {0.0393859717643068,  0.8554253248153219,  0.0664106720115785 },
      {0.0546157696564442,  0.9046209815078750,  0.0081454395843128 },
      {0.0827675295452056,  0.8014828860188918,  -0.0603556998423687},
      {0.1597588105482787,  0.4394923903182357,  -0.2315541388598548},
      {0.2718064393807186,  -0.1000000000000000, -0.4781435553379086},
    };
    double weights[] = {1.0000000000000000, 1.4765051510745644, 2.6079787691609004, 5.1268347869163309, 6.5102185113847195, 4.1580259220381004, 1.8332595186621026, 1.0000000000000000};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 11;
    double knots[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1074955614636500, 0.2821548928276248, 0.8654217910984585, 1.6253245423392435, 2.0667412798306555, 2.2547176314010859, 2.2547176314010859, 2.2547176314010859};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 2;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 8;
    SPAposition ctrlpts2[] = {
      {-0.0514340365405739, -0.1000000000000000, 0.5475897550951285 },
      {-0.0162360293255957, 0.2830554288102315,  0.3585251015470036 },
      {0.0165506885613765,  0.6318216392975380,  0.1840380564963251 },
      {0.0393859717643068,  0.8554253248153219,  0.0664106720115785 },
      {0.0546157696564442,  0.9046209815078750,  0.0081454395843128 },
      {0.0827675295452056,  0.8014828860188918,  -0.0603556998423687},
      {0.1597588105482787,  0.4394923903182357,  -0.2315541388598548},
      {0.2718064393807186,  -0.1000000000000000, -0.4781435553379086},
    };
    double weights2[] = {1.0000000000000000, 1.4765051510745644, 2.6079787691609004, 5.1268347869163309, 6.5102185113847195, 4.1580259220381004, 1.8332595186621026, 1.0000000000000000};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 11;
    double knots2[] = {0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.1074955614636500, 0.2821548928276248, 0.8654217910984585, 1.6253245423392435, 2.0667412798306555, 2.2547176314010859, 2.2547176314010859, 2.2547176314010859};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    curve_curve_int* acis_inters = int_cur_cur(*ic2, *ic);
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic2, *ic);
    judge(gme_inters, acis_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}


TEST_F(NurbsNurbsIntrTest, TestBug79) {
    int degree = 3;
    logical rational = TRUE;
    logical closed = FALSE;
    logical periodic = FALSE;
    int num_ctrlpts = 1410;
    SPAposition ctrlpts[] = {
      {2.5000000000000000,  -3.1224989991991987, 0.0000000000000000},
      {2.5064893934616124,  -3.1172699610927612, 0.0000000000000000},
      {2.5194921285166085,  -3.1068415606304480, 0.0000000000000000},
      {2.5388523045318707,  -3.0910210982890440, 0.0000000000000000},
      {2.5581253757049018,  -3.0750950987258809, 0.0000000000000000},
      {2.5772951502802410,  -3.0590449830963404, 0.0000000000000000},
      {2.5963650180320772,  -3.0428765255021863, 0.0000000000000000},
      {2.6153331269225593,  -3.0265889806448749, 0.0000000000000000},
      {2.6341990344840522,  -3.0101833559537181, 0.0000000000000000},
      {2.6529619256362809,  -2.9936601950604231, 0.0000000000000000},
      {2.6716210902536197,  -2.9770201716790319, 0.0000000000000000},
      {2.6901757952384422,  -2.9602639304453207, 0.0000000000000000},
      {2.7086253188346316,  -2.9433921295310643, 0.0000000000000000},
      {2.7269689414691474,  -2.9264054291931032, 0.0000000000000000},
      {2.7452059482415279,  -2.9093044948087705, 0.0000000000000000},
      {2.7633356282921904,  -2.8920899960295539, 0.0000000000000000},
      {2.7813572750068034,  -2.8747626069746008, 0.0000000000000000},
      {2.7992701859964706,  -2.8573230061454309, 0.0000000000000000},
      {2.8170736631377356,  -2.8397718764150914, 0.0000000000000000},
      {2.8347670125963740,  -2.8221099049971756, 0.0000000000000000},
      {2.8523495448553016,  -2.8043377834200092, 0.0000000000000000},
      {2.8698205747411798,  -2.7864562074992500, 0.0000000000000000},
      {2.8871794214511297,  -2.7684658773106796, 0.0000000000000000},
      {2.9044254085792360,  -2.7503674971627654, 0.0000000000000000},
      {2.9215578641428532,  -2.7321617755690388, 0.0000000000000000},
      {2.9385761206087722,  -2.7138494252203391, 0.0000000000000000},
      {2.9554795149191908,  -2.6954311629568819, 0.0000000000000000},
      {2.9722673885175204,  -2.6769077097401608, 0.0000000000000000},
      {2.9889390873740029,  -2.6582797906247002, 0.0000000000000000},
      {3.0054939620111689,  -2.6395481347296363, 0.0000000000000000},
      {3.0219313675291106,  -2.6207134752101631, 0.0000000000000000},
      {3.0382506636305564,  -2.6017765492287701, 0.0000000000000000},
      {3.0544512146458027,  -2.5827380979263981, 0.0000000000000000},
      {3.0705323895574352,  -2.5635988663933738, 0.0000000000000000},
      {3.0864935620248675,  -2.5443596036402196, 0.0000000000000000},
      {3.1023341104087265,  -2.5250210625683192, 0.0000000000000000},
      {3.1180534177950188,  -2.5055839999404106, 0.0000000000000000},
      {3.1336508720191238,  -2.4860491763509387, 0.0000000000000000},
      {3.1491258656896246,  -2.4664173561962643, 0.0000000000000000},
      {3.1644777962119051,  -2.4466893076447120, 0.0000000000000000},
      {3.1797060658116010,  -2.4268658026064811, 0.0000000000000000},
      {3.1948100815578542,  -2.4069476167034134, 0.0000000000000000},
      {3.2097892553863461,  -2.3869355292385999, 0.0000000000000000},
      {3.2246430041221870,  -2.3668303231658605, 0.0000000000000000},
      {3.2393707495025872,  -2.3466327850590849, 0.0000000000000000},
      {3.2539719181993298,  -2.3263437050814062, 0.0000000000000000},
      {3.2684459418410756,  -2.3059638769542667, 0.0000000000000000},
      {3.2827922570354522,  -2.2854940979263265, 0.0000000000000000},
      {3.2970103053909567,  -2.2649351687422383, 0.0000000000000000},
      {3.3110995335386608,  -2.2442878936112853, 0.0000000000000000},
      {3.3250593931537247,  -2.2235530801758894, 0.0000000000000000},
      {3.3388893409767091,  -2.2027315394799838, 0.0000000000000000},
      {3.3525888388346798,  -2.1818240859372442, 0.0000000000000000},
      {3.3661573536621416,  -2.1608315372992037, 0.0000000000000000},
      {3.3795943575217309,  -2.1397547146232241, 0.0000000000000000},
      {3.3928993276247539,  -2.1185944422403504, 0.0000000000000000},
      {3.4060717463514805,  -2.0973515477230302, 0.0000000000000000},
      {3.4191111012712656,  -2.0760268618527036, 0.0000000000000000},
      {3.4320168851624562,  -2.0546212185872847, 0.0000000000000000},
      {3.4447885960320979,  -2.0331354550284999, 0.0000000000000000},
      {3.4574257371354311,  -2.0115704113891133, 0.0000000000000000},
      {3.4699278169951802,  -1.9899269309600287, 0.0000000000000000},
      {3.4822943494206662,  -1.9682058600772838, 0.0000000000000000},
      {3.4945248535266478,  -1.9464080480888943, 0.0000000000000000},
      {3.5066188537520437,  -1.9245343473216310, 0.0000000000000000},
      {3.5185758798783624,  -1.9025856130476202, 0.0000000000000000},
      {3.5303954670479709,  -1.8805627034508838, 0.0000000000000000},
      {3.5420771557821515,  -1.8584664795937356, 0.0000000000000000},
      {3.5536204919989243,  -1.8362978053830710, 0.0000000000000000},
      {3.5650250270306931,  -1.8140575475365557, 0.0000000000000000},
      {3.5762903176416265,  -1.7917465755486859, 0.0000000000000000},
      {3.5874159260449101,  -1.7693657616567713, 0.0000000000000000},
      {3.5984014199196745,  -1.7469159808067671, 0.0000000000000000},
      {3.6092463724278341,  -1.7243981106190558, 0.0000000000000000},
      {3.6199503622305951,  -1.7018130313540660, 0.0000000000000000},
      {3.6305129735048354,  -1.6791616258778428, 0.0000000000000000},
      {3.6409337959592198,  -1.6564447796274744, 0.0000000000000000},
      {3.6512124248501174,  -1.6336633805764444, 0.0000000000000000},
      {3.6613484609973019,  -1.6108183191998773, 0.0000000000000000},
      {3.6713415107994232,  -1.5879104884396829, 0.0000000000000000},
      {3.6811911862492854,  -1.5649407836696163, 0.0000000000000000},
      {3.6908971049488621,  -1.5419101026602253, 0.0000000000000000},
      {3.7004588901241511,  -1.5188193455437244, 0.0000000000000000},
      {3.7098761706397565,  -1.4956694147787617, 0.0000000000000000},
      {3.7191485810132905,  -1.4724612151151066, 0.0000000000000000},
      {3.7282757614295017,  -1.4491956535582358, 0.0000000000000000},
      {3.7372573577542654,  -1.4258736393338480, 0.0000000000000000},
      {3.7460930215482597,  -1.4024960838522811, 0.0000000000000000},
      {3.7547824100804794,  -1.3790639006728380, 0.0000000000000000},
      {3.7633251863415205,  -1.3555780054680540, 0.0000000000000000},
      {3.7717210190565980,  -1.3320393159878481, 0.0000000000000000},
      {3.7799695826984050,  -1.3084487520236259, 0.0000000000000000},
      {3.7880705574996911,  -1.2848072353722819, 0.0000000000000000},
      {3.7960236294656511,  -1.2611156898001301, 0.0000000000000000},
      {3.8038284903860649,  -1.2373750410067639, 0.0000000000000000},
      {3.8114848378472272,  -1.2135862165888296, 0.0000000000000000},
      {3.8189923752436439,  -1.1897501460037356, 0.0000000000000000},
      {3.8263508117895073,  -1.1658677605332888, 0.0000000000000000},
      {3.8335598625299236,  -1.1419399932472485, 0.0000000000000000},
      {3.8406192483519517,  -1.1179677789668325, 0.0000000000000000},
      {3.8475286959953614,  -1.0939520542281318, 0.0000000000000000},
      {3.8542879380632264,  -1.0698937572454772, 0.0000000000000000},
      {3.8608967130322176,  -1.0457938278747272, 0.0000000000000000},
      {3.8673547652627294,  -1.0216532075765012, 0.0000000000000000},
      {3.8736618450087308,  -0.9974728393793488, 0.0000000000000000},
      {3.8798177084274279,  -0.9732536678428556, 0.0000000000000000},
      {3.8858221175886403,  -0.9489966390206881, 0.0000000000000000},
      {3.8916748404840100,  -0.9247027004235890, 0.0000000000000000},
      {3.8973756510359268,  -0.9003728009823047, 0.0000000000000000},
      {3.9029243291062610,  -0.8760078910104682, 0.0000000000000000},
      {3.9083206605048222,  -0.8516089221674203, 0.0000000000000000},
      {3.9135644369976355,  -0.8271768474209856, 0.0000000000000000},
      {3.9186554563149363,  -0.8027126210101894, 0.0000000000000000},
      {3.9235935221589777,  -0.7782171984079367, 0.0000000000000000},
      {3.9283784442115590,  -0.7536915362836286, 0.0000000000000000},
      {3.9330100381413642,  -0.7291365924657490, 0.0000000000000000},
      {3.9374881256110319,  -0.7045533259043928, 0.0000000000000000},
      {3.9418125342840016,  -0.6799426966337566, 0.0000000000000000},
      {3.9459830978311534,  -0.6553056657345886, 0.0000000000000000},
      {3.9499996559371593,  -0.6306431952965945, 0.0000000000000000},
      {3.9538620543066489,  -0.6059562483808066, 0.0000000000000000},
      {3.9575701446701137,  -0.5812457889819151, 0.0000000000000000},
      {3.9611237847895779,  -0.5565127819905608, 0.0000000000000000},
      {3.9645228384640498,  -0.5317581931555992, 0.0000000000000000},
      {3.9677671755347150,  -0.5069829890463242, 0.0000000000000000},
      {3.9708566718899094,  -0.4821881370146641, 0.0000000000000000},
      {3.9737912094698551,  -0.4573746051573485, 0.0000000000000000},
      {3.9765706762711441,  -0.4325433622780421, 0.0000000000000000},
      {3.9791949663510180,  -0.4076953778494560, 0.0000000000000000},
      {3.9816639798313647,  -0.3828316219754276, 0.0000000000000000},
      {3.9839776229025263,  -0.3579530653529835, 0.0000000000000000},
      {3.9861358078268383,  -0.3330606792343740, 0.0000000000000000},
      {3.9881384529419392,  -0.3081554353890871, 0.0000000000000000},
      {3.9899854826638563,  -0.2832383060658443, 0.0000000000000000},
      {3.9916768274898247,  -0.2583102639545760, 0.0000000000000000},
      {3.9932124240009070,  -0.2333722821483830, 0.0000000000000000},
      {3.9945922148643414,  -0.2084253341054779, 0.0000000000000000},
      {3.9958161488356767,  -0.1834703936111142, 0.0000000000000000},
      {3.9968841807606514,  -0.1585084347395149, 0.0000000000000000},
      {3.9977962715768278,  -0.1335404318157389, 0.0000000000000000},
      {3.9985523883151179,  -0.1085673593777212, 0.0000000000000000},
      {3.9991525041005005,  -0.0835901921376370, 0.0000000000000000},
      {3.9995965981546657,  -0.0586099049457345, 0.0000000000000000},
      {3.9998846557903107,  -0.0336274727449334, 0.0000000000000000},
      {4.0000166927768257,  -0.0086392639356516, 0.0000000000000000},
      {3.9999925998915771,  0.0163599264422212,  0.0000000000000000},
      {3.9998121449173243,  0.0413691214319214,  0.0000000000000000},
      {3.9994752066799206,  0.0663827351588579,  0.0000000000000000},
      {3.9989818456807114,  0.0913936099113499,  0.0000000000000000},
      {3.9983320838659910,  0.1164007678937389,  0.0000000000000000},
      {3.9975259493088764,  0.1414032314889455,  0.0000000000000000},
      {3.9965634761834252,  0.1664000232842234,  0.0000000000000000},
      {3.9954447047698070,  0.1913901661126114,  0.0000000000000000},
      {3.9941696814508383,  0.2163726830901679,  0.0000000000000000},
      {3.9927384587105426,  0.2413465976543201,  0.0000000000000000},
      {3.9911510951318441,  0.2663109336018988,  0.0000000000000000},
      {3.9894076553942188,  0.2912647151272372,  0.0000000000000000},
      {3.9875082102710246,  0.3162069668602369,  0.0000000000000000},
      {3.9854528366266475,  0.3411367139044195,  0.0000000000000000},
      {3.9832416174133720,  0.3660529818749556,  0.0000000000000000},
      {3.9808746416680236,  0.3909547969366808,  0.0000000000000000},
      {3.9783520045083929,  0.4158411858420840,  0.0000000000000000},
      {3.9756738071293847,  0.4407111759692730,  0.0000000000000000},
      {3.9728401567989735,  0.4655637953599187,  0.0000000000000000},
      {3.9698511668538843,  0.4903980727571683,  0.0000000000000000},
      {3.9667069566950470,  0.5152130376435380,  0.0000000000000000},
      {3.9634076517828434,  0.5400077202787670,  0.0000000000000000},
      {3.9599533836320506,  0.5647811517376494,  0.0000000000000000},
      {3.9563442898066330,  0.5895323639478254,  0.0000000000000000},
      {3.9525805139142269,  0.6142603897275536,  0.0000000000000000},
      {3.9486622056004221,  0.6389642628234258,  0.0000000000000000},
      {3.9445895205428045,  0.6636430179480676,  0.0000000000000000},
      {3.9403626204447533,  0.6882956908177863,  0.0000000000000000},
      {3.9359816730290267,  0.7129213181901869,  0.0000000000000000},
      {3.9314468520310735,  0.7375189379017386,  0.0000000000000000},
      {3.9267583371921413,  0.7620875889053145,  0.0000000000000000},
      {3.9219163142521500,  0.7866263113076647,  0.0000000000000000},
      {3.9169209749423048,  0.8111341464068694,  0.0000000000000000},
      {3.9117725169774982,  0.8356101367297210,  0.0000000000000000},
      {3.9064711440484814,  0.8600533260690765,  0.0000000000000000},
      {3.9010170658137753,  0.8844627595211501,  0.0000000000000000},
      {3.8954104978913824,  0.9088374835227545,  0.0000000000000000},
      {3.8896516618502348,  0.9331765458884993,  0.0000000000000000},
      {3.8837407852014354,  0.9574789958479175,  0.0000000000000000},
      {3.8776781013892538,  0.9817438840825572,  0.0000000000000000},
      {3.8714638497818861,  1.0059702627629989,  0.0000000000000000},
      {3.8650982756619965,  1.0301571855858223,  0.0000000000000000},
      {3.8585816302170235,  1.0543037078105144,  0.0000000000000000},
      {3.8519141705292359,  1.0784088862963097,  0.0000000000000000},
      {3.8450961595656068,  1.1024717795389769,  0.0000000000000000},
      {3.8381278661673899,  1.1264914477075276,  0.0000000000000000},
      {3.8310095650395417,  1.1504669526808773,  0.0000000000000000},
      {3.8237415367398402,  1.1743973580844185,  0.0000000000000000},
      {3.8163240676678440,  1.1982817293265493,  0.0000000000000000},
      {3.8087574500535606,  1.2221191336351023,  0.0000000000000000},
      {3.8010419819459429,  1.2459086400937351,  0.0000000000000000},
      {3.7931779672011121,  1.2696493196782175,  0.0000000000000000},
      {3.7851657154703924,  1.2933402452926646,  0.0000000000000000},
      {3.7770055421880819,  1.3169804918056891,  0.0000000000000000},
      {3.7686977685590373,  1.3405691360864687,  0.0000000000000000},
      {3.7602427215460006,  1.3641052570407459,  0.0000000000000000},
      {3.7516407338567133,  1.3875879356467431,  0.0000000000000000},
      {3.7428921439308165,  1.4110162549909926,  0.0000000000000000},
      {3.7339972959265033,  1.4343893003040880,  0.0000000000000000},
      {3.7249565397069819,  1.4577061589963598,  0.0000000000000000},
      {3.7157702308266654,  1.4809659206934380,  0.0000000000000000},
      {3.7064387305172097,  1.5041676772717678,  0.0000000000000000},
      {3.6969624056732533,  1.5273105228939956,  0.0000000000000000},
      {3.6873416288379994,  1.5503935540443028,  0.0000000000000000},
      {3.6775767781885347,  1.5734158695636140,  0.0000000000000000},
      {3.6676682375209513,  1.5963765706847413,  0.0000000000000000},
      {3.6576163962352481,  1.6192747610674192,  0.0000000000000000},
      {3.6474216493199960,  1.6421095468332458,  0.0000000000000000},
      {3.6370843973368046,  1.6648800366005283,  0.0000000000000000},
      {3.6266050464045678,  1.6875853415190420,  0.0000000000000000},
      {3.6159840081834718,  1.7102245753046623,  0.0000000000000000},
      {3.6052216998588311,  1.7327968542739305,  0.0000000000000000},
      {3.5943185441246532,  1.7553012973784892,  0.0000000000000000},
      {3.5832749691670340,  1.7777370262394265,  0.0000000000000000},
      {3.5720914086473137,  1.8001031651815231,  0.0000000000000000},
      {3.5607683016850284,  1.8223988412673708,  0.0000000000000000},
      {3.5493060928406592,  1.8446231843314154,  0.0000000000000000},
      {3.5377052320981250,  1.8667753270138516,  0.0000000000000000},
      {3.5259661748471363,  1.8888544047944491,  0.0000000000000000},
      {3.5140893818652645,  1.9108595560262351,  0.0000000000000000},
      {3.5020753192998519,  1.9327899219690785,  0.0000000000000000},
      {3.4899244586496865,  1.9546446468231653,  0.0000000000000000},
      {3.4776372767464756,  1.9764228777623372,  0.0000000000000000},
      {3.4652142557361199,  1.9981237649673460,  0.0000000000000000},
      {3.4526558830597573,  2.0197464616589582,  0.0000000000000000},
      {3.4399626514346231,  2.0412901241309536,  0.0000000000000000},
      {3.4271350588347063,  2.0627539117830214,  0.0000000000000000},
      {3.4141736084711556,  2.0841369871534878,  0.0000000000000000},
      {3.4010788087725659,  2.1054385159519855,  0.0000000000000000},
      {3.3878511733649583,  2.1266576670919255,  0.0000000000000000},
      {3.3744912210516640,  2.1477936127229151,  0.0000000000000000},
      {3.3609994757928927,  2.1688455282629868,  0.0000000000000000},
      {3.3473764666852186,  2.1898125924307523,  0.0000000000000000},
      {3.3336227279407646,  2.2106939872773812,  0.0000000000000000},
      {3.3197387988662497,  2.2314888982184793,  0.0000000000000000},
      {3.3057252238418111,  2.2521965140658313,  0.0000000000000000},
      {3.2915825522996318,  2.2728160270589886,  0.0000000000000000},
      {3.2773113387023889,  2.2933466328967587,  0.0000000000000000},
      {3.2629121425214698,  2.3137875307685225,  0.0000000000000000},
      {3.2483855282150262,  2.3341379233854411,  0.0000000000000000},
      {3.2337320652058237,  2.3543970170115105,  0.0000000000000000},
      {3.2189523278588883,  2.3745640214944870,  0.0000000000000000},
      {3.2040468954589758,  2.3946381502966609,  0.0000000000000000},
      {3.1890163521878270,  2.4146186205254927,  0.0000000000000000},
      {3.1738612871012601,  2.4345046529641197,  0.0000000000000000},
      {3.1585822941060648,  2.4542954721016987,  0.0000000000000000},
      {3.1431799719366706,  2.4739903061636088,  0.0000000000000000},
      {3.1276549241316909,  2.4935883871415183,  0.0000000000000000},
      {3.1120077590102322,  2.5130889508232914,  0.0000000000000000},
      {3.0962390896480292,  2.5324912368227599,  0.0000000000000000},
      {3.0803495338534010,  2.5517944886093225,  0.0000000000000000},
      {3.0643397141430171,  2.5709979535374230,  0.0000000000000000},
      {3.0482102577174852,  2.5901008828758463,  0.0000000000000000},
      {3.0319617964367378,  2.6091025318368848,  0.0000000000000000},
      {3.0155949667952746,  2.6280021596053400,  0.0000000000000000},
      {2.9991104098971779,  2.6467990293673624,  0.0000000000000000},
      {2.9825087714309904,  2.6654924083391536,  0.0000000000000000},
      {2.9657907016443792,  2.6840815677954812,  0.0000000000000000},
      {2.9489568553186527,  2.7025657830980720,  0.0000000000000000},
      {2.9320078917430794,  2.7209443337238119,  0.0000000000000000},
      {2.9149444746890376,  2.7392165032928006,  0.0000000000000000},
      {2.8977672723839931,  2.7573815795962471,  0.0000000000000000},
      {2.8804769574852975,  2.7754388546241859,  0.0000000000000000},
      {2.8630742070538249,  2.7933876245930520,  0.0000000000000000},
      {2.8455597025274217,  2.8112271899730645,  0.0000000000000000},
      {2.8279341296941958,  2.8289568555154694,  0.0000000000000000},
      {2.8101981786656367,  2.8465759302795890,  0.0000000000000000},
      {2.7923525438495607,  2.8640837276597262,  0.0000000000000000},
      {2.7743979239228955,  2.8814795654118885,  0.0000000000000000},
      {2.7563350218042917,  2.8987627656803259,  0.0000000000000000},
      {2.7381645446265783,  2.9159326550239379,  0.0000000000000000},
      {2.7198872037090420,  2.9329885644424580,  0.0000000000000000},
      {2.7015037145295531,  2.9499298294025067,  0.0000000000000000},
      {2.6830147966965288,  2.9667557898634382,  0.0000000000000000},
      {2.6644211739207249,  2.9834657903030308,  0.0000000000000000},
      {2.6457235739868836,  3.0000591797429998,  0.0000000000000000},
      {2.6269227287252122,  3.0165353117743097,  0.0000000000000000},
      {2.6080193739827018,  3.0328935445823459,  0.0000000000000000},
      {2.5890142495942983,  3.0491332409718650,  0.0000000000000000},
      {2.5699080993539178,  3.0652537683918082,  0.0000000000000000},
      {2.5507016709852977,  3.0812544989598831,  0.0000000000000000},
      {2.5313957161127001,  3.0971348094870077,  0.0000000000000000},
      {2.5119909902314754,  3.1128940815015502,  0.0000000000000000},
      {2.4924882526784442,  3.1285317012733724,  0.0000000000000000},
      {2.4728882666021708,  3.1440470598377219,  0.0000000000000000},
      {2.4531917989330525,  3.1594395530188990,  0.0000000000000000},
      {2.4333996203532817,  3.1747085814537677,  0.0000000000000000},
      {2.4135125052666515,  3.1898535506150534,  0.0000000000000000},
      {2.3935312317682280,  3.2048738708344748,  0.0000000000000000},
      {2.3734565816138664,  3.2197689573256643,  0.0000000000000000},
      {2.3532893401895865,  3.2345382302069097,  0.0000000000000000},
      {2.3330302964808185,  3.2491811145237035,  0.0000000000000000},
      {2.3126802430415023,  3.2636970402711052,  0.0000000000000000},
      {2.2922399759630268,  3.2780854424158696,  0.0000000000000000},
      {2.2717102948430767,  3.2923457609184621,  0.0000000000000000},
      {2.2510920027542975,  3.3064774407547817,  0.0000000000000000},
      {2.2303859062128542,  3.3204799319377751,  0.0000000000000000},
      {2.2095928151468418,  3.3343526895387816,  0.0000000000000000},
      {2.1887135428645652,  3.3480951737087352,  0.0000000000000000},
      {2.1677489060226991,  3.3617068496991314,  0.0000000000000000},
      {2.1466997245942969,  3.3751871878828230,  0.0000000000000000},
      {2.1255668218366908,  3.3885356637745865,  0.0000000000000000},
      {2.1043510242592474,  3.4017517580515042,  0.0000000000000000},
      {2.0830531615910095,  3.4148349565731588,  0.0000000000000000},
      {2.0616740667482061,  3.4277847504015808,  0.0000000000000000},
      {2.0402145758016377,  3.4406006358210441,  0.0000000000000000},
      {2.0186755279439472,  3.4532821143576280,  0.0000000000000000},
      {1.9970577654567505,  3.4658286927985600,  0.0000000000000000},
      {1.9753621336776752,  3.4782398832114074,  0.0000000000000000},
      {1.9535894809672496,  3.4905152029629960,  0.0000000000000000},
      {1.9317406586756993,  3.5026541747381739,  0.0000000000000000},
      {1.9098165211096170,  3.5146563265583319,  0.0000000000000000},
      {1.8878179254985048,  3.5265211917997363,  0.0000000000000000},
      {1.8657457319612361,  3.5382483092116517,  0.0000000000000000},
      {1.8436008034723619,  3.5498372229342321,  0.0000000000000000},
      {1.8213840058283495,  3.5612874825162364,  0.0000000000000000},
      {1.7990962076136761,  3.5725986429324941,  0.0000000000000000},
      {1.7767382801668310,  3.5837702646011853,  0.0000000000000000},
      {1.7543110975462162,  3.5948019134009064,  0.0000000000000000},
      {1.7318155364959240,  3.6056931606875118,  0.0000000000000000},
      {1.7092524764114203,  3.6164435833107342,  0.0000000000000000},
      {1.6866227993051308,  3.6270527636306200,  0.0000000000000000},
      {1.6639273897719060,  3.6375202895337182,  0.0000000000000000},
      {1.6411671349544128,  3.6478457544490688,  0.0000000000000000},
      {1.6183429245084020,  3.6580287573639758,  0.0000000000000000},
      {1.5954556505678901,  3.6680689028395497,  0.0000000000000000},
      {1.5725062077102485,  3.6779658010260530,  0.0000000000000000},
      {1.5494954929211833,  3.6877190676780005,  0.0000000000000000},
      {1.5264244055596401,  3.6973283241690695,  0.0000000000000000},
      {1.5032938473226021,  3.7067931975067685,  0.0000000000000000},
      {1.4801047222098000,  3.7161133203468899,  0.0000000000000000},
      {1.4568579364883429,  3.7252883310077562,  0.0000000000000000},
      {1.4335543986572394,  3.7343178734842204,  0.0000000000000000},
      {1.4101950194118631,  3.7432015974614723,  0.0000000000000000},
      {1.3867807116082971,  3.7519391583285926,  0.0000000000000000},
      {1.3633123902276247,  3.7605302171919144,  0.0000000000000000},
      {1.3397909723401238,  3.7689744408881323,  0.0000000000000000},
      {1.3162173770693721,  3.7772715019972161,  0.0000000000000000},
      {1.2925925255563018,  3.7854210788550753,  0.0000000000000000},
      {1.2689173409231289,  3.7934228555660034,  0.0000000000000000},
      {1.2451927482372593,  3.8012765220149283,  0.0000000000000000},
      {1.2214196744750792,  3.8089817738793736,  0.0000000000000000},
      {1.1975990484856851,  3.8165383126412626,  0.0000000000000000},
      {1.1737318009545459,  3.8239458455984430,  0.0000000000000000},
      {1.1498188643670888,  3.8312040858760215,  0.0000000000000000},
      {1.1258611729722110,  3.8383127524374325,  0.0000000000000000},
      {1.1018596627457300,  3.8452715700953215,  0.0000000000000000},
      {1.0778152713537708,  3.8520802695221734,  0.0000000000000000},
      {1.0537289381160626,  3.8587385872606959,  0.0000000000000000},
      {1.0296016039692151,  3.8652462657340338,  0.0000000000000000},
      {1.0054342114298878,  3.8716030532556740,  0.0000000000000000},
      {0.9812277045579202,  3.8778087040392002,  0.0000000000000000},
      {0.9569830289194069,  3.8838629782077314,  0.0000000000000000},
      {0.9327011315496979,  3.8897656418032209,  0.0000000000000000},
      {0.9083829609163530,  3.8955164667954536,  0.0000000000000000},
      {0.8840294668820410,  3.9011152310908379,  0.0000000000000000},
      {0.8596416006673764,  3.9065617185409760,  0.0000000000000000},
      {0.8352203148137143,  3.9118557189509806,  0.0000000000000000},
      {0.8107665631458804,  3.9169970280875734,  0.0000000000000000},
      {0.7862813007348760,  3.9219854476869469,  0.0000000000000000},
      {0.7617654838604940,  3.9268207854623922,  0.0000000000000000},
      {0.7372200699739362,  3.9315028551116908,  0.0000000000000000},
      {0.7126460176603451,  3.9360314763242785,  0.0000000000000000},
      {0.6880442866013167,  3.9404064747881735,  0.0000000000000000},
      {0.6634158375373557,  3.9446276821966695,  0.0000000000000000},
      {0.6387616322303036,  3.9486949362547792,  0.0000000000000000},
      {0.6140826334257151,  3.9526080806854909,  0.0000000000000000},
      {0.5893798048151996,  3.9563669652357145,  0.0000000000000000},
      {0.5646541109987343,  3.9599714456820703,  0.0000000000000000},
      {0.5399065174469286,  3.9634213838363865,  0.0000000000000000},
      {0.5151379904632669,  3.9667166475509834,  0.0000000000000000},
      {0.4903494971463098,  3.9698571107237335,  0.0000000000000000},
      {0.4655420053518748,  3.9728426533028460,  0.0000000000000000},
      {0.4407164836551741,  3.9756731612914660,  0.0000000000000000},
      {0.4158739013129427,  3.9783485267519940,  0.0000000000000000},
      {0.3910152282255174,  3.9808686478101976,  0.0000000000000000},
      {0.3661414348989179,  3.9832334286590623,  0.0000000000000000},
      {0.3412534924068746,  3.9854427795624394,  0.0000000000000000},
      {0.3163523723528654,  3.9874966168584112,  0.0000000000000000},
      {0.2914390468321069,  3.9893948629624578,  0.0000000000000000},
      {0.2665144883935373,  3.9911374463703799,  0.0000000000000000},
      {0.2415796700017886,  3.9927243016609539,  0.0000000000000000},
      {0.2166355649991237,  3.9941553694983964,  0.0000000000000000},
      {0.1916831470673869,  3.9954305966345460,  0.0000000000000000},
      {0.1667233901899049,  3.9965499359108554,  0.0000000000000000},
      {0.1417572686134243,  3.9975133462600789,  0.0000000000000000},
      {0.1167857568099442,  3.9983207927078341,  0.0000000000000000},
      {0.0918098294388576,  3.9989722463736630,  0.0000000000000000},
      {0.0668304613078813,  3.9994676844727071,  0.0000000000000000},
      {0.0418486273385189,  3.9998070903140337,  0.0000000000000000},
      {0.0168641685281224,  3.9999904616331250,  0.0000000000000000},
      {-0.0081315926091210, 4.0000177796703671,  0.0000000000000000},
      {-0.0331376804053374, 3.9998888101702086,  0.0000000000000000},
      {-0.0581519815827987, 3.9996033483591713,  0.0000000000000000},
      {-0.0831638655735814, 3.9991614578882633,  0.0000000000000000},
      {-0.1081723545280865, 3.9985631587027592,  0.0000000000000000},
      {-0.1331764707712739, 3.9978084768638134,  0.0000000000000000},
      {-0.1581752368176056, 3.9968974445369749,  0.0000000000000000},
      {-0.1831676754153919, 3.9958300999935941,  0.0000000000000000},
      {-0.2081528095832592, 3.9946064876084639,  0.0000000000000000},
      {-0.2331296626487013, 3.9932266578581892,  0.0000000000000000},
      {-0.2580972582860731, 3.9916906673190269,  0.0000000000000000},
      {-0.2830546205547047, 3.9899985786645953,  0.0000000000000000},
      {-0.3080007739369643, 3.9881504606633040,  0.0000000000000000},
      {-0.3329347433763278, 3.9861463881755452,  0.0000000000000000},
      {-0.3578555543154003, 3.9839864421506732,  0.0000000000000000},
      {-0.3827622327339550, 3.9816707096237147,  0.0000000000000000},
      {-0.4076538051869121, 3.9791992837118588,  0.0000000000000000},
      {-0.4325292988423202, 3.9765722636107066,  0.0000000000000000},
      {-0.4573877415193154, 3.9737897545902889,  0.0000000000000000},
      {-0.4822281617260279, 3.9708518679908198,  0.0000000000000000},
      {-0.5070495886975002, 3.9677587212182686,  0.0000000000000000},
      {-0.5318510524335365, 3.9645104377396034,  0.0000000000000000},
      {-0.5566315837365550, 3.9611071470779304,  0.0000000000000000},
      {-0.5813902142493871, 3.9575489848072385,  0.0000000000000000},
      {-0.6061259764930585, 3.9538360925470561,  0.0000000000000000},
      {-0.6308379039045182, 3.9499686179567552,  0.0000000000000000},
      {-0.6555250308743491, 3.9459467147297036,  0.0000000000000000},
      {-0.6801863927844338, 3.9417705425871272,  0.0000000000000000},
      {-0.7048210260455757, 3.9374402672717590,  0.0000000000000000},
      {-0.7294279681350854, 3.9329560605412590,  0.0000000000000000},
      {-0.7540062576343340, 3.9283181001613752,  0.0000000000000000},
      {-0.7785549342662366, 3.9235265698989013,  0.0000000000000000},
      {-0.8030730389327261, 3.9185816595143668,  0.0000000000000000},
      {-0.8275596137521470, 3.9134835647545234,  0.0000000000000000},
      {-0.8520137020966246, 3.9082324873445806,  0.0000000000000000},
      {-0.8764343486293724, 3.9028286349801951,  0.0000000000000000},
      {-0.9008205993419611, 3.8972722213192781,  0.0000000000000000},
      {-0.9251715015915140, 3.8915634659734870,  0.0000000000000000},
      {-0.9494861041378766, 3.8857025944995849,  0.0000000000000000},
      {-0.9737634571807003, 3.8796898383904570,  0.0000000000000000},
      {-0.9980026123965025, 3.8735254350660115,  0.0000000000000000},
      {-1.0222026229756374, 3.8672096278637458,  0.0000000000000000},
      {-1.0463625436592296, 3.8607426660291524,  0.0000000000000000},
      {-1.0704814307760371, 3.8541248047058461,  0.0000000000000000},
      {-1.0945583422792495, 3.8473563049255137,  0.0000000000000000},
      {-1.1185923377832345, 3.8404374335975735,  0.0000000000000000},
      {-1.1425824786001966, 3.8333684634986405,  0.0000000000000000},
      {-1.1665278277768045, 3.8261496732617850,  0.0000000000000000},
      {-1.1904274501307022, 3.8187813473654790,  0.0000000000000000},
      {-1.2142804122870090, 3.8112637761224368,  0.0000000000000000},
      {-1.2380857827146825, 3.8035972556680941,  0.0000000000000000},
      {-1.2618426317628721, 3.7957820879489783,  0.0000000000000000},
      {-1.2855500316971602, 3.7878185807107725,  0.0000000000000000},
      {-1.3092070567357250, 3.7797070474861840,  0.0000000000000000},
      {-1.3328127830854639, 3.7714478075825912,  0.0000000000000000},
      {-1.3563662889779984, 3.7630411860694482,  0.0000000000000000},
      {-1.3798666547056131, 3.7544875137654818,  0.0000000000000000},
      {-1.4033129626571290, 3.7457871272256420,  0.0000000000000000},
      {-1.4267042973536745, 3.7369403687278613,  0.0000000000000000},
      {-1.4500397454843761, 3.7279475862595515,  0.0000000000000000},
      {-1.4733183959419773, 3.7188091335039157,  0.0000000000000000},
      {-1.4965393398583497, 3.7095253698259998,  0.0000000000000000},
      {-1.5197016706399415, 3.7000966602585654,  0.0000000000000000},
      {-1.5428044840031097, 3.6905233754876972,  0.0000000000000000},
      {-1.5658468780093875, 3.6808058918382205,  0.0000000000000000},
      {-1.5888279531006355, 3.6709445912588943,  0.0000000000000000},
      {-1.6117468121341199, 3.6609398613073640,  0.0000000000000000},
      {-1.6346025604174823, 3.6507920951349258,  0.0000000000000000},
      {-1.6573943057436253, 3.6405016914710497,  0.0000000000000000},
      {-1.6801211584254780, 3.6300690546076897,  0.0000000000000000},
      {-1.7027822313307002, 3.6194945943833945,  0.0000000000000000},
      {-1.7253766399162456, 3.6087787261671678,  0.0000000000000000},
      {-1.7479035022628489, 3.5979218708421481,  0.0000000000000000},
      {-1.7703619391094034, 3.5869244547890382,  0.0000000000000000},
      {-1.7927510738872405, 3.5757869098693731,  0.0000000000000000},
      {-1.8150700327542784, 3.5645096734084918,  0.0000000000000000},
      {-1.8373179446291081, 3.5530931881784014,  0.0000000000000000},
      {-1.8594939412249207, 3.5415379023803117,  0.0000000000000000},
      {-1.8815971570833705, 3.5298442696270689,  0.0000000000000000},
      {-1.9036267296082889, 3.5180127489252913,  0.0000000000000000},
      {-1.9255817990993247, 3.5060438046573572,  0.0000000000000000},
      {-1.9474615087854241, 3.4939379065631306,  0.0000000000000000},
      {-1.9692650048582436, 3.4816955297215242,  0.0000000000000000},
      {-1.9909914365054187, 3.4693171545318200,  0.0000000000000000},
      {-2.0126399559437091, 3.4568032666948105,  0.0000000000000000},
      {-2.0342097184520567, 3.4441543571936930,  0.0000000000000000},
      {-2.0556998824044914, 3.4313709222748123,  0.0000000000000000},
      {-2.0771096093029287, 3.4184534634281460,  0.0000000000000000},
      {-2.0984380638098523, 3.4054024873676272,  0.0000000000000000},
      {-2.1196844137808526, 3.3922185060112162,  0.0000000000000000},
      {-2.1408478302970639, 3.3789020364608335,  0.0000000000000000},
      {-2.1619274876974548, 3.3654536009820242,  0.0000000000000000},
      {-2.1829225636110055, 3.3518737269834653,  0.0000000000000000},
      {-2.2038322389887433, 3.3381629469962588,  0.0000000000000000},
      {-2.2246556981356611, 3.3243217986530142,  0.0000000000000000},
      {-2.2453921287425014, 3.3103508246667577,  0.0000000000000000},
      {-2.2660407219173844, 3.2962505728096119,  0.0000000000000000},
      {-2.2866006722173480, 3.2820215958913015,  0.0000000000000000},
      {-2.3070711776797097, 3.2676644517374567,  0.0000000000000000},
      {-2.3274514398533155, 3.2531797031677230,  0.0000000000000000},
      {-2.3477406638296383, 3.2385679179736533,  0.0000000000000000},
      {-2.3679380582737570, 3.2238296688964514,  0.0000000000000000},
      {-2.3880428354551668, 3.2089655336044740,  0.0000000000000000},
      {-2.4080542112784764, 3.1939760946705866,  0.0000000000000000},
      {-2.4279714053139392, 3.1788619395492730,  0.0000000000000000},
      {-2.4477936408278627, 3.1636236605536165,  0.0000000000000000},
      {-2.4675201448128576, 3.1482618548320480,  0.0000000000000000},
      {-2.4871501480179417, 3.1327771243449147,  0.0000000000000000},
      {-2.5066828849785061, 3.1171700758408689,  0.0000000000000000},
      {-2.5261175940461316, 3.1014413208330751,  0.0000000000000000},
      {-2.5454535174182351, 3.0855914755752041,  0.0000000000000000},
      {-2.5646899011676023, 3.0696211610372819,  0.0000000000000000},
      {-2.5838259952717371, 3.0535310028813147,  0.0000000000000000},
      {-2.6028610536420631, 3.0373216314367646,  0.0000000000000000},
      {-2.6217943341529955, 3.0209936816758174,  0.0000000000000000},
      {-2.6406250986708200, 3.0045477931884919,  0.0000000000000000},
      {-2.6593526130824450, 2.9879846101575440,  0.0000000000000000},
      {-2.6779761473239834, 2.9713047813332203,  0.0000000000000000},
      {-2.6964949754091845, 2.9545089600078098,  0.0000000000000000},
      {-2.7149083754576866, 2.9375978039900295,  0.0000000000000000},
      {-2.7332156297231309, 2.9205719755792328,  0.0000000000000000},
      {-2.7514160246211117, 2.9034321415394473,  0.0000000000000000},
      {-2.7695088507569365, 2.8861789730732230,  0.0000000000000000},
      {-2.7874934029532721, 2.8688131457953250,  0.0000000000000000},
      {-2.8053689802775614, 2.8513353397062522,  0.0000000000000000},
      {-2.8231348860693370, 2.8337462391655652,  0.0000000000000000},
      {-2.8407904279673275, 2.8160465328650819,  0.0000000000000000},
      {-2.8583349179363968, 2.7982369138018526,  0.0000000000000000},
      {-2.8757676722943519, 2.7803180792510283,  0.0000000000000000},
      {-2.8930880117385183, 2.7622907307385027,  0.0000000000000000},
      {-2.9102952613722035, 2.7441555740134334,  0.0000000000000000},
      {-2.9273887507309593, 2.7259133190205782,  0.0000000000000000},
      {-2.9443678138086553, 2.7075646798724664,  0.0000000000000000},
      {-2.9612317890834228, 2.6891103748214160,  0.0000000000000000},
      {-2.9779800195433763, 2.6705511262313877,  0.0000000000000000},
      {-2.9946118527121954, 2.6518876605496740,  0.0000000000000000},
      {-3.0111266406744912, 2.6331207082784309,  0.0000000000000000},
      {-3.0275237401010466, 2.6142510039460602,  0.0000000000000000},
      {-3.0438025122738144, 2.5952792860784206,  0.0000000000000000},
      {-3.0599623231107840, 2.5762062971698918,  0.0000000000000000},
      {-3.0760025431906550, 2.5570327836542863,  0.0000000000000000},
      {-3.0919225477773074, 2.5377594958756027,  0.0000000000000000},
      {-3.1077217168441083, 2.5183871880586186,  0.0000000000000000},
      {-3.1233994350980412, 2.4989166182793610,  0.0000000000000000},
      {-3.1389550920036240, 2.4793485484353854,  0.0000000000000000},
      {-3.1543880818066592, 2.4596837442159463,  0.0000000000000000},
      {-3.1696978035578107, 2.4399229750719931,  0.0000000000000000},
      {-3.1848836611359381, 2.4200670141860225,  0.0000000000000000},
      {-3.1999450632713171, 2.4001166384418067,  0.0000000000000000},
      {-3.2148814235686158, 2.3800726283939477,  0.0000000000000000},
      {-3.2296921605296856, 2.3599357682373108,  0.0000000000000000},
      {-3.2443766975761994, 2.3397068457763068,  0.0000000000000000},
      {-3.2589344630720403, 2.3193866523940314,  0.0000000000000000},
      {-3.2733648903455435, 2.2989759830212764,  0.0000000000000000},
      {-3.2876674177115239, 2.2784756361053904,  0.0000000000000000},
      {-3.3018414884931082, 2.2578864135790111,  0.0000000000000000},
      {-3.3158865510433717, 2.2372091208286493,  0.0000000000000000},
      {-3.3298020587667878, 2.2164445666631667,  0.0000000000000000},
      {-3.3435874701404678, 2.1955935632820816,  0.0000000000000000},
      {-3.3572422487352074, 2.1746569262437712,  0.0000000000000000},
      {-3.3707658632363375, 2.1536354744335395,  0.0000000000000000},
      {-3.3841577874643645, 2.1325300300315395,  0.0000000000000000},
      {-3.3974175003954263, 2.1113414184805888,  0.0000000000000000},
      {-3.4105444861815233, 2.0900704684538374,  0.0000000000000000},
      {-3.4235382341705769, 2.0687180118223312,  0.0000000000000000},
      {-3.4363982389262491, 2.0472848836224333,  0.0000000000000000},
      {-3.4491240002476005, 2.0257719220231261,  0.0000000000000000},
      {-3.4617150231884883, 2.0041799682932027,  0.0000000000000000},
      {-3.4741708180768338, 1.9825098667683205,  0.0000000000000000},
      {-3.4864909005335925, 1.9607624648179534,  0.0000000000000000},
      {-3.4986747914916076, 1.9389386128122048,  0.0000000000000000},
      {-3.5107220172141873, 1.9170391640885294,  0.0000000000000000},
      {-3.5226321093135060, 1.8950649749183117,  0.0000000000000000},
      {-3.5344046047687963, 1.8730169044733567,  0.0000000000000000},
      {-3.5460390459443163, 1.8508958147922467,  0.0000000000000000},
      {-3.5575349806071226, 1.8287025707466036,  0.0000000000000000},
      {-3.5688919619446171, 1.8064380400072237,  0.0000000000000000},
      {-3.5801095485818939, 1.7841030930101216,  0.0000000000000000},
      {-3.5911873045988720, 1.7616986029224522,  0.0000000000000000},
      {-3.6021247995471968, 1.7392254456083329,  0.0000000000000000},
      {-3.6129216084669622, 1.7166844995945612,  0.0000000000000000},
      {-3.6235773119031869, 1.6940766460362300,  0.0000000000000000},
      {-3.6340914959220876, 1.6714027686822326,  0.0000000000000000},
      {-3.6444637521271259, 1.6486637538406708,  0.0000000000000000},
      {-3.6546936776748824, 1.6258604903441840,  0.0000000000000000},
      {-3.6647808752906315, 1.6029938695151316,  0.0000000000000000},
      {-3.6747249532837891, 1.5800647851307352,  0.0000000000000000},
      {-3.6845255255630733, 1.5570741333880815,  0.0000000000000000},
      {-3.6941822116514786, 1.5340228128690545,  0.0000000000000000},
      {-3.7036946367010359, 1.5109117245051742,  0.0000000000000000},
      {-3.7130624315073222, 1.4877417715423251,  0.0000000000000000},
      {-3.7222852325237854, 1.4645138595054208,  0.0000000000000000},
      {-3.7313626818758214, 1.4412288961629613,  0.0000000000000000},
      {-3.7402944273746348, 1.4178877914915096,  0.0000000000000000},
      {-3.7490801225309003, 1.3944914576400822,  0.0000000000000000},
      {-3.7577194265681637, 1.3710408088944590,  0.0000000000000000},
      {-3.7662120044360456, 1.3475367616413971,  0.0000000000000000},
      {-3.7745575268232177, 1.3239802343327853,  0.0000000000000000},
      {-3.7827556701701459, 1.3003721474496941,  0.0000000000000000},
      {-3.7908061166816172, 1.2767134234663591,  0.0000000000000000},
      {-3.7987085543390338, 1.2530049868140951,  0.0000000000000000},
      {-3.8064626769124992, 1.2292477638451162,  0.0000000000000000},
      {-3.8140681839726422, 1.2054426827962872,  0.0000000000000000},
      {-3.8215247809022612, 1.1815906737528201,  0.0000000000000000},
      {-3.8288321789076942, 1.1576926686118671,  0.0000000000000000},
      {-3.8359900950300081, 1.1337496010460679,  0.0000000000000000},
      {-3.8429982521559127, 1.1097624064670166,  0.0000000000000000},
      {-3.8498563790284805, 1.0857320219886690,  0.0000000000000000},
      {-3.8565642102576345, 1.0616593863906765,  0.0000000000000000},
      {-3.8631214863303778, 1.0375454400816491,  0.0000000000000000},
      {-3.8695279536208380, 1.0133911250623844,  0.0000000000000000},
      {-3.8757833644000410, 0.9891973848889979,  0.0000000000000000},
      {-3.8818874768454754, 0.9649651646360098,  0.0000000000000000},
      {-3.8878400550504351, 0.9406954108593855,  0.0000000000000000},
      {-3.8936408690330988, 0.9163890715594929,  0.0000000000000000},
      {-3.8992896947454092, 0.8920470961440257,  0.0000000000000000},
      {-3.9047863140817025, 0.8676704353908511,  0.0000000000000000},
      {-3.9101305148871219, 0.8432600414108369,  0.0000000000000000},
      {-3.9153220909657733, 0.8188168676105806,  0.0000000000000000},
      {-3.9203608420886762, 0.7943418686551409,  0.0000000000000000},
      {-3.9252465740014619, 0.7698360004306662,  0.0000000000000000},
      {-3.9299790984318452, 0.7453002200070309,  0.0000000000000000},
      {-3.9345582330968725, 0.7207354856003758,  0.0000000000000000},
      {-3.9389838017099006, 0.6961427565356364,  0.0000000000000000},
      {-3.9432556339874045, 0.6715229932090232,  0.0000000000000000},
      {-3.9473735656554729, 0.6468771570504438,  0.0000000000000000},
      {-3.9513374384561404, 0.6222062104859045,  0.0000000000000000},
      {-3.9551471001534257, 0.5975111168998657,  0.0000000000000000},
      {-3.9588024045391950, 0.5727928405975606,  0.0000000000000000},
      {-3.9623032114387229, 0.5480523467672747,  0.0000000000000000},
      {-3.9656493867160711, 0.5232906014425807,  0.0000000000000000},
      {-3.9688408022792165, 0.4985085714646519,  0.0000000000000000},
      {-3.9718773360849169, 0.4737072244440397,  0.0000000000000000},
      {-3.9747588721433846, 0.4488875287243974,  0.0000000000000000},
      {-3.9774853005226896, 0.4240504533386824,  0.0000000000000000},
      {-3.9800565173529616, 0.3991969679934502,  0.0000000000000000},
      {-3.9824724248301910, 0.3743280429480402,  0.0000000000000000},
      {-3.9847329312205435, 0.3494446492859815,  0.0000000000000000},
      {-3.9868379508614971, 0.3245477577225270,  0.0000000000000000},
      {-3.9887874041737823, 0.2996383428752321,  0.0000000000000000},
      {-3.9905812176318638, 0.2747173671462869,  0.0000000000000000},
      {-3.9922193238880883, 0.2497858406940717,  0.0000000000000000},
      {-3.9937016613220555, 0.2248445974381548,  0.0000000000000000},
      {-3.9950281757342010, 0.1998951308329991,  0.0000000000000000},
      {-3.9961988140357034, 0.1749364745640138,  0.0000000000000000},
      {-3.9972135478074540, 0.1499768436705430,  0.0000000000000000},
      {-3.9980722853857609, 0.1249901894683935,  0.0000000000000000},
      {-3.9987751999673762, 0.1000783372397959,  0.0000000000000000},
      {-3.9993215051213062, 0.0748658850674814,  0.0000000000000000},
      {-3.9997140246071399, 0.0507584528274633,  0.0000000000000000},
      {-3.9999421377295072, 0.0225148535713584,  0.0000000000000000},
      {-4.0000111392633926, 0.0139539877681827,  0.0000000000000000},
      {-3.9999998839763324, -0.0000408158603103, 0.0000000000000000},
      {-4.0000007537648408, 0.0002076774752672,  0.0000000000000000},
      {-3.9999996822970476, 0.0005370349074631,  0.0000000000000000},
      {-4.0000002739440568, 0.0015108192961253,  0.0000000000000000},
      {-3.9999985223357601, 0.0032894490276010,  0.0000000000000000},
      {-3.9999951519397126, 0.0069661359154261,  0.0000000000000000},
      {-3.9999782630819785, 0.0142338394064671,  0.0000000000000000},
      {-3.9999114805416207, 0.0288258003111088,  0.0000000000000000},
      {-3.9997179432352459, 0.0496374746444376,  0.0000000000000000},
      {-3.9993299294714890, 0.0746214899511640,  0.0000000000000000},
      {-3.9987858194811756, 0.0995991271305085,  0.0000000000000000},
      {-3.9980857187357679, 0.1245739863634957,  0.0000000000000000},
      {-3.9972296286415876, 0.1495438669875668,  0.0000000000000000},
      {-3.9962175862174805, 0.1745081228785715,  0.0000000000000000},
      {-3.9950496266666820, 0.1994656916137390,  0.0000000000000000},
      {-3.9937257934041082, 0.2244156226086473,  0.0000000000000000},
      {-3.9922461353676288, 0.2493569356504662,  0.0000000000000000},
      {-3.9906107077362720, 0.2742886588524753,  0.0000000000000000},
      {-3.9888195717352790, 0.2992098185323682,  0.0000000000000000},
      {-3.9868727946854907, 0.3241194419726495,  0.0000000000000000},
      {-3.9847704499870247, 0.3490165567292213,  0.0000000000000000},
      {-3.9825126171201859, 0.3739001908648708,  0.0000000000000000},
      {-3.9800993816415287, 0.3987693729349161,  0.0000000000000000},
      {-3.9775308351808532, 0.4236231320392251,  0.0000000000000000},
      {-3.9748070754377154, 0.4484604978564258,  0.0000000000000000},
      {-3.9719282061776990, 0.4732805006828746,  0.0000000000000000},
      {-3.9688943372285110, 0.4980821714702977,  0.0000000000000000},
      {-3.9657055844757902, 0.5228645418637790,  0.0000000000000000},
      {-3.9623620698586928, 0.5476266442395933,  0.0000000000000000},
      {-3.9588639213652570, 0.5723675117430782,  0.0000000000000000},
      {-3.9552112730275133, 0.5970861783264385,  0.0000000000000000},
      {-3.9514042649163654, 0.6217816787865333,  0.0000000000000000},
      {-3.9474430431362304, 0.6464530488026230,  0.0000000000000000},
      {-3.9433277598194616, 0.6710993249740917,  0.0000000000000000},
      {-3.9390585731205050, 0.6957195448581297,  0.0000000000000000},
      {-3.9346356472098454, 0.7203127470073785,  0.0000000000000000},
      {-3.9300591522677197, 0.7448779710075373,  0.0000000000000000},
      {-3.9253292644775657, 0.7694142575149202,  0.0000000000000000},
      {-3.9204461660192718, 0.7939206482940032,  0.0000000000000000},
      {-3.9154100450621678, 0.8183961862548808,  0.0000000000000000},
      {-3.9102210957578034, 0.8428399154907305,  0.0000000000000000},
      {-3.9048795182324607, 0.8672508813151734,  0.0000000000000000},
      {-3.8993855185794786, 0.8916281302996519,  0.0000000000000000},
      {-3.8937393088512917, 0.9159707103107056,  0.0000000000000000},
      {-3.8879411070512875, 0.9402776705472149,  0.0000000000000000},
      {-3.8819911371253890, 0.9645480615776143,  0.0000000000000000},
      {-3.8758896289534350, 0.9887809353770156,  0.0000000000000000},
      {-3.8696368183403154, 1.0129753453642958,  0.0000000000000000},
      {-3.8632329470068596, 1.0371303464391461,  0.0000000000000000},
      {-3.8566782625805476, 1.0612449950190184,  0.0000000000000000},
      {-3.8499730185859073, 1.0853183490760596,  0.0000000000000000},
      {-3.8431174744347638, 1.1093494681739648,  0.0000000000000000},
      {-3.8361118954162037, 1.1333374135047454,  0.0000000000000000},
      {-3.8289565526863392, 1.1572812479254977,  0.0000000000000000},
      {-3.8216517232578218, 1.1811800359950340,  0.0000000000000000},
      {-3.8141976899891414, 1.2050328440105018,  0.0000000000000000},
      {-3.8065947415736971, 1.2288387400438938,  0.0000000000000000},
      {-3.7988431725286311, 1.2525967939785403,  0.0000000000000000},
      {-3.7909432831834433, 1.2763060775454693,  0.0000000000000000},
      {-3.7828953796683700, 1.2999656643597486,  0.0000000000000000},
      {-3.7746997739025492, 1.3235746299567190,  0.0000000000000000},
      {-3.7663567835819434, 1.3471320518281864,  0.0000000000000000},
      {-3.7578667321670509, 1.3706370094584814,  0.0000000000000000},
      {-3.7492299488703793, 1.3940885843605240,  0.0000000000000000},
      {-3.7404467686437188, 1.4174858601117302,  0.0000000000000000},
      {-3.7315175321651415, 1.4408279223898832,  0.0000000000000000},
      {-3.7224425858258363, 1.4641138590089136,  0.0000000000000000},
      {-3.7132222817166869, 1.4873427599545930,  0.0000000000000000},
      {-3.7038569776146169, 1.5105137174201444,  0.0000000000000000},
      {-3.6943470369687512, 1.5336258258417694,  0.0000000000000000},
      {-3.6846928288863170, 1.5566781819340831,  0.0000000000000000},
      {-3.6748947281183502, 1.5796698847254647,  0.0000000000000000},
      {-3.6649531150451624, 1.6026000355933194,  0.0000000000000000},
      {-3.6548683756615894, 1.6254677382992513,  0.0000000000000000},
      {-3.6446409015620627, 1.6482720990241206,  0.0000000000000000},
      {-3.6342710899253734, 1.6710122264030460,  0.0000000000000000},
      {-3.6237593434993132, 1.6936872315602853,  0.0000000000000000},
      {-3.6131060705850353, 1.7162962281440146,  0.0000000000000000},
      {-3.6023116850212209, 1.7388383323610301,  0.0000000000000000},
      {-3.5913766061680370, 1.7613126630113471,  0.0000000000000000},
      {-3.5803012588908429, 1.7837183415226598,  0.0000000000000000},
      {-3.5690860735437382, 1.8060544919847741,  0.0000000000000000},
      {-3.5577314859528402, 1.8283202411838548,  0.0000000000000000},
      {-3.5462379373993755, 1.8505147186366340,  0.0000000000000000},
      {-3.5346058746025730, 1.8726370566244595,  0.0000000000000000},
      {-3.5228357497022897, 1.8946863902272830,  0.0000000000000000},
      {-3.5109280202415012, 1.9166618573575143,  0.0000000000000000},
      {-3.4988831491485040, 1.9385625987937551,  0.0000000000000000},
      {-3.4867016047189718, 1.9603877582144520,  0.0000000000000000},
      {-3.4743838605977508, 1.9821364822314091,  0.0000000000000000},
      {-3.4619303957604859, 2.0038079204232022,  0.0000000000000000},
      {-3.4493416944950033, 2.0254012253684706,  0.0000000000000000},
      {-3.4366182463825252, 2.0469155526790992,  0.0000000000000000},
      {-3.4237605462786327, 2.0683500610332701,  0.0000000000000000},
      {-3.4107690942940589, 2.0897039122084031,  0.0000000000000000},
      {-3.3976443957752576, 2.1109762711139863,  0.0000000000000000},
      {-3.3843869612847772, 2.1321663058242550,  0.0000000000000000},
      {-3.3709973065814101, 2.1532731876107865,  0.0000000000000000},
      {-3.3574759526001752, 2.1742960909749249,  0.0000000000000000},
      {-3.3438234254320696, 2.1952341936801343,  0.0000000000000000},
      {-3.3300402563036080, 2.2160866767841725,  0.0000000000000000},
      {-3.3161269815562116, 2.2368527246711691,  0.0000000000000000},
      {-3.3020841426253327, 2.2575315250835666,  0.0000000000000000},
      {-3.2879122860194396, 2.2781222691539229,  0.0000000000000000},
      {-3.2736119632987553, 2.2986241514365942,  0.0000000000000000},
      {-3.2591837310538221, 2.3190363699392758,  0.0000000000000000},
      {-3.2446281508838721, 2.3393581261544130,  0.0000000000000000},
      {-3.2299457893749985, 2.3595886250904616,  0.0000000000000000},
      {-3.2151372180781115, 2.3797270753030557,  0.0000000000000000},
      {-3.2002030134867323, 2.3997726889259674,  0.0000000000000000},
      {-3.1851437570145853, 2.4197246817019931,  0.0000000000000000},
      {-3.1699600349729598, 2.4395822730136589,  0.0000000000000000},
      {-3.1546524385479491, 2.4593446859138060,  0.0000000000000000},
      {-3.1392215637774363, 2.4790111471560183,  0.0000000000000000},
      {-3.1236680115279265, 2.4985808872249091,  0.0000000000000000},
      {-3.1079923874711697, 2.5180531403662822,  0.0000000000000000},
      {-3.0921953020606119, 2.5374271446171059,  0.0000000000000000},
      {-3.0762773705076558, 2.5567021418353830,  0.0000000000000000},
      {-3.0602392127577169, 2.5758773777298396,  0.0000000000000000},
      {-3.0440814534661165, 2.5949521018894868,  0.0000000000000000},
      {-3.0278047219737925, 2.6139255678130171,  0.0000000000000000},
      {-3.0114096522827962, 2.6327970329380403,  0.0000000000000000},
      {-2.9948968830316489, 2.6515657586702024,  0.0000000000000000},
      {-2.9782670574704735, 2.6702310104121119,  0.0000000000000000},
      {-2.9615208234359880, 2.6887920575921083,  0.0000000000000000},
      {-2.9446588333262897, 2.7072481736929301,  0.0000000000000000},
      {-2.9276817440754677, 2.7255986362801434,  0.0000000000000000},
      {-2.9105902171280458, 2.7438427270304748,  0.0000000000000000},
      {-2.8933849184132381, 2.7619797317599577,  0.0000000000000000},
      {-2.8760665183190399, 2.7800089404519168,  0.0000000000000000},
      {-2.8586356916661404, 2.7979296472848030,  0.0000000000000000},
      {-2.8410931176816416, 2.8157411506598460,  0.0000000000000000},
      {-2.8234394799726550, 2.8334427532285669,  0.0000000000000000},
      {-2.8056754664996668, 2.8510337619200881,  0.0000000000000000},
      {-2.7878017695497688, 2.8685134879683343,  0.0000000000000000},
      {-2.7698190857097211, 2.8858812469389958,  0.0000000000000000},
      {-2.7517281158388300, 2.9031363587563783,  0.0000000000000000},
      {-2.7335295650416556, 2.9202781477300688,  0.0000000000000000},
      {-2.7152241426405901, 2.9373059425813981,  0.0000000000000000},
      {-2.6968125621482097, 2.9542190764697853,  0.0000000000000000},
      {-2.6782955412395357, 2.9710168870188651,  0.0000000000000000},
      {-2.6596738017240549, 2.9876987163424698,  0.0000000000000000},
      {-2.6409480695176448, 3.0042639110704132,  0.0000000000000000},
      {-2.6221190746143024, 3.0207118223741150,  0.0000000000000000},
      {-2.6031875510577120, 3.0370418059920503,  0.0000000000000000},
      {-2.5841542369126875, 3.0532532222549920,  0.0000000000000000},
      {-2.5650198742363917, 3.0693454361111261,  0.0000000000000000},
      {-2.5457852090494928, 3.0853178171509286,  0.0000000000000000},
      {-2.5264509913070698, 3.1011697396319073,  0.0000000000000000},
      {-2.5070179748694312, 3.1169005825031357,  0.0000000000000000},
      {-2.4874869174727521, 3.1325097294296187,  0.0000000000000000},
      {-2.4678585806995614, 3.1479965688164575,  0.0000000000000000},
      {-2.4481337299490820, 3.1633604938328492,  0.0000000000000000},
      {-2.4283131344074258, 3.1786009024358997,  0.0000000000000000},
      {-2.4083975670176336, 3.1937171973942093,  0.0000000000000000},
      {-2.3883878044495557, 3.2087087863113455,  0.0000000000000000},
      {-2.3682846270696358, 3.2235750816490527,  0.0000000000000000},
      {-2.3480888189104725, 3.2383155007503239,  0.0000000000000000},
      {-2.3278011676403070, 3.2529294658622478,  0.0000000000000000},
      {-2.3074224645323329, 3.2674164041586975,  0.0000000000000000},
      {-2.2869535044338747, 3.2817757477627905,  0.0000000000000000},
      {-2.2663950857354145, 3.2960069337691911,  0.0000000000000000},
      {-2.2457480103395078, 3.3101094042661861,  0.0000000000000000},
      {-2.2250130836295243, 3.3240826063575999,  0.0000000000000000},
      {-2.2041911144382884, 3.3379259921844850,  0.0000000000000000},
      {-2.1832829150165476, 3.3516390189466221,  0.0000000000000000},
      {-2.1622893010013522, 3.3652211489238462,  0.0000000000000000},
      {-2.1412110913842537, 3.3786718494971342,  0.0000000000000000},
      {-2.1200491084794093, 3.3919905931695324,  0.0000000000000000},
      {-2.0988041778915330, 3.4051768575868655,  0.0000000000000000},
      {-2.0774771284837348, 3.4182301255582388,  0.0000000000000000},
      {-2.0560687923452163, 3.4311498850763460,  0.0000000000000000},
      {-2.0345800047588614, 3.4439356293375933,  0.0000000000000000},
      {-2.0130116041686534, 3.4565868567619833,  0.0000000000000000},
      {-1.9913644321470616, 3.4691030710128241,  0.0000000000000000},
      {-1.9696393333621778, 3.4814837810162298,  0.0000000000000000},
      {-1.9478371555448599, 3.4937285009803958,  0.0000000000000000},
      {-1.9259587494556478, 3.5058367504146952,  0.0000000000000000},
      {-1.9040049688516434, 3.5178080541485608,  0.0000000000000000},
      {-1.8819766704532264, 3.5296419423501333,  0.0000000000000000},
      {-1.8598747139106444, 3.5413379505447451,  0.0000000000000000},
      {-1.8376999617705470, 3.5528956196331580,  0.0000000000000000},
      {-1.8154532794423459, 3.5643144959096178,  0.0000000000000000},
      {-1.7931355351644729, 3.5755941310796771,  0.0000000000000000},
      {-1.7707475999705762, 3.5867340822778138,  0.0000000000000000},
      {-1.7482903476555269, 3.5977339120848582,  0.0000000000000000},
      {-1.7257646547414027, 3.6085931885451696,  0.0000000000000000},
      {-1.7031714004432812, 3.6193114851836241,  0.0000000000000000},
      {-1.6805114666350094, 3.6298883810223974,  0.0000000000000000},
      {-1.6577857378147884, 3.6403234605975063,  0.0000000000000000},
      {-1.6349951010707238, 3.6506163139751502,  0.0000000000000000},
      {-1.6121404460462370, 3.6607665367678379,  0.0000000000000000},
      {-1.5892226649053789, 3.6707737301503007,  0.0000000000000000},
      {-1.5662426522980575, 3.6806375008751728,  0.0000000000000000},
      {-1.5432013053251579, 3.6903574612884702,  0.0000000000000000},
      {-1.5200995235035690, 3.6999332293448384,  0.0000000000000000},
      {-1.4969382087311236, 3.7093644286226040,  0.0000000000000000},
      {-1.4737182652514165, 3.7186506883385699,  0.0000000000000000},
      {-1.4504405996185823, 3.7277916433626288,  0.0000000000000000},
      {-1.4271061206619167, 3.7367869342321285,  0.0000000000000000},
      {-1.4037157394504740, 3.7456362071660294,  0.0000000000000000},
      {-1.3802703692575187, 3.7543391140788387,  0.0000000000000000},
      {-1.3567709255249425, 3.7628953125943134,  0.0000000000000000},
      {-1.3332183258275552, 3.7713044660589521,  0.0000000000000000},
      {-1.3096134898373122, 3.7795662435552733,  0.0000000000000000},
      {-1.2859573392874499, 3.7876803199148226,  0.0000000000000000},
      {-1.2622507979365662, 3.7956463757310148,  0.0000000000000000},
      {-1.2384947915325664, 3.8034640973717195,  0.0000000000000000},
      {-1.2146902477765984, 3.8111331769916128,  0.0000000000000000},
      {-1.1908380962868674, 3.8186533125443356,  0.0000000000000000},
      {-1.1669392685623647, 3.8260242077943971,  0.0000000000000000},
      {-1.1429946979465866, 3.8332455723288517,  0.0000000000000000},
      {-1.1190053195910918, 3.8403171215687713,  0.0000000000000000},
      {-1.0949720704190806, 3.8472385767804766,  0.0000000000000000},
      {-1.0708958890888072, 3.8540096650865232,  0.0000000000000000},
      {-1.0467777159570266, 3.8606301194764896,  0.0000000000000000},
      {-1.0226184930422804, 3.8670996788175218,  0.0000000000000000},
      {-0.9984191639881868, 3.8734180878646387,  0.0000000000000000},
      {-0.9741806740266281, 3.8795850972708252,  0.0000000000000000},
      {-0.9499039699408831, 3.8856004635968895,  0.0000000000000000},
      {-0.9255900000287177, 3.8914639493210741,  0.0000000000000000},
      {-0.9012397140653892, 3.8971753228484598,  0.0000000000000000},
      {-0.8768540632666024, 3.9027343585201297,  0.0000000000000000},
      {-0.8524340002514239, 3.9081408366220862,  0.0000000000000000},
      {-0.8279804790051085, 3.9133945433939590,  0.0000000000000000},
      {-0.8034944548419121, 3.9184952710374645,  0.0000000000000000},
      {-0.7789768843678212, 3.9234428177246503,  0.0000000000000000},
      {-0.7544287254432377, 3.9282369876058700,  0.0000000000000000},
      {-0.7298509371456298, 3.9328775908175664,  0.0000000000000000},
      {-0.7052444797321155, 3.9373644434898072,  0.0000000000000000},
      {-0.6806103146020119, 3.9416973677535623,  0.0000000000000000},
      {-0.6559494042593361, 3.9458761917477840,  0.0000000000000000},
      {-0.6312627122752522, 3.9499007496262344,  0.0000000000000000},
      {-0.6065512032505074, 3.9537708815640604,  0.0000000000000000},
      {-0.5818158427777829, 3.9574864337641795,  0.0000000000000000},
      {-0.5570575974040524, 3.9610472584633776,  0.0000000000000000},
      {-0.5322774345928472, 3.9644532139382109,  0.0000000000000000},
      {-0.5074763226865587, 3.9677041645106503,  0.0000000000000000},
      {-0.4826552308686279, 3.9707999805534993,  0.0000000000000000},
      {-0.4578151291257725, 3.9737405384955586,  0.0000000000000000},
      {-0.4329569882101100, 3.9765257208266016,  0.0000000000000000},
      {-0.4080817796013309, 3.9791554161020279,  0.0000000000000000},
      {-0.3831904754687736, 3.9816295189473889,  0.0000000000000000},
      {-0.3582840486335065, 3.9839479300625582,  0.0000000000000000},
      {-0.3333634725303847, 3.9861105562257784,  0.0000000000000000},
      {-0.3084297211700684, 3.9881173102973850,  0.0000000000000000},
      {-0.2834837691010302, 3.9899681112233267,  0.0000000000000000},
      {-0.2585265913715373, 3.9916628840384600,  0.0000000000000000},
      {-0.2335591634916082, 3.9932015598695720,  0.0000000000000000},
      {-0.2085824613949577, 3.9945840759382056,  0.0000000000000000},
      {-0.1835974614009327, 3.9958103755632033,  0.0000000000000000},
      {-0.1586051401763979, 3.9968804081630402,  0.0000000000000000},
      {-0.1336064746977365, 3.9977941292579615,  0.0000000000000000},
      {-0.1086024422123031, 3.9985515004716179,  0.0000000000000000},
      {-0.0835940202019543, 3.9991524895334831,  0.0000000000000000},
      {-0.0585821863387597, 3.9995970702772201,  0.0000000000000000},
      {-0.0335679184697218, 3.9998852226530310,  0.0000000000000000},
      {-0.0085617235734530, 4.0000168825152596,  0.0000000000000000},
      {0.0164341614869463,  3.9999922518326914,  0.0000000000000000},
      {0.0414187609910605,  3.9998115647531840,  0.0000000000000000},
      {0.0664006288568165,  3.9994748437947685,  0.0000000000000000},
      {0.0913800476597184,  3.9989820903447049,  0.0000000000000000},
      {0.1163560424769215,  3.9983333209891718,  0.0000000000000000},
      {0.1413276384984183,  3.9975285584081153,  0.0000000000000000},
      {0.1662938610619381,  3.9965678313771287,  0.0000000000000000},
      {0.1912537356919414,  3.9954511747657531,  0.0000000000000000},
      {0.2162062881374826,  3.9941786295363961,  0.0000000000000000},
      {0.2411505444103714,  3.9927502427428259,  0.0000000000000000},
      {0.2660855308232684,  3.9911660675284248,  0.0000000000000000},
      {0.2910102740277366,  3.9894261631242571,  0.0000000000000000},
      {0.3159238010523251,  3.9875305948468469,  0.0000000000000000},
      {0.3408251393406231,  3.9854794340957600,  0.0000000000000000},
      {0.3657133167892843,  3.9832727583509095,  0.0000000000000000},
      {0.3905873617860522,  3.9809106511696761,  0.0000000000000000},
      {0.4154463032477534,  3.9783932021837138,  0.0000000000000000},
      {0.4402891706582877,  3.9757205070956099,  0.0000000000000000},
      {0.4651149941065673,  3.9728926676752359,  0.0000000000000000},
      {0.4899228043244669,  3.9699097917558950,  0.0000000000000000},
      {0.5147116327247272,  3.9667719932302186,  0.0000000000000000},
      {0.5394805114388284,  3.9634793920458451,  0.0000000000000000},
      {0.5642284733548684,  3.9600321142008506,  0.0000000000000000},
      {0.5889545521553531,  3.9564302917389202,  0.0000000000000000},
      {0.6136577823550278,  3.9526740627443413,  0.0000000000000000},
      {0.6383371993386142,  3.9487635713366931,  0.0000000000000000},
      {0.6629918393985602,  3.9446989676653628,  0.0000000000000000},
      {0.6876207397727006,  3.9404804079037596,  0.0000000000000000},
      {0.7122229386819671,  3.9361080542433813,  0.0000000000000000},
      {0.7367974753679460,  3.9315820748875359,  0.0000000000000000},
      {0.7613433901305184,  3.9269026440449402,  0.0000000000000000},
      {0.7858597243653475,  3.9220699419230014,  0.0000000000000000},
      {0.8103455206014144,  3.9170841547208970,  0.0000000000000000},
      {0.8347998225384399,  3.9119454746224269,  0.0000000000000000},
      {0.8592216750843199,  3.9066540997886223,  0.0000000000000000},
      {0.8836101243924659,  3.9012102343501072,  0.0000000000000000},
      {0.9079642178991245,  3.8956140883992636,  0.0000000000000000},
      {0.9322830043606389,  3.8898658779821167,  0.0000000000000000},
      {0.9565655338906611,  3.8839658250900309,  0.0000000000000000},
      {0.9808108579973173,  3.8779141576511522,  0.0000000000000000},
      {1.0050180296202920,  3.8717111095216046,  0.0000000000000000},
      {1.0291861031679075,  3.8653569204764970,  0.0000000000000000},
      {1.0533141345540820,  3.8588518362006510,  0.0000000000000000},
      {1.0774011812352984,  3.8521961082791356,  0.0000000000000000},
      {1.1014463022474521,  3.8453899941875447,  0.0000000000000000},
      {1.1254485582426763,  3.8384337572820630,  0.0000000000000000},
      {1.1494070115260835,  3.8313276667892979,  0.0000000000000000},
      {1.1733207260924614,  3.8240719977958602,  0.0000000000000000},
      {1.1971887676628961,  3.8166670312377580,  0.0000000000000000},
      {1.2210102037212962,  3.8091130538895301,  0.0000000000000000},
      {1.2447841035509279,  3.8014103583531442,  0.0000000000000000},
      {1.2685095382707785,  3.7935592430467215,  0.0000000000000000},
      {1.2921855808719349,  3.7855600121929402,  0.0000000000000000},
      {1.3158113062538457,  3.7774129758073203,  0.0000000000000000},
      {1.3393857912605029,  3.7691184496862018,  0.0000000000000000},
      {1.3629081147165973,  3.7606767553945200,  0.0000000000000000},
      {1.3863773574635188,  3.7520882202533827,  0.0000000000000000},
      {1.4097926023953664,  3.7433531773273705,  0.0000000000000000},
      {1.4331529344948064,  3.7344719654116694,  0.0000000000000000},
      {1.4564574408688764,  3.7254449290189320,  0.0000000000000000},
      {1.4797052107847417,  3.7162724183659419,  0.0000000000000000},
      {1.5028953357052890,  3.7069547893600459,  0.0000000000000000},
      {1.5260269093247056,  3.6974924035853758,  0.0000000000000000},
      {1.5490990276039542,  3.6878856282888162,  0.0000000000000000},
      {1.5721107888061254,  3.6781348363657980,  0.0000000000000000},
      {1.5950612935317490,  3.6682404063458285,  0.0000000000000000},
      {1.6179496447539865,  3.6582027223778297,  0.0000000000000000},
      {1.6407749478537281,  3.6480221742152401,  0.0000000000000000},
      {1.6635363106546268,  3.6376991572009043,  0.0000000000000000},
      {1.6862328434579832,  3.6272340722517473,  0.0000000000000000},
      {1.7088636590776094,  3.6166273258432220,  0.0000000000000000},
      {1.7314278728745096,  3.6058793299935403,  0.0000000000000000},
      {1.7539246027915429,  3.5949905022477155,  0.0000000000000000},
      {1.7763529693879136,  3.5839612656613204,  0.0000000000000000},
      {1.7987120958736242,  3.5727920487841285,  0.0000000000000000},
      {1.8210011081437676,  3.5614832856434302,  0.0000000000000000},
      {1.8432191348127722,  3.5500354157272387,  0.0000000000000000},
      {1.8653653072484795,  3.5384488839672006,  0.0000000000000000},
      {1.8874387596061633,  3.5267241407213552,  0.0000000000000000},
      {1.9094386288624361,  3.5148616417566165,  0.0000000000000000},
      {1.9313640548489972,  3.5028618482311278,  0.0000000000000000},
      {1.9532141802863527,  3.4907252266763162,  0.0000000000000000},
      {1.9749881508173215,  3.4784522489788046,  0.0000000000000000},
      {1.9966851150405425,  3.4660433923620868,  0.0000000000000000},
      {2.0183042245437486,  3.4534991393679793,  0.0000000000000000},
      {2.0398446339370291,  3.4408199778379047,  0.0000000000000000},
      {2.0613055008859029,  3.4280064008939322,  0.0000000000000000},
      {2.0826859861442957,  3.4150589069196187,  0.0000000000000000},
      {2.1039852535874144,  3.4019779995406689,  0.0000000000000000},
      {2.1252024702444796,  3.3887641876053531,  0.0000000000000000},
      {2.1463368063313273,  3.3754179851647494,  0.0000000000000000},
      {2.1673874352829183,  3.3619399114527710,  0.0000000000000000},
      {2.1883535337856963,  3.3483304908659792,  0.0000000000000000},
      {2.2092342818098150,  3.3345902529432312,  0.0000000000000000},
      {2.2300288626412788,  3.3207197323450850,  0.0000000000000000},
      {2.2507364629138875,  3.3067194688330082,  0.0000000000000000},
      {2.2713562726411229,  3.2925900072484540,  0.0000000000000000},
      {2.2918874852478410,  3.2783318974916047,  0.0000000000000000},
      {2.3123292976018797,  3.2639456945000846,  0.0000000000000000},
      {2.3326809100455050,  3.2494319582273090,  0.0000000000000000},
      {2.3529415264267195,  3.2347912536207808,  0.0000000000000000},
      {2.3731103541304606,  3.2200241506000817,  0.0000000000000000},
      {2.3931866041096406,  3.2051312240347536,  0.0000000000000000},
      {2.4131694909160331,  3.1901130537219027,  0.0000000000000000},
      {2.4330582327310704,  3.1749702243637090,  0.0000000000000000},
      {2.4528520513964320,  3.1597033255446396,  0.0000000000000000},
      {2.4725501724445613,  3.1443129517085584,  0.0000000000000000},
      {2.4921518251289685,  3.1287997021355904,  0.0000000000000000},
      {2.5116562424544475,  3.1131641809188269,  0.0000000000000000},
      {2.5310626612071165,  3.0974069969408204,  0.0000000000000000},
      {2.5503703219843024,  3.0815287638499065,  0.0000000000000000},
      {2.5695784692243162,  3.0655301000363409,  0.0000000000000000},
      {2.5886863512360354,  3.0494116286082380,  0.0000000000000000},
      {2.6076932202283589,  3.0331739773673383,  0.0000000000000000},
      {2.6265983323395061,  3.0168177787845840,  0.0000000000000000},
      {2.6454009476661655,  3.0003436699755079,  0.0000000000000000},
      {2.6641003302924804,  2.9837522926754607,  0.0000000000000000},
      {2.6826957483188885,  2.9670442932146273,  0.0000000000000000},
      {2.7011864738907998,  2.9502203224928913,  0.0000000000000000},
      {2.7195717832271131,  2.9332810359545038,  0.0000000000000000},
      {2.7378509566485896,  2.9162270935625729,  0.0000000000000000},
      {2.7560232786060492,  2.8990591597734041,  0.0000000000000000},
      {2.7740880377084132,  2.8817779035106144,  0.0000000000000000},
      {2.7920445267505820,  2.8643839981391221,  0.0000000000000000},
      {2.8098920427411627,  2.8468781214389312,  0.0000000000000000},
      {2.8276298869300081,  2.8292609555787549,  0.0000000000000000},
      {2.8452573648356192,  2.8115331870894704,  0.0000000000000000},
      {2.8627737862723439,  2.7936955068373837,  0.0000000000000000},
      {2.8801784653774680,  2.7757486099973563,  0.0000000000000000},
      {2.8974707206380512,  2.7576931960257367,  0.0000000000000000},
      {2.9146498749176986,  2.7395299686331258,  0.0000000000000000},
      {2.9317152554830508,  2.7212596357570029,  0.0000000000000000},
      {2.9486661940302055,  2.7028829095341429,  0.0000000000000000},
      {2.9655020267108885,  2.6844005062729153,  0.0000000000000000},
      {2.9822220941584892,  2.6658131464253740,  0.0000000000000000},
      {2.9988257415139179,  2.6471215545592326,  0.0000000000000000},
      {3.0153123184512820,  2.6283264593296272,  0.0000000000000000},
      {3.0316811792033755,  2.6094285934507777,  0.0000000000000000},
      {3.0479316825870217,  2.5904286936674188,  0.0000000000000000},
      {3.0640631920281969,  2.5713275007261549,  0.0000000000000000},
      {3.0800750755870103,  2.5521257593465760,  0.0000000000000000},
      {3.0959667059824771,  2.5328242181922986,  0.0000000000000000},
      {3.1117374606171260,  2.5134236298417640,  0.0000000000000000},
      {3.1273867216014168,  2.4939247507589810,  0.0000000000000000},
      {3.1429138757779804,  2.4743283412640267,  0.0000000000000000},
      {3.1583183147456637,  2.4546351655034533,  0.0000000000000000},
      {3.1735994348834007,  2.4348459914205267,  0.0000000000000000},
      {3.1887566373738880,  2.4149615907253148,  0.0000000000000000},
      {3.2037893282270815,  2.3949827388646345,  0.0000000000000000},
      {3.2186969183034968,  2.3749102149918335,  0.0000000000000000},
      {3.2334788233373333,  2.3547448019364605,  0.0000000000000000},
      {3.2481344639593774,  2.3344872861737680,  0.0000000000000000},
      {3.2626632657197661,  2.3141384577940602,  0.0000000000000000},
      {3.2770646591105033,  2.2936991104719455,  0.0000000000000000},
      {3.2913380795878271,  2.2731700414353835,  0.0000000000000000},
      {3.3054829675943518,  2.2525520514346691,  0.0000000000000000},
      {3.3194987685810466,  2.2318459447111922,  0.0000000000000000},
      {3.3333849330289760,  2.2110525289661469,  0.0000000000000000},
      {3.3471409164708987,  2.1901726153290353,  0.0000000000000000},
      {3.3607661795126207,  2.1692070183260865,  0.0000000000000000},
      {3.3742601878541754,  2.1481565558485021,  0.0000000000000000},
      {3.3876224123108027,  2.1270220491206100,  0.0000000000000000},
      {3.4008523288337273,  2.1058043226678440,  0.0000000000000000},
      {3.4139494185307200,  2.0845042042846456,  0.0000000000000000},
      {3.4269131676865010,  2.0631225250021785,  0.0000000000000000},
      {3.4397430677828873,  2.0416601190559742,  0.0000000000000000},
      {3.4524386155187727,  2.0201178238533966,  0.0000000000000000},
      {3.4649993128298986,  1.9984964799410494,  0.0000000000000000},
      {3.4774246669084143,  1.9767969309719691,  0.0000000000000000},
      {3.4897141902222311,  1.9550200236728026,  0.0000000000000000},
      {3.5018674005341799,  1.9331666078107714,  0.0000000000000000},
      {3.5138838209209537,  1.9112375361605682,  0.0000000000000000},
      {3.5257629797918466,  1.8892336644711265,  0.0000000000000000},
      {3.5375044109072844,  1.8671558514322675,  0.0000000000000000},
      {3.5491076533971371,  1.8450049586412289,  0.0000000000000000},
      {3.5605722517788494,  1.8227818505690920,  0.0000000000000000},
      {3.5718977559753253,  1.8004873945270816,  0.0000000000000000},
      {3.5830837213326250,  1.7781224606327675,  0.0000000000000000},
      {3.5941297086374409,  1.7556879217761470,  0.0000000000000000},
      {3.6050352841343729,  1.7331846535856219,  0.0000000000000000},
      {3.6158000195429763,  1.7106135343938720,  0.0000000000000000},
      {3.6264234920745952,  1.6879754452036093,  0.0000000000000000},
      {3.6369052844489973,  1.6652712696532455,  0.0000000000000000},
      {3.6472449849107855,  1.6425018939824496,  0.0000000000000000},
      {3.6574421872455867,  1.6196682069975821,  0.0000000000000000},
      {3.6674964907960343,  1.5967711000370759,  0.0000000000000000},
      {3.6774075004775355,  1.5738114669366650,  0.0000000000000000},
      {3.6871748267937998,  1.5507902039945487,  0.0000000000000000},
      {3.6967980858521794,  1.5277082099364518,  0.0000000000000000},
      {3.7062768993787834,  1.5045663858805987,  0.0000000000000000},
      {3.7156108947333450,  1.4813656353025393,  0.0000000000000000},
      {3.7247997049238979,  1.4581068639999946,  0.0000000000000000},
      {3.7338429686212473,  1.4347909800574716,  0.0000000000000000},
      {3.7427403301731537,  1.4114188938109131,  0.0000000000000000},
      {3.7514914396183787,  1.3879915178121753,  0.0000000000000000},
      {3.7600959527004463,  1.3645097667934578,  0.0000000000000000},
      {3.7685535308812090,  1.3409745576316365,  0.0000000000000000},
      {3.7768638413541789,  1.3173868093125209,  0.0000000000000000},
      {3.7850265570576642,  1.2937474428950071,  0.0000000000000000},
      {3.7930413566876195,  1.2700573814751754,  0.0000000000000000},
      {3.8009079247103550,  1.2463175501503065,  0.0000000000000000},
      {3.8086259513749328,  1.2225288759827779,  0.0000000000000000},
      {3.8161951327254156,  1.1986922879639539,  0.0000000000000000},
      {3.8236151706128343,  1.1748087169779167,  0.0000000000000000},
      {3.8308857727069525,  1.1508790957652217,  0.0000000000000000},
      {3.8380066525077954,  1.1269043588864616,  0.0000000000000000},
      {3.8449775293569779,  1.1028854426858776,  0.0000000000000000},
      {3.8517981284487410,  1.0788232852548152,  0.0000000000000000},
      {3.8584681808408474,  1.0547188263951457,  0.0000000000000000},
      {3.8649874234651618,  1.0305730075826240,  0.0000000000000000},
      {3.8713555991380701,  1.0063867719301636,  0.0000000000000000},
      {3.8775724565706176,  0.9821610641510667,  0.0000000000000000},
      {3.8836377503784654,  0.9578968305221716,  0.0000000000000000},
      {3.8895512410915591,  0.9335950188469520,  0.0000000000000000},
      {3.8953126951636263,  0.9092565784185543,  0.0000000000000000},
      {3.9009218849813996,  0.8848824599827709,  0.0000000000000000},
      {3.9063785888736220,  0.8604736157009646,  0.0000000000000000},
      {3.9116825911198303,  0.8360309991129260,  0.0000000000000000},
      {3.9168336819588836,  0.8115555650996901,  0.0000000000000000},
      {3.9218316575972838,  0.7870482698462877,  0.0000000000000000},
      {3.9266763202172434,  0.7625100708044622,  0.0000000000000000},
      {3.9313674779845336,  0.7379419266552996,  0.0000000000000000},
      {3.9359049450560848,  0.7133447972718753,  0.0000000000000000},
      {3.9402885415873738,  0.6887196436817719,  0.0000000000000000},
      {3.9445180937395450,  0.6640674280296375,  0.0000000000000000},
      {3.9485934336863382,  0.6393891135396087,  0.0000000000000000},
      {3.9525143996207368,  0.6146856644777882,  0.0000000000000000},
      {3.9562808357614241,  0.5899580461145980,  0.0000000000000000},
      {3.9598925923589636,  0.5652072246871362,  0.0000000000000000},
      {3.9633495257017839,  0.5404341673614999,  0.0000000000000000},
      {3.9666514981218857,  0.5156398421950342,  0.0000000000000000},
      {3.9697983780003510,  0.4908252180985944,  0.0000000000000000},
      {3.9727900397725868,  0.4659912647987371,  0.0000000000000000},
      {3.9756263639333582,  0.4411389527998919,  0.0000000000000000},
      {3.9783072370415553,  0.4162692533465113,  0.0000000000000000},
      {3.9808325517247498,  0.3913831383851742,  0.0000000000000000},
      {3.9832022066835000,  0.3664815805266740,  0.0000000000000000},
      {3.9854161066954212,  0.3415655530080801,  0.0000000000000000},
      {3.9874741626190220,  0.3166360296547646,  0.0000000000000000},
      {3.9893762913972912,  0.2916939848424213,  0.0000000000000000},
      {3.9911224160610734,  0.2667403934590502,  0.0000000000000000},
      {3.9927124657321738,  0.2417762308669130,  0.0000000000000000},
      {3.9941463756262356,  0.2168024728645148,  0.0000000000000000},
      {3.9954240870554178,  0.1918200956484966,  0.0000000000000000},
      {3.9965455474307414,  0.1668300757755806,  0.0000000000000000},
      {3.9975107102643852,  0.1418333901244898,  0.0000000000000000},
      {3.9983195351711589,  0.1168310158576469,  0.0000000000000000},
      {3.9989719878719550,  0.0918239303838701,  0.0000000000000000},
      {3.9994680401885399,  0.0668131113171294,  0.0000000000000000},
      {3.9998076700696785,  0.0417995364500234,  0.0000000000000000},
      {3.9999908180443557,  0.0167901175555284,  0.0000000000000000},
      {4.0000175990427600,  -0.0082093135793852, 0.0000000000000000},
      {3.9998882451786004,  -0.0331977799140798, 0.0000000000000000},
      {3.9996028713492917,  -0.0581802404789117, 0.0000000000000000},
      {3.9991614609022061,  -0.0831605728035009, 0.0000000000000000},
      {3.9985640284198531,  -0.1081378019440404, 0.0000000000000000},
      {3.9978105945756761,  -0.1331109530481416, 0.0000000000000000},
      {3.9969011861398767,  -0.1580790514009919, 0.0000000000000000},
      {3.9958358359767328,  -0.1830411224613217, 0.0000000000000000},
      {3.9946145830438899,  -0.2079961919000977, 0.0000000000000000},
      {3.9932374723908532,  -0.2329432856384512, 0.0000000000000000},
      {3.9917045551573320,  -0.2578814298858415, 0.0000000000000000},
      {3.9900158885714023,  -0.2828096511781105, 0.0000000000000000},
      {3.9881715359473393,  -0.3077269764155522, 0.0000000000000000},
      {3.9861715666832853,  -0.3326324329009862, 0.0000000000000000},
      {3.9840160562586533,  -0.3575250483777742, 0.0000000000000000},
      {3.9817050862312793,  -0.3824038510678718, 0.0000000000000000},
      {3.9792387442343666,  -0.4072678697098040, 0.0000000000000000},
      {3.9766171239731749,  -0.4321161335966786, 0.0000000000000000},
      {3.9738403252214614,  -0.4569476726141366, 0.0000000000000000},
      {3.9709084538177208,  -0.4817615172782843, 0.0000000000000000},
      {3.9678216216611517,  -0.5065566987736366, 0.0000000000000000},
      {3.9645799467074099,  -0.5313322489909803, 0.0000000000000000},
      {3.9611835529641093,  -0.5560872005652624, 0.0000000000000000},
      {3.9576325704860924,  -0.5808205869134033, 0.0000000000000000},
      {3.9539271353704817,  -0.6055314422721225, 0.0000000000000000},
      {3.9500673897514580,  -0.6302188017356928, 0.0000000000000000},
      {3.9460534817948512,  -0.6548817012937025, 0.0000000000000000},
      {3.9418855656924285,  -0.6795191778687353, 0.0000000000000000},
      {3.9375638016560339,  -0.7041302693540660, 0.0000000000000000},
      {3.9330883559114125,  -0.7287140146512772, 0.0000000000000000},
      {3.9284594006918514,  -0.7532694537078484, 0.0000000000000000},
      {3.9236771142315576,  -0.7777956275547295, 0.0000000000000000},
      {3.9187416807588216,  -0.8022915783438215, 0.0000000000000000},
      {3.9136532904889276,  -0.8267563493854758, 0.0000000000000000},
      {3.9084121396168534,  -0.8511889851858918, 0.0000000000000000},
      {3.9030184303096984,  -0.8755885314845068, 0.0000000000000000},
      {3.8974723706989414,  -0.8999540352913158, 0.0000000000000000},
      {3.8917741748723831,  -0.9242845449241608, 0.0000000000000000},
      {3.8859240628659339,  -0.9485791100459484, 0.0000000000000000},
      {3.8799222606551202,  -0.9728367817018317, 0.0000000000000000},
      {3.8737690001463698,  -0.9970566123563327, 0.0000000000000000},
      {3.8674645191680876,  -1.0212376559304088, 0.0000000000000000},
      {3.8610090614614614,  -1.0453789678384726, 0.0000000000000000},
      {3.8544028766710579,  -1.0694796050253232, 0.0000000000000000},
      {3.8476462203352124,  -1.0935386260030644, 0.0000000000000000},
      {3.8407393538761334,  -1.1175550908879244, 0.0000000000000000},
      {3.8336825445898226,  -1.1415280614370313, 0.0000000000000000},
      {3.8264760656357435,  -1.1654566010851182, 0.0000000000000000},
      {3.8191201960262768,  -1.1893397749811614, 0.0000000000000000},
      {3.8116152206159191,  -1.2131766500249761, 0.0000000000000000},
      {3.8039614300902915,  -1.2369662949036853, 0.0000000000000000},
      {3.7961591209548926,  -1.2607077801282083, 0.0000000000000000},
      {3.7882085955236264,  -1.2844001780695711, 0.0000000000000000},
      {3.7801101619071087,  -1.3080425629952637, 0.0000000000000000},
      {3.7718641340007721,  -1.3316340111053999, 0.0000000000000000},
      {3.7634708314726772,  -1.3551736005689190, 0.0000000000000000},
      {3.7549305797511732,  -1.3786604115596131, 0.0000000000000000},
      {3.7462437100122949,  -1.4020935262921452, 0.0000000000000000},
      {3.7374105591669338,  -1.4254720290579532, 0.0000000000000000},
      {3.7284314698477896,  -1.4487950062610779, 0.0000000000000000},
      {3.7193067903961223,  -1.4720615464539264, 0.0000000000000000},
      {3.7100368748482326,  -1.4952707403729253, 0.0000000000000000},
      {3.7006220829217638,  -1.5184216809741011, 0.0000000000000000},
      {3.6910627800017628,  -1.5415134634686036, 0.0000000000000000},
      {3.6813593371265139,  -1.5645451853580661, 0.0000000000000000},
      {3.6715121309731700,  -1.5875159464699706, 0.0000000000000000},
      {3.6615215438431412,  -1.6104248489928517, 0.0000000000000000},
      {3.6513879636472848,  -1.6332709975114335, 0.0000000000000000},
      {3.6411117838908575,  -1.6560534990416917, 0.0000000000000000},
      {3.6306934036582685,  -1.6787714630657684, 0.0000000000000000},
      {3.6201332275975910,  -1.7014240015668691, 0.0000000000000000},
      {3.6094316659048795,  -1.7240102290639812, 0.0000000000000000},
      {3.5985891343082494,  -1.7465292626465523, 0.0000000000000000},
      {3.5876060540517640,  -1.7689802220090449, 0.0000000000000000},
      {3.5764828518790699,  -1.7913622294853817, 0.0000000000000000},
      {3.5652199600168646,  -1.8136744100833178, 0.0000000000000000},
      {3.5538178161581158,  -1.8359158915186653, 0.0000000000000000},
      {3.5422768634450610,  -1.8580858042494730, 0.0000000000000000},
      {3.5305975504520299,  -1.8801832815100183, 0.0000000000000000},
      {3.5187803311680268,  -1.9022074593447846, 0.0000000000000000},
      {3.5068256649790999,  -1.9241574766422462, 0.0000000000000000},
      {3.4947340166505216,  -1.9460324751685913, 0.0000000000000000},
      {3.4825058563087250,  -1.9678315996013236, 0.0000000000000000},
      {3.4701416594230734,  -1.9895539975627436, 0.0000000000000000},
      {3.4576419067873778,  -2.0111988196533113, 0.0000000000000000},
      {3.4450070845012397,  -2.0327652194849062, 0.0000000000000000},
      {3.4322376839511621,  -2.0542523537139759, 0.0000000000000000},
      {3.4193342017914721,  -2.0756593820745310, 0.0000000000000000},
      {3.4062971399250226,  -2.0969854674110637, 0.0000000000000000},
      {3.3931270054837066,  -2.1182297757113107, 0.0000000000000000},
      {3.3798243108087429,  -2.1393914761389246, 0.0000000000000000},
      {3.3663895734307778,  -2.1604697410659899, 0.0000000000000000},
      {3.3528233160497818,  -2.1814637461054427, 0.0000000000000000},
      {3.3391260665147335,  -2.2023726701433355, 0.0000000000000000},
      {3.3252983578031046,  -2.2231956953710119, 0.0000000000000000},
      {3.3113407280001614,  -2.2439320073171176, 0.0000000000000000},
      {3.2972537202780305,  -2.2645807948794920, 0.0000000000000000},
      {3.2830378828746225,  -2.2851412503569435, 0.0000000000000000},
      {3.2686937690722799,  -2.3056125694808745, 0.0000000000000000},
      {3.2542219371763079,  -2.3259939514467782, 0.0000000000000000},
      {3.2396229504932550,  -2.3462845989455974, 0.0000000000000000},
      {3.2248973773090124,  -2.3664837181949685, 0.0000000000000000},
      {3.2100457908667224,  -2.3865905189702890, 0.0000000000000000},
      {3.1950687693445023,  -2.4066042146356805, 0.0000000000000000},
      {3.1799668958329432,  -2.4265240221748030, 0.0000000000000000},
      {3.1647407583124609,  -2.4463491622215052, 0.0000000000000000},
      {3.1493909496304107,  -2.4660788590903904, 0.0000000000000000},
      {3.1339180674780502,  -2.4857123408071509, 0.0000000000000000},
      {3.1183227143672774,  -2.5052488391388601, 0.0000000000000000},
      {3.1026054976072186,  -2.5246875896240231, 0.0000000000000000},
      {3.0867670292805918,  -2.5440278316025524, 0.0000000000000000},
      {3.0708079262199108,  -2.5632688082455584, 0.0000000000000000},
      {3.0547288099834802,  -2.5824097665849979, 0.0000000000000000},
      {3.0385303068312290,  -2.6014499575431724, 0.0000000000000000},
      {3.0222130477003448,  -2.6203886359620885, 0.0000000000000000},
      {3.0057776681807211,  -2.6392250606326391, 0.0000000000000000},
      {2.9892248084902535,  -2.6579584943236494, 0.0000000000000000},
      {2.9725551134498942,  -2.6765882038107676, 0.0000000000000000},
      {2.9557692324585956,  -2.6951134599052011, 0.0000000000000000},
      {2.9388678194680375,  -2.7135335374822720, 0.0000000000000000},
      {2.9218515329571622,  -2.7318477155098533, 0.0000000000000000},
      {2.9047210359065749,  -2.7500552770766036, 0.0000000000000000},
      {2.8874769957727304,  -2.7681555094200880, 0.0000000000000000},
      {2.8701200844619623,  -2.7861477039546814, 0.0000000000000000},
      {2.8526509783043412,  -2.8040311562993727, 0.0000000000000000},
      {2.8350703580273349,  -2.8218051663053423, 0.0000000000000000},
      {2.8173789087293342,  -2.8394690380834220, 0.0000000000000000},
      {2.7995773198529790,  -2.8570220800313639, 0.0000000000000000},
      {2.7816662851583236,  -2.8744636048609511, 0.0000000000000000},
      {2.7636465026958339,  -2.8917929296249469, 0.0000000000000000},
      {2.7455186747792046,  -2.9090093757438487, 0.0000000000000000},
      {2.7272835079580480,  -2.9261122690325059, 0.0000000000000000},
      {2.7089417129903479,  -2.9431009397265404, 0.0000000000000000},
      {2.6904940048148371,  -2.9599747225086190, 0.0000000000000000},
      {2.6719411025231139,  -2.9767329565345131, 0.0000000000000000},
      {2.6532837293316951,  -2.9933749854590328, 0.0000000000000000},
      {2.6345226125538184,  -3.0099001574617539, 0.0000000000000000},
      {2.6156584835711429,  -3.0263078252725739, 0.0000000000000000},
      {2.5966920778052849,  -3.0425973461970899, 0.0000000000000000},
      {2.5776241346891364,  -3.0587680821418211, 0.0000000000000000},
      {2.5584553976381441,  -3.0748193996391961, 0.0000000000000000},
      {2.5391866140212764,  -3.0907506698724454, 0.0000000000000000},
      {2.5198185351319888,  -3.1065612687002147, 0.0000000000000000},
      {2.5003519161589480,  -3.1222505766810693, 0.0000000000000000},
      {2.4807875161565778,  -3.1378179790978065, 0.0000000000000000},
      {2.4611260980155851,  -3.1532628659815147, 0.0000000000000000},
      {2.4413684284331527,  -3.1685846321355728, 0.0000000000000000},
      {2.4215152778831484,  -3.1837826771593218, 0.0000000000000000},
      {2.4015674205860913,  -3.1988564054716710, 0.0000000000000000},
      {2.3815256344789928,  -3.2138052263344274, 0.0000000000000000},
      {2.3613907011850515,  -3.2286285538755077, 0.0000000000000000},
      {2.3411634059832283,  -3.2433258071118898, 0.0000000000000000},
      {2.3208445377776461,  -3.2578964099724326, 0.0000000000000000},
      {2.3004348890668513,  -3.2723397913204835, 0.0000000000000000},
      {2.2799352559129500,  -3.2866553849762727, 0.0000000000000000},
      {2.2593464379106001,  -3.3008426297391611, 0.0000000000000000},
      {2.2386692381558535,  -3.3149009694096212, 0.0000000000000000},
      {2.2179044632148885,  -3.3288298528111229, 0.0000000000000000},
      {2.1970529230925449,  -3.3426287338117255, 0.0000000000000000},
      {2.1761154312008157,  -3.3562970713455345, 0.0000000000000000},
      {2.1550928043271269,  -3.3698343294339375, 0.0000000000000000},
      {2.1339858626025232,  -3.3832399772066437, 0.0000000000000000},
      {2.1127954294697067,  -3.3965134889225306, 0.0000000000000000},
      {2.0915223316509617,  -3.4096543439902880, 0.0000000000000000},
      {2.0701673991159355,  -3.4226620269888475, 0.0000000000000000},
      {2.0487314650493023,  -3.4355360276876454, 0.0000000000000000},
      {2.0272153658182912,  -3.4482758410666348, 0.0000000000000000},
      {2.0056199409401074,  -3.4608809673361294, 0.0000000000000000},
      {1.9839460330491927,  -3.4733509119564490, 0.0000000000000000},
      {1.9621944878644273,  -3.4856851856573168, 0.0000000000000000},
      {1.9403661541561403,  -3.4978833044571012, 0.0000000000000000},
      {1.9184618837130261,  -3.5099447896818234, 0.0000000000000000},
      {1.8964825313090081,  -3.5218691679839491, 0.0000000000000000},
      {1.8744289546698296,  -3.5336559713610258, 0.0000000000000000},
      {1.8523020144397249,  -3.5453047371740181, 0.0000000000000000},
      {1.8301025741478061,  -3.5568150081655370, 0.0000000000000000},
      {1.8078315001744365,  -3.5681863324777821, 0.0000000000000000},
      {1.7854896617174698,  -3.5794182636703149, 0.0000000000000000},
      {1.7630779307583371,  -3.5905103607375994, 0.0000000000000000},
      {1.7405971820281028,  -3.6014621881263515, 0.0000000000000000},
      {1.7180482929733392,  -3.6122733157526437, 0.0000000000000000},
      {1.6954321437219380,  -3.6229433190188303, 0.0000000000000000},
      {1.6727496170487932,  -3.6334717788302449, 0.0000000000000000},
      {1.6500015983414122,  -3.6438582816116645, 0.0000000000000000},
      {1.6271889755653588,  -3.6541024193235998, 0.0000000000000000},
      {1.6043126392296982,  -3.6642037894783268, 0.0000000000000000},
      {1.5813734823522296,  -3.6741619951557261, 0.0000000000000000},
      {1.5583724004246950,  -3.6839766450189129, 0.0000000000000000},
      {1.5353102913778875,  -3.6936473533295984, 0.0000000000000000},
      {1.5121880555466007,  -3.7031737399633147, 0.0000000000000000},
      {1.4890065956345828,  -3.7125554304243460, 0.0000000000000000},
      {1.4657668166792872,  -3.7217920558604769, 0.0000000000000000},
      {1.4424696260166421,  -3.7308832530775176, 0.0000000000000000},
      {1.4191159332456300,  -3.7398286645535990, 0.0000000000000000},
      {1.3957066501928621,  -3.7486279384532493, 0.0000000000000000},
      {1.3722426908769951,  -3.7572807286412591, 0.0000000000000000},
      {1.3487249714731253,  -3.7657866946963017, 0.0000000000000000},
      {1.3251544102770183,  -3.7741455019243615, 0.0000000000000000},
      {1.3015319276693751,  -3.7823568213719070, 0.0000000000000000},
      {1.2778584460798763,  -3.7904203298388564, 0.0000000000000000},
      {1.2541348899512588,  -3.7983357098913242, 0.0000000000000000},
      {1.2303621857032474,  -3.8061026498741213, 0.0000000000000000},
      {1.2065412616964393,  -3.8137208439230590, 0.0000000000000000},
      {1.1826730481961061,  -3.8211899919769960, 0.0000000000000000},
      {1.1587584773359110,  -3.8285097997896793, 0.0000000000000000},
      {1.1347984830815518,  -3.8356799789413616, 0.0000000000000000},
      {1.1107940011943831,  -3.8427002468501592, 0.0000000000000000},
      {1.0867459691948667,  -3.8495703267832289, 0.0000000000000000},
      {1.0626553263260345,  -3.8562899478676815, 0.0000000000000000},
      {1.0385230135169032,  -3.8628588451012664, 0.0000000000000000},
      {1.0143499733456924,  -3.8692767593628625, 0.0000000000000000},
      {0.9901371500031475,  -3.8755434374226976, 0.0000000000000000},
      {0.9658854892556840,  -3.8816586319523472, 0.0000000000000000},
      {0.9415959384084784,  -3.8876221015345371, 0.0000000000000000},
      {0.9172694462685786,  -3.8934336106726644, 0.0000000000000000},
      {0.8929069631078441,  -3.8990929298001218, 0.0000000000000000},
      {0.8685094406259303,  -3.9045998352893765, 0.0000000000000000},
      {0.8440778319131444,  -3.9099541094608181, 0.0000000000000000},
      {0.8196130914132600,  -3.9151555405913960, 0.0000000000000000},
      {0.7951161748863419,  -3.9202039229229690, 0.0000000000000000},
      {0.7705880393714186,  -3.9250990566704891, 0.0000000000000000},
      {0.7460296431491659,  -3.9298407480299100, 0.0000000000000000},
      {0.7214419457045638,  -3.9344288091858650, 0.0000000000000000},
      {0.6968259076894068,  -3.9388630583191269, 0.0000000000000000},
      {0.6721824908849096,  -3.9431433196138341, 0.0000000000000000},
      {0.6475126581641352,  -3.9472694232644416, 0.0000000000000000},
      {0.6228173734544611,  -3.9512412054825097, 0.0000000000000000},
      {0.5980976016999715,  -3.9550585085031864, 0.0000000000000000},
      {0.5733543088238475,  -3.9587211805914970, 0.0000000000000000},
      {0.5485884616906243,  -3.9622290760483878, 0.0000000000000000},
      {0.5238010280685562,  -3.9655820552165197, 0.0000000000000000},
      {0.4989929765917977,  -3.9687799844858613, 0.0000000000000000},
      {0.4741652767226729,  -3.9718227362989955, 0.0000000000000000},
      {0.4493188987138140,  -3.9747101891562355, 0.0000000000000000},
      {0.4244548135703401,  -3.9774422276204886, 0.0000000000000000},
      {0.3995739930119702,  -3.9800187423218052, 0.0000000000000000},
      {0.3746774094351157,  -3.9824396299621232, 0.0000000000000000},
      {0.3497660358749552,  -3.9847047933179822, 0.0000000000000000},
      {0.3248408459674651,  -3.9868141412498601, 0.0000000000000000},
      {0.2999028139114266,  -3.9887675886855876, 0.0000000000000000},
      {0.2749529144305401,  -3.9905650566994071, 0.0000000000000000},
      {0.2499921227348549,  -3.9922064722328745, 0.0000000000000000},
      {0.2250214144848797,  -3.9936917691514999, 0.0000000000000000},
      {0.2000417657453527,  -3.9950208843149024, 0.0000000000000000},
      {0.1750541529777414,  -3.9961937722560812, 0.0000000000000000},
      {0.1500595528879815,  -3.9972103504086052, 0.0000000000000000},
      {0.1250589428144958,  -3.9980707035336782, 0.0000000000000000},
      {0.1000532990996446,  -3.9987743207907567, 0.0000000000000000},
      {0.0750436029873226,  -3.9993229430610500, 0.0000000000000000},
      {0.0500308184321822,  -3.9997099365079656, 0.0000000000000000},
      {0.0250159747368822,  -3.9999599513344739, 0.0000000000000000},
      {0.0083386113996283,  -3.9999739250855604, 0.0000000000000000},
      {0.0000000000000000,  -4.0000000000000000, 0.0000000000000000},
    };
    double weights[] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double ctrlpt_tol = SPAresabs;
    int num_knots = 1414;
    double knots[] = {0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.0250019119901612,  0.0500037015124971,  0.0750053686098482,  0.1000069133226407,  0.1250083356888899,  0.1500096357442063,  0.1750108135217959,
                      0.2000118690524623,  0.2250128023646115,  0.2500136134842527,  0.2750143024349988,  0.3000148692380740,  0.3250153139123090,  0.3500156364741455,  0.3750158369376369,  0.4000159153144486,  0.4250158716138633,  0.4500157058427746,
                      0.4750154180056962,  0.5000150081047519,  0.5250144761396848,  0.5500138221078567,  0.5750130460042346,  0.6000121478214153,  0.6250111275495984,  0.6500099851766056,  0.6750087206878690,  0.7000073340664301,  0.7250058252929455,
                      0.7500041943456779,  0.7750024412005008,  0.8000005658308912,  0.8249985682079288,  0.8499964483003000,  0.8749942060742861,  0.8999918414937638,  0.9249893545202064,  0.9499867451126798,  0.9749840132278303,  0.9999811588198978,
                      1.0249781818406949,  1.0499750822396150,  1.0749718599636240,  1.0999685149572556,  1.1249650471626089,  1.1499614565193437,  1.1749577429646734,  1.1999539064333629,  1.2249499468577221,  1.2499458641676011,  1.2749416582903812,
                      1.2999373291509775,  1.3249328766718251,  1.3499283007728775,  1.3749236013715957,  1.3999187783829463,  1.4249138317193941,  1.4499087612908905,  1.4749035670048734,  1.4998982487662551,  1.5248928064774179,  1.5498872400381989,
                      1.5748815493458939,  1.5998757342952403,  1.6248697947784105,  1.6498637306850050,  1.6748575419020435,  1.6998512283139526,  1.7248447898025629,  1.7498382262470895,  1.7748315375241344,  1.7998247235076672,  1.8248177840690161,
                      1.8498107190768651,  1.8748035283972320,  1.8997962118934670,  1.9247887694262376,  1.9497812008535143,  1.9747735060305669,  1.9997656848099430,  2.0247577370414644,  2.0497496625722098,  2.0747414612465054,  2.0997331329059095,
                      2.1247246773891999,  2.1497160945323603,  2.1747073841685673,  2.1996985461281793,  2.2246895802387194,  2.2496804863248578,  2.2746712642084068,  2.2996619137082925,  2.3246524346405537,  2.3496428268183163,  2.3746330900517791,
                      2.3996232241482072,  2.4246132289119000,  2.4496031041441872,  2.4745928496434066,  2.4995824652048890,  2.5245719506209383,  2.5495613056808151,  2.5745505301707206,  2.5995396238737745,  2.6245285865699977,  2.6495174180362957,
                      2.6745061180464362,  2.6994946863710299,  2.7244831227775150,  2.7494714270301293,  2.7744595988898930,  2.7994476381145916,  2.8244355444587494,  2.8494233176736117,  2.8744109575071177,  2.8993984637038821,  2.9243858360051749,
                      2.9493730741488915,  2.9743601778695354,  2.9993471468981907,  3.0243339809624992,  3.0493206797866370,  3.0743072430912881,  3.0992936705936169,  3.1242799620072494,  3.1492661170422389,  3.1742521354050459,  3.1992380167985086,
                      3.2242237609218143,  3.2492093674704736,  3.2741948361362918,  3.2991801666073397,  3.3241653585679254,  3.3491504116985631,  3.3741353256759443,  3.3991201001729099,  3.4241047348584148,  3.4490892293975000,  3.4740735834512568,
                      3.4990577966768006,  3.5240418687272306,  3.5490257992516043,  3.5740095878948988,  3.5990070542736925,  3.6240229170646825,  3.6490386368134908,  3.6740542138889207,  3.6990696486555152,  3.7240849414736510,  3.7491000926995675,
                      3.7741151026854061,  3.7991299717792413,  3.8241447003251152,  3.8491592886630723,  3.8741737371291904,  3.8991880460556128,  3.9242022157705803,  3.9492162465984633,  3.9742301388597894,  3.9992438928712790,  4.0242575089458708,
                      4.0492709873927524,  4.0742843285173889,  4.0992975326215513,  4.1243106000033478,  4.1493235309572460,  4.1743363257741040,  4.1993489847411940,  4.2243615081422332,  4.2493738962574064,  4.2743861493633908,  4.2993982677333848,
                      4.3244102516371301,  4.3494221013409344,  4.3744338171077004,  4.3994453991969467,  4.4244568478648301,  4.4494681633641706,  4.4744793459444709,  4.4994903958519439,  4.5245013133295267,  4.5495120986169111,  4.5745227519505587,
                      4.5995332735637229,  4.6245436636864703,  4.6495539225456994,  4.6745640503651638,  4.6995740473654868,  4.7245839137641843,  4.7495936497756821,  4.7746032556113356,  4.7996127314794466,  4.8246220775852811,  4.8496312941310880,
                      4.8746403813161168,  4.8996493393366354,  4.9246581683859425,  4.9496668686543890,  4.9746754403293920,  4.9996838835954502,  5.0246921986341597,  5.0497003856242317,  5.0747084447415043,  5.0997163761589590,  5.1247241800467345,
                      5.1497318565721431,  5.1747394058996807,  5.1997468281910448,  5.2247541236051429,  5.2497612922981123,  5.2747683344233272,  5.2997752501314146,  5.3247820395702661,  5.3497887028850490,  5.3747952402182202,  5.3998016517095353,
                      5.4248079374960634,  5.4498140977121965,  5.4748201324896595,  5.4998260419575207,  5.5248318262422078,  5.5498374854675125,  5.5748430197546011,  5.5998484292220247,  5.6248537139857318,  5.6498588741590758,  5.6748639098528217,
                      5.6998688211751567,  5.7248736082317038,  5.7498782711255219,  5.7748828099571190,  5.7998872248244613,  5.8248915158229773,  5.8498956830455677,  5.8748997265826137,  5.8999036465219818,  5.9249074429490340,  5.9499111159466311,
                      5.9749146655951408,  5.9999180919724466,  6.0249213951539486,  6.0499245752125770,  6.0749276322187891,  6.0999305662405821,  6.1249333773434937,  6.1499360655906115,  6.1749386310425773,  6.1999410737575849,  6.2249433937913965,
                      6.2499455911973376,  6.2749476660263062,  6.2999496183267736,  6.3249514481447910,  6.3499531555239948,  6.3749547405056024,  6.3999562031284229,  6.4249575434288575,  6.4499587614409037,  6.4749598571961560,  6.4999608307238068,
                      6.5249616820506553,  6.5499624112011041,  6.5749630181971606,  6.5999635030584445,  6.6249638658021830,  6.6499641064432158,  6.6749642249939916,  6.6999642214645814,  6.7249640958626626,  6.7499638481935316,  6.7749634784600987,
                      6.7999629866628908,  6.8249623728000515,  6.8499616368673388,  6.8749607788581288,  6.8999597987634100,  6.9249586965717871,  6.9499574722694764,  6.9749561258403068,  6.9999546572657207,  7.0249530665247688,  7.0499513535941123,
                      7.0749495184480136,  7.0999475610583449,  7.1249454813945796,  7.1499432794237885,  7.1749409551106424,  7.1999385084174055,  7.2249359393039354,  7.2499332477276770,  7.2749304336436591,  7.2999274970044947,  7.3249244377603748,
                      7.3499212558590630,  7.3749179512458953,  7.3999145238637727,  7.4249109736531587,  7.4499073005520691,  7.4749035044960772,  7.4998995854183015,  7.5248955432494018,  7.5498913779175725,  7.5748870893485414,  7.5998826774655592,
                      7.6248781421893970,  7.6498734834383360,  7.6748687011281662,  7.6998637951721758,  7.7248587654811427,  7.7498536119633341,  7.7748483345244948,  7.7998429330678389,  7.8248374074940426,  7.8498317577012404,  7.8748259835850103,
                      7.8998200850383702,  7.9248140619517686,  7.9498079142130740,  7.9748016417075700,  7.9997952443179408,  8.0247887219242617,  8.0497820744039981,  8.0747753016319859,  8.0997684034804251,  8.1247613798188691,  8.1497542305142137,
                      8.1747469554306900,  8.1997395544298488,  8.2247320273705498,  8.2497243741089505,  8.2747165944984982,  8.2997086883899129,  8.3247006556311796,  8.3496924960675276,  8.3746842095414280,  8.3996757958925752,  8.4246672549578747,
                      8.4496585865714291,  8.4746497905645253,  8.4996408667656205,  8.5246318150003244,  8.5496226350913922,  8.5746133268587013,  8.5996038901192424,  8.6245943246871022,  8.6495846303734449,  8.6745748069865005,  8.6995648543315482,
                      8.7245547722108956,  8.7495445604238675,  8.7745342187667870,  8.7995237470329535,  8.8245131450126326,  8.8495024124930346,  8.8744915492582948,  8.8994805550894558,  8.9244694297644518,  8.9494581730580833,  8.9744467847420033,
                      8.9994352645846956,  9.0244236123514536,  9.0494118278043594,  9.0743999107022653,  9.0993878608007694,  9.1243756778521981,  9.1493633616055821,  9.1743509118066342,  9.1993383281977259,  9.2243256105178659,  9.2493127585026773,
                      9.2742997718843707,  9.2992866503917231,  9.3242733937500546,  9.3492600016812002,  9.3742464739034865,  9.3992328101317071,  9.4242190100770937,  9.4492050734472919,  9.4741909999463338,  9.4991767892746122,  9.5241624411288495,
                      9.5491479552020735,  9.5741333311835888,  9.5991185687589429,  9.6241036676099032,  9.6490886274144216,  9.6740734478466113,  9.6990581285767075,  9.7240426692710429,  9.7490270695920138,  9.7740113291980446,  9.7989954477435628,
                      9.8239794248789565,  9.8489632602505512,  9.8739503555293204,  9.8989662654712411,  9.9239820322487429,  9.9489976562319900,  9.9740131377869066,  9.9990284772752371,  10.0240436750545783, 10.0490587314784161, 10.0740736468961583,
                      10.0990884216531729, 10.1241030560908136, 10.1491175505464604, 10.1741319053535477, 10.1991461208415970, 10.2241601973362517, 10.2491741351592971, 10.2741879346287046, 10.2992015960586549, 10.3242151197595646, 10.3492285060381217,
                      10.3742417551973105, 10.3992548675364400, 10.4242678433511742, 10.4492806829335549, 10.4742933865720307, 10.4993059545514882, 10.5243183871532686, 10.5493306846552013, 10.5743428473316268, 10.5993548754534235, 10.6243667692880237,
                      10.6493785290994509, 10.6743901551483322, 10.6994016476919285, 10.7244130069841557, 10.7494242332756063, 10.7744353268135722, 10.7994462878420681, 10.8244571166018488, 10.8494678133304365, 10.8744783782621397, 10.8994888116280713,
                      10.9244991136561698, 10.9495092845712207, 10.9745193245948762, 10.9995292339456725, 11.0245390128390497, 11.0495486614873712, 11.0745581800999418, 11.0995675688830229, 11.1245768280398583, 11.1495859577706806, 11.1745949582727349,
                      11.1996038297402993, 11.2246125723646912, 11.2496211863342879, 11.2746296718345516, 11.2996380290480296, 11.3246462581543810, 11.3496543593303869, 11.3746623327499687, 11.3996701785841985, 11.4246778970013168, 11.4496854881667449,
                      11.4746929522430978, 11.4997002893902014, 11.5247074997651033, 11.5497145835220856, 11.5747215408126767, 11.5997283717856678, 11.6247350765871218, 11.6497416553603852, 11.6747481082461029, 11.6997544353822249, 11.7247606369040227,
                      11.7497667129440977, 11.7747726636323939, 11.7997784890962052, 11.8247841894601891, 11.8497897648463741, 11.8747952153741707, 11.8998005411603849, 11.9248057423192222, 11.9498108189622965, 11.9748157711986458, 11.9998205991347326,
                      12.0248253028744596, 12.0498298825191732, 12.0748343381676762, 12.0998386699162310, 12.1248428778585691, 12.1498469620858991, 12.1748509226869146, 12.1998547597478009, 12.2248584733522421, 12.2498620635814230, 12.2748655305140471,
                      12.2998688742263305, 12.3248720947920116, 12.3498751922823651, 12.3748781667661962, 12.3998810183098502, 12.4248837469772209, 12.4498863528297559, 12.4748888359264516, 12.4998911963238708, 12.5248934340761409, 12.5498955492349573,
                      12.5748975418495910, 12.5998994119668879, 12.6249011596312783, 12.6499027848847767, 12.6749042877669815, 12.6999056683150897, 12.7249069265638859, 12.7499080625457566, 12.7749090762906850, 12.7999099678262578, 12.8249107371776638,
                      12.8499113843677009, 12.8749119094167721, 12.8999123123428934, 12.9249125931616895, 12.9499127518863961, 12.9749127885278668, 12.9999127030945640, 13.0249124955925684, 13.0499121660255781, 13.0749117143949025, 13.0999111406994704,
                      13.1249104449358249, 13.1499096270981237, 13.1749086871781422, 13.1999076251652685, 13.2249064410465067, 13.2499051348064718, 13.2749037064273914, 13.2999021558891020, 13.3249004831690510, 13.3498986882422930, 13.3748967710814846,
                      13.3998947316568895, 13.4248925699363699, 13.4498902858853864, 13.4748878794669942, 13.4998853506418452, 13.5248826993681757, 13.5498799256018128, 13.5748770292961645, 13.5998740104022176, 13.6248708688685376, 13.6498676046412566,
                      13.6748642176640782, 13.6998607078782673, 13.7248570752226495, 13.7498533196336012, 13.7748494410450473, 13.7998454393884575, 13.8248413145928399, 13.8498370665847332, 13.8748326952882053, 13.8998282006248424, 13.9248235825137456,
                      13.9498188408715258, 13.9748139756122942, 13.9998089866476594, 14.0248038738867127, 14.0497986372360284, 14.0747932765996548, 14.0997877918791072, 14.1247821829733535, 14.1497764497788161, 14.1747705921893559, 14.1997646100962669,
                      14.2247585033882693, 14.2497522719514969, 14.2747459156694898, 14.2997394344231843, 14.3247328280909052, 14.3497260965483537, 14.3747192396685985, 14.3997122573220668, 14.4247051493765301, 14.4496979156970955, 14.4746905561461983,
                      14.4996830705835844, 14.5246754588663034, 14.5496677208486940, 14.5746598563823753, 14.5996518653162326, 14.6246437474964051, 14.6496355027662730, 14.6746271309664458, 14.6996186319347473, 14.7246100055062037, 14.7496012515130310,
                      14.7745923697846173, 14.7995833601475137, 14.8245742224254151, 14.8495649564391474, 14.8745555620066519, 14.8995460389429741, 14.9245363870602397, 14.9495266061676482, 14.9745166960714506, 14.9995066565749351, 15.0244964874784088,
                      15.0494861885791842, 15.0744757596715591, 15.0994652005467973, 15.1244545109931181, 15.1494436907956711, 15.1744327397365169, 15.1994216575946144, 15.2244104441457999, 15.2493990991627637, 15.2743876224150323, 15.2993760136689527,
                      15.3243642726876654, 15.3493523992310887, 15.3743403930558937, 15.3993282539154883, 15.4243159815599871, 15.4493035757361969, 15.4742910361875925, 15.4992783626542909, 15.5242655548730308, 15.5492526125771491, 15.5742395354965577,
                      15.5992263233577155, 15.6242129758836068, 15.6491994927937146, 15.6741858738039994, 15.6991721186268656, 15.7241582269711433, 15.7491441985420586, 15.7741300330412013, 15.7991157301665073, 15.8241012896122228, 15.8490867110688800,
                      15.8740719942232662, 15.8990571387583959, 15.9240421443534803, 15.9490270106838992, 15.9740117374211668, 15.9989963242329036, 16.0239807707828028, 16.0489650767306031, 16.0739492417320484, 16.0989332654388626, 16.1239171474987089,
                      16.1489008875551612, 16.1490035092445723, 16.1490562156771631, 16.1494468367272646, 16.1502280709309574, 16.1517905077720094, 16.1549152550483939, 16.1611642446417463, 16.1736602068924427, 16.1986440865129850, 16.2236281077865883,
                      16.2486122703608515, 16.2735965738874242, 16.2985810180219843, 16.3235656024241997, 16.3485503267576959, 16.3735351906900277, 16.3985201938926437, 16.4235053360408543, 16.4484906168138068, 16.4734760358944499, 16.4984615929695053,
                      16.5234472877294429, 16.5484331198684451, 16.5734190890843820, 16.5984051950787865, 16.6233914375568190, 16.6483778162272458, 16.6733643308024106, 16.6983509809982138, 16.7233377665340797, 16.7483246871329321, 16.7733117425211695,
                      16.7982989324286436, 16.8232862565886343, 16.8482737147378216, 16.8732613066162642, 16.8982490319673779, 16.9232368905379147, 16.9482248820779340, 16.9732130063407851, 16.9982012630830823, 17.0231896520646906, 17.0481781730486937,
                      17.0731668258013798, 17.0981556100922276, 17.1231445256938706, 17.1481335723820898, 17.1731227499357928, 17.1981120581369851, 17.2231014967707665, 17.2480910656252995, 17.2730807644917945, 17.2980705931645034, 17.3230605514406832,
                      17.3480506391205900, 17.3730408560074601, 17.3980312019074965, 17.4230216766298440, 17.4480122799865818, 17.4730030117927022, 17.4979938718661003, 17.5229848600275488, 17.5479759761006981, 17.5729672199120479, 17.5979585912909364,
                      17.6229500900695299, 17.6479417160828085, 17.6729334691685480, 17.6979253491673099, 17.7229173559224265, 17.7479094892799907, 17.7729017490888417, 17.7978941352005506, 17.8228866474694065, 17.8478792857524162, 17.8728720499092795,
                      17.8978649398023819, 17.9228579552967879, 17.9478510962602229, 17.9728443625630661, 17.9978377540783434, 18.0228312706817100, 18.0478249122514462, 18.0728186786684404, 18.0978125698161918, 18.1228065855807898, 18.1478007258509066,
                      18.1727949905177937, 18.1977893794752674, 18.2227838926197059, 18.2477785298500379, 18.2727732910677325, 18.2977681761767919, 18.3227631850837476, 18.3477583176976502, 18.3727535739300656, 18.3977489536950607, 18.4227444569092000,
                      18.4477400834915457, 18.4727358333636396, 18.4977317064495068, 18.5227277026756454, 18.5477238219710188, 18.5727200642670560, 18.5977164294976411, 18.6227129175991060, 18.6477095285102337, 18.6727062621722517, 18.6977031185288141,
                      18.7227000975260154, 18.7476971991123840, 18.7726944232388604, 18.7976917698588082, 18.8226892389280138, 18.8476868304046796, 18.8726845442494060, 18.8976823804252128, 18.9226803388975178, 18.9476784196341441, 18.9726766226053094,
                      18.9976749477836329, 19.0226733951441282, 19.0476719646642003, 19.0726706563236412, 19.0976694701046412, 19.1226684059917744, 19.1476674639720024, 19.1726666440346740, 19.1976659461715222, 19.2226653703766637, 19.2476649166466025,
                      19.2726645849802232, 19.2976643753787975, 19.3226642878459813, 19.3476643223878106, 19.3726644790127125, 19.3976647577314978, 19.4226651585573578, 19.4476656815058817, 19.4726663265950393, 19.4976670938451981, 19.5226679832791099,
                      19.5476689949219242, 19.5726701288011853, 19.5976713849468354, 19.6226727633912219, 19.6476742641690834, 19.6726758873175775, 19.6976776328762639, 19.7226795008871143, 19.7476814913945162, 19.7726836044452767, 19.7976858400886222,
                      19.8226881983762055, 19.8476906793621168, 19.8726932831028691, 19.8976960096574267, 19.9226988590871876, 19.9477018314560048, 19.9727049268301826, 19.9977081452784873, 20.0227114868721436, 20.0477149516848527, 20.0727185397927883,
                      20.0977222512746074, 20.1227260862114541, 20.1477300446869698, 20.1727341267872973, 20.1977383326010873, 20.2227426622195026, 20.2477471157362316, 20.2727516932474963, 20.2977563948520547, 20.3227612206512056, 20.3477661707488124,
                      20.3727712452512897, 20.3977764442676346, 20.4227817679094130, 20.4477872162907879, 20.4727927895285227, 20.4977984877419779, 20.5228043110531395, 20.5478102595866225, 20.5728163334696710, 20.5978225328321862, 20.6228288578067200,
                      20.6478353085284994, 20.6728418851354299, 20.6978485877681102, 20.7228554165698391, 20.7478623716866331, 20.7728694532672371, 20.7978766614631319, 20.8228839964285513, 20.8478914583204933, 20.8728990472987377, 20.8979067635258531,
                      20.9229146071672112, 20.9479225783910046, 20.9729306773682573, 20.9979389042728393, 21.0229472592814801, 21.0479557425737909, 21.0729643543322744, 21.0979730947423363, 21.1229819639923058, 21.1479909622734539, 21.1730000897800004,
                      21.1980093467091422, 21.2230187332610640, 21.2480282496389492, 21.2730378960490150, 21.2980476727005090, 21.3230575798057451, 21.3480676175801065, 21.3730777862420815, 21.3980880860132636, 21.4230985171183868, 21.4481090797853362,
                      21.4731197742451663, 21.4981306007321322, 21.5231415594837010, 21.5481526507405725, 21.5731638747467045, 21.5981752317493303, 21.6231867219989873, 21.6481983457495346, 21.6732101032581745, 21.6982219947854773, 21.7232340205954060,
                      21.7482461809553378, 21.7732584761360890, 21.7982709064119362, 21.8232834720606519, 21.8482961733635186, 21.8733090106053609, 21.8983219840745633, 21.9233350940631091, 21.9483483408665982, 21.9733617247842794, 21.9983752461190676,
                      22.0233889051775904, 22.0484027022702023, 22.0734166377110164, 22.0984307118179366, 22.1234449249126861, 22.1484592773208391, 22.1734737693718529, 22.1984884013990929, 22.2235031737398678, 22.2485180867354657, 22.2735331407311854,
                      22.2985483360763652, 22.3235636731244185, 22.3485791522328761, 22.3735947737634042, 22.3986105380818579, 22.4236264455583303, 22.4486139091171388, 22.4735977420463513, 22.4985817167454876, 22.5235658328607968, 22.5485500900425997,
                      22.5735344879452526, 22.5985190262271161, 22.6235037045505152, 22.6484885225817152, 22.6734734799908892, 22.6984585764520759, 22.7234438116431647, 22.7484291852458611, 22.7734146969456468, 22.7984003464317588, 22.8233861333971610,
                      22.8483720575385156, 22.8733581185561476, 22.8983443161540308, 22.9233306500397482, 22.9483171199244715, 22.9733037255229320, 22.9982904665533923, 23.0232773427376323, 23.0482643538009100, 23.0732514994719438, 23.0982387794828838,
                      23.1232261935692982, 23.1482137414701334, 23.1732014229277077, 23.1981892376876715, 23.2231771854990008, 23.2481652661139648, 23.2731534792881085, 23.2981418247802274, 23.3231303023523466, 23.3481189117697063, 23.3731076528007335,
                      23.3980965252170279, 23.4230855287933331, 23.4480746633075334, 23.4730639285406149, 23.4980533242766647, 23.5230428503028364, 23.5480325064093421, 23.5730222923894317, 23.5980122080393784, 23.6230022531584538, 23.6479924275489104,
                      23.6729827310159813, 23.6979731633678412, 23.7229637244156102, 23.7479544139733214, 23.7729452318579142, 23.7979361778892198, 23.8229272518899400, 23.8479184536856401, 23.8729097831047241, 23.8979012399784310, 23.9228928241408205,
                      23.9478845354287415, 23.9728763736818458, 23.9978683387425562, 24.0228604304560562, 24.0478526486702826, 24.0728449932359077, 24.0978374640063286, 24.1228300608376607, 24.1478227835887154, 24.1728156321210008, 24.1978086062986968,
                      24.2228017059886547, 24.2477949310603833, 24.2727882813860383, 24.2977817568404113, 24.3227753573009196, 24.3477690826475914, 24.3727629327630702, 24.3977569075325960, 24.4227510068439884, 24.4477452305876568, 24.4727395786565687,
                      24.4977340509462636, 24.5227286473548283, 24.5477233677829005, 24.5727182121336476, 24.5977131803127698, 24.6227082722284898, 24.6477034877915457, 24.6726988269151803, 24.6976942895151410, 24.7226898755096691, 24.7476855848194894,
                      24.7726814173678136, 24.7976773730803224, 24.8226734518851693, 24.8476696537129733, 24.8726659784968085, 24.8976624261722073, 24.9226589966771428, 24.9476556899520396, 24.9726525059397524, 24.9976494445855764, 25.0226465058372334,
                      25.0476436896448753, 25.0726409959610734, 25.0976384247408113, 25.1226359759414954, 25.1476336495229411, 25.1726314454473687, 25.1976293636794111, 25.2226274041860954, 25.2476255669368541, 25.2726238519035178, 25.2976222590603115,
                      25.3226207883838512, 25.3476194398531476, 25.3726182134496021, 25.3976171091570002, 25.4226161269615218, 25.4476152668517273, 25.4726145288185641, 25.4976139128553676, 25.5226134189578566, 25.5476130471241341, 25.5726127973546831,
                      25.5976126696523743, 25.6226126640224621, 25.6476127804725849, 25.6726130190127719, 25.6976133796554258, 25.7226138624153542, 25.7476144673097380, 25.7726151943581563, 25.7976160435825754, 25.8226170150073564, 25.8476181086592547,
                      25.8726193245674274, 25.8976206627634227, 25.9226221232812009, 25.9476237061571169, 25.9726254114299415, 25.9976272391408507, 26.0226291893334398, 26.0476312620537165, 26.0726334573501113, 26.0976357752734778, 26.1226382158771031,
                      26.1476407792167080, 26.1726434653504434, 26.1976462743389078, 26.2226492062451477, 26.2476522611346574, 26.2726554390753932, 26.2976587401377699, 26.3226621643946750, 26.3476657119214650, 26.3726693827959799, 26.3976731770985467,
                      26.4226770949119825, 26.4476811363216058, 26.4726853014152397, 26.4976895902832226, 26.5226940030184153, 26.5476985397161975, 26.5727032004744927, 26.5977079853937646, 26.6227128945770346, 26.6477179281298717, 26.6727230861604241,
                      26.6977283687794156, 26.7227337761001493, 26.7477393082385291, 26.7727449653130627, 26.7977507474448728, 26.8227566547577077, 26.8477626873779442, 26.8727688454346065, 26.8977751290593758, 26.9227815383865980, 26.9477880735532942,
                      26.9727947346991748, 26.9978015219666503, 27.0228084355008420, 27.0478154754495925, 27.0728226419634836, 27.0978299351958398, 27.1228373553027495, 27.1478449024430759, 27.1728525767784710, 27.1978603784733757, 27.2228683076950588,
                      27.2478763646136066, 27.2728845494019545, 27.2978928622358907, 27.3229013032940742, 27.3479098727580521, 27.3729185708122777, 27.3979273976441142, 27.4229363534438590, 27.4479454384047656, 27.4729546527230468, 27.4979639965979032,
                      27.5229734702315270, 27.5479830738291405, 27.5729928075989861, 27.5980026717523685, 27.6230126665036622, 27.6480227920703285, 27.6730330486729379, 27.6980434365351869, 27.7230539558839233, 27.7480646069491570, 27.7730753899640881,
                      27.7980863051651212, 27.8230973527918906, 27.8481085330872808, 27.8731198462974454, 27.8981312926718310, 27.9231428724632025, 27.9481545859276608, 27.9731664333246606, 27.9981784149170494, 28.0231905309710747, 28.0482027817564230,
                      28.0732151675462269, 28.0982276886171078, 28.1232403452491901, 28.1482531377261260, 28.1732660663351311, 28.1982791313669985, 28.2232923331161345, 28.2483056718805834, 28.2733191479620523, 28.2983327616659466, 28.3233465133013880,
                      28.3483604031812497, 28.3733744316221852, 28.3983885989446563, 28.4234029054729689, 28.4484173515352978, 28.4734319374637153, 28.4984466635942368, 28.5234615302668324, 28.5484765378254792, 28.5734916866181798, 28.5985069769970046,
                      28.6235224093181237, 28.6485379839418428, 28.6735537012326347, 28.6985695615592249, 28.7235677632833060, 28.7485515494832171, 28.7735354775703520, 28.7985195471896134, 28.8235037579899895, 28.8484881096245118, 28.8734726017502261,
                      28.8984572340281574, 28.9234420061232740, 28.9484269177044702, 28.9734119684445162, 28.9983971580200368, 29.0233824861114833, 29.0483679524030975, 29.0733535565828873, 29.0983392983425908, 29.1233251773776587, 29.1483111933872152,
                      29.1732973460740332, 29.1982836351445130, 29.2232700603086464, 29.2482566212799959, 29.2732433177756661, 29.2982301495162822, 29.3232171162259583, 29.3482042176322793, 29.3731914534662693, 29.3981788234623735, 29.4231663273584303,
                      29.4481539648956456, 29.4731417358185830, 29.4981296398751240, 29.5231176768164580, 29.5481058463970534, 29.5730941483746363, 29.5980825825101697, 29.6230711485678420, 29.6480598463150322, 29.6730486755222991, 29.6980376359633560,
                      29.7230267274150535, 29.7480159496573613, 29.7730053024733436, 29.7979947856491485, 29.8229843989739862, 29.8479741422401084, 29.8729640152427933, 29.8979540177803251, 29.9229441496539863, 29.9479344106680223, 29.9729248006296487,
                      29.9979153193490120, 30.0229059666391933, 30.0478967423161727, 30.0728876461988364, 30.0978786781089376, 30.1228698378711037, 30.1478611253128079, 30.1728525402643584, 30.1978440825588841, 30.2228357520323208, 30.2478275485234001,
                      30.2728194718736319, 30.2978115219272901, 30.3228036985314127, 30.3477960015357695, 30.3727884307928662, 30.3977809861579225, 30.4227736674888618, 30.4477664746463077, 30.4727594074935624, 30.4977524658965997, 30.5227456497240581,
                      30.5477389588472192, 30.5727323931400079, 30.5977259524789780, 30.6227196367433052, 30.6477134458147695, 30.6727073795777585, 30.6977014379192426, 30.7226956207287785, 30.7476899278984988, 30.7726843593230939, 30.7976789148998122,
                      30.8226735945284496, 30.8476683981113489, 30.8726633255533756, 30.8976583767619246, 30.9226535516469028, 30.9476488501207356, 30.9726442720983428, 30.9976398174971450, 31.0226354862370499, 31.0476312782404520, 31.0726271934322220,
                      31.0976232317396999, 31.1226193930926947, 31.1476156774234738, 31.1726120846667598, 31.1976086147597229, 31.2226052676419812, 31.2476020432555899, 31.2725989415450449, 31.2975959624572688, 31.3225931059416105, 31.3475903719498490,
                      31.3725877604361720, 31.3975852713571939, 31.4225829046719305, 31.4475806603418171, 31.4725785383306906, 31.4975765386047932, 31.5225746611327651, 31.5475729058856480, 31.5725712728368748, 31.5975697619622800, 31.6225683732400853,
                      31.6475671066509037, 31.6725659621777353, 31.6975649398059787, 31.7225640395234052, 31.7475632613201810, 31.7725626051888526, 31.7975620711243536, 31.8225616591240055, 31.8475613691875061, 31.8725612013169410, 31.8975611555167795,
                      31.9225612317938783, 31.9475614301574744, 31.9725617506191959, 31.9975621931930547, 32.0225627578954501, 32.0475634447451725, 32.0725642537634030, 32.0975651849737176, 32.1225662384020794, 32.1475674140768533, 32.1725687120288057,
                      32.1975701322910979, 32.2225716748993065, 32.2475733398913960, 32.2725751273077535, 32.2975770371911821, 32.3225790695868866, 32.3475812245425089, 32.3725835021080997, 32.3975859023361465, 32.4225884252815675, 32.4475910710017175,
                      32.4725938395563816, 32.4975967310078033, 32.5225997454206777, 32.5476028828621438, 32.5726061434018064, 32.5976095271117359, 32.6226130340664824, 32.6476166643430687, 32.6726204180209976, 32.6976242951822655, 32.7226282959113703,
                      32.7476324202953109, 32.7726366684235941, 32.7976410403882497, 32.8226455362838294, 32.8476501562074219, 32.8726549002586523, 32.8976597685396968, 32.9226647611552821, 32.9476698782127144, 32.9726751198218651, 32.9976804860951844,
                      33.0226859771477308, 33.0476915930971415, 33.0726973340636832, 33.0977032001702369, 33.1227091915423131, 33.1477153083080722, 33.1727215505983111, 33.1977279185464980, 33.2227344122887729, 33.2477410319639617, 33.2727477777135832,
                      33.2977546496818704, 33.3227616480157636, 33.3477687728649457, 33.3727760243818352, 33.3977834027216076, 33.4227909080422165, 33.4477985405043867, 33.4728063002716496, 33.4978141875103361, 33.5228222023896052, 33.5478303450814508,
                      33.5728386157607233, 33.5978470146051365, 33.6228555417952890, 33.6478641975146644, 33.6728729819496735, 33.6978818952896475, 33.7228909377268664, 33.7479001094565660, 33.7729094106769594, 33.7979188415892580, 33.8229284023976788,
                      33.8479380933094660, 33.8729479145349259, 33.8979578662874133, 33.9229679487833664, 33.9479781622423431, 33.9729885068869990, 33.9979989829431446, 34.0230095906397523, 34.0480203302089635, 34.0730312018861312, 34.0980422059098203,
                      34.1230533425218496, 34.1480646119672926, 34.1730760144945052, 34.1980875503551616, 34.2230992198042614, 34.2481110231001509, 34.2731229605045655, 34.2981350322826231, 34.3231472387028802, 34.3481595800373327, 34.3731720565614509,
                      34.3981846685542010, 34.4231974162980805, 34.4482103000791184, 34.4732233201869320, 34.4982364769147338, 34.5232497705593744, 34.5482632014213493, 34.5732767698048420, 34.5982904760177448, 34.6233043203716946, 34.6483183031821014,
                      34.6733324247681693, 34.6983466854529397, 34.7233610855633046, 34.7483756254300573, 34.7733903053879061, 34.7984051257755169, 34.8234200869355419, 34.8484351892146620, 34.8734504329636010, 34.8984658185371757, 34.9234813462943308,
                      34.9484970165981608, 34.9735128298159523, 34.9985287863192838, 34.9985287863192838, 34.9985287863192838, 34.9985287863192838};
    double knot_tol = SPAresabs;
    const int& dimension = 3;

    bs3_curve bs = bs3_curve_from_ctrlpts(degree, rational, closed, periodic, num_ctrlpts, ctrlpts, weights, ctrlpt_tol, num_knots, knots, knot_tol, dimension);
    exact_int_cur* cur = ACIS_NEW exact_int_cur(bs);
    intcurve* ic = ACIS_NEW intcurve(cur);

    int degree2 = 3;
    logical rational2 = TRUE;
    logical closed2 = FALSE;
    logical periodic2 = FALSE;
    int num_ctrlpts2 = 868;
    SPAposition ctrlpts2[] = {
      {-2.5000000000000000, -3.1224989991991983, 0.0000000000000000},
      {-2.4934791769644584, -3.1276864823406654, 0.0000000000000000},
      {-2.4804612411114482, -3.1380912980111226, 0.0000000000000000},
      {-2.4607923161194818, -3.1535192354414687, 0.0000000000000000},
      {-2.4410394928359285, -3.1688391287972966, 0.0000000000000000},
      {-2.4211881892815699, -3.1840311212565169, 0.0000000000000000},
      {-2.4012432964492563, -3.1990997820537119, 0.0000000000000000},
      {-2.3812044922677997, -3.2140431417020796, 0.0000000000000000},
      {-2.3610728561180814, -3.2288609889487017, 0.0000000000000000},
      {-2.3408490964529296, -3.2435526476571566, 0.0000000000000000},
      {-2.3205340256623819, -3.2581175725141387, 0.0000000000000000},
      {-2.3001284327955975, -3.2725551894397729, 0.0000000000000000},
      {-2.2796331176252358, -3.2868649383772213, 0.0000000000000000},
      {-2.2590488814804015, -3.3010462618550802, 0.0000000000000000},
      {-2.2383765296631539, -3.3150986080795630, 0.0000000000000000},
      {-2.2176168707610660, -3.3290214301332122, 0.0000000000000000},
      {-2.1967707167912951, -3.3428141862165903, 0.0000000000000000},
      {-2.1758388831217141, -3.3564763396103023, 0.0000000000000000},
      {-2.1548221884515746, -3.3700073587116419, 0.0000000000000000},
      {-2.1337214547760874, -3.3834067170510420, 0.0000000000000000},
      {-2.1125375073551265, -3.3966738933136447, 0.0000000000000000},
      {-2.0912711746806805, -3.4098083713592708, 0.0000000000000000},
      {-2.0699232884444738, -3.4228096402425425, 0.0000000000000000},
      {-2.0484946835053792, -3.4356771942327082, 0.0000000000000000},
      {-2.0269861978567487, -3.4484105328333237, 0.0000000000000000},
      {-2.0053986725935808, -3.4610091608016451, 0.0000000000000000},
      {-1.9837329518796094, -3.4734725881679074, 0.0000000000000000},
      {-1.9619898829142444, -3.4858003302543352, 0.0000000000000000},
      {-1.9401703158994004, -3.4979919076939607, 0.0000000000000000},
      {-1.9182751040062218, -3.5100468464492587, 0.0000000000000000},
      {-1.8963051033416649, -3.5219646778305247, 0.0000000000000000},
      {-1.8742611729150056, -3.5337449385141055, 0.0000000000000000},
      {-1.8521441746041878, -3.5453871705603563, 0.0000000000000000},
      {-1.8299549731221025, -3.5568909214314415, 0.0000000000000000},
      {-1.8076944359827283, -3.5682557440088853, 0.0000000000000000},
      {-1.7853634334671740, -3.5794811966109346, 0.0000000000000000},
      {-1.7629628385896114, -3.5905668430096913, 0.0000000000000000},
      {-1.7404935270631099, -3.6015122524480576, 0.0000000000000000},
      {-1.7179563772653468, -3.6123169996564277, 0.0000000000000000},
      {-1.6953522702042354, -3.6229806648692042, 0.0000000000000000},
      {-1.6726820894834391, -3.6335028338410797, 0.0000000000000000},
      {-1.6499467212677852, -3.6438830978630992, 0.0000000000000000},
      {-1.6271470542485786, -3.6541210537785154, 0.0000000000000000},
      {-1.6042839796088297, -3.6642163039984297, 0.0000000000000000},
      {-1.5813583909883611, -3.6741684565172035, 0.0000000000000000},
      {-1.5583711844488441, -3.6839771249276581, 0.0000000000000000},
      {-1.5353232584387249, -3.6936419284360520, 0.0000000000000000},
      {-1.5122155137580633, -3.7031624918768529, 0.0000000000000000},
      {-1.4890488535232835, -3.7125384457272692, 0.0000000000000000},
      {-1.4658241831318224, -3.7217694261215706, 0.0000000000000000},
      {-1.4425424102267077, -3.7308550748651870, 0.0000000000000000},
      {-1.4192044446610317, -3.7397950394485964, 0.0000000000000000},
      {-1.3958111984623518, -3.7485889730609641, 0.0000000000000000},
      {-1.3723635857969985, -3.7572365346035905, 0.0000000000000000},
      {-1.3488625229343025, -3.7657373887031058, 0.0000000000000000},
      {-1.3253089282107426, -3.7740912057244693, 0.0000000000000000},
      {-1.3017037219940117, -3.7822976617837214, 0.0000000000000000},
      {-1.2780478266469986, -3.7903564387605222, 0.0000000000000000},
      {-1.2543421664917036, -3.7982672243104663, 0.0000000000000000},
      {-1.2305876677730681, -3.8060297118771667, 0.0000000000000000},
      {-1.2067852586227328, -3.8136436007041055, 0.0000000000000000},
      {-1.1829358690227278, -3.8211085958462871, 0.0000000000000000},
      {-1.1590404307690771, -3.8284244081816148, 0.0000000000000000},
      {-1.1350998774353505, -3.8355907544220975, 0.0000000000000000},
      {-1.1111151443361342, -3.8426073571247850, 0.0000000000000000},
      {-1.0870871684904335, -3.8494739447024866, 0.0000000000000000},
      {-1.0630168885850182, -3.8561902514342670, 0.0000000000000000},
      {-1.0389052449376988, -3.8627560174757289, 0.0000000000000000},
      {-1.0147531794605307, -3.8691709888690076, 0.0000000000000000},
      {-0.9905616356229765, -3.8754349175526110, 0.0000000000000000},
      {-0.9663315584149860, -3.8815475613709753, 0.0000000000000000},
      {-0.9420638943100321, -3.8875086840838149, 0.0000000000000000},
      {-0.9177595912280825, -3.8933180553752269, 0.0000000000000000},
      {-0.8934195984985194, -3.8989754508625807, 0.0000000000000000},
      {-0.8690448668229993, -3.9044806521051618, 0.0000000000000000},
      {-0.8446363482382638, -3.9098334466125770, 0.0000000000000000},
      {-0.8201949960788995, -3.9150336278529703, 0.0000000000000000},
      {-0.7957217649400412, -3.9200809952609359, 0.0000000000000000},
      {-0.7712176106400341, -3.9249753542452566, 0.0000000000000000},
      {-0.7466834901830446, -3.9297165161963958, 0.0000000000000000},
      {-0.7221203617216241, -3.9343042984937258, 0.0000000000000000},
      {-0.6975291845192305, -3.9387385245125608, 0.0000000000000000},
      {-0.6729109189127069, -3.9430190236309466, 0.0000000000000000},
      {-0.6482665262747178, -3.9471456312361837, 0.0000000000000000},
      {-0.6235969689761439, -3.9511181887311668, 0.0000000000000000},
      {-0.5989032103484436, -3.9549365435404571, 0.0000000000000000},
      {-0.5741862146459678, -3.9586005491161043, 0.0000000000000000},
      {-0.5494469470082486, -3.9621100649432961, 0.0000000000000000},
      {-0.5246863734222484, -3.9654649565456883, 0.0000000000000000},
      {-0.4999054606845786, -3.9686650954905760, 0.0000000000000000},
      {-0.4751051763636849, -3.9717103593937679, 0.0000000000000000},
      {-0.4502864887620075, -3.9746006319242664, 0.0000000000000000},
      {-0.4254503668781033, -3.9773358028087000, 0.0000000000000000},
      {-0.4005977803687538, -3.9799157678354939, 0.0000000000000000},
      {-0.3757296995110357, -3.9823404288588495, 0.0000000000000000},
      {-0.3508470951643793, -3.9846096938024442, 0.0000000000000000},
      {-0.3259509387325920, -3.9867234766629212, 0.0000000000000000},
      {-0.3010422021258716, -3.9886816975131341, 0.0000000000000000},
      {-0.2761218577227951, -3.9904842825051556, 0.0000000000000000},
      {-0.2511908783322858, -3.9921311638730312, 0.0000000000000000},
      {-0.2262502371555751, -3.9936222799353400, 0.0000000000000000},
      {-0.2013009077481381, -3.9949575750974589, 0.0000000000000000},
      {-0.1763438639816159, -3.9961369998536416, 0.0000000000000000},
      {-0.1513800800057566, -3.9971605107888259, 0.0000000000000000},
      {-0.1264105302102072, -3.9980280705802187, 0.0000000000000000},
      {-0.1014361891868407, -3.9987396479986677, 0.0000000000000000},
      {-0.0764580316900174, -3.9992952179095980, 0.0000000000000000},
      {-0.0514770326045410, -3.9996947612745859, 0.0000000000000000},
      {-0.0264941668848499, -3.9999382651492970, 0.0000000000000000},
      {-0.0015008901370130, -4.0000257560175729, 0.0000000000000000},
      {0.0235030897156018,  -3.9999570214529405, 0.0000000000000000},
      {0.0485167941103021,  -3.9997318308615726, 0.0000000000000000},
      {0.0735297249888522,  -3.9993501941249230, 0.0000000000000000},
      {0.0985396374748709,  -3.9988121402713670, 0.0000000000000000},
      {0.1235455538266827,  -3.9981176930015403, 0.0000000000000000},
      {0.1485464964798656,  -3.9972668821310364, 0.0000000000000000},
      {0.1735414880885059,  -3.9962597435791070, 0.0000000000000000},
      {0.1985295515624928,  -3.9950963193698223, 0.0000000000000000},
      {0.2235097101058592,  -3.9937766576295930, 0.0000000000000000},
      {0.2484809872548329,  -3.9923008125853849, 0.0000000000000000},
      {0.2734424069159440,  -3.9906688445624185, 0.0000000000000000},
      {0.2983929934041026,  -3.9888808199817367, 0.0000000000000000},
      {0.3233317714806612,  -3.9869368113574648, 0.0000000000000000},
      {0.3482577663914598,  -3.9848368972938841, 0.0000000000000000},
      {0.3731700039048557,  -3.9825811624822465, 0.0000000000000000},
      {0.3980675103497238,  -3.9801696976973426, 0.0000000000000000},
      {0.4229493126534467,  -3.9776025997938556, 0.0000000000000000},
      {0.4478144383798696,  -3.9748799717024497, 0.0000000000000000},
      {0.4726619157672372,  -3.9720019224256431, 0.0000000000000000},
      {0.4974907737661010,  -3.9689685670334383, 0.0000000000000000},
      {0.5223000420772002,  -3.9657800266587055, 0.0000000000000000},
      {0.5470887511893100,  -3.9624364284923455, 0.0000000000000000},
      {0.5718559324170642,  -3.9589379057781944, 0.0000000000000000},
      {0.5966006179387392,  -3.9552845978077182, 0.0000000000000000},
      {0.6213218408340064,  -3.9514766499144445, 0.0000000000000000},
      {0.6460186351216523,  -3.9475142134681791, 0.0000000000000000},
      {0.6706900357972562,  -3.9433974458689818, 0.0000000000000000},
      {0.6953350788708307,  -3.9391265105408806, 0.0000000000000000},
      {0.7199528014044267,  -3.9347015769254150, 0.0000000000000000},
      {0.7445422415496893,  -3.9301228204748471, 0.0000000000000000},
      {0.7691024385853799,  -3.9253904226452523, 0.0000000000000000},
      {0.7936324329548428,  -3.9205045708892667, 0.0000000000000000},
      {0.8181312663034401,  -3.9154654586486788, 0.0000000000000000},
      {0.8425979815159240,  -3.9102732853467499, 0.0000000000000000},
      {0.8670316227537715,  -3.9049282563803023, 0.0000000000000000},
      {0.8914312354924654,  -3.8994305831115996, 0.0000000000000000},
      {0.9157958665587200,  -3.8937804828599525, 0.0000000000000000},
      {0.9401245641676607,  -3.8879781788931318, 0.0000000000000000},
      {0.9644163779599428,  -3.8820239004185257, 0.0000000000000000},
      {0.9886703590388177,  -3.8759178825740745, 0.0000000000000000},
      {1.0128855600071383,  -3.8696603664189628, 0.0000000000000000},
      {1.0370610350043092,  -3.8632515989240974, 0.0000000000000000},
      {1.0611958397431767,  -3.8566918329623445, 0.0000000000000000},
      {1.0852890315468522,  -3.8499813272985293, 0.0000000000000000},
      {1.1093396693854767,  -3.8431203465792261, 0.0000000000000000},
      {1.1333468139129188,  -3.8361091613222964, 0.0000000000000000},
      {1.1573095275034022,  -3.8289480479061986, 0.0000000000000000},
      {1.1812268742880798,  -3.8216372885591068, 0.0000000000000000},
      {1.2050979201915213,  -3.8141771713477457, 0.0000000000000000},
      {1.2289217329681397,  -3.8065679901660276, 0.0000000000000000},
      {1.2526973822385465,  -3.7988100447234698, 0.0000000000000000},
      {1.2764239395258290,  -3.7909036405333634, 0.0000000000000000},
      {1.3001004782917571,  -3.7828490889007265, 0.0000000000000000},
      {1.3237260739729115,  -3.7746467069100333, 0.0000000000000000},
      {1.3472998040167345,  -3.7662968174127118, 0.0000000000000000},
      {1.3708207479175012,  -3.7577997490144184, 0.0000000000000000},
      {1.3942879872522140,  -3.7491558360620867, 0.0000000000000000},
      {1.4177006057164110,  -3.7403654186307693, 0.0000000000000000},
      {1.4410576891598930,  -3.7314288425102085, 0.0000000000000000},
      {1.4643583256223656,  -3.7223464591912467, 0.0000000000000000},
      {1.4876016053690004,  -3.7131186258519757, 0.0000000000000000},
      {1.5107866209258893,  -3.7037457053436524, 0.0000000000000000},
      {1.5339124671154498,  -3.6942280661764468, 0.0000000000000000},
      {1.5569782410916848,  -3.6845660825048951, 0.0000000000000000},
      {1.5799830423754080,  -3.6747601341132086, 0.0000000000000000},
      {1.6029259728893321,  -3.6648106064003043, 0.0000000000000000},
      {1.6258061369930876,  -3.6547178903646400, 0.0000000000000000},
      {1.6486226415181391,  -3.6444823825888415, 0.0000000000000000},
      {1.6713745958025985,  -3.6341044852240860, 0.0000000000000000},
      {1.6940611117259559,  -3.6235846059742913, 0.0000000000000000},
      {1.7166813037436799,  -3.6129231580800636, 0.0000000000000000},
      {1.7392342889217678,  -3.6021205603024753, 0.0000000000000000},
      {1.7617191869711313,  -3.5911772369065527, 0.0000000000000000},
      {1.7841351202819320,  -3.5800936176446383, 0.0000000000000000},
      {1.8064812139577788,  -3.5688701377394527, 0.0000000000000000},
      {1.8287565958498346,  -3.5575072378670152, 0.0000000000000000},
      {1.8509603965908090,  -3.5460053641393032, 0.0000000000000000},
      {1.8730917496288400,  -3.5343649680867197, 0.0000000000000000},
      {1.8951497912612731,  -3.5225865066403426, 0.0000000000000000},
      {1.9171336606683220,  -3.5106704421139776, 0.0000000000000000},
      {1.9390424999466187,  -3.4986172421859782, 0.0000000000000000},
      {1.9608754541426507,  -3.4864273798808725, 0.0000000000000000},
      {1.9826316712860752,  -3.4741013335507809, 0.0000000000000000},
      {2.0043103024229278,  -3.4616395868566188, 0.0000000000000000},
      {2.0259105016487098,  -3.4490426287490954, 0.0000000000000000},
      {2.0474314261413333,  -3.4363109534494996, 0.0000000000000000},
      {2.0688722361939966,  -3.4234450604303106, 0.0000000000000000},
      {2.0902320952478779,  -3.4104454543955480, 0.0000000000000000},
      {2.1115101699247489,  -3.3973126452609748, 0.0000000000000000},
      {2.1327056300594460,  -3.3840471481340630, 0.0000000000000000},
      {2.1538176487322125,  -3.3706494832937581, 0.0000000000000000},
      {2.1748454023009289,  -3.3571201761700697, 0.0000000000000000},
      {2.1957880704331947,  -3.3434597573234162, 0.0000000000000000},
      {2.2166448361382991,  -3.3296687624238244, 0.0000000000000000},
      {2.2374148857990441,  -3.3157477322298625, 0.0000000000000000},
      {2.2580974092034567,  -3.3016972125674484, 0.0000000000000000},
      {2.2786915995763395,  -3.2875177543083973, 0.0000000000000000},
      {2.2991966536107080,  -3.2732099133488122, 0.0000000000000000},
      {2.3196117714990927,  -3.2587742505872672, 0.0000000000000000},
      {2.3399361569646837,  -3.2442113319027781, 0.0000000000000000},
      {2.3601690172923631,  -3.2295217281326174, 0.0000000000000000},
      {2.3803095633595746,  -3.2147060150498921, 0.0000000000000000},
      {2.4003570096670699,  -3.1997647733409607, 0.0000000000000000},
      {2.4203105743695010,  -3.1846985885826458, 0.0000000000000000},
      {2.4401694793058839,  -3.1695080512192626, 0.0000000000000000},
      {2.4599329500298870,  -3.1541937565394353, 0.0000000000000000},
      {2.4796002158400272,  -3.1387563046527749, 0.0000000000000000},
      {2.4991705098096548,  -3.1231963004662946, 0.0000000000000000},
      {2.5186430688168504,  -3.1075143536607253, 0.0000000000000000},
      {2.5380171335741233,  -3.0917110786665565, 0.0000000000000000},
      {2.5572919486579968,  -3.0757870946399661, 0.0000000000000000},
      {2.5764667625384239,  -3.0597430254385265, 0.0000000000000000},
      {2.5955408276080485,  -3.0435794995967234, 0.0000000000000000},
      {2.6145134002113206,  -3.0272971503013228, 0.0000000000000000},
      {2.6333837406734677,  -3.0108966153665322, 0.0000000000000000},
      {2.6521511133292690,  -2.9943785372089819, 0.0000000000000000},
      {2.6708147865517269,  -2.9777435628225390, 0.0000000000000000},
      {2.6893740327805418,  -2.9609923437529400, 0.0000000000000000},
      {2.7078281285504398,  -2.9441255360722298, 0.0000000000000000},
      {2.7261763545193460,  -2.9271438003530568, 0.0000000000000000},
      {2.7444179954963821,  -2.9100478016427482, 0.0000000000000000},
      {2.7625523404697194,  -2.8928382094372669, 0.0000000000000000},
      {2.7805786826342445,  -2.8755156976549263, 0.0000000000000000},
      {2.7984963194190979,  -2.8580809446100135, 0.0000000000000000},
      {2.8163045525149890,  -2.8405346329861509, 0.0000000000000000},
      {2.8340026879014188,  -2.8228774498095812, 0.0000000000000000},
      {2.8515900358736523,  -2.8051100864221974, 0.0000000000000000},
      {2.8690659110696033,  -2.7872332384544705, 0.0000000000000000},
      {2.8864296324964762,  -2.7692476057981672, 0.0000000000000000},
      {2.9036805235572989,  -2.7511538925789294, 0.0000000000000000},
      {2.9208179120772311,  -2.7329528071286675, 0.0000000000000000},
      {2.9378411303297427,  -2.7146450619578055, 0.0000000000000000},
      {2.9547495150625771,  -2.6962313737273522, 0.0000000000000000},
      {2.9715424075235921,  -2.6777124632208240, 0.0000000000000000},
      {2.9882191534863587,  -2.6590890553159885, 0.0000000000000000},
      {3.0047791032756463,  -2.6403618789564645, 0.0000000000000000},
      {3.0212216117926820,  -2.6215316671231577, 0.0000000000000000},
      {3.0375460385402588,  -2.6025991568055380, 0.0000000000000000},
      {3.0537517476476568,  -2.5835650889727608, 0.0000000000000000},
      {3.0698381078953711,  -2.5644302085446391, 0.0000000000000000},
      {3.0858044927396806,  -2.5451952643624547, 0.0000000000000000},
      {3.1016502803370116,  -2.5258610091596112, 0.0000000000000000},
      {3.1173748535681272,  -2.5064281995321567, 0.0000000000000000},
      {3.1329776000621399,  -2.4868975959091353, 0.0000000000000000},
      {3.1484579122203211,  -2.4672699625227974, 0.0000000000000000},
      {3.1638151872397362,  -2.4475460673786560, 0.0000000000000000},
      {3.1790488271366870,  -2.4277266822254124, 0.0000000000000000},
      {3.1941582387699721,  -2.4078125825247167, 0.0000000000000000},
      {3.2091428338639423,  -2.3878045474207892, 0.0000000000000000},
      {3.2240020290313942,  -2.3677033597099122, 0.0000000000000000},
      {3.2387352457962284,  -2.3475098058097541, 0.0000000000000000},
      {3.2533419106159682,  -2.3272246757285782, 0.0000000000000000},
      {3.2678214549040412,  -2.3068487630342984, 0.0000000000000000},
      {3.2821733150518888,  -2.2863828648233886, 0.0000000000000000},
      {3.2963969324508842,  -2.2658277816896804, 0.0000000000000000},
      {3.3104917535140292,  -2.2451843176929906, 0.0000000000000000},
      {3.3244572296974946,  -2.2244532803276464, 0.0000000000000000},
      {3.3382928175219293,  -2.2036354804908602, 0.0000000000000000},
      {3.3519979785935701,  -2.1827317324509563, 0.0000000000000000},
      {3.3655721796252025,  -2.1617428538155150, 0.0000000000000000},
      {3.3790148924568437,  -2.1406696654993267, 0.0000000000000000},
      {3.3923255940762913,  -2.1195129916922619, 0.0000000000000000},
      {3.4055037666394421,  -2.0982736598269960, 0.0000000000000000},
      {3.4185488974904019,  -2.0769525005466045, 0.0000000000000000},
      {3.4314604791814176,  -2.0555503476720474, 0.0000000000000000},
      {3.4442380094925746,  -2.0340680381695115, 0.0000000000000000},
      {3.4568809914513188,  -2.0125064121176490, 0.0000000000000000},
      {3.4693889333517540,  -1.9908663126746793, 0.0000000000000000},
      {3.4817613487737389,  -1.9691485860453828, 0.0000000000000000},
      {3.4939977566017828,  -1.9473540814479651, 0.0000000000000000},
      {3.5060976810437321,  -1.9254836510808195, 0.0000000000000000},
      {3.5180606516492254,  -1.9035381500891524, 0.0000000000000000},
      {3.5298862033279881,  -1.8815184365315143, 0.0000000000000000},
      {3.5415738763678655,  -1.8594253713462050, 0.0000000000000000},
      {3.5531232164526920,  -1.8372598183175735, 0.0000000000000000},
      {3.5645337746799006,  -1.8150226440421975, 0.0000000000000000},
      {3.5758051075779740,  -1.7927147178949721, 0.0000000000000000},
      {3.5869367771236211,  -1.7703369119950600, 0.0000000000000000},
      {3.5979283507588287,  -1.7478901011717811, 0.0000000000000000},
      {3.6087794014075811,  -1.7253751629303395, 0.0000000000000000},
      {3.6194895074924864,  -1.7027929774174959, 0.0000000000000000},
      {3.6300582529510970,  -1.6801444273871109, 0.0000000000000000},
      {3.6404852272520718,  -1.6574303981655940, 0.0000000000000000},
      {3.6507700254110773,  -1.6346517776172522, 0.0000000000000000},
      {3.6609122480065106,  -1.6118094561095391, 0.0000000000000000},
      {3.6709115011949951,  -1.5889043264782110, 0.0000000000000000},
      {3.6807673967266208,  -1.5659372839923780, 0.0000000000000000},
      {3.6904795519600340,  -1.5429092263194684, 0.0000000000000000},
      {3.7000475898772431,  -1.5198210534901000, 0.0000000000000000},
      {3.7094711390982491,  -1.4966736678628525, 0.0000000000000000},
      {3.7187498338954232,  -1.4734679740889578, 0.0000000000000000},
      {3.7278833142076957,  -1.4502048790768953, 0.0000000000000000},
      {3.7368712256544900,  -1.4268852919569008, 0.0000000000000000},
      {3.7457132195494660,  -1.4035101240453942, 0.0000000000000000},
      {3.7544089529140137,  -1.3800802888093113, 0.0000000000000000},
      {3.7629580884905440,  -1.3565967018303626, 0.0000000000000000},
      {3.7713602947555422,  -1.3330602807692062, 0.0000000000000000},
      {3.7796152459324084,  -1.3094719453295398, 0.0000000000000000},
      {3.7877226220040656,  -1.2858326172221086, 0.0000000000000000},
      {3.7956821087253445,  -1.2621432201286469, 0.0000000000000000},
      {3.8034933976351422,  -1.2384046796657318, 0.0000000000000000},
      {3.8111561860683620,  -1.2146179233485659, 0.0000000000000000},
      {3.8186701771676077,  -1.1907838805546873, 0.0000000000000000},
      {3.8260350798946838,  -1.1669034824876106, 0.0000000000000000},
      {3.8332506090418264,  -1.1429776621403842, 0.0000000000000000},
      {3.8403164852427452,  -1.1190073542590946, 0.0000000000000000},
      {3.8472324349834102,  -1.0949934953062903, 0.0000000000000000},
      {3.8539981906126268,  -1.0709370234243469, 0.0000000000000000},
      {3.8606134903523719,  -1.0468388783987621, 0.0000000000000000},
      {3.8670780783078946,  -1.0227000016213859, 0.0000000000000000},
      {3.8733917044776192,  -0.9985213360535981, 0.0000000000000000},
      {3.8795541247627687,  -0.9743038261894119, 0.0000000000000000},
      {3.8855651009767893,  -0.9500484180185248, 0.0000000000000000},
      {3.8914244008545662,  -0.9257560589893163, 0.0000000000000000},
      {3.8971317980613303,  -0.9014276979717770, 0.0000000000000000},
      {3.9026870722014309,  -0.8770642852203886, 0.0000000000000000},
      {3.9080900088267922,  -0.8526667723369601, 0.0000000000000000},
      {3.9133403994452030,  -0.8282361122333903, 0.0000000000000000},
      {3.9184380415283204,  -0.8037732590944041, 0.0000000000000000},
      {3.9233827385194804,  -0.7792791683402164, 0.0000000000000000},
      {3.9281742998412517,  -0.7547547965891626, 0.0000000000000000},
      {3.9328125409027610,  -0.7302011016202832, 0.0000000000000000},
      {3.9372972831068069,  -0.7056190423358513, 0.0000000000000000},
      {3.9416283538566841,  -0.6810095787238694, 0.0000000000000000},
      {3.9458055865628503,  -0.6563736718205190, 0.0000000000000000},
      {3.9498288206492855,  -0.6317122836725744, 0.0000000000000000},
      {3.9536979015596536,  -0.6070263772997568, 0.0000000000000000},
      {3.9574126807632477,  -0.5823169166570861, 0.0000000000000000},
      {3.9609730157606391,  -0.5575848665971654, 0.0000000000000000},
      {3.9643787700891586,  -0.5328311928324516, 0.0000000000000000},
      {3.9676298133280907,  -0.5080568618974677, 0.0000000000000000},
      {3.9707260211036646,  -0.4832628411110209, 0.0000000000000000},
      {3.9736672750937823,  -0.4584500985383519, 0.0000000000000000},
      {3.9764534630325494,  -0.4336196029532815, 0.0000000000000000},
      {3.9790844787145105,  -0.4087723238003163, 0.0000000000000000},
      {3.9815602219987212,  -0.3839092311567386, 0.0000000000000000},
      {3.9838805988125037,  -0.3590312956946563, 0.0000000000000000},
      {3.9860455211550407,  -0.3341394886430502, 0.0000000000000000},
      {3.9880549071006755,  -0.3092347817497892, 0.0000000000000000},
      {3.9899086808020066,  -0.2843181472436136, 0.0000000000000000},
      {3.9916067724927311,  -0.2593905577961276, 0.0000000000000000},
      {3.9931491184902588,  -0.2344529864837527, 0.0000000000000000},
      {3.9945356611980820,  -0.2095064067496686, 0.0000000000000000},
      {3.9957663491079143,  -0.1845517923657489, 0.0000000000000000},
      {3.9968411368015833,  -0.1595901173944861, 0.0000000000000000},
      {3.9977599849526748,  -0.1346223561508635, 0.0000000000000000},
      {3.9985228603280625,  -0.1096494831643658, 0.0000000000000000},
      {3.9991297357886531,  -0.0846724731404710, 0.0000000000000000},
      {3.9995805902919819,  -0.0596923009239982, 0.0000000000000000},
      {3.9998754088867789,  -0.0347099414555400, 0.0000000000000000},
      {4.0000142050406833,  -0.0097223542829306, 0.0000000000000000},
      {3.9999968834604704,  0.0152762566983443,  0.0000000000000000},
      {3.9998232116659871,  0.0402849147355369,  0.0000000000000000},
      {3.9994930536310376,  0.0652986250662011,  0.0000000000000000},
      {3.9990064720200138,  0.0903096388066154,  0.0000000000000000},
      {3.9983634885151096,  0.1153169781535169,  0.0000000000000000},
      {3.9975641309245802,  0.1403196654820304,  0.0000000000000000},
      {3.9966084331579053,  0.1653167233695602,  0.0000000000000000},
      {3.9954964352306739,  0.1903071746377590,  0.0000000000000000},
      {3.9942281832612299,  0.2152900423896145,  0.0000000000000000},
      {3.9928037294691920,  0.2402643500478342,  0.0000000000000000},
      {3.9912231321731935,  0.2652291213928868,  0.0000000000000000},
      {3.9894864557885166,  0.2901833806010812,  0.0000000000000000},
      {3.9875937708244584,  0.3151261522826551,  0.0000000000000000},
      {3.9855451538814615,  0.3400564615198118,  0.0000000000000000},
      {3.9833406876480106,  0.3649733339047594,  0.0000000000000000},
      {3.9809804608972863,  0.3898757955777195,  0.0000000000000000},
      {3.9784645684835898,  0.4147628732649251,  0.0000000000000000},
      {3.9757931113385077,  0.4396335943165791,  0.0000000000000000},
      {3.9729661964668797,  0.4644869867448065,  0.0000000000000000},
      {3.9699839369424845,  0.4893220792615661,  0.0000000000000000},
      {3.9668464519035158,  0.5141379013165416,  0.0000000000000000},
      {3.9635538665478132,  0.5389334831349996,  0.0000000000000000},
      {3.9601063121278570,  0.5637078557556248,  0.0000000000000000},
      {3.9565039259455332,  0.5884600510683100,  0.0000000000000000},
      {3.9527468513466428,  0.6131891018519279,  0.0000000000000000},
      {3.9488352377151936,  0.6378940418120538,  0.0000000000000000},
      {3.9447692404674597,  0.6625739056186595,  0.0000000000000000},
      {3.9405490210457774,  0.6872277289437735,  0.0000000000000000},
      {3.9361747469121391,  0.7118545484990821,  0.0000000000000000},
      {3.9316465915415315,  0.7364534020735241,  0.0000000000000000},
      {3.9269647344150425,  0.7610233285707985,  0.0000000000000000},
      {3.9221293610127423,  0.7855633680468740,  0.0000000000000000},
      {3.9171406628063092,  0.8100725617474134,  0.0000000000000000},
      {3.9119988372514545,  0.8345499521451845,  0.0000000000000000},
      {3.9067040877800778,  0.8589945829773896,  0.0000000000000000},
      {3.9012566237922135,  0.8834054992829856,  0.0000000000000000},
      {3.8956566606477381,  0.9077817474399046,  0.0000000000000000},
      {3.8899044196578361,  0.9321223752022691,  0.0000000000000000},
      {3.8840001280762424,  0.9564264317375163,  0.0000000000000000},
      {3.8779440190902603,  0.9806929676634931,  0.0000000000000000},
      {3.8717363318115128,  1.0049210350854725,  0.0000000000000000},
      {3.8653773112665242,  1.0291096876331287,  0.0000000000000000},
      {3.8588672083869997,  1.0532579804974442,  0.0000000000000000},
      {3.8522062799999213,  1.0773649704675501,  0.0000000000000000},
      {3.8453947888174156,  1.1014297159675221,  0.0000000000000000},
      {3.8384330034263545,  1.1254512770930942,  0.0000000000000000},
      {3.8313211982777551,  1.1494287156483012,  0.0000000000000000},
      {3.8240596536759597,  1.1733610951820908,  0.0000000000000000},
      {3.8166486557675467,  1.1972474810248168,  0.0000000000000000},
      {3.8090884965300620,  1.2210869403247031,  0.0000000000000000},
      {3.8013794737604920,  1.2448785420842143,  0.0000000000000000},
      {3.7935218910634987,  1.2686213571963600,  0.0000000000000000},
      {3.7855160578394824,  1.2923144584809263,  0.0000000000000000},
      {3.7773622892723493,  1.3159569207206299,  0.0000000000000000},
      {3.7690609063170992,  1.3395478206971918,  0.0000000000000000},
      {3.7606122356871818,  1.3630862372273398,  0.0000000000000000},
      {3.7520166098415988,  1.3865712511987220,  0.0000000000000000},
      {3.7432743669718360,  1.4100019456057538,  0.0000000000000000},
      {3.7343858509885060,  1.4333774055853585,  0.0000000000000000},
      {3.7253514115078228,  1.4566967184526467,  0.0000000000000000},
      {3.7161714038378308,  1.4799589737365026,  0.0000000000000000},
      {3.7068461889643944,  1.5031632632150740,  0.0000000000000000},
      {3.6973761335370128,  1.5263086809511874,  0.0000000000000000},
      {3.6877616098543617,  1.5493943233276706,  0.0000000000000000},
      {3.6780029958496461,  1.5724192890825701,  0.0000000000000000},
      {3.6681006750757299,  1.5953826793443038,  0.0000000000000000},
      {3.6580550366900373,  1.6182835976666861,  0.0000000000000000},
      {3.6478664754392311,  1.6411211500638911,  0.0000000000000000},
      {3.6375353916437043,  1.6638944450452908,  0.0000000000000000},
      {3.6270621911818020,  1.6866025936502198,  0.0000000000000000},
      {3.6164472854738801,  1.7092447094826153,  0.0000000000000000},
      {3.6056910914661082,  1.7318199087455801,  0.0000000000000000},
      {3.5947940316140796,  1.7543273102758346,  0.0000000000000000},
      {3.5837565338661905,  1.7767660355780568,  0.0000000000000000},
      {3.5725790316468253,  1.7991352088591259,  0.0000000000000000},
      {3.5612619638393079,  1.8214339570622773,  0.0000000000000000},
      {3.5498057747686382,  1.8436614099010948,  0.0000000000000000},
      {3.5382109141840523,  1.8658166998934771,  0.0000000000000000},
      {3.5264778372413135,  1.8878989623954130,  0.0000000000000000},
      {3.5146070044848501,  1.9099073356346978,  0.0000000000000000},
      {3.5025988818296394,  1.9318409607445159,  0.0000000000000000},
      {3.4904539405429040,  1.9536989817969186,  0.0000000000000000},
      {3.4781726572256009,  1.9754805458361742,  0.0000000000000000},
      {3.4657555137936802,  1.9971848029120165,  0.0000000000000000},
      {3.4532029974591705,  2.0188109061127628,  0.0000000000000000},
      {3.4405156007110316,  2.0403580115983226,  0.0000000000000000},
      {3.4276938212957981,  2.0618252786330791,  0.0000000000000000},
      {3.4147381621980530,  2.0832118696186552,  0.0000000000000000},
      {3.4016491316206472,  2.1045169501265368,  0.0000000000000000},
      {3.3884272429647675,  2.1257396889306230,  0.0000000000000000},
      {3.3750730148097436,  2.1468792580395690,  0.0000000000000000},
      {3.3615869708927195,  2.1679348327290890,  0.0000000000000000},
      {3.3479696400880572,  2.1889055915740681,  0.0000000000000000},
      {3.3342215563865985,  2.2097907164805703,  0.0000000000000000},
      {3.3203432588746855,  2.2305893927177252,  0.0000000000000000},
      {3.3063352917129993,  2.2513008089494537,  0.0000000000000000},
      {3.2921982041151998,  2.2719241572660915,  0.0000000000000000},
      {3.2779325503263808,  2.2924586332158583,  0.0000000000000000},
      {3.2635388896012847,  2.3129034358361964,  0.0000000000000000},
      {3.2490177861823883,  2.3332577676849771,  0.0000000000000000},
      {3.2343698092777333,  2.3535208348715670,  0.0000000000000000},
      {3.2195955330386057,  2.3736918470877528,  0.0000000000000000},
      {3.2046955365369909,  2.3937700176385208,  0.0000000000000000},
      {3.1896704037428583,  2.4137545634727111,  0.0000000000000000},
      {3.1745207235012511,  2.4336447052135157,  0.0000000000000000},
      {3.1592470895091762,  2.4534396671888330,  0.0000000000000000},
      {3.1438501002923100,  2.4731386774614785,  0.0000000000000000},
      {3.1283303591815321,  2.4927409678592629,  0.0000000000000000},
      {3.1126884742892398,  2.5122457740048905,  0.0000000000000000},
      {3.0969250584854957,  2.5316523353457505,  0.0000000000000000},
      {3.0810407293740063,  2.5509598951835222,  0.0000000000000000},
      {3.0650361092678620,  2.5701677007036450,  0.0000000000000000},
      {3.0489118251651721,  2.5892750030046439,  0.0000000000000000},
      {3.0326685087244294,  2.6082810571272881,  0.0000000000000000},
      {3.0163067962397738,  2.6271851220835956,  0.0000000000000000},
      {2.9998273286160213,  2.6459864608856973,  0.0000000000000000},
      {2.9832307513435277,  2.6646843405745200,  0.0000000000000000},
      {2.9665177144728889,  2.6832780322483423,  0.0000000000000000},
      {2.9496888725894381,  2.7017668110911561,  0.0000000000000000},
      {2.9327448847875939,  2.7201499564009066,  0.0000000000000000},
      {2.9156864146450054,  2.7384267516175367,  0.0000000000000000},
      {2.8985141301965380,  2.7565964843508870,  0.0000000000000000},
      {2.8812287039080888,  2.7746584464084361,  0.0000000000000000},
      {2.8638308126502228,  2.7926119338228643,  0.0000000000000000},
      {2.8463211376716195,  2.8104562468794509,  0.0000000000000000},
      {2.8287003645723985,  2.8281906901433280,  0.0000000000000000},
      {2.8109691832772175,  2.8458145724865411,  0.0000000000000000},
      {2.7931282880082446,  2.8633272071149429,  0.0000000000000000},
      {2.7751783772579341,  2.8807279115949402,  0.0000000000000000},
      {2.7571201537616634,  2.8980160078800394,  0.0000000000000000},
      {2.7389543244701766,  2.9151908223372494,  0.0000000000000000},
      {2.7206816005218855,  2.9322516857732843,  0.0000000000000000},
      {2.7023026972149999,  2.9491979334606229,  0.0000000000000000},
      {2.6838183339794845,  2.9660289051633546,  0.0000000000000000},
      {2.6652292343488821,  2.9827439451628903,  0.0000000000000000},
      {2.6465361259319415,  2.9993424022834665,  0.0000000000000000},
      {2.6277397403841212,  3.0158236299174845,  0.0000000000000000},
      {2.6088408133789138,  3.0321869860506743,  0.0000000000000000},
      {2.5898400845790173,  3.0484318332870690,  0.0000000000000000},
      {2.5707382976073534,  3.0645575388737911,  0.0000000000000000},
      {2.5515362000179387,  3.0805634747256936,  0.0000000000000000},
      {2.5322345432665863,  3.0964490174497747,  0.0000000000000000},
      {2.5128340826814703,  3.1122135483694269,  0.0000000000000000},
      {2.4933355774335331,  3.1278564535485129,  0.0000000000000000},
      {2.4737397905067438,  3.1433771238152417,  0.0000000000000000},
      {2.4540474886682047,  3.1587749547858515,  0.0000000000000000},
      {2.4342594424381230,  3.1740493468881352,  0.0000000000000000},
      {2.4143764260596141,  3.1891997053847354,  0.0000000000000000},
      {2.3943992174683824,  3.2042254403962946,  0.0000000000000000},
      {2.3743285982622515,  3.2191259669243726,  0.0000000000000000},
      {2.3541653536705303,  3.2339007048742086,  0.0000000000000000},
      {2.3339102725232901,  3.2485490790772751,  0.0000000000000000},
      {2.3135641472204327,  3.2630705193136302,  0.0000000000000000},
      {2.2931277737006832,  3.2774644603341083,  0.0000000000000000},
      {2.2726019514103886,  3.2917303418822526,  0.0000000000000000},
      {2.2519874832722393,  3.3058676087161531,  0.0000000000000000},
      {2.2312851756537997,  3.3198757106299777,  0.0000000000000000},
      {2.2104958383359365,  3.3337541024753889,  0.0000000000000000},
      {2.1896202844811121,  3.3475022441827171,  0.0000000000000000},
      {2.1686593306015305,  3.3611196007819535,  0.0000000000000000},
      {2.1476137965271698,  3.3746056424235471,  0.0000000000000000},
      {2.1264845053736807,  3.3879598443989845,  0.0000000000000000},
      {2.1052722835101503,  3.4011816871611895,  0.0000000000000000},
      {2.0839779605267372,  3.4142706563446903,  0.0000000000000000},
      {2.0626023692022093,  3.4272262427856273,  0.0000000000000000},
      {2.0411463454713177,  3.4400479425415185,  0.0000000000000000},
      {2.0196107283920717,  3.4527352569108394,  0.0000000000000000},
      {1.9979963601128887,  3.4652876924523968,  0.0000000000000000},
      {1.9763040858396268,  3.4777047610044933,  0.0000000000000000},
      {1.9545347538024784,  3.4899859797038832,  0.0000000000000000},
      {1.9326892152227795,  3.5021308710045229,  0.0000000000000000},
      {1.9107683242796747,  3.5141389626961281,  0.0000000000000000},
      {1.8887729380766789,  3.5260097879224941,  0.0000000000000000},
      {1.8667039166081225,  3.5377428851996253,  0.0000000000000000},
      {1.8445621227254900,  3.5493377984336569,  0.0000000000000000},
      {1.8223484221036381,  3.5607940769385551,  0.0000000000000000},
      {1.8000636832069072,  3.5721112754536106,  0.0000000000000000},
      {1.7777087772551270,  3.5832889541607216,  0.0000000000000000},
      {1.7552845781895212,  3.5943266787014636,  0.0000000000000000},
      {1.7327919626384842,  3.6052240201939396,  0.0000000000000000},
      {1.7102318098832789,  3.6159805552494215,  0.0000000000000000},
      {1.6876050018236177,  3.6265958659887922,  0.0000000000000000},
      {1.6649124229431447,  3.6370695400587287,  0.0000000000000000},
      {1.6421549602748073,  3.6474011706477136,  0.0000000000000000},
      {1.6193335033661598,  3.6575903565018226,  0.0000000000000000},
      {1.5964489442445251,  3.6676367019402534,  0.0000000000000000},
      {1.5735021773820983,  3.6775398168707127,  0.0000000000000000},
      {1.5504940996609278,  3.6872993168044981,  0.0000000000000000},
      {1.5274256103378288,  3.6969148228714315,  0.0000000000000000},
      {1.5042976110091708,  3.7063859618345276,  0.0000000000000000},
      {1.4811110055756209,  3.7157123661044809,  0.0000000000000000},
      {1.4578667002067380,  3.7248936737538818,  0.0000000000000000},
      {1.4345656033055367,  3.7339295285312670,  0.0000000000000000},
      {1.4112086254729275,  3.7428195798749027,  0.0000000000000000},
      {1.3877966794720868,  3.7515634829263718,  0.0000000000000000},
      {1.3643306801927333,  3.7601608985439281,  0.0000000000000000},
      {1.3408115446153381,  3.7686114933156354,  0.0000000000000000},
      {1.3172401917752297,  3.7769149395722605,  0.0000000000000000},
      {1.2936175427266432,  3.7850709153999773,  0.0000000000000000},
      {1.2699445205066746,  3.7930791046528096,  0.0000000000000000},
      {1.2462220500991712,  3.8009391969648876,  0.0000000000000000},
      {1.2224510583985215,  3.8086508877624095,  0.0000000000000000},
      {1.1986324741734156,  3.8162138782754971,  0.0000000000000000},
      {1.1747672280304771,  3.8236278755496675,  0.0000000000000000},
      {1.1508562523778760,  3.8308925924572357,  0.0000000000000000},
      {1.1269004813888355,  3.8380077477083558,  0.0000000000000000},
      {1.1029008509650780,  3.8449730658619323,  0.0000000000000000},
      {1.0788582987002280,  3.8517882773362451,  0.0000000000000000},
      {1.0547737638431056,  3.8584531184193680,  0.0000000000000000},
      {1.0306481872610025,  3.8649673312793529,  0.0000000000000000},
      {1.0064825114028548,  3.8713306639741898,  0.0000000000000000},
      {0.9822776802623867,  3.8775428704615251,  0.0000000000000000},
      {0.9580346393411687,  3.8836037106081607,  0.0000000000000000},
      {0.9337543356116433,  3.8895129501993146,  0.0000000000000000},
      {0.9094377174800578,  3.8952703609476607,  0.0000000000000000},
      {0.8850857347493862,  3.9008757205021203,  0.0000000000000000},
      {0.8606993385821546,  3.9063288124564366,  0.0000000000000000},
      {0.8362794814632483,  3.9116294263575164,  0.0000000000000000},
      {0.8118271171626363,  3.9167773577135199,  0.0000000000000000},
      {0.7873432006980786,  3.9217724080017500,  0.0000000000000000},
      {0.7628286882977537,  3.9266143846762716,  0.0000000000000000},
      {0.7382845373628677,  3.9313031011753372,  0.0000000000000000},
      {0.7137117064301896,  3.9358383769285421,  0.0000000000000000},
      {0.6891111551345706,  3.9402200373637659,  0.0000000000000000},
      {0.6644838441713998,  3.9444479139138804,  0.0000000000000000},
      {0.6398307352590302,  3.9485218440232162,  0.0000000000000000},
      {0.6151527911011592,  3.9524416711537738,  0.0000000000000000},
      {0.5904509753491718,  3.9562072447912775,  0.0000000000000000},
      {0.5657262525644596,  3.9598184204508660,  0.0000000000000000},
      {0.5409795881806748,  3.9632750596826818,  0.0000000000000000},
      {0.5162119484659884,  3.9665770300771293,  0.0000000000000000},
      {0.4914243004852843,  3.9697242052699435,  0.0000000000000000},
      {0.4666176120623422,  3.9727164649470010,  0.0000000000000000},
      {0.4417928517419799,  3.9755536948489150,  0.0000000000000000},
      {0.4169509887521768,  3.9782357867753788,  0.0000000000000000},
      {0.3920929929661635,  3.9807626385892707,  0.0000000000000000},
      {0.3672198348644902,  3.9831341542205356,  0.0000000000000000},
      {0.3423324854970742,  3.9853502436698145,  0.0000000000000000},
      {0.3174319164452156,  3.9874108230118548,  0.0000000000000000},
      {0.2925190997836079,  3.9893158143986653,  0.0000000000000000},
      {0.2675950080423107,  3.9910651460624447,  0.0000000000000000},
      {0.2426606141687278,  3.9926587523182677,  0.0000000000000000},
      {0.2177168914895473,  3.9940965735665444,  0.0000000000000000},
      {0.1927648136726776,  3.9953785562952184,  0.0000000000000000},
      {0.1678053546891721,  3.9965046530817547,  0.0000000000000000},
      {0.1428394887751528,  3.9974748225948713,  0.0000000000000000},
      {0.1178681903936311,  3.9982890295960676,  0.0000000000000000},
      {0.0928924341967183,  3.9989472449407559,  0.0000000000000000},
      {0.0679131949863091,  3.9994494455797867,  0.0000000000000000},
      {0.0429314476804451,  3.9997956145583498,  0.0000000000000000},
      {0.0179473162133797,  3.9999857475001748,  0.0000000000000000},
      {-0.0070481598255116, 4.0000198345720470,  0.0000000000000000},
      {-0.0320540048934537, 3.9998976412473728,  0.0000000000000000},
      {-0.0570683886854493, 3.9996189563863940,  0.0000000000000000},
      {-0.0820803976546045, 3.9991838421382475,  0.0000000000000000},
      {-0.1070890539448629, 3.9985923181848841,  0.0000000000000000},
      {-0.1320933798737740, 3.9978444103225463,  0.0000000000000000},
      {-0.1570923979465454, 3.9969401504523621,  0.0000000000000000},
      {-0.1820851309006368, 3.9958795765812019,  0.0000000000000000},
      {-0.2070706017421564, 3.9946627328194930,  0.0000000000000000},
      {-0.2320478337844312, 3.9932896693795472,  0.0000000000000000},
      {-0.2570158506860018, 3.9917604425734243,  0.0000000000000000},
      {-0.2819736764887266, 3.9900751148106570,  0.0000000000000000},
      {-0.3069203356558671, 3.9882337545956750,  0.0000000000000000},
      {-0.3318548531101270, 3.9862364365250307,  0.0000000000000000},
      {-0.3567762542717087, 3.9840832412843596,  0.0000000000000000},
      {-0.3816835650963195, 3.9817742556451274,  0.0000000000000000},
      {-0.4065758121131814, 3.9793095724611125,  0.0000000000000000},
      {-0.4314520224629969, 3.9766892906646873,  0.0000000000000000},
      {-0.4563112239359042, 3.9739135152628018,  0.0000000000000000},
      {-0.4811524450094073, 3.9709823573328156,  0.0000000000000000},
      {-0.5059747148862684, 3.9678959340180024,  0.0000000000000000},
      {-0.5307770635323804, 3.9646543685228863,  0.0000000000000000},
      {-0.5555585217146061, 3.9612577901082995,  0.0000000000000000},
      {-0.5803181210385894, 3.9577063340862333,  0.0000000000000000},
      {-0.6050548939865270, 3.9540001418144208,  0.0000000000000000},
      {-0.6297678739549069, 3.9501393606907138,  0.0000000000000000},
      {-0.6544560952922250, 3.9461241441472019,  0.0000000000000000},
      {-0.6791185933366320, 3.9419546516441115,  0.0000000000000000},
      {-0.7037544044535854, 3.9376310486634600,  0.0000000000000000},
      {-0.7283625660734137, 3.9331535067024683,  0.0000000000000000},
      {-0.7529421167288814, 3.9285222032667608,  0.0000000000000000},
      {-0.7774920960926730, 3.9237373218633111,  0.0000000000000000},
      {-0.8020115450148749, 3.9187990519931439,  0.0000000000000000},
      {-0.8264995055603543, 3.9137075891438551,  0.0000000000000000},
      {-0.8509550210461535, 3.9084631347818131,  0.0000000000000000},
      {-0.8753771360787836, 3.9030658963442111,  0.0000000000000000},
      {-0.8997648965914951, 3.8975160872308390,  0.0000000000000000},
      {-0.9241173498814861, 3.8918139267956167,  0.0000000000000000},
      {-0.9484335446470649, 3.8859596403379379,  0.0000000000000000},
      {-0.9727125310247413, 3.8799534590937297,  0.0000000000000000},
      {-0.9969533606262907, 3.8737956202263208,  0.0000000000000000},
      {-1.0211550865757191, 3.8674863668170580,  0.0000000000000000},
      {-1.0453167635462024, 3.8610259478556914,  0.0000000000000000},
      {-1.0694374477969659, 3.8544146182305434,  0.0000000000000000},
      {-1.0935161972100591, 3.8476526387184320,  0.0000000000000000},
      {-1.1175520713271301, 3.8407402759743587,  0.0000000000000000},
      {-1.1415441313860715, 3.8336778025210023,  0.0000000000000000},
      {-1.1654914403576568, 3.8264654967379421,  0.0000000000000000},
      {-1.1893930629820542, 3.8191036428506626,  0.0000000000000000},
      {-1.2132480658053226, 3.8115925309193663,  0.0000000000000000},
      {-1.2370555172157987, 3.8039324568274848,  0.0000000000000000},
      {-1.2608144874804221, 3.7961237222700515,  0.0000000000000000},
      {-1.2845240487810061, 3.7881666347417760,  0.0000000000000000},
      {-1.3081832752503941, 3.7800615075249260,  0.0000000000000000},
      {-1.3317912430085805, 3.7718086596769727,  0.0000000000000000},
      {-1.3553470301987336, 3.7634084160180148,  0.0000000000000000},
      {-1.3788497170231200, 3.7548611071179914,  0.0000000000000000},
      {-1.4022983857789990, 3.7461670692836222,  0.0000000000000000},
      {-1.4256921208943845, 3.7373266445452011,  0.0000000000000000},
      {-1.4490300089637471, 3.7283401806430811,  0.0000000000000000},
      {-1.4723111387836234, 3.7192080310139977,  0.0000000000000000},
      {-1.4955346013881630, 3.7099305547771699,  0.0000000000000000},
      {-1.5186994900845328, 3.7005081167200999,  0.0000000000000000},
      {-1.5418049004882994, 3.6909410872842856,  0.0000000000000000},
      {-1.5648499305586692, 3.6812298425505792,  0.0000000000000000},
      {-1.5878336806336570, 3.6713747642244119,  0.0000000000000000},
      {-1.6107552534651710, 3.6613762396207701,  0.0000000000000000},
      {-1.6336137542539739, 3.6512346616489433,  0.0000000000000000},
      {-1.6564082906845814, 3.6409504287970762,  0.0000000000000000},
      {-1.6791379729600411, 3.6305239451164839,  0.0000000000000000},
      {-1.7018019138366165, 3.6199556202057579,  0.0000000000000000},
      {-1.7243992286583794, 3.6092458691946661,  0.0000000000000000},
      {-1.7469290353916844, 3.5983951127277987,  0.0000000000000000},
      {-1.7693904546595662, 3.5874037769480660,  0.0000000000000000},
      {-1.7917826097760043, 3.5762722934798958,  0.0000000000000000},
      {-1.8141046267800944, 3.5650010994123105,  0.0000000000000000},
      {-1.8363556344701264, 3.5535906372817028,  0.0000000000000000},
      {-1.8585347644375299, 3.5420413550544629,  0.0000000000000000},
      {-1.8806411511007266, 3.5303537061093602,  0.0000000000000000},
      {-1.9026739317388586, 3.5185281492197351,  0.0000000000000000},
      {-1.9246322465254306, 3.5065651485354463,  0.0000000000000000},
      {-1.9465152385617972, 3.4944651735646604,  0.0000000000000000},
      {-1.9683220539105806, 3.4822286991553795,  0.0000000000000000},
      {-1.9900518416289337, 3.4698562054767961,  0.0000000000000000},
      {-2.0117037538017173, 3.4573481780004283,  0.0000000000000000},
      {-2.0332769455745243, 3.4447051074810369,  0.0000000000000000},
      {-2.0547705751866308, 3.4319274899373671,  0.0000000000000000},
      {-2.0761838040037661, 3.4190158266326418,  0.0000000000000000},
      {-2.0975157965508249, 3.4059706240548984,  0.0000000000000000},
      {-2.1187657205443973, 3.3927923938970785,  0.0000000000000000},
      {-2.1399327469252096, 3.3794816530369411,  0.0000000000000000},
      {-2.1610160498904376, 3.3660389235167729,  0.0000000000000000},
      {-2.1820148069258658, 3.3524647325228587,  0.0000000000000000},
      {-2.2029281988379541, 3.3387596123648429,  0.0000000000000000},
      {-2.2237554097857304, 3.3249241004547603,  0.0000000000000000},
      {-2.2444956273126122, 3.3109587392859936,  0.0000000000000000},
      {-2.2651480423780219, 3.2968640764119406,  0.0000000000000000},
      {-2.2857118493889375, 3.2826406644245525,  0.0000000000000000},
      {-2.3061862462312583, 3.2682890609326125,  0.0000000000000000},
      {-2.3265704343010660, 3.2538098285398758,  0.0000000000000000},
      {-2.3468636185357212, 3.2392035348229733,  0.0000000000000000},
      {-2.3670650074448507, 3.2244707523091538,  0.0000000000000000},
      {-2.3871738131411639, 3.2096120584537906,  0.0000000000000000},
      {-2.4071892513711699, 3.1946280356177534,  0.0000000000000000},
      {-2.4271105415456811, 3.1795192710445317,  0.0000000000000000},
      {-2.4469369067702704, 3.1642863568372115,  0.0000000000000000},
      {-2.4666675738754917, 3.1489298899352329,  0.0000000000000000},
      {-2.4863017734470163, 3.1334504720909768,  0.0000000000000000},
      {-2.5058387398555877, 3.1178487098461627,  0.0000000000000000},
      {-2.5252777112868454, 3.1021252145080354,  0.0000000000000000},
      {-2.5446179297709937, 3.0862806021254157,  0.0000000000000000},
      {-2.5638586412123279, 3.0703154934645092,  0.0000000000000000},
      {-2.5829990954185820, 3.0542305139845727,  0.0000000000000000},
      {-2.6020385461301676, 3.0380262938133855,  0.0000000000000000},
      {-2.6209762510492118, 3.0217034677225163,  0.0000000000000000},
      {-2.6398114718684749, 3.0052626751024571,  0.0000000000000000},
      {-2.6585434743000995, 2.9887045599375255,  0.0000000000000000},
      {-2.6771715281041928, 2.9720297707806314,  0.0000000000000000},
      {-2.6956949071172680, 2.9552389607278196,  0.0000000000000000},
      {-2.7141128892805106, 2.9383327873926968,  0.0000000000000000},
      {-2.7324247566678967, 2.9213119128806069,  0.0000000000000000},
      {-2.7506297955141461, 2.9041770037627108,  0.0000000000000000},
      {-2.7687272962424903, 2.8869287310498177,  0.0000000000000000},
      {-2.7867165534923246, 2.8695677701661078,  0.0000000000000000},
      {-2.8045968661466416, 2.8520948009226315,  0.0000000000000000},
      {-2.8223675373593435, 2.8345105074906711,  0.0000000000000000},
      {-2.8400278745823453, 2.8168155783749218,  0.0000000000000000},
      {-2.8575771895925577, 2.7990107063864973,  0.0000000000000000},
      {-2.8750147985186492, 2.7810965886157732,  0.0000000000000000},
      {-2.8923400218676818, 2.7630739264050774,  0.0000000000000000},
      {-2.9095521845515488, 2.7449434253211775,  0.0000000000000000},
      {-2.9266506159132382, 2.7267057951276548,  0.0000000000000000},
      {-2.9436346497529633, 2.7083617497570645,  0.0000000000000000},
      {-2.9605036243540428, 2.6899120072829725,  0.0000000000000000},
      {-2.9772568825086987, 2.6713572898917990,  0.0000000000000000},
      {-2.9938937715435894, 2.6526983238545365,  0.0000000000000000},
      {-3.0104136433452244, 2.6339358394982733,  0.0000000000000000},
      {-3.0268158543851875, 2.6150705711775899,  0.0000000000000000},
      {-3.0430997657451595, 2.5961032572457619,  0.0000000000000000},
      {-3.0592647431417843, 2.5770346400258641,  0.0000000000000000},
      {-3.0753101569513408, 2.5578654657816471,  0.0000000000000000},
      {-3.0912353822342395, 2.5385964846883233,  0.0000000000000000},
      {-3.1070397987593337, 2.5192284508031766,  0.0000000000000000},
      {-3.1227227910280408, 2.4997621220359929,  0.0000000000000000},
      {-3.1382837482982886, 2.4801982601194092,  0.0000000000000000},
      {-3.1537220646082642, 2.4605376305790312,  0.0000000000000000},
      {-3.1690371387999887, 2.4407810027034733,  0.0000000000000000},
      {-3.1842283745426849, 2.4209291495142145,  0.0000000000000000},
      {-3.1992951803559855, 2.4009828477353041,  0.0000000000000000},
      {-3.2142369696329158, 2.3809428777629584,  0.0000000000000000},
      {-3.2290531606627169, 2.3608100236349863,  0.0000000000000000},
      {-3.2437431766534615, 2.3405850730000552,  0.0000000000000000},
      {-3.2583064457544655, 2.3202688170868844,  0.0000000000000000},
      {-3.2727424010785571, 2.2998620506732106,  0.0000000000000000},
      {-3.2870504807240648, 2.2793655720547026,  0.0000000000000000},
      {-3.3012301277967104, 2.2587801830136436,  0.0000000000000000},
      {-3.3152807904312205, 2.2381066887875951,  0.0000000000000000},
      {-3.3292019218127971, 2.2173458980378005,  0.0000000000000000},
      {-3.3429929801983649, 2.1964986228175563,  0.0000000000000000},
      {-3.3566534289376229, 2.1755656785403930,  0.0000000000000000},
      {-3.3701827364939065, 2.1545478839481502,  0.0000000000000000},
      {-3.3835803764648458, 2.1334460610789181,  0.0000000000000000},
      {-3.3968458276027991, 2.1122610352348330,  0.0000000000000000},
      {-3.4099785738351422, 2.0909936349497853,  0.0000000000000000},
      {-3.4229781042842808, 2.0696446919569529,  0.0000000000000000},
      {-3.4358439132875285, 2.0482150411562592,  0.0000000000000000},
      {-3.4485755004167338, 2.0267055205816500,  0.0000000000000000},
      {-3.4611723704977218, 2.0051169713683250,  0.0000000000000000},
      {-3.4736340336295308, 1.9834502377197587,  0.0000000000000000},
      {-3.4859600052034381, 1.9617061668746878,  0.0000000000000000},
      {-3.4981498059217784, 1.9398856090739152,  0.0000000000000000},
      {-3.5102029618165611, 1.9179894175270387,  0.0000000000000000},
      {-3.5221190042678656, 1.8960184483790363,  0.0000000000000000},
      {-3.5338974700220431, 1.8739735606767636,  0.0000000000000000},
      {-3.5455379012097046, 1.8518556163353082,  0.0000000000000000},
      {-3.5570398453634811, 1.8296654801042664,  0.0000000000000000},
      {-3.5684028554356093, 1.8074040195338696,  0.0000000000000000},
      {-3.5796264898152583, 1.7850721049410578,  0.0000000000000000},
      {-3.5907103123456845, 1.7626706093753639,  0.0000000000000000},
      {-3.6016538923411558, 1.7402004085847964,  0.0000000000000000},
      {-3.6124568046036520, 1.7176623809814995,  0.0000000000000000},
      {-3.6231186294393782, 1.6950574076074363,  0.0000000000000000},
      {-3.6336389526750335, 1.6723863720998355,  0.0000000000000000},
      {-3.6440173656738812, 1.6496501606566651,  0.0000000000000000},
      {-3.6542534653515975, 1.6268496620019082,  0.0000000000000000},
      {-3.6643468541919120, 1.6039857673507991,  0.0000000000000000},
      {-3.6742971402620017, 1.5810593703749318,  0.0000000000000000},
      {-3.6841039372277153, 1.5580713671672881,  0.0000000000000000},
      {-3.6937668643685293, 1.5350226562071765,  0.0000000000000000},
      {-3.7032855465923062, 1.5119141383250521,  0.0000000000000000},
      {-3.7126596144498532, 1.4887467166672710,  0.0000000000000000},
      {-3.7218887041492179, 1.4655212966607585,  0.0000000000000000},
      {-3.7309724575697958, 1.4422387859775487,  0.0000000000000000},
      {-3.7399105222761966, 1.4189000944992924,  0.0000000000000000},
      {-3.7487025515319079, 1.3955061342816288,  0.0000000000000000},
      {-3.7573482043127133, 1.3720578195185174,  0.0000000000000000},
      {-3.7658471453199107, 1.3485560665064400,  0.0000000000000000},
      {-3.7741990449932805, 1.3250017936085656,  0.0000000000000000},
      {-3.7824035795238609, 1.3013959212188022,  0.0000000000000000},
      {-3.7904604308664651, 1.2777393717257963,  0.0000000000000000},
      {-3.7983692867520005, 1.2540330694768205,  0.0000000000000000},
      {-3.8061298406995423, 1.2302779407416300,  0.0000000000000000},
      {-3.8137417920282122, 1.2064749136761974,  0.0000000000000000},
      {-3.8212048458687677, 1.1826249182864137,  0.0000000000000000},
      {-3.8285187131750451, 1.1587288863916960,  0.0000000000000000},
      {-3.8356831107351148, 1.1347877515885179,  0.0000000000000000},
      {-3.8426977611822206, 1.1108024492139110,  0.0000000000000000},
      {-3.8495623930055274, 1.0867739163088279,  0.0000000000000000},
      {-3.8562767405605740, 1.0627030915815343,  0.0000000000000000},
      {-3.8628405440795648, 1.0385909153708255,  0.0000000000000000},
      {-3.8692535496813862, 1.0144383296092956,  0.0000000000000000},
      {-3.8755155093814042, 0.9902462777864391,  0.0000000000000000},
      {-3.8816261811010468, 0.9660157049117712,  0.0000000000000000},
      {-3.8875853286771331, 0.9417475574778402,  0.0000000000000000},
      {-3.8933927218709927, 0.9174427834232162,  0.0000000000000000},
      {-3.8990481363773304, 0.8931023320953920,  0.0000000000000000},
      {-3.9045513538328791, 0.8687271542136467,  0.0000000000000000},
      {-3.9099021618248173, 0.8443182018318777,  0.0000000000000000},
      {-3.9151003538989402, 0.8198764283013223,  0.0000000000000000},
      {-3.9201457295676132, 0.7954027882332890,  0.0000000000000000},
      {-3.9250380943174861, 0.7708982374618123,  0.0000000000000000},
      {-3.9297772596169818, 0.7463637330062525,  0.0000000000000000},
      {-3.9343630429235272, 0.7218002330338780,  0.0000000000000000},
      {-3.9387952676905820, 0.6972086968223636,  0.0000000000000000},
      {-3.9430737633744166, 0.6725900847222861,  0.0000000000000000},
      {-3.9471983654406571, 0.6479453581195598,  0.0000000000000000},
      {-3.9511689153705856, 0.6232754793978168,  0.0000000000000000},
      {-3.9549852606672316, 0.5985814119007695,  0.0000000000000000},
      {-3.9586472548612064, 0.5738641198945555,  0.0000000000000000},
      {-3.9621547575163030, 0.5491245685299745,  0.0000000000000000},
      {-3.9655076342348745, 0.5243637238047911,  0.0000000000000000},
      {-3.9687057566629602, 0.4995825525258990,  0.0000000000000000},
      {-3.9717490024951889, 0.4747820222715621,  0.0000000000000000},
      {-3.9746372554794434, 0.4499631013535177,  0.0000000000000000},
      {-3.9773704054212629, 0.4251267587791490,  0.0000000000000000},
      {-3.9799483481880853, 0.4002739642135583,  0.0000000000000000},
      {-3.9823709857130893, 0.3754056879416481,  0.0000000000000000},
      {-3.9846382259992024, 0.3505229008301919,  0.0000000000000000},
      {-3.9867499831215745, 0.3256265742898304,  0.0000000000000000},
      {-3.9887061772345378, 0.3007176802370988,  0.0000000000000000},
      {-3.9905067345607170, 0.2757971910564677,  0.0000000000000000},
      {-3.9921515874456732, 0.2508660795620572,  0.0000000000000000},
      {-3.9936406741668034, 0.2259253189605318,  0.0000000000000000},
      {-3.9949739396582924, 0.2009758828095986,  0.0000000000000000},
      {-3.9961513328161296, 0.1760187449927260,  0.0000000000000000},
      {-3.9971728165653970, 0.1510548796332886,  0.0000000000000000},
      {-3.9980383302972218, 0.1260852612348658,  0.0000000000000000},
      {-3.9987479300620961, 0.1011108639771932,  0.0000000000000000},
      {-3.9993012653718054, 0.0761326641635289,  0.0000000000000000},
      {-3.9996995317896138, 0.0511516309065405,  0.0000000000000000},
      {-3.9999381838302375, 0.0261687607084606,  0.0000000000000000},
      {-4.0000031485730219, 0.0092524262180829,  0.0000000000000000},
      {-3.9999995925142771, 0.0005339034719475,  0.0000000000000000},
      {-4.0000005197961164, 0.0001389243049350,  0.0000000000000000},
      {-4.0000000158932201, 0.0000043590887876,  0.0000000000000000},
      {-4.0000000000000000, 0.0000000000000007,  0.0000000000000000},
    };
    double weights2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double ctrlpt_tol2 = SPAresabs;
    int num_knots2 = 872;
    double knots2[] = {0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,  0.0249976004775398,  0.0499950785506011,  0.0749924341775603,  0.0999896673143787,  0.1249867779146005,  0.1499837659293504,  0.1749806313073295,
                       0.1999773739948083,  0.2249739939356284,  0.2499704910711892,  0.2749668653404538,  0.2999631166799369,  0.3249592450237038,  0.3499552503033615,  0.3749511324480568,  0.3999468913844695,  0.4249425270368038,  0.4499380393267874,
                       0.4749334281736641,  0.4999286934941817,  0.5249238352025933,  0.5499188532106466,  0.5749137474275785,  0.5999085177601033,  0.6249031641124150,  0.6498976863861669,  0.6748920844804744,  0.6998863582919014,  0.7248805077144538,
                       0.7498745326395723,  0.7748684329561211,  0.7998622085503787,  0.8248558593060337,  0.8498493851041681,  0.8748427858232539,  0.8998360613391417,  0.9248292115250492,  0.9498222362515497,  0.9748151353865669,  0.9998079087953593,
                       1.0248005563405096,  1.0497930778819184,  1.0747854732767865,  1.0997777423796080,  1.1247698850421528,  1.1497619011134612,  1.1747537904398262,  1.1997455528647845,  1.2247371882291025,  1.2497286963707617,  1.2747200771249469,
                       1.2997113303240324,  1.3247024557975657,  1.3496934533722573,  1.3746843228719643,  1.3996750641176732,  1.4246656769274901,  1.4496561611166234,  1.4746465164973646,  1.4996367428790773,  1.5246268400681793,  1.5496168078681261,
                       1.5746066460793933,  1.5995963544994620,  1.6245859329228012,  1.6495753811408480,  1.6745646989419916,  1.6995538861115538,  1.7245429424317722,  1.7495318676817797,  1.7745206616375899,  1.7995093240720701,  1.8244978547549258,
                       1.8494862534526835,  1.8744745199286661,  1.8994626539429722,  1.9244506552524574,  1.9494385236107126,  1.9744262587680397,  1.9994138604714327,  2.0244013284645539,  2.0493886624877127,  2.0743758622778374,  2.0993629275684569,
                       2.1243498580896749,  2.1493366535681462,  2.1743233137270530,  2.1993098382860774,  2.2242962269613766,  2.2492824794655579,  2.2742685955076514,  2.2992545747930886,  2.3242404170236646,  2.3492261218975221,  2.3742116891091154,
                       2.3991971183491865,  2.4241824093047346,  2.4491675616589870,  2.4741525750913733,  2.4991374492774852,  2.5241221838890584,  2.5491067785939316,  2.5740912330560253,  2.5990755469352962,  2.6240597198877165,  2.6490437515652352,
                       2.6740276416157482,  2.6990113896830605,  2.7240235537898085,  2.7490393756696898,  2.7740550546132190,  2.7990705909879621,  2.8240859851572688,  2.8491012374803293,  2.8741163483122096,  2.8991313180038847,  2.9241461469022734,
                       2.9491608353502743,  2.9741753836867919,  2.9991897922467783,  3.0242040613612589,  3.0492181913573648,  3.0742321825583638,  3.0992460352836950,  3.1242597498489935,  3.1492733265661230,  3.1742867657432061,  3.1993000676846490,
                       3.2243132326911739,  3.2493262610598435,  3.2743391530840928,  3.2993519090537524,  3.3243645292550754,  3.3493770139707677,  3.3743893634800095,  3.3994015780584812,  3.4244136579783890,  3.4494256035084940,  3.4744374149141275,
                       3.4994490924572217,  3.5244606363963324,  3.5494720469866619,  3.5744833244800791,  3.5994944691251445,  3.6245054811671324,  3.6495163608480516,  3.6745271084066689,  3.6995377240785268,  3.7245482080959640,  3.7495585606881416,
                       3.7745687820810563,  3.7995788724975661,  3.8245888321574060,  3.8495986612772053,  3.8746083600705106,  3.8996179287478023,  3.9246273675165142,  3.9496366765810476,  3.9746458561427924,  3.9996549064001456,  4.0246638275485234,
                       4.0496726197803818,  4.0746812832852308,  4.0996898182496526,  4.1246982248573154,  4.1497065032889875,  4.1747146537225586,  4.1997226763330504,  4.2247305712926284,  4.2497383387706256,  4.2747459789335442,  4.2997534919450802,
                       4.3247608779661348,  4.3497681371548209,  4.3747752696664843,  4.3997822756537133,  4.4247891552663541,  4.4497959086515149,  4.4748025359535903,  4.4998090373142619,  4.5248154128725178,  4.5498216627646606,  4.5748277871243195,
                       4.5998337860824599,  4.6248396597673942,  4.6498454083047953,  4.6748510318177035,  4.6998565304265369,  4.7248619042491029,  4.7498671534006052,  4.7748722779936585,  4.7998772781382897,  4.8248821539419531,  4.8498869055095382,
                       4.8748915329433729,  4.8998960363432396,  4.9249004158063778,  4.9499046714274932,  4.9749088032987654,  4.9999128115098577,  5.0249166961479190,  5.0499204572975955,  5.0749240950410339,  5.0999276094578949,  5.1249310006253488,
                       5.1499342686180913,  5.1749374135083430,  5.1999404353658596,  5.2249433342579348,  5.2499461102494056,  5.2749487634026586,  5.2999512937776396,  5.3249537014318422,  5.3499559864203352,  5.3749581487957503,  5.3999601886082900,
                       5.4249621059057347,  5.4499639007334455,  5.4749655731343649,  5.4999671231490233,  5.5249685508155411,  5.5499698561696347,  5.5749710392446099,  5.5999721000713798,  5.6249730386784504,  5.6499738550919343,  5.6749745493355510,
                       5.6999751214306267,  5.7249755713960955,  5.7499758992485024,  5.7749761050020050,  5.7999761886683716,  5.8249761502569894,  5.8499759897748556,  5.8749757072265840,  5.8999753026144051,  5.9249747759381641,  5.9499741271953219,
                       5.9749733563809579,  5.9999724634877643,  6.0249714485060508,  6.0499703114237358,  6.0749690522263560,  6.0999676708970609,  6.1249661674166074,  6.1499645417633610,  6.1749627939133003,  6.1999609238400053,  6.2249589315146618,
                       6.2499568169060566,  6.2749545799805775,  6.2999522207022052,  6.3249497390325180,  6.3499471349306829,  6.3749444083534579,  6.3999415592551792,  6.4249385875877687,  6.4499354933007238,  6.4749322763411170,  6.4999289366535864,
                       6.5249254741803373,  6.5499218888611335,  6.5749181806332970,  6.5999143494316961,  6.6249103951887500,  6.6499063178344144,  6.6749021172961784,  6.6998977934990620,  6.7248933463656098,  6.7498887758158803,  6.7748840817674463,
                       6.7998792641353800,  6.8248743228322564,  6.8498692577681348,  6.8748640688505622,  6.8998587559845594,  6.9248533190726205,  6.9498477580146920,  6.9748420727081815,  6.9998362630479365,  7.0248303289262406,  7.0498242702328042,
                       7.0748180868547630,  7.0998117786766519,  7.1248053455804161,  7.1497987874453859,  7.1747921041482732,  7.1997852955631627,  7.2247783615614996,  7.2497713020120820,  7.2747641167810420,  7.2997568057318469,  7.3247493687252803,
                       7.3497418056194297,  7.3747341162696793,  7.3997263005286991,  7.4247183582464293,  7.4497102892700662,  7.4747020934440540,  7.4996937706100733,  7.5246853206070226,  7.5496767432710064,  7.5746680384353233,  7.5996592059304557,
                       7.6246502455840472,  7.6496411572208940,  7.6746319406629286,  7.6996225957292079,  7.7246131222358914,  7.7496035199962332,  7.7745937888205630,  7.7995839285162676,  7.8245739388877773,  7.8495638197365505,  7.8745535708610586,
                       7.8995431920567585,  7.9245326831160865,  7.9495220438284377,  7.9745112739801431,  7.9995003733544596,  8.0244893417315417,  8.0494781788884282,  8.0744668845990244,  8.0994554586340790,  8.1244439007611682,  8.1494322107446671,
                       8.1744203883457374,  8.1994084333223043,  8.2243963454290334,  8.2493841244173147,  8.2743717700352288,  8.2993592820275381,  8.3243466601356531,  8.3493339040976213,  8.3743210136480890,  8.3993079885182915,  8.4242948284360200,
                       8.4492815331255997,  8.4742681023078656,  8.4992545357001408,  8.5242408330161989,  8.5492269939662542,  8.5742130182569198,  8.5991989055911908,  8.6241846556684134,  8.6491702681842604,  8.6741557428306972,  8.6991410792959538,
                       8.7241262772645047,  8.7491113364170321,  8.7740962564303917,  8.7990810369775900,  8.8240656777277522,  8.8490501783460882,  8.8740345384938628,  8.8990187578283635,  8.9240028360028667,  8.9489867726666024,  8.9739705674647272,
                       8.9989662665578400,  9.0239821355570768,  9.0489978614980568,  9.0740134447497613,  9.0990288856769173,  9.1240441846400788,  9.1490593419956685,  9.1740743580960000,  9.1990892332893246,  9.2241039679198629,  9.2491185623278263,
                       9.2741330168494667,  9.2991473318170961,  9.3241615075591238,  9.3491755444000866,  9.3741894426606809,  9.3992032026577892,  9.4242168247045139,  9.4492303091102041,  9.4742436561804872,  9.4992568662172943,  9.5242699395188897,
                       9.5492828763798983,  9.5742956770913352,  9.5993083419406275,  9.6243208712116441,  9.6493332651847243,  9.6743455241366956,  9.6993576483409072,  9.7243696380672482,  9.7493814935821774,  9.7743932151487432,  9.7994048030266114,
                       9.8244162574720821,  9.8494275787381227,  9.8744387670743770,  9.8994498227271990,  9.9244607459396708,  9.9494715369516218,  9.9744821959996539,  9.9994927233171591,  10.0245031191343408, 10.0495133836782351, 10.0745235171727323,
                       10.0995335198385909, 10.1245433918934591, 10.1495531335518994, 10.1745627450253959, 10.1995722265223847, 10.2245815782482641, 10.2495908004054126, 10.2745998931932085, 10.2996088568080495, 10.3246176914433612, 10.3496263972896223,
                       10.3746349745343771, 10.3996434233622512, 10.4246517439549660, 10.4496599364913560, 10.4746680011473856, 10.4996759380961588, 10.5246837475079378, 10.5496914295501565, 10.5746989843874335, 10.5997064121815843, 10.6247137130916407,
                       10.6497208872738582, 10.6747279348817301, 10.6997348560660033, 10.7247416509746873, 10.7497483197530670, 10.7747548625437162, 10.7997612794865070, 10.8247675707186257, 10.8497737363745799, 10.8747797765862089, 10.8997856914827000,
                       10.9247914811905904, 10.9497971458337862, 10.9748026855335681, 10.9998081004086021, 11.0248133905749484, 11.0498185561460716, 11.0748235972328484, 11.0998285139435797, 11.1248333063839979, 11.1498379746572738, 11.1748425188640237,
                       11.1998469391023274, 11.2248512354677192, 11.2498554080532127, 11.2748594569492973, 11.2998633822439469, 11.3248671840226312, 11.3498708623683218, 11.3748744173614931, 11.3998778490801342, 11.4248811575997582, 11.4498843429933963,
                       11.4748874053316161, 11.4998903446825196, 11.5248931611117538, 11.5498958546825108, 11.5748984254555349, 11.5999008734891316, 11.6249031988391653, 11.6499054015590673, 11.6749074816998419, 11.6999094393100656, 11.7249112744358932,
                       11.7499129871210641, 11.7749145774069035, 11.7999160453323242, 11.8249173909338303, 11.8499186142455226, 11.8749197152991020, 11.8999206941238658, 11.9249215507467152, 11.9499222851921552, 11.9749228974823012, 11.9999233876368727,
                       12.0249237556732016, 12.0499240016062306, 12.0749241254485149, 12.0999241272102243, 12.1249240068991426, 12.1499237645206666, 12.1749234000778124, 12.1999229135712106, 12.2249223049991080, 12.2499215743573657, 12.2749207216394627,
                       12.2999197468364905, 12.3249186499371550, 12.3499174309277784, 12.3749160897922952, 12.3999146265122491, 12.4249130410667963, 12.4499113334326967, 12.4749095035843229, 12.4999075514936475, 12.5249054771302486, 12.5499032804613009,
                       12.5749009614515792, 12.5998985200634515, 12.6248959562568803, 12.6498932699894144, 12.6748904612161901, 12.6998875298899225, 12.7248844759609092, 12.7498812993770194, 12.7748780000836923, 12.7998745780239354, 12.8248710331383169,
                       12.8498673653649611, 12.8748635746395461, 12.8998596608952987, 12.9248556240629817, 12.9498514640708997, 12.9748471808448862, 12.9998427743083003, 13.0248382443820194, 13.0498335909844343, 13.0748288140314415, 13.0998239134364365,
                       13.1248188891103101, 13.1498137409614362, 13.1748084688956677, 13.1998030728163300, 13.2247975526242119, 13.2497919082175546, 13.2747861394920488, 13.2997802463408217, 13.3247742286544355, 13.3497680863208714, 13.3747618192255224,
                       13.3997554272511863, 13.4247489102780531, 13.4497422681837016, 13.4747355008430798, 13.4997286081285033, 13.5247215899096407, 13.5497144460535051, 13.5747071764244396, 13.5996997808841122, 13.6246922592915016, 13.6496846115028827,
                       13.6746768373718179, 13.6996689367491467, 13.7246609094829708, 13.7496527554186443, 13.7746444743987553, 13.7996360662631190, 13.8246275308487618, 13.8496188679899088, 13.8746100775179677, 13.8996011592615201, 13.9245921130463000,
                       13.9495829386951833, 13.9745736360281754, 13.9995642048623914, 14.0245546450120440, 14.0495449562884254, 14.0745351384998933, 14.0995251914518533, 14.1245151149467461, 14.1495049087840208, 14.1744945727601337, 14.1994841066685158,
                       14.2244735102995659, 14.2494627834406238, 14.2744519258759599, 14.2994409373867519, 14.3244298177510689, 14.3494185667438465, 14.3744071841368761, 14.3993956696987784, 14.4243840231949854, 14.4493722443877193, 14.4743603330359711,
                       14.4993482888954830, 14.5243361117187231, 14.5493238012548645, 14.5743113572497638, 14.5992987794459381, 14.6242860675825437, 14.6492732213953509, 14.6742602406167162, 14.6992471249755692, 14.7242338741973775, 14.7492204880041289,
                       14.7742069661143027, 14.7991933082428453, 14.8241795141011448, 14.8491655833970029, 14.8741515158346083, 14.8991373111145116, 14.9241229689335952, 14.9491084889850487, 14.9740938709583364, 14.9990791145391693, 15.0240642194094800,
                       15.0490491852473891, 15.0740340117271732, 15.0990186985192381, 15.1240032452900852, 15.1489876517022815, 15.1739719174144252, 15.1989560420811163, 15.2239400253529240, 15.2489238668763463, 15.2739101194863700, 15.2989260356386918,
                       15.3239418086104688, 15.3489574387720431, 15.3739729264895217, 15.3989882721248286, 15.4240034760357414, 15.4490185385759222, 15.4740334600949545, 15.4990482409383805, 15.5240628814477279, 15.5490773819605490, 15.5740917428104471,
                       15.5991059643271139, 15.6241200468363566, 15.6491339906601308, 15.6741477961165714, 15.6991614635200207, 15.7241749931810606, 15.7491883854065389, 15.7742016404995997, 15.7992147587597120, 15.8242277404826961, 15.8492405859607484,
                       15.8742532954824753, 15.8992658693329147, 15.9242783077935623, 15.9492906111424002, 15.9743027796539181, 15.9993148135991419, 16.0243267132456566, 16.0493384788576314, 16.0743501106958391, 16.0993616090176879, 16.1243729740772359,
                       16.1493842061252195, 16.1743953054090746, 16.1994062721729541, 16.2244171066577572, 16.2494278091011459, 16.2744383797375640, 16.2994488187982647, 16.3244591265113250, 16.3494693031016638, 16.3744793487910698, 16.3994892637982126,
                       16.4244990483386673, 16.4495087026249287, 16.4745182268664365, 16.4995276212695856, 16.5245368860377440, 16.5495460213712775, 16.5745550274675608, 16.5995639045209984, 16.6245726527230353, 16.6495812722621785, 16.6745897633240148,
                       16.6995981260912174, 16.7246063607435680, 16.7496144674579739, 16.7746224464084825, 16.7996302977662850, 16.8246380216997480, 16.8496456183744137, 16.8746530879530177, 16.8996604305955067, 16.9246676464590458, 16.9496747356980393,
                       16.9746816984641349, 16.9996885349062410, 17.0246952451705376, 17.0497018294004903, 17.0747082877368612, 17.0997146203177159, 17.1247208272784412, 17.1497269087517559, 17.1747328648677176, 17.1997386957537337, 17.2247444015345756,
                       17.2497499823323892, 17.2747554382666948, 17.2997607694544122, 17.3247659760098571, 17.3497710580447588, 17.3747760156682638, 17.3997808489869499, 17.4247855581048263, 17.4497901431233515, 17.4747946041414366, 17.4997989412554560,
                       17.5248031545592511, 17.5498072441441408, 17.5748112100989253, 17.5998150525099000, 17.6248187714608555, 17.6498223670330852, 17.6748258393053987, 17.6998291883541228, 17.7248324142531040, 17.7498355170737163, 17.7748384968848754,
                       17.7998413537530382, 17.8248440877421999, 17.8498466989139111, 17.8748491873272819, 17.8998515530389746, 17.9248537961032248, 17.9498559165718312, 17.9748579144941694, 17.9998597899171919, 18.0248615428854357, 18.0498631734410147,
                       18.0748646816236374, 18.0998660674706002, 18.1248673310167945, 18.1498684722947097, 18.1748694913344337, 18.1998703881636565, 18.2248711628076698, 18.2498718152893780, 18.2748723456292872, 18.2998727538455128, 18.3248730399537862,
                       18.3498732039674479, 18.3748732458974509, 18.3998731657523642, 18.4248729635383732, 18.4498726392592758, 18.4748721929164859, 18.4998716245090336, 18.5248709340335651, 18.5498701214843464, 18.5748691868532525, 18.5998681301297779,
                       18.6248669513010228, 18.6498656503517104, 18.6748642272641732, 18.6998626820183524, 18.7248610145917951, 18.7498592249596605, 18.7748573130947101, 18.7998552789673106, 18.8248531225454308, 18.8498508437946306, 18.8748484426780756,
                       18.8998459191565154, 18.9248432731882943, 18.9498405047293446, 18.9748376137331753, 18.9998346001508800, 19.0248314639311324, 19.0498282050201659, 19.0748248233617943, 19.0998213188973835, 19.1248176915658696, 19.1498139413037265,
                       19.1748100680449944, 19.1998060717212446, 19.2248019522615934, 19.2497977095926878, 19.2747933436387022, 19.2997888543213314, 19.3247842415597830, 19.3497795052707744, 19.3747746453685252, 19.3997696617647541, 19.4247645543686609,
                       19.4497593230869334, 19.4747539678237267, 19.4997484884806624, 19.5247428849568223, 19.5497371571487371, 19.5747313049503795, 19.5997253282531574, 19.6247192269458992, 19.6497130009148542, 19.6747066500436709, 19.6997001742134046,
                       19.7246935733024884, 19.7496868471867408, 19.7746799957393407, 19.7996730188308341, 19.8246659163291028, 19.8496586880993746, 19.8746513340041986, 19.8996438539034379, 19.9246362476542593, 19.9496285151111188, 19.9746206561257544,
                       19.9996126705471688, 20.0246045582216183, 20.0495963189926059, 20.0745879527008597, 20.0995794591843264, 20.1245708382781530, 20.1495620898146797, 20.1745532136234154, 20.1995442095310338, 20.2245350773613524, 20.2495258169353249,
                       20.2745164280710171, 20.2995069105835988, 20.3244972642853234, 20.3494874889855168, 20.3744775844905597, 20.3994675506038661, 20.4244573871258766, 20.4494470938540296, 20.4744366705827581, 20.4994261171034537, 20.5244154332044708,
                       20.5494046186710904, 20.5743936732855097, 20.5993825968268212, 20.6243713890709977, 20.6493600497908645, 20.6743485787560850, 20.6993369757331465, 20.7243252404853280, 20.7493133727726864, 20.7743013723520349, 20.7992892389769217,
                       20.8242769723976089, 20.8492645723610437, 20.8742520386108446, 20.8992393708872797, 20.9242265689272315, 20.9492136324641827, 20.9742005612281979, 20.9991873549458816, 21.0241740133403745, 21.0491605361313070, 21.0741469230347960,
                       21.0991331737633985, 21.1241192880261011, 21.1491052655282843, 21.1740911059716979, 21.1990768090544393, 21.2240623744709112, 21.2490478019118072, 21.2740330910640800, 21.2990182416109057, 21.3240032532316626, 21.3489881256018990,
                       21.3739728583932909, 21.3989574512736347, 21.4239419039067904, 21.4489262159526710, 21.4739103870671926, 21.4988944169022531, 21.5238783051056934, 21.5488620513212688, 21.5496432855247413, 21.5500339065747859, 21.5500469839280662,
                       21.5500469839280662, 21.5500469839280662, 21.5500469839280662};
    double knot_tol2 = SPAresabs;
    const int& dimension2 = 3;

    bs3_curve bs2 = bs3_curve_from_ctrlpts(degree2, rational2, closed2, periodic2, num_ctrlpts2, ctrlpts2, weights2, ctrlpt_tol2, num_knots2, knots2, knot_tol2, dimension2);
    exact_int_cur* cur2 = ACIS_NEW exact_int_cur(bs2);
    intcurve* ic2 = ACIS_NEW intcurve(cur2);

    clock_t tic, toc;
    tic = clock();
    curve_curve_int* acis_inters = int_cur_cur(*ic, *ic2, *(SPAbox*)nullptr, 1e-3);
    toc = clock();
    
    tic = clock();
    curve_curve_int* gme_inters = answer_int_cur_cur(*ic, *ic2, *(SPAbox*)nullptr, 1e-3);
    toc = clock();
    
        pop_cache(acis_inters);
    pop_cache(gme_inters);
    ACIS_DELETE ic;
    ACIS_DELETE ic2;
}

TEST_F(NurbsNurbsIntrTest, TestBug80) {
        int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 8;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0,                     0,                       0.5               },
      {0.001666621333426541,  0,                       0.5               },
      {0.0012918155441886854, 1.451617907544928e-16,   0.4999999999999999},
      {0.1675155355113967,    9.357100451090104e-14,   0.4999999999999999},
      {0.33310298812101924,   0,                       0.5               },
      {0.49912696048709454,   0,                       0.5               },
      {0.49956348024354724,   -2.7780366602908225e-20, 0.5               },
      {0.5,                   0,                       0.5               },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 12;
    const double bs3_knots_cur1[] = {
      -0.0019088020727564157, -0.0019088020727564157, -0.0019088020727564157, -0.0019088020727564157, 0, 0, 0.49676235782886763, 0.49676235782886763, 0.49807191709822585, 0.49807191709822585, 0.49807191709822585, 0.49807191709822585,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    logical bss_rationalu_surf1_cur1 = FALSE;
    int bss_degreeu_surf1_cur1 = 3;
    int bss_num_ctrlptsu_surf1_cur1 = 5;
    int bss_formu_surf1_cur1 = 0;
    int bss_poleu_surf1_cur1 = 0;
    logical bss_rationalv_surf1_cur1 = FALSE;
    int bss_degreev_surf1_cur1 = 3;
    int bss_num_ctrlptsv_surf1_cur1 = 5;
    int bss_formv_surf1_cur1 = 0;
    int bss_polev_surf1_cur1 = 0;
    const SPAposition bss_ctrlpts_surf1_cur1[] = {
      {-0.5,                -0.5,                0.5                },
      {-0.5,                -0.3821488698022421, 0.38214886980224205},
      {-0.5,                0,                   0.6178511301977578 },
      {-0.5,                0.3821488698022421,  0.38214886980224205},
      {-0.5,                0.5,                 0.5                },
      {-0.3821488698022421, -0.5,                0.38214886980224205},
      {-0.3821488698022421, -0.3821488698022421, 0.3428651597363227 },
      {-0.382148869802242,  0,                   0.5785674201318385 },
      {-0.3821488698022421, 0.3821488698022421,  0.5                },
      {-0.3821488698022421, 0.5,                 0.6178511301977578 },
      {0,                   -0.5,                0.5                },
      {0,                   -0.382148869802242,  0.5                },
      {0,                   0,                   0.5                },
      {0,                   0.382148869802242,   0.5                },
      {0,                   0.5,                 0.5                },
      {0.3821488698022421,  -0.5,                0.6178511301977578 },
      {0.3821488698022421,  -0.3821488698022421, 0.6571348402636774 },
      {0.382148869802242,   0,                   0.4214325798681614 },
      {0.3821488698022421,  0.3821488698022421,  0.5                },
      {0.3821488698022421,  0.5,                 0.38214886980224205},
      {0.5,                 -0.5,                0.5                },
      {0.5,                 -0.3821488698022421, 0.6178511301977578 },
      {0.5,                 0,                   0.38214886980224216},
      {0.5,                 0.3821488698022421,  0.6178511301977578 },
      {0.5,                 0.5,                 0.5                },
    };
    const double* bss_weights_surf1_cur1 = nullptr;
    double bss_ctrlpt_tol_surf1_cur1 = 1e-06;
    int bss_num_knotsu_surf1_cur1 = 9;
    double bss_knotsu_surf1_cur1[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf1_cur1 = 9;
    double bss_knotsv_surf1_cur1[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf1_cur1 = 1e-10;
    bs3_surface bss_surf1_cur1 = bs3_surface_from_ctrlpts(bss_degreeu_surf1_cur1, bss_rationalu_surf1_cur1, bss_formu_surf1_cur1, bss_poleu_surf1_cur1, bss_num_ctrlptsu_surf1_cur1, bss_degreev_surf1_cur1, bss_rationalv_surf1_cur1, bss_formv_surf1_cur1,
                                                          bss_polev_surf1_cur1, bss_num_ctrlptsv_surf1_cur1, bss_ctrlpts_surf1_cur1, bss_weights_surf1_cur1, bss_ctrlpt_tol_surf1_cur1, bss_num_knotsu_surf1_cur1, bss_knotsu_surf1_cur1,
                                                          bss_num_knotsv_surf1_cur1, bss_knotsv_surf1_cur1, bss_ctrlpt_tol_surf1_cur1);
    spline spl_surf1_cur1(bss_surf1_cur1);
    int bs2_degree_pcurve1_cur1 = 3;
    logical bs2_rational_pcurve1_cur1 = FALSE;
    logical bs2_closed_pcurve1_cur1 = FALSE;
    logical bs2_periodic_pcurve1_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur1 = 10;
    const SPAposition bs2_ctrlpts_pcurve1_cur1[] = {
      {0.5,                0.5,                0},
      {0.5014537278227802, 0.5,                0},
      {0.5011267995922759, 0.5000000000000001, 0},
      {0.5016817928305074, 0.5000000000000004, 0},
      {0.6461177998623121, 0.5000000000000816, 0},
      {0.7650447183549304, 0.5,                0},
      {0.9981522409349775, 0.5,                0},
      {0.9987667563308018, 0.5,                0},
      {0.9993826678401807, 0.5,                0},
      {1,                  0.5,                0},
    };
    const double* bs2_weights_pcurve1_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur1 = 1e-06;
    int bs2_num_knots_pcurve1_cur1 = 14;
    const double bs2_knots_pcurve1_cur1[] = {
      -0.0019088020727564157, -0.0019088020727564157, -0.0019088020727564157, -0.0019088020727564157, 0, 0, 0, 0.49676235782886763, 0.49676235782886763, 0.49676235782886763,
      0.49807191709822585,    0.49807191709822585,    0.49807191709822585,    0.49807191709822585,
    };
    double bs2_knot_tol_pcurve1_cur1 = 1e-10;
    bs2_curve bs2_pcurve1_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur1, bs2_rational_pcurve1_cur1, bs2_closed_pcurve1_cur1, bs2_periodic_pcurve1_cur1, bs2_num_ctrlpts_pcurve1_cur1, bs2_ctrlpts_pcurve1_cur1, bs2_weights_pcurve1_cur1,
                                                        bs2_ctrlpt_tol_pcurve1_cur1, bs2_num_knots_pcurve1_cur1, bs2_knots_pcurve1_cur1, bs2_knot_tol_pcurve1_cur1);
    SPAposition pln_root_surf2_cur1(0, 0, 0.5);
    SPAunit_vector pln_dir_surf2_cur1(0, 0, 1);
    plane pln_surf2_cur1(pln_root_surf2_cur1, pln_dir_surf2_cur1);
    pln_surf2_cur1.u_deriv = SPAvector(1, 0, 0);
    pln_surf2_cur1.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 1e-11, spl_surf1_cur1, pln_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    bounded_curve bnd_curv1(&ic_cur1, -0.0019088020727564157, 0.49807191709822585);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 14;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0.5,                 0,                     0.5                },
      {0.4996918112262458,  0.000499672728544424,  0.5                },
      {0.49938355574325266, 0.0009992950874056026, 0.4999999999999999 },
      {0.47832770469235686, 0.03511676988836872,   0.4999999999999999 },
      {0.45953370994456233, 0.06490793846537063,   0.5000000000000001 },
      {0.41554478982579357, 0.14179151134995002,   0.5000000000000001 },
      {0.39517016215451134, 0.1843361918367547,    0.4999999999999999 },
      {0.3797080542445285,  0.25146462224818084,   0.4999999999999999 },
      {0.3777655789160891,  0.27670894276869595,   0.49999999999952105},
      {0.3845604769575043,  0.330904926735853,     0.49999999999952105},
      {0.39430307723641134, 0.3593258233802664,    0.5                },
      {0.4329224627791316,  0.4276244393692115,    0.5                },
      {0.46453549760426743, 0.4645354976042674,    0.5                },
      {0.5,                 0.5,                   0.5                },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 18;
    const double bs3_knots_cur2[] = {
      -0.001761215036068128,
      -0.001761215036068128,
      -0.001761215036068128,
      -0.001761215036068128,
      0,
      0,
      0.11851412970443456,
      0.11851412970443456,
      0.2909170033554776,
      0.2909170033554776,
      0.3952269693563475,
      0.3952269693563475,
      0.5100657434733372,
      0.5100657434733372,
      0.6598539261216276,
      0.6598539261216276,
      0.6598539261216276,
      0.6598539261216276,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    logical bss_rationalu_surf1_cur2 = FALSE;
    int bss_degreeu_surf1_cur2 = 3;
    int bss_num_ctrlptsu_surf1_cur2 = 5;
    int bss_formu_surf1_cur2 = 0;
    int bss_poleu_surf1_cur2 = 0;
    logical bss_rationalv_surf1_cur2 = FALSE;
    int bss_degreev_surf1_cur2 = 3;
    int bss_num_ctrlptsv_surf1_cur2 = 5;
    int bss_formv_surf1_cur2 = 0;
    int bss_polev_surf1_cur2 = 0;
    const SPAposition bss_ctrlpts_surf1_cur2[] = {
      {-0.5,                -0.5,                0.5                },
      {-0.5,                -0.3821488698022421, 0.38214886980224205},
      {-0.5,                0,                   0.6178511301977578 },
      {-0.5,                0.3821488698022421,  0.38214886980224205},
      {-0.5,                0.5,                 0.5                },
      {-0.3821488698022421, -0.5,                0.38214886980224205},
      {-0.3821488698022421, -0.3821488698022421, 0.3428651597363227 },
      {-0.382148869802242,  0,                   0.5785674201318385 },
      {-0.3821488698022421, 0.3821488698022421,  0.5                },
      {-0.3821488698022421, 0.5,                 0.6178511301977578 },
      {0,                   -0.5,                0.5                },
      {0,                   -0.382148869802242,  0.5                },
      {0,                   0,                   0.5                },
      {0,                   0.382148869802242,   0.5                },
      {0,                   0.5,                 0.5                },
      {0.3821488698022421,  -0.5,                0.6178511301977578 },
      {0.3821488698022421,  -0.3821488698022421, 0.6571348402636774 },
      {0.382148869802242,   0,                   0.4214325798681614 },
      {0.3821488698022421,  0.3821488698022421,  0.5                },
      {0.3821488698022421,  0.5,                 0.38214886980224205},
      {0.5,                 -0.5,                0.5                },
      {0.5,                 -0.3821488698022421, 0.6178511301977578 },
      {0.5,                 0,                   0.38214886980224216},
      {0.5,                 0.3821488698022421,  0.6178511301977578 },
      {0.5,                 0.5,                 0.5                },
    };
    const double* bss_weights_surf1_cur2 = nullptr;
    double bss_ctrlpt_tol_surf1_cur2 = 1e-06;
    int bss_num_knotsu_surf1_cur2 = 9;
    double bss_knotsu_surf1_cur2[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf1_cur2 = 9;
    double bss_knotsv_surf1_cur2[] = {
      0, 0, 0, 0, 0.5, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf1_cur2 = 1e-10;
    bs3_surface bss_surf1_cur2 = bs3_surface_from_ctrlpts(bss_degreeu_surf1_cur2, bss_rationalu_surf1_cur2, bss_formu_surf1_cur2, bss_poleu_surf1_cur2, bss_num_ctrlptsu_surf1_cur2, bss_degreev_surf1_cur2, bss_rationalv_surf1_cur2, bss_formv_surf1_cur2,
                                                          bss_polev_surf1_cur2, bss_num_ctrlptsv_surf1_cur2, bss_ctrlpts_surf1_cur2, bss_weights_surf1_cur2, bss_ctrlpt_tol_surf1_cur2, bss_num_knotsu_surf1_cur2, bss_knotsu_surf1_cur2,
                                                          bss_num_knotsv_surf1_cur2, bss_knotsv_surf1_cur2, bss_ctrlpt_tol_surf1_cur2);
    spline spl_surf1_cur2(bss_surf1_cur2);
    int bs2_degree_pcurve1_cur2 = 3;
    logical bs2_rational_pcurve1_cur2 = FALSE;
    logical bs2_closed_pcurve1_cur2 = FALSE;
    logical bs2_periodic_pcurve1_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur2 = 19;
    const SPAposition bs2_ctrlpts_pcurve1_cur2[] = {
      {1,                  0.5,                0},
      {0.9995641552563856, 0.5004358447436144, 0},
      {0.9991289243136852, 0.5008716455518353, 0},
      {0.9986942956311249, 0.5013074181895665, 0},
      {0.9694476454473915, 0.5306310463962718, 0},
      {0.9457920254333599, 0.5566216321839034, 0},
      {0.9242067436604959, 0.5842421021986564, 0},
      {0.8928065670276333, 0.6244216859665292, 0},
      {0.8706476997,       0.6625463579438065, 0},
      {0.8601593084953656, 0.7014473095706287, 0},
      {0.8538134529606506, 0.7249837904636823, 0},
      {0.8517387904780328, 0.748985393580226,  0},
      {0.8552364552080487, 0.7744227262044711, 0},
      {0.859087166173326,  0.802427644692797,  0},
      {0.8694997959568522, 0.8314639769947441, 0},
      {0.8885191628999146, 0.8639015801919586, 0},
      {0.9133267806355415, 0.9062110672945235, 0},
      {0.9498456197291418, 0.9498456197291418, 0},
      {1,                  1,                  0},
    };
    const double* bs2_weights_pcurve1_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur2 = 1e-06;
    int bs2_num_knots_pcurve1_cur2 = 23;
    const double bs2_knots_pcurve1_cur2[] = {
      -0.001761215036068128,
      -0.001761215036068128,
      -0.001761215036068128,
      -0.001761215036068128,
      0,
      0,
      0,
      0.11851412970443456,
      0.11851412970443456,
      0.11851412970443456,
      0.2909170033554776,
      0.2909170033554776,
      0.2909170033554776,
      0.3952269693563475,
      0.3952269693563475,
      0.3952269693563475,
      0.5100657434733372,
      0.5100657434733372,
      0.5100657434733372,
      0.6598539261216276,
      0.6598539261216276,
      0.6598539261216276,
      0.6598539261216276,
    };
    double bs2_knot_tol_pcurve1_cur2 = 1e-10;
    bs2_curve bs2_pcurve1_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur2, bs2_rational_pcurve1_cur2, bs2_closed_pcurve1_cur2, bs2_periodic_pcurve1_cur2, bs2_num_ctrlpts_pcurve1_cur2, bs2_ctrlpts_pcurve1_cur2, bs2_weights_pcurve1_cur2,
                                                        bs2_ctrlpt_tol_pcurve1_cur2, bs2_num_knots_pcurve1_cur2, bs2_knots_pcurve1_cur2, bs2_knot_tol_pcurve1_cur2);
    SPAposition pln_root_surf2_cur2(0, 0, 0.5);
    SPAunit_vector pln_dir_surf2_cur2(0, 0, 1);
    plane pln_surf2_cur2(pln_root_surf2_cur2, pln_dir_surf2_cur2);
    pln_surf2_cur2.u_deriv = SPAvector(1, 0, 0);
    pln_surf2_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 1.3186403344999644e-05, spl_surf1_cur2, pln_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, -0.001761215036068128, 0.6598539261216276);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug81) {
    SPAposition ell_center_cur1(0, 0, -0.8660254037844387);
    SPAunit_vector ell_normal_cur1(0, 0, 1);
    SPAvector ell_major_axis_cur1(5.5, 0, 0);
    double ell_ratio_cur1 = 1;
    ellipse ell_cur1(ell_center_cur1, ell_normal_cur1, ell_major_axis_cur1, ell_ratio_cur1, 0);

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = TRUE;
    logical bs3_periodic_cur2 = TRUE;
    int bs3_num_ctrlpts_cur2 = 66;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-6,                  0,                    0                   },
      {-6,                  -0.06618245055616803, 0.06618245055616803 },
      {-5.991850487666224,  -0.1385799537513051,  0.1385799537513051  },
      {-5.956293385199628,  -0.28093671477496146, 0.28093671477496146 },
      {-5.928862995002216,  -0.3508931246943151,  0.3508931246943151  },
      {-5.866759491906626,  -0.4692862028889392,  0.46928620288893913 },
      {-5.827714687730858,  -0.5291899839893948,  0.5291899839893949  },
      {-5.733984750155991,  -0.6424120519393354,  0.6424120519393355  },
      {-5.679242895620331,  -0.6957068559610973,  0.6957068559610974  },
      {-5.575135580621057,  -0.7793817888805696,  0.7793817888805696  },
      {-5.517900697537763,  -0.8186156005044027,  0.8186156005044026  },
      {-5.393138806233005,  -0.8875053989963257,  0.8875053989963256  },
      {-5.325549117374987,  -0.917104608598545,   0.9171046085985449  },
      {-5.206878555999552,  -0.9572175298216838,  0.9572175298216836  },
      {-5.146355575387972,  -0.9732350639241315,  0.9732350639241316  },
      {-5.021870772033858,  -0.9946622903847221,  0.9946622903847222  },
      {-4.957884190951506,  -1,                   1                   },
      {-4.845150595676954,  -1,                   1                   },
      {-4.786531774895743,  -0.9955302471934343,  0.9955302471934344  },
      {-4.673049924740481,  -0.9758414125775862,  0.9758414125775863  },
      {-4.618191962715223,  -0.9606077301299453,  0.9606077301299452  },
      {-4.51772715951459,   -0.9231641253278999,  0.9231641253278997  },
      {-4.464136560336353,  -0.8967802015013546,  0.8967802015013546  },
      {-4.367675417290689,  -0.8353031818955945,  0.8353031818955945  },
      {-4.324702915157475,  -0.8002901226301657,  0.8002901226301656  },
      {-4.244337844365597,  -0.7224543552867217,  0.7224543552867215  },
      {-4.202521814136225,  -0.6711109129521037,  0.6711109129521036  },
      {-4.1331322397405,    -0.5635557376190806,  0.5635557376190805  },
      {-4.105368434127912,  -0.5074054293596113,  0.5074054293596113  },
      {-4.056393312701493,  -0.3859179722763396,  0.3859179722763396  },
      {-4.0342752176891805, -0.30827039763161324, 0.30827039763161324 },
      {-4.006137327320466,  -0.15140351680175032, 0.15140351680175038 },
      {-4,                  -0.07219476290980094, 0.07219476290980094 },
      {-4,                  0.07219476290980119,  -0.07219476290980119},
      {-4.006137327320466,  0.15140351680175074,  -0.15140351680175068},
      {-4.0342752176891805, 0.30827039763161374,  -0.3082703976316137 },
      {-4.056393312701491,  0.3859179722763403,   -0.3859179722763403 },
      {-4.105368434127911,  0.5074054293596121,   -0.507405429359612  },
      {-4.1331322397405,    0.5635557376190812,   -0.5635557376190811 },
      {-4.202521814136225,  0.6711109129521045,   -0.6711109129521043 },
      {-4.244337844365598,  0.7224543552867219,   -0.7224543552867217 },
      {-4.324702915157475,  0.8002901226301657,   -0.8002901226301656 },
      {-4.367675417290689,  0.8353031818955945,   -0.8353031818955945 },
      {-4.464136560336353,  0.8967802015013546,   -0.8967802015013546 },
      {-4.51772715951459,   0.9231641253278999,   -0.9231641253278997 },
      {-4.618191962715223,  0.9606077301299453,   -0.9606077301299452 },
      {-4.673049924740479,  0.975841412577586,    -0.975841412577586  },
      {-4.786531774895743,  0.9955302471934346,   -0.9955302471934346 },
      {-4.845150595676955,  1,                    -1                  },
      {-4.957884190951507,  1,                    -1                  },
      {-5.021870772033859,  0.9946622903847223,   -0.9946622903847223 },
      {-5.146355575387973,  0.9732350639241315,   -0.9732350639241315 },
      {-5.206878555999554,  0.9572175298216836,   -0.9572175298216835 },
      {-5.3255491173749885, 0.9171046085985448,   -0.9171046085985447 },
      {-5.393138806233006,  0.8875053989963247,   -0.8875053989963247 },
      {-5.517900697537762,  0.8186156005044023,   -0.8186156005044023 },
      {-5.575135580621058,  0.7793817888805696,   -0.7793817888805696 },
      {-5.679242895620332,  0.6957068559610972,   -0.6957068559610972 },
      {-5.733984750155991,  0.6424120519393355,   -0.6424120519393355 },
      {-5.827714687730858,  0.5291899839893949,   -0.5291899839893949 },
      {-5.866759491906626,  0.46928620288893896,  -0.4692862028889389 },
      {-5.928862995002216,  0.35089312469431494,  -0.3508931246943149 },
      {-5.956293385199628,  0.2809367147749613,   -0.2809367147749613 },
      {-5.991850487666224,  0.13857995375130502,  -0.13857995375130502},
      {-6,                  0.066182450556168,    -0.066182450556168  },
      {-6,                  0,                    0                   },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 70;
    const double bs3_knots_cur2[] = {
      0,
      0,
      0,
      0,
      0.28078835750285885,
      0.28078835750285885,
      0.5615767150057177,
      0.5615767150057177,
      0.8165272708084603,
      0.8165272708084603,
      1.0714778266112028,
      1.0714778266112028,
      1.2893611703023842,
      1.2893611703023842,
      1.5072445139935653,
      1.5072445139935653,
      1.6839586301490166,
      1.6839586301490166,
      1.8606727463044679,
      1.8606727463044679,
      2.0221594159726717,
      2.0221594159726717,
      2.1836460856408757,
      2.1836460856408757,
      2.3628572496458076,
      2.3628572496458076,
      2.5420684136507394,
      2.5420684136507394,
      2.771731584415578,
      2.771731584415578,
      3.001394755180417,
      3.001394755180417,
      3.3076911936984694,
      3.3076911936984694,
      3.6139876322165216,
      3.6139876322165216,
      3.920284070734574,
      3.920284070734574,
      4.226580509252626,
      4.226580509252626,
      4.456243680017465,
      4.456243680017465,
      4.685906850782303,
      4.685906850782303,
      4.865118014787235,
      4.865118014787235,
      5.044329178792167,
      5.044329178792167,
      5.205815848460372,
      5.205815848460372,
      5.367302518128575,
      5.367302518128575,
      5.544016634284027,
      5.544016634284027,
      5.720730750439479,
      5.720730750439479,
      5.93861409413066,
      5.93861409413066,
      6.156497437821842,
      6.156497437821842,
      6.411447993624584,
      6.411447993624584,
      6.666398549427327,
      6.666398549427327,
      6.9471869069301855,
      6.9471869069301855,
      7.227975264433044,
      7.227975264433044,
      7.227975264433044,
      7.227975264433044,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition tor_center_surf1_cur2(0, 0, 0);
    SPAunit_vector tor_normal_surf1_cur2(0, 0, 1);
    torus tor_surf1_cur2(tor_center_surf1_cur2, tor_normal_surf1_cur2, 5, -1);
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition pln_root_surf2_cur2(0, 0, 0);
    SPAunit_vector pln_dir_surf2_cur2(0, 0.7071067811865475, 0.7071067811865475);
    plane pln_surf2_cur2(pln_root_surf2_cur2, pln_dir_surf2_cur2);
    pln_surf2_cur2.u_deriv = SPAvector(1, 0, 0);
    pln_surf2_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 0.0002012969059203653, tor_surf1_cur2, pln_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ell_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ell_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug82) {
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 4;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0.4489988614813707,  -0.09999999999999998, 0.2200000508827959 },
      {0.4489988818238449,  0.2999999999999975,   0.22000000936577024},
      {0.4489988786943312,  0.6999999999999998,   0.2200000157528022 },
      {0.44899887917581527, 1.1,                  0.22000001477013953},
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 8;
    const double bs3_knots_cur1[] = {
      0, 0, 0, 0, 1.2000000000000006, 1.2000000000000006, 1.2000000000000006, 1.2000000000000006,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    logical bss_rationalu_surf1_cur1 = FALSE;
    int bss_degreeu_surf1_cur1 = 3;
    int bss_num_ctrlptsu_surf1_cur1 = 4;
    int bss_formu_surf1_cur1 = 0;
    int bss_poleu_surf1_cur1 = 0;
    logical bss_rationalv_surf1_cur1 = FALSE;
    int bss_degreev_surf1_cur1 = 3;
    int bss_num_ctrlptsv_surf1_cur1 = 4;
    int bss_formv_surf1_cur1 = 0;
    int bss_polev_surf1_cur1 = 0;
    const SPAposition bss_ctrlpts_surf1_cur1[] = {
      {-1.0599999701976777,   -0.5599999701976777, -0.27999998509883883},
      {-1.0599999701976777,   0.44000002980232233, 0.7200000149011612  },
      {-1.0599999701976777,   1.4400000298023223,  -0.27999998509883883},
      {-1.0599999701976777,   2.4400000298023223,  0.7200000149011612  },
      {-0.059999970197677666, -0.5599999701976777, 0.7200000149011612  },
      {-0.059999970197677666, 0.44000002980232233, -0.27999998509883883},
      {-0.059999970197677666, 1.4400000298023223,  0.7200000149011612  },
      {-0.059999970197677666, 2.4400000298023223,  -0.27999998509883883},
      {0.9400000298023223,    -0.5599999701976777, -0.27999998509883883},
      {0.9400000298023223,    0.44000002980232233, 0.7200000149011612  },
      {0.9400000298023223,    1.4400000298023223,  -0.27999998509883883},
      {0.9400000298023223,    2.4400000298023223,  0.7200000149011612  },
      {1.9400000298023223,    -0.5599999701976777, 0.7200000149011612  },
      {1.9400000298023223,    0.44000002980232233, -0.27999998509883883},
      {1.9400000298023223,    1.4400000298023223,  0.7200000149011612  },
      {1.9400000298023223,    2.4400000298023223,  -0.27999998509883883},
    };
    const double* bss_weights_surf1_cur1 = nullptr;
    double bss_ctrlpt_tol_surf1_cur1 = 1e-06;
    int bss_num_knotsu_surf1_cur1 = 8;
    double bss_knotsu_surf1_cur1[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf1_cur1 = 8;
    double bss_knotsv_surf1_cur1[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf1_cur1 = 1e-10;
    bs3_surface bss_surf1_cur1 = bs3_surface_from_ctrlpts(bss_degreeu_surf1_cur1, bss_rationalu_surf1_cur1, bss_formu_surf1_cur1, bss_poleu_surf1_cur1, bss_num_ctrlptsu_surf1_cur1, bss_degreev_surf1_cur1, bss_rationalv_surf1_cur1, bss_formv_surf1_cur1,
                                                          bss_polev_surf1_cur1, bss_num_ctrlptsv_surf1_cur1, bss_ctrlpts_surf1_cur1, bss_weights_surf1_cur1, bss_ctrlpt_tol_surf1_cur1, bss_num_knotsu_surf1_cur1, bss_knotsu_surf1_cur1,
                                                          bss_num_knotsv_surf1_cur1, bss_knotsv_surf1_cur1, bss_ctrlpt_tol_surf1_cur1);
    spline spl_surf1_cur1(bss_surf1_cur1);
    int bs2_degree_pcurve1_cur1 = 3;
    logical bs2_rational_pcurve1_cur1 = FALSE;
    logical bs2_closed_pcurve1_cur1 = FALSE;
    logical bs2_periodic_pcurve1_cur1 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur1 = 4;
    const SPAposition bs2_ctrlpts_pcurve1_cur1[] = {
      {0.5029996105596828, 0.1533333233992259,  0},
      {0.5029996173405075, 0.28666665673255837, 0},
      {0.5029996162973362, 0.4199999900658925,  0},
      {0.502999616457831,  0.5533333233992259,  0},
    };
    const double* bs2_weights_pcurve1_cur1 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur1 = 1e-06;
    int bs2_num_knots_pcurve1_cur1 = 8;
    const double bs2_knots_pcurve1_cur1[] = {
      0, 0, 0, 0, 1.2000000000000006, 1.2000000000000006, 1.2000000000000006, 1.2000000000000006,
    };
    double bs2_knot_tol_pcurve1_cur1 = 1e-10;
    bs2_curve bs2_pcurve1_cur1 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur1, bs2_rational_pcurve1_cur1, bs2_closed_pcurve1_cur1, bs2_periodic_pcurve1_cur1, bs2_num_ctrlpts_pcurve1_cur1, bs2_ctrlpts_pcurve1_cur1, bs2_weights_pcurve1_cur1,
                                                        bs2_ctrlpt_tol_pcurve1_cur1, bs2_num_knots_pcurve1_cur1, bs2_knots_pcurve1_cur1, bs2_knot_tol_pcurve1_cur1);
    SPAposition c_base_center_surf2_cur1(0, 0.5, 0);
    SPAunit_vector c_base_normal_surf2_cur1(0, 1, 0);
    SPAvector c_base_major_surf2_cur1(0.5, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, 0, 1);
    c_surf2_cur1.u_param_scale = 0.5;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 1e-11, spl_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);
    INTCURVE* intcurve_cur1 = ACIS_NEW INTCURVE(ic_cur1);
    ic_cur1 = *(intcurve*)intcurve_cur1->trans_curve(*(SPAtransf*)nullptr, TRUE);
    bounded_curve bnd_curv1(&ic_cur1, -1.1000000000000123, -0.10000000000000055);
    EDGE* e1 = bnd_curv1.make_edge();

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 4;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.6500000000000001,  0, 0.17278440744013063},
      {-0.21765647389144926, 0, 0.2289679716390084 },
      {0.21874553547752662,  0, 0.2182574899400287 },
      {0.6499999999999999,   0, 0.22033766256670867},
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 8;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 0, 1.3079364117137278, 1.3079364117137278, 1.3079364117137278, 1.3079364117137278,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    logical bss_rationalu_surf1_cur2 = FALSE;
    int bss_degreeu_surf1_cur2 = 3;
    int bss_num_ctrlptsu_surf1_cur2 = 4;
    int bss_formu_surf1_cur2 = 0;
    int bss_poleu_surf1_cur2 = 0;
    logical bss_rationalv_surf1_cur2 = FALSE;
    int bss_degreev_surf1_cur2 = 3;
    int bss_num_ctrlptsv_surf1_cur2 = 4;
    int bss_formv_surf1_cur2 = 0;
    int bss_polev_surf1_cur2 = 0;
    const SPAposition bss_ctrlpts_surf1_cur2[] = {
      {-1.0599999701976777,   -0.5599999701976777, -0.27999998509883883},
      {-1.0599999701976777,   0.44000002980232233, 0.7200000149011612  },
      {-1.0599999701976777,   1.4400000298023223,  -0.27999998509883883},
      {-1.0599999701976777,   2.4400000298023223,  0.7200000149011612  },
      {-0.059999970197677666, -0.5599999701976777, 0.7200000149011612  },
      {-0.059999970197677666, 0.44000002980232233, -0.27999998509883883},
      {-0.059999970197677666, 1.4400000298023223,  0.7200000149011612  },
      {-0.059999970197677666, 2.4400000298023223,  -0.27999998509883883},
      {0.9400000298023223,    -0.5599999701976777, -0.27999998509883883},
      {0.9400000298023223,    0.44000002980232233, 0.7200000149011612  },
      {0.9400000298023223,    1.4400000298023223,  -0.27999998509883883},
      {0.9400000298023223,    2.4400000298023223,  0.7200000149011612  },
      {1.9400000298023223,    -0.5599999701976777, 0.7200000149011612  },
      {1.9400000298023223,    0.44000002980232233, -0.27999998509883883},
      {1.9400000298023223,    1.4400000298023223,  0.7200000149011612  },
      {1.9400000298023223,    2.4400000298023223,  -0.27999998509883883},
    };
    const double* bss_weights_surf1_cur2 = nullptr;
    double bss_ctrlpt_tol_surf1_cur2 = 1e-06;
    int bss_num_knotsu_surf1_cur2 = 8;
    double bss_knotsu_surf1_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    int bss_num_knotsv_surf1_cur2 = 8;
    double bss_knotsv_surf1_cur2[] = {
      0, 0, 0, 0, 1, 1, 1, 1,
    };
    double bss_knot_tol_surf1_cur2 = 1e-10;
    bs3_surface bss_surf1_cur2 = bs3_surface_from_ctrlpts(bss_degreeu_surf1_cur2, bss_rationalu_surf1_cur2, bss_formu_surf1_cur2, bss_poleu_surf1_cur2, bss_num_ctrlptsu_surf1_cur2, bss_degreev_surf1_cur2, bss_rationalv_surf1_cur2, bss_formv_surf1_cur2,
                                                          bss_polev_surf1_cur2, bss_num_ctrlptsv_surf1_cur2, bss_ctrlpts_surf1_cur2, bss_weights_surf1_cur2, bss_ctrlpt_tol_surf1_cur2, bss_num_knotsu_surf1_cur2, bss_knotsu_surf1_cur2,
                                                          bss_num_knotsv_surf1_cur2, bss_knotsv_surf1_cur2, bss_ctrlpt_tol_surf1_cur2);
    spline spl_surf1_cur2(bss_surf1_cur2);
    int bs2_degree_pcurve1_cur2 = 3;
    logical bs2_rational_pcurve1_cur2 = FALSE;
    logical bs2_closed_pcurve1_cur2 = FALSE;
    logical bs2_periodic_pcurve1_cur2 = FALSE;
    int bs2_num_ctrlpts_pcurve1_cur2 = 4;
    const SPAposition bs2_ctrlpts_pcurve1_cur2[] = {
      {0.13666665673255918, 0.18666665673255922, 0},
      {0.28078116543540943, 0.18666665673255922, 0},
      {0.42624850189173474, 0.18666665673255922, 0},
      {0.5699999900658925,  0.18666665673255922, 0},
    };
    const double* bs2_weights_pcurve1_cur2 = nullptr;
    double bs2_ctrlpt_tol_pcurve1_cur2 = 1e-06;
    int bs2_num_knots_pcurve1_cur2 = 8;
    const double bs2_knots_pcurve1_cur2[] = {
      0, 0, 0, 0, 1.3079364117137278, 1.3079364117137278, 1.3079364117137278, 1.3079364117137278,
    };
    double bs2_knot_tol_pcurve1_cur2 = 1e-10;
    bs2_curve bs2_pcurve1_cur2 = bs2_curve_from_ctrlpts(bs2_degree_pcurve1_cur2, bs2_rational_pcurve1_cur2, bs2_closed_pcurve1_cur2, bs2_periodic_pcurve1_cur2, bs2_num_ctrlpts_pcurve1_cur2, bs2_ctrlpts_pcurve1_cur2, bs2_weights_pcurve1_cur2,
                                                        bs2_ctrlpt_tol_pcurve1_cur2, bs2_num_knots_pcurve1_cur2, bs2_knots_pcurve1_cur2, bs2_knot_tol_pcurve1_cur2);
    SPAposition pln_root_surf2_cur2(0, 0, 0);
    SPAunit_vector pln_dir_surf2_cur2(0, -1, 0);
    plane pln_surf2_cur2(pln_root_surf2_cur2, pln_dir_surf2_cur2);
    pln_surf2_cur2.u_deriv = SPAvector(-1, 0, 0);
    pln_surf2_cur2.reverse_v = FALSE;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 7.01054089368727e-05, spl_surf1_cur2, pln_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);
    bounded_curve bnd_curv2(&ic_cur2, 0.19024468293127828, 1.1050741726794617);
    EDGE* e2 = bnd_curv2.make_edge();

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug83) {
    int bs3_degree_cur1 = 3;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 1061;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {42.021205284853366, -16.100257960936542,   -1.4000000000000072    },
      {42.020824288246985, -16.101252351010253,   -1.389737148173157     },
      {42.019828859418666, -16.103850112238494,   -1.3626257838970222    },
      {42.01826173522012,  -16.10793869131058,    -1.3186540606067514    },
      {42.016527014319934, -16.112463038809523,   -1.2680793131337111    },
      {42.014859504682356, -16.11681071852973,    -1.2174878022664657    },
      {42.01325930392859,  -16.12098163985343,    -1.1668801931988624    },
      {42.01172650578086,  -16.124975715801277,   -1.116257151775407     },
      {42.0102612000513,   -16.128792863040022,   -1.0656193444648818    },
      {42.008863472632534, -16.132433001889428,   -1.0149674383338483    },
      {42.00753340548704,  -16.13589605632938,    -0.9643021010200861    },
      {42.00627107663884,  -16.139181954006173,   -0.9136240007059222    },
      {42.0050765601639,   -16.14229062623894,    -0.8629338060915086    },
      {42.00394992618216,  -16.145222008025492,   -0.8122321863680017    },
      {42.0028912408494,   -16.14797603804792,    -0.7615198111906919    },
      {42.00190056634976,  -16.150552658677903,   -0.71079735065204      },
      {42.00097796088885,  -16.152951815981716,   -0.6600654752546783    },
      {42.00012347868666,  -16.15517345972484,    -0.6093248558843268    },
      {41.999337169971966, -16.157217543376355,   -0.5585761637826764    },
      {41.99861908097631,  -16.159084024112943,   -0.5078200705201893    },
      {41.99796925392866,  -16.160772862822615,   -0.4570572479688869    },
      {41.99738772705083,  -16.162284024108075,   -0.40628836827507037   },
      {41.99687453455296,  -16.163617476289822,   -0.3555141038320068    },
      {41.996429706629606, -16.16477319140888,    -0.30473512725257834   },
      {41.99605326945647,  -16.16575114522921,    -0.2539521113419028    },
      {41.99574524518717,  -16.166551317239858,   -0.2031657290699314    },
      {41.995505651950936, -16.16717369065667,    -0.15237665354399305   },
      {41.99533450385037,  -16.167618252423832,   -0.10158555798136872   },
      {41.995231810959936, -16.167884993214912,   -0.05079311568179404   },
      {41.99519757932476,  -16.16797390743376,    -2.1614654510671016e-15},
      {41.99523181095994,  -16.167884993214912,   0.05079311568178963    },
      {41.99533450385037,  -16.167618252423836,   0.10158555798136315    },
      {41.99550565195095,  -16.167173690656668,   0.1523766535439875     },
      {41.99574524518717,  -16.166551317239865,   0.20316572906992583    },
      {41.99605326945648,  -16.16575114522921,    0.25395211134189744    },
      {41.99642970662961,  -16.16477319140888,    0.3047351272525727     },
      {41.99687453455296,  -16.163617476289822,   0.3555141038320025     },
      {41.99738772705082,  -16.16228402410808,    0.40628836827506604    },
      {41.99796925392866,  -16.16077286282262,    0.4570572479688826     },
      {41.9986190809763,   -16.159084024112943,   0.5078200705201836     },
      {41.99933716997198,  -16.157217543376362,   0.558576163782671      },
      {42.000123478686646, -16.15517345972484,    0.6093248558843214     },
      {42.000977960888854, -16.152951815981712,   0.6600654752546726     },
      {42.001900566349775, -16.1505526586779,     0.7107973506520345     },
      {42.00289124084941,  -16.147976038047922,   0.7615198111906866     },
      {42.00394992618216,  -16.145222008025492,   0.8122321863679971     },
      {42.0050765601639,   -16.14229062623894,    0.8629338060915042     },
      {42.006271076638825, -16.139181954006173,   0.9136240007059176     },
      {42.007533405487045, -16.13589605632938,    0.9643021010200828     },
      {42.00886347263252,  -16.132433001889424,   1.0149674383338403     },
      {42.0102612000513,   -16.12879286304002,    1.0656193444648763     },
      {42.01172650578086,  -16.12497571580128,    1.1162571517754016     },
      {42.01325930392858,  -16.120981639853426,   1.1668801931988562     },
      {42.014859504682356, -16.116810718529734,   1.217487802266462      },
      {42.01652701431994,  -16.112463038809526,   1.268079313133707      },
      {42.01826173522012,  -16.10793869131058,    1.318654060606747      },
      {42.02006356587334,  -16.103237770281464,   1.3692113801687067     },
      {42.02193240089338,  -16.0983603735934,     1.419750608005892      },
      {42.02386813102903,  -16.093306602731932,   1.4702710810338626     },
      {42.02587064317652,  -16.088076562788242,   1.5207721369234783     },
      {42.02793982039201,  -16.08267036245018,    1.5712531141267387     },
      {42.030075541905006, -16.077088113993,      1.6217133519025975     },
      {42.03227768313157,  -16.07132993326984,    1.6721521903426004     },
      {42.034546115688414, -16.065395939701837,   1.7225689703964384     },
      {42.03688070740718,  -16.059286256267995,   1.7729630338973668     },
      {42.03928132234923,  -16.053001009494828,   1.823333723587498      },
      {42.04174782082075,  -16.046540329445566,   1.8736803831429503     },
      {42.044280059388235, -16.039904349709246,   1.9240023571989102     },
      {42.04687789089439,  -16.033093207389385,   1.9742989913744924     },
      {42.04954116447455,  -16.026107043092544,   2.0245696322975344     },
      {42.05226972557331,  -16.018946000916316,   2.0748136276291507     },
      {42.05506341596149,  -16.011610228437508,   2.1250303260882792     },
      {42.05792207375391,  -16.004099876699474,   2.1752190774759113     },
      {42.060845533426566, -15.996415100199808,   2.2253792326993476     },
      {42.06383362583561,  -15.988556056877172,   2.2755101437961245     },
      {42.06688617823522,  -15.980522908098369,   2.325611163957934      },
      {42.070003014296965, -15.97231581864474,    2.3756816475542655     },
      {42.0731839541288,   -15.963934956698683,   2.4257209501559753     },
      {42.07642881429477,  -15.955380493829548,   2.475728428558596      },
      {42.07973740783486,  -15.94665260497968,    2.525703440805605      },
      {42.08310954428555,  -15.937751468449767,   2.5756453462113362     },
      {42.08654502970015,  -15.928677265884359,   2.625553505383937      },
      {42.090043666669914, -15.919430182256875,   2.6754272802479386     },
      {42.09360525434537,  -15.910010405854532,   2.7252660340667987     },
      {42.09722958845775,  -15.90041812826286,    2.7750691314651803     },
      {42.10091646134116,  -15.890653544350196,   2.8248359384510544     },
      {42.104665661954684, -15.880716852251792,   2.8745658224376616     },
      {42.10847697590493,  -15.870608253353776,   2.9242581522652102     },
      {42.112350185468856, -15.860327952276858,   2.9739122982224595     },
      {42.11628506961721,  -15.849876156859791,   3.023527632067999      },
      {42.120281404037414, -15.839253078142717,   3.073103527051501      },
      {42.124338961157854, -15.828458930350191,   3.122639357934574      },
      {42.128457510171735, -15.817493930873983,   3.172134501011537      },
      {42.13263681706101,  -15.806358300255901,   3.221588334130019      },
      {42.13687664462152,  -15.795052262170024,   3.271000236711207      },
      {42.141176752487496, -15.783576043405077,   3.3203695897700225     },
      {42.14553689715658,  -15.771929873846503,   3.3696957759350568     },
      {42.14995683201545,  -15.760113986458233,   3.4189781794682306     },
      {42.15443630736511,  -15.748128617264426,   3.4682161862843053     },
      {42.158975070447084, -15.735974005330956,   3.517409183970184      },
      {42.163572865469106, -15.723650392746663,   3.5665565618039117     },
      {42.168229433631794, -15.711158024604561,   3.6156577107735757     },
      {42.17294451315494,  -15.698497148982717,   3.664712023595868      },
      {42.17771783930452,  -15.68566801692511,    3.713718894734519      },
      {42.18254914441931,  -15.672670882422167,   3.7626777204184583     },
      {42.18743815793863,  -15.659506002391288,   3.811587898659729      },
      {42.19238460642919,  -15.646173636657089,   3.8604488292712515     },
      {42.197388213613024, -15.632674047931598,   3.909259913884302      },
      {42.20244870039531,  -15.619007501794153,   3.9580205559657142     },
      {42.20756578489214,  -15.605174266671337,   4.0067301608350085     },
      {42.212739182459046, -15.59117461381657,    4.055388135681076      },
      {42.21796860571885,  -15.577008817289787,   4.103993889578852      },
      {42.22325376459078,  -15.562677153936718,   4.152546833505551      },
      {42.22859436631865,  -15.548179903368258,   4.201046380356812      },
      {42.23399011550009,  -15.533517347939583,   4.249491944962546      },
      {42.23944071411543,  -15.51868977272915,    4.297882944102524      },
      {42.244945861556715, -15.503697465517682,   4.346218796521827      },
      {42.2505052546573,   -15.488540716766856,   4.3944989229459015     },
      {42.256118587721055, -15.473219819598018,   4.442722746095528      },
      {42.261785552552176, -15.457735069770711,   4.490889690701438      },
      {42.267505838484695, -15.442086765661191,   4.538999183518776      },
      {42.27327913241235,  -15.426275208240664,   4.587050653341238      },
      {42.27910511881863,  -15.410300701053636,   4.635043531015038      },
      {42.28498347980688,  -15.394163550195959,   4.682977249452565      },
      {42.29091389513021,  -15.377864064293032,   4.730851243645914      },
      {42.29689604222207,  -15.361402554477568,   4.7786649506799534     },
      {42.30292959622644,  -15.34477933436764,    4.82641780974544       },
      {42.309014230028325, -15.327994720044426,   4.874109262151626      },
      {42.31514961428428,  -15.311049030029906,   4.921738751338807      },
      {42.32133541745314,  -15.293942585264531,   4.969305722890479      },
      {42.32757130582641,  -15.27667570908481,    5.016809624545413      },
      {42.333856943559454, -15.259248727200793,   5.0642499062093        },
      {42.34019199270196,  -15.241661967673519,   5.111626019966321      },
      {42.34657611322893,  -15.223915760892442,   5.158937420090369      },
      {42.35300896307187,  -15.206010439552694,   5.206183563056017      },
      {42.35949019814904,  -15.187946338632456,   5.2533639075493985     },
      {42.366019472397504, -15.16972379537005,    5.300477914478539      },
      {42.37259643780321,  -15.151343149241256,   5.347525046983812      },
      {42.37922074443277,  -15.132804741936386,   5.394504770447855      },
      {42.385892040464114, -15.1141089173374,     5.441416552505402      },
      {42.39260997221799,  -15.095256021494944,   5.488259863052794      },
      {42.39937418418873,  -15.076246402605442,   5.535034174257319      },
      {42.40618431907578,  -15.057080410988062,   5.581738960566226      },
      {42.41304001781456,  -15.037758399061701,   5.6283736987155715     },
      {42.41994091960787,  -15.018280721321979,   5.674937867738773      },
      {42.42688666195687,  -14.99864773431813,    5.721430948974959      },
      {42.43387688069226,  -14.978859796629983,   5.7678524260770505     },
      {42.44091121000562,  -14.958917268844836,   5.8142017850195895     },
      {42.44798928248019,  -14.93882051353441,    5.860478514106432      },
      {42.455110729122254, -14.918569895231709,   5.906682103978028      },
      {42.462275179392094, -14.898165780407947,   5.952812047618607      },
      {42.46948226123495,  -14.87760853744949,    5.998867840363118      },
      {42.47673160111219,  -14.856898536634663,   6.044848979903809      },
      {42.4840228240322,   -14.836036150110772,   6.090754966296709      },
      {42.49135555358119,  -14.815021751871027,   6.136585301967874      },
      {42.4987294119542,   -14.793855717731368,   6.1823394917192385     },
      {42.50614401998581,  -14.772538425307603,   6.228017042734464      },
      {42.51359899718112,  -14.751070253992216,   6.273617464584344      },
      {42.52109396174595,  -14.729451584931535,   6.319140269232185      },
      {42.528628530618015, -14.70768280100262,    6.36458497103874       },
      {42.53620231949712,  -14.685764286790418,   6.409951086767101      },
      {42.54381494287574,  -14.663696428564805,   6.455238135587268      },
      {42.55146601406941,  -14.641479614257767,   6.5004456390805165     },
      {42.55915514524702,  -14.619114233440492,   6.545573121243557      },
      {42.56688194746118,  -14.596600677300636,   6.590620108492376      },
      {42.574646030678004, -14.573939338619542,   6.635586129666103      },
      {42.58244700380762,  -14.55113061174956,    6.6804707160302765     },
      {42.5902844747337,   -14.528174892591371,   6.72527340128031       },
      {42.59815805034356,  -14.505072578571367,   6.769993721544367      },
      {42.606067336557686, -14.481824068619176,   6.814631215386329      },
      {42.614011938359646, -14.458429763145052,   6.859185423808279      },
      {42.62199145982527,  -14.434890064017557,   6.903655890253031      },
      {42.6300055041523,   -14.411205374541115,   6.948042160606234      },
      {42.6380536736895,   -14.387376099433725,   6.992343783198381      },
      {42.646135569965985, -14.36340264480472,    7.036560308806571      },
      {42.65425079372004,  -14.339285418132592,   7.080691290656125      },
      {42.662398944928256, -14.315024828242905,   7.124736284421847      },
      {42.670579622834,    -14.290621285286258,   7.168694848229325      },
      {42.67879242597649,  -14.266075200716296,   7.2125665426557095     },
      {42.687036952218676, -14.241386987267928,   7.256350930730673      },
      {42.69531279877628,  -14.216557058935432,   7.300047577936776      },
      {42.70361956224548,  -14.19158583095081,    7.343656052209971      },
      {42.71195683863124,  -14.166473719762134,   7.387175923939688      },
      {42.72032422337508,  -14.141221143012059,   7.430606765968879      },
      {42.728721311383076, -14.115828519516258,   7.473948153593669      },
      {42.73714769705309,  -14.090296269242211,   7.517199664563154      },
      {42.745602974302756, -14.064624813287798,   7.560360879078576      },
      {42.754086736596136, -14.03881457386025,    7.603431379792747      },
      {42.76259857697147,  -14.012865974254991,   7.646410751808923      },
      {42.77113808806761,  -13.986779438834692,   7.689298582679775      },
      {42.7797048621513,   -13.960555393008411,   7.7320944624059855     },
      {42.788298491143564, -13.934194263210767,   7.774797983434748      },
      {42.796918566646006, -13.907696476881348,   7.817408740658159      },
      {42.80556467996752,  -13.88106246244408,    7.859926331411235      },
      {42.81423642215009,  -13.85429264928681,    7.902350355469985      },
      {42.82293338399483,  -13.827387467740929,   7.94468041504916       },
      {42.831655156087734, -13.800347349061175,   7.9869161147998895     },
      {42.840401328825315, -13.773172725405454,   8.029057061807118      },
      {42.84917149243995,  -13.745864029814904,   8.071102865586958      },
      {42.85796523702508,  -13.718421696193904,   8.113053138083751      },
      {42.866782152560255, -13.690846159290388,   8.154907493667121      },
      {42.87562182893619,  -13.663137854676107,   8.196665549128639      },
      {42.88448385597891,  -13.635297218727152,   8.238326923678667      },
      {42.893367823474776, -13.607324688604475,   8.279891238942696      },
      {42.90227332119454,  -13.579220702234645,   8.321358118957761      },
      {42.91119993891721,  -13.550985698290619,   8.362727190168634      },
      {42.920147266454265, -13.522620116172718,   8.403998081423822      },
      {42.92911489367336,  -13.494124395989715,   8.445170423971486      },
      {42.93810241052134,  -13.465498978539998,   8.486243851455232      },
      {42.947109407048266, -13.436744305292924,   8.527217999909597      },
      {42.95613547342986,  -13.407860818370283,   8.568092507755653      },
      {42.96518019999084,  -13.378848960527858,   8.608867015796188      },
      {42.97424317722742,  -13.349709175137171,   8.64954116721099       },
      {42.98332399582983,  -13.320441906167325,   8.69011460755188       },
      {42.99242224670459,  -13.291047598166978,   8.730586984737581      },
      {43.001537520996806, -13.261526696246474,   8.770957949048494      },
      {43.010669410111774, -13.23187964606008,    8.811227153121424      },
      {43.01981750573671,  -13.202106893788397,   8.851394251944049      },
      {43.028981399862566, -13.172208886120854,   8.891458902849266      },
      {43.038160684804794, -13.142186070238424,   8.931420765509605      },
      {43.047354953224854, -13.112038893796331,   8.971279501931196      },
      {43.05656379815064,  -13.081767804907104,   9.011034776447998      },
      {43.06578681299765,  -13.05137325212354,    9.050686255715508      },
      {43.07502359158898,  -13.020855684422004,   9.090233608704711      },
      {43.08427372817577,  -12.990215551185761,   9.129676506695695      },
      {43.09353681745725,  -12.959453302188464,   9.16901462327121       },
      {43.10281245460029,  -12.92856938757782,    9.208247634310194      },
      {43.11210023525953,  -12.897564257859313,   9.247375217980988      },
      {43.12139975559621,  -12.866438363880224,   9.286397054734735      },
      {43.13071061229769,  -12.83519215681364,    9.325312827298418      },
      {43.14003240259641,  -12.80382608814265,    9.364122220667914      },
      {43.14936472428852,  -12.772340609644761,   9.402824922100958      },
      {43.1587071757525,   -12.74073617337633,    9.44142062110993       },
      {43.16805935596763,  -12.709013231657295,   9.479909009454664      },
      {43.177420864531975, -12.677172237055872,   9.51828978113498       },
      {43.18679130168039,  -12.645213642373564,   9.556562632383372      },
      {43.1961702683021,   -12.61313790063021,    9.594727261657372      },
      {43.2055573659586,   -12.580945465049206,   9.632783369631895      },
      {43.2149521969004,   -12.548636789042913,   9.670730659191662      },
      {43.22435436408459,  -12.516212326198135,   9.708568835423208      },
      {43.23376347119152,  -12.483672530261831,   9.746297605607168      },
      {43.24317912264148,  -12.451017855126876,   9.783916679210174      },
      {43.25260092361122,  -12.41824875481807,    9.821425767876876      },
      {43.26202848005022,  -12.385365683478213,   9.858824585421788      },
      {43.27146139869664,  -12.35236909535436,    9.896112847821101      },
      {43.28089928709336,  -12.319259444784262,   9.933290273204367      },
      {43.29034175360338,  -12.286037186182838,   9.970356581846204      },
      {43.29978840742557,  -12.25270277402894,    10.007311496157774     },
      {43.30923885860956,  -12.21925666285216,    10.044154740678412     },
      {43.31869271807108,  -12.185699307219817,   10.080886042066936     },
      {43.3281495976066,   -12.152031161724107,   10.117505129093118     },
      {43.33760910990791,  -12.118252680969377,   10.15401173262898      },
      {43.347070868576836, -12.08436431955952,    10.190405585639903     },
      {43.356534488139104, -12.050366532085626,   10.22668642317605      },
      {43.36599958405863,  -12.016259773113607,   10.262853982363234     },
      {43.37546577275117,  -11.98204449717214,    10.298908002394196     },
      {43.384932671598,    -11.947721158740638,   10.334848224519451     },
      {43.39439989895946,  -11.913290212237426,   10.37067439203836      },
      {43.403867074187865, -11.878752112008014,   10.406386250289973     },
      {43.413333817640975, -11.844107312313596,   10.44198354664387      },
      {43.42279975069442,  -11.809356267319583,   10.47746603049101      },
      {43.432264495754644, -11.774499431084394,   10.512833453234443     },
      {43.44172767627117,  -11.73953725754827,    10.548085568280014     },
      {43.45118891674889,  -11.70447020052241,    10.5832221310271       },
      {43.46064784276018,  -11.669298713677994,   10.618242898859105     },
      {43.47010408095683,  -11.634023250535625,   10.653147631134122     },
      {43.47955725908151,  -11.598644264454704,   10.687936089175466     },
      {43.4890070059795,   -11.563162208623048,   10.722608036262118     },
      {43.498452951609806, -11.527577536046646,   10.757163237619272     },
      {43.507894727056524, -11.491890699539518,   10.791601460408641     },
      {43.51733196453941,  -11.456102151713736,   10.82592247371898      },
      {43.52676429742514,  -11.420212344969613,   10.860126048556317     },
      {43.53619136023738,  -11.384221731485958,   10.894211957834372     },
      {43.5456127886674,   -11.34813076321056,    10.928179976364824     },
      {43.55502821958441,  -11.311939891850754,   10.962029880847528     },
      {43.56443729104531,  -11.27564956886414,    10.995761449860861     },
      {43.57383964230473,  -11.239260245449419,   11.029374463851802     },
      {43.58323491382479,  -11.202772372537448,   11.062868705126235     },
      {43.59262274728418,  -11.166186400782301,   11.096243957839091     },
      {43.60200278558807,  -11.129502780552585,   11.129500007984369     },
      {43.611374672876764, -11.092721961922843,   11.162636643385522     },
      {43.62073805453507,  -11.055844394665051,   11.195653653685202     },
      {43.6300925772007,   -11.018870528240353,   11.228550830335754     },
      {43.63943788877336,  -10.981800811790821,   11.26132796658888      },
      {43.64877363842282,  -10.94463569413144,    11.293984857486029     },
      {43.65809947659751,  -10.907375623742139,   11.326521299848222     },
      {43.667415055032514, -10.870021048760044,   11.358937092266185     },
      {43.67672002675767,  -10.832572416971773,   11.391232035090287     },
      {43.68601404610516,  -10.795030175805952,   11.423405930420621     },
      {43.69529676871743,  -10.757394772325785,   11.455458582096972     },
      {43.70456785155447,  -10.719666653221783,   11.487389795688758     },
      {43.713826952901414, -10.681846264804648,   11.519199378485082     },
      {43.72307373237544,  -10.643934052998247,   11.550887139484633     },
      {43.73230785093291,  -10.605930463332719,   11.582452889385728     },
      {43.741528970876246, -10.567835940937737,   11.613896440576223     },
      {43.75073675586078,  -10.529650930535865,   11.645217607123486     },
      {43.75993087090109,  -10.49137587643605,    11.676416204764362     },
      {43.769110982377434, -10.453011222527264,   11.707492050895159     },
      {43.77827675804231,  -10.414557412272208,   11.738444964561566     },
      {43.78742786702632,  -10.376014888701206,   11.769274766448603     },
      {43.79656397984408,  -10.337384094406215,   11.79998127887071      },
      {43.80568476840038,  -10.298665471534871,   11.830564325761495     },
      {43.81478990599556,  -10.259859461784803,   11.86102373266395      },
      {43.823879067331234, -10.220966506397898,   11.891359326720218     },
      {43.832951928515634, -10.181987046154884,   11.921570936661775     },
      {43.84200816706894,  -10.142921521369791,   11.95165839279922      },
      {43.85104746192835,  -10.103770371884783,   11.981621527012459     },
      {43.86006949345312,  -10.064534037064892,   12.011460172740591     },
      {43.86907394342947,  -10.025212955793027,   12.041174164971988     },
      {43.87806049507515,  -9.985807566464995,    12.070763340234329     },
      {43.887028833044376, -9.946318306984693,    12.100227536584612     },
      {43.89597864343194,  -9.906745614759375,    12.129566593599224     },
      {43.90490961377783,  -9.867089926695087,    12.158780352364028     },
      {43.91382143307122,  -9.827351679192168,    12.18786865546446      },
      {43.922713791754845, -9.787531308140846,    12.216831346975562     },
      {43.93158638172877,  -9.747629248917045,    12.245668272452185     },
      {43.94043889635419,  -9.707645936378153,    12.274379278919088     },
      {43.94927103045748,  -9.667581804859056,    12.30296421486106      },
      {43.958082480333374, -9.627437288168135,    12.331422930213174     },
      {43.966872943748854, -9.587212819583485,    12.35975527635086      },
      {43.97564211994627,  -9.546908831849185,    12.387961106080237     },
      {43.984389709646756, -9.506525757171687,    12.416040273628266     },
      {43.993115415053126, -9.466064027216298,    12.443992634633059     },
      {44.00181893985345,  -9.425524073103793,    12.471818046134082     },
      {44.01049998922324,  -9.38490632540711,     12.499516366562561     },
      {44.019158269829,    -9.34421121414814,     12.527087455731667     },
      {44.0277934898304,   -9.303439168794679,    12.554531174827034     },
      {44.0364053588831,   -9.262590618257374,    12.58184738639698      },
      {44.044993588141395, -9.22166599088688,     12.609035954342975     },
      {44.053557890260294, -9.18066571447106,     12.636096743910084     },
      {44.06209797939799,  -9.139590216232268,    12.663029621677385     },
      {44.0706135712181,   -9.098439922824783,    12.689834455548471     },
      {44.079104382891735, -9.057215260332313,    12.716511114741932     },
      {44.087570133099355, -9.015916654265563,    12.743059469781937     },
      {44.09601054203287,  -8.974544529559973,    12.769479392488758     },
      {44.104425331397394, -8.933099310573477,    12.795770755969388     },
      {44.11281422441284,  -8.891581421084396,    12.821933434608201     },
      {44.121176945815705, -8.849991284289448,    12.847967304057542     },
      {44.12951322186048,  -8.808329322801756,    12.87387224122849      },
      {44.1378227803212,   -8.766595958649068,    12.899648124281518     },
      {44.14610535049271,  -8.724791613271995,    12.92529483261733      },
      {44.15436066319201,  -8.682916707522327,    12.950812246867564     },
      {44.16258845075933,  -8.64097166166151,     12.97620024888568      },
      {44.170788447059294, -8.59895689535914,     13.001458721737793     },
      {44.17896038748202,  -8.556872827691583,    13.026587549693598     },
      {44.187104008943905, -8.514719877140669,    13.051586618217224     },
      {44.19521904988862,  -8.472498461592476,    13.0764558139583       },
      {44.20330525028768,  -8.430208998336187,    13.101195024742873     },
      {44.211362351641455, -8.38785190406309,     13.12580413956452      },
      {44.21939009697949,  -8.34542759486553,     13.150283048575329     },
      {44.22738823086125,  -8.302936486236128,    13.174631643077152     },
      {44.23535649937646,  -8.260378993066887,    13.198849815512563     },
      {44.24329465014573,  -8.217755529648574,    13.222937459456277     },
      {44.251202432320476, -8.17506650967,        13.246894469606199     },
      {44.259079596583824, -8.132312346217518,    13.270720741774722     },
      {44.266925895149996, -8.08949345177452,     13.294416172880174     },
      {44.27474108176517,  -8.04661023822105,     13.317980660937948     },
      {44.28252491170717,  -8.003663116833497,    13.341414105052074     },
      {44.29027714178548,  -7.9606524982843325,   13.364716405406558     },
      {44.297997530341235, -7.917578792641942,    13.387887463256865     },
      {44.305685837247125, -7.874442409370559,    13.410927180921457     },
      {44.31334182390721,  -7.831243757330229,    13.433835461773302     },
      {44.320965253256475, -7.787983244776863,    13.45661221023152      },
      {44.328555889760935, -7.744661279362392,    13.479257331752965     },
      {44.336113499416655, -7.701278268134954,    13.501770732824022     },
      {44.343637849750095, -7.657834617539171,    13.52415232095212      },
      {44.351128709816834, -7.6143307334164865,   13.546402004657757     },
      {44.358585850201834, -7.570767021005621,    13.56851969346606      },
      {44.36600904301802,  -7.5271438849429995,   13.590505297898876     },
      {44.373398061906414, -7.483461729263364,    13.61235872946649      },
      {44.380752682035045, -7.439720957400365,    13.63407990065965      },
      {44.38807268009811,  -7.395921972187245,    13.655668724941542     },
      {44.395357834315575, -7.352065175857632,    13.677125116739845     },
      {44.40260792443209,  -7.3081509700463325,   13.698448991438763     },
      {44.40982273171606,  -7.264179755790232,    13.719640265371165     },
      {44.41700203895888,  -7.220151933529253,    13.740698855810844     },
      {44.424145630474015, -7.176067903107366,    13.761624680964523     },
      {44.43125329209566,  -7.131928063773673,    13.782417659964393     },
      {44.43832481117818,  -7.087732814183555,    13.803077712860148     },
      {44.44535997659452,  -7.0434825523998805,   13.823604760611586     },
      {44.45235857873551,  -6.999177675894245,    13.843998725080784     },
      {44.45932040950834,  -6.954818581548356,    13.864259529024748     },
      {44.46624526233561,  -6.910405665655363,    13.884387096087798     },
      {44.47313293215392,  -6.8659393239213315,   13.904381350794077     },
      {44.47998321541279,  -6.821419951466755,    13.924242218540272     },
      {44.48679591007303,  -6.776847942828102,    13.943969625588132     },
      {44.493570815605665, -6.732223691959448,    13.963563499057228     },
      {44.50030773299051,  -6.68754759223415,     13.983023766917633     },
      {44.507006464714564, -6.642820036446583,    14.002350357982777     },
      {44.51366681477097,  -6.598041416813926,    14.02154320190218      },
      {44.52028858865695,  -6.553212124977996,    14.040602229154434     },
      {44.52687159337299,  -6.508332552007175,    14.059527371040055     },
      {44.533415637420646, -6.463403088398327,    14.07831855967449      },
      {44.53992053080151,  -6.418424124078843,    14.096975727981182     },
      {44.54638608501536,  -6.3733960484086465,   14.11549880968452      },
      {44.55281211305848,  -6.328319250182346,    14.13388773930317      },
      {44.55919842942242,  -6.283194117631385,    14.152142452143007     },
      {44.565544850091776, -6.238021038426228,    14.170262884290537     },
      {44.571851192543015, -6.192800399678656,    14.188248972606077     },
      {44.578117275742514, -6.1475325879440526,   14.206100654717055     },
      {44.58434292014478,  -6.102217989223759,    14.223817869011471     },
      {44.59052794769096,  -6.056856988967514,    14.241400554631241     },
      {44.596672181806895, -6.011449972075855,    14.25884865146567      },
      {44.60277544740131,  -5.9659973229026715,   14.276162100145065     },
      {44.60883757086419,  -5.9204994252577094,   14.29334084203417      },
      {44.614858380064774, -5.874956662409191,    14.310384819225892     },
      {44.62083770434981,  -5.829369417086447,    14.327293974534943     },
      {44.6267753745418,   -5.783738071482593,    14.344068251491546     },
      {44.632671222937034, -5.738063007257271,    14.36070759433522      },
      {44.63852508330355,  -5.69234460553939,     14.377211948008624     },
      {44.64433679087967,  -5.646583246929984,    14.393581258151377     },
      {44.65010618237172,  -5.6007793115050335,   14.409815471094065     },
      {44.65583309595237,  -5.554933178818369,    14.425914533852104     },
      {44.66151737125842,  -5.509045227904627,    14.441878394119893     },
      {44.66715884938924,  -5.463115837282217,    14.457707000264797     },
      {44.67275737290447,  -5.417145384956344,    14.473400301321307     },
      {44.67831278582241,  -5.371134248422079,    14.48895824698521      },
      {44.683824933617814, -5.325082804667446,    14.504380787607843     },
      {44.68929366321994,  -5.278991430176565,    14.519667874190324     },
      {44.6947188230108,   -5.232860500932847,    14.534819458377974     },
      {44.70010026282292,  -5.186690392422177,    14.549835492454546     },
      {44.70543783393741,  -5.140481479636199,    14.564715929336863     },
      {44.710731389082305, -5.094234137075582,    14.579460722569085     },
      {44.715980782429924, -5.047948738753355,    14.594069826317408     },
      {44.721185869595665, -5.001625658198286,    14.608543195364595     },
      {44.72634650763534,  -4.9552652684582466,   14.62288078510458      },
      {44.73146255504351,  -4.908867942103662,    14.637082551537205     },
      {44.7365338717515,   -4.862434051230985,    14.651148451262927     },
      {44.74156031912523,  -4.8159639674661845,   14.665078441477664     },
      {44.74654175996345,  -4.769458061968288,    14.678872479967541     },
      {44.751478058495415, -4.722916705432934,    14.692530525103896     },
      {44.756369080379315, -4.6763402680959905,   14.706052535838097     },
      {44.76121469269991,  -4.629729119737179,    14.71943847169669      },
      {44.76601476396666,  -4.583083629683737,    14.732688292776308     },
      {44.770769164111826, -4.536404166814116,    14.745801959738856     },
      {44.77547776448843,  -4.489691099561708,    14.7587794338066       },
      {44.78014043786814,  -4.4429447959185895,   14.771620676757447     },
      {44.7847570584396,   -4.396165623439329,    14.784325650920096     },
      {44.7893275018061,   -4.349353949244786,    14.796894319169423     },
      {44.793851644983874, -4.302510140025959,    14.80932664492183      },
      {44.7983293664001,   -4.2556345620478595,   14.82162259213056      },
      {44.80276054589071,  -4.208727581153415,    14.833782125281301     },
      {44.80714506469893,  -4.161789562767403,    14.845805209387535     },
      {44.81148280547274,  -4.114820871900388,    14.857691809986243     },
      {44.81577365226351,  -4.06782187315274,     14.869441893133432     },
      {44.82001749052364,  -4.020792930718599,    14.88105542539978      },
      {44.82421420710495,  -3.9737344083899555,   14.892532373866436     },
      {44.82836369025664,  -3.926646669560676,    14.903872706120675     },
      {44.832465829623395, -3.8795300772306205,   14.915076390251825     },
      {44.836520516243596, -3.832384994009732,    14.926143394847042     },
      {44.84052764254727,  -3.785211782122181,    14.937073688987283     },
      {44.844487102354556, -3.7380108034105386,   14.947867242243227     },
      {44.84839879087347,  -3.6907824193399392,   14.95852402467134      },
      {44.85226260469834,  -3.643526991002304,    14.969044006809956     },
      {44.85607844180794,  -3.5962448791205683,   14.979427159675291     },
      {44.859846201563535, -3.548936444052929,    14.989673454757796     },
      {44.86356578470739,  -3.5016020457971413,   14.999782864018197     },
      {44.86723709336059,  -3.4542420439947783,   15.009755359883894     },
      {44.8708600310218,   -3.406856797935605,    15.019590915245228     },
      {44.8744345025648,   -3.359446666561854,    15.029289503451874     },
      {44.87796041423758,  -3.312012008472653,    15.03885109830929      },
      {44.881437673659875, -3.2645531819283535,   15.048275674075137     },
      {44.88486618982199,  -3.217070544854961,    15.057563205455875     },
      {44.888245873082894, -3.169564454848555,    15.066713667603278     },
      {44.89157663516852,  -3.122035269179714,    15.075727036111132     },
      {44.894858389170146, -3.074483344798,       15.084603287011856     },
      {44.89809104954293,  -3.0269090383364183,   15.093342396773288     },
      {44.90127453210398,  -2.979312706115924,    15.101944342295404     },
      {44.90440875403105,  -2.9316947041499297,   15.110409100907209     },
      {44.90749363386082,  -2.884055388148855,    15.118736650363601     },
      {44.91052909148726,  -2.8363951135246492,   15.126926968842282     },
      {44.91351504816029,  -2.78871423539539,     15.134980034940783     },
      {44.91645142648413,  -2.7410131085898444,   15.142895827673481     },
      {44.91933815041585,  -2.693292087652079,    15.150674326468657     },
      {44.92217514526372,  -2.6455515268460807,   15.1583155111657       },
      {44.9249623376861,   -2.597791780160379,    15.165819362012236     },
      {44.927699655689594, -2.5500132013127,      15.173185859661363     },
      {44.93038702862792,  -2.502216143754625,    15.180414985169008     },
      {44.93302438720046,  -2.4544009606762787,   15.187506719991148     },
      {44.93561166345076,  -2.406568005011003,    15.194461045981337     },
      {44.9381487907653,   -2.358717629440085,    15.20127794538804      },
      {44.94063570387206,  -2.3108501863974533,   15.207957400852155     },
      {44.94307233883934,  -2.262966028074433,    15.21449939540457      },
      {44.945458633074395, -2.215065506424486,    15.220903912463722     },
      {44.947794525322145, -2.1671489731679587,   15.22717093583326      },
      {44.950079955663895, -2.119216779796875,    15.233300449699737     },
      {44.952314865516364, -2.0712692775797015,   15.239292438630315     },
      {44.954499197630156, -2.0233068175661613,   15.245146887570602     },
      {44.95663289608876,  -1.9753297505920302,   15.250863781842476     },
      {44.95871590630747,  -1.9273384272839609,   15.256443107141951     },
      {44.9607481750321,   -1.8793331980643142,   15.261884849537125     },
      {44.96272965033794,  -1.8313144131560024,   15.267188995466267     },
      {44.96466028162884,  -1.7832824225873432,   15.272355531735622     },
      {44.96654001963586,  -1.7352375761969165,   15.277384445517821     },
      {44.96836881641654,  -1.6871802236384439,   15.282275724349708     },
      {44.97014662535362,  -1.6391107143856682,   15.287029356130802     },
      {44.97187340115442,  -1.5910293977372447,   15.291645329121273     },
      {44.97354909984948,  -1.5429366228216448,   15.296123631940521     },
      {44.97517367879197,  -1.494832738602063,    15.300464253565226     },
      {44.97674709665667,  -1.4467180938813453,   15.304667183327954     },
      {44.978269313439,    -1.398593037306901,    15.308732410915518     },
      {44.97974029045438,  -1.3504579173756537,   15.31265992636743      },
      {44.98115999033723,  -1.3023130824389682,   15.316449720074505     },
      {44.98252837704026,  -1.25415888070762,     15.320101782777414     },
      {44.98384541583375,  -1.2059956602567343,   15.323616105565304     },
      {44.98511107330464,  -1.1578237690307644,   15.326992679874587     },
      {44.986325317356034, -1.1096435548484556,   15.330231497487514     },
      {44.98748811720639,  -1.0614553654078254,   15.333332550531114     },
      {44.988599443388836, -1.0132595482911535,   15.336295831475924     },
      {44.98965926775065,  -0.9650564509699604,   15.33912133313498      },
      {44.99066756345253,  -0.9168464208100147,   15.341809048662626     },
      {44.9916243049682,   -0.8686298050763226,   15.344358971553598     },
      {44.99252946808355,  -0.820406950938148,    15.346771095642051     },
      {44.99338302989649,  -0.7721782054740112,   15.349045415100537     },
      {44.9941849688162,   -0.72394391567671,     15.351181924439514     },
      {44.99493526456249,  -0.6757044284583392,   15.35318061850518      },
      {44.99563389816696,  -0.6274600906553178,   15.355041492483629     },
      {44.996280851965906, -0.5792112490334036,   15.356764541882072     },
      {44.99687610962516,  -0.5309582502927856,   15.358349762595067     },
      {44.99741965604594,  -0.48270144107286295,  15.359797150654854     },
      {44.99791147771377,  -0.43444116795827836,  15.361106703159626     },
      {44.99835156139579,  -0.38617777748020166,  15.362278414807065     },
      {44.99873989900003,  -0.33791161613542176,  15.363312290828379     },
      {44.99907646944021,  -0.28964303033895716,  15.364208298717013     },
      {44.99936130631441,  -0.24137236662478417,  15.364966548373411     },
      {44.99959424532825,  -0.19309997092063205,  15.365586619806692     },
      {44.99977586691001,  -0.14482619127829868,  15.366070072146254     },
      {44.99990397836342,  -0.09655136770804099,  15.366411079993998     },
      {44.999986742537395, -0.048275870140680216, 15.366631378725746     },
      {44.99999136833833,  -0.016091916464460496, 15.36664369129905      },
      {45,                 1.881873914689766e-15, 15.366666666666667     },
      {44.99999136833833,  0.016091916464461488,  15.36664369129905      },
      {44.999986742537374, 0.04827587014067366,   15.366631378725742     },
      {44.999903978363434, 0.09655136770803932,   15.366411079994005     },
      {44.99977586691001,  0.14482619127828486,   15.366070072146254     },
      {44.99959424532823,  0.19309997092063153,   15.365586619806685     },
      {44.99936130631442,  0.24137236662477823,   15.364966548373413     },
      {44.999076469440205, 0.28964303033895056,   15.364208298717012     },
      {44.998739899000036, 0.3379116161354146,    15.363312290828377     },
      {44.99835156139578,  0.386177777480188,     15.362278414807067     },
      {44.99791147771378,  0.4344411679582816,    15.361106703159624     },
      {44.99741965604595,  0.48270144107285234,   15.359797150654856     },
      {44.99687610962515,  0.5309582502927866,    15.358349762595063     },
      {44.99628085196591,  0.5792112490333938,    15.356764541882079     },
      {44.99563389816695,  0.6274600906553109,    15.355041492483625     },
      {44.99493526456248,  0.6757044284583302,    15.353180618505181     },
      {44.9941849688162,   0.7239439156767097,    15.351181924439508     },
      {44.993383029896485, 0.7721782054740005,    15.34904541510054      },
      {44.99252946808356,  0.8204069509381452,    15.346771095642051     },
      {44.99162430496819,  0.8686298050763195,    15.344358971553593     },
      {44.99066756345255,  0.9168464208100146,    15.341809048662629     },
      {44.98965926775064,  0.9650564509699538,    15.339121333134973     },
      {44.98859944338884,  1.0132595482911422,    15.336295831475931     },
      {44.98748811720639,  1.061455365407816,     15.333332550531107     },
      {44.986325317356034, 1.1096435548484564,    15.330231497487516     },
      {44.98511107330462,  1.1578237690307596,    15.326992679874584     },
      {44.98384541583377,  1.2059956602567217,    15.323616105565309     },
      {44.98252837704025,  1.2541588807076216,    15.32010178277741      },
      {44.981159990337225, 1.3023130824389644,    15.316449720074502     },
      {44.97974029045439,  1.350457917375647,     15.312659926367434     },
      {44.978269313439,    1.398593037306897,     15.308732410915518     },
      {44.97674709665668,  1.4467180938813344,    15.304667183327958     },
      {44.97517367879198,  1.4948327386020606,    15.300464253565222     },
      {44.97354909984947,  1.5429366228216328,    15.296123631940517     },
      {44.97187340115441,  1.5910293977372478,    15.291645329121273     },
      {44.97014662535363,  1.639110714385656,     15.287029356130807     },
      {44.96836881641654,  1.6871802236384323,    15.282275724349706     },
      {44.96654001963587,  1.7352375761969137,    15.277384445517825     },
      {44.96466028162884,  1.7832824225873378,    15.272355531735625     },
      {44.96272965033793,  1.8313144131559915,    15.267188995466258     },
      {44.96074817503211,  1.8793331980643093,    15.261884849537134     },
      {44.95871590630746,  1.9273384272839555,    15.256443107141948     },
      {44.95663289608876,  1.9753297505920235,    15.25086378184248      },
      {44.95449919763016,  2.023306817566163,     15.245146887570602     },
      {44.95231486551637,  2.071269277579693,     15.239292438630319     },
      {44.95007995566391,  2.119216779796863,     15.233300449699739     },
      {44.94779452532213,  2.16714897316796,      15.22717093583326      },
      {44.94545863307441,  2.2150655064244744,    15.220903912463722     },
      {44.94307233883936,  2.26296602807443,      15.21449939540457      },
      {44.94063570387206,  2.310850186397446,     15.207957400852157     },
      {44.9381487907653,   2.358717629440074,     15.201277945388041     },
      {44.93561166345076,  2.406568005011006,     15.194461045981337     },
      {44.933024387200476, 2.45440096067627,      15.187506719991156     },
      {44.93038702862791,  2.5022161437546204,    15.180414985169001     },
      {44.9276996556896,   2.550013201312697,     15.173185859661372     },
      {44.92496233768609,  2.5977917801603723,    15.165819362012233     },
      {44.922175145263736, 2.645551526846067,     15.158315511165704     },
      {44.91933815041584,  2.6932920876520807,    15.150674326468657     },
      {44.91645142648414,  2.74101310858983,      15.142895827673485     },
      {44.9135150481603,   2.7887142353953824,    15.134980034940787     },
      {44.91052909148725,  2.8363951135246515,    15.126926968842277     },
      {44.907493633860824, 2.884055388148843,     15.118736650363598     },
      {44.904408754031046, 2.931694704149934,     15.110409100907216     },
      {44.90127453210398,  2.9793127061159135,    15.1019443422954       },
      {44.89809104954293,  3.026909038336412,     15.093342396773298     },
      {44.894858389170146, 3.074483344797992,     15.084603287011856     },
      {44.891576635168526, 3.1220352691797078,    15.075727036111132     },
      {44.888245873082866, 3.1695644548485458,    15.066713667603281     },
      {44.88486618982202,  3.2170705448549506,    15.057563205455875     },
      {44.88143767365988,  3.2645531819283495,    15.048275674075137     },
      {44.87796041423756,  3.3120120084726508,    15.03885109830929      },
      {44.874434502564824, 3.359446666561854,     15.029289503451878     },
      {44.87086003102178,  3.406856797935597,     15.019590915245232     },
      {44.867237093360636, 3.4542420439947663,    15.009755359883894     },
      {44.86356578470739,  3.5016020457971417,    14.999782864018197     },
      {44.85984620156354,  3.5489364440529183,    14.989673454757803     },
      {44.856078441807924, 3.596244879120564,     14.97942715967529      },
      {44.85226260469834,  3.6435269910022927,    14.96904400680995      },
      {44.848398790873475, 3.6907824193399357,    14.958524024671346     },
      {44.844487102354556, 3.7380108034105404,    14.947867242243229     },
      {44.8405276425473,   3.7852117821221754,    14.937073688987287     },
      {44.83652051624358,  3.8323849940097254,    14.926143394847049     },
      {44.83246582962341,  3.8795300772306134,    14.91507639025183      },
      {44.82836369025664,  3.926646669560675,     14.903872706120675     },
      {44.824214207104944, 3.9737344083899457,    14.892532373866441     },
      {44.820017490523654, 4.020792930718605,     14.881055425399774     },
      {44.8157736522635,   4.067821873152726,     14.86944189313343      },
      {44.81148280547274,  4.114820871900395,     14.85769180998624      },
      {44.80714506469892,  4.161789562767397,     14.845805209387539     },
      {44.802760545890706, 4.2087275811534095,    14.833782125281294     },
      {44.79832936640011,  4.255634562047857,     14.821622592130561     },
      {44.79385164498386,  4.302510140025945,     14.809326644921832     },
      {44.78932750180611,  4.34935394924478,      14.796894319169423     },
      {44.78475705843961,  4.396165623439329,     14.7843256509201       },
      {44.780140437868134, 4.442944795918583,     14.771620676757443     },
      {44.77547776448843,  4.489691099561704,     14.758779433806605     },
      {44.77076916411182,  4.536404166814103,     14.745801959738857     },
      {44.76601476396666,  4.583083629683739,     14.732688292776308     },
      {44.761214692699916, 4.629729119737172,     14.71943847169669      },
      {44.75636908037933,  4.676340268095977,     14.706052535838104     },
      {44.75147805849545,  4.72291670543293,      14.692530525103887     },
      {44.74654175996344,  4.769458061968283,     14.678872479967547     },
      {44.74156031912523,  4.81596396746618,      14.665078441477664     },
      {44.73653387175148,  4.862434051230979,     14.65114845126293      },
      {44.731462555043514, 4.908867942103658,     14.637082551537203     },
      {44.726346507635334, 4.955265268458237,     14.622880785104583     },
      {44.72118586959566,  5.001625658198281,     14.608543195364597     },
      {44.71598078242996,  5.047948738753346,     14.594069826317412     },
      {44.71073138908228,  5.094234137075578,     14.579460722569083     },
      {44.70543783393743,  5.140481479636189,     14.564715929336863     },
      {44.700100262822914, 5.186690392422177,     14.54983549245455      },
      {44.6947188230108,   5.232860500932841,     14.534819458377976     },
      {44.68929366321994,  5.278991430176557,     14.519667874190333     },
      {44.683824933617814, 5.325082804667439,     14.504380787607843     },
      {44.67831278582241,  5.371134248422076,     14.488958246985208     },
      {44.67275737290446,  5.417145384956335,     14.473400301321313     },
      {44.66715884938924,  5.463115837282212,     14.457707000264792     },
      {44.66151737125842,  5.5090452279046165,    14.441878394119897     },
      {44.65583309595236,  5.554933178818365,     14.425914533852106     },
      {44.65010618237172,  5.600779311505029,     14.409815471094065     },
      {44.644336790879684, 5.646583246929981,     14.393581258151382     },
      {44.63852508330355,  5.692344605539384,     14.377211948008622     },
      {44.632671222937034, 5.738063007257264,     14.360707594335217     },
      {44.62677537454181,  5.783738071482588,     14.344068251491551     },
      {44.62083770434981,  5.829369417086437,     14.327293974534943     },
      {44.61485838006477,  5.8749566624091845,    14.310384819225892     },
      {44.608837570864175, 5.920499425257699,     14.293340842034171     },
      {44.60277544740133,  5.965997322902665,     14.276162100145077     },
      {44.59667218180691,  6.0114499720758525,    14.258848651465673     },
      {44.590527947690944, 6.056856988967515,     14.241400554631234     },
      {44.584342920144785, 6.102217989223755,     14.223817869011478     },
      {44.57811727574251,  6.147532587944037,     14.206100654717059     },
      {44.57185119254302,  6.192800399678655,     14.188248972606075     },
      {44.56554485009179,  6.238021038426217,     14.170262884290544     },
      {44.55919842942241,  6.283194117631383,     14.152142452143002     },
      {44.55281211305847,  6.328319250182333,     14.133887739303173     },
      {44.546386085015364, 6.373396048408647,     14.11549880968452      },
      {44.53992053080151,  6.418424124078831,     14.096975727981183     },
      {44.533415637420646, 6.463403088398328,     14.078318559674491     },
      {44.526871593372974, 6.508332552007175,     14.059527371040053     },
      {44.52028858865697,  6.5532121249779856,    14.04060222915444      },
      {44.51366681477097,  6.598041416813922,     14.021543201902178     },
      {44.507006464714586, 6.642820036446579,     14.002350357982786     },
      {44.50030773299049,  6.68754759223415,      13.983023766917631     },
      {44.493570815605665, 6.7322236919594385,    13.963563499057228     },
      {44.48679591007302,  6.776847942828104,     13.943969625588132     },
      {44.47998321541279,  6.821419951466751,     13.924242218540268     },
      {44.473132932153945, 6.865939323921326,     13.90438135079408      },
      {44.466245262335576, 6.910405665655355,     13.884387096087794     },
      {44.459320409508365, 6.954818581548354,     13.864259529024757     },
      {44.45235857873551,  6.999177675894241,     13.84399872508079      },
      {44.4453599765945,   7.043482552399869,     13.823604760611586     },
      {44.438324811178184, 7.0877328141835605,    13.803077712860151     },
      {44.43125329209566,  7.1319280637736675,    13.782417659964398     },
      {44.42414563047402,  7.176067903107359,     13.761624680964527     },
      {44.41700203895888,  7.220151933529252,     13.740698855810848     },
      {44.409822731716076, 7.26417975579022,      13.719640265371174     },
      {44.402607924432075, 7.308150970046325,     13.698448991438765     },
      {44.395357834315575, 7.352065175857623,     13.677125116739848     },
      {44.388072680098134, 7.395921972187244,     13.655668724941545     },
      {44.380752682035016, 7.439720957400352,     13.63407990065965      },
      {44.373398061906435, 7.483461729263368,     13.612358729466488     },
      {44.366009043018025, 7.527143884942994,     13.590505297898886     },
      {44.3585858502018,   7.570767021005612,     13.568519693466062     },
      {44.351128709816905, 7.6143307334164785,    13.546402004657747     },
      {44.34363784975007,  7.657834617539161,     13.524152320952123     },
      {44.33611349941667,  7.701278268134944,     13.501770732824022     },
      {44.32855588976094,  7.744661279362392,     13.47925733175298      },
      {44.320965253256475, 7.787983244776854,     13.456612210231524     },
      {44.31334182390721,  7.831243757330224,     13.433835461773302     },
      {44.30568583724712,  7.874442409370555,     13.410927180921458     },
      {44.29799753034126,  7.91757879264194,      13.387887463256872     },
      {44.29027714178548,  7.96065249828432,      13.364716405406563     },
      {44.28252491170717,  8.003663116833497,     13.341414105052081     },
      {44.27474108176519,  8.046610238221046,     13.317980660937952     },
      {44.26692589515002,  8.089493451774516,     13.29441617288017      },
      {44.2590795965838,   8.132312346217507,     13.270720741774728     },
      {44.251202432320504, 8.175066509669996,     13.2468944696062       },
      {44.243294650145714, 8.217755529648567,     13.222937459456281     },
      {44.235356499376486, 8.260378993066887,     13.198849815512574     },
      {44.22738823086123,  8.302936486236115,     13.17463164307714      },
      {44.2193900969795,   8.345427594865525,     13.15028304857534      },
      {44.211362351641455, 8.38785190406309,      13.125804139564522     },
      {44.20330525028768,  8.43020899833618,      13.101195024742879     },
      {44.19521904988863,  8.472498461592478,     13.076455813958296     },
      {44.18710400894392,  8.51471987714066,      13.051586618217232     },
      {44.17896038748201,  8.556872827691581,     13.026587549693595     },
      {44.17078844705931,  8.598956895359134,     13.001458721737801     },
      {44.16258845075933,  8.640971661661506,     12.976200248885679     },
      {44.15436066319201,  8.682916707522322,     12.950812246867569     },
      {44.14610535049271,  8.72479161327199,      12.925294832617329     },
      {44.13782278032121,  8.766595958649063,     12.899648124281528     },
      {44.12951322186048,  8.808329322801754,     12.873872241228492     },
      {44.12117694581572,  8.849991284289445,     12.847967304057548     },
      {44.11281422441284,  8.891581421084396,     12.821933434608194     },
      {44.10442533139741,  8.93309931057347,      12.795770755969397     },
      {44.09601054203285,  8.974544529559966,     12.769479392488753     },
      {44.08757013309936,  9.015916654265563,     12.743059469781933     },
      {44.07910438289172,  9.057215260332306,     12.716511114741937     },
      {44.070613571218104, 9.09843992282478,      12.689834455548477     },
      {44.06209797939799,  9.139590216232262,     12.663029621677389     },
      {44.05355789026028,  9.180665714471054,     12.636096743910088     },
      {44.0449935881414,   9.221665990886882,     12.609035954342975     },
      {44.03640535888311,  9.262590618257367,     12.581847386396984     },
      {44.02779348983039,  9.303439168794668,     12.554531174827037     },
      {44.01915826982899,  9.344211214148135,     12.527087455731674     },
      {44.01049998922324,  9.3849063254071,       12.499516366562563     },
      {44.00181893985343,  9.425524073103789,     12.471818046134084     },
      {43.993115415053154, 9.46606402721629,      12.443992634633057     },
      {43.98438970964675,  9.506525757171683,     12.416040273628276     },
      {43.97564211994628,  9.54690883184918,      12.387961106080235     },
      {43.966872943748854, 9.587212819583485,     12.35975527635086      },
      {43.95808248033338,  9.627437288168124,     12.331422930213183     },
      {43.94927103045748,  9.667581804859054,     12.302964214861067     },
      {43.94043889635418,  9.707645936378148,     12.274379278919088     },
      {43.931586381728756, 9.747629248917036,     12.245668272452185     },
      {43.92271379175485,  9.787531308140839,     12.216831346975566     },
      {43.913821433071206, 9.827351679192162,     12.187868655464458     },
      {43.90490961377781,  9.867089926695078,     12.158780352364033     },
      {43.895978643431945, 9.906745614759371,     12.129566593599224     },
      {43.88702883304438,  9.94631830698469,      12.100227536584615     },
      {43.87806049507515,  9.985807566464993,     12.07076334023433      },
      {43.86907394342948,  10.025212955793025,    12.041174164971997     },
      {43.86006949345312,  10.064534037064885,    12.011460172740598     },
      {43.851047461928346, 10.103770371884774,    11.981621527012464     },
      {43.84200816706896,  10.142921521369795,    11.951658392799223     },
      {43.83295192851563,  10.181987046154875,    11.921570936661782     },
      {43.823879067331255, 10.220966506397897,    11.891359326720227     },
      {43.81478990599555,  10.2598594617848,      11.86102373266395      },
      {43.8056847684004,   10.298665471534875,    11.830564325761497     },
      {43.79656397984408,  10.33738409440621,     11.799981278870712     },
      {43.787427867026324, 10.3760148887012,      11.769274766448623     },
      {43.77827675804231,  10.414557412272206,    11.738444964561564     },
      {43.76911098237745,  10.453011222527259,    11.70749205089517      },
      {43.75993087090108,  10.491375876436052,    11.67641620476436      },
      {43.75073675586078,  10.529650930535857,    11.645217607123495     },
      {43.741528970876274, 10.567835940937739,    11.61389644057622      },
      {43.732307850932884, 10.60593046333271,     11.58245288938573      },
      {43.72307373237543,  10.643934052998244,    11.550887139484631     },
      {43.71382695290142,  10.68184626480464,     11.519199378485087     },
      {43.70456785155448,  10.719666653221775,    11.487389795688769     },
      {43.695296768717405, 10.757394772325775,    11.455458582096973     },
      {43.68601404610516,  10.795030175805955,    11.423405930420621     },
      {43.676720026757664, 10.832572416971772,    11.39123203509029      },
      {43.66741505503251,  10.870021048760039,    11.358937092266183     },
      {43.65809947659752,  10.907375623742135,    11.326521299848231     },
      {43.64877363842281,  10.944635694131431,    11.29398485748603      },
      {43.639437888773365, 10.981800811790823,    11.261327966588883     },
      {43.630092577200685, 11.018870528240345,    11.228550830335754     },
      {43.62073805453508,  11.055844394665035,    11.195653653685211     },
      {43.61137467287674,  11.092721961922843,    11.162636643385522     },
      {43.602002785588084, 11.12950278055258,     11.129500007984372     },
      {43.59262274728416,  11.166186400782298,    11.096243957839091     },
      {43.58323491382479,  11.202772372537437,    11.062868705126245     },
      {43.573839642304755, 11.239260245449422,    11.029374463851806     },
      {43.564437291045294, 11.275649568864132,    10.995761449860863     },
      {43.55502821958441,  11.311939891850749,    10.962029880847536     },
      {43.5456127886674,   11.348130763210559,    10.928179976364822     },
      {43.536191360237375, 11.384221731485951,    10.894211957834383     },
      {43.526764297425146, 11.420212344969606,    10.860126048556324     },
      {43.51733196453942,  11.45610215171374,     10.825922473718986     },
      {43.50789472705651,  11.49189069953952,     10.791601460408637     },
      {43.49845295160981,  11.52757753604664,     10.75716323761928      },
      {43.48900700597949,  11.563162208623037,    10.72260803626213      },
      {43.479557259081524, 11.598644264454698,    10.68793608917547      },
      {43.47010408095683,  11.634023250535625,    10.653147631134127     },
      {43.46064784276022,  11.669298713677982,    10.618242898859105     },
      {43.45118891674888,  11.704470200522408,    10.583222131027103     },
      {43.44172767627117,  11.739537257548262,    10.54808556828002      },
      {43.432264495754644, 11.77449943108439,     10.512833453234444     },
      {43.42279975069442,  11.809356267319577,    10.47746603049101      },
      {43.413333817640954, 11.844107312313593,    10.441983546643872     },
      {43.40386707418787,  11.878752112008016,    10.406386250289982     },
      {43.39439989895945,  11.913290212237408,    10.370674392038365     },
      {43.384932671598015, 11.947721158740638,    10.334848224519455     },
      {43.375465772751184, 11.982044497172135,    10.298908002394196     },
      {43.36599958405862,  12.016259773113601,    10.262853982363245     },
      {43.35653448813913,  12.050366532085619,    10.22668642317605      },
      {43.34707086857683,  12.084364319559517,    10.190405585639907     },
      {43.337609109907916, 12.118252680969373,    10.154011732628978     },
      {43.32814959760658,  12.152031161724107,    10.117505129093121     },
      {43.31869271807109,  12.18569930721981,     10.080886042066945     },
      {43.30923885860954,  12.219256662852157,    10.044154740678415     },
      {43.299788407425574, 12.252702774028933,    10.00731149615778      },
      {43.29034175360337,  12.286037186182837,    9.970356581846206      },
      {43.280899287093355, 12.319259444784246,    9.933290273204378      },
      {43.271461398696644, 12.352369095354364,    9.896112847821108      },
      {43.26202848005022,  12.38536568347821,     9.85882458542179       },
      {43.252600923611226, 12.41824875481807,     9.821425767876878      },
      {43.243179122641486, 12.451017855126874,    9.783916679210181      },
      {43.233763471191516, 12.483672530261826,    9.746297605607168      },
      {43.2243543640846,   12.516212326198133,    9.708568835423216      },
      {43.21495219690038,  12.548636789042902,    9.670730659191666      },
      {43.20555736595858,  12.580945465049204,    9.632783369631895      },
      {43.19617026830211,  12.613137900630203,    9.594727261657372      },
      {43.18679130168037,  12.645213642373562,    9.556562632383374      },
      {43.17742086453199,  12.677172237055863,    9.518289781134992      },
      {43.16805935596762,  12.709013231657298,    9.479909009454659      },
      {43.15870717575251,  12.740736173376327,    9.441420621109934      },
      {43.14936472428849,  12.772340609644743,    9.402824922100962      },
      {43.140032402596404, 12.803826088142653,    9.364122220667923      },
      {43.13071061229768,  12.835192156813637,    9.325312827298422      },
      {43.121399755596215, 12.866438363880228,    9.286397054734735      },
      {43.11210023525952,  12.897564257859308,    9.247375217980997      },
      {43.10281245460028,  12.928569387577813,    9.208247634310194      },
      {43.09353681745725,  12.959453302188459,    9.16901462327122       },
      {43.08427372817578,  12.99021555118576,     9.129676506695697      },
      {43.07502359158899,  13.020855684422004,    9.090233608704713      },
      {43.06578681299765,  13.051373252123533,    9.050686255715513      },
      {43.056563798150634, 13.081767804907097,    9.011034776448005      },
      {43.047354953224854, 13.112038893796328,    8.971279501931203      },
      {43.03816068480481,  13.142186070238424,    8.931420765509607      },
      {43.02898139986256,  13.172208886120853,    8.891458902849273      },
      {43.01981750573672,  13.202106893788397,    8.851394251944058      },
      {43.010669410111774, 13.231879646060069,    8.811227153121434      },
      {43.001537520996806, 13.261526696246468,    8.770957949048494      },
      {42.99242224670459,  13.291047598166978,    8.730586984737588      },
      {42.98332399582982,  13.320441906167323,    8.690114607551884      },
      {42.974243177227436, 13.349709175137168,    8.649541167210995      },
      {42.96518019999083,  13.378848960527854,    8.60886701579619       },
      {42.95613547342986,  13.407860818370285,    8.568092507755654      },
      {42.94710940704825,  13.43674430529291,     8.527217999909606      },
      {42.93810241052134,  13.465498978539996,    8.486243851455242      },
      {42.92911489367334,  13.494124395989706,    8.445170423971497      },
      {42.92014726645427,  13.52262011617272,     8.403998081423826      },
      {42.91119993891722,  13.550985698290615,    8.362727190168634      },
      {42.90227332119451,  13.57922070223464,     8.321358118957766      },
      {42.893367823474804, 13.607324688604479,    8.279891238942696      },
      {42.8844838559789,   13.635297218727148,    8.238326923678674      },
      {42.87562182893619,  13.663137854676101,    8.19666554912864       },
      {42.86678215256026,  13.690846159290386,    8.154907493667123      },
      {42.857965237025084, 13.718421696193891,    8.113053138083764      },
      {42.849171492439936, 13.745864029814902,    8.07110286558696       },
      {42.84040132882532,  13.773172725405455,    8.029057061807125      },
      {42.831655156087734, 13.800347349061177,    7.986916114799889      },
      {42.82293338399482,  13.82738746774092,     7.9446804150491666     },
      {42.81423642215008,  13.854292649286805,    7.902350355469991      },
      {42.80556467996753,  13.881062462444081,    7.859926331411242      },
      {42.796918566646006, 13.907696476881341,    7.817408740658166      },
      {42.788298491143564, 13.934194263210761,    7.774797983434754      },
      {42.779704862151306, 13.960555393008407,    7.7320944624059935     },
      {42.771138088067616, 13.986779438834688,    7.689298582679784      },
      {42.762598576971456, 14.012865974254982,    7.6464107518089275     },
      {42.754086736596136, 14.038814573860254,    7.603431379792751      },
      {42.745602974302756, 14.064624813287791,    7.560360879078585      },
      {42.73714769705308,  14.090296269242213,    7.51719966456316       },
      {42.72872131138308,  14.115828519516253,    7.473948153593675      },
      {42.72032422337507,  14.14122114301206,     7.430606765968873      },
      {42.71195683863124,  14.166473719762129,    7.3871759239397035     },
      {42.70361956224547,  14.191585830950801,    7.343656052209973      },
      {42.69531279877627,  14.216557058935427,    7.300047577936783      },
      {42.68703695221868,  14.241386987267925,    7.256350930730675      },
      {42.678792425976475, 14.26607520071629,     7.212566542655717      },
      {42.67057962283401,  14.290621285286255,    7.168694848229325      },
      {42.66239894492825,  14.315024828242901,    7.124736284421858      },
      {42.65425079372005,  14.339285418132597,    7.080691290656125      },
      {42.646135569965985, 14.363402644804717,    7.036560308806576      },
      {42.6380536736895,   14.38737609943372,     6.992343783198387      },
      {42.63000550415231,  14.411205374541112,    6.948042160606244      },
      {42.62199145982527,  14.434890064017559,    6.90365589025304       },
      {42.61401193835966,  14.458429763145048,    6.8591854238082846     },
      {42.60606733655767,  14.481824068619169,    6.814631215386326      },
      {42.59815805034357,  14.50507257857137,     6.769993721544378      },
      {42.59028447473369,  14.528174892591366,    6.725273401280313      },
      {42.58244700380763,  14.55113061174956,     6.680470716030283      },
      {42.574646030678,    14.573939338619542,    6.635586129666109      },
      {42.56688194746117,  14.596600677300628,    6.590620108492379      },
      {42.55915514524702,  14.619114233440488,    6.545573121243564      },
      {42.55146601406939,  14.64147961425776,     6.5004456390805245     },
      {42.543814942875755, 14.663696428564808,    6.455238135587265      },
      {42.536202319497114, 14.685764286790416,    6.409951086767108      },
      {42.528628530618,    14.707682801002612,    6.364584971038743      },
      {42.52109396174597,  14.729451584931534,    6.319140269232198      },
      {42.513598997181106, 14.751070253992205,    6.273617464584355      },
      {42.50614401998583,  14.772538425307603,    6.228017042734471      },
      {42.4987294119542,   14.793855717731372,    6.182339491719237      },
      {42.49135555358118,  14.815021751871017,    6.136585301967889      },
      {42.484022824032216, 14.836036150110777,    6.090754966296708      },
      {42.4767316011122,   14.85689853663466,     6.044848979903814      },
      {42.46948226123495,  14.877608537449488,    5.9988678403631255     },
      {42.46227517939211,  14.898165780407943,    5.9528120476186155     },
      {42.455110729122254, 14.918569895231705,    5.9066821039780315     },
      {42.447989282480194, 14.938820513534404,    5.860478514106445      },
      {42.44091121000563,  14.958917268844832,    5.814201785019596      },
      {42.43387688069225,  14.978859796629983,    5.767852426077048      },
      {42.42688666195686,  14.998647734318125,    5.721430948974966      },
      {42.41994091960785,  15.018280721321975,    5.674937867738778      },
      {42.41304001781458,  15.0377583990617,      5.628373698715573      },
      {42.40618431907575,  15.057080410988057,    5.581738960566234      },
      {42.399374184188744, 15.076246402605438,    5.535034174257325      },
      {42.39260997221797,  15.095256021494938,    5.488259863052804      },
      {42.38589204046413,  15.114108917337399,    5.441416552505406      },
      {42.379220744432764, 15.132804741936381,    5.394504770447861      },
      {42.372596437803224, 15.151343149241253,    5.347525046983819      },
      {42.36601947239749,  15.169723795370048,    5.300477914478541      },
      {42.35949019814906,  15.187946338632447,    5.253363907549401      },
      {42.35300896307186,  15.206010439552692,    5.206183563056029      },
      {42.34657611322895,  15.223915760892442,    5.158937420090368      },
      {42.340191992701946, 15.241661967673519,    5.111626019966335      },
      {42.333856943559454, 15.259248727200777,    5.064249906209297      },
      {42.32757130582641,  15.27667570908481,     5.016809624545423      },
      {42.321335417453135, 15.293942585264526,    4.969305722890476      },
      {42.31514961428428,  15.311049030029906,    4.921738751338817      },
      {42.30901423002837,  15.32799472004442,     4.874109262151627      },
      {42.30292959622643,  15.344779334367638,    4.82641780974545       },
      {42.29689604222209,  15.361402554477564,    4.7786649506799606     },
      {42.29091389513019,  15.37786406429303,     4.730851243645914      },
      {42.284983479806904, 15.394163550195962,    4.682977249452577      },
      {42.27910511881861,  15.41030070105363,     4.635043531015043      },
      {42.27327913241234,  15.42627520824066,     4.587050653341248      },
      {42.2675058384847,   15.442086765661191,    4.538999183518781      },
      {42.26178555255217,  15.457735069770708,    4.490889690701438      },
      {42.256118587721055, 15.473219819598022,    4.442722746095536      },
      {42.250505254657305, 15.488540716766853,    4.394498922945909      },
      {42.244945861556715, 15.503697465517682,    4.346218796521826      },
      {42.239440714115425, 15.518689772729147,    4.29788294410253       },
      {42.23399011550008,  15.533517347939583,    4.249491944962551      },
      {42.228594366318646, 15.548179903368258,    4.201046380356821      },
      {42.22325376459077,  15.562677153936711,    4.152546833505555      },
      {42.21796860571885,  15.577008817289787,    4.103993889578859      },
      {42.212739182459046, 15.59117461381657,     4.055388135681076      },
      {42.20756578489214,  15.605174266671337,    4.006730160835016      },
      {42.20244870039532,  15.619007501794144,    3.9580205559657182     },
      {42.19738821361302,  15.632674047931598,    3.9092599138843083     },
      {42.19238460642919,  15.646173636657089,    3.8604488292712578     },
      {42.187438157938615, 15.659506002391286,    3.8115878986597265     },
      {42.182549144419326, 15.67267088242217,     3.7626777204184685     },
      {42.17771783930451,  15.6856680169251,      3.7137188947345257     },
      {42.17294451315495,  15.698497148982723,    3.664712023595874      },
      {42.16822943363179,  15.711158024604558,    3.6156577107735726     },
      {42.16357286546911,  15.72365039274666,     3.5665565618039223     },
      {42.15897507044707,  15.735974005330945,    3.5174091839701944     },
      {42.154436307365124, 15.74812861726443,     3.4682161862843155     },
      {42.14995683201545,  15.760113986458233,    3.418978179468241      },
      {42.14553689715658,  15.771929873846503,    3.369695775935061      },
      {42.141176752487496, 15.78357604340508,     3.320369589770028      },
      {42.136876644621545, 15.795052262170017,    3.271000236711212      },
      {42.132636817061,    15.806358300255898,    3.2215883341300207     },
      {42.12845751017173,  15.817493930873987,    3.1721345010115476     },
      {42.124338961157854, 15.828458930350195,    3.1226393579345753     },
      {42.120281404037414, 15.839253078142711,    3.0731035270515172     },
      {42.1162850696172,   15.849876156859786,    3.0235276320679993     },
      {42.112350185468856, 15.860327952276855,    2.9739122982224706     },
      {42.10847697590494,  15.870608253353783,    2.924258152265208      },
      {42.10466566195469,  15.880716852251787,    2.8745658224376687     },
      {42.100916461341164, 15.890653544350194,    2.824835938451062      },
      {42.09722958845772,  15.900418128262853,    2.7750691314651856     },
      {42.09360525434537,  15.910010405854536,    2.7252660340668022     },
      {42.09004366666993,  15.919430182256876,    2.675427280247944      },
      {42.08654502970013,  15.928677265884353,    2.6255535053839467     },
      {42.08310954428556,  15.937751468449765,    2.5756453462113518     },
      {42.07973740783486,  15.946652604979683,    2.525703440805602      },
      {42.07642881429477,  15.95538049382955,     2.475728428558608      },
      {42.07318395412881,  15.96393495669868,     2.4257209501559776     },
      {42.070003014296965, 15.972315818644745,    2.375681647554273      },
      {42.066886178235215, 15.98052290809837,     2.325611163957938      },
      {42.06383362583561,  15.988556056877169,    2.275510143796128      },
      {42.06084553342656,  15.996415100199801,    2.225379232699355      },
      {42.0579220737539,   16.00409987669947,     2.1752190774759215     },
      {42.0550634159615,   16.011610228437505,    2.1250303260882877     },
      {42.05226972557332,  16.01894600091632,     2.0748136276291533     },
      {42.04954116447453,  16.026107043092537,    2.0245696322975353     },
      {42.0468778908944,   16.033093207389385,    1.9742989913745053     },
      {42.04428005938823,  16.039904349709243,    1.924002357198912      },
      {42.04174782082076,  16.046540329445566,    1.873680383142958      },
      {42.03928132234923,  16.053001009494828,    1.8233337235874987     },
      {42.03688070740719,  16.059286256267995,    1.7729630338973754     },
      {42.03454611568841,  16.065395939701833,    1.722568970396446      },
      {42.03227768313157,  16.071329933269837,    1.6721521903426086     },
      {42.03007554190502,  16.077088113993003,    1.6217133519025997     },
      {42.02793982039201,  16.08267036245018,     1.5712531141267425     },
      {42.02587064317653,  16.08807656278824,     1.5207721369234863     },
      {42.023868131029026, 16.093306602731936,    1.470271081033863      },
      {42.02193240089338,  16.0983603735934,      1.419750608005903      },
      {42.02006356587336,  16.103237770281467,    1.3692113801687045     },
      {42.01826173522011,  16.107938691310572,    1.3186540606067587     },
      {42.016527014319934, 16.11246303880953,     1.2680793131337098     },
      {42.014859504682356, 16.11681071852973,     1.217487802266468      },
      {42.01325930392859,  16.120981639853433,    1.1668801931988675     },
      {42.01172650578086,  16.124975715801277,    1.116257151775403      },
      {42.01026120005131,  16.128792863040026,    1.065619344464879      },
      {42.008863472632534, 16.132433001889428,    1.0149674383338563     },
      {42.007533405487045, 16.135896056329372,    0.964302101020089      },
      {42.00627107663883,  16.139181954006173,    0.913624000705926      },
      {42.00507656016389,  16.142290626238943,    0.8629338060915042     },
      {42.003949926182166, 16.145222008025495,    0.8122321863680089     },
      {42.002891240849415, 16.147976038047922,    0.7615198111906966     },
      {42.001900566349775, 16.150552658677906,    0.7107973506520351     },
      {42.000977960888854, 16.15295181598171,     0.6600654752546736     },
      {42.00012347868665,  16.155173459724843,    0.6093248558843355     },
      {41.999337169971966, 16.15721754337636,     0.5585761637826787     },
      {41.998619080976304, 16.15908402411294,     0.5078200705201943     },
      {41.99796925392866,  16.160772862822615,    0.4570572479688869     },
      {41.99738772705083,  16.16228402410808,     0.40628836827507325    },
      {41.996874534552965, 16.163617476289822,    0.3555141038320095     },
      {41.99642970662961,  16.164773191408884,    0.3047351272525784     },
      {41.99605326945647,  16.165751145229205,    0.25395211134190476    },
      {41.99574524518718,  16.166551317239865,    0.20316572906992467    },
      {41.99550565195094,  16.16717369065667,     0.15237665354399563    },
      {41.99533450385037,  16.167618252423832,    0.10158555798137131    },
      {41.99523181095994,  16.167884993214912,    0.050793115681800546   },
      {41.995197579324746, 16.167973907433755,    3.7001651742585295e-15 },
      {41.99523181095995,  16.167884993214912,    -0.050793115681792865  },
      {41.99533450385037,  16.167618252423836,    -0.1015855579813589    },
      {41.99550565195095,  16.167173690656668,    -0.152376653543988     },
      {41.99574524518717,  16.16655131723986,     -0.20316572906992192   },
      {41.99605326945649,  16.165751145229212,    -0.25395211134190215   },
      {41.9964297066296,   16.164773191408884,    -0.3047351272525707    },
      {41.99687453455297,  16.16361747628982,     -0.3555141038319971    },
      {41.99738772705079,  16.16228402410809,     -0.40628836827506576   },
      {41.997969253928666, 16.16077286282261,     -0.4570572479688795    },
      {41.99861908097632,  16.15908402411295,     -0.5078200705201866    },
      {41.99933716997197,  16.157217543376355,    -0.5585761637826662    },
      {42.00012347868664,  16.15517345972484,     -0.6093248558843278    },
      {42.00097796088885,  16.152951815981716,    -0.6600654752546709    },
      {42.001900566349775, 16.150552658677906,    -0.7107973506520323    },
      {42.002891240849394, 16.14797603804792,     -0.7615198111906891    },
      {42.00394992618217,  16.145222008025495,    -0.8122321863679965    },
      {42.0050765601639,   16.142290626238943,    -0.8629338060914962    },
      {42.00627107663884,  16.139181954006176,    -0.9136240007059184    },
      {42.00753340548704,  16.135896056329383,    -0.9643021010200817    },
      {42.008863472632534, 16.132433001889424,    -1.014967438333844     },
      {42.01026120005131,  16.12879286304002,     -1.0656193444648716    },
      {42.01172650578085,  16.12497571580128,     -1.1162571517754003    },
      {42.01325930392859,  16.120981639853433,    -1.1668801931988653    },
      {42.01485950468235,  16.116810718529727,    -1.2174878022664597    },
      {42.01652701431994,  16.11246303880953,     -1.2680793131336978    },
      {42.018261735220136, 16.10793869131058,     -1.3186540606067516    },
      {42.01982885941867,  16.103850112238497,    -1.362625783897011     },
      {42.02082428824698,  16.101252351010253,    -1.3897371481731526    },
      {42.02120528485336,  16.100257960936542,    -1.4000000000000004    },
    };
    const double* bs3_weights_cur1 = nullptr;
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 1065;
    const double bs3_knots_cur1[] = {
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2637238670334754,
      -1.263215483489569,
      -1.2627071101650977,
      -1.2621987467081313,
      -1.26169039276197,
      -1.2611820479653228,
      -1.2606737119524851,
      -1.2601653843535185,
      -1.2596570647944343,
      -1.259148752897375,
      -1.2586404482808002,
      -1.258132150559672,
      -1.2576238593456424,
      -1.257115574247242,
      -1.2566072948700686,
      -1.2560990208169796,
      -1.2555907516882816,
      -1.255082487081925,
      -1.2545742265936957,
      -1.25406596981741,
      -1.2535577163451097,
      -1.2530494657672575,
      -1.252541217672933,
      -1.2520329716500294,
      -1.2515247272854506,
      -1.2510164841653086,
      -1.2505082418751217,
      -1.250000000000011,
      -1.2494917581249005,
      -1.2489835158347133,
      -1.2484752727145716,
      -1.2479670283499926,
      -1.247458782327089,
      -1.2469505342327645,
      -1.2464422836549123,
      -1.245934030182612,
      -1.2454257734063265,
      -1.2449175129180972,
      -1.2444092483117404,
      -1.2439009791830427,
      -1.2433927051299536,
      -1.2428844257527802,
      -1.2423761406543796,
      -1.2418678494403501,
      -1.241359551719222,
      -1.2408512471026472,
      -1.240342935205588,
      -1.2398346156465034,
      -1.239326288047537,
      -1.2388179520346991,
      -1.238309607238052,
      -1.237801253291891,
      -1.2372928898349242,
      -1.236784516510453,
      -1.2362761329665468,
      -1.2357677388562203,
      -1.2352593338376057,
      -1.2347509175741256,
      -1.234242489734662,
      -1.2337340499937248,
      -1.2332255980316178,
      -1.2327171335346014,
      -1.2322086561950565,
      -1.2317001657116415,
      -1.2311916617894523,
      -1.2306831441401753,
      -1.2301746124822421,
      -1.2296660665409778,
      -1.229157506048751,
      -1.2286489307451183,
      -1.2281403403769675,
      -1.2276317346986587,
      -1.2271231134721612,
      -1.2266144764671896,
      -1.2261058234613362,
      -1.225597154240201,
      -1.2250884685975187,
      -1.2245797663352826,
      -1.2240710472638676,
      -1.223562311202147,
      -1.2230535579776096,
      -1.222544787426472,
      -1.2220359993937897,
      -1.2215271937335614,
      -1.221018370308836,
      -1.2205095289918115,
      -1.2200006696639338,
      -1.2194917922159907,
      -1.2189828965482041,
      -1.2184739825703192,
      -1.2179650502016883,
      -1.2174560993713546,
      -1.2169471300181298,
      -1.2164381420906722,
      -1.2159291355475568,
      -1.2154201103573465,
      -1.214911066498658,
      -1.2144020039602246,
      -1.213892922740956,
      -1.2133838228499954,
      -1.2128747043067716,
      -1.2123655671410505,
      -1.2118564113929806,
      -1.2113472371131377,
      -1.2108380443625644,
      -1.2103288332128064,
      -1.2098196037459483,
      -1.209310356054642,
      -1.2088010902421358,
      -1.2082918064222963,
      -1.207782504719631,
      -1.207273185269305,
      -1.206763848217156,
      -1.2062544937197044,
      -1.2057451219441622,
      -1.205235733068437,
      -1.2047263272811342,
      -1.2042169047815554,
      -1.2037074657796938,
      -1.2031980104962259,
      -1.2026885391625013,
      -1.202179052020528,
      -1.2016695493229566,
      -1.2011600313330586,
      -1.2006504983247053,
      -1.2001409505823402,
      -1.199631388400951,
      -1.1991218120860376,
      -1.1986122219535762,
      -1.1981026183299834,
      -1.1975930015520746,
      -1.1970833719670204,
      -1.1965737299323014,
      -1.1960640758156584,
      -1.1955544099950417,
      -1.1950447328585554,
      -1.194535044804402,
      -1.1940253462408221,
      -1.1935156375860316,
      -1.1930059192681572,
      -1.1924961917251702,
      -1.1919864554048152,
      -1.1914767107645388,
      -1.1909669582714142,
      -1.1904571984020647,
      -1.1899474316425844,
      -1.189437658488456,
      -1.188927879444467,
      -1.1884180950246241,
      -1.1879083057520634,
      -1.1873985121589614,
      -1.186888714786442,
      -1.1863789141844807,
      -1.1858691109118094,
      -1.185359305535817,
      -1.184849498632448,
      -1.184339690786102,
      -1.1838298825895266,
      -1.1833200746437138,
      -1.18281026755779,
      -1.1823004619489075,
      -1.1817906584421323,
      -1.1812808576703313,
      -1.1807710602740582,
      -1.180261266901436,
      -1.1797514782080412,
      -1.1792416948567817,
      -1.1787319175177793,
      -1.1782221468682454,
      -1.1777123835923589,
      -1.17720262838114,
      -1.1766928819323268,
      -1.1761831449502451,
      -1.1756734181456823,
      -1.1751637022357568,
      -1.1746539979437878,
      -1.1741443059991636,
      -1.1736346271372096,
      -1.173124962099053,
      -1.17261531163149,
      -1.1721056764868498,
      -1.1715960574228588,
      -1.171086455202502,
      -1.1705768705938875,
      -1.170067304370106,
      -1.169557757309093,
      -1.1690482301934881,
      -1.1685387238104956,
      -1.1680292389517417,
      -1.167519776413135,
      -1.1670103369947236,
      -1.1665009215005526,
      -1.1659915307385218,
      -1.1654821655202416,
      -1.164972826660891,
      -1.164463514979072,
      -1.1639542312966675,
      -1.163444976438695,
      -1.1629357512331637,
      -1.1624265565109293,
      -1.1619173931055498,
      -1.16140826185314,
      -1.1608991635922268,
      -1.1603900991636054,
      -1.1598810694101926,
      -1.1593720751768846,
      -1.1588631173104103,
      -1.1583541966591868,
      -1.1578453140731773,
      -1.1573364704037439,
      -1.1568276665035062,
      -1.1563189032261958,
      -1.1558101814265143,
      -1.1553015019599888,
      -1.1547928656828306,
      -1.1542842734517913,
      -1.1537757261240222,
      -1.1532672245569318,
      -1.152758769608045,
      -1.152250362134862,
      -1.1517420029947192,
      -1.1512336930446483,
      -1.150725433141238,
      -1.1502172241404949,
      -1.149709066897707,
      -1.149200962267304,
      -1.1486929111027235,
      -1.1481849142562726,
      -1.1476769725789937,
      -1.1471690869205304,
      -1.1466612581289932,
      -1.1461534870508256,
      -1.1456457745306734,
      -1.1451381214112522,
      -1.1446305285332166,
      -1.1441229967350313,
      -1.1436155268528416,
      -1.1431081197203445,
      -1.1426007761686627,
      -1.142093497026218,
      -1.141586283118605,
      -1.1410791352684682,
      -1.140572054295377,
      -1.140065041015704,
      -1.1395580962425036,
      -1.1390512207853902,
      -1.138544415450421,
      -1.1380376810399746,
      -1.1375310183526361,
      -1.137024428183079,
      -1.1365179113219508,
      -1.1360114685557579,
      -1.1355051006667534,
      -1.134998808432824,
      -1.1344925926273801,
      -1.1339864540192446,
      -1.1334803933725457,
      -1.132974411446608,
      -1.1324685089958466,
      -1.131962686769662,
      -1.1314569455123356,
      -1.1309512859629267,
      -1.1304457088551716,
      -1.1299402149173814,
      -1.1294348048723442,
      -1.1289294794372262,
      -1.1284242393234747,
      -1.1279190852367218,
      -1.1274140178766916,
      -1.1269090379371045,
      -1.126404146105587,
      -1.1258993430635795,
      -1.1253946294862482,
      -1.1248900060423948,
      -1.1243854733943708,
      -1.1238810321979904,
      -1.1233766831024476,
      -1.1228724267502308,
      -1.122368263777042,
      -1.121864194811715,
      -1.1213602204761364,
      -1.1208563413851667,
      -1.1203525581465643,
      -1.1198488713609076,
      -1.1193452816215224,
      -1.1188417895144072,
      -1.1183383956181623,
      -1.1178351005039173,
      -1.117331904735264,
      -1.1168288088681848,
      -1.1163258134509895,
      -1.115822919024246,
      -1.1153201261207182,
      -1.1148174352653013,
      -1.114314846974961,
      -1.1138123617586717,
      -1.1133099801173576,
      -1.1128077025438337,
      -1.1123055295227502,
      -1.1118034615305354,
      -1.111301499035342,
      -1.1107996424969933,
      -1.1102978923669309,
      -1.1097962490881652,
      -1.1092947130952246,
      -1.1087932848141078,
      -1.1082919646622353,
      -1.1077907530484064,
      -1.107289650372751,
      -1.1067886570266885,
      -1.106287773392885,
      -1.1057869998452117,
      -1.1052863367487054,
      -1.1047857844595292,
      -1.1042853433249369,
      -1.1037850136832337,
      -1.1032847958637435,
      -1.102784690186774,
      -1.1022846969635838,
      -1.1017848164963508,
      -1.101285049078142,
      -1.1007853949928839,
      -1.1002858545153342,
      -1.0997864279110552,
      -1.0992871154363872,
      -1.098787917338424,
      -1.0982888338549899,
      -1.0977898652146156,
      -1.0972910116365182,
      -1.0967922733305804,
      -1.0962936504973309,
      -1.095795143327926,
      -1.0952967520041341,
      -1.0947984766983174,
      -1.0943003175734185,
      -1.0938022747829466,
      -1.0933043484709637,
      -1.0928065387720736,
      -1.0923088458114107,
      -1.0918112697046307,
      -1.091313810557902,
      -1.0908164684678978,
      -1.090319243521789,
      -1.0898221357972397,
      -1.089325145362402,
      -1.0888282722759126,
      -1.0883315165868892,
      -1.0878348783349305,
      -1.0873383575501148,
      -1.0868419542529995,
      -1.0863456684546235,
      -1.0858495001565096,
      -1.0853534493506658,
      -1.084857516019592,
      -1.0843617001362829,
      -1.0838660016642352,
      -1.0833704205574541,
      -1.082874956760461,
      -1.0823796102083023,
      -1.081884380826559,
      -1.0813892685313573,
      -1.0808942732293796,
      -1.0803993948178774,
      -1.0799046331846833,
      -1.0794099882082269,
      -1.0789154597575468,
      -1.0784210476923093,
      -1.077926751862823,
      -1.0774325721100564,
      -1.0769385082656568,
      -1.0764445601519683,
      -1.0759507275820528,
      -1.0754570103597092,
      -1.0749634082794959,
      -1.0744699211267528,
      -1.0739765486776236,
      -1.0734832906990808,
      -1.072990146948949,
      -1.0724971171759305,
      -1.072004201119632,
      -1.0715113985105906,
      -1.0710187090703018,
      -1.0705261325112478,
      -1.0700336685369256,
      -1.0695413168418781,
      -1.069049077111724,
      -1.0685569490231879,
      -1.068064932244134,
      -1.067573026433597,
      -1.0670812312418163,
      -1.0665895463102697,
      -1.0660979712717076,
      -1.0656065057501884,
      -1.0651151493611153,
      -1.064623901711271,
      -1.0641327623988568,
      -1.063641731013529,
      -1.0631508071364386,
      -1.0626599903402698,
      -1.0621692801892793,
      -1.061678676239337,
      -1.0611881780379682,
      -1.0606977851243926,
      -1.060207497029569,
      -1.059717313276236,
      -1.0592272333789574,
      -1.058737256844164,
      -1.0582473831701995,
      -1.057757611847365,
      -1.057267942357965,
      -1.056778374176353,
      -1.0562889067689787,
      -1.0557995395944348,
      -1.0553102721035053,
      -1.0548211037392137,
      -1.0543320339368714,
      -1.0538430621241273,
      -1.0533541877210184,
      -1.0528654101400188,
      -1.0523767287860917,
      -1.0518881430567404,
      -1.05139965234206,
      -1.0509112560247895,
      -1.0504229534803662,
      -1.0499347440769766,
      -1.0494466271756122,
      -1.0489586021301225,
      -1.0484706682872704,
      -1.0479828249867866,
      -1.047495071561426,
      -1.047007407337023,
      -1.0465198316325488,
      -1.0460323437601675,
      -1.0455449430252932,
      -1.0450576287266489,
      -1.0445704001563232,
      -1.0440832565998306,
      -1.043596197336168,
      -1.0431092216378768,
      -1.0426223287711003,
      -1.0421355179956453,
      -1.0416487885650416,
      -1.041162139726604,
      -1.0406755707214925,
      -1.0401890807847742,
      -1.0397026691454858,
      -1.0392163350266952,
      -1.0387300776455644,
      -1.038243896213413,
      -1.037757789935781,
      -1.0372717580124928,
      -1.036785799637721,
      -1.036299914000051,
      -1.0358141002825458,
      -1.0353283576628103,
      -1.0348426853130577,
      -1.0343570824001738,
      -1.0338715480857847,
      -1.0333860815263214,
      -1.0329006818730866,
      -1.0324153482723226,
      -1.0319300798652773,
      -1.0314448757882715,
      -1.0309597351727677,
      -1.0304746571454368,
      -1.0299896408282272,
      -1.029504685338432,
      -1.0290197897887594,
      -1.0285349532874006,
      -1.0280501749380988,
      -1.0275654538402192,
      -1.0270807890888192,
      -1.0265961797747165,
      -1.0261116249845617,
      -1.0256271238009065,
      -1.0251426753022754,
      -1.0246582785632368,
      -1.024173932654473,
      -1.0236896366428525,
      -1.023205389591501,
      -1.0227211905598725,
      -1.0222370386038222,
      -1.0217529327756778,
      -1.0212688721243124,
      -1.020784855695216,
      -1.0203008825305684,
      -1.019816951669313,
      -1.019333062147228,
      -1.0188492129970008,
      -1.018365403248301,
      -1.0178816319278532,
      -1.0173978980595115,
      -1.0169142006643326,
      -1.01643053876065,
      -1.0159469113641477,
      -1.0154633174879348,
      -1.0149797561426197,
      -1.0144962263363835,
      -1.0140127270750565,
      -1.0135292573621912,
      -1.0130458161991382,
      -1.0125624025851196,
      -1.0120790155173063,
      -1.0115956539908908,
      -1.011112316999164,
      -1.0106290035335896,
      -1.0101457125838804,
      -1.0096624431380727,
      -1.009179194182603,
      -1.0086959647023825,
      -1.0082127536808745,
      -1.0077295601001683,
      -1.0072463829410565,
      -1.0067632211831103,
      -1.006280073804756,
      -1.00579693978335,
      -1.0053138180952568,
      -1.004830707715923,
      -1.0043476076199562,
      -1.0038645167811981,
      -1.0033814341728033,
      -1.0028983587673146,
      -1.0024152895367395,
      -1.001932225452627,
      -1.0014491654861435,
      -1.0009661086081492,
      -1.0004830537892753,
      -1,
      -1,
      -1,
      -0.9995169462107246,
      -0.9990338913918508,
      -0.9985508345138566,
      -0.9980677745473732,
      -0.9975847104632605,
      -0.9971016412326855,
      -0.9966185658271968,
      -0.996135483218802,
      -0.9956523923800438,
      -0.9951692922840768,
      -0.9946861819047434,
      -0.9942030602166503,
      -0.9937199261952444,
      -0.9932367788168898,
      -0.9927536170589436,
      -0.9922704398998318,
      -0.9917872463191257,
      -0.9913040352976176,
      -0.9908208058173973,
      -0.9903375568619276,
      -0.9898542874161199,
      -0.9893709964664107,
      -0.9888876830008364,
      -0.9884043460091095,
      -0.9879209844826939,
      -0.9874375974148807,
      -0.9869541838008621,
      -0.9864707426378089,
      -0.9859872729249438,
      -0.9855037736636169,
      -0.985020243857381,
      -0.9845366825120655,
      -0.9840530886358527,
      -0.9835694612393505,
      -0.983085799335668,
      -0.9826021019404891,
      -0.9821183680721474,
      -0.9816345967516996,
      -0.9811507870029998,
      -0.9806669378527728,
      -0.9801830483306877,
      -0.9796991174694323,
      -0.9792151443047848,
      -0.9787311278756885,
      -0.9782470672243231,
      -0.9777629613961787,
      -0.9772788094401285,
      -0.9767946104085,
      -0.9763103633571485,
      -0.975826067345528,
      -0.9753417214367642,
      -0.9748573246977257,
      -0.9743728761990947,
      -0.9738883750154396,
      -0.9734038202252845,
      -0.972919210911182,
      -0.972434546159782,
      -0.9719498250619026,
      -0.9714650467126007,
      -0.9709802102112418,
      -0.9704953146615694,
      -0.9700103591717743,
      -0.9695253428545645,
      -0.9690402648272335,
      -0.9685551242117297,
      -0.968069920134724,
      -0.9675846517276787,
      -0.9670993181269146,
      -0.9666139184736801,
      -0.9661284519142167,
      -0.9656429175998277,
      -0.965157314686944,
      -0.9646716423371912,
      -0.9641858997174557,
      -0.9637000859999505,
      -0.9632142003622806,
      -0.9627282419875087,
      -0.9622422100642206,
      -0.9617561037865887,
      -0.9612699223544374,
      -0.9607836649733067,
      -0.9602973308545159,
      -0.9598109192152274,
      -0.9593244292785092,
      -0.9588378602733977,
      -0.95835121143496,
      -0.9578644820043565,
      -0.9573776712289015,
      -0.9568907783621251,
      -0.9564038026638337,
      -0.9559167434001713,
      -0.9554295998436786,
      -0.9549423712733532,
      -0.9544550569747089,
      -0.9539676562398347,
      -0.9534801683674532,
      -0.952992592662979,
      -0.9525049284385761,
      -0.9520171750132156,
      -0.9515293317127317,
      -0.9510413978698794,
      -0.9505533728243898,
      -0.9500652559230255,
      -0.949577046519636,
      -0.9490887439752126,
      -0.9486003476579423,
      -0.9481118569432618,
      -0.9476232712139104,
      -0.9471345898599832,
      -0.9466458122789836,
      -0.9461569378758747,
      -0.945667966063131,
      -0.9451788962607887,
      -0.9446897278964969,
      -0.9442004604055675,
      -0.9437110932310236,
      -0.9432216258236492,
      -0.9427320576420372,
      -0.9422423881526371,
      -0.9417526168298027,
      -0.9412627431558384,
      -0.9407727666210449,
      -0.9402826867237661,
      -0.9397925029704334,
      -0.9393022148756097,
      -0.9388118219620343,
      -0.9383213237606652,
      -0.9378307198107233,
      -0.9373400096597326,
      -0.9368491928635637,
      -0.9363582689864736,
      -0.9358672376011458,
      -0.9353760982887316,
      -0.9348848506388874,
      -0.9343934942498143,
      -0.9339020287282951,
      -0.9334104536897331,
      -0.9329187687581865,
      -0.9324269735664059,
      -0.931935067755869,
      -0.9314430509768148,
      -0.9309509228882789,
      -0.9304586831581246,
      -0.9299663314630774,
      -0.9294738674887552,
      -0.9289812909297009,
      -0.9284886014894124,
      -0.9279957988803711,
      -0.9275028828240727,
      -0.927009853051054,
      -0.9265167093009222,
      -0.9260234513223794,
      -0.9255300788732505,
      -0.9250365917205073,
      -0.924542989640294,
      -0.9240492724179504,
      -0.9235554398480349,
      -0.9230614917343466,
      -0.9225674278899468,
      -0.9220732481371804,
      -0.921578952307694,
      -0.9210845402424567,
      -0.9205900117917767,
      -0.9200953668153199,
      -0.9196006051821259,
      -0.9191057267706236,
      -0.9186107314686459,
      -0.9181156191734441,
      -0.9176203897917009,
      -0.9171250432395422,
      -0.9166295794425492,
      -0.9161339983357683,
      -0.9156382998637205,
      -0.9151424839804115,
      -0.9146465506493376,
      -0.914150499843494,
      -0.9136543315453797,
      -0.9131580457470039,
      -0.9126616424498887,
      -0.9121651216650729,
      -0.9116684834131144,
      -0.9111717277240909,
      -0.9106748546376014,
      -0.9101778642027638,
      -0.9096807564782147,
      -0.9091835315321057,
      -0.9086861894421016,
      -0.908188730295373,
      -0.9076911541885931,
      -0.9071934612279303,
      -0.9066956515290401,
      -0.9061977252170572,
      -0.9056996824265854,
      -0.9052015233016867,
      -0.9047032479958698,
      -0.9042048566720777,
      -0.903706349502673,
      -0.9032077266694234,
      -0.9027089883634857,
      -0.9022101347853883,
      -0.901711166145014,
      -0.9012120826615798,
      -0.9007128845636169,
      -0.9002135720889488,
      -0.8997141454846695,
      -0.89921460500712,
      -0.8987149509218619,
      -0.8982151835036531,
      -0.8977153030364201,
      -0.8972153098132298,
      -0.8967152041362603,
      -0.8962149863167703,
      -0.8957146566750671,
      -0.8952142155404745,
      -0.8947136632512985,
      -0.8942130001547922,
      -0.8937122266071189,
      -0.8932113429733154,
      -0.892710349627253,
      -0.8922092469515978,
      -0.8917080353377687,
      -0.8912067151858964,
      -0.8907052869047793,
      -0.8902037509118389,
      -0.8897021076330733,
      -0.8892003575030111,
      -0.8886985009646621,
      -0.8881965384694687,
      -0.8876944704772539,
      -0.8871922974561705,
      -0.8866900198826467,
      -0.8861876382413324,
      -0.8856851530250431,
      -0.8851825647347029,
      -0.8846798738792863,
      -0.8841770809757583,
      -0.8836741865490149,
      -0.8831711911318194,
      -0.8826680952647404,
      -0.882164899496087,
      -0.8816616043818422,
      -0.8811582104855971,
      -0.8806547183784821,
      -0.8801511286390968,
      -0.87964744185344,
      -0.8791436586148375,
      -0.878639779523868,
      -0.8781358051882894,
      -0.8776317362229623,
      -0.8771275732497734,
      -0.8766233168975566,
      -0.8761189678020138,
      -0.8756145266056338,
      -0.8751099939576095,
      -0.874605370513756,
      -0.8741006569364247,
      -0.8735958538944175,
      -0.8730909620628999,
      -0.8725859821233128,
      -0.8720809147632825,
      -0.8715757606765299,
      -0.8710705205627782,
      -0.8705651951276603,
      -0.8700597850826232,
      -0.869554291144833,
      -0.8690487140370778,
      -0.8685430544876691,
      -0.8680373132303425,
      -0.8675314910041578,
      -0.8670255885533966,
      -0.8665196066274589,
      -0.8660135459807601,
      -0.8655074073726247,
      -0.8650011915671807,
      -0.8644948993332515,
      -0.863988531444247,
      -0.8634820886780541,
      -0.8629755718169259,
      -0.8624689816473688,
      -0.8619623189600303,
      -0.861455584549584,
      -0.8609487792146147,
      -0.8604419037575016,
      -0.8599349589843011,
      -0.8594279457046282,
      -0.858920864731537,
      -0.8584137168814001,
      -0.8579065029737873,
      -0.8573992238313426,
      -0.8568918802796609,
      -0.8563844731471637,
      -0.855877003264974,
      -0.8553694714667889,
      -0.8548618785887534,
      -0.8543542254693319,
      -0.8538465129491798,
      -0.8533387418710123,
      -0.8528309130794749,
      -0.8523230274210117,
      -0.8518150857437329,
      -0.8513070888972819,
      -0.8507990377327013,
      -0.8502909331022985,
      -0.8497827758595102,
      -0.8492745668587675,
      -0.848766306955357,
      -0.848257997005286,
      -0.8477496378651432,
      -0.8472412303919603,
      -0.8467327754430735,
      -0.8462242738759831,
      -0.8457157265482141,
      -0.845207134317175,
      -0.8446984980400166,
      -0.8441898185734912,
      -0.8436810967738096,
      -0.8431723334964993,
      -0.8426635295962615,
      -0.8421546859268282,
      -0.8416458033408185,
      -0.8411368826895953,
      -0.8406279248231209,
      -0.8401189305898128,
      -0.8396099008364003,
      -0.8391008364077788,
      -0.8385917381468658,
      -0.8380826068944558,
      -0.8375734434890764,
      -0.8370642487668422,
      -0.8365550235613108,
      -0.8360457687033384,
      -0.8355364850209335,
      -0.8350271733391147,
      -0.834517834479764,
      -0.834008469261484,
      -0.8334990784994529,
      -0.832989663005282,
      -0.8324802235868707,
      -0.8319707610482641,
      -0.8314612761895102,
      -0.8309517698065173,
      -0.8304422426909126,
      -0.8299326956298997,
      -0.8294231294061184,
      -0.8289135447975038,
      -0.8284039425771472,
      -0.8278943235131561,
      -0.8273846883685161,
      -0.8268750379009532,
      -0.8263653728627964,
      -0.8258556940008421,
      -0.8253460020562182,
      -0.8248362977642493,
      -0.8243265818543236,
      -0.8238168550497608,
      -0.8233071180676792,
      -0.8227973716188659,
      -0.8222876164076474,
      -0.8217778531317607,
      -0.8212680824822268,
      -0.8207583051432246,
      -0.8202485217919652,
      -0.81973873309857,
      -0.819228939725948,
      -0.8187191423296749,
      -0.8182093415578741,
      -0.817699538051099,
      -0.8171897324422164,
      -0.8166799253562925,
      -0.8161701174104797,
      -0.8156603092139045,
      -0.8151505013675583,
      -0.8146406944641894,
      -0.814130889088197,
      -0.8136210858155256,
      -0.8131112852135645,
      -0.8126014878410448,
      -0.8120916942479429,
      -0.8115819049753823,
      -0.8110721205555393,
      -0.8105623415115505,
      -0.810052568357422,
      -0.8095428015979418,
      -0.8090330417285925,
      -0.8085232892354679,
      -0.8080135445951913,
      -0.8075038082748364,
      -0.8069940807318494,
      -0.8064843624139753,
      -0.8059746537591846,
      -0.8054649551956045,
      -0.8049552671414513,
      -0.8044455900049652,
      -0.8039359241843484,
      -0.8034262700677054,
      -0.8029166280329864,
      -0.8024069984479323,
      -0.8018973816700234,
      -0.8013877780464308,
      -0.8008781879139694,
      -0.8003686115990557,
      -0.7998590494176667,
      -0.7993495016753017,
      -0.7988399686669483,
      -0.7983304506770504,
      -0.797820947979479,
      -0.7973114608375058,
      -0.7968019895037811,
      -0.7962925342203132,
      -0.7957830952184517,
      -0.7952736727188732,
      -0.7947642669315705,
      -0.7942548780558452,
      -0.7937455062803028,
      -0.7932361517828512,
      -0.7927268147307023,
      -0.7922174952803765,
      -0.7917081935777112,
      -0.7911989097578718,
      -0.7906896439453653,
      -0.7901803962540592,
      -0.789671166787201,
      -0.7891619556374432,
      -0.7886527628868697,
      -0.7881435886070268,
      -0.7876344328589572,
      -0.787125295693236,
      -0.7866161771500123,
      -0.7861070772590516,
      -0.785597996039783,
      -0.7850889335013497,
      -0.784579889642661,
      -0.7840708644524509,
      -0.7835618579093355,
      -0.7830528699818778,
      -0.7825439006286532,
      -0.7820349497983194,
      -0.7815260174296886,
      -0.7810171034518038,
      -0.7805082077840174,
      -0.7799993303360742,
      -0.7794904710081964,
      -0.7789816296911719,
      -0.7784728062664465,
      -0.7779640006062182,
      -0.7774552125735357,
      -0.7769464420223984,
      -0.776437688797861,
      -0.7759289527361404,
      -0.7754202336647251,
      -0.7749115314024893,
      -0.7744028457598069,
      -0.7738941765386719,
      -0.7733855235328185,
      -0.7728768865278469,
      -0.7723682653013495,
      -0.7718596596230407,
      -0.77135106925489,
      -0.7708424939512573,
      -0.7703339334590306,
      -0.7698253875177663,
      -0.769316855859833,
      -0.768808338210556,
      -0.7682998342883669,
      -0.7677913438049521,
      -0.767282866465407,
      -0.7667744019683909,
      -0.7662659500062837,
      -0.7657575102653468,
      -0.7652490824258834,
      -0.7647406661624033,
      -0.7642322611437886,
      -0.7637238670334621,
      -0.7632154834895559,
      -0.7627071101650846,
      -0.762198746708118,
      -0.7616903927619568,
      -0.7611820479653099,
      -0.760673711952472,
      -0.7601653843535056,
      -0.7596570647944214,
      -0.7591487528973621,
      -0.7586404482807872,
      -0.7581321505596591,
      -0.7576238593456295,
      -0.7571155742472289,
      -0.7566072948700557,
      -0.7560990208169666,
      -0.755590751688269,
      -0.7550824870819124,
      -0.7545742265936829,
      -0.7540659698173973,
      -0.7535577163450972,
      -0.7530494657672451,
      -0.7525412176729205,
      -0.752032971650017,
      -0.7515247272854383,
      -0.7510164841652964,
      -0.7505082418751094,
      -0.7499999999999987,
      -0.7494917581248881,
      -0.7489835158347011,
      -0.7484752727145593,
      -0.7479670283499804,
      -0.7474587823270769,
      -0.7469505342327525,
      -0.7464422836549004,
      -0.7459340301826002,
      -0.7454257734063144,
      -0.7449175129180852,
      -0.7444092483117286,
      -0.7439009791830309,
      -0.7433927051299417,
      -0.7428844257527685,
      -0.742376140654368,
      -0.7418678494403385,
      -0.7413595517192103,
      -0.7408512471026354,
      -0.7403429352055761,
      -0.7398346156464919,
      -0.7393262880475254,
      -0.7388179520346876,
      -0.7383096072380406,
      -0.7378012532918794,
      -0.7372928898349128,
      -0.7367845165104416,
      -0.7362761329665353,
      -0.7359664050174322,
      -0.7359664050174322,
      -0.7359664050174322,
      -0.7359664050174322,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    SPAposition c_base_center_surf1_cur1(37, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur1(1, 0, 0);
    SPAvector c_base_major_surf1_cur1(0, 0, -17.5);
    double c_base_ratio_surf1_cur1 = 1;
    ellipse c_base_surf1_cur1(c_base_center_surf1_cur1, c_base_normal_surf1_cur1, c_base_major_surf1_cur1, c_base_ratio_surf1_cur1);
    cone c_surf1_cur1(c_base_surf1_cur1, -0.25766265056033233, 0.9662349396012463);
    c_surf1_cur1.u_param_scale = 17.5;
    bs2_curve bs2_pcurve1_cur1 = nullptr;
    SPAposition c_base_center_surf2_cur1(0, 0, 7);
    SPAunit_vector c_base_normal_surf2_cur1(0, 0, 1);
    SPAvector c_base_major_surf2_cur1(45, 0, 0);
    double c_base_ratio_surf2_cur1 = 1;
    ellipse c_base_surf2_cur1(c_base_center_surf2_cur1, c_base_normal_surf2_cur1, c_base_major_surf2_cur1, c_base_ratio_surf2_cur1);
    cone c_surf2_cur1(c_base_surf2_cur1, 0, 1);
    c_surf2_cur1.u_param_scale = 45;
    bs2_curve bs2_pcurve2_cur1 = nullptr;
    intcurve ic_cur1(bs3_cur1, 1e-06, c_surf1_cur1, c_surf2_cur1, bs2_pcurve1_cur1, bs2_pcurve2_cur1);

    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 1061;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {42.021205284853366, -16.100257960936542,   -1.4000000000000072    },
      {42.020824288246985, -16.101252351010253,   -1.389737148173157     },
      {42.019828859418666, -16.103850112238494,   -1.3626257838970222    },
      {42.01826173522012,  -16.10793869131058,    -1.3186540606067514    },
      {42.016527014319934, -16.112463038809523,   -1.2680793131337111    },
      {42.014859504682356, -16.11681071852973,    -1.2174878022664657    },
      {42.01325930392859,  -16.12098163985343,    -1.1668801931988624    },
      {42.01172650578086,  -16.124975715801277,   -1.116257151775407     },
      {42.0102612000513,   -16.128792863040022,   -1.0656193444648818    },
      {42.008863472632534, -16.132433001889428,   -1.0149674383338483    },
      {42.00753340548704,  -16.13589605632938,    -0.9643021010200861    },
      {42.00627107663884,  -16.139181954006173,   -0.9136240007059222    },
      {42.0050765601639,   -16.14229062623894,    -0.8629338060915086    },
      {42.00394992618216,  -16.145222008025492,   -0.8122321863680017    },
      {42.0028912408494,   -16.14797603804792,    -0.7615198111906919    },
      {42.00190056634976,  -16.150552658677903,   -0.71079735065204      },
      {42.00097796088885,  -16.152951815981716,   -0.6600654752546783    },
      {42.00012347868666,  -16.15517345972484,    -0.6093248558843268    },
      {41.999337169971966, -16.157217543376355,   -0.5585761637826764    },
      {41.99861908097631,  -16.159084024112943,   -0.5078200705201893    },
      {41.99796925392866,  -16.160772862822615,   -0.4570572479688869    },
      {41.99738772705083,  -16.162284024108075,   -0.40628836827507037   },
      {41.99687453455296,  -16.163617476289822,   -0.3555141038320068    },
      {41.996429706629606, -16.16477319140888,    -0.30473512725257834   },
      {41.99605326945647,  -16.16575114522921,    -0.2539521113419028    },
      {41.99574524518717,  -16.166551317239858,   -0.2031657290699314    },
      {41.995505651950936, -16.16717369065667,    -0.15237665354399305   },
      {41.99533450385037,  -16.167618252423832,   -0.10158555798136872   },
      {41.995231810959936, -16.167884993214912,   -0.05079311568179404   },
      {41.99519757932476,  -16.16797390743376,    -2.1614654510671016e-15},
      {41.99523181095994,  -16.167884993214912,   0.05079311568178963    },
      {41.99533450385037,  -16.167618252423836,   0.10158555798136315    },
      {41.99550565195095,  -16.167173690656668,   0.1523766535439875     },
      {41.99574524518717,  -16.166551317239865,   0.20316572906992583    },
      {41.99605326945648,  -16.16575114522921,    0.25395211134189744    },
      {41.99642970662961,  -16.16477319140888,    0.3047351272525727     },
      {41.99687453455296,  -16.163617476289822,   0.3555141038320025     },
      {41.99738772705082,  -16.16228402410808,    0.40628836827506604    },
      {41.99796925392866,  -16.16077286282262,    0.4570572479688826     },
      {41.9986190809763,   -16.159084024112943,   0.5078200705201836     },
      {41.99933716997198,  -16.157217543376362,   0.558576163782671      },
      {42.000123478686646, -16.15517345972484,    0.6093248558843214     },
      {42.000977960888854, -16.152951815981712,   0.6600654752546726     },
      {42.001900566349775, -16.1505526586779,     0.7107973506520345     },
      {42.00289124084941,  -16.147976038047922,   0.7615198111906866     },
      {42.00394992618216,  -16.145222008025492,   0.8122321863679971     },
      {42.0050765601639,   -16.14229062623894,    0.8629338060915042     },
      {42.006271076638825, -16.139181954006173,   0.9136240007059176     },
      {42.007533405487045, -16.13589605632938,    0.9643021010200828     },
      {42.00886347263252,  -16.132433001889424,   1.0149674383338403     },
      {42.0102612000513,   -16.12879286304002,    1.0656193444648763     },
      {42.01172650578086,  -16.12497571580128,    1.1162571517754016     },
      {42.01325930392858,  -16.120981639853426,   1.1668801931988562     },
      {42.014859504682356, -16.116810718529734,   1.217487802266462      },
      {42.01652701431994,  -16.112463038809526,   1.268079313133707      },
      {42.01826173522012,  -16.10793869131058,    1.318654060606747      },
      {42.02006356587334,  -16.103237770281464,   1.3692113801687067     },
      {42.02193240089338,  -16.0983603735934,     1.419750608005892      },
      {42.02386813102903,  -16.093306602731932,   1.4702710810338626     },
      {42.02587064317652,  -16.088076562788242,   1.5207721369234783     },
      {42.02793982039201,  -16.08267036245018,    1.5712531141267387     },
      {42.030075541905006, -16.077088113993,      1.6217133519025975     },
      {42.03227768313157,  -16.07132993326984,    1.6721521903426004     },
      {42.034546115688414, -16.065395939701837,   1.7225689703964384     },
      {42.03688070740718,  -16.059286256267995,   1.7729630338973668     },
      {42.03928132234923,  -16.053001009494828,   1.823333723587498      },
      {42.04174782082075,  -16.046540329445566,   1.8736803831429503     },
      {42.044280059388235, -16.039904349709246,   1.9240023571989102     },
      {42.04687789089439,  -16.033093207389385,   1.9742989913744924     },
      {42.04954116447455,  -16.026107043092544,   2.0245696322975344     },
      {42.05226972557331,  -16.018946000916316,   2.0748136276291507     },
      {42.05506341596149,  -16.011610228437508,   2.1250303260882792     },
      {42.05792207375391,  -16.004099876699474,   2.1752190774759113     },
      {42.060845533426566, -15.996415100199808,   2.2253792326993476     },
      {42.06383362583561,  -15.988556056877172,   2.2755101437961245     },
      {42.06688617823522,  -15.980522908098369,   2.325611163957934      },
      {42.070003014296965, -15.97231581864474,    2.3756816475542655     },
      {42.0731839541288,   -15.963934956698683,   2.4257209501559753     },
      {42.07642881429477,  -15.955380493829548,   2.475728428558596      },
      {42.07973740783486,  -15.94665260497968,    2.525703440805605      },
      {42.08310954428555,  -15.937751468449767,   2.5756453462113362     },
      {42.08654502970015,  -15.928677265884359,   2.625553505383937      },
      {42.090043666669914, -15.919430182256875,   2.6754272802479386     },
      {42.09360525434537,  -15.910010405854532,   2.7252660340667987     },
      {42.09722958845775,  -15.90041812826286,    2.7750691314651803     },
      {42.10091646134116,  -15.890653544350196,   2.8248359384510544     },
      {42.104665661954684, -15.880716852251792,   2.8745658224376616     },
      {42.10847697590493,  -15.870608253353776,   2.9242581522652102     },
      {42.112350185468856, -15.860327952276858,   2.9739122982224595     },
      {42.11628506961721,  -15.849876156859791,   3.023527632067999      },
      {42.120281404037414, -15.839253078142717,   3.073103527051501      },
      {42.124338961157854, -15.828458930350191,   3.122639357934574      },
      {42.128457510171735, -15.817493930873983,   3.172134501011537      },
      {42.13263681706101,  -15.806358300255901,   3.221588334130019      },
      {42.13687664462152,  -15.795052262170024,   3.271000236711207      },
      {42.141176752487496, -15.783576043405077,   3.3203695897700225     },
      {42.14553689715658,  -15.771929873846503,   3.3696957759350568     },
      {42.14995683201545,  -15.760113986458233,   3.4189781794682306     },
      {42.15443630736511,  -15.748128617264426,   3.4682161862843053     },
      {42.158975070447084, -15.735974005330956,   3.517409183970184      },
      {42.163572865469106, -15.723650392746663,   3.5665565618039117     },
      {42.168229433631794, -15.711158024604561,   3.6156577107735757     },
      {42.17294451315494,  -15.698497148982717,   3.664712023595868      },
      {42.17771783930452,  -15.68566801692511,    3.713718894734519      },
      {42.18254914441931,  -15.672670882422167,   3.7626777204184583     },
      {42.18743815793863,  -15.659506002391288,   3.811587898659729      },
      {42.19238460642919,  -15.646173636657089,   3.8604488292712515     },
      {42.197388213613024, -15.632674047931598,   3.909259913884302      },
      {42.20244870039531,  -15.619007501794153,   3.9580205559657142     },
      {42.20756578489214,  -15.605174266671337,   4.0067301608350085     },
      {42.212739182459046, -15.59117461381657,    4.055388135681076      },
      {42.21796860571885,  -15.577008817289787,   4.103993889578852      },
      {42.22325376459078,  -15.562677153936718,   4.152546833505551      },
      {42.22859436631865,  -15.548179903368258,   4.201046380356812      },
      {42.23399011550009,  -15.533517347939583,   4.249491944962546      },
      {42.23944071411543,  -15.51868977272915,    4.297882944102524      },
      {42.244945861556715, -15.503697465517682,   4.346218796521827      },
      {42.2505052546573,   -15.488540716766856,   4.3944989229459015     },
      {42.256118587721055, -15.473219819598018,   4.442722746095528      },
      {42.261785552552176, -15.457735069770711,   4.490889690701438      },
      {42.267505838484695, -15.442086765661191,   4.538999183518776      },
      {42.27327913241235,  -15.426275208240664,   4.587050653341238      },
      {42.27910511881863,  -15.410300701053636,   4.635043531015038      },
      {42.28498347980688,  -15.394163550195959,   4.682977249452565      },
      {42.29091389513021,  -15.377864064293032,   4.730851243645914      },
      {42.29689604222207,  -15.361402554477568,   4.7786649506799534     },
      {42.30292959622644,  -15.34477933436764,    4.82641780974544       },
      {42.309014230028325, -15.327994720044426,   4.874109262151626      },
      {42.31514961428428,  -15.311049030029906,   4.921738751338807      },
      {42.32133541745314,  -15.293942585264531,   4.969305722890479      },
      {42.32757130582641,  -15.27667570908481,    5.016809624545413      },
      {42.333856943559454, -15.259248727200793,   5.0642499062093        },
      {42.34019199270196,  -15.241661967673519,   5.111626019966321      },
      {42.34657611322893,  -15.223915760892442,   5.158937420090369      },
      {42.35300896307187,  -15.206010439552694,   5.206183563056017      },
      {42.35949019814904,  -15.187946338632456,   5.2533639075493985     },
      {42.366019472397504, -15.16972379537005,    5.300477914478539      },
      {42.37259643780321,  -15.151343149241256,   5.347525046983812      },
      {42.37922074443277,  -15.132804741936386,   5.394504770447855      },
      {42.385892040464114, -15.1141089173374,     5.441416552505402      },
      {42.39260997221799,  -15.095256021494944,   5.488259863052794      },
      {42.39937418418873,  -15.076246402605442,   5.535034174257319      },
      {42.40618431907578,  -15.057080410988062,   5.581738960566226      },
      {42.41304001781456,  -15.037758399061701,   5.6283736987155715     },
      {42.41994091960787,  -15.018280721321979,   5.674937867738773      },
      {42.42688666195687,  -14.99864773431813,    5.721430948974959      },
      {42.43387688069226,  -14.978859796629983,   5.7678524260770505     },
      {42.44091121000562,  -14.958917268844836,   5.8142017850195895     },
      {42.44798928248019,  -14.93882051353441,    5.860478514106432      },
      {42.455110729122254, -14.918569895231709,   5.906682103978028      },
      {42.462275179392094, -14.898165780407947,   5.952812047618607      },
      {42.46948226123495,  -14.87760853744949,    5.998867840363118      },
      {42.47673160111219,  -14.856898536634663,   6.044848979903809      },
      {42.4840228240322,   -14.836036150110772,   6.090754966296709      },
      {42.49135555358119,  -14.815021751871027,   6.136585301967874      },
      {42.4987294119542,   -14.793855717731368,   6.1823394917192385     },
      {42.50614401998581,  -14.772538425307603,   6.228017042734464      },
      {42.51359899718112,  -14.751070253992216,   6.273617464584344      },
      {42.52109396174595,  -14.729451584931535,   6.319140269232185      },
      {42.528628530618015, -14.70768280100262,    6.36458497103874       },
      {42.53620231949712,  -14.685764286790418,   6.409951086767101      },
      {42.54381494287574,  -14.663696428564805,   6.455238135587268      },
      {42.55146601406941,  -14.641479614257767,   6.5004456390805165     },
      {42.55915514524702,  -14.619114233440492,   6.545573121243557      },
      {42.56688194746118,  -14.596600677300636,   6.590620108492376      },
      {42.574646030678004, -14.573939338619542,   6.635586129666103      },
      {42.58244700380762,  -14.55113061174956,    6.6804707160302765     },
      {42.5902844747337,   -14.528174892591371,   6.72527340128031       },
      {42.59815805034356,  -14.505072578571367,   6.769993721544367      },
      {42.606067336557686, -14.481824068619176,   6.814631215386329      },
      {42.614011938359646, -14.458429763145052,   6.859185423808279      },
      {42.62199145982527,  -14.434890064017557,   6.903655890253031      },
      {42.6300055041523,   -14.411205374541115,   6.948042160606234      },
      {42.6380536736895,   -14.387376099433725,   6.992343783198381      },
      {42.646135569965985, -14.36340264480472,    7.036560308806571      },
      {42.65425079372004,  -14.339285418132592,   7.080691290656125      },
      {42.662398944928256, -14.315024828242905,   7.124736284421847      },
      {42.670579622834,    -14.290621285286258,   7.168694848229325      },
      {42.67879242597649,  -14.266075200716296,   7.2125665426557095     },
      {42.687036952218676, -14.241386987267928,   7.256350930730673      },
      {42.69531279877628,  -14.216557058935432,   7.300047577936776      },
      {42.70361956224548,  -14.19158583095081,    7.343656052209971      },
      {42.71195683863124,  -14.166473719762134,   7.387175923939688      },
      {42.72032422337508,  -14.141221143012059,   7.430606765968879      },
      {42.728721311383076, -14.115828519516258,   7.473948153593669      },
      {42.73714769705309,  -14.090296269242211,   7.517199664563154      },
      {42.745602974302756, -14.064624813287798,   7.560360879078576      },
      {42.754086736596136, -14.03881457386025,    7.603431379792747      },
      {42.76259857697147,  -14.012865974254991,   7.646410751808923      },
      {42.77113808806761,  -13.986779438834692,   7.689298582679775      },
      {42.7797048621513,   -13.960555393008411,   7.7320944624059855     },
      {42.788298491143564, -13.934194263210767,   7.774797983434748      },
      {42.796918566646006, -13.907696476881348,   7.817408740658159      },
      {42.80556467996752,  -13.88106246244408,    7.859926331411235      },
      {42.81423642215009,  -13.85429264928681,    7.902350355469985      },
      {42.82293338399483,  -13.827387467740929,   7.94468041504916       },
      {42.831655156087734, -13.800347349061175,   7.9869161147998895     },
      {42.840401328825315, -13.773172725405454,   8.029057061807118      },
      {42.84917149243995,  -13.745864029814904,   8.071102865586958      },
      {42.85796523702508,  -13.718421696193904,   8.113053138083751      },
      {42.866782152560255, -13.690846159290388,   8.154907493667121      },
      {42.87562182893619,  -13.663137854676107,   8.196665549128639      },
      {42.88448385597891,  -13.635297218727152,   8.238326923678667      },
      {42.893367823474776, -13.607324688604475,   8.279891238942696      },
      {42.90227332119454,  -13.579220702234645,   8.321358118957761      },
      {42.91119993891721,  -13.550985698290619,   8.362727190168634      },
      {42.920147266454265, -13.522620116172718,   8.403998081423822      },
      {42.92911489367336,  -13.494124395989715,   8.445170423971486      },
      {42.93810241052134,  -13.465498978539998,   8.486243851455232      },
      {42.947109407048266, -13.436744305292924,   8.527217999909597      },
      {42.95613547342986,  -13.407860818370283,   8.568092507755653      },
      {42.96518019999084,  -13.378848960527858,   8.608867015796188      },
      {42.97424317722742,  -13.349709175137171,   8.64954116721099       },
      {42.98332399582983,  -13.320441906167325,   8.69011460755188       },
      {42.99242224670459,  -13.291047598166978,   8.730586984737581      },
      {43.001537520996806, -13.261526696246474,   8.770957949048494      },
      {43.010669410111774, -13.23187964606008,    8.811227153121424      },
      {43.01981750573671,  -13.202106893788397,   8.851394251944049      },
      {43.028981399862566, -13.172208886120854,   8.891458902849266      },
      {43.038160684804794, -13.142186070238424,   8.931420765509605      },
      {43.047354953224854, -13.112038893796331,   8.971279501931196      },
      {43.05656379815064,  -13.081767804907104,   9.011034776447998      },
      {43.06578681299765,  -13.05137325212354,    9.050686255715508      },
      {43.07502359158898,  -13.020855684422004,   9.090233608704711      },
      {43.08427372817577,  -12.990215551185761,   9.129676506695695      },
      {43.09353681745725,  -12.959453302188464,   9.16901462327121       },
      {43.10281245460029,  -12.92856938757782,    9.208247634310194      },
      {43.11210023525953,  -12.897564257859313,   9.247375217980988      },
      {43.12139975559621,  -12.866438363880224,   9.286397054734735      },
      {43.13071061229769,  -12.83519215681364,    9.325312827298418      },
      {43.14003240259641,  -12.80382608814265,    9.364122220667914      },
      {43.14936472428852,  -12.772340609644761,   9.402824922100958      },
      {43.1587071757525,   -12.74073617337633,    9.44142062110993       },
      {43.16805935596763,  -12.709013231657295,   9.479909009454664      },
      {43.177420864531975, -12.677172237055872,   9.51828978113498       },
      {43.18679130168039,  -12.645213642373564,   9.556562632383372      },
      {43.1961702683021,   -12.61313790063021,    9.594727261657372      },
      {43.2055573659586,   -12.580945465049206,   9.632783369631895      },
      {43.2149521969004,   -12.548636789042913,   9.670730659191662      },
      {43.22435436408459,  -12.516212326198135,   9.708568835423208      },
      {43.23376347119152,  -12.483672530261831,   9.746297605607168      },
      {43.24317912264148,  -12.451017855126876,   9.783916679210174      },
      {43.25260092361122,  -12.41824875481807,    9.821425767876876      },
      {43.26202848005022,  -12.385365683478213,   9.858824585421788      },
      {43.27146139869664,  -12.35236909535436,    9.896112847821101      },
      {43.28089928709336,  -12.319259444784262,   9.933290273204367      },
      {43.29034175360338,  -12.286037186182838,   9.970356581846204      },
      {43.29978840742557,  -12.25270277402894,    10.007311496157774     },
      {43.30923885860956,  -12.21925666285216,    10.044154740678412     },
      {43.31869271807108,  -12.185699307219817,   10.080886042066936     },
      {43.3281495976066,   -12.152031161724107,   10.117505129093118     },
      {43.33760910990791,  -12.118252680969377,   10.15401173262898      },
      {43.347070868576836, -12.08436431955952,    10.190405585639903     },
      {43.356534488139104, -12.050366532085626,   10.22668642317605      },
      {43.36599958405863,  -12.016259773113607,   10.262853982363234     },
      {43.37546577275117,  -11.98204449717214,    10.298908002394196     },
      {43.384932671598,    -11.947721158740638,   10.334848224519451     },
      {43.39439989895946,  -11.913290212237426,   10.37067439203836      },
      {43.403867074187865, -11.878752112008014,   10.406386250289973     },
      {43.413333817640975, -11.844107312313596,   10.44198354664387      },
      {43.42279975069442,  -11.809356267319583,   10.47746603049101      },
      {43.432264495754644, -11.774499431084394,   10.512833453234443     },
      {43.44172767627117,  -11.73953725754827,    10.548085568280014     },
      {43.45118891674889,  -11.70447020052241,    10.5832221310271       },
      {43.46064784276018,  -11.669298713677994,   10.618242898859105     },
      {43.47010408095683,  -11.634023250535625,   10.653147631134122     },
      {43.47955725908151,  -11.598644264454704,   10.687936089175466     },
      {43.4890070059795,   -11.563162208623048,   10.722608036262118     },
      {43.498452951609806, -11.527577536046646,   10.757163237619272     },
      {43.507894727056524, -11.491890699539518,   10.791601460408641     },
      {43.51733196453941,  -11.456102151713736,   10.82592247371898      },
      {43.52676429742514,  -11.420212344969613,   10.860126048556317     },
      {43.53619136023738,  -11.384221731485958,   10.894211957834372     },
      {43.5456127886674,   -11.34813076321056,    10.928179976364824     },
      {43.55502821958441,  -11.311939891850754,   10.962029880847528     },
      {43.56443729104531,  -11.27564956886414,    10.995761449860861     },
      {43.57383964230473,  -11.239260245449419,   11.029374463851802     },
      {43.58323491382479,  -11.202772372537448,   11.062868705126235     },
      {43.59262274728418,  -11.166186400782301,   11.096243957839091     },
      {43.60200278558807,  -11.129502780552585,   11.129500007984369     },
      {43.611374672876764, -11.092721961922843,   11.162636643385522     },
      {43.62073805453507,  -11.055844394665051,   11.195653653685202     },
      {43.6300925772007,   -11.018870528240353,   11.228550830335754     },
      {43.63943788877336,  -10.981800811790821,   11.26132796658888      },
      {43.64877363842282,  -10.94463569413144,    11.293984857486029     },
      {43.65809947659751,  -10.907375623742139,   11.326521299848222     },
      {43.667415055032514, -10.870021048760044,   11.358937092266185     },
      {43.67672002675767,  -10.832572416971773,   11.391232035090287     },
      {43.68601404610516,  -10.795030175805952,   11.423405930420621     },
      {43.69529676871743,  -10.757394772325785,   11.455458582096972     },
      {43.70456785155447,  -10.719666653221783,   11.487389795688758     },
      {43.713826952901414, -10.681846264804648,   11.519199378485082     },
      {43.72307373237544,  -10.643934052998247,   11.550887139484633     },
      {43.73230785093291,  -10.605930463332719,   11.582452889385728     },
      {43.741528970876246, -10.567835940937737,   11.613896440576223     },
      {43.75073675586078,  -10.529650930535865,   11.645217607123486     },
      {43.75993087090109,  -10.49137587643605,    11.676416204764362     },
      {43.769110982377434, -10.453011222527264,   11.707492050895159     },
      {43.77827675804231,  -10.414557412272208,   11.738444964561566     },
      {43.78742786702632,  -10.376014888701206,   11.769274766448603     },
      {43.79656397984408,  -10.337384094406215,   11.79998127887071      },
      {43.80568476840038,  -10.298665471534871,   11.830564325761495     },
      {43.81478990599556,  -10.259859461784803,   11.86102373266395      },
      {43.823879067331234, -10.220966506397898,   11.891359326720218     },
      {43.832951928515634, -10.181987046154884,   11.921570936661775     },
      {43.84200816706894,  -10.142921521369791,   11.95165839279922      },
      {43.85104746192835,  -10.103770371884783,   11.981621527012459     },
      {43.86006949345312,  -10.064534037064892,   12.011460172740591     },
      {43.86907394342947,  -10.025212955793027,   12.041174164971988     },
      {43.87806049507515,  -9.985807566464995,    12.070763340234329     },
      {43.887028833044376, -9.946318306984693,    12.100227536584612     },
      {43.89597864343194,  -9.906745614759375,    12.129566593599224     },
      {43.90490961377783,  -9.867089926695087,    12.158780352364028     },
      {43.91382143307122,  -9.827351679192168,    12.18786865546446      },
      {43.922713791754845, -9.787531308140846,    12.216831346975562     },
      {43.93158638172877,  -9.747629248917045,    12.245668272452185     },
      {43.94043889635419,  -9.707645936378153,    12.274379278919088     },
      {43.94927103045748,  -9.667581804859056,    12.30296421486106      },
      {43.958082480333374, -9.627437288168135,    12.331422930213174     },
      {43.966872943748854, -9.587212819583485,    12.35975527635086      },
      {43.97564211994627,  -9.546908831849185,    12.387961106080237     },
      {43.984389709646756, -9.506525757171687,    12.416040273628266     },
      {43.993115415053126, -9.466064027216298,    12.443992634633059     },
      {44.00181893985345,  -9.425524073103793,    12.471818046134082     },
      {44.01049998922324,  -9.38490632540711,     12.499516366562561     },
      {44.019158269829,    -9.34421121414814,     12.527087455731667     },
      {44.0277934898304,   -9.303439168794679,    12.554531174827034     },
      {44.0364053588831,   -9.262590618257374,    12.58184738639698      },
      {44.044993588141395, -9.22166599088688,     12.609035954342975     },
      {44.053557890260294, -9.18066571447106,     12.636096743910084     },
      {44.06209797939799,  -9.139590216232268,    12.663029621677385     },
      {44.0706135712181,   -9.098439922824783,    12.689834455548471     },
      {44.079104382891735, -9.057215260332313,    12.716511114741932     },
      {44.087570133099355, -9.015916654265563,    12.743059469781937     },
      {44.09601054203287,  -8.974544529559973,    12.769479392488758     },
      {44.104425331397394, -8.933099310573477,    12.795770755969388     },
      {44.11281422441284,  -8.891581421084396,    12.821933434608201     },
      {44.121176945815705, -8.849991284289448,    12.847967304057542     },
      {44.12951322186048,  -8.808329322801756,    12.87387224122849      },
      {44.1378227803212,   -8.766595958649068,    12.899648124281518     },
      {44.14610535049271,  -8.724791613271995,    12.92529483261733      },
      {44.15436066319201,  -8.682916707522327,    12.950812246867564     },
      {44.16258845075933,  -8.64097166166151,     12.97620024888568      },
      {44.170788447059294, -8.59895689535914,     13.001458721737793     },
      {44.17896038748202,  -8.556872827691583,    13.026587549693598     },
      {44.187104008943905, -8.514719877140669,    13.051586618217224     },
      {44.19521904988862,  -8.472498461592476,    13.0764558139583       },
      {44.20330525028768,  -8.430208998336187,    13.101195024742873     },
      {44.211362351641455, -8.38785190406309,     13.12580413956452      },
      {44.21939009697949,  -8.34542759486553,     13.150283048575329     },
      {44.22738823086125,  -8.302936486236128,    13.174631643077152     },
      {44.23535649937646,  -8.260378993066887,    13.198849815512563     },
      {44.24329465014573,  -8.217755529648574,    13.222937459456277     },
      {44.251202432320476, -8.17506650967,        13.246894469606199     },
      {44.259079596583824, -8.132312346217518,    13.270720741774722     },
      {44.266925895149996, -8.08949345177452,     13.294416172880174     },
      {44.27474108176517,  -8.04661023822105,     13.317980660937948     },
      {44.28252491170717,  -8.003663116833497,    13.341414105052074     },
      {44.29027714178548,  -7.9606524982843325,   13.364716405406558     },
      {44.297997530341235, -7.917578792641942,    13.387887463256865     },
      {44.305685837247125, -7.874442409370559,    13.410927180921457     },
      {44.31334182390721,  -7.831243757330229,    13.433835461773302     },
      {44.320965253256475, -7.787983244776863,    13.45661221023152      },
      {44.328555889760935, -7.744661279362392,    13.479257331752965     },
      {44.336113499416655, -7.701278268134954,    13.501770732824022     },
      {44.343637849750095, -7.657834617539171,    13.52415232095212      },
      {44.351128709816834, -7.6143307334164865,   13.546402004657757     },
      {44.358585850201834, -7.570767021005621,    13.56851969346606      },
      {44.36600904301802,  -7.5271438849429995,   13.590505297898876     },
      {44.373398061906414, -7.483461729263364,    13.61235872946649      },
      {44.380752682035045, -7.439720957400365,    13.63407990065965      },
      {44.38807268009811,  -7.395921972187245,    13.655668724941542     },
      {44.395357834315575, -7.352065175857632,    13.677125116739845     },
      {44.40260792443209,  -7.3081509700463325,   13.698448991438763     },
      {44.40982273171606,  -7.264179755790232,    13.719640265371165     },
      {44.41700203895888,  -7.220151933529253,    13.740698855810844     },
      {44.424145630474015, -7.176067903107366,    13.761624680964523     },
      {44.43125329209566,  -7.131928063773673,    13.782417659964393     },
      {44.43832481117818,  -7.087732814183555,    13.803077712860148     },
      {44.44535997659452,  -7.0434825523998805,   13.823604760611586     },
      {44.45235857873551,  -6.999177675894245,    13.843998725080784     },
      {44.45932040950834,  -6.954818581548356,    13.864259529024748     },
      {44.46624526233561,  -6.910405665655363,    13.884387096087798     },
      {44.47313293215392,  -6.8659393239213315,   13.904381350794077     },
      {44.47998321541279,  -6.821419951466755,    13.924242218540272     },
      {44.48679591007303,  -6.776847942828102,    13.943969625588132     },
      {44.493570815605665, -6.732223691959448,    13.963563499057228     },
      {44.50030773299051,  -6.68754759223415,     13.983023766917633     },
      {44.507006464714564, -6.642820036446583,    14.002350357982777     },
      {44.51366681477097,  -6.598041416813926,    14.02154320190218      },
      {44.52028858865695,  -6.553212124977996,    14.040602229154434     },
      {44.52687159337299,  -6.508332552007175,    14.059527371040055     },
      {44.533415637420646, -6.463403088398327,    14.07831855967449      },
      {44.53992053080151,  -6.418424124078843,    14.096975727981182     },
      {44.54638608501536,  -6.3733960484086465,   14.11549880968452      },
      {44.55281211305848,  -6.328319250182346,    14.13388773930317      },
      {44.55919842942242,  -6.283194117631385,    14.152142452143007     },
      {44.565544850091776, -6.238021038426228,    14.170262884290537     },
      {44.571851192543015, -6.192800399678656,    14.188248972606077     },
      {44.578117275742514, -6.1475325879440526,   14.206100654717055     },
      {44.58434292014478,  -6.102217989223759,    14.223817869011471     },
      {44.59052794769096,  -6.056856988967514,    14.241400554631241     },
      {44.596672181806895, -6.011449972075855,    14.25884865146567      },
      {44.60277544740131,  -5.9659973229026715,   14.276162100145065     },
      {44.60883757086419,  -5.9204994252577094,   14.29334084203417      },
      {44.614858380064774, -5.874956662409191,    14.310384819225892     },
      {44.62083770434981,  -5.829369417086447,    14.327293974534943     },
      {44.6267753745418,   -5.783738071482593,    14.344068251491546     },
      {44.632671222937034, -5.738063007257271,    14.36070759433522      },
      {44.63852508330355,  -5.69234460553939,     14.377211948008624     },
      {44.64433679087967,  -5.646583246929984,    14.393581258151377     },
      {44.65010618237172,  -5.6007793115050335,   14.409815471094065     },
      {44.65583309595237,  -5.554933178818369,    14.425914533852104     },
      {44.66151737125842,  -5.509045227904627,    14.441878394119893     },
      {44.66715884938924,  -5.463115837282217,    14.457707000264797     },
      {44.67275737290447,  -5.417145384956344,    14.473400301321307     },
      {44.67831278582241,  -5.371134248422079,    14.48895824698521      },
      {44.683824933617814, -5.325082804667446,    14.504380787607843     },
      {44.68929366321994,  -5.278991430176565,    14.519667874190324     },
      {44.6947188230108,   -5.232860500932847,    14.534819458377974     },
      {44.70010026282292,  -5.186690392422177,    14.549835492454546     },
      {44.70543783393741,  -5.140481479636199,    14.564715929336863     },
      {44.710731389082305, -5.094234137075582,    14.579460722569085     },
      {44.715980782429924, -5.047948738753355,    14.594069826317408     },
      {44.721185869595665, -5.001625658198286,    14.608543195364595     },
      {44.72634650763534,  -4.9552652684582466,   14.62288078510458      },
      {44.73146255504351,  -4.908867942103662,    14.637082551537205     },
      {44.7365338717515,   -4.862434051230985,    14.651148451262927     },
      {44.74156031912523,  -4.8159639674661845,   14.665078441477664     },
      {44.74654175996345,  -4.769458061968288,    14.678872479967541     },
      {44.751478058495415, -4.722916705432934,    14.692530525103896     },
      {44.756369080379315, -4.6763402680959905,   14.706052535838097     },
      {44.76121469269991,  -4.629729119737179,    14.71943847169669      },
      {44.76601476396666,  -4.583083629683737,    14.732688292776308     },
      {44.770769164111826, -4.536404166814116,    14.745801959738856     },
      {44.77547776448843,  -4.489691099561708,    14.7587794338066       },
      {44.78014043786814,  -4.4429447959185895,   14.771620676757447     },
      {44.7847570584396,   -4.396165623439329,    14.784325650920096     },
      {44.7893275018061,   -4.349353949244786,    14.796894319169423     },
      {44.793851644983874, -4.302510140025959,    14.80932664492183      },
      {44.7983293664001,   -4.2556345620478595,   14.82162259213056      },
      {44.80276054589071,  -4.208727581153415,    14.833782125281301     },
      {44.80714506469893,  -4.161789562767403,    14.845805209387535     },
      {44.81148280547274,  -4.114820871900388,    14.857691809986243     },
      {44.81577365226351,  -4.06782187315274,     14.869441893133432     },
      {44.82001749052364,  -4.020792930718599,    14.88105542539978      },
      {44.82421420710495,  -3.9737344083899555,   14.892532373866436     },
      {44.82836369025664,  -3.926646669560676,    14.903872706120675     },
      {44.832465829623395, -3.8795300772306205,   14.915076390251825     },
      {44.836520516243596, -3.832384994009732,    14.926143394847042     },
      {44.84052764254727,  -3.785211782122181,    14.937073688987283     },
      {44.844487102354556, -3.7380108034105386,   14.947867242243227     },
      {44.84839879087347,  -3.6907824193399392,   14.95852402467134      },
      {44.85226260469834,  -3.643526991002304,    14.969044006809956     },
      {44.85607844180794,  -3.5962448791205683,   14.979427159675291     },
      {44.859846201563535, -3.548936444052929,    14.989673454757796     },
      {44.86356578470739,  -3.5016020457971413,   14.999782864018197     },
      {44.86723709336059,  -3.4542420439947783,   15.009755359883894     },
      {44.8708600310218,   -3.406856797935605,    15.019590915245228     },
      {44.8744345025648,   -3.359446666561854,    15.029289503451874     },
      {44.87796041423758,  -3.312012008472653,    15.03885109830929      },
      {44.881437673659875, -3.2645531819283535,   15.048275674075137     },
      {44.88486618982199,  -3.217070544854961,    15.057563205455875     },
      {44.888245873082894, -3.169564454848555,    15.066713667603278     },
      {44.89157663516852,  -3.122035269179714,    15.075727036111132     },
      {44.894858389170146, -3.074483344798,       15.084603287011856     },
      {44.89809104954293,  -3.0269090383364183,   15.093342396773288     },
      {44.90127453210398,  -2.979312706115924,    15.101944342295404     },
      {44.90440875403105,  -2.9316947041499297,   15.110409100907209     },
      {44.90749363386082,  -2.884055388148855,    15.118736650363601     },
      {44.91052909148726,  -2.8363951135246492,   15.126926968842282     },
      {44.91351504816029,  -2.78871423539539,     15.134980034940783     },
      {44.91645142648413,  -2.7410131085898444,   15.142895827673481     },
      {44.91933815041585,  -2.693292087652079,    15.150674326468657     },
      {44.92217514526372,  -2.6455515268460807,   15.1583155111657       },
      {44.9249623376861,   -2.597791780160379,    15.165819362012236     },
      {44.927699655689594, -2.5500132013127,      15.173185859661363     },
      {44.93038702862792,  -2.502216143754625,    15.180414985169008     },
      {44.93302438720046,  -2.4544009606762787,   15.187506719991148     },
      {44.93561166345076,  -2.406568005011003,    15.194461045981337     },
      {44.9381487907653,   -2.358717629440085,    15.20127794538804      },
      {44.94063570387206,  -2.3108501863974533,   15.207957400852155     },
      {44.94307233883934,  -2.262966028074433,    15.21449939540457      },
      {44.945458633074395, -2.215065506424486,    15.220903912463722     },
      {44.947794525322145, -2.1671489731679587,   15.22717093583326      },
      {44.950079955663895, -2.119216779796875,    15.233300449699737     },
      {44.952314865516364, -2.0712692775797015,   15.239292438630315     },
      {44.954499197630156, -2.0233068175661613,   15.245146887570602     },
      {44.95663289608876,  -1.9753297505920302,   15.250863781842476     },
      {44.95871590630747,  -1.9273384272839609,   15.256443107141951     },
      {44.9607481750321,   -1.8793331980643142,   15.261884849537125     },
      {44.96272965033794,  -1.8313144131560024,   15.267188995466267     },
      {44.96466028162884,  -1.7832824225873432,   15.272355531735622     },
      {44.96654001963586,  -1.7352375761969165,   15.277384445517821     },
      {44.96836881641654,  -1.6871802236384439,   15.282275724349708     },
      {44.97014662535362,  -1.6391107143856682,   15.287029356130802     },
      {44.97187340115442,  -1.5910293977372447,   15.291645329121273     },
      {44.97354909984948,  -1.5429366228216448,   15.296123631940521     },
      {44.97517367879197,  -1.494832738602063,    15.300464253565226     },
      {44.97674709665667,  -1.4467180938813453,   15.304667183327954     },
      {44.978269313439,    -1.398593037306901,    15.308732410915518     },
      {44.97974029045438,  -1.3504579173756537,   15.31265992636743      },
      {44.98115999033723,  -1.3023130824389682,   15.316449720074505     },
      {44.98252837704026,  -1.25415888070762,     15.320101782777414     },
      {44.98384541583375,  -1.2059956602567343,   15.323616105565304     },
      {44.98511107330464,  -1.1578237690307644,   15.326992679874587     },
      {44.986325317356034, -1.1096435548484556,   15.330231497487514     },
      {44.98748811720639,  -1.0614553654078254,   15.333332550531114     },
      {44.988599443388836, -1.0132595482911535,   15.336295831475924     },
      {44.98965926775065,  -0.9650564509699604,   15.33912133313498      },
      {44.99066756345253,  -0.9168464208100147,   15.341809048662626     },
      {44.9916243049682,   -0.8686298050763226,   15.344358971553598     },
      {44.99252946808355,  -0.820406950938148,    15.346771095642051     },
      {44.99338302989649,  -0.7721782054740112,   15.349045415100537     },
      {44.9941849688162,   -0.72394391567671,     15.351181924439514     },
      {44.99493526456249,  -0.6757044284583392,   15.35318061850518      },
      {44.99563389816696,  -0.6274600906553178,   15.355041492483629     },
      {44.996280851965906, -0.5792112490334036,   15.356764541882072     },
      {44.99687610962516,  -0.5309582502927856,   15.358349762595067     },
      {44.99741965604594,  -0.48270144107286295,  15.359797150654854     },
      {44.99791147771377,  -0.43444116795827836,  15.361106703159626     },
      {44.99835156139579,  -0.38617777748020166,  15.362278414807065     },
      {44.99873989900003,  -0.33791161613542176,  15.363312290828379     },
      {44.99907646944021,  -0.28964303033895716,  15.364208298717013     },
      {44.99936130631441,  -0.24137236662478417,  15.364966548373411     },
      {44.99959424532825,  -0.19309997092063205,  15.365586619806692     },
      {44.99977586691001,  -0.14482619127829868,  15.366070072146254     },
      {44.99990397836342,  -0.09655136770804099,  15.366411079993998     },
      {44.999986742537395, -0.048275870140680216, 15.366631378725746     },
      {44.99999136833833,  -0.016091916464460496, 15.36664369129905      },
      {45,                 1.881873914689766e-15, 15.366666666666667     },
      {44.99999136833833,  0.016091916464461488,  15.36664369129905      },
      {44.999986742537374, 0.04827587014067366,   15.366631378725742     },
      {44.999903978363434, 0.09655136770803932,   15.366411079994005     },
      {44.99977586691001,  0.14482619127828486,   15.366070072146254     },
      {44.99959424532823,  0.19309997092063153,   15.365586619806685     },
      {44.99936130631442,  0.24137236662477823,   15.364966548373413     },
      {44.999076469440205, 0.28964303033895056,   15.364208298717012     },
      {44.998739899000036, 0.3379116161354146,    15.363312290828377     },
      {44.99835156139578,  0.386177777480188,     15.362278414807067     },
      {44.99791147771378,  0.4344411679582816,    15.361106703159624     },
      {44.99741965604595,  0.48270144107285234,   15.359797150654856     },
      {44.99687610962515,  0.5309582502927866,    15.358349762595063     },
      {44.99628085196591,  0.5792112490333938,    15.356764541882079     },
      {44.99563389816695,  0.6274600906553109,    15.355041492483625     },
      {44.99493526456248,  0.6757044284583302,    15.353180618505181     },
      {44.9941849688162,   0.7239439156767097,    15.351181924439508     },
      {44.993383029896485, 0.7721782054740005,    15.34904541510054      },
      {44.99252946808356,  0.8204069509381452,    15.346771095642051     },
      {44.99162430496819,  0.8686298050763195,    15.344358971553593     },
      {44.99066756345255,  0.9168464208100146,    15.341809048662629     },
      {44.98965926775064,  0.9650564509699538,    15.339121333134973     },
      {44.98859944338884,  1.0132595482911422,    15.336295831475931     },
      {44.98748811720639,  1.061455365407816,     15.333332550531107     },
      {44.986325317356034, 1.1096435548484564,    15.330231497487516     },
      {44.98511107330462,  1.1578237690307596,    15.326992679874584     },
      {44.98384541583377,  1.2059956602567217,    15.323616105565309     },
      {44.98252837704025,  1.2541588807076216,    15.32010178277741      },
      {44.981159990337225, 1.3023130824389644,    15.316449720074502     },
      {44.97974029045439,  1.350457917375647,     15.312659926367434     },
      {44.978269313439,    1.398593037306897,     15.308732410915518     },
      {44.97674709665668,  1.4467180938813344,    15.304667183327958     },
      {44.97517367879198,  1.4948327386020606,    15.300464253565222     },
      {44.97354909984947,  1.5429366228216328,    15.296123631940517     },
      {44.97187340115441,  1.5910293977372478,    15.291645329121273     },
      {44.97014662535363,  1.639110714385656,     15.287029356130807     },
      {44.96836881641654,  1.6871802236384323,    15.282275724349706     },
      {44.96654001963587,  1.7352375761969137,    15.277384445517825     },
      {44.96466028162884,  1.7832824225873378,    15.272355531735625     },
      {44.96272965033793,  1.8313144131559915,    15.267188995466258     },
      {44.96074817503211,  1.8793331980643093,    15.261884849537134     },
      {44.95871590630746,  1.9273384272839555,    15.256443107141948     },
      {44.95663289608876,  1.9753297505920235,    15.25086378184248      },
      {44.95449919763016,  2.023306817566163,     15.245146887570602     },
      {44.95231486551637,  2.071269277579693,     15.239292438630319     },
      {44.95007995566391,  2.119216779796863,     15.233300449699739     },
      {44.94779452532213,  2.16714897316796,      15.22717093583326      },
      {44.94545863307441,  2.2150655064244744,    15.220903912463722     },
      {44.94307233883936,  2.26296602807443,      15.21449939540457      },
      {44.94063570387206,  2.310850186397446,     15.207957400852157     },
      {44.9381487907653,   2.358717629440074,     15.201277945388041     },
      {44.93561166345076,  2.406568005011006,     15.194461045981337     },
      {44.933024387200476, 2.45440096067627,      15.187506719991156     },
      {44.93038702862791,  2.5022161437546204,    15.180414985169001     },
      {44.9276996556896,   2.550013201312697,     15.173185859661372     },
      {44.92496233768609,  2.5977917801603723,    15.165819362012233     },
      {44.922175145263736, 2.645551526846067,     15.158315511165704     },
      {44.91933815041584,  2.6932920876520807,    15.150674326468657     },
      {44.91645142648414,  2.74101310858983,      15.142895827673485     },
      {44.9135150481603,   2.7887142353953824,    15.134980034940787     },
      {44.91052909148725,  2.8363951135246515,    15.126926968842277     },
      {44.907493633860824, 2.884055388148843,     15.118736650363598     },
      {44.904408754031046, 2.931694704149934,     15.110409100907216     },
      {44.90127453210398,  2.9793127061159135,    15.1019443422954       },
      {44.89809104954293,  3.026909038336412,     15.093342396773298     },
      {44.894858389170146, 3.074483344797992,     15.084603287011856     },
      {44.891576635168526, 3.1220352691797078,    15.075727036111132     },
      {44.888245873082866, 3.1695644548485458,    15.066713667603281     },
      {44.88486618982202,  3.2170705448549506,    15.057563205455875     },
      {44.88143767365988,  3.2645531819283495,    15.048275674075137     },
      {44.87796041423756,  3.3120120084726508,    15.03885109830929      },
      {44.874434502564824, 3.359446666561854,     15.029289503451878     },
      {44.87086003102178,  3.406856797935597,     15.019590915245232     },
      {44.867237093360636, 3.4542420439947663,    15.009755359883894     },
      {44.86356578470739,  3.5016020457971417,    14.999782864018197     },
      {44.85984620156354,  3.5489364440529183,    14.989673454757803     },
      {44.856078441807924, 3.596244879120564,     14.97942715967529      },
      {44.85226260469834,  3.6435269910022927,    14.96904400680995      },
      {44.848398790873475, 3.6907824193399357,    14.958524024671346     },
      {44.844487102354556, 3.7380108034105404,    14.947867242243229     },
      {44.8405276425473,   3.7852117821221754,    14.937073688987287     },
      {44.83652051624358,  3.8323849940097254,    14.926143394847049     },
      {44.83246582962341,  3.8795300772306134,    14.91507639025183      },
      {44.82836369025664,  3.926646669560675,     14.903872706120675     },
      {44.824214207104944, 3.9737344083899457,    14.892532373866441     },
      {44.820017490523654, 4.020792930718605,     14.881055425399774     },
      {44.8157736522635,   4.067821873152726,     14.86944189313343      },
      {44.81148280547274,  4.114820871900395,     14.85769180998624      },
      {44.80714506469892,  4.161789562767397,     14.845805209387539     },
      {44.802760545890706, 4.2087275811534095,    14.833782125281294     },
      {44.79832936640011,  4.255634562047857,     14.821622592130561     },
      {44.79385164498386,  4.302510140025945,     14.809326644921832     },
      {44.78932750180611,  4.34935394924478,      14.796894319169423     },
      {44.78475705843961,  4.396165623439329,     14.7843256509201       },
      {44.780140437868134, 4.442944795918583,     14.771620676757443     },
      {44.77547776448843,  4.489691099561704,     14.758779433806605     },
      {44.77076916411182,  4.536404166814103,     14.745801959738857     },
      {44.76601476396666,  4.583083629683739,     14.732688292776308     },
      {44.761214692699916, 4.629729119737172,     14.71943847169669      },
      {44.75636908037933,  4.676340268095977,     14.706052535838104     },
      {44.75147805849545,  4.72291670543293,      14.692530525103887     },
      {44.74654175996344,  4.769458061968283,     14.678872479967547     },
      {44.74156031912523,  4.81596396746618,      14.665078441477664     },
      {44.73653387175148,  4.862434051230979,     14.65114845126293      },
      {44.731462555043514, 4.908867942103658,     14.637082551537203     },
      {44.726346507635334, 4.955265268458237,     14.622880785104583     },
      {44.72118586959566,  5.001625658198281,     14.608543195364597     },
      {44.71598078242996,  5.047948738753346,     14.594069826317412     },
      {44.71073138908228,  5.094234137075578,     14.579460722569083     },
      {44.70543783393743,  5.140481479636189,     14.564715929336863     },
      {44.700100262822914, 5.186690392422177,     14.54983549245455      },
      {44.6947188230108,   5.232860500932841,     14.534819458377976     },
      {44.68929366321994,  5.278991430176557,     14.519667874190333     },
      {44.683824933617814, 5.325082804667439,     14.504380787607843     },
      {44.67831278582241,  5.371134248422076,     14.488958246985208     },
      {44.67275737290446,  5.417145384956335,     14.473400301321313     },
      {44.66715884938924,  5.463115837282212,     14.457707000264792     },
      {44.66151737125842,  5.5090452279046165,    14.441878394119897     },
      {44.65583309595236,  5.554933178818365,     14.425914533852106     },
      {44.65010618237172,  5.600779311505029,     14.409815471094065     },
      {44.644336790879684, 5.646583246929981,     14.393581258151382     },
      {44.63852508330355,  5.692344605539384,     14.377211948008622     },
      {44.632671222937034, 5.738063007257264,     14.360707594335217     },
      {44.62677537454181,  5.783738071482588,     14.344068251491551     },
      {44.62083770434981,  5.829369417086437,     14.327293974534943     },
      {44.61485838006477,  5.8749566624091845,    14.310384819225892     },
      {44.608837570864175, 5.920499425257699,     14.293340842034171     },
      {44.60277544740133,  5.965997322902665,     14.276162100145077     },
      {44.59667218180691,  6.0114499720758525,    14.258848651465673     },
      {44.590527947690944, 6.056856988967515,     14.241400554631234     },
      {44.584342920144785, 6.102217989223755,     14.223817869011478     },
      {44.57811727574251,  6.147532587944037,     14.206100654717059     },
      {44.57185119254302,  6.192800399678655,     14.188248972606075     },
      {44.56554485009179,  6.238021038426217,     14.170262884290544     },
      {44.55919842942241,  6.283194117631383,     14.152142452143002     },
      {44.55281211305847,  6.328319250182333,     14.133887739303173     },
      {44.546386085015364, 6.373396048408647,     14.11549880968452      },
      {44.53992053080151,  6.418424124078831,     14.096975727981183     },
      {44.533415637420646, 6.463403088398328,     14.078318559674491     },
      {44.526871593372974, 6.508332552007175,     14.059527371040053     },
      {44.52028858865697,  6.5532121249779856,    14.04060222915444      },
      {44.51366681477097,  6.598041416813922,     14.021543201902178     },
      {44.507006464714586, 6.642820036446579,     14.002350357982786     },
      {44.50030773299049,  6.68754759223415,      13.983023766917631     },
      {44.493570815605665, 6.7322236919594385,    13.963563499057228     },
      {44.48679591007302,  6.776847942828104,     13.943969625588132     },
      {44.47998321541279,  6.821419951466751,     13.924242218540268     },
      {44.473132932153945, 6.865939323921326,     13.90438135079408      },
      {44.466245262335576, 6.910405665655355,     13.884387096087794     },
      {44.459320409508365, 6.954818581548354,     13.864259529024757     },
      {44.45235857873551,  6.999177675894241,     13.84399872508079      },
      {44.4453599765945,   7.043482552399869,     13.823604760611586     },
      {44.438324811178184, 7.0877328141835605,    13.803077712860151     },
      {44.43125329209566,  7.1319280637736675,    13.782417659964398     },
      {44.42414563047402,  7.176067903107359,     13.761624680964527     },
      {44.41700203895888,  7.220151933529252,     13.740698855810848     },
      {44.409822731716076, 7.26417975579022,      13.719640265371174     },
      {44.402607924432075, 7.308150970046325,     13.698448991438765     },
      {44.395357834315575, 7.352065175857623,     13.677125116739848     },
      {44.388072680098134, 7.395921972187244,     13.655668724941545     },
      {44.380752682035016, 7.439720957400352,     13.63407990065965      },
      {44.373398061906435, 7.483461729263368,     13.612358729466488     },
      {44.366009043018025, 7.527143884942994,     13.590505297898886     },
      {44.3585858502018,   7.570767021005612,     13.568519693466062     },
      {44.351128709816905, 7.6143307334164785,    13.546402004657747     },
      {44.34363784975007,  7.657834617539161,     13.524152320952123     },
      {44.33611349941667,  7.701278268134944,     13.501770732824022     },
      {44.32855588976094,  7.744661279362392,     13.47925733175298      },
      {44.320965253256475, 7.787983244776854,     13.456612210231524     },
      {44.31334182390721,  7.831243757330224,     13.433835461773302     },
      {44.30568583724712,  7.874442409370555,     13.410927180921458     },
      {44.29799753034126,  7.91757879264194,      13.387887463256872     },
      {44.29027714178548,  7.96065249828432,      13.364716405406563     },
      {44.28252491170717,  8.003663116833497,     13.341414105052081     },
      {44.27474108176519,  8.046610238221046,     13.317980660937952     },
      {44.26692589515002,  8.089493451774516,     13.29441617288017      },
      {44.2590795965838,   8.132312346217507,     13.270720741774728     },
      {44.251202432320504, 8.175066509669996,     13.2468944696062       },
      {44.243294650145714, 8.217755529648567,     13.222937459456281     },
      {44.235356499376486, 8.260378993066887,     13.198849815512574     },
      {44.22738823086123,  8.302936486236115,     13.17463164307714      },
      {44.2193900969795,   8.345427594865525,     13.15028304857534      },
      {44.211362351641455, 8.38785190406309,      13.125804139564522     },
      {44.20330525028768,  8.43020899833618,      13.101195024742879     },
      {44.19521904988863,  8.472498461592478,     13.076455813958296     },
      {44.18710400894392,  8.51471987714066,      13.051586618217232     },
      {44.17896038748201,  8.556872827691581,     13.026587549693595     },
      {44.17078844705931,  8.598956895359134,     13.001458721737801     },
      {44.16258845075933,  8.640971661661506,     12.976200248885679     },
      {44.15436066319201,  8.682916707522322,     12.950812246867569     },
      {44.14610535049271,  8.72479161327199,      12.925294832617329     },
      {44.13782278032121,  8.766595958649063,     12.899648124281528     },
      {44.12951322186048,  8.808329322801754,     12.873872241228492     },
      {44.12117694581572,  8.849991284289445,     12.847967304057548     },
      {44.11281422441284,  8.891581421084396,     12.821933434608194     },
      {44.10442533139741,  8.93309931057347,      12.795770755969397     },
      {44.09601054203285,  8.974544529559966,     12.769479392488753     },
      {44.08757013309936,  9.015916654265563,     12.743059469781933     },
      {44.07910438289172,  9.057215260332306,     12.716511114741937     },
      {44.070613571218104, 9.09843992282478,      12.689834455548477     },
      {44.06209797939799,  9.139590216232262,     12.663029621677389     },
      {44.05355789026028,  9.180665714471054,     12.636096743910088     },
      {44.0449935881414,   9.221665990886882,     12.609035954342975     },
      {44.03640535888311,  9.262590618257367,     12.581847386396984     },
      {44.02779348983039,  9.303439168794668,     12.554531174827037     },
      {44.01915826982899,  9.344211214148135,     12.527087455731674     },
      {44.01049998922324,  9.3849063254071,       12.499516366562563     },
      {44.00181893985343,  9.425524073103789,     12.471818046134084     },
      {43.993115415053154, 9.46606402721629,      12.443992634633057     },
      {43.98438970964675,  9.506525757171683,     12.416040273628276     },
      {43.97564211994628,  9.54690883184918,      12.387961106080235     },
      {43.966872943748854, 9.587212819583485,     12.35975527635086      },
      {43.95808248033338,  9.627437288168124,     12.331422930213183     },
      {43.94927103045748,  9.667581804859054,     12.302964214861067     },
      {43.94043889635418,  9.707645936378148,     12.274379278919088     },
      {43.931586381728756, 9.747629248917036,     12.245668272452185     },
      {43.92271379175485,  9.787531308140839,     12.216831346975566     },
      {43.913821433071206, 9.827351679192162,     12.187868655464458     },
      {43.90490961377781,  9.867089926695078,     12.158780352364033     },
      {43.895978643431945, 9.906745614759371,     12.129566593599224     },
      {43.88702883304438,  9.94631830698469,      12.100227536584615     },
      {43.87806049507515,  9.985807566464993,     12.07076334023433      },
      {43.86907394342948,  10.025212955793025,    12.041174164971997     },
      {43.86006949345312,  10.064534037064885,    12.011460172740598     },
      {43.851047461928346, 10.103770371884774,    11.981621527012464     },
      {43.84200816706896,  10.142921521369795,    11.951658392799223     },
      {43.83295192851563,  10.181987046154875,    11.921570936661782     },
      {43.823879067331255, 10.220966506397897,    11.891359326720227     },
      {43.81478990599555,  10.2598594617848,      11.86102373266395      },
      {43.8056847684004,   10.298665471534875,    11.830564325761497     },
      {43.79656397984408,  10.33738409440621,     11.799981278870712     },
      {43.787427867026324, 10.3760148887012,      11.769274766448623     },
      {43.77827675804231,  10.414557412272206,    11.738444964561564     },
      {43.76911098237745,  10.453011222527259,    11.70749205089517      },
      {43.75993087090108,  10.491375876436052,    11.67641620476436      },
      {43.75073675586078,  10.529650930535857,    11.645217607123495     },
      {43.741528970876274, 10.567835940937739,    11.61389644057622      },
      {43.732307850932884, 10.60593046333271,     11.58245288938573      },
      {43.72307373237543,  10.643934052998244,    11.550887139484631     },
      {43.71382695290142,  10.68184626480464,     11.519199378485087     },
      {43.70456785155448,  10.719666653221775,    11.487389795688769     },
      {43.695296768717405, 10.757394772325775,    11.455458582096973     },
      {43.68601404610516,  10.795030175805955,    11.423405930420621     },
      {43.676720026757664, 10.832572416971772,    11.39123203509029      },
      {43.66741505503251,  10.870021048760039,    11.358937092266183     },
      {43.65809947659752,  10.907375623742135,    11.326521299848231     },
      {43.64877363842281,  10.944635694131431,    11.29398485748603      },
      {43.639437888773365, 10.981800811790823,    11.261327966588883     },
      {43.630092577200685, 11.018870528240345,    11.228550830335754     },
      {43.62073805453508,  11.055844394665035,    11.195653653685211     },
      {43.61137467287674,  11.092721961922843,    11.162636643385522     },
      {43.602002785588084, 11.12950278055258,     11.129500007984372     },
      {43.59262274728416,  11.166186400782298,    11.096243957839091     },
      {43.58323491382479,  11.202772372537437,    11.062868705126245     },
      {43.573839642304755, 11.239260245449422,    11.029374463851806     },
      {43.564437291045294, 11.275649568864132,    10.995761449860863     },
      {43.55502821958441,  11.311939891850749,    10.962029880847536     },
      {43.5456127886674,   11.348130763210559,    10.928179976364822     },
      {43.536191360237375, 11.384221731485951,    10.894211957834383     },
      {43.526764297425146, 11.420212344969606,    10.860126048556324     },
      {43.51733196453942,  11.45610215171374,     10.825922473718986     },
      {43.50789472705651,  11.49189069953952,     10.791601460408637     },
      {43.49845295160981,  11.52757753604664,     10.75716323761928      },
      {43.48900700597949,  11.563162208623037,    10.72260803626213      },
      {43.479557259081524, 11.598644264454698,    10.68793608917547      },
      {43.47010408095683,  11.634023250535625,    10.653147631134127     },
      {43.46064784276022,  11.669298713677982,    10.618242898859105     },
      {43.45118891674888,  11.704470200522408,    10.583222131027103     },
      {43.44172767627117,  11.739537257548262,    10.54808556828002      },
      {43.432264495754644, 11.77449943108439,     10.512833453234444     },
      {43.42279975069442,  11.809356267319577,    10.47746603049101      },
      {43.413333817640954, 11.844107312313593,    10.441983546643872     },
      {43.40386707418787,  11.878752112008016,    10.406386250289982     },
      {43.39439989895945,  11.913290212237408,    10.370674392038365     },
      {43.384932671598015, 11.947721158740638,    10.334848224519455     },
      {43.375465772751184, 11.982044497172135,    10.298908002394196     },
      {43.36599958405862,  12.016259773113601,    10.262853982363245     },
      {43.35653448813913,  12.050366532085619,    10.22668642317605      },
      {43.34707086857683,  12.084364319559517,    10.190405585639907     },
      {43.337609109907916, 12.118252680969373,    10.154011732628978     },
      {43.32814959760658,  12.152031161724107,    10.117505129093121     },
      {43.31869271807109,  12.18569930721981,     10.080886042066945     },
      {43.30923885860954,  12.219256662852157,    10.044154740678415     },
      {43.299788407425574, 12.252702774028933,    10.00731149615778      },
      {43.29034175360337,  12.286037186182837,    9.970356581846206      },
      {43.280899287093355, 12.319259444784246,    9.933290273204378      },
      {43.271461398696644, 12.352369095354364,    9.896112847821108      },
      {43.26202848005022,  12.38536568347821,     9.85882458542179       },
      {43.252600923611226, 12.41824875481807,     9.821425767876878      },
      {43.243179122641486, 12.451017855126874,    9.783916679210181      },
      {43.233763471191516, 12.483672530261826,    9.746297605607168      },
      {43.2243543640846,   12.516212326198133,    9.708568835423216      },
      {43.21495219690038,  12.548636789042902,    9.670730659191666      },
      {43.20555736595858,  12.580945465049204,    9.632783369631895      },
      {43.19617026830211,  12.613137900630203,    9.594727261657372      },
      {43.18679130168037,  12.645213642373562,    9.556562632383374      },
      {43.17742086453199,  12.677172237055863,    9.518289781134992      },
      {43.16805935596762,  12.709013231657298,    9.479909009454659      },
      {43.15870717575251,  12.740736173376327,    9.441420621109934      },
      {43.14936472428849,  12.772340609644743,    9.402824922100962      },
      {43.140032402596404, 12.803826088142653,    9.364122220667923      },
      {43.13071061229768,  12.835192156813637,    9.325312827298422      },
      {43.121399755596215, 12.866438363880228,    9.286397054734735      },
      {43.11210023525952,  12.897564257859308,    9.247375217980997      },
      {43.10281245460028,  12.928569387577813,    9.208247634310194      },
      {43.09353681745725,  12.959453302188459,    9.16901462327122       },
      {43.08427372817578,  12.99021555118576,     9.129676506695697      },
      {43.07502359158899,  13.020855684422004,    9.090233608704713      },
      {43.06578681299765,  13.051373252123533,    9.050686255715513      },
      {43.056563798150634, 13.081767804907097,    9.011034776448005      },
      {43.047354953224854, 13.112038893796328,    8.971279501931203      },
      {43.03816068480481,  13.142186070238424,    8.931420765509607      },
      {43.02898139986256,  13.172208886120853,    8.891458902849273      },
      {43.01981750573672,  13.202106893788397,    8.851394251944058      },
      {43.010669410111774, 13.231879646060069,    8.811227153121434      },
      {43.001537520996806, 13.261526696246468,    8.770957949048494      },
      {42.99242224670459,  13.291047598166978,    8.730586984737588      },
      {42.98332399582982,  13.320441906167323,    8.690114607551884      },
      {42.974243177227436, 13.349709175137168,    8.649541167210995      },
      {42.96518019999083,  13.378848960527854,    8.60886701579619       },
      {42.95613547342986,  13.407860818370285,    8.568092507755654      },
      {42.94710940704825,  13.43674430529291,     8.527217999909606      },
      {42.93810241052134,  13.465498978539996,    8.486243851455242      },
      {42.92911489367334,  13.494124395989706,    8.445170423971497      },
      {42.92014726645427,  13.52262011617272,     8.403998081423826      },
      {42.91119993891722,  13.550985698290615,    8.362727190168634      },
      {42.90227332119451,  13.57922070223464,     8.321358118957766      },
      {42.893367823474804, 13.607324688604479,    8.279891238942696      },
      {42.8844838559789,   13.635297218727148,    8.238326923678674      },
      {42.87562182893619,  13.663137854676101,    8.19666554912864       },
      {42.86678215256026,  13.690846159290386,    8.154907493667123      },
      {42.857965237025084, 13.718421696193891,    8.113053138083764      },
      {42.849171492439936, 13.745864029814902,    8.07110286558696       },
      {42.84040132882532,  13.773172725405455,    8.029057061807125      },
      {42.831655156087734, 13.800347349061177,    7.986916114799889      },
      {42.82293338399482,  13.82738746774092,     7.9446804150491666     },
      {42.81423642215008,  13.854292649286805,    7.902350355469991      },
      {42.80556467996753,  13.881062462444081,    7.859926331411242      },
      {42.796918566646006, 13.907696476881341,    7.817408740658166      },
      {42.788298491143564, 13.934194263210761,    7.774797983434754      },
      {42.779704862151306, 13.960555393008407,    7.7320944624059935     },
      {42.771138088067616, 13.986779438834688,    7.689298582679784      },
      {42.762598576971456, 14.012865974254982,    7.6464107518089275     },
      {42.754086736596136, 14.038814573860254,    7.603431379792751      },
      {42.745602974302756, 14.064624813287791,    7.560360879078585      },
      {42.73714769705308,  14.090296269242213,    7.51719966456316       },
      {42.72872131138308,  14.115828519516253,    7.473948153593675      },
      {42.72032422337507,  14.14122114301206,     7.430606765968873      },
      {42.71195683863124,  14.166473719762129,    7.3871759239397035     },
      {42.70361956224547,  14.191585830950801,    7.343656052209973      },
      {42.69531279877627,  14.216557058935427,    7.300047577936783      },
      {42.68703695221868,  14.241386987267925,    7.256350930730675      },
      {42.678792425976475, 14.26607520071629,     7.212566542655717      },
      {42.67057962283401,  14.290621285286255,    7.168694848229325      },
      {42.66239894492825,  14.315024828242901,    7.124736284421858      },
      {42.65425079372005,  14.339285418132597,    7.080691290656125      },
      {42.646135569965985, 14.363402644804717,    7.036560308806576      },
      {42.6380536736895,   14.38737609943372,     6.992343783198387      },
      {42.63000550415231,  14.411205374541112,    6.948042160606244      },
      {42.62199145982527,  14.434890064017559,    6.90365589025304       },
      {42.61401193835966,  14.458429763145048,    6.8591854238082846     },
      {42.60606733655767,  14.481824068619169,    6.814631215386326      },
      {42.59815805034357,  14.50507257857137,     6.769993721544378      },
      {42.59028447473369,  14.528174892591366,    6.725273401280313      },
      {42.58244700380763,  14.55113061174956,     6.680470716030283      },
      {42.574646030678,    14.573939338619542,    6.635586129666109      },
      {42.56688194746117,  14.596600677300628,    6.590620108492379      },
      {42.55915514524702,  14.619114233440488,    6.545573121243564      },
      {42.55146601406939,  14.64147961425776,     6.5004456390805245     },
      {42.543814942875755, 14.663696428564808,    6.455238135587265      },
      {42.536202319497114, 14.685764286790416,    6.409951086767108      },
      {42.528628530618,    14.707682801002612,    6.364584971038743      },
      {42.52109396174597,  14.729451584931534,    6.319140269232198      },
      {42.513598997181106, 14.751070253992205,    6.273617464584355      },
      {42.50614401998583,  14.772538425307603,    6.228017042734471      },
      {42.4987294119542,   14.793855717731372,    6.182339491719237      },
      {42.49135555358118,  14.815021751871017,    6.136585301967889      },
      {42.484022824032216, 14.836036150110777,    6.090754966296708      },
      {42.4767316011122,   14.85689853663466,     6.044848979903814      },
      {42.46948226123495,  14.877608537449488,    5.9988678403631255     },
      {42.46227517939211,  14.898165780407943,    5.9528120476186155     },
      {42.455110729122254, 14.918569895231705,    5.9066821039780315     },
      {42.447989282480194, 14.938820513534404,    5.860478514106445      },
      {42.44091121000563,  14.958917268844832,    5.814201785019596      },
      {42.43387688069225,  14.978859796629983,    5.767852426077048      },
      {42.42688666195686,  14.998647734318125,    5.721430948974966      },
      {42.41994091960785,  15.018280721321975,    5.674937867738778      },
      {42.41304001781458,  15.0377583990617,      5.628373698715573      },
      {42.40618431907575,  15.057080410988057,    5.581738960566234      },
      {42.399374184188744, 15.076246402605438,    5.535034174257325      },
      {42.39260997221797,  15.095256021494938,    5.488259863052804      },
      {42.38589204046413,  15.114108917337399,    5.441416552505406      },
      {42.379220744432764, 15.132804741936381,    5.394504770447861      },
      {42.372596437803224, 15.151343149241253,    5.347525046983819      },
      {42.36601947239749,  15.169723795370048,    5.300477914478541      },
      {42.35949019814906,  15.187946338632447,    5.253363907549401      },
      {42.35300896307186,  15.206010439552692,    5.206183563056029      },
      {42.34657611322895,  15.223915760892442,    5.158937420090368      },
      {42.340191992701946, 15.241661967673519,    5.111626019966335      },
      {42.333856943559454, 15.259248727200777,    5.064249906209297      },
      {42.32757130582641,  15.27667570908481,     5.016809624545423      },
      {42.321335417453135, 15.293942585264526,    4.969305722890476      },
      {42.31514961428428,  15.311049030029906,    4.921738751338817      },
      {42.30901423002837,  15.32799472004442,     4.874109262151627      },
      {42.30292959622643,  15.344779334367638,    4.82641780974545       },
      {42.29689604222209,  15.361402554477564,    4.7786649506799606     },
      {42.29091389513019,  15.37786406429303,     4.730851243645914      },
      {42.284983479806904, 15.394163550195962,    4.682977249452577      },
      {42.27910511881861,  15.41030070105363,     4.635043531015043      },
      {42.27327913241234,  15.42627520824066,     4.587050653341248      },
      {42.2675058384847,   15.442086765661191,    4.538999183518781      },
      {42.26178555255217,  15.457735069770708,    4.490889690701438      },
      {42.256118587721055, 15.473219819598022,    4.442722746095536      },
      {42.250505254657305, 15.488540716766853,    4.394498922945909      },
      {42.244945861556715, 15.503697465517682,    4.346218796521826      },
      {42.239440714115425, 15.518689772729147,    4.29788294410253       },
      {42.23399011550008,  15.533517347939583,    4.249491944962551      },
      {42.228594366318646, 15.548179903368258,    4.201046380356821      },
      {42.22325376459077,  15.562677153936711,    4.152546833505555      },
      {42.21796860571885,  15.577008817289787,    4.103993889578859      },
      {42.212739182459046, 15.59117461381657,     4.055388135681076      },
      {42.20756578489214,  15.605174266671337,    4.006730160835016      },
      {42.20244870039532,  15.619007501794144,    3.9580205559657182     },
      {42.19738821361302,  15.632674047931598,    3.9092599138843083     },
      {42.19238460642919,  15.646173636657089,    3.8604488292712578     },
      {42.187438157938615, 15.659506002391286,    3.8115878986597265     },
      {42.182549144419326, 15.67267088242217,     3.7626777204184685     },
      {42.17771783930451,  15.6856680169251,      3.7137188947345257     },
      {42.17294451315495,  15.698497148982723,    3.664712023595874      },
      {42.16822943363179,  15.711158024604558,    3.6156577107735726     },
      {42.16357286546911,  15.72365039274666,     3.5665565618039223     },
      {42.15897507044707,  15.735974005330945,    3.5174091839701944     },
      {42.154436307365124, 15.74812861726443,     3.4682161862843155     },
      {42.14995683201545,  15.760113986458233,    3.418978179468241      },
      {42.14553689715658,  15.771929873846503,    3.369695775935061      },
      {42.141176752487496, 15.78357604340508,     3.320369589770028      },
      {42.136876644621545, 15.795052262170017,    3.271000236711212      },
      {42.132636817061,    15.806358300255898,    3.2215883341300207     },
      {42.12845751017173,  15.817493930873987,    3.1721345010115476     },
      {42.124338961157854, 15.828458930350195,    3.1226393579345753     },
      {42.120281404037414, 15.839253078142711,    3.0731035270515172     },
      {42.1162850696172,   15.849876156859786,    3.0235276320679993     },
      {42.112350185468856, 15.860327952276855,    2.9739122982224706     },
      {42.10847697590494,  15.870608253353783,    2.924258152265208      },
      {42.10466566195469,  15.880716852251787,    2.8745658224376687     },
      {42.100916461341164, 15.890653544350194,    2.824835938451062      },
      {42.09722958845772,  15.900418128262853,    2.7750691314651856     },
      {42.09360525434537,  15.910010405854536,    2.7252660340668022     },
      {42.09004366666993,  15.919430182256876,    2.675427280247944      },
      {42.08654502970013,  15.928677265884353,    2.6255535053839467     },
      {42.08310954428556,  15.937751468449765,    2.5756453462113518     },
      {42.07973740783486,  15.946652604979683,    2.525703440805602      },
      {42.07642881429477,  15.95538049382955,     2.475728428558608      },
      {42.07318395412881,  15.96393495669868,     2.4257209501559776     },
      {42.070003014296965, 15.972315818644745,    2.375681647554273      },
      {42.066886178235215, 15.98052290809837,     2.325611163957938      },
      {42.06383362583561,  15.988556056877169,    2.275510143796128      },
      {42.06084553342656,  15.996415100199801,    2.225379232699355      },
      {42.0579220737539,   16.00409987669947,     2.1752190774759215     },
      {42.0550634159615,   16.011610228437505,    2.1250303260882877     },
      {42.05226972557332,  16.01894600091632,     2.0748136276291533     },
      {42.04954116447453,  16.026107043092537,    2.0245696322975353     },
      {42.0468778908944,   16.033093207389385,    1.9742989913745053     },
      {42.04428005938823,  16.039904349709243,    1.924002357198912      },
      {42.04174782082076,  16.046540329445566,    1.873680383142958      },
      {42.03928132234923,  16.053001009494828,    1.8233337235874987     },
      {42.03688070740719,  16.059286256267995,    1.7729630338973754     },
      {42.03454611568841,  16.065395939701833,    1.722568970396446      },
      {42.03227768313157,  16.071329933269837,    1.6721521903426086     },
      {42.03007554190502,  16.077088113993003,    1.6217133519025997     },
      {42.02793982039201,  16.08267036245018,     1.5712531141267425     },
      {42.02587064317653,  16.08807656278824,     1.5207721369234863     },
      {42.023868131029026, 16.093306602731936,    1.470271081033863      },
      {42.02193240089338,  16.0983603735934,      1.419750608005903      },
      {42.02006356587336,  16.103237770281467,    1.3692113801687045     },
      {42.01826173522011,  16.107938691310572,    1.3186540606067587     },
      {42.016527014319934, 16.11246303880953,     1.2680793131337098     },
      {42.014859504682356, 16.11681071852973,     1.217487802266468      },
      {42.01325930392859,  16.120981639853433,    1.1668801931988675     },
      {42.01172650578086,  16.124975715801277,    1.116257151775403      },
      {42.01026120005131,  16.128792863040026,    1.065619344464879      },
      {42.008863472632534, 16.132433001889428,    1.0149674383338563     },
      {42.007533405487045, 16.135896056329372,    0.964302101020089      },
      {42.00627107663883,  16.139181954006173,    0.913624000705926      },
      {42.00507656016389,  16.142290626238943,    0.8629338060915042     },
      {42.003949926182166, 16.145222008025495,    0.8122321863680089     },
      {42.002891240849415, 16.147976038047922,    0.7615198111906966     },
      {42.001900566349775, 16.150552658677906,    0.7107973506520351     },
      {42.000977960888854, 16.15295181598171,     0.6600654752546736     },
      {42.00012347868665,  16.155173459724843,    0.6093248558843355     },
      {41.999337169971966, 16.15721754337636,     0.5585761637826787     },
      {41.998619080976304, 16.15908402411294,     0.5078200705201943     },
      {41.99796925392866,  16.160772862822615,    0.4570572479688869     },
      {41.99738772705083,  16.16228402410808,     0.40628836827507325    },
      {41.996874534552965, 16.163617476289822,    0.3555141038320095     },
      {41.99642970662961,  16.164773191408884,    0.3047351272525784     },
      {41.99605326945647,  16.165751145229205,    0.25395211134190476    },
      {41.99574524518718,  16.166551317239865,    0.20316572906992467    },
      {41.99550565195094,  16.16717369065667,     0.15237665354399563    },
      {41.99533450385037,  16.167618252423832,    0.10158555798137131    },
      {41.99523181095994,  16.167884993214912,    0.050793115681800546   },
      {41.995197579324746, 16.167973907433755,    3.7001651742585295e-15 },
      {41.99523181095995,  16.167884993214912,    -0.050793115681792865  },
      {41.99533450385037,  16.167618252423836,    -0.1015855579813589    },
      {41.99550565195095,  16.167173690656668,    -0.152376653543988     },
      {41.99574524518717,  16.16655131723986,     -0.20316572906992192   },
      {41.99605326945649,  16.165751145229212,    -0.25395211134190215   },
      {41.9964297066296,   16.164773191408884,    -0.3047351272525707    },
      {41.99687453455297,  16.16361747628982,     -0.3555141038319971    },
      {41.99738772705079,  16.16228402410809,     -0.40628836827506576   },
      {41.997969253928666, 16.16077286282261,     -0.4570572479688795    },
      {41.99861908097632,  16.15908402411295,     -0.5078200705201866    },
      {41.99933716997197,  16.157217543376355,    -0.5585761637826662    },
      {42.00012347868664,  16.15517345972484,     -0.6093248558843278    },
      {42.00097796088885,  16.152951815981716,    -0.6600654752546709    },
      {42.001900566349775, 16.150552658677906,    -0.7107973506520323    },
      {42.002891240849394, 16.14797603804792,     -0.7615198111906891    },
      {42.00394992618217,  16.145222008025495,    -0.8122321863679965    },
      {42.0050765601639,   16.142290626238943,    -0.8629338060914962    },
      {42.00627107663884,  16.139181954006176,    -0.9136240007059184    },
      {42.00753340548704,  16.135896056329383,    -0.9643021010200817    },
      {42.008863472632534, 16.132433001889424,    -1.014967438333844     },
      {42.01026120005131,  16.12879286304002,     -1.0656193444648716    },
      {42.01172650578085,  16.12497571580128,     -1.1162571517754003    },
      {42.01325930392859,  16.120981639853433,    -1.1668801931988653    },
      {42.01485950468235,  16.116810718529727,    -1.2174878022664597    },
      {42.01652701431994,  16.11246303880953,     -1.2680793131336978    },
      {42.018261735220136, 16.10793869131058,     -1.3186540606067516    },
      {42.01982885941867,  16.103850112238497,    -1.362625783897011     },
      {42.02082428824698,  16.101252351010253,    -1.3897371481731526    },
      {42.02120528485336,  16.100257960936542,    -1.4000000000000004    },
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 1065;
    const double bs3_knots_cur2[] = {
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2640335949825785,
      -1.2637238670334754,
      -1.263215483489569,
      -1.2627071101650977,
      -1.2621987467081313,
      -1.26169039276197,
      -1.2611820479653228,
      -1.2606737119524851,
      -1.2601653843535185,
      -1.2596570647944343,
      -1.259148752897375,
      -1.2586404482808002,
      -1.258132150559672,
      -1.2576238593456424,
      -1.257115574247242,
      -1.2566072948700686,
      -1.2560990208169796,
      -1.2555907516882816,
      -1.255082487081925,
      -1.2545742265936957,
      -1.25406596981741,
      -1.2535577163451097,
      -1.2530494657672575,
      -1.252541217672933,
      -1.2520329716500294,
      -1.2515247272854506,
      -1.2510164841653086,
      -1.2505082418751217,
      -1.250000000000011,
      -1.2494917581249005,
      -1.2489835158347133,
      -1.2484752727145716,
      -1.2479670283499926,
      -1.247458782327089,
      -1.2469505342327645,
      -1.2464422836549123,
      -1.245934030182612,
      -1.2454257734063265,
      -1.2449175129180972,
      -1.2444092483117404,
      -1.2439009791830427,
      -1.2433927051299536,
      -1.2428844257527802,
      -1.2423761406543796,
      -1.2418678494403501,
      -1.241359551719222,
      -1.2408512471026472,
      -1.240342935205588,
      -1.2398346156465034,
      -1.239326288047537,
      -1.2388179520346991,
      -1.238309607238052,
      -1.237801253291891,
      -1.2372928898349242,
      -1.236784516510453,
      -1.2362761329665468,
      -1.2357677388562203,
      -1.2352593338376057,
      -1.2347509175741256,
      -1.234242489734662,
      -1.2337340499937248,
      -1.2332255980316178,
      -1.2327171335346014,
      -1.2322086561950565,
      -1.2317001657116415,
      -1.2311916617894523,
      -1.2306831441401753,
      -1.2301746124822421,
      -1.2296660665409778,
      -1.229157506048751,
      -1.2286489307451183,
      -1.2281403403769675,
      -1.2276317346986587,
      -1.2271231134721612,
      -1.2266144764671896,
      -1.2261058234613362,
      -1.225597154240201,
      -1.2250884685975187,
      -1.2245797663352826,
      -1.2240710472638676,
      -1.223562311202147,
      -1.2230535579776096,
      -1.222544787426472,
      -1.2220359993937897,
      -1.2215271937335614,
      -1.221018370308836,
      -1.2205095289918115,
      -1.2200006696639338,
      -1.2194917922159907,
      -1.2189828965482041,
      -1.2184739825703192,
      -1.2179650502016883,
      -1.2174560993713546,
      -1.2169471300181298,
      -1.2164381420906722,
      -1.2159291355475568,
      -1.2154201103573465,
      -1.214911066498658,
      -1.2144020039602246,
      -1.213892922740956,
      -1.2133838228499954,
      -1.2128747043067716,
      -1.2123655671410505,
      -1.2118564113929806,
      -1.2113472371131377,
      -1.2108380443625644,
      -1.2103288332128064,
      -1.2098196037459483,
      -1.209310356054642,
      -1.2088010902421358,
      -1.2082918064222963,
      -1.207782504719631,
      -1.207273185269305,
      -1.206763848217156,
      -1.2062544937197044,
      -1.2057451219441622,
      -1.205235733068437,
      -1.2047263272811342,
      -1.2042169047815554,
      -1.2037074657796938,
      -1.2031980104962259,
      -1.2026885391625013,
      -1.202179052020528,
      -1.2016695493229566,
      -1.2011600313330586,
      -1.2006504983247053,
      -1.2001409505823402,
      -1.199631388400951,
      -1.1991218120860376,
      -1.1986122219535762,
      -1.1981026183299834,
      -1.1975930015520746,
      -1.1970833719670204,
      -1.1965737299323014,
      -1.1960640758156584,
      -1.1955544099950417,
      -1.1950447328585554,
      -1.194535044804402,
      -1.1940253462408221,
      -1.1935156375860316,
      -1.1930059192681572,
      -1.1924961917251702,
      -1.1919864554048152,
      -1.1914767107645388,
      -1.1909669582714142,
      -1.1904571984020647,
      -1.1899474316425844,
      -1.189437658488456,
      -1.188927879444467,
      -1.1884180950246241,
      -1.1879083057520634,
      -1.1873985121589614,
      -1.186888714786442,
      -1.1863789141844807,
      -1.1858691109118094,
      -1.185359305535817,
      -1.184849498632448,
      -1.184339690786102,
      -1.1838298825895266,
      -1.1833200746437138,
      -1.18281026755779,
      -1.1823004619489075,
      -1.1817906584421323,
      -1.1812808576703313,
      -1.1807710602740582,
      -1.180261266901436,
      -1.1797514782080412,
      -1.1792416948567817,
      -1.1787319175177793,
      -1.1782221468682454,
      -1.1777123835923589,
      -1.17720262838114,
      -1.1766928819323268,
      -1.1761831449502451,
      -1.1756734181456823,
      -1.1751637022357568,
      -1.1746539979437878,
      -1.1741443059991636,
      -1.1736346271372096,
      -1.173124962099053,
      -1.17261531163149,
      -1.1721056764868498,
      -1.1715960574228588,
      -1.171086455202502,
      -1.1705768705938875,
      -1.170067304370106,
      -1.169557757309093,
      -1.1690482301934881,
      -1.1685387238104956,
      -1.1680292389517417,
      -1.167519776413135,
      -1.1670103369947236,
      -1.1665009215005526,
      -1.1659915307385218,
      -1.1654821655202416,
      -1.164972826660891,
      -1.164463514979072,
      -1.1639542312966675,
      -1.163444976438695,
      -1.1629357512331637,
      -1.1624265565109293,
      -1.1619173931055498,
      -1.16140826185314,
      -1.1608991635922268,
      -1.1603900991636054,
      -1.1598810694101926,
      -1.1593720751768846,
      -1.1588631173104103,
      -1.1583541966591868,
      -1.1578453140731773,
      -1.1573364704037439,
      -1.1568276665035062,
      -1.1563189032261958,
      -1.1558101814265143,
      -1.1553015019599888,
      -1.1547928656828306,
      -1.1542842734517913,
      -1.1537757261240222,
      -1.1532672245569318,
      -1.152758769608045,
      -1.152250362134862,
      -1.1517420029947192,
      -1.1512336930446483,
      -1.150725433141238,
      -1.1502172241404949,
      -1.149709066897707,
      -1.149200962267304,
      -1.1486929111027235,
      -1.1481849142562726,
      -1.1476769725789937,
      -1.1471690869205304,
      -1.1466612581289932,
      -1.1461534870508256,
      -1.1456457745306734,
      -1.1451381214112522,
      -1.1446305285332166,
      -1.1441229967350313,
      -1.1436155268528416,
      -1.1431081197203445,
      -1.1426007761686627,
      -1.142093497026218,
      -1.141586283118605,
      -1.1410791352684682,
      -1.140572054295377,
      -1.140065041015704,
      -1.1395580962425036,
      -1.1390512207853902,
      -1.138544415450421,
      -1.1380376810399746,
      -1.1375310183526361,
      -1.137024428183079,
      -1.1365179113219508,
      -1.1360114685557579,
      -1.1355051006667534,
      -1.134998808432824,
      -1.1344925926273801,
      -1.1339864540192446,
      -1.1334803933725457,
      -1.132974411446608,
      -1.1324685089958466,
      -1.131962686769662,
      -1.1314569455123356,
      -1.1309512859629267,
      -1.1304457088551716,
      -1.1299402149173814,
      -1.1294348048723442,
      -1.1289294794372262,
      -1.1284242393234747,
      -1.1279190852367218,
      -1.1274140178766916,
      -1.1269090379371045,
      -1.126404146105587,
      -1.1258993430635795,
      -1.1253946294862482,
      -1.1248900060423948,
      -1.1243854733943708,
      -1.1238810321979904,
      -1.1233766831024476,
      -1.1228724267502308,
      -1.122368263777042,
      -1.121864194811715,
      -1.1213602204761364,
      -1.1208563413851667,
      -1.1203525581465643,
      -1.1198488713609076,
      -1.1193452816215224,
      -1.1188417895144072,
      -1.1183383956181623,
      -1.1178351005039173,
      -1.117331904735264,
      -1.1168288088681848,
      -1.1163258134509895,
      -1.115822919024246,
      -1.1153201261207182,
      -1.1148174352653013,
      -1.114314846974961,
      -1.1138123617586717,
      -1.1133099801173576,
      -1.1128077025438337,
      -1.1123055295227502,
      -1.1118034615305354,
      -1.111301499035342,
      -1.1107996424969933,
      -1.1102978923669309,
      -1.1097962490881652,
      -1.1092947130952246,
      -1.1087932848141078,
      -1.1082919646622353,
      -1.1077907530484064,
      -1.107289650372751,
      -1.1067886570266885,
      -1.106287773392885,
      -1.1057869998452117,
      -1.1052863367487054,
      -1.1047857844595292,
      -1.1042853433249369,
      -1.1037850136832337,
      -1.1032847958637435,
      -1.102784690186774,
      -1.1022846969635838,
      -1.1017848164963508,
      -1.101285049078142,
      -1.1007853949928839,
      -1.1002858545153342,
      -1.0997864279110552,
      -1.0992871154363872,
      -1.098787917338424,
      -1.0982888338549899,
      -1.0977898652146156,
      -1.0972910116365182,
      -1.0967922733305804,
      -1.0962936504973309,
      -1.095795143327926,
      -1.0952967520041341,
      -1.0947984766983174,
      -1.0943003175734185,
      -1.0938022747829466,
      -1.0933043484709637,
      -1.0928065387720736,
      -1.0923088458114107,
      -1.0918112697046307,
      -1.091313810557902,
      -1.0908164684678978,
      -1.090319243521789,
      -1.0898221357972397,
      -1.089325145362402,
      -1.0888282722759126,
      -1.0883315165868892,
      -1.0878348783349305,
      -1.0873383575501148,
      -1.0868419542529995,
      -1.0863456684546235,
      -1.0858495001565096,
      -1.0853534493506658,
      -1.084857516019592,
      -1.0843617001362829,
      -1.0838660016642352,
      -1.0833704205574541,
      -1.082874956760461,
      -1.0823796102083023,
      -1.081884380826559,
      -1.0813892685313573,
      -1.0808942732293796,
      -1.0803993948178774,
      -1.0799046331846833,
      -1.0794099882082269,
      -1.0789154597575468,
      -1.0784210476923093,
      -1.077926751862823,
      -1.0774325721100564,
      -1.0769385082656568,
      -1.0764445601519683,
      -1.0759507275820528,
      -1.0754570103597092,
      -1.0749634082794959,
      -1.0744699211267528,
      -1.0739765486776236,
      -1.0734832906990808,
      -1.072990146948949,
      -1.0724971171759305,
      -1.072004201119632,
      -1.0715113985105906,
      -1.0710187090703018,
      -1.0705261325112478,
      -1.0700336685369256,
      -1.0695413168418781,
      -1.069049077111724,
      -1.0685569490231879,
      -1.068064932244134,
      -1.067573026433597,
      -1.0670812312418163,
      -1.0665895463102697,
      -1.0660979712717076,
      -1.0656065057501884,
      -1.0651151493611153,
      -1.064623901711271,
      -1.0641327623988568,
      -1.063641731013529,
      -1.0631508071364386,
      -1.0626599903402698,
      -1.0621692801892793,
      -1.061678676239337,
      -1.0611881780379682,
      -1.0606977851243926,
      -1.060207497029569,
      -1.059717313276236,
      -1.0592272333789574,
      -1.058737256844164,
      -1.0582473831701995,
      -1.057757611847365,
      -1.057267942357965,
      -1.056778374176353,
      -1.0562889067689787,
      -1.0557995395944348,
      -1.0553102721035053,
      -1.0548211037392137,
      -1.0543320339368714,
      -1.0538430621241273,
      -1.0533541877210184,
      -1.0528654101400188,
      -1.0523767287860917,
      -1.0518881430567404,
      -1.05139965234206,
      -1.0509112560247895,
      -1.0504229534803662,
      -1.0499347440769766,
      -1.0494466271756122,
      -1.0489586021301225,
      -1.0484706682872704,
      -1.0479828249867866,
      -1.047495071561426,
      -1.047007407337023,
      -1.0465198316325488,
      -1.0460323437601675,
      -1.0455449430252932,
      -1.0450576287266489,
      -1.0445704001563232,
      -1.0440832565998306,
      -1.043596197336168,
      -1.0431092216378768,
      -1.0426223287711003,
      -1.0421355179956453,
      -1.0416487885650416,
      -1.041162139726604,
      -1.0406755707214925,
      -1.0401890807847742,
      -1.0397026691454858,
      -1.0392163350266952,
      -1.0387300776455644,
      -1.038243896213413,
      -1.037757789935781,
      -1.0372717580124928,
      -1.036785799637721,
      -1.036299914000051,
      -1.0358141002825458,
      -1.0353283576628103,
      -1.0348426853130577,
      -1.0343570824001738,
      -1.0338715480857847,
      -1.0333860815263214,
      -1.0329006818730866,
      -1.0324153482723226,
      -1.0319300798652773,
      -1.0314448757882715,
      -1.0309597351727677,
      -1.0304746571454368,
      -1.0299896408282272,
      -1.029504685338432,
      -1.0290197897887594,
      -1.0285349532874006,
      -1.0280501749380988,
      -1.0275654538402192,
      -1.0270807890888192,
      -1.0265961797747165,
      -1.0261116249845617,
      -1.0256271238009065,
      -1.0251426753022754,
      -1.0246582785632368,
      -1.024173932654473,
      -1.0236896366428525,
      -1.023205389591501,
      -1.0227211905598725,
      -1.0222370386038222,
      -1.0217529327756778,
      -1.0212688721243124,
      -1.020784855695216,
      -1.0203008825305684,
      -1.019816951669313,
      -1.019333062147228,
      -1.0188492129970008,
      -1.018365403248301,
      -1.0178816319278532,
      -1.0173978980595115,
      -1.0169142006643326,
      -1.01643053876065,
      -1.0159469113641477,
      -1.0154633174879348,
      -1.0149797561426197,
      -1.0144962263363835,
      -1.0140127270750565,
      -1.0135292573621912,
      -1.0130458161991382,
      -1.0125624025851196,
      -1.0120790155173063,
      -1.0115956539908908,
      -1.011112316999164,
      -1.0106290035335896,
      -1.0101457125838804,
      -1.0096624431380727,
      -1.009179194182603,
      -1.0086959647023825,
      -1.0082127536808745,
      -1.0077295601001683,
      -1.0072463829410565,
      -1.0067632211831103,
      -1.006280073804756,
      -1.00579693978335,
      -1.0053138180952568,
      -1.004830707715923,
      -1.0043476076199562,
      -1.0038645167811981,
      -1.0033814341728033,
      -1.0028983587673146,
      -1.0024152895367395,
      -1.001932225452627,
      -1.0014491654861435,
      -1.0009661086081492,
      -1.0004830537892753,
      -1,
      -1,
      -1,
      -0.9995169462107246,
      -0.9990338913918508,
      -0.9985508345138566,
      -0.9980677745473732,
      -0.9975847104632605,
      -0.9971016412326855,
      -0.9966185658271968,
      -0.996135483218802,
      -0.9956523923800438,
      -0.9951692922840768,
      -0.9946861819047434,
      -0.9942030602166503,
      -0.9937199261952444,
      -0.9932367788168898,
      -0.9927536170589436,
      -0.9922704398998318,
      -0.9917872463191257,
      -0.9913040352976176,
      -0.9908208058173973,
      -0.9903375568619276,
      -0.9898542874161199,
      -0.9893709964664107,
      -0.9888876830008364,
      -0.9884043460091095,
      -0.9879209844826939,
      -0.9874375974148807,
      -0.9869541838008621,
      -0.9864707426378089,
      -0.9859872729249438,
      -0.9855037736636169,
      -0.985020243857381,
      -0.9845366825120655,
      -0.9840530886358527,
      -0.9835694612393505,
      -0.983085799335668,
      -0.9826021019404891,
      -0.9821183680721474,
      -0.9816345967516996,
      -0.9811507870029998,
      -0.9806669378527728,
      -0.9801830483306877,
      -0.9796991174694323,
      -0.9792151443047848,
      -0.9787311278756885,
      -0.9782470672243231,
      -0.9777629613961787,
      -0.9772788094401285,
      -0.9767946104085,
      -0.9763103633571485,
      -0.975826067345528,
      -0.9753417214367642,
      -0.9748573246977257,
      -0.9743728761990947,
      -0.9738883750154396,
      -0.9734038202252845,
      -0.972919210911182,
      -0.972434546159782,
      -0.9719498250619026,
      -0.9714650467126007,
      -0.9709802102112418,
      -0.9704953146615694,
      -0.9700103591717743,
      -0.9695253428545645,
      -0.9690402648272335,
      -0.9685551242117297,
      -0.968069920134724,
      -0.9675846517276787,
      -0.9670993181269146,
      -0.9666139184736801,
      -0.9661284519142167,
      -0.9656429175998277,
      -0.965157314686944,
      -0.9646716423371912,
      -0.9641858997174557,
      -0.9637000859999505,
      -0.9632142003622806,
      -0.9627282419875087,
      -0.9622422100642206,
      -0.9617561037865887,
      -0.9612699223544374,
      -0.9607836649733067,
      -0.9602973308545159,
      -0.9598109192152274,
      -0.9593244292785092,
      -0.9588378602733977,
      -0.95835121143496,
      -0.9578644820043565,
      -0.9573776712289015,
      -0.9568907783621251,
      -0.9564038026638337,
      -0.9559167434001713,
      -0.9554295998436786,
      -0.9549423712733532,
      -0.9544550569747089,
      -0.9539676562398347,
      -0.9534801683674532,
      -0.952992592662979,
      -0.9525049284385761,
      -0.9520171750132156,
      -0.9515293317127317,
      -0.9510413978698794,
      -0.9505533728243898,
      -0.9500652559230255,
      -0.949577046519636,
      -0.9490887439752126,
      -0.9486003476579423,
      -0.9481118569432618,
      -0.9476232712139104,
      -0.9471345898599832,
      -0.9466458122789836,
      -0.9461569378758747,
      -0.945667966063131,
      -0.9451788962607887,
      -0.9446897278964969,
      -0.9442004604055675,
      -0.9437110932310236,
      -0.9432216258236492,
      -0.9427320576420372,
      -0.9422423881526371,
      -0.9417526168298027,
      -0.9412627431558384,
      -0.9407727666210449,
      -0.9402826867237661,
      -0.9397925029704334,
      -0.9393022148756097,
      -0.9388118219620343,
      -0.9383213237606652,
      -0.9378307198107233,
      -0.9373400096597326,
      -0.9368491928635637,
      -0.9363582689864736,
      -0.9358672376011458,
      -0.9353760982887316,
      -0.9348848506388874,
      -0.9343934942498143,
      -0.9339020287282951,
      -0.9334104536897331,
      -0.9329187687581865,
      -0.9324269735664059,
      -0.931935067755869,
      -0.9314430509768148,
      -0.9309509228882789,
      -0.9304586831581246,
      -0.9299663314630774,
      -0.9294738674887552,
      -0.9289812909297009,
      -0.9284886014894124,
      -0.9279957988803711,
      -0.9275028828240727,
      -0.927009853051054,
      -0.9265167093009222,
      -0.9260234513223794,
      -0.9255300788732505,
      -0.9250365917205073,
      -0.924542989640294,
      -0.9240492724179504,
      -0.9235554398480349,
      -0.9230614917343466,
      -0.9225674278899468,
      -0.9220732481371804,
      -0.921578952307694,
      -0.9210845402424567,
      -0.9205900117917767,
      -0.9200953668153199,
      -0.9196006051821259,
      -0.9191057267706236,
      -0.9186107314686459,
      -0.9181156191734441,
      -0.9176203897917009,
      -0.9171250432395422,
      -0.9166295794425492,
      -0.9161339983357683,
      -0.9156382998637205,
      -0.9151424839804115,
      -0.9146465506493376,
      -0.914150499843494,
      -0.9136543315453797,
      -0.9131580457470039,
      -0.9126616424498887,
      -0.9121651216650729,
      -0.9116684834131144,
      -0.9111717277240909,
      -0.9106748546376014,
      -0.9101778642027638,
      -0.9096807564782147,
      -0.9091835315321057,
      -0.9086861894421016,
      -0.908188730295373,
      -0.9076911541885931,
      -0.9071934612279303,
      -0.9066956515290401,
      -0.9061977252170572,
      -0.9056996824265854,
      -0.9052015233016867,
      -0.9047032479958698,
      -0.9042048566720777,
      -0.903706349502673,
      -0.9032077266694234,
      -0.9027089883634857,
      -0.9022101347853883,
      -0.901711166145014,
      -0.9012120826615798,
      -0.9007128845636169,
      -0.9002135720889488,
      -0.8997141454846695,
      -0.89921460500712,
      -0.8987149509218619,
      -0.8982151835036531,
      -0.8977153030364201,
      -0.8972153098132298,
      -0.8967152041362603,
      -0.8962149863167703,
      -0.8957146566750671,
      -0.8952142155404745,
      -0.8947136632512985,
      -0.8942130001547922,
      -0.8937122266071189,
      -0.8932113429733154,
      -0.892710349627253,
      -0.8922092469515978,
      -0.8917080353377687,
      -0.8912067151858964,
      -0.8907052869047793,
      -0.8902037509118389,
      -0.8897021076330733,
      -0.8892003575030111,
      -0.8886985009646621,
      -0.8881965384694687,
      -0.8876944704772539,
      -0.8871922974561705,
      -0.8866900198826467,
      -0.8861876382413324,
      -0.8856851530250431,
      -0.8851825647347029,
      -0.8846798738792863,
      -0.8841770809757583,
      -0.8836741865490149,
      -0.8831711911318194,
      -0.8826680952647404,
      -0.882164899496087,
      -0.8816616043818422,
      -0.8811582104855971,
      -0.8806547183784821,
      -0.8801511286390968,
      -0.87964744185344,
      -0.8791436586148375,
      -0.878639779523868,
      -0.8781358051882894,
      -0.8776317362229623,
      -0.8771275732497734,
      -0.8766233168975566,
      -0.8761189678020138,
      -0.8756145266056338,
      -0.8751099939576095,
      -0.874605370513756,
      -0.8741006569364247,
      -0.8735958538944175,
      -0.8730909620628999,
      -0.8725859821233128,
      -0.8720809147632825,
      -0.8715757606765299,
      -0.8710705205627782,
      -0.8705651951276603,
      -0.8700597850826232,
      -0.869554291144833,
      -0.8690487140370778,
      -0.8685430544876691,
      -0.8680373132303425,
      -0.8675314910041578,
      -0.8670255885533966,
      -0.8665196066274589,
      -0.8660135459807601,
      -0.8655074073726247,
      -0.8650011915671807,
      -0.8644948993332515,
      -0.863988531444247,
      -0.8634820886780541,
      -0.8629755718169259,
      -0.8624689816473688,
      -0.8619623189600303,
      -0.861455584549584,
      -0.8609487792146147,
      -0.8604419037575016,
      -0.8599349589843011,
      -0.8594279457046282,
      -0.858920864731537,
      -0.8584137168814001,
      -0.8579065029737873,
      -0.8573992238313426,
      -0.8568918802796609,
      -0.8563844731471637,
      -0.855877003264974,
      -0.8553694714667889,
      -0.8548618785887534,
      -0.8543542254693319,
      -0.8538465129491798,
      -0.8533387418710123,
      -0.8528309130794749,
      -0.8523230274210117,
      -0.8518150857437329,
      -0.8513070888972819,
      -0.8507990377327013,
      -0.8502909331022985,
      -0.8497827758595102,
      -0.8492745668587675,
      -0.848766306955357,
      -0.848257997005286,
      -0.8477496378651432,
      -0.8472412303919603,
      -0.8467327754430735,
      -0.8462242738759831,
      -0.8457157265482141,
      -0.845207134317175,
      -0.8446984980400166,
      -0.8441898185734912,
      -0.8436810967738096,
      -0.8431723334964993,
      -0.8426635295962615,
      -0.8421546859268282,
      -0.8416458033408185,
      -0.8411368826895953,
      -0.8406279248231209,
      -0.8401189305898128,
      -0.8396099008364003,
      -0.8391008364077788,
      -0.8385917381468658,
      -0.8380826068944558,
      -0.8375734434890764,
      -0.8370642487668422,
      -0.8365550235613108,
      -0.8360457687033384,
      -0.8355364850209335,
      -0.8350271733391147,
      -0.834517834479764,
      -0.834008469261484,
      -0.8334990784994529,
      -0.832989663005282,
      -0.8324802235868707,
      -0.8319707610482641,
      -0.8314612761895102,
      -0.8309517698065173,
      -0.8304422426909126,
      -0.8299326956298997,
      -0.8294231294061184,
      -0.8289135447975038,
      -0.8284039425771472,
      -0.8278943235131561,
      -0.8273846883685161,
      -0.8268750379009532,
      -0.8263653728627964,
      -0.8258556940008421,
      -0.8253460020562182,
      -0.8248362977642493,
      -0.8243265818543236,
      -0.8238168550497608,
      -0.8233071180676792,
      -0.8227973716188659,
      -0.8222876164076474,
      -0.8217778531317607,
      -0.8212680824822268,
      -0.8207583051432246,
      -0.8202485217919652,
      -0.81973873309857,
      -0.819228939725948,
      -0.8187191423296749,
      -0.8182093415578741,
      -0.817699538051099,
      -0.8171897324422164,
      -0.8166799253562925,
      -0.8161701174104797,
      -0.8156603092139045,
      -0.8151505013675583,
      -0.8146406944641894,
      -0.814130889088197,
      -0.8136210858155256,
      -0.8131112852135645,
      -0.8126014878410448,
      -0.8120916942479429,
      -0.8115819049753823,
      -0.8110721205555393,
      -0.8105623415115505,
      -0.810052568357422,
      -0.8095428015979418,
      -0.8090330417285925,
      -0.8085232892354679,
      -0.8080135445951913,
      -0.8075038082748364,
      -0.8069940807318494,
      -0.8064843624139753,
      -0.8059746537591846,
      -0.8054649551956045,
      -0.8049552671414513,
      -0.8044455900049652,
      -0.8039359241843484,
      -0.8034262700677054,
      -0.8029166280329864,
      -0.8024069984479323,
      -0.8018973816700234,
      -0.8013877780464308,
      -0.8008781879139694,
      -0.8003686115990557,
      -0.7998590494176667,
      -0.7993495016753017,
      -0.7988399686669483,
      -0.7983304506770504,
      -0.797820947979479,
      -0.7973114608375058,
      -0.7968019895037811,
      -0.7962925342203132,
      -0.7957830952184517,
      -0.7952736727188732,
      -0.7947642669315705,
      -0.7942548780558452,
      -0.7937455062803028,
      -0.7932361517828512,
      -0.7927268147307023,
      -0.7922174952803765,
      -0.7917081935777112,
      -0.7911989097578718,
      -0.7906896439453653,
      -0.7901803962540592,
      -0.789671166787201,
      -0.7891619556374432,
      -0.7886527628868697,
      -0.7881435886070268,
      -0.7876344328589572,
      -0.787125295693236,
      -0.7866161771500123,
      -0.7861070772590516,
      -0.785597996039783,
      -0.7850889335013497,
      -0.784579889642661,
      -0.7840708644524509,
      -0.7835618579093355,
      -0.7830528699818778,
      -0.7825439006286532,
      -0.7820349497983194,
      -0.7815260174296886,
      -0.7810171034518038,
      -0.7805082077840174,
      -0.7799993303360742,
      -0.7794904710081964,
      -0.7789816296911719,
      -0.7784728062664465,
      -0.7779640006062182,
      -0.7774552125735357,
      -0.7769464420223984,
      -0.776437688797861,
      -0.7759289527361404,
      -0.7754202336647251,
      -0.7749115314024893,
      -0.7744028457598069,
      -0.7738941765386719,
      -0.7733855235328185,
      -0.7728768865278469,
      -0.7723682653013495,
      -0.7718596596230407,
      -0.77135106925489,
      -0.7708424939512573,
      -0.7703339334590306,
      -0.7698253875177663,
      -0.769316855859833,
      -0.768808338210556,
      -0.7682998342883669,
      -0.7677913438049521,
      -0.767282866465407,
      -0.7667744019683909,
      -0.7662659500062837,
      -0.7657575102653468,
      -0.7652490824258834,
      -0.7647406661624033,
      -0.7642322611437886,
      -0.7637238670334621,
      -0.7632154834895559,
      -0.7627071101650846,
      -0.762198746708118,
      -0.7616903927619568,
      -0.7611820479653099,
      -0.760673711952472,
      -0.7601653843535056,
      -0.7596570647944214,
      -0.7591487528973621,
      -0.7586404482807872,
      -0.7581321505596591,
      -0.7576238593456295,
      -0.7571155742472289,
      -0.7566072948700557,
      -0.7560990208169666,
      -0.755590751688269,
      -0.7550824870819124,
      -0.7545742265936829,
      -0.7540659698173973,
      -0.7535577163450972,
      -0.7530494657672451,
      -0.7525412176729205,
      -0.752032971650017,
      -0.7515247272854383,
      -0.7510164841652964,
      -0.7505082418751094,
      -0.7499999999999987,
      -0.7494917581248881,
      -0.7489835158347011,
      -0.7484752727145593,
      -0.7479670283499804,
      -0.7474587823270769,
      -0.7469505342327525,
      -0.7464422836549004,
      -0.7459340301826002,
      -0.7454257734063144,
      -0.7449175129180852,
      -0.7444092483117286,
      -0.7439009791830309,
      -0.7433927051299417,
      -0.7428844257527685,
      -0.742376140654368,
      -0.7418678494403385,
      -0.7413595517192103,
      -0.7408512471026354,
      -0.7403429352055761,
      -0.7398346156464919,
      -0.7393262880475254,
      -0.7388179520346876,
      -0.7383096072380406,
      -0.7378012532918794,
      -0.7372928898349128,
      -0.7367845165104416,
      -0.7362761329665353,
      -0.7359664050174322,
      -0.7359664050174322,
      -0.7359664050174322,
      -0.7359664050174322,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    SPAposition c_base_center_surf1_cur2(37, 0, 0);
    SPAunit_vector c_base_normal_surf1_cur2(1, 0, 0);
    SPAvector c_base_major_surf1_cur2(0, 0, -17.5);
    double c_base_ratio_surf1_cur2 = 1;
    ellipse c_base_surf1_cur2(c_base_center_surf1_cur2, c_base_normal_surf1_cur2, c_base_major_surf1_cur2, c_base_ratio_surf1_cur2);
    cone c_surf1_cur2(c_base_surf1_cur2, -0.25766265056033233, 0.9662349396012463);
    c_surf1_cur2.u_param_scale = 17.5;
    bs2_curve bs2_pcurve1_cur2 = nullptr;
    SPAposition c_base_center_surf2_cur2(0, 0, 7);
    SPAunit_vector c_base_normal_surf2_cur2(0, 0, 1);
    SPAvector c_base_major_surf2_cur2(45, 0, 0);
    double c_base_ratio_surf2_cur2 = 1;
    ellipse c_base_surf2_cur2(c_base_center_surf2_cur2, c_base_normal_surf2_cur2, c_base_major_surf2_cur2, c_base_ratio_surf2_cur2);
    cone c_surf2_cur2(c_base_surf2_cur2, 0, 1);
    c_surf2_cur2.u_param_scale = 45;
    bs2_curve bs2_pcurve2_cur2 = nullptr;
    intcurve ic_cur2(bs3_cur2, 1e-06, c_surf1_cur2, c_surf2_cur2, bs2_pcurve1_cur2, bs2_pcurve2_cur2);

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug84) {
    int bs3_degree_cur1 = 2;
    logical bs3_rational_cur1 = TRUE;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 3;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {-0.7396449704142012, -0.6923076923076924, 0},
      {-0.6863905325443787, -0.6153846153846155, 0},
      {-0.6449704142011833, -0.5384615384615387, 0},
    };
    const double bs3_weights_cur1[] = {
      1,
      1,
      1,
    };
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 6;
    const double bs3_knots_cur1[] = {
      0.15384615384615385, 0.15384615384615385, 0.15384615384615385, 0.23076923076923078, 0.23076923076923078, 0.23076923076923078,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    intcurve ic_cur1(ACIS_NEW exact_int_cur(bs3_cur1));

    int bs3_degree_cur2 = 2;
    logical bs3_rational_cur2 = TRUE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 3;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-0.6449704142011833, -0.5384615384615387,  0},
      {-0.603550295857988,  -0.4615384615384617,  0},
      {-0.57396449704142,   -0.38461538461538475, 0},
    };
    const double bs3_weights_cur2[] = {
      1,
      1,
      1,
    };
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 6;
    const double bs3_knots_cur2[] = {
      0.23076923076923078, 0.23076923076923078, 0.23076923076923078, 0.3076923076923077, 0.3076923076923077, 0.3076923076923077,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);
    judge(gme_inters, acis_inters);
}


TEST_F(NurbsNurbsIntrTest, TestBug87) {
    int bs3_degree_cur1 = 2;
    logical bs3_rational_cur1 = TRUE;
    logical bs3_closed_cur1 = FALSE;
    logical bs3_periodic_cur1 = FALSE;
    int bs3_num_ctrlpts_cur1 = 3;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {0,   0,                  0},
      {0.5, 0.4999999999999999, 0},
      {1,   0,                  0},
    };
    const double bs3_weights_cur1[] = {
      1,
      1,
      1,
    };
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 6;
    const double bs3_knots_cur1[] = {
      0, 0, 0, 1.118033988749895, 1.118033988749895, 1.118033988749895,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    intcurve ic_cur1(ACIS_NEW exact_int_cur(bs3_cur1));
    ic_cur1.limit({0, 1.118033988749895});

    int bs3_degree_cur2 = 2;
    logical bs3_rational_cur2 = TRUE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 3;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {0,                  0,                    0                   },
      {0.5031416838871369, 0.4937166322257261,   0.05560874930173676 },
      {0.9937166322257263, 0.012566735548547566, -0.11121749860347352},
    };
    const double bs3_weights_cur2[] = {
      1,
      1,
      1,
    };
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 6;
    const double bs3_knots_cur2[] = {
      0, 0, 0, 1.118033988749895, 1.118033988749895, 1.118033988749895,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));
    ic_cur2.limit({0, 1.118033988749895});

    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;
    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

    judge(gme_inters, acis_inters);
}

TEST_F(NurbsNurbsIntrTest, TestBug88) {
    int bs3_degree_cur1 = 2;
    logical bs3_rational_cur1 = FALSE;
    logical bs3_closed_cur1 = TRUE;
    logical bs3_periodic_cur1 = TRUE;
    int bs3_num_ctrlpts_cur1 = 9;
    const SPAposition bs3_ctrlpts_cur1[] = {
      {-0.00000000000000031, 0.00000000000000000,  0.00000000000000000},
      {-0.00000000000000031, 0.00000000000000031,  0.00000000000000000},
      {0.00000000000000000,  0.00000000000000031,  0.00000000000000000},
      {0.00000000000000031,  0.00000000000000031,  0.00000000000000000},
      {0.00000000000000031,  -0.00000000000000000, 0.00000000000000000},
      {0.00000000000000031,  -0.00000000000000031, 0.00000000000000000},
      {-0.00000000000000000, -0.00000000000000031, 0.00000000000000000},
      {-0.00000000000000031, -0.00000000000000031, 0.00000000000000000},
      {-0.00000000000000031, 0.00000000000000000,  0.00000000000000000},
    };
    const double bs3_weights_cur1[] = {
      1.00000000000000000, 0.70710678118654746, 1.00000000000000000, 0.70710678118654746, 1.00000000000000000, 0.70710678118654746, 1.00000000000000000, 0.70710678118654746, 1.00000000000000000,
    };
    double bs3_ctrlpt_tol_cur1 = 1e-06;
    int bs3_num_knots_cur1 = 12;
    const double bs3_knots_cur1[] = {
      0.00000000000000000, 0.00000000000000000, 0.00000000000000000, 1.57079632679489656, 1.57079632679489656, 3.14159265358979312,
      3.14159265358979312, 4.71238898038468967, 4.71238898038468967, 6.28318530717958623, 6.28318530717958623, 6.28318530717958623,
    };
    double bs3_knot_tol_cur1 = 1e-10;
    const int bs3_dimension_cur1 = 3;
    bs3_curve bs3_cur1 =
      bs3_curve_from_ctrlpts(bs3_degree_cur1, bs3_rational_cur1, bs3_closed_cur1, bs3_periodic_cur1, bs3_num_ctrlpts_cur1, bs3_ctrlpts_cur1, bs3_weights_cur1, bs3_ctrlpt_tol_cur1, bs3_num_knots_cur1, bs3_knots_cur1, bs3_knot_tol_cur1, bs3_dimension_cur1);
    intcurve ic_cur1(ACIS_NEW exact_int_cur(bs3_cur1));
    
    int bs3_degree_cur2 = 3;
    logical bs3_rational_cur2 = FALSE;
    logical bs3_closed_cur2 = FALSE;
    logical bs3_periodic_cur2 = FALSE;
    int bs3_num_ctrlpts_cur2 = 4;
    const SPAposition bs3_ctrlpts_cur2[] = {
      {-5.00000000000000000, 25.00000000000000000, 0.00000000000000000},
      {-1.66666666666654084, -8.33333333337407112, 0.00000000000000000},
      {1.66666666666654084,  -8.33333333337407112, 0.00000000000000000},
      {5.00000000000000000,  25.00000000000000000, 0.00000000000000000},
    };
    const double* bs3_weights_cur2 = nullptr;
    double bs3_ctrlpt_tol_cur2 = 1e-06;
    int bs3_num_knots_cur2 = 8;
    const double bs3_knots_cur2[] = {
      -5.00000000000000000, -5.00000000000000000, -5.00000000000000000, -5.00000000000000000, 5.00000000000000000, 5.00000000000000000, 5.00000000000000000, 5.00000000000000000,
    };
    double bs3_knot_tol_cur2 = 1e-10;
    const int bs3_dimension_cur2 = 3;
    bs3_curve bs3_cur2 =
      bs3_curve_from_ctrlpts(bs3_degree_cur2, bs3_rational_cur2, bs3_closed_cur2, bs3_periodic_cur2, bs3_num_ctrlpts_cur2, bs3_ctrlpts_cur2, bs3_weights_cur2, bs3_ctrlpt_tol_cur2, bs3_num_knots_cur2, bs3_knots_cur2, bs3_knot_tol_cur2, bs3_dimension_cur2);
    intcurve ic_cur2(ACIS_NEW exact_int_cur(bs3_cur2));
    
    curve_curve_int* acis_inters = nullptr;
    curve_curve_int* gme_inters = nullptr;

    acis_inters = int_cur_cur(ic_cur1, ic_cur2);
    gme_inters = answer_int_cur_cur(ic_cur1, ic_cur2);

        }