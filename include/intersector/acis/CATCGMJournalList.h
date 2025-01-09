#ifndef CATCGMJournalList_h_
#define CATCGMJournalList_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"

#include "YP00IMPL.h"
#include "CATCGMJournal.h"
#include "CATListOfCATGeometries.h"
#include "CATListOfCATCGMJournals.h"
#include "CATGeometry.h"
#include "CATCGMNewArray.h"
#include "CATListOfCATCGMJournalInfo.h"

#if __cplusplus >= 201103L  // C++11  
#include <memory>
#endif

class CATCGMJournalFilter;
class CATCGMJournalInfo;
class CATSoftwareConfiguration;


/**
 * Defines the type of request.
 * @param ThroughModify
 * Search for the terminal objects modified from one given object, but do not
 * output the intermediate 
 * objects.
 * @param ThroughCreateAndModify
 * Search for the terminal objects modified and/or created from one given
 * object, but do not output the intermediate objects.
 * @param ThroughAllCreateAndModify
 * Search for the objects modified and/or created from one given object,
 * and output the intermediate objects resulting in creations.
 * @param AllThroughModify
 * Search for the objects modified from one given object, and output the
 * intermediate objects.
 * @param ThroughAllCreate
 * Search for the objects created from one given object, and output the
 * intermediate created objects.
 * @param ThroughCreateAndModifyWithDeleted
 * Search for the terminal objects modified and/or created from one given
 * object, including the deleted ones, but do not output the intermediate
 * objects.
 */
enum CATCGMJournalRequest 
{
  ThroughModify,
  ThroughCreateAndModify,
  ThroughAllCreateAndModify,
  AllThroughModify,
  ThroughAllCreate,
  ThroughCreateAndModifyWithDeleted
};

/**
 * Class representing an aggregation of journal items and journal lists.
 * <br>You have to manage the creation and deletion of a journal list. 
 * The journal items are created when you report new events inside the
 * journal list (@href CATCGMJournalList#Report,
 * @href CATCGMJournalList#ReportUnspecModify). The journal
 * items are deleted with the journal list in which they are imbedded, except
 * if you have directly created an item, without inserting it inside a journal
 * list.
 * The journal information is also deleted with the journal it informs.
 */ 
class ExportedByYP00IMPL CATCGMJournalList : public CATCGMJournal
{
public:

    /**
 * Constructs a CGM journal list.
 * @param iConfig
 * The pointer to the configuration. Must not be <tt>NULL</tt>.
 * @param ioList
 * If not <tt>NULL</tt>, a pointer to a journal list, inside which
 * <tt>this</tt> will be inserted after its creation.
 */
                              CATCGMJournalList(CATSoftwareConfiguration * iConfig,
                                                CATCGMJournalList        * ioList);

/**
 * @nodoc
 * @deprecated V5R14
 * Use the signature with CATSoftwareConfiguration
 */
                              CATCGMJournalList();

/**
 * @nodoc
 * @deprecated V5R14
 * Use the signature with CATSoftwareConfiguration
 */
                              CATCGMJournalList(CATCGMJournalList * ioList);


  virtual                    ~CATCGMJournalList();
  /** @nodoc */
  CATCGMNewClassArrayDeclare;

/**
 * Returns the type of <tt>this</tt> CATCGMJournalList.
 * @return
 * <tt>CATCGMJournal::List</tt>.
 */
  virtual CATCGMJournal::Type GetType() const;

/** 
 *  Casts <tt>this</tt> into a journal list.
 * @return
 * The casted pointer.
 */
  virtual CATCGMJournalList * CastToReportList();

/** @nodoc */
  virtual void                Dump(ostream & ioWhereToWrite, int iIndent = 0);

/**
 * @nodoc
 * Dumps the content of <tt>this</tt> journal list.
 * @param iWhereToWrite
 * The output to write the journal list.
 * @param iIndent
 * The number of blanks before writing of the list.
 */
  virtual void                Dump(CATCGMOutput & ioWhereToWrite, int iIndent = 0);

/** 
 * Duplicates <tt>this</tt> CATCGMJournalList.
 * @param iInReport
 * The pointer to another journal list inside which the duplication is inserted. 
 * If <tt>NULL</tt>, no insertion.
 * @return
 * A pointer to the duplicated journal.
 */
  virtual CATCGMJournal *     Duplicate(CATCGMJournalList * ioInReport,
                                        int iCopyNext = 1) const;

/** 
 * Skips to the next item or list of <tt>this</tt> journal list.
 * @param iPtr
 * The pointer to the journal from which the search is initialized.
 * @return
 * A pointer to the next journal of <tt>this</tt> journal list.
 */
          CATCGMJournal *     Next(CATCGMJournal * ioPtr = NULL) const;

