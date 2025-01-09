#include "acis/cucuint.hxx"

#include <math.h>

#include <algorithm>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "acis/acistol.hxx"
#include "acis/ckoutcom.hxx"
#include "acis/condef.hxx"
#include "acis/cstrapi.hxx"
#include "acis/curve_approx.hxx"
#include "acis/cusfint.hxx"
#include "acis/elldef.hxx"
#include "acis/errorbase.err"
#include "acis/exct_int.hxx"
#include "acis/geom_utl.hxx"
#include "acis/heldef.hxx"
#include "acis/intcucu.err"
#include "acis/intcusf.hxx"
#include "acis/intdef.hxx"
#include "acis/kernapi.hxx"
#include "acis/law.hxx"
#include "acis/math.hxx"
#include "acis/pladef.hxx"
#include "acis/sp2crtn.hxx"
#include "acis/spldef.hxx"
#include "acis/sps3crtn.hxx"
#include "acis/strdef.hxx"
#include "acis/tordef.hxx"
#include "acis/vec.hxx"
#include "acis/vector_utils.hxx"
#include "cucuint_util.hxx"

curve_curve_int* answer_int_cur_cur(curve const& c1, curve const& c2, SPAbox const& box, double tol) {
    return nullptr;
}
