#ifndef NC_LIB_GRAPH_HPP
#	define NC_LIB_GRAPH_HPP
#	include "../nc_lib_core.hpp"
#	if (defined NC_API)
/* includes */
#		include "../std/nc_lib_util.hpp"
#		include "../std/nc_lib_list2.hpp"
#		include "nc_lib_name.hpp"
#		include "nc_lib_type.hpp"
/* types */
/// tree_node_type
/// description:
/// --data structure for tree composition;
template<typename tnode>
class nc_tree_node_t : public nc_name_owner_t, public nc_type_owner_t
{
public:
	using node_t = tnode;
	using node_tc = const node_t;
	using nodes_t = list2_t<node_t>;
	using nodes_tc = const nodes_t;
	using node_list_t = init_list_t<node_t>;
	using node_list_tc = const node_list_t;
	using tree_t = tree_node_t<node_t>;
	using tree_tc = const tree_t;
public:
	/* ctor_dtor */
	inline nc_tree_node_t() : nc_name_owner_t(), nc_type_owner_t(), m_nodes(nodes_t()) { set_name(type_info_t::get<tree_t>().m_name); set_type(type_info_t::get<tree_t>().m_type); }
	inline nc_tree_node_t(cstr_t name, nodes_tc& nodes) : t_tree_cmp() { set_name(name).set_nodes(nodes); }
	inline nc_tree_node_t(cstr_t name, type_tc type) : t_tree_cmp()    { set_name(name).set_type(type); }
	inline nc_tree_node_t(tree_tc& copy) : tree_node_t() { operator=(copy); }
	inline nc_tree_node_t(tree_t&& copy) : tree_node_t() { operator=(copy); }
	virtual ~nc_tree_node_t() { }
	/* getters */
	inline nodes_t& get_nodes()        { return m_nodes; }
	inline nodes_tc& get_nodes() const { return m_nodes; }
	inline size_t get_count() const { size_t count = 0u; for (auto& inode : m_nodes) { count++; } return count; }
	inline size_t get_space() const { return get_count() * sizeof(node_t); }
	inline node_t& get_node(size_t key) {
		size_t itr = 0u; auto inode = m_nodes.begin();
		do { if (itr++ == key) { return *inode; } } while (inode++ != m_nodes.end());
		NC_ERROR("key error!", return *this);
		return *this;
	}
	inline node_tc& get_node(size_t key) const {
		size_t itr = NC_NULL; auto inode = m_nodes.begin();
		do { if (itr++ == key) { return *inode; } } while (inode++ != m_nodes.end());
		NC_ERROR("key error!", return *this);
		return *this;
	}
	inline node_t& get_node(cstr_t key) {
		for (auto& inode : m_nodes) { if (inode.has_name(key)) { return inode; } }
		NC_ERROR("key error!", return *this);
		return *this;
	}
	inline node_tc& get_node(cstr_t key) const {
		for (auto& inode : m_nodes) { if (inode.has_name(key)) { return inode; } }
		NC_ERROR("key error!", return *this);
		return *this;
	}
	template<typename tname> tname& get_node(size_t key)             { static_cast<tname&>(get_node(key)); }
	template<typename tname> const tname& get_node(size_t key) const { static_cast<const tname&>(get_node(key)); }
	template<typename tname> tname& get_node(cstr_t key)             { static_cast<tname&>(get_node(key)); }
	template<typename tname> const tname& get_node(cstr_t key) const { static_cast<const tname&>(get_node(key)); }
	inline node_t& get_tree_node(size_t key) { for (auto& inode : m_nodes)   { if (inode.has_tree_node(key)) { return inode.get_tree_node(key); } } return get_node(key); }
	inline node_t& get_tree_node(cstr_t key) { for (auto& inode : m_nodes) { if (inode.has_tree_node(key)) { return inode.get_tree_node(key); } } return get_node(key); }
	inline size_t get_tree_space() const { size_t tree_space = sizeof(*this); for (auto& inode : m_nodes) { tree_space += inode.get_tree_space(); } return tree_space; }
	inline size_t get_tree_count() const { size_t tree_count = 1u; for (auto& inode : m_nodes) { tree_count += inode.get_tree_count(); } return tree_count; }
	inline dstr_t get_tree_str(size_t generation = 1u) {
		std::stringstream stm(" ");
		dstr_t offset(NC_CAST_SIZE((generation == 0ul ? 1ul : generation) * 4ul), ' ');
		stm << &offset[4u] << (is_tree() ? "[tree]" : "[leaf]") << ":{" NC_STR_ENDL;
		stm << &offset[0u] << "name:" << get_name() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "type:" << get_type() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "count:" << get_count() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "space:" << get_space() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "type_info:" << get_type_info() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "tree_count:" << get_tree_count() << ";" << NC_STR_ENDL;
		stm << &offset[0u] << "tree_space: " << get_tree_space() << ";" NC_STR_ENDL;
		for (auto& inode : get_nodes()) { stm << inode.get_tree_str(generation + 1u); }
		stm << &offset[4u] << "}:" << (is_tree() ? "[tree]" : "[leaf]") << ";" NC_STR_ENDL;
		return stm.str();
	}
	/* setters */
	inline tree_t& set_nodes(nodes_tc& nodes) { NC_CHECK(is_tree(), "type error!", return *this); m_nodes.clear(); for (auto& inode : nodes) { add_node(inode); } return *this; }
	inline tree_t& set_nodes(node_list_tc& nodes) { NC_CHECK(is_tree(), "type error!", return *this); m_nodes.clear(); for (auto& inode : nodes) { add_node(inode); } return *this; }
	inline tree_t& add_node(node_tc& node) {
		NC_CHECK(is_tree(), "type error!", return *this);
		NC_CHECK(!has_node(node.get_name()), "key error!", return *this);
		NC_CHECK(!has_tree_copy(&node) && !node.has_tree_copy(this), "recursive error!", return *this);
		m_nodes.push_back(node);
		return *this;
	}
	template<typename ... args> tree_t& add_node(cstr_t key, args&& ... arguments) {
		NC_CHECK(is_tree(), "type error!", return *this);
		NC_CHECK(!has_node(key), "already used key!", return *this);
		m_nodes.push_back(node_t(key, std::forward<args>(arguments)...));
		return *this;
	}
	template<typename tname, typename ... args> tree_t& add_node(cstr_t key, args&& ... arguments) {
		return add_node(key, type_info_t::get_type<tname>(), std::forward<args>(arguments)...);
	}
	inline tree_t& rmv_node(size_t key) {
		NC_CHECK(is_tree(), "type error!", return *this);
		size_t itr = 0u; auto inode = m_nodes.begin();
		while (inode++ != m_nodes.end()) { if (itr++ == key) { m_nodes.erase(inode); return *this; } }
		NC_ERROR("key error!", return *this);
		return *this;
	}
	inline tree_t& rmv_node(cstr_t key) {
		NC_CHECK(is_tree(), "type error!", return);
		auto inode = m_nodes.begin();
		while (inode++ != m_nodes.end()) { if (inode->has_name(key)) { m_nodes.erase(inode); return *this; } }
		NC_ERROR("key error!", return *this);
		return *this;
	}
	/* vetters */
	inline v1bit_t has_node() const              { return get_count() != NC_NULL; }
	inline v1bit_t has_node(size_t key) const    { return get_count() > key; }
	inline v1bit_t has_node(cstr_t key) const    { for (auto& inode : m_nodes) { if (inode.has_name(key)) return NC_TRUTH; } return NC_FALSE; }
	inline v1bit_t has_copy(tree_tc* copy) const { for (auto& inode : m_nodes) { if (&inode == copy) return NC_TRUTH; } return this == copy; }
	inline v1bit_t is_leaf() const { return has_type<tree_t>() == NC_FALSE; }
	inline v1bit_t is_tree() const { return has_type<tree_t>() == NC_TRUTH; }
	inline v1bit_t has_tree_node() const              { for (auto& inode : m_nodes) { if (inode.has_tree_node()) { return NC_TRUTH; } } return has_node(); }
	inline v1bit_t has_tree_node(size_t key) const    { for (auto& inode : m_nodes) { if (inode.has_tree_node(key)) { return NC_TRUTH; } } return has_node(key); }
	inline v1bit_t has_tree_node(cstr_t key) const    { for (auto& inode : m_nodes) { if (inode.has_tree_node(key)) { return NC_TRUTH; } } return has_node(key); }
	inline v1bit_t has_tree_copy(tree_tc* copy) const { for (auto& inode : m_nodes) { if (inode.has_tree_copy(copy)) return NC_TRUTH; } return has_copy(copy); }
	inline v1bit_t has_tree_type(type_tc type) const       { for (auto& inode : m_nodes) { if (inode.has_tree_type(type)) { return NC_TRUTH; } } return has_type(type); }
	template<typename tname> v1bit_t has_tree_type() const { return has_tree_type(type_info_t::get_type<tname>()); }
	/* commands */
	inline auto begin() { return m_nodes.begin(); }
	inline auto end()   { return m_nodes.end(); }
	/* operators */
	inline tree_t& operator=(tree_tc& copy) { nc_name_owner_t::operator=(copy); std_nc_type_owner_t::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } return *this; }
	inline tree_t& operator=(tree_t&& copy) { nc_name_owner_t::operator=(copy); std_nc_type_owner_t::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } return *this; }
	inline node_t& operator[](size_t key)        { return get_node(key); }
	inline node_tc& operator[](size_t key) const { return get_node(key); }
	inline node_t& operator[](cstr_t key)        { return get_node(key); }
	inline node_tc& operator[](cstr_t key) const { return get_node(key); }
protected:
	nodes_t m_nodes;
};
#	endif /* NC_API */
#	if (defined NC_API && NC_FALSE)
/* includes */
#		include "nc_lib_name.hpp"
#		include "nc_lib_util.hpp"
/* types */
/// link_node_type
/// description:
template<typename tdata>
class nc_link_node_t
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
	/* getters */
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
	/* setters */
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
	/* vetters */
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
	/* commands */
	/* operators */
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
#	endif	/* NC_API */
/* end_of_file */
#endif	/* NC_LIB_GRAPH_HPP */