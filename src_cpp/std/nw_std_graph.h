#ifndef NW_STD_GRAPH_H
#define NW_STD_GRAPH_H
#include "nw_lib_core.hpp"
#if(defined NW_API)
#	include "nw_std_util.h"
#	include "nw_std_name.h"
namespace NW
{
	/// typed_link_node class
	template<typename tdata>
	class NW_API t_link_node
	{
	public:
		using data_t = tdata*;
		using data_tc = const data_t;
		using node_t = t_link_node<data_t>;
		using node_tc = const node_t;
		using link_t = node_t*;
		using link_tc = const link_t;
		using links_t = list2_t<link_t>;
		using links_tc = const links_t;
	public:
		inline t_link_node() : m_data(NW_NULL), m_links(links_t()) { }
		inline t_link_node(data_t data) : t_link_node() { set_data(data); }
		inline t_link_node(data_t data, links_t& links) : t_link_node() { set_data(data); set_links(links); }
		inline t_link_node(node_t& copy) : t_link_node() { operator=(copy); }
		~t_link_node() { operator=(node_t()); }
		// --getters
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
		// --setters
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
				if (ilink == link) { NW_ERROR("such link already exists!", return *this); }
				if (il++ == key) { m_links.insert(ilink, link); return *this; }
			}
			NW_ERROR("key error!", return *this);
			return *this;
		}
		node_t& add_link(link_tc link) {
			auto ilink = m_links.begin();
			while (ilink++ != m_links.end()) {
				if (*ilink == link) { NW_ERROR("such link already exists!", return *this); }
			}
			m_links.push_back(link);
			return *this;
		}
		node_t& rmv_link(size_t key) {
			size_t il = 0u; auto ilink = m_links.begin();
			while (ilink++ != m_links.end()) { if (il++ == key) { m_links.erase(ilink); return *this; } }
			//NW_ERROR("nof found!", return NW_FALSE);
			return *this;
		}
		node_t& rmv_link(link_tc link) {
			auto ilink = m_links.begin();
			while (ilink++ != m_links.end()) { if (*ilink == link) { m_links.erase(ilink); return *this; } }
			return *this;
		}
		// --predicates
		inline v1bit has_data() const             { return m_data != NW_NULL; }
		inline v1bit has_data(data_t* data) const { return m_data == data; }
		inline v1bit has_link() const { return m_links.empty() == NW_FALSE; }
		inline v1bit has_link(size_t key) const {
			size_t il = 0u; auto ilink = m_links.begin();
			while (ilink++ != m_links.end()) { if (il++ == key) { return NW_TRUE; } }
			return NW_FALSE;
		}
		inline v1bit has_link(link_t* link) const {
			auto ilink = m_links.begin();
			while (ilink++ != m_links.end()) { if (*ilink == link) { return NW_TRUE; } }
			return NW_FALSE;
		}
		// --operators
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
}
#endif	// NW_API
#endif	// NW_STD_GRAPH_H