 /** 
 * Skips to the next item or list of <tt>this</tt> journal list.
 * W17-2023 : without const
 * @param iPtr
 * The pointer to the journal from which the search is initialized.
 * @return
 * A pointer to the next journal of <tt>this</tt> journal list.
 */
          CATCGMJournal *     Next(CATCGMJournal * ioPtr = NULL);

/** 
 * Tasses the contained items.
 * <br>Please refer to the encyclopedia articles to learn about the rules for
 * the tass.
 */
          void                Tass();

/** 
 * Retrieves the journals that reference a given geometric object.
 * @param iAnObject
 * A pointer to the object.
 * @param ioFoundReports
 * A list of journals that reference <tt>iAnObject</tt>.
 */
          void                SearchReportsAbout(CATGeometry * ioAnObject,
                                                 CATLISTP(CATCGMJournal) & ioFoundReports) const;

/** 
 * Retrieves the journals that reference a given geometric object.
 * W17-2023 : without const
 * @param iAnObject
 * A pointer to the object.
 * @param ioFoundReports
 * A list of journals that reference <tt>iAnObject</tt>.
 */
          void                SearchReportsAbout(CATGeometry * ioAnObject,
                                                 CATLISTP(CATCGMJournal) & ioFoundReports);
          
/** 
 * Retrieves the journals that reference objects of a given geometric type.
 * @param iGeoType
 * A geometric object type.
 * @param ioFoundReports
 * A list of journals that reference objects of type <tt>iGeoType</tt>.
 */
          void                SearchReportsAbout(CATGeometricType iGeoType,
                                                 CATLISTP(CATCGMJournal) & ioFoundReports) const;

/** 
 * Retrieves the journals that reference objects of a given geometric type.
 * W17-2023 : without const
 * @param iGeoType
 * A geometric object type.
 * @param ioFoundReports
 * A list of journals that reference objects of type <tt>iGeoType</tt>.
 */
          void                SearchReportsAbout(CATGeometricType iGeoType,
                                                 CATLISTP(CATCGMJournal) & ioFoundReports);

/**
 * Retrieves the objects that are created and/or modified by a given geometric
 * object.
 * @param iAnObject
 * A pointer to the object.
 * @param ioNewObjects
 * The list of geometrical objects that are defined by <tt>iAnObject</tt>.
 * @param iRequest
 * The type of search.
 */
          void                FindLasts(CATGeometry           * ioAnObject,
                                        CATLISTP(CATGeometry) & ioNewObjects,
                                        CATCGMJournalRequest    iRequest = ThroughModify);


/**
 * Retrieves the objects that lead to the definition of a given geometric
 * object.
 * @param iAnObject
 * A pointer to the object.
 * @param ioOriginObjects
 * The list of geometrical objects that lead to the definition of
 * <tt>iAnObject</tt>.
 * @param iRequest
 * The type of search.
 */
          void                FindFirsts(CATGeometry           * ioAnObject,
                                         CATLISTP(CATGeometry) & ioOriginObjects, 
                                         CATCGMJournalRequest    iRequest = ThroughModify);

/** 
 * DO NOT USE
 * <br>Automatically reports the attributes pointed by the objects before the
 * operation, on the objects after the operation.
 * <br>Not available for a creation item.
 * @param iAttr
 * The type of attribute to report. If the objects before the operation point
 * an attribute of this type, the attribute will also be shared by the objects
 * after modification.
 */
          void                MakeAttributesFollow(const CATCGMAttrId * iAttributeID);

/** 
 * Creates an item inside <tt>this</tt> journal list.
 * @param iType 
 * The type of the item.
 * @param iBeforeObjects
 * The list of the objects before the operation.
 * @param iAfterObjects
 * The list of the objects after the operation.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 */
          void                Report(      CATCGMJournal::Type     iType,
                                     const CATLISTP(CATGeometry) & iBeforeObjects,
                                     const CATLISTP(CATGeometry) & iAfterObjects,
                                           CATCGMJournalInfo     * ioOptionalInfo = NULL);

/** 
 * Creates a deletion item inside <tt>this</tt> journal list.
 * @param iDeletedObjects
 * The list of the objects to delete.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 */
          void                ReportDeletion(const CATLISTP(CATGeometry) & iDeletedObjects,
                                             CATCGMJournalInfo           * ioOptionalInfo = NULL);

/** 
 * Creates a keep item inside <tt>this</tt> journal list.
 * @param iToKeep
 * The pointer to the object to keep.
 */
          void                ReportKeeping(CATGeometry * ioToKeep);

/** 
 * Creates a creation item inside <tt>this</tt> journal list.
 * @param iOperands
 * The list of pointers to the geometric objects from which <tt>ioCreatedObject</tt> are created.
 * @param iCreatedObjects
 * The list of the objects to create.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 */
          void                ReportCreation(const CATLISTP(CATGeometry) & iOperands,
                                             CATGeometry                 * ioCreatedObject,
                                             CATCGMJournalInfo           * ioOptionalInfo = NULL);

/** 
 * Creates an item inside <tt>this</tt> journal list.
 * <br> Automatically finds the type of the item, according to the number of
 * objects in 
 * <tt>iBefore</tt> and the number of objects in <tt>iAfter</tt>.
 * @param iBefore
 * The list of the objects before the operation.
 * @param iAfter
 * The list of the objects after the operation.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 */
          void                ReportUnspecModify(const CATLISTP(CATGeometry) & iBefore,
                                                 const CATLISTP(CATGeometry) & iAfter,
                                                 CATCGMJournalInfo           * ioOptionalInfo = NULL);

