/*******************************************************************/
/*    Copyright (c) 2017-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CGMPolyImportNodeContainer_H
#define CGMPolyImportNodeContainer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATCGMValueClassImplHolder.h"
#include "CGMCompPoly.h"
#include "CGMMeshGeometry.h"
#include "CGMPolyImportGeometryContainers.h"

namespace CGMPolyImport {
    /**
     * A class storing a collection of nodes all belonging to the same <tt>Mesh</tt>
     * object. This class is designed with "value-class" semantics and is intended
     * to be passed by value.
     */
    class ExportedByCGMCompPoly NodeContainer {
      public:
        /**
         *  A class defining an iterator over nodes inside a <tt>NodeContainer</tt>.
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
             * Check equality to another <tt>Node</tt> iterator
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
             * Only the past-the-end iterator (queried from NodeContainer::end() ) is
             *not dereferenceable.
             * @return
             *	A <tt>Node</tt> object inside a <tt>NodeContainer</tt>.
             */
            Node operator*() const;

            /**
             * Returns a Node to which the iterator is pointing.
             * @return
             *    A <tt>Node</tt> object inside a <tt>NodeContainer</tt>.
             */
            Node Get() const;

            /** @nodoc */
            Iterator(CGMPolyImport::GeometryIteratorImpl<Node>* impl);

          private:
            CATCGMValueClassImplHolder _implHolder;

            GeometryIteratorImpl<Node> const& GetImpl() const;
            GeometryIteratorImpl<Node>& GetImpl();
        };

        /**
         * Returns an iterator to the first <tt>Node</tt> object in the
         *<tt>NodeContainer</tt>.
         * @return
         *	The iterator to the first <tt>Node</tt> object in the
         *<tt>NodeContainer</tt>.  Note that this will be an invalid iterator if the
         *<tt>NodeContainer</tt> is empty.
         **/
        Iterator begin() const;

        /**
         * Returns an iterator past the end of the data in the <tt>NodeContainer</tt>,
         *which is an invalid iterator.
         * @return
         *	The (invalid) iterator past the end of the data.
         **/
        Iterator end() const;

        /**
         * Returns the number of <tt>Node</tt> objects in the <tt>NodeContainer</tt>.
         * @return
         *	The number of <tt>Node</tt> objects in the <tt>NodeContainer</tt>.
         **/
        int Size() const;

        /**
         * Queries whether or not the <tt>NodeContainer</tt> is empty.
         * @return
         *	Whether or not the <tt>NodeContainer</tt> is empty.
         **/
        bool Empty() const;

        /**
         * The default constructor, which constructs an empty <tt>NodeContainer</tt>.
         */
        NodeContainer();

        /**
         * Returns the unique mesh where all the nodes live.
         * @return
         *	The mesh containing the nodes.  Note that if the container is empty, this
         *method throws.
         **/
        Mesh GetMesh() const;

        /**
         * The assignment operator.
         */
        NodeContainer& operator=(NodeContainer const& other);  //= default;

        /**
         * The copy constructor.
         */
        NodeContainer(NodeContainer const& other);  //= default;

        /**
         * The (non-virtual) destructor.
         */
        ~NodeContainer() {}

        /** @nodoc */
        NodeContainer(CGMPolyImport::GeometryContainerImpl<Node>* impl);

      private:
        CATCGMValueClassImplHolder _implHolder;
        GeometryContainerImpl<Node> const& GetImpl() const;
    };
}  // namespace CGMPolyImport
#endif
