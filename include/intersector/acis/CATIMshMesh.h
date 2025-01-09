#ifndef CATIMshMesh_H
#define CATIMshMesh_H

// CATIMshMesh -*- C++ -*-

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021-2022
//=============================================================================
/**
 * @CAA2Level L0
 * @CAA2Usage U3
 */

//=============================================================================
//
// CATIMshMesh :
// Interface of the minimal mesh
//
//=============================================================================

#include "CATMshBase.h"
#include "ExportedByCATMshMesherCore.h"

/**
 * Class holding any entity base tag
 * Tags are essentially unsigned integers
 */
class CATMshBaseTag {
public:
    /**
     * Constructor for an empty base tag
     */
    explicit CATMshBaseTag() noexcept : _tag(0) {}

    /**
     * Constructor for a given unsigned integer
     * @param tag
     *   the value of the tag
     */
    explicit CATMshBaseTag(const unsigned int tag) noexcept : _tag(tag){};

    /**
     * Copy constructor
     * @param tag
     *   the tag
     */
    CATMshBaseTag(const CATMshBaseTag& tag) noexcept { _tag = tag._tag; };

    /**
     * Returns whether the tag is empty or not
     */
    bool IsEmpty() const {
        if (!_tag) return true;
        return false;
    }

    /**
     * Returns the value of the tag
     */
    unsigned int Get() const { return _tag; }

    /**
     * Ordering operator
     */
    bool operator<(const CATMshBaseTag& tag) const { return _tag < tag.Get(); }

    /**
     * Equality operator
     */
    bool operator==(const CATMshBaseTag& tag) const {
        return _tag == tag.Get();
    }

    /**
     * Inequality operator
     */
    bool operator!=(const CATMshBaseTag& tag) const { return !operator==(tag); }

private:
    unsigned int _tag;
};

/**
 * Class holding any entity tag
 * A CATMshTag is a CATMshBaseTag that can be made from other CATMshBaseTags
 */
class CATMshTag final : public CATMshBaseTag {
public:
    /**
     * Constructor for an empty tag
     */
    explicit CATMshTag() noexcept : CATMshBaseTag() {}

    /**
     * Constructor for a given unsigned integer
     * @param tag
     *   the value of the tag
     */
    explicit CATMshTag(const unsigned int tag) noexcept : CATMshBaseTag(tag) {}
};

/**
 * Class holding any entity index
 * Indices are essentially unsigned integers
 */
template <class CRTP>
class CATMshIndex {
public:
    using crtp_type = CRTP;

    /**
     * Returns whether the index is empty or not
     */
    bool IsEmpty() const {
        if (!_index) return true;
        return false;
    }

    /**
     * Returns the value of the index
     */
    unsigned int Get() const { return _index; }

    /**
     * Ordering operator forbidden
     */
    bool operator<(const CATMshIndex& other) const {
        return Get() < other.Get();
    }

    /**
     * Equality operator forbidden
     */
    bool operator==(const CATMshIndex& other) const {
        return Get() == other.Get();
    }

    /**
     * Inequality operator forbidden
     */
    bool operator!=(const CATMshIndex& other) const {
        return Get() != other.Get();
    }

private:
    explicit CATMshIndex() noexcept : CATMshIndex(0) {}

    explicit CATMshIndex(const unsigned int idx) noexcept : _index(idx) {}

    friend crtp_type;

private:
    unsigned int _index;
};

/**
 * Class holding a vertex index
 */
