#ifndef NC_LIB_STACK_HPP
#	define NC_LIB_STACK_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
/* defines */
/* typedefs */
/// stack_iterator_type
/// description:
/// interaction:
template<typename tname>
class nc_stack_iter_t
{
public:
    using iter_t = nc_stack_iter_t<tname>;
    using iter_tc = const iter_t;
    using link_t = iter_t*;
    using link_tc = const link_t;
    using data_t = tname*;
    using data_tc = const data_t;
    using elem_t = tname;
    using elem_tc = const elem_t;
    using step_t = v1s64_t;
    using step_tc = const step_t;
public:
    /* codetor */
    constexpr inline nc_stack_iter_t() : m_data(NC_NULL), m_next(NC_NULL) { }
    constexpr inline nc_stack_iter_t(data_t data) : m_data(data), m_next(NC_NULL) { }
    inline nc_stack_iter_t(iter_tc& copy) : nc_stack_iter_t() { operator=(copy); }
    inline nc_stack_iter_t(iter_t&& copy) : nc_stack_iter_t() { operator=(copy); }
    inline ~nc_stack_iter_t() { NC_MEM_DEL_ONE(iter_t, m_next); }
    /* getters */
    /** link  **/
    inline link_t get_link() { return m_next; }
    inline link_tc get_link() const { return m_next; }
    inline link_t get_link(step_t step) {
        link_t link = m_next;
        while((link->has_next() != NC_NULL) && (step-- > NC_ZERO)) { link->set_next(); }
        return link;
    }
    inline link_tc get_link(step_t step) const {
        link_t link = m_next;
        while((link->has_next() != NC_NULL) && (step-- > NC_ZERO)) { link->set_next(); }
        return link;
    }
    /** iter  **/
    inline iter_t get_iter()        { return *m_next; }
    inline iter_tc get_iter() const { return *m_next; }
    inline iter_t get_iter(step_t step)        {
        link_t link = m_next;
        while((link->has_next() != NC_NULL) && (step-- > NC_ZERO)) { link->set_next(); }
        return *link;
    }
    inline iter_tc get_iter(step_t step) const {
        link_t link = m_next;
        while((link->has_next() != NC_NULL) && (step-- > NC_ZERO)) { link->set_next(); }
        return *link;
    }
    inline iter_t get_next()        { return get_iter(); }
    inline iter_tc get_next() const { return get_iter(); }
    inline iter_t get_next(step_t step)        { return get_iter(step); }
    inline iter_tc get_next(step_t step) const { return get_iter(step); }
    /** data  **/
    inline data_t get_data()        { return m_data; }
    inline data_tc get_data() const { return m_data; }
    inline data_t get_data(step_t step)        { return get_iter(step).get_data(); }
    inline data_tc get_data(step_t step) const { return get_iter(step).get_data(); }
    /** elem  **/
    inline elem_t& get_elem()        { return *m_data; }
    inline elem_tc& get_elem() const { return *m_data; }
    inline elem_t& get_elem(step_t step)        { return get_iter(step).get_elem(); }
    inline elem_tc& get_elem(step_t step) const { return get_iter(step).get_elem(); }
    /** numb  **/
    inline size_tc get_numb() const {
        size_t numb = NC_ZERO; link_t link = m_next;
        while (link != NC_NULL) { link->set_next(); numb++; }
        return numb;
    }
    /* setters */
    inline iter_t& set_iter()              { return *this = get_iter(); }
    inline iter_t& set_iter(step_t step)   { return *this = get_iter(step); }
    inline iter_t& set_next()              { return *this = get_next(); }
    inline iter_t& set_next(step_t step)   { return *this = get_next(step); }
    inline iter_t& set_data(data_t data)   { m_data = data; return *this; }
    inline iter_t& set_elem(elem_tc& elem) { *m_data = elem; return *this; }
    inline iter_t& set_elem(elem_t&& elem) { *m_data = elem; return *this; }
    /* vetters */
    inline v1bit_t has_data() const { return m_data != NC_NULL; }
    inline v1bit_t has_next() const { return m_next != NC_NULL; }
    /* command */
    /* operators */
    /** asign  **/
    inline iter_t& operator=(iter_tc& copy) {
        NC_MEM_DEL_ONE(iter_t, m_next);
        NC_MEM_FREE(m_data, sizeof(elem_t));
        NC_MEM_TAKE(m_data, sizeof(elem_t));
        memcpy(m_data, copy.get_elem(), sizeof(elem_t));
        return *this;
    }
    inline iter_t& operator=(iter_t&& copy) {
        NC_MEM_DEL_ONE(iter_t, m_next);
        NC_MEM_FREE(m_data, sizeof(elem_t));
        NC_MEM_TAKE(m_data, sizeof(elem_t));
        memmove(m_data, copy.get_elem(), sizeof(elem_t));
        return *this;
    }
    /** access  **/
    inline elem_t& operator[](step_t step)        { return get_elem(step); }
    inline elem_tc& operator[](step_t step) const { return get_elem(step); }
    inline elem_t& operator()(step_t step)        { return get_elem(step); }
    inline elem_tc& operator()(step_t step) const { return get_elem(step); }
    /** arith  **/
    inline iter_t& operator++()   { return set_iter(); }
    inline iter_t operator++(int) { return set_iter(); }
    inline iter_t operator+(step_tc step)        { return get_iter(step); }
    inline iter_tc operator+(step_tc step) const { return get_iter(step); }
    inline iter_t& operator+=(step_tc step)      { return set_iter(step); }
    /** logic  **/
    inline v1bit_t operator==(iter_tc& iter) const { return (m_data == iter.m_data) && (m_next == iter.m_next); }
    /** convertion  **/
    inline operator data_t ()        { return get_data(); }
    inline operator data_tc () const { return get_data(); }
    /** input_output  **/
public:
    data_t m_data;
    link_t m_next;
};
/// stack_main_type
template<typename tname>
class nc_stack_main_t
{
public:
    using main_t = nc_stack_main_t<tname>;
    using main_tc = const main_t;
    using iter_t = nc_stack_iter_t<tname>;
    using iter_tc = const iter_t;
    using data_t = tname*;
    using data_tc = const data_t;
    using elem_t = tname;
    using elem_tc = const elem_t;
public:
    /* codetor */
    constexpr inline nc_stack_main_t();
    inline ~nc_stack_main_t() { NC_CHECK(remake(NC_ZERO), "remake error!", return); }
    /* getters */
    /** iter  **/
    inline iter_t& get_head()        { return m_head; }
    inline iter_tc& get_head() const { return m_head; }
    inline iter_t get_iter()        { return m_head; }
    inline iter_tc get_iter() const { return m_head; }
    inline iter_t get_iter(step_t step)        { return m_head.get_iter(step); }
    inline iter_tc get_iter(step_t step) const { return m_head.get_iter(step); }
    /** data  **/
    /** elem  **/
    inline elem_t& get_elem()        { return m_head.get_elem(); }
    inline elem_tc& get_elem() const { return m_head.get_elem(); }
    inline elem_t& get_elem(step_t step)        { return m_head.get_elem(step); }
    inline elem_tc& get_elem(step_t step) const { return m_head.get_elem(step); }
    /* setters */
    /** iter  **/
    inline main_t& add_iter() {
        return *this;
    }
    inline main_t& rmv_iter() {
        return *this;
    }
    /** data  **/
    /** elem  **/
    inline main_t& set_elem(elem_tc& elem) { get_elem() = elem; return *this; }
    inline main_t& set_elem(step_t step, elem_tc& elem) { get_elem(step) = elem; return *this; }
    /* vetters */
    inline v1bit_t has_numb() const             { return m_numb; }
    inline v1bit_t has_numb(size_tc numb) const { return m_numb >= numb; }
    /* command */
    inline v1bit_t remake(size_tc numb) { return remake(); }
    inline v1bit_t remake() {
        NC_PCALL({ /* init */
        }, "remake error!", return NC_FALSE);
        NC_PCALL({ /* work */
            size_t numb = m_head.get_numb();
            while(m_numb > numb) {  }
        }, "remake error!", return NC_FALSE);
        /* quit */
        return NC_TRUTH;
    }
    /* operators */
private:
    iter_t m_head;
    size_t m_numb;
};
/* other names */
template<typename tname> using nc_stack_t = nc_stack_main_t<tname>;
template<typename tname> using nc_stack_tc = const nc_stack_t<tname>;
#	endif	/* NC_API */
/* end_of_file */
#endif /* NC_LIB_STACK_HPP */