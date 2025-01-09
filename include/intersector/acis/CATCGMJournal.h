/* -*-c++-*- */
#ifndef CATCGMJournal_h_
#define CATCGMJournal_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include <YP00IMPL.h>

#include "CATCGMNewArray.h"
#include "CATCGMVirtual.h"
#include "CATIACGMLevel.h"
#include "CATListOfCATGeometries.h"
#include "CATMathInline.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#    include <iosfwd.h>
#else
class ostream;
#endif
class CATCGMJournalList;
class CATCGMJournalItem;
class CATCGMOutput;
class CATCGMAttrId;
class CATCGMStream;
class CATGeoFactory;

/**
 * Class defining the journal of the topological operations.
 * <br> The journal logs the modifications of the faces, free edges and free vertices
 * of topological objects. The journal is designed as a composite pattern: it represents a journal item
 * ( @href CATCGMJournalItem ) and a list of items ( @href CATCGMJournalList ).
 * <br>You have to manage the creation and deletion of a journal.
 * The journal items are created when you report new events inside the
 * journal list (@href CATCGMJournalList#Report, @href CATCGMJournalList#ReportUnspecModify ). The journal
 * items are deleted with the journal list in which they are imbedded, except if you have directly
 * created an item, without inserting it inside a journal list.
 * The journal information is also deleted with the journal it informs.
 */

class ExportedByYP00IMPL CATCGMJournal : public CATCGMVirtual {
  public:
    /**
     * Constructs a CGM journal.
     * @param iList
     * If not <tt>NULL</tt>, a pointer to a journal list, inside which <tt>this</tt> will be inserted after its creation.
     */
    CATCGMJournal(CATCGMJournalList* iList);

    /** @nodoc */
    CATCGMNewClassArrayDeclare;

    virtual ~CATCGMJournal();

    /**
     * The types of report.
     * @param None
     * The report is inactivated.
     * @param List
     * The report is a CATCGMJournalList
     * @param Creation
     * The report is a CATCGMJournalItem describing the creation of an object.
     * @param Modification
     * The report is a CATCGMJournalItem describing the modification of an object in another one.
     * @param Subdivision
     * The report is a CATCGMJournalItem describing the subdivision of an object in P other objects.
     * @param Absorption
     * The report is a CATCGMJournalItem describing the absorption of N objects inside P>1 other objects.
     * @param Deletion
     * The report is a CATCGMJournalItem describing the deletion of an object.
     * @param Keep
     * The report is a CATCGMJournalItem describing that the object is not modified.
     * @param UnspecModif
     * One of the preceeding operations.
     * @param Copy
     * By default, the input objects are considered to be kept.
     * @param NoCopy
     * By default, none input object is considered to be kept.
     */
    enum Type {
        None = 0,           // inactivated report
        List = 10,          // CATCGMJournalList
        Creation = 21,      // CATCGMJournalItem
        Modification = 23,  // CATCGMJournalItem : 1 -> 1
        Subdivision = 24,   // CATCGMJournalItem : 1 -> P
        Absorption = 25,    // CATCGMJournalItem : N -> P  (P>=1)
        Deletion = 26,      // CATCGMJournalItem
        Keep = 27,          // CATCGMJournalItem : 1 -> itself

        UnspecModif = 30,

        Copy = 40,
        NoCopy = 41
    };
    /**
     * Returns the type of <tt>this</tt> journal.
     * @return
     * The type of the journal.
     */
    virtual CATCGMJournal::Type GetType() const = 0;

    /**
     *  Casts <tt>this</tt> into a journal list if possible.
     * @return
     * The casted pointer if <tt>this</tt> is a CATCGMJournalList, <tt>NULL</tt> otherwise.
     */
    virtual CATCGMJournalList* CastToReportList();

    /**
     *  Casts <tt>this</tt> into a journal item if possible.
     * @return
     * The casted pointer if <tt>this</tt> is a CATCGMJournalItem, <tt>NULL</tt> otherwise.
     */
    virtual CATCGMJournalItem* CastToReportItem();

    /**
     *  Activates or deactivates <tt>this</tt> journal.
     * @param iMode
     * The activation mode.
     * <br><b>Legal values</b>:
     *  0 inactive, 1 active
     */
    void SetActiveMode(short iMode);

/**
 *  Returns the activation mode.
 * @return
 * The activation mode.
 * <br><b>Legal values</b>:
 *  0 inactive, 1 active
 */
#ifdef CATIACGMR418CAA
    INLINE short GetActiveMode() const;
#else
    short GetActiveMode() const;
#endif

    /** @nodoc  */
    virtual void Dump(ostream& ioWhereToWrite, int iIndent = 0) = 0;

    /**
     * @nodoc
     * Dumps the content of <tt>this</tt> journal item.
     * @param iWhereToWrite
     * The output to write the journal.
     * @param iIndent
     * The number of blanks before writing the journal.
     */
    virtual void Dump(CATCGMOutput& ioWhereToWrite, int iIndent = 0) = 0;