class CATMshVertexIndex final : public CATMshIndex<CATMshVertexIndex> {
public:
    using base_type = CATMshIndex<CATMshVertexIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshVertexIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshVertexIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a vertex index
 */
class CATMshElementIndex final : public CATMshIndex<CATMshElementIndex> {
public:
    using base_type = CATMshIndex<CATMshElementIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshElementIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshElementIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a domain index
 */
class CATMshDomainIndex final : public CATMshIndex<CATMshDomainIndex> {
public:
    using base_type = CATMshIndex<CATMshDomainIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshDomainIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshDomainIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a topo face index
 */
class CATMshTopoFaceIndex final : public CATMshIndex<CATMshTopoFaceIndex> {
public:
    using base_type = CATMshIndex<CATMshTopoFaceIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshTopoFaceIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshTopoFaceIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a topo edge index
 */
class CATMshTopoEdgeIndex final : public CATMshIndex<CATMshTopoEdgeIndex> {
public:
    using base_type = CATMshIndex<CATMshTopoEdgeIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshTopoEdgeIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshTopoEdgeIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a topo vertex index
 */
class CATMshTopoVertexIndex final : public CATMshIndex<CATMshTopoVertexIndex> {
public:
    using base_type = CATMshIndex<CATMshTopoVertexIndex>;

    /**
     * Constructor for an empty index
     */
    explicit CATMshTopoVertexIndex() noexcept : base_type() {}

    /**
     * Constructor for a given unsigned integer
     * @param idx
     *   the value of the index
     */
    explicit CATMshTopoVertexIndex(const unsigned int idx) noexcept
        : base_type(idx) {}
};

/**
 * Class holding a mesh vertex
 */
class CATMshVertex final {
public:
    /**
     * Constructor for an empty vertex
     */
    explicit CATMshVertex() noexcept
        : _vertexIndex(CATMshVertexIndex()), _tag(CATMshTag()) {}

    /**
     * Constructor
     * @param vertexIndex
     *   the corresponding vertex index
     * @param xyz[3]
     *   vertex coordinates
     */
    explicit CATMshVertex(const CATMshVertexIndex& vertexIndex,
                          const double (&xyz)[3]) noexcept
        : CATMshVertex(vertexIndex, xyz, CATMshTag()) {}

    /**
     * Constructor
     * @param vertexIndex
     *   the corresponding vertex index
     * @param xyz[3]
     *   vertex coordinates
     * @param tag
     *   vertex tag
     */
    explicit CATMshVertex(const CATMshVertexIndex& vertexIndex,
                          const double (&xyz)[3], const CATMshTag& tag) noexcept
        : _vertexIndex(vertexIndex), _xyz{xyz[0], xyz[1], xyz[2]}, _tag(tag) {}

    /**
     * Returns whether the vertex is empty or not
     */
    bool IsEmpty() const { return _vertexIndex.IsEmpty(); }

    /**
     * Returns the corresponding vertex index
     */
    CATMshVertexIndex GetIndex() const { return _vertexIndex; }

    /**
     * Returns the X coordinate as double
     */
    double GetX() const { return _xyz[0]; }

    /**
     * Returns the Y coordinate as double
     */
    double GetY() const { return _xyz[1]; }

    /**
     * Returns the Z coordinate as double
     */
    double GetZ() const { return _xyz[2]; }

    /**
     * Returns the vertex tag
     */
    CATMshTag GetTag() const { return _tag; }

private:
    CATMshVertexIndex _vertexIndex;
    double _xyz[3];
    CATMshTag _tag;
};

/**
 * Class holding a mesh element
 */
class CATMshElement final {
public:
    /**
     * maximum number of possible vertices per element
     */
    static const int maxNumberOfVertices = 27;

    /**
     * Possible types of an element
     */
    enum class Type {
        Unknown,
        Edge2,
        Edge3,
        Triangle3,
        Triangle6,
        Quadrangle4,
        Quadrangle9,
        Tetrahedron4,
        Tetrahedron10,
        Hexahedron8,
        Hexahedron27,
        Prism6,
        Prism18,
        Pyramid5,
        Pyramid14,
    };

    /**
     * Possible orientations of an element
     */
    enum class Orientation {
        Unknown,
        Forward,
        Reverse,
        Full,
    };

    /**
     * Iterator that allows to iterate through the vertices of an element
     */
    class Iterator {
    public:
        using value_type = CATMshVertexIndex;

        explicit Iterator(value_type* ptr) noexcept : _ptr(ptr){};

