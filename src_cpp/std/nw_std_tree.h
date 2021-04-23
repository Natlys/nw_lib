#ifndef NW_STD_TREE_H
#define NW_STD_TREE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../info/nw_info_name.h"
#	include "../info/nw_info_type.h"
#	include "nw_std_list.h"
namespace NW
{
	/// tree_component typed class
	/// description:
	/// --data structure for tree composition;
	template<typename tnode>
	class t_tree_cmp : public v_type_owner, public a_name_owner
	{
	public:
		using node_t = tnode;
		using node_tc = const node_t;
		using nodes_t = t_list2<node_t>;
		using nodes_tc = const nodes_t;
		using tree_t = t_tree_cmp<node_t>;
		using tree_tc = const tree_t;
	public:
		t_tree_cmp(cstr_t name = NW_DEFAULT_STR, nodes_tc& nodes = nodes_t()) :
			a_name_owner(name), v_type_owner(type_info::get_type<tree_t>()),
			m_nodes(nodes_t()) { for (auto& inode : nodes) { add_node(inode); } }
		t_tree_cmp(cstr_t name, vtype_tc type) :
			a_name_owner(name), v_type_owner(type),
			m_nodes(nodes_t()) { }
		t_tree_cmp(tree_tc& copy) :
			a_name_owner(copy), v_type_owner(copy),
			m_nodes(copy.m_nodes) { }
		t_tree_cmp(tree_t&& copy) :
			a_name_owner(copy), v_type_owner(copy),
			m_nodes(copy.m_nodes) { }
		virtual ~t_tree_cmp() = default;
		// --getters
		inline nodes_t& get_nodes()        { return m_nodes; }
		inline nodes_tc& get_nodes() const { return m_nodes; }
		inline cv1u get_count() const      { return m_nodes.size(); }
		inline cv1u get_space() const      { return sizeof(node_t) * m_nodes.size(); }
		inline node_t& get_node(cv1u key)        { NW_CHECK(has_node(key), "not found!", return *this); auto itr = m_nodes.begin(); std::advance(itr, key); return *itr; }
		inline node_tc& get_node(cv1u key) const { NW_CHECK(has_node(key), "not found!", return *this); auto itr = m_nodes.begin(); std::advance(itr, key); return *itr; }
		inline node_t& get_node(cstr_t key)        { for (auto& inode : m_nodes) { if (inode.has_name(key)) return inode; } NW_ERROR("not found!", return *this); }
		inline node_tc& get_node(cstr_t key) const { for (auto& inode : m_nodes) { if (inode.has_name(key)) return inode; } NW_ERROR("not found!", return *this); }
		template<typename tname> tname& get_node(cv1u key)             { static_cast<tname&>(get_node(key)); }
		template<typename tname> const tname& get_node(cv1u key) const { static_cast<const tname&>(get_node(key)); }
		template<typename tname> tname& get_node(cstr_t key)           { static_cast<tname&>(get_node(key)); }
		template<typename tname> const tname& get_node(cstr_t key) const { static_cast<const tname&>(get_node(key)); }
		inline node_t& get_tree_node(cv1u key) { for (auto& inode : m_nodes)   { if (inode.has_node_tree(key)) { return inode.get_node_tree(key); } } return get_node(key); }
		inline node_t& get_tree_node(cstr_t key) { for (auto& inode : m_nodes) { if (inode.has_node_tree(key)) { return inode.get_node_tree(key); } } return get_node(key); }
		inline cv1u get_tree_space() const { v1u tree_space = sizeof(*this); for (auto& inode : m_nodes) { tree_space += inode.get_tree_space(); } return tree_space; }
		inline cv1u get_tree_count() const { v1u tree_count = 1u; for (auto& inode : m_nodes) { tree_count += inode.get_tree_count(); } return tree_count; }
		inline dstr_t get_tree_str(cv1u generation = 1u) {
			ops_stream_t stm(" ");
			dstr_t offset(NW_CAST_SIZE((generation == 0ul ? 1ul : generation) * 4ul), ' ');

			stm << &offset[4u] << (is_tree() ? "[tree]" : "[leaf]") << ":{" NW_STR_EOL;
			stm << &offset[0u] << "key:" << get_key() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "vtype:" << get_vtype_info() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "count:" << get_count() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "space:" << get_space() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_count:" << get_tree_count() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_space: " << get_tree_space() << ";" NW_STR_EOL;
			for (auto& inode : get_nodes()) { stm << inode.get_tree_str(generation + 1u); }
			stm << &offset[4u] << "}:" << (is_tree() ? "[tree]" : "[leaf]") << ";" NW_STR_EOL;

			return stm.str();
		}
		// --setters
		inline v1nil set_nodes(nodes_tc& nodes) { NW_CHECK(is_tree(), "type error!", return); m_nodes.clear(); for (auto& inode : nodes) { add_node(inode); } }
		node_t& add_node(node_tc& node) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(node.get_name()), "already used key!", return *this);
			NW_CHECK(&node != this, "tree recursion!", return *this);
			for (auto& inode : node.get_nodes()) { NW_CHECK(&inode != this, "tree recursion!", return *this); }
			m_nodes.push_back(node);
			return m_nodes.back();
		}
		template<typename ... args>
		node_t& add_node(cstr_t key, args&& ... arguments) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(key), "already used key!", return *this);
			m_nodes.push_back(node_t(key, std::forward<args>(arguments)...));
			return m_nodes.back();
		}
		template<typename tname, typename ... args>
		node_t& add_node(cstr_t key, args&& ... arguments) { return add_node(key, type_info::get_type<tname>(), std::forward<args>(arguments)...); }
		v1nil rmv_node(cv1u key) {
			NW_CHECK(is_tree(), "type error!", return);
			NW_CHECK(has_node(key), "not found", return);
			m_nodes.erase(m_nodes.begin() + key);
		}
		v1nil rmv_node(cstr_t key) {
			NW_CHECK(is_tree(), "type error!", return);
			NW_CHECK(has_node(key), "not found!", return);
			for (auto inode = m_nodes.begin(); inode != m_nodes.end(); inode++) { if (inode->has_name(key)) { m_nodes.erase(inode); return; } }
		}
		// --predicates
		inline v1bit has_node() const         { return get_count() != NW_NULL; }
		inline v1bit has_node(cv1u key) const { return get_count() > key; }
		inline v1bit has_node(cstr_t key) const { for (auto& inode : m_nodes) { if (inode.has_name(key)) return NW_TRUE; } return NW_FALSE; }
		inline v1bit is_leaf() const { return has_vtype<tree_t>() == NW_FALSE; }
		inline v1bit is_tree() const { return has_vtype<tree_t>() == NW_TRUE; }
		inline v1bit has_node_tree(cv1u key) const { for (auto& inode m_nodes) { if (inode.has_node_tree(key)) { return NW_TRUE; } } return has_node(key); }
		inline v1bit has_node_tree(cstr_t key) const { for (auto& inode m_nodes) { if (inode.has_node_tree(key)) { return NW_TRUE; } } return has_node(key); }
		inline v1bit has_vtype_tree(vtype_tc type) const      { for (auto& inode : m_nodes) { if (inode.has_vtype_tree(type)) { return NW_TRUE; } } return has_vtype(type); }
		template<typename tname> v1bit has_vtype_tree() const { return has_vtype_tree(type_info::get_type<tname>()); }
		// --operators
		inline v1nil operator=(tree_tc& copy)  { a_name_owner::operator=(copy); v_type_owner::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } }
		inline v1nil operator=(tree_t && copy) { a_name_owner::operator=(copy); v_type_owner::operator=(copy); if (is_tree()) { set_nodes(copy.get_nodes()); } }
		inline node_t& operator[](cv1u key)        { return get_node(key); }
		inline node_tc& operator[](cv1u key) const { return get_node(key); }
		inline node_t& operator[](cstr_t key)        { return get_node(key); }
		inline node_tc& operator[](cstr_t key) const { return get_node(key); }
	protected:
		nodes_t m_nodes;
	};
}
#endif // NW_API
#endif	// NW_STD_TREE_H