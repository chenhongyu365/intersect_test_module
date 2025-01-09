#ifndef CATTopData_H
#define CATTopData_H

// COPYRIGHT DASSAULT SYSTEMES 2000
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#ifndef NULL
/** @nodoc */
#define NULL 0
#endif

#include "CATGMModelInterfaces.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATIACGMLevel.h"

class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATCGMStream;
class CATGeoFactory;

/**
 * Class defining inputs of the topological operators.
 * @see CATSoftwareConfiguration, CATCGMJournalList
 */
class ExportedByCATGMModelInterfaces CATTopData
{
public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Constructs a CATTopData.
 * @param  iConfig
 * The pointer to the configuration. Must not be <tt>NULL</tt>.
 * @param iJournal
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not filled by the operator.
 */  
   CATTopData(CATSoftwareConfiguration* iConfig, CATCGMJournalList* iJournal=NULL);

/**
 * Constructs a CATTopData.
 * <br>
 * You must call the <tt>SetSoftwareConfiguration</tt> method afterwards, because a
 * CATSoftwareConfiguration is mandatory for use.
 */  
   CATTopData();
   
/**
 * Destructor.
 */
  virtual ~CATTopData ();
  

/**
  * Copy constructor.
  */  
  CATTopData(const CATTopData& iToCopy);

/**
  * Assignment operator.
  */  
  CATTopData& operator = (const CATTopData& iToAssign);
  
/** 
 * Defines the software configuration to be taken 
 * into acccount by <tt>this</tt> data.
 * @param iConfig
 * The software configuration.
 */
  void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig);

/** 
 * Returns the software configuration to be taken 
 * into acccount by <tt>this</tt> data.
 * @return
 * The software configuration.
 */
  inline CATSoftwareConfiguration* GetSoftwareConfiguration() const;
 
/** 
 * Defines the topological journal to be taken 
 * into acccount by <tt>this</tt> data.
 * @param iJournal
 * The topological journal.
 */
  void SetJournal(CATCGMJournalList* iJournal);

/**
* Returns the pointer to the topological journal associated with <tt>this</tt> CATTopData.
* <br>Only available if a journal was given at the data creation.
* @return
* The pointer to the journal of the operation.
  */
  inline CATCGMJournalList* GetJournal() const;

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifdef CATIACGMV5R21
  /** @nodoc */
  /**
  * Constructs a CATTopData with a Software Configuration and a NULL Journal.
  * @param  iConfig
  * The pointer to the configuration. Must not be <tt>NULL</tt>.
  *
  * USE WITH CAUTION
  * -----------------
  * This static creation method allows creation of specific TopData. It positions
  * the flag _JournalMustBeCreatedByTopOperator to TRUE.
  * The Topological Operator that recieves this TopData as input arg. will
  * create a journal and manage its life cycle with AddRef and Release mechanism
  */  
  static CATTopData *CATCreateTopData(CATSoftwareConfiguration* iConfig);
#endif
   
  /**
  * @nodoc
  */
  CATCGMNewClassArrayDeclare;
  
  /** @nodoc*/
  void  Stream  (CATGeoFactory *iFactory, CATCGMStream&os);
  /** @nodoc*/
  void  UnStream(CATGeoFactory *iFactory, CATCGMStream& os, const short ifAssociatedCGMReplayAddToClean = 1);
  /** @nodoc*/
  void  UnStreamInternal(CATGeoFactory *iFactory, CATGeoFactory *iFactoryForBuildVersion
                                         , CATCGMStream& os, const short ifAssociatedCGMReplayAddToClean = 1);

protected:

  /** @nodoc */
  CATSoftwareConfiguration*   _Config;
  /** @nodoc */
  CATCGMJournalList*          _Journal;

#ifdef CATIACGMV5R21
  /** @nodoc */
  CATBoolean                  _JournalMustBeCreatedByTopOperator;

  /** @nodoc */
  CATTopData(CATBoolean iJournalMustBeCreatedByTopOperator, CATSoftwareConfiguration* iConfig);
#endif

  /** @nodoc */
  friend class CATExtTopOperator;
};

//------------------------------------------------------------------------------
// GetSoftwareConfiguration
//------------------------------------------------------------------------------
inline CATSoftwareConfiguration* CATTopData::GetSoftwareConfiguration() const
{
  return _Config;
}

//------------------------------------------------------------------------------
// GetJournal
//------------------------------------------------------------------------------
inline CATCGMJournalList* CATTopData::GetJournal() const
{
  return _Journal;
}


#endif
