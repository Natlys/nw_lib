#ifndef NWL_IO_SWITCH_H
#define NWL_IO_SWITCH_H
#include <nwl_core.hpp>
namespace NW
{
	enum error_codes : ui32 {
		ERC_DEFAULT = 0,
		ERC_NO_INIT = 1, ERC_NO_QUIT = 2,
		ERC_NO_SUPPORT, ERC_NO_STATE,
		ERC_NO_MEMORY,
		ERC_NO_LOAD, ERC_NO_SAVE,
		ERC_RUNTIME,
		ERC_DATA_BAD, ERC_DATA_LOSS, ERC_DATA_OVERFLOW, ERC_DATA_UNDERFLOW,
		ERC_UNKNOWN_ID, ERC_UNKNOWN_NAME,
		ERC_INVALID_FORMAT, ERC_INVALID_SYNTAX, ERC_INVALID_TYPE, ERC_INVALID_ENUM,
		ERC_COMPILLATION, ERC_LINKAGE
	};
	enum event_types : ui32 {
		EVT_DEFAULT = 1 << 0,
		EVT_MS_MOVE = 1 << 1, EVT_MS_COORD = 1 << 2, EVT_MS_SCROLL = 1 << 3, EVT_MS_PRESSED = 1 << 4, EVT_MS_RELEASED = 1 << 5, EVT_MS_DOUBLE_CLICK = 1 << 6,
		EVT_KBD_RELEASED = 1 << 8, EVT_KBD_PRESSED = 1 << 9, EVT_KBD_CHAR = 1 << 10,
		EVT_WND_CLOSE = 1 << 12, EVT_WND_RESIZE = 1 << 13, EVT_WND_MOVE = 1 << 14, EVT_WND_FOCUS = 1 << 15, EVT_WND_DEFOCUS = 1 << 16,
		EVT_APP_DROP_FILE = 1 << 20
	};
	enum event_categories : ui32 {
		EVC_DEFAULT = EVT_DEFAULT,
		EVC_MOUSE = EVT_MS_MOVE | EVT_MS_COORD | EVT_MS_SCROLL | EVT_MS_PRESSED | EVT_MS_RELEASED | EVT_MS_DOUBLE_CLICK,
		EVC_KEYBOARD = EVT_KBD_PRESSED | EVT_KBD_RELEASED | EVT_KBD_CHAR,
		EVC_WINDOW = EVT_WND_CLOSE | EVT_WND_RESIZE | EVT_WND_MOVE | EVT_WND_FOCUS | EVT_WND_DEFOCUS,
		EVC_APPLICATION = EVT_APP_DROP_FILE
	};
	enum button_states : ui32 {
		BS_DEFAULT = 0,
		BS_HELD, BS_FREE,
		BS_RELEASED, BS_PRESSED,
	};
	enum keyboard_codes : ui32 {
		// controls
		KBC_BACKSPACE = 8,	KBC_VTAB = 9,	KBC_HTAB = 11,	KBC_ENTER = 13,
		KBC_LSHIFT = 16,	KBC_RSHIFT = 16,
		KBC_LCTRL = 17,		KBC_RCTRL = 18,
		KBC_LALT = 19,		KBC_RALT = 19,
		KBC_PAUSE = 20,		KBC_CAPS_LOCK = 26,	KBC_ESCAPE = 27,
		KBC_ARR_LT = 37,	KBC_ARR_UP = 38,	KBC_ARR_RT = 39,	KBC_ARR_DN = 40,
		KBC_INS = 45,		KBC_DEL = 46,		KBC_HOME = 47,
		// printable symbols
		KBC_SPACE = 32,		KBC_EXCLAIM = 33,
		KBC_QUOTE = 34,		KBC_HASH = 35,
		KBC_DOLLAR = 36,	KBC_PERCENT = 37,
		KBC_AMPERSAND = 38,	KBC_APOSTROPHE = 39,
		KBC_LBRACKET = 40,	KBC_RBRACKET = 41,
		KBC_ASTERISK = 42,	KBC_PLUS = 43,
		KBC_COMMA = 44,		KBC_MINUS = 45,
		KBC_DOT = 46,		KBC_SLASH = 47,
		// digits
		KBC_0 = 48,	KBC_1 = 49,	KBC_2 = 50,	KBC_3 = 51, KBC_4 = 52,
		KBC_5 = 53,	KBC_6 = 54,	KBC_7 = 55, KBC_8 = 56, KBC_9 = 57,
		// other symbols
		KBC_COLON = 58,	KBC_SEMICOLON = 59,
		KBC_LES = 60,	KBC_EQU = 61,	KBC_GRT = 62,
		// letters
		// --upper case
		KBC_A = 65,		KBC_B = 66,		KBC_C = 67,		KBC_D = 68,
		KBC_E = 69,		KBC_F = 70,		KBC_G = 71,		KBC_H = 72,
		KBC_I = 73,		KBC_J = 74,		KBC_K = 75,		KBC_L = 76,
		KBC_M = 77,		KBC_N = 78,		KBC_O = 79,		KBC_P = 80,
		KBC_Q = 81,		KBC_R = 82,		KBC_S = 83,		KBC_T = 84,
		KBC_U = 85,		KBC_V = 86,		KBC_W = 87,		KBC_X = 88,
		KBC_Y = 89,		KBC_Z = 90,
		// --lower case
		KBC_a = 97,		KBC_b = 98,		KBC_c = 99,		KBC_d = 100,
		KBC_e = 101,	KBC_f = 102,	KBC_g = 103,	KBC_h = 104,
		KBC_i = 105,	KBC_j = 106,	KBC_k = 107,	KBC_l = 108,
		KBC_m = 109,	KBC_n = 110,	KBC_o = 111,	KBC_p = 112,
		KBC_q = 113,	KBC_r = 114,	KBC_s = 115,	KBC_t = 116,
		KBC_u = 117,	KBC_v = 118,	KBC_w = 119,	KBC_x = 120,
		KBC_y = 121,	KBC_z = 122,
		// functional keys
		KBC_F1 = 112,	KBC_F2 = 113,	KBC_F3 = 114,
		KBC_F4 = 115,	KBC_F5 = 116,	KBC_F6 = 117,
		KBC_F7 = 118,	KBC_F8 = 119,	KBC_F9 = 120,
		KBC_F10 = 121,	KBC_F11 = 122,	KBC_F12 = 123,
		// other
		KBC_RECT_DITHER = 177,	KBC_QUAD = 254,
		KBC_COUNT = 255
	};
	enum mouse_codes : ui8 {
		MSC_DEFAULT = 0,
		MSC_0 = 0, MSC_1 = 1, MSC_2 = 2,
		MSC_3, MSC_4, MSC_5,
		MSC_6, MSC_7,
		MSC_LEFT = MSC_0, MSC_RIGHT = MSC_1, MSC_MIDDLE = MSC_2,
		MSC_COUNT = MSC_7
	};
}
#endif	// NWL_IO_SWITCH_H