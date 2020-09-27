#ifndef _MAGE_HEX_H
#define _MAGE_HEX_H

#include "mage.h"
#include "../../modules/led.h"
#include "../../../fonts/Monaco9.h"
#include "../../../fonts/DeterminationMono.h"
#include "../../../fonts/Scientifica.h"
#include "FrameBuffer.h"

#define BYTES_PER_PAGE 192
#define BYTES_PER_ROW 16
#define BYTE_OFFSET_X 12
#define BYTE_OFFSET_Y 40
#define BYTE_WIDTH 19
#define BYTE_HEIGHT 14
#define BYTE_CURSOR_OFFSET_X -4
#define BYTE_CURSOR_OFFSET_Y 5
#define HEX_TICK_DELAY 7

enum HEX_OPS {
	HEX_OPS_XOR,
	HEX_OPS_ADD,
	HEX_OPS_SUB
};

extern FrameBuffer *mage_canvas;

extern uint16_t hex_cursor;
extern uint8_t *hexEditorState;
extern void set_hex_op(enum HEX_OPS op);
extern void apply_input_to_hex_state();
extern void toggle_hex_editor();
extern void update_hex_lights();
extern void update_hex_editor();
extern void render_hex_editor();

#endif //_MAGE_HEX_H