        value_type operator*() const { return *_ptr; };

        Iterator& operator++() {
            _ptr++;
            return *this;
        };

        Iterator operator++(int) {
            Iterator tmp(*this);
            _ptr++;
            return tmp;
        }

        Iterator& operator+=(int n) {
            _ptr += n;
            return *this;
        }

        Iterator operator+(int n) const { return Iterator(_ptr + n); }

        bool operator==(const Iterator& other) { return _ptr == other._ptr; }
        bool operator!=(const Iterator& other) { return _ptr != other._ptr; }

    private:
        value_type* _ptr;
    };

    /**
     * Const Iterator that allows to iterate through the vertices of an element
     */
    class ConstIterator {
    public:
        using value_type = const CATMshVertexIndex;

        explicit ConstIterator(value_type* ptr) noexcept : _ptr(ptr){};

        value_type operator*() const { return *_ptr; };

        ConstIterator& operator++() {
            _ptr++;
            return *this;
        };

        ConstIterator operator++(int) {
            ConstIterator tmp(*this);
            _ptr++;
            return tmp;
        }

        ConstIterator& operator+=(int n) {
            _ptr += n;
            return *this;
        }

        ConstIterator operator+(int n) const { return ConstIterator(_ptr + n); }

        bool operator==(const ConstIterator& other) {
            return _ptr == other._ptr;
        }

        bool operator!=(const ConstIterator& other) {
            return _ptr != other._ptr;
        }

    private:
        value_type* _ptr;
    };

    /**
     * Constructor for an empty element
     */
    explicit CATMshElement() noexcept
        : _elementType(Type::Unknown),
          _elementOrientation(Orientation::Unknown),
          _elementIndex(CATMshElementIndex()),
          _tag(CATMshTag()) {}

    /**
     * Constructor
     * @param elementType
     * 	the type of the element
     * @param elementIndex
     * 	the index of the element
     * @param vertexIndices
     * 	the list of vertices of the element
     */
    explicit CATMshElement(
        const Type elementType, const CATMshElementIndex& elementIndex,
        const CATMshVertexIndex (&vertexIndices)[maxNumberOfVertices]) noexcept
        : CATMshElement(elementType, Orientation::Unknown, elementIndex,
                        vertexIndices, CATMshTag()) {}

    /**
     * Constructor
     * @param elementType
     * 	the type of the element
     * @param elementIndex
     * 	the index of the element
     * @param vertexIndices
     * 	the list of vertices of the element
     * @param tag
     * 	the tag of the element
     */
    explicit CATMshElement(
        const Type elementType, const Orientation orientation,
        const CATMshElementIndex& elementIndex,
        const CATMshVertexIndex (&vertexIndices)[maxNumberOfVertices],
        const CATMshTag& tag) noexcept
        : _elementType(elementType),
          _elementOrientation(orientation),
          _elementIndex(elementIndex),
          _tag(tag) {
        auto n = GetNumberOfVertices();
        for (auto i = 1; i <= n; i++)
            _vertexIndices[i - 1] = vertexIndices[i - 1];
    }

    /**
     * Returns an iterator pointing to the first vertex of the element
     */
    Iterator begin() { return Iterator(&_vertexIndices[0]); }

    /**
     * Returns a const iterator pointing to the first vertex of the element
     */
    ConstIterator begin() const { return cbegin(); }

    /**
     * Returns a const iterator pointing to the first vertex of the element
     */
    ConstIterator cbegin() const { return ConstIterator(&_vertexIndices[0]); }

    /**
     * Returns an iterator pointing to past the last vertex of the element
     */
    Iterator end() { return Iterator(&_vertexIndices[GetNumberOfVertices()]); }

    /**
     * Returns an iterator pointing to past the last vertex of the element
     */
    ConstIterator end() const { return cend(); }

    /**
     * Returns an iterator pointing to past the last vertex of the element
     */
    ConstIterator cend() const {
        return ConstIterator(&_vertexIndices[GetNumberOfVertices()]);
    }