  /** @nodoc */
          void                ReportCopy(CATCGMJournal::Type   iType,
                                         CATGeometry         * ioInObject,
                                         CATGeometry         * ioOutObject = NULL);



/**
 *-----------------------------------------------------------------------------
 * SAFE methods to replace void InsertJournal(...)
 *-----------------------------------------------------------------------------
 */

/**
 * Insert a copy of @param iJournalToInsert inside <tt>this</tt>.
 * Memory will be duplicated. safe.
 * @return 
 *  S_OK if journal properly duplicated and inserted,
 *  E_FAIL otherwise. 
 */
          HRESULT             InsertCopy(const CATCGMJournalList * iJournalToInsert);

#if __cplusplus >= 201103L  // C++11  
/**
 * Definitive merge of a journal list inside <tt>this</tt>.
 * -> Safer, it prevents leak and coredump ! To be used instead of old 'void InsertJournal(..)'
 * 
 * No memory is allocated.
 *
 * @param ipJournalToInsert
 *    The journal list to insert. It will be released and set to null afterward. 
 * @return 
 *    S_OK if journal properly inserted,
 *    E_FAIL otherwise. 
 */         
          HRESULT             InsertJournal(std::unique_ptr<CATCGMJournalList> & ipJournalToInsert);
#endif 

/**
 * Use safe InsertJournal above or InsertCopy  for a secure and proper code.
 * 
 * ! Unsafe !
 * >Uncompatible with SmartPointers of all kind.
 *
 * Inserts an isolated journal list inside <tt>this</tt>.
 * @param iJournalToInsert
 * The journal list to insert. It must be isolated (never referenced by
 * another journal).
 */
          void                InsertJournal(CATCGMJournalList * ioJournalToInsert);

/*------------------------------------------------------------------------------------------------------------*/