    /**  @nodoc  */
    virtual CATCGMJournal* Duplicate(CATCGMJournalList* iInList = 0, int iCopyNext = 1) const = 0;

    /**
     * DO NOT USE
     * <br>Automatically reports the attributes pointed by the objects before the operation, on the
     * objects after the operation.
     * <br>Not available for a creation item.
     * @param iAttr
     * The type of attribute to report. If the objects before the operation point an attribute of this
     * type, the attribute will also be shared by the objects after modification.
     */
    virtual void MakeAttributesFollow(const CATCGMAttrId* iAttr) = 0;

    /** @nodoc */
    INLINE unsigned short IncCounter();
    /** @nodoc */
    INLINE unsigned short DecCounter();

    /** @nodoc */
    /*
     * AddRef and Release mechanism which allows to handle the life cycle of the journal.
     *
     * USE WITH CAUTION
     * -----------------
     *
     * There are two "exclusive" manners to manage the life cycle of the Journal
     *
     * 1 - The first manner is to use the new and delete operators to create and delete
     *     a CATCGMJournal and then use the InCounter() and DecCounter() mechanism to increment
     *     and decrement the number of handler to the CATCGMJournal object. The mechanism
     *     of IncCounter() and DecCounter() doesn't manage the destruction of the object
     *     YOU HAVE TO USE the delete operator to remove it.
     * 2 -  The second way is to use the new operator to create your CATCGMJournal object
     *      and then use the AddRef() and Release() mechanism to increment
     *      and decrement the number of handlers to the CATCGMObject object.
     *      DO NOT USE the delete operator in this case since ht Release() method will delete
     *      the CATCGMJournal object when there is no longer handler.
     */

    /**
     * Use AddRef when a new handler of the journal references it
     *
     * @return
     *   Number of objects that still reference the journal
     */
    INLINE unsigned short AddRef();
    /** @nodoc */
    /**
     * Use Release when a handler want to unreference a journal that it handles.
     *
     * @return
     *   Number of objects that still reference the journal. When this number reach 0
     *   the journal is deleted
     *
     */
    INLINE unsigned short Release();

    /**
     * Discards a list of objects from the topological journal.
     * This method is to be used with caution. Only objects
     * which are not required by the backtracking mechanism can be discarded.
     * If not used properly, this method can lead to an invalid journal.
     * @param iToSimplify
     * The list of objects to be discarded from the journal.
     * @return
     * 0 if the objects can be removed - otherwise 1
     */
    virtual int ForgetObjects(const CATLISTP(CATGeometry) & iToSimplify) = 0;

  protected:
    /**
     * Copy constructor.
     */
    CATCGMJournal(const CATCGMJournal& iToCopy);

    /**
     * Affectation operator.
     */
    CATCGMJournal& operator=(const CATCGMJournal& iToCopy);

    /** @nodoc */
    static CATCGMJournal::Type GetMemoryType(const unsigned short iType);
    /** @nodoc */
    static unsigned short GetStreamType(const CATCGMJournal::Type iType);

    //---------------------------------------------------------------------------
    // DATA
    //---------------------------------------------------------------------------

    /** @nodoc */
    CATCGMJournalList* _pOwning;
    /** @nodoc */
    CATCGMJournal* _pPrevious;
    /** @nodoc */
    CATCGMJournal* _pNext;

    /** @nodoc */
    // un bloc de 32 bits ...
    struct {
        unsigned _ActiveMode : 1;
        unsigned _Counter : 31;
    } _Data;

    /** @nodoc */
    // New Counter for AddRef and Release mecanism
    unsigned short _RefCounter;

    friend class ExportedByYP00IMPL CATCGMJournalList;
    friend class ExportedByYP00IMPL CATCGMJournalItem;
};

//-----------------------------------------------------------------------------
INLINE unsigned short CATCGMJournal::IncCounter() {
    return ++_Data._Counter;
}

//-----------------------------------------------------------------------------
INLINE unsigned short CATCGMJournal::DecCounter() {
    return --_Data._Counter;
}

//-----------------------------------------------------------------------------
/** @nodoc */
INLINE unsigned short CATCGMJournal::AddRef() {
    return (++_RefCounter);
}

//-----------------------------------------------------------------------------
/** @nodoc */
INLINE unsigned short CATCGMJournal::Release() {
    if((--_RefCounter) > 0) return _RefCounter;
    // Delete Object if no more pointers handle it
    else {
        delete this;
        return 0;
    }
}

#ifdef CATIACGMR418CAA
//-----------------------------------------------------------------------------
// GetActiveMode
//-----------------------------------------------------------------------------
INLINE short CATCGMJournal::GetActiveMode() const {
    return _Data._ActiveMode;
}
#endif

#endif