    /**
     * Accesses the i-th element index.
     */
    CATMshVertexIndex operator[](int index) const {
        return *(_vertexIndices + index);
    }

    /**
     * Returns whether the element is empty or not
     */
    bool IsEmpty() const { return _elementIndex.IsEmpty(); }

    /**
     * Returns the corresponding element index
     */
    CATMshElementIndex GetIndex() const { return _elementIndex; }

    /**
     * Returns the element type
     */
    Type GetType() const { return _elementType; }

    /**
     * Returns the element orientation
     */
    Orientation GetOrientation() const noexcept { return _elementOrientation; }

    /**
     * Returns the number of vertices of the element
     */
    int GetNumberOfVertices() const {
        if (_elementType == CATMshElement::Type::Edge2) {
            return 2;
        } else if (_elementType == CATMshElement::Type::Edge3) {
            return 3;
        } else if (_elementType == CATMshElement::Type::Triangle3) {
            return 3;
        } else if (_elementType == CATMshElement::Type::Triangle6) {
            return 6;
        } else if (_elementType == CATMshElement::Type::Quadrangle4) {
            return 4;
        } else if (_elementType == CATMshElement::Type::Quadrangle9) {
            return 9;
        } else if (_elementType == CATMshElement::Type::Tetrahedron4) {
            return 4;
        } else if (_elementType == CATMshElement::Type::Tetrahedron10) {
            return 10;
        } else if (_elementType == CATMshElement::Type::Pyramid5) {
            return 5;
        } else if (_elementType == CATMshElement::Type::Pyramid14) {
            return 14;
        } else if (_elementType == CATMshElement::Type::Prism6) {
            return 6;
        } else if (_elementType == CATMshElement::Type::Prism18) {
            return 18;
        } else if (_elementType == CATMshElement::Type::Hexahedron8) {
            return 8;
        } else if (_elementType == CATMshElement::Type::Hexahedron27) {
            return 27;
        } else {
            return 0;
        }
    }

    /**
     * Returns the number of linear vertices of the element
     */
    int GetNumberOfLinearVertices() const {
        if (_elementType == CATMshElement::Type::Edge2 ||
            _elementType == CATMshElement::Type::Edge3) {
            return 2;
        } else if (_elementType == CATMshElement::Type::Triangle3 ||
                   _elementType == CATMshElement::Type::Triangle6) {
            return 3;
        } else if (_elementType == CATMshElement::Type::Quadrangle4 ||
                   _elementType == CATMshElement::Type::Quadrangle4) {
            return 4;
        } else if (_elementType == CATMshElement::Type::Tetrahedron4 ||
                   _elementType == CATMshElement::Type::Tetrahedron10) {
            return 4;
        } else if (_elementType == CATMshElement::Type::Pyramid5 ||
                   _elementType == CATMshElement::Type::Pyramid14) {
            return 5;
        } else if (_elementType == CATMshElement::Type::Prism6 ||
                   _elementType == CATMshElement::Type::Prism18) {
            return 6;
        } else if (_elementType == CATMshElement::Type::Hexahedron8 ||
                   _elementType == CATMshElement::Type::Hexahedron27) {
            return 8;
        } else {
            return 0;
        }
    }

    /**
     * Returns the element tag
     */
    CATMshTag GetTag() const { return _tag; }

    /**
     * Returns whether the element belongs to a line or not
     */
    bool IsOnLine() const {
        if (_elementType == CATMshElement::Type::Edge2 ||
            _elementType == CATMshElement::Type::Edge3) {
            return true;
        }
        return false;
    }

    /**
     * Returns whether the element belongs to the surface or not
     */
    bool IsOnSurface() const {
        if (_elementType == CATMshElement::Type::Triangle3 ||
            _elementType == CATMshElement::Type::Triangle6 ||
            _elementType == CATMshElement::Type::Quadrangle4 ||
            _elementType == CATMshElement::Type::Quadrangle9) {
            return true;
        }
        return false;
    }

