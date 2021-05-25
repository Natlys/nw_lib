#ifndef NC_STB_TEXT_EDIT_H
#  define NC_STB_TEXT_EDIT_H
#  include "../nc_lib_core.hxx"
#  if (defined NC_API)

//
//     STB_TexteditState
//
// Definition of STB_TexteditState which you should store
// per-textfield; it includes cursor position, selection state,
// and undo state.
//

#     ifndef STB_TEXTEDIT_UNDOSTATECOUNT
#        define STB_TEXTEDIT_UNDOSTATECOUNT   99
#     endif
#     ifndef STB_TEXTEDIT_UNDOCHARCOUNT
#        define STB_TEXTEDIT_UNDOCHARCOUNT   999
#     endif
#     ifndef STB_TEXTEDIT_CHARTYPE
#        define STB_TEXTEDIT_CHARTYPE        int
#     endif
#     ifndef STB_TEXTEDIT_STRING
#        define STB_TEXTEDIT_STRING          char*
#     endif
#     ifndef STB_TEXTEDIT_POSITIONTYPE
#        define STB_TEXTEDIT_POSITIONTYPE    int
#     endif

typedef struct
{
   // private data
   STB_TEXTEDIT_POSITIONTYPE  where;
   STB_TEXTEDIT_POSITIONTYPE  insert_length;
   STB_TEXTEDIT_POSITIONTYPE  delete_length;
   int                        char_storage;
} StbUndoRecord;

typedef struct
{
   // private data
   StbUndoRecord          undo_rec [STB_TEXTEDIT_UNDOSTATECOUNT];
   STB_TEXTEDIT_CHARTYPE  undo_char[STB_TEXTEDIT_UNDOCHARCOUNT];
   short undo_point, redo_point;
   int undo_char_point, redo_char_point;
} StbUndoState;

typedef struct
{
   /////////////////////
   //
   // public data
   //

   int cursor;
   // position of the text cursor within the string

   int select_start;          // selection start point
   int select_end;
   // selection start and end point in characters; if equal, no selection.
   // note that start may be less than or greater than end (e.g. when
   // dragging the mouse, start is where the initial click was, and you
   // can drag in either direction)

   unsigned char insert_mode;
   // each textfield keeps its own insert mode state. to keep an app-wide
   // insert mode, copy this value in/out of the app state

   int row_count_per_page;
   // page size in number of row.
   // this value MUST be set to >0 for pageup or pagedown in multilines documents.

   /////////////////////
   //
   // private data
   //
   unsigned char cursor_at_end_of_line; // not implemented yet
   unsigned char initialized;
   unsigned char has_preferred_x;
   unsigned char single_line;
   unsigned char padding1, padding2, padding3;
   float preferred_x; // this determines where the cursor up/down tries to seek to along x
   StbUndoState undostate;
} STB_TexteditState;


////////////////////////////////////////////////////////////////////////
//
//     StbTexteditRow
//
// Result of layout query, used by stb_textedit to determine where
// the text in each row is.

// result of layout query
typedef struct
{
   float x0,x1;             // starting x location, end x location (allows for align=right, etc)
   float baseline_y_delta;  // position of baseline relative to previous row's baseline
   float ymin,ymax;         // height of row above and below baseline
   int num_chars;
} StbTexteditRow;

#  endif /* NC_API */
/* end_of_file */
#endif // NC_STB_TEXT_EDIT_H //

