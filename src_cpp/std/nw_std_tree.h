#ifndef NW_STD_TREE_H
#define NW_STD_TREE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_std_name.h"
#	include "nw_std_type.h"
#	include "nw_std_util.h"
#	include "nw_std_list.h"
namespace NW
{
	/// tree_component typed class
	/// description:
	/// --data structure for tree composition;
	template<typename tnode>
	class t_tree_cmp : public a_name_owner, public a_type_owner
	{
	public:
		using node_t = tnode;
		using node_tc = const node_t;
		using nodes_t = list2_t<node_t>;
		using nodes_tc = const nodes_t;
		using node_list_t = init_list_t<node_t>;
		using node_list_tc = const node_list_t;
		using tree_t = t_tree_cmp<node_t>;
		using tree_tc = const tree_t;
	public:
		inline t_tree_cmp() : a_name_owner(), a_type_owner(), m_nodes(nodes_t()) { set_name(type_info::get<tree_t>().name); set_type(type_info::get<tree_t>().type); }
		inline t_tree_cmp(cstr_t name, nodes_tc& nodes) : t_tree_cmp()           { set_name(name), set_nodes(nodes); }
		inline t_tree_cmp(cstr_t name, type_tc type) : t_tree_cmp()              { set_name(name); set_type(type); }
		inline t_tree_cmp(tree_tc& copy) : t_tree_cmp() { operator=(copy); }
		inline t_tree_cmp(tree_t&& copy) : t_tree_cmp() { operator=(copy); }
		~t_tree_cmp() { }
		// --getters
		inline nodes_t& get_nodes()        { return m_nodes; }
		inline nodes_tc& get_nodes() const { return m_nodes; }
		inline size_t get_count() const { size_t count = 0u; for (auto& inode : m_nodes) { count++; } return count; }
		inline size_t get_space() const { return get_count() * sizeof(node_t); }
		inline node_t& get_node(size_t key) {
			size_t itr = 0u; auto inode = m_nodes.begin();
			do { if (itr++ == key) { return *inode; } } while (inode++ != m_nodes.end());
			NW_ERROR("key error!", return *this);
			return *this;
		}
		inline node_tc& get_node(size_t key) const {
			size_t itr = NW_NULL; auto inode = m_nodes.begin();
			do { if (itr++ == key) { return *inode; } } while (inode++ != m_nodes.end());
			NW_ERROR("key error!", return *this);
			return *this;
		}
		inline node_t& get_node(cstr_t key) {
			for (auto& inode : m_nodes) { if (inode.has_name(key)) { return inode; } }
			NW_ERROR("key error!", return *this);
			return *this;
		}
		inline node_tc& get_node(cstr_t key) const {
			for (auto& inode : m_nodes) { if (inode.has_name(key)) { return inode; } }
			NW_ERROR("key error!", return *this);
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
			dstr_t offset(NW_CAST_SIZE((generation == 0ul ? 1ul : generation) * 4ul), ' ');

			stm << &offset[4u] << (is_tree() ? "[tree]" : "[leaf]") << ":{" NW_STR_EOL;
			stm << &offset[0u] << "name:" << get_name() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "type:" << get_type() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "count:" << get_count() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "space:" << get_space() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "type_info:" << get_type_info() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_count:" << get_tree_count() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_space: " << get_tree_space() << ";" NW_STR_EOL;
			for (auto& inode : get_nodes()) { stm << inode.get_tree_str(generation + 1u); }
			stm << &offset[4u] << "}:" << (is_tree() ? "[tree]" : "[leaf]") << ";" NW_STR_EOL;

			return stm.str();
		}
		// --setters
		inline tree_t& set_nodes(nodes_tc& nodes) { NW_CHECK(is_tree(), "type error!", return *this); m_nodes.clear(); for (auto& inode : nodes) { add_node(inode); } return *this; }
		inline tree_t& set_nodes(node_list_tc& nodes) { NW_CHECK(is_tree(), "type error!", return *this); m_nodes.clear(); for (auto& inode : nodes) { add_node(inode); } return *this; }
		inline tree_t& add_node(node_tc& node) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(node.get_name()), "key error!", return *this);
			NW_CHECK(!has_tree_copy(&node) && !node.has_tree_copy(this), "recursive error!", return *this);
			m_nodes.push_back(node);
			return *this;
		}
		template<typename ... args>
		tree_t& add_node(cstr_t key, args&& ... arguments) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(key), "already used key!", return *this);
			m_nodes.push_back(node_t(key, std::forward<args>(arguments)...));
			return *this;
		}
		template<typename tname, typename ... args>
		tree_t& add_node(cstr_t key, args&& ... arguments) { return add_node(key, type_info::get_type<tname>(), std::forward<args>(arguments)...); }
		inline tree_t& rmv_node(size_t key) {
			NW_CHECK(is_tree(), "type error!", return *this);
			size_t itr = 0u; auto inode = m_nodes.begin();
			while (inode++ != m_nodes.end()) { if (itr++ == key) { m_nodes.erase(inode); return *this; } }
			NW_ERROR("key error!", return *this);
			return *this;
		}
		inline tree_t& rmv_node(cstr_t key) {
			NW_CHECK(is_tree(), "type error!", return);
			auto inode = m_nodes.begin();
			while (inode++ != m_nodes.end()) { if (inode->has_name(key)) { m_nodes.erase(inode); return *this; } }
			NW_ERROR("key error!", return *this);
			return *this;
		}
		// --predicates
		inline v1bit has_node() const              { return get_count() != NW_NULL; }
		inline v1bit has_node(size_t key) const    { return get_count() > key; }
		inline v1bit has_node(cstr_t key) const    { for (auto& inode : m_nodes) { if (inode.has_name(key)) return NW_TRUE; } return NW_FALSE; }
		inline v1bit has_copy(tree_tc* copy) const { for (auto& inode : m_nodes) { if (&inode == copy) return NW_TRUE; } return this == copy; }
		inline v1bit is_leaf() const { return has_type<tree_t>() == NW_FALSE; }
		inline v1bit is_tree() const { return has_type<tree_t>() == NW_TRUE; }
		inline v1bit has_tree_node() const              { for (auto& inode : m_nodes) { if (inode.has_tree_node()) { return NW_TRUE; } } return has_node(); }
		inline v1bit has_tree_node(size_t key) const    { for (auto& inode : m_nodes) { if (inode.has_tree_node(key)) { return NW_TRUE; } } return has_node(key); }
		inline v1bit has_tree_node(cstr_t key) const    { for (auto& inode : m_nodes) { if (inode.has_tree_node(key)) { return NW_TRUE; } } return has_node(key); }
		inline v1bit has_tree_copy(tree_tc* copy) const { for (auto& inode : m_nodes) { if (inode.has_tree_copy(copy)) return NW_TRUE; } return has_copy(copy); }
		inline v1bit has_tree_type(type_tc type) const       { for (auto& inode : m_nodes) { if (inode.has_tree_type(type)) { return NW_TRUE; } } return has_type(type); }
		template<typename tname> v1bit has_tree_type() const { return has_tree_type(type_info::get_type<tname>()); }
		// --operators
		inline v1nil operator=(tree_tc& copy) { a_name_owner::operator=(copy); a_type_owner::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } }
		inline v1nil operator=(tree_t&& copy) { a_name_owner::operator=(copy); a_type_owner::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } }
		inline node_t& operator[](size_t key)        { return get_node(key); }
		inline node_tc& operator[](size_t key) const { return get_node(key); }
		inline node_t& operator[](cstr_t key)        { return get_node(key); }
		inline node_tc& operator[](cstr_t key) const { return get_node(key); }
		// --core_methods
		inline auto begin() { return m_nodes.begin(); }
		inline auto end()   { return m_nodes.end(); }
	protected:
		nodes_t m_nodes;
	};
}
#endif // NW_API
#endif	// NW_STD_TREE_H