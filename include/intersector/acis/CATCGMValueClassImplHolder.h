#ifndef CATCGMValueClassImplHolder_H
#define CATCGMValueClassImplHolder_H

// COPYRIGHT DASSAULT SYSTEMES 2014

/** @CAA2Required */

#include "CATMathematics.h"

#include "CATBoolean.h"
#include "CATCGMImplHolderMacros.h"

class CATCGMUseCounted;


/**
 * @nodoc
 * For internal use only.
 */
class ExportedByCATMathematics CATCGMValueClassImplHolder
{
public:
	/**
	* Default Constructor
	*/
	CATCGMValueClassImplHolder();

	/**
	* Copy Constructor
	*/
	CATCGMValueClassImplHolder(CATCGMValueClassImplHolder const & iOther);

	/**
	* Assignment Operator
	*/
	CATCGMValueClassImplHolder & operator=(CATCGMValueClassImplHolder const & iOther);

	/**
	* Construct from ipImpl
	*
	* Note that the "const" is white lie for the compiler - it will be cast away inside *this
	* It is needed so that sharing an implementation between two holders is
	* treated as a const operation, even though it allows potential side effects if a non-const
	* method is called on a holder sharing the impl.
	* This is related to the fact that CATCGMValueClassImplHolder can be considered to have
	* reference-class/smart-pointer semantics, since modifying "a" can have side effects 
	* on "b" after "a = b".
	*/
	CATCGMValueClassImplHolder(CATCGMUseCounted const* ipImpl);

	/**
	* Destructor
	*/
	~CATCGMValueClassImplHolder();

	/**
	* resets _impl, while getting reference counts on new and old impls correct
	*
	* Note that the "const" is white lie for the compiler - it will be cast away inside *this
	* It is needed so that sharing an implementation between two holders is
	* treated as a const operation, even though it allows potential side effects if a non-const
	* method is called on a holder sharing the impl.
	* This is related to the fact that CATCGMValueClassImplHolder can be considered to have
	* reference-class/smart-pointer semantics, since modifying "a" can have side effects 
	* on "b" after "a = b".
	*/
	void SetImpl(CATCGMUseCounted const* ipNewImpl);

	/**
	* Returns pointer-to-impl, WITHOUT ADJUSTING THE USE COUNT OF THE IMPL
	* The class which owns this _implObject should wrap this in a method 
	*     TrueImplClassName* GetImpl()
	*       {return (TrueImplClassName*)_implObject.GetImpl();}
	* to ensure that the downcast from CATCGMUseCounted* is in a controlled location where the pointer type is known
	* (because a pointer to TrueImplClassName was placed into _implObject.
	*
	* NOTE: If this were templatized, then CATCGMValueClassImplHolder would be a template class 
	* over TrueImplClassName, and GetImpl() would return TrueImplClassName*
	*/
	CATCGMUseCounted const* GetImpl() const;
	CATCGMUseCounted* GetImpl();

	CATBoolean operator==(CATCGMValueClassImplHolder const& iOther) const;

private: 
	CATCGMUseCounted* _impl;
	void UnshareIfNecessary();
};

#endif