    /**
     * Returns whether the element belongs to the volume or not
     */
    bool IsInVolume() const {
        if (_elementType == CATMshElement::Type::Tetrahedron4 ||
            _elementType == CATMshElement::Type::Tetrahedron10 ||
            _elementType == CATMshElement::Type::Pyramid5 ||
            _elementType == CATMshElement::Type::Pyramid14 ||
            _elementType == CATMshElement::Type::Prism6 ||
            _elementType == CATMshElement::Type::Prism18 ||
            _elementType == CATMshElement::Type::Hexahedron8 ||
            _elementType == CATMshElement::Type::Hexahedron27) {
            return true;
        }
        return false;
    }

    /**
     * Returns whether the element is linear or not
     */
    bool IsLinear() const {
        if (_elementType == CATMshElement::Type::Edge2 ||
            _elementType == CATMshElement::Type::Triangle3 ||
            _elementType == CATMshElement::Type::Quadrangle4 ||
            _elementType == CATMshElement::Type::Tetrahedron4 ||
            _elementType == CATMshElement::Type::Pyramid5 ||
            _elementType == CATMshElement::Type::Prism6 ||
            _elementType == CATMshElement::Type::Hexahedron8) {
            return true;
        }
        return false;
    }

    /**
     * Returns whether the element is quadratic or not
     */
    bool IsQuadratic() const {
        if (_elementType == CATMshElement::Type::Edge3 ||
            _elementType == CATMshElement::Type::Triangle6 ||
            _elementType == CATMshElement::Type::Quadrangle9 ||
            _elementType == CATMshElement::Type::Tetrahedron10 ||
            _elementType == CATMshElement::Type::Pyramid14 ||
            _elementType == CATMshElement::Type::Prism18 ||
            _elementType == CATMshElement::Type::Hexahedron27) {
            return true;
        }
        return false;
    }

private:
    Type _elementType;
    Orientation _elementOrientation;
    CATMshElementIndex _elementIndex;
    CATMshTag _tag;
    CATMshVertexIndex _vertexIndices[maxNumberOfVertices];
};

/**
 * Class holding a container of objects
 * It provides accessor and iterator through the container content
 */
template <class OBJECT, class INDEX>
class CATMshMeshContainer : public CATMshBase {
public:
    using object_type = OBJECT;
    using index_type = INDEX;

    /**
     * Constructor
     */
    explicit CATMshMeshContainer() noexcept {};

    /**
     * Destructor
     */
    virtual ~CATMshMeshContainer() = default;

    /**
     * Iterator that allows to iterate through the container content
     */
    class Iterator {
    public:
        /**
         * Iterator default constructor
         * @param parent
         *   the parent container
         */
        explicit Iterator(CATMshMeshContainer& parent)
            : Iterator(parent, index_type()) {}

        /**
         * Iterator constructor at starting index
         * @param parent
         *   the parent container
         * @param objectIndex
         *   starting object index
         */
        explicit Iterator(CATMshMeshContainer& parent, index_type objectIndex)
            : _objectIndex(objectIndex), _parent(parent) {}

        /**
         * Operator to get the object
         */
        object_type operator*() const { return _parent.Get(_objectIndex); }

        /**
         * Get the current index
         */
        index_type GetIndex() const { return _objectIndex; }

        /**
         * Operator to move to the next index
         */
        Iterator& operator++() {
            _objectIndex = _parent.Next(_objectIndex);
            return *this;
        }

        /**
         * Equality means iterators are at same index
         */
        bool operator==(const Iterator& other) {
            return _objectIndex == other._objectIndex;
        }

        /**
         * Inequality means iterators are not at same index
         */
        bool operator!=(const Iterator& other) {
            return _objectIndex != other._objectIndex;
        }

    private:
        index_type _objectIndex;
        CATMshMeshContainer& _parent;
    };

    /**
     * Returns an iterator pointing to the first object in the container
     */
    virtual Iterator begin() = 0;