/*
// This C header file implements the guts of a multi-line text-editing
// widget; you implement display, word-wrapping, and low-level string
// insertion/deletion, and stb_textedit will map user inputs into
// insertions & deletions, plus updates to the cursor position,
// selection state, and undo state.
//
// It is intended for use in games and other systems that need to build
// their own custom widgets and which do not have heavy text-editing
// requirements (this library is not recommended for use for editing large
// texts, as its performance does not scale and it has limited undo).
//
//
// DEPENDENCIES
//
// Uses the C runtime function 'memmove', which you can override
// by defining STB_TEXTEDIT_memmove before the implementation.
// Uses no other functions. Performs no runtime allocations.
//
//
// VERSION HISTORY
//
//   1.13 (2019-02-07) fix bug in undo size management
//   1.12 (2018-01-29) user can change STB_TEXTEDIT_KEYTYPE, fix redo to avoid crash
//   1.11 (2017-03-03) fix HOME on last line, dragging off single-line textfield
//   1.10 (2016-10-25) supress warnings about casting away const with -Wcast-qual
//   1.9  (2016-08-27) customizable move-by-word
//   1.8  (2016-04-02) better keyboard handling when mouse button is down
//   1.7  (2015-09-13) change y range handling in case baseline is non-0
//   1.6  (2015-04-15) allow STB_TEXTEDIT_memmove
//   1.5  (2014-09-10) add support for secondary keys for OS X
//   1.4  (2014-08-17) fix signed/unsigned warnings
//   1.3  (2014-06-19) fix mouse clicking to round to nearest char boundary
//   1.2  (2014-05-27) fix some RAD types that had crept into the new code
//   1.1  (2013-12-15) move-by-word (requires STB_TEXTEDIT_IS_SPACE )
//   1.0  (2012-07-26) improve documentation, initial public release
//   0.3  (2012-02-24) bugfixes, single-line mode; insert mode
//   0.2  (2011-11-28) fixes to undo/redo
//   0.1  (2010-07-08) initial version
//
// ADDITIONAL CONTRIBUTORS
//
//   Ulf Winklemann: move-by-word in 1.1
//   Fabian Giesen: secondary key inputs in 1.5
//   Martins Mozeiko: STB_TEXTEDIT_memmove in 1.6
//
//   Bugfixes:
//      Scott Graham
//      Daniel Keller
//      Omar Cornut
//      Dan Thompson
//
// USAGE
//
// This file behaves differently depending on what symbols you define
// before including it.
//
//
// Header-file mode:
//
//   If you do not define STB_TEXTEDIT_IMPLEMENTATION before including this,
//   it will operate in "header file" mode. In this mode, it declares a
//   single public symbol, STB_TexteditState, which encapsulates the current
//   state of a text widget (except for the string, which you will store
//   separately).
//
//   To compile in this mode, you must define STB_TEXTEDIT_CHARTYPE to a
//   primitive type that defines a single character (e.g. char, wchar_t, etc).
//
//   To save space or increase undo-ability, you can optionally define the
//   following things that are used by the undo system:
//
//      STB_TEXTEDIT_POSITIONTYPE         small int type encoding a valid cursor position
//      STB_TEXTEDIT_UNDOSTATECOUNT       the number of undo states to allow
//      STB_TEXTEDIT_UNDOCHARCOUNT        the number of characters to store in the undo buffer
//
//   If you don't define these, they are set to permissive types and
//   moderate sizes. The undo system does no memory allocations, so
//   it grows STB_TexteditState by the worst-case storage which is (in bytes):
//
//        [4 + 3 * sizeof(STB_TEXTEDIT_POSITIONTYPE)] * STB_TEXTEDIT_UNDOSTATE_COUNT
//      +          sizeof(STB_TEXTEDIT_CHARTYPE)      * STB_TEXTEDIT_UNDOCHAR_COUNT
//
//
// Implementation mode:
//
//   If you define STB_TEXTEDIT_IMPLEMENTATION before including this, it
//   will compile the implementation of the text edit widget, depending
//   on a large number of symbols which must be defined before the include.
//
//   The implementation is defined only as static functions. You will then
//   need to provide your own APIs in the same file which will access the
//   static functions.
//
//   The basic concept is that you provide a "string" object which
//   behaves like an array of characters. stb_textedit uses indices to
//   refer to positions in the string, implicitly representing positions
//   in the displayed textedit. This is true for both plain text and
//   rich text; even with rich text stb_truetype interacts with your
//   code as if there was an array of all the displayed characters.
//
// Symbols that must be the same in header-file and implementation mode:
//
//     STB_TEXTEDIT_CHARTYPE             the character type
//     STB_TEXTEDIT_POSITIONTYPE         small type that is a valid cursor position
//     STB_TEXTEDIT_UNDOSTATECOUNT       the number of undo states to allow
//     STB_TEXTEDIT_UNDOCHARCOUNT        the number of characters to store in the undo buffer
//
// Symbols you must define for implementation mode:
//
//    STB_TEXTEDIT_STRING               the type of object representing a string being edited,
//                                      typically this is a wrapper object with other data you need
//
//    STB_TEXTEDIT_STRINGLEN(obj)       the length of the string (ideally O(1))
//    STB_TEXTEDIT_LAYOUTROW(&r,obj,n)  returns the results of laying out a line of characters
//                                        starting from character #n (see discussion below)
//    STB_TEXTEDIT_GETWIDTH(obj,n,i)    returns the pixel delta from the xpos of the i'th character
//                                        to the xpos of the i+1'th char for a line of characters
//                                        starting at character #n (i.e. accounts for kerning
//                                        with previous char)
//    STB_TEXTEDIT_KEYTOTEXT(k)         maps a keyboard input to an insertable character
//                                        (return type is int, -1 means not valid to insert)
//    STB_TEXTEDIT_GETCHAR(obj,i)       returns the i'th character of obj, 0-based
//    STB_TEXTEDIT_NEWLINE              the character returned by _GETCHAR() we recognize
//                                        as manually wordwrapping for end-of-line positioning
//
//    STB_TEXTEDIT_DELETECHARS(obj,i,n)      delete n characters starting at i
//    STB_TEXTEDIT_INSERTCHARS(obj,i,c*,n)   insert n characters at i (pointed to by STB_TEXTEDIT_CHARTYPE*)
//
//    STB_TEXTEDIT_K_SHIFT       a power of two that is or'd in to a keyboard input to represent the shift key
//
//    STB_TEXTEDIT_K_LEFT        keyboard input to move cursor left
//    STB_TEXTEDIT_K_RIGHT       keyboard input to move cursor right
//    STB_TEXTEDIT_K_UP          keyboard input to move cursor up
//    STB_TEXTEDIT_K_DOWN        keyboard input to move cursor down
//    STB_TEXTEDIT_K_PGUP        keyboard input to move cursor up a page
//    STB_TEXTEDIT_K_PGDOWN      keyboard input to move cursor down a page
//    STB_TEXTEDIT_K_LINESTART   keyboard input to move cursor to start of line  // e.g. HOME
//    STB_TEXTEDIT_K_LINEEND     keyboard input to move cursor to end of line    // e.g. END
//    STB_TEXTEDIT_K_TEXTSTART   keyboard input to move cursor to start of text  // e.g. ctrl-HOME
//    STB_TEXTEDIT_K_TEXTEND     keyboard input to move cursor to end of text    // e.g. ctrl-END
//    STB_TEXTEDIT_K_DELETE      keyboard input to delete selection or character under cursor
//    STB_TEXTEDIT_K_BACKSPACE   keyboard input to delete selection or character left of cursor
//    STB_TEXTEDIT_K_UNDO        keyboard input to perform undo
//    STB_TEXTEDIT_K_REDO        keyboard input to perform redo
//
// Optional:
//    STB_TEXTEDIT_K_INSERT              keyboard input to toggle insert mode
//    STB_TEXTEDIT_IS_SPACE(ch)          true if character is whitespace (e.g. 'isspace'),
//                                          required for default WORDLEFT/WORDRIGHT handlers
//    STB_TEXTEDIT_MOVEWORDLEFT(obj,i)   custom handler for WORDLEFT, returns index to move cursor to
//    STB_TEXTEDIT_MOVEWORDRIGHT(obj,i)  custom handler for WORDRIGHT, returns index to move cursor to
//    STB_TEXTEDIT_K_WORDLEFT            keyboard input to move cursor left one word // e.g. ctrl-LEFT
//    STB_TEXTEDIT_K_WORDRIGHT           keyboard input to move cursor right one word // e.g. ctrl-RIGHT
//    STB_TEXTEDIT_K_LINESTART2          secondary keyboard input to move cursor to start of line
//    STB_TEXTEDIT_K_LINEEND2            secondary keyboard input to move cursor to end of line
//    STB_TEXTEDIT_K_TEXTSTART2          secondary keyboard input to move cursor to start of text
//    STB_TEXTEDIT_K_TEXTEND2            secondary keyboard input to move cursor to end of text
//
// Keyboard input must be encoded as a single integer value; e.g. a character code
// and some bitflags that represent shift states. to simplify the interface, SHIFT must
// be a bitflag, so we can test the shifted state of cursor movements to allow selection,
// i.e. (STB_TEXTEDIT_K_RIGHT|STB_TEXTEDIT_K_SHIFT) should be shifted right-arrow.
//
// You can encode other things, such as CONTROL or ALT, in additional bits, and
// then test for their presence in e.g. STB_TEXTEDIT_K_WORDLEFT. For example,
// my Windows implementations add an additional CONTROL bit, and an additional KEYDOWN
// bit. Then all of the STB_TEXTEDIT_K_ values bitwise-or in the KEYDOWN bit,
// and I pass both WM_KEYDOWN and WM_CHAR events to the "key" function in the
// API below. The control keys will only match WM_KEYDOWN events because of the
// keydown bit I add, and STB_TEXTEDIT_KEYTOTEXT only tests for the KEYDOWN
// bit so it only decodes WM_CHAR events.
//
// STB_TEXTEDIT_LAYOUTROW returns information about the shape of one displayed
// row of characters assuming they start on the i'th character--the width and
// the height and the number of characters consumed. This allows this library
// to traverse the entire layout incrementally. You need to compute word-wrapping
// here.
//
// Each textfield keeps its own insert mode state, which is not how normal
// applications work. To keep an app-wide insert mode, update/copy the
// "insert_mode" field of STB_TexteditState before/after calling API functions.
//
// API
//
//    void stb_textedit_initialize_state(STB_TexteditState *state, int is_single_line)
//
//    void stb_textedit_click(STB_TEXTEDIT_STRING *str, STB_TexteditState *state, float x, float y)
//    void stb_textedit_drag(STB_TEXTEDIT_STRING *str, STB_TexteditState *state, float x, float y)
//    int  stb_textedit_cut(STB_TEXTEDIT_STRING *str, STB_TexteditState *state)
//    int  stb_textedit_paste(STB_TEXTEDIT_STRING *str, STB_TexteditState *state, STB_TEXTEDIT_CHARTYPE *text, int len)
//    void stb_textedit_key(STB_TEXTEDIT_STRING *str, STB_TexteditState *state, STB_TEXEDIT_KEYTYPE key)
//
//    Each of these functions potentially updates the string and updates the
//    state.
//
//      initialize_state:
//          set the textedit state to a known good default state when initially
//          constructing the textedit.
//
//      click:
//          call this with the mouse x,y on a mouse down; it will update the cursor
//          and reset the selection start/end to the cursor point. the x,y must
//          be relative to the text widget, with (0,0) being the top left.
//     
//      drag:
//          call this with the mouse x,y on a mouse drag/up; it will update the
//          cursor and the selection end point
//     
//      cut:
//          call this to delete the current selection; returns true if there was
//          one. you should FIRST copy the current selection to the system paste buffer.
//          (To copy, just copy the current selection out of the string yourself.)
//     
//      paste:
//          call this to paste text at the current cursor point or over the current
//          selection if there is one.
//     
//      key:
//          call this for keyboard inputs sent to the textfield. you can use it
//          for "key down" events or for "translated" key events. if you need to
//          do both (as in Win32), or distinguish Unicode characters from control
//          inputs, set a high bit to distinguish the two; then you can define the
//          various definitions like STB_TEXTEDIT_K_LEFT have the is-key-event bit
//          set, and make STB_TEXTEDIT_KEYTOCHAR check that the is-key-event bit is
//          clear. STB_TEXTEDIT_KEYTYPE defaults to int, but you can #define it to
//          anything other type you wante before including.
//
//     
//   When rendering, you can read the cursor position and selection state from
//   the STB_TexteditState.
//
//
// Notes:
//
// This is designed to be usable in IMGUI, so it allows for the possibility of
// running in an IMGUI that has NOT cached the multi-line layout. For this
// reason, it provides an interface that is compatible with computing the
// layout incrementally--we try to make sure we make as few passes through
// as possible. (For example, to locate the mouse pointer in the text, we
// could define functions that return the X and Y positions of characters
// and binary search Y and then X, but if we're doing dynamic layout this
// will run the layout algorithm many times, so instead we manually search
// forward in one pass. Similar logic applies to e.g. up-arrow and
// down-arrow movement.)
//
// If it's run in a widget that *has* cached the layout, then this is less
// efficient, but it's not horrible on modern computers. But you wouldn't
// want to edit million-line files with it.

*/