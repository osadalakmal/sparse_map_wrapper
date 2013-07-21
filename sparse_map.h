#include <sparsehash/sparse_hash_map>
#include <unordered_map>
#include <vector>

class sparse_map : 
    public google::sparse_hash_map<std::string,std::string,std::hash<std::string> >
{
public:
    typedef std::string key_type;
    typedef std::string data_type;
    typedef std::string mapped_type;
    typedef std::string value_type;
    typedef std::hash<std::string> hasher;

    typedef google::sparse_hash_map<std::string,std::string,std::hash<std::string> > ht;
    typedef ht::allocator_type allocator_type;
    typedef ht::key_equal key_equal;
    typedef ht::size_type size_type;
    typedef ht::difference_type difference_type;
    typedef ht::pointer pointer;
    typedef ht::const_pointer const_pointer;
    typedef ht::reference reference;
    typedef ht::const_reference const_reference;

    typedef ht::iterator iterator;
    typedef ht::const_iterator const_iterator;
    typedef ht::local_iterator local_iterator;
    typedef ht::const_local_iterator const_local_iterator;

    // Iterator functions
    iterator begin()                               { return ht::begin(); }
    iterator end()                                 { return ht::end(); }
    const_iterator begin() const                   { return ht::begin(); }
    const_iterator end() const                     { return ht::end(); }

    // These come from tr1's unordered_map. For us, a bucket has 0 or 1 elements.
    local_iterator begin(size_type i)              { return ht::begin(i); }
    local_iterator end(size_type i)                { return ht::end(i); }
    const_local_iterator begin(size_type i) const  { return ht::begin(i); }
    const_local_iterator end(size_type i) const    { return ht::end(i); }

    // Accessor functions
    allocator_type get_allocator() const           { return ht::get_allocator(); }
    hasher hash_funct() const                      { return ht::hash_funct(); }
    hasher hash_function() const                   { return hash_funct(); }
    key_equal key_eq() const                       { return ht::key_eq(); }


    // Constructors
    sparse_map(size_type expected_max_items_in_table = 0,
            const hasher& hf = hasher())
        : sparse_hash_map(expected_max_items_in_table, hf) {
        }

    // We use the default copy constructor
    // We use the default operator=()
    // We use the default destructor

    void clear()                        { ht::clear(); }
    void swap(sparse_map& hs)      { ht::swap(static_cast<ht&>(hs)); }

    // Functions concerning size
    size_type size() const              { return ht::size(); }
    size_type max_size() const          { return ht::max_size(); }
    bool empty() const                  { return ht::empty(); }
    size_type bucket_count() const      { return ht::bucket_count(); }
    size_type max_bucket_count() const  { return ht::max_bucket_count(); }

    // These are tr1 methods.  bucket() is the bucket the key is or would be in.
    size_type bucket_size(size_type i) const    { return ht::bucket_size(i); }
    size_type bucket(const key_type& key) const { return ht::bucket(key); }
    float load_factor() const {
        return size() * 1.0f / bucket_count();
    }
    float max_load_factor() const {
        return ht::max_load_factor();
    }
    void max_load_factor(float new_grow) {
        ht::max_load_factor(new_grow);
    }
    // These aren't tr1 methods but perhaps ought to be.
    float min_load_factor() const {
        return ht::min_load_factor();
    }
    void min_load_factor(float new_shrink) {
        ht::min_load_factor(new_shrink);
    }
    // Deprecated; use min_load_factor() or max_load_factor() instead.
    void set_resizing_parameters(float shrink, float grow) {
        ht::set_resizing_parameters(shrink, grow);
    }

    void resize(size_type hint)         { ht::resize(hint); }
    void rehash(size_type hint)         { resize(hint); }      // the tr1 name

    // Lookup routines
    iterator find(const key_type& key)                 { return ht::find(key); }
    const_iterator find(const key_type& key) const     { return ht::find(key); }

    data_type& operator[](const key_type& key) {       // This is our value-add!
        // If key is in the hashtable, returns find(key)->second,
        // otherwise returns insert(value_type(key, T()).first->second.
        // Note it does not create an empty T unless the find fails.
        return ht::operator[](key);
    }

    size_type count(const key_type& key) const         { return ht::count(key); }

    std::pair<iterator, iterator> equal_range(const key_type& key) {
        return ht::equal_range(key);
    }
    std::pair<const_iterator, const_iterator> equal_range(const key_type& key)
        const {
            return ht::equal_range(key);
        }

    // Insertion routines
    void insert(const std::string& key, const std::string& val) {
        ht::insert(std::make_pair(key,val));
    }
    template <class InputIterator> void insert(InputIterator f, InputIterator l) {
        ht::insert(f, l);
    }
    void insert(const_iterator f, const_iterator l) {
        ht::insert(f, l);
    }

    // Deletion routines
    // THESE ARE NON-STANDARD!  I make you specify an "impossible" key
    // value to identify deleted buckets.  You can change the key as
    // time goes on, or get rid of it entirely to be insert-only.
    void set_deleted_key(const key_type& key)   {
        ht::set_deleted_key(key);
    }
    void clear_deleted_key()                    { ht::clear_deleted_key(); }
    key_type deleted_key() const                { return ht::deleted_key(); }

    // These are standard
    size_type erase(const key_type& key)               { return ht::erase(key); }
    void erase(iterator it)                            { ht::erase(it); }
    void erase(iterator f, iterator l)                 { ht::erase(f, l); }


    // Comparison
    bool operator==(const sparse_map& hs) const   { return ht::operator==(static_cast<ht>(hs)); }
    bool operator!=(const sparse_map& hs) const   { return ht::operator!=(static_cast<ht>(hs)); }
};

