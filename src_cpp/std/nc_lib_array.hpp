#ifndef NC_LIB_ARRAY_HPP
#	define NC_LIB_ARRAY_HPP
#	include "../nc_lib_core.hpp"
/* includes */
/* defines */
/** constants **/
#	if (defined NC_API)
// types //
/// array_iterator_type
/// description:
/// interaction:
template<typename tname>
class nc_array_iter_t
{
public:
    using iter_t = nc_array_iter_t<tname>;
    using iter_tc = const iter_t;
    using data_t = tname*;
    using data_tc = const data_t;
    using elem_t = tname;
    using elem_tc = const elem_t;
    using step_t = v1s64_t;
    using step_tc = const step_t;
public:
    // ctor_dtor //
    constexpr inline nc_array_iter_t() : m_data(NC_NULL) { }
    constexpr inline nc_array_iter_t(data_t data) : m_data(data) { }
    constexpr inline nc_array_iter_t(iter_tc& copy) : m_data(copy.m_data) { }
    constexpr inline nc_array_iter_t(iter_t&& copy) : m_data(copy.m_data) { }
    inline ~nc_array_iter_t() { }
    /* getters */
    // // iter // //
    inline iter_t get_iter()        { return iter_t(get_data()); }
    inline iter_tc get_iter() const { return iter_tc(get_data()); }
    inline iter_t get_prev()        { return iter_t(get_data(-NC_UNIT)); }
    inline iter_tc get_prev() const { return iter_tc(get_data(-NC_UNIT)); }
    inline iter_t get_next()        { return iter_t(get_data(+NC_UNIT)); }
    inline iter_tc get_next() const { return iter_tc(get_data(+NC_UNIT)); }
    inline iter_t get_iter(step_tc step) { return iter_t(get_data(step)); }
    inline iter_t get_prev(step_tc step) { return iter_t(get_data(-step)); }
    inline iter_t get_next(step_tc step) { return iter_t(get_data(+step)); }
    // // data // //
    inline data_t get_data()             { return m_data; }
    inline data_tc get_data() const      { return m_data; }
    inline data_t get_data(step_tc step)        { return &m_data[step]; }
    inline data_tc get_data(step_tc step) const { return &m_data[step]; }
    // // elem // //
    inline elem_t& get_elem()             { return m_data[NC_ZERO]; }
    inline elem_tc& get_elem() const      { return m_data[NC_ZERO]; }
    inline elem_t& get_elem(step_tc step)        { return m_data[step]; }
    inline elem_tc& get_elem(step_tc step) const { return m_data[step]; }
    // // numb // //
    inline size_tc get_dist(iter_tc& iter) const { return NC_NUM_DIST(m_data, iter.m_data); }
    /* setters */
    inline iter_t& set_data(data_tc data)  { m_data = data; return *this; }
    inline iter_t& set_elem(elem_tc& elem) { *m_data = elem; return *this; }
    inline iter_t& set_elem(elem_t&& elem) { *m_data = elem; return *this; }
    /* predicates */
    /* commands */
    inline iter_t& make_iter() { return set_data(m_data + NC_ZERO); }
    inline iter_t& make_prev() { return set_data(m_data - NC_UNIT); }
    inline iter_t& make_next() { return set_data(m_data + NC_UNIT); }
    inline iter_t& make_iter(step_tc step) { return set_data(m_data + step); }
    inline iter_t& make_prev(step_tc step) { return set_data(m_data - step); }
    inline iter_t& make_next(step_tc step) { return set_data(m_data + step); }
    // operators //
    // // asign // //
    inline iter_t& operator=(iter_tc& copy) { memcpy(this, &copy, sizeof(iter_t));  return *this; }
    inline iter_t& operator=(iter_t&& copy) { memmove(this, &copy, sizeof(iter_t)); return *this; }
    // // access // //
    inline elem_t& operator[](indx_tc indx)        { return get_elem(indx); }
    inline elem_tc& operator[](indx_tc indx) const { return get_elem(indx); }
    inline elem_t& operator()(indx_tc indx)        { return get_elem(indx); }
    inline elem_tc& operator()(indx_tc indx) const { return get_elem(indx); }
    // // arith // //
    inline iter_t& operator--()   { return make_prev(); }
    inline iter_t operator--(int) { return make_prev(); }
    inline iter_t& operator++()   { return make_next(); }
    inline iter_t operator++(int) { return make_next(); }
    inline iter_t operator-(step_tc step)        { return get_iter(-step); }
    inline iter_tc operator-(step_tc step) const { return get_iter(-step); }
    inline iter_t operator+(step_tc step)        { return get_iter(+step); }
    inline iter_tc operator+(step_tc step) const { return get_iter(+step); }
    inline iter_t& operator-=(step_tc step) { return make_prev(step); }
    inline iter_t& operator+=(step_tc step) { return make_next(step); }
    // // logic // //
    inline v1bit_t operator>(iter_tc& iter) const  { return m_data > iter.m_data; }
    inline v1bit_t operator<(iter_tc& iter) const  { return m_data > iter.m_data; }
    inline v1bit_t operator==(iter_tc& iter) const { return m_data == iter.m_data; }
    inline v1bit_t operator<=(iter_tc& iter) const { return m_data <= iter.m_data; }
    inline v1bit_t operator>=(iter_tc& iter) const { return m_data >= iter.m_data; }
    // // convertion // //
    inline operator data_t& ()        { return get_data(); }
    inline operator data_tc& () const { return get_data(); }
    // // input_output // //
public:
    data_t m_data;
};
/// array_main_type
/// description:
/// interaction:
template<typename tname>
class nc_array_main_t
{
public:
    using main_t = nc_array_main_t<tname>;
    using main_tc = const main_t;
    using iter_t = nc_array_iter_t<tname>;
    using iter_tc = const iter_t;
    using data_t = tname*;
    using data_tc = const data_t;
    using elem_t = tname;
    using elem_tc = const elem_t;
public:
    // ctor_dtor //
    constexpr inline nc_array_main_t() : m_head(iter_t()), m_back(iter_t()), m_size(NC_ZERO), m_numb(NC_ZERO) { }
    inline nc_array_main_t(size_tc size) : nc_array_main_t() { remake(size); }
    inline nc_array_main_t(size_tc size, data_tc data) : nc_array_main_t() { remake(size, data); }
    inline nc_array_main_t(main_tc& copy) : nc_array_main_t() { operator=(copy); }
    inline nc_array_main_t(main_t&& copy) : nc_array_main_t() { operator=(copy); }
    inline ~nc_array_main_t() { NC_CHECK(remake(NC_ZERO), "remake error!", return); }
    /* getters */
    // // iter // //
    inline iter_t get_iter()             { return m_head.get_iter(); }
    inline iter_t get_iter(indx_tc indx) { return m_head.get_iter(indx); }
    inline iter_t& get_head()        { return m_head; }
    inline iter_tc& get_head() const { return m_head; }
    inline iter_t& get_back()        { return m_back; }
    inline iter_tc& get_back() const { return m_back; }
    inline iter_t& begin()        { return m_head; }
    inline iter_tc& begin() const { return m_head; }
    inline iter_t& end()          { return m_back; }
    inline iter_tc& end() const   { return m_back; }
    // // data // //
    inline data_t get_data()        { return m_head.get_data(); }
    inline data_tc get_data() const { return m_head.get_data(); }
    inline data_t get_data(indx_tc indx)        { return m_head.get_data(indx); }
    inline data_tc get_data(indx_tc indx) const { return m_head.get_data(indx); }
    // // elem // //
    inline elem_t& get_elem()        { return m_head.m_data[NC_ZERO]; }
    inline elem_tc& get_elem() const { return m_head.m_data[NC_ZERO]; }
    inline elem_t& get_elem(indx_tc indx)        { return m_head.m_data[indx]; }
    inline elem_tc& get_elem(indx_tc indx) const { return m_head.m_data[indx]; }
    // // numb // //
    inline size_tc get_leng() const { return m_head.get_dist(m_back); }
    inline size_tc get_size() const { return m_size; }
    inline size_tc get_numb() const { return m_numb; }
    /* setters */
    // // iter // //
    inline main_t& add_iter() { 
        NC_PCALL({ /* init */
            NC_CHECK(has_iter(m_head), "iter error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            NC_CHECK(remake(get_size() + NC_UNIT), "remake error!", return *this);
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    inline main_t& add_iter(iter_t iter) {
        NC_PCALL({ /* init */
            NC_CHECK(has_iter(iter), "iter error!", return *this);
        }, "set error!", return *this);
        /* work */
        NC_PCALL({ /* work */
            add_iter(); // new one should be empty; others are moved; //
            size_tc copy_size = (m_back.get_data() - iter.get_data() - NC_UNIT);
            data_tc copy_data = iter.get_data() + NC_UNIT;
            memcpy(copy_data, copy_data + NC_UNIT, copy_size * sizeof(elem_t));
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    inline main_t& rmv_iter() { init(get_size() - NC_UNIT); return *this; }
    inline main_t& rmv_iter(iter_t iter) {
        NC_PCALL({ /* init */
            NC_CHECK(has_iter(iter), "iter error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            size_tc copy_size = (m_back.get_data() - iter.get_data() - NC_UNIT);
            data_tc copy_data = iter.get_data();
            memcpy(copy_data, copy_data + NC_UNIT, copy_size * sizeof(elem_t));
            rmv_iter(); // last cell will be removed; others are moved back; //
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    // // data // //
    inline main_t& set_data(data_tc data, size_tc numb) {
        NC_PCALL({ /* init */
            NC_CHECK(has_data(), "data error!", return *this);
            NC_CHECK(has_size(numb), "size error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            m_numb = numb;
            memcpy(get_data(), data, get_numb());
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    // // elem // //
    template<typename ... targs> main_t& set_elem(iter_t iter, targs&& ... args) {
        NC_PCALL({ /* init */
            NC_CHECK(has_iter(iter), "iter error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            new(get_data(m_numb++))elem_t(std::forward<targs>(args)...);
        }, "set error!", return *this);
        return *this;
    }
    template<typename ... targs> main_t& add_elem(targs&& ... args) {
        NC_PCALL({ /* init */
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            if (!has_leng(m_numb + NC_UNIT)) { add_iter(); }
            new(get_data(m_numb++))elem_t(std::forward<targs>(args)...);
        }, "set error!", return *this);
        return *this;
    }
    inline main_t& rmv_elem() {
        NC_PCALL({ /* init */
            NC_CHECK(has_leng(), "size error!", return *this);
        }, "set error!", return *this)
        NC_PCALL({ /* work */
            NC_CHECK(remake(get_leng() - 1u), "remake error!", return *this);
        }, "set error!", return *this)
        /* quit */
        return *this;
    }
    inline main_t& rmv_elem(iter_t iter) {
        NC_PCALL({ /* init */
            NC_CHECK(has_iter(iter), "iter error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            iter.get_data()->~elem_t();
            m_numb--;
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    inline main_t& rmv_elem(indx_tc indx) {
        NC_PCALL({ /* init */
            NC_CHECK(has_elem(indx), "iter error!", return *this);
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            get_iter(indx).get_data()->~elem_t();
            m_numb--;
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    // // numb // //
    inline main_t& set_size(size_tc size) {
        NC_PCALL({/* init */
        }, "set error!", return *this);
        NC_PCALL({ /* work */
            m_size = size;
        }, "set error!", return *this);
        /* quit */
        return *this;
    }
    /* predicates */
    // // iter // //
    inline v1bit_t has_iter() const             { return has_data(); }
    inline v1bit_t has_iter(iter_tc iter) const { return has_data(iter); }
    // // data // //
    inline v1bit_t has_data() const             { return get_head() != get_back(); }
    inline v1bit_t has_data(data_tc data) const { return NC_NUM_ISIDE(data, get_head(), get_back()); }
    // // elem // //
    inline v1bit_t has_elem() const             { return m_numb > NC_ZERO; }
    inline v1bit_t has_elem(iter_tc iter) const { return m_numb > get_back().get_dist(iter); }
    inline v1bit_t has_elem(indx_tc indx) const { return m_numb > indx; }
    // // numb // //
    inline v1bit_t has_leng() const             { return get_leng() > NC_ZERO; }
    inline v1bit_t has_leng(size_tc leng) const { return get_leng() >= leng; }
    inline v1bit_t has_size() const             { return get_size() > NC_ZERO; }
    inline v1bit_t has_size(size_tc size) const { return get_size() >= size; }
    inline v1bit_t has_numb() const             { return get_numb() > NC_ZERO; }
    inline v1bit_t has_numb(size_tc numb) const { return get_numb() >= numb; }
    /* commands */
    inline v1bit_t remake(size_tc size) { return set_size(size).remake(); }
    inline v1bit_t remake() {
        NC_PCALL({ /* init */
        }, "remake error!", return NC_FALSE);
        NC_PCALL({ /* work */
            size_tc sz_old = get_leng() * sizeof(elem_t);
            size_tc sz_new = get_size() * sizeof(elem_t);
            NC_MEM_MOVE(m_head.m_data, sz_old, sz_new);
            m_back = m_head.m_data + m_size;
        }, "remake error!", return NC_FALSE);
        /* quit */
        return NC_TRUTH;
    }
    inline v1bit_t make_olog() {
        NC_PCALL({ /* work */
            NC_OLOG("array:");
            NC_OPUT("{" NC_EOL);
            NC_OPUT(NC_TAB "head:{%x};" NC_EOL, get_head().m_data);
            NC_OPUT(NC_TAB "back:{%x};" NC_EOL, get_back().m_data);
            NC_OPUT(NC_TAB "leng:{%d};" NC_EOL, get_leng());
            NC_OPUT(NC_TAB "size:{%d};" NC_EOL, get_size());
            NC_OPUT(NC_TAB "numb:{%d};" NC_EOL, get_numb());
            for (size_t itr = NC_ZERO; itr < get_leng(); itr += 1u) {
                std::cout <<
                    NC_TAB "[" << itr << "]"  << ":" << get_elem(itr)
                    << ";" NC_EOL;
            }
            NC_OPUT("}" NC_EOL);
        }, "olog error!", return NC_FALSE);
        /* quit */
        return NC_TRUTH;
    }
    // operators //
    // // asign // //
    inline main_t& operator=(main_tc& copy) { remake(copy.get_leng()); return set_data(copy.get_data(), copy.get_numb()); }
    inline main_t& operator=(main_t&& copy) { remake(copy.get_leng()); return set_data(copy.get_data(), copy.get_numb()); }
    // // access // //
    inline elem_t& operator[](indx_t indx)        { return get_elem(indx); }
    inline elem_tc& operator[](indx_t indx) const { return get_elem(indx); }
    inline elem_t& operator()(indx_t indx)        { return get_elem(indx); }
    inline elem_tc& operator()(indx_t indx) const { return get_elem(indx); }
    // // convertion // //
    // // // iter // //
    // inline operator iter_t()        { return get_head(); }
    // inline operator iter_tc() const { return get_head(); }
    // // // data // //
    // inline operator data_t()        { return get_data(); }
    // inline operator data_tc() const { return get_data(); }
    // // // elem // //
    // inline operator elem_t&() const  { return get_elem(); }
    // inline operator elem_tc&() const { return get_elem(); }
private:
    iter_t m_head;
    iter_t m_back;
    size_t m_size;
    size_t m_numb;
};
// other names //
template<typename tname> using nc_array_t = nc_array_main_t<tname>;
template<typename tname> using nc_array_tc = const nc_array_t<tname>;
#	endif	/* NC_API */
/* end_of_file */
#endif	// NC_LIB_ARRAY_HPP //