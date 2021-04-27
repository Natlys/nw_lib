#ifndef NW_MEM_COMPONENT_H
#define NW_MEM_COMPONENT_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
#	include "nw_mem_sys.h"
namespace NW
{
	/// typed_memory_user
	/// description:
	/// --overrides default new/delete operators
	/// so that the memory is allocated by memory system
	template<class tgiver>
	class t_mem_user
	{
	public:
		using giver_t = tgiver;
		using giver_tc = const giver_t;
	public:
		t_mem_user() = default;
		virtual ~t_mem_user() = default;
		// --operators
		inline ptr_t operator new(size_t size, ptr_t data) { return ::operator new(size, data); }
		inline ptr_t operator new(size_t size)   { return giver_t::static_take(size, NW_DEFAULT_SIZE); }
		inline ptr_t operator new[](size_t size) { return giver_t::static_take(size, NW_DEFAULT_SIZE); }
		inline v1nil operator delete(ptr_t data, size_t size)   { giver_t::static_free(data, size, NW_DEFAULT_SIZE); }
		inline v1nil operator delete[](ptr_t data, size_t size) { giver_t::static_free(data, size, NW_DEFAULT_SIZE); }
	};
	typedef t_mem_user<mem_sys> a_mem_user;
	/// abstract_memory_owner class
	class a_mem_owner
	{
	public:
	public:
		inline ptr_t operator new(size_t size) = delete;
		inline ptr_t operator new[](size_t size) = delete;
		inline v1nil operator delete(ptr_t data, size_t size) = delete;
		inline v1nil operator delete[](ptr_t data, size_t size) = delete;
	};
}
#endif
#endif	// NW_MEM_COMPONENT_H