  /** @nodoc */
          void                SetFilter(CATCGMJournalFilter * ioFilter);
  /** @nodoc */
    const CATCGMJournalFilter * GetFilter() const;
  /** @nodoc */
          void                ClearFrom(CATCGMJournal * ioReport = NULL);
  /** @nodoc */
          int ForgetObjects(const CATLISTP(CATGeometry)& iToForget);
  /** @nodoc */
    const CATCGMJournalInfo * TrackObjectInfo(CATGeometry * ioObject);
  /** @nodoc */
    const CATBoolean          TrackObjectCreation(CATGeometry * ioObject);


  /** @nodoc
  * DEPRECATED
  */
  static  CATCGMJournalList * OpenJournal();

  /** @nodoc
  * DEPRECATED
  */
  static  void                CloseJournal();

  /** @nodoc
  * DEPRECATED
  */
  static  CATCGMJournalList * GetJournal();

  /** @nodoc
  * DEPRECATED
  */
  static  void                SetJournal(CATCGMJournalList * ioJournal);

  

  /** @nodoc */
          CATULONG32          GetDebugIdentifier();
  /** @nodoc */
          CATBoolean          IsEmbedded();
  /** @nodoc */
          CATSoftwareConfiguration * GetConfiguration() const;

#ifdef CATIACGMR217CAA
  /** @nodoc */
          void                SetConfiguration(CATSoftwareConfiguration * iConfig);
#endif


  /** @nodoc */
          void                RemoveReport(CATCGMJournal* ipJournalToForget, int iWithTraces = 0, int iSens = 0, int iWithoutLinks = 0);

  
  /**
  * @nodoc
  * True Stream management
  */
  virtual void                Stream  (CATGeoFactory *iFactory, CATCGMStream &os);

  /**
  * @nodoc
  * True Stream management
  */
  static CATCGMJournalList  * UnStream(CATCGMJournalList * ioList, CATGeoFactory *iFactory, CATCGMStream & iStr);
#ifdef CATIACGMR216Code
    /**
  * @nodoc @nocgmitf
  * True Stream management
  */
  static CATCGMJournalList  * UnStream(CATCGMJournalList * ioList,
                                       CATGeoFactory     * iFactoryForFirst,
                                       CATGeoFactory     * iFactoryForLast ,
                                       CATCGMStream      & iStr);
#endif



#ifdef CATIACGMR217CAA
      /**
  * @nodoc
  * True Stream management
  */
          void                StreamContent(CATGeoFactory *iFactory, CATCGMStream& iStr);

      /**
  * @nodoc
  * True Stream management
  */
  static CATCGMJournalList  * UnStreamContent(CATCGMJournalList * ioList, CATGeoFactory *iFactory, CATCGMStream& iStr);
#endif

  /** @nodoc */
          CATBoolean          IsTassed() const;

  //W17-2023 : without const
  /** @nodoc */
          CATBoolean          IsTassed();

  /** @nodoc */
          void                InsertItem(CATCGMJournalItem *piJournalItem,CATBoolean iSens = FALSE);

  /** @nodoc */
  /** 
 * Skips to the previous item or list of <tt>this</tt> journal list.
 * @param iPtr
 * The pointer to the journal from which the search is initialized.
 * @return
 * A pointer to the previous journal of <tt>this</tt> journal list.
 */
          CATCGMJournal     * Last(CATCGMJournal * ioPtr = NULL) const;

  /** @nodoc */
  /** 
 * Skips to the previous item or list of <tt>this</tt> journal list.
 * W17-2023 : without const
 * @param iPtr
 * The pointer to the journal from which the search is initialized.
 * @return
 * A pointer to the previous journal of <tt>this</tt> journal list.
 */
          CATCGMJournal     * Last(CATCGMJournal * ioPtr = NULL);

