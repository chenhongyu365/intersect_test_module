#ifndef CATCGMVirtualMacros_h
#define CATCGMVirtualMacros_h

/** @CAA2Required */

/**
 * @nodoc
 * Declares the item for the CGM interface dictionary.
 * @param ClassName
 *   The class name.<br>
 *   This name is required in order to call the static method "<tt>ClassName_MetaClass</tt>". It's a protection against inheritance.<br>
 *   <i>Problem if only the static method "StaticMetaClass" was provided:</i><pre>
 *   class C1: public CATCGMVirtual
 *   {
 *     CATCGMVirtualDeclareClass; // -> static CATCGMVirtualMetaClass &StaticMetaClass();
 *   };
 *   class C2: public C1
 *   {
 *     // No CATCGMVirtualDeclareClass
 *   </pre>
 *   <tt>C2::StaticMetaClass()</tt> returns in fact <tt>C1::StaticMetaClass()</tt>.
 */
#define CATCGMVirtualDeclareClass(ClassName)                                                                                                     \
                                                                                                                                                 \
  public:                                                                                                                                        \
    static const CATCGMVirtualMetaClass& ClassName##_MetaClass(); /* Access to the static member. The class name protects against inheritance */ \
    static const CATCGMVirtualMetaClass& StaticMetaClass();       /* Access to the static member without protection against inheritance. */      \
    virtual const CATCGMVirtualMetaClass& GetMetaClass() const

#define CATCGMVirtualImplementClass(ClassName, BaseClassName)                                                        \
    const CATCGMVirtualMetaClass& ClassName::ClassName##_MetaClass() {                                               \
        static CATCGMVirtualMetaClass* pMetaClass = NULL;                                                            \
        if(pMetaClass == NULL) pMetaClass = new CATCGMVirtualMetaClass(&BaseClassName::BaseClassName##_MetaClass()); \
        return *pMetaClass;                                                                                          \
    }                                                                                                                \
    const CATCGMVirtualMetaClass& ClassName::StaticMetaClass() {                                                     \
        return ClassName##_MetaClass();                                                                              \
    }                                                                                                                \
    const CATCGMVirtualMetaClass& ClassName::GetMetaClass() const {                                                  \
        return ClassName##_MetaClass();                                                                              \
    }

#endif
