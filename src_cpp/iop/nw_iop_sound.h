#ifndef NW_IOP_SOUND_H
#define NW_IOP_SOUND_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	/// input_output_sound_format_wav_type
	struct NW_API iop_sound_wav_info_t
	{
	public:
	public:
		// --ctor_dtor
		constexpr inline iop_sound_wav_info_t() {}
		inline ~iop_sound_wav_info_t() = default;
		// --getters
		// --setters
		// --predicates
		// --operators
	public:
		v1s08 chunk_id[4];
		v1u64 chunk_size;
		v1u08 format[4];
		v1u08 subchunk_id[4];
		v1u64 subchunk_size;
		v1u16 aud_format;
		v1u16 nof_channels;
		v1u64 sample_rate;
		v1u64 byte_rate;
		v1u16 block_align;
		v1u16 bits_per_sample;
		v1s08 subchunk2_id[4];
		v1u64 subchunk2_size;
	};
	/// input_output_sound_type
	class NW_API iop_sound_t
	{
	public:
		using sound_t = iop_sound_t;
		using sound_tc = const sound_t;
	public:
		// --ctor_dtor
		constexpr inline iop_sound_t() { }
		inline ~iop_sound_t() { }
		// --getters
		// --setters
		// --predicates
		// --operators
		// // --assignment
		// // --convertion
		// --core_methods
	protected:
	};
}
#endif	// NW_API
#endif	// NW_IOP_SOUND_H