#ifndef NW_STD_TREE_H
#define NW_STD_TREE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "../std/nw_std_cont.h"
#	include "../info/nw_info_type.h"
namespace NW
{
	/// tree_component typed class
	/// description:
	/// --data structure for tree composition;
	template<typename tnode>
	class t_tree_cmp : public v_type_owner
	{
	public:
		using node_t = tnode;
		using node_tc = const node_t;
		using nodes_t = darray<node_t>;
		using nodes_tc = const nodes_t;
		using tree_t = t_tree_cmp<node_t>;
		using tree_tc = const tree_t;
	public:
		t_tree_cmp(cstr key = NW_DEFAULT_STR, nodes_tc& nodes = nodes_t()) :
			v_type_owner(type_info::get_type<tree_t>()),
			m_key(key), m_nodes(nodes_t()) { for (auto& inode : nodes) { add_node(inode); } }
		t_tree_cmp(cstr key, vtype_tc type) :
			v_type_owner(type),
			m_key(key), m_nodes(nodes_t()) { }
		t_tree_cmp(tree_tc& copy) :
			v_type_owner(copy),
			m_key(copy.m_key), m_nodes(copy.m_nodes) { }
		t_tree_cmp(tree_t&& copy) :
			v_type_owner(copy),
			m_key(copy.m_key), m_nodes(copy.m_nodes) { }
		virtual ~t_tree_cmp() = default;
		// --getters
		inline cstr get_key() const        { return &m_key[0]; }
		inline nodes_t& get_nodes()        { return m_nodes; }
		inline nodes_tc& get_nodes() const { return m_nodes; }
		inline cv1u get_count() const      { return m_nodes.size(); }
		inline node_t& get_node(cv1u key)        { NW_CHECK(has_node(key), "out of range", return *this); return m_nodes[key]; }
		inline node_tc& get_node(cv1u key) const { NW_CHECK(has_node(key), "out of range", return *this); return m_nodes[key]; }
		inline node_t& get_node(cstr key)        { for (auto& inode : m_nodes) { if (inode.has_key(key)) return inode; } NW_ERROR("not found!", return *this); }
		inline node_tc& get_node(cstr key) const { for (auto& inode : m_nodes) { if (inode.has_key(key)) return inode; } NW_ERROR("not found!", return *this); }
		template<typename tname> tname& get_node(cv1u key)             { static_cast<tname&>(get_node(key)); }
		template<typename tname> const tname& get_node(cv1u key) const { static_cast<const tname&>(get_node(key)); }
		template<typename tname> tname& get_node(cstr key)             { static_cast<tname&>(get_node(key)); }
		template<typename tname> const tname& get_node(cstr key) const { static_cast<const tname&>(get_node(key)); }
		inline size_tc get_tree_size() const { size_t tree_size = sizeof(*this); for (auto& inode : m_nodes) { tree_size += inode.get_tree_size(); } return tree_size; }
		inline dstr get_tree_str(cv1u generation = 1u) {
			stm_io_str stm(" ");
			dstr offset(NW_CAST_SIZE((generation == 0ul ? 1ul : generation) * 4ul), ' ');

			stm << &offset[4u] << (is_tree() ? "[tree]" : "[leaf]") << ":{" NW_STR_EOL;
			stm << &offset[0u] << "key:" << get_key() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "vtype:" << get_vtype_info() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_count:" << get_count() << ";" << NW_STR_EOL;
			stm << &offset[0u] << "tree_size: " << get_tree_size() << ";" NW_STR_EOL;
			for (auto& inode : get_nodes()) { stm << inode.get_tree_str(generation + 1u); }
			stm << &offset[4u] << "}:" << (is_tree() ? "[tree]" : "[leaf]") << ";" NW_STR_EOL;

			return stm.str();
		}
		// --setters
		node_t& add_node(node_tc& node) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(node.get_key()), "already used key!", return *this);
			NW_CHECK(&node != this, "tree recursion!", return *this);
			for (auto& inode : node.get_nodes()) { NW_CHECK(&inode != this, "tree recursion!", return *this); }
			m_nodes.push_back(node);
			return m_nodes.back();
		}
		template<typename ... args>
		node_t& add_node(cstr key, args&& ... arguments) {
			NW_CHECK(is_tree(), "type error!", return *this);
			NW_CHECK(!has_node(key), "already used key!", return *this);
			m_nodes.push_back(node_t(key, std::forward<args>(arguments)...));
			return m_nodes.back();
		}
		template<typename tname, typename ... args>
		node_t& add_node(cstr key, args&& ... arguments) { return add_node(key, type_info::get_type<tname>(), std::forward<args>(arguments)...); }
		v1nil rmv_node(cv1u key) {
			NW_CHECK(is_tree(), "type error!", return);
			NW_CHECK(has_node(key), "not found", return);
			m_nodes.erase(m_nodes.begin() + key);
		}
		v1nil rmv_node(cstr key) {
			NW_CHECK(is_tree(), "type error!", return);
			NW_CHECK(has_node(key), "not found!", return);
			for (iter_t inode = m_nodes.begin(); inode != m_nodes.end(); inode++) { if (inode->has_key(key)) { m_nodes.erase(inode); return; } }
		}
		// --predicates
		inline v1bit has_key(cstr key) const  { return m_key == key; }
		inline v1bit has_node(cv1u key) const { return key < get_count(); }
		inline v1bit has_node(cstr key) const { for (auto& inode : m_nodes) { if (inode.has_key(key)) return NW_TRUE; } return NW_FALSE; }
		inline v1bit is_leaf() const { return has_vtype<tree_t>() == NW_FALSE; }
		inline v1bit is_tree() const { return has_vtype<tree_t>() == NW_TRUE; }
		// --operators
		inline v1nil operator=(tree_tc& copy) { v_type_owner::operator=(copy); m_key = copy.m_key; m_nodes = copy.m_nodes; }
		inline v1nil operator=(tree_t&& copy) { v_type_owner::operator=(copy); m_key = copy.m_key; m_nodes = copy.m_nodes; }
		inline node_t& operator[](cv1u key)        { return get_node(key); }
		inline node_tc& operator[](cv1u key) const { return get_node(key); }
		inline node_t& operator[](cstr key)        { return get_node(key); }
		inline node_tc& operator[](cstr key) const { return get_node(key); }
	protected:
		dstr m_key;
		nodes_t m_nodes;
	};
}
#endif // NW_API
#endif	// NW_STD_TREE_H