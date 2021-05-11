#ifndef NC_LIB_UTILITY_HPP
#	define NC_LIB_UTILITY_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
// includes //
#   	include <utility>
#		include "../../nc_mem/src_cpp/core/nc_mem_sys.hpp"
#		include "nc_lib_type.hpp"
// types //
template <typename tval1, typename tval2>
using nc_pair_t = std::pair<tval1, tval2>;
template <typename tval1, typename tval2>
using nc_pair_tc = const pair_t<tval1, tval2>;
template <typename tval>
using nc_init_list_t = std::initializer_list<tval>;
template <typename tval>
using nc_init_list_tc = const init_list_t<tval>;
#		if (NC_FALSE)
/// initializer_list_type
template<typename tdata>
class NC_API nc_init_list_t
{
public:
	using data_t = tdata;
	using data_tc = const data_t;
	using iter_t = data_t*;
	using iter_tc = const iter_t;
public:
	init_list() : m_head(NC_NULL), m_back(NC_NULL) { }
	init_list(const tdata* head, const tdata* back) : m_head(head), m_back(back) { }
	~init_list() { }
	// getters //
	inline iter_tc get_head() const { return m_head; }
	inline iter_tc get_back() const { return m_back; }
	inline size_tc get_size() const { return NC_CAST_SIZE(m_back - m_head + 1); }
	inline iter_tc begin() const { return m_head; }
	inline iter_tc end() const   { return m_back; }
	// setters //
	// predicates //
	inline v1bit_t has_head() const             { return m_head != NC_NULL; }
	inline v1bit_t has_head(iter_tc iter) const { return m_head == iter; }
	inline v1bit_t has_back() const             { return m_back != NC_NULL; }
	inline v1bit_t has_back(iter_tc iter) const { return m_back == iter; }
	inline v1bit_t has_size() const             { return get_size() > NC_NULL; }
	inline v1bit_t has_size(size_tc size) const { return get_size() > size; }
	// operators //
private:
	iter_tc m_head;
	iter_tc m_back;
};
#		endif
#		if (NC_FALSE)
/// value_iterator_array class
class a_iter_array : public a_nc_type_owner
{
public:
	using iter_t = a_iter_array;
	using iter_tc = const iter_t;
	using data_t = byte_t;
	using data_tc = const data_t;
public:
	a_iter_array() : a_nc_type_owner(), m_data(NC_NULL) {}
	template<typename tname>
	inline a_iter_array(tname* data) : a_nc_type_owner(type_info_t::get_type()), m_data(reinterpret_cast<data_t*>(data)) { }
	inline a_iter_array(data_t* data, type_tc type) : a_nc_type_owner(type), m_data(data) { }
	inline a_iter_array(iter_tc& copy) : a_nc_type_owner(copy), m_data(copy.m_data) { }
	inline a_iter_array(iter_t&& copy) : a_nc_type_owner(copy), m_data(copy.m_data) { }
	~a_iter_array() { }
	// getters //
	inline data_t* get_data(type_tc type) { NC_CHECK(has_type(type), "type error!", return NC_NULL); return m_data; }
	inline data_tc* get_data(type_tc type) const { NC_CHECK(has_type(type), "type error!", return NC_NULL); return m_data; }
	template<typename tname> tname* get_data() { return get_data(type_info_t::get_type<tname>()); }
	template<typename tname> const tname* get_data() const { return get_data(type_info_t::get_type<tname>()); }
	template<typename tname> tname& get() { return *get_data<tname>(); }
	template<typename tname> const tname& get() const { return *get_data<tname>(); }
	// setters //
	inline iter_t& set_data(ptr_tc data, type_tc type) { memcpy(get_data(type), data, get_type_size()); return *this; }
	template<typename tname> iter_t& set_data(const tname* data) { return set_data(data, type_info_t::get_type<tname>()); }
	template<typename tname> iter_t& set(const tname& data) { return set_data<tname>(&data); }
	// predicates //
	inline v1bit_t has_data() const { return m_data != NC_NULL; }
	inline v1bit_t has_data(data_tc* data) const { return m_data == data; }
	// operators //
	// // --memory
	template<typename tname>
	inline tname& operator*() { return get<tname>(); }
	template<typename tname>
	inline const tname& operator*() const { return get<tname>(); }
	template<typename tname>
	inline tname* operator&() { return get_data<tname>(); }
	template<typename tname>
	inline const tname* operator&() const { return get_data<tname>(); }
	template<typename tname>
	inline tname* operator->() { return get_data<tname>(); }
	template<typename tname>
	inline const tname* operator->() const { return get_data<tname>(); }
	template<typename tname>
	operator tname* () { return get_data<tname>(); }
	template<typename tname>
	operator const tname* () const { return get_data<tname>(); }
	template<typename tname>
	operator tname& () { return get<tname>(); }
	template<typename tname>
	operator const tname& () const { return get<tname>(); ; }
	// // --arith
	inline iter_t& operator++(v1nil_t) { m_data += get_type_size(); return *this; }
	inline iter_t operator+(v1s_t steps) { return iter_t(m_data + get_type_size() * steps, m_type); }
	inline iter_t operator+=(v1s_t steps) { m_data += get_type_size() * steps; return *this; }
	inline iter_t operator++(v1s_t) { m_data += get_type_size(); return *this; }
	inline iter_t operator-(v1s_t steps) { return iter_t(m_data - get_type_size() * steps, m_type); }
	inline iter_t operator-=(v1s_t steps) { m_data -= get_type_size() * steps; return *this; }
	inline iter_t& operator--(v1nil_t) { m_data -= get_type_size(); return *this; }
	inline iter_t operator--(v1s_t) { m_data -= get_type_size(); return *this; }
	inline iter_t& operator=(iter_tc& copy) { a_nc_type_owner::operator=(copy); m_data = copy.m_data; return *this; }
	inline iter_t& operator=(iter_t&& copy) { a_nc_type_owner::operator=(copy); m_data = copy.m_data; return *this; }
	template<typename tname>
	iter_t& operator=(const tname* data) { return set_data<tname>(data); }
	template<typename tname>
	iter_t& operator=(const tname& data) { return set<tname>(data); }
	// // --logic
	inline v1bit_t operator!=(iter_tc& iter) const { return m_data != iter.m_data; }
	inline v1bit_t operator==(iter_tc& iter) const { return m_data == iter.m_data; }
	inline v1bit_t operator>(iter_tc& iter) const { return m_data > iter.m_data; }
	inline v1bit_t operator>=(iter_tc& iter) const { return m_data >= iter.m_data; }
	inline v1bit_t operator<(iter_tc& iter) const { return m_data < iter.m_data; }
	inline v1bit_t operator<=(iter_tc& iter) const { return m_data <= iter.m_data; }
	// commands //
public:
	data_t* m_data;
};
#		endif
#		if (NC_FALSE)
/// typed_iterator_array class
template<typename tdata>
class t_iter_array
{
public:
	using iter_t = t_iter_array<tdata>;
	using iter_tc = const iter_t;
	using data_t = tdata;
	using data_tc = const tdata;
public:
	inline t_iter_array() : m_data(NC_NULL) { }
	inline t_iter_array(data_t* data) : m_data(data) { }
	inline t_iter_array(iter_tc& copy) : m_data(copy.m_data) { }
	inline t_iter_array(iter_t&& copy) : m_data(copy.m_data) { }
	~t_iter_array() { }
	// getters //
	inline data_t* get_data() { return m_data; }
	inline data_tc* get_data() const { return m_data; }
	inline data_t& get() { return *m_data; }
	inline data_tc& get() const { return *m_data; }
	// setters //
	inline iter_t& set_data(data_tc* data) { memcpy(m_data, data, sizeof(data_t)); return *this; }
	inline iter_t& set(data_tc& data) { memcpy(m_data, &data, sizeof(data_t)); return *this; }
	// predicates //
	inline v1bit_t has_data() const { return m_data != NC_NULL; }
	inline v1bit_t has_data(data_tc* data) const { return m_data == data; }
	// operators //
	// // --memory
	inline data_t& operator*() { return *m_data; }
	inline data_tc& operator*() const { return *m_data; }
	inline data_t* operator&() { return m_data; }
	inline data_tc* operator&() const { return m_data; }
	inline data_t* operator->() { return m_data; }
	inline data_tc* operator->() const { return m_data; }
	inline operator data_t* () { return m_data; }
	inline operator data_tc* () const { return m_data; }
	inline operator data_t& () { return *m_data; }
	inline operator data_tc& () const { return *m_data; }
	// // --arith
	inline iter_t& operator++(v1nil_t) { m_data += 1; return *this; }
	inline iter_t operator+(v1s_t steps) { return iter_t(m_data + *steps, m_type); }
	inline iter_t& operator+=(v1s_t steps) { m_data += steps; return *this; }
	inline iter_t operator++(v1s_t) { m_data += 1; return *this; }
	inline iter_t operator-(v1s_t steps) { return iter_t(m_data - steps, m_type); }
	inline iter_t& operator-=(v1s_t steps) { m_data -= steps; return *this; }
	inline iter_t& operator--(v1nil_t) { m_data -= 1; return *this; }
	inline iter_t operator--(v1s_t) { m_data -= 1; return *this; }
	inline iter_t& operator=(iter_tc& copy) { m_data = copy.m_data; return *this; }
	inline iter_t& operator=(iter_t&& copy) { m_data = copy.m_data; return *this; }
	template<typename tname>
	iter_t& operator=(const tname* data) { return set_data(data); }
	template<typename tname>
	iter_t& operator=(const tname& data) { return set(data); }
	// // --logic
	inline v1bit_t operator!=(iter_tc& iter) const { return m_data != iter.m_data; }
	inline v1bit_t operator==(iter_tc& iter) const { return m_data == iter.m_data; }
	inline v1bit_t operator>(iter_tc& iter) const { return m_data > iter.m_data; }
	inline v1bit_t operator>=(iter_tc& iter) const { return m_data >= iter.m_data; }
	inline v1bit_t operator<(iter_tc& iter) const { return m_data < iter.m_data; }
	inline v1bit_t operator<=(iter_tc& iter) const { return m_data <= iter.m_data; }
	// // --iop
	inline op_stream_t& operator<<(op_stream_t& stm) const { return stm << *m_data; }
	inline ip_stream_t& operator<<(ip_stream_t& stm) { return stm >> *m_data; }
	// commands //
public:
	data_t* m_data;
};
template<typename tname>
inline op_stream_t& operator<<(op_stream_t& stm, const t_iter_array<tname>& iter) { return iter.operator<<(stm); }
template<typename tname>
inline ip_stream_t& operator<<(ip_stream_t& stm, t_iter_array<tname>& iter) { return iter.operator>>(stm); }
#		endif
#		if (NC_FALSE)
/// value_array class
template<class tgiver = mem_sys>
class v_array : public t_mem_user<tgiver>
{
	static_assert(NC_FALSE, "cannot use this class now");
public:
	using cont_t = v_array;
	using cont_tc = const cont_t;
	using iter_t = v_iter_array;
	using iter_tc = const iter_t;
	using elem_t = iter_t;
	using elem_tc = iter_tc;
public:
	v_array() : m_elems(NC_NULL), m_count(NC_NULL) { }
	v_array(cont_tc& copy) : m_elems(NC_NULL), m_count(NC_NULL) { operator=(copy); }
	v_array(cont_t&& copy) : m_elems(NC_NULL), m_count(NC_NULL) { operator=(copy); }
	~v_array() { reset(); }
	// getters //
	inline size_t get_count() const { return m_count; }
	inline elem_t* get_elems() { return m_elems; }
	inline elem_tc* get_elems() const { return m_elems; }
	inline elem_t& get_elem(size_t key = NC_NULL) { NC_CHECK(has_count(key), "key error!", return *m_elems); return m_elems[key]; }
	inline elem_tc& get_elem(size_t key = NC_NULL) const { NC_CHECK(has_count(key), "key error!", return *m_elems); return m_elems[key]; }
	inline iter_t get_head() { NC_CHECK(has_elems(), "no elems!", return iter_t()); return iter_t(m_elems[0]); }
	inline iter_t get_back() { NC_CHECK(has_elems(), "no elems!", return iter_t()); return iter_t(m_elems[m_count - 1]); }
	inline iter_t begin() { return get_head(); }
	inline iter_t end() { return get_back(); }
	// setters //
	inline cont_t& set_count(size_t count) {
		if (has_elems()) {
			giver_t::static_free(m_elems, m_count * sizeof(elem_t), alignof(elem_t));
			m_elems = NC_NULL;
			m_count = NC_NULL;
		}
		m_count = count;
		m_elems = reinterpret_cast<elem_t*>(giver_t::static_take(m_count * sizeof(elem_t), alignof(elem_t)));
		for (v1u_t ie; ie < m_count; ie++) { new(&m_elems[ie])elem_t(); }
		return *this;
	}
	inline cont_t& set_elems(elem_tc* elems) {
		NC_CHECK(has_elems(), "no elems!", return *this);
		for (v1u_t ie; ie < m_count; ie++) { m_elems[ie] = elems[ie]; }
		return *this;
	}
	inline cont_t& add_elem(elem_tc& elem) {
		set_count(m_count + 1u);
		m_elems[m_count - 1u] = elem;
		return *this;
	}
	inline cont_t& rmv_elem() {
		NC_CHECK(has_count(), "no elems!", return *this);
		set_count(m_count - 1);
		return *this;
	}
	// predicates //
	inline v1bit_t has_elem(elem_t* elem) const { return m_elems != elem; }
	inline v1bit_t has_elems() const { return m_elems != NC_NULL; }
	inline v1bit_t has_count() const { return m_count != NC_NULL; }
	inline v1bit_t has_count(size_t count) const { return m_count >= count; }
	// operators //
	inline cont_t& operator=(cont_tc& copy) { set_count(copy.get_count()); set_elems(copy.get_elems()); return *this; }
	inline cont_t& operator=(cont_t&& copy) { set_count(copy.get_count()); set_elems(copy.get_elems()); return *this; }
	inline elem_t& operator[](size_t key) { return get_elem(key); }
	inline elem_tc& operator[](size_t key) const { return get_elem(key); }
	// commands //
	cont_t& remake(size_t count, elem_t* elems) { set_count(count); return *this; }
	cont_t& reset() { set_elems(NC_NULL); set_count(NC_NULL); return *this; }
public:
	elem_t* m_elems;
	size_t m_count;
};
#		endif
#		if (NC_FALSE)
/// typed_array class
template<typename telem, class tgiver = mem_sys>
class t_array : public t_mem_user<tgiver>
{
public:
	using cont_t = t_array;
	using cont_tc = const cont_t;
	using iter_t = t_iter_array<telem>;
	using iter_tc = const iter_t;
	using elem_t = telem;
	using elem_tc = const elem_t;
	using elems_t = elem_t*;
	using elems_tc = const elems_t;
public:
	t_array() : t_mem_user(), m_elems(NC_NULL), m_range(NC_NULL), m_count(NC_NULL) { }
	t_array(size_t count) : t_array() { set_count(count); }
	t_array(cont_tc& copy) : t_mem_user(copy), m_elems(NC_NULL), m_range(NC_NULL), m_count(NC_NULL) { operator=(copy); }
	t_array(cont_t&& copy) : t_mem_user(copy), m_elems(NC_NULL), m_range(NC_NULL), m_count(NC_NULL) { operator=(copy); }
	~t_array() { reset(); }
	// getters //
	inline size_t get_count() const { return m_count; }
	inline size_t get_range() const { return m_range; }
	inline elems_t get_elems() { return m_elems; }
	inline elems_tc get_elems() const { return m_elems; }
	inline elem_t& get_elem(size_t key = NC_NULL) { NC_CHECK(has_count(key), "key error!", return *m_elems); return m_elems[key]; }
	inline elem_tc& get_elem(size_t key = NC_NULL) const { NC_CHECK(has_count(key), "key error!", return *m_elems); return m_elems[key]; }
	inline iter_t get_head() { NC_CHECK(has_elems(), "no elems!", return iter_t(NC_NULL)); return iter_t(&m_elems[0]); }
	inline iter_t get_back() { NC_CHECK(has_elems(), "no elems!", return iter_t(NC_NULL)); return iter_t(&m_elems[m_count]); }
	inline iter_t begin() { return get_head(); }
	inline iter_t end() { return get_back(); }
	// setters //
	inline cont_t& set_count(size_t count) {
		const auto old_count = m_count;
		const auto new_count = count;
		elems_t old_elems = m_elems;
		elems_t new_elems = NC_NULL;
		if (new_count > NC_NULL) {
			new_elems = reinterpret_cast<elem_t*>(giver_t::static_take(new_count * sizeof(elem_t), alignof(elem_t)));
			for (auto ie = 0u; ie < new_count; ie++) { new(&new_elems[ie])elem_t(); }
		}
		if (old_count > NC_NULL) {
			memcpy(new_elems, old_elems, NC_ALIGN(NC_NUM_MIN(old_count, new_count) * sizeof(elem_t), alignof(elem_t)));
			giver_t::static_free(old_elems, old_count * sizeof(elem_t), alignof(elem_t));
		}
		m_count = new_count;
		m_elems = new_elems;
		return *this;
	}
	inline cont_t& set_range(size_t range) {
		const auto old_range = m_range;
		const auto new_range = range;
		elems_t old_elems = m_elems;
		elems_t new_elems = NC_NULL;
		if (new_range > NC_NULL) {
			new_elems = reinterpret_cast<elem_t*>(giver_t::static_take(new_range * sizeof(elem_t), alignof(elem_t)));
			for (auto ie = 0u; ie < new_range; ie++) { new(&new_elems[ie])elem_t(); }
		}
		if (old_range > NC_NULL) {
			memcpy(new_elems, old_elems, NC_ALIGN(NC_NUM_MIN(old_range, new_range) * sizeof(elem_t), alignof(elem_t)));
			giver_t::static_free(old_elems, old_range * sizeof(elem_t), alignof(elem_t));
		}
		m_range = new_range;
		m_elems = new_elems;
		return *this;
	}
	inline cont_t& set_elems(elem_tc* elems) {
		NC_CHECK(has_elems(), "no elems!", return *this);
		for (auto ie = 0u; ie < m_count; ie++) { m_elems[ie] = elems[ie]; }
		return *this;
	}
	inline cont_t& set_elem(size_t key, elem_tc& elem) {
		if (m_range <= key) { // the element is emplaced further than the end;
			set_range(key * 2u + 1u);
		}
		else { // the element is inserted inside;
			set_range(key + 1u);
			for (auto ie = key + 1u; ie < m_count;) { m_elems[ie] = m_elems[++ie]; }
		}
		m_elems[key] = elem;
		return *this;
	}
	inline cont_t& set_head(elem_tc& elem) { NC_CHECK(has_count(), "no elems!", return *this); return set_elem(0u, elem); }
	inline cont_t& set_back(elem_tc& elem) { NC_CHECK(has_count(), "no elems!", return *this); return set_elem(m_count - 1u, elem); }
	inline cont_t& rmv_elem(size_t key) {
		NC_CHECK(has_count(key), "no elems!", return *this);
		const auto last_key = m_count - 1u;
		if (key < last_key) {
			for (auto ie = key; ie < last_key;) {
				m_elems[ie] = m_elems[++ie];
			}
		}
		set_count(m_count - 1u);
		return *this;
	}
	inline cont_t& add_back(elem_tc& elem) { return set_elem(m_count, elem); }
	inline cont_t& rmv_back() { NC_CHECK(has_count(), "no elems!", return *this); return set_count(m_count - 1u); }
	// predicates //
	inline v1bit_t has_elem() const { return m_elems != NC_NULL; }
	inline v1bit_t has_elem(elem_t* elem) const { return m_elems != elem; }
	inline v1bit_t has_range() const { return m_range != NC_NULL; }
	inline v1bit_t has_range(size_t range) const { return m_range >= range; }
	inline v1bit_t has_count() const { return m_count != NC_NULL; }
	inline v1bit_t has_count(size_t count) const { return m_count >= count; }
	// operators //
	inline cont_t& operator=(cont_tc& copy) { set_count(copy.get_count()); set_elems(copy.get_elems()); return *this; }
	inline cont_t& operator=(cont_t&& copy) { set_count(copy.get_count()); set_elems(copy.get_elems()); return *this; }
	inline elem_t& operator[](size_t key) { return get_elem(key); }
	inline elem_tc& operator[](size_t key) const { return get_elem(key); }
	// commands //
	cont_t& remake(size_t count, elem_t* elems) { set_count(count); return *this; }
	cont_t& reset() { set_count(NC_NULL); return *this; }
public:
	elem_t* m_elems;
	size_t m_range;
	size_t m_count;
};
#		endif
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_UTILITY_HPP //