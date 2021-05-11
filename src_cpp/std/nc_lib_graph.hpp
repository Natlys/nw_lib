#ifndef NC_LIB_GRAPH_HPP
#	define NC_LIB_GRAPH_HPP
#	include "../nc_lib_core.hpp"
#	if(defined NC_API)
// includes //
#		include "../nc_lib_name.hpp"
#		include "nc_lib_util.hpp"
// types //
/// link_node_type
/// description:
template<typename tdata>
class NC_API nc_link_node_t
{
public:
using data_t = tdata*;
using data_tc = const data_t;
using node_t = nc_link_node_t<data_t>;
using node_tc = const node_t;
using link_t = node_t*;
using link_tc = const link_t;
using links_t = list2_t<link_t>;
using links_tc = const links_t;
public:
	inline nc_link_node_t() : m_data(NC_NULL), m_links(links_t()) { }
	inline nc_link_node_t(data_t data) : t_link_node_t() { set_data(data); }
	inline nc_link_node_t(data_t data, links_t& links) : t_link_node_t() { set_data(data); set_links(links); }
	inline nc_link_node_t(node_t& copy) : t_link_node_t() { operator=(copy); }
	virtual ~nc_link_node_t() { operator=(node_t()); }
	// getters //
	inline data_t get_data()        { return m_data; }
	inline data_tc get_data() const { return m_data; }
	inline links_t& get_links()        { return m_links; }
	inline links_tc& get_links() const { return m_links; }
	inline auto get_beg()       { return m_links.begin(); }
	inline auto get_beg() const { return m_links.begin(); }
	inline auto get_end()       { return m_links.end(); }
	inline auto get_end() const { return m_links.end(); }
	inline size_t get_count() const {
		size_t count = 0u;
		auto ilink = links.begin();
		while (ilink++ != links.end()) { count++; }
		return count;
	}
	inline link_t get_link(size_t key) {
		size_t il = 0u; auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (il++ == key) { return ilink; } }
		return this;
	}
	inline link_tc get_link(size_t key) const {
		size_t il = 0u; auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (il++ == key) { return ilink; } }
		return this;
	}
	// setters //
	node_t& set_data(data_tc data) { m_data = data; }
	node_t& set_links(links_tc& links = links_t()) {
		m_links.clear();
		auto ilink = links.begin();
		while (ilink++ != links.end()) { add_link(*ilink); }
		return *this;
	}
	node_t& add_link(link_tc link, size_t key) {
		size_t il = 0u; auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) {
			if (ilink == link) { NC_ERROR("such link already exists!", return *this); }
			if (il++ == key) { m_links.insert(ilink, link); return *this; }
		}
		NC_ERROR("key error!", return *this);
		return *this;
	}
	node_t& add_link(link_tc link) {
		auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) {
			if (*ilink == link) { NC_ERROR("such link already exists!", return *this); }
		}
		m_links.push_back(link);
		return *this;
	}
	node_t& rmv_link(size_t key) {
		size_t il = 0u; auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (il++ == key) { m_links.erase(ilink); return *this; } }
		//NC_ERROR("nof found!", return NC_FALSE);
		return *this;
	}
	node_t& rmv_link(link_tc link) {
		auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (*ilink == link) { m_links.erase(ilink); return *this; } }
		return *this;
	}
	// predicates //
	inline v1bit_t has_data() const             { return m_data != NC_NULL; }
	inline v1bit_t has_data(data_t* data) const { return m_data == data; }
	inline v1bit_t has_link() const { return m_links.empty() == NC_FALSE; }
	inline v1bit_t has_link(size_t key) const {
		size_t il = 0u; auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (il++ == key) { return NC_TRUTH; } }
		return NC_FALSE;
	}
	inline v1bit_t has_link(link_t* link) const {
		auto ilink = m_links.begin();
		while (ilink++ != m_links.end()) { if (*ilink == link) { return NC_TRUTH; } }
		return NC_FALSE;
	}
	// commands //
	// operators //
	inline node_t& operator=(node_t& copy) {
		auto ilink = copy.get_beg();
		while (ilink++ != copy.get_end()) {
			auto& ilink_val = *(*ilink);
			if (ilink_val.has_link(&copy)) { ilink_val.rmv_link(&copy); ilink_val.add_link(*this); }
		}
		set_data(copy.get_data()); set_links(copy.get_links());
		return *this;
	}
	template<typename tname> operator tname* ()             { return static_cast<tname*>(m_data); }
	template<typename tname> operator const tname* () const { return static_cast<const tname*>(m_data); }
	template<typename tname> operator tname& ()             { return *static_cast<tname*>(m_data); }
	template<typename tname> operator const tname& () const { return *static_cast<const tname*>(m_data); }
protected:
	links_t m_links;
	data_t m_data;
};
#	endif	// NC_API //
// end_of_file //
#endif	// NC_LIB_GRAPH_HPP //