  /** @nodoc */
  /** 
  * Say if th Geometry has been deleted
  * @param piGeometry
  * The pointer to the query geometry
  * @return
  *    <dl>
  *    <dt><tt>TRUE</tt>    <dd>if geometry deleted
  *    <dt><tt>FALSE</tt>    <dd>otherwise
  *    </dl>
  */
          CATBoolean          IsDeleted(CATGeometry *piGeometry) ;

#ifdef CATIACGMR417CAA
  /** @nodoc */
  /**
  * Retrieves the objects that are created and/or modified by a given geometric
  * object.
  * @param iAnObject
  * A pointer to the object.
  * @param ioNewObjects
  * The list of geometrical objects that are defined by <tt>iAnObject</tt>.
  * @param iRequest
  * The type of search.
  */
          void                FindLasts(CATGeometry           * ioAnObject,
                                        CATLISTP(CATGeometry) & ioNewObjects,
                                        CATCGMJournalRequest    iRequest,
                                        CATLISTP(CATCGMJournalInfo) *pioListOfCGMJournalInfo);

  /** @nodoc */
  /**
  * Retrieves the objects that lead to the definition of a given geometric
  * object.
  * @param iAnObject
  * A pointer to the object.
  * @param ioOriginObjects
  * The list of geometrical objects that lead to the definition of
  * <tt>iAnObject</tt>.
  * @param iRequest
  * The type of search.
  */  
          void                FindFirsts(CATGeometry           * ioAnObject,
                                         CATLISTP(CATGeometry) & ioOriginObjects, 
                                         CATCGMJournalRequest    iRequest,
                                         CATLISTP(CATCGMJournalInfo) *pioListOfCGMJournalInfo);
  /** @nodoc */
  /** 
  * Tasses the contained items of the Jopurnal in the target Journal given as input argument.
  * <br>Please refer to the encyclopedia articles to learn about the rules for
  * the tass.
  */
          void                TassIn(CATCGMJournalList *pioJournalList);
#endif

#ifdef CATIACGMR421CAA

 /** @nodoc */
 /** 
 * Creates an item inside <tt>this</tt> journal list.
 * @param iType 
 * The type of the item.
 * @param iBeforeObjects
 * The list of the objects before the operation.
 * @param iAfterObjects
 * The list of the objects after the operation.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 *
 * @return
 * the created abd inserted Item Journal 
 */
          CATCGMJournalItem * ReportPrivate(CATCGMJournal::Type           iType,
                                            const CATLISTP(CATGeometry) & iBeforeObjects,
                                            const CATLISTP(CATGeometry) & iAfterObjects,
                                            CATCGMJournalInfo           * ioOptionalInfo = NULL);

  /** @nodoc */
  /** 
 * Creates an item inside the internal journal referenced by <tt>this</tt> journal list.
 * @param iType 
 * The type of the item.
 * @param iBeforeObjects
 * The list of the objects before the operation.
 * @param iAfterObjects
 * The list of the objects after the operation.
 * @param iOptionalInfo
 * A pointer to an optional information. If <tt>NULL</tt>, no information is
 * added.
 *
 * @return
 * <dl>
 * <dt><tt>S_OK</tt>     <dd>if succeeded
 * <dt><tt>E_FAIL</tt>    <dd>if failed
 * </dl>
 */
          HRESULT             ReportInternal(CATCGMJournal::Type           iType,
                                             const CATLISTP(CATGeometry) & iBeforeObjects,
                                             const CATLISTP(CATGeometry) & iAfterObjects,
                                             CATCGMJournalInfo           * ioOptionalInfo = NULL);

  /** @nodoc */
  /* Tasses the contained items inside Internal Journals .*/  
          void                TassInternalJournal();

  /** @nodoc */
  /** 
  * Return the created internal journal referenced by <tt>this</tt> journal list.
  *
  * @return
  *  The Internal Journal
  */
          CATCGMJournalList * CreateInternalJournal(); 

