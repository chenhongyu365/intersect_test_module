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

#ifndef DFILE_DEF
#define DFILE_DEF
#include <math.h>
#include <stdio.h>

#include "base/basedefs.h"
#include "vgl/attstack.h"
#include "vgl/bitmap.h"
#include "vgl/dispfun.h"
#include "vgl/drawfun.h"
#include "vgl/fbuffer.h"
#include "vgl/rasfont.h"
#include "vgl/texture.h"
#include "vgl/vgldefs.h"
#include "vgl/vglweb3d.h"
#include "vgl/xfm.h"
#include "vgl/xfmstack.h"
#include "vgl/zbuffer.h"
#define DFILE_UNITPRECISION 0
#define DFILE_UNITPRECISION_DEFAULT 0
#define DFILE_UNITPRECISION_SINGLE9 1
#define DFILE_UNITPRECISION_SINGLE7 2
#define DFILE_NATIVEVERSION 1
#define DFILE_CLOSE -2
#define DFILE_UNKNOWN -1
#define DFILE_ASCII 0
#define DFILE_BINARY 1
#define DFILE_VRML 4
#define DFILE_APIPRINT 5
#define DFILE_STL_ASCII 6
#define DFILE_JTPART 7
#define DFILE_JT 8
#define DFILE_OBJ 10
#define DFILE_X3D 11
#define DFILE_DAE 12
struct vgl_DFile {
    Vint ierr;
    Vint filetype;
    Vint filevers;
    Vint uservers;
    Vchar filename[256];
    Vchar assemblyname[256];
    FILE* fd;
    FILE* fdm;
    Vint byteswap;
    vgl_DrawFun* df;
    Vint funfrequency;
    Vfunc2* fun;
    Vobject* funobject;
    long setpos;
    long curpos;
    Vint unitprecision;
    Vint wxpix, wypix;
    void* jt;
    vsy_HashTable* rasfonthash;
    vsy_HashTable* texturehash;
    vsy_HashTable* bitmaphash;
    Vint abortflag;
    Vint mpts;
    Vfloat (*xx)[3];
    void* cx;
    void* vx;
    Vfloat* tx;
    Vfloat* dx;
    void* px;
    Vuint* ix;
    Vint gpts;
    Vfloat (*xxg)[3];
    void* cxg;
    void* vxg;
    Vfloat* txg;
    Vfloat* dxg;
    Vint fpts;
    Vfloat (*c3f)[3];
    Vfloat (*c4f)[4];
    Vfloat* vtf;
    Vint mprims;
    Vint* di;
    vgl_DrawFun* drawfun;
    vgl_Attstack* attstack;
    vgl_Web3D* web3d;
    float transp;
    Vint pointsize;
    Vint pointstyle;
    Vint linestyle;
    Vint linewidth;
    float intensity, shininess;
    float forecrgb[4];
    int pxmn, pxmx, pymn, pymx;
    float fzmn, fzmx;
    Vuint rgba;
    vsy_IntDict* mtldict;
#ifdef __cplusplus

