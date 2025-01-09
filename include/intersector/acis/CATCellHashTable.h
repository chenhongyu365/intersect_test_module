/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  1999
/** @CAA2Required */ 
/**
* @nodoc
*/
//===========================================================================
//
// Avr. 2002   Migration vers CATCGMHashTable                       HCN
// 
// April 2020  Migration vers CATGeomHashTableBase                  QF2
//
//===========================================================================
#ifndef CATCellHashTable_H
#define CATCellHashTable_H

#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"

class CATCell;
class CATLISTP(CATCell);

// exporting module
#include  "CATGMModelInterfaces.h"

typedef		int	         (*PFCompareFunction) ( CATCell *, CATCell * );	
typedef		unsigned int (*PFHashKeyFunction) ( CATCell * ) ;


ExportedByCATGMModelInterfaces unsigned int HashKeyFunction( CATCell * iCell );

ExportedByCATGMModelInterfaces int CompareFunction( CATCell * iCell1, CATCell *iCell2 );



#define NEW_CELL_HASHTABLE
#include "CATGeomHashTableBase.h"

#ifdef NEW_CELL_HASHTABLE


//=============================================================================
// NOUVEAU Code
//=============================================================================
class  ExportedByCATGMModelInterfaces  CATCellHashTable : public CATGeomHashTableBase
{

public : 
  // Constructor
  explicit CATCellHashTable(int iExpectedSize=0, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);  
  // constructor from list
  explicit CATCellHashTable(const CATLISTP(CATCell) &iCellList, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // old constructor - no default argument...
  CATCellHashTable (PFHashKeyFunction ipHashKeyFunction, PFCompareFunction ipCompareFunction, int iEstimatedSize = 0);
  // Copy-constructor
  CATCellHashTable(const CATCellHashTable & iCellHT);
  // Destructor
  virtual ~CATCellHashTable();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

#ifdef CATIACGMR424CAA
  virtual CATGeometricType GetType() const;
#endif

  // Main Methods
  // --------------------------------------------
  CATCell * operator[](int iPos)          const;
  CATCell * Get       (int iPos)          const;  
  int       Insert    (CATCell * ipCell);     
  int       Remove    (CATCell * ipCell);
  int       RemoveReturnPos(CATCell * ipCell);
  void *    Locate    (CATCell * ipCell)  const;
  CATCell * KeyLocate (unsigned int iKey) const;   
  CATCell * Next      (CATCell * ipCell)  const;


  // Insert
  // --------------------------------------------
  int Insert(const CATLISTP(CATCell) & iCellList); 
  int Insert(const CATCellHashTable & iCellHT);

  // Remove
  // --------------------------------------------
  // using CATGeomHashTableBase::Remove;
  int Remove(const CATCellHashTable & iCellHT);
  int Remove(const CATLISTP(CATCell) & iCellList); 

  // ConvertTo
  // --------------------------------------------
  using CATGeomHashTableBase::ConvertTo;
  void ConvertTo(CATLISTP(CATCell) &oCellList) const;
  

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATGeomHashTableBase & operator = (const CATCellHashTable & iCellHT);

  
// ----------------------------------------------------------------
// Protected call
protected:
  CATCellHashTable & operator =(const CATLISTP(CATCell) &iCellList);

};


#else
//=============================================================================
// ANCIEN CODE
//=============================================================================

class   ExportedByCATGMModelInterfaces  CATCellHashTable : public CATCGMHashTable
{
public:
  CATCellHashTable (PFHashKeyFunction ipHashKeyFunction, PFCompareFunction ipCompareFunction, int iEstimatedSize = 0);
  ~CATCellHashTable();
  CATCGMNewClassArrayDeclare;
  
  inline int      Insert(CATCell* ipCell);
  inline CATCell* Get(int iPos) const;
  inline void*    Locate(CATCell* ipCell) const;
  inline CATCell* KeyLocate(unsigned int iKey) const; 
  inline int      Remove(CATCell* ipCell);

  CATCell*        Next(CATCell* ipCell) const;
  int             Size() const;
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
inline int CATCellHashTable::Insert(CATCell* ipCell)
{
  return (this->CATCGMHashTable::Insert((void*)ipCell));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
inline CATCell* CATCellHashTable::Get(int iPos) const
{
  return ((CATCell*)this->CATCGMHashTable::Get(iPos));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
inline void* CATCellHashTable::Locate(CATCell* ipCell) const
{
  return (this->CATCGMHashTable::Locate((void*)ipCell));
}

//-----------------------------------------------------------------------------
// KeyLocate
//-----------------------------------------------------------------------------
inline CATCell* CATCellHashTable::KeyLocate(unsigned int iKey) const
{
  return ((CATCell*)this->CATCGMHashTable::KeyLocate(iKey));
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
inline int CATCellHashTable::Remove(CATCell* ipCell)
{
  return (this->CATCGMHashTable::Remove((void*)ipCell));
}

#endif


#define CATHashTabCATCell CATCellHashTable



#endif 
