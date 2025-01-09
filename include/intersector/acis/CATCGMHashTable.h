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
//===========================================================================
//
// Implementation generique d'une hash table avec gestion des adresses > 2 Go
//
// Avr. 02   Creation                                               HCN
// Sep. 02   Derivation de CATCGMHashTableBase                      HCN
//===========================================================================

#ifndef  CATCGMHashTable_h
#define  CATCGMHashTable_h

#include "CATCGMHashTableBase.h"

#define CATCGM_DEFAULT_HASH_TABLE_DIMENSION 31

class ExportedByCATMathematics CATCGMHashTable : public CATCGMHashTableBase
{
public:

  CATCGMHashTable(int iEstimatedSize = 0,
                  PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                  PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTable();

protected :

  // Par defaut, un bucket est un CATULONGPTR
  CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];
};
#endif