  /** @nodoc */
  /** 
  * Return the internal journal referenced by <tt>this</tt> journal list.
  *
  * @return
  *  The Internal Journal
  */
          CATCGMJournalList * GetInternalJournal(); 

  /** @nodoc */
  /** 
  * Set internal journal inside <tt>this</tt> journal list.
  *
  * @return
  *  The Internal Journal
  */
          void                SetInternalJournal(CATCGMJournalList *piCGMJournalList); 

  /**
  * @nodoc
  * Dumps the internal journal referenced by <tt>this</tt> journal list.
  * @param iWhereToWrite
  * The output to write the journal list.
  * @param iIndent
  * The number of blanks before writing of the list.
  */
          void                DumpInternal(CATCGMOutput & ioWhereToWrite, int iIndent = 0);

  /**
  * @nodoc
  * Duplicate the internal journal referenced by <tt>this</tt> journal list
  * into the given journal  
  * @param ioInternalJournal
  * The output journal into wich the Internal Journal will be copied 
  *
  * @return
  * <dl>
  * <dt><tt>S_OK</tt>     <dd>if succeeded
  * <dt><tt>E_FAIL</tt>    <dd>if failed
  * </dl>
  */
          HRESULT             CopyInternalJournals(CATCGMJournalList *& ioDestJournal, CATBoolean iFirstLevel = FALSE);

#endif

private:

#ifdef CATIACGMR217CAA
 /** @nodoc */
 /* Insert an isolated journal list to <tt>this</tt> at the last position.
  *  
  */
          void                InsertJournalAtLast(CATCGMJournalList * ioJournalToInsert);

          void                SetInsertOrder(CATBoolean iOrder);
          CATBoolean          GetInsertOrder();
#endif

protected:

friend class ExportedByYP00IMPL CATCGMJournal;
friend class ExportedByYP00IMPL CATCGMJournalItem;
friend class CATCGMJournalListBasicCheck;

/**
 * Copy constructor.
 */
                              CATCGMJournalList(const CATCGMJournalList & iToCopy);
/**
 * Affectation operator.
 */
  CATCGMJournalList & operator =               (const CATCGMJournalList & iToCopy);
  /** @nodoc */
          void                ReportChanged();
  /** @nodoc */
          void                InstallFilter();
  /** @nodoc */
          void                RemoveFilter();


  /**
  * @nodoc
  * True Stream management
  */
  virtual void                _UnStream(CATGeoFactory *iFactory, CATCGMStream & os);

#ifdef CATIACGMR217CAA
    /**
  * @nodoc
  * True Stream management
  */
  virtual void                _Stream(CATGeoFactory *iFactory, CATCGMStream & os);
#endif

  /** @nodoc */
         CATCGMJournalFilter      * _pFilter;

  /** @nodoc */
  static CATCGMJournalList        * _pTheUniqueJournal;

  /** @nodoc */
         CATCGMJournal            * _pFirst;
  /** @nodoc */
         CATCGMJournal            * _pLast;
  /** @nodoc */
         void                     * _pGraph;

  /** @nodoc */
  // un bloc de 32 bits ...
  struct
  {

     unsigned _Tassed        : 1;
     unsigned _Tassing       : 1;
#ifdef CATIACGMR421CAA
     unsigned _InternalTassed: 1;
     signed   _GraphToModify :29;
#else
     signed   _GraphToModify :30;
#endif
  } 
                                    _DataList;


private:

         CATULONG32                 _SessionId ;
  static CATULONG32                 _SessionBorn ;

         CATSoftwareConfiguration * _pSoftConfig;

#ifdef CATIACGMR217CAA
  // TRUE  : insert at _pFirst
  // FALSE : insert at _pLast
  // By defaut it is TRUE
         CATBoolean                 _InsertOrder;
#endif

#ifdef CATIACGMR421CAA
         CATCGMJournalList        * _pInternalJournal;
#endif
};

#endif
