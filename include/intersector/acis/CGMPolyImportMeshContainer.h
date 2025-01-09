/*******************************************************************/
/*    Copyright (c) 2019-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportMeshContainer_H
#define CGMPolyImportMeshContainer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMPolyImportContainers.h"
#include "CGMPolyImportMesh.h"

namespace CGMPolyImport {
    /**
     * A class storing a collection of <tt>Mesh</tt> objects.
     * This class is designed with "value-class" semantics and is intended to be
     * passed by value.
     */
    class ExportedByCGMCompPoly MeshContainer {
      public:
        /**
         *  A class defining an iterator over meshes inside a <tt>MeshContainer</tt>.
         */
        class ExportedByCGMCompPoly Iterator {
          public:
            /**
             * The copy constructor.
             */
            Iterator(Iterator const& other);  //= default;

            /**
             * The (non-virtual) destructor.
             */
            ~Iterator() {}

            /**
             * The assignment operator.
             */
            Iterator& operator=(Iterator const& other);  //= default;

            /**
             * The != operator.
             */
            bool operator!=(Iterator const& other) const;

            /**
             * The == operator.
             */
            bool operator==(Iterator const& iOther) const;

            /**
             * Check equality to another <tt>Mesh</tt> iterator
             * @param iOther
             *    The input iterator.
             * @return
             *    A Boolean value which indicates if <tt>this<tt> iterator
             *    and the input iterator are the same.
             */
            bool EqualTo(Iterator const& iOther) const;

            /**
             * The increment operator.
             */
            Iterator& operator++();

            /**
             * To increment the iterator.
             */
            void Increment();

            /**
             * The dereference operator.
             * Only the past-the-end iterator (queried from MeshContainer::end() ) is
             *not dereferenceable.
             * @return
             *	A <tt>Mesh</tt> object inside a <tt>MeshContainer</tt>.
             */
            Mesh operator*() const;

            /**
             * Returns a Mesh to which the iterator is pointing.
             * @return
             *	   A <tt>Mesh</tt> object inside a <tt>MeshContainer</tt>.
             */
            Mesh Get() const;

            /** @nodoc */
            Iterator(CGMPolyImport::IteratorImpl<Mesh>* impl);

          private:
            CATCGMValueClassImplHolder _implHolder;

            IteratorImpl<Mesh> const& GetImpl() const;
            IteratorImpl<Mesh>& GetImpl();
        };

        /**
         * Returns an iterator to the first <tt>Mesh</tt> object in the
         *<tt>MeshContainer</tt>.
         * @return
         *	The iterator to the first <tt>Mesh</tt> object in the
         *<tt>MeshContainer</tt>.  Note that this will be an invalid iterator if the
         *<tt>MeshContainer</tt> is empty.
         **/
        Iterator begin() const;

        /**
         * Returns an iterator past the end of the data in the <tt>MeshContainer</tt>,
         *which is an invalid iterator.
         * @return
         *	The (invalid) iterator past the end of the data.
         **/
        Iterator end() const;

        /**
         * Adds a <tt>Mesh</tt> object into the <tt>MeshContainer</tt>.
         * @param a
         *	The mesh to add into the container.
         **/
        void PushBack(Mesh m);

        /**
         * Returns the number of <tt>Mesh</tt> objects in the <tt>MeshContainer</tt>.
         * @return
         *	The number of <tt>Mesh</tt> objects in the <tt>MeshContainer</tt>.
         **/
        int Size() const;

        /**
         * Queries whether or not the <tt>MeshContainer</tt> is empty.
         * @return
         *	Whether or not the <tt>MeshContainer</tt> is empty.
         **/
        bool Empty() const;

        /**
         * The default constructor, which constructs an empty <tt>MeshContainer</tt>.
         */
        MeshContainer();

        /**
         * The (non-virtual) destructor.
         */
        ~MeshContainer() {}  //= default;

        /**
         * The assignment operator.
         */
        MeshContainer& operator=(MeshContainer const& other);  // = default;

        /**
         * The copy constructor.
         */
        MeshContainer(MeshContainer const& other);  // = default;

        /** @nodoc */
        MeshContainer(CGMPolyImport::ContainerImpl<Mesh>* impl);
        /** @nodoc */
        ContainerImpl<Mesh> const& GetImpl() const;
        /** @nodoc */
        ContainerImpl<Mesh>& GetImpl();

      private:
        CATCGMValueClassImplHolder _implHolder;
    };
}  // namespace CGMPolyImport
#endif