    /**
     * Returns an iterator pointing to past the last object in the container
     */
    virtual Iterator end() = 0;

    /*
     * Returns the number of objects in the container
     */
    virtual unsigned int Size() {
        auto i = 0;
        for (const auto& x : *this) i++;
        return i;
    }

    /**
     * Returns the contained object corresponding to the given index
     * @param objectIndex
     *   the object index
     */
    virtual object_type Get(const index_type& objectIndex) const = 0;

    /**
     * Returns the next index for a given index
     * @param objectIndex
     *   the object index
     */
    virtual index_type Next(const index_type& objectIndex) const = 0;
};

/**
 * Class holding a clonable container of objects
 */
template <class OBJECT, class INDEX>
class CATMshMeshCloneableContainer : public CATMshMeshContainer<OBJECT, INDEX> {
public:
    /**
     * Default constructor of container
     */
    explicit CATMshMeshCloneableContainer() noexcept {}

    /**
     * Class destructor (no dynamic storage so nothing special to be done)
     */
    virtual ~CATMshMeshCloneableContainer() = default;

    /**
     * Clones the container
     */
    virtual CATMshMeshCloneableContainer* Clone() const = 0;
};

/**
 * Class holding a mesh topology
 */
template <class CRTP, class INDEX>
class CATMshTopology {
public:
    using crtp_type = CRTP;
    using index_type = INDEX;

    /**
     * Returns the index
     */
    index_type GetIndex() const { return _index; }

    /**
     * Returns the tag
     */
    CATMshTag GetTag() const { return _tag; }

private:
    explicit CATMshTopology(const index_type& index, const CATMshTag& tag)
        : _index(index), _tag(tag) {}

