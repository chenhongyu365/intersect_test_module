/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2019 
/** @CAA2Required **/ 
//
//===========================================================================
//
// Avr. 2019   Creation Classe mere des objets Geometric             QF2
//
//===========================================================================
#ifndef CATGeomHashTableBase_H
#define CATGeomHashTableBase_H

// exporting module
#include "CATGMModelInterfaces.h"
#include "CATCGMHashTable.h"
#include "CATCollec.h"
#include "CATCGMNewArray.h"
#include "CATGeometryType.h"
#include "CATSysBoolean.h"
#include "CATGeometry.h"

class CATGeometry;
class CATCGMOutput;
class CATMathStream;
class CATICGMContainer;
class CATLISTP(CATGeometry);
class CATLISTP(CATCell);
class CATCellManifoldHashTable;
class CATDeclarativeManifoldHashTable;
class CATCellManifoldGroupHashTable;
class CATGeometryHTab;

//
typedef		int	         (*LSOCompareFunction) ( CATGeometry *, CATGeometry * );	
typedef		unsigned int (*LSOHashKeyFunction) ( CATGeometry * ) ;
//

// --------------------------------------------------------------------------------
// ** Heritage protégé ! **
// --------------------------------------------------------------------------------
// Class Abstraite 
// --------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATGeomHashTableBase : protected CATCGMHashTable 
{
public :
  // Destructor
  virtual ~CATGeomHashTableBase();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

#ifdef CATIACGMR424CAA
  virtual CATGeometricType GetType() const = 0;
#else
  virtual CATGeometricType GetType() const { return CATGeometryType; }
#endif
  
  // --------------------------------------------
  // Basic Access
  // --------------------------------------------
  CATGeometry * operator[](int iPos)                   const;    
  CATGeometry * Get       (int iPos)                   const;
  void        * Locate    (const CATGeometry * ipGeom) const;
  CATGeometry * KeyLocate (unsigned int iKey)          const; 
  CATGeometry * Next      (const CATGeometry * ipGeom) const;
  int           LocateReturnPos(const CATGeometry* ipGeom) const;

  void          RemoveAll();
  int           Size() const;


  // -----------------------------------------------------------------
  // Advanced Use
  // -----------------------------------------------------------------
  // Retrive common CATGeometry between iGeomHT and this. 
  // Restriction : iCellHT and oIntersectionHT must be same type than this or throw
  int Intersection(const CATGeomHashTableBase & iGeomHT, CATGeomHashTableBase &oIntersectionHT) const;

  // Test if at least one geometry belongs to both hashtables.
  CATBoolean  IsIntersected(const CATGeomHashTableBase &iGeomHT) const;
  // Test if the two hashtables contain exactly the same geometries, the order doesnt matter.
  CATBoolean  IsSameAs (const CATGeomHashTableBase &iGeomHT) const;
  // Test if all cells of iGeoHT are included in this.
  // Convention : returns FALSE if iGeoHT is empty.
  CATBoolean  Contains (const CATGeomHashTableBase &iGeomHT) const;

  
  // Remove
  // ------------------------------------------------------
  int Remove(const CATGeomHashTableBase & iGeomHT);
   
  // ConvertTo
  // ------------------------------------------------------
  void ConvertTo(CATCGMHashTable &oGeomHT)         const;
  void ConvertTo(CATLISTP(CATGeometry) &oGeomList) const;

  // Pickout
  // Get geometries if their types match
  // Returns the number of geometries picked out
  // ------------------------------------------------------
  template <typename ListT>
  int  Pickout(const ListT & iGeomList);

  // GetAs
  // ------------------------------------------------------
  virtual CATGeometryHTab                 * GetAsGeometryHT()     const;
  virtual CATCellManifoldHashTable        * GetAsCellManifoldHT() const;
  virtual CATCellManifoldGroupHashTable   * GetAsCMGroupHT()      const;
  virtual CATDeclarativeManifoldHashTable * GetAsDeclarativeHT()  const;
  
  // Const GetAs 
  // -----------------------------------------------------
  const CATCGMHashTable & GetAsCGMHashTable() const; // read only access

  // ---------------------------------------------------------------
  // Debug && Stream 
  // ---------------------------------------------------------------
  virtual void Dump (CATCGMOutput &oOut,  const char *iName=NULL) const;
  virtual void Write(CATMathStream &ioStr) const;
  virtual void Read (CATMathStream &ioStr, CATICGMContainer *iFactory);
  // Use RGB code
  void PutColor(int iRed, int iGreen, int iBlue) const;

  // HashTable Fonction
  static unsigned int HashKeyGEO_Function(CATGeometry * ipGeom);
  static int CompareGEO_Function(CATGeometry * ipGeom1, CATGeometry *ipGeom2);

protected :
  // Constructor
  explicit CATGeomHashTableBase(int iExpectedSize=0, LSOHashKeyFunction ipHashKeyFunction=HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CompareGEO_Function);
  // Copy-constructor
  CATGeomHashTableBase(const CATGeomHashTableBase & iGeomHT);
  
  // Restricted methods for child classes only
  // ---------------------------------------------  
  int     Insert(CATGeometry * ipGeom);  
  int     Remove(CATGeometry * ipGeom);
  int     RemoveReturnPos(CATGeometry* ipGeometry);

  // Union / Diff
  int Insert(const CATGeomHashTableBase & iGeometryHT);
  

  // Operators =
  CATGeomHashTableBase & operator =(const CATGeomHashTableBase & iGeometryHT);

};

template <typename ListT>
int CATGeomHashTableBase::Pickout(const ListT & iGeomList)
{
  int nbInsered = 0;
  CATGeometricType thisType = this->GetType();

  int numGeo = 1;
  for ( ; numGeo <= iGeomList.Size() ; numGeo++)
  {
    CATGeometry  * pCurGeom = iGeomList[numGeo];
    if (pCurGeom && pCurGeom->IsATypeOf(thisType)) // check compatibilié avec la HTab
    {
      nbInsered += this->Insert(pCurGeom);
    }
  }
  return nbInsered;
}

#endif

