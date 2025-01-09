/**
 * @fullReview  HCN 02:09:04
 */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************
/* -*-c++-*- */
//=============================================================================
//
// Implementation generique d'une hash table avec gestion des adresses > 2 Go
//
// NE PAS INSTANCER DIRECTEMENT CETTE CLASSE
//
// Cette classe permet de deriver des classes qui definissent
// elles-meme la taille statiquement pre-reservee de _StaticBuckets.
//
// Voir CATCGMHashTable et CATCGMHashTableTiny pour des exemples 
// de classes derivees
//
//=============================================================================
// Sep. 02 Creation                                                       HCN
// Feb. 05 void* Next(int& ioNumBucket, int& ioPos) const;                HCN
//=============================================================================

#ifndef  CATCGMHashTableBase_h
#define  CATCGMHashTableBase_h

#include "CATIACGMLevel.h"
#include "CATDataType.h"
#include "CATMathematics.h"
#include <stdio.h>
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

// #define CATCGM_DEFAULT_HASH_TABLE_DIMENSION 31

typedef unsigned int (*PFHASHKEYFUNCTION)(void*) ;
typedef int	         (*PFCOMPAREFUNCTION)(void*, void*);	

class ExportedByCATMathematics CATCGMHashTableBase : public CATCGMVirtual
{
public:

  CATCGMHashTableBase(size_t            iDefault_Size,
                      CATULONGPTR*      ipStaticBuckets,  // _StaticBuckets of derived class
                      int               iEstimatedSize = 0,
                      PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                      PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTableBase();

  int           Insert(void* ipElem);

  void*         Locate(void* ipElem) const;
  int           LocateReturnPos(void* ipElem) const;

  void*         KeyLocate(unsigned int iKey) const;

  INLINE void*  Get(int iPos) const;
  INLINE void*  operator[](int iPos) const;

  void*         Next(void* ipElem) const;
  void*         Next(int& ioNumBucket, int& ioPos) const;

  int           Remove(void* ipElem);
  int           RemoveReturnPos(void* ipElem);

  void          RemoveAll();


  INLINE int    Size() const;


  void          PrintStats() const;

  static int UpToNiceModulo(int iNum);

  // Methodes par defaut
  static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2); // This function returns 0 if both instance of the table are equal

protected :

  PFHASHKEYFUNCTION	_pHashKeyFunction;
  PFCOMPAREFUNCTION	_pCompareFunction;

  int          _NbAllocatedBuckets; // Dimension of the hashtab (maximum number of buckets to be stored in the Hashtable)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Par defaut, un bucket est un CATULONGPTR
  // CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (93 = 3 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 
  CATULONGPTR* _pStaticBuckets;

  int          _NbFreeBuckets;      // Number of free buckets 
  int          _NbStoredElems;      // Number of stored elements in the hashtable

  // Pour debug
  unsigned int        _Tag;
  static unsigned int _Tag_Counter;

  void ReAllocate();
};


//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableBase::Get(int iPos) const
{
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 2 * iPos);
};

//-----------------------------------------------------------------------------
// operateur []
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableBase::operator[](int iPos) const
{  
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 2 * iPos);
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
INLINE int CATCGMHashTableBase::Size() const
{
  return _NbStoredElems;
}


#endif