  public:
    VKI_EXTERN vgl_DFile(void);
    VKI_EXTERN void* operator new(size_t);
    VKI_EXTERN ~vgl_DFile(void);
    VKI_EXTERN
    void operator delete(void*);
    VKI_EXTERN Vint Error();
    VKI_EXTERN void SetObject(Vint, Vobject*);
    VKI_EXTERN
    void SetFunction(Vint, VDFilefunc*, Vobject*);
    VKI_EXTERN
    void Abort();
    VKI_EXTERN void SetParami(Vint, Vint);
    VKI_EXTERN
    void SetPosition(long);
    VKI_EXTERN void CurPosition(long*);
    VKI_EXTERN void SetWindowSize(Vint, Vint);
    VKI_EXTERN
    void GetWindowSize(Vint*, Vint*);
    VKI_EXTERN void Open();
    VKI_EXTERN void Close();
    VKI_EXTERN void Read();
    VKI_EXTERN
    void ReadFileType(Vint*);
    VKI_EXTERN void SetFileType(Vint);
    VKI_EXTERN void SetFileName(Vchar*);
    VKI_EXTERN void SetJTAssemblyName(Vchar*);
    VKI_EXTERN void GetFileType(Vint*);
    VKI_EXTERN void GetFileName(Vchar[]);
    VKI_EXTERN void OpenJTPart(Vobject*);
    VKI_EXTERN void CloseJTPart();
    VKI_EXTERN void PolyPointBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolyLineBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolygonBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolyArray(Vint, Vint, Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN
    void PolyBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void PolyElemArray(Vint, Vint, Vuint[], Vfloat[][3], Vint, void*, Vint, void*, Vint, Vfloat*, Vint, Vfloat*);
    VKI_EXTERN void PolyElemBuffer(Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint, Vint);
    VKI_EXTERN void DrawFun(vgl_DrawFun*);
#endif
};
#ifdef __cplusplus
extern "C" {
#endif
VKI_EXTERN vgl_DFile* vgl_DFileBegin(void);
VKI_EXTERN
void vgl_DFile_Construct(vgl_DFile* p);
VKI_EXTERN void vgl_DFileEnd(vgl_DFile* p);
VKI_EXTERN void vgl_DFile_Destruct(vgl_DFile* p);
VKI_EXTERN Vint vgl_DFileError(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileSetObject(vgl_DFile* p, Vint objecttype, Vobject* object);
VKI_EXTERN void vgl_DFileSetFunction(vgl_DFile* p, Vint frequency, VDFilefunc* function, Vobject* object);
VKI_EXTERN void vgl_DFileAbort(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileSetParami(vgl_DFile* p, Vint type, Vint iparam);
VKI_EXTERN void vgl_DFileSetPosition(vgl_DFile* p, long pos);
VKI_EXTERN void vgl_DFileCurPosition(vgl_DFile* p, long* pos);
VKI_EXTERN void vgl_DFileSetWindowSize(vgl_DFile* p, Vint wxpix, Vint wypix);
VKI_EXTERN void vgl_DFileGetWindowSize(vgl_DFile* p, Vint* wxpix, Vint* wypix);
VKI_EXTERN void vgl_DFileOpen(vgl_DFile* p);
VKI_EXTERN void vgl_DFileClose(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileRead(vgl_DFile* p);
VKI_EXTERN void vgl_DFileReadFileType(vgl_DFile* p, Vint* filetype);
VKI_EXTERN void vgl_DFileSetFileType(vgl_DFile* p, Vint filetype);
VKI_EXTERN void vgl_DFileSetFileName(vgl_DFile* p, Vchar* filename);
VKI_EXTERN void vgl_DFileSetJTAssemblyName(vgl_DFile* p, Vchar* name);
VKI_EXTERN void vgl_DFileGetFileType(vgl_DFile* p, Vint* filetype);
VKI_EXTERN void vgl_DFileGetFileName(vgl_DFile* p, Vchar filename[]);
VKI_EXTERN void vgl_DFileOpenJTPart(vgl_DFile* p, Vobject* part);
VKI_EXTERN void vgl_DFileCloseJTPart(vgl_DFile* p);
VKI_EXTERN void vgl_DFileColorIndex(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileColor(vgl_DFile* p, Vfloat c[3]);
VKI_EXTERN void vgl_DFileTransIndex(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileTrans(vgl_DFile* p, Vfloat transp);
VKI_EXTERN void vgl_DFileSpecularity(vgl_DFile* p, Vfloat intensity, Vfloat shininess);
VKI_EXTERN void vgl_DFileSetMode(vgl_DFile* p, Vint mode, Vint flag);
VKI_EXTERN void vgl_DFileSetFactors(vgl_DFile* p, Vint type, Vfloat factors[]);
VKI_EXTERN void vgl_DFilePointSize(vgl_DFile* p, Vint psize);
VKI_EXTERN void vgl_DFilePointStyle(vgl_DFile* p, Vint pstyle);
VKI_EXTERN void vgl_DFileLineStyle(vgl_DFile* p, Vint lstyle);
VKI_EXTERN void vgl_DFileLineWidth(vgl_DFile* p, Vint lwidth);
VKI_EXTERN void vgl_DFilePolyPoint(vgl_DFile* p, Vint npts, Vfloat x[][3]);
VKI_EXTERN void vgl_DFilePolyPointColor(vgl_DFile* p, Vint npts, Vfloat x[][3], Vfloat c[][3]);
VKI_EXTERN
void vgl_DFilePolyPointArray(vgl_DFile* p, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN
void vgl_DFilePolyPointBuffer(vgl_DFile* p, Vint vboid, Vint offset, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void vgl_DFilePolyPointDC(vgl_DFile* p, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN void vgl_DFilePolyPointData(vgl_DFile* p, Vint npts, Vfloat x[][3], Vint nrws, Vfloat* d);
VKI_EXTERN void vgl_DFilePolyLine(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3]);
VKI_EXTERN void vgl_DFilePolyLineColor(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vfloat c[][3]);
VKI_EXTERN void vgl_DFilePolyLineArray(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void vgl_DFilePolyLineBuffer(vgl_DFile* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void vgl_DFilePolyLineDC(vgl_DFile* p, Vint closedflag, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN void vgl_DFilePolyLineData(vgl_DFile* p, Vint closedflag, Vint npts, Vfloat x[][3], Vint nrws, Vfloat* d);
VKI_EXTERN void vgl_DFilePolygon(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vint vtflag, Vfloat vt[]);
VKI_EXTERN void vgl_DFilePolygonColor(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vfloat c[][3], Vint vtflag, Vfloat vt[]);
VKI_EXTERN void vgl_DFilePolygonArray(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void vgl_DFilePolygonBuffer(vgl_DFile* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void vgl_DFilePolygonDC(vgl_DFile* p, Vint type, Vint npts, Vfloat x[3], Vint dc[][3]);
VKI_EXTERN
void vgl_DFilePolygonData(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vint nrws, Vfloat* d, Vint vtflag, Vfloat vt[]);
VKI_EXTERN void vgl_DFilePolyArray(vgl_DFile* p, Vint type, Vint npts, Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void vgl_DFilePolyBuffer(vgl_DFile* p, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void vgl_DFilePolyElemArray(vgl_DFile* p, Vint type, Vint npts, Vuint ix[], Vfloat x[][3], Vint cflag, void* c, Vint vflag, void* v, Vint tflag, Vfloat* t, Vint dflag, Vfloat* d);
VKI_EXTERN void vgl_DFilePolyElemBuffer(vgl_DFile* p, Vint elemvboid, Vint elemoffset, Vint vboid, Vint offset, Vint type, Vint npts, Vint cflag, Vint vflag, Vint tflag, Vint dflag);
VKI_EXTERN void vgl_DFileText(vgl_DFile* p, Vfloat x[3], Vtchar* string);
VKI_EXTERN void vgl_DFileTextDC(vgl_DFile* p, Vfloat x[3], Vint dc[3], Vtchar* string);
VKI_EXTERN
void vgl_DFileDataIndex(vgl_DFile* p, Vint nprims, Vint nrws, Vint* index);
VKI_EXTERN void vgl_DFileData(vgl_DFile* p, Vint nrws, Vfloat* d);
VKI_EXTERN void vgl_DFileAttPush(vgl_DFile* p, Vint mask);
VKI_EXTERN void vgl_DFileAttPop(vgl_DFile* p);
VKI_EXTERN void vgl_DFileXfmPush(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileXfmPop(vgl_DFile* p);
VKI_EXTERN void vgl_DFileXfmLoad(vgl_DFile* p, Vfloat t[4][4]);
VKI_EXTERN void vgl_DFileXfmMult(vgl_DFile* p, Vfloat t[4][4]);
VKI_EXTERN void vgl_DFileClip(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top);
VKI_EXTERN
void vgl_DFileBitmapSelect(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileTextureSelect(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileRasFontSelect(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileLight(vgl_DFile* p, Vint index, Vint type, Vfloat c[3], Vfloat x[3]);
VKI_EXTERN
void vgl_DFileClipPlane(vgl_DFile* p, Vint index, Vfloat eqn[4]);
VKI_EXTERN void vgl_DFileSetSwitch(vgl_DFile* p, Vint type, Vint index, Vint flag);
VKI_EXTERN void vgl_DFilePositionWindow(vgl_DFile* p, Vint xorig, Vint yorig, Vint xsize, Vint ysize);
VKI_EXTERN
void vgl_DFileVisualWindow(vgl_DFile* p, Vint visflag);
VKI_EXTERN void vgl_DFileParentWindow(vgl_DFile* p, Vword parent);
VKI_EXTERN void vgl_DFileConfigureWindow(vgl_DFile* p, Vint type, Vint* params);
VKI_EXTERN void vgl_DFileOpenWindow(vgl_DFile* p, const Vchar* title);
VKI_EXTERN void vgl_DFileCloseWindow(vgl_DFile* p);
VKI_EXTERN void vgl_DFileConnectWindow(vgl_DFile* p, Vword window);
VKI_EXTERN void vgl_DFileDisconnectWindow(vgl_DFile* p);
VKI_EXTERN void vgl_DFileSetWindow(vgl_DFile* p);
VKI_EXTERN void vgl_DFileQueryWindow(vgl_DFile* p, Vword* window);
VKI_EXTERN void vgl_DFileClear(vgl_DFile* p);
VKI_EXTERN void vgl_DFileSwap(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileFlush(vgl_DFile* p);
VKI_EXTERN void vgl_DFileBell(vgl_DFile* p);
VKI_EXTERN void vgl_DFileDelay(vgl_DFile* p, Vfloat sec);
VKI_EXTERN void vgl_DFileResize(vgl_DFile* p);
VKI_EXTERN void vgl_DFileBackColorIndex(vgl_DFile* p, Vint index);
VKI_EXTERN void vgl_DFileBackColor(vgl_DFile* p, float c[3]);
VKI_EXTERN void vgl_DFileGetMode(vgl_DFile* p, Vint mode, Vint* flag);
VKI_EXTERN void vgl_DFileGetInteger(vgl_DFile* p, Vint type, Vint* params);
VKI_EXTERN void vgl_DFileGetFloat(vgl_DFile* p, Vint type, Vfloat* params);
VKI_EXTERN void vgl_DFileGetString(vgl_DFile* p, Vint type, Vchar* params);
VKI_EXTERN void vgl_DFileFBufferRead(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top, Vobject* fbuffer);
VKI_EXTERN void vgl_DFileFBufferWrite(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top, Vobject* fbuffer);
VKI_EXTERN void vgl_DFileZBufferRead(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top, Vobject* zbuffer);
VKI_EXTERN void vgl_DFileZBufferWrite(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top, Vobject* zbuffer);
VKI_EXTERN void vgl_DFilePixelmapCreate(vgl_DFile* p, Vobject* pixelmap);
VKI_EXTERN void vgl_DFilePixlemapDestroy(vgl_DFile* p, Vobject* pixelmap);
VKI_EXTERN void vgl_DFilePixelmapRead(vgl_DFile* p, Vobject* pixelmap);
VKI_EXTERN void vgl_DFilePixelmapWrite(vgl_DFile* p, Vobject* pixelmap);
VKI_EXTERN void vgl_DFileLightSwitch(vgl_DFile* p, Vint index, Vint flag);
VKI_EXTERN void vgl_DFileLightModel(vgl_DFile* p, Vint local, Vfloat koffset, Vfloat krate);
VKI_EXTERN
void vgl_DFileProjOrtho(vgl_DFile* p, Vfloat left, Vfloat right, Vfloat bottom, Vfloat top, Vfloat nearz, Vfloat farz);
VKI_EXTERN void vgl_DFileProjFrustum(vgl_DFile* p, Vfloat left, Vfloat right, Vfloat bottom, Vfloat top, Vfloat nearz, Vfloat farz);
VKI_EXTERN void vgl_DFileProjPush(vgl_DFile* p);
VKI_EXTERN void vgl_DFileProjPop(vgl_DFile* p);
VKI_EXTERN
void vgl_DFileProjLoad(vgl_DFile* p, Vfloat t[4][4]);
VKI_EXTERN void vgl_DFileViewport(vgl_DFile* p, Vint left, Vint right, Vint bottom, Vint top);
VKI_EXTERN void vgl_DFileDepthRange(vgl_DFile* p, Vfloat nearz, Vfloat farz);
VKI_EXTERN void vgl_DFilePolygonOffset(vgl_DFile* p, Vfloat factor, Vfloat bias);
VKI_EXTERN void vgl_DFilePolygonMode(vgl_DFile* p, Vint rend);
VKI_EXTERN void vgl_DFileTextPlane(vgl_DFile* p, Vfloat path[3], Vfloat plane[3]);
VKI_EXTERN void vgl_DFileTextPixelSize(vgl_DFile* p, Vfloat pixelsize);
VKI_EXTERN void vgl_DFileBitmapDefine(vgl_DFile* p, Vint index, vgl_Bitmap* bitmap);
VKI_EXTERN void vgl_DFileTextureDefine(vgl_DFile* p, Vint index, vgl_Texture* texture);
VKI_EXTERN void vgl_DFileRasFontDefine(vgl_DFile* p, Vint index, vgl_RasFont* rasfont);
VKI_EXTERN void vgl_DFilePollMouse(vgl_DFile* p, Vint* px, Vint* py, Vint* but1, Vint* but2, Vint* but3);
VKI_EXTERN void vgl_DFilePollModifiers(vgl_DFile* p, Vint* cntl, Vint* shft);
VKI_EXTERN void vgl_DFileWarpMouse(vgl_DFile* p, Vint px, Vint py);
VKI_EXTERN void vgl_DFileSetCursor(vgl_DFile* p, Vint type);
VKI_EXTERN void vgl_DFileReadQueue(vgl_DFile* p, Vint* dev, Vint* val);
VKI_EXTERN void vgl_DFileTestQueue(vgl_DFile* p, Vint* dev);
VKI_EXTERN void vgl_DFileResetQueue(vgl_DFile* p);
VKI_EXTERN void vgl_DFileRender(vgl_DFile* p, Vint type);
VKI_EXTERN void vgl_DFileSelectRegion(vgl_DFile* p, Vint type, Vint* params);
VKI_EXTERN void vgl_DFileSelectBuffer(vgl_DFile* p, Vint size, Vint* indexlist, Vfloat* mindepth, Vfloat* maxdepth);
VKI_EXTERN void vgl_DFileSelectQuery(vgl_DFile* p, Vint* hits);
VKI_EXTERN void vgl_DFileExtentQuery(vgl_DFile* p, Vfloat* lft, Vfloat* rgt, Vfloat* btm, Vfloat* top, Vfloat* znear, Vfloat* zfar);
VKI_EXTERN void vgl_DFileBufferSize(vgl_DFile* p, Vint xsize, Vint ysize);
VKI_EXTERN void vgl_DFileDrawFun(vgl_DFile* p, vgl_DrawFun* df);
#ifdef __cplusplus
}
#endif
#endif
