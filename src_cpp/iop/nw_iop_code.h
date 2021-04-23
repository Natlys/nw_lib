#ifndef NW_IOP_CODE_H
#define NW_IOP_CODE_H
#include "nw_lib_core.hpp"
#if (defined NW_API)
namespace NW
{
	// keyboard codes
	// // controls
#	define NW_KEYCODE_BACK  8
#	define NW_KEYCODE_VTAB  9
#	define NW_KEYCODE_HTAB  11
#	define NW_KEYCODE_ENTER 13
#	define NW_KEYCODE_SHIFT 16
#	define NW_KEYCODE_CONTR 18
#	define NW_KEYCODE_ALTER 19
#	define NW_KEYCODE_PAUSE 20
#	define NW_KEYCODE_CAPS  26
#	define NW_KEYCODE_ESCP  27
#	define NW_KEYCODE_ARROW_LEFT 37
#	define NW_KEYCODE_ARROW_UPWD 38
#	define NW_KEYCODE_ARROW_RIGT 39
#	define NW_KEYCODE_ARROW_DOWN 40
#	define NW_KEYCODE_INSERT 45
#	define NW_KEYCODE_DELETE 46
#	define NW_KEYCODE_HOME   47
	// // printable
#	define NW_KEYCODE_SPACE   32
#	define NW_KEYCODE_EXCLAIM 33
#	define NW_KEYCODE_QUOT    34
#	define NW_KEYCODE_HASH    35
#	define NW_KEYCODE_DOLLAR  36
#	define NW_KEYCODE_PERCEN  37
#	define NW_KEYCODE_AMPERS  38
#	define NW_KEYCODE_APOSTR  39
#	define NW_KEYCODE_BRACKET_LEFT 40
#	define NW_KEYCODE_BRACKET_RIGT 41
#	define NW_KEYCODE_ASTERK  42
#	define NW_KEYCODE_PLUS    43
#	define NW_KEYCODE_COMMA   44
#	define NW_KEYCODE_MINS    45
#	define NW_KEYCODE_DOT     46
#	define NW_KEYCODE_SLASH   47
	// // digits
#	define NW_KEYCODE_0 48
#	define NW_KEYCODE_1 49
#	define NW_KEYCODE_2 50
#	define NW_KEYCODE_3 51
#	define NW_KEYCODE_4 52
#	define NW_KEYCODE_5 53
#	define NW_KEYCODE_6 54
#	define NW_KEYCODE_7 55
#	define NW_KEYCODE_8 56
#	define NW_KEYCODE_9 57
	// // other symbols
#	define NW_KEYCODE_COLONON 58
#	define NW_KEYCODE_SEMICOL 59
#	define NW_KEYCODE_LESSER  60
#	define NW_KEYCODE_EQULIT  61
#	define NW_KEYCODE_GRETER  62
	// // letters
	// // // upper case
#	define NW_KEYCODE_A 65
#	define NW_KEYCODE_B 66
#	define NW_KEYCODE_C 67
#	define NW_KEYCODE_D 68
#	define NW_KEYCODE_E 69
#	define NW_KEYCODE_F 70
#	define NW_KEYCODE_G 71
#	define NW_KEYCODE_H 72
#	define NW_KEYCODE_I 73
#	define NW_KEYCODE_J 74
#	define NW_KEYCODE_K 75
#	define NW_KEYCODE_L 76
#	define NW_KEYCODE_M 77
#	define NW_KEYCODE_N 78
#	define NW_KEYCODE_O 79
#	define NW_KEYCODE_P 80
#	define NW_KEYCODE_Q 81
#	define NW_KEYCODE_R 82
#	define NW_KEYCODE_S 83
#	define NW_KEYCODE_T 84
#	define NW_KEYCODE_U 85
#	define NW_KEYCODE_V 86
#	define NW_KEYCODE_W 87
#	define NW_KEYCODE_X 88
#	define NW_KEYCODE_Y 89
#	define NW_KEYCODE_Z 90
	// // // lower case
#	define NW_KEYCODE_a 97
#	define NW_KEYCODE_b 98
#	define NW_KEYCODE_c 99
#	define NW_KEYCODE_d 100
#	define NW_KEYCODE_e 101
#	define NW_KEYCODE_f 102
#	define NW_KEYCODE_g 103
#	define NW_KEYCODE_h 104
#	define NW_KEYCODE_i 105
#	define NW_KEYCODE_j 106
#	define NW_KEYCODE_k 107
#	define NW_KEYCODE_l 108
#	define NW_KEYCODE_m 109
#	define NW_KEYCODE_n 110
#	define NW_KEYCODE_o 111
#	define NW_KEYCODE_p 112
#	define NW_KEYCODE_q 113
#	define NW_KEYCODE_r 114
#	define NW_KEYCODE_s 115
#	define NW_KEYCODE_t 116
#	define NW_KEYCODE_u 117
#	define NW_KEYCODE_v 118
#	define NW_KEYCODE_w 119
#	define NW_KEYCODE_x 120
#	define NW_KEYCODE_y 121
#	define NW_KEYCODE_z 122,
	// // functional keys
#	define NW_KEYCODE_F1 112
#	define NW_KEYCODE_F2 113
#	define NW_KEYCODE_F3 114
#	define NW_KEYCODE_F4 115
#	define NW_KEYCODE_F5 116
#	define NW_KEYCODE_F6 117
#	define NW_KEYCODE_F7 118
#	define NW_KEYCODE_F8 119
#	define NW_KEYCODE_F9 120
#	define NW_KEYCODE_F10 121
#	define NW_KEYCODE_F11 122
#	define NW_KEYCODE_F12 123
	// // other
#	define NW_KEYCODE_RECT_DITH 177
#	define NW_KEYCODE_RECT_QUAD 254
#	define NW_KEYCODE_COUNT     255
	// cursor codes
#	define NW_CURCODE_0     0
#	define NW_CURCODE_1     1
#	define NW_CURCODE_2     2
#	define NW_CURCODE_3     3
#	define NW_CURCODE_4     4
#	define NW_CURCODE_5     5
#	define NW_CURCODE_6     6
#	define NW_CURCODE_7     7
#	define NW_CURCODE_LEFT  NW_CURCODE_0
#	define NW_CURCODE_RIGT  NW_CURCODE_1
#	define NW_CURCODE_MIDL  NW_CURCODE_2
#	define NW_CURCODE_COUNT NW_CURCODE_7
	// button states
#	define NW_BUTTON_RAISE 1 << 1
#	define NW_BUTTON_PRESS 1 << 2
#	define NW_BUTTON_FREE  1 << 3
#	define NW_BUTTON_HELD  1 << 4
}
namespace NW
{
	/// keyboard_button struct
	struct NW_API iop_button_kbd
	{
	public:
		using state_t = v1u08;
		using state_tc = const state_t;
		using code_t = v1u16;
		using code_tc = const code_t;
	public:
		state_t m_state = NW_BUTTON_FREE;
		v1u m_nof_repeats = NW_NULL;
	};
	/// iop_button_crs struct
	struct NW_API iop_button_crs
	{
		using state_t = v1u08;
		using state_tc = const state_t;
	public:
		state_t m_state = NW_BUTTON_FREE;
		using code_t = v1u16;
		using code_tc = const code_t;
		// free state
		v1f m_free_coord_x = NW_NULL, m_free_coord_y = NW_NULL;
		v1f m_free_delta_x = NW_NULL, m_free_delta_y = NW_NULL;
		// held state
		v1f m_held_coord_x = NW_NULL, m_held_coord_y = NW_NULL;
		v1f m_held_delta_x = NW_NULL, m_held_delta_y = NW_NULL;
	};
}
#endif
#endif	// NW_IOP_CODE_H