    friend crtp_type;

private:
    index_type _index;
    CATMshTag _tag;
};

/**
 * Class holding a mesh topology that contains elements
 */
template <class CRTP, class INDEX>
class CATMshTopologyElements
    : public CATMshTopology<CATMshTopologyElements<CRTP, INDEX>, INDEX> {
public:
    using crtp_type = CRTP;
    using index_type = INDEX;

    using base_type =
        CATMshTopology<CATMshTopologyElements<crtp_type, index_type>,
                       index_type>;

    /**
     * Clonable container of elements
     */
    using container =
        CATMshMeshCloneableContainer<CATMshElement, CATMshElementIndex>;

    /**
     * Uses the container iterator
     */
    using Iterator = container::Iterator;

    /**
     * Returns an iterator pointing to the first object in the container
     */
    Iterator begin() { return _localContainer->begin(); }

    /**
     * Returns an iterator pointing to past the last object in the container
     */
    Iterator end() { return _localContainer->end(); }

    /*
     * Returns container of elements in the topology
     */
    const container& GetContainerOfElements() const { return *_localContainer; }

private:
    explicit CATMshTopologyElements(const index_type& index,
                                    const CATMshTag& tag,
                                    const container& elementContainer)
        : base_type(index, tag) {
        _localContainer = elementContainer.Clone();
    }

    ~CATMshTopologyElements() {
        if (_localContainer)
            _localContainer->Release(), _localContainer = nullptr;
    }

    friend crtp_type;

private:
    container* _localContainer;
};

/**
 * Class holding a topological mesh domain
 * It contains a container of elements that belong to the topological domain
 */
class CATMshDomain final
    : public CATMshTopologyElements<CATMshDomain, CATMshDomainIndex> {
public:
    using object_type = CATMshDomain;
    using index_type = CATMshDomainIndex;
    using base_type = CATMshTopologyElements<object_type, index_type>;
    using container = typename base_type::container;

    /**
     * Constructor
     * @param index
     * 	the topological domain index
     * @param tag
     * 	the topological domain tag
     * @param elementContainer
     * 	the container of elements in the topological domain
     */
    explicit CATMshDomain(const index_type& index, const CATMshTag& tag,
                          const container& elementContainer)
        : base_type(index, tag, elementContainer) {}
};

/**
 * Class holding a topological mesh face
 * It contains a container of elements that belong to the topological face
 */
class CATMshTopoFace final
    : public CATMshTopologyElements<CATMshTopoFace, CATMshTopoFaceIndex> {
public:
    using object_type = CATMshTopoFace;
    using index_type = CATMshTopoFaceIndex;
    using base_type = CATMshTopologyElements<object_type, index_type>;
    using container = typename base_type::container;

    /**
     * Constructor
     * @param index
     * 	the topological face index
     * @param tag
     * 	the topological face tag
     * @param elementContainer
     * 	the container of elements in the topological face
     */
    explicit CATMshTopoFace(const index_type& index, const CATMshTag& tag,
                            const container& elementContainer)
        : base_type(index, tag, elementContainer) {}
};

/**
 * Class holding a topological mesh edge
 * It contains a container of elements that belong to the topological edge
 */
class CATMshTopoEdge final
    : public CATMshTopologyElements<CATMshTopoEdge, CATMshTopoEdgeIndex> {
public:
    using object_type = CATMshTopoEdge;
    using index_type = CATMshTopoEdgeIndex;
    using base_type = CATMshTopologyElements<object_type, index_type>;
    using container = typename base_type::container;

    /**
     * Constructor
     * @param index
     * 	the topological edge index
     * @param tag
     * 	the topological edge tag
     * @param elementContainer
     * 	the container of elements in the topological edge
     */
    explicit CATMshTopoEdge(const index_type& index, const CATMshTag& tag,
                            const container& elementContainer)
        : base_type(index, tag, elementContainer) {}
};

/**
 * Class holding a mesh topo vertex
 * It contains a container of vertices that belong to the topological vertex
 */
class CATMshTopoVertex final
    : public CATMshTopology<CATMshTopoVertex, CATMshTopoVertexIndex> {
public:
    using base_type = CATMshTopology<CATMshTopoVertex, CATMshTopoVertexIndex>;

    /**
     * Clonable container of vertices
     */
    using container =
        CATMshMeshCloneableContainer<CATMshVertex, CATMshVertexIndex>;

    /**
     * Uses the container iterator
     */
    using Iterator = container::Iterator;

    /**
     * Constructor
     * @param topoVertexIndex
     * 	the topological vertex index
     * @param topoVertexTag
     * 	the topological vertex tag
     * @param vertices
     *  the container of vertices in the topological vertex
     */
    explicit CATMshTopoVertex(const CATMshTopoVertexIndex& topoVertexIndex,
                              const CATMshTag& topoVertexTag,
                              const container& vertices)
        : base_type(topoVertexIndex, topoVertexTag), _vertices(nullptr) {
        _vertices = vertices.Clone();
    }

    /**
     * Constructor
     */
    ~CATMshTopoVertex() {
        if (_vertices) _vertices->Release(), _vertices = nullptr;
    }

    /**
     * Returns an iterator pointing to the first object in the container
     */
    Iterator begin() { return _vertices->begin(); }

    /**
     * Returns an iterator pointing to past the last object in the container
     */
    Iterator end() { return _vertices->end(); }

    /*
     * Returns container of vertices in the topological vertex
     */
    const container& GetContainerOfVertices() const { return *_vertices; }

private:
    CATMshVertexIndex _vertexIndex;
    container* _vertices;
};

/**
 * Class holding a tag system
 */
class CATMshTagSystem : public CATMshBase {
public:
    /**
     * Constructor
     */
    explicit CATMshTagSystem() noexcept {}

    /*
     * Destructor
     */
    virtual ~CATMshTagSystem() = default;

    /**
     * Iterator that allows to iterate through the base tags of a tag
     */
    class Iterator {
    public:
        explicit Iterator(CATMshTagSystem& parent, const CATMshTag tag,
                          unsigned int iBaseTag)
            : _parent(parent), _tag(tag), _iBaseTag(iBaseTag) {}

