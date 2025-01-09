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
 
#ifndef DTEE_DEF
#define DTEE_DEF
#include "base/basedefs.h"
#include "vgl/drawfun.h"
struct vgl_DTee { Vint ierr;vgl_DrawFun* df;vgl_DrawFun*
dt;
#ifdef __cplusplus
public: VKI_EXTERN vgl_DTee(void);VKI_EXTERN void* operator
new(size_t);VKI_EXTERN ~vgl_DTee(void);VKI_EXTERN void
operator delete(void*);VKI_EXTERN Vint Error();VKI_EXTERN
void SetObject(Vint,Vobject*);VKI_EXTERN void DrawFun(vgl_DrawFun*);
#endif
};
#ifdef __cplusplus
extern "C" { 
#endif
VKI_EXTERN vgl_DTee* vgl_DTeeBegin(void);VKI_EXTERN
void vgl_DTee_Construct(vgl_DTee* p);VKI_EXTERN void
vgl_DTeeEnd(vgl_DTee* p);VKI_EXTERN void vgl_DTee_Destruct(vgl_DTee*
p);VKI_EXTERN Vint vgl_DTeeError(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeSetObject(vgl_DTee* p,Vint objecttype,
Vobject* object);VKI_EXTERN void vgl_DTeeXfmPush(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeXfmPop(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeXfmLoad(vgl_DTee* p,Vfloat xfm[4][4]);
VKI_EXTERN void vgl_DTeeXfmMult(vgl_DTee* p,Vfloat xfm[4][4]);
VKI_EXTERN void vgl_DTeeColorIndex(vgl_DTee* p,Vint
index);VKI_EXTERN void vgl_DTeeColor(vgl_DTee* p,Vfloat
c[3]);VKI_EXTERN void vgl_DTeeDataIndex(vgl_DTee* p,
Vint nprims,Vint nrws,Vint* index);VKI_EXTERN void vgl_DTeeData(vgl_DTee*
p,Vint nrws,Vfloat d[]);VKI_EXTERN void vgl_DTeeBackColorIndex(vgl_DTee*
p,Vint index);VKI_EXTERN void vgl_DTeeBackColor(vgl_DTee*
p,Vfloat c[3]);VKI_EXTERN void vgl_DTeeAttPush(vgl_DTee*
p,Vint mask);VKI_EXTERN void vgl_DTeeAttPop(vgl_DTee*
p);VKI_EXTERN void vgl_DTeePolygon(vgl_DTee* p,Vint
type,Vint npts,Vfloat x[][3],Vint vtflag,Vfloat vt[]);
VKI_EXTERN void vgl_DTeePolygonColor(vgl_DTee* p,Vint
type,Vint npts,Vfloat x[][3],Vfloat c[][3],Vint vtflag,
Vfloat vt[]);VKI_EXTERN void vgl_DTeePolygonDC(vgl_DTee*
p,Vint type,Vint npts,Vfloat x[3],Vint dc[][3]);VKI_EXTERN
void vgl_DTeePolygonData(vgl_DTee* p,Vint type,Vint
npts,Vfloat x[][3],Vint nrws,Vfloat d[],Vint vtflag,
Vfloat vt[]);VKI_EXTERN void vgl_DTeeLineStyle(vgl_DTee*
p,Vint lstyle);VKI_EXTERN void vgl_DTeeLineWidth(vgl_DTee*
p,Vint lwidth);VKI_EXTERN void vgl_DTeeTransIndex(vgl_DTee*
p,Vint index);VKI_EXTERN void vgl_DTeeTrans(vgl_DTee*
p,Vfloat trans);VKI_EXTERN void vgl_DTeeSpecularity(vgl_DTee*
p,Vfloat intensity,Vfloat shininess);VKI_EXTERN void
vgl_DTeeClip(vgl_DTee* p,Vint xmin,Vint xmax,Vint ymin,
Vint ymax);VKI_EXTERN void vgl_DTeeText(vgl_DTee* p,
Vfloat x[3],Vtchar* string);VKI_EXTERN void vgl_DTeeTextDC(vgl_DTee*
p,Vfloat x[3],Vint dc[3],Vtchar* string);VKI_EXTERN
void vgl_DTeePolyPoint(vgl_DTee* p,Vint npts,Vfloat
x[][3]);VKI_EXTERN void vgl_DTeePolyPointColor(vgl_DTee*
p,Vint npts,Vfloat x[][3],Vfloat c[][3]);VKI_EXTERN
void vgl_DTeePolyPointDC(vgl_DTee* p,Vint npts,Vfloat
x[3],Vint dc[][3]);VKI_EXTERN void vgl_DTeePolyPointData(vgl_DTee*
p,Vint npts,Vfloat x[][3],Vint nrws,Vfloat d[]);VKI_EXTERN
void vgl_DTeePolyLine(vgl_DTee* p,Vint type,Vint npts,
Vfloat x[][3]);VKI_EXTERN void vgl_DTeePolyLineColor(vgl_DTee*
p,Vint type,Vint npts,Vfloat x[][3],Vfloat c[][3]);
VKI_EXTERN void vgl_DTeePolyLineDC(vgl_DTee* p,Vint
type,Vint npts,Vfloat x[3],Vint dc[][3]);VKI_EXTERN
void vgl_DTeePolyLineData(vgl_DTee* p,Vint type,Vint
npts,Vfloat x[][3],Vint nrws,Vfloat d[]);VKI_EXTERN
void vgl_DTeeSetMode(vgl_DTee* p,Vint mode,Vint flag);
VKI_EXTERN void vgl_DTeeSetFactors(vgl_DTee* p,Vint
type,Vfloat factors[]);VKI_EXTERN void vgl_DTeePointSize(vgl_DTee*
p,Vint psize);VKI_EXTERN void vgl_DTeePositionWindow(vgl_DTee*
p,Vint xorig,Vint yorig,Vint xsize,Vint ysize);VKI_EXTERN
void vgl_DTeeVisualWindow(vgl_DTee* p,Vint visflag);
VKI_EXTERN void vgl_DTeeParentWindow(vgl_DTee* p,Vword
window);VKI_EXTERN void vgl_DTeeConfigureWindow(vgl_DTee*
p,Vint type,Vint* params);VKI_EXTERN void vgl_DTeeOpenWindow(vgl_DTee*
p,const Vchar* title);VKI_EXTERN void vgl_DTeeCloseWindow(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeConnectWindow(vgl_DTee* p,
Vword window);VKI_EXTERN void vgl_DTeeDisconnectWindow(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeSetWindow(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeQueryWindow(vgl_DTee* p,Vword* window);
VKI_EXTERN void vgl_DTeeClear(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeSwap(vgl_DTee* p);VKI_EXTERN void vgl_DTeeFlush(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeBell(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeDelay(vgl_DTee* p,Vfloat sec);VKI_EXTERN
void vgl_DTeeResize(vgl_DTee* p);VKI_EXTERN void vgl_DTeeGetMode(vgl_DTee*
p,Vint mode,Vint* flag);VKI_EXTERN void vgl_DTeeGetInteger(vgl_DTee*
p,Vint type,Vint* params);VKI_EXTERN void vgl_DTeeGetFloat(vgl_DTee*
p,Vint type,Vfloat* params);VKI_EXTERN void vgl_DTeeGetString(vgl_DTee*
p,Vint type,Vchar* params);VKI_EXTERN void vgl_DTeeFBufferRead(vgl_DTee*
p,Vint left,Vint right,Vint bottom,Vint top,Vobject*
fbuffer);VKI_EXTERN void vgl_DTeeFBufferWrite(vgl_DTee*
p,Vint left,Vint right,Vint bottom,Vint top,Vobject*
fbuffer);VKI_EXTERN void vgl_DTeeZBufferRead(vgl_DTee*
p,Vint left,Vint right,Vint bottom,Vint top,Vobject*
zbuffer);VKI_EXTERN void vgl_DTeeZBufferWrite(vgl_DTee*
p,Vint left,Vint right,Vint bottom,Vint top,Vobject*
zbuffer);VKI_EXTERN void vgl_DTeePixelmapCreate(vgl_DTee*
p,Vobject* pixelmap);VKI_EXTERN void vgl_DTeePixelmapDestroy(vgl_DTee*
p,Vobject* pixelmap);VKI_EXTERN void vgl_DTeePixelmapRead(vgl_DTee*
p,Vobject* pixelmap);VKI_EXTERN void vgl_DTeePixelmapWrite(vgl_DTee*
p,Vobject* pixelmap);VKI_EXTERN void vgl_DTeeClipPlane(vgl_DTee*
p,Vint index,Vfloat equation[4]);VKI_EXTERN void vgl_DTeeLight(vgl_DTee*
p,Vint index,Vint type,Vfloat c[3],Vfloat x[3]);VKI_EXTERN
void vgl_DTeeLightSwitch(vgl_DTee* p,Vint index,Vint
flag);VKI_EXTERN void vgl_DTeeLightModel(vgl_DTee* p,
Vint localviewer,Vfloat koffset,Vfloat krate);VKI_EXTERN
void vgl_DTeeSetSwitch(vgl_DTee* p,Vint type,Vint index,
Vint flag);VKI_EXTERN void vgl_DTeeProjOrtho(vgl_DTee*
p,Vfloat left,Vfloat right,Vfloat bottom,Vfloat top,
Vfloat nearz,Vfloat farz);VKI_EXTERN void vgl_DTeeProjFrustum(vgl_DTee*
p,Vfloat left,Vfloat right,Vfloat bottom,Vfloat top,
Vfloat nearz,Vfloat farz);VKI_EXTERN void vgl_DTeeProjPush(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeProjPop(vgl_DTee* p);VKI_EXTERN
void vgl_DTeeProjLoad(vgl_DTee* p,Vfloat xfm[4][4]);
VKI_EXTERN void vgl_DTeeViewport(vgl_DTee* p,Vint left,
Vint right,Vint bottom,Vint top);VKI_EXTERN void vgl_DTeeDepthRange(vgl_DTee*
p,Vfloat nearz,Vfloat farz);VKI_EXTERN void vgl_DTeePolygonOffset(vgl_DTee*
p,Vfloat factor,Vfloat bias);VKI_EXTERN void vgl_DTeePolygonMode(vgl_DTee*
p,Vint rend);VKI_EXTERN void vgl_DTeeTextPlane(vgl_DTee*
p,Vfloat path[3],Vfloat plane[3]);VKI_EXTERN void vgl_DTeeTextPixelSize(vgl_DTee*
p,Vfloat pixelsize);VKI_EXTERN void vgl_DTeeBitmapDefine(vgl_DTee*
p,Vint index,Vobject* bitmap);VKI_EXTERN void vgl_DTeeBitmapSelect(vgl_DTee*
p,Vint index);VKI_EXTERN void vgl_DTeeTextureDefine(vgl_DTee*
p,Vint index,Vobject* texture);VKI_EXTERN void vgl_DTeeTextureSelect(vgl_DTee*
p,Vint index);VKI_EXTERN void vgl_DTeeRasFontDefine(vgl_DTee*
p,Vint index,Vobject* rasfont);VKI_EXTERN void vgl_DTeeRasFontSelect(vgl_DTee*
p,Vint index);VKI_EXTERN void vgl_DTeePollMouse(vgl_DTee*
p,Vint* px,Vint* py,Vint* but1,Vint* but2,Vint* but3);
VKI_EXTERN void vgl_DTeeWarpMouse(vgl_DTee* p,Vint px,
Vint py);VKI_EXTERN void vgl_DTeeSetCursor(vgl_DTee*
p,Vint type);VKI_EXTERN void vgl_DTeePollModifiers(vgl_DTee*
p,Vint* cntl,Vint* shft);VKI_EXTERN void vgl_DTeeReadQueue(vgl_DTee*
p,Vint* dev,Vint* val);VKI_EXTERN void vgl_DTeeTestQueue(vgl_DTee*
p,Vint* dev);VKI_EXTERN void vgl_DTeeResetQueue(vgl_DTee*
p);VKI_EXTERN void vgl_DTeeRender(vgl_DTee* p,Vint type);
VKI_EXTERN void vgl_DTeeSelectRegion(vgl_DTee* p,Vint
type,Vint* params);VKI_EXTERN void vgl_DTeeSelectBuffer(vgl_DTee*
p,Vint size,Vint* indexlist,Vfloat* mindepth,Vfloat*
maxdepth);VKI_EXTERN void vgl_DTeeSelectQuery(vgl_DTee*
p,Vint* hits);VKI_EXTERN void vgl_DTeeExtentQuery(vgl_DTee*
p,Vfloat* lft,Vfloat* rgt,Vfloat* btm,Vfloat* top,Vfloat*
znear,Vfloat* zfar);VKI_EXTERN void vgl_DTeePolyPointArray(vgl_DTee*
p,Vint npts,Vfloat x[][3],Vint cflag,void* c,Vint vflag,
void* v,Vint tflag,Vfloat* t,Vint dflag,Vfloat* d);
VKI_EXTERN void vgl_DTeePolyLineArray(vgl_DTee* p,Vint
type,Vint npts,Vfloat x[][3],Vint cflag,void* c,Vint
vflag,void* v,Vint tflag,Vfloat* t,Vint dflag,Vfloat*
d);VKI_EXTERN void vgl_DTeePolygonArray(vgl_DTee* p,
Vint type,Vint npts,Vfloat x[][3],Vint cflag,void* c,
Vint vflag,void* v,Vint tflag,Vfloat* t,Vint dflag,
Vfloat* d);VKI_EXTERN void vgl_DTeePolyArray(vgl_DTee*
p,Vint type,Vint npts,Vfloat x[][3],Vint cflag,void*
c,Vint vflag,void* v,Vint tflag,Vfloat* t,Vint dflag,
Vfloat* d);VKI_EXTERN void vgl_DTeeInitBuffer(vgl_DTee*
p,Vint size,Vint* vboid);VKI_EXTERN void vgl_DTeeTermBuffer(vgl_DTee*
p,Vint vboid);VKI_EXTERN void vgl_DTeeCopyBuffer(vgl_DTee*
p,Vint vboid,Vint npts,Vfloat x[][3],Vint cflag,void*
c,Vint vflag,void* v,Vint tflag,Vfloat* t,Vint dflag,
Vfloat* d,Vint* offset);VKI_EXTERN void vgl_DTeeCopyElemBuffer(vgl_DTee*
p,Vint vboid,Vint npts,Vuint* ix,Vint* offset);VKI_EXTERN
void vgl_DTeePolyPointBuffer(vgl_DTee* p,Vint vboid,
Vint offset,Vint npts,Vint cflag,Vint vflag,Vint tflag,
Vint dflag);VKI_EXTERN void vgl_DTeePolyLineBuffer(vgl_DTee*
p,Vint vboid,Vint offset,Vint type,Vint npts,Vint cflag,
Vint vflag,Vint tflag,Vint dflag);VKI_EXTERN void vgl_DTeePolygonBuffer(vgl_DTee*
p,Vint vboid,Vint offset,Vint type,Vint npts,Vint cflag,
Vint vflag,Vint tflag,Vint dflag);VKI_EXTERN void vgl_DTeePolyBuffer(vgl_DTee*
p,Vint vboid,Vint offset,Vint type,Vint npts,Vint cflag,
Vint vflag,Vint tflag,Vint dflag);VKI_EXTERN void vgl_DTeePolyElemArray(vgl_DTee*
p,Vint type,Vint npts,Vuint ix[],Vfloat x[][3],Vint
cflag,void* c,Vint vflag,void* v,Vint tflag,Vfloat*
t,Vint dflag,Vfloat* d);VKI_EXTERN void vgl_DTeePolyElemBuffer(vgl_DTee*
p,Vint elemvboid,Vint elemoffset,Vint vboid,Vint offset,
Vint type,Vint npts,Vint cflag,Vint vflag,Vint tflag,
Vint dflag);VKI_EXTERN void vgl_DTeeDrawFun(vgl_DTee*
p,vgl_DrawFun* df);
#ifdef __cplusplus
}
#endif
#endif

