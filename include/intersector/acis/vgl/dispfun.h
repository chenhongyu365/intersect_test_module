/*********************************************************************
 *                                                                   *
 *                          DevTools 1.8.0                           *
 *                                                                   *
 *  These coded instructions, statements and computer programs       *
 *  contain unpublished proprietary information of Tech Soft 3D,     *
 *  and are protected by Federal copyright law.  They may not be     *
 *  disclosed to third parties or copied or duplicated in any form,  *
 *  in whole or in part, without the prior written consent of        *
 *  Tech Soft 3D.                                                    *
 *                                                                   *
 *                 Copyright (C) 2023, Tech Soft 3D                  *
 *                                                                   *
 *********************************************************************/
 
#ifndef DISPFUN_DEF
#define DISPFUN_DEF
#include "base/basedefs.h"
#include "vgl/vgldefs.h"
#define DISPFUN_POINT 1
#define DISPFUN_LINE 2
#define DISPFUN_SCAN 3
#define DISPFUN_POINTCOLOR 4
#define DISPFUN_SCANCOLOR 5
#define DISPFUN_TRIANGLE 6
#define DISPFUN_POINTDATA 7
#define DISPFUN_SCANDATA 8
#define DISPFUN_TEXT 9
#define DISPFUN_POLYLINE 10
#define DISPFUN_POINTZCOLOR 11
#define DISPFUN_POINTZDATA 12
#define DISPFUN_POINTZ 13
#define DISPFUN_MAX 14
#define DISPFUN_APIPRINT 0
struct vgl_DispFun { Vint ierr;Vobject* obj;void (*fun[1])();
void (*point)(Vobject*,Vint,Vint);void (*line)(Vobject*,
Vint,Vint,Vint,Vint);void (*scan)(Vobject*,Vint,Vint,
Vint);void (*pointcolor)(Vobject*,Vint,Vint,Vfloat[4]);
void (*scancolor)(Vobject*,Vint,Vfloat[3],Vint,Vfloat[3],
Vint);void (*triangle)(Vobject*,Vint,Vint,Vint,Vint,
Vint,Vint);void (*pointdata)(Vobject*,Vint,Vint,Vint,
Vfloat*);void (*scandata)(Vobject*,Vint,Vint,Vfloat*,
Vint,Vfloat*,Vint);void (*text)(Vobject*,Vint,Vint,
Vtchar*);void (*polyline)(Vobject*,Vint,Vint[][2]);
void (*pointzcolor)(Vobject*,Vint,Vint,Vfloat,Vfloat[4]);
void (*pointzdata)(Vobject*,Vint,Vint,Vint,Vfloat,Vfloat*);
void (*pointz)(Vobject*,Vint,Vint,Vfloat);};
#ifdef __cplusplus
extern "C" { 
#endif
VKI_EXTERN vgl_DispFun* vgl_DispFunBegin(void);VKI_EXTERN
void vgl_DispFun_Construct(vgl_DispFun* p);VKI_EXTERN
void vgl_DispFunEnd(vgl_DispFun* p);VKI_EXTERN void
vgl_DispFun_Destruct(vgl_DispFun* p);VKI_EXTERN Vint
vgl_DispFunError(vgl_DispFun* p);VKI_EXTERN void vgl_DispFunInit(vgl_DispFun*
p);VKI_EXTERN void vgl_DispFunSet(vgl_DispFun* p,Vint
type,Vfunc* function);VKI_EXTERN void vgl_DispFunGet(vgl_DispFun*
p,Vint type,Vfunc** function);VKI_EXTERN void vgl_DispFunSetObj(vgl_DispFun*
p,Vobject* obj);VKI_EXTERN void vgl_DispFunGetObj(vgl_DispFun*
p,Vobject** obj);VKI_EXTERN void vgl_DispFunCopy(vgl_DispFun*
p,vgl_DispFun* fromp);VKI_EXTERN void vgl_DispFun0Point(Vobject*
object,Vint x,Vint y);VKI_EXTERN void vgl_DispFun0PointColor(Vobject*
object,Vint x,Vint y,Vfloat c[3]);VKI_EXTERN void vgl_DispFun0Line(Vobject*
object,Vint xa,Vint ya,Vint xb,Vint yb);VKI_EXTERN void
vgl_DispFun0Scan(Vobject* object,Vint xa,Vint xb,Vint
y);VKI_EXTERN void vgl_DispFun0ScanColor(Vobject* object,
Vint xa,Vfloat ca[3],Vint xb,Vfloat cb[3],Vint y);VKI_EXTERN
void vgl_DispFun0Triangle(Vobject* object,Vint xa,Vint
ya,Vint xb,Vint yb,Vint xc,Vint yc);VKI_EXTERN void
vgl_DispFun0PointData(Vobject* object,Vint nrws,Vint
x,Vint y,Vfloat* d);VKI_EXTERN void vgl_DispFun0ScanData(Vobject*
object,Vint nrws,Vint xa,Vfloat* da,Vint xb,Vfloat*
db,Vint y);VKI_EXTERN void vgl_DispFun0Text(Vobject*
object,Vint x,Vint y,Vtchar* string);VKI_EXTERN void
vgl_DispFun0PolyLine(Vobject* object,Vint npts,Vint
xy[][2]);VKI_EXTERN void vgl_DispFun0PointZColor(Vobject*
object,Vint x,Vint y,Vfloat z,Vfloat c[3]);VKI_EXTERN
void vgl_DispFun0PointZData(Vobject* object,Vint nrws,
Vint x,Vint y,Vfloat z,Vfloat* d);VKI_EXTERN void vgl_DispFun0PointZ(Vobject*
object,Vint x,Vint y,Vfloat z);VKI_EXTERN void vgl_DispFunAPI(vgl_DispFun*
p,Vint api);
#ifdef __cplusplus
}
#endif
#define vgl_DispFunObj(x)(x)->obj
#define vgl_DispFunPoint(x,a,b)(x)->point((x)->obj,\
(a),(b))
#define vgl_DispFunPointColor(x,a,b,c)(x)->pointcolor((x)->obj,\
(a),(b),(c))
#define vgl_DispFunLine(x,a,b,c,d)(x)->line((x)->obj,\
(a),(b),(c),(d))
#define vgl_DispFunScan(x,a,b,c)(x)->scan((x)->obj,\
(a),(b),(c))
#define vgl_DispFunScanColor(x,a,b,c,d,e)(x)->scancolor((x)->obj,\
(a),(b),(c),(d),(e))
#define vgl_DispFunTriangle(x,a,b,c,d,e,f)(x)->triangle((x)->obj,\
(a),(b),(c),(d),(e),(f))
#define vgl_DispFunPointData(x,a,b,c,d)(x)->pointdata((x)->obj,\
(a),(b),(c),(d))
#define vgl_DispFunScanData(x,a,b,c,d,e,f)(x)->scandata((x)->obj,\
(a),(b),(c),(d),(e),(f))
#define vgl_DispFunText(x,a,b,c)(x)->text((x)->obj,\
(a),(b),(c))
#define vgl_DispFunPolyLine(x,a,b)(x)->polyline((x)->obj,\
(a),(b))
#define vgl_DispFunPointZColor(x,a,b,c,d)(x)->pointzcolor((x)->obj,\
(a),(b),(c),(d))
#define vgl_DispFunPointZData(x,a,b,c,d,e)(x)->pointzdata((x)->obj,\
(a),(b),(c),(d),(e))
#define vgl_DispFunPointZ(x,a,b,c)(x)->pointz((x)->obj,\
(a),(b),(c))
#endif