        CATMshBaseTag operator*() const {
            return _parent.GetBaseTag(_tag, _iBaseTag);
        }

        Iterator& operator++() {
            _iBaseTag++;
            return *this;
        }

        bool operator==(const Iterator& other) {
            if (_tag == other._tag && _iBaseTag == other._iBaseTag) return true;
            return false;
        }

        bool operator!=(const Iterator& other) { return !(*this == other); }

    private:
        unsigned int _iBaseTag;
        const CATMshTag _tag;
        CATMshTagSystem& _parent;
    };

    /**
     * Returns an iterator pointing to the first base tag for a given tag
     * @param tag
     * 	the tag
     */
    Iterator begin(const CATMshTag& tag) { return Iterator(*this, tag, 1); }

    /**
     * Returns an iterator pointing to the last base tag for a given tag
     * @param tag
     * 	the tag
     */
    Iterator end(const CATMshTag& tag) {
        return Iterator(*this, tag, GetBaseTagCount(tag) + 1);
    }

    /**
     * Returns whether the tag is composite or not
     * @param tag
     * 	the tag
     */
    bool IsComposite(const CATMshTag& tag) { return GetBaseTagCount(tag) > 1; }

    /**
     * Returns the number of base tags for a given tag
     * @param tag
     * 	the tag
     */
    virtual unsigned int GetBaseTagCount(const CATMshTag& tag) = 0;

    /**
     * Returns the i-th base tag for a given tag
     * @param tag
     * 	the tag
     * @param iBaseTag
     *  the i-th base
     */
    virtual CATMshBaseTag GetBaseTag(const CATMshTag& tag,
                                     const unsigned int iBaseTag) = 0;
};

/**
 * Class holding a mesh
 */
class ExportedByCATMshMesherCore CATIMshMesh : public CATMshBase {
public:
    /**
     * Container of vertices
     */
    using verticesContainer =
        CATMshMeshContainer<CATMshVertex, CATMshVertexIndex>;

    /**
     * Container of elements
     */
    using elementsContainer =
        CATMshMeshContainer<CATMshElement, CATMshElementIndex>;

    /**
     * Container of topological domains
     */
    using domainsContainer =
        CATMshMeshContainer<CATMshDomain, CATMshDomainIndex>;

    /**
     * Container of topological faces
     */
    using topoFacesContainer =
        CATMshMeshContainer<CATMshTopoFace, CATMshTopoFaceIndex>;

    /**
     * Container of topological edges
     */
    using topoEdgesContainer =
        CATMshMeshContainer<CATMshTopoEdge, CATMshTopoEdgeIndex>;

    /**
     * Container of topological vertices
     */
    using topoVerticesContainer =
        CATMshMeshContainer<CATMshTopoVertex, CATMshTopoVertexIndex>;

    /*
     * Tag system
     */
    using tagSystem = CATMshTagSystem;

    /**
     * Constructor
     */
    explicit CATIMshMesh() noexcept;

    /**
     * Destructor
     */
    virtual ~CATIMshMesh();

    /**
     * Returns a new container of vertices
     */
    virtual verticesContainer* NewVerticesContainer() const = 0;

    /**
     * Returns a new container of elements
     */
    virtual elementsContainer* NewElementsContainer() const = 0;

    /**
     * Returns a new container of topological domains
     */
    virtual domainsContainer* NewDomainsContainer() const { return nullptr; }

    /**
     * Returns a new container of topological domains
     */
    virtual topoFacesContainer* NewTopoFacesContainer() const {
        return nullptr;
    }

    /**
     * Returns a new container of topological edges
     */
    virtual topoEdgesContainer* NewTopoEdgesContainer() const {
        return nullptr;
    }

    /**
     * Returns a new container of topological vertices
     */
    virtual topoVerticesContainer* NewTopoVerticesContainer() const {
        return nullptr;
    }

    /*
     * Returns a new tag system
     */
    virtual CATMshTagSystem* NewTagSystem() const { return nullptr; }
};

#endif
